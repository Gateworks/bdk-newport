/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <malloc.h>
#include "libbdk-arch/bdk-csrs-cgx.h"
#include "libbdk-arch/bdk-csrs-nix.h"
#include "libbdk-arch/bdk-csrs-npc.h"
#include "libbdk-arch/bdk-csrs-sso.h"
#include "libbdk-arch/bdk-csrs-rvu.h"

static const int USE_SSO = 1; /* 1=Receive goes through SSO, 0=Completion Queues */
static const int MAX_MTU = 9212; /* Copied from CN8XXX, unverified (FIXME) */
static const int MAX_CQS = 32; /* Setup a max of 32 Completion Queues, hw supports up to 1<<20 */
#define MAX_SQS 32 /* Setup a max of 32 Send Queues, hw supports up to 1<<20 */
static const int MAX_RQS = 32; /* Setup a max of 32 Receive Queues, hw supports up to 1<<20 */
static const int RSS_SIZE = 0; /* Size of RSS table (256 entries), see NIXX_AF_LFX_RSS_CFG[size] */
static const int CQS_QSIZE = 2; /* Each completion queue contains 256 entries, see NIX_CQ_CTX_S[qsize] */
static const int CQ_ENTRY_SIZE = 512; /* Each completion queue entry contains 512 bytes, see NIXX_AF_LFX_CFG[xqe_size] */
static const int NIX_SEG_LIMIT = 9; /* Max segments in a gather list that fits in LMTST: 8 128bit words minus SEND_HDR - MEM_HDR = 6, two per 3 gather = 9 */
static const int SQ_AURA_LIMIT = 32; /* Max NPA buffers the aura for an SQ is allowed to use */

typedef struct
{
    int next_free_lf;
    int next_free_sq;
    int next_free_rq;
    int next_free_cq;
    uint64_t sq_depth[MAX_SQS]; /* Updated by Aura using FC_ADDR */
    int64_t sq_tx[MAX_SQS]; /* Packets submitted to SQ. Compared with NIXX_LF_SQ_OP_PKTS to determine queue depth */
} nix_node_state_t;

static nix_node_state_t global_node_state[BDK_NUMA_MAX_NODES][2];
static uint8_t lookup_send_size[BDK_IF_MAX_GATHER + 1];

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
 * Given a network handle, determine which NIX instance to use
 *
 * @param handle Handle to network port
 * @param is_rx  True if in RX direction, otherwise TX. Needed for LBK which can use two NIX
 *
 * @return NIX index
 */
static int nix_get_index(bdk_if_handle_t handle, bool is_rx)
{
    switch (handle->iftype)
    {
        case BDK_IF_PCIE: /* SDP0 = NIX0, SDP1 = NIX1 */
            return handle->interface;
        case BDK_IF_LBK:
            if (bdk_is_model(OCTEONTX_CN98XX))
            {
                switch (handle->interface)
                {
                    case 0:
                        return (is_rx) ? 0 : 0;
                    case 1:
                        return (is_rx) ? 1 : 0;
                    case 2:
                        return (is_rx) ? 0 : 1;
                    case 3:
                        return (is_rx) ? 1 : 1;
                    default:
                        return -1;
                }
            }
            else
                return 0;
        case BDK_IF_CGX:
            if (bdk_is_model(OCTEONTX_CN98XX))
                return handle->interface & 1; /* Stripe across NIX */
            else
                return 0;
        default:
            return -1;
    }
}

/**
 * Allocate a new NIX Local Function
 *
 * @param node      Node to allocate on
 * @param nix_index NIX to allocate for
 *
 * @return LF number, or negative on failure
 */
static int nix_lf_alloc(bdk_node_t node, int nix_index)
{
    nix_node_state_t *state = &global_node_state[node][nix_index];
    BDK_CSR_INIT(nix_af_const2, node, BDK_NIXX_AF_CONST2(nix_index));

    if (state->next_free_lf >= nix_af_const2.s.lfs)
    {
        bdk_error("N%d NIX%d: Ran out of LFs\n", node, nix_index);
        return -1;
    }

    int lf = state->next_free_lf++;

    /* Setup WQE/CQE size, SSO and NPA PF */
    /* Hardcode RVU selection to PF0 */
    union bdk_rvu_pf_func_s rvu_pf_func;
    rvu_pf_func.u = 0;
    rvu_pf_func.s.pf = 0;
    rvu_pf_func.s.func = 0;
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_CFG(nix_index, lf),
        c.s.xqe_size = (CQ_ENTRY_SIZE == 128) ? BDK_NIX_XQESZ_E_W16 : BDK_NIX_XQESZ_E_W64;
        c.s.sso_pf_func = rvu_pf_func.u;
        c.s.npa_pf_func = rvu_pf_func.u);

    /* Allocate space for storing LF Completion Interrupts */
    void *base = nix_memalloc(nix_af_const2.s.cints, sizeof(union bdk_nix_cint_hw_s), "LF Completion Interrupts");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_CINTS_BASE(nix_index, lf), bdk_ptr_to_phys(base));
    /* NIXX_AF_LFX_CINTS_CFG defaults are right */

    /* Allocate space for storing LF Completion Queues Admin */
    base = nix_memalloc(MAX_CQS, sizeof(union bdk_nix_cq_ctx_s), "LF Completion Queues Admin");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_CQS_BASE(nix_index, lf), bdk_ptr_to_phys(base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_CQS_CFG(nix_index, lf),
        c.s.max_queuesm1 = MAX_CQS - 1);

    /* Allocate space for storing LF Queue Interrupts */
    base = nix_memalloc(nix_af_const2.s.qints, sizeof(union bdk_nix_qint_hw_s), "LF Queue Interrupts");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_QINTS_BASE(nix_index, lf), bdk_ptr_to_phys(base));
    /* NIXX_AF_LFX_QINTS_CFG defaults are right */

    /* Allocate space for storing LF Receive Queues */
    base = nix_memalloc(MAX_RQS, sizeof(union bdk_nix_rq_ctx_s), "LF Receive Queues");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_RQS_BASE(nix_index, lf), bdk_ptr_to_phys(base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_RQS_CFG(nix_index, lf),
        c.s.max_queuesm1 = MAX_RQS - 1);

    /* Allocate space for storing LF RSS tables */
    base = nix_memalloc(256 << RSS_SIZE, sizeof(union bdk_nix_rsse_s), "LF RSS tables");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_RSS_BASE(nix_index, lf), bdk_ptr_to_phys(base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_RSS_CFG(nix_index, lf),
        c.s.ena = 1;
        c.s.size = RSS_SIZE);

    /* Allocate space for storing LF Send Queues */
    base = nix_memalloc(MAX_SQS, sizeof(union bdk_nix_sq_ctx_s), "LF Send Queues");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_LFX_SQS_BASE(nix_index, lf), bdk_ptr_to_phys(base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_SQS_CFG(nix_index, lf),
        c.s.max_queuesm1 = MAX_SQS - 1);

    /* NIX AF Local Function Transmit Configuration Register */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_TX_CFG(nix_index, lf),
        c.s.lock_ena = 1;
        c.s.lock_viol_cqe_ena = 1);
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_TX_CFG2(nix_index, lf),
        c.s.lmt_ena = 1);
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_LFX_TX_PARSE_CFG(nix_index, lf),
        c.s.pkind = 1);

    return lf;
}

/**
 * Issue a command to the NIX AF Admin Queue
 *
 * @param node      Node to issue to
 * @param nix_index NIX to issue to
 * @param op        Operation
 * @param ctype     Context type
 * @param lf        Local function
 * @param cindex    Context index
 * @param resp      Result pointer
 */
static void nix_aq_issue_command(bdk_node_t node, int nix_index, int op/*bdk_nix_aq_instop_e*/, int ctype /*bdk_nix_aq_ctype_e*/, int lf, int cindex, void *resp)
{
    /* Find the location in the Admin Queue */
    BDK_CSR_INIT(aq_status, node, BDK_NIXX_AF_AQ_STATUS(nix_index));
    BDK_CSR_INIT(aq_base, node, BDK_NIXX_AF_AQ_BASE(nix_index));
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
    BDK_CSR_WRITE(node, BDK_NIXX_AF_AQ_DOOR(nix_index), 1);

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
    int nix_index = nix_get_index(handle, true);
    nix_node_state_t *state = &global_node_state[handle->node][nix_index];
    if (state->next_free_cq >= MAX_CQS)
    {
        bdk_error("%s NIX%d: Ran out of Completion Queues\n", bdk_if_name(handle), nix_index);
        return -1;
    }
    int cq = state->next_free_cq++;
    int cqe_size = 16 << (CQS_QSIZE * 2);
    void *cqe_mem = nix_memalloc(cqe_size, CQ_ENTRY_SIZE, "Actual CQ Data");

    struct
    {
        union bdk_nix_aq_res_s resp BDK_CACHE_LINE_ALIGNED;
        union bdk_nix_cq_ctx_s cq BDK_CACHE_LINE_ALIGNED;
    } aq_request;
    bdk_zero_memory(&aq_request, sizeof(aq_request));

    BDK_CSR_INIT(af_rx_chanx_cfg, handle->node, BDK_NIXX_AF_RX_CHANX_CFG(nix_index, handle->pki_channel));

    aq_request.cq.s.ena = 1;
    aq_request.cq.s.bpid = af_rx_chanx_cfg.s.bpid;
    aq_request.cq.s.bp = 20 * 256 / 100; /* 0=Full, 255=empty: Backpressure when 80% full */
    aq_request.cq.s.bp_ena = 1;
    aq_request.cq.s.substream = 0; // FIXME: Substream IDs?
    aq_request.cq.s.drop_ena = 1;
    aq_request.cq.s.caching = 1;
    aq_request.cq.s.qsize = CQS_QSIZE;
    aq_request.cq.s.drop = 2 * 256 / 100; /* 0=Full, 255=empty: Drop when 98% full */
    aq_request.cq.s.qint_idx = 0;
    aq_request.cq.s.cint_idx = 0;
    aq_request.cq.s.avg_con = 0; /* No averaging */
    aq_request.cq.s.base = bdk_ptr_to_phys(cqe_mem);
#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(aq_request.cq) / 8; i++)
        aq_request.cq.u[i] = bdk_cpu_to_le64(aq_request.cq.u[i]);
#endif
    nix_aq_issue_command(handle->node, nix_index, BDK_NIX_AQ_INSTOP_E_INIT, BDK_NIX_AQ_CTYPE_E_CQ, lf, cq, &aq_request.resp);
    BDK_TRACE(NIC, "%s: NIX%d CQ(%d) allocated, base %p\n", handle->name, nix_index, cq, cqe_mem);
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
    int nix_index = nix_get_index(handle, true);
    nix_node_state_t *state = &global_node_state[handle->node][nix_index];
    if (state->next_free_rq >= MAX_RQS)
    {
        bdk_error("%s NIX%d: Ran out of Receive Queues\n", bdk_if_name(handle), nix_index);
        return -1;
    }
    int rq = state->next_free_rq++;

    struct
    {
        union bdk_nix_aq_res_s resp BDK_CACHE_LINE_ALIGNED;
        union bdk_nix_rq_ctx_s rq BDK_CACHE_LINE_ALIGNED;
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
    aq_request.rq.s.xqe_drop_ena = 1; /* Enable RED dropping for both SSO and CQ */
    aq_request.rq.s.spb_drop_ena = 0; /* Not using SPB, so don't drop based on it */
    aq_request.rq.s.lpb_drop_ena = 1; /* Enable dropping based on LPB */
    aq_request.rq.s.spb_sizem1 = bdk_fpa_get_block_size(handle->node, BDK_FPA_PACKET_POOL) / 8 - 1;
    aq_request.rq.s.spb_ena = 0; /* Don't use SPB because its width is too small */
    aq_request.rq.s.lpb_sizem1 = bdk_fpa_get_block_size(handle->node, BDK_FPA_PACKET_POOL) / 8 - 1;
    aq_request.rq.s.first_skip = (!USE_SSO) ? 0 : (CQ_ENTRY_SIZE == 128) ? 16 : 64;
    aq_request.rq.s.later_skip = 0;
    aq_request.rq.s.xqe_imm_copy = 0;
    aq_request.rq.s.xqe_hdr_split = 0;
    aq_request.rq.s.xqe_drop = (USE_SSO) ? 10 * 256 / 100 : 0; /* 0=Full, 255=empty: Drop when 90% full */
    aq_request.rq.s.xqe_pass = (USE_SSO) ? 20 * 256 / 100 : 0; /* 0=Full, 255=empty: RED when 80% full */
    aq_request.rq.s.wqe_pool_drop = 0; /* No WQE pool */
    aq_request.rq.s.wqe_pool_pass = 0; /* No WQE pool */
    aq_request.rq.s.spb_aura_drop = 0; /* Not using SPB */
    aq_request.rq.s.spb_aura_pass = 0; /* Not using SPB */
    aq_request.rq.s.spb_pool_drop = 0; /* Not using SPB */
    aq_request.rq.s.spb_pool_pass = 0; /* Not using SPB */
    aq_request.rq.s.lpb_aura_drop = 90 * 256 / 100; /* 255=Full, 0=empty: Drop when 90% full */
    aq_request.rq.s.lpb_aura_pass = 80 * 256 / 100; /* 255=Full, 0=empty: RED when 80% full */
    aq_request.rq.s.lpb_pool_drop = 10 * 256 / 100; /* 0=Full, 255=empty: Drop when 90% full */
    aq_request.rq.s.lpb_pool_pass = 20 * 256 / 100; /* 0=Full, 255=empty: RED when 80% full */
    aq_request.rq.s.qint_idx = 0;
#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(aq_request.rq) / 8; i++)
        aq_request.rq.u[i] = bdk_cpu_to_le64(aq_request.rq.u[i]);
#endif

    nix_aq_issue_command(handle->node, nix_index, BDK_NIX_AQ_INSTOP_E_INIT, BDK_NIX_AQ_CTYPE_E_RQ, lf, rq, &aq_request.resp);
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
    int nix_index = nix_get_index(handle, false);
    int tl1_index = nix_link_e; /* NIX_LINK_E enum */
    int tl2_index = tl1_index;
    int tl3_index = tl2_index;
    int tl4_index = tl3_index;
    int smq_index = tl4_index;

    int link_e_sdp;
    if (bdk_is_model(OCTEONTX_CN96XX))
        link_e_sdp = BDK_NIX_LINK_E_SDP_CN96XX;
    else if (bdk_is_model(OCTEONTX_CNF95XX))
        link_e_sdp = BDK_NIX_LINK_E_SDP_CNF95XX;
    else if (bdk_is_model(OCTEONTX_LOKI))
        link_e_sdp = BDK_NIX_LINK_E_SDP_LOKI;
    else if (bdk_is_model(OCTEONTX_CN98XX))
        link_e_sdp = BDK_NIX_LINK_E_SDP_CN98XX;
    else
        bdk_fatal("Update %s for this chip\n", __FUNCTION__);

    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL1X_SCHEDULE(nix_index, tl1_index),
        c.s.rr_quantum = MAX_MTU);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL2X_PARENT(nix_index, tl2_index),
        c.s.parent = tl1_index);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL3X_PARENT(nix_index, tl3_index),
        c.s.parent = tl2_index);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL3_TL2X_CFG(nix_index, tl3_index),
        c.s.express = 0);
    if (nix_link_e != link_e_sdp)
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL3_TL2X_LINKX_CFG(nix_index, tl3_index, nix_link_e),
            c.s.bp_ena = 1;
            c.s.ena = 1;
            c.s.relchan = 0);
    }
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL4X_PARENT(nix_index, tl4_index),
        c.s.parent = tl3_index);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TL4X_SDP_LINK_CFG(nix_index, tl4_index),
        c.s.bp_ena = (nix_link_e == link_e_sdp);
        c.s.ena = (nix_link_e == link_e_sdp);
        c.s.relchan = handle->index);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_SMQX_CFG(nix_index, smq_index),
        c.s.express = 0;
        c.s.lf = lf;
        c.s.maxlen = MAX_MTU;
        c.s.minlen = 60);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_MDQX_SCHEDULE(nix_index, smq_index),
        c.s.rr_quantum = MAX_MTU);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_MDQX_PARENT(nix_index, smq_index),
        c.s.parent = tl4_index);

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
    int nix_index = nix_get_index(handle, false);
    nix_node_state_t *state = &global_node_state[handle->node][nix_index];
    if (state->next_free_sq >= MAX_SQS)
    {
        bdk_error("%s NIX%d: Ran out of Send Queues\n", bdk_if_name(handle), nix_index);
        return -1;
    }
    int sq = state->next_free_sq++;
    int smq = nix_af_setup_sq(handle, lf, sq, nix_link_e);

    struct
    {
        union bdk_nix_aq_res_s resp BDK_CACHE_LINE_ALIGNED;
        union bdk_nix_sq_ctx_s sq BDK_CACHE_LINE_ALIGNED;
    } aq_request;
    bdk_zero_memory(&aq_request, sizeof(aq_request));

    aq_request.sq.s.ena = 1;
    aq_request.sq.s.cq_ena = !USE_SSO;
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
    aq_request.sq.s.sqb_aura = bdk_fpa_init_aura(handle->node, -1, BDK_FPA_PKO_POOL, SQ_AURA_LIMIT, bdk_ptr_to_phys(&state->sq_depth[sq]));

#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(aq_request.sq) / 8; i++)
        aq_request.sq.u[i] = bdk_cpu_to_le64(aq_request.sq.u[i]);
#endif
    nix_aq_issue_command(handle->node, nix_index, BDK_NIX_AQ_INSTOP_E_INIT, BDK_NIX_AQ_CTYPE_E_SQ, lf, sq, &aq_request.resp);
    return sq;
}

/**
 * Setup the NPC MCAM to route incoming packets to the NIX
 *
 * @param node   Which node to setup
 */
static void nix_setup_ndc(bdk_node_t node)
{
    /* Setup MCAM match for every INF type */
    BDK_CSR_INIT(npc_const, node, BDK_NPC_AF_CONST);
    for (int intf = 0; intf < npc_const.s.intfs; intf++)
    {
        /* Program key size and don't include any nibbles */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_INTFX_KEX_CFG(intf),
            c.s.keyw = BDK_NPC_MCAMKEYW_E_X1);
        /* First require interface direction to exactly match  */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(intf, 0, 0),
            c.s.intf = ~intf); /* Mask for bits that must be 0 */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_INTF(intf, 0, 1),
            c.s.intf = intf); /* Mask for bits that must be 1 */
        /* Second require none of the other key bits to match */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(intf, 0, 0),
            c.s.md = 0); /* Mask for bits that must be 0 */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_W0(intf, 0, 1),
            c.s.md = 0); /* Mask for bits that must be 1 */
        /* Third require none of the other key bits to match */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(intf, 0, 0),
            c.s.md = 0); /* Mask for bits that must be 0 */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_CAMX_W1(intf, 0, 1),
            c.s.md = 0); /* Mask for bits that must be 1 */
        /* Enable stats counter for this MCAM */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_STAT_ACT(intf, 0),
            c.s.ena = 1;
            c.s.stat_sel = intf);
        /* Enable stats counter for misses, which are dropped */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_INTFX_MISS_STAT_ACT(intf),
            c.s.ena = 1;
            c.s.stat_sel = 511 - intf);
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_INTFX_MISS_ACT(intf),
            c.s.action = BDK_NIX_RX_ACTIONOP_E_DROP);

        /* Action changes formwat based on whether its RX or TX */
        if ((intf & 1) == 0)
        {
            /* Setup receive direction action */
            /* Hardcode RVU selection to PF0 */
            union bdk_rvu_pf_func_s rvu_pf_func;
            rvu_pf_func.u = 0;
            rvu_pf_func.s.pf = 0;
            rvu_pf_func.s.func = 0;
            union bdk_nix_rx_action_s rx_action;
            rx_action.u = 0;
            rx_action.s.op = BDK_NIX_RX_ACTIONOP_E_UCAST;
            rx_action.s.pf_func = rvu_pf_func.u;
            rx_action.s.index = 0; // FIXME: RQ
            rx_action.s.match_id = intf;
            rx_action.s.flow_key_alg = 0;
            BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_ACTION(intf, 0),
                c.s.action = rx_action.u);
        }
        else
        {
            /* Setup transmit direction action */
            union bdk_nix_tx_action_s tx_action;
            tx_action.u = 0;
            tx_action.s.op = BDK_NIX_TX_ACTIONOP_E_UCAST_DEFAULT;
            tx_action.s.index = 0; /* Unused with UCAST_DEFAULT */
            tx_action.s.match_id = intf;
            BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_ACTION(intf, 0),
                c.s.action = tx_action.u);
        }

        /* Enable the receive MCAM entry */
        BDK_CSR_MODIFY(c, node, BDK_NPC_AF_MCAMEX_BANKX_CFG(intf, 0),
            c.s.ena = 1);
    }
}

/**
 * Initialize NIX before queue setup
 *
 * @param node      Node to initialize
 * @param nix_index Index to init
 *
 * @return Zero on success, negative on failure
 */
static int nix_init(bdk_node_t node, int nix_index)
{
    BDK_TRACE(NIC, "N%d: NIX%d init\n", node, nix_index);
    nix_node_state_t *state = &global_node_state[node][nix_index];
    bdk_zero_memory(state, sizeof(*state));

    /* The NPC setup of MCAMs is shared across all NIX */
    if (nix_index == 0)
        nix_setup_ndc(node);

    /* Building NIX_SEND_HDR_S requires filling SIZEM1 based on the
       length of the packet gather list. This requires a division and
       modulo of 3, so make a lookup table. Three entry gather lists
       wasn't the best idea. When the gather list is too large to fit in
       LMTST, then the JUMP header uses this and it doesn't have the
       SEND_HDR */
    for (int i = 0; i <= BDK_IF_MAX_GATHER; i++)
    {
        if (i > NIX_SEG_LIMIT)
            lookup_send_size[i] = (i / 3) * 2 - 1; /* No SEND_HDR in jump gather */
        else
            lookup_send_size[i] = (i / 3) * 2;
        switch (i % 3)
        {
            case 0: /* No more gather lists */
                break;
            case 1: /* Gather list with one pointer */
                lookup_send_size[i] += 1;
                break;
            case 2: /* Gather list with two pointers */
                lookup_send_size[i] += 2;
                break;
        }
    }

    BDK_TRACE(NIC, "N%d: NIX%d init pool in NPA\n", node, nix_index);
    if (!nix_index && bdk_fpa_fill_pool(node, BDK_FPA_PKO_POOL, SQ_AURA_LIMIT * MAX_SQS))
        return -1;

    const int AQ_SIZE = 0; /* AF Admin Queue has 16 entries */
    /* Allocate space for the AF Admin Queue */
    int aq_ring_size = 16 << (AQ_SIZE * 2);
    void *aq_base = nix_memalloc(aq_ring_size, sizeof(union bdk_nix_aq_inst_s), "AF Admin Queue");
    BDK_CSR_WRITE(node, BDK_NIXX_AF_AQ_BASE(nix_index), bdk_ptr_to_phys(aq_base));
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_AQ_CFG(nix_index),
        c.s.qsize = AQ_SIZE);

    /* Errata (NIX-35057) 2018-10-24 A0-A0 CatC NIX may fail when conditional clock stops */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
    {
        BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_CFG(nix_index),
            c.s.force_seb_clk_en = 1;
            c.s.force_rx_strm_clk_en = 1;
            c.s.force_rx_gbl_clk_en = 1;
            c.s.force_cqm_clk_en = 1;
            c.s.force_pse_clk_en = 1);
    }

    /* Calibrate X2P */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        BDK_CSR_INIT(af_status, node, BDK_NIXX_AF_STATUS(nix_index));
        if (!af_status.s.calibrate_done)
        {
            BDK_TRACE(NIC, "N%d: NIX%d Calibrate X2P\n", node, nix_index);
            /* Force restart of calibraton */
            BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_CFG(nix_index),
                c.s.calibrate_x2p = 0);
            BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_CFG(nix_index),
                c.s.calibrate_x2p = 1);
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_NIXX_AF_STATUS(nix_index), calibrate_done, ==, 1, 10000))
            {
                af_status.u = BDK_CSR_READ(node, BDK_NIXX_AF_STATUS(nix_index));
                bdk_error("N%d NIX%d: AF failed X2P calibration (NIXX_AF_STATUS[calibrate_status]=0x%x)\n", node, nix_index, af_status.s.calibrate_status);
            }
            BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_CFG(nix_index),
                c.s.calibrate_x2p = 0);
        }
        else
            BDK_TRACE(NIC, "N%d: NIX%d X2P calibration already complete\n", node, nix_index);
    }

    BDK_TRACE(NIC, "N%d: NIX%d setup backpressure\n", node, nix_index);
    /* Channel backpressure enable */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_RX_CFG(nix_index),
        c.s.cbp_ena = 1);

    /* Assign channel BP numbers sequentially */
    int bpid = 0;
    for (int channel = BDK_NIX_CHAN_E_CGXX_LMACX_CHX(0, 0, 0); channel < 4096; channel += 16)
    {
        BDK_CSR_INIT(cfg, node, BDK_NIXX_AF_RX_CHANX_CFG(nix_index, channel));
        if (cfg.s.imp)
        {
            cfg.s.bp_ena = 1;
            cfg.s.bpid = bpid;
            BDK_CSR_WRITE(node, BDK_NIXX_AF_RX_CHANX_CFG(nix_index, channel), cfg.u);
            if (bpid < 512)
                bpid++;
            else
            {
                bdk_error("N%d NIX%d: Ran out of BPID at channel %d\n", node, nix_index, channel);
                break;
            }
        }
    }

    /* Enable NDC cache */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_AF_NDC_CFG(nix_index),
        c.u = 0);

    /* Allocate MSIX space for NPA AF */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_PRIV_AF_INT_CFG(nix_index),
        c.s.msix_offset = bdk_rvu_alloc_msix(node, 5)); /* NIX_AF_INT_VEC_E */

    BDK_TRACE(NIC, "N%d: NIX%d allocate RVU LF\n", node, nix_index);
    /* Hardcode RVU selection to PF0 */
    union bdk_rvu_pf_func_s rvu_pf_func;
    rvu_pf_func.u = 0;
    rvu_pf_func.s.pf = 0;
    rvu_pf_func.s.func = 0;

    /* Allocate a NIX LF for use by RVU */
    int lf = nix_lf_alloc(node, nix_index);
    if (lf == -1)
    {
        bdk_error("N%d NIX%d: LF allocation failed\n", node, nix_index);
        return -1;
    }

    BDK_TRACE(NIC, "N%d: NIX%d allocate MSIX for RVU LF\n", node, nix_index);
    /* Allocate MSIX space for LF */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_PRIV_LFX_INT_CFG(nix_index, lf),
        c.s.msix_offset = bdk_rvu_alloc_msix(node, 131)); /* NIX_LF_INT_VEC_E */

    /* Assign and enable the RVU access to NPA */
    BDK_CSR_MODIFY(c, node, BDK_NIXX_PRIV_LFX_CFG(nix_index, lf),
        c.s.ena = 1;        /* Enable the NPA LF */
        c.s.pf_func = rvu_pf_func.u; /* Which RVU to use */
        c.s.slot = 0);      /* Starting at first */

    BDK_TRACE(NIC, "N%d: NIX%d init complete\n", node, nix_index);
    return 0;
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
    int nix_index = nix_get_index(handle, true);
    int cq = handle->nic_id;
    int lf = 0;

    struct
    {
        union bdk_nix_aq_res_s resp BDK_CACHE_LINE_ALIGNED;
        union bdk_nix_cq_ctx_s cq BDK_CACHE_LINE_ALIGNED;
    } aq_request;
    bdk_zero_memory(&aq_request, sizeof(aq_request));
    BDK_TRACE(NIC, "%s: NIX%d Getting CQ(%d) info\n", handle->name, nix_index, cq);
    nix_aq_issue_command(handle->node, nix_index, BDK_NIX_AQ_INSTOP_E_READ, BDK_NIX_AQ_CTYPE_E_CQ, lf, cq, &aq_request.resp);
#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(aq_request.cq) / 8; i++)
        aq_request.cq.u[i] = bdk_le64_to_cpu(aq_request.cq.u[i]);
#endif
    const void *cq_ptr = bdk_phys_to_ptr(aq_request.cq.s.base);
    /* Find the current CQ location */
    union bdk_nix_op_q_wdata_s q_wdata_s;
    q_wdata_s.u = 0;
    q_wdata_s.s.q = cq;
    int64_t *cq_op_status_ptr = bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_CQ_OP_STATUS(nix_index)));

    BDK_TRACE(NIC, "%s: NIX%d Receive thread for CQ(%d) started, base %p\n", handle->name, nix_index, cq, cq_ptr);

    while (1)
    {
        /* Exit immediately if the CQ is empty */
        bdk_nixx_lf_cq_op_status_t cq_op_status;
        cq_op_status.u = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(cq_op_status_ptr, bdk_cpu_to_le64(q_wdata_s.u)));
        if (bdk_likely(cq_op_status.s.head == cq_op_status.s.tail))
        {
            bdk_wait_usec(1);
            continue;
        }
        BDK_TRACE(NIC, "%s: NIX%d Receive thread CQ(%d): head %d, tail %d\n", handle->name, nix_index, cq, cq_op_status.s.head, cq_op_status.s.tail);

        /* Loop through all pending CQs */
        int count = 0;
        int loc = cq_op_status.s.head;
        const union bdk_nix_cqe_hdr_s *cq_next = cq_ptr + loc * CQ_ENTRY_SIZE;
        while (loc != cq_op_status.s.tail)
        {
            union bdk_nix_cqe_hdr_s cq_hdr;
            cq_hdr.u = bdk_le64_to_cpu(cq_next->u);
            const union bdk_nix_rx_parse_s *rx_parse = (const union bdk_nix_rx_parse_s *)(cq_next + 1);
            BDK_TRACE(NIC, "%s: NIX%d Receive HDR[%p] tag=0x%x, q=%d node=%d cqe_type=%d (0x%lx)\n",
                handle->name, nix_index, cq_next, cq_hdr.s.tag, cq_hdr.s.q, cq_hdr.s.node, cq_hdr.s.cqe_type, cq_hdr.u);
            loc++;
            loc &= CQ_ENTRIES - 1;
            cq_next = cq_ptr + loc * CQ_ENTRY_SIZE;
            BDK_PREFETCH(cq_next, 0);
            if (bdk_likely(cq_hdr.s.cqe_type == BDK_NIX_XQE_TYPE_E_RX))
                __bdk_nix_process_complete_rx(handle, rx_parse);
            else
                bdk_error("NIX%d Unsupported CQ header type %d\n", nix_index, cq_hdr.s.cqe_type);
            count++;
        }
        /* Free all the CQs that we've processed */
        bdk_nixx_lf_cq_op_door_t op_door;
        op_door.u = 0;
        op_door.s.cq = cq;
        op_door.s.count = count;
        BDK_CSR_WRITE(handle->node, BDK_NIXX_LF_CQ_OP_DOOR(nix_index), op_door.u);
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
    int nix_index = nix_get_index(handle, false);
    BDK_TRACE(NIC, "%s: NIX%d port init\n", handle->name, nix_index);
    BDK_CSR_INIT(af_aq_base, handle->node, BDK_NIXX_AF_AQ_BASE(nix_index));
    if (!af_aq_base.u)
    {
        if (nix_init(handle->node, 0))
            return -1;
        if (bdk_is_model(OCTEONTX_CN98XX) && nix_init(handle->node, 1))
            return -1;
    }

    int nix_link_e = -1;
    int tx_credit = -1;
    switch (ntype)
    {
        case BDK_NIX_TYPE_CGX:
            nix_link_e = BDK_NIX_LINK_E_CGXX_LMACX(handle->interface, handle->index);
            handle->pki_channel = BDK_NIX_CHAN_E_CGXX_LMACX_CHX(handle->interface, handle->index, 0);
            tx_credit = (lmac_credits - MAX_MTU) / 16;
            break;
        case BDK_NIX_TYPE_LBK:
            if (bdk_is_model(OCTEONTX_CN96XX))
                nix_link_e = BDK_NIX_LINK_E_LBKX_CN96XX(handle->interface);
            else if (bdk_is_model(OCTEONTX_CNF95XX))
                nix_link_e = BDK_NIX_LINK_E_LBKX_CNF95XX(handle->interface);
            else if (bdk_is_model(OCTEONTX_LOKI))
                nix_link_e = BDK_NIX_LINK_E_LBKX_LOKI(handle->interface);
            else if (bdk_is_model(OCTEONTX_CN98XX))
                nix_link_e = BDK_NIX_LINK_E_LBKX_CN98XX(handle->interface & 1);
            else
                bdk_fatal("Update %s for this chip\n", __FUNCTION__);
            handle->pki_channel = BDK_NIX_CHAN_E_LBKX_CHX(handle->interface, handle->index);
            tx_credit = 1600;
            break;
        case BDK_NIX_TYPE_SDP:
            if (bdk_is_model(OCTEONTX_CN96XX))
                nix_link_e = BDK_NIX_LINK_E_SDP_CN96XX;
            else if (bdk_is_model(OCTEONTX_CNF95XX))
                nix_link_e = BDK_NIX_LINK_E_SDP_CNF95XX;
            else if (bdk_is_model(OCTEONTX_LOKI))
                nix_link_e = BDK_NIX_LINK_E_SDP_LOKI;
            else if (bdk_is_model(OCTEONTX_CN98XX))
                nix_link_e = BDK_NIX_LINK_E_SDP_CN98XX;
            else
                bdk_fatal("Update %s for this chip\n", __FUNCTION__);
            handle->pki_channel = BDK_NIX_CHAN_E_SDP_CHX(handle->index);
            tx_credit = 800; /* HRM recommended value for 50GBps */
            BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_SDP_LINK_CREDIT(nix_index),
                c.s.cc_unit_cnt = tx_credit;
                c.s.cc_packet_cnt = 255;
                c.s.cc_enable = 1);
            break;
    }

    /* Set min and max allowed packet sizes */
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_RX_LINKX_CFG(nix_index, nix_link_e),
        c.s.maxlen = MAX_MTU;
        c.s.minlen = 60); /* FCS already removed */
    /* Set flow control at link level */
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TX_LINKX_NORM_CREDIT(nix_index, nix_link_e),
        c.s.cc_unit_cnt = tx_credit;
        c.s.cc_packet_cnt = 255;
        c.s.cc_enable = 1);
    BDK_CSR_MODIFY(c, handle->node, BDK_NIXX_AF_TX_LINKX_EXPR_CREDIT(nix_index, nix_link_e),
        c.s.cc_unit_cnt = tx_credit;
        c.s.cc_packet_cnt = 15;
        c.s.cc_enable = 1);

    int lf = 0;
    int cq = -1;
    if (USE_SSO)
    {
        /* Register handle with SSO */
        bdk_sso_register_handle(handle);
    }
    else
    {
        cq = nix_lf_alloc_cq(handle, lf);
        if (cq < 0)
            return -1;
    }
    int rq = nix_lf_alloc_rq(handle, lf, cq);
    if (rq < 0)
        return -1;
    int sq = nix_lf_alloc_sq(handle, lf, cq, nix_link_e);
    if (sq < 0)
        return -1;
    handle->nic_id = cq;
    handle->pko_queue = sq;

    /* Set the parsers to be skipped  */
    BDK_CSR_MODIFY(c, handle->node, BDK_NPC_AF_PKINDX_ACTION0(handle->pknd),
        c.s.parse_done = 1);

    if (!USE_SSO && bdk_thread_create(handle->node, 0, nix_receive, 0, handle, 0))
    {
        bdk_error("%s: NIX%d Failed to allocate receive thread\n", handle->name, nix_index);
        return -1;
    }
    BDK_TRACE(NIC, "%s: NIX%d port init complete\n", handle->name, nix_index);
    return 0;
}

/**
 * Send a packet
 *
 * @param handle Handle of port to send on
 * @param packet Packet to send
 * @param repeat_count
 *               Number of times to repeat the packet. This is used to send a high
 *               speed burst. Set to zero for no repeats, only one packet will be sent
 *
 * @return Number of packets sent or zero on failure
 */
int bdk_nix_transmit(bdk_if_handle_t handle, const bdk_if_packet_t *packet, int repeat_count)
{
    /* Flush pending writes */
    BDK_WMB;

    /* Check for max queue depth */
    int nix_index = nix_get_index(handle, false);
    nix_node_state_t *state = &global_node_state[handle->node][nix_index];
    uint64_t depth = bdk_le64_to_cpu(state->sq_depth[handle->pko_queue]);
    if (bdk_unlikely(depth >= SQ_AURA_LIMIT - 16))
    {
        /* Workaround for Errata NIX-35687: Link credit deadlock */
        if (handle->iftype == BDK_IF_CGX)
        {
            BDK_CSR_INIT(tx_fifo, handle->node, BDK_CGXX_CMRX_TX_FIFO_LEN(handle->interface, handle->index));
            if (tx_fifo.s.lmac_idle)
            {
                int nix_link_e = BDK_NIX_LINK_E_CGXX_LMACX(handle->interface, handle->index);
                /* Stop NIX */
                BDK_CSR_WRITE(handle->node, BDK_NIXX_AF_TL2X_SW_XOFF(nix_index, nix_link_e), 1);
                /* Reset credits */
                BDK_CSR_WRITE(handle->node, BDK_NIXX_AF_TX_LINKX_NORM_CREDIT(nix_index, nix_link_e),
                    BDK_CSR_READ(handle->node, BDK_NIXX_AF_TX_LINKX_EXPR_CREDIT(nix_index, nix_link_e)));
                /* Restart NIX */
                BDK_CSR_WRITE(handle->node, BDK_NIXX_AF_TL2X_SW_XOFF(nix_index, nix_link_e), 0);
            }
        }
        return 0;
    }

    /* Temporary buffer to store the LMTST command for fast repeating */
    uint64_t lmt_buf[16];
    int lmt_len = 0;

    uint64_t gather_addr = 0;
    if (bdk_unlikely(packet->segments > NIX_SEG_LIMIT))
    {
        /* Gather array is in the buffer - we need to build it only once */
        gather_addr = packet->packet[0].s.address + packet->packet[0].s.size;
        uint64_t *ptr = bdk_phys_to_ptr(gather_addr);
        for (int seg = 0; seg < packet->segments; seg += 3)
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
            *ptr++ = bdk_cpu_to_le64(send_sg_s.u);
            *ptr++ = bdk_cpu_to_le64(packet->packet[seg].s.address);
            if (segs < 2)
                break;
            *ptr++ = bdk_cpu_to_le64(packet->packet[seg + 1].s.address);
            *ptr++ = bdk_cpu_to_le64(packet->packet[seg + 2].s.address);
        }
        BDK_WMB;
    }

    /* Build the SQ header */
    union bdk_nix_send_hdr_s send_hdr_s;
    send_hdr_s.u[0] = 0;
    send_hdr_s.u[1] = 0;
    send_hdr_s.s.total = packet->length;
    send_hdr_s.s.df = 1;
    send_hdr_s.s.aura = BDK_FPA_PACKET_POOL;
    send_hdr_s.s.sizem1 = (gather_addr) ? 1 : lookup_send_size[packet->segments]; /* See nix_init() */
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
    lmt_buf[lmt_len++] = bdk_cpu_to_le64(send_hdr_s.u[0]);
    lmt_buf[lmt_len++] = bdk_cpu_to_le64(send_hdr_s.u[1]);

    if (bdk_unlikely(gather_addr))
    {
        /* Gather IO is too long for lmtst buffer, need to build it on
           the side No need to free in the jump, gather array is part of
           data */
        union bdk_nix_send_jump_s nix_send_jump_s;
        nix_send_jump_s.u[0] = 0;
        nix_send_jump_s.u[1] = 0;
        nix_send_jump_s.s.sizem1 = lookup_send_size[packet->segments];
        nix_send_jump_s.s.ld_type = BDK_NIX_SENDLDTYPE_E_LDD;
        nix_send_jump_s.s.aura = BDK_FPA_PACKET_POOL;
        nix_send_jump_s.s.f = 0;
        nix_send_jump_s.s.subdc = BDK_NIX_SUBDC_E_JUMP;
        nix_send_jump_s.s.addr = gather_addr;

        lmt_buf[lmt_len++] = bdk_cpu_to_le64(nix_send_jump_s.u[0]);
        lmt_buf[lmt_len++] = bdk_cpu_to_le64(nix_send_jump_s.u[1]);
    }
    else
    {
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
            lmt_buf[lmt_len++] = bdk_cpu_to_le64(send_sg_s.u);
            lmt_buf[lmt_len++] = bdk_cpu_to_le64(packet->packet[seg].s.address);
            if (segs < 2)
                break;
            lmt_buf[lmt_len++] = bdk_cpu_to_le64(packet->packet[seg + 1].s.address);
            lmt_buf[lmt_len++] = bdk_cpu_to_le64(packet->packet[seg + 2].s.address);
        }
    }

    uint64_t io_address = bdk_numa_get_address(handle->node, BDK_NIXX_LF_OP_SENDX(nix_index, 0));
    volatile uint64_t *lmt_ptr = bdk_lmt_store_ptr();
    int lmt_status;
    int sent = 0;
    do
    {
        do
        {
            bdk_lmt_cancel();
            for (int i = 0; i < lmt_len; i++)
                lmt_ptr[i] = lmt_buf[i];
            /* Issue LMTST, retrying if hardware says we should */
            lmt_status = bdk_lmt_submit(io_address);
        } while (lmt_status == 0);
        sent++;
    } while (repeat_count--);

    bdk_atomic_add64_nosync(&state->sq_tx[handle->pko_queue], sent);
    return sent;
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
    int nix_index = nix_get_index(handle, false);
    nix_node_state_t *state = &global_node_state[handle->node][nix_index];

    /* Atomic increment data  */
    union bdk_nix_op_q_wdata_s q_wdata_s;
    q_wdata_s.u = 0;
    q_wdata_s.s.q = handle->pko_queue;

    /* Get the hardware TX packets. These are incremented after the
       packet is read from memory. NIX is done with packets counted
       by NIXX_LF_SQ_OP_PKTS */
    bdk_nixx_lf_sq_op_pkts_t pkts;
    pkts.u = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_SQ_OP_PKTS(nix_index))), bdk_cpu_to_le64(q_wdata_s.u)));

    uint64_t sent = bdk_atomic_get64(&state->sq_tx[handle->pko_queue]) & bdk_build_mask(48);
    if (sent < pkts.u)
        return pkts.u + (1ul << 48) - sent;
    else
        return sent - pkts.u;
}

/**
 * Query NIC and fill in the transmit stats for the supplied
 * interface handle.
 *
 * @param handle Port handle
 */
void bdk_nix_fill_tx_stats(bdk_if_handle_t handle)
{
    int nix_index = nix_get_index(handle, false);
    /* Atomic increment data  */
    union bdk_nix_op_q_wdata_s q_wdata_s;
    q_wdata_s.u = 0;
    q_wdata_s.s.q = handle->pko_queue;

    /* Get the hardware stats  */
    bdk_nixx_lf_sq_op_drop_octs_t drop_octs;
    bdk_nixx_lf_sq_op_drop_pkts_t drop_pkts;
    bdk_nixx_lf_sq_op_octs_t octs;
    bdk_nixx_lf_sq_op_pkts_t pkts;

    drop_octs.u = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_SQ_OP_DROP_OCTS(nix_index))), bdk_cpu_to_le64(q_wdata_s.u)));
    drop_pkts.u = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_SQ_OP_DROP_PKTS(nix_index))), bdk_cpu_to_le64(q_wdata_s.u)));
    octs.u = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_SQ_OP_OCTS(nix_index))), bdk_cpu_to_le64(q_wdata_s.u)));
    pkts.u = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_SQ_OP_PKTS(nix_index))), bdk_cpu_to_le64(q_wdata_s.u)));

    /* Account for adding FCS */
    const int bytes_off_tx = (handle->flags & BDK_IF_FLAGS_HAS_FCS) ? 4 : 0;

    handle->stats.tx.dropped_octets -= handle->stats.tx.dropped_packets * bytes_off_tx;
    handle->stats.tx.octets -= handle->stats.tx.packets * bytes_off_tx;

    handle->stats.tx.dropped_octets = bdk_update_stat_with_overflow(drop_octs.s.cnt, handle->stats.tx.dropped_octets, 48);
    handle->stats.tx.dropped_packets = bdk_update_stat_with_overflow(drop_pkts.s.cnt, handle->stats.tx.dropped_packets, 48);
    handle->stats.tx.octets = bdk_update_stat_with_overflow(octs.s.cnt, handle->stats.tx.octets, 48);
    handle->stats.tx.packets = bdk_update_stat_with_overflow(pkts.s.cnt, handle->stats.tx.packets, 48);

    handle->stats.tx.dropped_octets += handle->stats.tx.dropped_packets * bytes_off_tx;
    handle->stats.tx.octets += handle->stats.tx.packets * bytes_off_tx;
}

/**
 * Query NIC and fill in the receive stats for the supplied
 * interface handle.
 *
 * @param handle Port handle
 */
void bdk_nix_fill_rx_stats(bdk_if_handle_t handle)
{
    int nix_index = nix_get_index(handle, true);
    /* Normal RX stats are done by software on receive */

    /* Atomic increment data  */
    union bdk_nix_op_q_wdata_s q_wdata_s;
    q_wdata_s.u = 0;
    q_wdata_s.s.q = handle->pko_queue;

    /* Get the hardware stats  */
    bdk_nixx_lf_rq_op_drop_octs_t drop_octs;
    bdk_nixx_lf_rq_op_drop_pkts_t drop_pkts;

    drop_octs.u = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_RQ_OP_DROP_OCTS(nix_index))), bdk_cpu_to_le64(q_wdata_s.u)));
    drop_pkts.u = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(bdk_phys_to_ptr(bdk_numa_get_address(handle->node, BDK_NIXX_LF_RQ_OP_DROP_PKTS(nix_index))), bdk_cpu_to_le64(q_wdata_s.u)));

    /* Account for adding FCS */
    const int bytes_off_rx = (handle->flags & BDK_IF_FLAGS_HAS_FCS) ? 4 : 0;

    handle->stats.rx.dropped_octets -= handle->stats.rx.dropped_packets * bytes_off_rx;

    handle->stats.rx.dropped_octets = bdk_update_stat_with_overflow(drop_octs.s.cnt, handle->stats.rx.dropped_octets, 48);
    handle->stats.rx.dropped_packets = bdk_update_stat_with_overflow(drop_pkts.s.cnt, handle->stats.rx.dropped_packets, 48);

    handle->stats.rx.dropped_octets += handle->stats.rx.dropped_packets * bytes_off_rx;
}

