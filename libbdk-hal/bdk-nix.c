/***********************license start***********************************
* Copyright (c) 2003-2016  Cavium Inc. (support@cavium.com). All rights
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
#include <malloc.h>
#include "libbdk-arch/bdk-csrs-nix.h"
#include "libbdk-arch/bdk-csrs-npc.h"
#include "libbdk-arch/bdk-csrs-sso.h"
#include "libbdk-arch/bdk-csrs-rvu.h"

static const int USE_SSO = 0; /* 1=Receive goes through SSO, 0=Completion Queues */
static const int MAX_MTU = 9212; /* Copied from CN8XXX, unverified (FIXME) */
static const int MAX_CQS = 32; /* Setup a max of 32 Completion Queues, hw supports up to 1<<20 */
static const int MAX_SQS = 32; /* Setup a max of 32 Send Queues, hw supports up to 1<<20 */
static const int MAX_RQS = 32; /* Setup a max of 32 Receive Queues, hw supports up to 1<<20 */
static const int RSS_SIZE = 0; /* Size of RSS table (256 entries), see NIXX_AF_LFX_RSS_CFG[size] */
static const int CQS_QSIZE = 2; /* Each completion queue contains 256 entries, see NIX_CQ_CTX_S[qsize] */
static const int CQ_ENTRY_SIZE = 512; /* Each completion queue entry contains 512 bytes, see NIXX_AF_LFX_CFG[xqe_size] */

typedef struct
{
    int next_free_lf;
    int next_free_sq;
    int next_free_rq;
    int next_free_cq;
    int next_free_rssi;
    int next_free_bpid;
} nix_node_state_t;

static nix_node_state_t global_node_state[BDK_NUMA_MAX_NODES];

/**
 * NIX needs a lot of memory areas. Rather than handle all the failure cases,
 * we'll use a wrapper around alloc that fatally kills the app if a memory
 * allocation fails. CN9XXX is just too complicated to cleanup all possible
 * failure cases.
 *
 * @param num_elements
 *                  Number of elements to allocate
 * @param elem_size Size of each element
 * @param message   Text string to show when allocation fails
 *
 * @return A valid memory location. Failure never returns
 */
static void* nix_memalloc(int num_elements, int elem_size, const char *message)
{
    int alloc_size = num_elements * elem_size;
    void *base = memalign(BDK_CACHE_LINE_SIZE, alloc_size);
    if (!base)
        bdk_fatal("NIX: Memory alloc failed for %s (%d * %d = %d bytes)\n", message, num_elements, elem_size, alloc_size);
    bdk_zero_memory(base, alloc_size);
    return base;
}

/**
 * Allocate a new NIX Local Function
 *
 * @param node   Node to allocate on
 *
 * @return LF number, or negative on failure
 */
static int nix_lf_alloc(bdk_node_t node)
{
    nix_node_state_t *state = &global_node_state[node];
    BDK_CSR_INIT(nix_af_const2, node, BDK_NIXX_AF_CONST2(0));

    if (state->next_free_lf >= nix_af_const2.s.lfs)
    {
        bdk_error("N%d NIX: Ran out of LFs\n", node);
        return -1;
    }

    int lf = state->next_free_lf++;

    /* Setup WQE/CQE size, SSO and NPA PF */
    /* Hardcode RVU selection to PF0 */
    union bdk_rvu_pf_func_s rvu_pf_func;
    rvu_pf_func.u = 0;
    rvu_pf_func.s.pf = 0;
    rvu_pf_func.s.func = 0;
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_CFG(0, lf),
        c.s.xqe_size = (CQ_ENTRY_SIZE == 128) ? BDK_NIX_XQESZ_E_W16 : BDK_NIX_XQESZ_E_W64;
        c.s.sso_pf_func = rvu_pf_func.u;
        c.s.npa_pf_func = rvu_pf_func.u);

    /* Allocate space for storing LF Completion Interrupts */
    void *base = nix_memalloc(nix_af_const2.s.cints, sizeof(union bdk_nix_cint_hw_s), "LF Completion Interrupts");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_CINTS_BASE(0, lf), bdk_ptr_to_phys(base));
    /* NIXX_AF_LFX_CINTS_CFG defaults are right */

    /* Allocate space for storing LF Completion Queues Admin */
    base = nix_memalloc(MAX_CQS, sizeof(union bdk_nix_cq_ctx_s), "LF Completion Queues Admin");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_CQS_BASE(0, lf), bdk_ptr_to_phys(base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_CQS_CFG(0, lf),
        c.s.max_queuesm1 = MAX_CQS - 1);

    /* Allocate space for storing LF Queue Interrupts */
    base = nix_memalloc(nix_af_const2.s.qints, sizeof(union bdk_nix_qint_hw_s), "LF Queue Interrupts");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_QINTS_BASE(0, lf), bdk_ptr_to_phys(base));
    /* NIXX_AF_LFX_QINTS_CFG defaults are right */

    /* Allocate space for storing LF Receive Queues */
    base = nix_memalloc(MAX_RQS, sizeof(union bdk_nix_rq_ctx_s), "LF Receive Queues");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_RQS_BASE(0, lf), bdk_ptr_to_phys(base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_RQS_CFG(0, lf),
        c.s.max_queuesm1 = MAX_RQS - 1);

    /* Allocate space for storing LF RSS tables */
    base = nix_memalloc(256 << RSS_SIZE, sizeof(union bdk_nix_rsse_s), "LF RSS tables");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_RSS_BASE(0, lf), bdk_ptr_to_phys(base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_RSS_CFG(0, lf),
        c.s.ena = 1;
        c.s.size = RSS_SIZE);

    /* Allocate space for storing LF Send Queues */
    base = nix_memalloc(MAX_SQS, sizeof(union bdk_nix_sq_ctx_s), "LF Send Queues");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_SQS_BASE(0, lf), bdk_ptr_to_phys(base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_SQS_CFG(0, lf),
        c.s.max_queuesm1 = MAX_SQS - 1);

    /* NIX AF Local Function Transmit Configuration Register */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_TX_CFG(0, lf),
        c.s.lmt_ena = 1;
        c.s.lock_ena = 1;
        c.s.lock_viol_cqe_ena = 1);
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_TX_PARSE_CFG(0, lf),
        c.s.pkind = 1);

    return lf;
}

/**
 * Issue a command to the NIX AF Admin Queue
 *
 * @param node   Node to issue to
 * @param op     Operation
 * @param ctype  Context type
 * @param lf     Local function
 * @param cindex Context index
 * @param resp   Result pointer
 */
static void nix_aq_issue_command(bdk_node_t node, int op/*bdk_nix_aq_instop_e*/, int ctype /*bdk_nix_aq_ctype_e*/, int lf, int cindex, void *resp)
{
    /* Find the location in the Admin Queue */
    BDK_CSR_INIT(aq_status, node, BDK_NIXX_AF_AQ_STATUS(0));
    BDK_CSR_INIT(aq_base, node, BDK_NIXX_AF_AQ_BASE(0));
    union bdk_nix_aq_inst_s *aq_inst = bdk_phys_to_ptr(aq_base.u);
    aq_inst += aq_status.s.head_ptr;

    /* Build the instruction */
    aq_inst->u[0] = 0;
    aq_inst->u[1] = 0;
    aq_inst->s.op = op;
    aq_inst->s.ctype = ctype;
    aq_inst->s.lf = lf;
    aq_inst->s.cindex = cindex;
    aq_inst->s.doneint = 0;
    aq_inst->s.res_addr = bdk_ptr_to_phys(resp);
    aq_inst->u[0] = bdk_cpu_to_le64(aq_inst->u[0]);
    aq_inst->u[1] = bdk_cpu_to_le64(aq_inst->u[1]);

    /* Issue the instruction */
    BDK_WMB;
    BDK_CSR_WRITE(node, BDK_NIXX_AF_AQ_DOOR(0), 1);

    /* Wait for completion  */
    volatile union bdk_nix_aq_res_s *result_le = resp;
    union bdk_nix_aq_res_s result;
    do
    {
        bdk_thread_yield();
        result.u[0] = bdk_le64_to_cpu(result_le->u[0]);
        result.u[1] = bdk_le64_to_cpu(result_le->u[1]);
    } while (result.s.compcode == 0);
    if (result.s.compcode != BDK_NIX_AQ_COMP_E_GOOD)
        bdk_fatal("N%d, NIX: Admin Queue failed with code %d\n", node, result.s.compcode);
}

/**
 * Allocate and setup a new Completion Queue for use
 *
 * @param handle Handle for port to config
 *
 * @return Completion Queue number, or negative on failure
 */
static int nix_lf_alloc_cq(bdk_if_handle_t handle, int lf)
{
    nix_node_state_t *state = &global_node_state[handle->node];
    if (state->next_free_cq >= MAX_CQS)
    {
        bdk_error("%s NIX: Ran out of Completion Queues\n", bdk_if_name(handle));
        return -1;
    }
    int cq = state->next_free_cq++;
    int cqe_size = 16 << (CQS_QSIZE * 2);
    void *cqe_mem = nix_memalloc(cqe_size, CQ_ENTRY_SIZE, "Actual CQ Data");

    struct
    {
        union bdk_nix_aq_res_s resp;
        union bdk_nix_cq_ctx_s cq;
    } aq_request;
    bdk_zero_memory(&aq_request, sizeof(aq_request));

    aq_request.cq.s.ena = 1;
    aq_request.cq.s.bpid = handle->pki_channel; /* Assume 1:1 mapping between channel and BPID */
    aq_request.cq.s.bp = 255;
    aq_request.cq.s.bp_ena = 1;
    aq_request.cq.s.substream = 0; // FIXME: Substream IDs?
    aq_request.cq.s.drop_ena = 1;
    aq_request.cq.s.caching = 1;
    aq_request.cq.s.qsize = CQS_QSIZE;
    aq_request.cq.s.drop = 255 * 7 / 8;
    aq_request.cq.s.qint_idx = 0;
    aq_request.cq.s.cint_idx = 0;
    aq_request.cq.s.base = bdk_ptr_to_phys(cqe_mem);
#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(aq_request.cq) / 8; i++)
        aq_request.cq.u[i] = bdk_cpu_to_le64(aq_request.cq.u[i]);
#endif
    nix_aq_issue_command(handle->node, BDK_NIX_AQ_INSTOP_E_INIT, BDK_NIX_AQ_CTYPE_E_CQ, lf, cq, &aq_request.resp);
    BDK_TRACE(NIC, "%s: CQ(%d) allocated, base %p\n", handle->name, cq, cqe_mem);
    return cq;
}

/**
 * Allocate and setup a new Receive Queue for use
 *
 * @param handle Handle for port to config
 *
 * @return Receive Queue number, or negative on failure
 */
static int nix_lf_alloc_rq(bdk_if_handle_t handle, int lf, int cq)
{
    nix_node_state_t *state = &global_node_state[handle->node];
    if (state->next_free_rq >= MAX_RQS)
    {
        bdk_error("%s NIX: Ran out of Receive Queues\n", bdk_if_name(handle));
        return -1;
    }
    int rq = state->next_free_rq++;

    struct
    {
        union bdk_nix_aq_res_s resp;
        union bdk_nix_rq_ctx_s rq;
    } aq_request;
    bdk_zero_memory(&aq_request, sizeof(aq_request));

    aq_request.rq.s.ena = 1;
    aq_request.rq.s.sso_ena = USE_SSO;
    aq_request.rq.s.ipsech_ena = 0;
    aq_request.rq.s.ena_wqwd = 1;
    aq_request.rq.s.cq = cq;
    aq_request.rq.s.substream = 0; // FIXME: Substream IDs?
    aq_request.rq.s.wqe_aura = -1; /* No WQE aura */
    aq_request.rq.s.spb_aura = BDK_FPA_PACKET_POOL;
    aq_request.rq.s.lpb_aura = BDK_FPA_PACKET_POOL;
    aq_request.rq.s.sso_grp = 0; /* BDK doesn't use WQE group for anything */
    aq_request.rq.s.sso_tt = BDK_SSO_TT_E_ORDERED;
    aq_request.rq.s.pb_caching = 1;
    aq_request.rq.s.wqe_caching = 1;
    aq_request.rq.s.xqe_drop_ena = 0; /* Disable RED dropping */
    aq_request.rq.s.spb_drop_ena = 0;
    aq_request.rq.s.lpb_drop_ena = 0;
    aq_request.rq.s.spb_sizem1 = bdk_fpa_get_block_size(handle->node, BDK_FPA_PACKET_POOL) / 8 - 1;
    aq_request.rq.s.spb_ena = 0; /* Don't use SPB because its width is too small */
    aq_request.rq.s.lpb_sizem1 = bdk_fpa_get_block_size(handle->node, BDK_FPA_PACKET_POOL) / 8 - 1;
    aq_request.rq.s.first_skip = 0; /* FIXME: Room for WQE */
    aq_request.rq.s.later_skip = 0;
    aq_request.rq.s.xqe_imm_copy = 0;
    aq_request.rq.s.xqe_hdr_split = 0;
    aq_request.rq.s.xqe_drop = 255;
    aq_request.rq.s.xqe_pass = 255;
    aq_request.rq.s.wqe_pool_drop = 0; /* No WQE pool */
    aq_request.rq.s.wqe_pool_pass = 0; /* No WQE pool */
    aq_request.rq.s.spb_aura_drop = 255;
    aq_request.rq.s.spb_aura_pass = 255;
    aq_request.rq.s.spb_pool_drop = 0;
    aq_request.rq.s.spb_pool_pass = 0;
    aq_request.rq.s.lpb_aura_drop = 255;
    aq_request.rq.s.lpb_aura_pass = 255;
    aq_request.rq.s.lpb_pool_drop = 0;
    aq_request.rq.s.lpb_pool_pass = 0;
    aq_request.rq.s.qint_idx = 0;
#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(aq_request.rq) / 8; i++)
        aq_request.rq.u[i] = bdk_cpu_to_le64(aq_request.rq.u[i]);
#endif

    nix_aq_issue_command(handle->node, BDK_NIX_AQ_INSTOP_E_INIT, BDK_NIX_AQ_CTYPE_E_RQ, lf, rq, &aq_request.resp);
    return rq;
}

/**
 * Setup SMQ -> TL4 -> TL3 -> TL2 -> TL1 -> MAC mapping
 *
 * @param handle     Handle to setup
 * @param lf         Local NIX function
 * @param sq         SQ number that will hook to this SMQ
 * @param nix_link_e NIX link number enumeration
 *
 * @return SMQ number, or negative on failure
 */
static int nix_af_setup_sq(bdk_if_handle_t handle, int lf, int sq, int nix_link_e)
{
    int tl1_index = nix_link_e; /* NIX_LINK_E enum */
    int tl2_index = tl1_index;
    int tl3_index = tl2_index;
    int tl4_index = tl3_index;
    int smq_index = tl4_index;

    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL1X_SCHEDULE(0, tl1_index),
        c.s.rr_quantum = MAX_MTU);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL2X_PARENT(0, tl2_index),
        c.s.parent = tl1_index);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL3X_PARENT(0, tl3_index),
        c.s.parent = tl2_index);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL3_TL2X_CFG(0, tl3_index),
        c.s.express = 0);
    if (nix_link_e != BDK_NIX_LINK_E_SDP)
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL3_TL2X_LINKX_CFG(0, tl3_index, nix_link_e),
            c.s.bp_ena = 1;
            c.s.ena = 1;
            c.s.relchan = 0);
    }
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL4X_PARENT(0, tl4_index),
        c.s.parent = tl3_index);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL4X_SDP_LINK_CFG(0, tl4_index),
        c.s.bp_ena = (nix_link_e == BDK_NIX_LINK_E_SDP);
        c.s.ena = (nix_link_e == BDK_NIX_LINK_E_SDP);
        c.s.relchan = handle->index);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_SMQX_CFG(0, smq_index),
        c.s.express = 0;
        c.s.lf = lf;
        c.s.maxlen = MAX_MTU;
        c.s.minlen = 60);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_MDQX_SCHEDULE(0, smq_index),
        c.s.rr_quantum = MAX_MTU);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_MDQX_PARENT(0, smq_index),
        c.s.parent = tl4_index);
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_PKINDX_ACTION0(handle->pknd),
        c.s.parse_done = 1);
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_INTFX_MISS_ACT(BDK_NPC_INTF_E_NIXX_RX(0)),
        c.s.action = BDK_NIX_RX_ACTIONOP_E_UCAST);
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_INTFX_MISS_ACT(BDK_NPC_INTF_E_NIXX_TX(0)),
        c.s.action = BDK_NIX_TX_ACTIONOP_E_UCAST_DEFAULT);

    return smq_index;
}

/**
 * Allocate and setup a new Send Queue for use
 *
 * @param handle     Handle for port to config
 * @param lf         NIX local function
 * @param cq         NIX CQ
 * @param nix_link_e NIX link number enumeration
 *
 * @return Send Queue number, or negative on failure
 */
static int nix_lf_alloc_sq(bdk_if_handle_t handle, int lf, int cq, int nix_link_e)
{
    nix_node_state_t *state = &global_node_state[handle->node];
    if (state->next_free_sq >= MAX_SQS)
    {
        bdk_error("%s NIX: Ran out of Send Queues\n", bdk_if_name(handle));
        return -1;
    }
    int sq = state->next_free_sq++;
    int smq = nix_af_setup_sq(handle, lf, sq, nix_link_e);

    struct
    {
        union bdk_nix_aq_res_s resp;
        union bdk_nix_sq_ctx_s sq;
    } aq_request;
    bdk_zero_memory(&aq_request, sizeof(aq_request));

    aq_request.sq.s.ena = 1;
    aq_request.sq.s.cq_ena = 1;
    aq_request.sq.s.max_sqe_size = BDK_NIX_MAXSQESZ_E_W16;
    aq_request.sq.s.substream = 0; // FIXME: Substream IDs?
    aq_request.sq.s.sdp_mcast = 0;
    aq_request.sq.s.cq = cq;
    aq_request.sq.s.cq_limit = 0;
    aq_request.sq.s.smq = smq;
    aq_request.sq.s.sso_ena = 1; /* Always allow a SQ to submit work */
    aq_request.sq.s.smq_rr_quantum = MAX_MTU / 4;
    aq_request.sq.s.default_chan = handle->pki_channel;
    aq_request.sq.s.sqe_stype = BDK_NIX_STYPE_E_STP;
    aq_request.sq.s.qint_idx = 0;
    aq_request.sq.s.sqb_aura = BDK_FPA_PKO_POOL; /* Use same pool as PKO on CN83XX */
#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(aq_request.sq) / 8; i++)
        aq_request.sq.u[i] = bdk_cpu_to_le64(aq_request.sq.u[i]);
#endif
    nix_aq_issue_command(handle->node, BDK_NIX_AQ_INSTOP_E_INIT, BDK_NIX_AQ_CTYPE_E_SQ, lf, sq, &aq_request.resp);
    return sq;
}

/**
 * Setup the NPC MCAM to route incomming packets to the NIX
 *
 * @param handle Handle to setup
 * @param lf     NIX local function
 * @param rq     NIX receive queue
 */
static void nix_setup_mcam(bdk_if_handle_t handle, int lf, int rq)
{
    int mcam = handle->pko_queue;
    int bank = 0;

    /* Setup receive direction MCAM match */
    /* First require interface direction to exactly match  */
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(mcam, bank, 0),
        c.s.intf = ~BDK_NPC_INTF_E_NIXX_RX(0)); /* Mask for bits that must be 0 */
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(mcam, bank, 1),
        c.s.intf = BDK_NPC_INTF_E_NIXX_RX(0)); /* Mask for bits that must be 1 */
    /* Second require the first 12 bits of the key to match,
       the channel */
    uint64_t key0 = handle->pki_channel;
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(mcam, bank, 0),
        c.s.md = ~key0 & bdk_build_mask(12)); /* Mask for bits that must be 0 */
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(mcam, bank, 1),
        c.s.md = key0); /* Mask for bits that must be 1 */
    /* Third require none of the other key bits to match */
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(mcam, bank, 0),
        c.s.md = 0); /* Mask for bits that must be 0 */
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(mcam, bank, 1),
        c.s.md = 0); /* Mask for bits that must be 1 */

    /* Setup receive direction action */
    union bdk_nix_rx_action_s rx_action;
    rx_action.u = 0;
    rx_action.s.op = BDK_NIX_RX_ACTIONOP_E_UCAST;
    rx_action.s.pf_func = lf;
    rx_action.s.index = rq;
    rx_action.s.match_id = 0;
    rx_action.s.flow_key_alg = 0;
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_MCAMEX_BANKX_ACTION(mcam, bank),
        c.s.action = rx_action.u);

    /* Enable the MCAM entry */
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_MCAMEX_BANKX_CFG(mcam, bank),
        c.s.ena = 1);

    /* Program key size and nibbles to include */
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_INTFX_KEX_CFG(BDK_NPC_INTF_E_NIXX_RX(0)),
        c.s.keyw = BDK_NPC_MCAMKEYW_E_X1;
        c.s.parse_nibble_ena = 0x7);
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_INTFX_KEX_CFG(BDK_NPC_INTF_E_NIXX_TX(0)),
        c.s.keyw = BDK_NPC_MCAMKEYW_E_X1;
        c.s.parse_nibble_ena = 0xfffffff);
}

/**
 * Initialize NIX before queue setup
 *
 * @param node   Node to initialize
 *
 * @return Zero on success, negative on failure
 */
static int nix_init(bdk_node_t node)
{
    nix_node_state_t *state = &global_node_state[node];
    bdk_zero_memory(state, sizeof(*state));

    if (bdk_fpa_fill_pool(node, BDK_FPA_PKO_POOL, 64))
        return -1;

    const int AQ_SIZE = 0; /* AF Admin Queue has 16 entries */
    /* Allocate space for the AF Admin Queue */
    int aq_ring_size = 16 << (AQ_SIZE * 2);
    void *aq_base = nix_memalloc(aq_ring_size, sizeof(union bdk_nix_aq_inst_s), "AF Admin Queue");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_AQ_BASE(0), bdk_ptr_to_phys(aq_base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_AQ_CFG(0),
        c.s.qsize = AQ_SIZE);

    /* Calibrate X2P */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_CFG(0),
            c.s.calibrate_x2p = 1);
        while (1)
        {
            BDK_CSR_INIT(af_status, node, BDK_NIXX_AF_STATUS(0));
            if (af_status.s.calibrate_done)
                break;
            bdk_thread_yield();
        }
        BDK_CSR_INIT(af_status, node, BDK_NIXX_AF_STATUS(0));
        if (!af_status.s.calibrate_status)
        {
            bdk_error("N%d NIX: AF failed X2P calibration\n", node);
            return -1;
        }
    }

    /* Channel backpressure enable */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_RX_CFG(0),
        c.s.cbp_ena = 1);

    /* Assign channel BP numbers sequencially */
    int bpid = 0;
    for (int channel = 0; channel < 4096; channel++)
    {
        BDK_CSR_INIT(cfg, node, BDK_NIXX_AF_RX_CHANX_CFG(0, channel));
        if (cfg.s.imp)
        {
            cfg.s.bp_ena = 1;
            cfg.s.bpid = bpid;
            BDK_CSR_WRITE(node, BDK_NIXX_AF_RX_CHANX_CFG(0, channel), cfg.u);
            if (bpid < 512)
                bpid++;
            else
            {
                bdk_error("N%d NIX: Ran out of BPID at channel %d\n", node, channel);
                break;
            }
        }
    }

    /* Enable NDC cache */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_NDC_CFG(0),
        c.s.force_ndc_bypass = 0);

    /* Allocate MSIX space for NPA AF */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_PRIV_AF_INT_CFG(0),
        c.s.msix_offset = bdk_rvu_alloc_msix(node, 5)); /* NIX_AF_INT_VEC_E */

    /* Done with AF, so enable NIX */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_CFG(0),
        c.s.ena = 1);

    /* Hardcode RVU selection to PF0 */
    union bdk_rvu_pf_func_s rvu_pf_func;
    rvu_pf_func.u = 0;
    rvu_pf_func.s.pf = 0;
    rvu_pf_func.s.func = 0;

    /* Allocate a NIX LF for use by RVU */
    int lf = nix_lf_alloc(node);
    if (lf == -1)
    {
        bdk_error("N%d NIX: LF allocation failed\n", node);
        return -1;
    }

    /* Allocate MSIX space for LF */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_PRIV_LFX_INT_CFG(0, lf),
        c.s.msix_offset = bdk_rvu_alloc_msix(node, 131)); /* NIX_LF_INT_VEC_E */

    /* Assign and enable the RVU access to NPA */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_PRIV_LFX_CFG(0, lf),
        c.s.ena = 1;        /* Enable the NPA LF */
        c.s.pf_func = rvu_pf_func.u; /* Which RVU to use */
        c.s.slot = 0);      /* Starting at first */

    return 0;
}

/**
 * Process a CQ receive entry
 *
 * @param node      Node containing the CQ
 * @param cq_header CQ header to process
 * @param cq_header_le
 *
 * @return Returns the amount the RBDR doorbell needs to increment
 */
static void nix_process_complete_rx(bdk_if_handle_t handle, const union bdk_nix_rx_parse_s *rx_parse)
{
    const union bdk_nix_rx_sg_s *rx_sg_ptr = (const union bdk_nix_rx_sg_s *)(rx_parse + 1);
    BDK_TRACE(NIC, "    Receive RX_PARSE[%p - %p]\n", rx_parse, rx_parse+1);

#if __BYTE_ORDER == __BIG_ENDIAN
    union bdk_nix_rx_parse_s rx_parse_be;
    for (int i = 0; i < (int)sizeof(union bdk_nix_rx_parse_s) / 8; i++)
        rx_parse_be.u[i] = bdk_le64_to_cpu(rx_parse->u[i]);
    rx_parse = &rx_parse_be;
#endif

    bdk_if_packet_t packet;
    packet.length = rx_parse->s.pkt_lenm1 + 1;
    packet.if_handle = handle;
    /* Combine the errlev and errop into a single 11 bit number. Errop
       is 8 bits, so errlev will be in the top byte */
    packet.rx_error = rx_parse->s.errlev;
    packet.rx_error <<= 8;
    packet.rx_error |= rx_parse->s.errcode;

    int segments = 0;
    int segment_length = 0;
    int qwords = rx_parse->s.desc_sizem1 + 1;
    while (qwords > 0)
    {
        union bdk_nix_rx_sg_s rx_sg;
        rx_sg.u = bdk_le64_to_cpu(rx_sg_ptr->u);
        BDK_TRACE(NIC, "    Receive RX_SQ subdc=%d segs=%d ([%p] = 0x%lx)\n", rx_sg.s.subdc, rx_sg.s.segs, rx_sg_ptr, rx_sg.u);
        int num_seg = rx_sg.s.segs;

        uint64_t addr = bdk_le64_to_cpu(rx_sg_ptr[1].u);
        BDK_PREFETCH(bdk_phys_to_ptr(addr), 0);
        packet.packet[segments].u = addr;
        packet.packet[segments].s.size = rx_sg.s.seg1_size;
        segment_length += packet.packet[segments].s.size;
        BDK_TRACE(NIC, "    Receive segment1 size %d address 0x%lx\n", packet.packet[segments].s.size, addr);
        segments++;
        if (num_seg < 2)
            break;
        addr = bdk_le64_to_cpu(rx_sg_ptr[2].u);
        BDK_PREFETCH(bdk_phys_to_ptr(addr), 0);
        packet.packet[segments].u = addr;
        packet.packet[segments].s.size = rx_sg.s.seg2_size;
        segment_length += packet.packet[segments].s.size;
        BDK_TRACE(NIC, "    Receive segment2 size %d address 0x%lx\n", packet.packet[segments].s.size, addr);
        segments++;
        if (num_seg < 3)
            break;
        addr = bdk_le64_to_cpu(rx_sg_ptr[3].u);
        BDK_PREFETCH(bdk_phys_to_ptr(addr), 0);
        packet.packet[segments].u = addr;
        packet.packet[segments].s.size = rx_sg.s.seg3_size;
        segment_length += packet.packet[segments].s.size;
        BDK_TRACE(NIC, "    Receive segment3 size %d address 0x%lx\n", packet.packet[segments].s.size, addr);
        segments++;
        rx_sg_ptr = rx_sg_ptr + 4;
        qwords -= 2;
    }
    packet.segments = segments;
    /* If we ran out of buffer the packet could be truncated */
    if (segment_length < packet.length)
        packet.length = segment_length;

    /* Do RX stats in software as it is fast and I don't really trust
       the hardware. The hardware tends to count packets that are received
       and dropped in some weird way. Hopefully the hardware counters
       looking for drops can find these. It is important that they
       aren't counted as good */
    packet.if_handle->stats.rx.packets++;
    packet.if_handle->stats.rx.octets += packet.length;
    if (packet.if_handle->flags & BDK_IF_FLAGS_HAS_FCS)
        packet.if_handle->stats.rx.octets += 4;
    if (packet.rx_error)
        packet.if_handle->stats.rx.errors++;
    bdk_if_dispatch_packet(&packet);
    /* Free the packet data to the NPA */
    for (int s = 0; s < packet.segments; s++)
        __bdk_fpa_raw_free(handle->node, packet.packet[s].s.address & (0xffffffffffffffffULL ^ BDK_CACHE_LINE_MASK), BDK_FPA_PACKET_POOL, 0);
}

/**
 * Process all entries in a completion queue (CQ). Note that a CQ is shared
 * among many ports, so packets will be dispatch for other port handles.
 *
 * @param handle Interface handle connected to the CQ
 *
 * @return Number of packets received
 */
static void nix_receive(int unused, void *hand)
{
    const int CQ_ENTRIES = 16 << (CQS_QSIZE * 2);

    /* Figure out which completion queue we're using */
    bdk_if_handle_t handle = hand;
    int cq = handle->nic_id;
    int lf = 0;

    struct
    {
        union bdk_nix_aq_res_s resp;
        union bdk_nix_cq_ctx_s cq;
    } aq_request;
    bdk_zero_memory(&aq_request, sizeof(aq_request));
    BDK_TRACE(NIC, "%s: Getting CQ(%d) info\n", handle->name, cq);
    nix_aq_issue_command(handle->node, BDK_NIX_AQ_INSTOP_E_READ, BDK_NIX_AQ_CTYPE_E_CQ, lf, cq, &aq_request.resp);
#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(aq_request.cq) / 8; i++)
        aq_request.cq.u[i] = bdk_le64_to_cpu(aq_request.cq.u[i]);
#endif
    const void *cq_ptr = bdk_phys_to_ptr(aq_request.cq.s.base);
    /* Find the current CQ location */
    union bdk_nix_op_q_wdata_s q_wdata_s;
    q_wdata_s.u = 0;
    q_wdata_s.s.q = cq;
    int64_t *cq_op_status_ptr = bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_CQ_OP_STATUS(0)));

    BDK_TRACE(NIC, "%s: Receive thread for CQ(%d) started, base %p\n", handle->name, cq, cq_ptr);

    while (1)
    {
        /* Exit immediately if the CQ is empty */
        bdk_nixx_lf_cq_op_status_t cq_op_status;
        cq_op_status.u = bdk_atomic_fetch_and_add64_nosync(cq_op_status_ptr, bdk_cpu_to_le64(q_wdata_s.u));
        if (bdk_likely(cq_op_status.s.head == cq_op_status.s.tail))
        {
            bdk_wait_usec(1);
            continue;
        }
        BDK_TRACE(NIC, "%s: Receive thread CQ(%d): head %d, tail %d\n", handle->name, cq, cq_op_status.s.head, cq_op_status.s.tail);

        /* Loop through all pending CQs */
        int count = 0;
        int loc = cq_op_status.s.head;
        const union bdk_nix_cqe_hdr_s *cq_next = cq_ptr + loc * CQ_ENTRY_SIZE;
        while (loc != cq_op_status.s.tail)
        {
            union bdk_nix_cqe_hdr_s cq_hdr;
            cq_hdr.u = bdk_le64_to_cpu(cq_next->u);
            const union bdk_nix_rx_parse_s *rx_parse = (const union bdk_nix_rx_parse_s *)(cq_next + 1);
            BDK_TRACE(NIC, "%s: Receive HDR[%p] tag=0x%x, q=%d node=%d cqe_type=%d (0x%lx)\n",
                handle->name, cq_next, cq_hdr.s.tag, cq_hdr.s.q, cq_hdr.s.node, cq_hdr.s.cqe_type, cq_hdr.u);
            loc++;
            loc &= CQ_ENTRIES - 1;
            cq_next = cq_ptr + loc * CQ_ENTRY_SIZE;
            BDK_PREFETCH(cq_next, 0);
            if (bdk_likely(cq_hdr.s.cqe_type == BDK_NIX_XQE_TYPE_E_RX))
                nix_process_complete_rx(handle, rx_parse);
            else
                bdk_error("Unsupported CQ header type %d\n", cq_hdr.s.cqe_type);
            count++;
        }
        /* Free all the CQs that we've processed */
        bdk_nixx_lf_cq_op_door_t op_door;
        op_door.u = 0;
        op_door.s.cq = cq;
        op_door.s.count = count;
        BDK_CSR_WRITE(handle->node, BDK_NIXX_LF_CQ_OP_DOOR(0), op_door.u);
        /* Yield before going through more packets. The low core count chips
           don't have enough cores to dedicate for TX and RX. This forces
           sharing under load. If there are enough cores, the yield does
           nothing */
        bdk_thread_yield();
    }
}

/**
 * Configure NIC for a specific port. This is called for each
 * port on every interface that connects to NIC.
 *
 * @param handle Handle for port to config
 * @param ntype  Type of LMAC this NIC connects to
 * @param lmac_credits
 *               Size of the LMAC buffer in bytes. Used to configure the number of credits to
 *               setup between the NIC and LMAC
 *
 * @return Zero on success, negative on failure
 */
int bdk_nix_port_init(bdk_if_handle_t handle, bdk_nix_type_t ntype, int lmac_credits)
{
    BDK_CSR_INIT(af_aq_base, handle->node, BDK_NIXX_AF_AQ_BASE(0));
    if (!af_aq_base.u && nix_init(handle->node))
        return -1;

    int nix_link_e = -1;
    switch (ntype)
    {
        case BDK_NIX_TYPE_CGX:
            nix_link_e = BDK_NIX_LINK_E_CGXX_LMACX(handle->interface, handle->index);
            handle->pki_channel = BDK_NIX_CHAN_E_CGXX_LMACX_CHX(handle->interface, handle->index, 0);
            break;
        case BDK_NIX_TYPE_LBK:
            nix_link_e = BDK_NIX_LINK_E_LBKX(handle->interface);
            handle->pki_channel = BDK_NIX_CHAN_E_LBKX_CHX(handle->interface, handle->index);
            break;
        //case BDK_NIX_TYPE_SDP:
        //    nix_link_e = BDK_NIX_LINK_E_SDP;
        //    break;
    }

    /* Set min and max allowed packet sizes */
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_RX_LINKX_CFG(0, nix_link_e),
        c.s.maxlen = MAX_MTU;
        c.s.minlen = 60); /* FCS already removed */

    int lf = 0;
    int cq = nix_lf_alloc_cq(handle, lf);
    if (cq < 0)
        return -1;
    int rq = nix_lf_alloc_rq(handle, lf, cq);
    if (rq < 0)
        return -1;
    int sq = nix_lf_alloc_sq(handle, lf, cq, nix_link_e);
    if (sq < 0)
        return -1;
    handle->nic_id = cq;
    handle->pko_queue = sq;
    nix_setup_mcam(handle, lf, rq);
    if (bdk_thread_create(handle->node, 0, nix_receive, 0, handle, 0))
    {
        bdk_error("%s: Failed to allocate receive thread\n", handle->name);
        return -1;
    }
    return 0;
}

/**
 * Send a packet
 *
 * @param handle Handle of port to send on
 * @param packet Packet to send
 *
 * @return Zero on success, negative on failure
 */
int bdk_nix_transmit(bdk_if_handle_t handle, const bdk_if_packet_t *packet)
{
    union bdk_nix_op_q_wdata_s q_wdata_s;
    q_wdata_s.u = 0;
    q_wdata_s.s.q = handle->pko_queue;

    bdk_nixx_lf_sq_op_status_t sq_op_status;
    /* Flush pending writes */
    sq_op_status.u = bdk_atomic_fetch_and_add64(bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_SQ_OP_STATUS(0))), bdk_cpu_to_le64(q_wdata_s.u));
    int64_t depth = sq_op_status.s.sqb_count;
    if (depth > 64) // FIXME
        return -1;

    int lmt_status;
    uint64_t io_address = bdk_numa_get_address(handle->node, BDK_NIXX_LF_OP_SENDX(0, 0));

    /* Build the SQ header */
    union bdk_nix_send_hdr_s send_hdr_s;
    send_hdr_s.u[0] = 0;
    send_hdr_s.u[1] = 0;
    send_hdr_s.s.total = packet->length;
    send_hdr_s.s.df = 1;
    send_hdr_s.s.aura = BDK_FPA_PACKET_POOL;
    send_hdr_s.s.sizem1 = (packet->segments / 3) * 2;
    switch (packet->segments % 3)
    {
        case 0: /* No more gather lists */
            break;
        case 1: /* Gather list with one pointer */
            send_hdr_s.s.sizem1 += 1;
            break;
        case 2: /* Gather list with two pointers */
            send_hdr_s.s.sizem1 += 2;
            break;
    }
    send_hdr_s.s.pnc = 0; /* No completion posted */
    send_hdr_s.s.sq = handle->pko_queue;
    send_hdr_s.s.sqe_id = 0;

    switch (packet->packet_type)
    {
        case BDK_IF_TYPE_UDP4:
            send_hdr_s.s.ol3ptr = 14;      /* L2 header is 14 bytes */
            send_hdr_s.s.ol4ptr = 14 + 20; /* 14 bytes L2 + 20 bytes IPv4 */
            send_hdr_s.s.ol3type = BDK_NIX_SENDL3TYPE_E_IP4_CKSUM;
            send_hdr_s.s.ol4type = BDK_NIX_SENDL4TYPE_E_UDP_CKSUM;
            break;
        case BDK_IF_TYPE_TCP4:
            send_hdr_s.s.ol3ptr = 14;      /* L2 header is 14 bytes */
            send_hdr_s.s.ol4ptr = 14 + 20; /* 14 bytes L2 + 20 bytes IPv4 */
            send_hdr_s.s.ol3type = BDK_NIX_SENDL3TYPE_E_IP4_CKSUM;
            send_hdr_s.s.ol4type = BDK_NIX_SENDL4TYPE_E_TCP_CKSUM;
            if (packet->mtu)
            {
                /* FIXME: TSO */
            }
            break;
        default:
            break;
    }

    do
    {
        bdk_lmt_cancel();
        volatile uint64_t *lmt_ptr = bdk_lmt_store_ptr();
        *lmt_ptr++ = bdk_cpu_to_le64(send_hdr_s.u[0]);
        *lmt_ptr++ = bdk_cpu_to_le64(send_hdr_s.u[1]);

        /* Descriptor fits in the lmtst buffer */
        for (int seg = 0; seg < packet->segments; seg+=3)
        {
            union bdk_nix_send_sg_s send_sg_s;
            send_sg_s.u = 0;
            send_sg_s.s.seg1_size = packet->packet[seg].s.size;
            send_sg_s.s.seg2_size = packet->packet[seg+1].s.size;
            send_sg_s.s.seg3_size = packet->packet[seg+2].s.size;
            send_sg_s.s.ld_type = BDK_NIX_SENDLDTYPE_E_LDD;
            send_sg_s.s.subdc = BDK_NIX_SUBDC_E_SG;
            int segs = packet->segments - seg;
            send_sg_s.s.segs = (segs > 3) ? 3 : segs;
            *lmt_ptr++ = bdk_cpu_to_le64(send_sg_s.u);
            *lmt_ptr++ = bdk_cpu_to_le64(packet->packet[seg].s.address);
            if (segs >= 2)
            {
                *lmt_ptr++ = bdk_cpu_to_le64(packet->packet[seg + 1].s.address);
                *lmt_ptr++ = bdk_cpu_to_le64(packet->packet[seg + 2].s.address);
            }
        }

        /* Issue LMTST, retrying if hardware says we should */
        lmt_status = bdk_lmt_submit(io_address);
    } while (lmt_status == 0);

    handle->stats.tx.packets++;
    handle->stats.tx.octets += packet->length;
    if (handle->flags & BDK_IF_FLAGS_HAS_FCS)
        handle->stats.tx.octets += 4;

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
int bdk_nix_get_queue_depth(bdk_if_handle_t handle)
{
    /* IO pointer to perform atomic on */
    int64_t *ptr = bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_SQ_OP_STATUS(0)));

    /* Atomic increment data  */
    union bdk_nix_op_q_wdata_s q_wdata_s;
    q_wdata_s.u = 0;
    q_wdata_s.s.q = handle->pko_queue;

    /* Perform the atomic increment and get the data */
    bdk_nixx_lf_sq_op_status_t sq_op_status;
    sq_op_status.u = bdk_atomic_fetch_and_add64_nosync(ptr, bdk_cpu_to_le64(q_wdata_s.u));

    return sq_op_status.s.sqb_count;
}

/**
 * Query NIC and fill in the transmit stats for the supplied
 * interface handle.
 *
 * @param handle Port handle
 */
void bdk_nix_fill_tx_stats(bdk_if_handle_t handle)
{
    /* FIXME: Transmit stats are done in software right now */
}

/**
 * Query NIC and fill in the receive stats for the supplied
 * interface handle.
 *
 * @param handle Port handle
 */
void bdk_nix_fill_rx_stats(bdk_if_handle_t handle)
{
    /* Normal RX stats are done by software on receive */

    // FIXME: Drops
    // FIXME: Errors
    //handle->stats.rx.errors          = bdk_update_stat_with_overflow(dstat_errs.u, handle->stats.rx.errors, 32);
    //handle->stats.rx.dropped_packets = bdk_update_stat_with_overflow(dstat_drps.u, handle->stats.rx.dropped_packets, 32);
    //handle->stats.rx.dropped_octets  = bdk_update_stat_with_overflow(dstat_doct.u, handle->stats.rx.dropped_octets, 40);
}

