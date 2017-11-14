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
#include "libbdk-arch/bdk-csrs-fpa.h"
#include "libbdk-arch/bdk-csrs-pki.h"
#include "libbdk-arch/bdk-csrs-sso.h"

extern const uint64_t __BDK_PKI_MICROCODE_CN8XXX[];
extern const int __BDK_PKI_MICROCODE_CN8XXX_LENGTH;

/* PKI global variables */
typedef struct
{
    int next_free_qpg_table;
    int next_free_pknd;
    int next_free_dstat;
    int next_wqe_grp;
} global_node_state_t;

static global_node_state_t global_node_state[BDK_NUMA_MAX_NODES];

/**
 * One time init of global Packet Input
 *
 * @return Zero on success, negative on failure
 */
int bdk_pki_global_init(bdk_node_t node)
{
    global_node_state_t *node_state = &global_node_state[node];
    bdk_zero_memory(node_state, sizeof(*node_state));

    /* Load microcode */
    for (int i=0; i<__BDK_PKI_MICROCODE_CN8XXX_LENGTH; i++)
        BDK_CSR_WRITE(node, BDK_PKI_IMEMX(i), __BDK_PKI_MICROCODE_CN8XXX[i]);

    BDK_CSR_INIT(fpa_const, node, BDK_FPA_CONST);
    BDK_CSR_INIT(pki_const, node, BDK_PKI_CONST);
    BDK_CSR_INIT(pki_const1, node, BDK_PKI_CONST1);

    /* Setup all Auras to support backpressure */
    for (int aura = 0; aura < fpa_const.s.auras; aura++)
    {
        BDK_CSR_MODIFY(c, node, BDK_PKI_AURAX_CFG(aura),
            c.s.ena_bp = 1; /* Enable backpressure */
            c.s.bpid = aura); /* 1:1 mapping between aura and bpid */
    }
    /* Setup defaults for PKNDs on all parsing clusters */
    for (int cluster=0; cluster<pki_const1.s.cls; cluster++)
    {
        for (int pknd = 0; pknd < pki_const.s.pknds; pknd++)
        {
            /* Set all PKNDS to be the correct SSO tag type */
            BDK_CSR_MODIFY(c, node, BDK_PKI_CLX_STYLEX_ALG(cluster, pknd),
                c.s.tt = BDK_SSO_TT_E_UNTAGGED);
            /* Set all PKNDS to use style of same number */
            BDK_CSR_MODIFY(c, node, BDK_PKI_CLX_PKINDX_STYLE(cluster, pknd),
                c.s.pm = 0;
                c.s.style = pknd);
        }
    }
    /* Allow PKI to parse Higig headers. The BDK currently doesn't use
        any other parsing */
    BDK_CSR_MODIFY(c, node, BDK_PKI_GBL_PEN,
        c.s.hg_pen = 1);
    /* Put all clusters in same cluster group */
    BDK_CSR_MODIFY(c, node, BDK_PKI_ICGX_CFG(0),
        c.s.clusters = (1<<pki_const1.s.cls)-1;
        c.s.delay = 800/pki_const1.s.cls; /* Per hrm formula, reset value is not suitable */
        );
    int buffer_size = bdk_fpa_get_block_size(node, BDK_FPA_PACKET_POOL);
    /* Set how the styles buffer to memory */
    for (int style = 0; style < pki_const.s.fstyles; style++)
    {
        BDK_CSR_MODIFY(c, node, BDK_PKI_STYLEX_BUF(style),
            c.s.wqe_hsz = 0; /* WQE uses word 0..4 */
            c.s.wqe_skip = 0; /* WQE starts at beginning of buffer */
            c.s.first_skip = 6; /* Room for WQE */
            c.s.later_skip = 0; /* NO 2nd skip */
            c.s.opc_mode = 1; /* all packet data and next-buffer pointers are written into the cache */
            c.s.dis_wq_dat = 0; /* Packet follows WQE */
            c.s.mb_size = buffer_size/8);
        /* OR bits for WQE word 2 */
        BDK_CSR_WRITE(node, BDK_PKI_STYLEX_WQ2(style), 0);
        /* OR bits for WQE word 4 */
        BDK_CSR_WRITE(node, BDK_PKI_STYLEX_WQ4(style), 0);
    }
    return 0;
}

/**
 * Configure packet input for a specific port. This is called for each
 * port on every interface that is connected to packet input.
 *
 * @param handle Handle for port to config
 *
 * @return Zero on success, negative on failure
 */
int bdk_pki_port_init(bdk_if_handle_t handle)
{
    global_node_state_t *node_state = &global_node_state[handle->node];

    BDK_CSR_INIT(pki_const, handle->node, BDK_PKI_CONST);
    BDK_CSR_INIT(pki_const1, handle->node, BDK_PKI_CONST1);
    BDK_CSR_INIT(pki_const2, handle->node, BDK_PKI_CONST2);
    BDK_CSR_INIT(sso_const, handle->node, BDK_SSO_CONST);

    /* Make sure we have room in the QPG table */
    if (node_state->next_free_qpg_table >= pki_const2.s.qpgs)
    {
        bdk_error("PKI QPG table full\n");
        return -1;
    }

    /* Make sure we have room in the DSTAT table */
    if (node_state->next_free_dstat >= pki_const2.s.dstats)
    {
        bdk_error("PKI DSTAT table full\n");
        return -1;
    }

    /* We give one PKND for each port because pki uses dstat(pkind) */
    if (node_state->next_free_pknd >= pki_const.s.pknds)
    {
        bdk_error("PKI ran out of PKNDs\n");
        return -1;
    }

    /* Give each aura 1/4 of the available buffers. Just a guess */
    int aura_max_count = BDK_CSR_READ(handle->node, BDK_FPA_VHPOOLX_AVAILABLE(BDK_FPA_PACKET_POOL)) / 4;
    int aura = bdk_fpa_init_aura(handle->node, -1, BDK_FPA_PACKET_POOL, aura_max_count);
    if (aura < 0)
        return -1;
    handle->aura = aura;

    /* Find the PKND for this port.
     * It relies on single-channel-per-bgx_port schema.
     */
    if ((handle->iftype == BDK_IF_PCIE) && handle->index)
        handle->pknd = node_state->next_free_pknd - 1;
    else
        handle->pknd = node_state->next_free_pknd++;

    /* Setup QPG table per channel */
    int qpg = node_state->next_free_qpg_table++;
    /* Setup DSTAT table per channel */
    handle->pki_dstat = node_state->next_free_dstat++;

    /* Set PKI to use the right backpressure id for this port. We use
        a 1:1 mapping between aura and bpid */
    BDK_CSR_MODIFY(c, handle->node, BDK_PKI_CHANX_CFG(handle->pki_channel),
        c.s.bpid = handle->aura);
    /* Setup all PKI clusters */
    for (int cluster = 0; cluster < pki_const1.s.cls; cluster++)
    {
        int qpg_base = qpg;
        int style = handle->pknd;
        /* Configure PKI style */
        BDK_CSR_MODIFY(c, handle->node, BDK_PKI_CLX_STYLEX_CFG(cluster, style),
            c.s.lenerr_en = 0; /* Don't check L2 length */
            /* FCS is already checked and stripped by BGX, LBK does not have it */
            c.s.fcs_strip = 0; /* Don't strip FCS as there is none */
            c.s.fcs_chk = 0 ; /* (handle->flags & BDK_IF_FLAGS_HAS_FCS) ? 1 : 0; */
            c.s.qpg_dis_padd = 1; /* Don't use QPG for port */
            c.s.qpg_dis_grp = 0; /* Use QPG for group */
            c.s.qpg_dis_aura = 0; /* Use QPG for aura */
            c.s.qpg_base = qpg_base); /* Base for QPG */
        /* FIXME: Tell PKI to compute checksum */
        BDK_CSR_MODIFY(c, handle->node, BDK_PKI_CLX_STYLEX_CFG2(cluster, style),
            c.s.csum_lb = 0);
    }
    /* Tell PKI to use cluster group 0 for this PKND */
    BDK_CSR_MODIFY(c, handle->node, BDK_PKI_PKINDX_ICGSEL(handle->pknd),
        c.s.icg = 0);
    /* Round robbin through groups. It isn't obvious, but the node
        number is embedded into the group */
    int wqe_grp = node_state->next_wqe_grp | (handle->node << 8);
    node_state->next_wqe_grp = (node_state->next_wqe_grp+1) & (sso_const.s.grp-1);
    BDK_CSR_MODIFY(c, handle->node, BDK_PKI_QPG_TBLX(qpg),
        c.s.padd = 0; /* Set WQE[CHAN] */
        c.s.grp_ok = wqe_grp; /* Set WQE[GRP] */
        c.s.grp_bad = wqe_grp; /* Set WQE[GRP] */
        c.s.gaura = handle->aura); /* Set WQE[AURA] */
    BDK_CSR_MODIFY(c, handle->node, BDK_PKI_QPG_TBLBX(qpg),
        c.s.pkt_add = 0; /* Increment was already done in FPA alloc */
        c.s.ena_red = 1; /* Enable RED */
        c.s.ena_drop = 1; /* Enable drop */
        c.s.strm = 0; /* Stream ID for looking up GMID */
        c.s.dstat_id = handle->pki_dstat);
    /* Setup stream ID 0 */
    BDK_CSR_MODIFY(c, handle->node, BDK_PKI_STRMX_CFG(0),
        c.s.gmid = 1);
    bdk_sso_register_handle(handle);
    return 0;
}

/**
 * Enable PKI after all setup is complete
 *
 * @return Zero on success, negative on failure
 */
int bdk_pki_enable(bdk_node_t node)
{
    BDK_CSR_MODIFY(c, node, BDK_PKI_BUF_CTL,
        c.s.fpa_wait = 0; /* Drop packets on FPA buffer shortage */
        c.s.pbp_en = 1; /* Enable backpressure */
        c.s.pki_en = 1); /* Enable PKI */
    /* Enable cluster group 0 */
    BDK_CSR_MODIFY(c, node, BDK_PKI_ICGX_CFG(0),
        c.s.pena = 1);
    return 0;
}

/**
 * Query PKI and fill in the receive stats for the supplied interface handle. The
 * interface must use PKI for RX.
 *
 * @param handle Port handle
 *
 * @return
 */
void bdk_pki_fill_rx_stats(bdk_if_handle_t handle)
{
 /* Account for RX stripping FCS */
    const int bytes_off_rx = (handle->flags & BDK_IF_FLAGS_HAS_FCS) ? 4 : 0;

    BDK_CSR_INIT(dstat_pkts, handle->node, BDK_PKI_DSTATX_STAT0(handle->pki_dstat)); /* 32 bits */
    BDK_CSR_INIT(dstat_octs, handle->node, BDK_PKI_DSTATX_STAT1(handle->pki_dstat)); /* 40 bits */
    BDK_CSR_INIT(dstat_errs, handle->node, BDK_PKI_DSTATX_STAT2(handle->pki_dstat)); /* 32 bits */
    BDK_CSR_INIT(dstat_drps, handle->node, BDK_PKI_DSTATX_STAT3(handle->pki_dstat)); /* 32 bits */
    BDK_CSR_INIT(dstat_doct, handle->node, BDK_PKI_DSTATX_STAT4(handle->pki_dstat)); /* 40 bits */

    handle->stats.rx.octets         -= handle->stats.rx.packets * bytes_off_rx;
    handle->stats.rx.packets         = bdk_update_stat_with_overflow(dstat_pkts.u, handle->stats.rx.packets, 32);
    handle->stats.rx.octets          = bdk_update_stat_with_overflow(dstat_octs.u, handle->stats.rx.octets, 40);
    handle->stats.rx.octets         += handle->stats.rx.packets * bytes_off_rx;

    handle->stats.rx.errors          = bdk_update_stat_with_overflow(dstat_errs.u, handle->stats.rx.errors, 32);
    handle->stats.rx.dropped_packets = bdk_update_stat_with_overflow(dstat_drps.u, handle->stats.rx.dropped_packets, 32);
    handle->stats.rx.dropped_octets  = bdk_update_stat_with_overflow(dstat_doct.u, handle->stats.rx.dropped_octets, 40);
}
