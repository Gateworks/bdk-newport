#ifndef __BDK_CSRS_NDC_H__
#define __BDK_CSRS_NDC_H__
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
 * OcteonTX NDC.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration ndc_af_int_vec_e
 *
 * NDC AF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_NDC_AF_INT_VEC_E_INTR (0)

/**
 * Enumeration ndc_ctype_e
 *
 * NDC Caching Type Enumeration
 * Enumerates the caching type of NDC port requests, and RT index of
 * NDC_AF_PORT()_RT()_RW()_REQ_PC and NDC_AF_PORT()_RT()_RW()_LAT_PC.
 */
#define BDK_NDC_CTYPE_E_BYPASS (1)
#define BDK_NDC_CTYPE_E_CACHING (0)

/**
 * Enumeration ndc_idx_e
 *
 * RVU NDC Index Enumeration
 * Enumerates NDC instances and index of RVU_BLOCK_ADDR_E::NDC().
 */
#define BDK_NDC_IDX_E_NIXX_RX(a) (0 + 4 * (a))
#define BDK_NDC_IDX_E_NIXX_TX(a) (1 + 4 * (a))
#define BDK_NDC_IDX_E_NPA_UX(a) (2 + (a))

/**
 * Enumeration ndc_inval_res_e
 *
 * NDC Invalidate Result Enumeration
 * Enumerates possible results from Invalidate requests, and IT index of NDC_AF_PORT()_IT()_INVAL_PC
 */
#define BDK_NDC_INVAL_RES_E_BUSY (2)
#define BDK_NDC_INVAL_RES_E_MISS (1)
#define BDK_NDC_INVAL_RES_E_SUCCESS (0)

/**
 * Register (RVU_PF_BAR0) ndc#_af_active_pc
 *
 * NDC AF Active Cycles Register
 */
union bdk_ndcx_af_active_pc
{
    uint64_t u;
    struct bdk_ndcx_af_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t active_cycles         : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the conditional clocks are active. */
#else /* Word 0 - Little Endian */
        uint64_t active_cycles         : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the conditional clocks are active. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_active_pc_s cn; */
};
typedef union bdk_ndcx_af_active_pc bdk_ndcx_af_active_pc_t;

static inline uint64_t BDK_NDCX_AF_ACTIVE_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_ACTIVE_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000078ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000078ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000078ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000078ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000078ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_ACTIVE_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_ACTIVE_PC(a) bdk_ndcx_af_active_pc_t
#define bustype_BDK_NDCX_AF_ACTIVE_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_ACTIVE_PC(a) "NDCX_AF_ACTIVE_PC"
#define device_bar_BDK_NDCX_AF_ACTIVE_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_ACTIVE_PC(a) (a)
#define arguments_BDK_NDCX_AF_ACTIVE_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank#_hit_pc
 *
 * NDC AF Per-bank hit Performance Counter Registers
 */
union bdk_ndcx_af_bankx_hit_pc
{
    uint64_t u;
    struct bdk_ndcx_af_bankx_hit_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Hit counter per bank. Incremented for every miss cache access to the bank. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Hit counter per bank. Incremented for every miss cache access to the bank. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bankx_hit_pc_s cn; */
};
typedef union bdk_ndcx_af_bankx_hit_pc bdk_ndcx_af_bankx_hit_pc_t;

static inline uint64_t BDK_NDCX_AF_BANKX_HIT_PC(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKX_HIT_PC(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=15)))
        return 0x8400c0001000ll + 0x10000000ll * ((a) & 0x3) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=15)))
        return 0x8400c0001000ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=15)))
        return 0x8400c0001000ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=15)))
        return 0x8400c0001000ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=15)))
        return 0x8400c0001000ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    __bdk_csr_fatal("NDCX_AF_BANKX_HIT_PC", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_HIT_PC(a,b) bdk_ndcx_af_bankx_hit_pc_t
#define bustype_BDK_NDCX_AF_BANKX_HIT_PC(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_HIT_PC(a,b) "NDCX_AF_BANKX_HIT_PC"
#define device_bar_BDK_NDCX_AF_BANKX_HIT_PC(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_HIT_PC(a,b) (a)
#define arguments_BDK_NDCX_AF_BANKX_HIT_PC(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank#_index#_busy
 *
 * INTERNAL: NDC Cache Index Busy Registers
 *
 * These registers provide raw access to the cache metadata. For diagnostic use only.
 */
union bdk_ndcx_af_bankx_indexx_busy
{
    uint64_t u;
    struct bdk_ndcx_af_bankx_indexx_busy_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t busy                  : 64; /**< [ 63:  0](RO) BUSY value for all ways per index. Bit 0 represents way 0. */
#else /* Word 0 - Little Endian */
        uint64_t busy                  : 64; /**< [ 63:  0](RO) BUSY value for all ways per index. Bit 0 represents way 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bankx_indexx_busy_s cn; */
};
typedef union bdk_ndcx_af_bankx_indexx_busy bdk_ndcx_af_bankx_indexx_busy_t;

static inline uint64_t BDK_NDCX_AF_BANKX_INDEXX_BUSY(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKX_INDEXX_BUSY(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=15) && (c<=3)))
        return 0x8400c0000600ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000600ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000600ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000600ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000600ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANKX_INDEXX_BUSY", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) bdk_ndcx_af_bankx_indexx_busy_t
#define bustype_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) "NDCX_AF_BANKX_INDEXX_BUSY"
#define device_bar_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) (a)
#define arguments_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank#_index#_dirty
 *
 * INTERNAL: NDC Cache Index Dirty Registers
 *
 * These registers provide raw access to the cache metadata. For diagnostic use only.
 */
union bdk_ndcx_af_bankx_indexx_dirty
{
    uint64_t u;
    struct bdk_ndcx_af_bankx_indexx_dirty_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dirty                 : 64; /**< [ 63:  0](RO) DIRTY value for all ways per index. Bit 0 represents way 0. */
#else /* Word 0 - Little Endian */
        uint64_t dirty                 : 64; /**< [ 63:  0](RO) DIRTY value for all ways per index. Bit 0 represents way 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bankx_indexx_dirty_s cn; */
};
typedef union bdk_ndcx_af_bankx_indexx_dirty bdk_ndcx_af_bankx_indexx_dirty_t;

static inline uint64_t BDK_NDCX_AF_BANKX_INDEXX_DIRTY(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKX_INDEXX_DIRTY(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=15) && (c<=3)))
        return 0x8400c0000800ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000800ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000800ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000800ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000800ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANKX_INDEXX_DIRTY", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) bdk_ndcx_af_bankx_indexx_dirty_t
#define bustype_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) "NDCX_AF_BANKX_INDEXX_DIRTY"
#define device_bar_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) (a)
#define arguments_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank#_index#_lock
 *
 * INTERNAL: NDC Cache Index Lock Registers
 *
 * These registers provide raw access to the cache metadata. For diagnostic use only.
 */
union bdk_ndcx_af_bankx_indexx_lock
{
    uint64_t u;
    struct bdk_ndcx_af_bankx_indexx_lock_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t lock                  : 64; /**< [ 63:  0](RO) LOCK value for all ways per index. Bit 0 represents way 0. */
#else /* Word 0 - Little Endian */
        uint64_t lock                  : 64; /**< [ 63:  0](RO) LOCK value for all ways per index. Bit 0 represents way 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bankx_indexx_lock_s cn; */
};
typedef union bdk_ndcx_af_bankx_indexx_lock bdk_ndcx_af_bankx_indexx_lock_t;

static inline uint64_t BDK_NDCX_AF_BANKX_INDEXX_LOCK(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKX_INDEXX_LOCK(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=15) && (c<=3)))
        return 0x8400c0000a00ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000a00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000a00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000a00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000a00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANKX_INDEXX_LOCK", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) bdk_ndcx_af_bankx_indexx_lock_t
#define bustype_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) "NDCX_AF_BANKX_INDEXX_LOCK"
#define device_bar_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) (a)
#define arguments_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank#_index#_vld
 *
 * INTERNAL: NDC Cache Index Valid Registers
 *
 * These registers provide raw access to the cache metadata. For diagnostic use only.
 */
union bdk_ndcx_af_bankx_indexx_vld
{
    uint64_t u;
    struct bdk_ndcx_af_bankx_indexx_vld_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t vld                   : 64; /**< [ 63:  0](RO) VLD value for all ways per index. Bit 0 represents way 0. */
#else /* Word 0 - Little Endian */
        uint64_t vld                   : 64; /**< [ 63:  0](RO) VLD value for all ways per index. Bit 0 represents way 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bankx_indexx_vld_s cn; */
};
typedef union bdk_ndcx_af_bankx_indexx_vld bdk_ndcx_af_bankx_indexx_vld_t;

static inline uint64_t BDK_NDCX_AF_BANKX_INDEXX_VLD(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKX_INDEXX_VLD(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=15) && (c<=3)))
        return 0x8400c0000400ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000400ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000400ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000400ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=15) && (c<=3)))
        return 0x8400c0000400ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANKX_INDEXX_VLD", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) bdk_ndcx_af_bankx_indexx_vld_t
#define bustype_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) "NDCX_AF_BANKX_INDEXX_VLD"
#define device_bar_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) (a)
#define arguments_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank#_line#_metadata
 *
 * INTERNAL: NDC Cache Metadata Registers
 *
 * These registers provide raw access to the cache meta data. For diagnostic use only.
 *
 * For valid data to be returned, before accessing this register software must set
 * NDC_AF_CAMS_RD_INTERVAL[ENABLE] to zero, then poll until
 * NDC_AF_CAMS_RD_INTERVAL[BUSY] is zero.
 */
union bdk_ndcx_af_bankx_linex_metadata
{
    uint64_t u;
    struct bdk_ndcx_af_bankx_linex_metadata_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t vld                   : 1;  /**< [ 63: 63](R/W/H) Cache line valid bit. */
        uint64_t busy                  : 1;  /**< [ 62: 62](R/W/H) Cache line busy bit. */
        uint64_t dirty                 : 1;  /**< [ 61: 61](R/W/H) Cache line dirty bit. */
        uint64_t lock                  : 1;  /**< [ 60: 60](R/W/H) Cache line lock bit. */
        uint64_t dyn                   : 1;  /**< [ 59: 59](R/W/H) Dynamic bit. Kept in CAM. Address CAM holds {DYN, 1'h0, ADD[52:7]}. */
        uint64_t address               : 46; /**< [ 58: 13](R/W/H) Cache line address bits \<52:7\>. Kept in CAM. Address CAM holds {DYN, 1'h0,ADD[52:7]}. */
        uint64_t strm_id               : 13; /**< [ 12:  0](R/W/H) Cache line stream ID. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 13; /**< [ 12:  0](R/W/H) Cache line stream ID. */
        uint64_t address               : 46; /**< [ 58: 13](R/W/H) Cache line address bits \<52:7\>. Kept in CAM. Address CAM holds {DYN, 1'h0,ADD[52:7]}. */
        uint64_t dyn                   : 1;  /**< [ 59: 59](R/W/H) Dynamic bit. Kept in CAM. Address CAM holds {DYN, 1'h0, ADD[52:7]}. */
        uint64_t lock                  : 1;  /**< [ 60: 60](R/W/H) Cache line lock bit. */
        uint64_t dirty                 : 1;  /**< [ 61: 61](R/W/H) Cache line dirty bit. */
        uint64_t busy                  : 1;  /**< [ 62: 62](R/W/H) Cache line busy bit. */
        uint64_t vld                   : 1;  /**< [ 63: 63](R/W/H) Cache line valid bit. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bankx_linex_metadata_s cn; */
};
typedef union bdk_ndcx_af_bankx_linex_metadata bdk_ndcx_af_bankx_linex_metadata_t;

static inline uint64_t BDK_NDCX_AF_BANKX_LINEX_METADATA(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKX_LINEX_METADATA(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=15) && (c<=255)))
        return 0x8400c0010000ll + 0x10000000ll * ((a) & 0x3) + 0x1000ll * ((b) & 0xf) + 8ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=15) && (c<=255)))
        return 0x8400c0010000ll + 0x10000000ll * ((a) & 0x7) + 0x1000ll * ((b) & 0xf) + 8ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=15) && (c<=255)))
        return 0x8400c0010000ll + 0x10000000ll * ((a) & 0x7) + 0x1000ll * ((b) & 0xf) + 8ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=15) && (c<=255)))
        return 0x8400c0010000ll + 0x10000000ll * ((a) & 0x7) + 0x1000ll * ((b) & 0xf) + 8ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=15) && (c<=255)))
        return 0x8400c0010000ll + 0x10000000ll * ((a) & 0x7) + 0x1000ll * ((b) & 0xf) + 8ll * ((c) & 0xff);
    __bdk_csr_fatal("NDCX_AF_BANKX_LINEX_METADATA", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) bdk_ndcx_af_bankx_linex_metadata_t
#define bustype_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) "NDCX_AF_BANKX_LINEX_METADATA"
#define device_bar_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) (a)
#define arguments_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank#_line#_word#
 *
 * INTERNAL: NDC Cache Word Data Registers
 *
 * These registers provide raw access to the cache. For diagnostic use only.
 */
union bdk_ndcx_af_bankx_linex_wordx
{
    uint64_t u;
    struct bdk_ndcx_af_bankx_linex_wordx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t word                  : 64; /**< [ 63:  0](R/W/H) Data from cache line. */
#else /* Word 0 - Little Endian */
        uint64_t word                  : 64; /**< [ 63:  0](R/W/H) Data from cache line. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bankx_linex_wordx_s cn; */
};
typedef union bdk_ndcx_af_bankx_linex_wordx bdk_ndcx_af_bankx_linex_wordx_t;

static inline uint64_t BDK_NDCX_AF_BANKX_LINEX_WORDX(unsigned long a, unsigned long b, unsigned long c, unsigned long d) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKX_LINEX_WORDX(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=15) && (c<=255) && (d<=15)))
        return 0x8400c0100000ll + 0x10000000ll * ((a) & 0x3) + 0x8000ll * ((b) & 0xf) + 0x80ll * ((c) & 0xff) + 8ll * ((d) & 0xf);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=15) && (c<=255) && (d<=15)))
        return 0x8400c0100000ll + 0x10000000ll * ((a) & 0x7) + 0x8000ll * ((b) & 0xf) + 0x80ll * ((c) & 0xff) + 8ll * ((d) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=15) && (c<=255) && (d<=15)))
        return 0x8400c0100000ll + 0x10000000ll * ((a) & 0x7) + 0x8000ll * ((b) & 0xf) + 0x80ll * ((c) & 0xff) + 8ll * ((d) & 0xf);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=15) && (c<=255) && (d<=15)))
        return 0x8400c0100000ll + 0x10000000ll * ((a) & 0x7) + 0x8000ll * ((b) & 0xf) + 0x80ll * ((c) & 0xff) + 8ll * ((d) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=15) && (c<=255) && (d<=15)))
        return 0x8400c0100000ll + 0x10000000ll * ((a) & 0x7) + 0x8000ll * ((b) & 0xf) + 0x80ll * ((c) & 0xff) + 8ll * ((d) & 0xf);
    __bdk_csr_fatal("NDCX_AF_BANKX_LINEX_WORDX", 4, a, b, c, d, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) bdk_ndcx_af_bankx_linex_wordx_t
#define bustype_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) "NDCX_AF_BANKX_LINEX_WORDX"
#define device_bar_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) (a)
#define arguments_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) (a),(b),(c),(d)

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank#_miss_pc
 *
 * NDC AF Per-bank miss Performance Counter Registers
 */
union bdk_ndcx_af_bankx_miss_pc
{
    uint64_t u;
    struct bdk_ndcx_af_bankx_miss_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Miss counter per bank. Incremented for every miss cache access to the bank. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Miss counter per bank. Incremented for every miss cache access to the bank. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bankx_miss_pc_s cn; */
};
typedef union bdk_ndcx_af_bankx_miss_pc bdk_ndcx_af_bankx_miss_pc_t;

static inline uint64_t BDK_NDCX_AF_BANKX_MISS_PC(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKX_MISS_PC(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=15)))
        return 0x8400c0001100ll + 0x10000000ll * ((a) & 0x3) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=15)))
        return 0x8400c0001100ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=15)))
        return 0x8400c0001100ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=15)))
        return 0x8400c0001100ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=15)))
        return 0x8400c0001100ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0xf);
    __bdk_csr_fatal("NDCX_AF_BANKX_MISS_PC", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_MISS_PC(a,b) bdk_ndcx_af_bankx_miss_pc_t
#define bustype_BDK_NDCX_AF_BANKX_MISS_PC(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_MISS_PC(a,b) "NDCX_AF_BANKX_MISS_PC"
#define device_bar_BDK_NDCX_AF_BANKX_MISS_PC(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_MISS_PC(a,b) (a)
#define arguments_BDK_NDCX_AF_BANKX_MISS_PC(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank_ctl_done
 *
 * NDC Bank Control Register
 * Done indication for operation taken by hardware due to a write to
 * NDC_AF_BANKS_CTL[SYNC_ALL] or NDC_AF_BANKS_CTL[FLUSH_ALL].
 */
union bdk_ndcx_af_bank_ctl_done
{
    uint64_t u;
    struct bdk_ndcx_af_bank_ctl_done_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t done                  : 16; /**< [ 15:  0](R/W1C/H) Done indication. Each bit represent one NDC bank.
                                                                 Set by hardware when NDC banks completes the request as was
                                                                 submitted using NDC_AF_BANKS_CTL[SYNC_ALL] or NDC_AF_BANKS_CTL[FLUSH_ALL].
                                                                 NDC_AF_BANKS_CTL[SYNC_ALL] or NDC_AF_BANKS_CTL[FLUSH_ALL] operation are completed
                                                                 when all 16 bits in [DONE] are set. Use W1C before setting NDC_AF_BANKS_CTL[SYNC_ALL]
                                                                 or NDC_AF_BANKS_CTL[FLUSH_ALL] again. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 16; /**< [ 15:  0](R/W1C/H) Done indication. Each bit represent one NDC bank.
                                                                 Set by hardware when NDC banks completes the request as was
                                                                 submitted using NDC_AF_BANKS_CTL[SYNC_ALL] or NDC_AF_BANKS_CTL[FLUSH_ALL].
                                                                 NDC_AF_BANKS_CTL[SYNC_ALL] or NDC_AF_BANKS_CTL[FLUSH_ALL] operation are completed
                                                                 when all 16 bits in [DONE] are set. Use W1C before setting NDC_AF_BANKS_CTL[SYNC_ALL]
                                                                 or NDC_AF_BANKS_CTL[FLUSH_ALL] again. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bank_ctl_done_s cn; */
};
typedef union bdk_ndcx_af_bank_ctl_done bdk_ndcx_af_bank_ctl_done_t;

static inline uint64_t BDK_NDCX_AF_BANK_CTL_DONE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANK_CTL_DONE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000048ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000048ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000048ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000048ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000048ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_BANK_CTL_DONE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANK_CTL_DONE(a) bdk_ndcx_af_bank_ctl_done_t
#define bustype_BDK_NDCX_AF_BANK_CTL_DONE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANK_CTL_DONE(a) "NDCX_AF_BANK_CTL_DONE"
#define device_bar_BDK_NDCX_AF_BANK_CTL_DONE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANK_CTL_DONE(a) (a)
#define arguments_BDK_NDCX_AF_BANK_CTL_DONE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_banks_ctl
 *
 * NDC Bank Control Register
 * Write only register clears NDC cache meta data or trigger FLUSH/SYNC ALL.
 */
union bdk_ndcx_af_banks_ctl
{
    uint64_t u;
    struct bdk_ndcx_af_banks_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_18_63        : 46;
        uint64_t flush_all             : 1;  /**< [ 17: 17](WO) When written one, all dirty lines will be flushed to LLC. All lines ends up
                                                                 invalidated when process is complete. If [FLUSH_ALL] is set none of the other
                                                                 bits should be set in the same write operation.
                                                                 W1C NDC_AF_BANK_CTL_DONE[DONE] before setting this bit. */
        uint64_t sync_all              : 1;  /**< [ 16: 16](WO) When written one, syncs NDC cache with LLC. All dirty lines will be flushed to
                                                                 LLC/DRAM. Lines valid bit remains set but dirty bit will be cleared upon completion
                                                                 of flush operation. If [SYNC_ALL] is set none of the other bits should be set in
                                                                 the same write operation.
                                                                 W1C NDC_AF_BANK_CTL_DONE[DONE] before setting this bit. */
        uint64_t reserved_4_15         : 12;
        uint64_t bk_rst_lock           : 1;  /**< [  3:  3](WO) When written one, clears all bank lines lock indication. Note any BK_RST* bits
                                                                 could be set at the same time for a single write operation. */
        uint64_t bk_rst_dirty          : 1;  /**< [  2:  2](WO) When written one, clears all bank lines dirty indication. If inappropriately
                                                                 used, this may cause data loss. Note any BK_RST* bits could be set at the same
                                                                 time for a single write operation. */
        uint64_t bk_rst_busy           : 1;  /**< [  1:  1](WO) When written one, clears all bank lines busy indication. If inappropriately
                                                                 used, this may cause data loss. Note any BK_RST* bits could be set at the same
                                                                 time for a single write operation. */
        uint64_t bk_rst_vld            : 1;  /**< [  0:  0](WO) When written one, invalidate all banks lines. When setting this bit, one should
                                                                 also set NDC_AF_BANKS_CTL[BK_RST_BUSY], NDC_AF_BANKS_CTL[BK_RST_DIRTY],
                                                                 and NDC_AF_BANKS_CTL[BK_RST_LOCK]. If inappropriately used, this may cause data loss.
                                                                 Note any BK_RST* bits could be set at the same time for a single write operation. */
#else /* Word 0 - Little Endian */
        uint64_t bk_rst_vld            : 1;  /**< [  0:  0](WO) When written one, invalidate all banks lines. When setting this bit, one should
                                                                 also set NDC_AF_BANKS_CTL[BK_RST_BUSY], NDC_AF_BANKS_CTL[BK_RST_DIRTY],
                                                                 and NDC_AF_BANKS_CTL[BK_RST_LOCK]. If inappropriately used, this may cause data loss.
                                                                 Note any BK_RST* bits could be set at the same time for a single write operation. */
        uint64_t bk_rst_busy           : 1;  /**< [  1:  1](WO) When written one, clears all bank lines busy indication. If inappropriately
                                                                 used, this may cause data loss. Note any BK_RST* bits could be set at the same
                                                                 time for a single write operation. */
        uint64_t bk_rst_dirty          : 1;  /**< [  2:  2](WO) When written one, clears all bank lines dirty indication. If inappropriately
                                                                 used, this may cause data loss. Note any BK_RST* bits could be set at the same
                                                                 time for a single write operation. */
        uint64_t bk_rst_lock           : 1;  /**< [  3:  3](WO) When written one, clears all bank lines lock indication. Note any BK_RST* bits
                                                                 could be set at the same time for a single write operation. */
        uint64_t reserved_4_15         : 12;
        uint64_t sync_all              : 1;  /**< [ 16: 16](WO) When written one, syncs NDC cache with LLC. All dirty lines will be flushed to
                                                                 LLC/DRAM. Lines valid bit remains set but dirty bit will be cleared upon completion
                                                                 of flush operation. If [SYNC_ALL] is set none of the other bits should be set in
                                                                 the same write operation.
                                                                 W1C NDC_AF_BANK_CTL_DONE[DONE] before setting this bit. */
        uint64_t flush_all             : 1;  /**< [ 17: 17](WO) When written one, all dirty lines will be flushed to LLC. All lines ends up
                                                                 invalidated when process is complete. If [FLUSH_ALL] is set none of the other
                                                                 bits should be set in the same write operation.
                                                                 W1C NDC_AF_BANK_CTL_DONE[DONE] before setting this bit. */
        uint64_t reserved_18_63        : 46;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_banks_ctl_s cn; */
};
typedef union bdk_ndcx_af_banks_ctl bdk_ndcx_af_banks_ctl_t;

static inline uint64_t BDK_NDCX_AF_BANKS_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKS_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000040ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000040ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000040ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000040ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000040ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_BANKS_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKS_CTL(a) bdk_ndcx_af_banks_ctl_t
#define bustype_BDK_NDCX_AF_BANKS_CTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKS_CTL(a) "NDCX_AF_BANKS_CTL"
#define device_bar_BDK_NDCX_AF_BANKS_CTL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BANKS_CTL(a) (a)
#define arguments_BDK_NDCX_AF_BANKS_CTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_blk_rst
 *
 * NDC AF Block Reset Registers
 */
union bdk_ndcx_af_blk_rst
{
    uint64_t u;
    struct bdk_ndcx_af_blk_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When one, the block is busy completing reset. No access except the reading of
                                                                 this bit should occur to the block until this is clear. */
        uint64_t reserved_1_62         : 62;
        uint64_t rst                   : 1;  /**< [  0:  0](WO) Write one to reset the block, except for privileged AF registers in PF BAR0
                                                                 (block_PRIV_*). Software must ensure that all block activity is quiesced before
                                                                 writing 1. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 1;  /**< [  0:  0](WO) Write one to reset the block, except for privileged AF registers in PF BAR0
                                                                 (block_PRIV_*). Software must ensure that all block activity is quiesced before
                                                                 writing 1. */
        uint64_t reserved_1_62         : 62;
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When one, the block is busy completing reset. No access except the reading of
                                                                 this bit should occur to the block until this is clear. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_blk_rst_s cn; */
};
typedef union bdk_ndcx_af_blk_rst bdk_ndcx_af_blk_rst_t;

static inline uint64_t BDK_NDCX_AF_BLK_RST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BLK_RST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c00002f0ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c00002f0ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c00002f0ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c00002f0ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c00002f0ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_BLK_RST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BLK_RST(a) bdk_ndcx_af_blk_rst_t
#define bustype_BDK_NDCX_AF_BLK_RST(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BLK_RST(a) "NDCX_AF_BLK_RST"
#define device_bar_BDK_NDCX_AF_BLK_RST(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BLK_RST(a) (a)
#define arguments_BDK_NDCX_AF_BLK_RST(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bp_test#
 *
 * INTERNAL: NDC AF Backpressure Test Register
 */
union bdk_ndcx_af_bp_testx
{
    uint64_t u;
    struct bdk_ndcx_af_bp_testx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode along with NDC_AF_BP_TEST_ENABLE. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 BP_TEST\<0.63\> = bp_prt_cmd_xbar    = Ports (0..5) CMD FIFO.
                                                                 BP_TEST\<0.62\> = bp_prt_data_xbar   = Ports (0..5) DATA FIFO.
                                                                 BP_TEST\<0.61\> = bp_xbar_bank_req   = Xbar towards the bank request FIFOs.
                                                                 BP_TEST\<0.60\> = bp_ncb_cmn_intf    = Ncb common interface to banks.
                                                                 BP_TEST\<1.63\> = bp_ncb_cmn_p0      = ncb_cmn module port 0.
                                                                 BP_TEST\<1.62\> = bp_ncb_cmn_p1      = ncb_cmn module port 1.
                                                                 BP_TEST\<1.61\> = bp_ncb_cmn_p2      = ncb_cmn module port 2.
                                                                 BP_TEST\<1.60\> = bp_ncb_cmn_p3      = ncb_cmn module port 3.
                                                                 BP_TEST\<2.63\> = bp_bk_cmd_req      = Bank command request FIFO.
                                                                 BP_TEST\<2.62\> = bp_bk_data_req     = Bank data request FIFO.
                                                                 BP_TEST\<2.61\> = bp_bk_pend_req     = Pending request FIFO.
                                                                 BP_TEST\<2.60\> = bp_bk_arb          = Bank mem Arbiter.
                                                                 BP_TEST\<3.63\> = bp_bk_ncb_req      = NCBI request interface.
                                                                 BP_TEST\<3.62\> = bp_bk_port_rsp     = Bank response.
                                                                 BP_TEST\<3.61\> = bp_bk_ncbo_ld_rsp  = Bank Load response.
                                                                 BP_TEST\<3.60\> = Reserved. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode along with NDC_AF_BP_TEST_ENABLE. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 BP_TEST\<0.63\> = bp_prt_cmd_xbar    = Ports (0..5) CMD FIFO.
                                                                 BP_TEST\<0.62\> = bp_prt_data_xbar   = Ports (0..5) DATA FIFO.
                                                                 BP_TEST\<0.61\> = bp_xbar_bank_req   = Xbar towards the bank request FIFOs.
                                                                 BP_TEST\<0.60\> = bp_ncb_cmn_intf    = Ncb common interface to banks.
                                                                 BP_TEST\<1.63\> = bp_ncb_cmn_p0      = ncb_cmn module port 0.
                                                                 BP_TEST\<1.62\> = bp_ncb_cmn_p1      = ncb_cmn module port 1.
                                                                 BP_TEST\<1.61\> = bp_ncb_cmn_p2      = ncb_cmn module port 2.
                                                                 BP_TEST\<1.60\> = bp_ncb_cmn_p3      = ncb_cmn module port 3.
                                                                 BP_TEST\<2.63\> = bp_bk_cmd_req      = Bank command request FIFO.
                                                                 BP_TEST\<2.62\> = bp_bk_data_req     = Bank data request FIFO.
                                                                 BP_TEST\<2.61\> = bp_bk_pend_req     = Pending request FIFO.
                                                                 BP_TEST\<2.60\> = bp_bk_arb          = Bank mem Arbiter.
                                                                 BP_TEST\<3.63\> = bp_bk_ncb_req      = NCBI request interface.
                                                                 BP_TEST\<3.62\> = bp_bk_port_rsp     = Bank response.
                                                                 BP_TEST\<3.61\> = bp_bk_ncbo_ld_rsp  = Bank Load response.
                                                                 BP_TEST\<3.60\> = Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bp_testx_s cn; */
};
typedef union bdk_ndcx_af_bp_testx bdk_ndcx_af_bp_testx_t;

static inline uint64_t BDK_NDCX_AF_BP_TESTX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BP_TESTX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=3)))
        return 0x8400c0000200ll + 0x10000000ll * ((a) & 0x3) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=3)))
        return 0x8400c0000200ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=3)))
        return 0x8400c0000200ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=3)))
        return 0x8400c0000200ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=3)))
        return 0x8400c0000200ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BP_TESTX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BP_TESTX(a,b) bdk_ndcx_af_bp_testx_t
#define bustype_BDK_NDCX_AF_BP_TESTX(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BP_TESTX(a,b) "NDCX_AF_BP_TESTX"
#define device_bar_BDK_NDCX_AF_BP_TESTX(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BP_TESTX(a,b) (a)
#define arguments_BDK_NDCX_AF_BP_TESTX(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bp_test_enable
 *
 * NDC AF Backpressure Test Enable Register
 */
union bdk_ndcx_af_bp_test_enable
{
    uint64_t u;
    struct bdk_ndcx_af_bp_test_enable_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t xbar_bp_en            : 4;  /**< [ 43: 40](R/W) Enables backpressure testing on each cluster XBAR as described in NDC_AF_BP_TEST(0.61). */
        uint64_t reserved_38_39        : 2;
        uint64_t prt_bp_en             : 6;  /**< [ 37: 32](R/W) Enables backpressure testing on CMD and DATA requests buffer as described in
                                                                 NDC_AF_BP_TEST(0.63,0.62). */
        uint64_t reserved_16_31        : 16;
        uint64_t bk_bp_en              : 16; /**< [ 15:  0](R/W) Enables backpressure testing on NDC banks as described in NDC_AF_BP_TEST(2..3) */
#else /* Word 0 - Little Endian */
        uint64_t bk_bp_en              : 16; /**< [ 15:  0](R/W) Enables backpressure testing on NDC banks as described in NDC_AF_BP_TEST(2..3) */
        uint64_t reserved_16_31        : 16;
        uint64_t prt_bp_en             : 6;  /**< [ 37: 32](R/W) Enables backpressure testing on CMD and DATA requests buffer as described in
                                                                 NDC_AF_BP_TEST(0.63,0.62). */
        uint64_t reserved_38_39        : 2;
        uint64_t xbar_bp_en            : 4;  /**< [ 43: 40](R/W) Enables backpressure testing on each cluster XBAR as described in NDC_AF_BP_TEST(0.61). */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bp_test_enable_s cn; */
};
typedef union bdk_ndcx_af_bp_test_enable bdk_ndcx_af_bp_test_enable_t;

static inline uint64_t BDK_NDCX_AF_BP_TEST_ENABLE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BP_TEST_ENABLE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c00001f8ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c00001f8ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c00001f8ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c00001f8ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c00001f8ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_BP_TEST_ENABLE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BP_TEST_ENABLE(a) bdk_ndcx_af_bp_test_enable_t
#define bustype_BDK_NDCX_AF_BP_TEST_ENABLE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BP_TEST_ENABLE(a) "NDCX_AF_BP_TEST_ENABLE"
#define device_bar_BDK_NDCX_AF_BP_TEST_ENABLE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_BP_TEST_ENABLE(a) (a)
#define arguments_BDK_NDCX_AF_BP_TEST_ENABLE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_cams_rd_interval
 *
 * NDC AF CAMS Read Interval For Parity Error Detection Register
 */
union bdk_ndcx_af_cams_rd_interval
{
    uint64_t u;
    struct bdk_ndcx_af_cams_rd_interval_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) When one, NDC reads all the CAMs entries periodically as specified by
                                                                 NDC_AF_CAMS_RD_INTERVAL[THRESHOLD] in order to find soft single-bit errors. */
        uint64_t reserved_48_62        : 15;
        uint64_t busy                  : 16; /**< [ 47: 32](RO/H) While one, hardware is busy reading all the CAMs entries. Each bit represents
                                                                 one of the NDC banks. */
        uint64_t reserved_16_31        : 16;
        uint64_t threshold             : 16; /**< [ 15:  0](R/W) Frequency between reading all CAMs entries, in units of 1024 coprocessor-clock
                                                                 cycles. Minimum possible value of 1 represents 1024 design cycles. Larger values
                                                                 will reduce power. Only valid when [ENABLE] is one. */
#else /* Word 0 - Little Endian */
        uint64_t threshold             : 16; /**< [ 15:  0](R/W) Frequency between reading all CAMs entries, in units of 1024 coprocessor-clock
                                                                 cycles. Minimum possible value of 1 represents 1024 design cycles. Larger values
                                                                 will reduce power. Only valid when [ENABLE] is one. */
        uint64_t reserved_16_31        : 16;
        uint64_t busy                  : 16; /**< [ 47: 32](RO/H) While one, hardware is busy reading all the CAMs entries. Each bit represents
                                                                 one of the NDC banks. */
        uint64_t reserved_48_62        : 15;
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) When one, NDC reads all the CAMs entries periodically as specified by
                                                                 NDC_AF_CAMS_RD_INTERVAL[THRESHOLD] in order to find soft single-bit errors. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_cams_rd_interval_s cn; */
};
typedef union bdk_ndcx_af_cams_rd_interval bdk_ndcx_af_cams_rd_interval_t;

static inline uint64_t BDK_NDCX_AF_CAMS_RD_INTERVAL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_CAMS_RD_INTERVAL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000080ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000080ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000080ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000080ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000080ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_CAMS_RD_INTERVAL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_CAMS_RD_INTERVAL(a) bdk_ndcx_af_cams_rd_interval_t
#define bustype_BDK_NDCX_AF_CAMS_RD_INTERVAL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_CAMS_RD_INTERVAL(a) "NDCX_AF_CAMS_RD_INTERVAL"
#define device_bar_BDK_NDCX_AF_CAMS_RD_INTERVAL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_CAMS_RD_INTERVAL(a) (a)
#define arguments_BDK_NDCX_AF_CAMS_RD_INTERVAL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_clk_en
 *
 * NDC Clock Enable Control Register
 */
union bdk_ndcx_af_clk_en
{
    uint64_t u;
    struct bdk_ndcx_af_clk_en_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t clk_en                : 1;  /**< [ 31: 31](R/W) When set, forces entire NDC block clock to be always on. For diagnostic use only. */
        uint64_t intf_clk_en           : 1;  /**< [ 30: 30](R/W) When set, forces NDC's interfaces clock to be always on. For diagnostic use only. */
        uint64_t reserved_0_29         : 30;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_29         : 30;
        uint64_t intf_clk_en           : 1;  /**< [ 30: 30](R/W) When set, forces NDC's interfaces clock to be always on. For diagnostic use only. */
        uint64_t clk_en                : 1;  /**< [ 31: 31](R/W) When set, forces entire NDC block clock to be always on. For diagnostic use only. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_clk_en_s cn; */
};
typedef union bdk_ndcx_af_clk_en bdk_ndcx_af_clk_en_t;

static inline uint64_t BDK_NDCX_AF_CLK_EN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_CLK_EN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000020ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000020ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000020ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000020ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000020ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_CLK_EN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_CLK_EN(a) bdk_ndcx_af_clk_en_t
#define bustype_BDK_NDCX_AF_CLK_EN(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_CLK_EN(a) "NDCX_AF_CLK_EN"
#define device_bar_BDK_NDCX_AF_CLK_EN(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_CLK_EN(a) (a)
#define arguments_BDK_NDCX_AF_CLK_EN(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_const
 *
 * NDC Constants Register
 */
union bdk_ndcx_af_const
{
    uint64_t u;
    struct bdk_ndcx_af_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t way                   : 8;  /**< [ 55: 48](RO) Number of ways per bank. */
        uint64_t reserved_32_47        : 16;
        uint64_t line                  : 16; /**< [ 31: 16](RO) Number of lines per bank. */
        uint64_t reserved_8_15         : 8;
        uint64_t bank                  : 8;  /**< [  7:  0](RO) Number of banks in NDC. */
#else /* Word 0 - Little Endian */
        uint64_t bank                  : 8;  /**< [  7:  0](RO) Number of banks in NDC. */
        uint64_t reserved_8_15         : 8;
        uint64_t line                  : 16; /**< [ 31: 16](RO) Number of lines per bank. */
        uint64_t reserved_32_47        : 16;
        uint64_t way                   : 8;  /**< [ 55: 48](RO) Number of ways per bank. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_const_s cn; */
};
typedef union bdk_ndcx_af_const bdk_ndcx_af_const_t;

static inline uint64_t BDK_NDCX_AF_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_CONST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000000ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000000ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000000ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000000ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000000ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_CONST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_CONST(a) bdk_ndcx_af_const_t
#define bustype_BDK_NDCX_AF_CONST(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_CONST(a) "NDCX_AF_CONST"
#define device_bar_BDK_NDCX_AF_CONST(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_CONST(a) (a)
#define arguments_BDK_NDCX_AF_CONST(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_ctl
 *
 * NDC Control Register
 * This register holds configuration bits for NDC.
 */
union bdk_ndcx_af_ctl
{
    uint64_t u;
    struct bdk_ndcx_af_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t en_flush_on_inval     : 1;  /**< [ 19: 19](R/W) When set, invalidate requests will flush the corresponding entry back to
                                                                 coherent memory if the entry is dirty.
                                                                 For diagnostic use only. */
        uint64_t dis_byp_on_inval_miss : 1;  /**< [ 18: 18](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, cause read miss + invalidate operations to allocate a
                                                                 cache entry, which could result in flushing a dirty entry.  When clear
                                                                 clear, read miss + invalidate operations will be treated as bypassed reads and
                                                                 will not allocate a cache entry nor initiate any flushes.  See the description
                                                                 of [DIS_INVAL_ON_BUSY] for more information about interactions between read miss
                                                                 and invalidate requests. */
        uint64_t dis_inval_on_busy     : 1;  /**< [ 17: 17](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable invalidate operations whenever the invalidate is
                                                                 requested for a Read Hit where a prior read miss to the same cache line has not
                                                                 yet been filled from coherent memory.  If the reset value of this bit is one,
                                                                 that indicated that the design does not support invalidates when an entry is
                                                                 busy (i.e., waiting for a fill to complete).  In that case, setting the bit to
                                                                 zero will have no effect. */
        uint64_t dis_inval             : 1;  /**< [ 16: 16](R/W) When one, disable all invalidate operations. For diagnostic use only. */
        uint64_t reserved_14_15        : 2;
        uint64_t dis_sync_mods         : 1;  /**< [ 13: 13](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable TBD late fixes introduced to
                                                                 resolve issues with FLR.SYNC operations.  As the design team
                                                                 adds consumers of this bit, the description will be updated. */
        uint64_t dis_unjam_w3a         : 1;  /**< [ 12: 12](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable the fix for McBuggin 36640.
                                                                 In short, the deadlock unjam mechanism will be disabled, such that
                                                                 the particular deadlock described in the bug becomes possible again;
                                                                 however, any inadvertent bug introduced by the fix could be avoided. */
        uint64_t perf_mode             : 4;  /**< [ 11:  8](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 These bits will eventually be used to limit performance
                                                                 -- in some TBD manner -- in hopes that the lower-performance
                                                                 mode(s) avoid triggering bugs fixed late in the design cycle. */
        uint64_t reserved_5_7          : 3;
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, NDC will not execute any command with lock bit set and report an error
                                                                 back to port if command has lock bit set. Unlock command is not effected by this CSR.
                                                                 When cleared NDC will process any command with lock bit set. */
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disabled. When set, all NDC's port command way select field
                                                                 is forced to all-ones. When cleared way select field is driven by the port. */
        uint64_t reserved_2            : 1;
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Hash disable. When set, the address hash function defined by NDC_AF_HASH()
                                                                 is not used.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 When set, iova \<18:15\> select the bank and \<14:13\> select the index within
                                                                 bank. */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. Software
                                                                 must not use the NDC LOCK feature. */
#else /* Word 0 - Little Endian */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. Software
                                                                 must not use the NDC LOCK feature. */
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Hash disable. When set, the address hash function defined by NDC_AF_HASH()
                                                                 is not used.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 When set, iova \<18:15\> select the bank and \<14:13\> select the index within
                                                                 bank. */
        uint64_t reserved_2            : 1;
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disabled. When set, all NDC's port command way select field
                                                                 is forced to all-ones. When cleared way select field is driven by the port. */
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, NDC will not execute any command with lock bit set and report an error
                                                                 back to port if command has lock bit set. Unlock command is not effected by this CSR.
                                                                 When cleared NDC will process any command with lock bit set. */
        uint64_t reserved_5_7          : 3;
        uint64_t perf_mode             : 4;  /**< [ 11:  8](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 These bits will eventually be used to limit performance
                                                                 -- in some TBD manner -- in hopes that the lower-performance
                                                                 mode(s) avoid triggering bugs fixed late in the design cycle. */
        uint64_t dis_unjam_w3a         : 1;  /**< [ 12: 12](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable the fix for McBuggin 36640.
                                                                 In short, the deadlock unjam mechanism will be disabled, such that
                                                                 the particular deadlock described in the bug becomes possible again;
                                                                 however, any inadvertent bug introduced by the fix could be avoided. */
        uint64_t dis_sync_mods         : 1;  /**< [ 13: 13](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable TBD late fixes introduced to
                                                                 resolve issues with FLR.SYNC operations.  As the design team
                                                                 adds consumers of this bit, the description will be updated. */
        uint64_t reserved_14_15        : 2;
        uint64_t dis_inval             : 1;  /**< [ 16: 16](R/W) When one, disable all invalidate operations. For diagnostic use only. */
        uint64_t dis_inval_on_busy     : 1;  /**< [ 17: 17](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable invalidate operations whenever the invalidate is
                                                                 requested for a Read Hit where a prior read miss to the same cache line has not
                                                                 yet been filled from coherent memory.  If the reset value of this bit is one,
                                                                 that indicated that the design does not support invalidates when an entry is
                                                                 busy (i.e., waiting for a fill to complete).  In that case, setting the bit to
                                                                 zero will have no effect. */
        uint64_t dis_byp_on_inval_miss : 1;  /**< [ 18: 18](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, cause read miss + invalidate operations to allocate a
                                                                 cache entry, which could result in flushing a dirty entry.  When clear
                                                                 clear, read miss + invalidate operations will be treated as bypassed reads and
                                                                 will not allocate a cache entry nor initiate any flushes.  See the description
                                                                 of [DIS_INVAL_ON_BUSY] for more information about interactions between read miss
                                                                 and invalidate requests. */
        uint64_t en_flush_on_inval     : 1;  /**< [ 19: 19](R/W) When set, invalidate requests will flush the corresponding entry back to
                                                                 coherent memory if the entry is dirty.
                                                                 For diagnostic use only. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_ctl_s cn9; */
    struct bdk_ndcx_af_ctl_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, NDC will not execute any command with lock bit set and report an error
                                                                 back to port if command has lock bit set. Unlock command is not effected by this CSR.
                                                                 When cleared NDC will process any command with lock bit set. */
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disabled. When set, all NDC's port command way select field
                                                                 is forced to all-ones. When cleared way select field is driven by the port. */
        uint64_t reserved_2            : 1;
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Hash disable. When set, the address hash function defined by NDC_AF_HASH()
                                                                 is not used.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 When set, iova \<18:15\> select the bank and \<14:13\> select the index within
                                                                 bank. */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. Software
                                                                 must not use the NDC LOCK feature. */
#else /* Word 0 - Little Endian */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. Software
                                                                 must not use the NDC LOCK feature. */
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Hash disable. When set, the address hash function defined by NDC_AF_HASH()
                                                                 is not used.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 When set, iova \<18:15\> select the bank and \<14:13\> select the index within
                                                                 bank. */
        uint64_t reserved_2            : 1;
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disabled. When set, all NDC's port command way select field
                                                                 is forced to all-ones. When cleared way select field is driven by the port. */
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, NDC will not execute any command with lock bit set and report an error
                                                                 back to port if command has lock bit set. Unlock command is not effected by this CSR.
                                                                 When cleared NDC will process any command with lock bit set. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_ndcx_af_ctl_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t en_flush_on_inval     : 1;  /**< [ 19: 19](R/W) When set, invalidate requests will flush the corresponding entry back to
                                                                 coherent memory if the entry is dirty.
                                                                 For diagnostic use only. */
        uint64_t dis_byp_on_inval_miss : 1;  /**< [ 18: 18](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, cause read miss + invalidate operations to allocate a
                                                                 cache entry, which could result in flushing a dirty entry.  When clear
                                                                 clear, read miss + invalidate operations will be treated as bypassed reads and
                                                                 will not allocate a cache entry nor initiate any flushes.  See the description
                                                                 of [DIS_INVAL_ON_BUSY] for more information about interactions between read miss
                                                                 and invalidate requests. */
        uint64_t dis_inval_on_busy     : 1;  /**< [ 17: 17](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable invalidate operations whenever the invalidate is
                                                                 requested for a Read Hit where a prior read miss to the same cache line has not
                                                                 yet been filled from coherent memory.  If the reset value of this bit is one,
                                                                 that indicated that the design does not support invalidates when an entry is
                                                                 busy (i.e., waiting for a fill to complete).  In that case, setting the bit to
                                                                 zero will have no effect. */
        uint64_t dis_inval             : 1;  /**< [ 16: 16](R/W) When one, disable all invalidate operations. For diagnostic use only. */
        uint64_t reserved_14_15        : 2;
        uint64_t dis_sync_mods         : 1;  /**< [ 13: 13](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable TBD late fixes introduced to
                                                                 resolve issues with FLR.SYNC operations.  As the design team
                                                                 adds consumers of this bit, the description will be updated. */
        uint64_t dis_unjam_w3a         : 1;  /**< [ 12: 12](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable the fix for McBuggin 36640.
                                                                 In short, the deadlock unjam mechanism will be disabled, such that
                                                                 the particular deadlock described in the bug becomes possible again;
                                                                 however, any inadvertent bug introduced by the fix could be avoided. */
        uint64_t perf_mode             : 4;  /**< [ 11:  8](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 These bits will eventually be used to limit performance
                                                                 -- in some TBD manner -- in hopes that the lower-performance
                                                                 mode(s) avoid triggering bugs fixed late in the design cycle. */
        uint64_t reserved_5_7          : 3;
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, NDC will not execute any command with lock bit set and report an error
                                                                 back to port if command has lock bit set. Unlock command is not effected by this CSR.
                                                                 When cleared NDC will process any command with lock bit set. */
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disable. Should be clear for normal operation.

                                                                 When clear, the way selected on a cache miss is based on the corresponding
                                                                 NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK]; if way mask bit N is clear, any of NDC
                                                                 ways 4*N through 4*N+3 may be selected, otherwise these ways are excluded
                                                                 from selection.

                                                                 When set on a cache miss with NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK] != 0xFFFF,
                                                                 NDC ignores the way mask and allows any way to be selected/allocated.

                                                                 Requests with NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK] == 0xFFFF bypass the
                                                                 NDC cache and are not affected by this bit. */
        uint64_t reserved_2            : 1;
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Hash disable. When set, the address hash function defined by NDC_AF_HASH()
                                                                 is not used.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 When set, iova \<18:15\> select the bank and \<14:13\> select the index within
                                                                 bank. */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. Software
                                                                 must not use the NDC LOCK feature. */
#else /* Word 0 - Little Endian */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. Software
                                                                 must not use the NDC LOCK feature. */
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Hash disable. When set, the address hash function defined by NDC_AF_HASH()
                                                                 is not used.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 When set, iova \<18:15\> select the bank and \<14:13\> select the index within
                                                                 bank. */
        uint64_t reserved_2            : 1;
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disable. Should be clear for normal operation.

                                                                 When clear, the way selected on a cache miss is based on the corresponding
                                                                 NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK]; if way mask bit N is clear, any of NDC
                                                                 ways 4*N through 4*N+3 may be selected, otherwise these ways are excluded
                                                                 from selection.

                                                                 When set on a cache miss with NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK] != 0xFFFF,
                                                                 NDC ignores the way mask and allows any way to be selected/allocated.

                                                                 Requests with NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK] == 0xFFFF bypass the
                                                                 NDC cache and are not affected by this bit. */
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, NDC will not execute any command with lock bit set and report an error
                                                                 back to port if command has lock bit set. Unlock command is not effected by this CSR.
                                                                 When cleared NDC will process any command with lock bit set. */
        uint64_t reserved_5_7          : 3;
        uint64_t perf_mode             : 4;  /**< [ 11:  8](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 These bits will eventually be used to limit performance
                                                                 -- in some TBD manner -- in hopes that the lower-performance
                                                                 mode(s) avoid triggering bugs fixed late in the design cycle. */
        uint64_t dis_unjam_w3a         : 1;  /**< [ 12: 12](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable the fix for McBuggin 36640.
                                                                 In short, the deadlock unjam mechanism will be disabled, such that
                                                                 the particular deadlock described in the bug becomes possible again;
                                                                 however, any inadvertent bug introduced by the fix could be avoided. */
        uint64_t dis_sync_mods         : 1;  /**< [ 13: 13](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable TBD late fixes introduced to
                                                                 resolve issues with FLR.SYNC operations.  As the design team
                                                                 adds consumers of this bit, the description will be updated. */
        uint64_t reserved_14_15        : 2;
        uint64_t dis_inval             : 1;  /**< [ 16: 16](R/W) When one, disable all invalidate operations. For diagnostic use only. */
        uint64_t dis_inval_on_busy     : 1;  /**< [ 17: 17](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, disable invalidate operations whenever the invalidate is
                                                                 requested for a Read Hit where a prior read miss to the same cache line has not
                                                                 yet been filled from coherent memory.  If the reset value of this bit is one,
                                                                 that indicated that the design does not support invalidates when an entry is
                                                                 busy (i.e., waiting for a fill to complete).  In that case, setting the bit to
                                                                 zero will have no effect. */
        uint64_t dis_byp_on_inval_miss : 1;  /**< [ 18: 18](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 When set, cause read miss + invalidate operations to allocate a
                                                                 cache entry, which could result in flushing a dirty entry.  When clear
                                                                 clear, read miss + invalidate operations will be treated as bypassed reads and
                                                                 will not allocate a cache entry nor initiate any flushes.  See the description
                                                                 of [DIS_INVAL_ON_BUSY] for more information about interactions between read miss
                                                                 and invalidate requests. */
        uint64_t en_flush_on_inval     : 1;  /**< [ 19: 19](R/W) When set, invalidate requests will flush the corresponding entry back to
                                                                 coherent memory if the entry is dirty.
                                                                 For diagnostic use only. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_ndcx_af_ctl_cn96xxp3 cn98xx; */
    /* struct bdk_ndcx_af_ctl_cn96xxp1 cnf95xxp1; */
    struct bdk_ndcx_af_ctl_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t dis_sync_mods         : 1;  /**< [ 13: 13](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 Setting this bit will disable TBD late fixes introduced to
                                                                 resolve issues with FLR.SYNC operations.  As the design team
                                                                 adds consumers of this bit, the description will be updated. */
        uint64_t dis_unjam_w3a         : 1;  /**< [ 12: 12](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 "Setting this bit will disable the fix for McBuggin #36640.
                                                                 In short, the deadlock unjam mechanism will be disabled, such that
                                                                 the particular deadlock described in the bug becomes possible again;
                                                                 however, any inadvertent bug introduced by the fix could be avoided." */
        uint64_t perf_mode             : 4;  /**< [ 11:  8](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 These bits will eventually be used to limit performance
                                                                 -- in some TBD manner -- in hopes that the lower-performance
                                                                 mode(s) avoid triggering bugs fixed late in the design cycle. */
        uint64_t reserved_5_7          : 3;
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, NDC will not execute any command with lock bit set and report an error
                                                                 back to port if command has lock bit set. Unlock command is not effected by this CSR.
                                                                 When cleared NDC will process any command with lock bit set. */
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disable. Should be clear for normal operation.

                                                                 When clear, the way selected on a cache miss is based on the corresponding
                                                                 NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK]; if way mask bit N is clear, any of NDC
                                                                 ways 4*N through 4*N+3 may be selected, otherwise these ways are excluded
                                                                 from selection.

                                                                 When set on a cache miss with NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK] != 0xFFFF,
                                                                 NDC ignores the way mask and allows any way to be selected/allocated.

                                                                 Requests with NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK] == 0xFFFF bypass the
                                                                 NDC cache and are not affected by this bit. */
        uint64_t reserved_2            : 1;
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Hash disable. When set, the address hash function defined by NDC_AF_HASH()
                                                                 is not used.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 When set, iova \<18:15\> select the bank and \<14:13\> select the index within
                                                                 bank. */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. Software
                                                                 must not use the NDC LOCK feature. */
#else /* Word 0 - Little Endian */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. Software
                                                                 must not use the NDC LOCK feature. */
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Hash disable. When set, the address hash function defined by NDC_AF_HASH()
                                                                 is not used.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 When set, iova \<18:15\> select the bank and \<14:13\> select the index within
                                                                 bank. */
        uint64_t reserved_2            : 1;
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disable. Should be clear for normal operation.

                                                                 When clear, the way selected on a cache miss is based on the corresponding
                                                                 NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK]; if way mask bit N is clear, any of NDC
                                                                 ways 4*N through 4*N+3 may be selected, otherwise these ways are excluded
                                                                 from selection.

                                                                 When set on a cache miss with NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK] != 0xFFFF,
                                                                 NDC ignores the way mask and allows any way to be selected/allocated.

                                                                 Requests with NIX_*[*WAY_MASK]/NPA_*[*WAY_MASK] == 0xFFFF bypass the
                                                                 NDC cache and are not affected by this bit. */
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, NDC will not execute any command with lock bit set and report an error
                                                                 back to port if command has lock bit set. Unlock command is not effected by this CSR.
                                                                 When cleared NDC will process any command with lock bit set. */
        uint64_t reserved_5_7          : 3;
        uint64_t perf_mode             : 4;  /**< [ 11:  8](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 These bits will eventually be used to limit performance
                                                                 -- in some TBD manner -- in hopes that the lower-performance
                                                                 mode(s) avoid triggering bugs fixed late in the design cycle. */
        uint64_t dis_unjam_w3a         : 1;  /**< [ 12: 12](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 "Setting this bit will disable the fix for McBuggin #36640.
                                                                 In short, the deadlock unjam mechanism will be disabled, such that
                                                                 the particular deadlock described in the bug becomes possible again;
                                                                 however, any inadvertent bug introduced by the fix could be avoided." */
        uint64_t dis_sync_mods         : 1;  /**< [ 13: 13](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 Setting this bit will disable TBD late fixes introduced to
                                                                 resolve issues with FLR.SYNC operations.  As the design team
                                                                 adds consumers of this bit, the description will be updated. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_ndcx_af_ctl_cn96xxp3 loki; */
};
typedef union bdk_ndcx_af_ctl bdk_ndcx_af_ctl_t;

static inline uint64_t BDK_NDCX_AF_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000030ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000030ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000030ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000030ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000030ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_CTL(a) bdk_ndcx_af_ctl_t
#define bustype_BDK_NDCX_AF_CTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_CTL(a) "NDCX_AF_CTL"
#define device_bar_BDK_NDCX_AF_CTL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_CTL(a) (a)
#define arguments_BDK_NDCX_AF_CTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_eco
 *
 * INTERNAL: NDC ECO Register
 */
union bdk_ndcx_af_eco
{
    uint64_t u;
    struct bdk_ndcx_af_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_eco_s cn; */
};
typedef union bdk_ndcx_af_eco bdk_ndcx_af_eco_t;

static inline uint64_t BDK_NDCX_AF_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000010ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000010ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000010ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000010ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000010ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_ECO(a) bdk_ndcx_af_eco_t
#define bustype_BDK_NDCX_AF_ECO(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_ECO(a) "NDCX_AF_ECO"
#define device_bar_BDK_NDCX_AF_ECO(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_ECO(a) (a)
#define arguments_BDK_NDCX_AF_ECO(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_hash#
 *
 * NDC Hash Registers
 */
union bdk_ndcx_af_hashx
{
    uint64_t u;
    struct bdk_ndcx_af_hashx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t ena                   : 62; /**< [ 61:  0](R/W) Enable for each address and stream ID bit that is to participate in the
                                                                 XORs for the corresponding hash bit's computation: 1 means participate, 0
                                                                 means do not participate.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 Usage:
                                                                 _ \<61:59\> = unused.
                                                                 _ \<58:46\> = streamID\<12:0\>.
                                                                 _ \<45:0\> = iova\<52:7\>.

                                                                 NDC_AF_HASH(3..0) select the bank and NDC_AF_HASH(5..4) select the index within
                                                                 bank.

                                                                 The reset hash value for each register is:
                                                                 _ NDC_AF_HASH(0)[ENA] = 0x03731d7ed10b2a4e.
                                                                 _ NDC_AF_HASH(1)[ENA] = 0x05952783731d7ed3.
                                                                 _ NDC_AF_HASH(2)[ENA] = 0x085952783731d7e9.
                                                                 _ NDC_AF_HASH(3)[ENA] = 0x10b2a4f06e63afd2.
                                                                 _ NDC_AF_HASH(4)[ENA] = 0x216549e0dcc75fa4.
                                                                 _ NDC_AF_HASH(5)[ENA] = 0x41b98ebf68859507.

                                                                 The default/reset hash ensures that:
                                                                 * The 16 cache lines of any naturally aligned 2KB block are evenly
                                                                 distributed among the 16 banks.
                                                                 * The 64 cache lines of any naturally aligned 8KB block (64 cache lines)
                                                                 are evenly distributed among the 64 indices. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 62; /**< [ 61:  0](R/W) Enable for each address and stream ID bit that is to participate in the
                                                                 XORs for the corresponding hash bit's computation: 1 means participate, 0
                                                                 means do not participate.

                                                                 For diagnostic use only. May only be modified when NDC is idle and has no
                                                                 cached data.

                                                                 Internal:
                                                                 Usage:
                                                                 _ \<61:59\> = unused.
                                                                 _ \<58:46\> = streamID\<12:0\>.
                                                                 _ \<45:0\> = iova\<52:7\>.

                                                                 NDC_AF_HASH(3..0) select the bank and NDC_AF_HASH(5..4) select the index within
                                                                 bank.

                                                                 The reset hash value for each register is:
                                                                 _ NDC_AF_HASH(0)[ENA] = 0x03731d7ed10b2a4e.
                                                                 _ NDC_AF_HASH(1)[ENA] = 0x05952783731d7ed3.
                                                                 _ NDC_AF_HASH(2)[ENA] = 0x085952783731d7e9.
                                                                 _ NDC_AF_HASH(3)[ENA] = 0x10b2a4f06e63afd2.
                                                                 _ NDC_AF_HASH(4)[ENA] = 0x216549e0dcc75fa4.
                                                                 _ NDC_AF_HASH(5)[ENA] = 0x41b98ebf68859507.

                                                                 The default/reset hash ensures that:
                                                                 * The 16 cache lines of any naturally aligned 2KB block are evenly
                                                                 distributed among the 16 banks.
                                                                 * The 64 cache lines of any naturally aligned 8KB block (64 cache lines)
                                                                 are evenly distributed among the 64 indices. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_hashx_s cn; */
};
typedef union bdk_ndcx_af_hashx bdk_ndcx_af_hashx_t;

static inline uint64_t BDK_NDCX_AF_HASHX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_HASHX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=5)))
        return 0x8400c0000300ll + 0x10000000ll * ((a) & 0x3) + 8ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=5)))
        return 0x8400c0000300ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=5)))
        return 0x8400c0000300ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=5)))
        return 0x8400c0000300ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=5)))
        return 0x8400c0000300ll + 0x10000000ll * ((a) & 0x7) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("NDCX_AF_HASHX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_HASHX(a,b) bdk_ndcx_af_hashx_t
#define bustype_BDK_NDCX_AF_HASHX(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_HASHX(a,b) "NDCX_AF_HASHX"
#define device_bar_BDK_NDCX_AF_HASHX(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_HASHX(a,b) (a)
#define arguments_BDK_NDCX_AF_HASHX(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_intr
 *
 * NDC AF Interrupt Register
 */
union bdk_ndcx_af_intr
{
    uint64_t u;
    struct bdk_ndcx_af_intr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t allocate_error        : 16; /**< [ 47: 32](R/W1C/H) Allocation interrupt. Each bit corresponds to banks 15..0 respectively. If set,
                                                                 bank couldn't allocate a way since all ways were locked for a given way select. */
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1C/H) Interrupt bit per bank. Each bit corresponds to banks 15..0 respectively.
                                                                 If set, bank got a global FLR.flr request from port for a line that had busy bit set.
                                                                 Software must request FLR.flr only if all matching lines are quiesced. */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1C/H) Interrupt bit per bank. Each bit corresponds to banks 15..0 respectively. If
                                                                 set, bank got a store fault error when writing a line back to LLC/DRAM. */
#else /* Word 0 - Little Endian */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1C/H) Interrupt bit per bank. Each bit corresponds to banks 15..0 respectively. If
                                                                 set, bank got a store fault error when writing a line back to LLC/DRAM. */
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1C/H) Interrupt bit per bank. Each bit corresponds to banks 15..0 respectively.
                                                                 If set, bank got a global FLR.flr request from port for a line that had busy bit set.
                                                                 Software must request FLR.flr only if all matching lines are quiesced. */
        uint64_t allocate_error        : 16; /**< [ 47: 32](R/W1C/H) Allocation interrupt. Each bit corresponds to banks 15..0 respectively. If set,
                                                                 bank couldn't allocate a way since all ways were locked for a given way select. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_intr_s cn; */
};
typedef union bdk_ndcx_af_intr bdk_ndcx_af_intr_t;

static inline uint64_t BDK_NDCX_AF_INTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_INTR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000058ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000058ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000058ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000058ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000058ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_INTR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_INTR(a) bdk_ndcx_af_intr_t
#define bustype_BDK_NDCX_AF_INTR(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_INTR(a) "NDCX_AF_INTR"
#define device_bar_BDK_NDCX_AF_INTR(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_INTR(a) (a)
#define arguments_BDK_NDCX_AF_INTR(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_intr_ena_w1c
 *
 * NDC AF Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_ndcx_af_intr_ena_w1c
{
    uint64_t u;
    struct bdk_ndcx_af_intr_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t allocate_error        : 16; /**< [ 47: 32](R/W1C/H) Reads or clears enable for NDC_AF_INTR[ALLOCATE_ERROR]. */
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1C/H) Reads or clears enable for NDC_AF_INTR[FLR_AND_BUSY_ERROR]. */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1C/H) Reads or clears enable for NDC_AF_INTR[FLUSH_ERROR]. */
#else /* Word 0 - Little Endian */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1C/H) Reads or clears enable for NDC_AF_INTR[FLUSH_ERROR]. */
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1C/H) Reads or clears enable for NDC_AF_INTR[FLR_AND_BUSY_ERROR]. */
        uint64_t allocate_error        : 16; /**< [ 47: 32](R/W1C/H) Reads or clears enable for NDC_AF_INTR[ALLOCATE_ERROR]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_intr_ena_w1c_s cn; */
};
typedef union bdk_ndcx_af_intr_ena_w1c bdk_ndcx_af_intr_ena_w1c_t;

static inline uint64_t BDK_NDCX_AF_INTR_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_INTR_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000070ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000070ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000070ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000070ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000070ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_INTR_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_INTR_ENA_W1C(a) bdk_ndcx_af_intr_ena_w1c_t
#define bustype_BDK_NDCX_AF_INTR_ENA_W1C(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_INTR_ENA_W1C(a) "NDCX_AF_INTR_ENA_W1C"
#define device_bar_BDK_NDCX_AF_INTR_ENA_W1C(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_INTR_ENA_W1C(a) (a)
#define arguments_BDK_NDCX_AF_INTR_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_intr_ena_w1s
 *
 * NDC AF Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_ndcx_af_intr_ena_w1s
{
    uint64_t u;
    struct bdk_ndcx_af_intr_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t allocate_error        : 16; /**< [ 47: 32](R/W1S/H) Reads or sets enable for NDC_AF_INTR[ALLOCATE_ERROR]. */
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1S/H) Reads or sets enable for NDC_AF_INTR[FLR_AND_BUSY_ERROR]. */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1S/H) Reads or sets enable for NDC_AF_INTR[FLUSH_ERROR]. */
#else /* Word 0 - Little Endian */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1S/H) Reads or sets enable for NDC_AF_INTR[FLUSH_ERROR]. */
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1S/H) Reads or sets enable for NDC_AF_INTR[FLR_AND_BUSY_ERROR]. */
        uint64_t allocate_error        : 16; /**< [ 47: 32](R/W1S/H) Reads or sets enable for NDC_AF_INTR[ALLOCATE_ERROR]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_intr_ena_w1s_s cn; */
};
typedef union bdk_ndcx_af_intr_ena_w1s bdk_ndcx_af_intr_ena_w1s_t;

static inline uint64_t BDK_NDCX_AF_INTR_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_INTR_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000068ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000068ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000068ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000068ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000068ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_INTR_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_INTR_ENA_W1S(a) bdk_ndcx_af_intr_ena_w1s_t
#define bustype_BDK_NDCX_AF_INTR_ENA_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_INTR_ENA_W1S(a) "NDCX_AF_INTR_ENA_W1S"
#define device_bar_BDK_NDCX_AF_INTR_ENA_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_INTR_ENA_W1S(a) (a)
#define arguments_BDK_NDCX_AF_INTR_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_intr_w1s
 *
 * NDC AF Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_ndcx_af_intr_w1s
{
    uint64_t u;
    struct bdk_ndcx_af_intr_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t allocate_error        : 16; /**< [ 47: 32](R/W1S/H) Reads or sets NDC_AF_INTR[ALLOCATE_ERROR]. */
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1S/H) Reads or sets NDC_AF_INTR[FLR_AND_BUSY_ERROR]. */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1S/H) Reads or sets NDC_AF_INTR[FLUSH_ERROR]. */
#else /* Word 0 - Little Endian */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1S/H) Reads or sets NDC_AF_INTR[FLUSH_ERROR]. */
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1S/H) Reads or sets NDC_AF_INTR[FLR_AND_BUSY_ERROR]. */
        uint64_t allocate_error        : 16; /**< [ 47: 32](R/W1S/H) Reads or sets NDC_AF_INTR[ALLOCATE_ERROR]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_intr_w1s_s cn; */
};
typedef union bdk_ndcx_af_intr_w1s bdk_ndcx_af_intr_w1s_t;

static inline uint64_t BDK_NDCX_AF_INTR_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_INTR_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000060ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000060ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000060ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000060ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000060ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_INTR_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_INTR_W1S(a) bdk_ndcx_af_intr_w1s_t
#define bustype_BDK_NDCX_AF_INTR_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_INTR_W1S(a) "NDCX_AF_INTR_W1S"
#define device_bar_BDK_NDCX_AF_INTR_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_INTR_W1S(a) (a)
#define arguments_BDK_NDCX_AF_INTR_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_port#_busy_rd_pc
 *
 * NDC AF Per-port invalidate Performance Counter Registers
 */
union bdk_ndcx_af_portx_busy_rd_pc
{
    uint64_t u;
    struct bdk_ndcx_af_portx_busy_rd_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Per-port counters tracking read hit references that must wait for an already-
                                                                 launched read fetch to return over NCB. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Per-port counters tracking read hit references that must wait for an already-
                                                                 launched read fetch to return over NCB. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_portx_busy_rd_pc_s cn; */
};
typedef union bdk_ndcx_af_portx_busy_rd_pc bdk_ndcx_af_portx_busy_rd_pc_t;

static inline uint64_t BDK_NDCX_AF_PORTX_BUSY_RD_PC(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_PORTX_BUSY_RD_PC(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=5)))
        return 0x8400c0001318ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=5)))
        return 0x8400c0001318ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=5)))
        return 0x8400c0001318ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7);
    __bdk_csr_fatal("NDCX_AF_PORTX_BUSY_RD_PC", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_PORTX_BUSY_RD_PC(a,b) bdk_ndcx_af_portx_busy_rd_pc_t
#define bustype_BDK_NDCX_AF_PORTX_BUSY_RD_PC(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_PORTX_BUSY_RD_PC(a,b) "NDCX_AF_PORTX_BUSY_RD_PC"
#define device_bar_BDK_NDCX_AF_PORTX_BUSY_RD_PC(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_PORTX_BUSY_RD_PC(a,b) (a)
#define arguments_BDK_NDCX_AF_PORTX_BUSY_RD_PC(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_port#_hm#_rw#_req_pc
 *
 * NDC AF Per-port hit/miss Performance Counter Registers
 */
union bdk_ndcx_af_portx_hmx_rwx_req_pc
{
    uint64_t u;
    struct bdk_ndcx_af_portx_hmx_rwx_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Per-port counters tracking references that hit or allocated.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ HM(0) registers increment on requests that hit in the cache.
                                                                   _ HM(1) registers increment on requests that caused a cache allocation.
                                                                   _ RW(0) registers increment on read  transaction entering NDC on given request port.
                                                                   _ RW(1) registers increment on write transaction entering NDC on given request port.

                                                                 Note that requests treated as bypass. All partial write misses or any
                                                                 reference that cannot allocate a new cache line may be counted in
                                                                 NDC_AF_PORT()_RT(1)_RW()_REQ_PC and NDC_AF_PORT()_RW()_CANT_ALLOC_PC. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Per-port counters tracking references that hit or allocated.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ HM(0) registers increment on requests that hit in the cache.
                                                                   _ HM(1) registers increment on requests that caused a cache allocation.
                                                                   _ RW(0) registers increment on read  transaction entering NDC on given request port.
                                                                   _ RW(1) registers increment on write transaction entering NDC on given request port.

                                                                 Note that requests treated as bypass. All partial write misses or any
                                                                 reference that cannot allocate a new cache line may be counted in
                                                                 NDC_AF_PORT()_RT(1)_RW()_REQ_PC and NDC_AF_PORT()_RW()_CANT_ALLOC_PC. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_portx_hmx_rwx_req_pc_s cn; */
};
typedef union bdk_ndcx_af_portx_hmx_rwx_req_pc bdk_ndcx_af_portx_hmx_rwx_req_pc_t;

static inline uint64_t BDK_NDCX_AF_PORTX_HMX_RWX_REQ_PC(unsigned long a, unsigned long b, unsigned long c, unsigned long d) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_PORTX_HMX_RWX_REQ_PC(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0001200ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0001200ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0001200ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    __bdk_csr_fatal("NDCX_AF_PORTX_HMX_RWX_REQ_PC", 4, a, b, c, d, 0, 0);
}

#define typedef_BDK_NDCX_AF_PORTX_HMX_RWX_REQ_PC(a,b,c,d) bdk_ndcx_af_portx_hmx_rwx_req_pc_t
#define bustype_BDK_NDCX_AF_PORTX_HMX_RWX_REQ_PC(a,b,c,d) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_PORTX_HMX_RWX_REQ_PC(a,b,c,d) "NDCX_AF_PORTX_HMX_RWX_REQ_PC"
#define device_bar_BDK_NDCX_AF_PORTX_HMX_RWX_REQ_PC(a,b,c,d) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_PORTX_HMX_RWX_REQ_PC(a,b,c,d) (a)
#define arguments_BDK_NDCX_AF_PORTX_HMX_RWX_REQ_PC(a,b,c,d) (a),(b),(c),(d)

/**
 * Register (RVU_PF_BAR0) ndc#_af_port#_it#_inval_pc
 *
 * NDC AF Per-port invalidate Performance Counter Registers
 */
union bdk_ndcx_af_portx_itx_inval_pc
{
    uint64_t u;
    struct bdk_ndcx_af_portx_itx_inval_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Per-port counters tracking invalidate references.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ IT(0..2) is enumerated by NDC_INVAL_RES_E. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Per-port counters tracking invalidate references.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ IT(0..2) is enumerated by NDC_INVAL_RES_E. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_portx_itx_inval_pc_s cn; */
};
typedef union bdk_ndcx_af_portx_itx_inval_pc bdk_ndcx_af_portx_itx_inval_pc_t;

static inline uint64_t BDK_NDCX_AF_PORTX_ITX_INVAL_PC(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_PORTX_ITX_INVAL_PC(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=5) && (c<=2)))
        return 0x8400c0001300ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=5) && (c<=2)))
        return 0x8400c0001300ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=5) && (c<=2)))
        return 0x8400c0001300ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("NDCX_AF_PORTX_ITX_INVAL_PC", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_PORTX_ITX_INVAL_PC(a,b,c) bdk_ndcx_af_portx_itx_inval_pc_t
#define bustype_BDK_NDCX_AF_PORTX_ITX_INVAL_PC(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_PORTX_ITX_INVAL_PC(a,b,c) "NDCX_AF_PORTX_ITX_INVAL_PC"
#define device_bar_BDK_NDCX_AF_PORTX_ITX_INVAL_PC(a,b,c) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_PORTX_ITX_INVAL_PC(a,b,c) (a)
#define arguments_BDK_NDCX_AF_PORTX_ITX_INVAL_PC(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_port#_rt#_rw#_lat_pc
 *
 * NDC AF Per-port Latency Performance Counter Registers
 */
union bdk_ndcx_af_portx_rtx_rwx_lat_pc
{
    uint64_t u;
    struct bdk_ndcx_af_portx_rtx_rwx_lat_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Latency performance counter. This counter should be divided by
                                                                 NDC_AF_PORT()_RT()_RW()_REQ_PC to determine each port's average read and write
                                                                 latency.

                                                                 The register index indicates the type of request that is counted:

                                                                   _ RT(0..1) is enumerated by NDC_CTYPE_E.

                                                                   _ RW(0) increments every cycle by the number of read transactions
                                                                   that have entered NDC from the given request port, but have not
                                                                   returned read data to the device.

                                                                   _ RW(1) increments every cycle by the number of write
                                                                   transactions that have entered NDC from the given request port,
                                                                   but have not returned write commits to the device. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Latency performance counter. This counter should be divided by
                                                                 NDC_AF_PORT()_RT()_RW()_REQ_PC to determine each port's average read and write
                                                                 latency.

                                                                 The register index indicates the type of request that is counted:

                                                                   _ RT(0..1) is enumerated by NDC_CTYPE_E.

                                                                   _ RW(0) increments every cycle by the number of read transactions
                                                                   that have entered NDC from the given request port, but have not
                                                                   returned read data to the device.

                                                                   _ RW(1) increments every cycle by the number of write
                                                                   transactions that have entered NDC from the given request port,
                                                                   but have not returned write commits to the device. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_portx_rtx_rwx_lat_pc_s cn; */
};
typedef union bdk_ndcx_af_portx_rtx_rwx_lat_pc bdk_ndcx_af_portx_rtx_rwx_lat_pc_t;

static inline uint64_t BDK_NDCX_AF_PORTX_RTX_RWX_LAT_PC(unsigned long a, unsigned long b, unsigned long c, unsigned long d) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_PORTX_RTX_RWX_LAT_PC(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000e00ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000e00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000e00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000e00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000e00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    __bdk_csr_fatal("NDCX_AF_PORTX_RTX_RWX_LAT_PC", 4, a, b, c, d, 0, 0);
}

#define typedef_BDK_NDCX_AF_PORTX_RTX_RWX_LAT_PC(a,b,c,d) bdk_ndcx_af_portx_rtx_rwx_lat_pc_t
#define bustype_BDK_NDCX_AF_PORTX_RTX_RWX_LAT_PC(a,b,c,d) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_PORTX_RTX_RWX_LAT_PC(a,b,c,d) "NDCX_AF_PORTX_RTX_RWX_LAT_PC"
#define device_bar_BDK_NDCX_AF_PORTX_RTX_RWX_LAT_PC(a,b,c,d) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_PORTX_RTX_RWX_LAT_PC(a,b,c,d) (a)
#define arguments_BDK_NDCX_AF_PORTX_RTX_RWX_LAT_PC(a,b,c,d) (a),(b),(c),(d)

/**
 * Register (RVU_PF_BAR0) ndc#_af_port#_rt#_rw#_ostdn_pc
 *
 * NDC AF Per-port Outstanding Requests Performance Counter Registers
 */
union bdk_ndcx_af_portx_rtx_rwx_ostdn_pc
{
    uint64_t u;
    struct bdk_ndcx_af_portx_rtx_rwx_ostdn_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Outstanding requests performance counter.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ RT(0..1) is enumerated by NDC_CTYPE_E.
                                                                   _ RW(0) registers increments on read  transaction entering NDC on given request port.
                                                                   _ RW(1) registers increments on write transaction entering NDC on given request port. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Outstanding requests performance counter.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ RT(0..1) is enumerated by NDC_CTYPE_E.
                                                                   _ RW(0) registers increments on read  transaction entering NDC on given request port.
                                                                   _ RW(1) registers increments on write transaction entering NDC on given request port. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_portx_rtx_rwx_ostdn_pc_s cn; */
};
typedef union bdk_ndcx_af_portx_rtx_rwx_ostdn_pc bdk_ndcx_af_portx_rtx_rwx_ostdn_pc_t;

static inline uint64_t BDK_NDCX_AF_PORTX_RTX_RWX_OSTDN_PC(unsigned long a, unsigned long b, unsigned long c, unsigned long d) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_PORTX_RTX_RWX_OSTDN_PC(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000d00ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000d00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000d00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000d00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000d00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    __bdk_csr_fatal("NDCX_AF_PORTX_RTX_RWX_OSTDN_PC", 4, a, b, c, d, 0, 0);
}

#define typedef_BDK_NDCX_AF_PORTX_RTX_RWX_OSTDN_PC(a,b,c,d) bdk_ndcx_af_portx_rtx_rwx_ostdn_pc_t
#define bustype_BDK_NDCX_AF_PORTX_RTX_RWX_OSTDN_PC(a,b,c,d) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_PORTX_RTX_RWX_OSTDN_PC(a,b,c,d) "NDCX_AF_PORTX_RTX_RWX_OSTDN_PC"
#define device_bar_BDK_NDCX_AF_PORTX_RTX_RWX_OSTDN_PC(a,b,c,d) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_PORTX_RTX_RWX_OSTDN_PC(a,b,c,d) (a)
#define arguments_BDK_NDCX_AF_PORTX_RTX_RWX_OSTDN_PC(a,b,c,d) (a),(b),(c),(d)

/**
 * Register (RVU_PF_BAR0) ndc#_af_port#_rt#_rw#_req_pc
 *
 * NDC AF Per-port Request Performance Counter Registers
 */
union bdk_ndcx_af_portx_rtx_rwx_req_pc
{
    uint64_t u;
    struct bdk_ndcx_af_portx_rtx_rwx_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Request performance counter.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ RT(0..1) is enumerated by NDC_CTYPE_E.
                                                                   _ RW(0) registers increments on read  transaction entering NDC on given request port.
                                                                   _ RW(1) registers increments on write transaction entering NDC on given request port. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Request performance counter.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ RT(0..1) is enumerated by NDC_CTYPE_E.
                                                                   _ RW(0) registers increments on read  transaction entering NDC on given request port.
                                                                   _ RW(1) registers increments on write transaction entering NDC on given request port. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_portx_rtx_rwx_req_pc_s cn; */
};
typedef union bdk_ndcx_af_portx_rtx_rwx_req_pc bdk_ndcx_af_portx_rtx_rwx_req_pc_t;

static inline uint64_t BDK_NDCX_AF_PORTX_RTX_RWX_REQ_PC(unsigned long a, unsigned long b, unsigned long c, unsigned long d) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_PORTX_RTX_RWX_REQ_PC(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000c00ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000c00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000c00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000c00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=5) && (c<=1) && (d<=1)))
        return 0x8400c0000c00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1) + 8ll * ((d) & 0x1);
    __bdk_csr_fatal("NDCX_AF_PORTX_RTX_RWX_REQ_PC", 4, a, b, c, d, 0, 0);
}

#define typedef_BDK_NDCX_AF_PORTX_RTX_RWX_REQ_PC(a,b,c,d) bdk_ndcx_af_portx_rtx_rwx_req_pc_t
#define bustype_BDK_NDCX_AF_PORTX_RTX_RWX_REQ_PC(a,b,c,d) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_PORTX_RTX_RWX_REQ_PC(a,b,c,d) "NDCX_AF_PORTX_RTX_RWX_REQ_PC"
#define device_bar_BDK_NDCX_AF_PORTX_RTX_RWX_REQ_PC(a,b,c,d) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_PORTX_RTX_RWX_REQ_PC(a,b,c,d) (a)
#define arguments_BDK_NDCX_AF_PORTX_RTX_RWX_REQ_PC(a,b,c,d) (a),(b),(c),(d)

/**
 * Register (RVU_PF_BAR0) ndc#_af_port#_rw#_cant_alloc_pc
 *
 * NDC AF Per-port Write/Read Can't Allocate Performance Counter Registers
 */
union bdk_ndcx_af_portx_rwx_cant_alloc_pc
{
    uint64_t u;
    struct bdk_ndcx_af_portx_rwx_cant_alloc_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Cache write/read can't allocate performance counter.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ RW(0) registers increments on read  transaction cache can't allocate.
                                                                   _ RW(1) registers increments on write transaction cache can't allocate.

                                                                 Note that:
                                                                   * NDC can't cache allocate writes if it's partial write that is a miss in cache or if
                                                                   all ways are locked.
                                                                   * NDC can't cache allocate reads if all ways are locked.
                                                                   * Requests that NDC can't allocate are converted to bypass requests.
                                                                   * Up until NDC decides it can't allocate, the response latency will be counted as cache latency,
                                                                 once cache made such decision it will update NDC_AF_PORT()_RT()_RW()_REQ_PC and
                                                                 NDC_AF_PORT()_RT()_RW()_OSTDN_PC to minimize inaccuracy of
                                                                 NDC_AF_PORT()_RT()_RW()_LAT_PC registers. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Cache write/read can't allocate performance counter.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ RW(0) registers increments on read  transaction cache can't allocate.
                                                                   _ RW(1) registers increments on write transaction cache can't allocate.

                                                                 Note that:
                                                                   * NDC can't cache allocate writes if it's partial write that is a miss in cache or if
                                                                   all ways are locked.
                                                                   * NDC can't cache allocate reads if all ways are locked.
                                                                   * Requests that NDC can't allocate are converted to bypass requests.
                                                                   * Up until NDC decides it can't allocate, the response latency will be counted as cache latency,
                                                                 once cache made such decision it will update NDC_AF_PORT()_RT()_RW()_REQ_PC and
                                                                 NDC_AF_PORT()_RT()_RW()_OSTDN_PC to minimize inaccuracy of
                                                                 NDC_AF_PORT()_RT()_RW()_LAT_PC registers. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_portx_rwx_cant_alloc_pc_s cn; */
};
typedef union bdk_ndcx_af_portx_rwx_cant_alloc_pc bdk_ndcx_af_portx_rwx_cant_alloc_pc_t;

static inline uint64_t BDK_NDCX_AF_PORTX_RWX_CANT_ALLOC_PC(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_PORTX_RWX_CANT_ALLOC_PC(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && ((a<=2) && (b<=5) && (c<=1)))
        return 0x8400c0000f00ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=5) && (c<=1)))
        return 0x8400c0000f00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=5) && (c<=1)))
        return 0x8400c0000f00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=5) && (b<=5) && (c<=1)))
        return 0x8400c0000f00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=5) && (c<=1)))
        return 0x8400c0000f00ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1);
    __bdk_csr_fatal("NDCX_AF_PORTX_RWX_CANT_ALLOC_PC", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_PORTX_RWX_CANT_ALLOC_PC(a,b,c) bdk_ndcx_af_portx_rwx_cant_alloc_pc_t
#define bustype_BDK_NDCX_AF_PORTX_RWX_CANT_ALLOC_PC(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_PORTX_RWX_CANT_ALLOC_PC(a,b,c) "NDCX_AF_PORTX_RWX_CANT_ALLOC_PC"
#define device_bar_BDK_NDCX_AF_PORTX_RWX_CANT_ALLOC_PC(a,b,c) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_PORTX_RWX_CANT_ALLOC_PC(a,b,c) (a)
#define arguments_BDK_NDCX_AF_PORTX_RWX_CANT_ALLOC_PC(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_port#_rw#_flush_pc
 *
 * NDC AF Per-port Flush Performance Counter Registers
 */
union bdk_ndcx_af_portx_rwx_flush_pc
{
    uint64_t u;
    struct bdk_ndcx_af_portx_rwx_flush_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Per-port counters tracking dirty lines flushed by new cacheline allocations.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ RW(0) registers increment on flushes caused by read  transactions entering
                                                                 NDC on given request port.
                                                                   _ RW(1) registers increment on flushes caused by write transactions entering
                                                                 NDC on given request port. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Per-port counters tracking dirty lines flushed by new cacheline allocations.

                                                                 The register index indicates the type of request that is counted:
                                                                   _ RW(0) registers increment on flushes caused by read  transactions entering
                                                                 NDC on given request port.
                                                                   _ RW(1) registers increment on flushes caused by write transactions entering
                                                                 NDC on given request port. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_portx_rwx_flush_pc_s cn; */
};
typedef union bdk_ndcx_af_portx_rwx_flush_pc bdk_ndcx_af_portx_rwx_flush_pc_t;

static inline uint64_t BDK_NDCX_AF_PORTX_RWX_FLUSH_PC(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_PORTX_RWX_FLUSH_PC(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && ((a<=5) && (b<=5) && (c<=1)))
        return 0x8400c0001400ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=5) && (c<=1)))
        return 0x8400c0001400ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=5) && (b<=5) && (c<=1)))
        return 0x8400c0001400ll + 0x10000000ll * ((a) & 0x7) + 0x20ll * ((b) & 0x7) + 0x10ll * ((c) & 0x1);
    __bdk_csr_fatal("NDCX_AF_PORTX_RWX_FLUSH_PC", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_PORTX_RWX_FLUSH_PC(a,b,c) bdk_ndcx_af_portx_rwx_flush_pc_t
#define bustype_BDK_NDCX_AF_PORTX_RWX_FLUSH_PC(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_PORTX_RWX_FLUSH_PC(a,b,c) "NDCX_AF_PORTX_RWX_FLUSH_PC"
#define device_bar_BDK_NDCX_AF_PORTX_RWX_FLUSH_PC(a,b,c) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_PORTX_RWX_FLUSH_PC(a,b,c) (a)
#define arguments_BDK_NDCX_AF_PORTX_RWX_FLUSH_PC(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_scratch
 *
 * INTERNAL: NDC Scratch Register
 */
union bdk_ndcx_af_scratch
{
    uint64_t u;
    struct bdk_ndcx_af_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t scratch               : 64; /**< [ 63:  0](R/W) Reserved for DV usage. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 64; /**< [ 63:  0](R/W) Reserved for DV usage. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_scratch_s cn; */
};
typedef union bdk_ndcx_af_scratch bdk_ndcx_af_scratch_t;

static inline uint64_t BDK_NDCX_AF_SCRATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_SCRATCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c0000018ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c0000018ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c0000018ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c0000018ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c0000018ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_AF_SCRATCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_SCRATCH(a) bdk_ndcx_af_scratch_t
#define bustype_BDK_NDCX_AF_SCRATCH(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_SCRATCH(a) "NDCX_AF_SCRATCH"
#define device_bar_BDK_NDCX_AF_SCRATCH(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_AF_SCRATCH(a) (a)
#define arguments_BDK_NDCX_AF_SCRATCH(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_priv_af_int_cfg
 *
 * NDC AF Interrupt Configuration Registers
 */
union bdk_ndcx_priv_af_int_cfg
{
    uint64_t u;
    struct bdk_ndcx_priv_af_int_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by NDC_AF_INT_VEC_E. */
        uint64_t reserved_11           : 1;
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of AF interrupt vectors enumerated by
                                                                 NDC_AF_INT_VEC_E in RVU PF(0)'s MSI-X table. This offset is added to each
                                                                 enumerated value to obtain the corresponding MSI-X vector index. The
                                                                 highest enumerated value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF(0)_MSIX_CFG[PF_MSIXT_SIZEM1]. */
#else /* Word 0 - Little Endian */
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of AF interrupt vectors enumerated by
                                                                 NDC_AF_INT_VEC_E in RVU PF(0)'s MSI-X table. This offset is added to each
                                                                 enumerated value to obtain the corresponding MSI-X vector index. The
                                                                 highest enumerated value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF(0)_MSIX_CFG[PF_MSIXT_SIZEM1]. */
        uint64_t reserved_11           : 1;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by NDC_AF_INT_VEC_E. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_priv_af_int_cfg_s cn; */
};
typedef union bdk_ndcx_priv_af_int_cfg bdk_ndcx_priv_af_int_cfg_t;

static inline uint64_t BDK_NDCX_PRIV_AF_INT_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_PRIV_AF_INT_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=2))
        return 0x8400c00002f8ll + 0x10000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=5))
        return 0x8400c00002f8ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x8400c00002f8ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x8400c00002f8ll + 0x10000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x8400c00002f8ll + 0x10000000ll * ((a) & 0x7);
    __bdk_csr_fatal("NDCX_PRIV_AF_INT_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDCX_PRIV_AF_INT_CFG(a) bdk_ndcx_priv_af_int_cfg_t
#define bustype_BDK_NDCX_PRIV_AF_INT_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_PRIV_AF_INT_CFG(a) "NDCX_PRIV_AF_INT_CFG"
#define device_bar_BDK_NDCX_PRIV_AF_INT_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_NDCX_PRIV_AF_INT_CFG(a) (a)
#define arguments_BDK_NDCX_PRIV_AF_INT_CFG(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_NDC_H__ */
