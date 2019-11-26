/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <malloc.h>
#include "libbdk-arch/bdk-csrs-npa.h"
#include "libbdk-arch/bdk-csrs-nix.h"
#include "libbdk-arch/bdk-csrs-rvu.h"
#include "libbdk-arch/bdk-csrs-sso.h"

/**
 * Get a new block from an aura
 *
 * @param node   Node to use in a Numa setup. See bdk-numa.h
 * @param aura   Aura to get the block from (0-BDK_FPA_NUM_AURAS)
 *
 * @return Pointer to the block or NULL on failure
 */
static void *npa_alloc(bdk_node_t node, int aura)
{
    union bdk_npa_aura_op_wdata_s wdata;
    wdata.u = 0;
    wdata.s.aura = aura;
    wdata.s.drop = 1;
    void *ptr = bdk_phys_to_ptr(bdk_numa_get_address(node, BDK_NPA_LF_AURA_OP_ALLOCX(0)));
    uint64_t address = bdk_le64_to_cpu(bdk_atomic_fetch_and_add64_nosync(ptr, bdk_cpu_to_le64(wdata.u)));

    BDK_TRACE(FPA, "N%d NPA alloc aura=%d addr=0x%lx\n", node, aura, address);

    if (bdk_likely(address))
        return bdk_phys_to_ptr(address);
    else
        return NULL;
}

/**
 * Free a block allocated with bdk_fpa_alloc().  Does NOT provide memory ordering
 * for core stores. Software must insure all pending writes are flushed before
 * calling this function.
 *
 * @param node    Node to use in a Numa setup. See bdk-numa.h
 * @param address Physical address to free to the FPA aura
 * @param aura    Aura number to free to (0-BDK_FPA_NUM_AURAS)
 * @param num_cache_lines
 *                Cache lines to invalidate. Use this if the data in the buffer is no longer
 *                requires cache coherency. Normally best to set this to zero.
 */
static void npa_raw_free(bdk_node_t node, uint64_t address, int aura, int num_cache_lines)
{
    BDK_TRACE(FPA, "N%d NPA free aura=%d addr=0x%lx\n", node, aura, address);
    void *ptr = bdk_phys_to_ptr(bdk_numa_get_address(node, BDK_NPA_LF_AURA_OP_FREE0));
    bdk_npa_lf_aura_op_free1_t op_free1;
    op_free1.u = 0;
    op_free1.s.aura = aura;
    asm volatile ("" : : : "memory");  /* Prevent GCC from reordering around free */
    BDK_STORE_PAIR(ptr, bdk_cpu_to_le64(address), bdk_cpu_to_le64(op_free1.u));
}

static int npa_lf_alloc(bdk_node_t node)
{
    const int LOC_AURA_SIZE = 1; /* BDK sets up 128 auras, the smallest allowed */
    __bdk_fpa_state_t *state = &__bdk_fpa_node_state[node];

    BDK_CSR_INIT(npa_af_const, node, BDK_NPA_AF_CONST);
    if (state->next_free_lf >= npa_af_const.s.lfs)
    {
        bdk_error("N%d NPA: Ran out of LFs\n", node);
        return -1;
    }

    int lf = state->next_free_lf++;

    /* Allocate space for storing LF Queue Interrupts */
    int alloc_size = sizeof(union bdk_npa_qint_hw_s) * npa_af_const.s.qints;
    void *lf_qints_base = memalign(BDK_CACHE_LINE_SIZE, alloc_size);
    if (!lf_qints_base)
    {
        bdk_error("N%d NPA: Memory alloc failed for LF Queue Interrupts\n", node);
        state->next_free_lf--;
        return -1;
    }
    bdk_zero_memory(lf_qints_base, alloc_size);
    BDK_CSR_WRITE(node, BDK_NPA_AF_LFX_QINTS_BASE(lf), bdk_ptr_to_phys(lf_qints_base));
    /* NPA_AF_LFX_QINTS_CFG defaults are right */
    BDK_CSR_WRITE(node, BDK_NPA_AF_LFX_LOC_AURAS_BASE(lf), bdk_ptr_to_phys(state->npa_auras_ptr));

    /* Complete config of LF Auras */
    BDK_CSR_MODIFY(c, node, BDK_NPA_AF_LFX_AURAS_CFG(lf),
        c.s.loc_aura_offset = 0; /* Always zero for BDK */
        c.s.loc_aura_size = LOC_AURA_SIZE);
    return lf;
}

static void npa_aq_issue_command(bdk_node_t node, int op/*bdk_npa_aq_instop_e*/, int ctype /*bdk_npa_aq_ctype_e*/, int lf, int aura, void *resp)
{
    /* Find the location in the Admin Queue */
    BDK_CSR_INIT(aq_status, node, BDK_NPA_AF_AQ_STATUS);
    BDK_CSR_INIT(aq_base, node, BDK_NPA_AF_AQ_BASE);
    union bdk_npa_aq_inst_s *aq_inst = bdk_phys_to_ptr(aq_base.u);
    aq_inst += aq_status.s.head_ptr;

    /* Build the instruction */
    aq_inst->u[0] = 0;
    aq_inst->u[1] = 0;
    aq_inst->s.op = op;
    aq_inst->s.ctype = ctype;
    aq_inst->s.lf = lf;
    aq_inst->s.cindex = aura;
    aq_inst->s.doneint = 0;
    aq_inst->s.res_addr = bdk_ptr_to_phys(resp);
    aq_inst->u[0] = bdk_cpu_to_le64(aq_inst->u[0]);
    aq_inst->u[1] = bdk_cpu_to_le64(aq_inst->u[1]);

    /* Issue the instruction */
    BDK_WMB;
    BDK_CSR_WRITE(node, BDK_NPA_AF_AQ_DOOR, 1);

    /* Wait for completion  */
    volatile union bdk_npa_aq_res_s *result_le = resp;
    union bdk_npa_aq_res_s result;
    do
    {
        bdk_thread_yield();
        result.u[0] = bdk_le64_to_cpu(result_le->u[0]);
        result.u[1] = bdk_le64_to_cpu(result_le->u[1]);
    } while (result.s.compcode == 0);
    if (result.s.compcode != BDK_NPA_AQ_COMP_E_GOOD)
        bdk_fatal("N%d, NPA: Admin Queue failed with code %d\n", node, result.s.compcode);
}

/**
 * Initialize an Aura for a specific pool
 *
 * @param node       Node to use in a Numa setup. See bdk-numa.h
 * @param aura       Aura to initialize, or -1 to dynamically allocate a free aura
 * @param pool       Pool this aura is for (0 <= pool < BDK_FPA_NUM_POOLS)
 * @param num_blocks Number of buffers to allow this aura to contain. This may be different
 *                   from the pool
 * @param fc_addr    Address to write the aura count to in memory. Not valid for CN8XXX parts.
 *
 * @return Aura number or negative on failure
 */
static int npa_init_aura(bdk_node_t node, int aura, bdk_fpa_pool_t pool, int num_blocks, uint64_t fc_addr)
{
    const int lf = 0;
    __bdk_fpa_state_t *state = &__bdk_fpa_node_state[node];
    BDK_CSR_INIT(npa_af_const1, node, BDK_NPA_AF_CONST1);
    if (aura < 0)
    {
        aura = state->next_free_aura++;
        if (aura >= BDK_FPA_NUM_AURAS)
        {
            bdk_error("N%d NPA: Ran out of auras\n", node);
            return -1;
        }
    }

    BDK_TRACE(FPA, "N%d NPA: Initializing Aura %d using pool %d with %d buffers\n", node, aura, pool, num_blocks);

    /* Calculate the stack SHIFT */
    int shift = 0;
    while (num_blocks >> shift >= 0x100)
        shift++;

    BDK_TRACE(FPA, "N%d NPA: Issuing aura INIT\n", node);
    struct
    {
        union bdk_npa_aq_res_s result BDK_CACHE_LINE_ALIGNED;
        union bdk_npa_aura_s aura BDK_CACHE_LINE_ALIGNED;
    } init_req;
    bdk_zero_memory(&init_req, sizeof(init_req));
    init_req.aura.s.pool_addr = bdk_ptr_to_phys(state->npa_pools_ptr + (1 << npa_af_const1.s.pool_log2bytes) * pool);
    init_req.aura.s.ena = 1;
    init_req.aura.s.pool_drop_ena = (fc_addr) ? 0 : 1; /* Don't enable drop if flow control is being used */
    init_req.aura.s.aura_drop_ena = (fc_addr) ? 0 : 1; /* Don't enable drop if flow control is being used */
    init_req.aura.s.bp_ena = 0;
    init_req.aura.s.aura_drop = 90 * 256 / 100; /* 255=Full, 0=empty: Drop when 90% full */
    init_req.aura.s.shift = shift;
    init_req.aura.s.nix0_bpid = 0;
    init_req.aura.s.nix1_bpid = 0;
    init_req.aura.s.limit = num_blocks;
    init_req.aura.s.bp = 80 * 256 / 100; /* 255=Full, 0=empty: RED when 80% full */
    init_req.aura.s.pool_drop = 10 * 256 / 100; /* 0=Full, 255=empty: Drop when 90% full */
    if (fc_addr)
    {
        init_req.aura.s.fc_ena = 1;
        init_req.aura.s.fc_stype = 2;
        init_req.aura.s.fc_hyst_bits = 2;
        init_req.aura.s.fc_addr = fc_addr;
    }
#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(init_req.aura) / 8; i++)
        init_req.aura.u[i] = bdk_cpu_to_le64(init_req.aura.u[i]);
#endif
    npa_aq_issue_command(node, BDK_NPA_AQ_INSTOP_E_INIT, BDK_NPA_AQ_CTYPE_E_AURA, lf, aura, &init_req);
    state->buffer_size_aura[aura] = state->buffer_size_pool[pool];
    return aura;
}

/**
 * Fill a pool with buffers
 *
 * @param node       Node to use in a Numa setup. See bdk-numa.h
 * @param pool       Pool to initialize (0 <= pool < BDK_FPA_NUM_POOLS)
 * @param num_blocks Number of blocks
 *
 * @return Zero on Success, negative on failure
 */
static int npa_fill_pool(bdk_node_t node, bdk_fpa_pool_t pool, int num_blocks)
{
    const int lf = 0;
    __bdk_fpa_state_t *state = &__bdk_fpa_node_state[node];

    int block_size = 0;
    switch (pool)
    {
        case BDK_FPA_PACKET_POOL: /* Stores PKI packet buffers */
            block_size = bdk_config_get_int(BDK_CONFIG_PACKET_BUFFER_SIZE);
            break;
        case BDK_FPA_SSO_POOL: /* Used for internal storage in the SSO */
        {
            BDK_CSR_INIT(sso_const1, node, BDK_SSO_AF_CONST1);
            block_size = sso_const1.s.xaq_buf_size;
            break;
        }
        case BDK_FPA_PKO_POOL: /* Actually NIX SQ */
            {
                BDK_CSR_INIT(sq_const, node, BDK_NIXX_AF_SQ_CONST(0));
                block_size = sq_const.s.sqb_size;
                break;
            }
        case BDK_FPA_NUM_POOLS: /* Invalid, here to keep compiler happy */
            break;
    }
    if (block_size == 0)
        bdk_fatal("NPA: Unable to determine block size for pool %d\n", pool);

    BDK_TRACE(FPA, "N%d NPA: Initializing pool %d with %d buffers\n", node, pool, num_blocks);
    state->buffer_size_pool[pool] = block_size;
    BDK_CSR_INIT(npa_af_const, node, BDK_NPA_AF_CONST);

    /* Allocate space for buffers */
    int alloc_size = block_size * num_blocks;
    void *buffers = memalign(block_size, alloc_size);
    if (!buffers)
    {
        bdk_error("N%d NPA: Failed to allocate space for buffers\n", node);
        return -1;
    }
    bdk_zero_memory(buffers, alloc_size);

    /* Allocate space for stack */
    int stack_size = (num_blocks + npa_af_const.s.stack_page_ptrs - 1) / npa_af_const.s.stack_page_ptrs;
    alloc_size = stack_size * npa_af_const.s.stack_page_bytes;
    void *stack = memalign(BDK_CACHE_LINE_SIZE, alloc_size);
    if (!stack)
    {
        bdk_error("N%d NPA: Failed to allocate space for pool stack\n", node);
        free(buffers);
        return -1;
    }
    bdk_zero_memory(stack, alloc_size);

    int aura = npa_init_aura(node, pool, pool, num_blocks, 0);
    if (aura < 0)
        return -1;

    /* Calculate the stack SHIFT */
    int shift = 0;
    while (stack_size >> shift >= 0x100)
        shift++;

    /* Initialize the pool */
    BDK_TRACE(FPA, "N%d NPA: Issuing pool INIT\n", node);
    struct
    {
        union bdk_npa_aq_res_s result BDK_CACHE_LINE_ALIGNED;
        union bdk_npa_pool_s pool BDK_CACHE_LINE_ALIGNED;
    } init_req;
    bdk_zero_memory(&init_req, sizeof(init_req));
    init_req.pool.s.stack_base = bdk_ptr_to_phys(stack);
    init_req.pool.s.ena = 1;
    init_req.pool.s.nat_align = 1;
    init_req.pool.s.buf_size = block_size / BDK_CACHE_LINE_SIZE;
    init_req.pool.s.stack_max_pages = stack_size;
    init_req.pool.s.shift = shift;
    init_req.pool.s.ptr_start = bdk_ptr_to_phys(buffers);
    init_req.pool.s.ptr_end = init_req.pool.s.ptr_start + block_size * num_blocks - 1;
#if __BYTE_ORDER == __BIG_ENDIAN
    for (int i = 0; i < (int)sizeof(init_req.pool) / 8; i++)
        init_req.pool.u[i] = bdk_cpu_to_le64(init_req.pool.u[i]);
#endif
    npa_aq_issue_command(node, BDK_NPA_AQ_INSTOP_E_INIT, BDK_NPA_AQ_CTYPE_E_POOL, lf, pool, &init_req);

    /* Adding buffers decrement the aura count. Update the count
        for the new buffers */
    BDK_TRACE(FPA, "N%d NPA: Updating Aura count\n", node);
    bdk_npa_lf_aura_op_cnt_t aura_op_cnt;
    aura_op_cnt.u = 0;
    aura_op_cnt.s.aura = aura;
    aura_op_cnt.s.cnt_add = 1;
    aura_op_cnt.s.count = num_blocks;
    BDK_CSR_WRITE(node, BDK_NPA_LF_AURA_OP_CNT, aura_op_cnt.u);

    /* Fill pool */
    BDK_TRACE(FPA, "N%d NPA: Filling pool\n", node);
    while (num_blocks--)
    {
        bdk_fpa_free(node, buffers, aura, 0);
        buffers += block_size;
    }

    BDK_TRACE(FPA, "N%d NPA: Pool init succeeded\n", node);
    return 0;
}

/**
 * Global NPA initialization
 *
 * @return Zero on success, negative on failure
 */
static int npa_init(bdk_node_t node)
{
    const int AF_AQ_CFG_QSIZE = 0; /* Size of the NPA AF Admin Queue, 0=16 entries */
    __bdk_fpa_state_t *state = &__bdk_fpa_node_state[node];
    bdk_zero_memory(state, sizeof(*state));

    /* Reserve the first auras for 1:1 mapping to pools */
    state->next_free_aura = BDK_FPA_NUM_POOLS;

    BDK_CSR_INIT(npa_af_const1, node, BDK_NPA_AF_CONST1);

    /* Enable the NDC cache */
    BDK_CSR_MODIFY(c, node, BDK_NPA_AF_NDC_CFG,
        c.u = 0);

    /* Allocate space for NPA overhead, which contains the AF Admin
       Queue, Aura Context Table, and the Pool Context Table. To make
       management of this easier, we create one large malloc()
       covering all of them */
    BDK_TRACE(FPA, "N%d NPA: Allocating Admin Queue and context areas\n", node);
    int num_aq_entries = 16 << (AF_AQ_CFG_QSIZE * 2);
    int alloc_size = sizeof(union bdk_npa_aq_inst_s) * num_aq_entries;
    alloc_size += BDK_FPA_NUM_AURAS * (1 << npa_af_const1.s.aura_log2bytes);
    alloc_size += BDK_FPA_NUM_POOLS * (1 << npa_af_const1.s.pool_log2bytes);
    void *aq_base = memalign(BDK_CACHE_LINE_SIZE, alloc_size);
    if (!aq_base)
    {
        bdk_error("N%d NPA: Memory alloc failed for NPA context\n", node);
        return -1;
    }
    bdk_zero_memory(aq_base, alloc_size);
    state->npa_auras_ptr = aq_base + sizeof(union bdk_npa_aq_inst_s) * num_aq_entries;
    state->npa_pools_ptr = state->npa_auras_ptr + BDK_FPA_NUM_AURAS * (1 << npa_af_const1.s.aura_log2bytes);

    BDK_TRACE(FPA, "N%d NPA: Initializing AF Admin Queue\n", node);
    BDK_CSR_WRITE(node, BDK_NPA_AF_AQ_BASE, bdk_ptr_to_phys(aq_base));
    BDK_CSR_MODIFY(c, node, BDK_NPA_AF_AQ_CFG,
        c.s.qsize = AF_AQ_CFG_QSIZE);
    /* NPA_AF_GEN_CFG defaults are right */

    /* Hardcode RVU selection to PF0 */
    union bdk_rvu_pf_func_s rvu_pf_func;
    rvu_pf_func.u = 0;
    rvu_pf_func.s.pf = 0;
    rvu_pf_func.s.func = 0;

    /* Allocate a NPA LF for use by RVU */
    BDK_TRACE(FPA, "N%d Allocating a NPA LF\n", node);
    int lf = npa_lf_alloc(node);
    if (lf == -1)
    {
        bdk_error("N%d NPA: LF allocation failed\n", node);
        return -1;
    }

    /* Allocate MSIX space for NPA */
    BDK_TRACE(FPA, "N%d NPA: Setting MSIX offsets\n", node);
    BDK_CSR_MODIFY(c, node, BDK_NPA_PRIV_AF_INT_CFG,
        c.s.msix_offset = bdk_rvu_alloc_msix(node, 3)); /* NPA_AF_INT_VEC_E */
    BDK_CSR_MODIFY(c, node, BDK_NPA_PRIV_LFX_INT_CFG(lf),
        c.s.msix_offset = bdk_rvu_alloc_msix(node, 65)); /* NPA_LF_INT_VEC_E */

    /* Assign and enable the RVU access to NPA */
    BDK_CSR_MODIFY(c, node, BDK_NPA_PRIV_LFX_CFG(lf),
        c.s.ena = 1;        /* Enable the NPA LF */
        c.s.pf_func = rvu_pf_func.u; /* Which RVU to use */
        c.s.slot = 0);      /* Must be zero for NPA */
    BDK_TRACE(FPA, "N%d NPA: Read for pool and aura allocation\n", node);
    return 0;
}

/**
 * Global NPA initialization
 *
 * @return Zero on success, negative on failure
 */
int __bdk_npa_init(bdk_node_t node)
{
    bdk_fpa_alloc = npa_alloc;
    __bdk_fpa_raw_free = npa_raw_free;
    bdk_fpa_fill_pool = npa_fill_pool;
    bdk_fpa_init_aura = npa_init_aura;
    return npa_init(node);
}

