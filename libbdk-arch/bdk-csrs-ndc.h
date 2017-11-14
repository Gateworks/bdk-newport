#ifndef __BDK_CSRS_NDC_H__
#define __BDK_CSRS_NDC_H__
/* This file is auto-generated. Do not edit */

/***********************license start***************
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

 *   * Neither the name of Cavium Inc. nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.

 * This Software, including technical data, may be subject to U.S. export  control
 * laws, including the U.S. Export Administration Act and its  associated
 * regulations, and may be subject to export or import  regulations in other
 * countries.

 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM  NETWORKS MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR
 * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/


/**
 * @file
 *
 * Configuration and status register (CSR) address and type definitions for
 * Cavium NDC.
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
 * Enumerates the caching type of NDC port requests, and CT index of
 * NDC_AF_PORT()_CT()_RW()_REQ_PC and NDC_AF_PORT()_CT()_RW()_LAT_PC.
 */
#define BDK_NDC_CTYPE_E_BYPASS (1)
#define BDK_NDC_CTYPE_E_CACHING (0)

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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000078ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_ACTIVE_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_ACTIVE_PC(a) bdk_ndcx_af_active_pc_t
#define bustype_BDK_NDCX_AF_ACTIVE_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_ACTIVE_PC(a) "NDCX_AF_ACTIVE_PC"
#define device_bar_BDK_NDCX_AF_ACTIVE_PC(a) 0x0 /* BAR0 */
#define busnum_BDK_NDCX_AF_ACTIVE_PC(a) (a)
#define arguments_BDK_NDCX_AF_ACTIVE_PC(a) (a),-1,-1,-1

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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=2) && (b<=15) && (c<=3)))
        return 0x8500c0000600ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANKX_INDEXX_BUSY", 3, a, b, c, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) bdk_ndcx_af_bankx_indexx_busy_t
#define bustype_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) "NDCX_AF_BANKX_INDEXX_BUSY"
#define device_bar_BDK_NDCX_AF_BANKX_INDEXX_BUSY(a,b,c) 0x0 /* BAR0 */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=2) && (b<=15) && (c<=3)))
        return 0x8500c0000800ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANKX_INDEXX_DIRTY", 3, a, b, c, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) bdk_ndcx_af_bankx_indexx_dirty_t
#define bustype_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) "NDCX_AF_BANKX_INDEXX_DIRTY"
#define device_bar_BDK_NDCX_AF_BANKX_INDEXX_DIRTY(a,b,c) 0x0 /* BAR0 */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=2) && (b<=15) && (c<=3)))
        return 0x8500c0000a00ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANKX_INDEXX_LOCK", 3, a, b, c, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) bdk_ndcx_af_bankx_indexx_lock_t
#define bustype_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) "NDCX_AF_BANKX_INDEXX_LOCK"
#define device_bar_BDK_NDCX_AF_BANKX_INDEXX_LOCK(a,b,c) 0x0 /* BAR0 */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=2) && (b<=15) && (c<=3)))
        return 0x8500c0000400ll + 0x10000000ll * ((a) & 0x3) + 0x20ll * ((b) & 0xf) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANKX_INDEXX_VLD", 3, a, b, c, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) bdk_ndcx_af_bankx_indexx_vld_t
#define bustype_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) "NDCX_AF_BANKX_INDEXX_VLD"
#define device_bar_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) 0x0 /* BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) (a)
#define arguments_BDK_NDCX_AF_BANKX_INDEXX_VLD(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank#_line#_metadata
 *
 * INTERNAL: NDC Cache Metadata Registers
 *
 * These registers provide raw access to the cache meta data. For diagnostic use only.
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
        uint64_t strm_id               : 13; /**< [ 12:  0](R/W/H) Cache line stream ID. Kept in CAM. */
#else /* Word 0 - Little Endian */
        uint64_t strm_id               : 13; /**< [ 12:  0](R/W/H) Cache line stream ID. Kept in CAM. */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=2) && (b<=15) && (c<=255)))
        return 0x8500c0010000ll + 0x10000000ll * ((a) & 0x3) + 0x1000ll * ((b) & 0xf) + 8ll * ((c) & 0xff);
    __bdk_csr_fatal("NDCX_AF_BANKX_LINEX_METADATA", 3, a, b, c, 0);
}

#define typedef_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) bdk_ndcx_af_bankx_linex_metadata_t
#define bustype_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) "NDCX_AF_BANKX_LINEX_METADATA"
#define device_bar_BDK_NDCX_AF_BANKX_LINEX_METADATA(a,b,c) 0x0 /* BAR0 */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=2) && (b<=15) && (c<=255) && (d<=15)))
        return 0x8500c0100000ll + 0x10000000ll * ((a) & 0x3) + 0x8000ll * ((b) & 0xf) + 0x80ll * ((c) & 0xff) + 8ll * ((d) & 0xf);
    __bdk_csr_fatal("NDCX_AF_BANKX_LINEX_WORDX", 4, a, b, c, d);
}

#define typedef_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) bdk_ndcx_af_bankx_linex_wordx_t
#define bustype_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) "NDCX_AF_BANKX_LINEX_WORDX"
#define device_bar_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) 0x0 /* BAR0 */
#define busnum_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) (a)
#define arguments_BDK_NDCX_AF_BANKX_LINEX_WORDX(a,b,c,d) (a),(b),(c),(d)

/**
 * Register (RVU_PF_BAR0) ndc#_af_bank_bp_test
 *
 * INTERNAL: NDC Bank Backpressure Test Register
 *
 * Back pressure for testing purposes. Drives all XBARs or BANKs.
 */
union bdk_ndcx_af_bank_bp_test
{
    uint64_t u;
    struct bdk_ndcx_af_bank_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t bp_bank_rsp_ncbi      : 1;  /**< [  6:  6](R/W) Prevent acknowledging bank response data towards the NCBI interface. */
        uint64_t bp_bank_req_ncbi      : 1;  /**< [  5:  5](R/W) Prevent acknowledging bank bypass or miss request towards the NCBI interface. */
        uint64_t bp_bank_arb           : 1;  /**< [  4:  4](R/W) Prevent acknowledging any requests toward bank mem. */
        uint64_t bp_bk_pend_req        : 1;  /**< [  3:  3](R/W) Prevent poping requests from bank pending request FIFO. */
        uint64_t bp_bk_req             : 1;  /**< [  2:  2](R/W) Prevent poping bank command request fifo. */
        uint64_t bp_xbar_bank_req      : 1;  /**< [  1:  1](R/W) Prevent pushing requests from xbar towards the bank request FIFOs. */
        uint64_t bp_prt_xbar           : 1;  /**< [  0:  0](R/W) Prevent acknowledging requests from port towards XBAR. Will cause port buffer to get full. */
#else /* Word 0 - Little Endian */
        uint64_t bp_prt_xbar           : 1;  /**< [  0:  0](R/W) Prevent acknowledging requests from port towards XBAR. Will cause port buffer to get full. */
        uint64_t bp_xbar_bank_req      : 1;  /**< [  1:  1](R/W) Prevent pushing requests from xbar towards the bank request FIFOs. */
        uint64_t bp_bk_req             : 1;  /**< [  2:  2](R/W) Prevent poping bank command request fifo. */
        uint64_t bp_bk_pend_req        : 1;  /**< [  3:  3](R/W) Prevent poping requests from bank pending request FIFO. */
        uint64_t bp_bank_arb           : 1;  /**< [  4:  4](R/W) Prevent acknowledging any requests toward bank mem. */
        uint64_t bp_bank_req_ncbi      : 1;  /**< [  5:  5](R/W) Prevent acknowledging bank bypass or miss request towards the NCBI interface. */
        uint64_t bp_bank_rsp_ncbi      : 1;  /**< [  6:  6](R/W) Prevent acknowledging bank response data towards the NCBI interface. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bank_bp_test_s cn; */
};
typedef union bdk_ndcx_af_bank_bp_test bdk_ndcx_af_bank_bp_test_t;

static inline uint64_t BDK_NDCX_AF_BANK_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANK_BP_TEST(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000200ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANK_BP_TEST", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANK_BP_TEST(a) bdk_ndcx_af_bank_bp_test_t
#define bustype_BDK_NDCX_AF_BANK_BP_TEST(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANK_BP_TEST(a) "NDCX_AF_BANK_BP_TEST"
#define device_bar_BDK_NDCX_AF_BANK_BP_TEST(a) 0x0 /* BAR0 */
#define busnum_BDK_NDCX_AF_BANK_BP_TEST(a) (a)
#define arguments_BDK_NDCX_AF_BANK_BP_TEST(a) (a),-1,-1,-1

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
        uint64_t done                  : 16; /**< [ 15:  0](R/W1C/H) Done indication. Set by hardware when hardware completes the request as was
                                                                 submitted using NDC_AF_BANKS_CTL. The expectation is that user wait for
                                                                 [DONE] to be set for every write access to NDC_AF_BANKS_CTL
                                                                 before the next write is performed. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 16; /**< [ 15:  0](R/W1C/H) Done indication. Set by hardware when hardware completes the request as was
                                                                 submitted using NDC_AF_BANKS_CTL. The expectation is that user wait for
                                                                 [DONE] to be set for every write access to NDC_AF_BANKS_CTL
                                                                 before the next write is performed. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_bank_ctl_done_s cn; */
};
typedef union bdk_ndcx_af_bank_ctl_done bdk_ndcx_af_bank_ctl_done_t;

static inline uint64_t BDK_NDCX_AF_BANK_CTL_DONE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANK_CTL_DONE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000048ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANK_CTL_DONE", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANK_CTL_DONE(a) bdk_ndcx_af_bank_ctl_done_t
#define bustype_BDK_NDCX_AF_BANK_CTL_DONE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANK_CTL_DONE(a) "NDCX_AF_BANK_CTL_DONE"
#define device_bar_BDK_NDCX_AF_BANK_CTL_DONE(a) 0x0 /* BAR0 */
#define busnum_BDK_NDCX_AF_BANK_CTL_DONE(a) (a)
#define arguments_BDK_NDCX_AF_BANK_CTL_DONE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ndc#_af_banks_ctl
 *
 * NDC Bank Control Register
 * This register sets or clears NDC cache meta data.
 */
union bdk_ndcx_af_banks_ctl
{
    uint64_t u;
    struct bdk_ndcx_af_banks_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_18_63        : 46;
        uint64_t flush_all             : 1;  /**< [ 17: 17](WO) When written one, all NDC's lines will be flushed to LLC. All lines ends up
                                                                 invalidated when process is complete. If [FLUSH_ALL] is set none of the other
                                                                 bits should be set in the same write operation. */
        uint64_t sync_all              : 1;  /**< [ 16: 16](WO) When written one, syncs NDC cache with LLC. All dirty lines will be flushed to
                                                                 LLC/DRAM. Lines valid bit remains set but dirty bit will be cleared upon completion
                                                                 of flush operation. If [SYNC_ALL] is set none of the other bits should be set in
                                                                 the same write operation. */
        uint64_t reserved_4_15         : 12;
        uint64_t bk_rst_lock           : 1;  /**< [  3:  3](WO) When written one, clears all bank lines lock indication. Note any BK_RST* bits
                                                                 could be set at the same time for a single write operation. */
        uint64_t bk_rst_dirty          : 1;  /**< [  2:  2](WO) When written one, clears all bank lines dirty indication. If inappropriately
                                                                 used, this may cause data loss. Note any BK_RST* bits could be set at the same
                                                                 time for a single write operation. */
        uint64_t bk_rst_busy           : 1;  /**< [  1:  1](WO) When written one, clears all bank lines busy indication. If inappropriately
                                                                 used, this may cause data loss. Note any BK_RST* bits could be set at the same
                                                                 time for a single write operation. */
        uint64_t bk_rst_vld            : 1;  /**< [  0:  0](WO) When written one, invalidate all banks lines. If inappropriately used, this may
                                                                 cause data loss. Note any BK_RST* bits could be set at the same time for a
                                                                 single write operation. */
#else /* Word 0 - Little Endian */
        uint64_t bk_rst_vld            : 1;  /**< [  0:  0](WO) When written one, invalidate all banks lines. If inappropriately used, this may
                                                                 cause data loss. Note any BK_RST* bits could be set at the same time for a
                                                                 single write operation. */
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
                                                                 the same write operation. */
        uint64_t flush_all             : 1;  /**< [ 17: 17](WO) When written one, all NDC's lines will be flushed to LLC. All lines ends up
                                                                 invalidated when process is complete. If [FLUSH_ALL] is set none of the other
                                                                 bits should be set in the same write operation. */
        uint64_t reserved_18_63        : 46;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_banks_ctl_s cn; */
};
typedef union bdk_ndcx_af_banks_ctl bdk_ndcx_af_banks_ctl_t;

static inline uint64_t BDK_NDCX_AF_BANKS_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_BANKS_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000040ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_BANKS_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_BANKS_CTL(a) bdk_ndcx_af_banks_ctl_t
#define bustype_BDK_NDCX_AF_BANKS_CTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_BANKS_CTL(a) "NDCX_AF_BANKS_CTL"
#define device_bar_BDK_NDCX_AF_BANKS_CTL(a) 0x0 /* BAR0 */
#define busnum_BDK_NDCX_AF_BANKS_CTL(a) (a)
#define arguments_BDK_NDCX_AF_BANKS_CTL(a) (a),-1,-1,-1

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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000000ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_CONST", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_CONST(a) bdk_ndcx_af_const_t
#define bustype_BDK_NDCX_AF_CONST(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_CONST(a) "NDCX_AF_CONST"
#define device_bar_BDK_NDCX_AF_CONST(a) 0x0 /* BAR0 */
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
        uint64_t reserved_6_63         : 58;
        uint64_t clken_dis             : 1;  /**< [  5:  5](R/W) When set, forces conditional clock to be always on. For diagnostic use only. */
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, all NDC's port command lock field is forced to
                                                                 zero. When cleared lock field is driven by the port. */
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disabled. When set, all NDC's port command way select field
                                                                 is forced to all-ones. When cleared way select field is driven by the port. */
        uint64_t wr_thrgh              : 1;  /**< [  2:  2](R/W) Write through.
                                                                 0 = Only cache is updated in case of write request and hit.
                                                                 1 = Forces write through operation in case of cache write request and hit. Both bank
                                                                 cache and LLC are updated. */
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Disables the hash functionality. If disabled, port uses direct mapping for RD/WR operations. */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. */
#else /* Word 0 - Little Endian */
        uint64_t byp_only              : 1;  /**< [  0:  0](R/W) Bypass only.
                                                                 0 = Bypass only mode is disabled and NDC will steer port requests based on command
                                                                 bits, either to cache, for cache accesses or to LLC for bypass accesses.
                                                                 1 = All requests will be directed to LLC, similar to bypass operation. */
        uint64_t hash_dis              : 1;  /**< [  1:  1](R/W) Disables the hash functionality. If disabled, port uses direct mapping for RD/WR operations. */
        uint64_t wr_thrgh              : 1;  /**< [  2:  2](R/W) Write through.
                                                                 0 = Only cache is updated in case of write request and hit.
                                                                 1 = Forces write through operation in case of cache write request and hit. Both bank
                                                                 cache and LLC are updated. */
        uint64_t way_select_dis        : 1;  /**< [  3:  3](R/W) Way select disabled. When set, all NDC's port command way select field
                                                                 is forced to all-ones. When cleared way select field is driven by the port. */
        uint64_t lock_dis              : 1;  /**< [  4:  4](R/W) Lock disabled. When set, all NDC's port command lock field is forced to
                                                                 zero. When cleared lock field is driven by the port. */
        uint64_t clken_dis             : 1;  /**< [  5:  5](R/W) When set, forces conditional clock to be always on. For diagnostic use only. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndcx_af_ctl_s cn; */
};
typedef union bdk_ndcx_af_ctl bdk_ndcx_af_ctl_t;

static inline uint64_t BDK_NDCX_AF_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDCX_AF_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000030ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_CTL(a) bdk_ndcx_af_ctl_t
#define bustype_BDK_NDCX_AF_CTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_CTL(a) "NDCX_AF_CTL"
#define device_bar_BDK_NDCX_AF_CTL(a) 0x0 /* BAR0 */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000010ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_ECO", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_ECO(a) bdk_ndcx_af_eco_t
#define bustype_BDK_NDCX_AF_ECO(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_ECO(a) "NDCX_AF_ECO"
#define device_bar_BDK_NDCX_AF_ECO(a) 0x0 /* BAR0 */
#define busnum_BDK_NDCX_AF_ECO(a) (a)
#define arguments_BDK_NDCX_AF_ECO(a) (a),-1,-1,-1

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
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1C/H) Interrupt bit per bank. Each bit corresponds to banks 15..0 respectively. If
                                                                 set, bank got FLR request for a line that had busy bit set. */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1C/H) Interrupt bit per bank. Each bit corresponds to banks 15..0 respectively. If
                                                                 set, bank got a store fault error when writing a line back to LLC/DRAM. */
#else /* Word 0 - Little Endian */
        uint64_t flush_error           : 16; /**< [ 15:  0](R/W1C/H) Interrupt bit per bank. Each bit corresponds to banks 15..0 respectively. If
                                                                 set, bank got a store fault error when writing a line back to LLC/DRAM. */
        uint64_t flr_and_busy_error    : 16; /**< [ 31: 16](R/W1C/H) Interrupt bit per bank. Each bit corresponds to banks 15..0 respectively. If
                                                                 set, bank got FLR request for a line that had busy bit set. */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000058ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_INTR", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_INTR(a) bdk_ndcx_af_intr_t
#define bustype_BDK_NDCX_AF_INTR(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_INTR(a) "NDCX_AF_INTR"
#define device_bar_BDK_NDCX_AF_INTR(a) 0x0 /* BAR0 */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000070ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_INTR_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_INTR_ENA_W1C(a) bdk_ndcx_af_intr_ena_w1c_t
#define bustype_BDK_NDCX_AF_INTR_ENA_W1C(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_INTR_ENA_W1C(a) "NDCX_AF_INTR_ENA_W1C"
#define device_bar_BDK_NDCX_AF_INTR_ENA_W1C(a) 0x0 /* BAR0 */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000068ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_INTR_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_INTR_ENA_W1S(a) bdk_ndcx_af_intr_ena_w1s_t
#define bustype_BDK_NDCX_AF_INTR_ENA_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_INTR_ENA_W1S(a) "NDCX_AF_INTR_ENA_W1S"
#define device_bar_BDK_NDCX_AF_INTR_ENA_W1S(a) 0x0 /* BAR0 */
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000060ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_INTR_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_INTR_W1S(a) bdk_ndcx_af_intr_w1s_t
#define bustype_BDK_NDCX_AF_INTR_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_INTR_W1S(a) "NDCX_AF_INTR_W1S"
#define device_bar_BDK_NDCX_AF_INTR_W1S(a) 0x0 /* BAR0 */
#define busnum_BDK_NDCX_AF_INTR_W1S(a) (a)
#define arguments_BDK_NDCX_AF_INTR_W1S(a) (a),-1,-1,-1

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
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x8500c0000018ll + 0x10000000ll * ((a) & 0x3);
    __bdk_csr_fatal("NDCX_AF_SCRATCH", 1, a, 0, 0, 0);
}

#define typedef_BDK_NDCX_AF_SCRATCH(a) bdk_ndcx_af_scratch_t
#define bustype_BDK_NDCX_AF_SCRATCH(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_NDCX_AF_SCRATCH(a) "NDCX_AF_SCRATCH"
#define device_bar_BDK_NDCX_AF_SCRATCH(a) 0x0 /* BAR0 */
#define busnum_BDK_NDCX_AF_SCRATCH(a) (a)
#define arguments_BDK_NDCX_AF_SCRATCH(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_NDC_H__ */
