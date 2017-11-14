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
#include <malloc.h> // for memalign
#include "libbdk-arch/bdk-csrs-bgx.h"
#include "libbdk-arch/bdk-csrs-dpi.h"
#include "libbdk-arch/bdk-csrs-lbk.h"
#include "libbdk-arch/bdk-csrs-pki.h"
#include "libbdk-arch/bdk-csrs-pko.h"

#define PKO_MAX_DQ 256 /* CN83XX, Must be a define as it sizes static arrays */
static const int PKO_QUEUES_PER_CHANNEL = 1; /* Number of DQ connected to each LMAC */
static const int DQ_FC_NOMINAL_DEPTH = 31; /* PKO pages from FPA for each DQ.
                                    According to HW (Brian Folsom) opening DQ
                                    preallocates 4 pages */
static const int DQ_FC_HYST_BITS = 2; /* Hysteresis bits must be a max of 2 bits less than DQ_FC_NOMINAL_DEPTH */
static const int DQ_FC_SKID = 4; /* Number of buffers to use as slop when
                                    stopping on full DQ */
#define FC_STRIDE 16 /* Stride in bytes between DQ_FC entries in memory. Can be
                                    either 16 or 128. Must be a define */

/* PKO global variables */
typedef struct
{
    /* Queue depth flow control counters. Volatile as hardware updates
       asynchronously */
    volatile int64_t pko_fc_depth[PKO_MAX_DQ * FC_STRIDE / sizeof(uint64_t)] BDK_CACHE_LINE_ALIGNED;
    uint64_t pko_dq_send[PKO_MAX_DQ]; /* The address of PKO_VFX_DQX_OP_SENDX */
    uint64_t pko_free_fifo_mask;    /* PKO_PTGFX_CFG(5) is reserved for NULL MAC */
    int pko_next_free_port_queue;   /* L1 = Port Queues are 0-31 (CN83XX) */
    int pko_next_free_l2_queue;     /* L2 = Channel Queues 0-255 (CN83XX) */
    int pko_next_free_l3_queue;     /* L3 = Channel Queues 0-255 (CN83XX) */
    int pko_next_free_descr_queue;  /* L6 = Descriptor Queues 0-255 (CN83XX) */
} global_node_state_t;

static global_node_state_t *global_node_state[BDK_NUMA_MAX_NODES] = { NULL, };

/**
 * Perform global init of PKO
 *
 * @return Zero on success, negative on failure
 */
int bdk_pko_global_init(bdk_node_t node)
{
    global_node_state[node] = memalign(BDK_CACHE_LINE_SIZE, sizeof(global_node_state_t));
    if (global_node_state[node] == NULL)
    {
        bdk_error("N%d.PKO: Failed to allocate global state\n", node);
        return -1;
    }
    global_node_state_t *node_state = global_node_state[node];
    bzero(node_state,sizeof(*node_state));

    BDK_CSR_INIT(pko_const, node, BDK_PKO_CONST);
    node_state->pko_free_fifo_mask = bdk_build_mask((pko_const.s.ptgfs - 1) * 4);
    int num_buffers = DQ_FC_NOMINAL_DEPTH * PKO_MAX_DQ;
    if (bdk_fpa_fill_pool(node, BDK_FPA_PKO_POOL, num_buffers))
        return -1;
    const int aura = BDK_FPA_PKO_POOL; /* Use 1:1 mapping aura */
    BDK_CSR_MODIFY(c, node, BDK_PKO_DPFI_FPA_AURA,
        c.s.laura = aura);
    BDK_CSR_MODIFY(c, node, BDK_PKO_DPFI_GMCTL,
        c.s.gmid = 1);
    BDK_CSR_MODIFY(c, node, BDK_PKO_DPFI_ENA,
        c.s.enable = 1);
    BDK_CSR_MODIFY(c, node, BDK_PKO_PTF_IOBP_CFG,
        c.s.iobp1_ds_opt = 1; /* Optimize IOBP1 requests when data is to be dropped */
        c.s.iobp1_magic_addr = bdk_numa_get_address(node, 0) >> 7;
        c.s.max_read_size = 16); /* Maximum number of IOBP1 read requests outstanding */
    BDK_CSR_MODIFY(c, node, BDK_PKO_PDM_CFG,
        c.s.pko_pad_minlen = 60; /* When padding, min is 60 bytes before FCS */
        c.s.alloc_lds = 1; /* Allocate DQ fetches in L2 */
        c.s.alloc_sts = 1); /* Allocate DQ stores in L2 */
    BDK_CSR_MODIFY(c, node, BDK_PKO_PDM_CFG,
        c.s.dq_fc_sa = 0; /* Allocate to L2 */
        c.s.dq_fc_skid = DQ_FC_SKID); /* Allow for SKID worth of requests in flight for flow control*/
    /* Configure format 0 so that if marking is used, yellow packets are
       marked with a 1 and red packets are marked with a 2. Set the mask
       so we change all four possible bits. Set the offset to 12, which causes
       the bits to be the lower 4 bits of the IPv4 TOS byte */
    BDK_CSR_MODIFY(c, node, BDK_PKO_FORMATX_CTL(0),
        c.s.offset = 12; /* Skip IP header, Lower 4 bits of TOS */
        c.s.y_mask = 0xe; /* Clear bits 3:1 */
        c.s.y_val = 0x1; /* Set bit 0 */
        c.s.r_mask = 0xd; /* Clear bits 3:2,0 */
        c.s.r_val = 0x2); /* Set bit 1 */

    /* Put FIFOs in reset */
    for (int i = 0; i < pko_const.s.ptgfs; i++)
        BDK_CSR_MODIFY(c, node, BDK_PKO_PTGFX_CFG(i), c.s.reset = 1);

    return 0;
}

/**
 * Dynamically allocate a PKO fifo for a port
 *
 * @param lmac   Logical mac to use (0-27)
 * @param size   The size needed in 2.5kb chunks (1,2,4).
 *
 * @return Fifo number of negative on failure
 */
static int __bdk_pko_allocate_fifo(bdk_node_t node, int lmac, int size)
{
    global_node_state_t *node_state = global_node_state[node];

    BDK_CSR_INIT(pko_const, node, BDK_PKO_CONST);
    int max_fifo = (pko_const.s.ptgfs-1) * 4; /* Minus one as NULL MAC is an entry */
    /* Start at 0 znd look for a fifo location that has enough
        consecutive space */
    int fifo = 0;
    while (fifo < max_fifo)
    {
        /* Buid a mask representing what this fifo would use */
        uint64_t mask = bdk_build_mask(size) << fifo;
        /* Stop search if all bits are free */
        if ((mask & node_state->pko_free_fifo_mask) == mask)
        {
            /* Found a spot, mark it used and stop searching */
            node_state->pko_free_fifo_mask &= ~mask;
            break;
        }
        /* Increment by size to keep alignment */
        fifo += size;
    }
    /* Check if didn't have space */
    if (fifo >= max_fifo)
    {
        bdk_error("pko_allocate_fifo: Tried to allocate too many fifos lmac %d size %d mask 0x%06x\n", lmac, size, (int) node_state->pko_free_fifo_mask);
        return -1;
    }
    /* Program the PKO fifo. Each PKO_PTGFX_CFG represents a cluster of four
        FIFOs */
    int index = fifo >> 2;
    BDK_CSR_INIT(cfg, node, BDK_PKO_PTGFX_CFG(index));
    cfg.s.reset = 1;
    cfg.s.rate = 1; /* Default rate for all ports is 12.5 Gb/s */
    switch (cfg.s.size)
    {
        case 0: /* 2.5kb, 2.5kb, 2.5kb, 2.5kb */
            switch (size)
            {
                case 1:
                    cfg.s.size = 0; /* 2.5kb for all */
                    break;
                case 2:
                    if (fifo & 2)
                        cfg.s.size = 2; /* 2.5kb, 2.5kb, 5kb */
                    else
                        cfg.s.size = 1; /* 5kb, 2.5kb, 2.5kb */
                    break;
                default: /* 4 */
                    cfg.s.size = 4; /* 10kb */
                    cfg.s.rate = 3; /* Large FIFOs are for 40G links, use 50 Gb/s */
                    break;
            }
            break;
        case 1: /* 5kb, 2.5kb, 2.5kb */
            /* Can only possible combine the two 2.5kb */
            switch (size)
            {
                case 1:
                    /* No change */
                    cfg.s.size = 1; /* 5kb, 2.5kb, 2.5kb */
                    break;
                case 2:
                    /* 2nd buffer is now 5kb */
                    cfg.s.size = 3; /* 5kb, 5kb */
                    cfg.s.rate = 2; /* Use 25 Gb/s rate */
                    break;
                default: /* 4 */
                    /* This shouldn't be possible */
                    bdk_fatal("Illegal fifo size\n");
                    break;
            }
            break;
        case 2: /* 2.5kb, 5kb - already allocated */
            if (1 != size)
                bdk_fatal("Illegal fifo size\n");
            /* we may be allocating into the 2.5kb, <unused 2.5kb>, 5kb */
            break;
        case 3: /* 5kb, 5kb - already allocated */
            /* This shouldn't be possible */
            bdk_fatal("Illegal fifo size\n");
            break;
        default: /* 10kb - already allocated */
            /* This shouldn't be possible */
            bdk_fatal("Illegal fifo size\n");
            break;
    }
    BDK_CSR_WRITE(node, BDK_PKO_PTGFX_CFG(index), cfg.u);

    /* Setup PKO MCI1 credits */
    int mac_buffering;
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
    {
        switch (lmac)
        {
            case BDK_PKO_LMAC_E_LOOPBACK_0:
            case BDK_PKO_LMAC_E_LOOPBACK_1:
            {
                BDK_CSR_INIT(lbkx_const, node, BDK_LBKX_CONST( (lmac != BDK_PKO_LMAC_E_LOOPBACK_0)  ? 2 : 0));
                mac_buffering = lbkx_const.s.buf_size;
                break;
            }
            case BDK_PKO_LMAC_E_DPI:
            {
                BDK_CSR_INIT(sdpx_const, node, BDK_SDPX_CONST(0));
                mac_buffering = sdpx_const.s.fifosz;
                break;
            }
            default: /* BGX */
            {
                BDK_CSR_INIT(bgxx_const, node, BDK_BGXX_CONST(0));
                mac_buffering = bgxx_const.s.tx_fifosz * size / 4;
                break;
            }
        }
    }
    else
        bdk_fatal("Update __bdk_pko_allocate_fifo() for this chip");
    /* Confine the credits to not overflow the LBK FIFO */
    BDK_CSR_MODIFY(c, node, BDK_PKO_MCI1_MAX_CREDX(lmac),
        c.s.max_cred_lim = mac_buffering / 16);
    return fifo;
}

/**
 * Configure PKO for a specific port. This is called for each
 * port on every interface that connects to PKO.
 *
 * @param handle Handle for port to config
 *
 * @return Zero on success, negative on failure
 */
int bdk_pko_port_init(bdk_if_handle_t handle)
{
    global_node_state_t *node_state = global_node_state[handle->node];
    int pq;     /* L1 = port queue */
    int sq_l2;  /* L2 = schedule queue feeding PQ */
    int sq_l3;  /* L3 = schedule queue feeding L2 */
    int dq;     /* L4 = descriptor queue feeding L3 */

    BDK_CSR_INIT(pko_l2_const, handle->node, BDK_PKO_L2_CONST);
    if (node_state->pko_next_free_l2_queue >= pko_l2_const.s.count)
    {
        bdk_error("pko_port_init: Ran out of L2 queues\n");
        return -1;
    }
    BDK_CSR_INIT(pko_l3_const, handle->node, BDK_PKO_L3_CONST);
    if (node_state->pko_next_free_l3_queue >= pko_l3_const.s.count)
    {
        bdk_error("pko_port_init: Ran out of L3 queues\n");
        return -1;
    }
    BDK_CSR_INIT(pko_dq_const, handle->node, BDK_PKO_DQ_CONST);
    if (node_state->pko_next_free_descr_queue > pko_dq_const.s.count - PKO_QUEUES_PER_CHANNEL)
    {
        bdk_error("pko_port_init: Ran out of descriptor (L6) queues\n");
        return -1;
    }

    if ((handle->index == 0) || (handle->iftype == BDK_IF_BGX))
    {
        BDK_CSR_INIT(pko_l1_const, handle->node, BDK_PKO_L1_CONST);
        if (node_state->pko_next_free_port_queue >= pko_l1_const.s.count)
        {
            bdk_error("pko_port_init: Ran out of port (L1) queues\n");
            return -1;
        }
        pq = node_state->pko_next_free_port_queue++;
    }
    else
    {
        /* This relies on channels being initialized in order */
        pq = node_state->pko_next_free_port_queue - 1;
    }

    sq_l2 = node_state->pko_next_free_l2_queue++;
    sq_l3 = node_state->pko_next_free_l3_queue++;
    dq = node_state->pko_next_free_descr_queue;
    node_state->pko_next_free_descr_queue += PKO_QUEUES_PER_CHANNEL;

    int lmac;
    int fcs_ena = 0; /* For thunder, FCS is added at the BGX layer */
    int skid_max_cnt;
    int fifo_size;
    int compressed_channel_id; /* compressed_channel_id comes from the LUT
                                    compressed channel inside
                                    "PKO Technical Specification1.docx" */
    switch (handle->iftype)
    {
        case BDK_IF_BGX:
        {
            int port = handle->index;
            BDK_CSR_INIT(config, handle->node, BDK_BGXX_CMRX_CONFIG(handle->interface, handle->index));
            switch (config.s.lmac_type)
            {
                case BDK_BGX_LMAC_TYPES_E_SGMII:
                case BDK_BGX_LMAC_TYPES_E_QSGMII:
                case BDK_BGX_LMAC_TYPES_E_RGMII:
                    fifo_size = 1;
                    skid_max_cnt = 0;
                    break;
                case BDK_BGX_LMAC_TYPES_E_TENG_R: /* 10GBASE-R */
                    fifo_size = 1;
                    skid_max_cnt = 0;
                    break;
                case BDK_BGX_LMAC_TYPES_E_RXAUI:
                    fifo_size = 2;
                    skid_max_cnt = 1;
                    break;
                case BDK_BGX_LMAC_TYPES_E_XAUI:
                    fifo_size = 4;
                    skid_max_cnt = 2;
                    break;
                case BDK_BGX_LMAC_TYPES_E_FORTYG_R: /* 40GBASE-R */
                default:
                    fifo_size = 4;
                    skid_max_cnt = 2;
                    break;
            }
            lmac = BDK_PKO_LMAC_E_BGXX_PORTX(handle->interface, port);
            compressed_channel_id = BDK_PKI_CHAN_E_BGXX_LMACX_CHX(handle->interface, handle->index, 0 /* channel */);
            break;
        }
        case BDK_IF_PCIE:
            lmac = BDK_PKO_LMAC_E_DPI;
            /* On CN83XX, if DLM4 is QSGMII you can have 16 total BGXs in use.
               This leaves 4 FIFOs for LBK and SDP, so we're do 1 each, totalling 20 */
            fifo_size = 1;
            skid_max_cnt = 0;
            compressed_channel_id = BDK_PKI_CHAN_E_DPI_CHX(handle->interface * 64 + handle->index);
            break;
        case BDK_IF_LBK:
            if (handle->interface == 2) {
                lmac = BDK_PKO_LMAC_E_LOOPBACK_1;
            } else {
                lmac = BDK_PKO_LMAC_E_LOOPBACK_0;
            }
            /* On CN83XX, if DLM4 is QSGMII you can have 16 total BGXs in use.
               This leaves 4 FIFOs for LBK and SDP, so we're do 1 each, totalling 20 */
            fifo_size = 1;
            skid_max_cnt = 0;
            compressed_channel_id = BDK_PKI_CHAN_E_LBKX_CHX(handle->interface, handle->index);
            break;
        default:
            return -1;
    }

    /* Get the FIFO number for this lmac */
    BDK_CSR_INIT(pko_macx_cfg, handle->node, BDK_PKO_MACX_CFG(lmac));
    if (pko_macx_cfg.s.fifo_num == 0x1f)
    {
        int fifo = __bdk_pko_allocate_fifo(handle->node, lmac, fifo_size);
        if (fifo<0)
            return -1;
        pko_macx_cfg.s.fifo_num = fifo;
        pko_macx_cfg.s.min_pad_ena = fcs_ena; /* Enable padding on ports using FCS */
        pko_macx_cfg.s.fcs_ena = fcs_ena; /* FCS */
        pko_macx_cfg.s.fcs_sop_off = 0; /* No FCS offset */
        pko_macx_cfg.s.skid_max_cnt = skid_max_cnt;
        BDK_CSR_WRITE(handle->node, BDK_PKO_MACX_CFG(lmac), pko_macx_cfg.u);
    }
//    printf("%s: PKO using lmac %d, fifo_size %d, fifo %d, compressed_chan %d, pq %d, l2 %d, l3 %d, dq %d\n",
//        handle->name, lmac, fifo_size, pko_macx_cfg.s.fifo_num, compressed_channel_id, pq, sq_l2, sq_l3, dq);

    /* Program L1 = port queue */
    BDK_CSR_MODIFY(c, handle->node, BDK_PKO_L1_SQX_TOPOLOGY(pq),
        c.s.prio_anchor = sq_l2;
        c.s.link = lmac;
        c.s.rr_prio = 0);
    BDK_CSR_MODIFY(c, handle->node, BDK_PKO_L1_SQX_SHAPE(pq),
        c.s.link = lmac);
    BDK_CSR_MODIFY(c, handle->node, BDK_PKO_L1_SQX_LINK(pq),
        c.s.link = lmac;
        c.s.cc_enable = 0);
    /* Program L2 = schedule queue */
    BDK_CSR_MODIFY(c, handle->node, BDK_PKO_L2_SQX_SCHEDULE(sq_l2),
        c.s.prio = 0;
        c.s.rr_quantum = 0);
    BDK_CSR_MODIFY(c, handle->node, BDK_PKO_L2_SQX_TOPOLOGY(sq_l2),
        c.s.prio_anchor = sq_l3;
        c.s.parent = pq;
        c.s.rr_prio = 0);
    /* Program L3 = schedule queue */
    BDK_CSR_MODIFY(c, handle->node, BDK_PKO_L3_L2_SQX_CHANNEL(sq_l3),
        c.s.cc_channel = compressed_channel_id);
    BDK_CSR_MODIFY(c, handle->node, BDK_PKO_L3_SQX_SCHEDULE(sq_l3),
        c.s.prio = 0;
        c.s.rr_quantum = 0);
    BDK_CSR_MODIFY(c, handle->node, BDK_PKO_L3_SQX_TOPOLOGY(sq_l3),
        c.s.prio_anchor = dq;
        c.s.parent = sq_l2;
        c.s.rr_prio = 0);
    /* Program L4 = descriptor queue */
    for (int q=0; q<PKO_QUEUES_PER_CHANNEL; q++)
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_PKO_DQX_SCHEDULE(dq+q),
            c.s.prio = 0;
            c.s.rr_quantum = 0);
        BDK_CSR_MODIFY(c, handle->node, BDK_PKO_DQX_TOPOLOGY(dq+q),
            c.s.parent = sq_l3);
    }
    if (compressed_channel_id != -1)
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_PKO_LUTX(compressed_channel_id),
            c.s.valid = 1;
            c.s.pq_idx = pq;
            c.s.queue_number = sq_l2); /* Would be sql_l3 if PKO_CHANNEL_LEVEL[cc_level]=1 */
    }

    /* Have the PKO DQ watermarks count descriptors. This way they are
       equivalent to the queue depth */
    BDK_CSR_MODIFY(c, handle->node, BDK_PKO_VFX_DQX_WM_CTL(dq / 8, dq & 7),
        c.s.kind = 1);

    /* The calculation of PKO_VFX_DQX_OP_SENDX address is slow, so cache it
       for the DQ */
    node_state->pko_dq_send[dq] = BDK_PKO_VFX_DQX_OP_SENDX(dq / 8, dq & 7, 0);
    node_state->pko_dq_send[dq] = bdk_numa_get_address(handle->node, node_state->pko_dq_send[dq]);

    handle->pko_queue = dq;
    return 0;
}

/**
 * Enable PKO after all setup is complete
 *
 * @return Zero on success, negative on failure
 */
int bdk_pko_enable(bdk_node_t node)
{
    global_node_state_t *node_state = global_node_state[node];

    /* Take FIFOs out of reset */
    BDK_CSR_INIT(pko_const, node, BDK_PKO_CONST);
    for (int i = 0; i < pko_const.s.ptgfs; i++)
        BDK_CSR_MODIFY(c, node, BDK_PKO_PTGFX_CFG(i), c.s.reset = 0);

    BDK_CSR_MODIFY(c, node, BDK_PKO_ENABLE,
        c.s.enable = 1);
    /* Read needed to make sure enable is done before accesses below */
    BDK_CSR_READ(node, BDK_PKO_ENABLE);

    /* PDM needs to be enabled before opening channels */
    BDK_CSR_MODIFY(c, node, BDK_PKO_PDM_CFG,
        c.s.pdm_en = 1;);

    /* Wait for PKO to be ready (100us) */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_PKO_STATUS, pko_rdy, ==, 1, 100))
    {
        bdk_error("PKO: Timeout waiting for ready\n");
        if (!bdk_is_platform(BDK_PLATFORM_ASIM))
            return -1;
    }

    /* Open all configured descriptor queues */
    for (int dq_index = 0; dq_index < node_state->pko_next_free_descr_queue; dq_index++)
    {
        volatile int64_t *pko_depth_ptr = node_state->pko_fc_depth + dq_index * FC_STRIDE / sizeof(uint64_t);
        int vf = dq_index / 8;
        int dq = dq_index & 7;
	/* Flow control needs to be set up before open */
        if (dq == 0)
        {
            BDK_CSR_MODIFY(c, node, BDK_PKO_VFX_DQ_FC_CONFIG(vf),
                c.s.base = (bdk_ptr_to_phys((int64_t*)pko_depth_ptr) >> 7);
                c.s.hyst_bits = DQ_FC_HYST_BITS;
                c.s.stride = (FC_STRIDE == 16) ? 1 : 0;
                c.s.enable=1);
        }
        *pko_depth_ptr = bdk_cpu_to_le64(DQ_FC_NOMINAL_DEPTH - DQ_FC_SKID);
        BDK_CSR_MODIFY(c, node, BDK_PKO_VFX_DQX_FC_STATUS(vf, dq),
            c.s.count = DQ_FC_NOMINAL_DEPTH);
        /* Successful open may cause update of value in memory, so
           settle writes now */
        BDK_WMB;
        /* Open the DQ for use */
        BDK_CSR_DEFINE(pko_open, BDK_PKO_VFX_DQX_OP_OPEN(vf, dq));
        void *open_op_ptr = bdk_phys_to_ptr(bdk_numa_get_address(node, (BDK_PKO_VFX_DQX_OP_OPEN(vf, dq))));
        pko_open.u = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(open_op_ptr, 0));
        if (pko_open.s.dqstatus != BDK_PKO_DQSTATUS_E_PASS)
            bdk_error("PKO open failed with response 0x%lx for vf %d dq %d\n", pko_open.u, vf, dq);
    }
    return 0;
}

/**
 * Get the current TX queue depth. Note that this operation may be slow
 * and adversly affect packet IO performance.
 *
 * @param handle Port to check
 *
 * @return Depth of the queue in packets
 */
int bdk_pko_get_queue_depth(bdk_if_handle_t handle)
{
    BDK_CSR_INIT(pkt_cnt, handle->node, BDK_PKO_VFX_DQX_WM_CNT(handle->pko_queue / 8, handle->pko_queue & 7));
    if (pkt_cnt.s.count == 0)
    {
        /* Queue count does not include pending transmits, delay reporting and
           refetch */
        bdk_wait_usec(500);
        pkt_cnt.u = BDK_CSR_READ(handle->node, BDK_PKO_VFX_DQX_WM_CNT(handle->pko_queue / 8, handle->pko_queue & 7));
    }
    if (pkt_cnt.s.count > 0x7fffffff)
        return 0x7fffffff;
    return pkt_cnt.s.count;
}

/**
 * Set PKO shapping as a specific queue level
 *
 * @param node       Node to shape
 * @param queue      Queue to shape
 * @param level      Level in PKO
 * @param is_red     Non-zero of the rate is for the yellow/red transition. Zero for the
 *                   green/yellow transition.
 * @param is_packets Non-zero if the rate is packets/sec, otherwise rate is bits/sec
 * @param rate       Desired rate. A rate of zero disables shaping
 *
 * @return Zero on success, negative on failure
 */
int bdk_pko_shape(bdk_node_t node, int queue, int level, int is_red, int is_packets, uint64_t rate)
{
    const int BURST_TIME = 10; /* us */
    /* Figure out how many times per second the shaper updates. L1 is every
       48 cycles, all other level are every 768 cycles */
    uint64_t sclk = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
    uint64_t tick = (level == 1) ? 48 : 768;
    uint64_t tick_per_sec = (sclk + tick/2) / tick;
    BDK_TRACE(PKO, "SCLK = %lu, tick = %lu, ticks/sec = %lu\n", sclk, tick, tick_per_sec);
    /* Average over the longer time period, 2^12 ticks */
    int rate_divider_exponent = 12; /* Max value is 1<<12 ticks */
retry_lower_divider:
    BDK_TRACE(PKO, "Trying rate divider exponent %d\n", rate_divider_exponent);
    /* RATE (bytes/second) = (tick_per_sec) * ((1.RATE_MANTISSA) << RATE_EXPONENT) / (1 << RATE_DIVIDER_EXPONENT) */
    uint64_t raw_rate = ((rate << rate_divider_exponent) + tick_per_sec/2) / tick_per_sec;
    if (is_packets)
        BDK_TRACE(PKO, "    rate = %lu packets/sec, raw_rate = %lu (packets/tick << %d)\n", rate, raw_rate, rate_divider_exponent);
    else
    {
        raw_rate = (raw_rate + 4) / 8; /* Convert to bytes */
        BDK_TRACE(PKO, "    rate = %lu bits/sec, raw_rate = %lu (bytes/tick << %d)\n", rate, raw_rate, rate_divider_exponent);
    }
    /* The below calculations scale the rate between 0x100 and 0x1ff. These are
       actually floating point, so they represent 1.xx. Multiply by 256 to
       account for this */
    raw_rate <<= 8;
    /* Scale to fit in range */
    int rate_exponent = 0;
    while (raw_rate >= 0x200)
    {
        rate_exponent++;
        raw_rate >>= 1;
    }
    /* Rate exponent is limited to 8 bits */
    if (rate_exponent > 0xff)
    {
        if (rate_divider_exponent)
        {
            BDK_TRACE(PKO, "    Rate too larger, reducing rate divider exponent\n");
            rate_divider_exponent--;
            goto retry_lower_divider;
        }
        rate_exponent = 0xff;
        raw_rate = 0x1ff;
    }
    BDK_TRACE(PKO, "    rate_exponent = %d, raw_rate = 0x%lx (should be 0x1xx)\n", rate_exponent, raw_rate);
    /* The mantissa implies the top bit, so and it off */
    int rate_mantissa = raw_rate & 0xff;
    /* Calculate the burst as rate * BURST_TIME */
    uint64_t ticks_per_burst = BURST_TIME * tick_per_sec / 1000000;
    uint64_t burst = raw_rate * ticks_per_burst;
    /* Scale to fit in range */
    int burst_exponent = rate_exponent;
    while (burst >= 0x200)
    {
        burst_exponent++;
        burst >>= 1;
    }
    /* Burst exponent is limited to 4 bits enocded in -1 notation */
    if (burst_exponent > 0x10)
    {
        if (rate_divider_exponent)
        {
            BDK_TRACE(PKO, "    Burst too larger, reducing rate divider exponent\n");
            rate_divider_exponent--;
            goto retry_lower_divider;
        }
        burst_exponent = 0x10;
        burst = 0xff;
    }
    BDK_TRACE(PKO, "    burst_exponent = %d, burst = 0x%lx (should be 0x1xx)\n", burst_exponent, burst);
    /* The mantissa implies the top bit, so and it off */
    int burst_mantissa = burst & 0xff;
    /* All of this is only enable of rate is not zero */
    int enable = (rate != 0);

    if (is_red)
    {
        bdk_pko_dqx_pir_t pir = {.u = 0};
        pir.s.burst_exponent = (burst_exponent) ? burst_exponent - 1 : 0; /* Encoded in -1 notation */
        pir.s.burst_mantissa = burst_mantissa;
        pir.s.rate_divider_exponent = rate_divider_exponent;
        pir.s.rate_exponent = rate_exponent;
        pir.s.rate_mantissa = rate_mantissa;
        pir.s.enable = enable;
        switch (level)
        {
            case 0:
                BDK_CSR_WRITE(node, BDK_PKO_DQX_PIR(queue), pir.u);
                BDK_CSR_MODIFY(c, node, BDK_PKO_DQX_SHAPE(queue),
                    c.s.length_disable = is_packets;
                    c.s.adjust = is_packets);
                return 0;
            case 1:
                bdk_error("PKO: Level %d doesn't support yellow/red rate limiting\n", level);
                return -1;
            case 2:
                BDK_CSR_WRITE(node, BDK_PKO_L2_SQX_PIR(queue), pir.u);
                BDK_CSR_MODIFY(c, node, BDK_PKO_L2_SQX_SHAPE(queue),
                    c.s.length_disable = is_packets;
                    c.s.adjust = is_packets);
                return 0;
            case 3:
                BDK_CSR_WRITE(node, BDK_PKO_L3_SQX_PIR(queue), pir.u);
                BDK_CSR_MODIFY(c, node, BDK_PKO_L3_SQX_SHAPE(queue),
                    c.s.length_disable = is_packets;
                    c.s.adjust = is_packets);
                return 0;
            default:
                bdk_error("PKO: Invalid level %d\n", level);
                return -1;
        }
    }
    else
    {
        bdk_pko_dqx_cir_t cir = {.u = 0};
        cir.s.burst_exponent = (burst_exponent) ? burst_exponent - 1 : 0; /* Encoded in -1 notation */
        cir.s.burst_mantissa = burst_mantissa;
        cir.s.rate_divider_exponent = rate_divider_exponent;
        cir.s.rate_exponent = rate_exponent;
        cir.s.rate_mantissa = rate_mantissa;
        cir.s.enable = enable;
        switch (level)
        {
            case 0:
                BDK_CSR_WRITE(node, BDK_PKO_DQX_CIR(queue), cir.u);
                BDK_CSR_MODIFY(c, node, BDK_PKO_DQX_SHAPE(queue),
                    c.s.length_disable = is_packets;
                    c.s.adjust = is_packets);
                return 0;
            case 1:
                BDK_CSR_WRITE(node, BDK_PKO_L1_SQX_CIR(queue), cir.u);
                BDK_CSR_MODIFY(c, node, BDK_PKO_L1_SQX_SHAPE(queue),
                    c.s.length_disable = is_packets;
                    c.s.adjust = is_packets);
                return 0;
            case 2:
                BDK_CSR_WRITE(node, BDK_PKO_L2_SQX_CIR(queue), cir.u);
                BDK_CSR_MODIFY(c, node, BDK_PKO_L2_SQX_SHAPE(queue),
                    c.s.length_disable = is_packets;
                    c.s.adjust = is_packets);
                return 0;
            case 3:
                BDK_CSR_WRITE(node, BDK_PKO_L3_SQX_CIR(queue), cir.u);
                BDK_CSR_MODIFY(c, node, BDK_PKO_L3_SQX_SHAPE(queue),
                    c.s.length_disable = is_packets;
                    c.s.adjust = is_packets);
                return 0;
            default:
                bdk_error("PKO: Invalid level %d\n", level);
                return -1;
        }
    }
}

/**
 * Build a PKO Gather sub-descriptor for a packet segment
 * @param packet_ptr pointer to packet
 * @param gather_desc pointer to packet gather entry to fill
 */

static void __bdk_pko_build_gather_subdesc(const bdk_packet_ptr_t *pptr, union bdk_pko_send_gather_s *gdesc)
{
    gdesc->u[0] = 0;
    gdesc->u[1] = 0;
    gdesc->s.size = pptr->s.size;
    gdesc->s.subdc = BDK_PKO_SENDSUBDC_E_GATHER;
    gdesc->s.addr = pptr->s.address;
}


/**
 * Send a packet
 *
 * @param handle Handle of port to send on
 * @param packet Packet to send
 *
 * @return Zero on success, negative on failure
 */
int bdk_pko_transmit(bdk_if_handle_t handle, const bdk_if_packet_t *packet)
{
    /* Flush pending writes */
    BDK_WMB;
    global_node_state_t *node_state = global_node_state[handle->node];
    int64_t pko_depth = node_state->pko_fc_depth[handle->pko_queue * FC_STRIDE / sizeof(uint64_t)];
    pko_depth = bdk_le64_to_cpu(pko_depth);
    if (pko_depth < 1)
        return -1;

    int lmt_status;
    uint64_t gather_addr = 0;
    if (packet->segments > BDK_PKO_SEG_LIMIT) {
        /* Gather array is in the buffer - we need to build it only once */
        gather_addr = packet->packet[0].s.address + packet->packet[0].s.size;
        uint64_t *ptr = bdk_phys_to_ptr(gather_addr);
        for (int seg = 0; seg < packet->segments; seg++)
        {
            union bdk_pko_send_gather_s pko_send_gather_s;
            __bdk_pko_build_gather_subdesc(&packet->packet[seg],&pko_send_gather_s);
            *ptr++ = bdk_cpu_to_le64( pko_send_gather_s.u[0]);
            *ptr++ = bdk_cpu_to_le64(pko_send_gather_s.u[1]);
        }
        BDK_WMB;
    }

    uint64_t io_address = global_node_state[handle->node]->pko_dq_send[handle->pko_queue];

    /* Build the two PKO comamnd words we need */
    union bdk_pko_send_hdr_s pko_send_hdr_s;
    pko_send_hdr_s.u[0] = 0;
    pko_send_hdr_s.u[1] = 0;
    pko_send_hdr_s.s.df = 1;
    pko_send_hdr_s.s.total = packet->length;

    switch (packet->packet_type)
    {
        case BDK_IF_TYPE_UDP4:
            pko_send_hdr_s.s.ckl3 = 1;        /* L3 - IPv4 checksum enable */
            pko_send_hdr_s.s.l3ptr = 14;      /* L2 header is 14 bytes */
            pko_send_hdr_s.s.ckl4 = BDK_PKO_CKL4ALG_E_UDP; /* L4 - UDP checksum enable */
            pko_send_hdr_s.s.l4ptr = 14 + 20; /* 14 bytes L2 + 20 bytes IPv4 */
            break;
        case BDK_IF_TYPE_TCP4:
            pko_send_hdr_s.s.ckl3 = 1;        /* L3 - IPv4 checksum enable */
            pko_send_hdr_s.s.l3ptr = 14;      /* L2 header is 14 bytes */
            pko_send_hdr_s.s.ckl4 = BDK_PKO_CKL4ALG_E_TCP; /* L4 - TCP checksum enable */
            pko_send_hdr_s.s.l4ptr = 14 + 20; /* 14 bytes L2 + 20 bytes IPv4 */
            if (packet->mtu)
            {
                int headers = 14 + 20 + 20;
                pko_send_hdr_s.s.tso = 1;     /* Use TCP offload */
                pko_send_hdr_s.s.tso_sb = headers; /* 14 bytes L2 + 20 bytes IPv4, 20 bytes TCP */
                pko_send_hdr_s.s.tso_mss = packet->mtu ; /* TCP MSS */
            }
            break;
        default:
            break;
    }

    do
    {
        bdk_lmt_cancel();
        volatile uint64_t *lmt_ptr = bdk_lmt_store_ptr();
        *lmt_ptr++ = bdk_cpu_to_le64(pko_send_hdr_s.u[0]);
        *lmt_ptr++ = bdk_cpu_to_le64(pko_send_hdr_s.u[1]);

        /* PKO allows a max of 15 minus header and decrement */
        if (gather_addr)
        {
            /* Gather IO is too long for lmtst buffer, need to build it on
               the side No need to free in the jump, gather array is part of
               data */
            union bdk_pko_send_jump_s pko_send_jump_s;
            pko_send_jump_s.u[0] = 0;
            pko_send_jump_s.u[1] = 0;
            pko_send_jump_s.s.subdc = BDK_PKO_SENDSUBDC_E_JUMP;
            pko_send_jump_s.s.size = packet->segments;
            pko_send_jump_s.s.addr = gather_addr;

            *lmt_ptr++ = bdk_cpu_to_le64(pko_send_jump_s.u[0]);
            *lmt_ptr++ = bdk_cpu_to_le64(pko_send_jump_s.u[1]);
        }
        else
        {
            /* Descriptor fits in the lmtst buffer */
            for (int seg = 0; seg < packet->segments; seg++)
            {
                union bdk_pko_send_gather_s pko_send_gather_s;
                __bdk_pko_build_gather_subdesc(&packet->packet[seg],&pko_send_gather_s);
                *lmt_ptr++ = bdk_cpu_to_le64(pko_send_gather_s.u[0]);
                *lmt_ptr++ = bdk_cpu_to_le64(pko_send_gather_s.u[1]);
            }
        }

        /* Issue LMTST, retrying if hardware says we should */
        lmt_status = bdk_lmt_submit(io_address);
    } while (lmt_status == 0);

    return 0;
}

/**
 * Query PKO and fill in the receive stats for the supplied
 * interface handle. The interface must use PKO for TX.
 *
 * @param handle Port handle
 *
 * @return
 */
void bdk_pko_fill_tx_stats(bdk_if_handle_t handle)
{
    /* Account for TX adding FCS */
    const int bytes_off_tx = (handle->flags & BDK_IF_FLAGS_HAS_FCS) ? 4 : 0;

    BDK_CSR_INIT(drps, handle->node, BDK_PKO_DQX_DROPPED_PACKETS(handle->pko_queue));
    BDK_CSR_INIT(doct, handle->node, BDK_PKO_DQX_DROPPED_BYTES(handle->pko_queue));

    if ( (handle->iftype != BDK_IF_BGX)) {
        // Not a BGX interface - fill both transmit and drop counters
        BDK_CSR_INIT(pkts, handle->node, BDK_PKO_DQX_PACKETS(handle->pko_queue));
        BDK_CSR_INIT(octs, handle->node, BDK_PKO_DQX_BYTES(handle->pko_queue));
        handle->stats.tx.octets -= handle->stats.tx.packets * bytes_off_tx;
        handle->stats.tx.packets = bdk_update_stat_with_overflow(pkts.u, handle->stats.tx.packets, 40);
        handle->stats.tx.octets = bdk_update_stat_with_overflow(octs.u, handle->stats.tx.octets, 48);
        handle->stats.tx.octets += handle->stats.tx.packets * bytes_off_tx;
    }

    handle->stats.tx.dropped_packets -= handle->stats.tx.dropped_packets * bytes_off_tx;
    handle->stats.tx.dropped_packets = bdk_update_stat_with_overflow(drps.u, handle->stats.tx.dropped_packets, 40);
    handle->stats.tx.dropped_octets = bdk_update_stat_with_overflow(doct.u, handle->stats.tx.dropped_octets, 48);
    handle->stats.tx.dropped_packets += handle->stats.tx.dropped_packets * bytes_off_tx;
}
