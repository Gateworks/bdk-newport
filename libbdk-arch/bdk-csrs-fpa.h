#ifndef __BDK_CSRS_FPA_H__
#define __BDK_CSRS_FPA_H__
/* This file is auto-generated. Do not edit */

/***********************license start***********************************
* Copyright (C) 2019 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/


/**
 * @file
 *
 * Configuration and status register (CSR) address and type definitions for
 * OcteonTX FPA.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration fpa_bar_e
 *
 * FPA Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_FPA_BAR_E_FPA_PF_BAR0 (0x828000000000ll)
#define BDK_FPA_BAR_E_FPA_PF_BAR0_SIZE 0x80000000ull
#define BDK_FPA_BAR_E_FPA_PF_BAR4 (0x828300000000ll)
#define BDK_FPA_BAR_E_FPA_PF_BAR4_SIZE 0x100000ull
#define BDK_FPA_BAR_E_FPA_VFX_BAR0(a) (0x828400000000ll + 0x400000ll * (a))
#define BDK_FPA_BAR_E_FPA_VFX_BAR0_SIZE 0x400000ull
#define BDK_FPA_BAR_E_FPA_VFX_BAR4(a) (0x828700000000ll + 0x100000ll * (a))
#define BDK_FPA_BAR_E_FPA_VFX_BAR4_SIZE 0x100000ull

/**
 * Enumeration fpa_pf_int_vec_e
 *
 * FPA MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_FPA_PF_INT_VEC_E_ECC (0)
#define BDK_FPA_PF_INT_VEC_E_GEN (1)

/**
 * Enumeration fpa_vf_int_vec_e
 *
 * FPA MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_FPA_VF_INT_VEC_E_MISC (0)

/**
 * Structure fpa_alloc_addr_s
 *
 * FPA Allocate Operation Address Structure
 * This structure forms the address for FPA_VHAURA()_OP_ALLOC().
 */
union bdk_fpa_alloc_addr_s
{
    uint64_t u;
    struct bdk_fpa_alloc_addr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_15_63        : 49;
        uint64_t red                   : 1;  /**< [ 14: 14] Perform RED processing on allocation. Refer to Sections 10.3.2 and 10.3.4. */
        uint64_t drop                  : 1;  /**< [ 13: 13] Perform DROP processing on allocation. Refer to Sections 10.3.3 and 10.3.4. */
        uint64_t reserved_0_12         : 13;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_12         : 13;
        uint64_t drop                  : 1;  /**< [ 13: 13] Perform DROP processing on allocation. Refer to Sections 10.3.3 and 10.3.4. */
        uint64_t red                   : 1;  /**< [ 14: 14] Perform RED processing on allocation. Refer to Sections 10.3.2 and 10.3.4. */
        uint64_t reserved_15_63        : 49;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_alloc_addr_s_s cn; */
};

/**
 * Structure fpa_free_addr_s
 *
 * FPA Free Operation Address Structure
 * This structure forms the address for FPA_VHAURA()_OP_FREE().
 */
union bdk_fpa_free_addr_s
{
    uint64_t u;
    struct bdk_fpa_free_addr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_15_63        : 49;
        uint64_t fabs                  : 1;  /**< [ 14: 14] Free absolute. */
        uint64_t reserved_12_13        : 2;
        uint64_t dwb_count             : 9;  /**< [ 11:  3] Number of cache lines for which the hardware (in IOB) should try to execute
                                                                 'don't-write-back' commands. The hardware starts from the free operation's
                                                                 FPA_VHAURA()_OP_FREE()[ADDR] (i.e. to where the address points) and marches
                                                                 forward linearly for [DWB_COUNT] cache lines. As the DWB command can modify the
                                                                 value of memory locations, software must ensure that the maximum addressed DWB'd
                                                                 ([ADDR] + [DWB_COUNT] * 128 - 1) does not go past the end of the buffer being
                                                                 freed. As the DWB commands consume CMI bandwidth, software should keep the
                                                                 [DWB_COUNT] low to cover only those cache blocks that may have been modified. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t dwb_count             : 9;  /**< [ 11:  3] Number of cache lines for which the hardware (in IOB) should try to execute
                                                                 'don't-write-back' commands. The hardware starts from the free operation's
                                                                 FPA_VHAURA()_OP_FREE()[ADDR] (i.e. to where the address points) and marches
                                                                 forward linearly for [DWB_COUNT] cache lines. As the DWB command can modify the
                                                                 value of memory locations, software must ensure that the maximum addressed DWB'd
                                                                 ([ADDR] + [DWB_COUNT] * 128 - 1) does not go past the end of the buffer being
                                                                 freed. As the DWB commands consume CMI bandwidth, software should keep the
                                                                 [DWB_COUNT] low to cover only those cache blocks that may have been modified. */
        uint64_t reserved_12_13        : 2;
        uint64_t fabs                  : 1;  /**< [ 14: 14] Free absolute. */
        uint64_t reserved_15_63        : 49;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_free_addr_s_s cn; */
};

/**
 * Register (NCB) fpa_addr_range_error
 *
 * FPA Address Range Error Information Register
 * When any FPA_VF()_INT[RANGE] error occurs, this register is latched with
 * additional error information. [POOL} and [ADDR] must be used from a single
 * read of this register to avoid a race whereby a new range error changes this
 * register.
 */
union bdk_fpa_addr_range_error
{
    uint64_t u;
    struct bdk_fpa_addr_range_error_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pool                  : 8;  /**< [ 63: 56](RO/H) Pool to which address was sent. */
        uint64_t reserved_49_55        : 7;
        uint64_t addr                  : 49; /**< [ 48:  0](RO/H) Failing IOVA. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 49; /**< [ 48:  0](RO/H) Failing IOVA. */
        uint64_t reserved_49_55        : 7;
        uint64_t pool                  : 8;  /**< [ 63: 56](RO/H) Pool to which address was sent. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_addr_range_error_s cn; */
};
typedef union bdk_fpa_addr_range_error bdk_fpa_addr_range_error_t;

#define BDK_FPA_ADDR_RANGE_ERROR BDK_FPA_ADDR_RANGE_ERROR_FUNC()
static inline uint64_t BDK_FPA_ADDR_RANGE_ERROR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_ADDR_RANGE_ERROR_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000458ll;
    __bdk_csr_fatal("FPA_ADDR_RANGE_ERROR", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_ADDR_RANGE_ERROR bdk_fpa_addr_range_error_t
#define bustype_BDK_FPA_ADDR_RANGE_ERROR BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_ADDR_RANGE_ERROR "FPA_ADDR_RANGE_ERROR"
#define device_bar_BDK_FPA_ADDR_RANGE_ERROR 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_ADDR_RANGE_ERROR 0
#define arguments_BDK_FPA_ADDR_RANGE_ERROR -1,-1,-1,-1

/**
 * Register (NCB) fpa_aura#_cfg
 *
 * FPA Aura Config Register
 * This register configures aura backpressure, etc.
 */
union bdk_fpa_aurax_cfg
{
    uint64_t u;
    struct bdk_fpa_aurax_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ptr_dis               : 1;  /**< [  9:  9](R/W) Disable aura tracking pointer allocates/returns.

                                                                 0 = When FPA allocates a pointer from this aura (including coprocessor or core requests),
                                                                 increment the count. When a pointer is returned to FPA for this aura (including
                                                                 coprocessor or core requests), decrement the count. Note that PKI may prefetch buffers it
                                                                 later returns, this may result in the count intermittently being higher than the number of
                                                                 buffers actually in use by packets visible to software.

                                                                 1 = Pointer allocations/returns will not automatically change the count.
                                                                 Note specific requests to change the count, including FPA_VHAURA()_CNT_ADD,
                                                                 PKO_SEND_AURA_S, or PKI_AURA()_CFG[PKT_ADD] will be applied regardless of the
                                                                 setting of this bit. */
        uint64_t avg_con               : 9;  /**< [  8:  0](R/W) This value controls how much of each present average resource level is used to
                                                                 calculate the new resource level. The value is a number from 0 to 256, which
                                                                 represents [AVG_CON]/256 of the average resource level that will be used in the
                                                                 calculation:
                                                                 _  next_LEVEL = ([AVG_CON]/256) * prev_LEVEL
                                                                 _  + (1-([AVG_CON]/256)) * count

                                                                 Note setting this value to zero will disable averaging, and always use the most immediate
                                                                 levels. FPA_GEN_CFG[AVG_EN] must be set and FPA_GEN_CFG[LVL_DLY] must be nonzero to
                                                                 globally enable averaging. FPA_RED_DELAY[AVG_DLY] controls the periodicity of the level
                                                                 calculations. */
#else /* Word 0 - Little Endian */
        uint64_t avg_con               : 9;  /**< [  8:  0](R/W) This value controls how much of each present average resource level is used to
                                                                 calculate the new resource level. The value is a number from 0 to 256, which
                                                                 represents [AVG_CON]/256 of the average resource level that will be used in the
                                                                 calculation:
                                                                 _  next_LEVEL = ([AVG_CON]/256) * prev_LEVEL
                                                                 _  + (1-([AVG_CON]/256)) * count

                                                                 Note setting this value to zero will disable averaging, and always use the most immediate
                                                                 levels. FPA_GEN_CFG[AVG_EN] must be set and FPA_GEN_CFG[LVL_DLY] must be nonzero to
                                                                 globally enable averaging. FPA_RED_DELAY[AVG_DLY] controls the periodicity of the level
                                                                 calculations. */
        uint64_t ptr_dis               : 1;  /**< [  9:  9](R/W) Disable aura tracking pointer allocates/returns.

                                                                 0 = When FPA allocates a pointer from this aura (including coprocessor or core requests),
                                                                 increment the count. When a pointer is returned to FPA for this aura (including
                                                                 coprocessor or core requests), decrement the count. Note that PKI may prefetch buffers it
                                                                 later returns, this may result in the count intermittently being higher than the number of
                                                                 buffers actually in use by packets visible to software.

                                                                 1 = Pointer allocations/returns will not automatically change the count.
                                                                 Note specific requests to change the count, including FPA_VHAURA()_CNT_ADD,
                                                                 PKO_SEND_AURA_S, or PKI_AURA()_CFG[PKT_ADD] will be applied regardless of the
                                                                 setting of this bit. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_aurax_cfg_s cn; */
};
typedef union bdk_fpa_aurax_cfg bdk_fpa_aurax_cfg_t;

static inline uint64_t BDK_FPA_AURAX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_AURAX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x828040008110ll + 0x10000ll * ((a) & 0x1ff);
    __bdk_csr_fatal("FPA_AURAX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_AURAX_CFG(a) bdk_fpa_aurax_cfg_t
#define bustype_BDK_FPA_AURAX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_AURAX_CFG(a) "FPA_AURAX_CFG"
#define device_bar_BDK_FPA_AURAX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_AURAX_CFG(a) (a)
#define arguments_BDK_FPA_AURAX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_aura#_cnt_levels
 *
 * FPA Aura Count Level Registers
 */
union bdk_fpa_aurax_cnt_levels
{
    uint64_t u;
    struct bdk_fpa_aurax_cnt_levels_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_41_63        : 23;
        uint64_t drop_dis              : 1;  /**< [ 40: 40](R/W) Disable aura DROP based on the [DROP] level. */
        uint64_t bp_ena                : 1;  /**< [ 39: 39](R/W) Enable backpressure based on [BP] level. If set FPA_GEN_CFG[LVL_DLY] must be nonzero.
                                                                 PKI_AURA()_CFG[ENA_BP] must also be set for backpressure to propagate through PKI. */
        uint64_t red_ena               : 1;  /**< [ 38: 38](R/W) Enable aura RED based on [DROP] and [PASS] levels. If set FPA_GEN_CFG[LVL_DLY] must be
                                                                 nonzero.
                                                                 If set, aura RED is performed on core requests with
                                                                 FPA_ALLOC_ADDR_S[RED] set, and also may be performed on the
                                                                 first PKI allocation request for a packet (depends on PKI style and aura
                                                                 configuration). */
        uint64_t shift                 : 6;  /**< [ 37: 32](R/W) Right shift to FPA_VHAURA()_CNT[CNT] to create a narrower depth for aura QOS and
                                                                 backpressure calculations. PKI saturates the shifted FPA_VHAURA()_CNT[CNT] to
                                                                 8-bits, and compares this 8-bit shifted and saturated depth directly to
                                                                 [DROP/BP]. PKI also creates [LEVEL], which is a moving average of the 8-bit
                                                                 shifted and saturated depth of the aura, for comparison to [DROP/PASS] in RED
                                                                 calculations. */
        uint64_t bp                    : 8;  /**< [ 31: 24](R/W) Backpressure can assert if the current 8-bit shifted and saturated FPA_VHAURA()_CNT[CNT]
                                                                 is
                                                                 equal to or greater than this value. */
        uint64_t drop                  : 8;  /**< [ 23: 16](R/W) If [RED_ENA]=1 and RED processing is requested, the packet will be dropped if
                                                                 [LEVEL] is equal to or greater than this value.

                                                                 If [DROP_DIS]=0 and DROP processing is requested, the packet will be dropped if
                                                                 the current 8-bit shifted and saturated FPA_VHAURA()_CNT[CNT] is equal to or greater
                                                                 than this value. */
        uint64_t pass                  : 8;  /**< [ 15:  8](R/W) Aura RED processing will not drop an allocation request if [LEVEL] is less than this value. */
        uint64_t level                 : 8;  /**< [  7:  0](RO/H) Current moving average of the 8-bit shifted and saturated FPA_VHAURA()_CNT[CNT].
                                                                 The lower [LEVEL] is, the more free resources. The highest [LEVEL]'s indicate buffer
                                                                 exhaustion.
                                                                 See [SHIFT]. */
#else /* Word 0 - Little Endian */
        uint64_t level                 : 8;  /**< [  7:  0](RO/H) Current moving average of the 8-bit shifted and saturated FPA_VHAURA()_CNT[CNT].
                                                                 The lower [LEVEL] is, the more free resources. The highest [LEVEL]'s indicate buffer
                                                                 exhaustion.
                                                                 See [SHIFT]. */
        uint64_t pass                  : 8;  /**< [ 15:  8](R/W) Aura RED processing will not drop an allocation request if [LEVEL] is less than this value. */
        uint64_t drop                  : 8;  /**< [ 23: 16](R/W) If [RED_ENA]=1 and RED processing is requested, the packet will be dropped if
                                                                 [LEVEL] is equal to or greater than this value.

                                                                 If [DROP_DIS]=0 and DROP processing is requested, the packet will be dropped if
                                                                 the current 8-bit shifted and saturated FPA_VHAURA()_CNT[CNT] is equal to or greater
                                                                 than this value. */
        uint64_t bp                    : 8;  /**< [ 31: 24](R/W) Backpressure can assert if the current 8-bit shifted and saturated FPA_VHAURA()_CNT[CNT]
                                                                 is
                                                                 equal to or greater than this value. */
        uint64_t shift                 : 6;  /**< [ 37: 32](R/W) Right shift to FPA_VHAURA()_CNT[CNT] to create a narrower depth for aura QOS and
                                                                 backpressure calculations. PKI saturates the shifted FPA_VHAURA()_CNT[CNT] to
                                                                 8-bits, and compares this 8-bit shifted and saturated depth directly to
                                                                 [DROP/BP]. PKI also creates [LEVEL], which is a moving average of the 8-bit
                                                                 shifted and saturated depth of the aura, for comparison to [DROP/PASS] in RED
                                                                 calculations. */
        uint64_t red_ena               : 1;  /**< [ 38: 38](R/W) Enable aura RED based on [DROP] and [PASS] levels. If set FPA_GEN_CFG[LVL_DLY] must be
                                                                 nonzero.
                                                                 If set, aura RED is performed on core requests with
                                                                 FPA_ALLOC_ADDR_S[RED] set, and also may be performed on the
                                                                 first PKI allocation request for a packet (depends on PKI style and aura
                                                                 configuration). */
        uint64_t bp_ena                : 1;  /**< [ 39: 39](R/W) Enable backpressure based on [BP] level. If set FPA_GEN_CFG[LVL_DLY] must be nonzero.
                                                                 PKI_AURA()_CFG[ENA_BP] must also be set for backpressure to propagate through PKI. */
        uint64_t drop_dis              : 1;  /**< [ 40: 40](R/W) Disable aura DROP based on the [DROP] level. */
        uint64_t reserved_41_63        : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_aurax_cnt_levels_s cn; */
};
typedef union bdk_fpa_aurax_cnt_levels bdk_fpa_aurax_cnt_levels_t;

static inline uint64_t BDK_FPA_AURAX_CNT_LEVELS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_AURAX_CNT_LEVELS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x828040008310ll + 0x10000ll * ((a) & 0x1ff);
    __bdk_csr_fatal("FPA_AURAX_CNT_LEVELS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_AURAX_CNT_LEVELS(a) bdk_fpa_aurax_cnt_levels_t
#define bustype_BDK_FPA_AURAX_CNT_LEVELS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_AURAX_CNT_LEVELS(a) "FPA_AURAX_CNT_LEVELS"
#define device_bar_BDK_FPA_AURAX_CNT_LEVELS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_AURAX_CNT_LEVELS(a) (a)
#define arguments_BDK_FPA_AURAX_CNT_LEVELS(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_aura#_pool
 *
 * FPA Aura to Pool Registers
 * Provides the mapping from each aura to the pool number.
 */
union bdk_fpa_aurax_pool
{
    uint64_t u;
    struct bdk_fpa_aurax_pool_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t pool                  : 6;  /**< [  5:  0](R/W) Indicates which hardware pool corresponds to each aura. Must not be larger than the
                                                                 number of pools; see FPA_GEN_CFG[POOLS]. */
#else /* Word 0 - Little Endian */
        uint64_t pool                  : 6;  /**< [  5:  0](R/W) Indicates which hardware pool corresponds to each aura. Must not be larger than the
                                                                 number of pools; see FPA_GEN_CFG[POOLS]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_aurax_pool_s cn; */
};
typedef union bdk_fpa_aurax_pool bdk_fpa_aurax_pool_t;

static inline uint64_t BDK_FPA_AURAX_POOL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_AURAX_POOL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x828040008100ll + 0x10000ll * ((a) & 0x1ff);
    __bdk_csr_fatal("FPA_AURAX_POOL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_AURAX_POOL(a) bdk_fpa_aurax_pool_t
#define bustype_BDK_FPA_AURAX_POOL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_AURAX_POOL(a) "FPA_AURAX_POOL"
#define device_bar_BDK_FPA_AURAX_POOL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_AURAX_POOL(a) (a)
#define arguments_BDK_FPA_AURAX_POOL(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_aura#_pool_levels
 *
 * FPA Aura FPA Level Registers
 */
union bdk_fpa_aurax_pool_levels
{
    uint64_t u;
    struct bdk_fpa_aurax_pool_levels_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_41_63        : 23;
        uint64_t drop_dis              : 1;  /**< [ 40: 40](R/W) Disables aura-unique pool DROP based on the [DROP] level. */
        uint64_t bp_ena                : 1;  /**< [ 39: 39](R/W) Enable aura-unique pool backpressure based on [BP] level. If set FPA_GEN_CFG[LVL_DLY] must
                                                                 be nonzero. */
        uint64_t red_ena               : 1;  /**< [ 38: 38](R/W) Enable aura-unique pool RED based on [DROP] and [PASS] levels. If set FPA_GEN_CFG[LVL_DLY]
                                                                 must be nonzero.
                                                                 If set, aura-unique pool RED is performed on core requests with
                                                                 FPA_ALLOC_ADDR_S[RED] set, and also may be performed on the first PKI
                                                                 allocation request for a packet (depending on PKI style and aura configuration). */
        uint64_t shift                 : 6;  /**< [ 37: 32](R/W) Right shift to FPA_VHPOOL()_AVAILABLE[COUNT] used to create a narrower depth for
                                                                 aura-unique pool QOS and backpressure calculations. PKI saturates the shifted
                                                                 FPA_VHPOOL()_AVAILABLE[COUNT] to 8-bits for the aura, and compares this 8-bit
                                                                 shifted and saturated depth directly to [DROP/BP]. PKI also creates [LEVEL],
                                                                 which is a moving average of the 8-bit shifted and saturated depth for the aura,
                                                                 for comparison to [DROP/PASS] in aura-unique pool RED calculations.

                                                                 Though [SHIFT] may differ amongst the auras sharing a given pool, they may most
                                                                 commonly be the same (i.e. the 8-bit shifted and saturated depth and [LEVEL] may
                                                                 typically be the same for all auras sharing a pool), with the [DROP/PASS/BP]
                                                                 configuration providing aura-uniqueness in aura-unique pool RED/DROP/BP
                                                                 processing. */
        uint64_t bp                    : 8;  /**< [ 31: 24](R/W) Backpressure can assert if the current 8-bit shifted and saturated
                                                                 FPA_VHPOOL()_AVAILABLE[COUNT] for the aura is equal to or less than this value. */
        uint64_t drop                  : 8;  /**< [ 23: 16](R/W) If [RED_ENA]=1 and RED processing is requested, the packet will be dropped if
                                                                 [LEVEL] is equal to or less than this value.

                                                                 If [DROP_DIS]=0 and DROP processing is requested, the packet will be dropped
                                                                 if the current 8-bit shifted and saturated FPA_VHPOOL()_AVAILABLE[COUNT] for the
                                                                 aura is equal to or less than this value. */
        uint64_t pass                  : 8;  /**< [ 15:  8](R/W) Aura-unique pool RED processing will not drop an allocation request if [LEVEL] is larger
                                                                 than this value. */
        uint64_t level                 : 8;  /**< [  7:  0](RO/H) Current moving average of the 8-bit shifted and saturated FPA_VHPOOL()_AVAILABLE[COUNT]
                                                                 for
                                                                 the aura.
                                                                 The higher [LEVEL] is, the more free resources. The lowest [LEVEL]'s indicate buffer
                                                                 exhaustion.
                                                                 See [SHIFT]. */
#else /* Word 0 - Little Endian */
        uint64_t level                 : 8;  /**< [  7:  0](RO/H) Current moving average of the 8-bit shifted and saturated FPA_VHPOOL()_AVAILABLE[COUNT]
                                                                 for
                                                                 the aura.
                                                                 The higher [LEVEL] is, the more free resources. The lowest [LEVEL]'s indicate buffer
                                                                 exhaustion.
                                                                 See [SHIFT]. */
        uint64_t pass                  : 8;  /**< [ 15:  8](R/W) Aura-unique pool RED processing will not drop an allocation request if [LEVEL] is larger
                                                                 than this value. */
        uint64_t drop                  : 8;  /**< [ 23: 16](R/W) If [RED_ENA]=1 and RED processing is requested, the packet will be dropped if
                                                                 [LEVEL] is equal to or less than this value.

                                                                 If [DROP_DIS]=0 and DROP processing is requested, the packet will be dropped
                                                                 if the current 8-bit shifted and saturated FPA_VHPOOL()_AVAILABLE[COUNT] for the
                                                                 aura is equal to or less than this value. */
        uint64_t bp                    : 8;  /**< [ 31: 24](R/W) Backpressure can assert if the current 8-bit shifted and saturated
                                                                 FPA_VHPOOL()_AVAILABLE[COUNT] for the aura is equal to or less than this value. */
        uint64_t shift                 : 6;  /**< [ 37: 32](R/W) Right shift to FPA_VHPOOL()_AVAILABLE[COUNT] used to create a narrower depth for
                                                                 aura-unique pool QOS and backpressure calculations. PKI saturates the shifted
                                                                 FPA_VHPOOL()_AVAILABLE[COUNT] to 8-bits for the aura, and compares this 8-bit
                                                                 shifted and saturated depth directly to [DROP/BP]. PKI also creates [LEVEL],
                                                                 which is a moving average of the 8-bit shifted and saturated depth for the aura,
                                                                 for comparison to [DROP/PASS] in aura-unique pool RED calculations.

                                                                 Though [SHIFT] may differ amongst the auras sharing a given pool, they may most
                                                                 commonly be the same (i.e. the 8-bit shifted and saturated depth and [LEVEL] may
                                                                 typically be the same for all auras sharing a pool), with the [DROP/PASS/BP]
                                                                 configuration providing aura-uniqueness in aura-unique pool RED/DROP/BP
                                                                 processing. */
        uint64_t red_ena               : 1;  /**< [ 38: 38](R/W) Enable aura-unique pool RED based on [DROP] and [PASS] levels. If set FPA_GEN_CFG[LVL_DLY]
                                                                 must be nonzero.
                                                                 If set, aura-unique pool RED is performed on core requests with
                                                                 FPA_ALLOC_ADDR_S[RED] set, and also may be performed on the first PKI
                                                                 allocation request for a packet (depending on PKI style and aura configuration). */
        uint64_t bp_ena                : 1;  /**< [ 39: 39](R/W) Enable aura-unique pool backpressure based on [BP] level. If set FPA_GEN_CFG[LVL_DLY] must
                                                                 be nonzero. */
        uint64_t drop_dis              : 1;  /**< [ 40: 40](R/W) Disables aura-unique pool DROP based on the [DROP] level. */
        uint64_t reserved_41_63        : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_aurax_pool_levels_s cn; */
};
typedef union bdk_fpa_aurax_pool_levels bdk_fpa_aurax_pool_levels_t;

static inline uint64_t BDK_FPA_AURAX_POOL_LEVELS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_AURAX_POOL_LEVELS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x828040008300ll + 0x10000ll * ((a) & 0x1ff);
    __bdk_csr_fatal("FPA_AURAX_POOL_LEVELS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_AURAX_POOL_LEVELS(a) bdk_fpa_aurax_pool_levels_t
#define bustype_BDK_FPA_AURAX_POOL_LEVELS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_AURAX_POOL_LEVELS(a) "FPA_AURAX_POOL_LEVELS"
#define device_bar_BDK_FPA_AURAX_POOL_LEVELS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_AURAX_POOL_LEVELS(a) (a)
#define arguments_BDK_FPA_AURAX_POOL_LEVELS(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_bist_status
 *
 * FPA BIST Status Register
 * This register provides the result of the BIST run on the FPA memories.
 */
union bdk_fpa_bist_status
{
    uint64_t u;
    struct bdk_fpa_bist_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_42_63        : 22;
        uint64_t status                : 42; /**< [ 41:  0](RO/H) Memory BIST status. */
#else /* Word 0 - Little Endian */
        uint64_t status                : 42; /**< [ 41:  0](RO/H) Memory BIST status. */
        uint64_t reserved_42_63        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_bist_status_s cn; */
};
typedef union bdk_fpa_bist_status bdk_fpa_bist_status_t;

#define BDK_FPA_BIST_STATUS BDK_FPA_BIST_STATUS_FUNC()
static inline uint64_t BDK_FPA_BIST_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_BIST_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8280000000e8ll;
    __bdk_csr_fatal("FPA_BIST_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_BIST_STATUS bdk_fpa_bist_status_t
#define bustype_BDK_FPA_BIST_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_BIST_STATUS "FPA_BIST_STATUS"
#define device_bar_BDK_FPA_BIST_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_BIST_STATUS 0
#define arguments_BDK_FPA_BIST_STATUS -1,-1,-1,-1

/**
 * Register (NCB) fpa_bp_test
 *
 * INTERNAL: FPA Backpressure Test Register
 */
union bdk_fpa_bp_test
{
    uint64_t u;
    struct bdk_fpa_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 16; /**< [ 63: 48](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Apply backpressure to adp      to csr traffic.      Backpressure weight controlled
                                                                 by [BP_CFG12].
                                                                 \<59\> = Apply backpressure to adp      to l2s traffic.      Backpressure weight controlled
                                                                 by [BP_CFG11].
                                                                 \<58\> = Apply backpressure to adp      to l2l traffic.      Backpressure weight controlled
                                                                 by [BP_CFG10].
                                                                 \<57\> = Apply backpressure to red read to csr traffic.      Backpressure weight controlled
                                                                 by [BP_CFG9].
                                                                 \<56\> = Apply backpressure to l2arb    to csr traffic.      Backpressure weight controlled
                                                                 by [BP_CFG8].
                                                                 \<55\> = Apply backpressure to csr      to adp traffic.      Backpressure weight controlled
                                                                 by [BP_CFG7].
                                                                 \<54\> = Apply backpressure to pcc      to gib traffic.      Backpressure weight controlled
                                                                 by [BP_CFG6].
                                                                 \<53\> = Apply backpressure to adp      to pfc traffic.      Backpressure weight controlled
                                                                 by [BP_CFG5].
                                                                 \<52\> = generate pmc                   to pfc backpressure. Backpressure weight controlled
                                                                 by [BP_CFG4].
                                                                 \<51\> = Apply backpressure to pmc      to ncbi traffic.     Backpressure weight controlled
                                                                 by [BP_CFG3].
                                                                 \<50\> = Apply backpressure to csr      to ncbi traffic.     Backpressure weight controlled
                                                                 by [BP_CFG2].
                                                                 \<49\> = Apply backpressure to l2s      to ncbi traffic.     Backpressure weight controlled
                                                                 by [BP_CFG1].
                                                                 \<48\> = Apply backpressure to l2l      to ncbi traffic.     Backpressure weight controlled
                                                                 by [BP_CFG0]. */
        uint64_t bp_cfg                : 32; /**< [ 47: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<47:46\> = BP_CFG15.
                                                                   \<45:44\> = BP_CFG14.
                                                                   \<43:42\> = BP_CFG13.
                                                                   \<41:40\> = BP_CFG12.
                                                                   \<39:38\> = BP_CFG11.
                                                                   \<37:36\> = BP_CFG10.
                                                                   \<35:34\> = BP_CFG9.
                                                                   \<33:32\> = BP_CFG8.
                                                                   \<31:30\> = BP_CFG7.
                                                                   \<29:28\> = BP_CFG6.
                                                                   \<27:26\> = BP_CFG5.
                                                                   \<25:24\> = BP_CFG4.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 32; /**< [ 47: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<47:46\> = BP_CFG15.
                                                                   \<45:44\> = BP_CFG14.
                                                                   \<43:42\> = BP_CFG13.
                                                                   \<41:40\> = BP_CFG12.
                                                                   \<39:38\> = BP_CFG11.
                                                                   \<37:36\> = BP_CFG10.
                                                                   \<35:34\> = BP_CFG9.
                                                                   \<33:32\> = BP_CFG8.
                                                                   \<31:30\> = BP_CFG7.
                                                                   \<29:28\> = BP_CFG6.
                                                                   \<27:26\> = BP_CFG5.
                                                                   \<25:24\> = BP_CFG4.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t enable                : 16; /**< [ 63: 48](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Apply backpressure to adp      to csr traffic.      Backpressure weight controlled
                                                                 by [BP_CFG12].
                                                                 \<59\> = Apply backpressure to adp      to l2s traffic.      Backpressure weight controlled
                                                                 by [BP_CFG11].
                                                                 \<58\> = Apply backpressure to adp      to l2l traffic.      Backpressure weight controlled
                                                                 by [BP_CFG10].
                                                                 \<57\> = Apply backpressure to red read to csr traffic.      Backpressure weight controlled
                                                                 by [BP_CFG9].
                                                                 \<56\> = Apply backpressure to l2arb    to csr traffic.      Backpressure weight controlled
                                                                 by [BP_CFG8].
                                                                 \<55\> = Apply backpressure to csr      to adp traffic.      Backpressure weight controlled
                                                                 by [BP_CFG7].
                                                                 \<54\> = Apply backpressure to pcc      to gib traffic.      Backpressure weight controlled
                                                                 by [BP_CFG6].
                                                                 \<53\> = Apply backpressure to adp      to pfc traffic.      Backpressure weight controlled
                                                                 by [BP_CFG5].
                                                                 \<52\> = generate pmc                   to pfc backpressure. Backpressure weight controlled
                                                                 by [BP_CFG4].
                                                                 \<51\> = Apply backpressure to pmc      to ncbi traffic.     Backpressure weight controlled
                                                                 by [BP_CFG3].
                                                                 \<50\> = Apply backpressure to csr      to ncbi traffic.     Backpressure weight controlled
                                                                 by [BP_CFG2].
                                                                 \<49\> = Apply backpressure to l2s      to ncbi traffic.     Backpressure weight controlled
                                                                 by [BP_CFG1].
                                                                 \<48\> = Apply backpressure to l2l      to ncbi traffic.     Backpressure weight controlled
                                                                 by [BP_CFG0]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_bp_test_s cn; */
};
typedef union bdk_fpa_bp_test bdk_fpa_bp_test_t;

#define BDK_FPA_BP_TEST BDK_FPA_BP_TEST_FUNC()
static inline uint64_t BDK_FPA_BP_TEST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_BP_TEST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000200ll;
    __bdk_csr_fatal("FPA_BP_TEST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_BP_TEST bdk_fpa_bp_test_t
#define bustype_BDK_FPA_BP_TEST BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_BP_TEST "FPA_BP_TEST"
#define device_bar_BDK_FPA_BP_TEST 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_BP_TEST 0
#define arguments_BDK_FPA_BP_TEST -1,-1,-1,-1

/**
 * Register (NCB) fpa_clk_count
 *
 * FPA Clock Count Register
 * This register counts the number of coprocessor-clock cycles since the deassertion of reset.
 */
union bdk_fpa_clk_count
{
    uint64_t u;
    struct bdk_fpa_clk_count_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t clk_cnt               : 64; /**< [ 63:  0](RO/H) Clock count. This counter is cleared to 0x0 when reset is applied and increments on every
                                                                 rising edge of the coprocessor clock. */
#else /* Word 0 - Little Endian */
        uint64_t clk_cnt               : 64; /**< [ 63:  0](RO/H) Clock count. This counter is cleared to 0x0 when reset is applied and increments on every
                                                                 rising edge of the coprocessor clock. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_clk_count_s cn; */
};
typedef union bdk_fpa_clk_count bdk_fpa_clk_count_t;

#define BDK_FPA_CLK_COUNT BDK_FPA_CLK_COUNT_FUNC()
static inline uint64_t BDK_FPA_CLK_COUNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_CLK_COUNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8280000000f0ll;
    __bdk_csr_fatal("FPA_CLK_COUNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_CLK_COUNT bdk_fpa_clk_count_t
#define bustype_BDK_FPA_CLK_COUNT BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_CLK_COUNT "FPA_CLK_COUNT"
#define device_bar_BDK_FPA_CLK_COUNT 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_CLK_COUNT 0
#define arguments_BDK_FPA_CLK_COUNT -1,-1,-1,-1

/**
 * Register (NCB) fpa_const
 *
 * FPA Constants Register
 * This register contains constants for software discovery.
 */
union bdk_fpa_const
{
    uint64_t u;
    struct bdk_fpa_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t stk_ln_ptrs           : 8;  /**< [ 55: 48](RO) Number of pointers stored within each 128-byte line of the FPA stack. */
        uint64_t fpfs                  : 16; /**< [ 47: 32](RO) Number of FPF entries across all pools. See also FPA_GEN_CFG[POOLS]. */
        uint64_t auras                 : 16; /**< [ 31: 16](RO) Maximum number of auras supported. */
        uint64_t pools                 : 16; /**< [ 15:  0](RO) Maximum number of pools supported. See also FPA_GEN_CFG[POOLS]. */
#else /* Word 0 - Little Endian */
        uint64_t pools                 : 16; /**< [ 15:  0](RO) Maximum number of pools supported. See also FPA_GEN_CFG[POOLS]. */
        uint64_t auras                 : 16; /**< [ 31: 16](RO) Maximum number of auras supported. */
        uint64_t fpfs                  : 16; /**< [ 47: 32](RO) Number of FPF entries across all pools. See also FPA_GEN_CFG[POOLS]. */
        uint64_t stk_ln_ptrs           : 8;  /**< [ 55: 48](RO) Number of pointers stored within each 128-byte line of the FPA stack. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_const_s cn; */
};
typedef union bdk_fpa_const bdk_fpa_const_t;

#define BDK_FPA_CONST BDK_FPA_CONST_FUNC()
static inline uint64_t BDK_FPA_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_CONST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000010ll;
    __bdk_csr_fatal("FPA_CONST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_CONST bdk_fpa_const_t
#define bustype_BDK_FPA_CONST BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_CONST "FPA_CONST"
#define device_bar_BDK_FPA_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_CONST 0
#define arguments_BDK_FPA_CONST -1,-1,-1,-1

/**
 * Register (NCB) fpa_const1
 *
 * FPA Constants Register 1
 * This register contains constants for software discovery.
 */
union bdk_fpa_const1
{
    uint64_t u;
    struct bdk_fpa_const1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t maps                  : 12; /**< [ 11:  0](RO) Number of entries in FPA_PF_MAP(). */
#else /* Word 0 - Little Endian */
        uint64_t maps                  : 12; /**< [ 11:  0](RO) Number of entries in FPA_PF_MAP(). */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_const1_s cn; */
};
typedef union bdk_fpa_const1 bdk_fpa_const1_t;

#define BDK_FPA_CONST1 BDK_FPA_CONST1_FUNC()
static inline uint64_t BDK_FPA_CONST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_CONST1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000018ll;
    __bdk_csr_fatal("FPA_CONST1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_CONST1 bdk_fpa_const1_t
#define bustype_BDK_FPA_CONST1 BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_CONST1 "FPA_CONST1"
#define device_bar_BDK_FPA_CONST1 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_CONST1 0
#define arguments_BDK_FPA_CONST1 -1,-1,-1,-1

/**
 * Register (NCB) fpa_dbg_info
 *
 * FPA Debug Information Register
 * Internal:
 * This register provides debug information.
 */
union bdk_fpa_dbg_info
{
    uint64_t u;
    struct bdk_fpa_dbg_info_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t low_pool_deadlock     : 1;  /**< [ 16: 16](RO/H) For diagnostic use only.
                                                                 Internal:
                                                                 When the ADP pipeline is stalled indefinitely, this bit indicates the scenario in bug 28280. */
        uint64_t reserved_14_15        : 2;
        uint64_t ncbo_cmd_fault_cmd    : 5;  /**< [ 13:  9](RO/H) For diagnostic use only.
                                                                 Internal:
                                                                 When an unsupported ncbo command is detected, a fault bit along with the cmd is latched.

                                                                 \<13:9\> = NCBO unsupport command. */
        uint64_t ncbo_cmd_fault        : 1;  /**< [  8:  8](R/W1C/H) For diagnostic use only.
                                                                 Internal:
                                                                 When an unsupported ncbo command is detected, a fault bit along with the cmd is latched.

                                                                 \<8\> = NCBO cmd fault (unsupport command detected). */
        uint64_t reserved_6_7          : 2;
        uint64_t dwb_pending           : 6;  /**< [  5:  0](RO/H) Number of outstanding DWB requests in the DWB queue. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dwb_pending           : 6;  /**< [  5:  0](RO/H) Number of outstanding DWB requests in the DWB queue. For diagnostic use only. */
        uint64_t reserved_6_7          : 2;
        uint64_t ncbo_cmd_fault        : 1;  /**< [  8:  8](R/W1C/H) For diagnostic use only.
                                                                 Internal:
                                                                 When an unsupported ncbo command is detected, a fault bit along with the cmd is latched.

                                                                 \<8\> = NCBO cmd fault (unsupport command detected). */
        uint64_t ncbo_cmd_fault_cmd    : 5;  /**< [ 13:  9](RO/H) For diagnostic use only.
                                                                 Internal:
                                                                 When an unsupported ncbo command is detected, a fault bit along with the cmd is latched.

                                                                 \<13:9\> = NCBO unsupport command. */
        uint64_t reserved_14_15        : 2;
        uint64_t low_pool_deadlock     : 1;  /**< [ 16: 16](RO/H) For diagnostic use only.
                                                                 Internal:
                                                                 When the ADP pipeline is stalled indefinitely, this bit indicates the scenario in bug 28280. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_dbg_info_s cn; */
};
typedef union bdk_fpa_dbg_info bdk_fpa_dbg_info_t;

#define BDK_FPA_DBG_INFO BDK_FPA_DBG_INFO_FUNC()
static inline uint64_t BDK_FPA_DBG_INFO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_DBG_INFO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000468ll;
    __bdk_csr_fatal("FPA_DBG_INFO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_DBG_INFO bdk_fpa_dbg_info_t
#define bustype_BDK_FPA_DBG_INFO BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_DBG_INFO "FPA_DBG_INFO"
#define device_bar_BDK_FPA_DBG_INFO 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_DBG_INFO 0
#define arguments_BDK_FPA_DBG_INFO -1,-1,-1,-1

/**
 * Register (NCB) fpa_ecc_ctl
 *
 * FPA ECC Control Register
 * This register allows inserting ECC errors for testing.
 */
union bdk_fpa_ecc_ctl
{
    uint64_t u;
    struct bdk_fpa_ecc_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t ram_flip1             : 21; /**< [ 62: 42](R/W) Flip syndrome bits on write. Flip syndrome bits \<1\> on writes to the corresponding ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t ram_flip0             : 21; /**< [ 41: 21](R/W) Flip syndrome bits on write. Flip syndrome bits \<0\> on writes to the corresponding ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t ram_cdis              : 21; /**< [ 20:  0](R/W) RAM ECC correction disable. Each bit corresponds to a different RAM. */
#else /* Word 0 - Little Endian */
        uint64_t ram_cdis              : 21; /**< [ 20:  0](R/W) RAM ECC correction disable. Each bit corresponds to a different RAM. */
        uint64_t ram_flip0             : 21; /**< [ 41: 21](R/W) Flip syndrome bits on write. Flip syndrome bits \<0\> on writes to the corresponding ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t ram_flip1             : 21; /**< [ 62: 42](R/W) Flip syndrome bits on write. Flip syndrome bits \<1\> on writes to the corresponding ram to
                                                                 test single-bit or double-bit error handling. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_ecc_ctl_s cn; */
};
typedef union bdk_fpa_ecc_ctl bdk_fpa_ecc_ctl_t;

#define BDK_FPA_ECC_CTL BDK_FPA_ECC_CTL_FUNC()
static inline uint64_t BDK_FPA_ECC_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_ECC_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000058ll;
    __bdk_csr_fatal("FPA_ECC_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_ECC_CTL bdk_fpa_ecc_ctl_t
#define bustype_BDK_FPA_ECC_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_ECC_CTL "FPA_ECC_CTL"
#define device_bar_BDK_FPA_ECC_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_ECC_CTL 0
#define arguments_BDK_FPA_ECC_CTL -1,-1,-1,-1

/**
 * Register (NCB) fpa_ecc_int
 *
 * FPA ECC Interrupt Register
 * This register contains ECC error interrupt summary bits.
 */
union bdk_fpa_ecc_int
{
    uint64_t u;
    struct bdk_fpa_ecc_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Set when a double-bit error is detected in the corresponding RAM. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Set when a single-bit error is detected in the corresponding RAM. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Set when a single-bit error is detected in the corresponding RAM. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Set when a double-bit error is detected in the corresponding RAM. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_ecc_int_s cn; */
};
typedef union bdk_fpa_ecc_int bdk_fpa_ecc_int_t;

#define BDK_FPA_ECC_INT BDK_FPA_ECC_INT_FUNC()
static inline uint64_t BDK_FPA_ECC_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_ECC_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000068ll;
    __bdk_csr_fatal("FPA_ECC_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_ECC_INT bdk_fpa_ecc_int_t
#define bustype_BDK_FPA_ECC_INT BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_ECC_INT "FPA_ECC_INT"
#define device_bar_BDK_FPA_ECC_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_ECC_INT 0
#define arguments_BDK_FPA_ECC_INT -1,-1,-1,-1

/**
 * Register (NCB) fpa_ecc_int_ena_w1c
 *
 * FPA ECC Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_fpa_ecc_int_ena_w1c
{
    uint64_t u;
    struct bdk_fpa_ecc_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Reads or clears enable for FPA_ECC_INT[RAM_DBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Reads or clears enable for FPA_ECC_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Reads or clears enable for FPA_ECC_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Reads or clears enable for FPA_ECC_INT[RAM_DBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_ecc_int_ena_w1c_s cn; */
};
typedef union bdk_fpa_ecc_int_ena_w1c bdk_fpa_ecc_int_ena_w1c_t;

#define BDK_FPA_ECC_INT_ENA_W1C BDK_FPA_ECC_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_FPA_ECC_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_ECC_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000080ll;
    __bdk_csr_fatal("FPA_ECC_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_ECC_INT_ENA_W1C bdk_fpa_ecc_int_ena_w1c_t
#define bustype_BDK_FPA_ECC_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_ECC_INT_ENA_W1C "FPA_ECC_INT_ENA_W1C"
#define device_bar_BDK_FPA_ECC_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_ECC_INT_ENA_W1C 0
#define arguments_BDK_FPA_ECC_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) fpa_ecc_int_ena_w1s
 *
 * FPA ECC Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_fpa_ecc_int_ena_w1s
{
    uint64_t u;
    struct bdk_fpa_ecc_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets enable for FPA_ECC_INT[RAM_DBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets enable for FPA_ECC_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets enable for FPA_ECC_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets enable for FPA_ECC_INT[RAM_DBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_ecc_int_ena_w1s_s cn; */
};
typedef union bdk_fpa_ecc_int_ena_w1s bdk_fpa_ecc_int_ena_w1s_t;

#define BDK_FPA_ECC_INT_ENA_W1S BDK_FPA_ECC_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_FPA_ECC_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_ECC_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000078ll;
    __bdk_csr_fatal("FPA_ECC_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_ECC_INT_ENA_W1S bdk_fpa_ecc_int_ena_w1s_t
#define bustype_BDK_FPA_ECC_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_ECC_INT_ENA_W1S "FPA_ECC_INT_ENA_W1S"
#define device_bar_BDK_FPA_ECC_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_ECC_INT_ENA_W1S 0
#define arguments_BDK_FPA_ECC_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) fpa_ecc_int_w1s
 *
 * FPA ECC Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_fpa_ecc_int_w1s
{
    uint64_t u;
    struct bdk_fpa_ecc_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets FPA_ECC_INT[RAM_DBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets FPA_ECC_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets FPA_ECC_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets FPA_ECC_INT[RAM_DBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_ecc_int_w1s_s cn; */
};
typedef union bdk_fpa_ecc_int_w1s bdk_fpa_ecc_int_w1s_t;

#define BDK_FPA_ECC_INT_W1S BDK_FPA_ECC_INT_W1S_FUNC()
static inline uint64_t BDK_FPA_ECC_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_ECC_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000070ll;
    __bdk_csr_fatal("FPA_ECC_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_ECC_INT_W1S bdk_fpa_ecc_int_w1s_t
#define bustype_BDK_FPA_ECC_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_ECC_INT_W1S "FPA_ECC_INT_W1S"
#define device_bar_BDK_FPA_ECC_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_ECC_INT_W1S 0
#define arguments_BDK_FPA_ECC_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) fpa_gen_cfg
 *
 * FPA Configuration Register
 * This register provides FPA control and status information.
 */
union bdk_fpa_gen_cfg
{
    uint64_t u;
    struct bdk_fpa_gen_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_18_63        : 46;
        uint64_t dwbq                  : 6;  /**< [ 17: 12](R/W) Don't write back queue size. Number of transactions requesting DWB that may be
                                                                 held waiting for DWB. Once the stack is full, additional DWB requests will be
                                                                 ignored. 0x0 disables DWBs. 0x3F sets to maximum size. */
        uint64_t halfrate              : 1;  /**< [ 11: 11](R/W) Half rate. Limit peak alloc/free rate to half of peak to insure all alloc/frees are
                                                                 visible to OCLA. */
        uint64_t ocla_bp               : 1;  /**< [ 10: 10](R/W) OCLA backpressure enable. When OCLA FIFOs are near full, allow OCLA to backpressure
                                                                 alloc/frees. See also [HALFRATE]. */
        uint64_t lvl_dly               : 6;  /**< [  9:  4](R/W) Levelizer delay. Number of cycles between level computations for backpressure and RED.
                                                                 Increasing values decrease power and leave additional bandwidth for allocate/deallocates.
                                                                 Zero disables, one indicates a level computation every other cycle, etc. Once set to
                                                                 nonzero must not be later set to zero without resetting FPA. */
        uint64_t pools                 : 2;  /**< [  3:  2](R/W) Number of pools. Each halving of the number of pools doubles the buffering available to
                                                                 the remaining pools, leading to some improvement in memory bandwidth. Value must not be
                                                                 changed if FPA_POOL()_CFG[ENA] is set for any pool.
                                                                 0x0 = Reserved.
                                                                 0x1 = 32 pools, 216 FPF entries per pool.
                                                                 0x2 = 16 pools, 432 FPF entries per pool.
                                                                 0x3 = Reserved.

                                                                 See also FPA_CONST[POOLS] (= 32) and FPA_CONST[FPFS] (= 32*216). */
        uint64_t avg_en                : 1;  /**< [  1:  1](R/W) QoS averaging enable. When set, RED calculations use average buffer levels. When clear,
                                                                 RED calculations use the current values. */
        uint64_t clk_override          : 1;  /**< [  0:  0](R/W) Conditional clock override. */
#else /* Word 0 - Little Endian */
        uint64_t clk_override          : 1;  /**< [  0:  0](R/W) Conditional clock override. */
        uint64_t avg_en                : 1;  /**< [  1:  1](R/W) QoS averaging enable. When set, RED calculations use average buffer levels. When clear,
                                                                 RED calculations use the current values. */
        uint64_t pools                 : 2;  /**< [  3:  2](R/W) Number of pools. Each halving of the number of pools doubles the buffering available to
                                                                 the remaining pools, leading to some improvement in memory bandwidth. Value must not be
                                                                 changed if FPA_POOL()_CFG[ENA] is set for any pool.
                                                                 0x0 = Reserved.
                                                                 0x1 = 32 pools, 216 FPF entries per pool.
                                                                 0x2 = 16 pools, 432 FPF entries per pool.
                                                                 0x3 = Reserved.

                                                                 See also FPA_CONST[POOLS] (= 32) and FPA_CONST[FPFS] (= 32*216). */
        uint64_t lvl_dly               : 6;  /**< [  9:  4](R/W) Levelizer delay. Number of cycles between level computations for backpressure and RED.
                                                                 Increasing values decrease power and leave additional bandwidth for allocate/deallocates.
                                                                 Zero disables, one indicates a level computation every other cycle, etc. Once set to
                                                                 nonzero must not be later set to zero without resetting FPA. */
        uint64_t ocla_bp               : 1;  /**< [ 10: 10](R/W) OCLA backpressure enable. When OCLA FIFOs are near full, allow OCLA to backpressure
                                                                 alloc/frees. See also [HALFRATE]. */
        uint64_t halfrate              : 1;  /**< [ 11: 11](R/W) Half rate. Limit peak alloc/free rate to half of peak to insure all alloc/frees are
                                                                 visible to OCLA. */
        uint64_t dwbq                  : 6;  /**< [ 17: 12](R/W) Don't write back queue size. Number of transactions requesting DWB that may be
                                                                 held waiting for DWB. Once the stack is full, additional DWB requests will be
                                                                 ignored. 0x0 disables DWBs. 0x3F sets to maximum size. */
        uint64_t reserved_18_63        : 46;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_gen_cfg_s cn; */
};
typedef union bdk_fpa_gen_cfg bdk_fpa_gen_cfg_t;

#define BDK_FPA_GEN_CFG BDK_FPA_GEN_CFG_FUNC()
static inline uint64_t BDK_FPA_GEN_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_GEN_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000050ll;
    __bdk_csr_fatal("FPA_GEN_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_GEN_CFG bdk_fpa_gen_cfg_t
#define bustype_BDK_FPA_GEN_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_GEN_CFG "FPA_GEN_CFG"
#define device_bar_BDK_FPA_GEN_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_GEN_CFG 0
#define arguments_BDK_FPA_GEN_CFG -1,-1,-1,-1

/**
 * Register (NCB) fpa_gen_int
 *
 * FPA General Interrupt Register
 * This register contains GEN error interrupt summary bits.
 */
union bdk_fpa_gen_int
{
    uint64_t u;
    struct bdk_fpa_gen_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t alloc_dis             : 1;  /**< [  4:  4](R/W1C/H) An allocation request was dropped due to the settings of FPA_INP_CTL[ALLOC_DIS]. */
        uint64_t free_dis              : 1;  /**< [  3:  3](R/W1C/H) A free request was dropped due to the settings of FPA_INP_CTL[FREE_DIS]. */
        uint64_t gmid_multi            : 1;  /**< [  2:  2](R/W1C/H) Coprocessor allocate/return dropped due to that coprocessor requesting with
                                                                 GMID/GAURA have multiple hits in FPA_PF_MAP(). When a request thus dropped, even
                                                                 if this bit is already set, FPA_UNMAP_INFO is loaded. */
        uint64_t gmid_unmap            : 1;  /**< [  1:  1](R/W1C/H) Coprocessor allocate/return dropped due to that coprocessor requesting with GMID
                                                                 not mapped in FPA_PF_MAP(). When a request thus dropped, even if this bit is
                                                                 already set, FPA_UNMAP_INFO is loaded. */
        uint64_t gmid0                 : 1;  /**< [  0:  0](R/W1C/H) Coprocessor allocate/return dropped due to that coprocessor requesting with
                                                                 GMID=0x0. See PKI_QPG_TBLB()[GMID], TIM_RING()_GMCTL[GMID], SSO_XAQ_GMCTL[GMID],
                                                                 and other GMID registers. */
#else /* Word 0 - Little Endian */
        uint64_t gmid0                 : 1;  /**< [  0:  0](R/W1C/H) Coprocessor allocate/return dropped due to that coprocessor requesting with
                                                                 GMID=0x0. See PKI_QPG_TBLB()[GMID], TIM_RING()_GMCTL[GMID], SSO_XAQ_GMCTL[GMID],
                                                                 and other GMID registers. */
        uint64_t gmid_unmap            : 1;  /**< [  1:  1](R/W1C/H) Coprocessor allocate/return dropped due to that coprocessor requesting with GMID
                                                                 not mapped in FPA_PF_MAP(). When a request thus dropped, even if this bit is
                                                                 already set, FPA_UNMAP_INFO is loaded. */
        uint64_t gmid_multi            : 1;  /**< [  2:  2](R/W1C/H) Coprocessor allocate/return dropped due to that coprocessor requesting with
                                                                 GMID/GAURA have multiple hits in FPA_PF_MAP(). When a request thus dropped, even
                                                                 if this bit is already set, FPA_UNMAP_INFO is loaded. */
        uint64_t free_dis              : 1;  /**< [  3:  3](R/W1C/H) A free request was dropped due to the settings of FPA_INP_CTL[FREE_DIS]. */
        uint64_t alloc_dis             : 1;  /**< [  4:  4](R/W1C/H) An allocation request was dropped due to the settings of FPA_INP_CTL[ALLOC_DIS]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_gen_int_s cn; */
};
typedef union bdk_fpa_gen_int bdk_fpa_gen_int_t;

#define BDK_FPA_GEN_INT BDK_FPA_GEN_INT_FUNC()
static inline uint64_t BDK_FPA_GEN_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_GEN_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000140ll;
    __bdk_csr_fatal("FPA_GEN_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_GEN_INT bdk_fpa_gen_int_t
#define bustype_BDK_FPA_GEN_INT BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_GEN_INT "FPA_GEN_INT"
#define device_bar_BDK_FPA_GEN_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_GEN_INT 0
#define arguments_BDK_FPA_GEN_INT -1,-1,-1,-1

/**
 * Register (NCB) fpa_gen_int_ena_w1c
 *
 * FPA General Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_fpa_gen_int_ena_w1c
{
    uint64_t u;
    struct bdk_fpa_gen_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t alloc_dis             : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for FPA_GEN_INT[ALLOC_DIS]. */
        uint64_t free_dis              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for FPA_GEN_INT[FREE_DIS]. */
        uint64_t gmid_multi            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for FPA_GEN_INT[GMID_MULTI]. */
        uint64_t gmid_unmap            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for FPA_GEN_INT[GMID_UNMAP]. */
        uint64_t gmid0                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for FPA_GEN_INT[GMID0]. */
#else /* Word 0 - Little Endian */
        uint64_t gmid0                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for FPA_GEN_INT[GMID0]. */
        uint64_t gmid_unmap            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for FPA_GEN_INT[GMID_UNMAP]. */
        uint64_t gmid_multi            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for FPA_GEN_INT[GMID_MULTI]. */
        uint64_t free_dis              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for FPA_GEN_INT[FREE_DIS]. */
        uint64_t alloc_dis             : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for FPA_GEN_INT[ALLOC_DIS]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_gen_int_ena_w1c_s cn; */
};
typedef union bdk_fpa_gen_int_ena_w1c bdk_fpa_gen_int_ena_w1c_t;

#define BDK_FPA_GEN_INT_ENA_W1C BDK_FPA_GEN_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_FPA_GEN_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_GEN_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000158ll;
    __bdk_csr_fatal("FPA_GEN_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_GEN_INT_ENA_W1C bdk_fpa_gen_int_ena_w1c_t
#define bustype_BDK_FPA_GEN_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_GEN_INT_ENA_W1C "FPA_GEN_INT_ENA_W1C"
#define device_bar_BDK_FPA_GEN_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_GEN_INT_ENA_W1C 0
#define arguments_BDK_FPA_GEN_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) fpa_gen_int_ena_w1s
 *
 * FPA General Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_fpa_gen_int_ena_w1s
{
    uint64_t u;
    struct bdk_fpa_gen_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t alloc_dis             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for FPA_GEN_INT[ALLOC_DIS]. */
        uint64_t free_dis              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for FPA_GEN_INT[FREE_DIS]. */
        uint64_t gmid_multi            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for FPA_GEN_INT[GMID_MULTI]. */
        uint64_t gmid_unmap            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for FPA_GEN_INT[GMID_UNMAP]. */
        uint64_t gmid0                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for FPA_GEN_INT[GMID0]. */
#else /* Word 0 - Little Endian */
        uint64_t gmid0                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for FPA_GEN_INT[GMID0]. */
        uint64_t gmid_unmap            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for FPA_GEN_INT[GMID_UNMAP]. */
        uint64_t gmid_multi            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for FPA_GEN_INT[GMID_MULTI]. */
        uint64_t free_dis              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for FPA_GEN_INT[FREE_DIS]. */
        uint64_t alloc_dis             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for FPA_GEN_INT[ALLOC_DIS]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_gen_int_ena_w1s_s cn; */
};
typedef union bdk_fpa_gen_int_ena_w1s bdk_fpa_gen_int_ena_w1s_t;

#define BDK_FPA_GEN_INT_ENA_W1S BDK_FPA_GEN_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_FPA_GEN_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_GEN_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000150ll;
    __bdk_csr_fatal("FPA_GEN_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_GEN_INT_ENA_W1S bdk_fpa_gen_int_ena_w1s_t
#define bustype_BDK_FPA_GEN_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_GEN_INT_ENA_W1S "FPA_GEN_INT_ENA_W1S"
#define device_bar_BDK_FPA_GEN_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_GEN_INT_ENA_W1S 0
#define arguments_BDK_FPA_GEN_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) fpa_gen_int_w1s
 *
 * FPA General Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_fpa_gen_int_w1s
{
    uint64_t u;
    struct bdk_fpa_gen_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t alloc_dis             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets FPA_GEN_INT[ALLOC_DIS]. */
        uint64_t free_dis              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets FPA_GEN_INT[FREE_DIS]. */
        uint64_t gmid_multi            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets FPA_GEN_INT[GMID_MULTI]. */
        uint64_t gmid_unmap            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets FPA_GEN_INT[GMID_UNMAP]. */
        uint64_t gmid0                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets FPA_GEN_INT[GMID0]. */
#else /* Word 0 - Little Endian */
        uint64_t gmid0                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets FPA_GEN_INT[GMID0]. */
        uint64_t gmid_unmap            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets FPA_GEN_INT[GMID_UNMAP]. */
        uint64_t gmid_multi            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets FPA_GEN_INT[GMID_MULTI]. */
        uint64_t free_dis              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets FPA_GEN_INT[FREE_DIS]. */
        uint64_t alloc_dis             : 1;  /**< [  4:  4](R/W1S/H) Reads or sets FPA_GEN_INT[ALLOC_DIS]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_gen_int_w1s_s cn; */
};
typedef union bdk_fpa_gen_int_w1s bdk_fpa_gen_int_w1s_t;

#define BDK_FPA_GEN_INT_W1S BDK_FPA_GEN_INT_W1S_FUNC()
static inline uint64_t BDK_FPA_GEN_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_GEN_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000148ll;
    __bdk_csr_fatal("FPA_GEN_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_GEN_INT_W1S bdk_fpa_gen_int_w1s_t
#define bustype_BDK_FPA_GEN_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_GEN_INT_W1S "FPA_GEN_INT_W1S"
#define device_bar_BDK_FPA_GEN_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_GEN_INT_W1S 0
#define arguments_BDK_FPA_GEN_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) fpa_inp_ctl
 *
 * FPA Input Control Register
 */
union bdk_fpa_inp_ctl
{
    uint64_t u;
    struct bdk_fpa_inp_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t alloc_dis             : 20; /**< [ 39: 20](R/W) Allocation input disable. Each bit corresponds to a hardware allocation input
                                                                 queue, and if set add-works from the corresponding coprocessor will be dropped
                                                                 with a no-pointer fault response and FPA_GEN_INT[ALLOC_DIS] set.
                                                                 \<0\> = SSO.
                                                                 \<1\> = PKO queue.
                                                                 \<2\> = PKI.
                                                                 \<19:3\> = Reserved.

                                                                 Internal:
                                                                 There are 3 requesters on XFR bus. */
        uint64_t free_dis              : 20; /**< [ 19:  0](R/W) Dellocation input disable. Each bit corresponds to a hardware deallocation input
                                                                 queue, and if set add-works from the corresponding coprocessor will be dropped
                                                                 and FPA_GEN_INT[FREE_DIS] set
                                                                 \<0\> = SSO.
                                                                 \<1\> = PKO DPFI.
                                                                 \<2\> = PKI.
                                                                 \<3\> = CPT1.
                                                                 \<4\> = ZIP.
                                                                 \<5\> = TIM.
                                                                 \<6\> = RAD.
                                                                 \<7\> = PKO PPFI.
                                                                 \<8\> = CPT0.
                                                                 \<9\> = DPI.
                                                                 \<10\> = DDF.
                                                                 \<11\> = BCH.
                                                                 \<19:12\> = Reserved.

                                                                 Internal:
                                                                 Once the grant is sent, the request is marked and it is dropped when the request
                                                                 data is received. */
#else /* Word 0 - Little Endian */
        uint64_t free_dis              : 20; /**< [ 19:  0](R/W) Dellocation input disable. Each bit corresponds to a hardware deallocation input
                                                                 queue, and if set add-works from the corresponding coprocessor will be dropped
                                                                 and FPA_GEN_INT[FREE_DIS] set
                                                                 \<0\> = SSO.
                                                                 \<1\> = PKO DPFI.
                                                                 \<2\> = PKI.
                                                                 \<3\> = CPT1.
                                                                 \<4\> = ZIP.
                                                                 \<5\> = TIM.
                                                                 \<6\> = RAD.
                                                                 \<7\> = PKO PPFI.
                                                                 \<8\> = CPT0.
                                                                 \<9\> = DPI.
                                                                 \<10\> = DDF.
                                                                 \<11\> = BCH.
                                                                 \<19:12\> = Reserved.

                                                                 Internal:
                                                                 Once the grant is sent, the request is marked and it is dropped when the request
                                                                 data is received. */
        uint64_t alloc_dis             : 20; /**< [ 39: 20](R/W) Allocation input disable. Each bit corresponds to a hardware allocation input
                                                                 queue, and if set add-works from the corresponding coprocessor will be dropped
                                                                 with a no-pointer fault response and FPA_GEN_INT[ALLOC_DIS] set.
                                                                 \<0\> = SSO.
                                                                 \<1\> = PKO queue.
                                                                 \<2\> = PKI.
                                                                 \<19:3\> = Reserved.

                                                                 Internal:
                                                                 There are 3 requesters on XFR bus. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_inp_ctl_s cn; */
};
typedef union bdk_fpa_inp_ctl bdk_fpa_inp_ctl_t;

#define BDK_FPA_INP_CTL BDK_FPA_INP_CTL_FUNC()
static inline uint64_t BDK_FPA_INP_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_INP_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8280000000d0ll;
    __bdk_csr_fatal("FPA_INP_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_INP_CTL bdk_fpa_inp_ctl_t
#define bustype_BDK_FPA_INP_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_INP_CTL "FPA_INP_CTL"
#define device_bar_BDK_FPA_INP_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_INP_CTL 0
#define arguments_BDK_FPA_INP_CTL -1,-1,-1,-1

/**
 * Register (NCB) fpa_pf_map#
 *
 * FPA PF VF-Mapping Registers
 * These registers map GMIDs and guest aura-sets to hardware aura-sets. An aura-set is
 * a naturally aligned set of 16 auras. This table provides a few extra entries (40
 * instead of 32) in case software needs to have an entry mapped to two guests when
 * e.g. migrating traffic or otherwise reprovisioning.
 *
 * * Regardless of this mapping table, GMID 0x0 is always invalid and use of 0x0 will
 * cause a FPA_GEN_INT[GMID0] error.
 *
 * * else, regardless of this mapping table, GMID 0x1 is always a one-to-one mapping of
 * GAURASET into VHAURASET.
 *
 * * else (excluding GMID 0x0 and 0x1), if a request hits duplicate entries a
 * FPA_GEN_INT[GMID_MULTI] error will be reported.
 *
 * * else (excluding GMID 0x0 and 0x1), if a request does not hit any entries a
 * FPA_GEN_INT[GMID_UNMAP] error will be reported.
 */
union bdk_fpa_pf_mapx
{
    uint64_t u;
    struct bdk_fpa_pf_mapx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W) This entry is valid for matching. */
        uint64_t reserved_37_62        : 26;
        uint64_t vhauraset             : 5;  /**< [ 36: 32](R/W) When [VALID] is set and this entry matches, the VHAURASET the request will be
                                                                 performed to. */
        uint64_t reserved_24_31        : 8;
        uint64_t gauraset              : 8;  /**< [ 23: 16](R/W) Guest aura-set. When [VALID], the guest's aura set to which this entry will be
                                                                 compared. */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine ID. When [VALID], the guest machine identifier to which [GAURASET]
                                                                 belongs, and to which this entry will be compared. */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine ID. When [VALID], the guest machine identifier to which [GAURASET]
                                                                 belongs, and to which this entry will be compared. */
        uint64_t gauraset              : 8;  /**< [ 23: 16](R/W) Guest aura-set. When [VALID], the guest's aura set to which this entry will be
                                                                 compared. */
        uint64_t reserved_24_31        : 8;
        uint64_t vhauraset             : 5;  /**< [ 36: 32](R/W) When [VALID] is set and this entry matches, the VHAURASET the request will be
                                                                 performed to. */
        uint64_t reserved_37_62        : 26;
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W) This entry is valid for matching. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_pf_mapx_s cn; */
};
typedef union bdk_fpa_pf_mapx bdk_fpa_pf_mapx_t;

static inline uint64_t BDK_FPA_PF_MAPX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_PF_MAPX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=39))
        return 0x828000001000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("FPA_PF_MAPX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_PF_MAPX(a) bdk_fpa_pf_mapx_t
#define bustype_BDK_FPA_PF_MAPX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_PF_MAPX(a) "FPA_PF_MAPX"
#define device_bar_BDK_FPA_PF_MAPX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_PF_MAPX(a) (a)
#define arguments_BDK_FPA_PF_MAPX(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pf_msix_pba#
 *
 * FPA MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the FPA_PF_INT_VEC_E
 * enumeration.
 */
union bdk_fpa_pf_msix_pbax
{
    uint64_t u;
    struct bdk_fpa_pf_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated FPA_PF_MSIX_VEC()_CTL, enumerated by
                                                                 FPA_PF_INT_VEC_E. Bits that have no associated FPA_PF_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated FPA_PF_MSIX_VEC()_CTL, enumerated by
                                                                 FPA_PF_INT_VEC_E. Bits that have no associated FPA_PF_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_pf_msix_pbax_s cn; */
};
typedef union bdk_fpa_pf_msix_pbax bdk_fpa_pf_msix_pbax_t;

static inline uint64_t BDK_FPA_PF_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_PF_MSIX_PBAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x8283000f0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("FPA_PF_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_PF_MSIX_PBAX(a) bdk_fpa_pf_msix_pbax_t
#define bustype_BDK_FPA_PF_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_PF_MSIX_PBAX(a) "FPA_PF_MSIX_PBAX"
#define device_bar_BDK_FPA_PF_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_FPA_PF_MSIX_PBAX(a) (a)
#define arguments_BDK_FPA_PF_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pf_msix_vec#_addr
 *
 * FPA MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the FPA_PF_INT_VEC_E enumeration.
 */
union bdk_fpa_pf_msix_vecx_addr
{
    uint64_t u;
    struct bdk_fpa_pf_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's FPA_PF_MSIX_VEC()_ADDR, FPA_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of FPA_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_FPA_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's FPA_PF_MSIX_VEC()_ADDR, FPA_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of FPA_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_FPA_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_pf_msix_vecx_addr_s cn; */
};
typedef union bdk_fpa_pf_msix_vecx_addr bdk_fpa_pf_msix_vecx_addr_t;

static inline uint64_t BDK_FPA_PF_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_PF_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x828300000000ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("FPA_PF_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_PF_MSIX_VECX_ADDR(a) bdk_fpa_pf_msix_vecx_addr_t
#define bustype_BDK_FPA_PF_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_PF_MSIX_VECX_ADDR(a) "FPA_PF_MSIX_VECX_ADDR"
#define device_bar_BDK_FPA_PF_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_FPA_PF_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_FPA_PF_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pf_msix_vec#_ctl
 *
 * FPA MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the FPA_PF_INT_VEC_E enumeration.
 */
union bdk_fpa_pf_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_fpa_pf_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_pf_msix_vecx_ctl_s cn; */
};
typedef union bdk_fpa_pf_msix_vecx_ctl bdk_fpa_pf_msix_vecx_ctl_t;

static inline uint64_t BDK_FPA_PF_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_PF_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x828300000008ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("FPA_PF_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_PF_MSIX_VECX_CTL(a) bdk_fpa_pf_msix_vecx_ctl_t
#define bustype_BDK_FPA_PF_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_PF_MSIX_VECX_CTL(a) "FPA_PF_MSIX_VECX_CTL"
#define device_bar_BDK_FPA_PF_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_FPA_PF_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_FPA_PF_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pf_vf#_gmctl
 *
 * FPA PF VF Guest Machine Control Register
 * These registers configure the memory management for each VF.
 */
union bdk_fpa_pf_vfx_gmctl
{
    uint64_t u;
    struct bdk_fpa_pf_vfx_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t stack_strm            : 8;  /**< [ 31: 24](R/W) Stack stream. Low 8 bits of the SMMU stream identifier to use for
                                                                 requests when issuing pool load/stores associated with FPA_POOL()_STACK_ADDR.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1; i.e. setting
                                                                 [STACK_STRM] to 0x0 would put the stack into the PF's memory translation space.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc.

                                                                 Only global reset can reset this register. */
        uint64_t ptr_strm              : 8;  /**< [ 23: 16](R/W) Pointer stream. Low 8 bits of the SMMU stream identifier to use
                                                                 when issuing don't write back commands on pointer returns from FPA_VHAURA()_OP_FREE().

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc.

                                                                 Only global reset can reset this register. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t ptr_strm              : 8;  /**< [ 23: 16](R/W) Pointer stream. Low 8 bits of the SMMU stream identifier to use
                                                                 when issuing don't write back commands on pointer returns from FPA_VHAURA()_OP_FREE().

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc.

                                                                 Only global reset can reset this register. */
        uint64_t stack_strm            : 8;  /**< [ 31: 24](R/W) Stack stream. Low 8 bits of the SMMU stream identifier to use for
                                                                 requests when issuing pool load/stores associated with FPA_POOL()_STACK_ADDR.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1; i.e. setting
                                                                 [STACK_STRM] to 0x0 would put the stack into the PF's memory translation space.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc.

                                                                 Only global reset can reset this register. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_pf_vfx_gmctl_s cn; */
};
typedef union bdk_fpa_pf_vfx_gmctl bdk_fpa_pf_vfx_gmctl_t;

static inline uint64_t BDK_FPA_PF_VFX_GMCTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_PF_VFX_GMCTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828040001000ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_PF_VFX_GMCTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_PF_VFX_GMCTL(a) bdk_fpa_pf_vfx_gmctl_t
#define bustype_BDK_FPA_PF_VFX_GMCTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_PF_VFX_GMCTL(a) "FPA_PF_VFX_GMCTL"
#define device_bar_BDK_FPA_PF_VFX_GMCTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_PF_VFX_GMCTL(a) (a)
#define arguments_BDK_FPA_PF_VFX_GMCTL(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pool#_cfg
 *
 * FPA Pool Configuration Registers
 */
union bdk_fpa_poolx_cfg
{
    uint64_t u;
    struct bdk_fpa_poolx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t buf_size              : 11; /**< [ 42: 32](R/W) Buffer size in 128-byte cache lines. Must be zero if [NAT_ALIGN] is clear. Buffer sizes
                                                                 are supported that are any multiple of 128 bytes in the range of 128 bytes to 128 KB. */
        uint64_t reserved_31           : 1;
        uint64_t buf_offset            : 15; /**< [ 30: 16](R/W) Number of 128-byte cache lines to offset the stored pointer. This field is sign extended
                                                                 so that two's complement numbers may be used to do subtractions.

                                                                 If [NAT_ALIGN] is clear, the pointer stored in the pool is normally the freed pointer
                                                                 adjusted by [BUF_OFFSET]. [BUF_OFFSET] will normally be zero or negative to adjust the
                                                                 pointer back to the beginning of the buffer.)

                                                                 If [NAT_ALIGN] is set, the pointer stored in the pool is normally [BUF_OFFSET] from the
                                                                 beginning of the buffer. [BUF_OFFSET] will normally be zero or positive to adjust the
                                                                 pointer into the buffer. */
        uint64_t reserved_5_15         : 11;
        uint64_t l_type                : 2;  /**< [  4:  3](R/W) Type of load to send to L2.
                                                                 0x0 = LDD.
                                                                 0x1 = LDT.
                                                                 0x2 = Load with DWB.
                                                                 0x3 = Reserved. */
        uint64_t s_type                : 1;  /**< [  2:  2](R/W) Type of store to use when FPA sends stores to L2:
                                                                 0 = use STF.
                                                                 1 = use STT. */
        uint64_t nat_align             : 1;  /**< [  1:  1](R/W) Returning buffers should be rounded to the nearest natural alignment specified with
                                                                 [BUF_SIZE]. */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) Enable. Must be set after writing pool configuration, if clear any allocations
                                                                 will fail and returns will be dropped. If any pool configuration is changed
                                                                 while this bit is set (or until traffic is quiesced after clearing), the FPA may
                                                                 operate incorrectly. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) Enable. Must be set after writing pool configuration, if clear any allocations
                                                                 will fail and returns will be dropped. If any pool configuration is changed
                                                                 while this bit is set (or until traffic is quiesced after clearing), the FPA may
                                                                 operate incorrectly. */
        uint64_t nat_align             : 1;  /**< [  1:  1](R/W) Returning buffers should be rounded to the nearest natural alignment specified with
                                                                 [BUF_SIZE]. */
        uint64_t s_type                : 1;  /**< [  2:  2](R/W) Type of store to use when FPA sends stores to L2:
                                                                 0 = use STF.
                                                                 1 = use STT. */
        uint64_t l_type                : 2;  /**< [  4:  3](R/W) Type of load to send to L2.
                                                                 0x0 = LDD.
                                                                 0x1 = LDT.
                                                                 0x2 = Load with DWB.
                                                                 0x3 = Reserved. */
        uint64_t reserved_5_15         : 11;
        uint64_t buf_offset            : 15; /**< [ 30: 16](R/W) Number of 128-byte cache lines to offset the stored pointer. This field is sign extended
                                                                 so that two's complement numbers may be used to do subtractions.

                                                                 If [NAT_ALIGN] is clear, the pointer stored in the pool is normally the freed pointer
                                                                 adjusted by [BUF_OFFSET]. [BUF_OFFSET] will normally be zero or negative to adjust the
                                                                 pointer back to the beginning of the buffer.)

                                                                 If [NAT_ALIGN] is set, the pointer stored in the pool is normally [BUF_OFFSET] from the
                                                                 beginning of the buffer. [BUF_OFFSET] will normally be zero or positive to adjust the
                                                                 pointer into the buffer. */
        uint64_t reserved_31           : 1;
        uint64_t buf_size              : 11; /**< [ 42: 32](R/W) Buffer size in 128-byte cache lines. Must be zero if [NAT_ALIGN] is clear. Buffer sizes
                                                                 are supported that are any multiple of 128 bytes in the range of 128 bytes to 128 KB. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_poolx_cfg_s cn; */
};
typedef union bdk_fpa_poolx_cfg bdk_fpa_poolx_cfg_t;

static inline uint64_t BDK_FPA_POOLX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_POOLX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828040004100ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_POOLX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_POOLX_CFG(a) bdk_fpa_poolx_cfg_t
#define bustype_BDK_FPA_POOLX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_POOLX_CFG(a) "FPA_POOLX_CFG"
#define device_bar_BDK_FPA_POOLX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_POOLX_CFG(a) (a)
#define arguments_BDK_FPA_POOLX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pool#_fpf_marks
 *
 * FPA Pool Internal Read Write Marks Registers
 * The low watermark register that determines when we read free pages from L2C.
 */
union bdk_fpa_poolx_fpf_marks
{
    uint64_t u;
    struct bdk_fpa_poolx_fpf_marks_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_27_63        : 37;
        uint64_t fpf_rd                : 11; /**< [ 26: 16](R/W) When the number of free-page pointers in a pool drops below this value and there are free-
                                                                 page pointers in DRAM, the FPA reads one page of pointers from DRAM. The recommended value
                                                                 for this field is:

                                                                 _  fpf_sz * 0.75

                                                                 _  where, fpf_sz = FPA_CONST[FPFS] / (FPA_CONST[POOLS] \>\> (FPA_GEN_CFG[POOLS]-1)).

                                                                 The maximum value is fpf_sz - 48.

                                                                 It is recommended that software APIs represent this value as a percentage of fpf_sz, as
                                                                 fpf_sz may vary between products.

                                                                 Internal:
                                                                 The worse case buffer requirement is:
                                                                 (memory_latency + 16 * (num_pools_active - 1) / cycles_per_alloc */
        uint64_t reserved_11_15        : 5;
        uint64_t fpf_level             : 11; /**< [ 10:  0](RO/H) The current number of free-page pointers in the pool, in entries. For diagnostic use. */
#else /* Word 0 - Little Endian */
        uint64_t fpf_level             : 11; /**< [ 10:  0](RO/H) The current number of free-page pointers in the pool, in entries. For diagnostic use. */
        uint64_t reserved_11_15        : 5;
        uint64_t fpf_rd                : 11; /**< [ 26: 16](R/W) When the number of free-page pointers in a pool drops below this value and there are free-
                                                                 page pointers in DRAM, the FPA reads one page of pointers from DRAM. The recommended value
                                                                 for this field is:

                                                                 _  fpf_sz * 0.75

                                                                 _  where, fpf_sz = FPA_CONST[FPFS] / (FPA_CONST[POOLS] \>\> (FPA_GEN_CFG[POOLS]-1)).

                                                                 The maximum value is fpf_sz - 48.

                                                                 It is recommended that software APIs represent this value as a percentage of fpf_sz, as
                                                                 fpf_sz may vary between products.

                                                                 Internal:
                                                                 The worse case buffer requirement is:
                                                                 (memory_latency + 16 * (num_pools_active - 1) / cycles_per_alloc */
        uint64_t reserved_27_63        : 37;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_poolx_fpf_marks_s cn; */
};
typedef union bdk_fpa_poolx_fpf_marks bdk_fpa_poolx_fpf_marks_t;

static inline uint64_t BDK_FPA_POOLX_FPF_MARKS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_POOLX_FPF_MARKS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828040004110ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_POOLX_FPF_MARKS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_POOLX_FPF_MARKS(a) bdk_fpa_poolx_fpf_marks_t
#define bustype_BDK_FPA_POOLX_FPF_MARKS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_POOLX_FPF_MARKS(a) "FPA_POOLX_FPF_MARKS"
#define device_bar_BDK_FPA_POOLX_FPF_MARKS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_POOLX_FPF_MARKS(a) (a)
#define arguments_BDK_FPA_POOLX_FPF_MARKS(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pool#_op_pc
 *
 * FPA Pool Operation Perf-Count Registers
 */
union bdk_fpa_poolx_op_pc
{
    uint64_t u;
    struct bdk_fpa_poolx_op_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of allocations or returns performed to this pool, including those that
                                                                 fail due to RED/DROP. Does not include aura count change requests (from PKI/PKO)
                                                                 that come without allocation/returns. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of allocations or returns performed to this pool, including those that
                                                                 fail due to RED/DROP. Does not include aura count change requests (from PKI/PKO)
                                                                 that come without allocation/returns. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_poolx_op_pc_s cn; */
};
typedef union bdk_fpa_poolx_op_pc bdk_fpa_poolx_op_pc_t;

static inline uint64_t BDK_FPA_POOLX_OP_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_POOLX_OP_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828040004280ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_POOLX_OP_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_POOLX_OP_PC(a) bdk_fpa_poolx_op_pc_t
#define bustype_BDK_FPA_POOLX_OP_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_POOLX_OP_PC(a) "FPA_POOLX_OP_PC"
#define device_bar_BDK_FPA_POOLX_OP_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_POOLX_OP_PC(a) (a)
#define arguments_BDK_FPA_POOLX_OP_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pool#_stack_addr
 *
 * FPA Pool Stack Last Address Registers
 */
union bdk_fpa_poolx_stack_addr
{
    uint64_t u;
    struct bdk_fpa_poolx_stack_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W/H) Next address. The IOVA of the next stack write. Must be initialized to
                                                                 FPA_POOL()_STACK_BASE[ADDR] when stack is created. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W/H) Next address. The IOVA of the next stack write. Must be initialized to
                                                                 FPA_POOL()_STACK_BASE[ADDR] when stack is created. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_poolx_stack_addr_s cn; */
};
typedef union bdk_fpa_poolx_stack_addr bdk_fpa_poolx_stack_addr_t;

static inline uint64_t BDK_FPA_POOLX_STACK_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_POOLX_STACK_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828040004240ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_POOLX_STACK_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_POOLX_STACK_ADDR(a) bdk_fpa_poolx_stack_addr_t
#define bustype_BDK_FPA_POOLX_STACK_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_POOLX_STACK_ADDR(a) "FPA_POOLX_STACK_ADDR"
#define device_bar_BDK_FPA_POOLX_STACK_ADDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_POOLX_STACK_ADDR(a) (a)
#define arguments_BDK_FPA_POOLX_STACK_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pool#_stack_base
 *
 * FPA Pool Stack Base Address Registers
 */
union bdk_fpa_poolx_stack_base
{
    uint64_t u;
    struct bdk_fpa_poolx_stack_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W) Base IOVA. The lowest address used by the pool's stack. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W) Base IOVA. The lowest address used by the pool's stack. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_poolx_stack_base_s cn; */
};
typedef union bdk_fpa_poolx_stack_base bdk_fpa_poolx_stack_base_t;

static inline uint64_t BDK_FPA_POOLX_STACK_BASE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_POOLX_STACK_BASE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828040004220ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_POOLX_STACK_BASE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_POOLX_STACK_BASE(a) bdk_fpa_poolx_stack_base_t
#define bustype_BDK_FPA_POOLX_STACK_BASE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_POOLX_STACK_BASE(a) "FPA_POOLX_STACK_BASE"
#define device_bar_BDK_FPA_POOLX_STACK_BASE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_POOLX_STACK_BASE(a) (a)
#define arguments_BDK_FPA_POOLX_STACK_BASE(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_pool#_stack_end
 *
 * FPA Pool Stack End Registers
 */
union bdk_fpa_poolx_stack_end
{
    uint64_t u;
    struct bdk_fpa_poolx_stack_end_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W) Stack ending IOVA plus one line; hardware will never write this address. If
                                                                 FPA_POOL()_STACK_ADDR is equal to this value, the stack is full. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W) Stack ending IOVA plus one line; hardware will never write this address. If
                                                                 FPA_POOL()_STACK_ADDR is equal to this value, the stack is full. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_poolx_stack_end_s cn; */
};
typedef union bdk_fpa_poolx_stack_end bdk_fpa_poolx_stack_end_t;

static inline uint64_t BDK_FPA_POOLX_STACK_END(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_POOLX_STACK_END(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828040004230ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_POOLX_STACK_END", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_POOLX_STACK_END(a) bdk_fpa_poolx_stack_end_t
#define bustype_BDK_FPA_POOLX_STACK_END(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_POOLX_STACK_END(a) "FPA_POOLX_STACK_END"
#define device_bar_BDK_FPA_POOLX_STACK_END(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_POOLX_STACK_END(a) (a)
#define arguments_BDK_FPA_POOLX_STACK_END(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_rd_latency_pc
 *
 * FPA Read Latency Perf-Count Register
 */
union bdk_fpa_rd_latency_pc
{
    uint64_t u;
    struct bdk_fpa_rd_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for L2C pool read returns. Incremented every
                                                                 coprocessor-clock by the number of transactions outstanding in that cycle. This
                                                                 may be divided by FPA_RD_REQ_PC to determine the average read latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for L2C pool read returns. Incremented every
                                                                 coprocessor-clock by the number of transactions outstanding in that cycle. This
                                                                 may be divided by FPA_RD_REQ_PC to determine the average read latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_rd_latency_pc_s cn; */
};
typedef union bdk_fpa_rd_latency_pc bdk_fpa_rd_latency_pc_t;

#define BDK_FPA_RD_LATENCY_PC BDK_FPA_RD_LATENCY_PC_FUNC()
static inline uint64_t BDK_FPA_RD_LATENCY_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_RD_LATENCY_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000610ll;
    __bdk_csr_fatal("FPA_RD_LATENCY_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_RD_LATENCY_PC bdk_fpa_rd_latency_pc_t
#define bustype_BDK_FPA_RD_LATENCY_PC BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_RD_LATENCY_PC "FPA_RD_LATENCY_PC"
#define device_bar_BDK_FPA_RD_LATENCY_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_RD_LATENCY_PC 0
#define arguments_BDK_FPA_RD_LATENCY_PC -1,-1,-1,-1

/**
 * Register (NCB) fpa_rd_req_pc
 *
 * FPA Read Request Perf-Count Register
 */
union bdk_fpa_rd_req_pc
{
    uint64_t u;
    struct bdk_fpa_rd_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of L2C pool read requests. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of L2C pool read requests. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_rd_req_pc_s cn; */
};
typedef union bdk_fpa_rd_req_pc bdk_fpa_rd_req_pc_t;

#define BDK_FPA_RD_REQ_PC BDK_FPA_RD_REQ_PC_FUNC()
static inline uint64_t BDK_FPA_RD_REQ_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_RD_REQ_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000600ll;
    __bdk_csr_fatal("FPA_RD_REQ_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_RD_REQ_PC bdk_fpa_rd_req_pc_t
#define bustype_BDK_FPA_RD_REQ_PC BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_RD_REQ_PC "FPA_RD_REQ_PC"
#define device_bar_BDK_FPA_RD_REQ_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_RD_REQ_PC 0
#define arguments_BDK_FPA_RD_REQ_PC -1,-1,-1,-1

/**
 * Register (NCB) fpa_red_delay
 *
 * FPA RED Delay Register
 */
union bdk_fpa_red_delay
{
    uint64_t u;
    struct bdk_fpa_red_delay_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t avg_dly               : 14; /**< [ 13:  0](R/W) Average-queue-size delay. The number of levelizer-clock cycles to wait (1024 *
                                                                 ([AVG_DLY]+1) * (FPA_GEN_CFG[LVL_DLY]+1)) coprocessor clocks) between calculating the
                                                                 moving average for each aura level. Note the minimum value of 2048 cycles implies that at
                                                                 100 M packets/sec, 1.2 GHz coprocessor clock, approximately 160 packets may arrive between
                                                                 average calculations.

                                                                 Larger FPA_GEN_CFG[LVL_DLY] values cause the backpressure indications and moving averages
                                                                 of all aura levels to track changes in the actual free space more slowly. Larger [AVG_DLY]
                                                                 also causes the moving averages of all aura levels to track changes in the actual free
                                                                 space more slowly, but does not affect backpressure. Larger
                                                                 FPA_AURA()_CFG[AVG_CON]) values causes a specific aura to track more slowly, but
                                                                 only affects an individual aura level, rather than all. */
#else /* Word 0 - Little Endian */
        uint64_t avg_dly               : 14; /**< [ 13:  0](R/W) Average-queue-size delay. The number of levelizer-clock cycles to wait (1024 *
                                                                 ([AVG_DLY]+1) * (FPA_GEN_CFG[LVL_DLY]+1)) coprocessor clocks) between calculating the
                                                                 moving average for each aura level. Note the minimum value of 2048 cycles implies that at
                                                                 100 M packets/sec, 1.2 GHz coprocessor clock, approximately 160 packets may arrive between
                                                                 average calculations.

                                                                 Larger FPA_GEN_CFG[LVL_DLY] values cause the backpressure indications and moving averages
                                                                 of all aura levels to track changes in the actual free space more slowly. Larger [AVG_DLY]
                                                                 also causes the moving averages of all aura levels to track changes in the actual free
                                                                 space more slowly, but does not affect backpressure. Larger
                                                                 FPA_AURA()_CFG[AVG_CON]) values causes a specific aura to track more slowly, but
                                                                 only affects an individual aura level, rather than all. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_red_delay_s cn; */
};
typedef union bdk_fpa_red_delay bdk_fpa_red_delay_t;

#define BDK_FPA_RED_DELAY BDK_FPA_RED_DELAY_FUNC()
static inline uint64_t BDK_FPA_RED_DELAY_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_RED_DELAY_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000100ll;
    __bdk_csr_fatal("FPA_RED_DELAY", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_RED_DELAY bdk_fpa_red_delay_t
#define bustype_BDK_FPA_RED_DELAY BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_RED_DELAY "FPA_RED_DELAY"
#define device_bar_BDK_FPA_RED_DELAY 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_RED_DELAY 0
#define arguments_BDK_FPA_RED_DELAY -1,-1,-1,-1

/**
 * Register (NCB) fpa_sft_rst
 *
 * FPA Soft Reset Register
 * Allows soft reset.
 */
union bdk_fpa_sft_rst
{
    uint64_t u;
    struct bdk_fpa_sft_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When 1, FPA is busy completing reset. No access except the reading of this bit should
                                                                 occur to the FPA until this is clear. */
        uint64_t reserved_1_62         : 62;
        uint64_t rst                   : 1;  /**< [  0:  0](R/W1/H) Reset. When set to 1 by software, FPA gets a short reset pulse (three cycles in duration).
                                                                 Following a write to this register and prior to performing another FPA operation, software
                                                                 must write SSO_BIST_STATUS0 (or any register on the same NCB bus as FPA) and read it back. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 1;  /**< [  0:  0](R/W1/H) Reset. When set to 1 by software, FPA gets a short reset pulse (three cycles in duration).
                                                                 Following a write to this register and prior to performing another FPA operation, software
                                                                 must write SSO_BIST_STATUS0 (or any register on the same NCB bus as FPA) and read it back. */
        uint64_t reserved_1_62         : 62;
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When 1, FPA is busy completing reset. No access except the reading of this bit should
                                                                 occur to the FPA until this is clear. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_sft_rst_s cn; */
};
typedef union bdk_fpa_sft_rst bdk_fpa_sft_rst_t;

#define BDK_FPA_SFT_RST BDK_FPA_SFT_RST_FUNC()
static inline uint64_t BDK_FPA_SFT_RST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_SFT_RST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000000ll;
    __bdk_csr_fatal("FPA_SFT_RST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_SFT_RST bdk_fpa_sft_rst_t
#define bustype_BDK_FPA_SFT_RST BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_SFT_RST "FPA_SFT_RST"
#define device_bar_BDK_FPA_SFT_RST 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_SFT_RST 0
#define arguments_BDK_FPA_SFT_RST -1,-1,-1,-1

/**
 * Register (NCB) fpa_status
 *
 * FPA Status Register
 * This register returns FPA operational status.
 */
union bdk_fpa_status
{
    uint64_t u;
    struct bdk_fpa_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t dwbq_busy             : 1;  /**< [  2:  2](RO/H) When 1, the DWBQ queue is non-empty. */
        uint64_t fpa_busy              : 1;  /**< [  1:  1](R/W1/H) When 1, FPA is active, ignoring CSR read/write activity. */
        uint64_t inp_busy              : 1;  /**< [  0:  0](R/W1/H) When 1, an input queue is non-empty. */
#else /* Word 0 - Little Endian */
        uint64_t inp_busy              : 1;  /**< [  0:  0](R/W1/H) When 1, an input queue is non-empty. */
        uint64_t fpa_busy              : 1;  /**< [  1:  1](R/W1/H) When 1, FPA is active, ignoring CSR read/write activity. */
        uint64_t dwbq_busy             : 1;  /**< [  2:  2](RO/H) When 1, the DWBQ queue is non-empty. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_status_s cn; */
};
typedef union bdk_fpa_status bdk_fpa_status_t;

#define BDK_FPA_STATUS BDK_FPA_STATUS_FUNC()
static inline uint64_t BDK_FPA_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8280000000c0ll;
    __bdk_csr_fatal("FPA_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_STATUS bdk_fpa_status_t
#define bustype_BDK_FPA_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_STATUS "FPA_STATUS"
#define device_bar_BDK_FPA_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_STATUS 0
#define arguments_BDK_FPA_STATUS -1,-1,-1,-1

/**
 * Register (NCB) fpa_unmap_info
 *
 * FPA Unmapped Error Information Register
 * When any FPA_GEN_INT[GMID_UNMAP] error occurs, this register is latched with
 * information from the original request.
 */
union bdk_fpa_unmap_info
{
    uint64_t u;
    struct bdk_fpa_unmap_info_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t gaura                 : 16; /**< [ 31: 16](RO/H) Failing GAURA. */
        uint64_t gmid                  : 16; /**< [ 15:  0](RO/H) Failing GMID. */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](RO/H) Failing GMID. */
        uint64_t gaura                 : 16; /**< [ 31: 16](RO/H) Failing GAURA. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_unmap_info_s cn; */
};
typedef union bdk_fpa_unmap_info bdk_fpa_unmap_info_t;

#define BDK_FPA_UNMAP_INFO BDK_FPA_UNMAP_INFO_FUNC()
static inline uint64_t BDK_FPA_UNMAP_INFO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_UNMAP_INFO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x828000000460ll;
    __bdk_csr_fatal("FPA_UNMAP_INFO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_UNMAP_INFO bdk_fpa_unmap_info_t
#define bustype_BDK_FPA_UNMAP_INFO BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_UNMAP_INFO "FPA_UNMAP_INFO"
#define device_bar_BDK_FPA_UNMAP_INFO 0x0 /* PF_BAR0 */
#define busnum_BDK_FPA_UNMAP_INFO 0
#define arguments_BDK_FPA_UNMAP_INFO -1,-1,-1,-1

/**
 * Register (NCB) fpa_vf#_int
 *
 * FPA VF Interrupt Registers
 */
union bdk_fpa_vfx_int
{
    uint64_t u;
    struct bdk_fpa_vfx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t a_thresh              : 16; /**< [ 47: 32](R/W1C/H) Watermark interrupt pending. Set when FPA_VHAURA()_CNT, after being modified, is
                                                                 equal to or crosses FPA_VHAURA()_CNT_THRESHOLD (i.e. value was greater than, then
                                                                 becomes less then, or value was less than, and becomes greater than). Each index
                                                                 is associated with each aura(0..15) in the aura set.

                                                                 _ FPA_VF(0)_INT[A_THRESH]\<0\> is vaura 0.
                                                                 _ FPA_VF(0)_INT[A_THRESH]\<15\> is vaura 15.
                                                                 _ FPA_VF(1)_INT[A_THRESH]\<0\> is vaura 16.
                                                                 _ FPA_VF(1)_INT[A_THRESH]\<15\> is vaura 31. */
        uint64_t reserved_7_31         : 25;
        uint64_t p_fault               : 1;  /**< [  6:  6](R/W1C/H) Set when a stack read or write returned a fault, e.g. the address the FPA stack
                                                                 was trying to access does not have a page mapped in the SMMU. */
        uint64_t as_hw_wrap            : 1;  /**< [  5:  5](R/W1C/H) Set when hardware does an add or subtract to FPA_VHAURA()_CNT for any aura in
                                                                 this aura-set caused the counter to wrap. */
        uint64_t as_sw_wrap            : 1;  /**< [  4:  4](R/W1C/H) Set when a write to FPA_VHAURA()_CNT_ADD for any aura in this aura-set does an
                                                                 add or subtract to the count that would have caused the counter to wrap, so the
                                                                 count was zeroed. */
        uint64_t p_thresh              : 1;  /**< [  3:  3](R/W1C/H) Set when FPA_VHPOOL()_AVAILABLE is equal to FPA_VHPOOL()_THRESHOLD and a pointer
                                                                 is allocated or deallocated. */
        uint64_t range                 : 1;  /**< [  2:  2](R/W1C/H) Set when a pointer address does not fall in the address range for that pool
                                                                 specified by FPA_VHPOOL()_START_ADDR and FPA_VHPOOL()_END_ADDR. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1C/H) Set when a page read from the DRAM contains inconsistent data (FPA ownership CRC
                                                                 does not match what FPA wrote). Most likely indicates the stack has been fatally
                                                                 corrupted. */
        uint64_t ovfls                 : 1;  /**< [  0:  0](R/W1C/H) Set on stack overflow; when
                                                                 FPA_POOL()_STACK_ADDR would exceed FPA_POOL()_STACK_END. */
#else /* Word 0 - Little Endian */
        uint64_t ovfls                 : 1;  /**< [  0:  0](R/W1C/H) Set on stack overflow; when
                                                                 FPA_POOL()_STACK_ADDR would exceed FPA_POOL()_STACK_END. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1C/H) Set when a page read from the DRAM contains inconsistent data (FPA ownership CRC
                                                                 does not match what FPA wrote). Most likely indicates the stack has been fatally
                                                                 corrupted. */
        uint64_t range                 : 1;  /**< [  2:  2](R/W1C/H) Set when a pointer address does not fall in the address range for that pool
                                                                 specified by FPA_VHPOOL()_START_ADDR and FPA_VHPOOL()_END_ADDR. */
        uint64_t p_thresh              : 1;  /**< [  3:  3](R/W1C/H) Set when FPA_VHPOOL()_AVAILABLE is equal to FPA_VHPOOL()_THRESHOLD and a pointer
                                                                 is allocated or deallocated. */
        uint64_t as_sw_wrap            : 1;  /**< [  4:  4](R/W1C/H) Set when a write to FPA_VHAURA()_CNT_ADD for any aura in this aura-set does an
                                                                 add or subtract to the count that would have caused the counter to wrap, so the
                                                                 count was zeroed. */
        uint64_t as_hw_wrap            : 1;  /**< [  5:  5](R/W1C/H) Set when hardware does an add or subtract to FPA_VHAURA()_CNT for any aura in
                                                                 this aura-set caused the counter to wrap. */
        uint64_t p_fault               : 1;  /**< [  6:  6](R/W1C/H) Set when a stack read or write returned a fault, e.g. the address the FPA stack
                                                                 was trying to access does not have a page mapped in the SMMU. */
        uint64_t reserved_7_31         : 25;
        uint64_t a_thresh              : 16; /**< [ 47: 32](R/W1C/H) Watermark interrupt pending. Set when FPA_VHAURA()_CNT, after being modified, is
                                                                 equal to or crosses FPA_VHAURA()_CNT_THRESHOLD (i.e. value was greater than, then
                                                                 becomes less then, or value was less than, and becomes greater than). Each index
                                                                 is associated with each aura(0..15) in the aura set.

                                                                 _ FPA_VF(0)_INT[A_THRESH]\<0\> is vaura 0.
                                                                 _ FPA_VF(0)_INT[A_THRESH]\<15\> is vaura 15.
                                                                 _ FPA_VF(1)_INT[A_THRESH]\<0\> is vaura 16.
                                                                 _ FPA_VF(1)_INT[A_THRESH]\<15\> is vaura 31. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vfx_int_s cn; */
};
typedef union bdk_fpa_vfx_int bdk_fpa_vfx_int_t;

static inline uint64_t BDK_FPA_VFX_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VFX_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828400000200ll + 0x400000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_VFX_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VFX_INT(a) bdk_fpa_vfx_int_t
#define bustype_BDK_FPA_VFX_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VFX_INT(a) "FPA_VFX_INT"
#define device_bar_BDK_FPA_VFX_INT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VFX_INT(a) (a)
#define arguments_BDK_FPA_VFX_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vf#_int_ena_w1c
 *
 * FPA VF Interrupt Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_fpa_vfx_int_ena_w1c
{
    uint64_t u;
    struct bdk_fpa_vfx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t a_thresh              : 16; /**< [ 47: 32](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[A_THRESH]. */
        uint64_t reserved_7_31         : 25;
        uint64_t p_fault               : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[P_FAULT]. */
        uint64_t as_hw_wrap            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[AS_HW_WRAP]. */
        uint64_t as_sw_wrap            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[AS_SW_WRAP]. */
        uint64_t p_thresh              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[P_THRESH]. */
        uint64_t range                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[RANGE]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[CRCERR]. */
        uint64_t ovfls                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[OVFLS]. */
#else /* Word 0 - Little Endian */
        uint64_t ovfls                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[OVFLS]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[CRCERR]. */
        uint64_t range                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[RANGE]. */
        uint64_t p_thresh              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[P_THRESH]. */
        uint64_t as_sw_wrap            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[AS_SW_WRAP]. */
        uint64_t as_hw_wrap            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[AS_HW_WRAP]. */
        uint64_t p_fault               : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[P_FAULT]. */
        uint64_t reserved_7_31         : 25;
        uint64_t a_thresh              : 16; /**< [ 47: 32](R/W1C/H) Reads or clears enable for FPA_VF(0..31)_INT[A_THRESH]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vfx_int_ena_w1c_s cn; */
};
typedef union bdk_fpa_vfx_int_ena_w1c bdk_fpa_vfx_int_ena_w1c_t;

static inline uint64_t BDK_FPA_VFX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VFX_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828400000230ll + 0x400000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_VFX_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VFX_INT_ENA_W1C(a) bdk_fpa_vfx_int_ena_w1c_t
#define bustype_BDK_FPA_VFX_INT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VFX_INT_ENA_W1C(a) "FPA_VFX_INT_ENA_W1C"
#define device_bar_BDK_FPA_VFX_INT_ENA_W1C(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VFX_INT_ENA_W1C(a) (a)
#define arguments_BDK_FPA_VFX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vf#_int_ena_w1s
 *
 * FPA VF Interrupt Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_fpa_vfx_int_ena_w1s
{
    uint64_t u;
    struct bdk_fpa_vfx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t a_thresh              : 16; /**< [ 47: 32](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[A_THRESH]. */
        uint64_t reserved_7_31         : 25;
        uint64_t p_fault               : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[P_FAULT]. */
        uint64_t as_hw_wrap            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[AS_HW_WRAP]. */
        uint64_t as_sw_wrap            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[AS_SW_WRAP]. */
        uint64_t p_thresh              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[P_THRESH]. */
        uint64_t range                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[RANGE]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[CRCERR]. */
        uint64_t ovfls                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[OVFLS]. */
#else /* Word 0 - Little Endian */
        uint64_t ovfls                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[OVFLS]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[CRCERR]. */
        uint64_t range                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[RANGE]. */
        uint64_t p_thresh              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[P_THRESH]. */
        uint64_t as_sw_wrap            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[AS_SW_WRAP]. */
        uint64_t as_hw_wrap            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[AS_HW_WRAP]. */
        uint64_t p_fault               : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[P_FAULT]. */
        uint64_t reserved_7_31         : 25;
        uint64_t a_thresh              : 16; /**< [ 47: 32](R/W1S/H) Reads or sets enable for FPA_VF(0..31)_INT[A_THRESH]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vfx_int_ena_w1s_s cn; */
};
typedef union bdk_fpa_vfx_int_ena_w1s bdk_fpa_vfx_int_ena_w1s_t;

static inline uint64_t BDK_FPA_VFX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VFX_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828400000220ll + 0x400000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_VFX_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VFX_INT_ENA_W1S(a) bdk_fpa_vfx_int_ena_w1s_t
#define bustype_BDK_FPA_VFX_INT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VFX_INT_ENA_W1S(a) "FPA_VFX_INT_ENA_W1S"
#define device_bar_BDK_FPA_VFX_INT_ENA_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VFX_INT_ENA_W1S(a) (a)
#define arguments_BDK_FPA_VFX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vf#_int_w1s
 *
 * FPA VF Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_fpa_vfx_int_w1s
{
    uint64_t u;
    struct bdk_fpa_vfx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t a_thresh              : 16; /**< [ 47: 32](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[A_THRESH]. */
        uint64_t reserved_7_31         : 25;
        uint64_t p_fault               : 1;  /**< [  6:  6](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[P_FAULT]. */
        uint64_t as_hw_wrap            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[AS_HW_WRAP]. */
        uint64_t as_sw_wrap            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[AS_SW_WRAP]. */
        uint64_t p_thresh              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[P_THRESH]. */
        uint64_t range                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[RANGE]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[CRCERR]. */
        uint64_t ovfls                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[OVFLS]. */
#else /* Word 0 - Little Endian */
        uint64_t ovfls                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[OVFLS]. */
        uint64_t crcerr                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[CRCERR]. */
        uint64_t range                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[RANGE]. */
        uint64_t p_thresh              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[P_THRESH]. */
        uint64_t as_sw_wrap            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[AS_SW_WRAP]. */
        uint64_t as_hw_wrap            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[AS_HW_WRAP]. */
        uint64_t p_fault               : 1;  /**< [  6:  6](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[P_FAULT]. */
        uint64_t reserved_7_31         : 25;
        uint64_t a_thresh              : 16; /**< [ 47: 32](R/W1S/H) Reads or sets FPA_VF(0..31)_INT[A_THRESH]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vfx_int_w1s_s cn; */
};
typedef union bdk_fpa_vfx_int_w1s bdk_fpa_vfx_int_w1s_t;

static inline uint64_t BDK_FPA_VFX_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VFX_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828400000210ll + 0x400000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_VFX_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VFX_INT_W1S(a) bdk_fpa_vfx_int_w1s_t
#define bustype_BDK_FPA_VFX_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VFX_INT_W1S(a) "FPA_VFX_INT_W1S"
#define device_bar_BDK_FPA_VFX_INT_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VFX_INT_W1S(a) (a)
#define arguments_BDK_FPA_VFX_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vf#_msix_pba#
 *
 * FPA MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the FPA_VF()_INT_VEC_E
 * enumeration.
 */
union bdk_fpa_vfx_msix_pbax
{
    uint64_t u;
    struct bdk_fpa_vfx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated FPA_PF_MSIX_VEC()_CTL, enumerated by
                                                                 FPA_PF_INT_VEC_E. Bits that have no associated FPA_PF_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated FPA_PF_MSIX_VEC()_CTL, enumerated by
                                                                 FPA_PF_INT_VEC_E. Bits that have no associated FPA_PF_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vfx_msix_pbax_s cn; */
};
typedef union bdk_fpa_vfx_msix_pbax bdk_fpa_vfx_msix_pbax_t;

static inline uint64_t BDK_FPA_VFX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VFX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b==0)))
        return 0x8287000f0000ll + 0x100000ll * ((a) & 0x1f) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("FPA_VFX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VFX_MSIX_PBAX(a,b) bdk_fpa_vfx_msix_pbax_t
#define bustype_BDK_FPA_VFX_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VFX_MSIX_PBAX(a,b) "FPA_VFX_MSIX_PBAX"
#define device_bar_BDK_FPA_VFX_MSIX_PBAX(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_FPA_VFX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_FPA_VFX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) fpa_vf#_msix_vec#_addr
 *
 * FPA VF MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the FPA_VF_INT_VEC_E enumeration.
 */
union bdk_fpa_vfx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_fpa_vfx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_FPA_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_FPA_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vfx_msix_vecx_addr_s cn; */
};
typedef union bdk_fpa_vfx_msix_vecx_addr bdk_fpa_vfx_msix_vecx_addr_t;

static inline uint64_t BDK_FPA_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b==0)))
        return 0x828700000000ll + 0x100000ll * ((a) & 0x1f) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("FPA_VFX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VFX_MSIX_VECX_ADDR(a,b) bdk_fpa_vfx_msix_vecx_addr_t
#define bustype_BDK_FPA_VFX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VFX_MSIX_VECX_ADDR(a,b) "FPA_VFX_MSIX_VECX_ADDR"
#define device_bar_BDK_FPA_VFX_MSIX_VECX_ADDR(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_FPA_VFX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_FPA_VFX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) fpa_vf#_msix_vec#_ctl
 *
 * FPA MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the FPA_VF_INT_VEC_E enumeration.
 */
union bdk_fpa_vfx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_fpa_vfx_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vfx_msix_vecx_ctl_s cn; */
};
typedef union bdk_fpa_vfx_msix_vecx_ctl bdk_fpa_vfx_msix_vecx_ctl_t;

static inline uint64_t BDK_FPA_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b==0)))
        return 0x828700000008ll + 0x100000ll * ((a) & 0x1f) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("FPA_VFX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VFX_MSIX_VECX_CTL(a,b) bdk_fpa_vfx_msix_vecx_ctl_t
#define bustype_BDK_FPA_VFX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VFX_MSIX_VECX_CTL(a,b) "FPA_VFX_MSIX_VECX_CTL"
#define device_bar_BDK_FPA_VFX_MSIX_VECX_CTL(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_FPA_VFX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_FPA_VFX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) fpa_vhaura#_cnt
 *
 * FPA VF Aura Count Register
 */
union bdk_fpa_vhaurax_cnt
{
    uint64_t u;
    struct bdk_fpa_vhaurax_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t cnt                   : 40; /**< [ 39:  0](R/W/H) The current aura count. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 40; /**< [ 39:  0](R/W/H) The current aura count. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhaurax_cnt_s cn; */
};
typedef union bdk_fpa_vhaurax_cnt bdk_fpa_vhaurax_cnt_t;

static inline uint64_t BDK_FPA_VHAURAX_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHAURAX_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x828400020120ll + 0x40000ll * ((a) & 0x1ff);
    __bdk_csr_fatal("FPA_VHAURAX_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHAURAX_CNT(a) bdk_fpa_vhaurax_cnt_t
#define bustype_BDK_FPA_VHAURAX_CNT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHAURAX_CNT(a) "FPA_VHAURAX_CNT"
#define device_bar_BDK_FPA_VHAURAX_CNT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHAURAX_CNT(a) (a)
#define arguments_BDK_FPA_VHAURAX_CNT(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vhaura#_cnt_add
 *
 * FPA VF Aura Count Addition Register
 */
union bdk_fpa_vhaurax_cnt_add
{
    uint64_t u;
    struct bdk_fpa_vhaurax_cnt_add_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t cnt                   : 40; /**< [ 39:  0](R/W/H) The value to be added to FPA_VHAURA()_CNT. The value may alternatively be a 2's
                                                                 complement of a value to be subtracted. Subtraction or addition that results in
                                                                 overflow will zero the count, not roll-around, and set either
                                                                 FPA_VF()_INT[AS_SW_WRAP] or FPA_VF()_INT[AS_HW_WRAP].

                                                                 This register is intended for use when FPA_AURA()_CFG[PTR_DIS] is set.  If
                                                                 FPA_AURA()_CFG[PTR_DIS] is clear, this register would typically only be used if buffers
                                                                 are being re-provisioned. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 40; /**< [ 39:  0](R/W/H) The value to be added to FPA_VHAURA()_CNT. The value may alternatively be a 2's
                                                                 complement of a value to be subtracted. Subtraction or addition that results in
                                                                 overflow will zero the count, not roll-around, and set either
                                                                 FPA_VF()_INT[AS_SW_WRAP] or FPA_VF()_INT[AS_HW_WRAP].

                                                                 This register is intended for use when FPA_AURA()_CFG[PTR_DIS] is set.  If
                                                                 FPA_AURA()_CFG[PTR_DIS] is clear, this register would typically only be used if buffers
                                                                 are being re-provisioned. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhaurax_cnt_add_s cn; */
};
typedef union bdk_fpa_vhaurax_cnt_add bdk_fpa_vhaurax_cnt_add_t;

static inline uint64_t BDK_FPA_VHAURAX_CNT_ADD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHAURAX_CNT_ADD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x828400020128ll + 0x40000ll * ((a) & 0x1ff);
    __bdk_csr_fatal("FPA_VHAURAX_CNT_ADD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHAURAX_CNT_ADD(a) bdk_fpa_vhaurax_cnt_add_t
#define bustype_BDK_FPA_VHAURAX_CNT_ADD(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHAURAX_CNT_ADD(a) "FPA_VHAURAX_CNT_ADD"
#define device_bar_BDK_FPA_VHAURAX_CNT_ADD(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHAURAX_CNT_ADD(a) (a)
#define arguments_BDK_FPA_VHAURAX_CNT_ADD(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vhaura#_cnt_limit
 *
 * FPA VF Aura Allocation Limit Register
 */
union bdk_fpa_vhaurax_cnt_limit
{
    uint64_t u;
    struct bdk_fpa_vhaurax_cnt_limit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t limit                 : 40; /**< [ 39:  0](R/W) When FPA_VHAURA()_CNT is equal to or greater than this value, any allocations using
                                                                 this aura will fail. This allows a hard resource division between multiple auras sharing a
                                                                 common pool. */
#else /* Word 0 - Little Endian */
        uint64_t limit                 : 40; /**< [ 39:  0](R/W) When FPA_VHAURA()_CNT is equal to or greater than this value, any allocations using
                                                                 this aura will fail. This allows a hard resource division between multiple auras sharing a
                                                                 common pool. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhaurax_cnt_limit_s cn; */
};
typedef union bdk_fpa_vhaurax_cnt_limit bdk_fpa_vhaurax_cnt_limit_t;

static inline uint64_t BDK_FPA_VHAURAX_CNT_LIMIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHAURAX_CNT_LIMIT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x828400020130ll + 0x40000ll * ((a) & 0x1ff);
    __bdk_csr_fatal("FPA_VHAURAX_CNT_LIMIT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHAURAX_CNT_LIMIT(a) bdk_fpa_vhaurax_cnt_limit_t
#define bustype_BDK_FPA_VHAURAX_CNT_LIMIT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHAURAX_CNT_LIMIT(a) "FPA_VHAURAX_CNT_LIMIT"
#define device_bar_BDK_FPA_VHAURAX_CNT_LIMIT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHAURAX_CNT_LIMIT(a) (a)
#define arguments_BDK_FPA_VHAURAX_CNT_LIMIT(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vhaura#_cnt_threshold
 *
 * FPA VF Aura Count Threshold Register
 */
union bdk_fpa_vhaurax_cnt_threshold
{
    uint64_t u;
    struct bdk_fpa_vhaurax_cnt_threshold_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t thresh                : 40; /**< [ 39:  0](R/W) When FPA_VHAURA()_CNT, after being modified, is equal to or crosses this value (i.e.
                                                                 value was greater than, then becomes less than, or the value was less than and becomes
                                                                 greater than) the corresponding bit in FPA_VF()_INT[A_THRESH] is set. */
#else /* Word 0 - Little Endian */
        uint64_t thresh                : 40; /**< [ 39:  0](R/W) When FPA_VHAURA()_CNT, after being modified, is equal to or crosses this value (i.e.
                                                                 value was greater than, then becomes less than, or the value was less than and becomes
                                                                 greater than) the corresponding bit in FPA_VF()_INT[A_THRESH] is set. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhaurax_cnt_threshold_s cn; */
};
typedef union bdk_fpa_vhaurax_cnt_threshold bdk_fpa_vhaurax_cnt_threshold_t;

static inline uint64_t BDK_FPA_VHAURAX_CNT_THRESHOLD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHAURAX_CNT_THRESHOLD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=511))
        return 0x828400020140ll + 0x40000ll * ((a) & 0x1ff);
    __bdk_csr_fatal("FPA_VHAURAX_CNT_THRESHOLD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHAURAX_CNT_THRESHOLD(a) bdk_fpa_vhaurax_cnt_threshold_t
#define bustype_BDK_FPA_VHAURAX_CNT_THRESHOLD(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHAURAX_CNT_THRESHOLD(a) "FPA_VHAURAX_CNT_THRESHOLD"
#define device_bar_BDK_FPA_VHAURAX_CNT_THRESHOLD(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHAURAX_CNT_THRESHOLD(a) (a)
#define arguments_BDK_FPA_VHAURAX_CNT_THRESHOLD(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vhaura#_op_alloc#
 *
 * FPA VF Aura Allocate Operation Register
 * Reads from this register allocate a pointer from the given aura's pool.
 *
 * The "(0)" in this register specify only the base address to which must be added the
 * lower bits of the address formed with FPA_ALLOC_ADDR_S.
 *
 * Writes to this register's address range are ignored.
 *
 * Internal:
 * arch_max really 65536,4096.
 */
union bdk_fpa_vhaurax_op_allocx
{
    uint64_t u;
    struct bdk_fpa_vhaurax_op_allocx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](RO/H) IOVA newly allocated by hardware. Bits \<6:0\> are always zero.  Bits \<63:49\> are
                                                                 a sign extension of bit \<48\>.

                                                                 If all zeros, the selected pool is empty, aura limit has been hit, or RED/DROP
                                                                 was applied. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](RO/H) IOVA newly allocated by hardware. Bits \<6:0\> are always zero.  Bits \<63:49\> are
                                                                 a sign extension of bit \<48\>.

                                                                 If all zeros, the selected pool is empty, aura limit has been hit, or RED/DROP
                                                                 was applied. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhaurax_op_allocx_s cn; */
};
typedef union bdk_fpa_vhaurax_op_allocx bdk_fpa_vhaurax_op_allocx_t;

static inline uint64_t BDK_FPA_VHAURAX_OP_ALLOCX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHAURAX_OP_ALLOCX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=511) && (b==0)))
        return 0x828400030000ll + 0x40000ll * ((a) & 0x1ff) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("FPA_VHAURAX_OP_ALLOCX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHAURAX_OP_ALLOCX(a,b) bdk_fpa_vhaurax_op_allocx_t
#define bustype_BDK_FPA_VHAURAX_OP_ALLOCX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHAURAX_OP_ALLOCX(a,b) "FPA_VHAURAX_OP_ALLOCX"
#define device_bar_BDK_FPA_VHAURAX_OP_ALLOCX(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHAURAX_OP_ALLOCX(a,b) (a)
#define arguments_BDK_FPA_VHAURAX_OP_ALLOCX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) fpa_vhaura#_op_free#
 *
 * FPA VF Aura Free Operation Register
 * Writes to this register free a pointer into the given aura's pool.
 *
 * The "(0)" in this register specify only the base address to which must be added the
 * lower bits of the address formed with FPA_FREE_ADDR_S.
 *
 * Reads to this register's address range return 0x0.
 *
 * Internal:
 * arch_max really 65536,4096.
 */
union bdk_fpa_vhaurax_op_freex
{
    uint64_t u;
    struct bdk_fpa_vhaurax_op_freex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](WO) IOVA to return to pool. Bits \<6:0\> are ignored as buffers must be 128 byte
                                                                 aligned. Bits \<63:49\> are ignored (as they are typically sign extensions of bit
                                                                 \<48\>). */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](WO) IOVA to return to pool. Bits \<6:0\> are ignored as buffers must be 128 byte
                                                                 aligned. Bits \<63:49\> are ignored (as they are typically sign extensions of bit
                                                                 \<48\>). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhaurax_op_freex_s cn; */
};
typedef union bdk_fpa_vhaurax_op_freex bdk_fpa_vhaurax_op_freex_t;

static inline uint64_t BDK_FPA_VHAURAX_OP_FREEX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHAURAX_OP_FREEX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=511) && (b==0)))
        return 0x828400038000ll + 0x40000ll * ((a) & 0x1ff) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("FPA_VHAURAX_OP_FREEX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHAURAX_OP_FREEX(a,b) bdk_fpa_vhaurax_op_freex_t
#define bustype_BDK_FPA_VHAURAX_OP_FREEX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHAURAX_OP_FREEX(a,b) "FPA_VHAURAX_OP_FREEX"
#define device_bar_BDK_FPA_VHAURAX_OP_FREEX(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHAURAX_OP_FREEX(a,b) (a)
#define arguments_BDK_FPA_VHAURAX_OP_FREEX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) fpa_vhpool#_available
 *
 * FPA Pool Free Buffers Available Registers
 */
union bdk_fpa_vhpoolx_available
{
    uint64_t u;
    struct bdk_fpa_vhpoolx_available_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t count                 : 36; /**< [ 35:  0](RO/H) The number of free buffers available in this pool.
                                                                 Internal:
                                                                 Sized for 2^41 bit
                                                                 max physical memory - 7 bit cache line. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 36; /**< [ 35:  0](RO/H) The number of free buffers available in this pool.
                                                                 Internal:
                                                                 Sized for 2^41 bit
                                                                 max physical memory - 7 bit cache line. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhpoolx_available_s cn; */
};
typedef union bdk_fpa_vhpoolx_available bdk_fpa_vhpoolx_available_t;

static inline uint64_t BDK_FPA_VHPOOLX_AVAILABLE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHPOOLX_AVAILABLE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828400004150ll + 0x400000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_VHPOOLX_AVAILABLE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHPOOLX_AVAILABLE(a) bdk_fpa_vhpoolx_available_t
#define bustype_BDK_FPA_VHPOOLX_AVAILABLE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHPOOLX_AVAILABLE(a) "FPA_VHPOOLX_AVAILABLE"
#define device_bar_BDK_FPA_VHPOOLX_AVAILABLE(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHPOOLX_AVAILABLE(a) (a)
#define arguments_BDK_FPA_VHPOOLX_AVAILABLE(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vhpool#_end_addr
 *
 * FPA Pool Ending Address Registers
 * Pointers sent to this pool after alignment must be equal to or less than this address.
 */
union bdk_fpa_vhpoolx_end_addr
{
    uint64_t u;
    struct bdk_fpa_vhpoolx_end_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W) End IOVA. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W) End IOVA. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhpoolx_end_addr_s cn; */
};
typedef union bdk_fpa_vhpoolx_end_addr bdk_fpa_vhpoolx_end_addr_t;

static inline uint64_t BDK_FPA_VHPOOLX_END_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHPOOLX_END_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828400004210ll + 0x400000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_VHPOOLX_END_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHPOOLX_END_ADDR(a) bdk_fpa_vhpoolx_end_addr_t
#define bustype_BDK_FPA_VHPOOLX_END_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHPOOLX_END_ADDR(a) "FPA_VHPOOLX_END_ADDR"
#define device_bar_BDK_FPA_VHPOOLX_END_ADDR(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHPOOLX_END_ADDR(a) (a)
#define arguments_BDK_FPA_VHPOOLX_END_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vhpool#_start_addr
 *
 * FPA Pool Starting Address Registers
 * Pointers sent to this pool after alignment must be equal to or greater than this address.
 */
union bdk_fpa_vhpoolx_start_addr
{
    uint64_t u;
    struct bdk_fpa_vhpoolx_start_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W) Start IOVA. Defaults to 1 so that a NULL pointer free will cause an exception. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t addr                  : 42; /**< [ 48:  7](R/W) Start IOVA. Defaults to 1 so that a NULL pointer free will cause an exception. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhpoolx_start_addr_s cn; */
};
typedef union bdk_fpa_vhpoolx_start_addr bdk_fpa_vhpoolx_start_addr_t;

static inline uint64_t BDK_FPA_VHPOOLX_START_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHPOOLX_START_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828400004200ll + 0x400000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_VHPOOLX_START_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHPOOLX_START_ADDR(a) bdk_fpa_vhpoolx_start_addr_t
#define bustype_BDK_FPA_VHPOOLX_START_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHPOOLX_START_ADDR(a) "FPA_VHPOOLX_START_ADDR"
#define device_bar_BDK_FPA_VHPOOLX_START_ADDR(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHPOOLX_START_ADDR(a) (a)
#define arguments_BDK_FPA_VHPOOLX_START_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) fpa_vhpool#_threshold
 *
 * FPA Pool Threshold Register
 */
union bdk_fpa_vhpoolx_threshold
{
    uint64_t u;
    struct bdk_fpa_vhpoolx_threshold_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t thresh                : 36; /**< [ 35:  0](R/W) Threshold for the pool. When the value of FPA_VHPOOL()_AVAILABLE[COUNT] is equal to
                                                                 [THRESH] and a pointer is allocated or freed, set interrupt
                                                                 FPA_VF()_INT[P_THRESH]. */
#else /* Word 0 - Little Endian */
        uint64_t thresh                : 36; /**< [ 35:  0](R/W) Threshold for the pool. When the value of FPA_VHPOOL()_AVAILABLE[COUNT] is equal to
                                                                 [THRESH] and a pointer is allocated or freed, set interrupt
                                                                 FPA_VF()_INT[P_THRESH]. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_fpa_vhpoolx_threshold_s cn; */
};
typedef union bdk_fpa_vhpoolx_threshold bdk_fpa_vhpoolx_threshold_t;

static inline uint64_t BDK_FPA_VHPOOLX_THRESHOLD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_FPA_VHPOOLX_THRESHOLD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x828400004160ll + 0x400000ll * ((a) & 0x1f);
    __bdk_csr_fatal("FPA_VHPOOLX_THRESHOLD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_FPA_VHPOOLX_THRESHOLD(a) bdk_fpa_vhpoolx_threshold_t
#define bustype_BDK_FPA_VHPOOLX_THRESHOLD(a) BDK_CSR_TYPE_NCB
#define basename_BDK_FPA_VHPOOLX_THRESHOLD(a) "FPA_VHPOOLX_THRESHOLD"
#define device_bar_BDK_FPA_VHPOOLX_THRESHOLD(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_FPA_VHPOOLX_THRESHOLD(a) (a)
#define arguments_BDK_FPA_VHPOOLX_THRESHOLD(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_FPA_H__ */
