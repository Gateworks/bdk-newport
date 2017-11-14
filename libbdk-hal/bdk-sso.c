/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pki.h"
#include "libbdk-arch/bdk-csrs-sso.h"
#include "libbdk-arch/bdk-csrs-ssow.h"

/* Channels is 12 bits in WQE. This contains pointers to 1024 element arrays
   for each node. They are not allocated until a network interface is required
   for the node to save space */
static bdk_if_handle_t *sso_map[BDK_NUMA_MAX_NODES] = { NULL, };

/**
 * Initialize the SSO
 *
 * @return Zero on success, negative on failure
 */
int bdk_sso_init(bdk_node_t node)
{
    BDK_CSR_INIT(sso_const, node, BDK_SSO_CONST);
    BDK_CSR_INIT(sso_const1, node, BDK_SSO_CONST1);

    /* No work slot retries */
    BDK_CSR_MODIFY(c, node, BDK_SSO_GWE_CFG,
        c.s.ws_retries = 0);
    /* Set no-work timer, units of 1024 SCLK
       0=1024 2=2048 3=3072 ... */
    BDK_CSR_MODIFY(c, node, BDK_SSO_NW_TIM,
        c.s.nw_tim = 0);

    /* Setup an FPA pool to store the SSO queues */
    /* Need two per group, one per hardware work slot (HWS) + some for
       memory spillage */
    const int MEM_SPILL = 1024; /* Number of WQE that can spill to DRAM */
    int num_blocks = sso_const.s.grp*3 + 48 + ((MEM_SPILL + sso_const1.s.xae_waes-1) / sso_const1.s.xae_waes);
    if (bdk_fpa_fill_pool(node, BDK_FPA_SSO_POOL, num_blocks))
        return -1;
    const int aura = BDK_FPA_SSO_POOL; /* Use 1:1 mapping aura */

    /* Initialize the group/qos queues */
    for (int grp=0; grp<sso_const.s.grp; grp++)
    {
        void *buffer = bdk_fpa_alloc(node, aura);
        if (buffer == NULL)
        {
            bdk_error("sso_init: Failed to allocate buffer\n");
            return -1;
        }
        uint64_t addr = bdk_ptr_to_phys(buffer);
        BDK_CSR_MODIFY(c, node, BDK_SSO_XAQX_HEAD_PTR(grp),
            c.s.ptr = addr >> 7;
            c.s.cl = 0);
        BDK_CSR_MODIFY(c, node, BDK_SSO_XAQX_HEAD_NEXT(grp),
            c.s.ptr = addr >> 7);
        BDK_CSR_MODIFY(c, node, BDK_SSO_XAQX_TAIL_PTR(grp),
            c.s.ptr = addr >> 7;
            c.s.cl = 0);
        BDK_CSR_MODIFY(c, node, BDK_SSO_XAQX_TAIL_NEXT(grp),
            c.s.ptr = addr >> 7);
        BDK_CSR_MODIFY(c, node, BDK_SSO_VHGRPX_QCTL(grp),
            c.s.ena = 1);
    }
    /* Set the aura number */
    BDK_CSR_MODIFY(c, node, BDK_SSO_XAQ_AURA,
        c.s.laura = aura);
    /* Set the GMID to global for SSO internal allocations */
    BDK_CSR_MODIFY(c, node, BDK_SSO_XAQ_GMCTL,
        c.s.gmid = 1);
    /* Setup how the SSO accesses memory */
    BDK_CSR_MODIFY(c, node, BDK_SSO_AW_CFG,
        c.s.rwen = 1);

    /* Setup the group mask for hardware work slots (HWS) */
    for (int hws=0; hws < sso_const.s.hws; hws++)
    {
        for (int group_set = 0; group_set < 2; group_set++)
        {
            /* CN83XX has only one bank */
            BDK_CSR_WRITE(node, BDK_SSO_HWSX_SX_GRPMSKX(hws, group_set, 0), -1);
        }
    }
    return 0;
}

/**
 * Register a bdk-if handle with the SSO code so the SSO can be used to receive
 * traffic from it.
 *
 * @param handle Handle to register
 */
void bdk_sso_register_handle(bdk_if_handle_t handle)
{
    if (sso_map[handle->node] == NULL)
    {
        /* Channels is 12 bits in WQE */
        sso_map[handle->node] = calloc(0x1000, sizeof(bdk_if_handle_t));
        if (sso_map[handle->node] == NULL)
        {
            bdk_error("N%d.SSO: Failed to allocate channel mapping table\n", handle->node);
            return;
        }
    }
    sso_map[handle->node][handle->pki_channel] = handle;
}

/**
 * Convert a WQE into a BDK packet
 *
 * @param work   Pointer to WQE to convert
 * @param packet Packet to receive the data
 *
 * @return Zero on success, negative on failure
 */
static int bdk_sso_wqe_to_packet(const void *work, bdk_if_packet_t *packet)
{
    const union bdk_pki_wqe_s *wqe = work;
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
    union bdk_pki_wqe_s wqe_be;
    for (int i = 0; i < 16; i++)
        wqe_be.u[i] = bdk_le64_to_cpu(wqe->u[i]);
    wqe = &wqe_be;
#endif
    const bdk_node_t input_node = wqe->s.node;
    if (bdk_likely(sso_map[input_node]))
        packet->if_handle = sso_map[input_node][wqe->s.chan];
    else
        packet->if_handle = NULL;
    packet->length = wqe->s.len;
    packet->segments = wqe->s.bufs;
    /* Error combines word2[errlev] and word2[opcode] into 11 bits */
    packet->rx_error = (wqe->s.errlev << 8) | wqe->s.opcode;
    if (bdk_unlikely(wqe->s.bufs > 12))
        bdk_fatal("WQE has too many segments %d > 12\n", wqe->s.bufs);

    union bdk_pki_buflink_s buflink;
    buflink.s.addr = wqe->s.addr;
    buflink.s.size = wqe->s.size;
    for (int seg = 0; seg < packet->segments; seg++)
    {
        packet->packet[seg].u = 0;
        packet->packet[seg].s.size = buflink.s.size;
        packet->packet[seg].s.address = buflink.s.addr;
        if (seg + 1 < packet->segments)
        {
            buflink = *(union bdk_pki_buflink_s *)bdk_phys_to_ptr(buflink.s.addr - sizeof(union bdk_pki_buflink_s));
            buflink.u[0] = bdk_le64_to_cpu(buflink.u[0]);
            buflink.u[1] = bdk_le64_to_cpu(buflink.u[1]);
        }
    }

    if (bdk_unlikely(!packet->if_handle))
    {
        bdk_error("Unable to find IF for packet to port %d\n", wqe->s.chan);
        return -1;
    }

    return 0;
}


/**
 * Function called during bdk_thread_yield() to process work while we're idle
 */
void bdk_sso_process_work(void)
{
    bdk_if_packet_t packet;
    bdk_node_t node = bdk_numa_local();
    /* Build the offset into SSO */
    union bdk_ssow_get_work_addr_s work_offset = {  .u = 0 };
    work_offset.s.waitw = 1; /* Wait for work */
    work_offset.s.index_ggrp_mask = 1; /* Use mask_set 0*/
    work_offset.s.grouped = 0;	       /* ... */
    work_offset.s.indexed = 0;         /* ... */

    while (true)
    {
        /* We recalculate work address here to allow for called functions
        ** to use wait/yield/printf */
        /* Get the base into SSO */
        uint64_t work_address = BDK_SSOW_VHWSX_OP_GET_WORK1(bdk_get_core_num());
        /* Add the base and offset to get the final GET_WORK address */
        work_address += work_offset.u;
        /* Do a GET_WORK */
        bdk_ssow_vhwsx_op_get_work1_t work1;
        work1.u = bdk_le64_to_cpu(bdk_read64_uint64(work_address));
        if (!work1.u)
            break;
        const union bdk_pki_wqe_s *wqe = bdk_phys_to_ptr(work1.u);
        if (bdk_sso_wqe_to_packet(wqe, &packet) == 0)
            bdk_if_dispatch_packet(&packet);
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        int aura = bdk_extract(bdk_le64_to_cpu(wqe->u[0]), 48, 12);
#else
        int aura = wqe->s.aura;
#endif
        for (int s = 0; s < packet.segments; s++)
            __bdk_fpa_raw_free(node, packet.packet[s].s.address & (0xffffffffffffffffULL ^ BDK_CACHE_LINE_MASK), aura, 0);
    }
}
