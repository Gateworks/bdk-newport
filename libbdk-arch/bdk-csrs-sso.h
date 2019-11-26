#ifndef __BDK_CSRS_SSO_H__
#define __BDK_CSRS_SSO_H__
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
 * OcteonTX SSO.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration sso_af_int_vec_e
 *
 * SSO MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_SSO_AF_INT_VEC_E_ERR0 (0)
#define BDK_SSO_AF_INT_VEC_E_ERR2 (1)
#define BDK_SSO_AF_INT_VEC_E_RAS (2)

/**
 * Enumeration sso_bar_e
 *
 * SSO Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_SSO_BAR_E_SSO_PF_BAR0 (0x860000000000ll)
#define BDK_SSO_BAR_E_SSO_PF_BAR0_SIZE 0x100000000ull
#define BDK_SSO_BAR_E_SSO_PF_BAR4 (0x860700000000ll)
#define BDK_SSO_BAR_E_SSO_PF_BAR4_SIZE 0x100000ull
#define BDK_SSO_BAR_E_SSO_VFX_BAR0(a) (0x860800000000ll + 0x100000ll * (a))
#define BDK_SSO_BAR_E_SSO_VFX_BAR0_SIZE 0x100000ull
#define BDK_SSO_BAR_E_SSO_VFX_BAR2(a) (0x862800000000ll + 0x100000ll * (a))
#define BDK_SSO_BAR_E_SSO_VFX_BAR2_SIZE 0x100000ull
#define BDK_SSO_BAR_E_SSO_VFX_BAR4(a) (0x860c00000000ll + 0x100000ll * (a))
#define BDK_SSO_BAR_E_SSO_VFX_BAR4_SIZE 0x100000ull

/**
 * Enumeration sso_lf_int_vec_e
 *
 * SSO MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_SSO_LF_INT_VEC_E_GRP (0)

/**
 * Enumeration sso_op_e
 *
 * INTERNAL: SSO Operation Code Enumeration
 *
 * Enumerates the different SSO operation codes.  For RTL use only.
 */
#define BDK_SSO_OP_E_ADDWQ_CN8 (4)
#define BDK_SSO_OP_E_ADDWQ_CN96XX (8)
#define BDK_SSO_OP_E_ADDWQ_CN98XX (7)
#define BDK_SSO_OP_E_ADDWQ_CNF95XX (8)
#define BDK_SSO_OP_E_ADDWQ_LOKI (8)
#define BDK_SSO_OP_E_ALLOC_WE_CN96XX (0xc)
#define BDK_SSO_OP_E_ALLOC_WE_CN98XX (0xa)
#define BDK_SSO_OP_E_ALLOC_WE_CNF95XX (0xc)
#define BDK_SSO_OP_E_ALLOC_WE_LOKI (0xc)
#define BDK_SSO_OP_E_CLR_NSCHED_CN8 (7)
#define BDK_SSO_OP_E_CLR_NSCHED_CN96XX (0xa)
#define BDK_SSO_OP_E_CLR_NSCHED_CN98XX (0xb)
#define BDK_SSO_OP_E_CLR_NSCHED_CNF95XX (0xa)
#define BDK_SSO_OP_E_CLR_NSCHED_LOKI (0xa)
#define BDK_SSO_OP_E_DESCH_CN8 (3)
#define BDK_SSO_OP_E_DESCH_CN96XX (6)
#define BDK_SSO_OP_E_DESCH_CN98XX (8)
#define BDK_SSO_OP_E_DESCH_CNF95XX (6)
#define BDK_SSO_OP_E_DESCH_LOKI (6)
#define BDK_SSO_OP_E_GET_WORK_CN96XX (0xb)
#define BDK_SSO_OP_E_GET_WORK_CN98XX (0xc)
#define BDK_SSO_OP_E_GET_WORK_CNF95XX (0xb)
#define BDK_SSO_OP_E_GET_WORK_LOKI (0xb)
#define BDK_SSO_OP_E_GWC_INVAL_CN96XX (0xd)
#define BDK_SSO_OP_E_GWC_INVAL_CN98XX (0x11)
#define BDK_SSO_OP_E_GWC_INVAL_CNF95XX (0xd)
#define BDK_SSO_OP_E_GWC_INVAL_LOKI (0xd)
#define BDK_SSO_OP_E_NOP_CN8 (0xf)
#define BDK_SSO_OP_E_NOP_CN96XX (0x13)
#define BDK_SSO_OP_E_NOP_CN98XX (0)
#define BDK_SSO_OP_E_NOP_CNF95XX (0x13)
#define BDK_SSO_OP_E_NOP_LOKI (0x13)
#define BDK_SSO_OP_E_NOSCH_CN96XX (7)
#define BDK_SSO_OP_E_NOSCH_CN98XX (9)
#define BDK_SSO_OP_E_NOSCH_CNF95XX (7)
#define BDK_SSO_OP_E_NOSCH_LOKI (7)
#define BDK_SSO_OP_E_RST (0x10)
#define BDK_SSO_OP_E_SWTAG_CN8 (0)
#define BDK_SSO_OP_E_SWTAG_CN96XX (0)
#define BDK_SSO_OP_E_SWTAG_CN98XX (1)
#define BDK_SSO_OP_E_SWTAG_CNF95XX (0)
#define BDK_SSO_OP_E_SWTAG_LOKI (0)
#define BDK_SSO_OP_E_SWTAG_DESCH_CN8 (2)
#define BDK_SSO_OP_E_SWTAG_DESCH_CN96XX (3)
#define BDK_SSO_OP_E_SWTAG_DESCH_CN98XX (4)
#define BDK_SSO_OP_E_SWTAG_DESCH_CNF95XX (3)
#define BDK_SSO_OP_E_SWTAG_DESCH_LOKI (3)
#define BDK_SSO_OP_E_SWTAG_FLUSH_CN96XX (2)
#define BDK_SSO_OP_E_SWTAG_FLUSH_CN98XX (3)
#define BDK_SSO_OP_E_SWTAG_FLUSH_CNF95XX (2)
#define BDK_SSO_OP_E_SWTAG_FLUSH_LOKI (2)
#define BDK_SSO_OP_E_SWTAG_FULL_CN8 (1)
#define BDK_SSO_OP_E_SWTAG_FULL_CN96XX (1)
#define BDK_SSO_OP_E_SWTAG_FULL_CN98XX (2)
#define BDK_SSO_OP_E_SWTAG_FULL_CNF95XX (1)
#define BDK_SSO_OP_E_SWTAG_FULL_LOKI (1)
#define BDK_SSO_OP_E_SWTAG_NOSCH_CN96XX (4)
#define BDK_SSO_OP_E_SWTAG_NOSCH_CN98XX (5)
#define BDK_SSO_OP_E_SWTAG_NOSCH_CNF95XX (4)
#define BDK_SSO_OP_E_SWTAG_NOSCH_LOKI (4)
#define BDK_SSO_OP_E_SWTAG_UNTAG_CN96XX (5)
#define BDK_SSO_OP_E_SWTAG_UNTAG_CN98XX (6)
#define BDK_SSO_OP_E_SWTAG_UNTAG_CNF95XX (5)
#define BDK_SSO_OP_E_SWTAG_UNTAG_LOKI (5)
#define BDK_SSO_OP_E_SWTP_CLR_CN96XX (0xe)
#define BDK_SSO_OP_E_SWTP_CLR_CN98XX (0x12)
#define BDK_SSO_OP_E_SWTP_CLR_CNF95XX (0xe)
#define BDK_SSO_OP_E_SWTP_CLR_LOKI (0xe)
#define BDK_SSO_OP_E_SWTP_SET_CN96XX (0xf)
#define BDK_SSO_OP_E_SWTP_SET_CN98XX (0x13)
#define BDK_SSO_OP_E_SWTP_SET_CNF95XX (0xf)
#define BDK_SSO_OP_E_SWTP_SET_LOKI (0xf)
#define BDK_SSO_OP_E_UPD_GRP_CN96XX (0x11)
#define BDK_SSO_OP_E_UPD_GRP_CN98XX (0xd)
#define BDK_SSO_OP_E_UPD_GRP_CNF95XX (0x11)
#define BDK_SSO_OP_E_UPD_GRP_LOKI (0x11)
#define BDK_SSO_OP_E_UPD_WQP_CN96XX (0x12)
#define BDK_SSO_OP_E_UPD_WQP_CN98XX (0xe)
#define BDK_SSO_OP_E_UPD_WQP_CNF95XX (0x12)
#define BDK_SSO_OP_E_UPD_WQP_LOKI (0x12)
#define BDK_SSO_OP_E_UPD_WQP_GRP_CN8 (5)
#define BDK_SSO_OP_E_UPD_WQP_GRP_CN96XX (9)
#define BDK_SSO_OP_E_UPD_WQP_GRP_CN98XX (0xf)
#define BDK_SSO_OP_E_UPD_WQP_GRP_CNF95XX (9)
#define BDK_SSO_OP_E_UPD_WQP_GRP_LOKI (9)

/**
 * Enumeration sso_pf_int_vec_e
 *
 * SSO MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_SSO_PF_INT_VEC_E_ERR0 (0)
#define BDK_SSO_PF_INT_VEC_E_ERR1 (1)
#define BDK_SSO_PF_INT_VEC_E_ERR2 (2)
#define BDK_SSO_PF_INT_VEC_E_MBOXX(a) (3 + (a))

/**
 * Enumeration sso_sai_op_e
 *
 * INTERNAL: SSO AP Interconnect Opcode Enumeration
 *
 * Enumerates the SAI opcodes. For RTL use only.
 */
#define BDK_SSO_SAI_OP_E_FLUSH (4)
#define BDK_SSO_SAI_OP_E_GW_RESP (1)
#define BDK_SSO_SAI_OP_E_INVAL (3)
#define BDK_SSO_SAI_OP_E_SET_HEAD (2)
#define BDK_SSO_SAI_OP_E_SWTP_CLR (0)

/**
 * Enumeration sso_tt_e
 *
 * SSO Tag Type Enumeration
 * Enumerates the different SSO tag types.
 */
#define BDK_SSO_TT_E_ATOMIC (1)
#define BDK_SSO_TT_E_EMPTY (3)
#define BDK_SSO_TT_E_ORDERED (0)
#define BDK_SSO_TT_E_UNTAGGED (2)

/**
 * Enumeration sso_vf_int_vec_e
 *
 * SSO MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_SSO_VF_INT_VEC_E_GRP (0)

/**
 * Enumeration sso_wa_e
 *
 * SSO Work Add Interface Enumeration
 * Enumerates the different SSO work-add interfaces bit fields in SSO_AF_AW_INP_CTL[WA_DIS].
 */
#define BDK_SSO_WA_E_ADDWQ (3)
#define BDK_SSO_WA_E_CPT (2)
#define BDK_SSO_WA_E_CPTX(a) (2 + 7 * (a))
#define BDK_SSO_WA_E_CPT0 (2)
#define BDK_SSO_WA_E_CPT1 (4)
#define BDK_SSO_WA_E_DDF (0xc)
#define BDK_SSO_WA_E_DFA (5)
#define BDK_SSO_WA_E_DPI_CN8 (6)
#define BDK_SSO_WA_E_DPI_CN9 (4)
#define BDK_SSO_WA_E_DPIX(a) (4 + 6 * (a))
#define BDK_SSO_WA_E_HNA (7)
#define BDK_SSO_WA_E_IOBN (0)
#define BDK_SSO_WA_E_NIXRX (1)
#define BDK_SSO_WA_E_NIXRXX(a) (1 + 7 * (a))
#define BDK_SSO_WA_E_NIXTX (5)
#define BDK_SSO_WA_E_NIXTXX(a) (5 + 6 * (a))
#define BDK_SSO_WA_E_PKI (1)
#define BDK_SSO_WA_E_PKO (8)
#define BDK_SSO_WA_E_PSM (8)
#define BDK_SSO_WA_E_RAD (9)
#define BDK_SSO_WA_E_TIM_CN8 (0xa)
#define BDK_SSO_WA_E_TIM_CN9 (6)
#define BDK_SSO_WA_E_ZIP_CN8 (0xb)
#define BDK_SSO_WA_E_ZIP_CN9 (7)
#define BDK_SSO_WA_E_ZIPX(a) (7 + 5 * (a))

/**
 * Register (NCB) sso_active_cycles0
 *
 * SSO PF Active Cycles Register
 */
union bdk_sso_active_cycles0
{
    uint64_t u;
    struct bdk_sso_active_cycles0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO AW. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO AW. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_active_cycles0_s cn; */
};
typedef union bdk_sso_active_cycles0 bdk_sso_active_cycles0_t;

#define BDK_SSO_ACTIVE_CYCLES0 BDK_SSO_ACTIVE_CYCLES0_FUNC()
static inline uint64_t BDK_SSO_ACTIVE_CYCLES0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ACTIVE_CYCLES0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001100ll;
    __bdk_csr_fatal("SSO_ACTIVE_CYCLES0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ACTIVE_CYCLES0 bdk_sso_active_cycles0_t
#define bustype_BDK_SSO_ACTIVE_CYCLES0 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ACTIVE_CYCLES0 "SSO_ACTIVE_CYCLES0"
#define device_bar_BDK_SSO_ACTIVE_CYCLES0 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ACTIVE_CYCLES0 0
#define arguments_BDK_SSO_ACTIVE_CYCLES0 -1,-1,-1,-1

/**
 * Register (NCB) sso_active_cycles1
 *
 * SSO PF Active Cycles Register
 */
union bdk_sso_active_cycles1
{
    uint64_t u;
    struct bdk_sso_active_cycles1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO GW. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO GW. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_active_cycles1_s cn; */
};
typedef union bdk_sso_active_cycles1 bdk_sso_active_cycles1_t;

#define BDK_SSO_ACTIVE_CYCLES1 BDK_SSO_ACTIVE_CYCLES1_FUNC()
static inline uint64_t BDK_SSO_ACTIVE_CYCLES1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ACTIVE_CYCLES1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001108ll;
    __bdk_csr_fatal("SSO_ACTIVE_CYCLES1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ACTIVE_CYCLES1 bdk_sso_active_cycles1_t
#define bustype_BDK_SSO_ACTIVE_CYCLES1 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ACTIVE_CYCLES1 "SSO_ACTIVE_CYCLES1"
#define device_bar_BDK_SSO_ACTIVE_CYCLES1 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ACTIVE_CYCLES1 0
#define arguments_BDK_SSO_ACTIVE_CYCLES1 -1,-1,-1,-1

/**
 * Register (NCB) sso_active_cycles2
 *
 * SSO PF Active Cycles Register
 */
union bdk_sso_active_cycles2
{
    uint64_t u;
    struct bdk_sso_active_cycles2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO WS. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO WS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_active_cycles2_s cn; */
};
typedef union bdk_sso_active_cycles2 bdk_sso_active_cycles2_t;

#define BDK_SSO_ACTIVE_CYCLES2 BDK_SSO_ACTIVE_CYCLES2_FUNC()
static inline uint64_t BDK_SSO_ACTIVE_CYCLES2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ACTIVE_CYCLES2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001110ll;
    __bdk_csr_fatal("SSO_ACTIVE_CYCLES2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ACTIVE_CYCLES2 bdk_sso_active_cycles2_t
#define bustype_BDK_SSO_ACTIVE_CYCLES2 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ACTIVE_CYCLES2 "SSO_ACTIVE_CYCLES2"
#define device_bar_BDK_SSO_ACTIVE_CYCLES2 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ACTIVE_CYCLES2 0
#define arguments_BDK_SSO_ACTIVE_CYCLES2 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_active_cycles0
 *
 * SSO AF Active Cycles Register
 */
union bdk_sso_af_active_cycles0
{
    uint64_t u;
    struct bdk_sso_af_active_cycles0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO AW. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO AW. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_active_cycles0_s cn; */
};
typedef union bdk_sso_af_active_cycles0 bdk_sso_af_active_cycles0_t;

#define BDK_SSO_AF_ACTIVE_CYCLES0 BDK_SSO_AF_ACTIVE_CYCLES0_FUNC()
static inline uint64_t BDK_SSO_AF_ACTIVE_CYCLES0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ACTIVE_CYCLES0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001100ll;
    __bdk_csr_fatal("SSO_AF_ACTIVE_CYCLES0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ACTIVE_CYCLES0 bdk_sso_af_active_cycles0_t
#define bustype_BDK_SSO_AF_ACTIVE_CYCLES0 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ACTIVE_CYCLES0 "SSO_AF_ACTIVE_CYCLES0"
#define device_bar_BDK_SSO_AF_ACTIVE_CYCLES0 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ACTIVE_CYCLES0 0
#define arguments_BDK_SSO_AF_ACTIVE_CYCLES0 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_active_cycles1
 *
 * SSO AF Active Cycles Register
 */
union bdk_sso_af_active_cycles1
{
    uint64_t u;
    struct bdk_sso_af_active_cycles1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO GW. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO GW. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_active_cycles1_s cn; */
};
typedef union bdk_sso_af_active_cycles1 bdk_sso_af_active_cycles1_t;

#define BDK_SSO_AF_ACTIVE_CYCLES1 BDK_SSO_AF_ACTIVE_CYCLES1_FUNC()
static inline uint64_t BDK_SSO_AF_ACTIVE_CYCLES1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ACTIVE_CYCLES1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001108ll;
    __bdk_csr_fatal("SSO_AF_ACTIVE_CYCLES1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ACTIVE_CYCLES1 bdk_sso_af_active_cycles1_t
#define bustype_BDK_SSO_AF_ACTIVE_CYCLES1 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ACTIVE_CYCLES1 "SSO_AF_ACTIVE_CYCLES1"
#define device_bar_BDK_SSO_AF_ACTIVE_CYCLES1 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ACTIVE_CYCLES1 0
#define arguments_BDK_SSO_AF_ACTIVE_CYCLES1 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_active_cycles2
 *
 * SSO AF Active Cycles Register
 */
union bdk_sso_af_active_cycles2
{
    uint64_t u;
    struct bdk_sso_af_active_cycles2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO WS. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the SSO clocks are active in SSO WS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_active_cycles2_s cn; */
};
typedef union bdk_sso_af_active_cycles2 bdk_sso_af_active_cycles2_t;

#define BDK_SSO_AF_ACTIVE_CYCLES2 BDK_SSO_AF_ACTIVE_CYCLES2_FUNC()
static inline uint64_t BDK_SSO_AF_ACTIVE_CYCLES2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ACTIVE_CYCLES2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001110ll;
    __bdk_csr_fatal("SSO_AF_ACTIVE_CYCLES2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ACTIVE_CYCLES2 bdk_sso_af_active_cycles2_t
#define bustype_BDK_SSO_AF_ACTIVE_CYCLES2 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ACTIVE_CYCLES2 "SSO_AF_ACTIVE_CYCLES2"
#define device_bar_BDK_SSO_AF_ACTIVE_CYCLES2 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ACTIVE_CYCLES2 0
#define arguments_BDK_SSO_AF_ACTIVE_CYCLES2 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_aw_add
 *
 * SSO AF Work-Entries Add Register
 */
union bdk_sso_af_aw_add
{
    uint64_t u;
    struct bdk_sso_af_aw_add_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t rsvd_free             : 14; /**< [ 29: 16](WO) Written value is added to SSO_AF_AW_WE[RSVD_FREE] to prevent races between software and
                                                                 hardware changes. This is a two's complement value so subtraction may also be performed. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t rsvd_free             : 14; /**< [ 29: 16](WO) Written value is added to SSO_AF_AW_WE[RSVD_FREE] to prevent races between software and
                                                                 hardware changes. This is a two's complement value so subtraction may also be performed. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_aw_add_s cn; */
};
typedef union bdk_sso_af_aw_add bdk_sso_af_aw_add_t;

#define BDK_SSO_AF_AW_ADD BDK_SSO_AF_AW_ADD_FUNC()
static inline uint64_t BDK_SSO_AF_AW_ADD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AW_ADD_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070002080ll;
    __bdk_csr_fatal("SSO_AF_AW_ADD", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AW_ADD bdk_sso_af_aw_add_t
#define bustype_BDK_SSO_AF_AW_ADD BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AW_ADD "SSO_AF_AW_ADD"
#define device_bar_BDK_SSO_AF_AW_ADD 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AW_ADD 0
#define arguments_BDK_SSO_AF_AW_ADD -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_aw_cfg
 *
 * SSO AF Add-Work Configuration Register
 * This register controls the operation of the add-work block (AW).
 */
union bdk_sso_af_aw_cfg
{
    uint64_t u;
    struct bdk_sso_af_aw_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t ocla_bp               : 1;  /**< [  5:  5](R/W) OCLA backpressure enable. When OCLA FIFOs are near full, allow OCLA to backpressure AW pipeline. */
        uint64_t reserved_0_4          : 5;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_4          : 5;
        uint64_t ocla_bp               : 1;  /**< [  5:  5](R/W) OCLA backpressure enable. When OCLA FIFOs are near full, allow OCLA to backpressure AW pipeline. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    struct bdk_sso_af_aw_cfg_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t reserved_8            : 1;
        uint64_t reserved_7            : 1;
        uint64_t reserved_6            : 1;
        uint64_t ocla_bp               : 1;  /**< [  5:  5](R/W) OCLA backpressure enable. When OCLA FIFOs are near full, allow OCLA to backpressure AW pipeline. */
        uint64_t reserved_4            : 1;
        uint64_t reserved_3            : 1;
        uint64_t reserved_2            : 1;
        uint64_t reserved_1            : 1;
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t reserved_1            : 1;
        uint64_t reserved_2            : 1;
        uint64_t reserved_3            : 1;
        uint64_t reserved_4            : 1;
        uint64_t ocla_bp               : 1;  /**< [  5:  5](R/W) OCLA backpressure enable. When OCLA FIFOs are near full, allow OCLA to backpressure AW pipeline. */
        uint64_t reserved_6            : 1;
        uint64_t reserved_7            : 1;
        uint64_t reserved_8            : 1;
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } cn;
};
typedef union bdk_sso_af_aw_cfg bdk_sso_af_aw_cfg_t;

#define BDK_SSO_AF_AW_CFG BDK_SSO_AF_AW_CFG_FUNC()
static inline uint64_t BDK_SSO_AF_AW_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AW_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700010f0ll;
    __bdk_csr_fatal("SSO_AF_AW_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AW_CFG bdk_sso_af_aw_cfg_t
#define bustype_BDK_SSO_AF_AW_CFG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AW_CFG "SSO_AF_AW_CFG"
#define device_bar_BDK_SSO_AF_AW_CFG 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AW_CFG 0
#define arguments_BDK_SSO_AF_AW_CFG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_aw_dropped_digest#
 *
 * SSO AF 64 Bit Store To ADD_WORK0 Error Summary Registers
 * One bit per HWGRP to indicate which groups have reported an SSO_AF_ERR0[ADDWQ_DROPPED] error.
 */
union bdk_sso_af_aw_dropped_digestx
{
    uint64_t u;
    struct bdk_sso_af_aw_dropped_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_aw_dropped_digestx_s cn; */
};
typedef union bdk_sso_af_aw_dropped_digestx bdk_sso_af_aw_dropped_digestx_t;

static inline uint64_t BDK_SSO_AF_AW_DROPPED_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AW_DROPPED_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900c00ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_AW_DROPPED_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AW_DROPPED_DIGESTX(a) bdk_sso_af_aw_dropped_digestx_t
#define bustype_BDK_SSO_AF_AW_DROPPED_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AW_DROPPED_DIGESTX(a) "SSO_AF_AW_DROPPED_DIGESTX"
#define device_bar_BDK_SSO_AF_AW_DROPPED_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AW_DROPPED_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_AW_DROPPED_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_aw_dropped_digest#_w1s
 *
 * SSO AF WQP0 Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_aw_dropped_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_aw_dropped_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_AW_DROPPED_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_AW_DROPPED_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_aw_dropped_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_aw_dropped_digestx_w1s bdk_sso_af_aw_dropped_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_AW_DROPPED_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AW_DROPPED_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900d00ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_AW_DROPPED_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AW_DROPPED_DIGESTX_W1S(a) bdk_sso_af_aw_dropped_digestx_w1s_t
#define bustype_BDK_SSO_AF_AW_DROPPED_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AW_DROPPED_DIGESTX_W1S(a) "SSO_AF_AW_DROPPED_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_AW_DROPPED_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AW_DROPPED_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_AW_DROPPED_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_aw_eco
 *
 * INTERNAL: SSO AF AW ECO Register
 */
union bdk_sso_af_aw_eco
{
    uint64_t u;
    struct bdk_sso_af_aw_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_aw_eco_s cn; */
};
typedef union bdk_sso_af_aw_eco bdk_sso_af_aw_eco_t;

#define BDK_SSO_AF_AW_ECO BDK_SSO_AF_AW_ECO_FUNC()
static inline uint64_t BDK_SSO_AF_AW_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AW_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001030ll;
    __bdk_csr_fatal("SSO_AF_AW_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AW_ECO bdk_sso_af_aw_eco_t
#define bustype_BDK_SSO_AF_AW_ECO BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AW_ECO "SSO_AF_AW_ECO"
#define device_bar_BDK_SSO_AF_AW_ECO 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AW_ECO 0
#define arguments_BDK_SSO_AF_AW_ECO -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_aw_inp_ctl
 *
 * SSO AF Add-Work Input Control Register
 */
union bdk_sso_af_aw_inp_ctl
{
    uint64_t u;
    struct bdk_sso_af_aw_inp_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t wa_dis                : 13; /**< [ 12:  0](R/W) Add-work input disable.  Each bit corresponds to a hardware input queue, and if
                                                                 set add-works from the corresponding coprocessor will be dropped.
                                                                 Bit numbers enumerated by SSO_WA_E. */
#else /* Word 0 - Little Endian */
        uint64_t wa_dis                : 13; /**< [ 12:  0](R/W) Add-work input disable.  Each bit corresponds to a hardware input queue, and if
                                                                 set add-works from the corresponding coprocessor will be dropped.
                                                                 Bit numbers enumerated by SSO_WA_E. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_aw_inp_ctl_s cn9; */
    struct bdk_sso_af_aw_inp_ctl_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t wa_dis                : 10; /**< [  9:  0](R/W) Add-work input disable.  Each bit corresponds to a hardware input queue, and if
                                                                 set add-works from the corresponding coprocessor will be dropped.
                                                                 Bit numbers enumerated by SSO_WA_E. */
#else /* Word 0 - Little Endian */
        uint64_t wa_dis                : 10; /**< [  9:  0](R/W) Add-work input disable.  Each bit corresponds to a hardware input queue, and if
                                                                 set add-works from the corresponding coprocessor will be dropped.
                                                                 Bit numbers enumerated by SSO_WA_E. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_sso_af_aw_inp_ctl_s cn98xx; */
    /* struct bdk_sso_af_aw_inp_ctl_cn96xx cnf95xx; */
    /* struct bdk_sso_af_aw_inp_ctl_cn96xx loki; */
};
typedef union bdk_sso_af_aw_inp_ctl bdk_sso_af_aw_inp_ctl_t;

#define BDK_SSO_AF_AW_INP_CTL BDK_SSO_AF_AW_INP_CTL_FUNC()
static inline uint64_t BDK_SSO_AF_AW_INP_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AW_INP_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070002070ll;
    __bdk_csr_fatal("SSO_AF_AW_INP_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AW_INP_CTL bdk_sso_af_aw_inp_ctl_t
#define bustype_BDK_SSO_AF_AW_INP_CTL BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AW_INP_CTL "SSO_AF_AW_INP_CTL"
#define device_bar_BDK_SSO_AF_AW_INP_CTL 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AW_INP_CTL 0
#define arguments_BDK_SSO_AF_AW_INP_CTL -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_aw_read_arb
 *
 * SSO AF Read Arbitration Register
 * This register fine tunes the AW read arbiter and is for diagnostic use.
 */
union bdk_sso_af_aw_read_arb
{
    uint64_t u;
    struct bdk_sso_af_aw_read_arb_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW tag reads in flight. */
        uint64_t reserved_14_15        : 2;
        uint64_t aw_tag_lev            : 6;  /**< [ 13:  8](RO/H) Reserved.
                                                                 Internal:
                                                                 Current number of tag reads outstanding.  This is for short-form, and will be removed. */
        uint64_t reserved_5_7          : 3;
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Reserved.
                                                                 Internal:
                                                                 Number of read slots reserved for AQ tag read exclusive use.  This is for short-
                                                                 form, and will be removed. */
#else /* Word 0 - Little Endian */
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Reserved.
                                                                 Internal:
                                                                 Number of read slots reserved for AQ tag read exclusive use.  This is for short-
                                                                 form, and will be removed. */
        uint64_t reserved_5_7          : 3;
        uint64_t aw_tag_lev            : 6;  /**< [ 13:  8](RO/H) Reserved.
                                                                 Internal:
                                                                 Current number of tag reads outstanding.  This is for short-form, and will be removed. */
        uint64_t reserved_14_15        : 2;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW tag reads in flight. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_aw_read_arb_s cn9; */
    /* struct bdk_sso_af_aw_read_arb_s cn96xxp1_0; */
    struct bdk_sso_af_aw_read_arb_cn96xxp1_1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW tag reads in flight. */
        uint64_t reserved_14_15        : 2;
        uint64_t reserved_5_13         : 9;
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Reserved. */
        uint64_t reserved_5_13         : 9;
        uint64_t reserved_14_15        : 2;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW tag reads in flight. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } cn96xxp1_1;
    /* struct bdk_sso_af_aw_read_arb_cn96xxp1_1 cn96xxp3; */
    struct bdk_sso_af_aw_read_arb_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW tag reads in flight. */
        uint64_t reserved_5_15         : 11;
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Reserved. */
        uint64_t reserved_5_15         : 11;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW tag reads in flight. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_sso_af_aw_read_arb_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW tag reads in flight. */
        uint64_t reserved_14_15        : 2;
        uint64_t reserved_8_13         : 6;
        uint64_t reserved_5_7          : 3;
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Reserved. */
        uint64_t reserved_5_7          : 3;
        uint64_t reserved_8_13         : 6;
        uint64_t reserved_14_15        : 2;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW tag reads in flight. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_sso_af_aw_read_arb_cnf95xx loki; */
};
typedef union bdk_sso_af_aw_read_arb bdk_sso_af_aw_read_arb_t;

#define BDK_SSO_AF_AW_READ_ARB BDK_SSO_AF_AW_READ_ARB_FUNC()
static inline uint64_t BDK_SSO_AF_AW_READ_ARB_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AW_READ_ARB_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070002090ll;
    __bdk_csr_fatal("SSO_AF_AW_READ_ARB", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AW_READ_ARB bdk_sso_af_aw_read_arb_t
#define bustype_BDK_SSO_AF_AW_READ_ARB BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AW_READ_ARB "SSO_AF_AW_READ_ARB"
#define device_bar_BDK_SSO_AF_AW_READ_ARB 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AW_READ_ARB 0
#define arguments_BDK_SSO_AF_AW_READ_ARB -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_aw_we
 *
 * SSO AF Work-Entries Count Register
 */
union bdk_sso_af_aw_we
{
    uint64_t u;
    struct bdk_sso_af_aw_we_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t rsvd_free             : 14; /**< [ 29: 16](R/W/H) Number of free reserved entries. Used to ensure that each hardware group can get
                                                                 a specific number of entries. Must always be greater than or equal to the sum
                                                                 across all SSO_AF_HWGRP()_IAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to SSO_AF_HWGRP()_IAQ_THR[RSVD_THR] are going to be made. To
                                                                 prevent races, software should not change this register when SSO is being used;
                                                                 instead use SSO_AF_AW_ADD[RSVD_FREE]. */
        uint64_t reserved_14_15        : 2;
        uint64_t free_cnt              : 14; /**< [ 13:  0](RO/H) Number of total free entries. */
#else /* Word 0 - Little Endian */
        uint64_t free_cnt              : 14; /**< [ 13:  0](RO/H) Number of total free entries. */
        uint64_t reserved_14_15        : 2;
        uint64_t rsvd_free             : 14; /**< [ 29: 16](R/W/H) Number of free reserved entries. Used to ensure that each hardware group can get
                                                                 a specific number of entries. Must always be greater than or equal to the sum
                                                                 across all SSO_AF_HWGRP()_IAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to SSO_AF_HWGRP()_IAQ_THR[RSVD_THR] are going to be made. To
                                                                 prevent races, software should not change this register when SSO is being used;
                                                                 instead use SSO_AF_AW_ADD[RSVD_FREE]. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_aw_we_s cn9; */
    /* struct bdk_sso_af_aw_we_s cn96xx; */
    struct bdk_sso_af_aw_we_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t rsvd_free             : 14; /**< [ 29: 16](R/W/H) Number of free reserved entries. Used to ensure that each hardware group can get
                                                                 a specific number of entries. Must always be greater than or equal to the sum
                                                                 across all SSO_AF_HWGRP()_IAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to SSO_AF_HWGRP()_IAQ_THR[RSVD_THR] are going to be made. To
                                                                 prevent races, software should not change this register when SSO is being used;
                                                                 instead use SSO_AF_AW_ADD[RSVD_FREE].

                                                                 Internal:
                                                                 (16..`SSO_IDX_W+16) */
        uint64_t reserved_14_15        : 2;
        uint64_t free_cnt              : 14; /**< [ 13:  0](RO/H) Number of total free entries.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W) and fix reset value */
#else /* Word 0 - Little Endian */
        uint64_t free_cnt              : 14; /**< [ 13:  0](RO/H) Number of total free entries.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W) and fix reset value */
        uint64_t reserved_14_15        : 2;
        uint64_t rsvd_free             : 14; /**< [ 29: 16](R/W/H) Number of free reserved entries. Used to ensure that each hardware group can get
                                                                 a specific number of entries. Must always be greater than or equal to the sum
                                                                 across all SSO_AF_HWGRP()_IAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to SSO_AF_HWGRP()_IAQ_THR[RSVD_THR] are going to be made. To
                                                                 prevent races, software should not change this register when SSO is being used;
                                                                 instead use SSO_AF_AW_ADD[RSVD_FREE].

                                                                 Internal:
                                                                 (16..`SSO_IDX_W+16) */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_aw_we_s cnf95xx; */
    /* struct bdk_sso_af_aw_we_s loki; */
};
typedef union bdk_sso_af_aw_we bdk_sso_af_aw_we_t;

#define BDK_SSO_AF_AW_WE BDK_SSO_AF_AW_WE_FUNC()
static inline uint64_t BDK_SSO_AF_AW_WE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AW_WE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001080ll;
    __bdk_csr_fatal("SSO_AF_AW_WE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AW_WE bdk_sso_af_aw_we_t
#define bustype_BDK_SSO_AF_AW_WE BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AW_WE "SSO_AF_AW_WE"
#define device_bar_BDK_SSO_AF_AW_WE 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AW_WE 0
#define arguments_BDK_SSO_AF_AW_WE -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_awempty_digest#
 *
 * SSO AF AWEMPTY Error Summary Registers
 * One bit per HWGRP to indicate which groups have reported an SSO_AF_ERR0[AWEMPTY] error.
 */
union bdk_sso_af_awempty_digestx
{
    uint64_t u;
    struct bdk_sso_af_awempty_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_awempty_digestx_s cn; */
};
typedef union bdk_sso_af_awempty_digestx bdk_sso_af_awempty_digestx_t;

static inline uint64_t BDK_SSO_AF_AWEMPTY_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AWEMPTY_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900800ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_AWEMPTY_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AWEMPTY_DIGESTX(a) bdk_sso_af_awempty_digestx_t
#define bustype_BDK_SSO_AF_AWEMPTY_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AWEMPTY_DIGESTX(a) "SSO_AF_AWEMPTY_DIGESTX"
#define device_bar_BDK_SSO_AF_AWEMPTY_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AWEMPTY_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_AWEMPTY_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_awempty_digest#_w1s
 *
 * SSO AF AWEMPTY Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_awempty_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_awempty_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_AWEMPTY_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_AWEMPTY_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_awempty_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_awempty_digestx_w1s bdk_sso_af_awempty_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_AWEMPTY_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_AWEMPTY_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900900ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_AWEMPTY_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_AWEMPTY_DIGESTX_W1S(a) bdk_sso_af_awempty_digestx_w1s_t
#define bustype_BDK_SSO_AF_AWEMPTY_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_AWEMPTY_DIGESTX_W1S(a) "SSO_AF_AWEMPTY_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_AWEMPTY_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_AWEMPTY_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_AWEMPTY_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_bar2_alias#
 *
 * INTERNAL: SSO Admin Function  BAR2 Alias Registers
 *
 * These registers alias to the SSO BAR2 registers for the PF and function
 * selected by SSO_AF_BAR2_SEL[PF_FUNC].
 *
 * Internal:
 * Not implemented. Placeholder for bug33464.
 */
union bdk_sso_af_bar2_aliasx
{
    uint64_t u;
    struct bdk_sso_af_bar2_aliasx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Aliased register data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Aliased register data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_bar2_aliasx_s cn; */
};
typedef union bdk_sso_af_bar2_aliasx bdk_sso_af_bar2_aliasx_t;

static inline uint64_t BDK_SSO_AF_BAR2_ALIASX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BAR2_ALIASX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=131071))
        return 0x840079100000ll + 8ll * ((a) & 0x1ffff);
    __bdk_csr_fatal("SSO_AF_BAR2_ALIASX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BAR2_ALIASX(a) bdk_sso_af_bar2_aliasx_t
#define bustype_BDK_SSO_AF_BAR2_ALIASX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BAR2_ALIASX(a) "SSO_AF_BAR2_ALIASX"
#define device_bar_BDK_SSO_AF_BAR2_ALIASX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BAR2_ALIASX(a) (a)
#define arguments_BDK_SSO_AF_BAR2_ALIASX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_bar2_sel
 *
 * INTERNAL: SSO Admin Function BAR2 Select Register
 *
 * This register configures BAR2 accesses from the SSO_AF_BAR2_ALIAS() registers in BAR0.
 * Internal:
 * Not implemented. Placeholder for bug33464.
 */
union bdk_sso_af_bar2_sel
{
    uint64_t u;
    struct bdk_sso_af_bar2_sel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t alias_ena             : 1;  /**< [ 16: 16](R/W) Enable BAR2 register accesses from the AF BAR2 alias registers in BAR0. */
        uint64_t alias_pf_func         : 16; /**< [ 15:  0](R/W) PF and function whose BAR2 registers may be accessed from the AF BAR2 alias
                                                                 registers. Format specified by RVU_PF_FUNC_S. */
#else /* Word 0 - Little Endian */
        uint64_t alias_pf_func         : 16; /**< [ 15:  0](R/W) PF and function whose BAR2 registers may be accessed from the AF BAR2 alias
                                                                 registers. Format specified by RVU_PF_FUNC_S. */
        uint64_t alias_ena             : 1;  /**< [ 16: 16](R/W) Enable BAR2 register accesses from the AF BAR2 alias registers in BAR0. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_bar2_sel_s cn; */
};
typedef union bdk_sso_af_bar2_sel bdk_sso_af_bar2_sel_t;

#define BDK_SSO_AF_BAR2_SEL BDK_SSO_AF_BAR2_SEL_FUNC()
static inline uint64_t BDK_SSO_AF_BAR2_SEL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BAR2_SEL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840079000000ll;
    __bdk_csr_fatal("SSO_AF_BAR2_SEL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BAR2_SEL bdk_sso_af_bar2_sel_t
#define bustype_BDK_SSO_AF_BAR2_SEL BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BAR2_SEL "SSO_AF_BAR2_SEL"
#define device_bar_BDK_SSO_AF_BAR2_SEL 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BAR2_SEL 0
#define arguments_BDK_SSO_AF_BAR2_SEL -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_bfp_digest#
 *
 * SSO AF BFP Error Summary Registers
 * One bit per HWGRP to indicate which groups have reported an SSO_AF_ERR0[BFP] error.
 */
union bdk_sso_af_bfp_digestx
{
    uint64_t u;
    struct bdk_sso_af_bfp_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_bfp_digestx_s cn; */
};
typedef union bdk_sso_af_bfp_digestx bdk_sso_af_bfp_digestx_t;

static inline uint64_t BDK_SSO_AF_BFP_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BFP_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900200ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_BFP_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BFP_DIGESTX(a) bdk_sso_af_bfp_digestx_t
#define bustype_BDK_SSO_AF_BFP_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BFP_DIGESTX(a) "SSO_AF_BFP_DIGESTX"
#define device_bar_BDK_SSO_AF_BFP_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BFP_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_BFP_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_bfp_digest#_w1s
 *
 * SSO AF BFP Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_bfp_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_bfp_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_BFP_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_BFP_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_bfp_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_bfp_digestx_w1s bdk_sso_af_bfp_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_BFP_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BFP_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900300ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_BFP_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BFP_DIGESTX_W1S(a) bdk_sso_af_bfp_digestx_w1s_t
#define bustype_BDK_SSO_AF_BFP_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BFP_DIGESTX_W1S(a) "SSO_AF_BFP_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_BFP_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BFP_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_BFP_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_bfpn_digest#
 *
 * SSO AF BFP Error Summary Registers
 * One bit per HWGRP to indicate which groups have reported an SSO_AF_ERR0[BFPN] error.
 */
union bdk_sso_af_bfpn_digestx
{
    uint64_t u;
    struct bdk_sso_af_bfpn_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_bfpn_digestx_s cn; */
};
typedef union bdk_sso_af_bfpn_digestx bdk_sso_af_bfpn_digestx_t;

static inline uint64_t BDK_SSO_AF_BFPN_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BFPN_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900400ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_BFPN_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BFPN_DIGESTX(a) bdk_sso_af_bfpn_digestx_t
#define bustype_BDK_SSO_AF_BFPN_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BFPN_DIGESTX(a) "SSO_AF_BFPN_DIGESTX"
#define device_bar_BDK_SSO_AF_BFPN_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BFPN_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_BFPN_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_bfpn_digest#_w1s
 *
 * SSO AF BFPN Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_bfpn_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_bfpn_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_BFPN_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_BFPN_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_bfpn_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_bfpn_digestx_w1s bdk_sso_af_bfpn_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_BFPN_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BFPN_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900500ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_BFPN_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BFPN_DIGESTX_W1S(a) bdk_sso_af_bfpn_digestx_w1s_t
#define bustype_BDK_SSO_AF_BFPN_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BFPN_DIGESTX_W1S(a) "SSO_AF_BFPN_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_BFPN_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BFPN_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_BFPN_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_blk_rst
 *
 * SSO AF Block Reset Register
 * Writing a 1 to SSO_AF_BLK_RST[RST] resets the SSO. After receiving a store to this CSR, the SSO
 * must not be sent any other operations for 16,000 coprocessor (SCLK) cycles. Note that the
 * contents of this register are reset along with the rest of the SSO.
 */
union bdk_sso_af_blk_rst
{
    uint64_t u;
    struct bdk_sso_af_blk_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) Initialization in progress. After reset asserts, SSO will set this bit until internal
                                                                 structures are initialized. This bit must read as zero before any configuration may be
                                                                 done. */
        uint64_t reserved_1_62         : 62;
        uint64_t rst                   : 1;  /**< [  0:  0](WO) Write one to reset the block, except for privileged AF registers in PF BAR0
                                                                 (SSO_PRIV_*). Software must ensure that all block activity is quiesced before
                                                                 writing 1. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 1;  /**< [  0:  0](WO) Write one to reset the block, except for privileged AF registers in PF BAR0
                                                                 (SSO_PRIV_*). Software must ensure that all block activity is quiesced before
                                                                 writing 1. */
        uint64_t reserved_1_62         : 62;
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) Initialization in progress. After reset asserts, SSO will set this bit until internal
                                                                 structures are initialized. This bit must read as zero before any configuration may be
                                                                 done. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_blk_rst_s cn; */
};
typedef union bdk_sso_af_blk_rst bdk_sso_af_blk_rst_t;

#define BDK_SSO_AF_BLK_RST BDK_SSO_AF_BLK_RST_FUNC()
static inline uint64_t BDK_SSO_AF_BLK_RST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BLK_RST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700010f8ll;
    __bdk_csr_fatal("SSO_AF_BLK_RST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BLK_RST bdk_sso_af_blk_rst_t
#define bustype_BDK_SSO_AF_BLK_RST BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BLK_RST "SSO_AF_BLK_RST"
#define device_bar_BDK_SSO_AF_BLK_RST 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BLK_RST 0
#define arguments_BDK_SSO_AF_BLK_RST -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_bp_test0
 *
 * INTERNAL: SSO AF Backpressure Test Register 0
 */
union bdk_sso_af_bp_test0
{
    uint64_t u;
    struct bdk_sso_af_bp_test0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit the egs.totq.totq_rd fifo pop.
                                                                 \<62\> = Limit the emc.rlreq.ptr_fifo pop.
                                                                 \<61\> = Limit the sso_aw_fffwrap fill fifo pop.
                                                                 \<60\> = Limit the aw aq credit decrement returns. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit the egs.totq.totq_rd fifo pop.
                                                                 \<62\> = Limit the emc.rlreq.ptr_fifo pop.
                                                                 \<61\> = Limit the sso_aw_fffwrap fill fifo pop.
                                                                 \<60\> = Limit the aw aq credit decrement returns. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_bp_test0_s cn; */
};
typedef union bdk_sso_af_bp_test0 bdk_sso_af_bp_test0_t;

#define BDK_SSO_AF_BP_TEST0 BDK_SSO_AF_BP_TEST0_FUNC()
static inline uint64_t BDK_SSO_AF_BP_TEST0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BP_TEST0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001380ll;
    __bdk_csr_fatal("SSO_AF_BP_TEST0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BP_TEST0 bdk_sso_af_bp_test0_t
#define bustype_BDK_SSO_AF_BP_TEST0 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BP_TEST0 "SSO_AF_BP_TEST0"
#define device_bar_BDK_SSO_AF_BP_TEST0 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BP_TEST0 0
#define arguments_BDK_SSO_AF_BP_TEST0 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_bp_test1
 *
 * INTERNAL: SSO AF Backpressure Test Register 1
 */
union bdk_sso_af_bp_test1
{
    uint64_t u;
    struct bdk_sso_af_bp_test1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Limit the gw_csr_rxfifo from asserting valid for the next request. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Limit the gw_csr_rxfifo from asserting valid for the next request. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_bp_test1_s cn; */
};
typedef union bdk_sso_af_bp_test1 bdk_sso_af_bp_test1_t;

#define BDK_SSO_AF_BP_TEST1 BDK_SSO_AF_BP_TEST1_FUNC()
static inline uint64_t BDK_SSO_AF_BP_TEST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BP_TEST1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001390ll;
    __bdk_csr_fatal("SSO_AF_BP_TEST1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BP_TEST1 bdk_sso_af_bp_test1_t
#define bustype_BDK_SSO_AF_BP_TEST1 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BP_TEST1 "SSO_AF_BP_TEST1"
#define device_bar_BDK_SSO_AF_BP_TEST1 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BP_TEST1 0
#define arguments_BDK_SSO_AF_BP_TEST1 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_bp_test2
 *
 * INTERNAL: SSO AF Backpressure Test Register 2
 */
union bdk_sso_af_bp_test2
{
    uint64_t u;
    struct bdk_sso_af_bp_test2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 8;  /**< [ 63: 56](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = SAI bus stall.
                                                                 \<61\> = GWMGR unit, getwork request stall.
                                                                 \<60\> = Issue unit, pipeline issue stall.
                                                                 \<59\> = ACDQ unit; cq dq stall.
                                                                 \<58\> = ACDQ unit; addwork stall.
                                                                 \<57\> = Reduce the rate at which NCB/RSL requests are dispatched.
                                                                 \<56\> = Starve the NCBO fifo of credits, forcing it to fill. */
        uint64_t reserved_32_55        : 24;
        uint64_t bp_cfg                : 16; /**< [ 31: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<31:30\> = Config 7.
                                                                   \<29:28\> = Config 6.
                                                                   \<27:26\> = Config 5.
                                                                   \<25:24\> = Config 4.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1 (NCB/RSL).
                                                                   \<17:16\> = Config 0 (NCBO). */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 16; /**< [ 31: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<31:30\> = Config 7.
                                                                   \<29:28\> = Config 6.
                                                                   \<27:26\> = Config 5.
                                                                   \<25:24\> = Config 4.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1 (NCB/RSL).
                                                                   \<17:16\> = Config 0 (NCBO). */
        uint64_t reserved_32_55        : 24;
        uint64_t enable                : 8;  /**< [ 63: 56](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = SAI bus stall.
                                                                 \<61\> = GWMGR unit, getwork request stall.
                                                                 \<60\> = Issue unit, pipeline issue stall.
                                                                 \<59\> = ACDQ unit; cq dq stall.
                                                                 \<58\> = ACDQ unit; addwork stall.
                                                                 \<57\> = Reduce the rate at which NCB/RSL requests are dispatched.
                                                                 \<56\> = Starve the NCBO fifo of credits, forcing it to fill. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_bp_test2_s cn; */
};
typedef union bdk_sso_af_bp_test2 bdk_sso_af_bp_test2_t;

#define BDK_SSO_AF_BP_TEST2 BDK_SSO_AF_BP_TEST2_FUNC()
static inline uint64_t BDK_SSO_AF_BP_TEST2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_BP_TEST2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700013a0ll;
    __bdk_csr_fatal("SSO_AF_BP_TEST2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_BP_TEST2 bdk_sso_af_bp_test2_t
#define bustype_BDK_SSO_AF_BP_TEST2 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_BP_TEST2 "SSO_AF_BP_TEST2"
#define device_bar_BDK_SSO_AF_BP_TEST2 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_BP_TEST2 0
#define arguments_BDK_SSO_AF_BP_TEST2 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_const
 *
 * SSO AF Constants Register
 * This register contains constants for software discovery.
 */
union bdk_sso_af_const
{
    uint64_t u;
    struct bdk_sso_af_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 8;  /**< [ 63: 56](RO) Number of hardware workslots. */
        uint64_t taq_b                 : 8;  /**< [ 55: 48](RO) Number of TAQ entries per line.  Multiply [TAQ_A] times [TAQ_B] to find total entries.
                                                                 A value of 0x0 should be interpreted to mean 0xb. */
        uint64_t taq_a                 : 16; /**< [ 47: 32](RO) Number of TAQ lines.  Multiply [TAQ_A] times [TAQ_B] to find total entries. */
        uint64_t iue                   : 16; /**< [ 31: 16](RO) Number of in-unit entries. */
        uint64_t grp                   : 16; /**< [ 15:  0](RO) Number of hardware groups. */
#else /* Word 0 - Little Endian */
        uint64_t grp                   : 16; /**< [ 15:  0](RO) Number of hardware groups. */
        uint64_t iue                   : 16; /**< [ 31: 16](RO) Number of in-unit entries. */
        uint64_t taq_a                 : 16; /**< [ 47: 32](RO) Number of TAQ lines.  Multiply [TAQ_A] times [TAQ_B] to find total entries. */
        uint64_t taq_b                 : 8;  /**< [ 55: 48](RO) Number of TAQ entries per line.  Multiply [TAQ_A] times [TAQ_B] to find total entries.
                                                                 A value of 0x0 should be interpreted to mean 0xb. */
        uint64_t hws                   : 8;  /**< [ 63: 56](RO) Number of hardware workslots. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_const_s cn9; */
    /* struct bdk_sso_af_const_s cn96xx; */
    struct bdk_sso_af_const_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 8;  /**< [ 63: 56](RO) Number of hardware workslots.
                                                                 Internal:
                                                                 reset and typical `SSO_NUM_WS */
        uint64_t taq_b                 : 8;  /**< [ 55: 48](RO) Number of TAQ entries per line.  Multiply [TAQ_A] times [TAQ_B] to find total entries.
                                                                 A value of 0x0 should be interpreted to mean 0xb. */
        uint64_t taq_a                 : 16; /**< [ 47: 32](RO) Number of TAQ lines.  Multiply [TAQ_A] times [TAQ_B] to find total entries. */
        uint64_t iue                   : 16; /**< [ 31: 16](RO) Number of in-unit entries.
                                                                 Internal:
                                                                 reset and typical `SSO_IDX_CNT */
        uint64_t grp                   : 16; /**< [ 15:  0](RO) Number of hardware groups. */
#else /* Word 0 - Little Endian */
        uint64_t grp                   : 16; /**< [ 15:  0](RO) Number of hardware groups. */
        uint64_t iue                   : 16; /**< [ 31: 16](RO) Number of in-unit entries.
                                                                 Internal:
                                                                 reset and typical `SSO_IDX_CNT */
        uint64_t taq_a                 : 16; /**< [ 47: 32](RO) Number of TAQ lines.  Multiply [TAQ_A] times [TAQ_B] to find total entries. */
        uint64_t taq_b                 : 8;  /**< [ 55: 48](RO) Number of TAQ entries per line.  Multiply [TAQ_A] times [TAQ_B] to find total entries.
                                                                 A value of 0x0 should be interpreted to mean 0xb. */
        uint64_t hws                   : 8;  /**< [ 63: 56](RO) Number of hardware workslots.
                                                                 Internal:
                                                                 reset and typical `SSO_NUM_WS */
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_const_s cnf95xx; */
    /* struct bdk_sso_af_const_s loki; */
};
typedef union bdk_sso_af_const bdk_sso_af_const_t;

#define BDK_SSO_AF_CONST BDK_SSO_AF_CONST_FUNC()
static inline uint64_t BDK_SSO_AF_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_CONST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001000ll;
    __bdk_csr_fatal("SSO_AF_CONST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_CONST bdk_sso_af_const_t
#define bustype_BDK_SSO_AF_CONST BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_CONST "SSO_AF_CONST"
#define device_bar_BDK_SSO_AF_CONST 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_CONST 0
#define arguments_BDK_SSO_AF_CONST -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_const1
 *
 * SSO AF Constants Register 1
 * This register contains constants for software discovery.
 */
union bdk_sso_af_const1
{
    uint64_t u;
    struct bdk_sso_af_const1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t fwd                   : 1;  /**< [ 32: 32](RO) Indicates that SSO supports forwarding groups. */
        uint64_t xae_waes              : 16; /**< [ 31: 16](RO) Number of WAEs (work entries) in a XAQ buffer. */
        uint64_t xaq_buf_size          : 16; /**< [ 15:  0](RO) Number of bytes in a XAQ buffer. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_buf_size          : 16; /**< [ 15:  0](RO) Number of bytes in a XAQ buffer. */
        uint64_t xae_waes              : 16; /**< [ 31: 16](RO) Number of WAEs (work entries) in a XAQ buffer. */
        uint64_t fwd                   : 1;  /**< [ 32: 32](RO) Indicates that SSO supports forwarding groups. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_const1_s cn9; */
    struct bdk_sso_af_const1_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t xae_waes              : 16; /**< [ 31: 16](RO) Number of WAEs (work entries) in a XAQ buffer. */
        uint64_t xaq_buf_size          : 16; /**< [ 15:  0](RO) Number of bytes in a XAQ buffer. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_buf_size          : 16; /**< [ 15:  0](RO) Number of bytes in a XAQ buffer. */
        uint64_t xae_waes              : 16; /**< [ 31: 16](RO) Number of WAEs (work entries) in a XAQ buffer. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp1;
    /* struct bdk_sso_af_const1_s cn96xxp3; */
    /* struct bdk_sso_af_const1_s cn98xx; */
    /* struct bdk_sso_af_const1_cn96xxp1 cnf95xx; */
    /* struct bdk_sso_af_const1_cn96xxp1 loki; */
};
typedef union bdk_sso_af_const1 bdk_sso_af_const1_t;

#define BDK_SSO_AF_CONST1 BDK_SSO_AF_CONST1_FUNC()
static inline uint64_t BDK_SSO_AF_CONST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_CONST1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001008ll;
    __bdk_csr_fatal("SSO_AF_CONST1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_CONST1 bdk_sso_af_const1_t
#define bustype_BDK_SSO_AF_CONST1 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_CONST1 "SSO_AF_CONST1"
#define device_bar_BDK_SSO_AF_CONST1 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_CONST1 0
#define arguments_BDK_SSO_AF_CONST1 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_err0
 *
 * SSO AF_PF Error 0 Register
 * This register contains ECC and other miscellaneous error bits.
 */
union bdk_sso_af_err0
{
    uint64_t u;
    struct bdk_sso_af_err0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t bfpp                  : 1;  /**< [ 15: 15](R/W1C/H) Bad-fill-packet NCB error. NCB detected poison on fill data.  Any
                                                                 groups that experience this error are reported in SSO_AF_POISON(). */
        uint64_t flr_aq_cnt            : 1;  /**< [ 14: 14](R/W1C/H) An FLR was initiated, but SSO_LF_GGRP_AQ_CNT[AQ_CNT] != 0.  Any groups
                                                                 reporting this error are indicated in SSO_AF_FLR_AQ_DIGEST(). */
        uint64_t addwq_dropped_xaqen   : 1;  /**< [ 13: 13](R/W1C/H) Add work dropped due to XAQ pointers not yet initialized.  Any groups
                                                                 reporting this error are indicated in SSO_AF_XAQDIS_DIGEST(). */
        uint64_t ggrp_multi            : 1;  /**< [ 12: 12](R/W1C/H) PF_FUNC map had double-hit error. Set when a load or store accesses an
                                                                 SSO LF register in BAR2 and SSO_PRIV_LF()_HWGRP_CFG has a double hit.
                                                                 When a request thus dropped, even if this bit is already set,
                                                                 SSO_AF_UNMAP_INFO is loaded. */
        uint64_t ggrp_unmap            : 1;  /**< [ 11: 11](R/W1C/H) PF_FUNC mapping not found error. Set when a load or store accesses an
                                                                 SSO LF register in BAR2 and SSO_PRIV_LF()_HWGRP_CFG does not have any
                                                                 matching entry.  When a request thus dropped, even if this bit is
                                                                 already set, SSO_AF_UNMAP_INFO is loaded. */
        uint64_t aw_multi              : 1;  /**< [ 10: 10](R/W1C/H) PF_FUNC map had double-hit error. Set when a coprocessor add-work is
                                                                 dropped due to SSO_PRIV_LF()_HWGRP_CFG having a double hit.
                                                                 When a request thus dropped, even if this bit is already set,
                                                                 SSO_AF_UNMAP_INFO is loaded. */
        uint64_t aw_unmap              : 1;  /**< [  9:  9](R/W1C/H) PF_FUNC mapping not found error. Set when a coprocessor add-work is
                                                                 dropped due to SSO_PRIV_LF()_HWGRP_CFG not having any matching mapping.
                                                                 When a request thus dropped, even if this bit is already set,
                                                                 SSO_AF_UNMAP_INFO is loaded. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1C/H) Add work dropped due to QTL being disabled, 0x0.  Any groups that
                                                                 experience this error are reported in SSO_AF_QCTLDIS_DIGEST(). */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1C/H) Add work dropped due to WQP being 0x0.  Any groups that experience
                                                                 this error are reported in SSO_AF_WQP0_DIGEST(). */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1C/H) Add work dropped due to 64 bit write to SSO_LF_GGRP_OP_ADD_WORK0 */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1C/H) Set when received add work with tag type is specified as EMPTY, or when
                                                                 SSO_AF_AW_INP_CTL[WA_DIS] is set and work is added from disabled coprocessor. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1C/H) Add work to disabled hardware group. An ADDWQ was received and dropped
                                                                 to a hardware group with SSO_AF_HWGRP()_IAQ_THR[RSVD_THR] = 0.  Any
                                                                 groups that experience this error are reported in
                                                                 SSO_AF_GRPDIS_DIGEST(). */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1C/H) Bad-fill-packet NCB error. NCB detected error on fill or spill data.
                                                                 Any groups that experience this error are reported in
                                                                 SSO_AF_BFPN_DIGEST(). */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1C/H) Bad-fill-packet error. The WAE CRC field was incorrect, or the XAQ
                                                                 next address was zero.  Any groups that experience this error are
                                                                 reported in SSO_AF_BFP_DIGEST(). */
        uint64_t npa                   : 1;  /**< [  1:  1](R/W1C/H) The NPA returned an error indication.  Any groups that experience this
                                                                 error are reported in SSO_AF_NPA_DIGEST().
                                                                 During the initialization phase, failure will be reported when receiving
                                                                 more than 3 null pointer errors for the same group,
                                                                 see SSO_AF_HWGRP()_AW_STATUS[INIT_FAIL]. Once initialization has
                                                                 completed, any subsequent NPA errors will be reported immediately,
                                                                 with no retries.  XAQ operation for the errored group will be disabled
                                                                 after NPA failures, see SSO_AF_HWGRP()_AW_CFG[RWEN]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t npa                   : 1;  /**< [  1:  1](R/W1C/H) The NPA returned an error indication.  Any groups that experience this
                                                                 error are reported in SSO_AF_NPA_DIGEST().
                                                                 During the initialization phase, failure will be reported when receiving
                                                                 more than 3 null pointer errors for the same group,
                                                                 see SSO_AF_HWGRP()_AW_STATUS[INIT_FAIL]. Once initialization has
                                                                 completed, any subsequent NPA errors will be reported immediately,
                                                                 with no retries.  XAQ operation for the errored group will be disabled
                                                                 after NPA failures, see SSO_AF_HWGRP()_AW_CFG[RWEN]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1C/H) Bad-fill-packet error. The WAE CRC field was incorrect, or the XAQ
                                                                 next address was zero.  Any groups that experience this error are
                                                                 reported in SSO_AF_BFP_DIGEST(). */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1C/H) Bad-fill-packet NCB error. NCB detected error on fill or spill data.
                                                                 Any groups that experience this error are reported in
                                                                 SSO_AF_BFPN_DIGEST(). */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1C/H) Add work to disabled hardware group. An ADDWQ was received and dropped
                                                                 to a hardware group with SSO_AF_HWGRP()_IAQ_THR[RSVD_THR] = 0.  Any
                                                                 groups that experience this error are reported in
                                                                 SSO_AF_GRPDIS_DIGEST(). */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1C/H) Set when received add work with tag type is specified as EMPTY, or when
                                                                 SSO_AF_AW_INP_CTL[WA_DIS] is set and work is added from disabled coprocessor. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1C/H) Add work dropped due to 64 bit write to SSO_LF_GGRP_OP_ADD_WORK0 */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1C/H) Add work dropped due to WQP being 0x0.  Any groups that experience
                                                                 this error are reported in SSO_AF_WQP0_DIGEST(). */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1C/H) Add work dropped due to QTL being disabled, 0x0.  Any groups that
                                                                 experience this error are reported in SSO_AF_QCTLDIS_DIGEST(). */
        uint64_t aw_unmap              : 1;  /**< [  9:  9](R/W1C/H) PF_FUNC mapping not found error. Set when a coprocessor add-work is
                                                                 dropped due to SSO_PRIV_LF()_HWGRP_CFG not having any matching mapping.
                                                                 When a request thus dropped, even if this bit is already set,
                                                                 SSO_AF_UNMAP_INFO is loaded. */
        uint64_t aw_multi              : 1;  /**< [ 10: 10](R/W1C/H) PF_FUNC map had double-hit error. Set when a coprocessor add-work is
                                                                 dropped due to SSO_PRIV_LF()_HWGRP_CFG having a double hit.
                                                                 When a request thus dropped, even if this bit is already set,
                                                                 SSO_AF_UNMAP_INFO is loaded. */
        uint64_t ggrp_unmap            : 1;  /**< [ 11: 11](R/W1C/H) PF_FUNC mapping not found error. Set when a load or store accesses an
                                                                 SSO LF register in BAR2 and SSO_PRIV_LF()_HWGRP_CFG does not have any
                                                                 matching entry.  When a request thus dropped, even if this bit is
                                                                 already set, SSO_AF_UNMAP_INFO is loaded. */
        uint64_t ggrp_multi            : 1;  /**< [ 12: 12](R/W1C/H) PF_FUNC map had double-hit error. Set when a load or store accesses an
                                                                 SSO LF register in BAR2 and SSO_PRIV_LF()_HWGRP_CFG has a double hit.
                                                                 When a request thus dropped, even if this bit is already set,
                                                                 SSO_AF_UNMAP_INFO is loaded. */
        uint64_t addwq_dropped_xaqen   : 1;  /**< [ 13: 13](R/W1C/H) Add work dropped due to XAQ pointers not yet initialized.  Any groups
                                                                 reporting this error are indicated in SSO_AF_XAQDIS_DIGEST(). */
        uint64_t flr_aq_cnt            : 1;  /**< [ 14: 14](R/W1C/H) An FLR was initiated, but SSO_LF_GGRP_AQ_CNT[AQ_CNT] != 0.  Any groups
                                                                 reporting this error are indicated in SSO_AF_FLR_AQ_DIGEST(). */
        uint64_t bfpp                  : 1;  /**< [ 15: 15](R/W1C/H) Bad-fill-packet NCB error. NCB detected poison on fill data.  Any
                                                                 groups that experience this error are reported in SSO_AF_POISON(). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_err0_s cn; */
};
typedef union bdk_sso_af_err0 bdk_sso_af_err0_t;

#define BDK_SSO_AF_ERR0 BDK_SSO_AF_ERR0_FUNC()
static inline uint64_t BDK_SSO_AF_ERR0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ERR0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001220ll;
    __bdk_csr_fatal("SSO_AF_ERR0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ERR0 bdk_sso_af_err0_t
#define bustype_BDK_SSO_AF_ERR0 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ERR0 "SSO_AF_ERR0"
#define device_bar_BDK_SSO_AF_ERR0 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ERR0 0
#define arguments_BDK_SSO_AF_ERR0 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_err0_ena_w1c
 *
 * SSO AF Error 0 Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_sso_af_err0_ena_w1c
{
    uint64_t u;
    struct bdk_sso_af_err0_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t bfpp                  : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[BFPP]. */
        uint64_t flr_aq_cnt            : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[FLR_AQ_CNT]. */
        uint64_t addwq_dropped_xaqen   : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[ADDWQ_DROPPED_XAQEN]. */
        uint64_t ggrp_multi            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[GGRP_MULTI]. */
        uint64_t ggrp_unmap            : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[GGRP_UNMAP]. */
        uint64_t aw_multi              : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[AW_MULTI]. */
        uint64_t aw_unmap              : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[AW_UNMAP]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[ADDWQ_DROPPED]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[AWEMPTY]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[GRPDIS]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[BFPN]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[BFP]. */
        uint64_t npa                   : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[NPA]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t npa                   : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[NPA]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[BFP]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[BFPN]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[GRPDIS]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[AWEMPTY]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[ADDWQ_DROPPED]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t aw_unmap              : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[AW_UNMAP]. */
        uint64_t aw_multi              : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[AW_MULTI]. */
        uint64_t ggrp_unmap            : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[GGRP_UNMAP]. */
        uint64_t ggrp_multi            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[GGRP_MULTI]. */
        uint64_t addwq_dropped_xaqen   : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[ADDWQ_DROPPED_XAQEN]. */
        uint64_t flr_aq_cnt            : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[FLR_AQ_CNT]. */
        uint64_t bfpp                  : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for SSO_AF_ERR0[BFPP]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_err0_ena_w1c_s cn; */
};
typedef union bdk_sso_af_err0_ena_w1c bdk_sso_af_err0_ena_w1c_t;

#define BDK_SSO_AF_ERR0_ENA_W1C BDK_SSO_AF_ERR0_ENA_W1C_FUNC()
static inline uint64_t BDK_SSO_AF_ERR0_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ERR0_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001230ll;
    __bdk_csr_fatal("SSO_AF_ERR0_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ERR0_ENA_W1C bdk_sso_af_err0_ena_w1c_t
#define bustype_BDK_SSO_AF_ERR0_ENA_W1C BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ERR0_ENA_W1C "SSO_AF_ERR0_ENA_W1C"
#define device_bar_BDK_SSO_AF_ERR0_ENA_W1C 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ERR0_ENA_W1C 0
#define arguments_BDK_SSO_AF_ERR0_ENA_W1C -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_err0_ena_w1s
 *
 * SSO AF Error 0 Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_sso_af_err0_ena_w1s
{
    uint64_t u;
    struct bdk_sso_af_err0_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t bfpp                  : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[BFPP]. */
        uint64_t flr_aq_cnt            : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[FLR_AQ_CNT]. */
        uint64_t addwq_dropped_xaqen   : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[ADDWQ_DROPPED_XAQEN]. */
        uint64_t ggrp_multi            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[GGRP_MULTI]. */
        uint64_t ggrp_unmap            : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[GGRP_UNMAP]. */
        uint64_t aw_multi              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[AW_MULTI]. */
        uint64_t aw_unmap              : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[AW_UNMAP]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[ADDWQ_DROPPED]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[AWEMPTY]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[GRPDIS]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[BFPN]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[BFP]. */
        uint64_t npa                   : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[NPA]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t npa                   : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[NPA]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[BFP]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[BFPN]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[GRPDIS]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[AWEMPTY]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[ADDWQ_DROPPED]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t aw_unmap              : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[AW_UNMAP]. */
        uint64_t aw_multi              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[AW_MULTI]. */
        uint64_t ggrp_unmap            : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[GGRP_UNMAP]. */
        uint64_t ggrp_multi            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[GGRP_MULTI]. */
        uint64_t addwq_dropped_xaqen   : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[ADDWQ_DROPPED_XAQEN]. */
        uint64_t flr_aq_cnt            : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[FLR_AQ_CNT]. */
        uint64_t bfpp                  : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for SSO_AF_ERR0[BFPP]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_err0_ena_w1s_s cn; */
};
typedef union bdk_sso_af_err0_ena_w1s bdk_sso_af_err0_ena_w1s_t;

#define BDK_SSO_AF_ERR0_ENA_W1S BDK_SSO_AF_ERR0_ENA_W1S_FUNC()
static inline uint64_t BDK_SSO_AF_ERR0_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ERR0_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001238ll;
    __bdk_csr_fatal("SSO_AF_ERR0_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ERR0_ENA_W1S bdk_sso_af_err0_ena_w1s_t
#define bustype_BDK_SSO_AF_ERR0_ENA_W1S BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ERR0_ENA_W1S "SSO_AF_ERR0_ENA_W1S"
#define device_bar_BDK_SSO_AF_ERR0_ENA_W1S 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ERR0_ENA_W1S 0
#define arguments_BDK_SSO_AF_ERR0_ENA_W1S -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_err0_w1s
 *
 * SSO AF Error 0 Set Register
 * This register sets interrupt bits.
 */
union bdk_sso_af_err0_w1s
{
    uint64_t u;
    struct bdk_sso_af_err0_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t bfpp                  : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets SSO_AF_ERR0[BFPP]. */
        uint64_t flr_aq_cnt            : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets SSO_AF_ERR0[FLR_AQ_CNT]. */
        uint64_t addwq_dropped_xaqen   : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets SSO_AF_ERR0[ADDWQ_DROPPED_XAQEN]. */
        uint64_t ggrp_multi            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets SSO_AF_ERR0[GGRP_MULTI]. */
        uint64_t ggrp_unmap            : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets SSO_AF_ERR0[GGRP_UNMAP]. */
        uint64_t aw_multi              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSO_AF_ERR0[AW_MULTI]. */
        uint64_t aw_unmap              : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSO_AF_ERR0[AW_UNMAP]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSO_AF_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSO_AF_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSO_AF_ERR0[ADDWQ_DROPPED]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSO_AF_ERR0[AWEMPTY]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSO_AF_ERR0[GRPDIS]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSO_AF_ERR0[BFPN]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSO_AF_ERR0[BFP]. */
        uint64_t npa                   : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSO_AF_ERR0[NPA]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t npa                   : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSO_AF_ERR0[NPA]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSO_AF_ERR0[BFP]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSO_AF_ERR0[BFPN]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSO_AF_ERR0[GRPDIS]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSO_AF_ERR0[AWEMPTY]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSO_AF_ERR0[ADDWQ_DROPPED]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSO_AF_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSO_AF_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t aw_unmap              : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSO_AF_ERR0[AW_UNMAP]. */
        uint64_t aw_multi              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSO_AF_ERR0[AW_MULTI]. */
        uint64_t ggrp_unmap            : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets SSO_AF_ERR0[GGRP_UNMAP]. */
        uint64_t ggrp_multi            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets SSO_AF_ERR0[GGRP_MULTI]. */
        uint64_t addwq_dropped_xaqen   : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets SSO_AF_ERR0[ADDWQ_DROPPED_XAQEN]. */
        uint64_t flr_aq_cnt            : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets SSO_AF_ERR0[FLR_AQ_CNT]. */
        uint64_t bfpp                  : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets SSO_AF_ERR0[BFPP]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_err0_w1s_s cn; */
};
typedef union bdk_sso_af_err0_w1s bdk_sso_af_err0_w1s_t;

#define BDK_SSO_AF_ERR0_W1S BDK_SSO_AF_ERR0_W1S_FUNC()
static inline uint64_t BDK_SSO_AF_ERR0_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ERR0_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001228ll;
    __bdk_csr_fatal("SSO_AF_ERR0_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ERR0_W1S bdk_sso_af_err0_w1s_t
#define bustype_BDK_SSO_AF_ERR0_W1S BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ERR0_W1S "SSO_AF_ERR0_W1S"
#define device_bar_BDK_SSO_AF_ERR0_W1S 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ERR0_W1S 0
#define arguments_BDK_SSO_AF_ERR0_W1S -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_err2
 *
 * SSO AF Error 2 Register
 * This register contains workslot related errors.
 */
union bdk_sso_af_err2
{
    uint64_t u;
    struct bdk_sso_af_err2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t ws_multi              : 1;  /**< [ 31: 31](R/W1C/H) Workslot access found HWS PF_FUNC map had double-hit error.  Set when
                                                                 SSOW_PRIV_LF()_HWS_CFG has a double hit for the PF_FUNC and SLOT from
                                                                 the address for an SSOW load or store. When this bit is set,
                                                                 SSO_AF_UNMAP_INFO3 is loaded. */
        uint64_t ws_unmap              : 1;  /**< [ 30: 30](R/W1C/H) Workslot access found no HWS PF_FUNC mapping. Set when
                                                                 SSOW_PRIV_LF()_HWS_CFG has no match for the PF_FUNC and SLOT from the
                                                                 address for an SSOW load or store. When this bit is set,
                                                                 SSO_AF_UNMAP_INFO3 is loaded. */
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](R/W1C/H) Workslot operation found HWGRP PF_FUNC map had double-hit error for
                                                                 supplied guest group. Set when SSO_PRIV_LF()_HWGRP_CFG has a double
                                                                 hit for the GGRP parameter in a workslot operation and the workslot's
                                                                 PF_FUNC. When this bit is set, SSO_AF_UNMAP_INFO2 is loaded.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_GMULTI_DIGEST(). */
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](R/W1C/H) Workslot operation found no HWGRP PF_FUNC mapping for
                                                                 supplied guest group. Set when SSO_PRIV_LF()_HWGRP_CFG has no match
                                                                 for the GGRP parameter in a workslot operation and the workslot's
                                                                 PF_FUNC. When this bit is set, SSO_AF_UNMAP_INFO2 is loaded.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_GUNMAP_DIGEST(). */
        uint64_t reserved_17_27        : 11;
        uint64_t ws_flr_ni             : 1;  /**< [ 16: 16](R/W1C/H) SSOW_AF_LF_HWS_RST was attempted for a workslot that was not idle,
                                                                 i.e., has a pending operation.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_NI_DIGEST(). */
        uint64_t ws_flr_ne             : 1;  /**< [ 15: 15](R/W1C/H) SSOW_AF_LF_HWS_RST was attempted for a workslot that was not empty.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_NE_DIGEST(). */
        uint64_t alloc_we_dis          : 1;  /**< [ 14: 14](R/W1C/H) Attempted ALLOC_WE when disabled.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_AWE_DIGEST(). */
        uint64_t early_op              : 1;  /**< [ 13: 13](R/W1C/H) Attempted access before reset was complete. */
        uint64_t gw_idx_dis            : 1;  /**< [ 12: 12](R/W1C/H) Attempted GET_WORK(indexed) operation when disabled.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_GWI_DIGEST(). */
        uint64_t reserved_0_11         : 12;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_11         : 12;
        uint64_t gw_idx_dis            : 1;  /**< [ 12: 12](R/W1C/H) Attempted GET_WORK(indexed) operation when disabled.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_GWI_DIGEST(). */
        uint64_t early_op              : 1;  /**< [ 13: 13](R/W1C/H) Attempted access before reset was complete. */
        uint64_t alloc_we_dis          : 1;  /**< [ 14: 14](R/W1C/H) Attempted ALLOC_WE when disabled.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_AWE_DIGEST(). */
        uint64_t ws_flr_ne             : 1;  /**< [ 15: 15](R/W1C/H) SSOW_AF_LF_HWS_RST was attempted for a workslot that was not empty.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_NE_DIGEST(). */
        uint64_t ws_flr_ni             : 1;  /**< [ 16: 16](R/W1C/H) SSOW_AF_LF_HWS_RST was attempted for a workslot that was not idle,
                                                                 i.e., has a pending operation.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_NI_DIGEST(). */
        uint64_t reserved_17_27        : 11;
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](R/W1C/H) Workslot operation found no HWGRP PF_FUNC mapping for
                                                                 supplied guest group. Set when SSO_PRIV_LF()_HWGRP_CFG has no match
                                                                 for the GGRP parameter in a workslot operation and the workslot's
                                                                 PF_FUNC. When this bit is set, SSO_AF_UNMAP_INFO2 is loaded.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_GUNMAP_DIGEST(). */
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](R/W1C/H) Workslot operation found HWGRP PF_FUNC map had double-hit error for
                                                                 supplied guest group. Set when SSO_PRIV_LF()_HWGRP_CFG has a double
                                                                 hit for the GGRP parameter in a workslot operation and the workslot's
                                                                 PF_FUNC. When this bit is set, SSO_AF_UNMAP_INFO2 is loaded.

                                                                 Any workslot that experiences this error is recorded in
                                                                 SSO_AF_WS_GMULTI_DIGEST(). */
        uint64_t ws_unmap              : 1;  /**< [ 30: 30](R/W1C/H) Workslot access found no HWS PF_FUNC mapping. Set when
                                                                 SSOW_PRIV_LF()_HWS_CFG has no match for the PF_FUNC and SLOT from the
                                                                 address for an SSOW load or store. When this bit is set,
                                                                 SSO_AF_UNMAP_INFO3 is loaded. */
        uint64_t ws_multi              : 1;  /**< [ 31: 31](R/W1C/H) Workslot access found HWS PF_FUNC map had double-hit error.  Set when
                                                                 SSOW_PRIV_LF()_HWS_CFG has a double hit for the PF_FUNC and SLOT from
                                                                 the address for an SSOW load or store. When this bit is set,
                                                                 SSO_AF_UNMAP_INFO3 is loaded. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_err2_s cn; */
};
typedef union bdk_sso_af_err2 bdk_sso_af_err2_t;

#define BDK_SSO_AF_ERR2 BDK_SSO_AF_ERR2_FUNC()
static inline uint64_t BDK_SSO_AF_ERR2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ERR2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001260ll;
    __bdk_csr_fatal("SSO_AF_ERR2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ERR2 bdk_sso_af_err2_t
#define bustype_BDK_SSO_AF_ERR2 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ERR2 "SSO_AF_ERR2"
#define device_bar_BDK_SSO_AF_ERR2 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ERR2 0
#define arguments_BDK_SSO_AF_ERR2 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_err2_ena_w1c
 *
 * SSO AF Error 2 Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_sso_af_err2_ena_w1c
{
    uint64_t u;
    struct bdk_sso_af_err2_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t ws_multi              : 1;  /**< [ 31: 31](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_MULTI]. */
        uint64_t ws_unmap              : 1;  /**< [ 30: 30](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_UNMAP]. */
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_GRP_MULTI]. */
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_GRP_UNMAP]. */
        uint64_t reserved_17_27        : 11;
        uint64_t ws_flr_ni             : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_FLR_NI]. */
        uint64_t ws_flr_ne             : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_FLR_NE]. */
        uint64_t alloc_we_dis          : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[ALLOC_WE_DIS]. */
        uint64_t early_op              : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[EARLY_OP]. */
        uint64_t gw_idx_dis            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[GW_IDX_DIS]. */
        uint64_t reserved_0_11         : 12;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_11         : 12;
        uint64_t gw_idx_dis            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[GW_IDX_DIS]. */
        uint64_t early_op              : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[EARLY_OP]. */
        uint64_t alloc_we_dis          : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[ALLOC_WE_DIS]. */
        uint64_t ws_flr_ne             : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_FLR_NE]. */
        uint64_t ws_flr_ni             : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_FLR_NI]. */
        uint64_t reserved_17_27        : 11;
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_GRP_UNMAP]. */
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_GRP_MULTI]. */
        uint64_t ws_unmap              : 1;  /**< [ 30: 30](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_UNMAP]. */
        uint64_t ws_multi              : 1;  /**< [ 31: 31](R/W1C/H) Reads or clears enable for SSO_AF_ERR2[WS_MULTI]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_err2_ena_w1c_s cn; */
};
typedef union bdk_sso_af_err2_ena_w1c bdk_sso_af_err2_ena_w1c_t;

#define BDK_SSO_AF_ERR2_ENA_W1C BDK_SSO_AF_ERR2_ENA_W1C_FUNC()
static inline uint64_t BDK_SSO_AF_ERR2_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ERR2_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001270ll;
    __bdk_csr_fatal("SSO_AF_ERR2_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ERR2_ENA_W1C bdk_sso_af_err2_ena_w1c_t
#define bustype_BDK_SSO_AF_ERR2_ENA_W1C BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ERR2_ENA_W1C "SSO_AF_ERR2_ENA_W1C"
#define device_bar_BDK_SSO_AF_ERR2_ENA_W1C 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ERR2_ENA_W1C 0
#define arguments_BDK_SSO_AF_ERR2_ENA_W1C -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_err2_ena_w1s
 *
 * SSO AF Error 2 Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_sso_af_err2_ena_w1s
{
    uint64_t u;
    struct bdk_sso_af_err2_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t ws_multi              : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_MULTI]. */
        uint64_t ws_unmap              : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_UNMAP]. */
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_GRP_MULTI]. */
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_GRP_UNMAP]. */
        uint64_t reserved_17_27        : 11;
        uint64_t ws_flr_ni             : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_FLR_NI]. */
        uint64_t ws_flr_ne             : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_FLR_NE]. */
        uint64_t alloc_we_dis          : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[ALLOC_WE_DIS]. */
        uint64_t early_op              : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[EARLY_OP]. */
        uint64_t gw_idx_dis            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[GW_IDX_DIS]. */
        uint64_t reserved_0_11         : 12;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_11         : 12;
        uint64_t gw_idx_dis            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[GW_IDX_DIS]. */
        uint64_t early_op              : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[EARLY_OP]. */
        uint64_t alloc_we_dis          : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[ALLOC_WE_DIS]. */
        uint64_t ws_flr_ne             : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_FLR_NE]. */
        uint64_t ws_flr_ni             : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_FLR_NI]. */
        uint64_t reserved_17_27        : 11;
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_GRP_UNMAP]. */
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_GRP_MULTI]. */
        uint64_t ws_unmap              : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_UNMAP]. */
        uint64_t ws_multi              : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets enable for SSO_AF_ERR2[WS_MULTI]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_err2_ena_w1s_s cn; */
};
typedef union bdk_sso_af_err2_ena_w1s bdk_sso_af_err2_ena_w1s_t;

#define BDK_SSO_AF_ERR2_ENA_W1S BDK_SSO_AF_ERR2_ENA_W1S_FUNC()
static inline uint64_t BDK_SSO_AF_ERR2_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ERR2_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001278ll;
    __bdk_csr_fatal("SSO_AF_ERR2_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ERR2_ENA_W1S bdk_sso_af_err2_ena_w1s_t
#define bustype_BDK_SSO_AF_ERR2_ENA_W1S BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ERR2_ENA_W1S "SSO_AF_ERR2_ENA_W1S"
#define device_bar_BDK_SSO_AF_ERR2_ENA_W1S 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ERR2_ENA_W1S 0
#define arguments_BDK_SSO_AF_ERR2_ENA_W1S -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_err2_w1s
 *
 * SSO AF Error 2 Set Register
 * This register sets interrupt bits.
 */
union bdk_sso_af_err2_w1s
{
    uint64_t u;
    struct bdk_sso_af_err2_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t ws_multi              : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_MULTI]. */
        uint64_t ws_unmap              : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_UNMAP]. */
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_GRP_MULTI]. */
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_GRP_UNMAP]. */
        uint64_t reserved_17_27        : 11;
        uint64_t ws_flr_ni             : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_FLR_NI]. */
        uint64_t ws_flr_ne             : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_FLR_NE]. */
        uint64_t alloc_we_dis          : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets SSO_AF_ERR2[ALLOC_WE_DIS]. */
        uint64_t early_op              : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets SSO_AF_ERR2[EARLY_OP]. */
        uint64_t gw_idx_dis            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets SSO_AF_ERR2[GW_IDX_DIS]. */
        uint64_t reserved_0_11         : 12;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_11         : 12;
        uint64_t gw_idx_dis            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets SSO_AF_ERR2[GW_IDX_DIS]. */
        uint64_t early_op              : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets SSO_AF_ERR2[EARLY_OP]. */
        uint64_t alloc_we_dis          : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets SSO_AF_ERR2[ALLOC_WE_DIS]. */
        uint64_t ws_flr_ne             : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_FLR_NE]. */
        uint64_t ws_flr_ni             : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_FLR_NI]. */
        uint64_t reserved_17_27        : 11;
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_GRP_UNMAP]. */
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_GRP_MULTI]. */
        uint64_t ws_unmap              : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_UNMAP]. */
        uint64_t ws_multi              : 1;  /**< [ 31: 31](R/W1S/H) Reads or sets SSO_AF_ERR2[WS_MULTI]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_err2_w1s_s cn; */
};
typedef union bdk_sso_af_err2_w1s bdk_sso_af_err2_w1s_t;

#define BDK_SSO_AF_ERR2_W1S BDK_SSO_AF_ERR2_W1S_FUNC()
static inline uint64_t BDK_SSO_AF_ERR2_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_ERR2_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001268ll;
    __bdk_csr_fatal("SSO_AF_ERR2_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_ERR2_W1S bdk_sso_af_err2_w1s_t
#define bustype_BDK_SSO_AF_ERR2_W1S BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_ERR2_W1S "SSO_AF_ERR2_W1S"
#define device_bar_BDK_SSO_AF_ERR2_W1S 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_ERR2_W1S 0
#define arguments_BDK_SSO_AF_ERR2_W1S -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_flr_aq_digest#
 *
 * SSO AF FLR_AQ_CNT Error Summary Registers
 * One bit per HWGRP to indicate which groups have reported an SSO_AF_ERR0[FLR_AQ_CNT] error.
 */
union bdk_sso_af_flr_aq_digestx
{
    uint64_t u;
    struct bdk_sso_af_flr_aq_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_flr_aq_digestx_s cn; */
};
typedef union bdk_sso_af_flr_aq_digestx bdk_sso_af_flr_aq_digestx_t;

static inline uint64_t BDK_SSO_AF_FLR_AQ_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_FLR_AQ_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070901200ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_FLR_AQ_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_FLR_AQ_DIGESTX(a) bdk_sso_af_flr_aq_digestx_t
#define bustype_BDK_SSO_AF_FLR_AQ_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_FLR_AQ_DIGESTX(a) "SSO_AF_FLR_AQ_DIGESTX"
#define device_bar_BDK_SSO_AF_FLR_AQ_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_FLR_AQ_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_FLR_AQ_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_flr_aq_digest#_w1s
 *
 * SSO AF FLR_AQ_CNT Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_flr_aq_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_flr_aq_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_FLR_AQ_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_FLR_AQ_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_flr_aq_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_flr_aq_digestx_w1s bdk_sso_af_flr_aq_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_FLR_AQ_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_FLR_AQ_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070901300ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_FLR_AQ_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_FLR_AQ_DIGESTX_W1S(a) bdk_sso_af_flr_aq_digestx_w1s_t
#define bustype_BDK_SSO_AF_FLR_AQ_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_FLR_AQ_DIGESTX_W1S(a) "SSO_AF_FLR_AQ_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_FLR_AQ_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_FLR_AQ_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_FLR_AQ_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_grpdis_digest#
 *
 * SSO AF GRPDIS Error Summary Registers
 * One bit per HWGRP to indicate which groups have reported an SSO_AF_ERR0[GRPDIS] error.
 */
union bdk_sso_af_grpdis_digestx
{
    uint64_t u;
    struct bdk_sso_af_grpdis_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_grpdis_digestx_s cn; */
};
typedef union bdk_sso_af_grpdis_digestx bdk_sso_af_grpdis_digestx_t;

static inline uint64_t BDK_SSO_AF_GRPDIS_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_GRPDIS_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900600ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_GRPDIS_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_GRPDIS_DIGESTX(a) bdk_sso_af_grpdis_digestx_t
#define bustype_BDK_SSO_AF_GRPDIS_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_GRPDIS_DIGESTX(a) "SSO_AF_GRPDIS_DIGESTX"
#define device_bar_BDK_SSO_AF_GRPDIS_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_GRPDIS_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_GRPDIS_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_grpdis_digest#_w1s
 *
 * SSO AF GRPDIS Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_grpdis_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_grpdis_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_GRPDIS_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_GRPDIS_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_grpdis_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_grpdis_digestx_w1s bdk_sso_af_grpdis_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_GRPDIS_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_GRPDIS_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900700ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_GRPDIS_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_GRPDIS_DIGESTX_W1S(a) bdk_sso_af_grpdis_digestx_w1s_t
#define bustype_BDK_SSO_AF_GRPDIS_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_GRPDIS_DIGESTX_W1S(a) "SSO_AF_GRPDIS_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_GRPDIS_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_GRPDIS_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_GRPDIS_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_gw_eco
 *
 * INTERNAL: SSO AF GW ECO Register
 */
union bdk_sso_af_gw_eco
{
    uint64_t u;
    struct bdk_sso_af_gw_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_gw_eco_s cn; */
};
typedef union bdk_sso_af_gw_eco bdk_sso_af_gw_eco_t;

#define BDK_SSO_AF_GW_ECO BDK_SSO_AF_GW_ECO_FUNC()
static inline uint64_t BDK_SSO_AF_GW_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_GW_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001038ll;
    __bdk_csr_fatal("SSO_AF_GW_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_GW_ECO bdk_sso_af_gw_eco_t
#define bustype_BDK_SSO_AF_GW_ECO BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_GW_ECO "SSO_AF_GW_ECO"
#define device_bar_BDK_SSO_AF_GW_ECO 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_GW_ECO 0
#define arguments_BDK_SSO_AF_GW_ECO -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_gwe_cfg
 *
 * SSO AF Get-Work Examiner Configuration Register
 * This register controls the operation of the get-work examiner (GWE).
 */
union bdk_sso_af_gwe_cfg
{
    uint64_t u;
    struct bdk_sso_af_gwe_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t dis_wgt_credit        : 1;  /**< [  8:  8](R/W) Disable hardware group weight credits. When set, groups have infinite weight credit. */
        uint64_t ws_retries            : 8;  /**< [  7:  0](R/W) Workslot retries. When a given workslot performs this number of retries without
                                                                 successfully finding work then NO_WORK will be returned. Values zero, one, two,
                                                                 and three are reserved. */
#else /* Word 0 - Little Endian */
        uint64_t ws_retries            : 8;  /**< [  7:  0](R/W) Workslot retries. When a given workslot performs this number of retries without
                                                                 successfully finding work then NO_WORK will be returned. Values zero, one, two,
                                                                 and three are reserved. */
        uint64_t dis_wgt_credit        : 1;  /**< [  8:  8](R/W) Disable hardware group weight credits. When set, groups have infinite weight credit. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_gwe_cfg_s cn; */
};
typedef union bdk_sso_af_gwe_cfg bdk_sso_af_gwe_cfg_t;

#define BDK_SSO_AF_GWE_CFG BDK_SSO_AF_GWE_CFG_FUNC()
static inline uint64_t BDK_SSO_AF_GWE_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_GWE_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001098ll;
    __bdk_csr_fatal("SSO_AF_GWE_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_GWE_CFG bdk_sso_af_gwe_cfg_t
#define bustype_BDK_SSO_AF_GWE_CFG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_GWE_CFG "SSO_AF_GWE_CFG"
#define device_bar_BDK_SSO_AF_GWE_CFG 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_GWE_CFG 0
#define arguments_BDK_SSO_AF_GWE_CFG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_gwe_random
 *
 * SSO AF Get-Work Examiner Random Register
 * This register contains the random search start position for the get-work examiner (GWE).
 */
union bdk_sso_af_gwe_random
{
    uint64_t u;
    struct bdk_sso_af_gwe_random_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rnd                   : 16; /**< [ 15:  0](R/W/H) Current random value, with low eight bits indicating first hardware group to start
                                                                 next get-work search at. Implementation defined as to when changes.
                                                                 For diagnostic use only, must not be zero.

                                                                 Internal:
                                                                 Changes on each work search, even if unsuccessful or retried.

                                                                 Uses 16, 15, 13, 4 tap LFSR (this choice is important to
                                                                 ensure even hardware group probabilities) with the formula:
                                                                 _ grp_to_start_arb_at = RND[7:0].
                                                                 _ RND_next[15:8] = RND[7:0].
                                                                 _ RND_next[7] = ^(RND[15:0] & 0xd008).
                                                                 _ RND_next[6] = ^(RND[15:0] & 0x6804).
                                                                 _ RND_next[5] = ^(RND[15:0] & 0x3402).
                                                                 _ RND_next[4] = ^(RND[15:0] & 0x1a01).
                                                                 _ RND_next[3] = ^(RND[15:0] & 0xdd08).
                                                                 _ RND_next[2] = ^(RND[15:0] & 0x6e84).
                                                                 _ RND_next[1] = ^(RND[15:0] & 0x3742).
                                                                 _ RND_next[0] = ^(RND[15:0] & 0x1ba1). */
#else /* Word 0 - Little Endian */
        uint64_t rnd                   : 16; /**< [ 15:  0](R/W/H) Current random value, with low eight bits indicating first hardware group to start
                                                                 next get-work search at. Implementation defined as to when changes.
                                                                 For diagnostic use only, must not be zero.

                                                                 Internal:
                                                                 Changes on each work search, even if unsuccessful or retried.

                                                                 Uses 16, 15, 13, 4 tap LFSR (this choice is important to
                                                                 ensure even hardware group probabilities) with the formula:
                                                                 _ grp_to_start_arb_at = RND[7:0].
                                                                 _ RND_next[15:8] = RND[7:0].
                                                                 _ RND_next[7] = ^(RND[15:0] & 0xd008).
                                                                 _ RND_next[6] = ^(RND[15:0] & 0x6804).
                                                                 _ RND_next[5] = ^(RND[15:0] & 0x3402).
                                                                 _ RND_next[4] = ^(RND[15:0] & 0x1a01).
                                                                 _ RND_next[3] = ^(RND[15:0] & 0xdd08).
                                                                 _ RND_next[2] = ^(RND[15:0] & 0x6e84).
                                                                 _ RND_next[1] = ^(RND[15:0] & 0x3742).
                                                                 _ RND_next[0] = ^(RND[15:0] & 0x1ba1). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_gwe_random_s cn; */
};
typedef union bdk_sso_af_gwe_random bdk_sso_af_gwe_random_t;

#define BDK_SSO_AF_GWE_RANDOM BDK_SSO_AF_GWE_RANDOM_FUNC()
static inline uint64_t BDK_SSO_AF_GWE_RANDOM_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_GWE_RANDOM_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700010b0ll;
    __bdk_csr_fatal("SSO_AF_GWE_RANDOM", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_GWE_RANDOM bdk_sso_af_gwe_random_t
#define bustype_BDK_SSO_AF_GWE_RANDOM BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_GWE_RANDOM "SSO_AF_GWE_RANDOM"
#define device_bar_BDK_SSO_AF_GWE_RANDOM 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_GWE_RANDOM 0
#define arguments_BDK_SSO_AF_GWE_RANDOM -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_gws_inv
 *
 * SSO AF Guest Workslot SAI Invalidate Register
 * Sends an SAI Invalidate request to a guest workslot.
 */
union bdk_sso_af_gws_inv
{
    uint64_t u;
    struct bdk_sso_af_gws_inv_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t pf_func               : 16; /**< [ 31: 16](WO) PF_FUNC of GWS to be invalidated. */
        uint64_t reserved_12_15        : 4;
        uint64_t slot                  : 8;  /**< [ 11:  4](WO) Slot of GWS to be invalidated. */
        uint64_t reserved_1_3          : 3;
        uint64_t sai_inval             : 1;  /**< [  0:  0](WO) When written to one, invalidate any GW cache entries associated with this HWS. */
#else /* Word 0 - Little Endian */
        uint64_t sai_inval             : 1;  /**< [  0:  0](WO) When written to one, invalidate any GW cache entries associated with this HWS. */
        uint64_t reserved_1_3          : 3;
        uint64_t slot                  : 8;  /**< [ 11:  4](WO) Slot of GWS to be invalidated. */
        uint64_t reserved_12_15        : 4;
        uint64_t pf_func               : 16; /**< [ 31: 16](WO) PF_FUNC of GWS to be invalidated. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_gws_inv_s cn; */
};
typedef union bdk_sso_af_gws_inv bdk_sso_af_gws_inv_t;

#define BDK_SSO_AF_GWS_INV BDK_SSO_AF_GWS_INV_FUNC()
static inline uint64_t BDK_SSO_AF_GWS_INV_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_GWS_INV_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_1))
        return 0x840070001060ll;
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X))
        return 0x840070001060ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x840070001060ll;
    if (bdk_is_model(OCTEONTX_CNF95XX))
        return 0x840070001060ll;
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x840070001060ll;
    __bdk_csr_fatal("SSO_AF_GWS_INV", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_GWS_INV bdk_sso_af_gws_inv_t
#define bustype_BDK_SSO_AF_GWS_INV BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_GWS_INV "SSO_AF_GWS_INV"
#define device_bar_BDK_SSO_AF_GWS_INV 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_GWS_INV 0
#define arguments_BDK_SSO_AF_GWS_INV -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_aw_cfg
 *
 * SSO AF Per-Group Add-Work Configuration Register
 * This register controls the operation of the add-work block (AW).
 */
union bdk_sso_af_hwgrpx_aw_cfg
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_aw_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t swtag_dis             : 1;  /**< [ 10: 10](R/W) Disallow SWTAG operations to this group when set. */
        uint64_t rd_psn_ign            : 1;  /**< [  9:  9](R/W) Ignore POISON when reading XAQ entries. */
        uint64_t reserved_8            : 1;
        uint64_t lol                   : 1;  /**< [  7:  7](R/W) Reserved. */
        uint64_t xaq_alloc_dis         : 1;  /**< [  6:  6](R/W) Disable NPA alloc requests to fill the SSO page cache.
                                                                 When this bit is set, all existing cached free pointers will be returned to NPA,
                                                                 software needs to wait for SSO_AF_HWGRP()_AW_STATUS[XAQ_BUF_CACHED] to be zero
                                                                 before sending traffic to that group. */
        uint64_t reserved_5            : 1;
        uint64_t xaq_byp_dis           : 1;  /**< [  4:  4](R/W) Disable bypass path in add-work engine. For diagnostic use only. */
        uint64_t stt                   : 1;  /**< [  3:  3](R/W) Use STT to bypass LLC allocation for XAQ store operations. When this bit is not set it uses STF. */
        uint64_t ldt                   : 1;  /**< [  2:  2](R/W) Use LDT to bypass LLC allocation for XAQ load operations when [LDWB] is not
                                                                 set. When [LDT] and [LDWB] are both clear, uses LDD load type. */
        uint64_t ldwb                  : 1;  /**< [  1:  1](R/W) When reading XAQ cache lines, use LDWB transactions to invalidate the cache
                                                                 line. When clear, use [LDT] to determine load type. */
        uint64_t rwen                  : 1;  /**< [  0:  0](R/W/H) Enable XAQ operations. This bit should be set after SSO_AF_XAQ()_HEAD_PTR and
                                                                 SSO_AF_XAQ()_TAIL_PTR have been programmed. If cleared, all cached buffers will be
                                                                 returned to NPA as soon as possible, and TAQ arbitration is simplified. */
#else /* Word 0 - Little Endian */
        uint64_t rwen                  : 1;  /**< [  0:  0](R/W/H) Enable XAQ operations. This bit should be set after SSO_AF_XAQ()_HEAD_PTR and
                                                                 SSO_AF_XAQ()_TAIL_PTR have been programmed. If cleared, all cached buffers will be
                                                                 returned to NPA as soon as possible, and TAQ arbitration is simplified. */
        uint64_t ldwb                  : 1;  /**< [  1:  1](R/W) When reading XAQ cache lines, use LDWB transactions to invalidate the cache
                                                                 line. When clear, use [LDT] to determine load type. */
        uint64_t ldt                   : 1;  /**< [  2:  2](R/W) Use LDT to bypass LLC allocation for XAQ load operations when [LDWB] is not
                                                                 set. When [LDT] and [LDWB] are both clear, uses LDD load type. */
        uint64_t stt                   : 1;  /**< [  3:  3](R/W) Use STT to bypass LLC allocation for XAQ store operations. When this bit is not set it uses STF. */
        uint64_t xaq_byp_dis           : 1;  /**< [  4:  4](R/W) Disable bypass path in add-work engine. For diagnostic use only. */
        uint64_t reserved_5            : 1;
        uint64_t xaq_alloc_dis         : 1;  /**< [  6:  6](R/W) Disable NPA alloc requests to fill the SSO page cache.
                                                                 When this bit is set, all existing cached free pointers will be returned to NPA,
                                                                 software needs to wait for SSO_AF_HWGRP()_AW_STATUS[XAQ_BUF_CACHED] to be zero
                                                                 before sending traffic to that group. */
        uint64_t lol                   : 1;  /**< [  7:  7](R/W) Reserved. */
        uint64_t reserved_8            : 1;
        uint64_t rd_psn_ign            : 1;  /**< [  9:  9](R/W) Ignore POISON when reading XAQ entries. */
        uint64_t swtag_dis             : 1;  /**< [ 10: 10](R/W) Disallow SWTAG operations to this group when set. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_aw_cfg_s cn9; */
    struct bdk_sso_af_hwgrpx_aw_cfg_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t rd_psn_ign            : 1;  /**< [  9:  9](R/W) Ignore POISON when reading XAQ entries. */
        uint64_t reserved_8            : 1;
        uint64_t lol                   : 1;  /**< [  7:  7](R/W) Reserved. */
        uint64_t xaq_alloc_dis         : 1;  /**< [  6:  6](R/W) Disable NPA alloc requests to fill the SSO page cache.
                                                                 When this bit is set, all existing cached free pointers will be returned to NPA,
                                                                 software needs to wait for SSO_AF_HWGRP()_AW_STATUS[XAQ_BUF_CACHED] to be zero
                                                                 before sending traffic to that group. */
        uint64_t reserved_5            : 1;
        uint64_t xaq_byp_dis           : 1;  /**< [  4:  4](R/W) Disable bypass path in add-work engine. For diagnostic use only. */
        uint64_t stt                   : 1;  /**< [  3:  3](R/W) Use STT to bypass LLC allocation for XAQ store operations. When this bit is not set it uses STF. */
        uint64_t ldt                   : 1;  /**< [  2:  2](R/W) Use LDT to bypass LLC allocation for XAQ load operations when [LDWB] is not
                                                                 set. When [LDT] and [LDWB] are both clear, uses LDD load type. */
        uint64_t ldwb                  : 1;  /**< [  1:  1](R/W) When reading XAQ cache lines, use LDWB transactions to invalidate the cache
                                                                 line. When clear, use [LDT] to determine load type. */
        uint64_t rwen                  : 1;  /**< [  0:  0](R/W/H) Enable XAQ operations. This bit should be set after SSO_AF_XAQ()_HEAD_PTR and
                                                                 SSO_AF_XAQ()_TAIL_PTR have been programmed. If cleared, all cached buffers will be
                                                                 returned to NPA as soon as possible, and TAQ arbitration is simplified. */
#else /* Word 0 - Little Endian */
        uint64_t rwen                  : 1;  /**< [  0:  0](R/W/H) Enable XAQ operations. This bit should be set after SSO_AF_XAQ()_HEAD_PTR and
                                                                 SSO_AF_XAQ()_TAIL_PTR have been programmed. If cleared, all cached buffers will be
                                                                 returned to NPA as soon as possible, and TAQ arbitration is simplified. */
        uint64_t ldwb                  : 1;  /**< [  1:  1](R/W) When reading XAQ cache lines, use LDWB transactions to invalidate the cache
                                                                 line. When clear, use [LDT] to determine load type. */
        uint64_t ldt                   : 1;  /**< [  2:  2](R/W) Use LDT to bypass LLC allocation for XAQ load operations when [LDWB] is not
                                                                 set. When [LDT] and [LDWB] are both clear, uses LDD load type. */
        uint64_t stt                   : 1;  /**< [  3:  3](R/W) Use STT to bypass LLC allocation for XAQ store operations. When this bit is not set it uses STF. */
        uint64_t xaq_byp_dis           : 1;  /**< [  4:  4](R/W) Disable bypass path in add-work engine. For diagnostic use only. */
        uint64_t reserved_5            : 1;
        uint64_t xaq_alloc_dis         : 1;  /**< [  6:  6](R/W) Disable NPA alloc requests to fill the SSO page cache.
                                                                 When this bit is set, all existing cached free pointers will be returned to NPA,
                                                                 software needs to wait for SSO_AF_HWGRP()_AW_STATUS[XAQ_BUF_CACHED] to be zero
                                                                 before sending traffic to that group. */
        uint64_t lol                   : 1;  /**< [  7:  7](R/W) Reserved. */
        uint64_t reserved_8            : 1;
        uint64_t rd_psn_ign            : 1;  /**< [  9:  9](R/W) Ignore POISON when reading XAQ entries. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } cn96xxp1;
    /* struct bdk_sso_af_hwgrpx_aw_cfg_s cn96xxp3; */
    /* struct bdk_sso_af_hwgrpx_aw_cfg_s cn98xx; */
    /* struct bdk_sso_af_hwgrpx_aw_cfg_cn96xxp1 cnf95xx; */
    /* struct bdk_sso_af_hwgrpx_aw_cfg_cn96xxp1 loki; */
};
typedef union bdk_sso_af_hwgrpx_aw_cfg bdk_sso_af_hwgrpx_aw_cfg_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_AW_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_AW_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200120ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_AW_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_AW_CFG(a) bdk_sso_af_hwgrpx_aw_cfg_t
#define bustype_BDK_SSO_AF_HWGRPX_AW_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_AW_CFG(a) "SSO_AF_HWGRPX_AW_CFG"
#define device_bar_BDK_SSO_AF_HWGRPX_AW_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_AW_CFG(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_AW_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_aw_fwd
 *
 * SSO AF Hardware Forwarding Register
 * The HWGRP this group forwards to. Resets to HWGRP.
 */
union bdk_sso_af_hwgrpx_aw_fwd
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_aw_fwd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t fwgrp                 : 8;  /**< [  7:  0](R/W) The HWGRP this group forwards to. */
#else /* Word 0 - Little Endian */
        uint64_t fwgrp                 : 8;  /**< [  7:  0](R/W) The HWGRP this group forwards to. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_aw_fwd_s cn; */
};
typedef union bdk_sso_af_hwgrpx_aw_fwd bdk_sso_af_hwgrpx_aw_fwd_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_AW_FWD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_AW_FWD(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=255))
        return 0x840070200030ll + 0x1000ll * ((a) & 0xff);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=255))
        return 0x840070200030ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_AW_FWD", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_AW_FWD(a) bdk_sso_af_hwgrpx_aw_fwd_t
#define bustype_BDK_SSO_AF_HWGRPX_AW_FWD(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_AW_FWD(a) "SSO_AF_HWGRPX_AW_FWD"
#define device_bar_BDK_SSO_AF_HWGRPX_AW_FWD(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_AW_FWD(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_AW_FWD(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_aw_status
 *
 * SSO AF Hardware Group Add-Work Status Register
 * This register indicates the status of the add-work block (AW) for HWGRP {a}.
 */
union bdk_sso_af_hwgrpx_aw_status
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_aw_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t aw_inflight           : 6;  /**< [ 21: 16](RO/H) The number of addworks in LWA add-work interfaces and software addworks in the
                                                                 input FIFOs, which are not yet included in the TAQ count. */
        uint64_t reserved_11_15        : 5;
        uint64_t tptr_next_vld         : 1;  /**< [ 10: 10](R/W1C/H) The tail next pointer in SSO_AF_XAQ()_TAIL_NEXT is valid.
                                                                 This field is normally written by hardware, but must be cleared by software on
                                                                 an FLR.

                                                                 SSO_AF_HWGRP()_AW_CFG[RWEN] should be cleared before modifying this field.
                                                                 In addition, software should wait for [NPA_FETCH] to be clear before modifying this bit. */
        uint64_t npa_fetch             : 1;  /**< [  9:  9](RO) The SSO buffer pool manager has a pointer fetch for this group in progress.

                                                                 Software should wait for this bit to be clear before clearing [TPTR_VLD]. */
        uint64_t tptr_vld              : 1;  /**< [  8:  8](R/W1C/H) The tail pointer in SSO_AF_XAQ()_TAIL_PTR is valid.
                                                                 This field is normally written by hardware, but must be cleared by software on
                                                                 an FLR.

                                                                 SSO_AF_HWGRP()_AW_CFG[RWEN] should be cleared before modifying this field.
                                                                 In addition, software should wait for [NPA_FETCH] to be clear before modifying this bit. */
        uint64_t reserved_5_7          : 3;
        uint64_t init_fail             : 1;  /**< [  4:  4](R/W1C/H) The NPA pointer initialization for this group failed.
                                                                 This error is reported after receiving more than 3 null pointers for  the
                                                                 same group during the initialization phase.
                                                                 This error is also reported via SSO_AF_ERR0[NPA] interrupt.
                                                                 XAQ operation for this group will be disabled after this [INIT_FAIL] failure,
                                                                 see SSO_AF_HWGRP()_AW_CFG[RWEN]. */
        uint64_t init_done             : 1;  /**< [  3:  3](RO/H) The NPA pointer initialization for this group is done. */
        uint64_t xaq_buf_cached        : 3;  /**< [  2:  0](RO/H) Indicates number of NPA buffers cached inside SSO for this group. This does not
                                                                 include pointers in the tail pointer memory. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_buf_cached        : 3;  /**< [  2:  0](RO/H) Indicates number of NPA buffers cached inside SSO for this group. This does not
                                                                 include pointers in the tail pointer memory. */
        uint64_t init_done             : 1;  /**< [  3:  3](RO/H) The NPA pointer initialization for this group is done. */
        uint64_t init_fail             : 1;  /**< [  4:  4](R/W1C/H) The NPA pointer initialization for this group failed.
                                                                 This error is reported after receiving more than 3 null pointers for  the
                                                                 same group during the initialization phase.
                                                                 This error is also reported via SSO_AF_ERR0[NPA] interrupt.
                                                                 XAQ operation for this group will be disabled after this [INIT_FAIL] failure,
                                                                 see SSO_AF_HWGRP()_AW_CFG[RWEN]. */
        uint64_t reserved_5_7          : 3;
        uint64_t tptr_vld              : 1;  /**< [  8:  8](R/W1C/H) The tail pointer in SSO_AF_XAQ()_TAIL_PTR is valid.
                                                                 This field is normally written by hardware, but must be cleared by software on
                                                                 an FLR.

                                                                 SSO_AF_HWGRP()_AW_CFG[RWEN] should be cleared before modifying this field.
                                                                 In addition, software should wait for [NPA_FETCH] to be clear before modifying this bit. */
        uint64_t npa_fetch             : 1;  /**< [  9:  9](RO) The SSO buffer pool manager has a pointer fetch for this group in progress.

                                                                 Software should wait for this bit to be clear before clearing [TPTR_VLD]. */
        uint64_t tptr_next_vld         : 1;  /**< [ 10: 10](R/W1C/H) The tail next pointer in SSO_AF_XAQ()_TAIL_NEXT is valid.
                                                                 This field is normally written by hardware, but must be cleared by software on
                                                                 an FLR.

                                                                 SSO_AF_HWGRP()_AW_CFG[RWEN] should be cleared before modifying this field.
                                                                 In addition, software should wait for [NPA_FETCH] to be clear before modifying this bit. */
        uint64_t reserved_11_15        : 5;
        uint64_t aw_inflight           : 6;  /**< [ 21: 16](RO/H) The number of addworks in LWA add-work interfaces and software addworks in the
                                                                 input FIFOs, which are not yet included in the TAQ count. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_aw_status_s cn; */
};
typedef union bdk_sso_af_hwgrpx_aw_status bdk_sso_af_hwgrpx_aw_status_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_AW_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_AW_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200110ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_AW_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_AW_STATUS(a) bdk_sso_af_hwgrpx_aw_status_t
#define bustype_BDK_SSO_AF_HWGRPX_AW_STATUS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_AW_STATUS(a) "SSO_AF_HWGRPX_AW_STATUS"
#define device_bar_BDK_SSO_AF_HWGRPX_AW_STATUS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_AW_STATUS(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_AW_STATUS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_aw_tagspace
 *
 * SSO AF Per-Group Add-Work Configuration Register
 * This register controls the operation of the add-work block (AW).
 */
union bdk_sso_af_hwgrpx_aw_tagspace
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_aw_tagspace_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t tagspace              : 8;  /**< [  7:  0](R/W) The tag space assigned to this group. All work-queue entries added to
                                                                 this group will use this tag space, and all tag ordering and atomicity
                                                                 checks will be restricted to work from hardware groups with the same
                                                                 tag space (regardless of what PF_FUNCs those hardware groups are
                                                                 assigned to). */
#else /* Word 0 - Little Endian */
        uint64_t tagspace              : 8;  /**< [  7:  0](R/W) The tag space assigned to this group. All work-queue entries added to
                                                                 this group will use this tag space, and all tag ordering and atomicity
                                                                 checks will be restricted to work from hardware groups with the same
                                                                 tag space (regardless of what PF_FUNCs those hardware groups are
                                                                 assigned to). */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_aw_tagspace_s cn; */
};
typedef union bdk_sso_af_hwgrpx_aw_tagspace bdk_sso_af_hwgrpx_aw_tagspace_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_AW_TAGSPACE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_AW_TAGSPACE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200130ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_AW_TAGSPACE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_AW_TAGSPACE(a) bdk_sso_af_hwgrpx_aw_tagspace_t
#define bustype_BDK_SSO_AF_HWGRPX_AW_TAGSPACE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_AW_TAGSPACE(a) "SSO_AF_HWGRPX_AW_TAGSPACE"
#define device_bar_BDK_SSO_AF_HWGRPX_AW_TAGSPACE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_AW_TAGSPACE(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_AW_TAGSPACE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_dq_pc
 *
 * SSO AF Hardware Group Work-Descheduled Performance Counter Register
 * Counts the number of work schedules of descheduled work for each hardware group. The
 * counter rolls over through zero when the maximum value is exceeded.
 */
union bdk_sso_af_hwgrpx_dq_pc
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_dq_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work deschedule performance counter for hardware group. Writes are for diagnostic
                                                                 use only, and defined only when neither work nor GET_WORKs are present in the
                                                                 SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work deschedule performance counter for hardware group. Writes are for diagnostic
                                                                 use only, and defined only when neither work nor GET_WORKs are present in the
                                                                 SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_dq_pc_s cn; */
};
typedef union bdk_sso_af_hwgrpx_dq_pc bdk_sso_af_hwgrpx_dq_pc_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_DQ_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_DQ_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x8400702000a0ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_DQ_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_DQ_PC(a) bdk_sso_af_hwgrpx_dq_pc_t
#define bustype_BDK_SSO_AF_HWGRPX_DQ_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_DQ_PC(a) "SSO_AF_HWGRPX_DQ_PC"
#define device_bar_BDK_SSO_AF_HWGRPX_DQ_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_DQ_PC(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_DQ_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_ds_pc
 *
 * SSO AF Hardware Group Deschedule Performance Counter Register
 * Counts the number of deschedule requests for each hardware group. Counter rolls over
 * through zero when the maximum value is exceeded.
 */
union bdk_sso_af_hwgrpx_ds_pc
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_ds_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Deschedule performance counter. Writes are for diagnostic use only, and defined only when
                                                                 neither work nor GET_WORKs are present in the SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Deschedule performance counter. Writes are for diagnostic use only, and defined only when
                                                                 neither work nor GET_WORKs are present in the SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_ds_pc_s cn; */
};
typedef union bdk_sso_af_hwgrpx_ds_pc bdk_sso_af_hwgrpx_ds_pc_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_DS_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_DS_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200090ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_DS_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_DS_PC(a) bdk_sso_af_hwgrpx_ds_pc_t
#define bustype_BDK_SSO_AF_HWGRPX_DS_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_DS_PC(a) "SSO_AF_HWGRPX_DS_PC"
#define device_bar_BDK_SSO_AF_HWGRPX_DS_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_DS_PC(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_DS_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_ext_pc
 *
 * SSO AF Hardware Group External Schedule Performance Counter Register
 * Counts the number of cache lines of WAEs sent to LLC/DRAM. Counter rolls over
 * through zero when the maximum value is exceeded.
 */
union bdk_sso_af_hwgrpx_ext_pc
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_ext_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) External admission queue cache lines written. Each write corresponds to 11 WAEs. Writes
                                                                 are for diagnostic use only, and defined only when neither work nor GET_WORKs are present
                                                                 in the SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) External admission queue cache lines written. Each write corresponds to 11 WAEs. Writes
                                                                 are for diagnostic use only, and defined only when neither work nor GET_WORKs are present
                                                                 in the SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_ext_pc_s cn; */
};
typedef union bdk_sso_af_hwgrpx_ext_pc bdk_sso_af_hwgrpx_ext_pc_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_EXT_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_EXT_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200060ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_EXT_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_EXT_PC(a) bdk_sso_af_hwgrpx_ext_pc_t
#define bustype_BDK_SSO_AF_HWGRPX_EXT_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_EXT_PC(a) "SSO_AF_HWGRPX_EXT_PC"
#define device_bar_BDK_SSO_AF_HWGRPX_EXT_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_EXT_PC(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_EXT_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_iaq_thr
 *
 * SSO AF Hardware Group In-unit Admission Queue Threshold Registers
 * These registers contain the thresholds for allocating SSO in-unit admission queue entries.
 */
union bdk_sso_af_hwgrpx_iaq_thr
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_iaq_thr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t grp_cnt               : 14; /**< [ 61: 48](RO/H) Hardware group's entry count. Number of internal entries allocated to IAQ,
                                                                 conflicted work, or CQ in this hardware group.

                                                                 Internal:
                                                                 Increments on admission to IAQ, decrements on scheduling into
                                                                 work slot. */
        uint64_t reserved_46_47        : 2;
        uint64_t max_thr               : 14; /**< [ 45: 32](R/W) Max threshold for this internal admission queue. If nonzero, must be \>= [RSVD_THR] + 4.
                                                                 To ensure full streaming performance to all cores, should be at least 208. Must not be
                                                                 changed after traffic is sent to this hardware group. */
        uint64_t reserved_14_31        : 18;
        uint64_t rsvd_thr              : 14; /**< [ 13:  0](R/W) Threshold for reserved entries for this internal hardware group queue. Should be
                                                                 at least 0x1 for any hardware groups that must make forward progress when other
                                                                 hardware group's work is pending. Updates to this field must also update
                                                                 SSO_AF_AW_ADD[RSVD_FREE]. Must not be changed after traffic is sent to this
                                                                 hardware group. */
#else /* Word 0 - Little Endian */
        uint64_t rsvd_thr              : 14; /**< [ 13:  0](R/W) Threshold for reserved entries for this internal hardware group queue. Should be
                                                                 at least 0x1 for any hardware groups that must make forward progress when other
                                                                 hardware group's work is pending. Updates to this field must also update
                                                                 SSO_AF_AW_ADD[RSVD_FREE]. Must not be changed after traffic is sent to this
                                                                 hardware group. */
        uint64_t reserved_14_31        : 18;
        uint64_t max_thr               : 14; /**< [ 45: 32](R/W) Max threshold for this internal admission queue. If nonzero, must be \>= [RSVD_THR] + 4.
                                                                 To ensure full streaming performance to all cores, should be at least 208. Must not be
                                                                 changed after traffic is sent to this hardware group. */
        uint64_t reserved_46_47        : 2;
        uint64_t grp_cnt               : 14; /**< [ 61: 48](RO/H) Hardware group's entry count. Number of internal entries allocated to IAQ,
                                                                 conflicted work, or CQ in this hardware group.

                                                                 Internal:
                                                                 Increments on admission to IAQ, decrements on scheduling into
                                                                 work slot. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_iaq_thr_s cn9; */
    /* struct bdk_sso_af_hwgrpx_iaq_thr_s cn96xx; */
    struct bdk_sso_af_hwgrpx_iaq_thr_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t grp_cnt               : 14; /**< [ 61: 48](RO/H) Hardware group's entry count. Number of internal entries allocated to IAQ,
                                                                 conflicted work, or CQ in this hardware group.

                                                                 Internal:
                                                                 Increments on admission to IAQ, decrements on scheduling into
                                                                 work slot. (48..`SSO_IDX_W+48) */
        uint64_t reserved_46_47        : 2;
        uint64_t max_thr               : 14; /**< [ 45: 32](R/W) Max threshold for this internal admission queue. If nonzero, must be \>= [RSVD_THR] + 4.
                                                                 To ensure full streaming performance to all cores, should be at least 208. Must not be
                                                                 changed after traffic is sent to this hardware group.

                                                                 Internal:
                                                                 (32..`SSO_IDX_W+32) */
        uint64_t reserved_14_31        : 18;
        uint64_t rsvd_thr              : 14; /**< [ 13:  0](R/W) Threshold for reserved entries for this internal hardware group queue. Should be
                                                                 at least 0x1 for any hardware groups that must make forward progress when other
                                                                 hardware group's work is pending. Updates to this field must also update
                                                                 SSO_AF_AW_ADD[RSVD_FREE]. Must not be changed after traffic is sent to this
                                                                 hardware group.

                                                                 Internal:
                                                                 (0..`SSO_IDX_W) */
#else /* Word 0 - Little Endian */
        uint64_t rsvd_thr              : 14; /**< [ 13:  0](R/W) Threshold for reserved entries for this internal hardware group queue. Should be
                                                                 at least 0x1 for any hardware groups that must make forward progress when other
                                                                 hardware group's work is pending. Updates to this field must also update
                                                                 SSO_AF_AW_ADD[RSVD_FREE]. Must not be changed after traffic is sent to this
                                                                 hardware group.

                                                                 Internal:
                                                                 (0..`SSO_IDX_W) */
        uint64_t reserved_14_31        : 18;
        uint64_t max_thr               : 14; /**< [ 45: 32](R/W) Max threshold for this internal admission queue. If nonzero, must be \>= [RSVD_THR] + 4.
                                                                 To ensure full streaming performance to all cores, should be at least 208. Must not be
                                                                 changed after traffic is sent to this hardware group.

                                                                 Internal:
                                                                 (32..`SSO_IDX_W+32) */
        uint64_t reserved_46_47        : 2;
        uint64_t grp_cnt               : 14; /**< [ 61: 48](RO/H) Hardware group's entry count. Number of internal entries allocated to IAQ,
                                                                 conflicted work, or CQ in this hardware group.

                                                                 Internal:
                                                                 Increments on admission to IAQ, decrements on scheduling into
                                                                 work slot. (48..`SSO_IDX_W+48) */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_hwgrpx_iaq_thr_s cnf95xx; */
    /* struct bdk_sso_af_hwgrpx_iaq_thr_s loki; */
};
typedef union bdk_sso_af_hwgrpx_iaq_thr bdk_sso_af_hwgrpx_iaq_thr_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_IAQ_THR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_IAQ_THR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200000ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_IAQ_THR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_IAQ_THR(a) bdk_sso_af_hwgrpx_iaq_thr_t
#define bustype_BDK_SSO_AF_HWGRPX_IAQ_THR(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_IAQ_THR(a) "SSO_AF_HWGRPX_IAQ_THR"
#define device_bar_BDK_SSO_AF_HWGRPX_IAQ_THR(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_IAQ_THR(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_IAQ_THR(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_iu_accnt
 *
 * SSO AF Hardware Group In-Unit Account Index Registers
 * These registers assign an in-unit accounting index to each hardware group.
 */
union bdk_sso_af_hwgrpx_iu_accnt
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_iu_accnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t ena                   : 1;  /**< [ 16: 16](R/W) Enable the use of the in-unit accounting index. When clear, the
                                                                 hardware group does not participate in any in-unit accounting index.

                                                                 Note that the per-group IAQ thresholds in SSO_AF_HWGRP()_IAQ_THR and
                                                                 SSO_LF_GGRP_INT_THR[IAQ_THR] always apply, regardless of the in-unit
                                                                 accounting index. */
        uint64_t reserved_8_15         : 8;
        uint64_t accnt_indx            : 8;  /**< [  7:  0](R/W) In-unit accounting index assigned to this hardware group. */
#else /* Word 0 - Little Endian */
        uint64_t accnt_indx            : 8;  /**< [  7:  0](R/W) In-unit accounting index assigned to this hardware group. */
        uint64_t reserved_8_15         : 8;
        uint64_t ena                   : 1;  /**< [ 16: 16](R/W) Enable the use of the in-unit accounting index. When clear, the
                                                                 hardware group does not participate in any in-unit accounting index.

                                                                 Note that the per-group IAQ thresholds in SSO_AF_HWGRP()_IAQ_THR and
                                                                 SSO_LF_GGRP_INT_THR[IAQ_THR] always apply, regardless of the in-unit
                                                                 accounting index. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_iu_accnt_s cn; */
};
typedef union bdk_sso_af_hwgrpx_iu_accnt bdk_sso_af_hwgrpx_iu_accnt_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_IU_ACCNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_IU_ACCNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200230ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_IU_ACCNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_IU_ACCNT(a) bdk_sso_af_hwgrpx_iu_accnt_t
#define bustype_BDK_SSO_AF_HWGRPX_IU_ACCNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_IU_ACCNT(a) "SSO_AF_HWGRPX_IU_ACCNT"
#define device_bar_BDK_SSO_AF_HWGRPX_IU_ACCNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_IU_ACCNT(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_IU_ACCNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_page_cnt
 *
 * SSO AF Hardware Group In-use Page Count Register
 */
union bdk_sso_af_hwgrpx_page_cnt
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_page_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cnt                   : 32; /**< [ 31:  0](R/W/H) In-use page count. Number of pages SSO has allocated and not yet returned for
                                                                 HWGRP {a}. Excludes unused
                                                                 pointers cached in SSO. Hardware updates this register. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 32; /**< [ 31:  0](R/W/H) In-use page count. Number of pages SSO has allocated and not yet returned for
                                                                 HWGRP {a}. Excludes unused
                                                                 pointers cached in SSO. Hardware updates this register. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_page_cnt_s cn; */
};
typedef union bdk_sso_af_hwgrpx_page_cnt bdk_sso_af_hwgrpx_page_cnt_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_PAGE_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_PAGE_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200100ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_PAGE_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_PAGE_CNT(a) bdk_sso_af_hwgrpx_page_cnt_t
#define bustype_BDK_SSO_AF_HWGRPX_PAGE_CNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_PAGE_CNT(a) "SSO_AF_HWGRPX_PAGE_CNT"
#define device_bar_BDK_SSO_AF_HWGRPX_PAGE_CNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_PAGE_CNT(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_PAGE_CNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_pri
 *
 * SSO AF Hardware Group Priority Register
 * Controls the priority and hardware group affinity arbitration for each hardware group.
 */
union bdk_sso_af_hwgrpx_pri
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_pri_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t wgt_left              : 6;  /**< [ 29: 24](RO/H) Arbitration credits remaining on this hardware group. */
        uint64_t reserved_22_23        : 2;
        uint64_t weight                : 6;  /**< [ 21: 16](R/W) Arbitration weight to apply to this hardware group. Must be \>= 0x2. */
        uint64_t reserved_12_15        : 4;
        uint64_t affinity              : 4;  /**< [ 11:  8](R/W) Processor affinity arbitration weight to apply to this hardware group. If zero, affinity
                                                                 is disabled. A change to [AFFINITY] will not take effect until the old [AFFINITY]'s
                                                                 value loaded into SSO_AF_HWS()_ARB[AFF_LEFT] has drained to zero. */
        uint64_t reserved_3_7          : 5;
        uint64_t pri                   : 3;  /**< [  2:  0](R/W) Priority for this hardware group relative to other hardware groups. To prevent a
                                                                 HWS from receiving work use SSO_AF_HWS()_S()_GRPMSK().

                                                                 0x0 = highest priority.
                                                                 0x7 = lowest priority.

                                                                 Changing priority while GET_WORKs are in flight may result in a GET_WORK using either the
                                                                 old or new priority, or a mix thereof. */
#else /* Word 0 - Little Endian */
        uint64_t pri                   : 3;  /**< [  2:  0](R/W) Priority for this hardware group relative to other hardware groups. To prevent a
                                                                 HWS from receiving work use SSO_AF_HWS()_S()_GRPMSK().

                                                                 0x0 = highest priority.
                                                                 0x7 = lowest priority.

                                                                 Changing priority while GET_WORKs are in flight may result in a GET_WORK using either the
                                                                 old or new priority, or a mix thereof. */
        uint64_t reserved_3_7          : 5;
        uint64_t affinity              : 4;  /**< [ 11:  8](R/W) Processor affinity arbitration weight to apply to this hardware group. If zero, affinity
                                                                 is disabled. A change to [AFFINITY] will not take effect until the old [AFFINITY]'s
                                                                 value loaded into SSO_AF_HWS()_ARB[AFF_LEFT] has drained to zero. */
        uint64_t reserved_12_15        : 4;
        uint64_t weight                : 6;  /**< [ 21: 16](R/W) Arbitration weight to apply to this hardware group. Must be \>= 0x2. */
        uint64_t reserved_22_23        : 2;
        uint64_t wgt_left              : 6;  /**< [ 29: 24](RO/H) Arbitration credits remaining on this hardware group. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_pri_s cn; */
};
typedef union bdk_sso_af_hwgrpx_pri bdk_sso_af_hwgrpx_pri_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_PRI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_PRI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200020ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_PRI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_PRI(a) bdk_sso_af_hwgrpx_pri_t
#define bustype_BDK_SSO_AF_HWGRPX_PRI(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_PRI(a) "SSO_AF_HWGRPX_PRI"
#define device_bar_BDK_SSO_AF_HWGRPX_PRI(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_PRI(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_PRI(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_taq_thr
 *
 * SSO AF Hardware Group Transitory Admission Queue Threshold Registers
 * These registers contain the thresholds for allocating SSO transitory admission queue storage
 * buffers, indexed by hardware group.
 */
union bdk_sso_af_hwgrpx_taq_thr
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_taq_thr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_59_63        : 5;
        uint64_t grp_cnt               : 11; /**< [ 58: 48](RO/H) hardware group's entry count. Number of transitory admission buffers allocated to this group. */
        uint64_t reserved_43_47        : 5;
        uint64_t max_thr               : 11; /**< [ 42: 32](R/W) Max threshold for this transitory admission queue, in buffers of 11
                                                                 entries. Must be \>= 3, must be \>= [RSVD_THR], and to ensure full streaming
                                                                 performance on this hardware group, should be at least 16 buffers. SSO may
                                                                 exceed this count using unreserved free buffers if and only if persistently
                                                                 backpressured by IOBI. Must not be changed after traffic is sent to this
                                                                 hardware group. */
        uint64_t reserved_11_31        : 21;
        uint64_t rsvd_thr              : 11; /**< [ 10:  0](R/W) Threshold for reserved entries for this transitory admission queue, in buffers
                                                                 of 11 entries. Must be at least three buffers for any hardware groups that are to be
                                                                 used. Changes to this field must also update SSO_AF_TAQ_ADD[RSVD_FREE]. Must not be
                                                                 changed after traffic is sent to this hardware group.

                                                                 If fewer than three hardware groups are used, then the sum of
                                                                 [RSVD_THR] across used hardware groups must be less than
                                                                 SSO_AF_CONST[TAQ_A]-4. */
#else /* Word 0 - Little Endian */
        uint64_t rsvd_thr              : 11; /**< [ 10:  0](R/W) Threshold for reserved entries for this transitory admission queue, in buffers
                                                                 of 11 entries. Must be at least three buffers for any hardware groups that are to be
                                                                 used. Changes to this field must also update SSO_AF_TAQ_ADD[RSVD_FREE]. Must not be
                                                                 changed after traffic is sent to this hardware group.

                                                                 If fewer than three hardware groups are used, then the sum of
                                                                 [RSVD_THR] across used hardware groups must be less than
                                                                 SSO_AF_CONST[TAQ_A]-4. */
        uint64_t reserved_11_31        : 21;
        uint64_t max_thr               : 11; /**< [ 42: 32](R/W) Max threshold for this transitory admission queue, in buffers of 11
                                                                 entries. Must be \>= 3, must be \>= [RSVD_THR], and to ensure full streaming
                                                                 performance on this hardware group, should be at least 16 buffers. SSO may
                                                                 exceed this count using unreserved free buffers if and only if persistently
                                                                 backpressured by IOBI. Must not be changed after traffic is sent to this
                                                                 hardware group. */
        uint64_t reserved_43_47        : 5;
        uint64_t grp_cnt               : 11; /**< [ 58: 48](RO/H) hardware group's entry count. Number of transitory admission buffers allocated to this group. */
        uint64_t reserved_59_63        : 5;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_taq_thr_s cn; */
};
typedef union bdk_sso_af_hwgrpx_taq_thr bdk_sso_af_hwgrpx_taq_thr_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_TAQ_THR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_TAQ_THR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200010ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_TAQ_THR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_TAQ_THR(a) bdk_sso_af_hwgrpx_taq_thr_t
#define bustype_BDK_SSO_AF_HWGRPX_TAQ_THR(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_TAQ_THR(a) "SSO_AF_HWGRPX_TAQ_THR"
#define device_bar_BDK_SSO_AF_HWGRPX_TAQ_THR(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_TAQ_THR(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_TAQ_THR(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_ts_pc
 *
 * SSO AF Hardware Group Tag Switch Performance Counter Register
 * Counts the number of tag switch requests for each hardware group being switched
 * to. Counter rolls over through zero when maximum value is exceeded.
 */
union bdk_sso_af_hwgrpx_ts_pc
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_ts_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Tag switch performance counter. Writes are for diagnostic use only, and defined only when
                                                                 neither work nor GET_WORKs are present in the SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Tag switch performance counter. Writes are for diagnostic use only, and defined only when
                                                                 neither work nor GET_WORKs are present in the SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_ts_pc_s cn; */
};
typedef union bdk_sso_af_hwgrpx_ts_pc bdk_sso_af_hwgrpx_ts_pc_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_TS_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_TS_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200080ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_TS_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_TS_PC(a) bdk_sso_af_hwgrpx_ts_pc_t
#define bustype_BDK_SSO_AF_HWGRPX_TS_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_TS_PC(a) "SSO_AF_HWGRPX_TS_PC"
#define device_bar_BDK_SSO_AF_HWGRPX_TS_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_TS_PC(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_TS_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_wa_pc
 *
 * SSO AF Hardware Group Work-Add Performance Counter Registers
 * Counts the number of add new work requests for each hardware group. The counter
 * rolls over through zero when the maximum value is exceeded.
 */
union bdk_sso_af_hwgrpx_wa_pc
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_wa_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work add performance counter for hardware group. Increments when work moves into
                                                                 IAQ. Writes are for diagnostic use only, and defined only when neither work nor
                                                                 GET_WORKs are present in the SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work add performance counter for hardware group. Increments when work moves into
                                                                 IAQ. Writes are for diagnostic use only, and defined only when neither work nor
                                                                 GET_WORKs are present in the SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_wa_pc_s cn; */
};
typedef union bdk_sso_af_hwgrpx_wa_pc bdk_sso_af_hwgrpx_wa_pc_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_WA_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_WA_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200070ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_WA_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_WA_PC(a) bdk_sso_af_hwgrpx_wa_pc_t
#define bustype_BDK_SSO_AF_HWGRPX_WA_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_WA_PC(a) "SSO_AF_HWGRPX_WA_PC"
#define device_bar_BDK_SSO_AF_HWGRPX_WA_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_WA_PC(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_WA_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_ws_pc
 *
 * SSO AF Hardware Group Work-Schedule Performance Counter Registers
 * Counts the number of work schedules for each hardware group. The counter rolls over
 * through zero when the maximum value is exceeded.
 */
union bdk_sso_af_hwgrpx_ws_pc
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_ws_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work schedule performance counter for hardware group. Writes are for diagnostic
                                                                 use only, and defined only when neither work nor GET_WORKs are present in the
                                                                 SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work schedule performance counter for hardware group. Writes are for diagnostic
                                                                 use only, and defined only when neither work nor GET_WORKs are present in the
                                                                 SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_ws_pc_s cn; */
};
typedef union bdk_sso_af_hwgrpx_ws_pc bdk_sso_af_hwgrpx_ws_pc_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_WS_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_WS_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200050ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_WS_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_WS_PC(a) bdk_sso_af_hwgrpx_ws_pc_t
#define bustype_BDK_SSO_AF_HWGRPX_WS_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_WS_PC(a) "SSO_AF_HWGRPX_WS_PC"
#define device_bar_BDK_SSO_AF_HWGRPX_WS_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_WS_PC(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_WS_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_xaq_aura
 *
 * SSO PF External Admission Queue Aura Register
 */
union bdk_sso_af_hwgrpx_xaq_aura
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_xaq_aura_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t aura                  : 20; /**< [ 19:  0](R/W) NPA aura assigned to this group for SSO XAQ allocations and frees. The NPA aura
                                                                 selected by [AURA] must correspond to a pool where the buffers are at least 4 KB. */
#else /* Word 0 - Little Endian */
        uint64_t aura                  : 20; /**< [ 19:  0](R/W) NPA aura assigned to this group for SSO XAQ allocations and frees. The NPA aura
                                                                 selected by [AURA] must correspond to a pool where the buffers are at least 4 KB. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_xaq_aura_s cn; */
};
typedef union bdk_sso_af_hwgrpx_xaq_aura bdk_sso_af_hwgrpx_xaq_aura_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_XAQ_AURA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_XAQ_AURA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200140ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_XAQ_AURA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_XAQ_AURA(a) bdk_sso_af_hwgrpx_xaq_aura_t
#define bustype_BDK_SSO_AF_HWGRPX_XAQ_AURA(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_XAQ_AURA(a) "SSO_AF_HWGRPX_XAQ_AURA"
#define device_bar_BDK_SSO_AF_HWGRPX_XAQ_AURA(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_XAQ_AURA(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_XAQ_AURA(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hwgrp#_xaq_limit
 *
 * SSO AF Hardware Group External Admission Queue Limit Registers
 */
union bdk_sso_af_hwgrpx_xaq_limit
{
    uint64_t u;
    struct bdk_sso_af_hwgrpx_xaq_limit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t xaq_limit             : 33; /**< [ 32:  0](R/W) XAQ limit. Each count holds 11 work entries. If an add work is requested to a
                                                                 group where SSO_LF_GGRP_XAQ_CNT[XAQ_CNT] \>= [XAQ_LIMIT], then the add work is
                                                                 dropped and will SSO_LF_GGRP_QCTL[ENA] is cleared and SSO_LF_GGRP_INT[XAQ_LIMIT] is
                                                                 set. When 0x0, limiting is disabled. Due to pipelining, hardware may exceed this
                                                                 limit by up to the TAQ size (320) entries. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_limit             : 33; /**< [ 32:  0](R/W) XAQ limit. Each count holds 11 work entries. If an add work is requested to a
                                                                 group where SSO_LF_GGRP_XAQ_CNT[XAQ_CNT] \>= [XAQ_LIMIT], then the add work is
                                                                 dropped and will SSO_LF_GGRP_QCTL[ENA] is cleared and SSO_LF_GGRP_INT[XAQ_LIMIT] is
                                                                 set. When 0x0, limiting is disabled. Due to pipelining, hardware may exceed this
                                                                 limit by up to the TAQ size (320) entries. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwgrpx_xaq_limit_s cn; */
};
typedef union bdk_sso_af_hwgrpx_xaq_limit bdk_sso_af_hwgrpx_xaq_limit_t;

static inline uint64_t BDK_SSO_AF_HWGRPX_XAQ_LIMIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWGRPX_XAQ_LIMIT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070200220ll + 0x1000ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_HWGRPX_XAQ_LIMIT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWGRPX_XAQ_LIMIT(a) bdk_sso_af_hwgrpx_xaq_limit_t
#define bustype_BDK_SSO_AF_HWGRPX_XAQ_LIMIT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWGRPX_XAQ_LIMIT(a) "SSO_AF_HWGRPX_XAQ_LIMIT"
#define device_bar_BDK_SSO_AF_HWGRPX_XAQ_LIMIT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWGRPX_XAQ_LIMIT(a) (a)
#define arguments_BDK_SSO_AF_HWGRPX_XAQ_LIMIT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hws#_arb
 *
 * SSO AF Hardware Workslot Arbitration State Register
 * For diagnostic use, returns the arbitration state for each HWS.
 */
union bdk_sso_af_hwsx_arb
{
    uint64_t u;
    struct bdk_sso_af_hwsx_arb_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t aff_left              : 4;  /**< [ 19: 16](R/W/H) HWS affinity arbitration credits remaining on the last serviced hardware group. */
        uint64_t reserved_10_15        : 6;
        uint64_t last_grp              : 10; /**< [  9:  0](R/W/H) Last hardware group number serviced by this HWS. */
#else /* Word 0 - Little Endian */
        uint64_t last_grp              : 10; /**< [  9:  0](R/W/H) Last hardware group number serviced by this HWS. */
        uint64_t reserved_10_15        : 6;
        uint64_t aff_left              : 4;  /**< [ 19: 16](R/W/H) HWS affinity arbitration credits remaining on the last serviced hardware group. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwsx_arb_s cn; */
};
typedef union bdk_sso_af_hwsx_arb bdk_sso_af_hwsx_arb_t;

static inline uint64_t BDK_SSO_AF_HWSX_ARB(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWSX_ARB(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=51))
        return 0x840070400100ll + 0x1000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=75))
        return 0x840070400100ll + 0x1000ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=51))
        return 0x840070400100ll + 0x1000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=51))
        return 0x840070400100ll + 0x1000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_AF_HWSX_ARB", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWSX_ARB(a) bdk_sso_af_hwsx_arb_t
#define bustype_BDK_SSO_AF_HWSX_ARB(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWSX_ARB(a) "SSO_AF_HWSX_ARB"
#define device_bar_BDK_SSO_AF_HWSX_ARB(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWSX_ARB(a) (a)
#define arguments_BDK_SSO_AF_HWSX_ARB(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hws#_gmctl
 *
 * SSO AF Hardware Workslot Guest Machine Control Register
 */
union bdk_sso_af_hwsx_gmctl
{
    uint64_t u;
    struct bdk_sso_af_hwsx_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_18_63        : 46;
        uint64_t alloc_we_ena          : 1;  /**< [ 17: 17](R/W) Allocate work-entry enable.
                                                                 0 = ALLOC_WE operations for the given HWS will always fail and trigger
                                                                 an error.
                                                                 1 = ALLOC_WE operations are allowed for the given HWS.

                                                                 Note that ALLOC_WE may leak information from one PF_FUNC to another. */
        uint64_t gw_indx_ena           : 1;  /**< [ 16: 16](R/W) Get work indexed enable.
                                                                 0 = Get work indexed operations for the given HWS will immediately return
                                                                 error response.
                                                                 1 = Get-work indexed operations are allowed. However software can only perform
                                                                 get-work indexed for entries that were previously descheduled by a HWS, and have
                                                                 a HWGRP which has a valid GGRP for the PF_FUNC which is performing
                                                                 the get-work indexed.

                                                                 Violation of these conditions may result in unpredictable behavior, including
                                                                 corruption of other PF_FUNCs using SSO, or leaking of information from
                                                                 one PF_FUNC to another. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t gw_indx_ena           : 1;  /**< [ 16: 16](R/W) Get work indexed enable.
                                                                 0 = Get work indexed operations for the given HWS will immediately return
                                                                 error response.
                                                                 1 = Get-work indexed operations are allowed. However software can only perform
                                                                 get-work indexed for entries that were previously descheduled by a HWS, and have
                                                                 a HWGRP which has a valid GGRP for the PF_FUNC which is performing
                                                                 the get-work indexed.

                                                                 Violation of these conditions may result in unpredictable behavior, including
                                                                 corruption of other PF_FUNCs using SSO, or leaking of information from
                                                                 one PF_FUNC to another. */
        uint64_t alloc_we_ena          : 1;  /**< [ 17: 17](R/W) Allocate work-entry enable.
                                                                 0 = ALLOC_WE operations for the given HWS will always fail and trigger
                                                                 an error.
                                                                 1 = ALLOC_WE operations are allowed for the given HWS.

                                                                 Note that ALLOC_WE may leak information from one PF_FUNC to another. */
        uint64_t reserved_18_63        : 46;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwsx_gmctl_s cn; */
};
typedef union bdk_sso_af_hwsx_gmctl bdk_sso_af_hwsx_gmctl_t;

static inline uint64_t BDK_SSO_AF_HWSX_GMCTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWSX_GMCTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=51))
        return 0x840070400200ll + 0x1000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=75))
        return 0x840070400200ll + 0x1000ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=51))
        return 0x840070400200ll + 0x1000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=51))
        return 0x840070400200ll + 0x1000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_AF_HWSX_GMCTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWSX_GMCTL(a) bdk_sso_af_hwsx_gmctl_t
#define bustype_BDK_SSO_AF_HWSX_GMCTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWSX_GMCTL(a) "SSO_AF_HWSX_GMCTL"
#define device_bar_BDK_SSO_AF_HWSX_GMCTL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWSX_GMCTL(a) (a)
#define arguments_BDK_SSO_AF_HWSX_GMCTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hws#_inv
 *
 * SSO AF Hardware Workslot SAI Invalidate Register
 */
union bdk_sso_af_hwsx_inv
{
    uint64_t u;
    struct bdk_sso_af_hwsx_inv_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t sai_inval             : 1;  /**< [  0:  0](WO) When written to one, invalidate any GW cache entries associated with
                                                                 this HWS. */
#else /* Word 0 - Little Endian */
        uint64_t sai_inval             : 1;  /**< [  0:  0](WO) When written to one, invalidate any GW cache entries associated with
                                                                 this HWS. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwsx_inv_s cn; */
};
typedef union bdk_sso_af_hwsx_inv bdk_sso_af_hwsx_inv_t;

static inline uint64_t BDK_SSO_AF_HWSX_INV(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWSX_INV(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=51))
        return 0x840070400180ll + 0x1000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=75))
        return 0x840070400180ll + 0x1000ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=51))
        return 0x840070400180ll + 0x1000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=51))
        return 0x840070400180ll + 0x1000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_AF_HWSX_INV", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWSX_INV(a) bdk_sso_af_hwsx_inv_t
#define bustype_BDK_SSO_AF_HWSX_INV(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWSX_INV(a) "SSO_AF_HWSX_INV"
#define device_bar_BDK_SSO_AF_HWSX_INV(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWSX_INV(a) (a)
#define arguments_BDK_SSO_AF_HWSX_INV(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_hws#_s#_grpmsk#
 *
 * SSO AF HWS Hardware Group Mask Registers
 * These registers select which hardware group(s) a HWS belongs to. There are two sets of
 * masks per HWS, each with four registers corresponding to 256 hardware groups
 * (64 hardware groups per register).
 *
 * Note bit-fields are indexed by hardware group, not the guest group; therefore this
 * register should not be exposed as-is to guest drivers.
 */
union bdk_sso_af_hwsx_sx_grpmskx
{
    uint64_t u;
    struct bdk_sso_af_hwsx_sx_grpmskx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t grp_msk               : 64; /**< [ 63:  0](R/W) HWS hardware group mask. A one in any bit position sets the HWS's membership in
                                                                 the corresponding hardware group for hardware groups \<255:0\>.

                                                                 A value of 0x0 in GRPMSK for a given HWS prevents the HWS from receiving new
                                                                 work. HWSs that will never receive work should use GRPMSK=0x0; while this
                                                                 setting is not special in SSO, for backward and forward compatibility this may
                                                                 enable reallocation of internal resources to the remaining (nonzero-mask)
                                                                 hardware workslots.

                                                                 This register is intended only for large-scale save-restore of masks by the AF.
                                                                 Individual changes must use SSOW_LF_GWS_GRPMSK_CHG. */
#else /* Word 0 - Little Endian */
        uint64_t grp_msk               : 64; /**< [ 63:  0](R/W) HWS hardware group mask. A one in any bit position sets the HWS's membership in
                                                                 the corresponding hardware group for hardware groups \<255:0\>.

                                                                 A value of 0x0 in GRPMSK for a given HWS prevents the HWS from receiving new
                                                                 work. HWSs that will never receive work should use GRPMSK=0x0; while this
                                                                 setting is not special in SSO, for backward and forward compatibility this may
                                                                 enable reallocation of internal resources to the remaining (nonzero-mask)
                                                                 hardware workslots.

                                                                 This register is intended only for large-scale save-restore of masks by the AF.
                                                                 Individual changes must use SSOW_LF_GWS_GRPMSK_CHG. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_hwsx_sx_grpmskx_s cn9; */
    /* struct bdk_sso_af_hwsx_sx_grpmskx_s cn96xx; */
    struct bdk_sso_af_hwsx_sx_grpmskx_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t grp_msk               : 64; /**< [ 63:  0](R/W) HWS hardware group mask. A one in any bit position sets the HWS's membership in
                                                                 the corresponding hardware group for hardware groups \<255:0\>.

                                                                 A value of 0x0 in GRPMSK for a given HWS prevents the HWS from receiving new
                                                                 work. HWSs that will never receive work should use GRPMSK=0x0; while this
                                                                 setting is not special in SSO, for backward and forward compatibility this may
                                                                 enable reallocation of internal resources to the remaining (nonzero-mask)
                                                                 hardware workslots.

                                                                 This register is intended only for large-scale save-restore of masks by the AF.
                                                                 Individual changes must use SSOW_LF_GWS_GRPMSK_CHG.

                                                                 Internal:
                                                                 (0..`SSO_NUM_WS-1) */
#else /* Word 0 - Little Endian */
        uint64_t grp_msk               : 64; /**< [ 63:  0](R/W) HWS hardware group mask. A one in any bit position sets the HWS's membership in
                                                                 the corresponding hardware group for hardware groups \<255:0\>.

                                                                 A value of 0x0 in GRPMSK for a given HWS prevents the HWS from receiving new
                                                                 work. HWSs that will never receive work should use GRPMSK=0x0; while this
                                                                 setting is not special in SSO, for backward and forward compatibility this may
                                                                 enable reallocation of internal resources to the remaining (nonzero-mask)
                                                                 hardware workslots.

                                                                 This register is intended only for large-scale save-restore of masks by the AF.
                                                                 Individual changes must use SSOW_LF_GWS_GRPMSK_CHG.

                                                                 Internal:
                                                                 (0..`SSO_NUM_WS-1) */
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_hwsx_sx_grpmskx_s cnf95xx; */
    /* struct bdk_sso_af_hwsx_sx_grpmskx_s loki; */
};
typedef union bdk_sso_af_hwsx_sx_grpmskx bdk_sso_af_hwsx_sx_grpmskx_t;

static inline uint64_t BDK_SSO_AF_HWSX_SX_GRPMSKX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_HWSX_SX_GRPMSKX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=51) && (b<=1) && (c<=3)))
        return 0x840070400400ll + 0x1000ll * ((a) & 0x3f) + 0x20ll * ((b) & 0x1) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=75) && (b<=1) && (c<=3)))
        return 0x840070400400ll + 0x1000ll * ((a) & 0x7f) + 0x20ll * ((b) & 0x1) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=51) && (b<=1) && (c<=3)))
        return 0x840070400400ll + 0x1000ll * ((a) & 0x3f) + 0x20ll * ((b) & 0x1) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=51) && (b<=1) && (c<=3)))
        return 0x840070400400ll + 0x1000ll * ((a) & 0x3f) + 0x20ll * ((b) & 0x1) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("SSO_AF_HWSX_SX_GRPMSKX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_HWSX_SX_GRPMSKX(a,b,c) bdk_sso_af_hwsx_sx_grpmskx_t
#define bustype_BDK_SSO_AF_HWSX_SX_GRPMSKX(a,b,c) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_HWSX_SX_GRPMSKX(a,b,c) "SSO_AF_HWSX_SX_GRPMSKX"
#define device_bar_BDK_SSO_AF_HWSX_SX_GRPMSKX(a,b,c) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_HWSX_SX_GRPMSKX(a,b,c) (a)
#define arguments_BDK_SSO_AF_HWSX_SX_GRPMSKX(a,b,c) (a),(b),(c),-1

/**
 * Register (RVU_PF_BAR0) sso_af_ient#_grp
 *
 * SSO AF Internal Entry Hardware Group Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_af_ientx_grp
{
    uint64_t u;
    struct bdk_sso_af_ientx_grp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t head                  : 1;  /**< [ 61: 61](RO/H) SSO entry is at the head of a tag chain that is descheduled. */
        uint64_t nosched               : 1;  /**< [ 60: 60](RO/H) The nosched bit for the SSO entry. */
        uint64_t reserved_58_59        : 2;
        uint64_t grp                   : 10; /**< [ 57: 48](RO/H) Hardware group of the SSO entry. This register is typically only for diagnostic
                                                                 use; however if this value is delivered to guest drivers, [GRP] must be
                                                                 converted to a guest group by the hypervisor software. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t grp                   : 10; /**< [ 57: 48](RO/H) Hardware group of the SSO entry. This register is typically only for diagnostic
                                                                 use; however if this value is delivered to guest drivers, [GRP] must be
                                                                 converted to a guest group by the hypervisor software. */
        uint64_t reserved_58_59        : 2;
        uint64_t nosched               : 1;  /**< [ 60: 60](RO/H) The nosched bit for the SSO entry. */
        uint64_t head                  : 1;  /**< [ 61: 61](RO/H) SSO entry is at the head of a tag chain that is descheduled. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ientx_grp_s cn; */
};
typedef union bdk_sso_af_ientx_grp bdk_sso_af_ientx_grp_t;

static inline uint64_t BDK_SSO_AF_IENTX_GRP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IENTX_GRP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=8191))
        return 0x840070a20000ll + 8ll * ((a) & 0x1fff);
    __bdk_csr_fatal("SSO_AF_IENTX_GRP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IENTX_GRP(a) bdk_sso_af_ientx_grp_t
#define bustype_BDK_SSO_AF_IENTX_GRP(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IENTX_GRP(a) "SSO_AF_IENTX_GRP"
#define device_bar_BDK_SSO_AF_IENTX_GRP(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IENTX_GRP(a) (a)
#define arguments_BDK_SSO_AF_IENTX_GRP(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ient#_links
 *
 * SSO AF Internal Entry Links Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_af_ientx_links
{
    uint64_t u;
    struct bdk_sso_af_ientx_links_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t prev_index            : 13; /**< [ 28: 16](RO/H) The previous entry in the tag chain. Unpredictable if the entry is at the head of the list
                                                                 or the head of a conflicted tag chain. */
        uint64_t reserved_14_15        : 2;
        uint64_t next_index_vld        : 1;  /**< [ 13: 13](RO/H) The [NEXT_INDEX] is valid. Unpredictable unless the entry is the tail entry of an atomic tag chain. */
        uint64_t next_index            : 13; /**< [ 12:  0](RO/H) The next entry in the tag chain or conflicted tag chain. Unpredictable if the entry is at
                                                                 the tail of the list. */
#else /* Word 0 - Little Endian */
        uint64_t next_index            : 13; /**< [ 12:  0](RO/H) The next entry in the tag chain or conflicted tag chain. Unpredictable if the entry is at
                                                                 the tail of the list. */
        uint64_t next_index_vld        : 1;  /**< [ 13: 13](RO/H) The [NEXT_INDEX] is valid. Unpredictable unless the entry is the tail entry of an atomic tag chain. */
        uint64_t reserved_14_15        : 2;
        uint64_t prev_index            : 13; /**< [ 28: 16](RO/H) The previous entry in the tag chain. Unpredictable if the entry is at the head of the list
                                                                 or the head of a conflicted tag chain. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ientx_links_s cn9; */
    /* struct bdk_sso_af_ientx_links_s cn96xx; */
    struct bdk_sso_af_ientx_links_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t prev_index            : 13; /**< [ 28: 16](RO/H) The previous entry in the tag chain. Unpredictable if the entry is at the head of the list
                                                                 or the head of a conflicted tag chain.

                                                                 Internal:
                                                                 (16..`SSO_IDX_W+16-1) */
        uint64_t reserved_14_15        : 2;
        uint64_t next_index_vld        : 1;  /**< [ 13: 13](RO/H) The [NEXT_INDEX] is valid. Unpredictable unless the entry is the tail entry of an atomic tag chain.
                                                                 Internal:
                                                                 (`SSO_IDX_W) */
        uint64_t next_index            : 13; /**< [ 12:  0](RO/H) The next entry in the tag chain or conflicted tag chain. Unpredictable if the entry is at
                                                                 the tail of the list.

                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
#else /* Word 0 - Little Endian */
        uint64_t next_index            : 13; /**< [ 12:  0](RO/H) The next entry in the tag chain or conflicted tag chain. Unpredictable if the entry is at
                                                                 the tail of the list.

                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
        uint64_t next_index_vld        : 1;  /**< [ 13: 13](RO/H) The [NEXT_INDEX] is valid. Unpredictable unless the entry is the tail entry of an atomic tag chain.
                                                                 Internal:
                                                                 (`SSO_IDX_W) */
        uint64_t reserved_14_15        : 2;
        uint64_t prev_index            : 13; /**< [ 28: 16](RO/H) The previous entry in the tag chain. Unpredictable if the entry is at the head of the list
                                                                 or the head of a conflicted tag chain.

                                                                 Internal:
                                                                 (16..`SSO_IDX_W+16-1) */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ientx_links_s cnf95xx; */
    /* struct bdk_sso_af_ientx_links_s loki; */
};
typedef union bdk_sso_af_ientx_links bdk_sso_af_ientx_links_t;

static inline uint64_t BDK_SSO_AF_IENTX_LINKS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IENTX_LINKS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=8191))
        return 0x840070a60000ll + 8ll * ((a) & 0x1fff);
    __bdk_csr_fatal("SSO_AF_IENTX_LINKS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IENTX_LINKS(a) bdk_sso_af_ientx_links_t
#define bustype_BDK_SSO_AF_IENTX_LINKS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IENTX_LINKS(a) "SSO_AF_IENTX_LINKS"
#define device_bar_BDK_SSO_AF_IENTX_LINKS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IENTX_LINKS(a) (a)
#define arguments_BDK_SSO_AF_IENTX_LINKS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ient#_pendtag
 *
 * SSO AF Internal Entry Pending Tag Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_af_ientx_pendtag
{
    uint64_t u;
    struct bdk_sso_af_ientx_pendtag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_38_63        : 26;
        uint64_t pend_switch           : 1;  /**< [ 37: 37](RO/H) Set when there is a pending SWTAG or SWTAG_FULL and the SSO entry has not
                                                                 left the list for the original tag. */
        uint64_t reserved_34_36        : 3;
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The next tag type for the new tag list when [PEND_SWITCH] is set. Enumerated by SSO_TT_E. */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The next tag for the new tag list when [PEND_SWITCH] is set. */
#else /* Word 0 - Little Endian */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The next tag for the new tag list when [PEND_SWITCH] is set. */
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The next tag type for the new tag list when [PEND_SWITCH] is set. Enumerated by SSO_TT_E. */
        uint64_t reserved_34_36        : 3;
        uint64_t pend_switch           : 1;  /**< [ 37: 37](RO/H) Set when there is a pending SWTAG or SWTAG_FULL and the SSO entry has not
                                                                 left the list for the original tag. */
        uint64_t reserved_38_63        : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ientx_pendtag_s cn; */
};
typedef union bdk_sso_af_ientx_pendtag bdk_sso_af_ientx_pendtag_t;

static inline uint64_t BDK_SSO_AF_IENTX_PENDTAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IENTX_PENDTAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=8191))
        return 0x840070a40000ll + 8ll * ((a) & 0x1fff);
    __bdk_csr_fatal("SSO_AF_IENTX_PENDTAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IENTX_PENDTAG(a) bdk_sso_af_ientx_pendtag_t
#define bustype_BDK_SSO_AF_IENTX_PENDTAG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IENTX_PENDTAG(a) "SSO_AF_IENTX_PENDTAG"
#define device_bar_BDK_SSO_AF_IENTX_PENDTAG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IENTX_PENDTAG(a) (a)
#define arguments_BDK_SSO_AF_IENTX_PENDTAG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ient#_qlinks
 *
 * SSO AF Internal Queue Links Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_af_ientx_qlinks
{
    uint64_t u;
    struct bdk_sso_af_ientx_qlinks_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t next_index            : 13; /**< [ 12:  0](RO/H) The next entry in the AQ/CQ/DQ. */
#else /* Word 0 - Little Endian */
        uint64_t next_index            : 13; /**< [ 12:  0](RO/H) The next entry in the AQ/CQ/DQ. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ientx_qlinks_s cn9; */
    /* struct bdk_sso_af_ientx_qlinks_s cn96xx; */
    struct bdk_sso_af_ientx_qlinks_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t next_index            : 13; /**< [ 12:  0](RO/H) The next entry in the AQ/CQ/DQ.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
#else /* Word 0 - Little Endian */
        uint64_t next_index            : 13; /**< [ 12:  0](RO/H) The next entry in the AQ/CQ/DQ.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ientx_qlinks_s cnf95xx; */
    /* struct bdk_sso_af_ientx_qlinks_s loki; */
};
typedef union bdk_sso_af_ientx_qlinks bdk_sso_af_ientx_qlinks_t;

static inline uint64_t BDK_SSO_AF_IENTX_QLINKS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IENTX_QLINKS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=8191))
        return 0x840070a80000ll + 8ll * ((a) & 0x1fff);
    __bdk_csr_fatal("SSO_AF_IENTX_QLINKS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IENTX_QLINKS(a) bdk_sso_af_ientx_qlinks_t
#define bustype_BDK_SSO_AF_IENTX_QLINKS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IENTX_QLINKS(a) "SSO_AF_IENTX_QLINKS"
#define device_bar_BDK_SSO_AF_IENTX_QLINKS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IENTX_QLINKS(a) (a)
#define arguments_BDK_SSO_AF_IENTX_QLINKS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ient#_tag
 *
 * SSO AF Internal Entry Tag Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_af_ientx_tag
{
    uint64_t u;
    struct bdk_sso_af_ientx_tag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_39_63        : 25;
        uint64_t tailc                 : 1;  /**< [ 38: 38](RO/H) The SSO entry is the tail of tag chain that is conflicted. No conflicted chain exists if
                                                                 [TAIL] is also set on the same entry. */
        uint64_t tail                  : 1;  /**< [ 37: 37](RO/H) The SSO entry is the tail of tag chain that is descheduled.
                                                                 Internal:
                                                                 Read from the SOC. */
        uint64_t reserved_34_36        : 3;
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type of the SSO entry. Enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag of the SSO entry. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag of the SSO entry. */
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type of the SSO entry. Enumerated by SSO_TT_E. */
        uint64_t reserved_34_36        : 3;
        uint64_t tail                  : 1;  /**< [ 37: 37](RO/H) The SSO entry is the tail of tag chain that is descheduled.
                                                                 Internal:
                                                                 Read from the SOC. */
        uint64_t tailc                 : 1;  /**< [ 38: 38](RO/H) The SSO entry is the tail of tag chain that is conflicted. No conflicted chain exists if
                                                                 [TAIL] is also set on the same entry. */
        uint64_t reserved_39_63        : 25;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ientx_tag_s cn; */
};
typedef union bdk_sso_af_ientx_tag bdk_sso_af_ientx_tag_t;

static inline uint64_t BDK_SSO_AF_IENTX_TAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IENTX_TAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=8191))
        return 0x840070a00000ll + 8ll * ((a) & 0x1fff);
    __bdk_csr_fatal("SSO_AF_IENTX_TAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IENTX_TAG(a) bdk_sso_af_ientx_tag_t
#define bustype_BDK_SSO_AF_IENTX_TAG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IENTX_TAG(a) "SSO_AF_IENTX_TAG"
#define device_bar_BDK_SSO_AF_IENTX_TAG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IENTX_TAG(a) (a)
#define arguments_BDK_SSO_AF_IENTX_TAG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ient#_wqp
 *
 * SSO AF Internal Entry WQP Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_af_ientx_wqp
{
    uint64_t u;
    struct bdk_sso_af_ientx_wqp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) Work queue LF IOVA held in the SSO entry.
                                                                 Bits \<63:53\> are a sign extension of \<52\>.  Bits \<2:0\> are 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) Work queue LF IOVA held in the SSO entry.
                                                                 Bits \<63:53\> are a sign extension of \<52\>.  Bits \<2:0\> are 0x0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ientx_wqp_s cn; */
};
typedef union bdk_sso_af_ientx_wqp bdk_sso_af_ientx_wqp_t;

static inline uint64_t BDK_SSO_AF_IENTX_WQP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IENTX_WQP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=8191))
        return 0x840070aa0000ll + 8ll * ((a) & 0x1fff);
    __bdk_csr_fatal("SSO_AF_IENTX_WQP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IENTX_WQP(a) bdk_sso_af_ientx_wqp_t
#define bustype_BDK_SSO_AF_IENTX_WQP(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IENTX_WQP(a) "SSO_AF_IENTX_WQP"
#define device_bar_BDK_SSO_AF_IENTX_WQP(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IENTX_WQP(a) (a)
#define arguments_BDK_SSO_AF_IENTX_WQP(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ipl_conf#
 *
 * SSO AF Hardware Group Conflicted List State Registers
 * Returns list status for the conflicted list indexed by hardware group. Register
 * fields are identical to those in SSO_AF_IPL_IAQ() above.
 */
union bdk_sso_af_ipl_confx
{
    uint64_t u;
    struct bdk_sso_af_ipl_confx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue. */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ipl_confx_s cn9; */
    /* struct bdk_sso_af_ipl_confx_s cn96xx; */
    struct bdk_sso_af_ipl_confx_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue.
                                                                 Internal:
                                                                 (13..`SSO_IDX_W+13-1) */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue.
                                                                 Internal:
                                                                 (13..`SSO_IDX_W+13-1) */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ipl_confx_s cnf95xx; */
    /* struct bdk_sso_af_ipl_confx_s loki; */
};
typedef union bdk_sso_af_ipl_confx bdk_sso_af_ipl_confx_t;

static inline uint64_t BDK_SSO_AF_IPL_CONFX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IPL_CONFX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070880000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_IPL_CONFX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IPL_CONFX(a) bdk_sso_af_ipl_confx_t
#define bustype_BDK_SSO_AF_IPL_CONFX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IPL_CONFX(a) "SSO_AF_IPL_CONFX"
#define device_bar_BDK_SSO_AF_IPL_CONFX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IPL_CONFX(a) (a)
#define arguments_BDK_SSO_AF_IPL_CONFX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ipl_desched#
 *
 * SSO AF Hardware Group Deschedule List State Registers
 * Returns list status for the deschedule list indexed by hardware group. Register
 * fields are identical to those in SSO_AF_IPL_IAQ() above.
 */
union bdk_sso_af_ipl_deschedx
{
    uint64_t u;
    struct bdk_sso_af_ipl_deschedx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue. */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ipl_deschedx_s cn9; */
    /* struct bdk_sso_af_ipl_deschedx_s cn96xx; */
    struct bdk_sso_af_ipl_deschedx_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue.
                                                                 Internal:
                                                                 (13..`SSO_IDX_W+13-1) */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue.
                                                                 Internal:
                                                                 (13..`SSO_IDX_W+13-1) */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ipl_deschedx_s cnf95xx; */
    /* struct bdk_sso_af_ipl_deschedx_s loki; */
};
typedef union bdk_sso_af_ipl_deschedx bdk_sso_af_ipl_deschedx_t;

static inline uint64_t BDK_SSO_AF_IPL_DESCHEDX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IPL_DESCHEDX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070860000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_IPL_DESCHEDX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IPL_DESCHEDX(a) bdk_sso_af_ipl_deschedx_t
#define bustype_BDK_SSO_AF_IPL_DESCHEDX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IPL_DESCHEDX(a) "SSO_AF_IPL_DESCHEDX"
#define device_bar_BDK_SSO_AF_IPL_DESCHEDX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IPL_DESCHEDX(a) (a)
#define arguments_BDK_SSO_AF_IPL_DESCHEDX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ipl_free#
 *
 * SSO AF Free List State Registers
 * Returns list status.
 */
union bdk_sso_af_ipl_freex
{
    uint64_t u;
    struct bdk_sso_af_ipl_freex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t qnum_head             : 2;  /**< [ 59: 58](RO/H) Subqueue with current head. */
        uint64_t qnum_tail             : 2;  /**< [ 57: 56](RO/H) Subqueue for next tail. */
        uint64_t reserved_41_55        : 15;
        uint64_t queue_val             : 1;  /**< [ 40: 40](RO/H) One or more valid entries are in this subqueue. */
        uint64_t queue_cnt             : 14; /**< [ 39: 26](RO/H) Number of valid entries in this subqueue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of this subqueue. */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of this subqueue. */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of this subqueue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of this subqueue. */
        uint64_t queue_cnt             : 14; /**< [ 39: 26](RO/H) Number of valid entries in this subqueue. */
        uint64_t queue_val             : 1;  /**< [ 40: 40](RO/H) One or more valid entries are in this subqueue. */
        uint64_t reserved_41_55        : 15;
        uint64_t qnum_tail             : 2;  /**< [ 57: 56](RO/H) Subqueue for next tail. */
        uint64_t qnum_head             : 2;  /**< [ 59: 58](RO/H) Subqueue with current head. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ipl_freex_s cn9; */
    /* struct bdk_sso_af_ipl_freex_s cn96xx; */
    struct bdk_sso_af_ipl_freex_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t qnum_head             : 2;  /**< [ 59: 58](RO/H) Subqueue with current head. */
        uint64_t qnum_tail             : 2;  /**< [ 57: 56](RO/H) Subqueue for next tail. */
        uint64_t reserved_41_55        : 15;
        uint64_t queue_val             : 1;  /**< [ 40: 40](RO/H) One or more valid entries are in this subqueue. */
        uint64_t queue_cnt             : 14; /**< [ 39: 26](RO/H) Number of valid entries in this subqueue.
                                                                 Internal:
                                                                 (26..`SSO_IDX_W+26) */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of this subqueue.
                                                                 Internal:
                                                                 (13..`SSO_IDX_W+13-1) */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of this subqueue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of this subqueue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of this subqueue.
                                                                 Internal:
                                                                 (13..`SSO_IDX_W+13-1) */
        uint64_t queue_cnt             : 14; /**< [ 39: 26](RO/H) Number of valid entries in this subqueue.
                                                                 Internal:
                                                                 (26..`SSO_IDX_W+26) */
        uint64_t queue_val             : 1;  /**< [ 40: 40](RO/H) One or more valid entries are in this subqueue. */
        uint64_t reserved_41_55        : 15;
        uint64_t qnum_tail             : 2;  /**< [ 57: 56](RO/H) Subqueue for next tail. */
        uint64_t qnum_head             : 2;  /**< [ 59: 58](RO/H) Subqueue with current head. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ipl_freex_s cnf95xx; */
    /* struct bdk_sso_af_ipl_freex_s loki; */
};
typedef union bdk_sso_af_ipl_freex bdk_sso_af_ipl_freex_t;

static inline uint64_t BDK_SSO_AF_IPL_FREEX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IPL_FREEX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070800000ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_IPL_FREEX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IPL_FREEX(a) bdk_sso_af_ipl_freex_t
#define bustype_BDK_SSO_AF_IPL_FREEX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IPL_FREEX(a) "SSO_AF_IPL_FREEX"
#define device_bar_BDK_SSO_AF_IPL_FREEX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IPL_FREEX(a) (a)
#define arguments_BDK_SSO_AF_IPL_FREEX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ipl_iaq#
 *
 * SSO AF Hardware Group IAQ List State Registers
 * Returns list status for the internal admission queue indexed by hardware group.
 */
union bdk_sso_af_ipl_iaqx
{
    uint64_t u;
    struct bdk_sso_af_ipl_iaqx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue. */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ipl_iaqx_s cn9; */
    /* struct bdk_sso_af_ipl_iaqx_s cn96xx; */
    struct bdk_sso_af_ipl_iaqx_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue.
                                                                 Internal:
                                                                 (13..`SSO_IDX_W+13-1) */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 13; /**< [ 12:  0](RO/H) Index of entry at the tail of the queue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
        uint64_t queue_head            : 13; /**< [ 25: 13](RO/H) Index of entry at the head of the queue.
                                                                 Internal:
                                                                 (13..`SSO_IDX_W+13-1) */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ipl_iaqx_s cnf95xx; */
    /* struct bdk_sso_af_ipl_iaqx_s loki; */
};
typedef union bdk_sso_af_ipl_iaqx bdk_sso_af_ipl_iaqx_t;

static inline uint64_t BDK_SSO_AF_IPL_IAQX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IPL_IAQX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070840000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_IPL_IAQX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IPL_IAQX(a) bdk_sso_af_ipl_iaqx_t
#define bustype_BDK_SSO_AF_IPL_IAQX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IPL_IAQX(a) "SSO_AF_IPL_IAQX"
#define device_bar_BDK_SSO_AF_IPL_IAQX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IPL_IAQX(a) (a)
#define arguments_BDK_SSO_AF_IPL_IAQX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_iu_accnt#_cfg
 *
 * SSO AF In-Unit Accounting Configuration Registers
 * These registers configure and report status for the in-unit entry
 * accounting indices.
 */
union bdk_sso_af_iu_accntx_cfg
{
    uint64_t u;
    struct bdk_sso_af_iu_accntx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_31_63        : 33;
        uint64_t thresh                : 15; /**< [ 30: 16](R/W) The maximum number of in-unit entries that may be used by this
                                                                 accounting index. */
        uint64_t cnt                   : 16; /**< [ 15:  0](RO/H) The number of in-unit entries currently used by this accounting index.
                                                                 This is a signed number and may temporarily be negative due to
                                                                 different latencies between incrementing and decrementing the count. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 16; /**< [ 15:  0](RO/H) The number of in-unit entries currently used by this accounting index.
                                                                 This is a signed number and may temporarily be negative due to
                                                                 different latencies between incrementing and decrementing the count. */
        uint64_t thresh                : 15; /**< [ 30: 16](R/W) The maximum number of in-unit entries that may be used by this
                                                                 accounting index. */
        uint64_t reserved_31_63        : 33;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_iu_accntx_cfg_s cn; */
};
typedef union bdk_sso_af_iu_accntx_cfg bdk_sso_af_iu_accntx_cfg_t;

static inline uint64_t BDK_SSO_AF_IU_ACCNTX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IU_ACCNTX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070050000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_IU_ACCNTX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IU_ACCNTX_CFG(a) bdk_sso_af_iu_accntx_cfg_t
#define bustype_BDK_SSO_AF_IU_ACCNTX_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IU_ACCNTX_CFG(a) "SSO_AF_IU_ACCNTX_CFG"
#define device_bar_BDK_SSO_AF_IU_ACCNTX_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IU_ACCNTX_CFG(a) (a)
#define arguments_BDK_SSO_AF_IU_ACCNTX_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_iu_accnt#_rst
 *
 * SSO AF In-Unit Accounting Count Reset Registers
 */
union bdk_sso_af_iu_accntx_rst
{
    uint64_t u;
    struct bdk_sso_af_iu_accntx_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t rst                   : 1;  /**< [  0:  0](WO) Resets the IU accounting index count for SSO_AF_IU_ACCNT()_CFG[CNT]. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 1;  /**< [  0:  0](WO) Resets the IU accounting index count for SSO_AF_IU_ACCNT()_CFG[CNT]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_iu_accntx_rst_s cn; */
};
typedef union bdk_sso_af_iu_accntx_rst bdk_sso_af_iu_accntx_rst_t;

static inline uint64_t BDK_SSO_AF_IU_ACCNTX_RST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_IU_ACCNTX_RST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070060000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_IU_ACCNTX_RST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_IU_ACCNTX_RST(a) bdk_sso_af_iu_accntx_rst_t
#define bustype_BDK_SSO_AF_IU_ACCNTX_RST(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_IU_ACCNTX_RST(a) "SSO_AF_IU_ACCNTX_RST"
#define device_bar_BDK_SSO_AF_IU_ACCNTX_RST(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_IU_ACCNTX_RST(a) (a)
#define arguments_BDK_SSO_AF_IU_ACCNTX_RST(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_lf_hwgrp_rst
 *
 * SSO AF LF HWGRP Reset Register
 */
union bdk_sso_af_lf_hwgrp_rst
{
    uint64_t u;
    struct bdk_sso_af_lf_hwgrp_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t exec                  : 1;  /**< [ 12: 12](R/W1S/H) Execute LF software-initiated reset. When software writes a one to set this bit, hardware
                                                                 resets the local function selected by [LF]. Hardware clears this bit when
                                                                 done.

                                                                 Internal:
                                                                 This comment applies to all blocks that refer to this register:

                                                                 This should preferrably reset all registers/state associated with the LF, including
                                                                 any BLK_LF_* and BLK_AF_LF()_* registers. It would also be nice to reset any per-LF
                                                                 bits in other registers but its OK to have exceptions as long as the AF software has
                                                                 another way to reset them, e.g. by writing to the bits. Such additional steps
                                                                 expected from software should be documented in the HRM, e.g. in section 19.11.5
                                                                 "VF Function Level Reset". */
        uint64_t reserved_8_11         : 4;
        uint64_t lf                    : 8;  /**< [  7:  0](R/W) Local function that is reset when [EXEC] is set. */
#else /* Word 0 - Little Endian */
        uint64_t lf                    : 8;  /**< [  7:  0](R/W) Local function that is reset when [EXEC] is set. */
        uint64_t reserved_8_11         : 4;
        uint64_t exec                  : 1;  /**< [ 12: 12](R/W1S/H) Execute LF software-initiated reset. When software writes a one to set this bit, hardware
                                                                 resets the local function selected by [LF]. Hardware clears this bit when
                                                                 done.

                                                                 Internal:
                                                                 This comment applies to all blocks that refer to this register:

                                                                 This should preferrably reset all registers/state associated with the LF, including
                                                                 any BLK_LF_* and BLK_AF_LF()_* registers. It would also be nice to reset any per-LF
                                                                 bits in other registers but its OK to have exceptions as long as the AF software has
                                                                 another way to reset them, e.g. by writing to the bits. Such additional steps
                                                                 expected from software should be documented in the HRM, e.g. in section 19.11.5
                                                                 "VF Function Level Reset". */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_lf_hwgrp_rst_s cn; */
};
typedef union bdk_sso_af_lf_hwgrp_rst bdk_sso_af_lf_hwgrp_rst_t;

#define BDK_SSO_AF_LF_HWGRP_RST BDK_SSO_AF_LF_HWGRP_RST_FUNC()
static inline uint64_t BDK_SSO_AF_LF_HWGRP_RST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_LF_HWGRP_RST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700010e0ll;
    __bdk_csr_fatal("SSO_AF_LF_HWGRP_RST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_LF_HWGRP_RST bdk_sso_af_lf_hwgrp_rst_t
#define bustype_BDK_SSO_AF_LF_HWGRP_RST BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_LF_HWGRP_RST "SSO_AF_LF_HWGRP_RST"
#define device_bar_BDK_SSO_AF_LF_HWGRP_RST 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_LF_HWGRP_RST 0
#define arguments_BDK_SSO_AF_LF_HWGRP_RST -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_nos_cnt
 *
 * SSO AF No-schedule Count Register
 * Contains the number of work-queue entries on the no-schedule list.
 */
union bdk_sso_af_nos_cnt
{
    uint64_t u;
    struct bdk_sso_af_nos_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t nos_cnt               : 13; /**< [ 12:  0](RO/H) Number of work-queue entries on the no-schedule list. */
#else /* Word 0 - Little Endian */
        uint64_t nos_cnt               : 13; /**< [ 12:  0](RO/H) Number of work-queue entries on the no-schedule list. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_nos_cnt_s cn9; */
    /* struct bdk_sso_af_nos_cnt_s cn96xx; */
    struct bdk_sso_af_nos_cnt_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t nos_cnt               : 13; /**< [ 12:  0](RO/H) Number of work-queue entries on the no-schedule list.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
#else /* Word 0 - Little Endian */
        uint64_t nos_cnt               : 13; /**< [ 12:  0](RO/H) Number of work-queue entries on the no-schedule list.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W-1) */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_nos_cnt_s cnf95xx; */
    /* struct bdk_sso_af_nos_cnt_s loki; */
};
typedef union bdk_sso_af_nos_cnt bdk_sso_af_nos_cnt_t;

#define BDK_SSO_AF_NOS_CNT BDK_SSO_AF_NOS_CNT_FUNC()
static inline uint64_t BDK_SSO_AF_NOS_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_NOS_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001050ll;
    __bdk_csr_fatal("SSO_AF_NOS_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_NOS_CNT bdk_sso_af_nos_cnt_t
#define bustype_BDK_SSO_AF_NOS_CNT BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_NOS_CNT "SSO_AF_NOS_CNT"
#define device_bar_BDK_SSO_AF_NOS_CNT 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_NOS_CNT 0
#define arguments_BDK_SSO_AF_NOS_CNT -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_npa_digest#
 *
 * SSO AF NPA Error Summary W1C Registers
 * One bit per HWGRP to indicate which groups have reported an SSO_AF_ERR0[NPA] error.
 */
union bdk_sso_af_npa_digestx
{
    uint64_t u;
    struct bdk_sso_af_npa_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_npa_digestx_s cn; */
};
typedef union bdk_sso_af_npa_digestx bdk_sso_af_npa_digestx_t;

static inline uint64_t BDK_SSO_AF_NPA_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_NPA_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900000ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_NPA_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_NPA_DIGESTX(a) bdk_sso_af_npa_digestx_t
#define bustype_BDK_SSO_AF_NPA_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_NPA_DIGESTX(a) "SSO_AF_NPA_DIGESTX"
#define device_bar_BDK_SSO_AF_NPA_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_NPA_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_NPA_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_npa_digest#_w1s
 *
 * SSO AF NPA Error Summary W1S Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_npa_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_npa_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_NPA_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_NPA_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_npa_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_npa_digestx_w1s bdk_sso_af_npa_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_NPA_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_NPA_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900100ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_NPA_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_NPA_DIGESTX_W1S(a) bdk_sso_af_npa_digestx_w1s_t
#define bustype_BDK_SSO_AF_NPA_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_NPA_DIGESTX_W1S(a) "SSO_AF_NPA_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_NPA_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_NPA_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_NPA_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_poison#
 *
 * SSO AF Poison Registers
 * These registers report which hardware group(s) have had POSION returned
 * during an XAQ read operation. There is one bit for each hardware group.
 */
union bdk_sso_af_poisonx
{
    uint64_t u;
    struct bdk_sso_af_poisonx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrps                : 64; /**< [ 63:  0](R/W1C/H) One bit per hardware group indicating XAQ poison. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrps                : 64; /**< [ 63:  0](R/W1C/H) One bit per hardware group indicating XAQ poison. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_poisonx_s cn; */
};
typedef union bdk_sso_af_poisonx bdk_sso_af_poisonx_t;

static inline uint64_t BDK_SSO_AF_POISONX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_POISONX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070002100ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_POISONX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_POISONX(a) bdk_sso_af_poisonx_t
#define bustype_BDK_SSO_AF_POISONX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_POISONX(a) "SSO_AF_POISONX"
#define device_bar_BDK_SSO_AF_POISONX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_POISONX(a) (a)
#define arguments_BDK_SSO_AF_POISONX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_poison#_w1s
 *
 * SSO AF Posion Set Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_poisonx_w1s
{
    uint64_t u;
    struct bdk_sso_af_poisonx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrps                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_POISON(0..3)[HWGRPS]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrps                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_POISON(0..3)[HWGRPS]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_poisonx_w1s_s cn; */
};
typedef union bdk_sso_af_poisonx_w1s bdk_sso_af_poisonx_w1s_t;

static inline uint64_t BDK_SSO_AF_POISONX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_POISONX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070002200ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_POISONX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_POISONX_W1S(a) bdk_sso_af_poisonx_w1s_t
#define bustype_BDK_SSO_AF_POISONX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_POISONX_W1S(a) "SSO_AF_POISONX_W1S"
#define device_bar_BDK_SSO_AF_POISONX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_POISONX_W1S(a) (a)
#define arguments_BDK_SSO_AF_POISONX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_qctldis_digest#
 *
 * SSO AF QCTLDIS Error Summary Registers
 * One bit per HWGRP to indicate which groups have reported an
 * SSO_AF_ERR0[ADDWQ_DROPPED_QCTLDIS] error.
 */
union bdk_sso_af_qctldis_digestx
{
    uint64_t u;
    struct bdk_sso_af_qctldis_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_qctldis_digestx_s cn; */
};
typedef union bdk_sso_af_qctldis_digestx bdk_sso_af_qctldis_digestx_t;

static inline uint64_t BDK_SSO_AF_QCTLDIS_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_QCTLDIS_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900e00ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_QCTLDIS_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_QCTLDIS_DIGESTX(a) bdk_sso_af_qctldis_digestx_t
#define bustype_BDK_SSO_AF_QCTLDIS_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_QCTLDIS_DIGESTX(a) "SSO_AF_QCTLDIS_DIGESTX"
#define device_bar_BDK_SSO_AF_QCTLDIS_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_QCTLDIS_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_QCTLDIS_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_qctldis_digest#_w1s
 *
 * SSO AF QCTLDIS Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_qctldis_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_qctldis_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_QCTLDIS_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_QCTLDIS_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_qctldis_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_qctldis_digestx_w1s bdk_sso_af_qctldis_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_QCTLDIS_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_QCTLDIS_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900f00ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_QCTLDIS_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_QCTLDIS_DIGESTX_W1S(a) bdk_sso_af_qctldis_digestx_w1s_t
#define bustype_BDK_SSO_AF_QCTLDIS_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_QCTLDIS_DIGESTX_W1S(a) "SSO_AF_QCTLDIS_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_QCTLDIS_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_QCTLDIS_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_QCTLDIS_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ras
 *
 * SSO AF RAS Register
 * This register reports and clears RAS interrupts.
 */
union bdk_sso_af_ras
{
    uint64_t u;
    struct bdk_sso_af_ras_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t xaq_psn               : 1;  /**< [  0:  0](R/W1C/H) An XAQ read returned poison. See SSO_AF_POISON() to determine which
                                                                 hardware group(s) have been affected. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_psn               : 1;  /**< [  0:  0](R/W1C/H) An XAQ read returned poison. See SSO_AF_POISON() to determine which
                                                                 hardware group(s) have been affected. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ras_s cn; */
};
typedef union bdk_sso_af_ras bdk_sso_af_ras_t;

#define BDK_SSO_AF_RAS BDK_SSO_AF_RAS_FUNC()
static inline uint64_t BDK_SSO_AF_RAS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_RAS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001420ll;
    __bdk_csr_fatal("SSO_AF_RAS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_RAS bdk_sso_af_ras_t
#define bustype_BDK_SSO_AF_RAS BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_RAS "SSO_AF_RAS"
#define device_bar_BDK_SSO_AF_RAS 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_RAS 0
#define arguments_BDK_SSO_AF_RAS -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ras_ena_w1c
 *
 * SSO AF RAS Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_sso_af_ras_ena_w1c
{
    uint64_t u;
    struct bdk_sso_af_ras_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t xaq_psn               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSO_AF_RAS[XAQ_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_psn               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSO_AF_RAS[XAQ_PSN]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ras_ena_w1c_s cn; */
};
typedef union bdk_sso_af_ras_ena_w1c bdk_sso_af_ras_ena_w1c_t;

#define BDK_SSO_AF_RAS_ENA_W1C BDK_SSO_AF_RAS_ENA_W1C_FUNC()
static inline uint64_t BDK_SSO_AF_RAS_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_RAS_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001460ll;
    __bdk_csr_fatal("SSO_AF_RAS_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_RAS_ENA_W1C bdk_sso_af_ras_ena_w1c_t
#define bustype_BDK_SSO_AF_RAS_ENA_W1C BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_RAS_ENA_W1C "SSO_AF_RAS_ENA_W1C"
#define device_bar_BDK_SSO_AF_RAS_ENA_W1C 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_RAS_ENA_W1C 0
#define arguments_BDK_SSO_AF_RAS_ENA_W1C -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ras_ena_w1s
 *
 * SSO AF RAS Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_sso_af_ras_ena_w1s
{
    uint64_t u;
    struct bdk_sso_af_ras_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t xaq_psn               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSO_AF_RAS[XAQ_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_psn               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSO_AF_RAS[XAQ_PSN]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ras_ena_w1s_s cn; */
};
typedef union bdk_sso_af_ras_ena_w1s bdk_sso_af_ras_ena_w1s_t;

#define BDK_SSO_AF_RAS_ENA_W1S BDK_SSO_AF_RAS_ENA_W1S_FUNC()
static inline uint64_t BDK_SSO_AF_RAS_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_RAS_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001470ll;
    __bdk_csr_fatal("SSO_AF_RAS_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_RAS_ENA_W1S bdk_sso_af_ras_ena_w1s_t
#define bustype_BDK_SSO_AF_RAS_ENA_W1S BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_RAS_ENA_W1S "SSO_AF_RAS_ENA_W1S"
#define device_bar_BDK_SSO_AF_RAS_ENA_W1S 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_RAS_ENA_W1S 0
#define arguments_BDK_SSO_AF_RAS_ENA_W1S -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ras_w1s
 *
 * SSO AF RAS Set Register
 * This register sets interrupt bits.
 */
union bdk_sso_af_ras_w1s
{
    uint64_t u;
    struct bdk_sso_af_ras_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t xaq_psn               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSO_AF_RAS[XAQ_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_psn               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSO_AF_RAS[XAQ_PSN]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ras_w1s_s cn; */
};
typedef union bdk_sso_af_ras_w1s bdk_sso_af_ras_w1s_t;

#define BDK_SSO_AF_RAS_W1S BDK_SSO_AF_RAS_W1S_FUNC()
static inline uint64_t BDK_SSO_AF_RAS_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_RAS_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001430ll;
    __bdk_csr_fatal("SSO_AF_RAS_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_RAS_W1S bdk_sso_af_ras_w1s_t
#define bustype_BDK_SSO_AF_RAS_W1S BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_RAS_W1S "SSO_AF_RAS_W1S"
#define device_bar_BDK_SSO_AF_RAS_W1S 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_RAS_W1S 0
#define arguments_BDK_SSO_AF_RAS_W1S -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_rvu_lf_cfg_debug
 *
 * SSO Privileged Local Function Configuration Debug Register
 */
union bdk_sso_af_rvu_lf_cfg_debug
{
    uint64_t u;
    struct bdk_sso_af_rvu_lf_cfg_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t pf_func               : 16; /**< [ 39: 24](R/W) RVU VF/PF for reverse lookup. Format defined by RVU_PF_FUNC_S. */
        uint64_t slot                  : 8;  /**< [ 23: 16](R/W) Slot within the VF/PF selected by [PF_FUNC] for reverse lookup. Must be
                                                                 zero for NIX and NPA. */
        uint64_t reserved_14_15        : 2;
        uint64_t exec                  : 1;  /**< [ 13: 13](R/W1S/H) Execute lookup. Writing a one to this bit initiates the reverse lookup
                                                                 from {[PF_FUNC], [SLOT]}. Hardware writes the lookup result to {[LF_VALID],
                                                                 [LF]} and clears this bit when done. */
        uint64_t lf_valid              : 1;  /**< [ 12: 12](RO/H) When set, indicates local function [LF] is provisioned to the VF/PF slot
                                                                 indexed by this register. When clear, a local function is not provisioned
                                                                 to the VF/PF slot. */
        uint64_t lf                    : 12; /**< [ 11:  0](RO/H) When [LF_VALID] is set, local function provisioned to the VF/PF slot. */
#else /* Word 0 - Little Endian */
        uint64_t lf                    : 12; /**< [ 11:  0](RO/H) When [LF_VALID] is set, local function provisioned to the VF/PF slot. */
        uint64_t lf_valid              : 1;  /**< [ 12: 12](RO/H) When set, indicates local function [LF] is provisioned to the VF/PF slot
                                                                 indexed by this register. When clear, a local function is not provisioned
                                                                 to the VF/PF slot. */
        uint64_t exec                  : 1;  /**< [ 13: 13](R/W1S/H) Execute lookup. Writing a one to this bit initiates the reverse lookup
                                                                 from {[PF_FUNC], [SLOT]}. Hardware writes the lookup result to {[LF_VALID],
                                                                 [LF]} and clears this bit when done. */
        uint64_t reserved_14_15        : 2;
        uint64_t slot                  : 8;  /**< [ 23: 16](R/W) Slot within the VF/PF selected by [PF_FUNC] for reverse lookup. Must be
                                                                 zero for NIX and NPA. */
        uint64_t pf_func               : 16; /**< [ 39: 24](R/W) RVU VF/PF for reverse lookup. Format defined by RVU_PF_FUNC_S. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_rvu_lf_cfg_debug_s cn; */
};
typedef union bdk_sso_af_rvu_lf_cfg_debug bdk_sso_af_rvu_lf_cfg_debug_t;

#define BDK_SSO_AF_RVU_LF_CFG_DEBUG BDK_SSO_AF_RVU_LF_CFG_DEBUG_FUNC()
static inline uint64_t BDK_SSO_AF_RVU_LF_CFG_DEBUG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_RVU_LF_CFG_DEBUG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070003800ll;
    __bdk_csr_fatal("SSO_AF_RVU_LF_CFG_DEBUG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_RVU_LF_CFG_DEBUG bdk_sso_af_rvu_lf_cfg_debug_t
#define bustype_BDK_SSO_AF_RVU_LF_CFG_DEBUG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_RVU_LF_CFG_DEBUG "SSO_AF_RVU_LF_CFG_DEBUG"
#define device_bar_BDK_SSO_AF_RVU_LF_CFG_DEBUG 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_RVU_LF_CFG_DEBUG 0
#define arguments_BDK_SSO_AF_RVU_LF_CFG_DEBUG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_taq#_link
 *
 * SSO AF Transitory Admission Queue Link Registers
 * Returns TAQ status for a given line.
 */
union bdk_sso_af_taqx_link
{
    uint64_t u;
    struct bdk_sso_af_taqx_link_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t next                  : 11; /**< [ 10:  0](RO/H) Next TAQ entry in linked list. Only valid when not at the tail of the list. */
#else /* Word 0 - Little Endian */
        uint64_t next                  : 11; /**< [ 10:  0](RO/H) Next TAQ entry in linked list. Only valid when not at the tail of the list. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_taqx_link_s cn; */
};
typedef union bdk_sso_af_taqx_link bdk_sso_af_taqx_link_t;

static inline uint64_t BDK_SSO_AF_TAQX_LINK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_TAQX_LINK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=1279))
        return 0x840070c00000ll + 8ll * ((a) & 0x7ff);
    __bdk_csr_fatal("SSO_AF_TAQX_LINK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_TAQX_LINK(a) bdk_sso_af_taqx_link_t
#define bustype_BDK_SSO_AF_TAQX_LINK(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_TAQX_LINK(a) "SSO_AF_TAQX_LINK"
#define device_bar_BDK_SSO_AF_TAQX_LINK(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_TAQX_LINK(a) (a)
#define arguments_BDK_SSO_AF_TAQX_LINK(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_taq#_wae#_tag
 *
 * SSO AF Transitory Admission Queue Tag Registers
 * Returns TAQ status for a given line and WAE within that line.
 */
union bdk_sso_af_taqx_waex_tag
{
    uint64_t u;
    struct bdk_sso_af_taqx_waex_tag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type of the TAQ entry. Enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag of the TAQ entry. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag of the TAQ entry. */
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type of the TAQ entry. Enumerated by SSO_TT_E. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_taqx_waex_tag_s cn; */
};
typedef union bdk_sso_af_taqx_waex_tag bdk_sso_af_taqx_waex_tag_t;

static inline uint64_t BDK_SSO_AF_TAQX_WAEX_TAG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_TAQX_WAEX_TAG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && ((a<=1279) && (b<=10)))
        return 0x840070e00000ll + 0x100ll * ((a) & 0x7ff) + 0x10ll * ((b) & 0xf);
    __bdk_csr_fatal("SSO_AF_TAQX_WAEX_TAG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_TAQX_WAEX_TAG(a,b) bdk_sso_af_taqx_waex_tag_t
#define bustype_BDK_SSO_AF_TAQX_WAEX_TAG(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_TAQX_WAEX_TAG(a,b) "SSO_AF_TAQX_WAEX_TAG"
#define device_bar_BDK_SSO_AF_TAQX_WAEX_TAG(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_TAQX_WAEX_TAG(a,b) (a)
#define arguments_BDK_SSO_AF_TAQX_WAEX_TAG(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_taq#_wae#_wqp
 *
 * SSO AF Transitory Admission Queue Pointer Registers
 * Returns TAQ status for a given line and WAE within that line.
 */
union bdk_sso_af_taqx_waex_wqp
{
    uint64_t u;
    struct bdk_sso_af_taqx_waex_wqp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) Work queue LF IOVA held in the TAQ entry.
                                                                 Bits \<63:49\> are a sign extension of \<52\>.  Bits \<2:0\> are 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) Work queue LF IOVA held in the TAQ entry.
                                                                 Bits \<63:49\> are a sign extension of \<52\>.  Bits \<2:0\> are 0x0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_taqx_waex_wqp_s cn; */
};
typedef union bdk_sso_af_taqx_waex_wqp bdk_sso_af_taqx_waex_wqp_t;

static inline uint64_t BDK_SSO_AF_TAQX_WAEX_WQP(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_TAQX_WAEX_WQP(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && ((a<=1279) && (b<=10)))
        return 0x840070e00008ll + 0x100ll * ((a) & 0x7ff) + 0x10ll * ((b) & 0xf);
    __bdk_csr_fatal("SSO_AF_TAQX_WAEX_WQP", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_TAQX_WAEX_WQP(a,b) bdk_sso_af_taqx_waex_wqp_t
#define bustype_BDK_SSO_AF_TAQX_WAEX_WQP(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_TAQX_WAEX_WQP(a,b) "SSO_AF_TAQX_WAEX_WQP"
#define device_bar_BDK_SSO_AF_TAQX_WAEX_WQP(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_TAQX_WAEX_WQP(a,b) (a)
#define arguments_BDK_SSO_AF_TAQX_WAEX_WQP(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_taq_add
 *
 * SSO AF Transitory Admission Queue Add Register
 */
union bdk_sso_af_taq_add
{
    uint64_t u;
    struct bdk_sso_af_taq_add_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t rsvd_free             : 13; /**< [ 28: 16](WO) Written value is added to SSO_AF_TAQ_CNT[RSVD_FREE] to prevent races between software and
                                                                 hardware changes. This is a two's complement value so subtraction may also be performed. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t rsvd_free             : 13; /**< [ 28: 16](WO) Written value is added to SSO_AF_TAQ_CNT[RSVD_FREE] to prevent races between software and
                                                                 hardware changes. This is a two's complement value so subtraction may also be performed. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_taq_add_s cn; */
};
typedef union bdk_sso_af_taq_add bdk_sso_af_taq_add_t;

#define BDK_SSO_AF_TAQ_ADD BDK_SSO_AF_TAQ_ADD_FUNC()
static inline uint64_t BDK_SSO_AF_TAQ_ADD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_TAQ_ADD_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700020e0ll;
    __bdk_csr_fatal("SSO_AF_TAQ_ADD", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_TAQ_ADD bdk_sso_af_taq_add_t
#define bustype_BDK_SSO_AF_TAQ_ADD BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_TAQ_ADD "SSO_AF_TAQ_ADD"
#define device_bar_BDK_SSO_AF_TAQ_ADD 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_TAQ_ADD 0
#define arguments_BDK_SSO_AF_TAQ_ADD -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_taq_cnt
 *
 * SSO AF Transitory Admission Queue Count Register
 */
union bdk_sso_af_taq_cnt
{
    uint64_t u;
    struct bdk_sso_af_taq_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_27_63        : 37;
        uint64_t rsvd_free             : 11; /**< [ 26: 16](R/W/H) Number of free reserved buffers. Used to ensure each hardware group may get a
                                                                 specific number of buffers. Must always be greater than or equal to the sum
                                                                 across all SSO_AF_HWGRP()_TAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to SSO_AF_HWGRP()_TAQ_THR[RSVD_THR] are going to be made. To
                                                                 prevent races, software should not change this register when SSO is being used;
                                                                 instead use SSO_AF_TAQ_ADD[RSVD_FREE]. Legal values are 0..0x4FF. */
        uint64_t reserved_11_15        : 5;
        uint64_t free_cnt              : 11; /**< [ 10:  0](RO/H) Number of total free buffers. */
#else /* Word 0 - Little Endian */
        uint64_t free_cnt              : 11; /**< [ 10:  0](RO/H) Number of total free buffers. */
        uint64_t reserved_11_15        : 5;
        uint64_t rsvd_free             : 11; /**< [ 26: 16](R/W/H) Number of free reserved buffers. Used to ensure each hardware group may get a
                                                                 specific number of buffers. Must always be greater than or equal to the sum
                                                                 across all SSO_AF_HWGRP()_TAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to SSO_AF_HWGRP()_TAQ_THR[RSVD_THR] are going to be made. To
                                                                 prevent races, software should not change this register when SSO is being used;
                                                                 instead use SSO_AF_TAQ_ADD[RSVD_FREE]. Legal values are 0..0x4FF. */
        uint64_t reserved_27_63        : 37;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_taq_cnt_s cn; */
};
typedef union bdk_sso_af_taq_cnt bdk_sso_af_taq_cnt_t;

#define BDK_SSO_AF_TAQ_CNT BDK_SSO_AF_TAQ_CNT_FUNC()
static inline uint64_t BDK_SSO_AF_TAQ_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_TAQ_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700020c0ll;
    __bdk_csr_fatal("SSO_AF_TAQ_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_TAQ_CNT bdk_sso_af_taq_cnt_t
#define bustype_BDK_SSO_AF_TAQ_CNT BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_TAQ_CNT "SSO_AF_TAQ_CNT"
#define device_bar_BDK_SSO_AF_TAQ_CNT 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_TAQ_CNT 0
#define arguments_BDK_SSO_AF_TAQ_CNT -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_tiaq#_status
 *
 * SSO AF Hardware Group Transitory Input Admission Queue Status Registers
 * This register returns TAQ inbound status indexed by hardware group.
 */
union bdk_sso_af_tiaqx_status
{
    uint64_t u;
    struct bdk_sso_af_tiaqx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wae_head              : 4;  /**< [ 63: 60](RO/H) Head's WAE number within current cache line, 0-10. This provides the second index into
                                                                 SSO_AF_TAQ()_WAE()_TAG and SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t wae_tail              : 4;  /**< [ 59: 56](RO/H) When [WAE_USED] is nonzero, this provides the next free WAE number in the cache
                                                                 line of the tail entry. If 0x0, the next entry will be placed at the beginning of
                                                                 a new cache line. This provides the second index into SSO_AF_TAQ()_WAE()_TAG and
                                                                 SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t reserved_47_55        : 9;
        uint64_t wae_used              : 15; /**< [ 46: 32](RO/H) Number of WAEs in use. */
        uint64_t reserved_23_31        : 9;
        uint64_t ent_head              : 11; /**< [ 22: 12](RO/H) Head's entry number. This provides the first index into SSO_AF_TAQ()_WAE()_TAG
                                                                 and SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t reserved_11           : 1;
        uint64_t ent_tail              : 11; /**< [ 10:  0](RO/H) Tail's entry number. This provides the first index into SSO_AF_TAQ()_WAE()_TAG
                                                                 and SSO_AF_TAQ()_WAE()_WQP. */
#else /* Word 0 - Little Endian */
        uint64_t ent_tail              : 11; /**< [ 10:  0](RO/H) Tail's entry number. This provides the first index into SSO_AF_TAQ()_WAE()_TAG
                                                                 and SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t reserved_11           : 1;
        uint64_t ent_head              : 11; /**< [ 22: 12](RO/H) Head's entry number. This provides the first index into SSO_AF_TAQ()_WAE()_TAG
                                                                 and SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t reserved_23_31        : 9;
        uint64_t wae_used              : 15; /**< [ 46: 32](RO/H) Number of WAEs in use. */
        uint64_t reserved_47_55        : 9;
        uint64_t wae_tail              : 4;  /**< [ 59: 56](RO/H) When [WAE_USED] is nonzero, this provides the next free WAE number in the cache
                                                                 line of the tail entry. If 0x0, the next entry will be placed at the beginning of
                                                                 a new cache line. This provides the second index into SSO_AF_TAQ()_WAE()_TAG and
                                                                 SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t wae_head              : 4;  /**< [ 63: 60](RO/H) Head's WAE number within current cache line, 0-10. This provides the second index into
                                                                 SSO_AF_TAQ()_WAE()_TAG and SSO_AF_TAQ()_WAE()_WQP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_tiaqx_status_s cn; */
};
typedef union bdk_sso_af_tiaqx_status bdk_sso_af_tiaqx_status_t;

static inline uint64_t BDK_SSO_AF_TIAQX_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_TIAQX_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x8400700c0000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_TIAQX_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_TIAQX_STATUS(a) bdk_sso_af_tiaqx_status_t
#define bustype_BDK_SSO_AF_TIAQX_STATUS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_TIAQX_STATUS(a) "SSO_AF_TIAQX_STATUS"
#define device_bar_BDK_SSO_AF_TIAQX_STATUS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_TIAQX_STATUS(a) (a)
#define arguments_BDK_SSO_AF_TIAQX_STATUS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_toaq#_status
 *
 * SSO AF Hardware Group Transitory Output Admission Queue Status Registers
 * This register returns TAQ outbound status indexed by hardware group.
 */
union bdk_sso_af_toaqx_status
{
    uint64_t u;
    struct bdk_sso_af_toaqx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t ext_vld               : 1;  /**< [ 61: 61](RO/H) External queuing is in use on this hardware group. */
        uint64_t partial               : 1;  /**< [ 60: 60](RO/H) Partial cache line is allocated to tail of queue. */
        uint64_t wae_tail              : 4;  /**< [ 59: 56](RO/H) If [PARTIAL] is set, this provides the next free WAE number in the cache line of
                                                                 the tail entry. If [PARTIAL] is clear, the next entry will be placed at the
                                                                 beginning of a new cache line. This provides the second index into
                                                                 SSO_AF_TAQ()_WAE()_TAG and SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t reserved_43_55        : 13;
        uint64_t cl_used               : 11; /**< [ 42: 32](RO/H) Number of cache lines in use. */
        uint64_t reserved_23_31        : 9;
        uint64_t ent_head              : 11; /**< [ 22: 12](RO/H) Head's entry number. This provides the first index into SSO_AF_TAQ()_WAE()_TAG
                                                                 and SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t reserved_11           : 1;
        uint64_t ent_tail              : 11; /**< [ 10:  0](RO/H) Tail's entry number. This provides the first index into SSO_AF_TAQ()_WAE()_TAG
                                                                 and SSO_AF_TAQ()_WAE()_WQP. */
#else /* Word 0 - Little Endian */
        uint64_t ent_tail              : 11; /**< [ 10:  0](RO/H) Tail's entry number. This provides the first index into SSO_AF_TAQ()_WAE()_TAG
                                                                 and SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t reserved_11           : 1;
        uint64_t ent_head              : 11; /**< [ 22: 12](RO/H) Head's entry number. This provides the first index into SSO_AF_TAQ()_WAE()_TAG
                                                                 and SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t reserved_23_31        : 9;
        uint64_t cl_used               : 11; /**< [ 42: 32](RO/H) Number of cache lines in use. */
        uint64_t reserved_43_55        : 13;
        uint64_t wae_tail              : 4;  /**< [ 59: 56](RO/H) If [PARTIAL] is set, this provides the next free WAE number in the cache line of
                                                                 the tail entry. If [PARTIAL] is clear, the next entry will be placed at the
                                                                 beginning of a new cache line. This provides the second index into
                                                                 SSO_AF_TAQ()_WAE()_TAG and SSO_AF_TAQ()_WAE()_WQP. */
        uint64_t partial               : 1;  /**< [ 60: 60](RO/H) Partial cache line is allocated to tail of queue. */
        uint64_t ext_vld               : 1;  /**< [ 61: 61](RO/H) External queuing is in use on this hardware group. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_toaqx_status_s cn; */
};
typedef union bdk_sso_af_toaqx_status bdk_sso_af_toaqx_status_t;

static inline uint64_t BDK_SSO_AF_TOAQX_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_TOAQX_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x8400700d0000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_TOAQX_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_TOAQX_STATUS(a) bdk_sso_af_toaqx_status_t
#define bustype_BDK_SSO_AF_TOAQX_STATUS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_TOAQX_STATUS(a) "SSO_AF_TOAQX_STATUS"
#define device_bar_BDK_SSO_AF_TOAQX_STATUS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_TOAQX_STATUS(a) (a)
#define arguments_BDK_SSO_AF_TOAQX_STATUS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_unmap_info
 *
 * SSO AF Unmapped Error Information Register
 * When any of SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP],
 * SSO_AF_ERR0[GGRP_MULTI], or SSO_AF_ERR0[ADDWQ_DROPPED_WQP0]
 * error occurs, this register is latched with information from the original request.
 * This register latches the first error detected for SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] and
 * the first error detected for SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
 * SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI]. Values in
 * register are held until errors are cleared in SSO_AF_ERR0 register.
 */
union bdk_sso_af_unmap_info
{
    uint64_t u;
    struct bdk_sso_af_unmap_info_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t wqp0_src              : 12; /**< [ 43: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<6\> = ZIP.
                                                                 \<5\> = TIM.
                                                                 \<4\> = NIXTX.
                                                                 \<3\> = DPI.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT.
                                                                 \<0\> = NIXRX. */
        uint64_t ggrp_multi            : 1;  /**< [ 31: 31](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[GGRP_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_unmap            : 1;  /**< [ 30: 30](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[GGRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[AW_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[AW_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t reserved_26_27        : 2;
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t reserved_26_27        : 2;
        uint64_t aw_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[AW_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[AW_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_unmap            : 1;  /**< [ 30: 30](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[GGRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_multi            : 1;  /**< [ 31: 31](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[GGRP_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t wqp0_src              : 12; /**< [ 43: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<6\> = ZIP.
                                                                 \<5\> = TIM.
                                                                 \<4\> = NIXTX.
                                                                 \<3\> = DPI.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT.
                                                                 \<0\> = NIXRX. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_unmap_info_s cn9; */
    struct bdk_sso_af_unmap_info_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_39_63        : 25;
        uint64_t wqp0_src              : 7;  /**< [ 38: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<6\> = ZIP.
                                                                 \<5\> = TIM.
                                                                 \<4\> = NIXTX.
                                                                 \<3\> = DPI.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT.
                                                                 \<0\> = NIXRX. */
        uint64_t ggrp_multi            : 1;  /**< [ 31: 31](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[GGRP_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_unmap            : 1;  /**< [ 30: 30](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[GGRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[AW_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[AW_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t reserved_26_27        : 2;
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t reserved_26_27        : 2;
        uint64_t aw_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[AW_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[AW_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_unmap            : 1;  /**< [ 30: 30](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[GGRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_multi            : 1;  /**< [ 31: 31](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[GGRP_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t wqp0_src              : 7;  /**< [ 38: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<6\> = ZIP.
                                                                 \<5\> = TIM.
                                                                 \<4\> = NIXTX.
                                                                 \<3\> = DPI.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT.
                                                                 \<0\> = NIXRX. */
        uint64_t reserved_39_63        : 25;
#endif /* Word 0 - End */
    } cn96xx;
    struct bdk_sso_af_unmap_info_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t wqp0_src              : 12; /**< [ 43: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<11\> = ZIP1.
                                                                 \<10\> = NIXTX1.
                                                                 \<9\> = DPI1.
                                                                 \<8\> = CPT1.
                                                                 \<7\> = NIXRX1.
                                                                 \<6\> = ZIP0.
                                                                 \<5\> = TIM.
                                                                 \<4\> = NIXTX0.
                                                                 \<3\> = DPI0.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT0.
                                                                 \<0\> = NIXRX0. */
        uint64_t ggrp_multi            : 1;  /**< [ 31: 31](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[GGRP_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_unmap            : 1;  /**< [ 30: 30](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[GGRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[AW_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[AW_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t reserved_26_27        : 2;
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t reserved_26_27        : 2;
        uint64_t aw_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[AW_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[AW_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_unmap            : 1;  /**< [ 30: 30](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[GGRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_multi            : 1;  /**< [ 31: 31](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[GGRP_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t wqp0_src              : 12; /**< [ 43: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<11\> = ZIP1.
                                                                 \<10\> = NIXTX1.
                                                                 \<9\> = DPI1.
                                                                 \<8\> = CPT1.
                                                                 \<7\> = NIXRX1.
                                                                 \<6\> = ZIP0.
                                                                 \<5\> = TIM.
                                                                 \<4\> = NIXTX0.
                                                                 \<3\> = DPI0.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT0.
                                                                 \<0\> = NIXRX0. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_sso_af_unmap_info_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t wqp0_src              : 8;  /**< [ 39: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<7\> = PSM.
                                                                 \<6\> = ZIP.
                                                                 \<5\> = TIM.
                                                                 \<4\> = NIXTX.
                                                                 \<3\> = DPI.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT.
                                                                 \<0\> = NIXRX. */
        uint64_t ggrp_multi            : 1;  /**< [ 31: 31](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[GGRP_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_unmap            : 1;  /**< [ 30: 30](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[GGRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[AW_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[AW_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t reserved_26_27        : 2;
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP] or SSO_AF_ERR0[GGRP_MULTI] and is held until all four
                                                                 errors are cleared in
                                                                 SSO_AF_ERR0. */
        uint64_t reserved_26_27        : 2;
        uint64_t aw_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[AW_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t aw_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[AW_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_unmap            : 1;  /**< [ 30: 30](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR0[GGRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI], SSO_AF_ERR0[GGRP_UNMAP], and
                                                                 SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t ggrp_multi            : 1;  /**< [ 31: 31](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR0[GGRP_MULTI] is set
                                                                 and held until SSO_AF_ERR0[AW_UNMAP], SSO_AF_ERR0[AW_MULTI],
                                                                 SSO_AF_ERR0[GGRP_UNMAP], and SSO_AF_ERR0[GGRP_MULTI] are cleared. */
        uint64_t wqp0_src              : 8;  /**< [ 39: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<7\> = PSM.
                                                                 \<6\> = ZIP.
                                                                 \<5\> = TIM.
                                                                 \<4\> = NIXTX.
                                                                 \<3\> = DPI.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT.
                                                                 \<0\> = NIXRX. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_sso_af_unmap_info_cnf95xx loki; */
};
typedef union bdk_sso_af_unmap_info bdk_sso_af_unmap_info_t;

#define BDK_SSO_AF_UNMAP_INFO BDK_SSO_AF_UNMAP_INFO_FUNC()
static inline uint64_t BDK_SSO_AF_UNMAP_INFO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_UNMAP_INFO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700012f0ll;
    __bdk_csr_fatal("SSO_AF_UNMAP_INFO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_UNMAP_INFO bdk_sso_af_unmap_info_t
#define bustype_BDK_SSO_AF_UNMAP_INFO BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_UNMAP_INFO "SSO_AF_UNMAP_INFO"
#define device_bar_BDK_SSO_AF_UNMAP_INFO 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_UNMAP_INFO 0
#define arguments_BDK_SSO_AF_UNMAP_INFO -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_unmap_info2
 *
 * SSO AF Unmapped Error2 Information Register
 * When any SSO_AF_ERR2[WS_GRP_UNMAP] or SSO_AF_ERR2[WS_GRP_MULTI] error occurs, this
 * register is latched with information from the original request. This register
 * latches the first error and will not be updated again until all of the
 * corresponding SSO_AF_ERR2 bits are cleared.
 */
union bdk_sso_af_unmap_info2
{
    uint64_t u;
    struct bdk_sso_af_unmap_info2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t cam_src               : 3;  /**< [ 34: 32](RO/H) Failing WS GCAM error path. This field is updated when one of he following errors
                                                                 occur: SSO_AF_ERR2[WS_GRP_UNMAP] or SSO_AF_ERR2[WS_GRP_MULTI] and is held until both
                                                                 errors are cleared from SSO_AF_ERR2. When multiple errors occur at the same
                                                                 time, the priority to latch error information is as follows: WS to PP, NCBO1 to WS,
                                                                 NCBO0 to WS.
                                                                 \<0\> = GGRP field in a WorkSlot Op failed
                                                                 \<1\> = One of the GGRP fields in a SSOW_LF_GWS_GRPMSK_CHG store failed. */
        uint64_t reserved_30_31        : 2;
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR2[WS_GRP_MULTI] is set
                                                                 and held until SSO_AF_ERR2[WS_GRP_MULTI] and SSO_AF_ERR2[WS_GRP_UNMAP] are cleared. */
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR2[WS_GRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR2[WS_GRP_UNMAP] and SSO_AF_ERR2[WS_GRP_MULTI] are cleared */
        uint64_t reserved_26_27        : 2;
        uint64_t grp                   : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP or HWGRP. See [CAM_SRC] to identify the
                                                                 type. This field is updated when  any of he following errors occur:
                                                                 SSO_AF_ERR2[WS_GRP_UNMAP] or SSO_AF_ERR2[WS_GRP_MULTI] and is held until all both
                                                                 errors are cleared in SSO_AF_ERR2. */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when any of he following errors occur:
                                                                 SSO_AF_ERR2[WS_GRP_UNMAP] or SSO_AF_ERR2[WS_GRP_MULTI] and is held until both errors
                                                                 are cleared from SSO_AF_ERR2. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when any of he following errors occur:
                                                                 SSO_AF_ERR2[WS_GRP_UNMAP] or SSO_AF_ERR2[WS_GRP_MULTI] and is held until both errors
                                                                 are cleared from SSO_AF_ERR2. */
        uint64_t grp                   : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP or HWGRP. See [CAM_SRC] to identify the
                                                                 type. This field is updated when  any of he following errors occur:
                                                                 SSO_AF_ERR2[WS_GRP_UNMAP] or SSO_AF_ERR2[WS_GRP_MULTI] and is held until all both
                                                                 errors are cleared in SSO_AF_ERR2. */
        uint64_t reserved_26_27        : 2;
        uint64_t ws_grp_unmap          : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR2[WS_GRP_UNMAP] is set and held
                                                                 until SSO_AF_ERR2[WS_GRP_UNMAP] and SSO_AF_ERR2[WS_GRP_MULTI] are cleared */
        uint64_t ws_grp_multi          : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR2[WS_GRP_MULTI] is set
                                                                 and held until SSO_AF_ERR2[WS_GRP_MULTI] and SSO_AF_ERR2[WS_GRP_UNMAP] are cleared. */
        uint64_t reserved_30_31        : 2;
        uint64_t cam_src               : 3;  /**< [ 34: 32](RO/H) Failing WS GCAM error path. This field is updated when one of he following errors
                                                                 occur: SSO_AF_ERR2[WS_GRP_UNMAP] or SSO_AF_ERR2[WS_GRP_MULTI] and is held until both
                                                                 errors are cleared from SSO_AF_ERR2. When multiple errors occur at the same
                                                                 time, the priority to latch error information is as follows: WS to PP, NCBO1 to WS,
                                                                 NCBO0 to WS.
                                                                 \<0\> = GGRP field in a WorkSlot Op failed
                                                                 \<1\> = One of the GGRP fields in a SSOW_LF_GWS_GRPMSK_CHG store failed. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_unmap_info2_s cn; */
};
typedef union bdk_sso_af_unmap_info2 bdk_sso_af_unmap_info2_t;

#define BDK_SSO_AF_UNMAP_INFO2 BDK_SSO_AF_UNMAP_INFO2_FUNC()
static inline uint64_t BDK_SSO_AF_UNMAP_INFO2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_UNMAP_INFO2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001300ll;
    __bdk_csr_fatal("SSO_AF_UNMAP_INFO2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_UNMAP_INFO2 bdk_sso_af_unmap_info2_t
#define bustype_BDK_SSO_AF_UNMAP_INFO2 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_UNMAP_INFO2 "SSO_AF_UNMAP_INFO2"
#define device_bar_BDK_SSO_AF_UNMAP_INFO2 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_UNMAP_INFO2 0
#define arguments_BDK_SSO_AF_UNMAP_INFO2 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_unmap_info3
 *
 * SSO AF Unmapped Error3 Information Register
 * When any SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI] error occurs, this
 * register is latched with information from the original request. This register
 * latches the first error and will not be updated again until all of the
 * corresponding SSO_AF_ERR2 bits are cleared.
 */
union bdk_sso_af_unmap_info3
{
    uint64_t u;
    struct bdk_sso_af_unmap_info3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t cam_src               : 3;  /**< [ 34: 32](RO/H) Failing WCAM error path. This field is updated when one of the following errors
                                                                 occur: SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI] and is held until both
                                                                 errors are cleared from SSO_AF_ERR2. */
        uint64_t reserved_30_31        : 2;
        uint64_t ws_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR2[WS_MULTI] is set
                                                                 and held until SSO_AF_ERR2[WS_MULTI] and SSO_AF_ERR2[WS_UNMAP] are cleared. */
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR2[WS_UNMAP] is set and held
                                                                 until SSO_AF_ERR2[WS_UNMAP] and SSO_AF_ERR2[WS_MULTI] are cleared. */
        uint64_t reserved_23_27        : 5;
        uint64_t gws                   : 7;  /**< [ 22: 16](RO/H) This field indicates the failing GWS. This field is updated when any
                                                                 of he following errors occur: SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI]
                                                                 and is held until all both errors are cleared in SSO_AF_ERR2. */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when any of the following errors occur:
                                                                 SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI] and is held until both errors
                                                                 are cleared from SSO_AF_ERR2. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when any of the following errors occur:
                                                                 SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI] and is held until both errors
                                                                 are cleared from SSO_AF_ERR2. */
        uint64_t gws                   : 7;  /**< [ 22: 16](RO/H) This field indicates the failing GWS. This field is updated when any
                                                                 of he following errors occur: SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI]
                                                                 and is held until all both errors are cleared in SSO_AF_ERR2. */
        uint64_t reserved_23_27        : 5;
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR2[WS_UNMAP] is set and held
                                                                 until SSO_AF_ERR2[WS_UNMAP] and SSO_AF_ERR2[WS_MULTI] are cleared. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR2[WS_MULTI] is set
                                                                 and held until SSO_AF_ERR2[WS_MULTI] and SSO_AF_ERR2[WS_UNMAP] are cleared. */
        uint64_t reserved_30_31        : 2;
        uint64_t cam_src               : 3;  /**< [ 34: 32](RO/H) Failing WCAM error path. This field is updated when one of the following errors
                                                                 occur: SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI] and is held until both
                                                                 errors are cleared from SSO_AF_ERR2. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_unmap_info3_s cn9; */
    /* struct bdk_sso_af_unmap_info3_s cn96xx; */
    struct bdk_sso_af_unmap_info3_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t cam_src               : 3;  /**< [ 34: 32](RO/H) Failing WCAM error path. This field is updated when one of the following errors
                                                                 occur: SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI] and is held until both
                                                                 errors are cleared from SSO_AF_ERR2. */
        uint64_t reserved_30_31        : 2;
        uint64_t ws_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR2[WS_MULTI] is set
                                                                 and held until SSO_AF_ERR2[WS_MULTI] and SSO_AF_ERR2[WS_UNMAP] are cleared. */
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR2[WS_UNMAP] is set and held
                                                                 until SSO_AF_ERR2[WS_UNMAP] and SSO_AF_ERR2[WS_MULTI] are cleared. */
        uint64_t reserved_23_27        : 5;
        uint64_t gws                   : 7;  /**< [ 22: 16](RO/H) This field indicates the failing GWS. This field is updated when any
                                                                 of he following errors occur: SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI]
                                                                 and is held until all both errors are cleared in SSO_AF_ERR2.

                                                                 Internal:
                                                                 (16..`SSO_NUM_WS-1+16) */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when any of the following errors occur:
                                                                 SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI] and is held until both errors
                                                                 are cleared from SSO_AF_ERR2. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](RO/H) Failing PF_FUNC. This field is updated when any of the following errors occur:
                                                                 SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI] and is held until both errors
                                                                 are cleared from SSO_AF_ERR2. */
        uint64_t gws                   : 7;  /**< [ 22: 16](RO/H) This field indicates the failing GWS. This field is updated when any
                                                                 of he following errors occur: SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI]
                                                                 and is held until all both errors are cleared in SSO_AF_ERR2.

                                                                 Internal:
                                                                 (16..`SSO_NUM_WS-1+16) */
        uint64_t reserved_23_27        : 5;
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](RO/H) PF_FUNC mapping not found error. Set when SSO_AF_ERR2[WS_UNMAP] is set and held
                                                                 until SSO_AF_ERR2[WS_UNMAP] and SSO_AF_ERR2[WS_MULTI] are cleared. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](RO/H) PF_FUNC map had double-hit error. Set when SSO_AF_ERR2[WS_MULTI] is set
                                                                 and held until SSO_AF_ERR2[WS_MULTI] and SSO_AF_ERR2[WS_UNMAP] are cleared. */
        uint64_t reserved_30_31        : 2;
        uint64_t cam_src               : 3;  /**< [ 34: 32](RO/H) Failing WCAM error path. This field is updated when one of the following errors
                                                                 occur: SSO_AF_ERR2[WS_UNMAP] or SSO_AF_ERR2[WS_MULTI] and is held until both
                                                                 errors are cleared from SSO_AF_ERR2. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_unmap_info3_s cnf95xx; */
    /* struct bdk_sso_af_unmap_info3_s loki; */
};
typedef union bdk_sso_af_unmap_info3 bdk_sso_af_unmap_info3_t;

#define BDK_SSO_AF_UNMAP_INFO3 BDK_SSO_AF_UNMAP_INFO3_FUNC()
static inline uint64_t BDK_SSO_AF_UNMAP_INFO3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_UNMAP_INFO3_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001310ll;
    __bdk_csr_fatal("SSO_AF_UNMAP_INFO3", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_UNMAP_INFO3 bdk_sso_af_unmap_info3_t
#define bustype_BDK_SSO_AF_UNMAP_INFO3 BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_UNMAP_INFO3 "SSO_AF_UNMAP_INFO3"
#define device_bar_BDK_SSO_AF_UNMAP_INFO3 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_UNMAP_INFO3 0
#define arguments_BDK_SSO_AF_UNMAP_INFO3 -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_wq_int_pc
 *
 * SSO AF Work-Queue Interrupt Periodic Counter Register
 * Contains the threshold value for the work-executable interrupt periodic counter and also a
 * read-only copy of the periodic counter. For more information on this register, refer to
 * Interrupts.
 */
union bdk_sso_af_wq_int_pc
{
    uint64_t u;
    struct bdk_sso_af_wq_int_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t pc                    : 28; /**< [ 59: 32](RO/H) Work-executable interrupt periodic counter. */
        uint64_t reserved_28_31        : 4;
        uint64_t pc_thr                : 20; /**< [ 27:  8](R/W) Work-executable interrupt periodic counter threshold. Zero disables the counter.
                                                                 If nonzero, the value must be \>= 3. */
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t pc_thr                : 20; /**< [ 27:  8](R/W) Work-executable interrupt periodic counter threshold. Zero disables the counter.
                                                                 If nonzero, the value must be \>= 3. */
        uint64_t reserved_28_31        : 4;
        uint64_t pc                    : 28; /**< [ 59: 32](RO/H) Work-executable interrupt periodic counter. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_wq_int_pc_s cn; */
};
typedef union bdk_sso_af_wq_int_pc bdk_sso_af_wq_int_pc_t;

#define BDK_SSO_AF_WQ_INT_PC BDK_SSO_AF_WQ_INT_PC_FUNC()
static inline uint64_t BDK_SSO_AF_WQ_INT_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WQ_INT_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001020ll;
    __bdk_csr_fatal("SSO_AF_WQ_INT_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WQ_INT_PC bdk_sso_af_wq_int_pc_t
#define bustype_BDK_SSO_AF_WQ_INT_PC BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WQ_INT_PC "SSO_AF_WQ_INT_PC"
#define device_bar_BDK_SSO_AF_WQ_INT_PC 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WQ_INT_PC 0
#define arguments_BDK_SSO_AF_WQ_INT_PC -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_wqp0_digest#
 *
 * SSO AF WQP0 Error Summary Registers
 * One bit per HWGRP to indicate which groups have reported an SSO_AF_ERR0[ADDWQ_DROPPED_WQP0] error.
 */
union bdk_sso_af_wqp0_digestx
{
    uint64_t u;
    struct bdk_sso_af_wqp0_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_wqp0_digestx_s cn; */
};
typedef union bdk_sso_af_wqp0_digestx bdk_sso_af_wqp0_digestx_t;

static inline uint64_t BDK_SSO_AF_WQP0_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WQP0_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900a00ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_WQP0_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WQP0_DIGESTX(a) bdk_sso_af_wqp0_digestx_t
#define bustype_BDK_SSO_AF_WQP0_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WQP0_DIGESTX(a) "SSO_AF_WQP0_DIGESTX"
#define device_bar_BDK_SSO_AF_WQP0_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WQP0_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_WQP0_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_wqp0_digest#_w1s
 *
 * SSO AF WQP0 Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_wqp0_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_wqp0_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WQP0_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WQP0_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_wqp0_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_wqp0_digestx_w1s bdk_sso_af_wqp0_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_WQP0_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WQP0_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070900b00ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_WQP0_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WQP0_DIGESTX_W1S(a) bdk_sso_af_wqp0_digestx_w1s_t
#define bustype_BDK_SSO_AF_WQP0_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WQP0_DIGESTX_W1S(a) "SSO_AF_WQP0_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_WQP0_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WQP0_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_WQP0_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_awe_digest#
 *
 * SSO AF WS IOP (ALLOC_WE_DIS) Error Summary Registers
 * One bit per HWS to indicate which workslots have reported an SSO_AF_ERR2[ALLOC_WE_DIS] error.
 */
union bdk_sso_af_ws_awe_digestx
{
    uint64_t u;
    struct bdk_sso_af_ws_awe_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_awe_digestx_s cn9; */
    struct bdk_sso_af_ws_awe_digestx_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_sso_af_ws_awe_digestx_s cn98xx; */
    /* struct bdk_sso_af_ws_awe_digestx_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_awe_digestx_cn96xx loki; */
};
typedef union bdk_sso_af_ws_awe_digestx bdk_sso_af_ws_awe_digestx_t;

static inline uint64_t BDK_SSO_AF_WS_AWE_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_AWE_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902400ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902400ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902400ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902400ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_AWE_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_AWE_DIGESTX(a) bdk_sso_af_ws_awe_digestx_t
#define bustype_BDK_SSO_AF_WS_AWE_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_AWE_DIGESTX(a) "SSO_AF_WS_AWE_DIGESTX"
#define device_bar_BDK_SSO_AF_WS_AWE_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_AWE_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_WS_AWE_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_awe_digest#_w1s
 *
 * SSO AF WS IOP (ALLOC_WE_DIS) Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_ws_awe_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_ws_awe_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_AWE_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_AWE_DIGEST(0)[HWS]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_awe_digestx_w1s_s cn9; */
    struct bdk_sso_af_ws_awe_digestx_w1s_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_AWE_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_AWE_DIGEST(0)[HWS]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    struct bdk_sso_af_ws_awe_digestx_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_AWE_DIGEST(0..1)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_AWE_DIGEST(0..1)[HWS]. */
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ws_awe_digestx_w1s_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_awe_digestx_w1s_cn96xx loki; */
};
typedef union bdk_sso_af_ws_awe_digestx_w1s bdk_sso_af_ws_awe_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_WS_AWE_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_AWE_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902500ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902500ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902500ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902500ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_AWE_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_AWE_DIGESTX_W1S(a) bdk_sso_af_ws_awe_digestx_w1s_t
#define bustype_BDK_SSO_AF_WS_AWE_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_AWE_DIGESTX_W1S(a) "SSO_AF_WS_AWE_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_WS_AWE_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_AWE_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_WS_AWE_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_cfg
 *
 * SSO AF Configuration Register
 * This register contains various SSO workslot configuration bits.
 */
union bdk_sso_af_ws_cfg
{
    uint64_t u;
    struct bdk_sso_af_ws_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t ocla_bp               : 8;  /**< [ 55: 48](R/W) Enable OCLA backpressure stalls. For diagnostic use only.
                                                                 Internal:
                                                                 \<55\> = NCBB input fifo stall (ncbo).
                                                                 \<54\> = Work-slot response. (arbrsp).
                                                                 \<53\> = Reserved.
                                                                 \<52\> = Work-slot SWTAG response. (arbs).
                                                                 \<51\> = Work-slot access to get-work engine. (arbgw).
                                                                 \<50\> = Reserved.
                                                                 \<49\> = Reserved.
                                                                 \<48\> = Work-slot pushes to AQ, CQ, DQ. (arbq). */
        uint64_t reserved_31_47        : 17;
        uint64_t bp_interval           : 3;  /**< [ 30: 28](R/W) Coprocessor-clock cycles between each 16 cycle interval of HWS backpressure.
                                                                 For diagnostic use only.
                                                                 0x0 = Disable this backpressure mechanism.
                                                                 0x1 =   64 cycles.
                                                                 0x2 =  128 cycles.
                                                                 0x3 =  256 cycles.
                                                                 0x4 =  512 cycles.
                                                                 0x5 = 1024 cycles.
                                                                 0x6 = 2048 cycles.
                                                                 0x7 = 4096 cycles. */
        uint64_t reserved_10_27        : 18;
        uint64_t dq_opt_ena            : 1;  /**< [  9:  9](R/W) Enable early DQ push optimization. */
        uint64_t force_ncbi_clk_en     : 1;  /**< [  8:  8](R/W) Force NCBI conditional clocks on. For diagnostic use only. */
        uint64_t sai_flush             : 1;  /**< [  7:  7](R/W1) When written with one, send a pulse to invalidate the GW cache
                                                                 inside the cores.  Reads as zero. For diagnostic use only. */
        uint64_t aw_clk_dis            : 1;  /**< [  6:  6](R/W) Reserved. */
        uint64_t gw_clk_dis            : 1;  /**< [  5:  5](R/W) Reserved. */
        uint64_t disable_pw            : 1;  /**< [  4:  4](R/W) Reserved. */
        uint64_t issue_step_en         : 1;  /**< [  3:  3](R/W) Enable single-stepping issue unit, 1 command at a time. For diagnostic use only. */
        uint64_t ncbo_step_en          : 1;  /**< [  2:  2](R/W) Enable single-stepping commands from NCBO, once per 32 clocks. For diagnostic use only. */
        uint64_t soc_ccam_dis          : 1;  /**< [  1:  1](R/W) Disable power saving SOC conditional CAM. */
        uint64_t sso_cclk_dis          : 1;  /**< [  0:  0](R/W) Disable power saving SSO conditional clocking, */
#else /* Word 0 - Little Endian */
        uint64_t sso_cclk_dis          : 1;  /**< [  0:  0](R/W) Disable power saving SSO conditional clocking, */
        uint64_t soc_ccam_dis          : 1;  /**< [  1:  1](R/W) Disable power saving SOC conditional CAM. */
        uint64_t ncbo_step_en          : 1;  /**< [  2:  2](R/W) Enable single-stepping commands from NCBO, once per 32 clocks. For diagnostic use only. */
        uint64_t issue_step_en         : 1;  /**< [  3:  3](R/W) Enable single-stepping issue unit, 1 command at a time. For diagnostic use only. */
        uint64_t disable_pw            : 1;  /**< [  4:  4](R/W) Reserved. */
        uint64_t gw_clk_dis            : 1;  /**< [  5:  5](R/W) Reserved. */
        uint64_t aw_clk_dis            : 1;  /**< [  6:  6](R/W) Reserved. */
        uint64_t sai_flush             : 1;  /**< [  7:  7](R/W1) When written with one, send a pulse to invalidate the GW cache
                                                                 inside the cores.  Reads as zero. For diagnostic use only. */
        uint64_t force_ncbi_clk_en     : 1;  /**< [  8:  8](R/W) Force NCBI conditional clocks on. For diagnostic use only. */
        uint64_t dq_opt_ena            : 1;  /**< [  9:  9](R/W) Enable early DQ push optimization. */
        uint64_t reserved_10_27        : 18;
        uint64_t bp_interval           : 3;  /**< [ 30: 28](R/W) Coprocessor-clock cycles between each 16 cycle interval of HWS backpressure.
                                                                 For diagnostic use only.
                                                                 0x0 = Disable this backpressure mechanism.
                                                                 0x1 =   64 cycles.
                                                                 0x2 =  128 cycles.
                                                                 0x3 =  256 cycles.
                                                                 0x4 =  512 cycles.
                                                                 0x5 = 1024 cycles.
                                                                 0x6 = 2048 cycles.
                                                                 0x7 = 4096 cycles. */
        uint64_t reserved_31_47        : 17;
        uint64_t ocla_bp               : 8;  /**< [ 55: 48](R/W) Enable OCLA backpressure stalls. For diagnostic use only.
                                                                 Internal:
                                                                 \<55\> = NCBB input fifo stall (ncbo).
                                                                 \<54\> = Work-slot response. (arbrsp).
                                                                 \<53\> = Reserved.
                                                                 \<52\> = Work-slot SWTAG response. (arbs).
                                                                 \<51\> = Work-slot access to get-work engine. (arbgw).
                                                                 \<50\> = Reserved.
                                                                 \<49\> = Reserved.
                                                                 \<48\> = Work-slot pushes to AQ, CQ, DQ. (arbq). */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_cfg_s cn; */
};
typedef union bdk_sso_af_ws_cfg bdk_sso_af_ws_cfg_t;

#define BDK_SSO_AF_WS_CFG BDK_SSO_AF_WS_CFG_FUNC()
static inline uint64_t BDK_SSO_AF_WS_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001088ll;
    __bdk_csr_fatal("SSO_AF_WS_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_CFG bdk_sso_af_ws_cfg_t
#define bustype_BDK_SSO_AF_WS_CFG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_CFG "SSO_AF_WS_CFG"
#define device_bar_BDK_SSO_AF_WS_CFG 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_CFG 0
#define arguments_BDK_SSO_AF_WS_CFG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_eco
 *
 * INTERNAL: SSO AF WS ECO Register
 */
union bdk_sso_af_ws_eco
{
    uint64_t u;
    struct bdk_sso_af_ws_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_eco_s cn; */
};
typedef union bdk_sso_af_ws_eco bdk_sso_af_ws_eco_t;

#define BDK_SSO_AF_WS_ECO BDK_SSO_AF_WS_ECO_FUNC()
static inline uint64_t BDK_SSO_AF_WS_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070001040ll;
    __bdk_csr_fatal("SSO_AF_WS_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_ECO bdk_sso_af_ws_eco_t
#define bustype_BDK_SSO_AF_WS_ECO BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_ECO "SSO_AF_WS_ECO"
#define device_bar_BDK_SSO_AF_WS_ECO 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_ECO 0
#define arguments_BDK_SSO_AF_WS_ECO -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_gmulti_digest#
 *
 * SSO AF WS GRP MULTI Error Summary Registers
 * One bit per HWS to indicate which workslots have reported an SSO_AF_ERR2[WS_GRP_MULTI] error.
 */
union bdk_sso_af_ws_gmulti_digestx
{
    uint64_t u;
    struct bdk_sso_af_ws_gmulti_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_gmulti_digestx_s cn9; */
    struct bdk_sso_af_ws_gmulti_digestx_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_sso_af_ws_gmulti_digestx_s cn98xx; */
    /* struct bdk_sso_af_ws_gmulti_digestx_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_gmulti_digestx_cn96xx loki; */
};
typedef union bdk_sso_af_ws_gmulti_digestx bdk_sso_af_ws_gmulti_digestx_t;

static inline uint64_t BDK_SSO_AF_WS_GMULTI_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_GMULTI_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902000ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902000ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902000ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_GMULTI_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_GMULTI_DIGESTX(a) bdk_sso_af_ws_gmulti_digestx_t
#define bustype_BDK_SSO_AF_WS_GMULTI_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_GMULTI_DIGESTX(a) "SSO_AF_WS_GMULTI_DIGESTX"
#define device_bar_BDK_SSO_AF_WS_GMULTI_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_GMULTI_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_WS_GMULTI_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_gmulti_digest#_w1s
 *
 * SSO AF WS GRP MULTI Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_ws_gmulti_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_ws_gmulti_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GMULTI_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GMULTI_DIGEST(0)[HWS]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_gmulti_digestx_w1s_s cn9; */
    struct bdk_sso_af_ws_gmulti_digestx_w1s_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_GMULTI_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_GMULTI_DIGEST(0)[HWS]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    struct bdk_sso_af_ws_gmulti_digestx_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GMULTI_DIGEST(0..1)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GMULTI_DIGEST(0..1)[HWS]. */
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ws_gmulti_digestx_w1s_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_gmulti_digestx_w1s_cn96xx loki; */
};
typedef union bdk_sso_af_ws_gmulti_digestx_w1s bdk_sso_af_ws_gmulti_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_WS_GMULTI_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_GMULTI_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902100ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902100ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902100ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902100ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_GMULTI_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_GMULTI_DIGESTX_W1S(a) bdk_sso_af_ws_gmulti_digestx_w1s_t
#define bustype_BDK_SSO_AF_WS_GMULTI_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_GMULTI_DIGESTX_W1S(a) "SSO_AF_WS_GMULTI_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_WS_GMULTI_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_GMULTI_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_WS_GMULTI_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_gunmap_digest#
 *
 * SSO AF WS GRP UNMAP Error Summary Registers
 * One bit per HWS to indicate which workslots have reported an SSO_AF_ERR2[WS_GRP_UNMAP] error.
 */
union bdk_sso_af_ws_gunmap_digestx
{
    uint64_t u;
    struct bdk_sso_af_ws_gunmap_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_gunmap_digestx_s cn9; */
    struct bdk_sso_af_ws_gunmap_digestx_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_sso_af_ws_gunmap_digestx_s cn98xx; */
    /* struct bdk_sso_af_ws_gunmap_digestx_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_gunmap_digestx_cn96xx loki; */
};
typedef union bdk_sso_af_ws_gunmap_digestx bdk_sso_af_ws_gunmap_digestx_t;

static inline uint64_t BDK_SSO_AF_WS_GUNMAP_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_GUNMAP_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902200ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902200ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902200ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902200ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_GUNMAP_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_GUNMAP_DIGESTX(a) bdk_sso_af_ws_gunmap_digestx_t
#define bustype_BDK_SSO_AF_WS_GUNMAP_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_GUNMAP_DIGESTX(a) "SSO_AF_WS_GUNMAP_DIGESTX"
#define device_bar_BDK_SSO_AF_WS_GUNMAP_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_GUNMAP_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_WS_GUNMAP_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_gunmap_digest#_w1s
 *
 * SSO AF WS GRP UNMAP Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_ws_gunmap_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_ws_gunmap_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GUNMAP_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GUNMAP_DIGEST(0)[HWS]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_gunmap_digestx_w1s_s cn9; */
    struct bdk_sso_af_ws_gunmap_digestx_w1s_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_GUNMAP_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_GUNMAP_DIGEST(0)[HWS]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    struct bdk_sso_af_ws_gunmap_digestx_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GUNMAP_DIGEST(0..1)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GUNMAP_DIGEST(0..1)[HWS]. */
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ws_gunmap_digestx_w1s_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_gunmap_digestx_w1s_cn96xx loki; */
};
typedef union bdk_sso_af_ws_gunmap_digestx_w1s bdk_sso_af_ws_gunmap_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_WS_GUNMAP_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_GUNMAP_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902300ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902300ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902300ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902300ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_GUNMAP_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_GUNMAP_DIGESTX_W1S(a) bdk_sso_af_ws_gunmap_digestx_w1s_t
#define bustype_BDK_SSO_AF_WS_GUNMAP_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_GUNMAP_DIGESTX_W1S(a) "SSO_AF_WS_GUNMAP_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_WS_GUNMAP_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_GUNMAP_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_WS_GUNMAP_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_gwi_digest#
 *
 * SSO AF WS IOP (GW Indexed with GW_IDX_ENA disabled) Error Summary Registers
 * One bit per HWS to indicate which workslots have reported an SSO_AF_ERR2[GW_IDX_DIS] error.
 */
union bdk_sso_af_ws_gwi_digestx
{
    uint64_t u;
    struct bdk_sso_af_ws_gwi_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_gwi_digestx_s cn9; */
    struct bdk_sso_af_ws_gwi_digestx_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_sso_af_ws_gwi_digestx_s cn98xx; */
    /* struct bdk_sso_af_ws_gwi_digestx_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_gwi_digestx_cn96xx loki; */
};
typedef union bdk_sso_af_ws_gwi_digestx bdk_sso_af_ws_gwi_digestx_t;

static inline uint64_t BDK_SSO_AF_WS_GWI_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_GWI_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902600ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902600ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902600ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902600ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_GWI_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_GWI_DIGESTX(a) bdk_sso_af_ws_gwi_digestx_t
#define bustype_BDK_SSO_AF_WS_GWI_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_GWI_DIGESTX(a) "SSO_AF_WS_GWI_DIGESTX"
#define device_bar_BDK_SSO_AF_WS_GWI_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_GWI_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_WS_GWI_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_gwi_digest#_w1s
 *
 * SSO AF WS IOP (GW Indexed with GW_IDX_ENA disabled) Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_ws_gwi_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_ws_gwi_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GWI_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GWI_DIGEST(0)[HWS]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_gwi_digestx_w1s_s cn9; */
    struct bdk_sso_af_ws_gwi_digestx_w1s_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_GWI_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_GWI_DIGEST(0)[HWS]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    struct bdk_sso_af_ws_gwi_digestx_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GWI_DIGEST(0..1)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_GWI_DIGEST(0..1)[HWS]. */
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ws_gwi_digestx_w1s_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_gwi_digestx_w1s_cn96xx loki; */
};
typedef union bdk_sso_af_ws_gwi_digestx_w1s bdk_sso_af_ws_gwi_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_WS_GWI_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_GWI_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902700ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902700ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902700ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902700ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_GWI_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_GWI_DIGESTX_W1S(a) bdk_sso_af_ws_gwi_digestx_w1s_t
#define bustype_BDK_SSO_AF_WS_GWI_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_GWI_DIGESTX_W1S(a) "SSO_AF_WS_GWI_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_WS_GWI_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_GWI_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_WS_GWI_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_ne_digest#
 *
 * SSO AF WS IOP (FLR initiated while not empty) Error Summary Registers
 * One bit per HWS to indicate which workslots have reported an SSO_AF_ERR2[WS_FLR_NE] error.
 */
union bdk_sso_af_ws_ne_digestx
{
    uint64_t u;
    struct bdk_sso_af_ws_ne_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_ne_digestx_s cn9; */
    struct bdk_sso_af_ws_ne_digestx_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_sso_af_ws_ne_digestx_s cn98xx; */
    /* struct bdk_sso_af_ws_ne_digestx_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_ne_digestx_cn96xx loki; */
};
typedef union bdk_sso_af_ws_ne_digestx bdk_sso_af_ws_ne_digestx_t;

static inline uint64_t BDK_SSO_AF_WS_NE_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_NE_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902800ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902800ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902800ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902800ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_NE_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_NE_DIGESTX(a) bdk_sso_af_ws_ne_digestx_t
#define bustype_BDK_SSO_AF_WS_NE_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_NE_DIGESTX(a) "SSO_AF_WS_NE_DIGESTX"
#define device_bar_BDK_SSO_AF_WS_NE_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_NE_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_WS_NE_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_ne_digest#_w1s
 *
 * SSO AF WS IOP (FLR initiated while not empty) Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_ws_ne_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_ws_ne_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_NE_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_NE_DIGEST(0)[HWS]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_ne_digestx_w1s_s cn9; */
    struct bdk_sso_af_ws_ne_digestx_w1s_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_NE_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_NE_DIGEST(0)[HWS]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    struct bdk_sso_af_ws_ne_digestx_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_NE_DIGEST(0..1)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_NE_DIGEST(0..1)[HWS]. */
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ws_ne_digestx_w1s_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_ne_digestx_w1s_cn96xx loki; */
};
typedef union bdk_sso_af_ws_ne_digestx_w1s bdk_sso_af_ws_ne_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_WS_NE_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_NE_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070902900ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070902900ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070902900ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070902900ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_NE_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_NE_DIGESTX_W1S(a) bdk_sso_af_ws_ne_digestx_w1s_t
#define bustype_BDK_SSO_AF_WS_NE_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_NE_DIGESTX_W1S(a) "SSO_AF_WS_NE_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_WS_NE_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_NE_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_WS_NE_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_ni_digest#
 *
 * SSO AF WS IOP (FLR initiated while not idle) Error Summary Registers
 * One bit per HWS to indicate which workslots have reported an SSO_AF_ERR2[WS_FLR_NI] error.
 */
union bdk_sso_af_ws_ni_digestx
{
    uint64_t u;
    struct bdk_sso_af_ws_ni_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1C/H) One bit per HWS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_ni_digestx_s cn9; */
    struct bdk_sso_af_ws_ni_digestx_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1C/H) One bit per HWS. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_sso_af_ws_ni_digestx_s cn98xx; */
    /* struct bdk_sso_af_ws_ni_digestx_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_ni_digestx_cn96xx loki; */
};
typedef union bdk_sso_af_ws_ni_digestx bdk_sso_af_ws_ni_digestx_t;

static inline uint64_t BDK_SSO_AF_WS_NI_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_NI_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070903000ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070903000ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070903000ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070903000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_NI_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_NI_DIGESTX(a) bdk_sso_af_ws_ni_digestx_t
#define bustype_BDK_SSO_AF_WS_NI_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_NI_DIGESTX(a) "SSO_AF_WS_NI_DIGESTX"
#define device_bar_BDK_SSO_AF_WS_NI_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_NI_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_WS_NI_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_ws_ni_digest#_w1s
 *
 * SSO AF WS IOP (FLR initiated while not idle) Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_ws_ni_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_ws_ni_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_NI_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_NI_DIGEST(0)[HWS]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_ws_ni_digestx_w1s_s cn9; */
    struct bdk_sso_af_ws_ni_digestx_w1s_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_NI_DIGEST(0)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 52; /**< [ 51:  0](R/W1S/H) Reads or sets SSO_AF_WS_NI_DIGEST(0)[HWS]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn96xx;
    struct bdk_sso_af_ws_ni_digestx_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_NI_DIGEST(0..1)[HWS]. */
#else /* Word 0 - Little Endian */
        uint64_t hws                   : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_WS_NI_DIGEST(0..1)[HWS]. */
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_af_ws_ni_digestx_w1s_cn96xx cnf95xx; */
    /* struct bdk_sso_af_ws_ni_digestx_w1s_cn96xx loki; */
};
typedef union bdk_sso_af_ws_ni_digestx_w1s bdk_sso_af_ws_ni_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_WS_NI_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_WS_NI_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x840070903100ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840070903100ll + 8ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x840070903100ll + 8ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x840070903100ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_AF_WS_NI_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_WS_NI_DIGESTX_W1S(a) bdk_sso_af_ws_ni_digestx_w1s_t
#define bustype_BDK_SSO_AF_WS_NI_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_WS_NI_DIGESTX_W1S(a) "SSO_AF_WS_NI_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_WS_NI_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_WS_NI_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_WS_NI_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_xaq#_gmctl
 *
 * SSO PF External Admission Queue Guest Machine Control Register
 */
union bdk_sso_af_xaqx_gmctl
{
    uint64_t u;
    struct bdk_sso_af_xaqx_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t pf_func               : 16; /**< [ 15:  0](R/W) NPA PF and function whose auras are used to allocate and free buffers.
                                                                 Format specified by RVU_PF_FUNC_S. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](R/W) NPA PF and function whose auras are used to allocate and free buffers.
                                                                 Format specified by RVU_PF_FUNC_S. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_xaqx_gmctl_s cn; */
};
typedef union bdk_sso_af_xaqx_gmctl bdk_sso_af_xaqx_gmctl_t;

static inline uint64_t BDK_SSO_AF_XAQX_GMCTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_XAQX_GMCTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x8400700e0000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_XAQX_GMCTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_XAQX_GMCTL(a) bdk_sso_af_xaqx_gmctl_t
#define bustype_BDK_SSO_AF_XAQX_GMCTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_XAQX_GMCTL(a) "SSO_AF_XAQX_GMCTL"
#define device_bar_BDK_SSO_AF_XAQX_GMCTL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_XAQX_GMCTL(a) (a)
#define arguments_BDK_SSO_AF_XAQX_GMCTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_xaq#_head_next
 *
 * SSO AF Hardware Group External Admission Queue Head Next Register
 * These registers contain the pointer to the next buffer to become the head when the final cache
 * line in this buffer is read.
 *
 * This register must not be written when SSO_AF_HWGRP()_AW_CFG[RWEN] is set.
 */
union bdk_sso_af_xaqx_head_next
{
    uint64_t u;
    struct bdk_sso_af_xaqx_head_next_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) LF IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) LF IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_xaqx_head_next_s cn; */
};
typedef union bdk_sso_af_xaqx_head_next bdk_sso_af_xaqx_head_next_t;

static inline uint64_t BDK_SSO_AF_XAQX_HEAD_NEXT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_XAQX_HEAD_NEXT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x8400700a0000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_XAQX_HEAD_NEXT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_XAQX_HEAD_NEXT(a) bdk_sso_af_xaqx_head_next_t
#define bustype_BDK_SSO_AF_XAQX_HEAD_NEXT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_XAQX_HEAD_NEXT(a) "SSO_AF_XAQX_HEAD_NEXT"
#define device_bar_BDK_SSO_AF_XAQX_HEAD_NEXT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_XAQX_HEAD_NEXT(a) (a)
#define arguments_BDK_SSO_AF_XAQX_HEAD_NEXT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_xaq#_head_ptr
 *
 * SSO AF Hardware-Group External Admission Queue Head Pointer Register
 * These registers contain the pointer to the first entry of the external linked
 * list(s) for a particular hardware group. These pointers are initialized by hardware.
 *
 * This register must not be written when SSO_AF_HWGRP()_AW_CFG[RWEN] is set.
 */
union bdk_sso_af_xaqx_head_ptr
{
    uint64_t u;
    struct bdk_sso_af_xaqx_head_ptr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) LF IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_5_6          : 2;
        uint64_t cl                    : 5;  /**< [  4:  0](R/W/H) Cache line number in buffer. Cache line zero contains the next pointer. */
#else /* Word 0 - Little Endian */
        uint64_t cl                    : 5;  /**< [  4:  0](R/W/H) Cache line number in buffer. Cache line zero contains the next pointer. */
        uint64_t reserved_5_6          : 2;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) LF IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_xaqx_head_ptr_s cn; */
};
typedef union bdk_sso_af_xaqx_head_ptr bdk_sso_af_xaqx_head_ptr_t;

static inline uint64_t BDK_SSO_AF_XAQX_HEAD_PTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_XAQX_HEAD_PTR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070080000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_XAQX_HEAD_PTR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_XAQX_HEAD_PTR(a) bdk_sso_af_xaqx_head_ptr_t
#define bustype_BDK_SSO_AF_XAQX_HEAD_PTR(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_XAQX_HEAD_PTR(a) "SSO_AF_XAQX_HEAD_PTR"
#define device_bar_BDK_SSO_AF_XAQX_HEAD_PTR(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_XAQX_HEAD_PTR(a) (a)
#define arguments_BDK_SSO_AF_XAQX_HEAD_PTR(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_xaq#_tail_next
 *
 * SSO AF Hardware Group External Admission Queue Tail Next Register
 * These registers contain the pointer to the next buffer to become the tail when the final cache
 * line in this buffer is written.  Register fields are identical to those in
 * SSO_AF_XAQ()_HEAD_NEXT above.
 *
 * This register must not be written when SSO_AF_HWGRP()_AW_CFG[RWEN] is set.
 */
union bdk_sso_af_xaqx_tail_next
{
    uint64_t u;
    struct bdk_sso_af_xaqx_tail_next_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) LF IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) LF IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_xaqx_tail_next_s cn; */
};
typedef union bdk_sso_af_xaqx_tail_next bdk_sso_af_xaqx_tail_next_t;

static inline uint64_t BDK_SSO_AF_XAQX_TAIL_NEXT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_XAQX_TAIL_NEXT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x8400700b0000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_XAQX_TAIL_NEXT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_XAQX_TAIL_NEXT(a) bdk_sso_af_xaqx_tail_next_t
#define bustype_BDK_SSO_AF_XAQX_TAIL_NEXT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_XAQX_TAIL_NEXT(a) "SSO_AF_XAQX_TAIL_NEXT"
#define device_bar_BDK_SSO_AF_XAQX_TAIL_NEXT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_XAQX_TAIL_NEXT(a) (a)
#define arguments_BDK_SSO_AF_XAQX_TAIL_NEXT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_xaq#_tail_ptr
 *
 * SSO AF Hardware-Group External Admission Queue Tail Pointer Register
 * These registers contain the pointer to the last entry of the external linked list(s)
 * for a particular hardware group. Register fields are identical to those in
 * SSO_AF_XAQ()_HEAD_PTR above.
 *
 * During an FLR event, software must return the reset group's tail pointers to NPA and clear
 * SSO_AF_HWGRP()_AW_STATUS[TPTR_VLD].
 *
 * This register must not be written when SSO_AF_HWGRP()_AW_CFG[RWEN] is set.
 */
union bdk_sso_af_xaqx_tail_ptr
{
    uint64_t u;
    struct bdk_sso_af_xaqx_tail_ptr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) LF IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_5_6          : 2;
        uint64_t cl                    : 5;  /**< [  4:  0](R/W/H) Cache line number in buffer. Cache line zero contains the next pointer. */
#else /* Word 0 - Little Endian */
        uint64_t cl                    : 5;  /**< [  4:  0](R/W/H) Cache line number in buffer. Cache line zero contains the next pointer. */
        uint64_t reserved_5_6          : 2;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) LF IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_xaqx_tail_ptr_s cn; */
};
typedef union bdk_sso_af_xaqx_tail_ptr bdk_sso_af_xaqx_tail_ptr_t;

static inline uint64_t BDK_SSO_AF_XAQX_TAIL_PTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_XAQX_TAIL_PTR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070090000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_AF_XAQX_TAIL_PTR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_XAQX_TAIL_PTR(a) bdk_sso_af_xaqx_tail_ptr_t
#define bustype_BDK_SSO_AF_XAQX_TAIL_PTR(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_XAQX_TAIL_PTR(a) "SSO_AF_XAQX_TAIL_PTR"
#define device_bar_BDK_SSO_AF_XAQX_TAIL_PTR(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_XAQX_TAIL_PTR(a) (a)
#define arguments_BDK_SSO_AF_XAQX_TAIL_PTR(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_xaq_latency_pc
 *
 * SSO AF External Admission Queue Latency Perf-Count Register
 */
union bdk_sso_af_xaq_latency_pc
{
    uint64_t u;
    struct bdk_sso_af_xaq_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for XAQ read returns. This may be divided by SSO_AF_XAQ_REQ_PC to
                                                                 determine the average read latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for XAQ read returns. This may be divided by SSO_AF_XAQ_REQ_PC to
                                                                 determine the average read latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_xaq_latency_pc_s cn; */
};
typedef union bdk_sso_af_xaq_latency_pc bdk_sso_af_xaq_latency_pc_t;

#define BDK_SSO_AF_XAQ_LATENCY_PC BDK_SSO_AF_XAQ_LATENCY_PC_FUNC()
static inline uint64_t BDK_SSO_AF_XAQ_LATENCY_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_XAQ_LATENCY_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700020b8ll;
    __bdk_csr_fatal("SSO_AF_XAQ_LATENCY_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_XAQ_LATENCY_PC bdk_sso_af_xaq_latency_pc_t
#define bustype_BDK_SSO_AF_XAQ_LATENCY_PC BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_XAQ_LATENCY_PC "SSO_AF_XAQ_LATENCY_PC"
#define device_bar_BDK_SSO_AF_XAQ_LATENCY_PC 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_XAQ_LATENCY_PC 0
#define arguments_BDK_SSO_AF_XAQ_LATENCY_PC -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_xaq_req_pc
 *
 * SSO AF External Admission Queue Requests Perf-Count Register
 */
union bdk_sso_af_xaq_req_pc
{
    uint64_t u;
    struct bdk_sso_af_xaq_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of XAQ read requests. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of XAQ read requests. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_xaq_req_pc_s cn; */
};
typedef union bdk_sso_af_xaq_req_pc bdk_sso_af_xaq_req_pc_t;

#define BDK_SSO_AF_XAQ_REQ_PC BDK_SSO_AF_XAQ_REQ_PC_FUNC()
static inline uint64_t BDK_SSO_AF_XAQ_REQ_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_XAQ_REQ_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8400700020b0ll;
    __bdk_csr_fatal("SSO_AF_XAQ_REQ_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_XAQ_REQ_PC bdk_sso_af_xaq_req_pc_t
#define bustype_BDK_SSO_AF_XAQ_REQ_PC BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_XAQ_REQ_PC "SSO_AF_XAQ_REQ_PC"
#define device_bar_BDK_SSO_AF_XAQ_REQ_PC 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_XAQ_REQ_PC 0
#define arguments_BDK_SSO_AF_XAQ_REQ_PC -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_xaqdis_digest#
 *
 * SSO AF XAQDIS Error Summary Registers
 * One bit per HWGRP to indicate which groups have reported an SSO_AF_ERR0[ADDWQ_DROPPED_XAQEN] error.
 */
union bdk_sso_af_xaqdis_digestx
{
    uint64_t u;
    struct bdk_sso_af_xaqdis_digestx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1C/H) One bit per HWGRP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_xaqdis_digestx_s cn; */
};
typedef union bdk_sso_af_xaqdis_digestx bdk_sso_af_xaqdis_digestx_t;

static inline uint64_t BDK_SSO_AF_XAQDIS_DIGESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_XAQDIS_DIGESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070901000ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_XAQDIS_DIGESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_XAQDIS_DIGESTX(a) bdk_sso_af_xaqdis_digestx_t
#define bustype_BDK_SSO_AF_XAQDIS_DIGESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_XAQDIS_DIGESTX(a) "SSO_AF_XAQDIS_DIGESTX"
#define device_bar_BDK_SSO_AF_XAQDIS_DIGESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_XAQDIS_DIGESTX(a) (a)
#define arguments_BDK_SSO_AF_XAQDIS_DIGESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_af_xaqdis_digest#_w1s
 *
 * SSO AF XAQDIS Error Summary Registers
 * This register reads or sets bits.
 */
union bdk_sso_af_xaqdis_digestx_w1s
{
    uint64_t u;
    struct bdk_sso_af_xaqdis_digestx_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_XAQDIS_DIGEST(0..3)[HWGRP]. */
#else /* Word 0 - Little Endian */
        uint64_t hwgrp                 : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_AF_XAQDIS_DIGEST(0..3)[HWGRP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_af_xaqdis_digestx_w1s_s cn; */
};
typedef union bdk_sso_af_xaqdis_digestx_w1s bdk_sso_af_xaqdis_digestx_w1s_t;

static inline uint64_t BDK_SSO_AF_XAQDIS_DIGESTX_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AF_XAQDIS_DIGESTX_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840070901100ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_AF_XAQDIS_DIGESTX_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AF_XAQDIS_DIGESTX_W1S(a) bdk_sso_af_xaqdis_digestx_w1s_t
#define bustype_BDK_SSO_AF_XAQDIS_DIGESTX_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_AF_XAQDIS_DIGESTX_W1S(a) "SSO_AF_XAQDIS_DIGESTX_W1S"
#define device_bar_BDK_SSO_AF_XAQDIS_DIGESTX_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_AF_XAQDIS_DIGESTX_W1S(a) (a)
#define arguments_BDK_SSO_AF_XAQDIS_DIGESTX_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_aw_add
 *
 * SSO PF Work-Entries Add Register
 */
union bdk_sso_aw_add
{
    uint64_t u;
    struct bdk_sso_aw_add_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t rsvd_free             : 14; /**< [ 29: 16](WO) Written value is added to SSO_AW_WE[RSVD_FREE] to prevent races between software and
                                                                 hardware changes. This is a two's complement value so subtraction may also be performed. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t rsvd_free             : 14; /**< [ 29: 16](WO) Written value is added to SSO_AW_WE[RSVD_FREE] to prevent races between software and
                                                                 hardware changes. This is a two's complement value so subtraction may also be performed. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_aw_add_s cn; */
};
typedef union bdk_sso_aw_add bdk_sso_aw_add_t;

#define BDK_SSO_AW_ADD BDK_SSO_AW_ADD_FUNC()
static inline uint64_t BDK_SSO_AW_ADD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AW_ADD_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000002080ll;
    __bdk_csr_fatal("SSO_AW_ADD", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AW_ADD bdk_sso_aw_add_t
#define bustype_BDK_SSO_AW_ADD BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_AW_ADD "SSO_AW_ADD"
#define device_bar_BDK_SSO_AW_ADD 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_AW_ADD 0
#define arguments_BDK_SSO_AW_ADD -1,-1,-1,-1

/**
 * Register (NCB) sso_aw_cfg
 *
 * SSO PF Add-Work Configuration Register
 * This register controls the operation of the add-work block (AW).
 */
union bdk_sso_aw_cfg
{
    uint64_t u;
    struct bdk_sso_aw_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ldt_short             : 1;  /**< [  8:  8](R/W) Use LDT to bypass L2 allocations when reading short form work. */
        uint64_t lol                   : 1;  /**< [  7:  7](R/W) Reserved. */
        uint64_t xaq_alloc_dis         : 1;  /**< [  6:  6](R/W) Disable FPA alloc requests to fill the SSO page cache. Also all existing cached free
                                                                 buffers will be returned to FPA and will not be cached. */
        uint64_t ocla_bp               : 1;  /**< [  5:  5](R/W) OCLA backpressure enable. When OCLA FIFOs are near full, allow OCLA to backpressure AW pipeline. */
        uint64_t xaq_byp_dis           : 1;  /**< [  4:  4](R/W) Disable bypass path in add-work engine. For diagnostic use only. */
        uint64_t stt                   : 1;  /**< [  3:  3](R/W) Use STT to bypass L2 allocation for XAQ store operations. When this bit is not set it uses STF. */
        uint64_t ldt                   : 1;  /**< [  2:  2](R/W) Use LDT to bypass L2 allocation for XAQ load operations when [LDWB] is not
                                                                 set. When [LDT] and [LDWB] are both clear, uses LDD load type. */
        uint64_t ldwb                  : 1;  /**< [  1:  1](R/W) When reading XAQ cache lines, use LDWB transactions to invalidate the cache
                                                                 line. When clear, use [LDT] to determine load type. */
        uint64_t rwen                  : 1;  /**< [  0:  0](R/W) Enable XAQ operations. This bit should be set after SSO_XAQ()_HEAD_PTR and
                                                                 SSO_XAQ()_TAIL_PTR have been programmed. If cleared, all cached buffers will be
                                                                 returned from the FPA as soon as possible, and TAQ arbitration is simplified. */
#else /* Word 0 - Little Endian */
        uint64_t rwen                  : 1;  /**< [  0:  0](R/W) Enable XAQ operations. This bit should be set after SSO_XAQ()_HEAD_PTR and
                                                                 SSO_XAQ()_TAIL_PTR have been programmed. If cleared, all cached buffers will be
                                                                 returned from the FPA as soon as possible, and TAQ arbitration is simplified. */
        uint64_t ldwb                  : 1;  /**< [  1:  1](R/W) When reading XAQ cache lines, use LDWB transactions to invalidate the cache
                                                                 line. When clear, use [LDT] to determine load type. */
        uint64_t ldt                   : 1;  /**< [  2:  2](R/W) Use LDT to bypass L2 allocation for XAQ load operations when [LDWB] is not
                                                                 set. When [LDT] and [LDWB] are both clear, uses LDD load type. */
        uint64_t stt                   : 1;  /**< [  3:  3](R/W) Use STT to bypass L2 allocation for XAQ store operations. When this bit is not set it uses STF. */
        uint64_t xaq_byp_dis           : 1;  /**< [  4:  4](R/W) Disable bypass path in add-work engine. For diagnostic use only. */
        uint64_t ocla_bp               : 1;  /**< [  5:  5](R/W) OCLA backpressure enable. When OCLA FIFOs are near full, allow OCLA to backpressure AW pipeline. */
        uint64_t xaq_alloc_dis         : 1;  /**< [  6:  6](R/W) Disable FPA alloc requests to fill the SSO page cache. Also all existing cached free
                                                                 buffers will be returned to FPA and will not be cached. */
        uint64_t lol                   : 1;  /**< [  7:  7](R/W) Reserved. */
        uint64_t ldt_short             : 1;  /**< [  8:  8](R/W) Use LDT to bypass L2 allocations when reading short form work. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_aw_cfg_s cn; */
};
typedef union bdk_sso_aw_cfg bdk_sso_aw_cfg_t;

#define BDK_SSO_AW_CFG BDK_SSO_AW_CFG_FUNC()
static inline uint64_t BDK_SSO_AW_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AW_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000010f0ll;
    __bdk_csr_fatal("SSO_AW_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AW_CFG bdk_sso_aw_cfg_t
#define bustype_BDK_SSO_AW_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_AW_CFG "SSO_AW_CFG"
#define device_bar_BDK_SSO_AW_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_AW_CFG 0
#define arguments_BDK_SSO_AW_CFG -1,-1,-1,-1

/**
 * Register (NCB) sso_aw_eco
 *
 * INTERNAL: SSO PF AW ECO Register
 */
union bdk_sso_aw_eco
{
    uint64_t u;
    struct bdk_sso_aw_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_aw_eco_s cn; */
};
typedef union bdk_sso_aw_eco bdk_sso_aw_eco_t;

#define BDK_SSO_AW_ECO BDK_SSO_AW_ECO_FUNC()
static inline uint64_t BDK_SSO_AW_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AW_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001030ll;
    __bdk_csr_fatal("SSO_AW_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AW_ECO bdk_sso_aw_eco_t
#define bustype_BDK_SSO_AW_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_AW_ECO "SSO_AW_ECO"
#define device_bar_BDK_SSO_AW_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_AW_ECO 0
#define arguments_BDK_SSO_AW_ECO -1,-1,-1,-1

/**
 * Register (NCB) sso_aw_inp_ctl
 *
 * SSO PF Add-Work Input Control Register
 */
union bdk_sso_aw_inp_ctl
{
    uint64_t u;
    struct bdk_sso_aw_inp_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t wa_dis                : 13; /**< [ 12:  0](R/W) Add-work input disable.  Each bit corresponds to a hardware input queue, and if
                                                                 set add-works from the corresponding coprocessor will be dropped.
                                                                 Bit numbers enumerated by SSO_WA_E. */
#else /* Word 0 - Little Endian */
        uint64_t wa_dis                : 13; /**< [ 12:  0](R/W) Add-work input disable.  Each bit corresponds to a hardware input queue, and if
                                                                 set add-works from the corresponding coprocessor will be dropped.
                                                                 Bit numbers enumerated by SSO_WA_E. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_aw_inp_ctl_s cn; */
};
typedef union bdk_sso_aw_inp_ctl bdk_sso_aw_inp_ctl_t;

#define BDK_SSO_AW_INP_CTL BDK_SSO_AW_INP_CTL_FUNC()
static inline uint64_t BDK_SSO_AW_INP_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AW_INP_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000002070ll;
    __bdk_csr_fatal("SSO_AW_INP_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AW_INP_CTL bdk_sso_aw_inp_ctl_t
#define bustype_BDK_SSO_AW_INP_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_AW_INP_CTL "SSO_AW_INP_CTL"
#define device_bar_BDK_SSO_AW_INP_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_AW_INP_CTL 0
#define arguments_BDK_SSO_AW_INP_CTL -1,-1,-1,-1

/**
 * Register (NCB) sso_aw_read_arb
 *
 * SSO PF Read Arbitration Register
 * This register fine tunes the AW read arbiter and is for diagnostic use.
 */
union bdk_sso_aw_read_arb
{
    uint64_t u;
    struct bdk_sso_aw_read_arb_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW_TAG reads in flight. */
        uint64_t reserved_14_15        : 2;
        uint64_t aw_tag_lev            : 6;  /**< [ 13:  8](RO/H) Current number of tag reads outstanding. */
        uint64_t reserved_5_7          : 3;
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Number of read slots reserved for AQ tag read exclusive use. */
#else /* Word 0 - Little Endian */
        uint64_t aw_tag_min            : 5;  /**< [  4:  0](R/W) Number of read slots reserved for AQ tag read exclusive use. */
        uint64_t reserved_5_7          : 3;
        uint64_t aw_tag_lev            : 6;  /**< [ 13:  8](RO/H) Current number of tag reads outstanding. */
        uint64_t reserved_14_15        : 2;
        uint64_t xaq_min               : 5;  /**< [ 20: 16](R/W) Number of read slots reserved for XAQ exclusive use. Values \> 16 will not result in
                                                                 additional XAQ reads in flight, but will reduce maximum AW_TAG reads in flight. */
        uint64_t reserved_21_23        : 3;
        uint64_t xaq_lev               : 6;  /**< [ 29: 24](RO/H) Current number of XAQ reads outstanding. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_aw_read_arb_s cn; */
};
typedef union bdk_sso_aw_read_arb bdk_sso_aw_read_arb_t;

#define BDK_SSO_AW_READ_ARB BDK_SSO_AW_READ_ARB_FUNC()
static inline uint64_t BDK_SSO_AW_READ_ARB_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AW_READ_ARB_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000002090ll;
    __bdk_csr_fatal("SSO_AW_READ_ARB", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AW_READ_ARB bdk_sso_aw_read_arb_t
#define bustype_BDK_SSO_AW_READ_ARB BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_AW_READ_ARB "SSO_AW_READ_ARB"
#define device_bar_BDK_SSO_AW_READ_ARB 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_AW_READ_ARB 0
#define arguments_BDK_SSO_AW_READ_ARB -1,-1,-1,-1

/**
 * Register (NCB) sso_aw_status
 *
 * SSO PF Add-Work Status Register
 * This register indicates the status of the add-work block (AW).
 */
union bdk_sso_aw_status
{
    uint64_t u;
    struct bdk_sso_aw_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t xaq_buf_cached        : 6;  /**< [  5:  0](RO/H) Indicates number of FPA buffers cached inside SSO. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_buf_cached        : 6;  /**< [  5:  0](RO/H) Indicates number of FPA buffers cached inside SSO. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_aw_status_s cn; */
};
typedef union bdk_sso_aw_status bdk_sso_aw_status_t;

#define BDK_SSO_AW_STATUS BDK_SSO_AW_STATUS_FUNC()
static inline uint64_t BDK_SSO_AW_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AW_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000010e0ll;
    __bdk_csr_fatal("SSO_AW_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AW_STATUS bdk_sso_aw_status_t
#define bustype_BDK_SSO_AW_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_AW_STATUS "SSO_AW_STATUS"
#define device_bar_BDK_SSO_AW_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_AW_STATUS 0
#define arguments_BDK_SSO_AW_STATUS -1,-1,-1,-1

/**
 * Register (NCB) sso_aw_tag_latency_pc
 *
 * SSO PF Short Form Tag Requests Perf-Count Register
 */
union bdk_sso_aw_tag_latency_pc
{
    uint64_t u;
    struct bdk_sso_aw_tag_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for tag read returns. This may be divided by SSO_AW_TAG_REQ_PC to
                                                                 determine the average read latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for tag read returns. This may be divided by SSO_AW_TAG_REQ_PC to
                                                                 determine the average read latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_aw_tag_latency_pc_s cn; */
};
typedef union bdk_sso_aw_tag_latency_pc bdk_sso_aw_tag_latency_pc_t;

#define BDK_SSO_AW_TAG_LATENCY_PC BDK_SSO_AW_TAG_LATENCY_PC_FUNC()
static inline uint64_t BDK_SSO_AW_TAG_LATENCY_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AW_TAG_LATENCY_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000020a8ll;
    __bdk_csr_fatal("SSO_AW_TAG_LATENCY_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AW_TAG_LATENCY_PC bdk_sso_aw_tag_latency_pc_t
#define bustype_BDK_SSO_AW_TAG_LATENCY_PC BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_AW_TAG_LATENCY_PC "SSO_AW_TAG_LATENCY_PC"
#define device_bar_BDK_SSO_AW_TAG_LATENCY_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_AW_TAG_LATENCY_PC 0
#define arguments_BDK_SSO_AW_TAG_LATENCY_PC -1,-1,-1,-1

/**
 * Register (NCB) sso_aw_tag_req_pc
 *
 * SSO PF Short Form Tag Latency Perf-Count Register
 */
union bdk_sso_aw_tag_req_pc
{
    uint64_t u;
    struct bdk_sso_aw_tag_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of tag read requests. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of tag read requests. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_aw_tag_req_pc_s cn; */
};
typedef union bdk_sso_aw_tag_req_pc bdk_sso_aw_tag_req_pc_t;

#define BDK_SSO_AW_TAG_REQ_PC BDK_SSO_AW_TAG_REQ_PC_FUNC()
static inline uint64_t BDK_SSO_AW_TAG_REQ_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AW_TAG_REQ_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000020a0ll;
    __bdk_csr_fatal("SSO_AW_TAG_REQ_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AW_TAG_REQ_PC bdk_sso_aw_tag_req_pc_t
#define bustype_BDK_SSO_AW_TAG_REQ_PC BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_AW_TAG_REQ_PC "SSO_AW_TAG_REQ_PC"
#define device_bar_BDK_SSO_AW_TAG_REQ_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_AW_TAG_REQ_PC 0
#define arguments_BDK_SSO_AW_TAG_REQ_PC -1,-1,-1,-1

/**
 * Register (NCB) sso_aw_we
 *
 * SSO PF Work-Entries Count Register
 */
union bdk_sso_aw_we
{
    uint64_t u;
    struct bdk_sso_aw_we_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t rsvd_free             : 13; /**< [ 28: 16](R/W/H) Number of free reserved entries. Used to ensure that each hardware-group can get
                                                                 a specific number of entries. Must always be greater than or equal to the sum
                                                                 across all SSO_GRP()_IAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to RSVD_THR are going to be made. To prevent races, software
                                                                 should not change this register when SSO is being used; instead use
                                                                 SSO_AW_ADD[RSVD_FREE]. */
        uint64_t reserved_13_15        : 3;
        uint64_t free_cnt              : 13; /**< [ 12:  0](RO/H) Number of total free entries. */
#else /* Word 0 - Little Endian */
        uint64_t free_cnt              : 13; /**< [ 12:  0](RO/H) Number of total free entries. */
        uint64_t reserved_13_15        : 3;
        uint64_t rsvd_free             : 13; /**< [ 28: 16](R/W/H) Number of free reserved entries. Used to ensure that each hardware-group can get
                                                                 a specific number of entries. Must always be greater than or equal to the sum
                                                                 across all SSO_GRP()_IAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to RSVD_THR are going to be made. To prevent races, software
                                                                 should not change this register when SSO is being used; instead use
                                                                 SSO_AW_ADD[RSVD_FREE]. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_aw_we_s cn; */
};
typedef union bdk_sso_aw_we bdk_sso_aw_we_t;

#define BDK_SSO_AW_WE BDK_SSO_AW_WE_FUNC()
static inline uint64_t BDK_SSO_AW_WE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_AW_WE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001080ll;
    __bdk_csr_fatal("SSO_AW_WE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_AW_WE bdk_sso_aw_we_t
#define bustype_BDK_SSO_AW_WE BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_AW_WE "SSO_AW_WE"
#define device_bar_BDK_SSO_AW_WE 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_AW_WE 0
#define arguments_BDK_SSO_AW_WE -1,-1,-1,-1

/**
 * Register (NCB) sso_bist_status0
 *
 * SSO PF BIST Status Register
 * Contains the BIST status for the SSO memories.
 */
union bdk_sso_bist_status0
{
    uint64_t u;
    struct bdk_sso_bist_status0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t bist                  : 12; /**< [ 11:  0](RO/H) Memory BIST status.
                                                                 0 = Pass.
                                                                 1 = Fail.

                                                                 Internal:
                                                                 \<11\> = XAQ_CNT.
                                                                 \<10\> = XAQ_LIMIT.
                                                                  \<9\> = WES.
                                                                  \<8\> = FFF.
                                                                  \<7\> = XAQ.
                                                                  \<6\> = QTC.
                                                                  \<5\> = INP.
                                                                  \<4\> = LLM.
                                                                  \<3\> = TIAQ_HPTR.
                                                                  \<2\> = TIAQ_TPTR.
                                                                  \<1\> = TOAQ_HPTR.
                                                                  \<0\> = TOAQ_TPTR. */
#else /* Word 0 - Little Endian */
        uint64_t bist                  : 12; /**< [ 11:  0](RO/H) Memory BIST status.
                                                                 0 = Pass.
                                                                 1 = Fail.

                                                                 Internal:
                                                                 \<11\> = XAQ_CNT.
                                                                 \<10\> = XAQ_LIMIT.
                                                                  \<9\> = WES.
                                                                  \<8\> = FFF.
                                                                  \<7\> = XAQ.
                                                                  \<6\> = QTC.
                                                                  \<5\> = INP.
                                                                  \<4\> = LLM.
                                                                  \<3\> = TIAQ_HPTR.
                                                                  \<2\> = TIAQ_TPTR.
                                                                  \<1\> = TOAQ_HPTR.
                                                                  \<0\> = TOAQ_TPTR. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_bist_status0_s cn; */
};
typedef union bdk_sso_bist_status0 bdk_sso_bist_status0_t;

#define BDK_SSO_BIST_STATUS0 BDK_SSO_BIST_STATUS0_FUNC()
static inline uint64_t BDK_SSO_BIST_STATUS0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_BIST_STATUS0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001200ll;
    __bdk_csr_fatal("SSO_BIST_STATUS0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_BIST_STATUS0 bdk_sso_bist_status0_t
#define bustype_BDK_SSO_BIST_STATUS0 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_BIST_STATUS0 "SSO_BIST_STATUS0"
#define device_bar_BDK_SSO_BIST_STATUS0 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_BIST_STATUS0 0
#define arguments_BDK_SSO_BIST_STATUS0 -1,-1,-1,-1

/**
 * Register (NCB) sso_bist_status1
 *
 * SSO PF BIST Status 1 Register
 * Contains the BIST status for the SSO memories.
 */
union bdk_sso_bist_status1
{
    uint64_t u;
    struct bdk_sso_bist_status1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t bist                  : 8;  /**< [  7:  0](RO/H) Memory BIST status.
                                                                 0 = Pass.
                                                                 1 = Fail.

                                                                 Internal:
                                                                 \<7\> = MBOX_MEM,
                                                                 \<6\> = THRINT.
                                                                 \<5\> = MASK.
                                                                 \<4\> = GDW.
                                                                 \<3\> = QIDX.
                                                                 \<2\> = TPTR.
                                                                 \<1\> = HPTR.
                                                                 \<0\> = CNTR. */
#else /* Word 0 - Little Endian */
        uint64_t bist                  : 8;  /**< [  7:  0](RO/H) Memory BIST status.
                                                                 0 = Pass.
                                                                 1 = Fail.

                                                                 Internal:
                                                                 \<7\> = MBOX_MEM,
                                                                 \<6\> = THRINT.
                                                                 \<5\> = MASK.
                                                                 \<4\> = GDW.
                                                                 \<3\> = QIDX.
                                                                 \<2\> = TPTR.
                                                                 \<1\> = HPTR.
                                                                 \<0\> = CNTR. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_bist_status1_s cn; */
};
typedef union bdk_sso_bist_status1 bdk_sso_bist_status1_t;

#define BDK_SSO_BIST_STATUS1 BDK_SSO_BIST_STATUS1_FUNC()
static inline uint64_t BDK_SSO_BIST_STATUS1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_BIST_STATUS1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001208ll;
    __bdk_csr_fatal("SSO_BIST_STATUS1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_BIST_STATUS1 bdk_sso_bist_status1_t
#define bustype_BDK_SSO_BIST_STATUS1 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_BIST_STATUS1 "SSO_BIST_STATUS1"
#define device_bar_BDK_SSO_BIST_STATUS1 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_BIST_STATUS1 0
#define arguments_BDK_SSO_BIST_STATUS1 -1,-1,-1,-1

/**
 * Register (NCB) sso_bist_status2
 *
 * SSO PF BIST Status 2 Register
 * Contains the BIST status for the SSO memories.
 */
union bdk_sso_bist_status2
{
    uint64_t u;
    struct bdk_sso_bist_status2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t bist                  : 12; /**< [ 11:  0](RO/H) Memory BIST status.
                                                                 0 = Pass.
                                                                 1 = Fail.

                                                                 Internal:
                                                                 \<11\> = VHGRP.
                                                                 \<10\> = HWSX_GMCTL.
                                                                 \<9\>  = PCC.
                                                                 \<8\>  = PC_WS.
                                                                 \<7\>  = PC_WA.
                                                                 \<6\>  = PC_TS.
                                                                 \<5\>  = PC_DS.
                                                                 \<4\>  = NCB0.
                                                                 \<3\>  = PND.
                                                                 \<2\>  = OTH.
                                                                 \<1\>  = NIDX.
                                                                 \<0\>  = PIDX. */
#else /* Word 0 - Little Endian */
        uint64_t bist                  : 12; /**< [ 11:  0](RO/H) Memory BIST status.
                                                                 0 = Pass.
                                                                 1 = Fail.

                                                                 Internal:
                                                                 \<11\> = VHGRP.
                                                                 \<10\> = HWSX_GMCTL.
                                                                 \<9\>  = PCC.
                                                                 \<8\>  = PC_WS.
                                                                 \<7\>  = PC_WA.
                                                                 \<6\>  = PC_TS.
                                                                 \<5\>  = PC_DS.
                                                                 \<4\>  = NCB0.
                                                                 \<3\>  = PND.
                                                                 \<2\>  = OTH.
                                                                 \<1\>  = NIDX.
                                                                 \<0\>  = PIDX. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_bist_status2_s cn; */
};
typedef union bdk_sso_bist_status2 bdk_sso_bist_status2_t;

#define BDK_SSO_BIST_STATUS2 BDK_SSO_BIST_STATUS2_FUNC()
static inline uint64_t BDK_SSO_BIST_STATUS2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_BIST_STATUS2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001210ll;
    __bdk_csr_fatal("SSO_BIST_STATUS2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_BIST_STATUS2 bdk_sso_bist_status2_t
#define bustype_BDK_SSO_BIST_STATUS2 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_BIST_STATUS2 "SSO_BIST_STATUS2"
#define device_bar_BDK_SSO_BIST_STATUS2 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_BIST_STATUS2 0
#define arguments_BDK_SSO_BIST_STATUS2 -1,-1,-1,-1

/**
 * Register (NCB) sso_bp_test0
 *
 * INTERNAL: SSO PF Backpressure Test Register 0
 */
union bdk_sso_bp_test0
{
    uint64_t u;
    struct bdk_sso_bp_test0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Limit the aw aq credit decrement returns */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Limit the aw aq credit decrement returns */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_bp_test0_s cn; */
};
typedef union bdk_sso_bp_test0 bdk_sso_bp_test0_t;

#define BDK_SSO_BP_TEST0 BDK_SSO_BP_TEST0_FUNC()
static inline uint64_t BDK_SSO_BP_TEST0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_BP_TEST0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001380ll;
    __bdk_csr_fatal("SSO_BP_TEST0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_BP_TEST0 bdk_sso_bp_test0_t
#define bustype_BDK_SSO_BP_TEST0 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_BP_TEST0 "SSO_BP_TEST0"
#define device_bar_BDK_SSO_BP_TEST0 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_BP_TEST0 0
#define arguments_BDK_SSO_BP_TEST0 -1,-1,-1,-1

/**
 * Register (NCB) sso_bp_test1
 *
 * INTERNAL: SSO PF Backpressure Test Register 1
 */
union bdk_sso_bp_test1
{
    uint64_t u;
    struct bdk_sso_bp_test1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Limit the gw_csr_rxfifo from asserting valid for the next request. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Limit the gw_csr_rxfifo from asserting valid for the next request. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_bp_test1_s cn; */
};
typedef union bdk_sso_bp_test1 bdk_sso_bp_test1_t;

#define BDK_SSO_BP_TEST1 BDK_SSO_BP_TEST1_FUNC()
static inline uint64_t BDK_SSO_BP_TEST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_BP_TEST1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001390ll;
    __bdk_csr_fatal("SSO_BP_TEST1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_BP_TEST1 bdk_sso_bp_test1_t
#define bustype_BDK_SSO_BP_TEST1 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_BP_TEST1 "SSO_BP_TEST1"
#define device_bar_BDK_SSO_BP_TEST1 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_BP_TEST1 0
#define arguments_BDK_SSO_BP_TEST1 -1,-1,-1,-1

/**
 * Register (NCB) sso_bp_test2
 *
 * INTERNAL: SSO PF Backpressure Test Register 2
 */
union bdk_sso_bp_test2
{
    uint64_t u;
    struct bdk_sso_bp_test2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Limit the ncbo FIFO from asserting valid for the next request. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Reserved.
                                                                 \<60\> = Limit the ncbo FIFO from asserting valid for the next request. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_bp_test2_s cn; */
};
typedef union bdk_sso_bp_test2 bdk_sso_bp_test2_t;

#define BDK_SSO_BP_TEST2 BDK_SSO_BP_TEST2_FUNC()
static inline uint64_t BDK_SSO_BP_TEST2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_BP_TEST2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000013a0ll;
    __bdk_csr_fatal("SSO_BP_TEST2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_BP_TEST2 bdk_sso_bp_test2_t
#define bustype_BDK_SSO_BP_TEST2 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_BP_TEST2 "SSO_BP_TEST2"
#define device_bar_BDK_SSO_BP_TEST2 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_BP_TEST2 0
#define arguments_BDK_SSO_BP_TEST2 -1,-1,-1,-1

/**
 * Register (NCB) sso_const
 *
 * SSO PF Constants Register
 * This register contains constants for software discovery.
 */
union bdk_sso_const
{
    uint64_t u;
    struct bdk_sso_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hws                   : 8;  /**< [ 63: 56](RO) Number of hardware work slots. */
        uint64_t taq_b                 : 8;  /**< [ 55: 48](RO) Number of TAQ entries per line.  Multiply [TAQ_A] times [TAQ_B] to find total entries. */
        uint64_t taq_a                 : 16; /**< [ 47: 32](RO) Number of TAQ lines.  Multiply [TAQ_A] times [TAQ_B] to find total entries. */
        uint64_t iue                   : 16; /**< [ 31: 16](RO) Number of in-unit entries. */
        uint64_t grp                   : 16; /**< [ 15:  0](RO) Number of hardware-groups. */
#else /* Word 0 - Little Endian */
        uint64_t grp                   : 16; /**< [ 15:  0](RO) Number of hardware-groups. */
        uint64_t iue                   : 16; /**< [ 31: 16](RO) Number of in-unit entries. */
        uint64_t taq_a                 : 16; /**< [ 47: 32](RO) Number of TAQ lines.  Multiply [TAQ_A] times [TAQ_B] to find total entries. */
        uint64_t taq_b                 : 8;  /**< [ 55: 48](RO) Number of TAQ entries per line.  Multiply [TAQ_A] times [TAQ_B] to find total entries. */
        uint64_t hws                   : 8;  /**< [ 63: 56](RO) Number of hardware work slots. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_const_s cn; */
};
typedef union bdk_sso_const bdk_sso_const_t;

#define BDK_SSO_CONST BDK_SSO_CONST_FUNC()
static inline uint64_t BDK_SSO_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_CONST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001000ll;
    __bdk_csr_fatal("SSO_CONST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_CONST bdk_sso_const_t
#define bustype_BDK_SSO_CONST BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_CONST "SSO_CONST"
#define device_bar_BDK_SSO_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_CONST 0
#define arguments_BDK_SSO_CONST -1,-1,-1,-1

/**
 * Register (NCB) sso_const1
 *
 * SSO PF Constants Register 1
 * This register contains constants for software discovery.
 */
union bdk_sso_const1
{
    uint64_t u;
    struct bdk_sso_const1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t maps                  : 12; /**< [ 43: 32](RO) Number of entries in SSO_PF_MAP(). */
        uint64_t xae_waes              : 16; /**< [ 31: 16](RO) Number of WAEs (work entries) in a XAQ buffer. */
        uint64_t xaq_buf_size          : 16; /**< [ 15:  0](RO) Number of bytes in a XAQ buffer. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_buf_size          : 16; /**< [ 15:  0](RO) Number of bytes in a XAQ buffer. */
        uint64_t xae_waes              : 16; /**< [ 31: 16](RO) Number of WAEs (work entries) in a XAQ buffer. */
        uint64_t maps                  : 12; /**< [ 43: 32](RO) Number of entries in SSO_PF_MAP(). */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_const1_s cn; */
};
typedef union bdk_sso_const1 bdk_sso_const1_t;

#define BDK_SSO_CONST1 BDK_SSO_CONST1_FUNC()
static inline uint64_t BDK_SSO_CONST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_CONST1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001008ll;
    __bdk_csr_fatal("SSO_CONST1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_CONST1 bdk_sso_const1_t
#define bustype_BDK_SSO_CONST1 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_CONST1 "SSO_CONST1"
#define device_bar_BDK_SSO_CONST1 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_CONST1 0
#define arguments_BDK_SSO_CONST1 -1,-1,-1,-1

/**
 * Register (NCB) sso_ecc_ctl0
 *
 * SSO PF ECC Control 0 Register
 */
union bdk_sso_ecc_ctl0
{
    uint64_t u;
    struct bdk_sso_ecc_ctl0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t xaq_cnt_flip          : 2;  /**< [ 35: 34](R/W) XAQ_CNT flip syndrome bits on write. */
        uint64_t xaq_cnt_cdis          : 1;  /**< [ 33: 33](R/W) XAQ_CNT ECC correction disable. */
        uint64_t xaq_limit_flip        : 2;  /**< [ 32: 31](R/W) XAQ_LIMIT flip syndrome bits on write. */
        uint64_t xaq_limit_cdis        : 1;  /**< [ 30: 30](R/W) XAQ_LIMIT ECC correction disable. */
        uint64_t toaqt_flip            : 2;  /**< [ 29: 28](R/W) TOAQT flip syndrome bits on write. */
        uint64_t toaqt_cdis            : 1;  /**< [ 27: 27](R/W) TOAQT ECC correction disable. */
        uint64_t toaqh_flip            : 2;  /**< [ 26: 25](R/W) TOAQH flip syndrome bits on write. */
        uint64_t toaqh_cdis            : 1;  /**< [ 24: 24](R/W) TOAQH ECC correction disable. */
        uint64_t tiaqt_flip            : 2;  /**< [ 23: 22](R/W) TIAQT flip syndrome bits on write. */
        uint64_t tiaqt_cdis            : 1;  /**< [ 21: 21](R/W) TIAQT ECC correction disable. */
        uint64_t tiaqh_flip            : 2;  /**< [ 20: 19](R/W) TIAQH flip syndrome bits on write. */
        uint64_t tiaqh_cdis            : 1;  /**< [ 18: 18](R/W) TIAQH ECC correction disable. */
        uint64_t llm_flip              : 2;  /**< [ 17: 16](R/W) LLM flip syndrome bits on write. */
        uint64_t llm_cdis              : 1;  /**< [ 15: 15](R/W) LLM ECC correction disable. */
        uint64_t inp_flip              : 2;  /**< [ 14: 13](R/W) INP flip syndrome bits on write. */
        uint64_t inp_cdis              : 1;  /**< [ 12: 12](R/W) INP ECC correction disable. */
        uint64_t qtc_flip              : 2;  /**< [ 11: 10](R/W) QTC flip syndrome bits on write. */
        uint64_t qtc_cdis              : 1;  /**< [  9:  9](R/W) QTC ECC correction disable. */
        uint64_t xaq_flip              : 2;  /**< [  8:  7](R/W) XAQ flip syndrome bits on write. */
        uint64_t xaq_cdis              : 1;  /**< [  6:  6](R/W) XAQ ECC correction disable. */
        uint64_t fff_flip              : 2;  /**< [  5:  4](R/W) FFF flip syndrome bits on write. */
        uint64_t fff_cdis              : 1;  /**< [  3:  3](R/W) FFF ECC correction disable. */
        uint64_t wes_flip              : 2;  /**< [  2:  1](R/W) WES flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the ram to test
                                                                 single-bit or double-bit error handling. */
        uint64_t wes_cdis              : 1;  /**< [  0:  0](R/W) WES ECC correction disable. */
#else /* Word 0 - Little Endian */
        uint64_t wes_cdis              : 1;  /**< [  0:  0](R/W) WES ECC correction disable. */
        uint64_t wes_flip              : 2;  /**< [  2:  1](R/W) WES flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the ram to test
                                                                 single-bit or double-bit error handling. */
        uint64_t fff_cdis              : 1;  /**< [  3:  3](R/W) FFF ECC correction disable. */
        uint64_t fff_flip              : 2;  /**< [  5:  4](R/W) FFF flip syndrome bits on write. */
        uint64_t xaq_cdis              : 1;  /**< [  6:  6](R/W) XAQ ECC correction disable. */
        uint64_t xaq_flip              : 2;  /**< [  8:  7](R/W) XAQ flip syndrome bits on write. */
        uint64_t qtc_cdis              : 1;  /**< [  9:  9](R/W) QTC ECC correction disable. */
        uint64_t qtc_flip              : 2;  /**< [ 11: 10](R/W) QTC flip syndrome bits on write. */
        uint64_t inp_cdis              : 1;  /**< [ 12: 12](R/W) INP ECC correction disable. */
        uint64_t inp_flip              : 2;  /**< [ 14: 13](R/W) INP flip syndrome bits on write. */
        uint64_t llm_cdis              : 1;  /**< [ 15: 15](R/W) LLM ECC correction disable. */
        uint64_t llm_flip              : 2;  /**< [ 17: 16](R/W) LLM flip syndrome bits on write. */
        uint64_t tiaqh_cdis            : 1;  /**< [ 18: 18](R/W) TIAQH ECC correction disable. */
        uint64_t tiaqh_flip            : 2;  /**< [ 20: 19](R/W) TIAQH flip syndrome bits on write. */
        uint64_t tiaqt_cdis            : 1;  /**< [ 21: 21](R/W) TIAQT ECC correction disable. */
        uint64_t tiaqt_flip            : 2;  /**< [ 23: 22](R/W) TIAQT flip syndrome bits on write. */
        uint64_t toaqh_cdis            : 1;  /**< [ 24: 24](R/W) TOAQH ECC correction disable. */
        uint64_t toaqh_flip            : 2;  /**< [ 26: 25](R/W) TOAQH flip syndrome bits on write. */
        uint64_t toaqt_cdis            : 1;  /**< [ 27: 27](R/W) TOAQT ECC correction disable. */
        uint64_t toaqt_flip            : 2;  /**< [ 29: 28](R/W) TOAQT flip syndrome bits on write. */
        uint64_t xaq_limit_cdis        : 1;  /**< [ 30: 30](R/W) XAQ_LIMIT ECC correction disable. */
        uint64_t xaq_limit_flip        : 2;  /**< [ 32: 31](R/W) XAQ_LIMIT flip syndrome bits on write. */
        uint64_t xaq_cnt_cdis          : 1;  /**< [ 33: 33](R/W) XAQ_CNT ECC correction disable. */
        uint64_t xaq_cnt_flip          : 2;  /**< [ 35: 34](R/W) XAQ_CNT flip syndrome bits on write. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ecc_ctl0_s cn; */
};
typedef union bdk_sso_ecc_ctl0 bdk_sso_ecc_ctl0_t;

#define BDK_SSO_ECC_CTL0 BDK_SSO_ECC_CTL0_FUNC()
static inline uint64_t BDK_SSO_ECC_CTL0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ECC_CTL0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001280ll;
    __bdk_csr_fatal("SSO_ECC_CTL0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ECC_CTL0 bdk_sso_ecc_ctl0_t
#define bustype_BDK_SSO_ECC_CTL0 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ECC_CTL0 "SSO_ECC_CTL0"
#define device_bar_BDK_SSO_ECC_CTL0 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ECC_CTL0 0
#define arguments_BDK_SSO_ECC_CTL0 -1,-1,-1,-1

/**
 * Register (NCB) sso_ecc_ctl1
 *
 * SSO PF ECC Control 1 Register
 */
union bdk_sso_ecc_ctl1
{
    uint64_t u;
    struct bdk_sso_ecc_ctl1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t mbox_mem_flip         : 2;  /**< [ 23: 22](R/W) MBOX_MEM flip syndrome bits on write. */
        uint64_t mbox_mem_cdis         : 1;  /**< [ 21: 21](R/W) MBOX_MEM ECC correction disable. */
        uint64_t thrint_flip           : 2;  /**< [ 20: 19](R/W) THRINT flip syndrome bits on write. */
        uint64_t thrint_cdis           : 1;  /**< [ 18: 18](R/W) THRINT ECC correction disable. */
        uint64_t mask_flip             : 2;  /**< [ 17: 16](R/W) MASK flip syndrome bits on write. */
        uint64_t mask_cdis             : 1;  /**< [ 15: 15](R/W) MASK ECC correction disable. */
        uint64_t gdw_flip              : 2;  /**< [ 14: 13](R/W) GDW flip syndrome bits on write. */
        uint64_t gdw_cdis              : 1;  /**< [ 12: 12](R/W) GDW ECC correction disable. */
        uint64_t qidx_flip             : 2;  /**< [ 11: 10](R/W) QIDX flip syndrome bits on write. */
        uint64_t qidx_cdis             : 1;  /**< [  9:  9](R/W) QIDX ECC correction disable. */
        uint64_t tptr_flip             : 2;  /**< [  8:  7](R/W) TPTR flip syndrome bits on write. */
        uint64_t tptr_cdis             : 1;  /**< [  6:  6](R/W) TPTR ECC correction disable. */
        uint64_t hptr_flip             : 2;  /**< [  5:  4](R/W) HPTR flip syndrome bits on write. */
        uint64_t hptr_cdis             : 1;  /**< [  3:  3](R/W) HPTR ECC correction disable. */
        uint64_t cntr_flip             : 2;  /**< [  2:  1](R/W) CNTR flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the ram to test
                                                                 single-bit or double-bit error handling. */
        uint64_t cntr_cdis             : 1;  /**< [  0:  0](R/W) CNTR ECC correction disable. */
#else /* Word 0 - Little Endian */
        uint64_t cntr_cdis             : 1;  /**< [  0:  0](R/W) CNTR ECC correction disable. */
        uint64_t cntr_flip             : 2;  /**< [  2:  1](R/W) CNTR flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the ram to test
                                                                 single-bit or double-bit error handling. */
        uint64_t hptr_cdis             : 1;  /**< [  3:  3](R/W) HPTR ECC correction disable. */
        uint64_t hptr_flip             : 2;  /**< [  5:  4](R/W) HPTR flip syndrome bits on write. */
        uint64_t tptr_cdis             : 1;  /**< [  6:  6](R/W) TPTR ECC correction disable. */
        uint64_t tptr_flip             : 2;  /**< [  8:  7](R/W) TPTR flip syndrome bits on write. */
        uint64_t qidx_cdis             : 1;  /**< [  9:  9](R/W) QIDX ECC correction disable. */
        uint64_t qidx_flip             : 2;  /**< [ 11: 10](R/W) QIDX flip syndrome bits on write. */
        uint64_t gdw_cdis              : 1;  /**< [ 12: 12](R/W) GDW ECC correction disable. */
        uint64_t gdw_flip              : 2;  /**< [ 14: 13](R/W) GDW flip syndrome bits on write. */
        uint64_t mask_cdis             : 1;  /**< [ 15: 15](R/W) MASK ECC correction disable. */
        uint64_t mask_flip             : 2;  /**< [ 17: 16](R/W) MASK flip syndrome bits on write. */
        uint64_t thrint_cdis           : 1;  /**< [ 18: 18](R/W) THRINT ECC correction disable. */
        uint64_t thrint_flip           : 2;  /**< [ 20: 19](R/W) THRINT flip syndrome bits on write. */
        uint64_t mbox_mem_cdis         : 1;  /**< [ 21: 21](R/W) MBOX_MEM ECC correction disable. */
        uint64_t mbox_mem_flip         : 2;  /**< [ 23: 22](R/W) MBOX_MEM flip syndrome bits on write. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ecc_ctl1_s cn; */
};
typedef union bdk_sso_ecc_ctl1 bdk_sso_ecc_ctl1_t;

#define BDK_SSO_ECC_CTL1 BDK_SSO_ECC_CTL1_FUNC()
static inline uint64_t BDK_SSO_ECC_CTL1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ECC_CTL1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001288ll;
    __bdk_csr_fatal("SSO_ECC_CTL1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ECC_CTL1 bdk_sso_ecc_ctl1_t
#define bustype_BDK_SSO_ECC_CTL1 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ECC_CTL1 "SSO_ECC_CTL1"
#define device_bar_BDK_SSO_ECC_CTL1 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ECC_CTL1 0
#define arguments_BDK_SSO_ECC_CTL1 -1,-1,-1,-1

/**
 * Register (NCB) sso_ecc_ctl2
 *
 * SSO PF ECC Control 2 Register
 */
union bdk_sso_ecc_ctl2
{
    uint64_t u;
    struct bdk_sso_ecc_ctl2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t pcc_flip              : 2;  /**< [ 23: 22](R/W) PCC flip syndrome bits on write. */
        uint64_t pcc_cdis              : 1;  /**< [ 21: 21](R/W) PCC ECC correction disable. */
        uint64_t vhgrp_flip            : 2;  /**< [ 20: 19](R/W) VHGRP flip syndrome bits on write. */
        uint64_t vhgrp_cdis            : 1;  /**< [ 18: 18](R/W) VHGRP ECC correction disable. */
        uint64_t hwsx_gmctl_flip       : 2;  /**< [ 17: 16](R/W) HWSX_GMCTL flip syndrome bits on write. */
        uint64_t hwsx_gmctl_cdis       : 1;  /**< [ 15: 15](R/W) HWSX_GMCTL ECC correction disable. */
        uint64_t ncbo_flip             : 2;  /**< [ 14: 13](R/W) NCBO flip syndrome bits on write. */
        uint64_t ncbo_cdis             : 1;  /**< [ 12: 12](R/W) NCBO ECC correction disable. */
        uint64_t pnd_flip              : 2;  /**< [ 11: 10](R/W) PND flip syndrome bits on write. */
        uint64_t pnd_cdis              : 1;  /**< [  9:  9](R/W) PND ECC correction disable. */
        uint64_t oth_flip              : 2;  /**< [  8:  7](R/W) OTH flip syndrome bits on write. */
        uint64_t oth_cdis              : 1;  /**< [  6:  6](R/W) OTH ECC correction disable. */
        uint64_t nidx_flip             : 2;  /**< [  5:  4](R/W) NIDX flip syndrome bits on write. */
        uint64_t nidx_cdis             : 1;  /**< [  3:  3](R/W) NIDX ECC correction disable. */
        uint64_t pidx_flip             : 2;  /**< [  2:  1](R/W) PIDX flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the ram to test
                                                                 single-bit or double-bit error handling. */
        uint64_t pidx_cdis             : 1;  /**< [  0:  0](R/W) PIDX ECC correction disable. */
#else /* Word 0 - Little Endian */
        uint64_t pidx_cdis             : 1;  /**< [  0:  0](R/W) PIDX ECC correction disable. */
        uint64_t pidx_flip             : 2;  /**< [  2:  1](R/W) PIDX flip syndrome bits on write. Flip syndrome bits \<1:0\> on writes to the ram to test
                                                                 single-bit or double-bit error handling. */
        uint64_t nidx_cdis             : 1;  /**< [  3:  3](R/W) NIDX ECC correction disable. */
        uint64_t nidx_flip             : 2;  /**< [  5:  4](R/W) NIDX flip syndrome bits on write. */
        uint64_t oth_cdis              : 1;  /**< [  6:  6](R/W) OTH ECC correction disable. */
        uint64_t oth_flip              : 2;  /**< [  8:  7](R/W) OTH flip syndrome bits on write. */
        uint64_t pnd_cdis              : 1;  /**< [  9:  9](R/W) PND ECC correction disable. */
        uint64_t pnd_flip              : 2;  /**< [ 11: 10](R/W) PND flip syndrome bits on write. */
        uint64_t ncbo_cdis             : 1;  /**< [ 12: 12](R/W) NCBO ECC correction disable. */
        uint64_t ncbo_flip             : 2;  /**< [ 14: 13](R/W) NCBO flip syndrome bits on write. */
        uint64_t hwsx_gmctl_cdis       : 1;  /**< [ 15: 15](R/W) HWSX_GMCTL ECC correction disable. */
        uint64_t hwsx_gmctl_flip       : 2;  /**< [ 17: 16](R/W) HWSX_GMCTL flip syndrome bits on write. */
        uint64_t vhgrp_cdis            : 1;  /**< [ 18: 18](R/W) VHGRP ECC correction disable. */
        uint64_t vhgrp_flip            : 2;  /**< [ 20: 19](R/W) VHGRP flip syndrome bits on write. */
        uint64_t pcc_cdis              : 1;  /**< [ 21: 21](R/W) PCC ECC correction disable. */
        uint64_t pcc_flip              : 2;  /**< [ 23: 22](R/W) PCC flip syndrome bits on write. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ecc_ctl2_s cn; */
};
typedef union bdk_sso_ecc_ctl2 bdk_sso_ecc_ctl2_t;

#define BDK_SSO_ECC_CTL2 BDK_SSO_ECC_CTL2_FUNC()
static inline uint64_t BDK_SSO_ECC_CTL2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ECC_CTL2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001290ll;
    __bdk_csr_fatal("SSO_ECC_CTL2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ECC_CTL2 bdk_sso_ecc_ctl2_t
#define bustype_BDK_SSO_ECC_CTL2 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ECC_CTL2 "SSO_ECC_CTL2"
#define device_bar_BDK_SSO_ECC_CTL2 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ECC_CTL2 0
#define arguments_BDK_SSO_ECC_CTL2 -1,-1,-1,-1

/**
 * Register (NCB) sso_err0
 *
 * SSO PF Error 0 Register
 * This register contains ECC and other miscellaneous error bits.
 */
union bdk_sso_err0
{
    uint64_t u;
    struct bdk_sso_err0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t xaq_cnt_dbe           : 1;  /**< [ 55: 55](R/W1C/H) Double-bit error for XAQ_CNT RAM. */
        uint64_t xaq_cnt_sbe           : 1;  /**< [ 54: 54](R/W1C/H) Single-bit error for XAQ_CNT RAM. */
        uint64_t xaq_limit_dbe         : 1;  /**< [ 53: 53](R/W1C/H) Double-bit error for XAQ_LIMIT RAM. */
        uint64_t xaq_limit_sbe         : 1;  /**< [ 52: 52](R/W1C/H) Single-bit error for XAQ_LIMIT RAM. */
        uint64_t toaqt_dbe             : 1;  /**< [ 51: 51](R/W1C/H) Double-bit error for TOAQT RAM. */
        uint64_t toaqt_sbe             : 1;  /**< [ 50: 50](R/W1C/H) Single-bit error for TOAQT RAM. */
        uint64_t toaqh_dbe             : 1;  /**< [ 49: 49](R/W1C/H) Double-bit error for TOAQH RAM. */
        uint64_t toaqh_sbe             : 1;  /**< [ 48: 48](R/W1C/H) Single-bit error for TOAQH RAM. */
        uint64_t tiaqt_dbe             : 1;  /**< [ 47: 47](R/W1C/H) Double-bit error for TIAQT RAM. */
        uint64_t tiaqt_sbe             : 1;  /**< [ 46: 46](R/W1C/H) Single-bit error for TIAQT RAM. */
        uint64_t tiaqh_dbe             : 1;  /**< [ 45: 45](R/W1C/H) Double-bit error for TIAQH RAM. */
        uint64_t tiaqh_sbe             : 1;  /**< [ 44: 44](R/W1C/H) Single-bit error for TIAQH RAM. */
        uint64_t llm_dbe               : 1;  /**< [ 43: 43](R/W1C/H) Double-bit error for LLM RAM. */
        uint64_t llm_sbe               : 1;  /**< [ 42: 42](R/W1C/H) Single-bit error for LLM RAM. */
        uint64_t inp_dbe               : 1;  /**< [ 41: 41](R/W1C/H) Double-bit error for INP RAM. */
        uint64_t inp_sbe               : 1;  /**< [ 40: 40](R/W1C/H) Single-bit error for INP RAM. */
        uint64_t qtc_dbe               : 1;  /**< [ 39: 39](R/W1C/H) Double-bit error for QTC RAM. */
        uint64_t qtc_sbe               : 1;  /**< [ 38: 38](R/W1C/H) Single-bit error for QTC RAM. */
        uint64_t xaq_dbe               : 1;  /**< [ 37: 37](R/W1C/H) Double-bit error for XAQ RAM. */
        uint64_t xaq_sbe               : 1;  /**< [ 36: 36](R/W1C/H) Single-bit error for XAQ RAM. */
        uint64_t fff_dbe               : 1;  /**< [ 35: 35](R/W1C/H) Double-bit error for  RAM. */
        uint64_t fff_sbe               : 1;  /**< [ 34: 34](R/W1C/H) Single-bit error for  RAM. */
        uint64_t wes_dbe               : 1;  /**< [ 33: 33](R/W1C/H) Double-bit error for WES RAM. */
        uint64_t wes_sbe               : 1;  /**< [ 32: 32](R/W1C/H) Single-bit error for WES RAM. */
        uint64_t reserved_12_31        : 20;
        uint64_t gmid_multi            : 1;  /**< [ 11: 11](R/W1C/H) GMID map had double-hit error. Set when either:

                                                                   * Coprocessor add-work is dropped due to SSO_PF_MAP() having a double
                                                                 hit. When a request thus dropped, even if this bit is already set,
                                                                 SSO_UNMAP_INFO is loaded. */
        uint64_t gmid_unmap            : 1;  /**< [ 10: 10](R/W1C/H) GMID mapping not found error. Set when either:

                                                                   * Coprocessor add-work dropped due to that coprocessor requesting with GMID
                                                                 not mapped in SSO_PF_MAP(). When a request thus dropped, even if this bit is
                                                                 already set, SSO_UNMAP_INFO is loaded. */
        uint64_t gmid0                 : 1;  /**< [  9:  9](R/W1C/H) GMID zero access error. Set when either:

                                                                   * Coprocessor add-work dropped due to that coprocessor requesting with
                                                                 GMID=0x0. See PKI_QPG_TBLB()[GMID], TIM_RING()_GMCTL[GMID], and other GMID
                                                                 registers. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1C/H) Add work dropped due to QTL being disabled, 0x0. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1C/H) Add work dropped due to WQP being 0x0. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1C/H) Add work dropped due to wrong command/DID requested. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1C/H) Set when (a) received add work with tag type is specified as EMPTY, or (b) when
                                                                 SSO_AW_INP_CTL[WA_DIS] is set and work is added from disabled coprocessor. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1C/H) Add work to disabled hardware-group. An ADDWQ was received and dropped to a
                                                                 hardware-group with SSO_GRP()_IAQ_THR[RSVD_THR] = 0. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1C/H) Bad-fill-packet NCB error. NCB detected error on fill data. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1C/H) Bad-fill-packet error. The WAE VLD_CRC field was incorrect, or the XAQ next address was
                                                                 zero. */
        uint64_t npf                   : 1;  /**< [  1:  1](R/W1C/H) No-pointer-fault error. Treat identically to [FPE]. */
        uint64_t fpe                   : 1;  /**< [  0:  0](R/W1C/H) Free-page error. The FPA returned indication of illegal combinatation of
                                                                 GMID/GAURA for a pointer request, or there are no remaining free pages. SSO has
                                                                 dropped some add-work as a result, and this should be considered fatal to
                                                                 SSO. This may indicate software did not allocate sufficient FPA buffers to cover
                                                                 all possible outstanding work. */
#else /* Word 0 - Little Endian */
        uint64_t fpe                   : 1;  /**< [  0:  0](R/W1C/H) Free-page error. The FPA returned indication of illegal combinatation of
                                                                 GMID/GAURA for a pointer request, or there are no remaining free pages. SSO has
                                                                 dropped some add-work as a result, and this should be considered fatal to
                                                                 SSO. This may indicate software did not allocate sufficient FPA buffers to cover
                                                                 all possible outstanding work. */
        uint64_t npf                   : 1;  /**< [  1:  1](R/W1C/H) No-pointer-fault error. Treat identically to [FPE]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1C/H) Bad-fill-packet error. The WAE VLD_CRC field was incorrect, or the XAQ next address was
                                                                 zero. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1C/H) Bad-fill-packet NCB error. NCB detected error on fill data. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1C/H) Add work to disabled hardware-group. An ADDWQ was received and dropped to a
                                                                 hardware-group with SSO_GRP()_IAQ_THR[RSVD_THR] = 0. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1C/H) Set when (a) received add work with tag type is specified as EMPTY, or (b) when
                                                                 SSO_AW_INP_CTL[WA_DIS] is set and work is added from disabled coprocessor. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1C/H) Add work dropped due to wrong command/DID requested. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1C/H) Add work dropped due to WQP being 0x0. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1C/H) Add work dropped due to QTL being disabled, 0x0. */
        uint64_t gmid0                 : 1;  /**< [  9:  9](R/W1C/H) GMID zero access error. Set when either:

                                                                   * Coprocessor add-work dropped due to that coprocessor requesting with
                                                                 GMID=0x0. See PKI_QPG_TBLB()[GMID], TIM_RING()_GMCTL[GMID], and other GMID
                                                                 registers. */
        uint64_t gmid_unmap            : 1;  /**< [ 10: 10](R/W1C/H) GMID mapping not found error. Set when either:

                                                                   * Coprocessor add-work dropped due to that coprocessor requesting with GMID
                                                                 not mapped in SSO_PF_MAP(). When a request thus dropped, even if this bit is
                                                                 already set, SSO_UNMAP_INFO is loaded. */
        uint64_t gmid_multi            : 1;  /**< [ 11: 11](R/W1C/H) GMID map had double-hit error. Set when either:

                                                                   * Coprocessor add-work is dropped due to SSO_PF_MAP() having a double
                                                                 hit. When a request thus dropped, even if this bit is already set,
                                                                 SSO_UNMAP_INFO is loaded. */
        uint64_t reserved_12_31        : 20;
        uint64_t wes_sbe               : 1;  /**< [ 32: 32](R/W1C/H) Single-bit error for WES RAM. */
        uint64_t wes_dbe               : 1;  /**< [ 33: 33](R/W1C/H) Double-bit error for WES RAM. */
        uint64_t fff_sbe               : 1;  /**< [ 34: 34](R/W1C/H) Single-bit error for  RAM. */
        uint64_t fff_dbe               : 1;  /**< [ 35: 35](R/W1C/H) Double-bit error for  RAM. */
        uint64_t xaq_sbe               : 1;  /**< [ 36: 36](R/W1C/H) Single-bit error for XAQ RAM. */
        uint64_t xaq_dbe               : 1;  /**< [ 37: 37](R/W1C/H) Double-bit error for XAQ RAM. */
        uint64_t qtc_sbe               : 1;  /**< [ 38: 38](R/W1C/H) Single-bit error for QTC RAM. */
        uint64_t qtc_dbe               : 1;  /**< [ 39: 39](R/W1C/H) Double-bit error for QTC RAM. */
        uint64_t inp_sbe               : 1;  /**< [ 40: 40](R/W1C/H) Single-bit error for INP RAM. */
        uint64_t inp_dbe               : 1;  /**< [ 41: 41](R/W1C/H) Double-bit error for INP RAM. */
        uint64_t llm_sbe               : 1;  /**< [ 42: 42](R/W1C/H) Single-bit error for LLM RAM. */
        uint64_t llm_dbe               : 1;  /**< [ 43: 43](R/W1C/H) Double-bit error for LLM RAM. */
        uint64_t tiaqh_sbe             : 1;  /**< [ 44: 44](R/W1C/H) Single-bit error for TIAQH RAM. */
        uint64_t tiaqh_dbe             : 1;  /**< [ 45: 45](R/W1C/H) Double-bit error for TIAQH RAM. */
        uint64_t tiaqt_sbe             : 1;  /**< [ 46: 46](R/W1C/H) Single-bit error for TIAQT RAM. */
        uint64_t tiaqt_dbe             : 1;  /**< [ 47: 47](R/W1C/H) Double-bit error for TIAQT RAM. */
        uint64_t toaqh_sbe             : 1;  /**< [ 48: 48](R/W1C/H) Single-bit error for TOAQH RAM. */
        uint64_t toaqh_dbe             : 1;  /**< [ 49: 49](R/W1C/H) Double-bit error for TOAQH RAM. */
        uint64_t toaqt_sbe             : 1;  /**< [ 50: 50](R/W1C/H) Single-bit error for TOAQT RAM. */
        uint64_t toaqt_dbe             : 1;  /**< [ 51: 51](R/W1C/H) Double-bit error for TOAQT RAM. */
        uint64_t xaq_limit_sbe         : 1;  /**< [ 52: 52](R/W1C/H) Single-bit error for XAQ_LIMIT RAM. */
        uint64_t xaq_limit_dbe         : 1;  /**< [ 53: 53](R/W1C/H) Double-bit error for XAQ_LIMIT RAM. */
        uint64_t xaq_cnt_sbe           : 1;  /**< [ 54: 54](R/W1C/H) Single-bit error for XAQ_CNT RAM. */
        uint64_t xaq_cnt_dbe           : 1;  /**< [ 55: 55](R/W1C/H) Double-bit error for XAQ_CNT RAM. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err0_s cn; */
};
typedef union bdk_sso_err0 bdk_sso_err0_t;

#define BDK_SSO_ERR0 BDK_SSO_ERR0_FUNC()
static inline uint64_t BDK_SSO_ERR0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001220ll;
    __bdk_csr_fatal("SSO_ERR0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR0 bdk_sso_err0_t
#define bustype_BDK_SSO_ERR0 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR0 "SSO_ERR0"
#define device_bar_BDK_SSO_ERR0 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR0 0
#define arguments_BDK_SSO_ERR0 -1,-1,-1,-1

/**
 * Register (NCB) sso_err0_ena_w1c
 *
 * SSO PF Error 0 Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_sso_err0_ena_w1c
{
    uint64_t u;
    struct bdk_sso_err0_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t xaq_cnt_dbe           : 1;  /**< [ 55: 55](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_CNT_DBE]. */
        uint64_t xaq_cnt_sbe           : 1;  /**< [ 54: 54](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_CNT_SBE]. */
        uint64_t xaq_limit_dbe         : 1;  /**< [ 53: 53](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_LIMIT_DBE]. */
        uint64_t xaq_limit_sbe         : 1;  /**< [ 52: 52](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_LIMIT_SBE]. */
        uint64_t toaqt_dbe             : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for SSO_ERR0[TOAQT_DBE]. */
        uint64_t toaqt_sbe             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for SSO_ERR0[TOAQT_SBE]. */
        uint64_t toaqh_dbe             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for SSO_ERR0[TOAQH_DBE]. */
        uint64_t toaqh_sbe             : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for SSO_ERR0[TOAQH_SBE]. */
        uint64_t tiaqt_dbe             : 1;  /**< [ 47: 47](R/W1C/H) Reads or clears enable for SSO_ERR0[TIAQT_DBE]. */
        uint64_t tiaqt_sbe             : 1;  /**< [ 46: 46](R/W1C/H) Reads or clears enable for SSO_ERR0[TIAQT_SBE]. */
        uint64_t tiaqh_dbe             : 1;  /**< [ 45: 45](R/W1C/H) Reads or clears enable for SSO_ERR0[TIAQH_DBE]. */
        uint64_t tiaqh_sbe             : 1;  /**< [ 44: 44](R/W1C/H) Reads or clears enable for SSO_ERR0[TIAQH_SBE]. */
        uint64_t llm_dbe               : 1;  /**< [ 43: 43](R/W1C/H) Reads or clears enable for SSO_ERR0[LLM_DBE]. */
        uint64_t llm_sbe               : 1;  /**< [ 42: 42](R/W1C/H) Reads or clears enable for SSO_ERR0[LLM_SBE]. */
        uint64_t inp_dbe               : 1;  /**< [ 41: 41](R/W1C/H) Reads or clears enable for SSO_ERR0[INP_DBE]. */
        uint64_t inp_sbe               : 1;  /**< [ 40: 40](R/W1C/H) Reads or clears enable for SSO_ERR0[INP_SBE]. */
        uint64_t qtc_dbe               : 1;  /**< [ 39: 39](R/W1C/H) Reads or clears enable for SSO_ERR0[QTC_DBE]. */
        uint64_t qtc_sbe               : 1;  /**< [ 38: 38](R/W1C/H) Reads or clears enable for SSO_ERR0[QTC_SBE]. */
        uint64_t xaq_dbe               : 1;  /**< [ 37: 37](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_DBE]. */
        uint64_t xaq_sbe               : 1;  /**< [ 36: 36](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_SBE]. */
        uint64_t fff_dbe               : 1;  /**< [ 35: 35](R/W1C/H) Reads or clears enable for SSO_ERR0[FFF_DBE]. */
        uint64_t fff_sbe               : 1;  /**< [ 34: 34](R/W1C/H) Reads or clears enable for SSO_ERR0[FFF_SBE]. */
        uint64_t wes_dbe               : 1;  /**< [ 33: 33](R/W1C/H) Reads or clears enable for SSO_ERR0[WES_DBE]. */
        uint64_t wes_sbe               : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for SSO_ERR0[WES_SBE]. */
        uint64_t reserved_12_31        : 20;
        uint64_t gmid_multi            : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for SSO_ERR0[GMID_MULTI]. */
        uint64_t gmid_unmap            : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSO_ERR0[GMID_UNMAP]. */
        uint64_t gmid0                 : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSO_ERR0[GMID0]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSO_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSO_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSO_ERR0[ADDWQ_DROPPED]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSO_ERR0[AWEMPTY]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSO_ERR0[GRPDIS]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSO_ERR0[BFPN]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSO_ERR0[BFP]. */
        uint64_t npf                   : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSO_ERR0[NPF]. */
        uint64_t fpe                   : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSO_ERR0[FPE]. */
#else /* Word 0 - Little Endian */
        uint64_t fpe                   : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSO_ERR0[FPE]. */
        uint64_t npf                   : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSO_ERR0[NPF]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSO_ERR0[BFP]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSO_ERR0[BFPN]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSO_ERR0[GRPDIS]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSO_ERR0[AWEMPTY]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSO_ERR0[ADDWQ_DROPPED]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSO_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSO_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t gmid0                 : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSO_ERR0[GMID0]. */
        uint64_t gmid_unmap            : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSO_ERR0[GMID_UNMAP]. */
        uint64_t gmid_multi            : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for SSO_ERR0[GMID_MULTI]. */
        uint64_t reserved_12_31        : 20;
        uint64_t wes_sbe               : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for SSO_ERR0[WES_SBE]. */
        uint64_t wes_dbe               : 1;  /**< [ 33: 33](R/W1C/H) Reads or clears enable for SSO_ERR0[WES_DBE]. */
        uint64_t fff_sbe               : 1;  /**< [ 34: 34](R/W1C/H) Reads or clears enable for SSO_ERR0[FFF_SBE]. */
        uint64_t fff_dbe               : 1;  /**< [ 35: 35](R/W1C/H) Reads or clears enable for SSO_ERR0[FFF_DBE]. */
        uint64_t xaq_sbe               : 1;  /**< [ 36: 36](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_SBE]. */
        uint64_t xaq_dbe               : 1;  /**< [ 37: 37](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_DBE]. */
        uint64_t qtc_sbe               : 1;  /**< [ 38: 38](R/W1C/H) Reads or clears enable for SSO_ERR0[QTC_SBE]. */
        uint64_t qtc_dbe               : 1;  /**< [ 39: 39](R/W1C/H) Reads or clears enable for SSO_ERR0[QTC_DBE]. */
        uint64_t inp_sbe               : 1;  /**< [ 40: 40](R/W1C/H) Reads or clears enable for SSO_ERR0[INP_SBE]. */
        uint64_t inp_dbe               : 1;  /**< [ 41: 41](R/W1C/H) Reads or clears enable for SSO_ERR0[INP_DBE]. */
        uint64_t llm_sbe               : 1;  /**< [ 42: 42](R/W1C/H) Reads or clears enable for SSO_ERR0[LLM_SBE]. */
        uint64_t llm_dbe               : 1;  /**< [ 43: 43](R/W1C/H) Reads or clears enable for SSO_ERR0[LLM_DBE]. */
        uint64_t tiaqh_sbe             : 1;  /**< [ 44: 44](R/W1C/H) Reads or clears enable for SSO_ERR0[TIAQH_SBE]. */
        uint64_t tiaqh_dbe             : 1;  /**< [ 45: 45](R/W1C/H) Reads or clears enable for SSO_ERR0[TIAQH_DBE]. */
        uint64_t tiaqt_sbe             : 1;  /**< [ 46: 46](R/W1C/H) Reads or clears enable for SSO_ERR0[TIAQT_SBE]. */
        uint64_t tiaqt_dbe             : 1;  /**< [ 47: 47](R/W1C/H) Reads or clears enable for SSO_ERR0[TIAQT_DBE]. */
        uint64_t toaqh_sbe             : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for SSO_ERR0[TOAQH_SBE]. */
        uint64_t toaqh_dbe             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for SSO_ERR0[TOAQH_DBE]. */
        uint64_t toaqt_sbe             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for SSO_ERR0[TOAQT_SBE]. */
        uint64_t toaqt_dbe             : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for SSO_ERR0[TOAQT_DBE]. */
        uint64_t xaq_limit_sbe         : 1;  /**< [ 52: 52](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_LIMIT_SBE]. */
        uint64_t xaq_limit_dbe         : 1;  /**< [ 53: 53](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_LIMIT_DBE]. */
        uint64_t xaq_cnt_sbe           : 1;  /**< [ 54: 54](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_CNT_SBE]. */
        uint64_t xaq_cnt_dbe           : 1;  /**< [ 55: 55](R/W1C/H) Reads or clears enable for SSO_ERR0[XAQ_CNT_DBE]. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err0_ena_w1c_s cn; */
};
typedef union bdk_sso_err0_ena_w1c bdk_sso_err0_ena_w1c_t;

#define BDK_SSO_ERR0_ENA_W1C BDK_SSO_ERR0_ENA_W1C_FUNC()
static inline uint64_t BDK_SSO_ERR0_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR0_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001230ll;
    __bdk_csr_fatal("SSO_ERR0_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR0_ENA_W1C bdk_sso_err0_ena_w1c_t
#define bustype_BDK_SSO_ERR0_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR0_ENA_W1C "SSO_ERR0_ENA_W1C"
#define device_bar_BDK_SSO_ERR0_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR0_ENA_W1C 0
#define arguments_BDK_SSO_ERR0_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) sso_err0_ena_w1s
 *
 * SSO PF Error 0 Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_sso_err0_ena_w1s
{
    uint64_t u;
    struct bdk_sso_err0_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t xaq_cnt_dbe           : 1;  /**< [ 55: 55](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_CNT_DBE]. */
        uint64_t xaq_cnt_sbe           : 1;  /**< [ 54: 54](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_CNT_SBE]. */
        uint64_t xaq_limit_dbe         : 1;  /**< [ 53: 53](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_LIMIT_DBE]. */
        uint64_t xaq_limit_sbe         : 1;  /**< [ 52: 52](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_LIMIT_SBE]. */
        uint64_t toaqt_dbe             : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for SSO_ERR0[TOAQT_DBE]. */
        uint64_t toaqt_sbe             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for SSO_ERR0[TOAQT_SBE]. */
        uint64_t toaqh_dbe             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for SSO_ERR0[TOAQH_DBE]. */
        uint64_t toaqh_sbe             : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for SSO_ERR0[TOAQH_SBE]. */
        uint64_t tiaqt_dbe             : 1;  /**< [ 47: 47](R/W1S/H) Reads or sets enable for SSO_ERR0[TIAQT_DBE]. */
        uint64_t tiaqt_sbe             : 1;  /**< [ 46: 46](R/W1S/H) Reads or sets enable for SSO_ERR0[TIAQT_SBE]. */
        uint64_t tiaqh_dbe             : 1;  /**< [ 45: 45](R/W1S/H) Reads or sets enable for SSO_ERR0[TIAQH_DBE]. */
        uint64_t tiaqh_sbe             : 1;  /**< [ 44: 44](R/W1S/H) Reads or sets enable for SSO_ERR0[TIAQH_SBE]. */
        uint64_t llm_dbe               : 1;  /**< [ 43: 43](R/W1S/H) Reads or sets enable for SSO_ERR0[LLM_DBE]. */
        uint64_t llm_sbe               : 1;  /**< [ 42: 42](R/W1S/H) Reads or sets enable for SSO_ERR0[LLM_SBE]. */
        uint64_t inp_dbe               : 1;  /**< [ 41: 41](R/W1S/H) Reads or sets enable for SSO_ERR0[INP_DBE]. */
        uint64_t inp_sbe               : 1;  /**< [ 40: 40](R/W1S/H) Reads or sets enable for SSO_ERR0[INP_SBE]. */
        uint64_t qtc_dbe               : 1;  /**< [ 39: 39](R/W1S/H) Reads or sets enable for SSO_ERR0[QTC_DBE]. */
        uint64_t qtc_sbe               : 1;  /**< [ 38: 38](R/W1S/H) Reads or sets enable for SSO_ERR0[QTC_SBE]. */
        uint64_t xaq_dbe               : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_DBE]. */
        uint64_t xaq_sbe               : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_SBE]. */
        uint64_t fff_dbe               : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets enable for SSO_ERR0[FFF_DBE]. */
        uint64_t fff_sbe               : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets enable for SSO_ERR0[FFF_SBE]. */
        uint64_t wes_dbe               : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets enable for SSO_ERR0[WES_DBE]. */
        uint64_t wes_sbe               : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for SSO_ERR0[WES_SBE]. */
        uint64_t reserved_12_31        : 20;
        uint64_t gmid_multi            : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for SSO_ERR0[GMID_MULTI]. */
        uint64_t gmid_unmap            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSO_ERR0[GMID_UNMAP]. */
        uint64_t gmid0                 : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSO_ERR0[GMID0]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSO_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSO_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSO_ERR0[ADDWQ_DROPPED]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSO_ERR0[AWEMPTY]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSO_ERR0[GRPDIS]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSO_ERR0[BFPN]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSO_ERR0[BFP]. */
        uint64_t npf                   : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSO_ERR0[NPF]. */
        uint64_t fpe                   : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSO_ERR0[FPE]. */
#else /* Word 0 - Little Endian */
        uint64_t fpe                   : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSO_ERR0[FPE]. */
        uint64_t npf                   : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSO_ERR0[NPF]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSO_ERR0[BFP]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSO_ERR0[BFPN]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSO_ERR0[GRPDIS]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSO_ERR0[AWEMPTY]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSO_ERR0[ADDWQ_DROPPED]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSO_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSO_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t gmid0                 : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSO_ERR0[GMID0]. */
        uint64_t gmid_unmap            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSO_ERR0[GMID_UNMAP]. */
        uint64_t gmid_multi            : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for SSO_ERR0[GMID_MULTI]. */
        uint64_t reserved_12_31        : 20;
        uint64_t wes_sbe               : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for SSO_ERR0[WES_SBE]. */
        uint64_t wes_dbe               : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets enable for SSO_ERR0[WES_DBE]. */
        uint64_t fff_sbe               : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets enable for SSO_ERR0[FFF_SBE]. */
        uint64_t fff_dbe               : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets enable for SSO_ERR0[FFF_DBE]. */
        uint64_t xaq_sbe               : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_SBE]. */
        uint64_t xaq_dbe               : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_DBE]. */
        uint64_t qtc_sbe               : 1;  /**< [ 38: 38](R/W1S/H) Reads or sets enable for SSO_ERR0[QTC_SBE]. */
        uint64_t qtc_dbe               : 1;  /**< [ 39: 39](R/W1S/H) Reads or sets enable for SSO_ERR0[QTC_DBE]. */
        uint64_t inp_sbe               : 1;  /**< [ 40: 40](R/W1S/H) Reads or sets enable for SSO_ERR0[INP_SBE]. */
        uint64_t inp_dbe               : 1;  /**< [ 41: 41](R/W1S/H) Reads or sets enable for SSO_ERR0[INP_DBE]. */
        uint64_t llm_sbe               : 1;  /**< [ 42: 42](R/W1S/H) Reads or sets enable for SSO_ERR0[LLM_SBE]. */
        uint64_t llm_dbe               : 1;  /**< [ 43: 43](R/W1S/H) Reads or sets enable for SSO_ERR0[LLM_DBE]. */
        uint64_t tiaqh_sbe             : 1;  /**< [ 44: 44](R/W1S/H) Reads or sets enable for SSO_ERR0[TIAQH_SBE]. */
        uint64_t tiaqh_dbe             : 1;  /**< [ 45: 45](R/W1S/H) Reads or sets enable for SSO_ERR0[TIAQH_DBE]. */
        uint64_t tiaqt_sbe             : 1;  /**< [ 46: 46](R/W1S/H) Reads or sets enable for SSO_ERR0[TIAQT_SBE]. */
        uint64_t tiaqt_dbe             : 1;  /**< [ 47: 47](R/W1S/H) Reads or sets enable for SSO_ERR0[TIAQT_DBE]. */
        uint64_t toaqh_sbe             : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for SSO_ERR0[TOAQH_SBE]. */
        uint64_t toaqh_dbe             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for SSO_ERR0[TOAQH_DBE]. */
        uint64_t toaqt_sbe             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for SSO_ERR0[TOAQT_SBE]. */
        uint64_t toaqt_dbe             : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for SSO_ERR0[TOAQT_DBE]. */
        uint64_t xaq_limit_sbe         : 1;  /**< [ 52: 52](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_LIMIT_SBE]. */
        uint64_t xaq_limit_dbe         : 1;  /**< [ 53: 53](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_LIMIT_DBE]. */
        uint64_t xaq_cnt_sbe           : 1;  /**< [ 54: 54](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_CNT_SBE]. */
        uint64_t xaq_cnt_dbe           : 1;  /**< [ 55: 55](R/W1S/H) Reads or sets enable for SSO_ERR0[XAQ_CNT_DBE]. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err0_ena_w1s_s cn; */
};
typedef union bdk_sso_err0_ena_w1s bdk_sso_err0_ena_w1s_t;

#define BDK_SSO_ERR0_ENA_W1S BDK_SSO_ERR0_ENA_W1S_FUNC()
static inline uint64_t BDK_SSO_ERR0_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR0_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001238ll;
    __bdk_csr_fatal("SSO_ERR0_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR0_ENA_W1S bdk_sso_err0_ena_w1s_t
#define bustype_BDK_SSO_ERR0_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR0_ENA_W1S "SSO_ERR0_ENA_W1S"
#define device_bar_BDK_SSO_ERR0_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR0_ENA_W1S 0
#define arguments_BDK_SSO_ERR0_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) sso_err0_w1s
 *
 * SSO PF Error 0 Set Register
 * This register sets interrupt bits.
 */
union bdk_sso_err0_w1s
{
    uint64_t u;
    struct bdk_sso_err0_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t xaq_cnt_dbe           : 1;  /**< [ 55: 55](R/W1S/H) Reads or sets SSO_ERR0[XAQ_CNT_DBE]. */
        uint64_t xaq_cnt_sbe           : 1;  /**< [ 54: 54](R/W1S/H) Reads or sets SSO_ERR0[XAQ_CNT_SBE]. */
        uint64_t xaq_limit_dbe         : 1;  /**< [ 53: 53](R/W1S/H) Reads or sets SSO_ERR0[XAQ_LIMIT_DBE]. */
        uint64_t xaq_limit_sbe         : 1;  /**< [ 52: 52](R/W1S/H) Reads or sets SSO_ERR0[XAQ_LIMIT_SBE]. */
        uint64_t toaqt_dbe             : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets SSO_ERR0[TOAQT_DBE]. */
        uint64_t toaqt_sbe             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets SSO_ERR0[TOAQT_SBE]. */
        uint64_t toaqh_dbe             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets SSO_ERR0[TOAQH_DBE]. */
        uint64_t toaqh_sbe             : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets SSO_ERR0[TOAQH_SBE]. */
        uint64_t tiaqt_dbe             : 1;  /**< [ 47: 47](R/W1S/H) Reads or sets SSO_ERR0[TIAQT_DBE]. */
        uint64_t tiaqt_sbe             : 1;  /**< [ 46: 46](R/W1S/H) Reads or sets SSO_ERR0[TIAQT_SBE]. */
        uint64_t tiaqh_dbe             : 1;  /**< [ 45: 45](R/W1S/H) Reads or sets SSO_ERR0[TIAQH_DBE]. */
        uint64_t tiaqh_sbe             : 1;  /**< [ 44: 44](R/W1S/H) Reads or sets SSO_ERR0[TIAQH_SBE]. */
        uint64_t llm_dbe               : 1;  /**< [ 43: 43](R/W1S/H) Reads or sets SSO_ERR0[LLM_DBE]. */
        uint64_t llm_sbe               : 1;  /**< [ 42: 42](R/W1S/H) Reads or sets SSO_ERR0[LLM_SBE]. */
        uint64_t inp_dbe               : 1;  /**< [ 41: 41](R/W1S/H) Reads or sets SSO_ERR0[INP_DBE]. */
        uint64_t inp_sbe               : 1;  /**< [ 40: 40](R/W1S/H) Reads or sets SSO_ERR0[INP_SBE]. */
        uint64_t qtc_dbe               : 1;  /**< [ 39: 39](R/W1S/H) Reads or sets SSO_ERR0[QTC_DBE]. */
        uint64_t qtc_sbe               : 1;  /**< [ 38: 38](R/W1S/H) Reads or sets SSO_ERR0[QTC_SBE]. */
        uint64_t xaq_dbe               : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets SSO_ERR0[XAQ_DBE]. */
        uint64_t xaq_sbe               : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets SSO_ERR0[XAQ_SBE]. */
        uint64_t fff_dbe               : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets SSO_ERR0[FFF_DBE]. */
        uint64_t fff_sbe               : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets SSO_ERR0[FFF_SBE]. */
        uint64_t wes_dbe               : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets SSO_ERR0[WES_DBE]. */
        uint64_t wes_sbe               : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets SSO_ERR0[WES_SBE]. */
        uint64_t reserved_12_31        : 20;
        uint64_t gmid_multi            : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets SSO_ERR0[GMID_MULTI]. */
        uint64_t gmid_unmap            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSO_ERR0[GMID_UNMAP]. */
        uint64_t gmid0                 : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSO_ERR0[GMID0]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSO_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSO_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSO_ERR0[ADDWQ_DROPPED]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSO_ERR0[AWEMPTY]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSO_ERR0[GRPDIS]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSO_ERR0[BFPN]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSO_ERR0[BFP]. */
        uint64_t npf                   : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSO_ERR0[NPF]. */
        uint64_t fpe                   : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSO_ERR0[FPE]. */
#else /* Word 0 - Little Endian */
        uint64_t fpe                   : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSO_ERR0[FPE]. */
        uint64_t npf                   : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSO_ERR0[NPF]. */
        uint64_t bfp                   : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSO_ERR0[BFP]. */
        uint64_t bfpn                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSO_ERR0[BFPN]. */
        uint64_t grpdis                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSO_ERR0[GRPDIS]. */
        uint64_t awempty               : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSO_ERR0[AWEMPTY]. */
        uint64_t addwq_dropped         : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSO_ERR0[ADDWQ_DROPPED]. */
        uint64_t addwq_dropped_wqp0    : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSO_ERR0[ADDWQ_DROPPED_WQP0]. */
        uint64_t addwq_dropped_qctldis : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSO_ERR0[ADDWQ_DROPPED_QCTLDIS]. */
        uint64_t gmid0                 : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSO_ERR0[GMID0]. */
        uint64_t gmid_unmap            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSO_ERR0[GMID_UNMAP]. */
        uint64_t gmid_multi            : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets SSO_ERR0[GMID_MULTI]. */
        uint64_t reserved_12_31        : 20;
        uint64_t wes_sbe               : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets SSO_ERR0[WES_SBE]. */
        uint64_t wes_dbe               : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets SSO_ERR0[WES_DBE]. */
        uint64_t fff_sbe               : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets SSO_ERR0[FFF_SBE]. */
        uint64_t fff_dbe               : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets SSO_ERR0[FFF_DBE]. */
        uint64_t xaq_sbe               : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets SSO_ERR0[XAQ_SBE]. */
        uint64_t xaq_dbe               : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets SSO_ERR0[XAQ_DBE]. */
        uint64_t qtc_sbe               : 1;  /**< [ 38: 38](R/W1S/H) Reads or sets SSO_ERR0[QTC_SBE]. */
        uint64_t qtc_dbe               : 1;  /**< [ 39: 39](R/W1S/H) Reads or sets SSO_ERR0[QTC_DBE]. */
        uint64_t inp_sbe               : 1;  /**< [ 40: 40](R/W1S/H) Reads or sets SSO_ERR0[INP_SBE]. */
        uint64_t inp_dbe               : 1;  /**< [ 41: 41](R/W1S/H) Reads or sets SSO_ERR0[INP_DBE]. */
        uint64_t llm_sbe               : 1;  /**< [ 42: 42](R/W1S/H) Reads or sets SSO_ERR0[LLM_SBE]. */
        uint64_t llm_dbe               : 1;  /**< [ 43: 43](R/W1S/H) Reads or sets SSO_ERR0[LLM_DBE]. */
        uint64_t tiaqh_sbe             : 1;  /**< [ 44: 44](R/W1S/H) Reads or sets SSO_ERR0[TIAQH_SBE]. */
        uint64_t tiaqh_dbe             : 1;  /**< [ 45: 45](R/W1S/H) Reads or sets SSO_ERR0[TIAQH_DBE]. */
        uint64_t tiaqt_sbe             : 1;  /**< [ 46: 46](R/W1S/H) Reads or sets SSO_ERR0[TIAQT_SBE]. */
        uint64_t tiaqt_dbe             : 1;  /**< [ 47: 47](R/W1S/H) Reads or sets SSO_ERR0[TIAQT_DBE]. */
        uint64_t toaqh_sbe             : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets SSO_ERR0[TOAQH_SBE]. */
        uint64_t toaqh_dbe             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets SSO_ERR0[TOAQH_DBE]. */
        uint64_t toaqt_sbe             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets SSO_ERR0[TOAQT_SBE]. */
        uint64_t toaqt_dbe             : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets SSO_ERR0[TOAQT_DBE]. */
        uint64_t xaq_limit_sbe         : 1;  /**< [ 52: 52](R/W1S/H) Reads or sets SSO_ERR0[XAQ_LIMIT_SBE]. */
        uint64_t xaq_limit_dbe         : 1;  /**< [ 53: 53](R/W1S/H) Reads or sets SSO_ERR0[XAQ_LIMIT_DBE]. */
        uint64_t xaq_cnt_sbe           : 1;  /**< [ 54: 54](R/W1S/H) Reads or sets SSO_ERR0[XAQ_CNT_SBE]. */
        uint64_t xaq_cnt_dbe           : 1;  /**< [ 55: 55](R/W1S/H) Reads or sets SSO_ERR0[XAQ_CNT_DBE]. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err0_w1s_s cn; */
};
typedef union bdk_sso_err0_w1s bdk_sso_err0_w1s_t;

#define BDK_SSO_ERR0_W1S BDK_SSO_ERR0_W1S_FUNC()
static inline uint64_t BDK_SSO_ERR0_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR0_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001228ll;
    __bdk_csr_fatal("SSO_ERR0_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR0_W1S bdk_sso_err0_w1s_t
#define bustype_BDK_SSO_ERR0_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR0_W1S "SSO_ERR0_W1S"
#define device_bar_BDK_SSO_ERR0_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR0_W1S 0
#define arguments_BDK_SSO_ERR0_W1S -1,-1,-1,-1

/**
 * Register (NCB) sso_err1
 *
 * SSO PF Error 1 Register
 * This register contains ECC and other miscellaneous error bits.
 */
union bdk_sso_err1
{
    uint64_t u;
    struct bdk_sso_err1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t mbox_mem_dbe          : 1;  /**< [ 15: 15](R/W1C/H) Double-bit error for MBOX_MEM RAM. */
        uint64_t mbox_mem_sbe          : 1;  /**< [ 14: 14](R/W1C/H) Single-bit error for MBOX_MEM RAM. */
        uint64_t thrint_dbe            : 1;  /**< [ 13: 13](R/W1C/H) Double-bit error for THRINT RAM. */
        uint64_t thrint_sbe            : 1;  /**< [ 12: 12](R/W1C/H) Single-bit error for THRINT RAM. */
        uint64_t mask_dbe              : 1;  /**< [ 11: 11](R/W1C/H) Double-bit error for MASK RAM. */
        uint64_t mask_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Single-bit error for MASK RAM. */
        uint64_t gdw_dbe               : 1;  /**< [  9:  9](R/W1C/H) Double-bit error for GDW RAM. */
        uint64_t gdw_sbe               : 1;  /**< [  8:  8](R/W1C/H) Single-bit error for GDW RAM. */
        uint64_t qidx_dbe              : 1;  /**< [  7:  7](R/W1C/H) Double-bit error for QIDX RAM. */
        uint64_t qidx_sbe              : 1;  /**< [  6:  6](R/W1C/H) Single-bit error for QIDX RAM. */
        uint64_t tptr_dbe              : 1;  /**< [  5:  5](R/W1C/H) Double-bit error for TPTR RAM. */
        uint64_t tptr_sbe              : 1;  /**< [  4:  4](R/W1C/H) Single-bit error for TPTR RAM. */
        uint64_t hptr_dbe              : 1;  /**< [  3:  3](R/W1C/H) Double-bit error for HPTR RAM. */
        uint64_t hptr_sbe              : 1;  /**< [  2:  2](R/W1C/H) Single-bit error for HPTR RAM. */
        uint64_t cntr_dbe              : 1;  /**< [  1:  1](R/W1C/H) Double-bit error for CNTR RAM. */
        uint64_t cntr_sbe              : 1;  /**< [  0:  0](R/W1C/H) Single-bit error for CNTR RAM. */
#else /* Word 0 - Little Endian */
        uint64_t cntr_sbe              : 1;  /**< [  0:  0](R/W1C/H) Single-bit error for CNTR RAM. */
        uint64_t cntr_dbe              : 1;  /**< [  1:  1](R/W1C/H) Double-bit error for CNTR RAM. */
        uint64_t hptr_sbe              : 1;  /**< [  2:  2](R/W1C/H) Single-bit error for HPTR RAM. */
        uint64_t hptr_dbe              : 1;  /**< [  3:  3](R/W1C/H) Double-bit error for HPTR RAM. */
        uint64_t tptr_sbe              : 1;  /**< [  4:  4](R/W1C/H) Single-bit error for TPTR RAM. */
        uint64_t tptr_dbe              : 1;  /**< [  5:  5](R/W1C/H) Double-bit error for TPTR RAM. */
        uint64_t qidx_sbe              : 1;  /**< [  6:  6](R/W1C/H) Single-bit error for QIDX RAM. */
        uint64_t qidx_dbe              : 1;  /**< [  7:  7](R/W1C/H) Double-bit error for QIDX RAM. */
        uint64_t gdw_sbe               : 1;  /**< [  8:  8](R/W1C/H) Single-bit error for GDW RAM. */
        uint64_t gdw_dbe               : 1;  /**< [  9:  9](R/W1C/H) Double-bit error for GDW RAM. */
        uint64_t mask_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Single-bit error for MASK RAM. */
        uint64_t mask_dbe              : 1;  /**< [ 11: 11](R/W1C/H) Double-bit error for MASK RAM. */
        uint64_t thrint_sbe            : 1;  /**< [ 12: 12](R/W1C/H) Single-bit error for THRINT RAM. */
        uint64_t thrint_dbe            : 1;  /**< [ 13: 13](R/W1C/H) Double-bit error for THRINT RAM. */
        uint64_t mbox_mem_sbe          : 1;  /**< [ 14: 14](R/W1C/H) Single-bit error for MBOX_MEM RAM. */
        uint64_t mbox_mem_dbe          : 1;  /**< [ 15: 15](R/W1C/H) Double-bit error for MBOX_MEM RAM. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err1_s cn; */
};
typedef union bdk_sso_err1 bdk_sso_err1_t;

#define BDK_SSO_ERR1 BDK_SSO_ERR1_FUNC()
static inline uint64_t BDK_SSO_ERR1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001240ll;
    __bdk_csr_fatal("SSO_ERR1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR1 bdk_sso_err1_t
#define bustype_BDK_SSO_ERR1 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR1 "SSO_ERR1"
#define device_bar_BDK_SSO_ERR1 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR1 0
#define arguments_BDK_SSO_ERR1 -1,-1,-1,-1

/**
 * Register (NCB) sso_err1_ena_w1c
 *
 * SSO PF Error 1 Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_sso_err1_ena_w1c
{
    uint64_t u;
    struct bdk_sso_err1_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t mbox_mem_dbe          : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for SSO_ERR1[MBOX_MEM_DBE]. */
        uint64_t mbox_mem_sbe          : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for SSO_ERR1[MBOX_MEM_SBE]. */
        uint64_t thrint_dbe            : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for SSO_ERR1[THRINT_DBE]. */
        uint64_t thrint_sbe            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for SSO_ERR1[THRINT_SBE]. */
        uint64_t mask_dbe              : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for SSO_ERR1[MASK_DBE]. */
        uint64_t mask_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSO_ERR1[MASK_SBE]. */
        uint64_t gdw_dbe               : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSO_ERR1[GDW_DBE]. */
        uint64_t gdw_sbe               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSO_ERR1[GDW_SBE]. */
        uint64_t qidx_dbe              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSO_ERR1[QIDX_DBE]. */
        uint64_t qidx_sbe              : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSO_ERR1[QIDX_SBE]. */
        uint64_t tptr_dbe              : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSO_ERR1[TPTR_DBE]. */
        uint64_t tptr_sbe              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSO_ERR1[TPTR_SBE]. */
        uint64_t hptr_dbe              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSO_ERR1[HPTR_DBE]. */
        uint64_t hptr_sbe              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSO_ERR1[HPTR_SBE]. */
        uint64_t cntr_dbe              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSO_ERR1[CNTR_DBE]. */
        uint64_t cntr_sbe              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSO_ERR1[CNTR_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t cntr_sbe              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSO_ERR1[CNTR_SBE]. */
        uint64_t cntr_dbe              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSO_ERR1[CNTR_DBE]. */
        uint64_t hptr_sbe              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSO_ERR1[HPTR_SBE]. */
        uint64_t hptr_dbe              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSO_ERR1[HPTR_DBE]. */
        uint64_t tptr_sbe              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSO_ERR1[TPTR_SBE]. */
        uint64_t tptr_dbe              : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSO_ERR1[TPTR_DBE]. */
        uint64_t qidx_sbe              : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSO_ERR1[QIDX_SBE]. */
        uint64_t qidx_dbe              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSO_ERR1[QIDX_DBE]. */
        uint64_t gdw_sbe               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSO_ERR1[GDW_SBE]. */
        uint64_t gdw_dbe               : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSO_ERR1[GDW_DBE]. */
        uint64_t mask_sbe              : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSO_ERR1[MASK_SBE]. */
        uint64_t mask_dbe              : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for SSO_ERR1[MASK_DBE]. */
        uint64_t thrint_sbe            : 1;  /**< [ 12: 12](R/W1C/H) Reads or clears enable for SSO_ERR1[THRINT_SBE]. */
        uint64_t thrint_dbe            : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for SSO_ERR1[THRINT_DBE]. */
        uint64_t mbox_mem_sbe          : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for SSO_ERR1[MBOX_MEM_SBE]. */
        uint64_t mbox_mem_dbe          : 1;  /**< [ 15: 15](R/W1C/H) Reads or clears enable for SSO_ERR1[MBOX_MEM_DBE]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err1_ena_w1c_s cn; */
};
typedef union bdk_sso_err1_ena_w1c bdk_sso_err1_ena_w1c_t;

#define BDK_SSO_ERR1_ENA_W1C BDK_SSO_ERR1_ENA_W1C_FUNC()
static inline uint64_t BDK_SSO_ERR1_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR1_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001250ll;
    __bdk_csr_fatal("SSO_ERR1_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR1_ENA_W1C bdk_sso_err1_ena_w1c_t
#define bustype_BDK_SSO_ERR1_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR1_ENA_W1C "SSO_ERR1_ENA_W1C"
#define device_bar_BDK_SSO_ERR1_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR1_ENA_W1C 0
#define arguments_BDK_SSO_ERR1_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) sso_err1_ena_w1s
 *
 * SSO PF Error 1 Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_sso_err1_ena_w1s
{
    uint64_t u;
    struct bdk_sso_err1_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t mbox_mem_dbe          : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for SSO_ERR1[MBOX_MEM_DBE]. */
        uint64_t mbox_mem_sbe          : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for SSO_ERR1[MBOX_MEM_SBE]. */
        uint64_t thrint_dbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for SSO_ERR1[THRINT_DBE]. */
        uint64_t thrint_sbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for SSO_ERR1[THRINT_SBE]. */
        uint64_t mask_dbe              : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for SSO_ERR1[MASK_DBE]. */
        uint64_t mask_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSO_ERR1[MASK_SBE]. */
        uint64_t gdw_dbe               : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSO_ERR1[GDW_DBE]. */
        uint64_t gdw_sbe               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSO_ERR1[GDW_SBE]. */
        uint64_t qidx_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSO_ERR1[QIDX_DBE]. */
        uint64_t qidx_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSO_ERR1[QIDX_SBE]. */
        uint64_t tptr_dbe              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSO_ERR1[TPTR_DBE]. */
        uint64_t tptr_sbe              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSO_ERR1[TPTR_SBE]. */
        uint64_t hptr_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSO_ERR1[HPTR_DBE]. */
        uint64_t hptr_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSO_ERR1[HPTR_SBE]. */
        uint64_t cntr_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSO_ERR1[CNTR_DBE]. */
        uint64_t cntr_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSO_ERR1[CNTR_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t cntr_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSO_ERR1[CNTR_SBE]. */
        uint64_t cntr_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSO_ERR1[CNTR_DBE]. */
        uint64_t hptr_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSO_ERR1[HPTR_SBE]. */
        uint64_t hptr_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSO_ERR1[HPTR_DBE]. */
        uint64_t tptr_sbe              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSO_ERR1[TPTR_SBE]. */
        uint64_t tptr_dbe              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSO_ERR1[TPTR_DBE]. */
        uint64_t qidx_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSO_ERR1[QIDX_SBE]. */
        uint64_t qidx_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSO_ERR1[QIDX_DBE]. */
        uint64_t gdw_sbe               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSO_ERR1[GDW_SBE]. */
        uint64_t gdw_dbe               : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSO_ERR1[GDW_DBE]. */
        uint64_t mask_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSO_ERR1[MASK_SBE]. */
        uint64_t mask_dbe              : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for SSO_ERR1[MASK_DBE]. */
        uint64_t thrint_sbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets enable for SSO_ERR1[THRINT_SBE]. */
        uint64_t thrint_dbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for SSO_ERR1[THRINT_DBE]. */
        uint64_t mbox_mem_sbe          : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for SSO_ERR1[MBOX_MEM_SBE]. */
        uint64_t mbox_mem_dbe          : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets enable for SSO_ERR1[MBOX_MEM_DBE]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err1_ena_w1s_s cn; */
};
typedef union bdk_sso_err1_ena_w1s bdk_sso_err1_ena_w1s_t;

#define BDK_SSO_ERR1_ENA_W1S BDK_SSO_ERR1_ENA_W1S_FUNC()
static inline uint64_t BDK_SSO_ERR1_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR1_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001258ll;
    __bdk_csr_fatal("SSO_ERR1_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR1_ENA_W1S bdk_sso_err1_ena_w1s_t
#define bustype_BDK_SSO_ERR1_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR1_ENA_W1S "SSO_ERR1_ENA_W1S"
#define device_bar_BDK_SSO_ERR1_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR1_ENA_W1S 0
#define arguments_BDK_SSO_ERR1_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) sso_err1_w1s
 *
 * SSO PF Error 1 Set Register
 * This register sets interrupt bits.
 */
union bdk_sso_err1_w1s
{
    uint64_t u;
    struct bdk_sso_err1_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t mbox_mem_dbe          : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets SSO_ERR1[MBOX_MEM_DBE]. */
        uint64_t mbox_mem_sbe          : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets SSO_ERR1[MBOX_MEM_SBE]. */
        uint64_t thrint_dbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets SSO_ERR1[THRINT_DBE]. */
        uint64_t thrint_sbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets SSO_ERR1[THRINT_SBE]. */
        uint64_t mask_dbe              : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets SSO_ERR1[MASK_DBE]. */
        uint64_t mask_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSO_ERR1[MASK_SBE]. */
        uint64_t gdw_dbe               : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSO_ERR1[GDW_DBE]. */
        uint64_t gdw_sbe               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSO_ERR1[GDW_SBE]. */
        uint64_t qidx_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSO_ERR1[QIDX_DBE]. */
        uint64_t qidx_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSO_ERR1[QIDX_SBE]. */
        uint64_t tptr_dbe              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSO_ERR1[TPTR_DBE]. */
        uint64_t tptr_sbe              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSO_ERR1[TPTR_SBE]. */
        uint64_t hptr_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSO_ERR1[HPTR_DBE]. */
        uint64_t hptr_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSO_ERR1[HPTR_SBE]. */
        uint64_t cntr_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSO_ERR1[CNTR_DBE]. */
        uint64_t cntr_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSO_ERR1[CNTR_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t cntr_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSO_ERR1[CNTR_SBE]. */
        uint64_t cntr_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSO_ERR1[CNTR_DBE]. */
        uint64_t hptr_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSO_ERR1[HPTR_SBE]. */
        uint64_t hptr_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSO_ERR1[HPTR_DBE]. */
        uint64_t tptr_sbe              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSO_ERR1[TPTR_SBE]. */
        uint64_t tptr_dbe              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSO_ERR1[TPTR_DBE]. */
        uint64_t qidx_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSO_ERR1[QIDX_SBE]. */
        uint64_t qidx_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSO_ERR1[QIDX_DBE]. */
        uint64_t gdw_sbe               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSO_ERR1[GDW_SBE]. */
        uint64_t gdw_dbe               : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSO_ERR1[GDW_DBE]. */
        uint64_t mask_sbe              : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSO_ERR1[MASK_SBE]. */
        uint64_t mask_dbe              : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets SSO_ERR1[MASK_DBE]. */
        uint64_t thrint_sbe            : 1;  /**< [ 12: 12](R/W1S/H) Reads or sets SSO_ERR1[THRINT_SBE]. */
        uint64_t thrint_dbe            : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets SSO_ERR1[THRINT_DBE]. */
        uint64_t mbox_mem_sbe          : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets SSO_ERR1[MBOX_MEM_SBE]. */
        uint64_t mbox_mem_dbe          : 1;  /**< [ 15: 15](R/W1S/H) Reads or sets SSO_ERR1[MBOX_MEM_DBE]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err1_w1s_s cn; */
};
typedef union bdk_sso_err1_w1s bdk_sso_err1_w1s_t;

#define BDK_SSO_ERR1_W1S BDK_SSO_ERR1_W1S_FUNC()
static inline uint64_t BDK_SSO_ERR1_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR1_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001248ll;
    __bdk_csr_fatal("SSO_ERR1_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR1_W1S bdk_sso_err1_w1s_t
#define bustype_BDK_SSO_ERR1_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR1_W1S "SSO_ERR1_W1S"
#define device_bar_BDK_SSO_ERR1_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR1_W1S 0
#define arguments_BDK_SSO_ERR1_W1S -1,-1,-1,-1

/**
 * Register (NCB) sso_err2
 *
 * SSO PF Error 2 Register
 * This register contains ECC and other miscellaneous error bits.
 */
union bdk_sso_err2
{
    uint64_t u;
    struct bdk_sso_err2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t pcc_dbe               : 1;  /**< [ 47: 47](R/W1C/H) Double-bit error for PCC RAM. */
        uint64_t pcc_sbe               : 1;  /**< [ 46: 46](R/W1C/H) Single-bit error for PCC RAM. */
        uint64_t vhgrp_dbe             : 1;  /**< [ 45: 45](R/W1C/H) Double-bit error for VHGRP RAM. */
        uint64_t vhgrp_sbe             : 1;  /**< [ 44: 44](R/W1C/H) Single-bit error for VHGRP RAM. */
        uint64_t hwsx_gmctl_dbe        : 1;  /**< [ 43: 43](R/W1C/H) Double-bit error for HWSX_GMCTL RAM. */
        uint64_t hwsx_gmctl_sbe        : 1;  /**< [ 42: 42](R/W1C/H) Single-bit error for HWSX_GMCTL RAM. */
        uint64_t ncbo_dbe              : 1;  /**< [ 41: 41](R/W1C/H) Double-bit error for NCBO RAM. */
        uint64_t ncbo_sbe              : 1;  /**< [ 40: 40](R/W1C/H) Single-bit error for NCBO RAM. */
        uint64_t pnd_dbe               : 1;  /**< [ 39: 39](R/W1C/H) Double-bit error for PND RAM. */
        uint64_t pnd_sbe               : 1;  /**< [ 38: 38](R/W1C/H) Single-bit error for PND RAM. */
        uint64_t oth_dbe               : 1;  /**< [ 37: 37](R/W1C/H) Double-bit error for odd OTH RAM. */
        uint64_t oth_sbe               : 1;  /**< [ 36: 36](R/W1C/H) Single-bit error for odd OTH RAM. */
        uint64_t nidx_dbe              : 1;  /**< [ 35: 35](R/W1C/H) Double-bit error for IDX RAM. */
        uint64_t nidx_sbe              : 1;  /**< [ 34: 34](R/W1C/H) Single-bit error for IDX RAM. */
        uint64_t pidx_dbe              : 1;  /**< [ 33: 33](R/W1C/H) Double-bit error for FIDX RAM. */
        uint64_t pidx_sbe              : 1;  /**< [ 32: 32](R/W1C/H) Single-bit error for FIDX RAM. */
        uint64_t reserved_31           : 1;
        uint64_t ws_gmid0              : 1;  /**< [ 30: 30](R/W1C/H) Work-slot operation found a SSO_PF_MAP() with GMID=0x0; no-work was returned or the
                                                                 switch-tag was not performed. When a request thus dropped, even if this bit is
                                                                 already set. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](R/W1C/H) Work-slot operation found a SSO_PF_MAP() double-hit; no-work was returned or the
                                                                 switch-tag was not performed. When a request thus dropped, even if this bit is
                                                                 already set, SSO_UNMAP_INFO2 is loaded. */
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](R/W1C/H) Work-slot operation found a SSO_PF_MAP() double-hit; no-work was returned or the
                                                                 switch-tag was not performed. When a request thus dropped, even if this bit is
                                                                 already set, SSO_UNMAP_INFO2 is loaded. */
        uint64_t reserved_15_27        : 13;
        uint64_t iop                   : 15; /**< [ 14:  0](R/W1C/H) Illegal operation errors:
                                                                 \<14\> = Received command before SSO_RESET[BUSY] cleared.
                                                                 \<13\> = Received illegal opcode.
                                                                 \<12\> = Received GET_WORK(INDEXED) when SSO_HWS()_GMCTL[GW_INDX_ENA] is zero.
                                                                 \<11\> = Received illegal load for work slot op.
                                                                 \<10\> = Received illegal store for work slot op.
                                                                 \<9\> = Received UPD_WQP_GRP/SWTAG_FULL/CLR_NSCHED with WQP=0.
                                                                 \<8\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/DESCH/UPD_WQP_GRP/GET_WORK/ALLOC_WE from work
                                                                 slot with CLR_NSCHED pending.
                                                                 \<7\> = Received CLR_NSCHED from work slot with SWTAG_DESCH/DESCH/CLR_NSCHED pending.
                                                                 \<6\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/DESCH/UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED
                                                                 from work slot with ALLOC_WE pending.
                                                                 \<5\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/DESCH/UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED
                                                                 from work slot with GET_WORK pending.
                                                                 \<4\> = Received SWTAG_FULL/SWTAG_DESCH with tag specified as UNTAGGED.
                                                                 \<3\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH with tag specified as EMPTY.
                                                                 \<2\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/GET_WORK from work slot with pending tag
                                                                 switch to ORDERED or ATOMIC.
                                                                 \<1\> = Received SWTAG/SWTAG_DESCH/DESCH/UPD_WQP_GRP from work slot in UNTAGGED state.
                                                                 \<0\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/DESCH/UPD_WQP_GRP from work slot in EMPTY
                                                                 state. */
#else /* Word 0 - Little Endian */
        uint64_t iop                   : 15; /**< [ 14:  0](R/W1C/H) Illegal operation errors:
                                                                 \<14\> = Received command before SSO_RESET[BUSY] cleared.
                                                                 \<13\> = Received illegal opcode.
                                                                 \<12\> = Received GET_WORK(INDEXED) when SSO_HWS()_GMCTL[GW_INDX_ENA] is zero.
                                                                 \<11\> = Received illegal load for work slot op.
                                                                 \<10\> = Received illegal store for work slot op.
                                                                 \<9\> = Received UPD_WQP_GRP/SWTAG_FULL/CLR_NSCHED with WQP=0.
                                                                 \<8\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/DESCH/UPD_WQP_GRP/GET_WORK/ALLOC_WE from work
                                                                 slot with CLR_NSCHED pending.
                                                                 \<7\> = Received CLR_NSCHED from work slot with SWTAG_DESCH/DESCH/CLR_NSCHED pending.
                                                                 \<6\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/DESCH/UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED
                                                                 from work slot with ALLOC_WE pending.
                                                                 \<5\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/DESCH/UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED
                                                                 from work slot with GET_WORK pending.
                                                                 \<4\> = Received SWTAG_FULL/SWTAG_DESCH with tag specified as UNTAGGED.
                                                                 \<3\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH with tag specified as EMPTY.
                                                                 \<2\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/GET_WORK from work slot with pending tag
                                                                 switch to ORDERED or ATOMIC.
                                                                 \<1\> = Received SWTAG/SWTAG_DESCH/DESCH/UPD_WQP_GRP from work slot in UNTAGGED state.
                                                                 \<0\> = Received SWTAG/SWTAG_FULL/SWTAG_DESCH/DESCH/UPD_WQP_GRP from work slot in EMPTY
                                                                 state. */
        uint64_t reserved_15_27        : 13;
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](R/W1C/H) Work-slot operation found a SSO_PF_MAP() double-hit; no-work was returned or the
                                                                 switch-tag was not performed. When a request thus dropped, even if this bit is
                                                                 already set, SSO_UNMAP_INFO2 is loaded. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](R/W1C/H) Work-slot operation found a SSO_PF_MAP() double-hit; no-work was returned or the
                                                                 switch-tag was not performed. When a request thus dropped, even if this bit is
                                                                 already set, SSO_UNMAP_INFO2 is loaded. */
        uint64_t ws_gmid0              : 1;  /**< [ 30: 30](R/W1C/H) Work-slot operation found a SSO_PF_MAP() with GMID=0x0; no-work was returned or the
                                                                 switch-tag was not performed. When a request thus dropped, even if this bit is
                                                                 already set. */
        uint64_t reserved_31           : 1;
        uint64_t pidx_sbe              : 1;  /**< [ 32: 32](R/W1C/H) Single-bit error for FIDX RAM. */
        uint64_t pidx_dbe              : 1;  /**< [ 33: 33](R/W1C/H) Double-bit error for FIDX RAM. */
        uint64_t nidx_sbe              : 1;  /**< [ 34: 34](R/W1C/H) Single-bit error for IDX RAM. */
        uint64_t nidx_dbe              : 1;  /**< [ 35: 35](R/W1C/H) Double-bit error for IDX RAM. */
        uint64_t oth_sbe               : 1;  /**< [ 36: 36](R/W1C/H) Single-bit error for odd OTH RAM. */
        uint64_t oth_dbe               : 1;  /**< [ 37: 37](R/W1C/H) Double-bit error for odd OTH RAM. */
        uint64_t pnd_sbe               : 1;  /**< [ 38: 38](R/W1C/H) Single-bit error for PND RAM. */
        uint64_t pnd_dbe               : 1;  /**< [ 39: 39](R/W1C/H) Double-bit error for PND RAM. */
        uint64_t ncbo_sbe              : 1;  /**< [ 40: 40](R/W1C/H) Single-bit error for NCBO RAM. */
        uint64_t ncbo_dbe              : 1;  /**< [ 41: 41](R/W1C/H) Double-bit error for NCBO RAM. */
        uint64_t hwsx_gmctl_sbe        : 1;  /**< [ 42: 42](R/W1C/H) Single-bit error for HWSX_GMCTL RAM. */
        uint64_t hwsx_gmctl_dbe        : 1;  /**< [ 43: 43](R/W1C/H) Double-bit error for HWSX_GMCTL RAM. */
        uint64_t vhgrp_sbe             : 1;  /**< [ 44: 44](R/W1C/H) Single-bit error for VHGRP RAM. */
        uint64_t vhgrp_dbe             : 1;  /**< [ 45: 45](R/W1C/H) Double-bit error for VHGRP RAM. */
        uint64_t pcc_sbe               : 1;  /**< [ 46: 46](R/W1C/H) Single-bit error for PCC RAM. */
        uint64_t pcc_dbe               : 1;  /**< [ 47: 47](R/W1C/H) Double-bit error for PCC RAM. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err2_s cn; */
};
typedef union bdk_sso_err2 bdk_sso_err2_t;

#define BDK_SSO_ERR2 BDK_SSO_ERR2_FUNC()
static inline uint64_t BDK_SSO_ERR2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001260ll;
    __bdk_csr_fatal("SSO_ERR2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR2 bdk_sso_err2_t
#define bustype_BDK_SSO_ERR2 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR2 "SSO_ERR2"
#define device_bar_BDK_SSO_ERR2 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR2 0
#define arguments_BDK_SSO_ERR2 -1,-1,-1,-1

/**
 * Register (NCB) sso_err2_ena_w1c
 *
 * SSO PF Error 2 Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_sso_err2_ena_w1c
{
    uint64_t u;
    struct bdk_sso_err2_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t pcc_dbe               : 1;  /**< [ 47: 47](R/W1C/H) Reads or clears enable for SSO_ERR2[PCC_DBE]. */
        uint64_t pcc_sbe               : 1;  /**< [ 46: 46](R/W1C/H) Reads or clears enable for SSO_ERR2[PCC_SBE]. */
        uint64_t vhgrp_dbe             : 1;  /**< [ 45: 45](R/W1C/H) Reads or clears enable for SSO_ERR2[VHGRP_DBE]. */
        uint64_t vhgrp_sbe             : 1;  /**< [ 44: 44](R/W1C/H) Reads or clears enable for SSO_ERR2[VHGRP_SBE]. */
        uint64_t hwsx_gmctl_dbe        : 1;  /**< [ 43: 43](R/W1C/H) Reads or clears enable for SSO_ERR2[HWSX_GMCTL_DBE]. */
        uint64_t hwsx_gmctl_sbe        : 1;  /**< [ 42: 42](R/W1C/H) Reads or clears enable for SSO_ERR2[HWSX_GMCTL_SBE]. */
        uint64_t ncbo_dbe              : 1;  /**< [ 41: 41](R/W1C/H) Reads or clears enable for SSO_ERR2[NCBO_DBE]. */
        uint64_t ncbo_sbe              : 1;  /**< [ 40: 40](R/W1C/H) Reads or clears enable for SSO_ERR2[NCBO_SBE]. */
        uint64_t pnd_dbe               : 1;  /**< [ 39: 39](R/W1C/H) Reads or clears enable for SSO_ERR2[PND_DBE]. */
        uint64_t pnd_sbe               : 1;  /**< [ 38: 38](R/W1C/H) Reads or clears enable for SSO_ERR2[PND_SBE]. */
        uint64_t oth_dbe               : 1;  /**< [ 37: 37](R/W1C/H) Reads or clears enable for SSO_ERR2[OTH_DBE]. */
        uint64_t oth_sbe               : 1;  /**< [ 36: 36](R/W1C/H) Reads or clears enable for SSO_ERR2[OTH_SBE]. */
        uint64_t nidx_dbe              : 1;  /**< [ 35: 35](R/W1C/H) Reads or clears enable for SSO_ERR2[NIDX_DBE]. */
        uint64_t nidx_sbe              : 1;  /**< [ 34: 34](R/W1C/H) Reads or clears enable for SSO_ERR2[NIDX_SBE]. */
        uint64_t pidx_dbe              : 1;  /**< [ 33: 33](R/W1C/H) Reads or clears enable for SSO_ERR2[PIDX_DBE]. */
        uint64_t pidx_sbe              : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for SSO_ERR2[PIDX_SBE]. */
        uint64_t reserved_31           : 1;
        uint64_t ws_gmid0              : 1;  /**< [ 30: 30](R/W1C/H) Reads or clears enable for SSO_ERR2[WS_GMID0]. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](R/W1C/H) Reads or clears enable for SSO_ERR2[WS_MULTI]. */
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](R/W1C/H) Reads or clears enable for SSO_ERR2[WS_UNMAP]. */
        uint64_t reserved_15_27        : 13;
        uint64_t iop                   : 15; /**< [ 14:  0](R/W1C/H) Reads or clears enable for SSO_ERR2[IOP]. */
#else /* Word 0 - Little Endian */
        uint64_t iop                   : 15; /**< [ 14:  0](R/W1C/H) Reads or clears enable for SSO_ERR2[IOP]. */
        uint64_t reserved_15_27        : 13;
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](R/W1C/H) Reads or clears enable for SSO_ERR2[WS_UNMAP]. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](R/W1C/H) Reads or clears enable for SSO_ERR2[WS_MULTI]. */
        uint64_t ws_gmid0              : 1;  /**< [ 30: 30](R/W1C/H) Reads or clears enable for SSO_ERR2[WS_GMID0]. */
        uint64_t reserved_31           : 1;
        uint64_t pidx_sbe              : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for SSO_ERR2[PIDX_SBE]. */
        uint64_t pidx_dbe              : 1;  /**< [ 33: 33](R/W1C/H) Reads or clears enable for SSO_ERR2[PIDX_DBE]. */
        uint64_t nidx_sbe              : 1;  /**< [ 34: 34](R/W1C/H) Reads or clears enable for SSO_ERR2[NIDX_SBE]. */
        uint64_t nidx_dbe              : 1;  /**< [ 35: 35](R/W1C/H) Reads or clears enable for SSO_ERR2[NIDX_DBE]. */
        uint64_t oth_sbe               : 1;  /**< [ 36: 36](R/W1C/H) Reads or clears enable for SSO_ERR2[OTH_SBE]. */
        uint64_t oth_dbe               : 1;  /**< [ 37: 37](R/W1C/H) Reads or clears enable for SSO_ERR2[OTH_DBE]. */
        uint64_t pnd_sbe               : 1;  /**< [ 38: 38](R/W1C/H) Reads or clears enable for SSO_ERR2[PND_SBE]. */
        uint64_t pnd_dbe               : 1;  /**< [ 39: 39](R/W1C/H) Reads or clears enable for SSO_ERR2[PND_DBE]. */
        uint64_t ncbo_sbe              : 1;  /**< [ 40: 40](R/W1C/H) Reads or clears enable for SSO_ERR2[NCBO_SBE]. */
        uint64_t ncbo_dbe              : 1;  /**< [ 41: 41](R/W1C/H) Reads or clears enable for SSO_ERR2[NCBO_DBE]. */
        uint64_t hwsx_gmctl_sbe        : 1;  /**< [ 42: 42](R/W1C/H) Reads or clears enable for SSO_ERR2[HWSX_GMCTL_SBE]. */
        uint64_t hwsx_gmctl_dbe        : 1;  /**< [ 43: 43](R/W1C/H) Reads or clears enable for SSO_ERR2[HWSX_GMCTL_DBE]. */
        uint64_t vhgrp_sbe             : 1;  /**< [ 44: 44](R/W1C/H) Reads or clears enable for SSO_ERR2[VHGRP_SBE]. */
        uint64_t vhgrp_dbe             : 1;  /**< [ 45: 45](R/W1C/H) Reads or clears enable for SSO_ERR2[VHGRP_DBE]. */
        uint64_t pcc_sbe               : 1;  /**< [ 46: 46](R/W1C/H) Reads or clears enable for SSO_ERR2[PCC_SBE]. */
        uint64_t pcc_dbe               : 1;  /**< [ 47: 47](R/W1C/H) Reads or clears enable for SSO_ERR2[PCC_DBE]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err2_ena_w1c_s cn; */
};
typedef union bdk_sso_err2_ena_w1c bdk_sso_err2_ena_w1c_t;

#define BDK_SSO_ERR2_ENA_W1C BDK_SSO_ERR2_ENA_W1C_FUNC()
static inline uint64_t BDK_SSO_ERR2_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR2_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001270ll;
    __bdk_csr_fatal("SSO_ERR2_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR2_ENA_W1C bdk_sso_err2_ena_w1c_t
#define bustype_BDK_SSO_ERR2_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR2_ENA_W1C "SSO_ERR2_ENA_W1C"
#define device_bar_BDK_SSO_ERR2_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR2_ENA_W1C 0
#define arguments_BDK_SSO_ERR2_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) sso_err2_ena_w1s
 *
 * SSO PF Error 2 Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_sso_err2_ena_w1s
{
    uint64_t u;
    struct bdk_sso_err2_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t pcc_dbe               : 1;  /**< [ 47: 47](R/W1S/H) Reads or sets enable for SSO_ERR2[PCC_DBE]. */
        uint64_t pcc_sbe               : 1;  /**< [ 46: 46](R/W1S/H) Reads or sets enable for SSO_ERR2[PCC_SBE]. */
        uint64_t vhgrp_dbe             : 1;  /**< [ 45: 45](R/W1S/H) Reads or sets enable for SSO_ERR2[VHGRP_DBE]. */
        uint64_t vhgrp_sbe             : 1;  /**< [ 44: 44](R/W1S/H) Reads or sets enable for SSO_ERR2[VHGRP_SBE]. */
        uint64_t hwsx_gmctl_dbe        : 1;  /**< [ 43: 43](R/W1S/H) Reads or sets enable for SSO_ERR2[HWSX_GMCTL_DBE]. */
        uint64_t hwsx_gmctl_sbe        : 1;  /**< [ 42: 42](R/W1S/H) Reads or sets enable for SSO_ERR2[HWSX_GMCTL_SBE]. */
        uint64_t ncbo_dbe              : 1;  /**< [ 41: 41](R/W1S/H) Reads or sets enable for SSO_ERR2[NCBO_DBE]. */
        uint64_t ncbo_sbe              : 1;  /**< [ 40: 40](R/W1S/H) Reads or sets enable for SSO_ERR2[NCBO_SBE]. */
        uint64_t pnd_dbe               : 1;  /**< [ 39: 39](R/W1S/H) Reads or sets enable for SSO_ERR2[PND_DBE]. */
        uint64_t pnd_sbe               : 1;  /**< [ 38: 38](R/W1S/H) Reads or sets enable for SSO_ERR2[PND_SBE]. */
        uint64_t oth_dbe               : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets enable for SSO_ERR2[OTH_DBE]. */
        uint64_t oth_sbe               : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets enable for SSO_ERR2[OTH_SBE]. */
        uint64_t nidx_dbe              : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets enable for SSO_ERR2[NIDX_DBE]. */
        uint64_t nidx_sbe              : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets enable for SSO_ERR2[NIDX_SBE]. */
        uint64_t pidx_dbe              : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets enable for SSO_ERR2[PIDX_DBE]. */
        uint64_t pidx_sbe              : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for SSO_ERR2[PIDX_SBE]. */
        uint64_t reserved_31           : 1;
        uint64_t ws_gmid0              : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets enable for SSO_ERR2[WS_GMID0]. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets enable for SSO_ERR2[WS_MULTI]. */
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets enable for SSO_ERR2[WS_UNMAP]. */
        uint64_t reserved_15_27        : 13;
        uint64_t iop                   : 15; /**< [ 14:  0](R/W1S/H) Reads or sets enable for SSO_ERR2[IOP]. */
#else /* Word 0 - Little Endian */
        uint64_t iop                   : 15; /**< [ 14:  0](R/W1S/H) Reads or sets enable for SSO_ERR2[IOP]. */
        uint64_t reserved_15_27        : 13;
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets enable for SSO_ERR2[WS_UNMAP]. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets enable for SSO_ERR2[WS_MULTI]. */
        uint64_t ws_gmid0              : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets enable for SSO_ERR2[WS_GMID0]. */
        uint64_t reserved_31           : 1;
        uint64_t pidx_sbe              : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for SSO_ERR2[PIDX_SBE]. */
        uint64_t pidx_dbe              : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets enable for SSO_ERR2[PIDX_DBE]. */
        uint64_t nidx_sbe              : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets enable for SSO_ERR2[NIDX_SBE]. */
        uint64_t nidx_dbe              : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets enable for SSO_ERR2[NIDX_DBE]. */
        uint64_t oth_sbe               : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets enable for SSO_ERR2[OTH_SBE]. */
        uint64_t oth_dbe               : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets enable for SSO_ERR2[OTH_DBE]. */
        uint64_t pnd_sbe               : 1;  /**< [ 38: 38](R/W1S/H) Reads or sets enable for SSO_ERR2[PND_SBE]. */
        uint64_t pnd_dbe               : 1;  /**< [ 39: 39](R/W1S/H) Reads or sets enable for SSO_ERR2[PND_DBE]. */
        uint64_t ncbo_sbe              : 1;  /**< [ 40: 40](R/W1S/H) Reads or sets enable for SSO_ERR2[NCBO_SBE]. */
        uint64_t ncbo_dbe              : 1;  /**< [ 41: 41](R/W1S/H) Reads or sets enable for SSO_ERR2[NCBO_DBE]. */
        uint64_t hwsx_gmctl_sbe        : 1;  /**< [ 42: 42](R/W1S/H) Reads or sets enable for SSO_ERR2[HWSX_GMCTL_SBE]. */
        uint64_t hwsx_gmctl_dbe        : 1;  /**< [ 43: 43](R/W1S/H) Reads or sets enable for SSO_ERR2[HWSX_GMCTL_DBE]. */
        uint64_t vhgrp_sbe             : 1;  /**< [ 44: 44](R/W1S/H) Reads or sets enable for SSO_ERR2[VHGRP_SBE]. */
        uint64_t vhgrp_dbe             : 1;  /**< [ 45: 45](R/W1S/H) Reads or sets enable for SSO_ERR2[VHGRP_DBE]. */
        uint64_t pcc_sbe               : 1;  /**< [ 46: 46](R/W1S/H) Reads or sets enable for SSO_ERR2[PCC_SBE]. */
        uint64_t pcc_dbe               : 1;  /**< [ 47: 47](R/W1S/H) Reads or sets enable for SSO_ERR2[PCC_DBE]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err2_ena_w1s_s cn; */
};
typedef union bdk_sso_err2_ena_w1s bdk_sso_err2_ena_w1s_t;

#define BDK_SSO_ERR2_ENA_W1S BDK_SSO_ERR2_ENA_W1S_FUNC()
static inline uint64_t BDK_SSO_ERR2_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR2_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001278ll;
    __bdk_csr_fatal("SSO_ERR2_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR2_ENA_W1S bdk_sso_err2_ena_w1s_t
#define bustype_BDK_SSO_ERR2_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR2_ENA_W1S "SSO_ERR2_ENA_W1S"
#define device_bar_BDK_SSO_ERR2_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR2_ENA_W1S 0
#define arguments_BDK_SSO_ERR2_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) sso_err2_w1s
 *
 * SSO PF Error 2 Set Register
 * This register sets interrupt bits.
 */
union bdk_sso_err2_w1s
{
    uint64_t u;
    struct bdk_sso_err2_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t pcc_dbe               : 1;  /**< [ 47: 47](R/W1S/H) Reads or sets SSO_ERR2[PCC_DBE]. */
        uint64_t pcc_sbe               : 1;  /**< [ 46: 46](R/W1S/H) Reads or sets SSO_ERR2[PCC_SBE]. */
        uint64_t vhgrp_dbe             : 1;  /**< [ 45: 45](R/W1S/H) Reads or sets SSO_ERR2[VHGRP_DBE]. */
        uint64_t vhgrp_sbe             : 1;  /**< [ 44: 44](R/W1S/H) Reads or sets SSO_ERR2[VHGRP_SBE]. */
        uint64_t hwsx_gmctl_dbe        : 1;  /**< [ 43: 43](R/W1S/H) Reads or sets SSO_ERR2[HWSX_GMCTL_DBE]. */
        uint64_t hwsx_gmctl_sbe        : 1;  /**< [ 42: 42](R/W1S/H) Reads or sets SSO_ERR2[HWSX_GMCTL_SBE]. */
        uint64_t ncbo_dbe              : 1;  /**< [ 41: 41](R/W1S/H) Reads or sets SSO_ERR2[NCBO_DBE]. */
        uint64_t ncbo_sbe              : 1;  /**< [ 40: 40](R/W1S/H) Reads or sets SSO_ERR2[NCBO_SBE]. */
        uint64_t pnd_dbe               : 1;  /**< [ 39: 39](R/W1S/H) Reads or sets SSO_ERR2[PND_DBE]. */
        uint64_t pnd_sbe               : 1;  /**< [ 38: 38](R/W1S/H) Reads or sets SSO_ERR2[PND_SBE]. */
        uint64_t oth_dbe               : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets SSO_ERR2[OTH_DBE]. */
        uint64_t oth_sbe               : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets SSO_ERR2[OTH_SBE]. */
        uint64_t nidx_dbe              : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets SSO_ERR2[NIDX_DBE]. */
        uint64_t nidx_sbe              : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets SSO_ERR2[NIDX_SBE]. */
        uint64_t pidx_dbe              : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets SSO_ERR2[PIDX_DBE]. */
        uint64_t pidx_sbe              : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets SSO_ERR2[PIDX_SBE]. */
        uint64_t reserved_31           : 1;
        uint64_t ws_gmid0              : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets SSO_ERR2[WS_GMID0]. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets SSO_ERR2[WS_MULTI]. */
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets SSO_ERR2[WS_UNMAP]. */
        uint64_t reserved_15_27        : 13;
        uint64_t iop                   : 15; /**< [ 14:  0](R/W1S/H) Reads or sets SSO_ERR2[IOP]. */
#else /* Word 0 - Little Endian */
        uint64_t iop                   : 15; /**< [ 14:  0](R/W1S/H) Reads or sets SSO_ERR2[IOP]. */
        uint64_t reserved_15_27        : 13;
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](R/W1S/H) Reads or sets SSO_ERR2[WS_UNMAP]. */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](R/W1S/H) Reads or sets SSO_ERR2[WS_MULTI]. */
        uint64_t ws_gmid0              : 1;  /**< [ 30: 30](R/W1S/H) Reads or sets SSO_ERR2[WS_GMID0]. */
        uint64_t reserved_31           : 1;
        uint64_t pidx_sbe              : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets SSO_ERR2[PIDX_SBE]. */
        uint64_t pidx_dbe              : 1;  /**< [ 33: 33](R/W1S/H) Reads or sets SSO_ERR2[PIDX_DBE]. */
        uint64_t nidx_sbe              : 1;  /**< [ 34: 34](R/W1S/H) Reads or sets SSO_ERR2[NIDX_SBE]. */
        uint64_t nidx_dbe              : 1;  /**< [ 35: 35](R/W1S/H) Reads or sets SSO_ERR2[NIDX_DBE]. */
        uint64_t oth_sbe               : 1;  /**< [ 36: 36](R/W1S/H) Reads or sets SSO_ERR2[OTH_SBE]. */
        uint64_t oth_dbe               : 1;  /**< [ 37: 37](R/W1S/H) Reads or sets SSO_ERR2[OTH_DBE]. */
        uint64_t pnd_sbe               : 1;  /**< [ 38: 38](R/W1S/H) Reads or sets SSO_ERR2[PND_SBE]. */
        uint64_t pnd_dbe               : 1;  /**< [ 39: 39](R/W1S/H) Reads or sets SSO_ERR2[PND_DBE]. */
        uint64_t ncbo_sbe              : 1;  /**< [ 40: 40](R/W1S/H) Reads or sets SSO_ERR2[NCBO_SBE]. */
        uint64_t ncbo_dbe              : 1;  /**< [ 41: 41](R/W1S/H) Reads or sets SSO_ERR2[NCBO_DBE]. */
        uint64_t hwsx_gmctl_sbe        : 1;  /**< [ 42: 42](R/W1S/H) Reads or sets SSO_ERR2[HWSX_GMCTL_SBE]. */
        uint64_t hwsx_gmctl_dbe        : 1;  /**< [ 43: 43](R/W1S/H) Reads or sets SSO_ERR2[HWSX_GMCTL_DBE]. */
        uint64_t vhgrp_sbe             : 1;  /**< [ 44: 44](R/W1S/H) Reads or sets SSO_ERR2[VHGRP_SBE]. */
        uint64_t vhgrp_dbe             : 1;  /**< [ 45: 45](R/W1S/H) Reads or sets SSO_ERR2[VHGRP_DBE]. */
        uint64_t pcc_sbe               : 1;  /**< [ 46: 46](R/W1S/H) Reads or sets SSO_ERR2[PCC_SBE]. */
        uint64_t pcc_dbe               : 1;  /**< [ 47: 47](R/W1S/H) Reads or sets SSO_ERR2[PCC_DBE]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_err2_w1s_s cn; */
};
typedef union bdk_sso_err2_w1s bdk_sso_err2_w1s_t;

#define BDK_SSO_ERR2_W1S BDK_SSO_ERR2_W1S_FUNC()
static inline uint64_t BDK_SSO_ERR2_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_ERR2_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001268ll;
    __bdk_csr_fatal("SSO_ERR2_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_ERR2_W1S bdk_sso_err2_w1s_t
#define bustype_BDK_SSO_ERR2_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_ERR2_W1S "SSO_ERR2_W1S"
#define device_bar_BDK_SSO_ERR2_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_ERR2_W1S 0
#define arguments_BDK_SSO_ERR2_W1S -1,-1,-1,-1

/**
 * Register (NCB) sso_grp#_ds_pc
 *
 * SSO PF Hardware-Group Deschedule Performance Counter Register
 * Counts the number of deschedule requests for each hardware-group. Counter rolls over
 * through zero when max value exceeded.
 */
union bdk_sso_grpx_ds_pc
{
    uint64_t u;
    struct bdk_sso_grpx_ds_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Deschedule performance counter. Writes are for diagnostic use only, and defined only when
                                                                 neither work nor GET_WORKs are present in the SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Deschedule performance counter. Writes are for diagnostic use only, and defined only when
                                                                 neither work nor GET_WORKs are present in the SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_grpx_ds_pc_s cn; */
};
typedef union bdk_sso_grpx_ds_pc bdk_sso_grpx_ds_pc_t;

static inline uint64_t BDK_SSO_GRPX_DS_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GRPX_DS_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860020001400ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_GRPX_DS_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GRPX_DS_PC(a) bdk_sso_grpx_ds_pc_t
#define bustype_BDK_SSO_GRPX_DS_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GRPX_DS_PC(a) "SSO_GRPX_DS_PC"
#define device_bar_BDK_SSO_GRPX_DS_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GRPX_DS_PC(a) (a)
#define arguments_BDK_SSO_GRPX_DS_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_grp#_ext_pc
 *
 * SSO PF Hardware-Group External Schedule Performance Counter Register
 * Counts the number of cache lines of WAEs sent to L2/DDR. Counter rolls over through zero when
 * max value exceeded.
 */
union bdk_sso_grpx_ext_pc
{
    uint64_t u;
    struct bdk_sso_grpx_ext_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) External admission queue cache lines written. Each write corresponds to 11 WAEs. Writes
                                                                 are for diagnostic use only, and defined only when neither work nor GET_WORKs are present
                                                                 in the SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) External admission queue cache lines written. Each write corresponds to 11 WAEs. Writes
                                                                 are for diagnostic use only, and defined only when neither work nor GET_WORKs are present
                                                                 in the SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_grpx_ext_pc_s cn; */
};
typedef union bdk_sso_grpx_ext_pc bdk_sso_grpx_ext_pc_t;

static inline uint64_t BDK_SSO_GRPX_EXT_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GRPX_EXT_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860020001100ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_GRPX_EXT_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GRPX_EXT_PC(a) bdk_sso_grpx_ext_pc_t
#define bustype_BDK_SSO_GRPX_EXT_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GRPX_EXT_PC(a) "SSO_GRPX_EXT_PC"
#define device_bar_BDK_SSO_GRPX_EXT_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GRPX_EXT_PC(a) (a)
#define arguments_BDK_SSO_GRPX_EXT_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_grp#_iaq_thr
 *
 * SSO PF Hardware-Group In-unit Admission Queue Threshold Registers
 * These registers contain the thresholds for allocating SSO in-unit admission queue entries.
 */
union bdk_sso_grpx_iaq_thr
{
    uint64_t u;
    struct bdk_sso_grpx_iaq_thr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_61_63        : 3;
        uint64_t grp_cnt               : 13; /**< [ 60: 48](RO/H) Hardware-group's entry count. Number of internal entries allocated to IAQ,
                                                                 conflicted work, or CQ in this hardware-group.

                                                                 Internal:
                                                                 Increments on admission to IAQ, decrements on scheduling into
                                                                 work slot. */
        uint64_t reserved_45_47        : 3;
        uint64_t max_thr               : 13; /**< [ 44: 32](R/W) Max threshold for this internal admission queue. If nonzero, must be \>= [RSVD_THR] + 4.
                                                                 To ensure full streaming performance to all cores, should be at least 208. Must not be
                                                                 changed after traffic is sent to this hardware-group. */
        uint64_t reserved_13_31        : 19;
        uint64_t rsvd_thr              : 13; /**< [ 12:  0](R/W) Threshold for reserved entries for this internal hardware-group queue. Should be
                                                                 at least 0x1 for any hardware-groups that must make forward progress when other
                                                                 hardware-group's work is pending. Updates to this field must also update
                                                                 SSO_AW_ADD[RSVD_FREE]. Must not be changed after traffic is sent to this
                                                                 hardware-group. */
#else /* Word 0 - Little Endian */
        uint64_t rsvd_thr              : 13; /**< [ 12:  0](R/W) Threshold for reserved entries for this internal hardware-group queue. Should be
                                                                 at least 0x1 for any hardware-groups that must make forward progress when other
                                                                 hardware-group's work is pending. Updates to this field must also update
                                                                 SSO_AW_ADD[RSVD_FREE]. Must not be changed after traffic is sent to this
                                                                 hardware-group. */
        uint64_t reserved_13_31        : 19;
        uint64_t max_thr               : 13; /**< [ 44: 32](R/W) Max threshold for this internal admission queue. If nonzero, must be \>= [RSVD_THR] + 4.
                                                                 To ensure full streaming performance to all cores, should be at least 208. Must not be
                                                                 changed after traffic is sent to this hardware-group. */
        uint64_t reserved_45_47        : 3;
        uint64_t grp_cnt               : 13; /**< [ 60: 48](RO/H) Hardware-group's entry count. Number of internal entries allocated to IAQ,
                                                                 conflicted work, or CQ in this hardware-group.

                                                                 Internal:
                                                                 Increments on admission to IAQ, decrements on scheduling into
                                                                 work slot. */
        uint64_t reserved_61_63        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_grpx_iaq_thr_s cn; */
};
typedef union bdk_sso_grpx_iaq_thr bdk_sso_grpx_iaq_thr_t;

static inline uint64_t BDK_SSO_GRPX_IAQ_THR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GRPX_IAQ_THR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860020000000ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_GRPX_IAQ_THR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GRPX_IAQ_THR(a) bdk_sso_grpx_iaq_thr_t
#define bustype_BDK_SSO_GRPX_IAQ_THR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GRPX_IAQ_THR(a) "SSO_GRPX_IAQ_THR"
#define device_bar_BDK_SSO_GRPX_IAQ_THR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GRPX_IAQ_THR(a) (a)
#define arguments_BDK_SSO_GRPX_IAQ_THR(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_grp#_pri
 *
 * SSO PF Hardware-Group Priority Register
 * Controls the priority and hardware-group affinity arbitration for each hardware-group.
 */
union bdk_sso_grpx_pri
{
    uint64_t u;
    struct bdk_sso_grpx_pri_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t wgt_left              : 6;  /**< [ 29: 24](RO/H) Arbitration credits remaining on this hardware-group. */
        uint64_t reserved_22_23        : 2;
        uint64_t weight                : 6;  /**< [ 21: 16](R/W) Arbitration weight to apply to this hardware-group. Must be \>= 0x2. */
        uint64_t reserved_12_15        : 4;
        uint64_t affinity              : 4;  /**< [ 11:  8](R/W) Processor affinity arbitration weight to apply to this hardware-group. If zero, affinity
                                                                 is disabled. A change to [AFFINITY] will not take effect until the old [AFFINITY]'s
                                                                 value loaded into SSO_HWS()_ARB[AFF_LEFT] has drained to zero. */
        uint64_t reserved_3_7          : 5;
        uint64_t pri                   : 3;  /**< [  2:  0](R/W) Priority for this hardware-group relative to other hardware-groups. To prevent a
                                                                 HWS from receiving work use SSO_HWS()_S()_GRPMSK().

                                                                 0x0 = highest priority.
                                                                 0x7 = lowest priority.

                                                                 Changing priority while GET_WORKs are in flight may result in a GET_WORK using either the
                                                                 old or new priority, or a mix thereof. */
#else /* Word 0 - Little Endian */
        uint64_t pri                   : 3;  /**< [  2:  0](R/W) Priority for this hardware-group relative to other hardware-groups. To prevent a
                                                                 HWS from receiving work use SSO_HWS()_S()_GRPMSK().

                                                                 0x0 = highest priority.
                                                                 0x7 = lowest priority.

                                                                 Changing priority while GET_WORKs are in flight may result in a GET_WORK using either the
                                                                 old or new priority, or a mix thereof. */
        uint64_t reserved_3_7          : 5;
        uint64_t affinity              : 4;  /**< [ 11:  8](R/W) Processor affinity arbitration weight to apply to this hardware-group. If zero, affinity
                                                                 is disabled. A change to [AFFINITY] will not take effect until the old [AFFINITY]'s
                                                                 value loaded into SSO_HWS()_ARB[AFF_LEFT] has drained to zero. */
        uint64_t reserved_12_15        : 4;
        uint64_t weight                : 6;  /**< [ 21: 16](R/W) Arbitration weight to apply to this hardware-group. Must be \>= 0x2. */
        uint64_t reserved_22_23        : 2;
        uint64_t wgt_left              : 6;  /**< [ 29: 24](RO/H) Arbitration credits remaining on this hardware-group. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_grpx_pri_s cn; */
};
typedef union bdk_sso_grpx_pri bdk_sso_grpx_pri_t;

static inline uint64_t BDK_SSO_GRPX_PRI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GRPX_PRI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860020000200ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_GRPX_PRI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GRPX_PRI(a) bdk_sso_grpx_pri_t
#define bustype_BDK_SSO_GRPX_PRI(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GRPX_PRI(a) "SSO_GRPX_PRI"
#define device_bar_BDK_SSO_GRPX_PRI(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GRPX_PRI(a) (a)
#define arguments_BDK_SSO_GRPX_PRI(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_grp#_taq_thr
 *
 * SSO PF Hardware-Group Transitory Admission Queue Threshold Registers
 * These registers contain the thresholds for allocating SSO transitory admission queue storage
 * buffers, indexed by hardware-group.
 */
union bdk_sso_grpx_taq_thr
{
    uint64_t u;
    struct bdk_sso_grpx_taq_thr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_59_63        : 5;
        uint64_t grp_cnt               : 11; /**< [ 58: 48](RO/H) Hardware-group's entry count. Number of transitory admission buffers allocated to this group. */
        uint64_t reserved_43_47        : 5;
        uint64_t max_thr               : 11; /**< [ 42: 32](R/W) Max threshold for this transitory admission queue, in buffers of 11
                                                                 entries. Must be \>= 3, must be \>= [RSVD_THR], and to ensure full streaming
                                                                 performance on this hardware-group, should be at least 16 buffers. SSO may
                                                                 exceed this count using unreserved free buffers if and only if persistently
                                                                 backpressured by IOBI. Must not be changed after traffic is sent to this
                                                                 hardware-group. */
        uint64_t reserved_11_31        : 21;
        uint64_t rsvd_thr              : 11; /**< [ 10:  0](R/W) Threshold for reserved entries for this transitory admission queue, in buffers
                                                                 of 11 entries. Must be at least three buffers for any hardware-groups that are to be
                                                                 used. Changes to this field must also update SSO_TAQ_ADD[RSVD_FREE]. Must not be
                                                                 changed after traffic is sent to this hardware-group. */
#else /* Word 0 - Little Endian */
        uint64_t rsvd_thr              : 11; /**< [ 10:  0](R/W) Threshold for reserved entries for this transitory admission queue, in buffers
                                                                 of 11 entries. Must be at least three buffers for any hardware-groups that are to be
                                                                 used. Changes to this field must also update SSO_TAQ_ADD[RSVD_FREE]. Must not be
                                                                 changed after traffic is sent to this hardware-group. */
        uint64_t reserved_11_31        : 21;
        uint64_t max_thr               : 11; /**< [ 42: 32](R/W) Max threshold for this transitory admission queue, in buffers of 11
                                                                 entries. Must be \>= 3, must be \>= [RSVD_THR], and to ensure full streaming
                                                                 performance on this hardware-group, should be at least 16 buffers. SSO may
                                                                 exceed this count using unreserved free buffers if and only if persistently
                                                                 backpressured by IOBI. Must not be changed after traffic is sent to this
                                                                 hardware-group. */
        uint64_t reserved_43_47        : 5;
        uint64_t grp_cnt               : 11; /**< [ 58: 48](RO/H) Hardware-group's entry count. Number of transitory admission buffers allocated to this group. */
        uint64_t reserved_59_63        : 5;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_grpx_taq_thr_s cn; */
};
typedef union bdk_sso_grpx_taq_thr bdk_sso_grpx_taq_thr_t;

static inline uint64_t BDK_SSO_GRPX_TAQ_THR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GRPX_TAQ_THR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860020000100ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_GRPX_TAQ_THR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GRPX_TAQ_THR(a) bdk_sso_grpx_taq_thr_t
#define bustype_BDK_SSO_GRPX_TAQ_THR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GRPX_TAQ_THR(a) "SSO_GRPX_TAQ_THR"
#define device_bar_BDK_SSO_GRPX_TAQ_THR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GRPX_TAQ_THR(a) (a)
#define arguments_BDK_SSO_GRPX_TAQ_THR(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_grp#_ts_pc
 *
 * SSO PF Hardware-Group Tag Switch Performance Counter Register
 * Counts the number of tag switch requests for each hardware-group being switched
 * to. Counter rolls over through zero when max value exceeded.
 */
union bdk_sso_grpx_ts_pc
{
    uint64_t u;
    struct bdk_sso_grpx_ts_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Tag switch performance counter. Writes are for diagnostic use only, and defined only when
                                                                 neither work nor GET_WORKs are present in the SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Tag switch performance counter. Writes are for diagnostic use only, and defined only when
                                                                 neither work nor GET_WORKs are present in the SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_grpx_ts_pc_s cn; */
};
typedef union bdk_sso_grpx_ts_pc bdk_sso_grpx_ts_pc_t;

static inline uint64_t BDK_SSO_GRPX_TS_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GRPX_TS_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860020001300ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_GRPX_TS_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GRPX_TS_PC(a) bdk_sso_grpx_ts_pc_t
#define bustype_BDK_SSO_GRPX_TS_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GRPX_TS_PC(a) "SSO_GRPX_TS_PC"
#define device_bar_BDK_SSO_GRPX_TS_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GRPX_TS_PC(a) (a)
#define arguments_BDK_SSO_GRPX_TS_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_grp#_wa_pc
 *
 * SSO PF Hardware-Group Work-Add Performance Counter Registers
 * Counts the number of add new work requests for each hardware-group. The counter
 * rolls over through zero when the max value exceeded.
 */
union bdk_sso_grpx_wa_pc
{
    uint64_t u;
    struct bdk_sso_grpx_wa_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work add performance counter for hardware-group. Increments when work moves into
                                                                 IAQ. Writes are for diagnostic use only, and defined only when neither work nor
                                                                 GET_WORKs are present in the SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work add performance counter for hardware-group. Increments when work moves into
                                                                 IAQ. Writes are for diagnostic use only, and defined only when neither work nor
                                                                 GET_WORKs are present in the SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_grpx_wa_pc_s cn; */
};
typedef union bdk_sso_grpx_wa_pc bdk_sso_grpx_wa_pc_t;

static inline uint64_t BDK_SSO_GRPX_WA_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GRPX_WA_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860020001200ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_GRPX_WA_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GRPX_WA_PC(a) bdk_sso_grpx_wa_pc_t
#define bustype_BDK_SSO_GRPX_WA_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GRPX_WA_PC(a) "SSO_GRPX_WA_PC"
#define device_bar_BDK_SSO_GRPX_WA_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GRPX_WA_PC(a) (a)
#define arguments_BDK_SSO_GRPX_WA_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_grp#_ws_pc
 *
 * SSO PF Hardware-Group Work-Schedule Performance Counter Registers
 * Counts the number of work schedules for each hardware-group. The counter rolls over
 * through zero when the maximum value is exceeded.
 */
union bdk_sso_grpx_ws_pc
{
    uint64_t u;
    struct bdk_sso_grpx_ws_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work schedule performance counter for hardware-group. Writes are for diagnostic
                                                                 use only, and defined only when neither work nor GET_WORKs are present in the
                                                                 SSO. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Work schedule performance counter for hardware-group. Writes are for diagnostic
                                                                 use only, and defined only when neither work nor GET_WORKs are present in the
                                                                 SSO. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_grpx_ws_pc_s cn; */
};
typedef union bdk_sso_grpx_ws_pc bdk_sso_grpx_ws_pc_t;

static inline uint64_t BDK_SSO_GRPX_WS_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GRPX_WS_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860020001000ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_GRPX_WS_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GRPX_WS_PC(a) bdk_sso_grpx_ws_pc_t
#define bustype_BDK_SSO_GRPX_WS_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GRPX_WS_PC(a) "SSO_GRPX_WS_PC"
#define device_bar_BDK_SSO_GRPX_WS_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GRPX_WS_PC(a) (a)
#define arguments_BDK_SSO_GRPX_WS_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_grp#_xaq_limit
 *
 * SSO PF Hardware-Group External Admission Queue Limit Registers
 */
union bdk_sso_grpx_xaq_limit
{
    uint64_t u;
    struct bdk_sso_grpx_xaq_limit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t xaq_limit             : 33; /**< [ 32:  0](R/W) XAQ limit. Each count holds 11 work entries. If an add work is requested to a
                                                                 group where SSO_VHGRP()_XAQ_CNT[XAQ_CNT] \>= [XAQ_LIMIT], then the add work is
                                                                 dropped and will SSO_VHGRP()_QCTL[ENA] is cleared and SSO_VHGRP()_INT[XAQ_LIMIT] is
                                                                 set. When 0x0, limiting is disabled. Due to pipelining, hardware may exceed this
                                                                 limit by up to the TAQ size (320) entries. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_limit             : 33; /**< [ 32:  0](R/W) XAQ limit. Each count holds 11 work entries. If an add work is requested to a
                                                                 group where SSO_VHGRP()_XAQ_CNT[XAQ_CNT] \>= [XAQ_LIMIT], then the add work is
                                                                 dropped and will SSO_VHGRP()_QCTL[ENA] is cleared and SSO_VHGRP()_INT[XAQ_LIMIT] is
                                                                 set. When 0x0, limiting is disabled. Due to pipelining, hardware may exceed this
                                                                 limit by up to the TAQ size (320) entries. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_grpx_xaq_limit_s cn; */
};
typedef union bdk_sso_grpx_xaq_limit bdk_sso_grpx_xaq_limit_t;

static inline uint64_t BDK_SSO_GRPX_XAQ_LIMIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GRPX_XAQ_LIMIT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860020000220ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_GRPX_XAQ_LIMIT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GRPX_XAQ_LIMIT(a) bdk_sso_grpx_xaq_limit_t
#define bustype_BDK_SSO_GRPX_XAQ_LIMIT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GRPX_XAQ_LIMIT(a) "SSO_GRPX_XAQ_LIMIT"
#define device_bar_BDK_SSO_GRPX_XAQ_LIMIT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GRPX_XAQ_LIMIT(a) (a)
#define arguments_BDK_SSO_GRPX_XAQ_LIMIT(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_gw_eco
 *
 * INTERNAL: SSO PF GW ECO Register
 */
union bdk_sso_gw_eco
{
    uint64_t u;
    struct bdk_sso_gw_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_gw_eco_s cn; */
};
typedef union bdk_sso_gw_eco bdk_sso_gw_eco_t;

#define BDK_SSO_GW_ECO BDK_SSO_GW_ECO_FUNC()
static inline uint64_t BDK_SSO_GW_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GW_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001038ll;
    __bdk_csr_fatal("SSO_GW_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GW_ECO bdk_sso_gw_eco_t
#define bustype_BDK_SSO_GW_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GW_ECO "SSO_GW_ECO"
#define device_bar_BDK_SSO_GW_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GW_ECO 0
#define arguments_BDK_SSO_GW_ECO -1,-1,-1,-1

/**
 * Register (NCB) sso_gwe_cfg
 *
 * SSO PF Get-Work Examiner Configuration Register
 * This register controls the operation of the get-work examiner (GWE).
 */
union bdk_sso_gwe_cfg
{
    uint64_t u;
    struct bdk_sso_gwe_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t dis_wgt_credit        : 1;  /**< [  8:  8](R/W) Disable hardware-group weight credits. When set, groups have infinite weight credit. */
        uint64_t ws_retries            : 8;  /**< [  7:  0](R/W) Work slot retries. When a given work-slot performs this number of retries without
                                                                 successfully finding work then NO_WORK will be returned. Values zero, one, two,
                                                                 and three are reserved. */
#else /* Word 0 - Little Endian */
        uint64_t ws_retries            : 8;  /**< [  7:  0](R/W) Work slot retries. When a given work-slot performs this number of retries without
                                                                 successfully finding work then NO_WORK will be returned. Values zero, one, two,
                                                                 and three are reserved. */
        uint64_t dis_wgt_credit        : 1;  /**< [  8:  8](R/W) Disable hardware-group weight credits. When set, groups have infinite weight credit. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_gwe_cfg_s cn; */
};
typedef union bdk_sso_gwe_cfg bdk_sso_gwe_cfg_t;

#define BDK_SSO_GWE_CFG BDK_SSO_GWE_CFG_FUNC()
static inline uint64_t BDK_SSO_GWE_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GWE_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001098ll;
    __bdk_csr_fatal("SSO_GWE_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GWE_CFG bdk_sso_gwe_cfg_t
#define bustype_BDK_SSO_GWE_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GWE_CFG "SSO_GWE_CFG"
#define device_bar_BDK_SSO_GWE_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GWE_CFG 0
#define arguments_BDK_SSO_GWE_CFG -1,-1,-1,-1

/**
 * Register (NCB) sso_gwe_random
 *
 * SSO PF Get-Work Examiner Random Register
 * This register contains the random search start position for the get-work examiner (GWE).
 */
union bdk_sso_gwe_random
{
    uint64_t u;
    struct bdk_sso_gwe_random_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rnd                   : 16; /**< [ 15:  0](R/W/H) Current random value, with low eight bits indicating first hardware-group to start
                                                                 next get-work search at. Implementation defined as to when changes.
                                                                 For diagnostic use only, must not be zero.

                                                                 Internal:
                                                                 Changes on each work search, even if unsuccessful or retried.

                                                                 Uses 16, 15, 13, 4 tap LFSR (this choice is important to
                                                                 insure even hardware-group probabilities) with the formula:
                                                                 _ grp_to_start_arb_at = RND[7:0];
                                                                 _ RND_next[15:8] = RND[7:0];
                                                                 _ RND_next[7] = ^(RND[15:0] & 0xd008);
                                                                 _ RND_next[6] = ^(RND[15:0] & 0x6804);
                                                                 _ RND_next[5] = ^(RND[15:0] & 0x3402);
                                                                 _ RND_next[4] = ^(RND[15:0] & 0x1a01);
                                                                 _ RND_next[3] = ^(RND[15:0] & 0xdd08);
                                                                 _ RND_next[2] = ^(RND[15:0] & 0x6e84);
                                                                 _ RND_next[1] = ^(RND[15:0] & 0x3742);
                                                                 _ RND_next[0] = ^(RND[15:0] & 0x1ba1); */
#else /* Word 0 - Little Endian */
        uint64_t rnd                   : 16; /**< [ 15:  0](R/W/H) Current random value, with low eight bits indicating first hardware-group to start
                                                                 next get-work search at. Implementation defined as to when changes.
                                                                 For diagnostic use only, must not be zero.

                                                                 Internal:
                                                                 Changes on each work search, even if unsuccessful or retried.

                                                                 Uses 16, 15, 13, 4 tap LFSR (this choice is important to
                                                                 insure even hardware-group probabilities) with the formula:
                                                                 _ grp_to_start_arb_at = RND[7:0];
                                                                 _ RND_next[15:8] = RND[7:0];
                                                                 _ RND_next[7] = ^(RND[15:0] & 0xd008);
                                                                 _ RND_next[6] = ^(RND[15:0] & 0x6804);
                                                                 _ RND_next[5] = ^(RND[15:0] & 0x3402);
                                                                 _ RND_next[4] = ^(RND[15:0] & 0x1a01);
                                                                 _ RND_next[3] = ^(RND[15:0] & 0xdd08);
                                                                 _ RND_next[2] = ^(RND[15:0] & 0x6e84);
                                                                 _ RND_next[1] = ^(RND[15:0] & 0x3742);
                                                                 _ RND_next[0] = ^(RND[15:0] & 0x1ba1); */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_gwe_random_s cn; */
};
typedef union bdk_sso_gwe_random bdk_sso_gwe_random_t;

#define BDK_SSO_GWE_RANDOM BDK_SSO_GWE_RANDOM_FUNC()
static inline uint64_t BDK_SSO_GWE_RANDOM_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_GWE_RANDOM_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000010b0ll;
    __bdk_csr_fatal("SSO_GWE_RANDOM", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_GWE_RANDOM bdk_sso_gwe_random_t
#define bustype_BDK_SSO_GWE_RANDOM BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_GWE_RANDOM "SSO_GWE_RANDOM"
#define device_bar_BDK_SSO_GWE_RANDOM 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_GWE_RANDOM 0
#define arguments_BDK_SSO_GWE_RANDOM -1,-1,-1,-1

/**
 * Register (NCB) sso_hws#_arb
 *
 * SSO PF HWS Arbitration State Register
 * For diagnostic use, returns the arbitration state for each HWS.
 */
union bdk_sso_hwsx_arb
{
    uint64_t u;
    struct bdk_sso_hwsx_arb_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t aff_left              : 4;  /**< [ 19: 16](RO/H) HWS affinity arbitration credits remaining on the last serviced hardware-group. */
        uint64_t reserved_8_15         : 8;
        uint64_t last_grp              : 8;  /**< [  7:  0](RO/H) Last hardware-group number serviced by this HWS. */
#else /* Word 0 - Little Endian */
        uint64_t last_grp              : 8;  /**< [  7:  0](RO/H) Last hardware-group number serviced by this HWS. */
        uint64_t reserved_8_15         : 8;
        uint64_t aff_left              : 4;  /**< [ 19: 16](RO/H) HWS affinity arbitration credits remaining on the last serviced hardware-group. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_hwsx_arb_s cn; */
};
typedef union bdk_sso_hwsx_arb bdk_sso_hwsx_arb_t;

static inline uint64_t BDK_SSO_HWSX_ARB(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_HWSX_ARB(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x860040000100ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSO_HWSX_ARB", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_HWSX_ARB(a) bdk_sso_hwsx_arb_t
#define bustype_BDK_SSO_HWSX_ARB(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_HWSX_ARB(a) "SSO_HWSX_ARB"
#define device_bar_BDK_SSO_HWSX_ARB(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_HWSX_ARB(a) (a)
#define arguments_BDK_SSO_HWSX_ARB(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_hws#_gmctl
 *
 * SSO PF HWS Guest Machine Control Register
 */
union bdk_sso_hwsx_gmctl
{
    uint64_t u;
    struct bdk_sso_hwsx_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t gw_indx_ena           : 1;  /**< [ 16: 16](R/W) Get work indexeded enable.
                                                                 0 = Get work indexed operations for the given HWS will immediately return
                                                                 error response.
                                                                 1 = Get-work indexed operations are allowed. However software can only perform
                                                                 get-work indexed for entries that were previously descheduled by a HWS, and have
                                                                 a vhgroup which has a valid guest-group mapping for the GMID which is performing
                                                                 the get-work indexed.

                                                                 Violation of these conditions may result in unpredictable behavior, including
                                                                 corruption of other GMIDs using SSO. */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) GMID assigned to this VHWS.
                                                                 Used to translate the following CSRs:

                                                                   * SSOW_VHWS()_GRPMSK_CHG()[GGRP].
                                                                   * SSOW_VHWS()_TAG[GGRP].
                                                                   * SSOW_VHWS()_LINKS[GGRP].
                                                                   * SSOW_VHWS()_OP_UPD_WQP_GRP0[GGRP].
                                                                   * SSOW_VHWS()_OP_SWTAG_NOSCHED[GGRP].
                                                                   * SSOW_VHWS()_OP_SWTAG_FULL0[GGRP].
                                                                   * SSOW_VHWS()_OP_SWTAG_DESCHED[GGRP].
                                                                   * SSOW_VHWS()_OP_GET_WORK0[GGRP].
                                                                   * SSOW_VHWS()_OP_GET_WORK0/1's SSOW_GET_WORK_ADDR_S[INDEX_GGRP_MASK].

                                                                 If 0x0, (which normally represents a disabled-GMID), results are unpredictable.

                                                                 Else if 0x1, then the above CSRs will not be translated; the value read from the
                                                                 field above will be a hardware-group number.

                                                                 Else (if not 0x0 nor 0x1), see the CSR descriptions above for the
                                                                 transformations performed; which generally use SSO_PF_MAP(). */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) GMID assigned to this VHWS.
                                                                 Used to translate the following CSRs:

                                                                   * SSOW_VHWS()_GRPMSK_CHG()[GGRP].
                                                                   * SSOW_VHWS()_TAG[GGRP].
                                                                   * SSOW_VHWS()_LINKS[GGRP].
                                                                   * SSOW_VHWS()_OP_UPD_WQP_GRP0[GGRP].
                                                                   * SSOW_VHWS()_OP_SWTAG_NOSCHED[GGRP].
                                                                   * SSOW_VHWS()_OP_SWTAG_FULL0[GGRP].
                                                                   * SSOW_VHWS()_OP_SWTAG_DESCHED[GGRP].
                                                                   * SSOW_VHWS()_OP_GET_WORK0[GGRP].
                                                                   * SSOW_VHWS()_OP_GET_WORK0/1's SSOW_GET_WORK_ADDR_S[INDEX_GGRP_MASK].

                                                                 If 0x0, (which normally represents a disabled-GMID), results are unpredictable.

                                                                 Else if 0x1, then the above CSRs will not be translated; the value read from the
                                                                 field above will be a hardware-group number.

                                                                 Else (if not 0x0 nor 0x1), see the CSR descriptions above for the
                                                                 transformations performed; which generally use SSO_PF_MAP(). */
        uint64_t gw_indx_ena           : 1;  /**< [ 16: 16](R/W) Get work indexeded enable.
                                                                 0 = Get work indexed operations for the given HWS will immediately return
                                                                 error response.
                                                                 1 = Get-work indexed operations are allowed. However software can only perform
                                                                 get-work indexed for entries that were previously descheduled by a HWS, and have
                                                                 a vhgroup which has a valid guest-group mapping for the GMID which is performing
                                                                 the get-work indexed.

                                                                 Violation of these conditions may result in unpredictable behavior, including
                                                                 corruption of other GMIDs using SSO. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_hwsx_gmctl_s cn; */
};
typedef union bdk_sso_hwsx_gmctl bdk_sso_hwsx_gmctl_t;

static inline uint64_t BDK_SSO_HWSX_GMCTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_HWSX_GMCTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x860040000200ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSO_HWSX_GMCTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_HWSX_GMCTL(a) bdk_sso_hwsx_gmctl_t
#define bustype_BDK_SSO_HWSX_GMCTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_HWSX_GMCTL(a) "SSO_HWSX_GMCTL"
#define device_bar_BDK_SSO_HWSX_GMCTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_HWSX_GMCTL(a) (a)
#define arguments_BDK_SSO_HWSX_GMCTL(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_hws#_s#_grpmsk#
 *
 * SSO PF HWS Hardware-Group Mask Registers
 * These registers select which hardware-group(s) a HWS belongs to. There are 2 sets of
 * masks per HWS, each with 1 register corresponding to 64 hardware-groups.
 *
 * Note bit-fields are indexed by hardware-group, not the guest-group; therefore this
 * register should not be exposed as-is to guest drivers.
 */
union bdk_sso_hwsx_sx_grpmskx
{
    uint64_t u;
    struct bdk_sso_hwsx_sx_grpmskx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t grp_msk               : 64; /**< [ 63:  0](R/W) HWS hardware-group mask. A one in any bit position sets the HWS's membership in
                                                                 the corresponding hardware-group for hardware-groups \<63:0\>.

                                                                 A value of 0x0 in GRPMSK for a given HWS prevents the HWS from receiving new
                                                                 work. HWSs that will never receive work should use GRPMSK=0x0; while this
                                                                 setting is not special in SSO, for backward and forward compatibility this may
                                                                 enable reallocation of internal resources to the remaining (nonzero-mask)
                                                                 hardware work-slots.

                                                                 This register is intended only for large-scale save-restore of masks.
                                                                 Individual changes should use SSOW_VHWS()_GRPMSK_CHG().

                                                                 Internal:
                                                                 SSO virtualization will only allow PF access; this register will only be used
                                                                 for paging HWS in or out.  Guests must use SSOW_VHWS()_GRPMSK_CHG(). */
#else /* Word 0 - Little Endian */
        uint64_t grp_msk               : 64; /**< [ 63:  0](R/W) HWS hardware-group mask. A one in any bit position sets the HWS's membership in
                                                                 the corresponding hardware-group for hardware-groups \<63:0\>.

                                                                 A value of 0x0 in GRPMSK for a given HWS prevents the HWS from receiving new
                                                                 work. HWSs that will never receive work should use GRPMSK=0x0; while this
                                                                 setting is not special in SSO, for backward and forward compatibility this may
                                                                 enable reallocation of internal resources to the remaining (nonzero-mask)
                                                                 hardware work-slots.

                                                                 This register is intended only for large-scale save-restore of masks.
                                                                 Individual changes should use SSOW_VHWS()_GRPMSK_CHG().

                                                                 Internal:
                                                                 SSO virtualization will only allow PF access; this register will only be used
                                                                 for paging HWS in or out.  Guests must use SSOW_VHWS()_GRPMSK_CHG(). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_hwsx_sx_grpmskx_s cn; */
};
typedef union bdk_sso_hwsx_sx_grpmskx bdk_sso_hwsx_sx_grpmskx_t;

static inline uint64_t BDK_SSO_HWSX_SX_GRPMSKX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_HWSX_SX_GRPMSKX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=1) && (c==0)))
        return 0x860040001000ll + 0x100000ll * ((a) & 0x1f) + 0x20ll * ((b) & 0x1) + 8ll * ((c) & 0x0);
    __bdk_csr_fatal("SSO_HWSX_SX_GRPMSKX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_SSO_HWSX_SX_GRPMSKX(a,b,c) bdk_sso_hwsx_sx_grpmskx_t
#define bustype_BDK_SSO_HWSX_SX_GRPMSKX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_HWSX_SX_GRPMSKX(a,b,c) "SSO_HWSX_SX_GRPMSKX"
#define device_bar_BDK_SSO_HWSX_SX_GRPMSKX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_HWSX_SX_GRPMSKX(a,b,c) (a)
#define arguments_BDK_SSO_HWSX_SX_GRPMSKX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) sso_ient#_grp
 *
 * SSO PF Internal Entry Hardware-Group Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_ientx_grp
{
    uint64_t u;
    struct bdk_sso_ientx_grp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t head                  : 1;  /**< [ 61: 61](RO/H) SSO entry is at the head of a tag chain that is descheduled. */
        uint64_t nosched               : 1;  /**< [ 60: 60](RO/H) The nosched bit for the SSO entry. */
        uint64_t reserved_56_59        : 4;
        uint64_t grp                   : 8;  /**< [ 55: 48](RO/H) Hardware-group of the SSO entry. This register is typically only for diagnostic
                                                                 use; however if this value is delivered to guest drivers, [GRP] must be
                                                                 converted to a guest-group by the hypervisor software. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t grp                   : 8;  /**< [ 55: 48](RO/H) Hardware-group of the SSO entry. This register is typically only for diagnostic
                                                                 use; however if this value is delivered to guest drivers, [GRP] must be
                                                                 converted to a guest-group by the hypervisor software. */
        uint64_t reserved_56_59        : 4;
        uint64_t nosched               : 1;  /**< [ 60: 60](RO/H) The nosched bit for the SSO entry. */
        uint64_t head                  : 1;  /**< [ 61: 61](RO/H) SSO entry is at the head of a tag chain that is descheduled. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ientx_grp_s cn; */
};
typedef union bdk_sso_ientx_grp bdk_sso_ientx_grp_t;

static inline uint64_t BDK_SSO_IENTX_GRP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IENTX_GRP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x8600a0020000ll + 8ll * ((a) & 0x3ff);
    __bdk_csr_fatal("SSO_IENTX_GRP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IENTX_GRP(a) bdk_sso_ientx_grp_t
#define bustype_BDK_SSO_IENTX_GRP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IENTX_GRP(a) "SSO_IENTX_GRP"
#define device_bar_BDK_SSO_IENTX_GRP(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IENTX_GRP(a) (a)
#define arguments_BDK_SSO_IENTX_GRP(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_ient#_links
 *
 * SSO PF Internal Entry Links Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_ientx_links
{
    uint64_t u;
    struct bdk_sso_ientx_links_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_26_63        : 38;
        uint64_t prev_index            : 10; /**< [ 25: 16](RO/H) The previous entry in the tag chain. Unpredictable if the entry is at the head of the list
                                                                 or the head of a conflicted tag chain. */
        uint64_t reserved_11_15        : 5;
        uint64_t next_index_vld        : 1;  /**< [ 10: 10](RO/H) The [NEXT_INDEX] is valid. Unpredictable unless the entry is the tail entry of an atomic tag chain. */
        uint64_t next_index            : 10; /**< [  9:  0](RO/H) The next entry in the tag chain or conflicted tag chain. Unpredictable if the entry is at
                                                                 the tail of the list. */
#else /* Word 0 - Little Endian */
        uint64_t next_index            : 10; /**< [  9:  0](RO/H) The next entry in the tag chain or conflicted tag chain. Unpredictable if the entry is at
                                                                 the tail of the list. */
        uint64_t next_index_vld        : 1;  /**< [ 10: 10](RO/H) The [NEXT_INDEX] is valid. Unpredictable unless the entry is the tail entry of an atomic tag chain. */
        uint64_t reserved_11_15        : 5;
        uint64_t prev_index            : 10; /**< [ 25: 16](RO/H) The previous entry in the tag chain. Unpredictable if the entry is at the head of the list
                                                                 or the head of a conflicted tag chain. */
        uint64_t reserved_26_63        : 38;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ientx_links_s cn; */
};
typedef union bdk_sso_ientx_links bdk_sso_ientx_links_t;

static inline uint64_t BDK_SSO_IENTX_LINKS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IENTX_LINKS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x8600a0060000ll + 8ll * ((a) & 0x3ff);
    __bdk_csr_fatal("SSO_IENTX_LINKS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IENTX_LINKS(a) bdk_sso_ientx_links_t
#define bustype_BDK_SSO_IENTX_LINKS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IENTX_LINKS(a) "SSO_IENTX_LINKS"
#define device_bar_BDK_SSO_IENTX_LINKS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IENTX_LINKS(a) (a)
#define arguments_BDK_SSO_IENTX_LINKS(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_ient#_pendtag
 *
 * SSO PF Internal Entry Pending Tag Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_ientx_pendtag
{
    uint64_t u;
    struct bdk_sso_ientx_pendtag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_38_63        : 26;
        uint64_t pend_switch           : 1;  /**< [ 37: 37](RO/H) Set when there is a pending non-UNTAGGED SWTAG or SWTAG_FULL and the SSO entry has not
                                                                 left the list for the original tag. */
        uint64_t reserved_34_36        : 3;
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The next tag type for the new tag list when PEND_SWITCH is set. Enumerated by SSO_TT_E. */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The next tag for the new tag list when PEND_SWITCH is set. */
#else /* Word 0 - Little Endian */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The next tag for the new tag list when PEND_SWITCH is set. */
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The next tag type for the new tag list when PEND_SWITCH is set. Enumerated by SSO_TT_E. */
        uint64_t reserved_34_36        : 3;
        uint64_t pend_switch           : 1;  /**< [ 37: 37](RO/H) Set when there is a pending non-UNTAGGED SWTAG or SWTAG_FULL and the SSO entry has not
                                                                 left the list for the original tag. */
        uint64_t reserved_38_63        : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ientx_pendtag_s cn; */
};
typedef union bdk_sso_ientx_pendtag bdk_sso_ientx_pendtag_t;

static inline uint64_t BDK_SSO_IENTX_PENDTAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IENTX_PENDTAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x8600a0040000ll + 8ll * ((a) & 0x3ff);
    __bdk_csr_fatal("SSO_IENTX_PENDTAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IENTX_PENDTAG(a) bdk_sso_ientx_pendtag_t
#define bustype_BDK_SSO_IENTX_PENDTAG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IENTX_PENDTAG(a) "SSO_IENTX_PENDTAG"
#define device_bar_BDK_SSO_IENTX_PENDTAG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IENTX_PENDTAG(a) (a)
#define arguments_BDK_SSO_IENTX_PENDTAG(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_ient#_qlinks
 *
 * SSO PF Internal Queue Links Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_ientx_qlinks
{
    uint64_t u;
    struct bdk_sso_ientx_qlinks_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t next_index            : 12; /**< [ 11:  0](RO/H) The next entry in the AQ/CQ/DQ. */
#else /* Word 0 - Little Endian */
        uint64_t next_index            : 12; /**< [ 11:  0](RO/H) The next entry in the AQ/CQ/DQ. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ientx_qlinks_s cn; */
};
typedef union bdk_sso_ientx_qlinks bdk_sso_ientx_qlinks_t;

static inline uint64_t BDK_SSO_IENTX_QLINKS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IENTX_QLINKS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x8600a0080000ll + 8ll * ((a) & 0x3ff);
    __bdk_csr_fatal("SSO_IENTX_QLINKS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IENTX_QLINKS(a) bdk_sso_ientx_qlinks_t
#define bustype_BDK_SSO_IENTX_QLINKS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IENTX_QLINKS(a) "SSO_IENTX_QLINKS"
#define device_bar_BDK_SSO_IENTX_QLINKS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IENTX_QLINKS(a) (a)
#define arguments_BDK_SSO_IENTX_QLINKS(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_ient#_tag
 *
 * SSO PF Internal Entry Tag Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_ientx_tag
{
    uint64_t u;
    struct bdk_sso_ientx_tag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_39_63        : 25;
        uint64_t tailc                 : 1;  /**< [ 38: 38](RO/H) The SSO entry is the tail of tag chain that is conflicted. No conflicted chain exists if
                                                                 [TAIL] is also set on the same entry. */
        uint64_t tail                  : 1;  /**< [ 37: 37](RO/H) The SSO entry is the tail of tag chain that is descheduled.
                                                                 Internal:
                                                                 Read from the SOC. */
        uint64_t reserved_34_36        : 3;
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type of the SSO entry. Enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag of the SSO entry. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag of the SSO entry. */
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type of the SSO entry. Enumerated by SSO_TT_E. */
        uint64_t reserved_34_36        : 3;
        uint64_t tail                  : 1;  /**< [ 37: 37](RO/H) The SSO entry is the tail of tag chain that is descheduled.
                                                                 Internal:
                                                                 Read from the SOC. */
        uint64_t tailc                 : 1;  /**< [ 38: 38](RO/H) The SSO entry is the tail of tag chain that is conflicted. No conflicted chain exists if
                                                                 [TAIL] is also set on the same entry. */
        uint64_t reserved_39_63        : 25;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ientx_tag_s cn; */
};
typedef union bdk_sso_ientx_tag bdk_sso_ientx_tag_t;

static inline uint64_t BDK_SSO_IENTX_TAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IENTX_TAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x8600a0000000ll + 8ll * ((a) & 0x3ff);
    __bdk_csr_fatal("SSO_IENTX_TAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IENTX_TAG(a) bdk_sso_ientx_tag_t
#define bustype_BDK_SSO_IENTX_TAG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IENTX_TAG(a) "SSO_IENTX_TAG"
#define device_bar_BDK_SSO_IENTX_TAG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IENTX_TAG(a) (a)
#define arguments_BDK_SSO_IENTX_TAG(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_ient#_wqp
 *
 * SSO PF Internal Entry WQP Registers
 * Returns unit memory status for an index.
 */
union bdk_sso_ientx_wqp
{
    uint64_t u;
    struct bdk_sso_ientx_wqp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) Work queue IOVA held in the SSO entry.
                                                                 Bits \<63:49\> are a sign extension of \<48\>.  Bits \<2:0\> are 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) Work queue IOVA held in the SSO entry.
                                                                 Bits \<63:49\> are a sign extension of \<48\>.  Bits \<2:0\> are 0x0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ientx_wqp_s cn; */
};
typedef union bdk_sso_ientx_wqp bdk_sso_ientx_wqp_t;

static inline uint64_t BDK_SSO_IENTX_WQP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IENTX_WQP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1023))
        return 0x8600a00a0000ll + 8ll * ((a) & 0x3ff);
    __bdk_csr_fatal("SSO_IENTX_WQP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IENTX_WQP(a) bdk_sso_ientx_wqp_t
#define bustype_BDK_SSO_IENTX_WQP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IENTX_WQP(a) "SSO_IENTX_WQP"
#define device_bar_BDK_SSO_IENTX_WQP(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IENTX_WQP(a) (a)
#define arguments_BDK_SSO_IENTX_WQP(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_ipl_conf#
 *
 * SSO PF Hardware-Group Conflicted List State Registers
 * Returns list status for the conflicted list indexed by hardware-group. Register
 * fields are identical to those in SSO_IPL_IAQ() above.
 */
union bdk_sso_ipl_confx
{
    uint64_t u;
    struct bdk_sso_ipl_confx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t reserved_25           : 1;
        uint64_t queue_head            : 12; /**< [ 24: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t reserved_12           : 1;
        uint64_t queue_tail            : 12; /**< [ 11:  0](RO/H) Index of entry at the tail of the queue. */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 12; /**< [ 11:  0](RO/H) Index of entry at the tail of the queue. */
        uint64_t reserved_12           : 1;
        uint64_t queue_head            : 12; /**< [ 24: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t reserved_25           : 1;
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ipl_confx_s cn; */
};
typedef union bdk_sso_ipl_confx bdk_sso_ipl_confx_t;

static inline uint64_t BDK_SSO_IPL_CONFX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IPL_CONFX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860080080000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_IPL_CONFX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IPL_CONFX(a) bdk_sso_ipl_confx_t
#define bustype_BDK_SSO_IPL_CONFX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IPL_CONFX(a) "SSO_IPL_CONFX"
#define device_bar_BDK_SSO_IPL_CONFX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IPL_CONFX(a) (a)
#define arguments_BDK_SSO_IPL_CONFX(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_ipl_desched#
 *
 * SSO PF Hardware-Group Deschedule List State Registers
 * Returns list status for the deschedule list indexed by hardware-group. Register
 * fields are identical to those in SSO_IPL_IAQ() above.
 */
union bdk_sso_ipl_deschedx
{
    uint64_t u;
    struct bdk_sso_ipl_deschedx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t reserved_25           : 1;
        uint64_t queue_head            : 12; /**< [ 24: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t reserved_12           : 1;
        uint64_t queue_tail            : 12; /**< [ 11:  0](RO/H) Index of entry at the tail of the queue. */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 12; /**< [ 11:  0](RO/H) Index of entry at the tail of the queue. */
        uint64_t reserved_12           : 1;
        uint64_t queue_head            : 12; /**< [ 24: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t reserved_25           : 1;
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ipl_deschedx_s cn; */
};
typedef union bdk_sso_ipl_deschedx bdk_sso_ipl_deschedx_t;

static inline uint64_t BDK_SSO_IPL_DESCHEDX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IPL_DESCHEDX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860080060000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_IPL_DESCHEDX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IPL_DESCHEDX(a) bdk_sso_ipl_deschedx_t
#define bustype_BDK_SSO_IPL_DESCHEDX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IPL_DESCHEDX(a) "SSO_IPL_DESCHEDX"
#define device_bar_BDK_SSO_IPL_DESCHEDX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IPL_DESCHEDX(a) (a)
#define arguments_BDK_SSO_IPL_DESCHEDX(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_ipl_free#
 *
 * SSO PF Free List State Registers
 * Returns list status.
 */
union bdk_sso_ipl_freex
{
    uint64_t u;
    struct bdk_sso_ipl_freex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t qnum_head             : 3;  /**< [ 61: 59](RO/H) Subqueue with current head. */
        uint64_t qnum_tail             : 3;  /**< [ 58: 56](RO/H) Subqueue for next tail. */
        uint64_t reserved_28_55        : 28;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in this subqueue. */
        uint64_t reserved_23_26        : 4;
        uint64_t queue_head            : 10; /**< [ 22: 13](RO/H) Index of entry at the head of this subqueue. */
        uint64_t reserved_10_12        : 3;
        uint64_t queue_tail            : 10; /**< [  9:  0](RO/H) Index of entry at the tail of this subqueue. */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 10; /**< [  9:  0](RO/H) Index of entry at the tail of this subqueue. */
        uint64_t reserved_10_12        : 3;
        uint64_t queue_head            : 10; /**< [ 22: 13](RO/H) Index of entry at the head of this subqueue. */
        uint64_t reserved_23_26        : 4;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in this subqueue. */
        uint64_t reserved_28_55        : 28;
        uint64_t qnum_tail             : 3;  /**< [ 58: 56](RO/H) Subqueue for next tail. */
        uint64_t qnum_head             : 3;  /**< [ 61: 59](RO/H) Subqueue with current head. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ipl_freex_s cn; */
};
typedef union bdk_sso_ipl_freex bdk_sso_ipl_freex_t;

static inline uint64_t BDK_SSO_IPL_FREEX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IPL_FREEX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=4))
        return 0x860080000000ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("SSO_IPL_FREEX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IPL_FREEX(a) bdk_sso_ipl_freex_t
#define bustype_BDK_SSO_IPL_FREEX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IPL_FREEX(a) "SSO_IPL_FREEX"
#define device_bar_BDK_SSO_IPL_FREEX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IPL_FREEX(a) (a)
#define arguments_BDK_SSO_IPL_FREEX(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_ipl_iaq#
 *
 * SSO PF Hardware-Group IAQ List State Registers
 * Returns list status for the internal admission queue indexed by hardware-group.
 */
union bdk_sso_ipl_iaqx
{
    uint64_t u;
    struct bdk_sso_ipl_iaqx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t reserved_25           : 1;
        uint64_t queue_head            : 12; /**< [ 24: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t reserved_12           : 1;
        uint64_t queue_tail            : 12; /**< [ 11:  0](RO/H) Index of entry at the tail of the queue. */
#else /* Word 0 - Little Endian */
        uint64_t queue_tail            : 12; /**< [ 11:  0](RO/H) Index of entry at the tail of the queue. */
        uint64_t reserved_12           : 1;
        uint64_t queue_head            : 12; /**< [ 24: 13](RO/H) Index of entry at the head of the queue. */
        uint64_t reserved_25           : 1;
        uint64_t queue_one             : 1;  /**< [ 26: 26](RO/H) Exactly one valid entry is in the queue. */
        uint64_t queue_val             : 1;  /**< [ 27: 27](RO/H) One or more valid entries are in the queue. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ipl_iaqx_s cn; */
};
typedef union bdk_sso_ipl_iaqx bdk_sso_ipl_iaqx_t;

static inline uint64_t BDK_SSO_IPL_IAQX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_IPL_IAQX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860080040000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_IPL_IAQX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_IPL_IAQX(a) bdk_sso_ipl_iaqx_t
#define bustype_BDK_SSO_IPL_IAQX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_IPL_IAQX(a) "SSO_IPL_IAQX"
#define device_bar_BDK_SSO_IPL_IAQX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_IPL_IAQX(a) (a)
#define arguments_BDK_SSO_IPL_IAQX(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_aq_cnt
 *
 * SSO LF Guest Group Admission Queue Count Registers
 */
union bdk_sso_lf_ggrp_aq_cnt
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_aq_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t aq_cnt                : 33; /**< [ 32:  0](RO/H) Number of total in-unit, transitional and external admission queue entries for this guest group. */
#else /* Word 0 - Little Endian */
        uint64_t aq_cnt                : 33; /**< [ 32:  0](RO/H) Number of total in-unit, transitional and external admission queue entries for this guest group. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_aq_cnt_s cn; */
};
typedef union bdk_sso_lf_ggrp_aq_cnt bdk_sso_lf_ggrp_aq_cnt_t;

#define BDK_SSO_LF_GGRP_AQ_CNT BDK_SSO_LF_GGRP_AQ_CNT_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_AQ_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_AQ_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8402007001c0ll;
    __bdk_csr_fatal("SSO_LF_GGRP_AQ_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_AQ_CNT bdk_sso_lf_ggrp_aq_cnt_t
#define bustype_BDK_SSO_LF_GGRP_AQ_CNT BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_AQ_CNT "SSO_LF_GGRP_AQ_CNT"
#define device_bar_BDK_SSO_LF_GGRP_AQ_CNT 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_AQ_CNT 0
#define arguments_BDK_SSO_LF_GGRP_AQ_CNT -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_aq_thr
 *
 * SSO LF Guest Group Total Admission Queue Threshold Register
 */
union bdk_sso_lf_ggrp_aq_thr
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_aq_thr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t aq_thr                : 33; /**< [ 32:  0](R/W) Total admission queue entry threshold. Compared against SSO_LF_GGRP_AQ_CNT for
                                                                 triggering AQ interrupts. */
#else /* Word 0 - Little Endian */
        uint64_t aq_thr                : 33; /**< [ 32:  0](R/W) Total admission queue entry threshold. Compared against SSO_LF_GGRP_AQ_CNT for
                                                                 triggering AQ interrupts. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_aq_thr_s cn; */
};
typedef union bdk_sso_lf_ggrp_aq_thr bdk_sso_lf_ggrp_aq_thr_t;

#define BDK_SSO_LF_GGRP_AQ_THR BDK_SSO_LF_GGRP_AQ_THR_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_AQ_THR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_AQ_THR_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8402007001e0ll;
    __bdk_csr_fatal("SSO_LF_GGRP_AQ_THR", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_AQ_THR bdk_sso_lf_ggrp_aq_thr_t
#define bustype_BDK_SSO_LF_GGRP_AQ_THR BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_AQ_THR "SSO_LF_GGRP_AQ_THR"
#define device_bar_BDK_SSO_LF_GGRP_AQ_THR 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_AQ_THR 0
#define arguments_BDK_SSO_LF_GGRP_AQ_THR -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_exe_dis
 *
 * SSO LF Guest Group Interrupt Temporary Disable Register
 * Contains the per-guest group temporary interrupt disable.  This register
 * must be written before the interrupt is enabled or cleared. For more
 * information on this register, refer to Interrupts.
 */
union bdk_sso_lf_ggrp_exe_dis
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_exe_dis_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1S/H) Executable interrupt temporary disable. Corresponding SSO_LF_GGRP_INT[EXE_INT]
                                                                 bit cannot be set due to IAQ_CNT/IAQ_THR check when this bit is set. [EXE_DIS]
                                                                 is cleared by hardware whenever:
                                                                 * SSO_LF_GGRP_INT_CNT[IAQ_CNT] is zero.
                                                                 * Or, the hardware decrements the time counter for this guest group to zero, i.e.
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_AF_WQ_INT_PC[PC] is
                                                                 equal to zero. */
        uint64_t reserved_0_62         : 63;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_62         : 63;
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1S/H) Executable interrupt temporary disable. Corresponding SSO_LF_GGRP_INT[EXE_INT]
                                                                 bit cannot be set due to IAQ_CNT/IAQ_THR check when this bit is set. [EXE_DIS]
                                                                 is cleared by hardware whenever:
                                                                 * SSO_LF_GGRP_INT_CNT[IAQ_CNT] is zero.
                                                                 * Or, the hardware decrements the time counter for this guest group to zero, i.e.
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_AF_WQ_INT_PC[PC] is
                                                                 equal to zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_exe_dis_s cn; */
};
typedef union bdk_sso_lf_ggrp_exe_dis bdk_sso_lf_ggrp_exe_dis_t;

#define BDK_SSO_LF_GGRP_EXE_DIS BDK_SSO_LF_GGRP_EXE_DIS_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_EXE_DIS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_EXE_DIS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700080ll;
    __bdk_csr_fatal("SSO_LF_GGRP_EXE_DIS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_EXE_DIS bdk_sso_lf_ggrp_exe_dis_t
#define bustype_BDK_SSO_LF_GGRP_EXE_DIS BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_EXE_DIS "SSO_LF_GGRP_EXE_DIS"
#define device_bar_BDK_SSO_LF_GGRP_EXE_DIS 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_EXE_DIS 0
#define arguments_BDK_SSO_LF_GGRP_EXE_DIS -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_int
 *
 * SSO LF Guest Group Interrupt Register
 * Contains the per-guest group interrupts and is used to clear these
 * interrupts. For more information on this register, refer to Interrupts.
 */
union bdk_sso_lf_ggrp_int
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1C/H) Guest group XAQ exceeded allocation limit error; add-works to this GGRP may
                                                                 be dropped. Set when SSO_LF_GGRP_XAQ_CNT[XAQ_CNT] \>=
                                                                 SSO_AF_HWGRP()_XAQ_LIMIT[XAQ_LIMIT]. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1C/H) Work-executable interrupt. Generally used to indicate work is waiting for software.
                                                                 Set by hardware whenever:

                                                                 * SSO_LF_GGRP_INT_CNT[IAQ_CNT] \>= SSO_LF_GGRP_INT_THR[IAQ_THR] and [IAQ_THR] != 0
                                                                 and SSO_LF_GGRP_EXE_DIS[EXE_DIS] is clear.

                                                                 * SSO_LF_GGRP_INT_CNT[DS_CNT] \>= SSO_LF_GGRP_INT_THR[DS_THR] and [DS_THR] != 0.

                                                                 * SSO_LF_GGRP_INT_CNT[CQ_CNT] \>= SSO_LF_GGRP_INT_THR[CQ_THR] and [CQ_THR] != 0.

                                                                 * SSO_LF_GGRP_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_AF_WQ_INT_PC[PC] is
                                                                 equal to zero and SSO_LF_GGRP_INT_THR[TC_EN] is set and at least one of the following is
                                                                 true:
                                                                   o SSO_LF_GGRP_INT_CNT[IAQ_CNT] \> 0.
                                                                   o SSO_LF_GGRP_INT_CNT[DS_CNT] \> 0.
                                                                   o SSO_LF_GGRP_INT_CNT[CQ_CNT] \> 0. */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1C/H) AQ threshold interrupt. Set if SSO_LF_GGRP_AQ_CNT changes, and the
                                                                 resulting value is equal to SSO_LF_GGRP_AQ_THR. */
#else /* Word 0 - Little Endian */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1C/H) AQ threshold interrupt. Set if SSO_LF_GGRP_AQ_CNT changes, and the
                                                                 resulting value is equal to SSO_LF_GGRP_AQ_THR. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1C/H) Work-executable interrupt. Generally used to indicate work is waiting for software.
                                                                 Set by hardware whenever:

                                                                 * SSO_LF_GGRP_INT_CNT[IAQ_CNT] \>= SSO_LF_GGRP_INT_THR[IAQ_THR] and [IAQ_THR] != 0
                                                                 and SSO_LF_GGRP_EXE_DIS[EXE_DIS] is clear.

                                                                 * SSO_LF_GGRP_INT_CNT[DS_CNT] \>= SSO_LF_GGRP_INT_THR[DS_THR] and [DS_THR] != 0.

                                                                 * SSO_LF_GGRP_INT_CNT[CQ_CNT] \>= SSO_LF_GGRP_INT_THR[CQ_THR] and [CQ_THR] != 0.

                                                                 * SSO_LF_GGRP_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_AF_WQ_INT_PC[PC] is
                                                                 equal to zero and SSO_LF_GGRP_INT_THR[TC_EN] is set and at least one of the following is
                                                                 true:
                                                                   o SSO_LF_GGRP_INT_CNT[IAQ_CNT] \> 0.
                                                                   o SSO_LF_GGRP_INT_CNT[DS_CNT] \> 0.
                                                                   o SSO_LF_GGRP_INT_CNT[CQ_CNT] \> 0. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1C/H) Guest group XAQ exceeded allocation limit error; add-works to this GGRP may
                                                                 be dropped. Set when SSO_LF_GGRP_XAQ_CNT[XAQ_CNT] \>=
                                                                 SSO_AF_HWGRP()_XAQ_LIMIT[XAQ_LIMIT]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_int_s cn; */
};
typedef union bdk_sso_lf_ggrp_int bdk_sso_lf_ggrp_int_t;

#define BDK_SSO_LF_GGRP_INT BDK_SSO_LF_GGRP_INT_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700100ll;
    __bdk_csr_fatal("SSO_LF_GGRP_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_INT bdk_sso_lf_ggrp_int_t
#define bustype_BDK_SSO_LF_GGRP_INT BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_INT "SSO_LF_GGRP_INT"
#define device_bar_BDK_SSO_LF_GGRP_INT 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_INT 0
#define arguments_BDK_SSO_LF_GGRP_INT -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_int_cnt
 *
 * SSO LF Guest Group Work-Queue Interrupt Count Registers
 * These registers contain a read-only copy of the counts used to trigger work-queue interrupts
 * (one per guest group). For more information on this register, refer to Interrupts.
 */
union bdk_sso_lf_ggrp_int_cnt
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_int_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t tc_cnt                : 14; /**< [ 61: 48](RO/H) Time counter current value. Hardware sets this field to the value of
                                                                 SSO_LF_GGRP_INT_THR[TC_THR] whenever:
                                                                 * Corresponding SSO_LF_GGRP_INT_CNT[IAQ_CNT, DS_CNT, CQ_CNT] are all equal to zero.
                                                                 * Corresponding SSO_LF_GGRP_INT[EXE_INT] is written with a one to clear by software.
                                                                 * Corresponding SSO_LF_GGRP_EXE_DIS[EXE_DIS] is written with a one to set by software.
                                                                 * Corresponding SSO_LF_GGRP_INT_THR is written by software.
                                                                 * [TC_CNT] is equal to one and periodic counter SSO_AF_WQ_INT_PC[PC] is equal to zero.

                                                                 Otherwise, hardware decrements this field whenever the periodic counter SSO_AF_WQ_INT_PC[PC]
                                                                 is equal to zero. This field is zero whenever SSO_LF_GGRP_INT_THR[TC_THR] is equal to zero. */
        uint64_t reserved_46_47        : 2;
        uint64_t cq_cnt                : 14; /**< [ 45: 32](RO/H) Conflicted queue executable count. */
        uint64_t reserved_30_31        : 2;
        uint64_t ds_cnt                : 14; /**< [ 29: 16](RO/H) Deschedule executable count. */
        uint64_t reserved_14_15        : 2;
        uint64_t iaq_cnt               : 14; /**< [ 13:  0](RO/H) Work-queue entries for this in-unit admission queue. */
#else /* Word 0 - Little Endian */
        uint64_t iaq_cnt               : 14; /**< [ 13:  0](RO/H) Work-queue entries for this in-unit admission queue. */
        uint64_t reserved_14_15        : 2;
        uint64_t ds_cnt                : 14; /**< [ 29: 16](RO/H) Deschedule executable count. */
        uint64_t reserved_30_31        : 2;
        uint64_t cq_cnt                : 14; /**< [ 45: 32](RO/H) Conflicted queue executable count. */
        uint64_t reserved_46_47        : 2;
        uint64_t tc_cnt                : 14; /**< [ 61: 48](RO/H) Time counter current value. Hardware sets this field to the value of
                                                                 SSO_LF_GGRP_INT_THR[TC_THR] whenever:
                                                                 * Corresponding SSO_LF_GGRP_INT_CNT[IAQ_CNT, DS_CNT, CQ_CNT] are all equal to zero.
                                                                 * Corresponding SSO_LF_GGRP_INT[EXE_INT] is written with a one to clear by software.
                                                                 * Corresponding SSO_LF_GGRP_EXE_DIS[EXE_DIS] is written with a one to set by software.
                                                                 * Corresponding SSO_LF_GGRP_INT_THR is written by software.
                                                                 * [TC_CNT] is equal to one and periodic counter SSO_AF_WQ_INT_PC[PC] is equal to zero.

                                                                 Otherwise, hardware decrements this field whenever the periodic counter SSO_AF_WQ_INT_PC[PC]
                                                                 is equal to zero. This field is zero whenever SSO_LF_GGRP_INT_THR[TC_THR] is equal to zero. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_int_cnt_s cn9; */
    /* struct bdk_sso_lf_ggrp_int_cnt_s cn96xx; */
    struct bdk_sso_lf_ggrp_int_cnt_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t tc_cnt                : 14; /**< [ 61: 48](RO/H) Time counter current value. Hardware sets this field to the value of
                                                                 SSO_LF_GGRP_INT_THR[TC_THR] whenever:
                                                                 * Corresponding SSO_LF_GGRP_INT_CNT[IAQ_CNT, DS_CNT, CQ_CNT] are all equal to zero.
                                                                 * Corresponding SSO_LF_GGRP_INT[EXE_INT] is written with a one to clear by software.
                                                                 * Corresponding SSO_LF_GGRP_EXE_DIS[EXE_DIS] is written with a one to set by software.
                                                                 * Corresponding SSO_LF_GGRP_INT_THR is written by software.
                                                                 * [TC_CNT] is equal to one and periodic counter SSO_AF_WQ_INT_PC[PC] is equal to zero.

                                                                 Otherwise, hardware decrements this field whenever the periodic counter SSO_AF_WQ_INT_PC[PC]
                                                                 is equal to zero. This field is zero whenever SSO_LF_GGRP_INT_THR[TC_THR] is equal to zero.

                                                                 Internal:
                                                                 (48..`SSO_IDX_W+48) */
        uint64_t reserved_46_47        : 2;
        uint64_t cq_cnt                : 14; /**< [ 45: 32](RO/H) Conflicted queue executable count.
                                                                 Internal:
                                                                 (32..`SSO_IDX_W+32) */
        uint64_t reserved_30_31        : 2;
        uint64_t ds_cnt                : 14; /**< [ 29: 16](RO/H) Deschedule executable count.
                                                                 Internal:
                                                                 (16..`SSO_IDX_W+16) */
        uint64_t reserved_14_15        : 2;
        uint64_t iaq_cnt               : 14; /**< [ 13:  0](RO/H) Work-queue entries for this in-unit admission queue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W) */
#else /* Word 0 - Little Endian */
        uint64_t iaq_cnt               : 14; /**< [ 13:  0](RO/H) Work-queue entries for this in-unit admission queue.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W) */
        uint64_t reserved_14_15        : 2;
        uint64_t ds_cnt                : 14; /**< [ 29: 16](RO/H) Deschedule executable count.
                                                                 Internal:
                                                                 (16..`SSO_IDX_W+16) */
        uint64_t reserved_30_31        : 2;
        uint64_t cq_cnt                : 14; /**< [ 45: 32](RO/H) Conflicted queue executable count.
                                                                 Internal:
                                                                 (32..`SSO_IDX_W+32) */
        uint64_t reserved_46_47        : 2;
        uint64_t tc_cnt                : 14; /**< [ 61: 48](RO/H) Time counter current value. Hardware sets this field to the value of
                                                                 SSO_LF_GGRP_INT_THR[TC_THR] whenever:
                                                                 * Corresponding SSO_LF_GGRP_INT_CNT[IAQ_CNT, DS_CNT, CQ_CNT] are all equal to zero.
                                                                 * Corresponding SSO_LF_GGRP_INT[EXE_INT] is written with a one to clear by software.
                                                                 * Corresponding SSO_LF_GGRP_EXE_DIS[EXE_DIS] is written with a one to set by software.
                                                                 * Corresponding SSO_LF_GGRP_INT_THR is written by software.
                                                                 * [TC_CNT] is equal to one and periodic counter SSO_AF_WQ_INT_PC[PC] is equal to zero.

                                                                 Otherwise, hardware decrements this field whenever the periodic counter SSO_AF_WQ_INT_PC[PC]
                                                                 is equal to zero. This field is zero whenever SSO_LF_GGRP_INT_THR[TC_THR] is equal to zero.

                                                                 Internal:
                                                                 (48..`SSO_IDX_W+48) */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_lf_ggrp_int_cnt_s cnf95xx; */
    /* struct bdk_sso_lf_ggrp_int_cnt_s loki; */
};
typedef union bdk_sso_lf_ggrp_int_cnt bdk_sso_lf_ggrp_int_cnt_t;

#define BDK_SSO_LF_GGRP_INT_CNT BDK_SSO_LF_GGRP_INT_CNT_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_INT_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_INT_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700180ll;
    __bdk_csr_fatal("SSO_LF_GGRP_INT_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_INT_CNT bdk_sso_lf_ggrp_int_cnt_t
#define bustype_BDK_SSO_LF_GGRP_INT_CNT BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_INT_CNT "SSO_LF_GGRP_INT_CNT"
#define device_bar_BDK_SSO_LF_GGRP_INT_CNT 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_INT_CNT 0
#define arguments_BDK_SSO_LF_GGRP_INT_CNT -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_int_ena_w1c
 *
 * SSO LF Guest Group Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_sso_lf_ggrp_int_ena_w1c
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSO_LF_GGRP_INT[XAQ_LIMIT]. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSO_LF_GGRP_INT[EXE_INT]. */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSO_LF_GGRP_INT[AQ_INT]. */
#else /* Word 0 - Little Endian */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSO_LF_GGRP_INT[AQ_INT]. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSO_LF_GGRP_INT[EXE_INT]. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSO_LF_GGRP_INT[XAQ_LIMIT]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_int_ena_w1c_s cn; */
};
typedef union bdk_sso_lf_ggrp_int_ena_w1c bdk_sso_lf_ggrp_int_ena_w1c_t;

#define BDK_SSO_LF_GGRP_INT_ENA_W1C BDK_SSO_LF_GGRP_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700118ll;
    __bdk_csr_fatal("SSO_LF_GGRP_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_INT_ENA_W1C bdk_sso_lf_ggrp_int_ena_w1c_t
#define bustype_BDK_SSO_LF_GGRP_INT_ENA_W1C BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_INT_ENA_W1C "SSO_LF_GGRP_INT_ENA_W1C"
#define device_bar_BDK_SSO_LF_GGRP_INT_ENA_W1C 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_INT_ENA_W1C 0
#define arguments_BDK_SSO_LF_GGRP_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_int_ena_w1s
 *
 * SSO LF Guest Group Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_sso_lf_ggrp_int_ena_w1s
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSO_LF_GGRP_INT[XAQ_LIMIT]. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSO_LF_GGRP_INT[EXE_INT]. */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSO_LF_GGRP_INT[AQ_INT]. */
#else /* Word 0 - Little Endian */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSO_LF_GGRP_INT[AQ_INT]. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSO_LF_GGRP_INT[EXE_INT]. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSO_LF_GGRP_INT[XAQ_LIMIT]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_int_ena_w1s_s cn; */
};
typedef union bdk_sso_lf_ggrp_int_ena_w1s bdk_sso_lf_ggrp_int_ena_w1s_t;

#define BDK_SSO_LF_GGRP_INT_ENA_W1S BDK_SSO_LF_GGRP_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700110ll;
    __bdk_csr_fatal("SSO_LF_GGRP_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_INT_ENA_W1S bdk_sso_lf_ggrp_int_ena_w1s_t
#define bustype_BDK_SSO_LF_GGRP_INT_ENA_W1S BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_INT_ENA_W1S "SSO_LF_GGRP_INT_ENA_W1S"
#define device_bar_BDK_SSO_LF_GGRP_INT_ENA_W1S 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_INT_ENA_W1S 0
#define arguments_BDK_SSO_LF_GGRP_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_int_thr
 *
 * SSO LF Guest Group Work-Queue Interrupt Threshold Registers
 * These registers contain the thresholds for enabling and setting work-queue interrupts (one per
 * guest group). For more information on this register, refer to Interrupts.
 */
union bdk_sso_lf_ggrp_int_thr
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_int_thr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t tc_en                 : 1;  /**< [ 63: 63](R/W) Time counter interrupt enable for this guest group. This field must be zero
                                                                 when [TC_THR] is zero. */
        uint64_t reserved_61_62        : 2;
        uint64_t tc_thr                : 13; /**< [ 60: 48](R/W) Time counter interrupt threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT]. When this field is equal to zero,
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT] is zero. */
        uint64_t reserved_46_47        : 2;
        uint64_t cq_thr                : 14; /**< [ 45: 32](R/W) Conflicted queue count threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[CQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled. */
        uint64_t reserved_30_31        : 2;
        uint64_t ds_thr                : 14; /**< [ 29: 16](R/W) Deschedule count threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[DS_CNT]. When
                                                                 this field is zero, the threshold interrupt is disabled. */
        uint64_t reserved_14_15        : 2;
        uint64_t iaq_thr               : 14; /**< [ 13:  0](R/W) In-unit admission queue threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[IAQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled. */
#else /* Word 0 - Little Endian */
        uint64_t iaq_thr               : 14; /**< [ 13:  0](R/W) In-unit admission queue threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[IAQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled. */
        uint64_t reserved_14_15        : 2;
        uint64_t ds_thr                : 14; /**< [ 29: 16](R/W) Deschedule count threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[DS_CNT]. When
                                                                 this field is zero, the threshold interrupt is disabled. */
        uint64_t reserved_30_31        : 2;
        uint64_t cq_thr                : 14; /**< [ 45: 32](R/W) Conflicted queue count threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[CQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled. */
        uint64_t reserved_46_47        : 2;
        uint64_t tc_thr                : 13; /**< [ 60: 48](R/W) Time counter interrupt threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT]. When this field is equal to zero,
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT] is zero. */
        uint64_t reserved_61_62        : 2;
        uint64_t tc_en                 : 1;  /**< [ 63: 63](R/W) Time counter interrupt enable for this guest group. This field must be zero
                                                                 when [TC_THR] is zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_int_thr_s cn9; */
    /* struct bdk_sso_lf_ggrp_int_thr_s cn96xx; */
    struct bdk_sso_lf_ggrp_int_thr_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t tc_en                 : 1;  /**< [ 63: 63](R/W) Time counter interrupt enable for this guest group. This field must be zero
                                                                 when [TC_THR] is zero. */
        uint64_t reserved_61_62        : 2;
        uint64_t tc_thr                : 13; /**< [ 60: 48](R/W) Time counter interrupt threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT]. When this field is equal to zero,
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT] is zero.

                                                                 Internal:
                                                                 (48..`SSO_IDX_W+48-1) */
        uint64_t reserved_46_47        : 2;
        uint64_t cq_thr                : 14; /**< [ 45: 32](R/W) Conflicted queue count threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[CQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled.

                                                                 Internal:
                                                                 (32..`SSO_IDX_W+32) */
        uint64_t reserved_30_31        : 2;
        uint64_t ds_thr                : 14; /**< [ 29: 16](R/W) Deschedule count threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[DS_CNT]. When
                                                                 this field is zero, the threshold interrupt is disabled.

                                                                 Internal:
                                                                 (16..`SSO_IDX_W+16) */
        uint64_t reserved_14_15        : 2;
        uint64_t iaq_thr               : 14; /**< [ 13:  0](R/W) In-unit admission queue threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[IAQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled.

                                                                 Internal:
                                                                 (0..`SSO_IDX_W) */
#else /* Word 0 - Little Endian */
        uint64_t iaq_thr               : 14; /**< [ 13:  0](R/W) In-unit admission queue threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[IAQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled.

                                                                 Internal:
                                                                 (0..`SSO_IDX_W) */
        uint64_t reserved_14_15        : 2;
        uint64_t ds_thr                : 14; /**< [ 29: 16](R/W) Deschedule count threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[DS_CNT]. When
                                                                 this field is zero, the threshold interrupt is disabled.

                                                                 Internal:
                                                                 (16..`SSO_IDX_W+16) */
        uint64_t reserved_30_31        : 2;
        uint64_t cq_thr                : 14; /**< [ 45: 32](R/W) Conflicted queue count threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[CQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled.

                                                                 Internal:
                                                                 (32..`SSO_IDX_W+32) */
        uint64_t reserved_46_47        : 2;
        uint64_t tc_thr                : 13; /**< [ 60: 48](R/W) Time counter interrupt threshold for this guest group. Compared against
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT]. When this field is equal to zero,
                                                                 SSO_LF_GGRP_INT_CNT[TC_CNT] is zero.

                                                                 Internal:
                                                                 (48..`SSO_IDX_W+48-1) */
        uint64_t reserved_61_62        : 2;
        uint64_t tc_en                 : 1;  /**< [ 63: 63](R/W) Time counter interrupt enable for this guest group. This field must be zero
                                                                 when [TC_THR] is zero. */
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_lf_ggrp_int_thr_s cnf95xx; */
    /* struct bdk_sso_lf_ggrp_int_thr_s loki; */
};
typedef union bdk_sso_lf_ggrp_int_thr bdk_sso_lf_ggrp_int_thr_t;

#define BDK_SSO_LF_GGRP_INT_THR BDK_SSO_LF_GGRP_INT_THR_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_INT_THR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_INT_THR_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700140ll;
    __bdk_csr_fatal("SSO_LF_GGRP_INT_THR", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_INT_THR bdk_sso_lf_ggrp_int_thr_t
#define bustype_BDK_SSO_LF_GGRP_INT_THR BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_INT_THR "SSO_LF_GGRP_INT_THR"
#define device_bar_BDK_SSO_LF_GGRP_INT_THR 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_INT_THR 0
#define arguments_BDK_SSO_LF_GGRP_INT_THR -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_int_w1s
 *
 * SSO LF Guest Group Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_sso_lf_ggrp_int_w1s
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSO_LF_GGRP_INT[XAQ_LIMIT]. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSO_LF_GGRP_INT[EXE_INT]. */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSO_LF_GGRP_INT[AQ_INT]. */
#else /* Word 0 - Little Endian */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSO_LF_GGRP_INT[AQ_INT]. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSO_LF_GGRP_INT[EXE_INT]. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSO_LF_GGRP_INT[XAQ_LIMIT]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_int_w1s_s cn; */
};
typedef union bdk_sso_lf_ggrp_int_w1s bdk_sso_lf_ggrp_int_w1s_t;

#define BDK_SSO_LF_GGRP_INT_W1S BDK_SSO_LF_GGRP_INT_W1S_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700108ll;
    __bdk_csr_fatal("SSO_LF_GGRP_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_INT_W1S bdk_sso_lf_ggrp_int_w1s_t
#define bustype_BDK_SSO_LF_GGRP_INT_W1S BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_INT_W1S "SSO_LF_GGRP_INT_W1S"
#define device_bar_BDK_SSO_LF_GGRP_INT_W1S 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_INT_W1S 0
#define arguments_BDK_SSO_LF_GGRP_INT_W1S -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_misc_cnt
 *
 * SSO LF Guest Group Desched Pending Register
 */
union bdk_sso_lf_ggrp_misc_cnt
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_misc_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t ds_pend_sw            : 14; /**< [ 13:  0](R/W/H) Number of descheduled pending switches. */
#else /* Word 0 - Little Endian */
        uint64_t ds_pend_sw            : 14; /**< [ 13:  0](R/W/H) Number of descheduled pending switches. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_misc_cnt_s cn9; */
    /* struct bdk_sso_lf_ggrp_misc_cnt_s cn96xx; */
    struct bdk_sso_lf_ggrp_misc_cnt_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t ds_pend_sw            : 14; /**< [ 13:  0](R/W/H) Number of descheduled pending switches.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W) */
#else /* Word 0 - Little Endian */
        uint64_t ds_pend_sw            : 14; /**< [ 13:  0](R/W/H) Number of descheduled pending switches.
                                                                 Internal:
                                                                 (0..`SSO_IDX_W) */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_sso_lf_ggrp_misc_cnt_s cnf95xx; */
    /* struct bdk_sso_lf_ggrp_misc_cnt_s loki; */
};
typedef union bdk_sso_lf_ggrp_misc_cnt bdk_sso_lf_ggrp_misc_cnt_t;

#define BDK_SSO_LF_GGRP_MISC_CNT BDK_SSO_LF_GGRP_MISC_CNT_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_MISC_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_MISC_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700200ll;
    __bdk_csr_fatal("SSO_LF_GGRP_MISC_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_MISC_CNT bdk_sso_lf_ggrp_misc_cnt_t
#define bustype_BDK_SSO_LF_GGRP_MISC_CNT BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_MISC_CNT "SSO_LF_GGRP_MISC_CNT"
#define device_bar_BDK_SSO_LF_GGRP_MISC_CNT 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_MISC_CNT 0
#define arguments_BDK_SSO_LF_GGRP_MISC_CNT -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_op_add_work0
 *
 * SSO LF Guest Group Add Work Register 0
 * See SSO_LF_GGRP_OP_ADD_WORK1.
 */
union bdk_sso_lf_ggrp_op_add_work0
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_op_add_work0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) Tag type to add, enumerated by SSO_TT_E.  Must not be EMPTY. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag of the work-queue entry, if [TT] is ATOMIC or ORDERED. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag of the work-queue entry, if [TT] is ATOMIC or ORDERED. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) Tag type to add, enumerated by SSO_TT_E.  Must not be EMPTY. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_op_add_work0_s cn; */
};
typedef union bdk_sso_lf_ggrp_op_add_work0 bdk_sso_lf_ggrp_op_add_work0_t;

#define BDK_SSO_LF_GGRP_OP_ADD_WORK0 BDK_SSO_LF_GGRP_OP_ADD_WORK0_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_OP_ADD_WORK0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_OP_ADD_WORK0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700000ll;
    __bdk_csr_fatal("SSO_LF_GGRP_OP_ADD_WORK0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_OP_ADD_WORK0 bdk_sso_lf_ggrp_op_add_work0_t
#define bustype_BDK_SSO_LF_GGRP_OP_ADD_WORK0 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_OP_ADD_WORK0 "SSO_LF_GGRP_OP_ADD_WORK0"
#define device_bar_BDK_SSO_LF_GGRP_OP_ADD_WORK0 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_OP_ADD_WORK0 0
#define arguments_BDK_SSO_LF_GGRP_OP_ADD_WORK0 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_op_add_work1
 *
 * SSO LF Guest Group Add Work Register 1
 * A write to this register performs an add work. Either:
 * * A single-transaction 128-bit store (STP) is used to SSO_LF_GGRP_OP_ADD_WORK0 and
 * SSO_LF_GGRP_OP_ADD_WORK1 to perform a single add work with both a tag and work
 * pointer.
 * * Or, a single 64-bit store is used to SSO_LF_GGRP_OP_ADD_WORK1 to perform a single
 * add work which is untagged.
 * * Writing SSO_LF_GGRP_OP_ADD_WORK0 without a simultaneous write to
 * SSO_LF_GGRP_OP_ADD_WORK1 as described above is an error.
 */
union bdk_sso_lf_ggrp_op_add_work1
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_op_add_work1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) LF IOVA of the work-queue entry.  Bits \<63:53\> and \<2:0\> are ignored. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) LF IOVA of the work-queue entry.  Bits \<63:53\> and \<2:0\> are ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_op_add_work1_s cn; */
};
typedef union bdk_sso_lf_ggrp_op_add_work1 bdk_sso_lf_ggrp_op_add_work1_t;

#define BDK_SSO_LF_GGRP_OP_ADD_WORK1 BDK_SSO_LF_GGRP_OP_ADD_WORK1_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_OP_ADD_WORK1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_OP_ADD_WORK1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700008ll;
    __bdk_csr_fatal("SSO_LF_GGRP_OP_ADD_WORK1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_OP_ADD_WORK1 bdk_sso_lf_ggrp_op_add_work1_t
#define bustype_BDK_SSO_LF_GGRP_OP_ADD_WORK1 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_OP_ADD_WORK1 "SSO_LF_GGRP_OP_ADD_WORK1"
#define device_bar_BDK_SSO_LF_GGRP_OP_ADD_WORK1 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_OP_ADD_WORK1 0
#define arguments_BDK_SSO_LF_GGRP_OP_ADD_WORK1 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_qctl
 *
 * SSO Admission Queue Control Register
 */
union bdk_sso_lf_ggrp_qctl
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_qctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) GGRP enable. If clear, add work is dropped.

                                                                 Cleared by hardware when SSO_AF_HWGRP()_XAQ_LIMIT[XAQ_LIMIT] \>=
                                                                 SSO_LF_GGRP_XAQ_CNT[XAQ_CNT]. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) GGRP enable. If clear, add work is dropped.

                                                                 Cleared by hardware when SSO_AF_HWGRP()_XAQ_LIMIT[XAQ_LIMIT] \>=
                                                                 SSO_LF_GGRP_XAQ_CNT[XAQ_CNT]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_qctl_s cn; */
};
typedef union bdk_sso_lf_ggrp_qctl bdk_sso_lf_ggrp_qctl_t;

#define BDK_SSO_LF_GGRP_QCTL BDK_SSO_LF_GGRP_QCTL_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_QCTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_QCTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200700020ll;
    __bdk_csr_fatal("SSO_LF_GGRP_QCTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_QCTL bdk_sso_lf_ggrp_qctl_t
#define bustype_BDK_SSO_LF_GGRP_QCTL BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_QCTL "SSO_LF_GGRP_QCTL"
#define device_bar_BDK_SSO_LF_GGRP_QCTL 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_QCTL 0
#define arguments_BDK_SSO_LF_GGRP_QCTL -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) sso_lf_ggrp_xaq_cnt
 *
 * SSO LF Guest Group External Queue Count Registers
 */
union bdk_sso_lf_ggrp_xaq_cnt
{
    uint64_t u;
    struct bdk_sso_lf_ggrp_xaq_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t xaq_cnt               : 33; /**< [ 32:  0](RO/H) Number of external admission queue entries for this guest group. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_cnt               : 33; /**< [ 32:  0](RO/H) Number of external admission queue entries for this guest group. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_lf_ggrp_xaq_cnt_s cn; */
};
typedef union bdk_sso_lf_ggrp_xaq_cnt bdk_sso_lf_ggrp_xaq_cnt_t;

#define BDK_SSO_LF_GGRP_XAQ_CNT BDK_SSO_LF_GGRP_XAQ_CNT_FUNC()
static inline uint64_t BDK_SSO_LF_GGRP_XAQ_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_LF_GGRP_XAQ_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8402007001b0ll;
    __bdk_csr_fatal("SSO_LF_GGRP_XAQ_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_LF_GGRP_XAQ_CNT bdk_sso_lf_ggrp_xaq_cnt_t
#define bustype_BDK_SSO_LF_GGRP_XAQ_CNT BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSO_LF_GGRP_XAQ_CNT "SSO_LF_GGRP_XAQ_CNT"
#define device_bar_BDK_SSO_LF_GGRP_XAQ_CNT 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSO_LF_GGRP_XAQ_CNT 0
#define arguments_BDK_SSO_LF_GGRP_XAQ_CNT -1,-1,-1,-1

/**
 * Register (NCB) sso_nos_cnt
 *
 * SSO PF No-schedule Count Register
 * Contains the number of work-queue entries on the no-schedule list.
 */
union bdk_sso_nos_cnt
{
    uint64_t u;
    struct bdk_sso_nos_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t nos_cnt               : 13; /**< [ 12:  0](RO/H) Number of work-queue entries on the no-schedule list. */
#else /* Word 0 - Little Endian */
        uint64_t nos_cnt               : 13; /**< [ 12:  0](RO/H) Number of work-queue entries on the no-schedule list. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_nos_cnt_s cn; */
};
typedef union bdk_sso_nos_cnt bdk_sso_nos_cnt_t;

#define BDK_SSO_NOS_CNT BDK_SSO_NOS_CNT_FUNC()
static inline uint64_t BDK_SSO_NOS_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_NOS_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001040ll;
    __bdk_csr_fatal("SSO_NOS_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_NOS_CNT bdk_sso_nos_cnt_t
#define bustype_BDK_SSO_NOS_CNT BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_NOS_CNT "SSO_NOS_CNT"
#define device_bar_BDK_SSO_NOS_CNT 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_NOS_CNT 0
#define arguments_BDK_SSO_NOS_CNT -1,-1,-1,-1

/**
 * Register (NCB) sso_nw_tim
 *
 * SSO PF New-Work Timer Period Register
 * Sets the minimum period for a new-work-request timeout. The period is specified in n-1
 * notation, with the increment value of 1024 clock cycles. Thus, a value of 0x0 in this register
 * translates to 1024 cycles, 0x1 translates to 2048 cycles, 0x2 translates to 3072 cycles, etc.
 */
union bdk_sso_nw_tim
{
    uint64_t u;
    struct bdk_sso_nw_tim_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t nw_tim                : 10; /**< [  9:  0](R/W) New-work-timer period.
                                                                 0x0 = 1024 clock cycles.
                                                                 0x1 = 2048 clock cycles.
                                                                 0x2 = 3072 clock cycles.
                                                                 _ ... etc. */
#else /* Word 0 - Little Endian */
        uint64_t nw_tim                : 10; /**< [  9:  0](R/W) New-work-timer period.
                                                                 0x0 = 1024 clock cycles.
                                                                 0x1 = 2048 clock cycles.
                                                                 0x2 = 3072 clock cycles.
                                                                 _ ... etc. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_nw_tim_s cn; */
};
typedef union bdk_sso_nw_tim bdk_sso_nw_tim_t;

#define BDK_SSO_NW_TIM BDK_SSO_NW_TIM_FUNC()
static inline uint64_t BDK_SSO_NW_TIM_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_NW_TIM_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001028ll;
    __bdk_csr_fatal("SSO_NW_TIM", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_NW_TIM bdk_sso_nw_tim_t
#define bustype_BDK_SSO_NW_TIM BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_NW_TIM "SSO_NW_TIM"
#define device_bar_BDK_SSO_NW_TIM 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_NW_TIM 0
#define arguments_BDK_SSO_NW_TIM -1,-1,-1,-1

/**
 * Register (NCB) sso_page_cnt
 *
 * SSO PF In-use Page Count Register
 */
union bdk_sso_page_cnt
{
    uint64_t u;
    struct bdk_sso_page_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cnt                   : 32; /**< [ 31:  0](R/W/H) In-use page count. Number of pages SSO has allocated and not yet returned. Excludes unused
                                                                 pointers cached in SSO. Hardware updates this register. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 32; /**< [ 31:  0](R/W/H) In-use page count. Number of pages SSO has allocated and not yet returned. Excludes unused
                                                                 pointers cached in SSO. Hardware updates this register. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_page_cnt_s cn; */
};
typedef union bdk_sso_page_cnt bdk_sso_page_cnt_t;

#define BDK_SSO_PAGE_CNT BDK_SSO_PAGE_CNT_FUNC()
static inline uint64_t BDK_SSO_PAGE_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PAGE_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001090ll;
    __bdk_csr_fatal("SSO_PAGE_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PAGE_CNT bdk_sso_page_cnt_t
#define bustype_BDK_SSO_PAGE_CNT BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PAGE_CNT "SSO_PAGE_CNT"
#define device_bar_BDK_SSO_PAGE_CNT 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_PAGE_CNT 0
#define arguments_BDK_SSO_PAGE_CNT -1,-1,-1,-1

/**
 * Register (NCB) sso_pf_map#
 *
 * SSO PF VF Mapping Registers
 * These registers map GMIDs and guest-groups to hardware-groups, and GMIDs and
 * hardware-groups to GGRPs. An entry must not be changed if there is traffic in flight
 * that may potentially match that entry's GMID/VHGRP/GGRP.
 *
 * The mapping algorithm depends on the type of operation:
 *
 * * Coprocessors make add-work requests with a GMID and guest-group, which
 *   is translated to a hardware-group as follows:
 *
 *   o Regardless of this mapping table, GMID 0x0 is always invalid and use of 0x0 will
 *     cause a SSO_ERR0[GMID0] error and the add-work is dropped.
 *
 *   o else, regardless of this mapping table, GMID 0x1 is always a one-to-one mapping
 *     of GGRP into VHGRP.
 *
 *   o else (excluding GMID 0x0 and 0x1), a lookup is performed across all SSO_PF_MAP()
 *     entries, looking for a entry where [VALID] is set, the request's GMID = entry's
 *     [GMID], and the request's GGRP = entry's [GGRP].
 *
 *   o if the lookup hits a single entry, the resulting hardware-group is from the
 *     matching entry's [VHGRP].
 *
 *   o if the lookup does not hit any entries a SSO_ERR0[GMID_UNMAP] error is reported
 *     and the add-work is dropped.
 *
 *   o if the lookup hits duplicate entries a SSO_ERR0[GMID_MULTI] error is reported
 *     and the add-work is dropped.
 *
 * * HWS operations make guest-group requests, where the GMID is from
 *   SSO_HWS()_GMCTL[GMID] and the GGRP is from SSOW_VHWS()_GRPMSK_CHG()[GGRP],
 *   SSOW_VHWS()_OP_GET_WORK0[GGRP], SSOW_VHWS()_OP_UPD_WQP_GRP0[GGRP],
 *   SSOW_VHWS()_OP_SWTAG_NOSCHED[GGRP], SSOW_VHWS()_OP_SWTAG_FULL0[GGRP],
 *   SSOW_VHWS()_OP_SWTAG_DESCHED[GGRP], or SSOW_VHWS()_OP_GET_WORK0/1's
 *   SSOW_GET_WORK_ADDR_S[INDEX_GGRP_MASK]. These are translated to a hardware-group as
 *   follows:
 *
 *   o Regardless of this mapping table, using GMID 0x0 is unpredictable.
 *
 *   o else, regardless of this mapping table, GMID 0x1 is always a one-to-one mapping
 *     of GGRP into VHGRP.
 *
 *   o else (excluding GMID 0x0 and 0x1), a lookup is performed across all SSO_PF_MAP()
 *     entries, looking for a entry where [VALID] is set, the request's GMID = entry's
 *     [GMID], and the request's GGRP = entry's [GGRP].
 *
 *   o if the lookup hits a single entry, the resulting hardware-group is from the
 *     matching entry's [VHGRP].
 *
 *   o if the lookup does not hit any entries a SSO_ERR2[WS_UNMAP] error is reported
 *     and the group-mask change or switch-tag is dropped.
 *
 *   o if the lookup hits duplicate entries a SSO_ERR2[WS_MULTI] error is reported and
 *     the group-mask change or switch-tag is dropped.
 *
 * * HWS reads, where the GMID is from SSO_HWS()_GMCTL[GMID], return a guest-group in
 *   SSOW_VHWS()_TAG[GGRP] and SSOW_VHWS()_LINKS[GGRP]. These are translated from the
 *   HWS's storage of a hardware-group to the operation's read value's guest-group
 *   follows:
 *
 *   o Regardless of this mapping table, using GMID 0x0 is unprefictable.
 *
 *   o else, regardless of this mapping table, GMID 0x1 is always a one-to-one mapping
 *     of VHGRP into GGRP.
 *
 *   o else (excluding GMID 0x0 and 0x1), a lookup is performed across all SSO_PF_MAP()
 *     entries, looking for a entry where [VALID] is set, the request's GMID = entry's
 *     [GMID], and the request's VHGRP = entry's [VHGRP].
 *
 *   o if the lookup hits a single entry, the resulting guest-group is from the
 *     matching entry's [GGRP].
 *
 *   o if the lookup does not hit any entriesa a SSO_ERR2[WS_UNMAP] error is reported
 *     and the GGRP returned is the VHGRP.
 *
 *  o if the lookup hits duplicate entries a SSO_ERR2[WS_MULTI] error is reported and
 *     the GGRP returned is the VHGRP.
 */
union bdk_sso_pf_mapx
{
    uint64_t u;
    struct bdk_sso_pf_mapx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W) This entry is valid for matching. See register description. */
        uint64_t reserved_38_62        : 25;
        uint64_t vhgrp                 : 6;  /**< [ 37: 32](R/W) Entry's hardware-group. See register description. */
        uint64_t reserved_26_31        : 6;
        uint64_t ggrp                  : 10; /**< [ 25: 16](R/W) Entry's guest-group. See register description. */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Entry's guest machine ID. See register description. */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Entry's guest machine ID. See register description. */
        uint64_t ggrp                  : 10; /**< [ 25: 16](R/W) Entry's guest-group. See register description. */
        uint64_t reserved_26_31        : 6;
        uint64_t vhgrp                 : 6;  /**< [ 37: 32](R/W) Entry's hardware-group. See register description. */
        uint64_t reserved_38_62        : 25;
        uint64_t valid                 : 1;  /**< [ 63: 63](R/W) This entry is valid for matching. See register description. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_pf_mapx_s cn; */
};
typedef union bdk_sso_pf_mapx bdk_sso_pf_mapx_t;

static inline uint64_t BDK_SSO_PF_MAPX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PF_MAPX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=71))
        return 0x860000004000ll + 8ll * ((a) & 0x7f);
    __bdk_csr_fatal("SSO_PF_MAPX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PF_MAPX(a) bdk_sso_pf_mapx_t
#define bustype_BDK_SSO_PF_MAPX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PF_MAPX(a) "SSO_PF_MAPX"
#define device_bar_BDK_SSO_PF_MAPX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_PF_MAPX(a) (a)
#define arguments_BDK_SSO_PF_MAPX(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_pf_mbox_ena_w1c#
 *
 * SSO PF Mailbox Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_sso_pf_mbox_ena_w1cx
{
    uint64_t u;
    struct bdk_sso_pf_mbox_ena_w1cx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for SSO_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for SSO_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_pf_mbox_ena_w1cx_s cn; */
};
typedef union bdk_sso_pf_mbox_ena_w1cx bdk_sso_pf_mbox_ena_w1cx_t;

static inline uint64_t BDK_SSO_PF_MBOX_ENA_W1CX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PF_MBOX_ENA_W1CX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x860000001480ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_PF_MBOX_ENA_W1CX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PF_MBOX_ENA_W1CX(a) bdk_sso_pf_mbox_ena_w1cx_t
#define bustype_BDK_SSO_PF_MBOX_ENA_W1CX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PF_MBOX_ENA_W1CX(a) "SSO_PF_MBOX_ENA_W1CX"
#define device_bar_BDK_SSO_PF_MBOX_ENA_W1CX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_PF_MBOX_ENA_W1CX(a) (a)
#define arguments_BDK_SSO_PF_MBOX_ENA_W1CX(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_pf_mbox_ena_w1s#
 *
 * SSO PF Mailbox Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_sso_pf_mbox_ena_w1sx
{
    uint64_t u;
    struct bdk_sso_pf_mbox_ena_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for SSO_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for SSO_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_pf_mbox_ena_w1sx_s cn; */
};
typedef union bdk_sso_pf_mbox_ena_w1sx bdk_sso_pf_mbox_ena_w1sx_t;

static inline uint64_t BDK_SSO_PF_MBOX_ENA_W1SX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PF_MBOX_ENA_W1SX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x8600000014c0ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_PF_MBOX_ENA_W1SX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PF_MBOX_ENA_W1SX(a) bdk_sso_pf_mbox_ena_w1sx_t
#define bustype_BDK_SSO_PF_MBOX_ENA_W1SX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PF_MBOX_ENA_W1SX(a) "SSO_PF_MBOX_ENA_W1SX"
#define device_bar_BDK_SSO_PF_MBOX_ENA_W1SX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_PF_MBOX_ENA_W1SX(a) (a)
#define arguments_BDK_SSO_PF_MBOX_ENA_W1SX(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_pf_mbox_int#
 *
 * SSO PF Mailbox Interrupt Registers
 */
union bdk_sso_pf_mbox_intx
{
    uint64_t u;
    struct bdk_sso_pf_mbox_intx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF. Each bit is set when the associated
                                                                 SSO_VHGRP(0..63)_PF_MBOX(1) is written. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF. Each bit is set when the associated
                                                                 SSO_VHGRP(0..63)_PF_MBOX(1) is written. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_pf_mbox_intx_s cn; */
};
typedef union bdk_sso_pf_mbox_intx bdk_sso_pf_mbox_intx_t;

static inline uint64_t BDK_SSO_PF_MBOX_INTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PF_MBOX_INTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x860000001400ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_PF_MBOX_INTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PF_MBOX_INTX(a) bdk_sso_pf_mbox_intx_t
#define bustype_BDK_SSO_PF_MBOX_INTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PF_MBOX_INTX(a) "SSO_PF_MBOX_INTX"
#define device_bar_BDK_SSO_PF_MBOX_INTX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_PF_MBOX_INTX(a) (a)
#define arguments_BDK_SSO_PF_MBOX_INTX(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_pf_mbox_int_w1s#
 *
 * SSO PF Mailbox Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_sso_pf_mbox_int_w1sx
{
    uint64_t u;
    struct bdk_sso_pf_mbox_int_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets SSO_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_pf_mbox_int_w1sx_s cn; */
};
typedef union bdk_sso_pf_mbox_int_w1sx bdk_sso_pf_mbox_int_w1sx_t;

static inline uint64_t BDK_SSO_PF_MBOX_INT_W1SX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PF_MBOX_INT_W1SX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x860000001440ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_PF_MBOX_INT_W1SX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PF_MBOX_INT_W1SX(a) bdk_sso_pf_mbox_int_w1sx_t
#define bustype_BDK_SSO_PF_MBOX_INT_W1SX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PF_MBOX_INT_W1SX(a) "SSO_PF_MBOX_INT_W1SX"
#define device_bar_BDK_SSO_PF_MBOX_INT_W1SX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_PF_MBOX_INT_W1SX(a) (a)
#define arguments_BDK_SSO_PF_MBOX_INT_W1SX(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_pf_msix_pba#
 *
 * SSO PF MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the SSO_PF_INT_VEC_E
 * enumeration.
 */
union bdk_sso_pf_msix_pbax
{
    uint64_t u;
    struct bdk_sso_pf_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated SSO_PF_MSIX_VEC()_CTL, enumerated by
                                                                 SSO_PF_INT_VEC_E. Bits that have no associated SSO_PF_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated SSO_PF_MSIX_VEC()_CTL, enumerated by
                                                                 SSO_PF_INT_VEC_E. Bits that have no associated SSO_PF_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_pf_msix_pbax_s cn; */
};
typedef union bdk_sso_pf_msix_pbax bdk_sso_pf_msix_pbax_t;

static inline uint64_t BDK_SSO_PF_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PF_MSIX_PBAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x8607000f0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("SSO_PF_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PF_MSIX_PBAX(a) bdk_sso_pf_msix_pbax_t
#define bustype_BDK_SSO_PF_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PF_MSIX_PBAX(a) "SSO_PF_MSIX_PBAX"
#define device_bar_BDK_SSO_PF_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_SSO_PF_MSIX_PBAX(a) (a)
#define arguments_BDK_SSO_PF_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_pf_msix_vec#_addr
 *
 * SSO PF MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the SSO_PF_INT_VEC_E enumeration.
 */
union bdk_sso_pf_msix_vecx_addr
{
    uint64_t u;
    struct bdk_sso_pf_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's SSO_PF_MSIX_VEC()_ADDR, SSO_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of SSO_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_SSO_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's SSO_PF_MSIX_VEC()_ADDR, SSO_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of SSO_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_SSO_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_pf_msix_vecx_addr_s cn; */
};
typedef union bdk_sso_pf_msix_vecx_addr bdk_sso_pf_msix_vecx_addr_t;

static inline uint64_t BDK_SSO_PF_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PF_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x860700000000ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_PF_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PF_MSIX_VECX_ADDR(a) bdk_sso_pf_msix_vecx_addr_t
#define bustype_BDK_SSO_PF_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PF_MSIX_VECX_ADDR(a) "SSO_PF_MSIX_VECX_ADDR"
#define device_bar_BDK_SSO_PF_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_SSO_PF_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_SSO_PF_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_pf_msix_vec#_ctl
 *
 * SSO PF MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the SSO_PF_INT_VEC_E enumeration.
 */
union bdk_sso_pf_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_sso_pf_msix_vecx_ctl_s
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
    /* struct bdk_sso_pf_msix_vecx_ctl_s cn; */
};
typedef union bdk_sso_pf_msix_vecx_ctl bdk_sso_pf_msix_vecx_ctl_t;

static inline uint64_t BDK_SSO_PF_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PF_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x860700000008ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("SSO_PF_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PF_MSIX_VECX_CTL(a) bdk_sso_pf_msix_vecx_ctl_t
#define bustype_BDK_SSO_PF_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PF_MSIX_VECX_CTL(a) "SSO_PF_MSIX_VECX_CTL"
#define device_bar_BDK_SSO_PF_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_SSO_PF_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_SSO_PF_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_pf_vhgrp#_mbox#
 *
 * SSO PF/VF Mailbox Registers
 */
union bdk_sso_pf_vhgrpx_mboxx
{
    uint64_t u;
    struct bdk_sso_pf_vhgrpx_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 SSO_VHGRP()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing SSO_PF_VHGRP(0..63)_MBOX(0) (but not
                                                                 SSO_VHGRP(0..63)_PF_MBOX(0)) will set the corresponding
                                                                 SSO_VHGRP()_INT[MBOX] which if appropriately enabled will send an interrupt
                                                                 to the VF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 SSO_VHGRP()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing SSO_PF_VHGRP(0..63)_MBOX(0) (but not
                                                                 SSO_VHGRP(0..63)_PF_MBOX(0)) will set the corresponding
                                                                 SSO_VHGRP()_INT[MBOX] which if appropriately enabled will send an interrupt
                                                                 to the VF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_pf_vhgrpx_mboxx_s cn; */
};
typedef union bdk_sso_pf_vhgrpx_mboxx bdk_sso_pf_vhgrpx_mboxx_t;

static inline uint64_t BDK_SSO_PF_VHGRPX_MBOXX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PF_VHGRPX_MBOXX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=63) && (b<=1)))
        return 0x860020000400ll + 0x100000ll * ((a) & 0x3f) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("SSO_PF_VHGRPX_MBOXX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PF_VHGRPX_MBOXX(a,b) bdk_sso_pf_vhgrpx_mboxx_t
#define bustype_BDK_SSO_PF_VHGRPX_MBOXX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_PF_VHGRPX_MBOXX(a,b) "SSO_PF_VHGRPX_MBOXX"
#define device_bar_BDK_SSO_PF_VHGRPX_MBOXX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_PF_VHGRPX_MBOXX(a,b) (a)
#define arguments_BDK_SSO_PF_VHGRPX_MBOXX(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) sso_priv_af_int_cfg
 *
 * SSO Privileged Admin Function Interrupt Configuration Register
 */
union bdk_sso_priv_af_int_cfg
{
    uint64_t u;
    struct bdk_sso_priv_af_int_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by SSO_AF_INT_VEC_E. */
        uint64_t reserved_11           : 1;
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of AF interrupt vectors enumerated by
                                                                 SSO_AF_INT_VEC_E in RVU PF(0)'s MSI-X table. This offset is added to each
                                                                 enumerated value to obtain the corresponding MSI-X vector index. The
                                                                 highest enumerated value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF(0)_MSIX_CFG[PF_MSIXT_SIZEM1]. */
#else /* Word 0 - Little Endian */
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of AF interrupt vectors enumerated by
                                                                 SSO_AF_INT_VEC_E in RVU PF(0)'s MSI-X table. This offset is added to each
                                                                 enumerated value to obtain the corresponding MSI-X vector index. The
                                                                 highest enumerated value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF(0)_MSIX_CFG[PF_MSIXT_SIZEM1]. */
        uint64_t reserved_11           : 1;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by SSO_AF_INT_VEC_E. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_priv_af_int_cfg_s cn; */
};
typedef union bdk_sso_priv_af_int_cfg bdk_sso_priv_af_int_cfg_t;

#define BDK_SSO_PRIV_AF_INT_CFG BDK_SSO_PRIV_AF_INT_CFG_FUNC()
static inline uint64_t BDK_SSO_PRIV_AF_INT_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PRIV_AF_INT_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840070003000ll;
    __bdk_csr_fatal("SSO_PRIV_AF_INT_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PRIV_AF_INT_CFG bdk_sso_priv_af_int_cfg_t
#define bustype_BDK_SSO_PRIV_AF_INT_CFG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_PRIV_AF_INT_CFG "SSO_PRIV_AF_INT_CFG"
#define device_bar_BDK_SSO_PRIV_AF_INT_CFG 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_PRIV_AF_INT_CFG 0
#define arguments_BDK_SSO_PRIV_AF_INT_CFG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_priv_lf#_hwgrp_cfg
 *
 * SSO Privileged Local Function Configuration Registers
 */
union bdk_sso_priv_lfx_hwgrp_cfg
{
    uint64_t u;
    struct bdk_sso_priv_lfx_hwgrp_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enable. When set, the LF is enabled and provisioned to the VF/PF slot
                                                                 selected by [PF_FUNC] and [SLOT]. When clear, the LF is not provisioned.

                                                                 LF to slot mapping must be 1-to-1. Thus, each enabled LF must be provisioned
                                                                 to a unique {[PF_FUNC], [SLOT]} combination. */
        uint64_t reserved_24_62        : 39;
        uint64_t pf_func               : 16; /**< [ 23:  8](R/W) RVU VF/PF to which the LF is provisioned. Format defined by RVU_PF_FUNC_S.
                                                                 Interrupts from the LF are delivered to the selected PF/VF. */
        uint64_t slot                  : 8;  /**< [  7:  0](R/W) Slot within the VF/PF selected by [PF_FUNC] to which the LF is
                                                                 provisioned. */
#else /* Word 0 - Little Endian */
        uint64_t slot                  : 8;  /**< [  7:  0](R/W) Slot within the VF/PF selected by [PF_FUNC] to which the LF is
                                                                 provisioned. */
        uint64_t pf_func               : 16; /**< [ 23:  8](R/W) RVU VF/PF to which the LF is provisioned. Format defined by RVU_PF_FUNC_S.
                                                                 Interrupts from the LF are delivered to the selected PF/VF. */
        uint64_t reserved_24_62        : 39;
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enable. When set, the LF is enabled and provisioned to the VF/PF slot
                                                                 selected by [PF_FUNC] and [SLOT]. When clear, the LF is not provisioned.

                                                                 LF to slot mapping must be 1-to-1. Thus, each enabled LF must be provisioned
                                                                 to a unique {[PF_FUNC], [SLOT]} combination. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_priv_lfx_hwgrp_cfg_s cn; */
};
typedef union bdk_sso_priv_lfx_hwgrp_cfg bdk_sso_priv_lfx_hwgrp_cfg_t;

static inline uint64_t BDK_SSO_PRIV_LFX_HWGRP_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PRIV_LFX_HWGRP_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070010000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_PRIV_LFX_HWGRP_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PRIV_LFX_HWGRP_CFG(a) bdk_sso_priv_lfx_hwgrp_cfg_t
#define bustype_BDK_SSO_PRIV_LFX_HWGRP_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_PRIV_LFX_HWGRP_CFG(a) "SSO_PRIV_LFX_HWGRP_CFG"
#define device_bar_BDK_SSO_PRIV_LFX_HWGRP_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_PRIV_LFX_HWGRP_CFG(a) (a)
#define arguments_BDK_SSO_PRIV_LFX_HWGRP_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) sso_priv_lf#_hwgrp_int_cfg
 *
 * SSO Privileged Local Function Interrupt Configuration Registers
 */
union bdk_sso_priv_lfx_hwgrp_int_cfg
{
    uint64_t u;
    struct bdk_sso_priv_lfx_hwgrp_int_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by SSO_LF_INT_VEC_E. */
        uint64_t reserved_11           : 1;
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of LF interrupt vectors enumerated by the block's
                                                                 SSO_LF_INT_VEC_E in the MSI-X table of the corresponding RVU VF/PF (see
                                                                 SSO_PRIV_LF()_HWGRP_CFG[PF_FUNC]). This offset is added to each enumerated value
                                                                 to obtain the corresponding MSI-X vector index. The highest enumerated
                                                                 value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF()_MSIX_CFG[PF_MSIXT_SIZEM1,VF_MSIXT_SIZEM1]. */
#else /* Word 0 - Little Endian */
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of LF interrupt vectors enumerated by the block's
                                                                 SSO_LF_INT_VEC_E in the MSI-X table of the corresponding RVU VF/PF (see
                                                                 SSO_PRIV_LF()_HWGRP_CFG[PF_FUNC]). This offset is added to each enumerated value
                                                                 to obtain the corresponding MSI-X vector index. The highest enumerated
                                                                 value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF()_MSIX_CFG[PF_MSIXT_SIZEM1,VF_MSIXT_SIZEM1]. */
        uint64_t reserved_11           : 1;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by SSO_LF_INT_VEC_E. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_priv_lfx_hwgrp_int_cfg_s cn; */
};
typedef union bdk_sso_priv_lfx_hwgrp_int_cfg bdk_sso_priv_lfx_hwgrp_int_cfg_t;

static inline uint64_t BDK_SSO_PRIV_LFX_HWGRP_INT_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_PRIV_LFX_HWGRP_INT_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840070020000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("SSO_PRIV_LFX_HWGRP_INT_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_PRIV_LFX_HWGRP_INT_CFG(a) bdk_sso_priv_lfx_hwgrp_int_cfg_t
#define bustype_BDK_SSO_PRIV_LFX_HWGRP_INT_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSO_PRIV_LFX_HWGRP_INT_CFG(a) "SSO_PRIV_LFX_HWGRP_INT_CFG"
#define device_bar_BDK_SSO_PRIV_LFX_HWGRP_INT_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSO_PRIV_LFX_HWGRP_INT_CFG(a) (a)
#define arguments_BDK_SSO_PRIV_LFX_HWGRP_INT_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_reset
 *
 * SSO PF Soft Reset Register
 * Writing a 1 to SSO_RESET[RESET] resets the SSO. After receiving a store to this CSR, the SSO
 * must not be sent any other operations for 2500 coprocessor (SCLK) cycles. Note that the
 * contents of this register are reset along with the rest of the SSO.
 */
union bdk_sso_reset
{
    uint64_t u;
    struct bdk_sso_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) Initialization in progress. After reset asserts, SSO will set this bit until internal
                                                                 structures are initialized. This bit must read as zero before any configuration may be
                                                                 done. */
        uint64_t reserved_1_62         : 62;
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1/H) Reset the SSO. */
#else /* Word 0 - Little Endian */
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1/H) Reset the SSO. */
        uint64_t reserved_1_62         : 62;
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) Initialization in progress. After reset asserts, SSO will set this bit until internal
                                                                 structures are initialized. This bit must read as zero before any configuration may be
                                                                 done. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_reset_s cn; */
};
typedef union bdk_sso_reset bdk_sso_reset_t;

#define BDK_SSO_RESET BDK_SSO_RESET_FUNC()
static inline uint64_t BDK_SSO_RESET_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_RESET_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000010f8ll;
    __bdk_csr_fatal("SSO_RESET", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_RESET bdk_sso_reset_t
#define bustype_BDK_SSO_RESET BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_RESET "SSO_RESET"
#define device_bar_BDK_SSO_RESET 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_RESET 0
#define arguments_BDK_SSO_RESET -1,-1,-1,-1

/**
 * Register (NCB) sso_taq#_link
 *
 * SSO PF Transitory Admission Queue Link Registers
 * Returns TAQ status for a given line.
 */
union bdk_sso_taqx_link
{
    uint64_t u;
    struct bdk_sso_taqx_link_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t next                  : 11; /**< [ 10:  0](RO/H) Next TAQ entry in linked list. Only valid when not at the tail of the list. */
#else /* Word 0 - Little Endian */
        uint64_t next                  : 11; /**< [ 10:  0](RO/H) Next TAQ entry in linked list. Only valid when not at the tail of the list. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_taqx_link_s cn; */
};
typedef union bdk_sso_taqx_link bdk_sso_taqx_link_t;

static inline uint64_t BDK_SSO_TAQX_LINK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_TAQX_LINK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=319))
        return 0x8600c0000000ll + 0x1000ll * ((a) & 0x1ff);
    __bdk_csr_fatal("SSO_TAQX_LINK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_TAQX_LINK(a) bdk_sso_taqx_link_t
#define bustype_BDK_SSO_TAQX_LINK(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_TAQX_LINK(a) "SSO_TAQX_LINK"
#define device_bar_BDK_SSO_TAQX_LINK(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_TAQX_LINK(a) (a)
#define arguments_BDK_SSO_TAQX_LINK(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_taq#_wae#_tag
 *
 * SSO PF Transitory Admission Queue Tag Registers
 * Returns TAQ status for a given line and WAE within that line.
 */
union bdk_sso_taqx_waex_tag
{
    uint64_t u;
    struct bdk_sso_taqx_waex_tag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type of the TAQ entry. Enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag of the TAQ entry. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag of the TAQ entry. */
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type of the TAQ entry. Enumerated by SSO_TT_E. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_taqx_waex_tag_s cn; */
};
typedef union bdk_sso_taqx_waex_tag bdk_sso_taqx_waex_tag_t;

static inline uint64_t BDK_SSO_TAQX_WAEX_TAG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_TAQX_WAEX_TAG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=319) && (b<=10)))
        return 0x8600d0000000ll + 0x1000ll * ((a) & 0x1ff) + 0x10ll * ((b) & 0xf);
    __bdk_csr_fatal("SSO_TAQX_WAEX_TAG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_TAQX_WAEX_TAG(a,b) bdk_sso_taqx_waex_tag_t
#define bustype_BDK_SSO_TAQX_WAEX_TAG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_TAQX_WAEX_TAG(a,b) "SSO_TAQX_WAEX_TAG"
#define device_bar_BDK_SSO_TAQX_WAEX_TAG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_TAQX_WAEX_TAG(a,b) (a)
#define arguments_BDK_SSO_TAQX_WAEX_TAG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) sso_taq#_wae#_wqp
 *
 * SSO PF Transitory Admission Queue Pointer Registers
 * Returns TAQ status for a given line and WAE within that line.
 */
union bdk_sso_taqx_waex_wqp
{
    uint64_t u;
    struct bdk_sso_taqx_waex_wqp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) Work queue IOVA held in the TAQ entry.
                                                                 Bits \<63:49\> are a sign extension of \<48\>.  Bits \<2:0\> are 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) Work queue IOVA held in the TAQ entry.
                                                                 Bits \<63:49\> are a sign extension of \<48\>.  Bits \<2:0\> are 0x0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_taqx_waex_wqp_s cn; */
};
typedef union bdk_sso_taqx_waex_wqp bdk_sso_taqx_waex_wqp_t;

static inline uint64_t BDK_SSO_TAQX_WAEX_WQP(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_TAQX_WAEX_WQP(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=319) && (b<=10)))
        return 0x8600d0000008ll + 0x1000ll * ((a) & 0x1ff) + 0x10ll * ((b) & 0xf);
    __bdk_csr_fatal("SSO_TAQX_WAEX_WQP", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_TAQX_WAEX_WQP(a,b) bdk_sso_taqx_waex_wqp_t
#define bustype_BDK_SSO_TAQX_WAEX_WQP(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_TAQX_WAEX_WQP(a,b) "SSO_TAQX_WAEX_WQP"
#define device_bar_BDK_SSO_TAQX_WAEX_WQP(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_TAQX_WAEX_WQP(a,b) (a)
#define arguments_BDK_SSO_TAQX_WAEX_WQP(a,b) (a),(b),-1,-1

/**
 * Register (NCB) sso_taq_add
 *
 * SSO PF Transitory Admission Queue Add Register
 */
union bdk_sso_taq_add
{
    uint64_t u;
    struct bdk_sso_taq_add_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t rsvd_free             : 13; /**< [ 28: 16](WO) Written value is added to SSO_TAQ_CNT[RSVD_FREE] to prevent races between software and
                                                                 hardware changes. This is a two's complement value so subtraction may also be performed. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t rsvd_free             : 13; /**< [ 28: 16](WO) Written value is added to SSO_TAQ_CNT[RSVD_FREE] to prevent races between software and
                                                                 hardware changes. This is a two's complement value so subtraction may also be performed. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_taq_add_s cn; */
};
typedef union bdk_sso_taq_add bdk_sso_taq_add_t;

#define BDK_SSO_TAQ_ADD BDK_SSO_TAQ_ADD_FUNC()
static inline uint64_t BDK_SSO_TAQ_ADD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_TAQ_ADD_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000020e0ll;
    __bdk_csr_fatal("SSO_TAQ_ADD", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_TAQ_ADD bdk_sso_taq_add_t
#define bustype_BDK_SSO_TAQ_ADD BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_TAQ_ADD "SSO_TAQ_ADD"
#define device_bar_BDK_SSO_TAQ_ADD 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_TAQ_ADD 0
#define arguments_BDK_SSO_TAQ_ADD -1,-1,-1,-1

/**
 * Register (NCB) sso_taq_cnt
 *
 * SSO PF Transitory Admission Queue Count Register
 */
union bdk_sso_taq_cnt
{
    uint64_t u;
    struct bdk_sso_taq_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_27_63        : 37;
        uint64_t rsvd_free             : 11; /**< [ 26: 16](R/W/H) Number of free reserved buffers. Used to insure each hardware-group may get a
                                                                 specific number of buffers. Must always be greater than or equal to the sum
                                                                 across all SSO_GRP()_TAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to RSVD_THR are going to be made. To prevent races, software
                                                                 should not change this register when SSO is being used; instead use
                                                                 SSO_TAQ_ADD[RSVD_FREE]. Legal values are 0..0x140 */
        uint64_t reserved_11_15        : 5;
        uint64_t free_cnt              : 11; /**< [ 10:  0](RO/H) Number of total free buffers. */
#else /* Word 0 - Little Endian */
        uint64_t free_cnt              : 11; /**< [ 10:  0](RO/H) Number of total free buffers. */
        uint64_t reserved_11_15        : 5;
        uint64_t rsvd_free             : 11; /**< [ 26: 16](R/W/H) Number of free reserved buffers. Used to insure each hardware-group may get a
                                                                 specific number of buffers. Must always be greater than or equal to the sum
                                                                 across all SSO_GRP()_TAQ_THR[RSVD_THR], and will generally be equal to that sum
                                                                 unless changes to RSVD_THR are going to be made. To prevent races, software
                                                                 should not change this register when SSO is being used; instead use
                                                                 SSO_TAQ_ADD[RSVD_FREE]. Legal values are 0..0x140 */
        uint64_t reserved_27_63        : 37;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_taq_cnt_s cn; */
};
typedef union bdk_sso_taq_cnt bdk_sso_taq_cnt_t;

#define BDK_SSO_TAQ_CNT BDK_SSO_TAQ_CNT_FUNC()
static inline uint64_t BDK_SSO_TAQ_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_TAQ_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000020c0ll;
    __bdk_csr_fatal("SSO_TAQ_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_TAQ_CNT bdk_sso_taq_cnt_t
#define bustype_BDK_SSO_TAQ_CNT BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_TAQ_CNT "SSO_TAQ_CNT"
#define device_bar_BDK_SSO_TAQ_CNT 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_TAQ_CNT 0
#define arguments_BDK_SSO_TAQ_CNT -1,-1,-1,-1

/**
 * Register (NCB) sso_tiaq#_status
 *
 * SSO PF Hardware-Group Transitory Input Admission Queue Status Registers
 * This register returns TAQ inbound status indexed by hardware-group.
 */
union bdk_sso_tiaqx_status
{
    uint64_t u;
    struct bdk_sso_tiaqx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wae_head              : 4;  /**< [ 63: 60](RO/H) Head's WAE number within current cache line, 0-10. This provides the second index into
                                                                 SSO_TAQ()_WAE()_TAG and SSO_TAQ()_WAE()_WQP. */
        uint64_t wae_tail              : 4;  /**< [ 59: 56](RO/H) When [WAE_USED] is nonzero, this provides the next free WAE number in the cache
                                                                 line of the tail entry. If 0x0, the next entry will be placed at the beginning of
                                                                 a new cache line. This provides the second index into SSO_TAQ()_WAE()_TAG and
                                                                 SSO_TAQ()_WAE()_WQP. */
        uint64_t reserved_47_55        : 9;
        uint64_t wae_used              : 15; /**< [ 46: 32](RO/H) Number of WAEs in use. */
        uint64_t reserved_23_31        : 9;
        uint64_t ent_head              : 11; /**< [ 22: 12](RO/H) Head's entry number. This provides the first index into SSO_TAQ()_WAE()_TAG
                                                                 and SSO_TAQ()_WAE()_WQP. */
        uint64_t reserved_11           : 1;
        uint64_t ent_tail              : 11; /**< [ 10:  0](RO/H) Tail's entry number. This provides the first index into SSO_TAQ()_WAE()_TAG
                                                                 and SSO_TAQ()_WAE()_WQP. */
#else /* Word 0 - Little Endian */
        uint64_t ent_tail              : 11; /**< [ 10:  0](RO/H) Tail's entry number. This provides the first index into SSO_TAQ()_WAE()_TAG
                                                                 and SSO_TAQ()_WAE()_WQP. */
        uint64_t reserved_11           : 1;
        uint64_t ent_head              : 11; /**< [ 22: 12](RO/H) Head's entry number. This provides the first index into SSO_TAQ()_WAE()_TAG
                                                                 and SSO_TAQ()_WAE()_WQP. */
        uint64_t reserved_23_31        : 9;
        uint64_t wae_used              : 15; /**< [ 46: 32](RO/H) Number of WAEs in use. */
        uint64_t reserved_47_55        : 9;
        uint64_t wae_tail              : 4;  /**< [ 59: 56](RO/H) When [WAE_USED] is nonzero, this provides the next free WAE number in the cache
                                                                 line of the tail entry. If 0x0, the next entry will be placed at the beginning of
                                                                 a new cache line. This provides the second index into SSO_TAQ()_WAE()_TAG and
                                                                 SSO_TAQ()_WAE()_WQP. */
        uint64_t wae_head              : 4;  /**< [ 63: 60](RO/H) Head's WAE number within current cache line, 0-10. This provides the second index into
                                                                 SSO_TAQ()_WAE()_TAG and SSO_TAQ()_WAE()_WQP. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_tiaqx_status_s cn; */
};
typedef union bdk_sso_tiaqx_status bdk_sso_tiaqx_status_t;

static inline uint64_t BDK_SSO_TIAQX_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_TIAQX_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x8600000c0000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_TIAQX_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_TIAQX_STATUS(a) bdk_sso_tiaqx_status_t
#define bustype_BDK_SSO_TIAQX_STATUS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_TIAQX_STATUS(a) "SSO_TIAQX_STATUS"
#define device_bar_BDK_SSO_TIAQX_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_TIAQX_STATUS(a) (a)
#define arguments_BDK_SSO_TIAQX_STATUS(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_toaq#_status
 *
 * SSO PF Hardware-Group Transitory Output Admission Queue Status Registers
 * This register returns TAQ outbound status indexed by hardware-group.
 */
union bdk_sso_toaqx_status
{
    uint64_t u;
    struct bdk_sso_toaqx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t ext_vld               : 1;  /**< [ 61: 61](RO/H) External queuing is in use on this hardware-group. */
        uint64_t partial               : 1;  /**< [ 60: 60](RO/H) Partial cache line is allocated to tail of queue. */
        uint64_t wae_tail              : 4;  /**< [ 59: 56](RO/H) If [PARTIAL] is set, this provides the next free WAE number in the cache line of
                                                                 the tail entry. If [PARTIAL] is clear, the next entry will be placed at the
                                                                 beginning of a new cache line. This provides the second index into
                                                                 SSO_TAQ()_WAE()_TAG and SSO_TAQ()_WAE()_WQP. */
        uint64_t reserved_43_55        : 13;
        uint64_t cl_used               : 11; /**< [ 42: 32](RO/H) Number of cache lines in use. */
        uint64_t reserved_23_31        : 9;
        uint64_t ent_head              : 11; /**< [ 22: 12](RO/H) Head's entry number. This provides the first index into SSO_TAQ()_WAE()_TAG
                                                                 and SSO_TAQ()_WAE()_WQP. */
        uint64_t reserved_11           : 1;
        uint64_t ent_tail              : 11; /**< [ 10:  0](RO/H) Tail's entry number. This provides the first index into SSO_TAQ()_WAE()_TAG
                                                                 and SSO_TAQ()_WAE()_WQP. */
#else /* Word 0 - Little Endian */
        uint64_t ent_tail              : 11; /**< [ 10:  0](RO/H) Tail's entry number. This provides the first index into SSO_TAQ()_WAE()_TAG
                                                                 and SSO_TAQ()_WAE()_WQP. */
        uint64_t reserved_11           : 1;
        uint64_t ent_head              : 11; /**< [ 22: 12](RO/H) Head's entry number. This provides the first index into SSO_TAQ()_WAE()_TAG
                                                                 and SSO_TAQ()_WAE()_WQP. */
        uint64_t reserved_23_31        : 9;
        uint64_t cl_used               : 11; /**< [ 42: 32](RO/H) Number of cache lines in use. */
        uint64_t reserved_43_55        : 13;
        uint64_t wae_tail              : 4;  /**< [ 59: 56](RO/H) If [PARTIAL] is set, this provides the next free WAE number in the cache line of
                                                                 the tail entry. If [PARTIAL] is clear, the next entry will be placed at the
                                                                 beginning of a new cache line. This provides the second index into
                                                                 SSO_TAQ()_WAE()_TAG and SSO_TAQ()_WAE()_WQP. */
        uint64_t partial               : 1;  /**< [ 60: 60](RO/H) Partial cache line is allocated to tail of queue. */
        uint64_t ext_vld               : 1;  /**< [ 61: 61](RO/H) External queuing is in use on this hardware-group. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_toaqx_status_s cn; */
};
typedef union bdk_sso_toaqx_status bdk_sso_toaqx_status_t;

static inline uint64_t BDK_SSO_TOAQX_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_TOAQX_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x8600000d0000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_TOAQX_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_TOAQX_STATUS(a) bdk_sso_toaqx_status_t
#define bustype_BDK_SSO_TOAQX_STATUS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_TOAQX_STATUS(a) "SSO_TOAQX_STATUS"
#define device_bar_BDK_SSO_TOAQX_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_TOAQX_STATUS(a) (a)
#define arguments_BDK_SSO_TOAQX_STATUS(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_unmap_info
 *
 * SSO PF Unmapped Error Information Register
 * When any SSO_ERR0[GMID_UNMAP] , SSO_ERR0[GMID_MULTI], or SSO_ERR0[ADDWQ_DROPPED_WQP0]
 * error occurs, this register is latched with information from the original request.
 * This register latches the first error detected for SSO_ERR0[ADDWQ_DROPPED_WQP0] and
 * the first error detected for SSO_ERR0[GMID_UNMAP] or SSO_ERR0[GMID_MULTI]. Values in
 * register are held until errors are cleared in SSO_ERR0 register.
 */
union bdk_sso_unmap_info
{
    uint64_t u;
    struct bdk_sso_unmap_info_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_42_63        : 22;
        uint64_t wqp0_src              : 10; /**< [ 41: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<9\> = DDF.
                                                                 \<8\> = ZIP.
                                                                 \<7\> = TIM.
                                                                 \<6\> = RAD.
                                                                 \<5\> = PKO.
                                                                 \<4\> = DPI.
                                                                 \<3\> = CPT1.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT0.
                                                                 \<0\> = PKI. */
        uint64_t reserved_30_31        : 2;
        uint64_t gmid_multi            : 1;  /**< [ 29: 29](RO/H) GMID map had double-hit error. Set when SSO_ERR0[GMID_MULTI] is set
                                                                 and held until SSO_ERR0[GMID_MULTI] and SSO_ERR0[GMID_unmap] are cleared. */
        uint64_t gmid_unmap            : 1;  /**< [ 28: 28](RO/H) GMID mapping not found error. Set when SSO_ERR0[GMID_UNMAP] is set and held
                                                                 until SSO_ERR0[GMID_UNMAP] and SSO_ERR0[GMID_MULTI] are cleared */
        uint64_t reserved_26_27        : 2;
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_ERR0[GMID_UNMAP] or
                                                                 SSO_ERR0[GMID_MULTI] and is held until both errors are cleared in
                                                                 SSO_ERR0. */
        uint64_t gmid                  : 16; /**< [ 15:  0](RO/H) Failing GMID. This field is updated when any of he following errors occur:
                                                                 SSO_ERR0[GMID_UNMAP] or SSO_ERR0[GMID_MULTI] and is held until both errors
                                                                 have been cleared in SSO_ERR0. */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](RO/H) Failing GMID. This field is updated when any of he following errors occur:
                                                                 SSO_ERR0[GMID_UNMAP] or SSO_ERR0[GMID_MULTI] and is held until both errors
                                                                 have been cleared in SSO_ERR0. */
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP. This field is updated when
                                                                 any of he following errors occur: SSO_ERR0[GMID_UNMAP] or
                                                                 SSO_ERR0[GMID_MULTI] and is held until both errors are cleared in
                                                                 SSO_ERR0. */
        uint64_t reserved_26_27        : 2;
        uint64_t gmid_unmap            : 1;  /**< [ 28: 28](RO/H) GMID mapping not found error. Set when SSO_ERR0[GMID_UNMAP] is set and held
                                                                 until SSO_ERR0[GMID_UNMAP] and SSO_ERR0[GMID_MULTI] are cleared */
        uint64_t gmid_multi            : 1;  /**< [ 29: 29](RO/H) GMID map had double-hit error. Set when SSO_ERR0[GMID_MULTI] is set
                                                                 and held until SSO_ERR0[GMID_MULTI] and SSO_ERR0[GMID_unmap] are cleared. */
        uint64_t reserved_30_31        : 2;
        uint64_t wqp0_src              : 10; /**< [ 41: 32](RO/H) Illegal WQP0 error source. This field is updated when
                                                                 SSO_ERR0[ADDWQ_DROPPED_WQP0] error occurs, and is held until
                                                                 SSO_ERR0[ADDWQ_DROPPED_WQP0] is cleared.
                                                                 \<9\> = DDF.
                                                                 \<8\> = ZIP.
                                                                 \<7\> = TIM.
                                                                 \<6\> = RAD.
                                                                 \<5\> = PKO.
                                                                 \<4\> = DPI.
                                                                 \<3\> = CPT1.
                                                                 \<2\> = ADDWQ.
                                                                 \<1\> = CPT0.
                                                                 \<0\> = PKI. */
        uint64_t reserved_42_63        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_unmap_info_s cn; */
};
typedef union bdk_sso_unmap_info bdk_sso_unmap_info_t;

#define BDK_SSO_UNMAP_INFO BDK_SSO_UNMAP_INFO_FUNC()
static inline uint64_t BDK_SSO_UNMAP_INFO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_UNMAP_INFO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000012f0ll;
    __bdk_csr_fatal("SSO_UNMAP_INFO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_UNMAP_INFO bdk_sso_unmap_info_t
#define bustype_BDK_SSO_UNMAP_INFO BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_UNMAP_INFO "SSO_UNMAP_INFO"
#define device_bar_BDK_SSO_UNMAP_INFO 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_UNMAP_INFO 0
#define arguments_BDK_SSO_UNMAP_INFO -1,-1,-1,-1

/**
 * Register (NCB) sso_unmap_info2
 *
 * SSO PF Unmapped Error2 Information Register
 * When any SSO_ERR2[WS_UNMAP] or SSO_ERR2[WS_MULTI] error occurs, this
 * register is latched with information from the original request. This register
 * latches the first error and will not be updated again until all of the
 * corresponding SSO_ERR2 bits are cleared.
 */
union bdk_sso_unmap_info2
{
    uint64_t u;
    struct bdk_sso_unmap_info2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t cam_src               : 3;  /**< [ 34: 32](RO/H) Failing WS_GCAM error path. This field is updated when one of he following errors
                                                                 occur: SSO_ERR0[GMID_UNMAP] or SSO_ERR0[GMID_MULTI] and is held until both
                                                                 errors are cleared from SSO_ERR2. When multiple errors occur at the same
                                                                 time, the prioritiy to latch error information is as follows: WS to PP, NCBO1 to WS,
                                                                 NCBO0 to WS.
                                                                 \<2\> = From WS to PP (VHGRP to GGRP).
                                                                 \<1\> = From NCBO1 to WS (GGRP to VHGRP).
                                                                 \<0\> = From NCBO0 to WS (GGRP to VHGRP). */
        uint64_t reserved_30_31        : 2;
        uint64_t ws_multi              : 1;  /**< [ 29: 29](RO/H) GMID map had double-hit error. Set when SSO_ERR2[WS_MULTI] is set
                                                                 and held until SSO_ERR2[WS_MULTI] and SSO_ERR2[WS_UNMAP] are cleared. */
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](RO/H) GMID mapping not found error. Set when SSO_ERR2[GMID_UNMAP] is set and held
                                                                 until SSO_ERR2[WS_UNMAP] and SS2_ERR0[WS_MULTI] are cleared */
        uint64_t reserved_26_27        : 2;
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP or VHGRP. See [CAM_SRC] to identify the
                                                                 type. This field is updated when  any of he following errors occur:
                                                                 SSO_ERR2[WS_UNMAP] or SSO_ERR2[WS_MULTI] and is held until all both
                                                                 errors are cleared in SSO_ERR2. */
        uint64_t gmid                  : 16; /**< [ 15:  0](RO/H) Failing GMID. This field is updated when any of he following errors occur:
                                                                 SSO_ERR2[WS_UNMAP] or SSO_ERR2[WS_MULTI] and is held until both errors
                                                                 are cleared from SSO_ERR2. */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](RO/H) Failing GMID. This field is updated when any of he following errors occur:
                                                                 SSO_ERR2[WS_UNMAP] or SSO_ERR2[WS_MULTI] and is held until both errors
                                                                 are cleared from SSO_ERR2. */
        uint64_t ggrp                  : 10; /**< [ 25: 16](RO/H) This field indicates the failing GGRP or VHGRP. See [CAM_SRC] to identify the
                                                                 type. This field is updated when  any of he following errors occur:
                                                                 SSO_ERR2[WS_UNMAP] or SSO_ERR2[WS_MULTI] and is held until all both
                                                                 errors are cleared in SSO_ERR2. */
        uint64_t reserved_26_27        : 2;
        uint64_t ws_unmap              : 1;  /**< [ 28: 28](RO/H) GMID mapping not found error. Set when SSO_ERR2[GMID_UNMAP] is set and held
                                                                 until SSO_ERR2[WS_UNMAP] and SS2_ERR0[WS_MULTI] are cleared */
        uint64_t ws_multi              : 1;  /**< [ 29: 29](RO/H) GMID map had double-hit error. Set when SSO_ERR2[WS_MULTI] is set
                                                                 and held until SSO_ERR2[WS_MULTI] and SSO_ERR2[WS_UNMAP] are cleared. */
        uint64_t reserved_30_31        : 2;
        uint64_t cam_src               : 3;  /**< [ 34: 32](RO/H) Failing WS_GCAM error path. This field is updated when one of he following errors
                                                                 occur: SSO_ERR0[GMID_UNMAP] or SSO_ERR0[GMID_MULTI] and is held until both
                                                                 errors are cleared from SSO_ERR2. When multiple errors occur at the same
                                                                 time, the prioritiy to latch error information is as follows: WS to PP, NCBO1 to WS,
                                                                 NCBO0 to WS.
                                                                 \<2\> = From WS to PP (VHGRP to GGRP).
                                                                 \<1\> = From NCBO1 to WS (GGRP to VHGRP).
                                                                 \<0\> = From NCBO0 to WS (GGRP to VHGRP). */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_unmap_info2_s cn; */
};
typedef union bdk_sso_unmap_info2 bdk_sso_unmap_info2_t;

#define BDK_SSO_UNMAP_INFO2 BDK_SSO_UNMAP_INFO2_FUNC()
static inline uint64_t BDK_SSO_UNMAP_INFO2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_UNMAP_INFO2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001300ll;
    __bdk_csr_fatal("SSO_UNMAP_INFO2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_UNMAP_INFO2 bdk_sso_unmap_info2_t
#define bustype_BDK_SSO_UNMAP_INFO2 BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_UNMAP_INFO2 "SSO_UNMAP_INFO2"
#define device_bar_BDK_SSO_UNMAP_INFO2 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_UNMAP_INFO2 0
#define arguments_BDK_SSO_UNMAP_INFO2 -1,-1,-1,-1

/**
 * Register (NCB) sso_vf#_msix_pba#
 *
 * SSO VF MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the SSO_VF_INT_VEC_E
 * enumeration.
 */
union bdk_sso_vfx_msix_pbax
{
    uint64_t u;
    struct bdk_sso_vfx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated SSO_VF_MSIX_VEC()_CTL, enumerated by
                                                                 SSO_VF_INT_VEC_E. Bits that have no associated SSO_VF_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated SSO_VF_MSIX_VEC()_CTL, enumerated by
                                                                 SSO_VF_INT_VEC_E. Bits that have no associated SSO_VF_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vfx_msix_pbax_s cn; */
};
typedef union bdk_sso_vfx_msix_pbax bdk_sso_vfx_msix_pbax_t;

static inline uint64_t BDK_SSO_VFX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VFX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=63) && (b==0)))
        return 0x860c000f0000ll + 0x100000ll * ((a) & 0x3f) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("SSO_VFX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VFX_MSIX_PBAX(a,b) bdk_sso_vfx_msix_pbax_t
#define bustype_BDK_SSO_VFX_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VFX_MSIX_PBAX(a,b) "SSO_VFX_MSIX_PBAX"
#define device_bar_BDK_SSO_VFX_MSIX_PBAX(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_SSO_VFX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_SSO_VFX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) sso_vf#_msix_vec#_addr
 *
 * SSO VF MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the SSO_VF_INT_VEC_E enumeration.
 */
union bdk_sso_vfx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_sso_vfx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_SSO_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_SSO_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vfx_msix_vecx_addr_s cn; */
};
typedef union bdk_sso_vfx_msix_vecx_addr bdk_sso_vfx_msix_vecx_addr_t;

static inline uint64_t BDK_SSO_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=63) && (b==0)))
        return 0x860c00000000ll + 0x100000ll * ((a) & 0x3f) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("SSO_VFX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VFX_MSIX_VECX_ADDR(a,b) bdk_sso_vfx_msix_vecx_addr_t
#define bustype_BDK_SSO_VFX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VFX_MSIX_VECX_ADDR(a,b) "SSO_VFX_MSIX_VECX_ADDR"
#define device_bar_BDK_SSO_VFX_MSIX_VECX_ADDR(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_SSO_VFX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_SSO_VFX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) sso_vf#_msix_vec#_ctl
 *
 * SSO VF MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the SSO_VF_INT_VEC_E enumeration.
 */
union bdk_sso_vfx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_sso_vfx_msix_vecx_ctl_s
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
    /* struct bdk_sso_vfx_msix_vecx_ctl_s cn; */
};
typedef union bdk_sso_vfx_msix_vecx_ctl bdk_sso_vfx_msix_vecx_ctl_t;

static inline uint64_t BDK_SSO_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=63) && (b==0)))
        return 0x860c00000008ll + 0x100000ll * ((a) & 0x3f) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("SSO_VFX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VFX_MSIX_VECX_CTL(a,b) bdk_sso_vfx_msix_vecx_ctl_t
#define bustype_BDK_SSO_VFX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VFX_MSIX_VECX_CTL(a,b) "SSO_VFX_MSIX_VECX_CTL"
#define device_bar_BDK_SSO_VFX_MSIX_VECX_CTL(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_SSO_VFX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_SSO_VFX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) sso_vhgrp#_aq_cnt
 *
 * SSO VF Hardware-Group Admission Queue Count Registers
 */
union bdk_sso_vhgrpx_aq_cnt
{
    uint64_t u;
    struct bdk_sso_vhgrpx_aq_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t aq_cnt                : 33; /**< [ 32:  0](RO/H) Number of total in-unit, transitional and external admission queue entries for this hardware-group. */
#else /* Word 0 - Little Endian */
        uint64_t aq_cnt                : 33; /**< [ 32:  0](RO/H) Number of total in-unit, transitional and external admission queue entries for this hardware-group. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_aq_cnt_s cn; */
};
typedef union bdk_sso_vhgrpx_aq_cnt bdk_sso_vhgrpx_aq_cnt_t;

static inline uint64_t BDK_SSO_VHGRPX_AQ_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_AQ_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x8608000001c0ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_AQ_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_AQ_CNT(a) bdk_sso_vhgrpx_aq_cnt_t
#define bustype_BDK_SSO_VHGRPX_AQ_CNT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_AQ_CNT(a) "SSO_VHGRPX_AQ_CNT"
#define device_bar_BDK_SSO_VHGRPX_AQ_CNT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_AQ_CNT(a) (a)
#define arguments_BDK_SSO_VHGRPX_AQ_CNT(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_aq_thr
 *
 * SSO VF Hardware-Group Total Admission Queue Threshold Register
 */
union bdk_sso_vhgrpx_aq_thr
{
    uint64_t u;
    struct bdk_sso_vhgrpx_aq_thr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t aq_thr                : 33; /**< [ 32:  0](R/W) Total admission queue entry threshold. Compared against SSO_VHGRP()_AQ_CNT for
                                                                 triggering AQ interrupts. */
#else /* Word 0 - Little Endian */
        uint64_t aq_thr                : 33; /**< [ 32:  0](R/W) Total admission queue entry threshold. Compared against SSO_VHGRP()_AQ_CNT for
                                                                 triggering AQ interrupts. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_aq_thr_s cn; */
};
typedef union bdk_sso_vhgrpx_aq_thr bdk_sso_vhgrpx_aq_thr_t;

static inline uint64_t BDK_SSO_VHGRPX_AQ_THR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_AQ_THR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x8608000001e0ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_AQ_THR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_AQ_THR(a) bdk_sso_vhgrpx_aq_thr_t
#define bustype_BDK_SSO_VHGRPX_AQ_THR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_AQ_THR(a) "SSO_VHGRPX_AQ_THR"
#define device_bar_BDK_SSO_VHGRPX_AQ_THR(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_AQ_THR(a) (a)
#define arguments_BDK_SSO_VHGRPX_AQ_THR(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_int
 *
 * SSO VF Hardware-Group Interrupt Register
 * Contains the per-hardware-group interrupts and are used to clear these
 * interrupts. For more information on this register, refer to Interrupts.
 */
union bdk_sso_vhgrpx_int
{
    uint64_t u;
    struct bdk_sso_vhgrpx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1S/H) Executable interrupt temporary disable. Corresponding [EXE_INT] bit cannot be set due to
                                                                 IAQ_CNT/IAQ_THR check when this bit is set. [EXE_DIS] is cleared by hardware whenever:
                                                                 * SSO_VHGRP()_INT_CNT[IAQ_CNT] is zero.
                                                                 * Or, the hardware decrements the time counter for this hardware-group to zero, i.e.
                                                                 SSO_VHGRP()_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_WQ_INT_PC[PC] is
                                                                 equal to zero. */
        uint64_t reserved_4_62         : 59;
        uint64_t mbox                  : 1;  /**< [  3:  3](R/W1C/H) PF to VF mailbox interrupt. Set when SSO_VHGRP(0..63)_MBOX(0) is written. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1C/H) Hardware-group AQ exceeded allocation limit error; add-works to this VHGRP may
                                                                 be dropped. Set when SSO_VHGRP()_XAQ_CNT[XAQ_CNT] \>=
                                                                 SSO_GRP()_XAQ_LIMIT[XAQ_LIMIT]. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1C/H) Work-executable interrupt. Generally used to indicate work is waiting for software.
                                                                 Set by hardware whenever:

                                                                 * SSO_VHGRP()_INT_CNT[IAQ_CNT] \>= SSO_VHGRP()_INT_THR [IAQ_THR] and [IAQ_THR] != 0
                                                                 and [EXE_DIS] is clear.

                                                                 * SSO_VHGRP()_INT_CNT[DS_CNT] \>= SSO_VHGRP()_INT_THR[DS_THR] and [DS_THR] != 0.

                                                                 * SSO_VHGRP()_INT_CNT[CQ_CNT] \>= SSO_VHGRP()_INT_THR[CQ_THR] and [CQ_THR] != 0.

                                                                 * SSO_VHGRP()_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_WQ_INT_PC[PC] is
                                                                 equal to zero and SSO_VHGRP()_INT_THR[TC_EN] is set and at least one of the following is
                                                                 true:
                                                                 _ SSO_VHGRP()_INT_CNT[IAQ_CNT] \> 0
                                                                 _ SSO_VHGRP()_INT_CNT[DS_CNT] \> 0
                                                                 _ SSO_VHGRP()_INT_CNT[CQ_CNT] \> 0 */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1C/H) AQ threshold interrupt. Set if SSO_VHGRP()_AQ_CNT changes, and the
                                                                 resulting value is equal to SSO_VHGRP()_AQ_THR. */
#else /* Word 0 - Little Endian */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1C/H) AQ threshold interrupt. Set if SSO_VHGRP()_AQ_CNT changes, and the
                                                                 resulting value is equal to SSO_VHGRP()_AQ_THR. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1C/H) Work-executable interrupt. Generally used to indicate work is waiting for software.
                                                                 Set by hardware whenever:

                                                                 * SSO_VHGRP()_INT_CNT[IAQ_CNT] \>= SSO_VHGRP()_INT_THR [IAQ_THR] and [IAQ_THR] != 0
                                                                 and [EXE_DIS] is clear.

                                                                 * SSO_VHGRP()_INT_CNT[DS_CNT] \>= SSO_VHGRP()_INT_THR[DS_THR] and [DS_THR] != 0.

                                                                 * SSO_VHGRP()_INT_CNT[CQ_CNT] \>= SSO_VHGRP()_INT_THR[CQ_THR] and [CQ_THR] != 0.

                                                                 * SSO_VHGRP()_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_WQ_INT_PC[PC] is
                                                                 equal to zero and SSO_VHGRP()_INT_THR[TC_EN] is set and at least one of the following is
                                                                 true:
                                                                 _ SSO_VHGRP()_INT_CNT[IAQ_CNT] \> 0
                                                                 _ SSO_VHGRP()_INT_CNT[DS_CNT] \> 0
                                                                 _ SSO_VHGRP()_INT_CNT[CQ_CNT] \> 0 */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1C/H) Hardware-group AQ exceeded allocation limit error; add-works to this VHGRP may
                                                                 be dropped. Set when SSO_VHGRP()_XAQ_CNT[XAQ_CNT] \>=
                                                                 SSO_GRP()_XAQ_LIMIT[XAQ_LIMIT]. */
        uint64_t mbox                  : 1;  /**< [  3:  3](R/W1C/H) PF to VF mailbox interrupt. Set when SSO_VHGRP(0..63)_MBOX(0) is written. */
        uint64_t reserved_4_62         : 59;
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1S/H) Executable interrupt temporary disable. Corresponding [EXE_INT] bit cannot be set due to
                                                                 IAQ_CNT/IAQ_THR check when this bit is set. [EXE_DIS] is cleared by hardware whenever:
                                                                 * SSO_VHGRP()_INT_CNT[IAQ_CNT] is zero.
                                                                 * Or, the hardware decrements the time counter for this hardware-group to zero, i.e.
                                                                 SSO_VHGRP()_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_WQ_INT_PC[PC] is
                                                                 equal to zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_int_s cn; */
};
typedef union bdk_sso_vhgrpx_int bdk_sso_vhgrpx_int_t;

static inline uint64_t BDK_SSO_VHGRPX_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860800000100ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_INT(a) bdk_sso_vhgrpx_int_t
#define bustype_BDK_SSO_VHGRPX_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_INT(a) "SSO_VHGRPX_INT"
#define device_bar_BDK_SSO_VHGRPX_INT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_INT(a) (a)
#define arguments_BDK_SSO_VHGRPX_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_int_cnt
 *
 * SSO VF Hardware-Group Work-Queue Interrupt Count Registers
 * These registers contain a read-only copy of the counts used to trigger work-queue interrupts
 * (one per hardware-group). For more information on this register, refer to Interrupts.
 */
union bdk_sso_vhgrpx_int_cnt
{
    uint64_t u;
    struct bdk_sso_vhgrpx_int_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_61_63        : 3;
        uint64_t tc_cnt                : 13; /**< [ 60: 48](RO/H) Time counter current value. Hardware sets this field to the value of
                                                                 SSO_VHGRP()_INT_THR[TC_THR] whenever:
                                                                 * Corresponding SSO_VHGRP()_INT_CNT[IAQ_CNT, DS_CNT and CQ_CNT] are all equal to zero.
                                                                 * Corresponding SSO_VHGRP()_INT[EXE_INT] is written with a one to clear by software.
                                                                 * Corresponding SSO_VHGRP()_INT[EXE_DIS] is written with a one to set by software.
                                                                 * Corresponding SSO_VHGRP()_INT_THR is written by software.
                                                                 * TC_CNT is equal to one and periodic counter SSO_WQ_INT_PC[PC] is equal to zero.

                                                                 Otherwise, hardware decrements this field whenever the periodic counter SSO_WQ_INT_PC[PC]
                                                                 is equal to zero. This field is zero whenever SSO_VHGRP()_INT_THR[TC_THR] is equal to zero. */
        uint64_t reserved_45_47        : 3;
        uint64_t cq_cnt                : 13; /**< [ 44: 32](RO/H) Conflicted queue executable count. */
        uint64_t reserved_29_31        : 3;
        uint64_t ds_cnt                : 13; /**< [ 28: 16](RO/H) Deschedule executable count. */
        uint64_t reserved_13_15        : 3;
        uint64_t iaq_cnt               : 13; /**< [ 12:  0](RO/H) Work-queue entries for this in-unit admission queue. */
#else /* Word 0 - Little Endian */
        uint64_t iaq_cnt               : 13; /**< [ 12:  0](RO/H) Work-queue entries for this in-unit admission queue. */
        uint64_t reserved_13_15        : 3;
        uint64_t ds_cnt                : 13; /**< [ 28: 16](RO/H) Deschedule executable count. */
        uint64_t reserved_29_31        : 3;
        uint64_t cq_cnt                : 13; /**< [ 44: 32](RO/H) Conflicted queue executable count. */
        uint64_t reserved_45_47        : 3;
        uint64_t tc_cnt                : 13; /**< [ 60: 48](RO/H) Time counter current value. Hardware sets this field to the value of
                                                                 SSO_VHGRP()_INT_THR[TC_THR] whenever:
                                                                 * Corresponding SSO_VHGRP()_INT_CNT[IAQ_CNT, DS_CNT and CQ_CNT] are all equal to zero.
                                                                 * Corresponding SSO_VHGRP()_INT[EXE_INT] is written with a one to clear by software.
                                                                 * Corresponding SSO_VHGRP()_INT[EXE_DIS] is written with a one to set by software.
                                                                 * Corresponding SSO_VHGRP()_INT_THR is written by software.
                                                                 * TC_CNT is equal to one and periodic counter SSO_WQ_INT_PC[PC] is equal to zero.

                                                                 Otherwise, hardware decrements this field whenever the periodic counter SSO_WQ_INT_PC[PC]
                                                                 is equal to zero. This field is zero whenever SSO_VHGRP()_INT_THR[TC_THR] is equal to zero. */
        uint64_t reserved_61_63        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_int_cnt_s cn; */
};
typedef union bdk_sso_vhgrpx_int_cnt bdk_sso_vhgrpx_int_cnt_t;

static inline uint64_t BDK_SSO_VHGRPX_INT_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_INT_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860800000180ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_INT_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_INT_CNT(a) bdk_sso_vhgrpx_int_cnt_t
#define bustype_BDK_SSO_VHGRPX_INT_CNT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_INT_CNT(a) "SSO_VHGRPX_INT_CNT"
#define device_bar_BDK_SSO_VHGRPX_INT_CNT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_INT_CNT(a) (a)
#define arguments_BDK_SSO_VHGRPX_INT_CNT(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_int_ena_w1c
 *
 * SSO VF Hardware-Group Interrupt Enable Clear Register
 */
union bdk_sso_vhgrpx_int_ena_w1c
{
    uint64_t u;
    struct bdk_sso_vhgrpx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1C/H) Internal:
                                                                 This bit exists to enable auto-generation of the CSR and work
                                                                 around the inheritance_disabled attribute issue. This bit
                                                                 will not be connected to the EXE_DIS flop in SSO_VHGRP()_INT.
                                                                 See Bugzilla - bug 2050. */
        uint64_t reserved_4_62         : 59;
        uint64_t mbox                  : 1;  /**< [  3:  3](R/W1C/H) PF to VF mailbox interrupt. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1C/H) Group AQ exceeded allocation limit. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1C/H) Work-executable interrupt enable W1C. */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1C/H) External group queue threshold interrupt enable W1C. */
#else /* Word 0 - Little Endian */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1C/H) External group queue threshold interrupt enable W1C. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1C/H) Work-executable interrupt enable W1C. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1C/H) Group AQ exceeded allocation limit. */
        uint64_t mbox                  : 1;  /**< [  3:  3](R/W1C/H) PF to VF mailbox interrupt. */
        uint64_t reserved_4_62         : 59;
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1C/H) Internal:
                                                                 This bit exists to enable auto-generation of the CSR and work
                                                                 around the inheritance_disabled attribute issue. This bit
                                                                 will not be connected to the EXE_DIS flop in SSO_VHGRP()_INT.
                                                                 See Bugzilla - bug 2050. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_int_ena_w1c_s cn; */
};
typedef union bdk_sso_vhgrpx_int_ena_w1c bdk_sso_vhgrpx_int_ena_w1c_t;

static inline uint64_t BDK_SSO_VHGRPX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860800000118ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_INT_ENA_W1C(a) bdk_sso_vhgrpx_int_ena_w1c_t
#define bustype_BDK_SSO_VHGRPX_INT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_INT_ENA_W1C(a) "SSO_VHGRPX_INT_ENA_W1C"
#define device_bar_BDK_SSO_VHGRPX_INT_ENA_W1C(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_INT_ENA_W1C(a) (a)
#define arguments_BDK_SSO_VHGRPX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_int_ena_w1s
 *
 * SSO VF Hardware-Group Interrupt Enable Set Register
 */
union bdk_sso_vhgrpx_int_ena_w1s
{
    uint64_t u;
    struct bdk_sso_vhgrpx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1S/H) Internal:
                                                                 This bit exists to enable auto-generation of the CSR and work
                                                                 around the inheritance_disabled attribute issue. This bit
                                                                 will not be connected to the EXE_DIS flop in SSO_VHGRP()_INT.
                                                                 See Bugzilla - bug 2050. */
        uint64_t reserved_4_62         : 59;
        uint64_t mbox                  : 1;  /**< [  3:  3](R/W1S/H) PF to VF mailbox interrupt enable. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1S/H) Hardware-group AQ exceeded allocation limit error enable. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1S/H) Work-executable interrupt enable W1S. */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1S/H) External group queue threshold interrupt enable W1S. */
#else /* Word 0 - Little Endian */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1S/H) External group queue threshold interrupt enable W1S. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1S/H) Work-executable interrupt enable W1S. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1S/H) Hardware-group AQ exceeded allocation limit error enable. */
        uint64_t mbox                  : 1;  /**< [  3:  3](R/W1S/H) PF to VF mailbox interrupt enable. */
        uint64_t reserved_4_62         : 59;
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1S/H) Internal:
                                                                 This bit exists to enable auto-generation of the CSR and work
                                                                 around the inheritance_disabled attribute issue. This bit
                                                                 will not be connected to the EXE_DIS flop in SSO_VHGRP()_INT.
                                                                 See Bugzilla - bug 2050. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_int_ena_w1s_s cn; */
};
typedef union bdk_sso_vhgrpx_int_ena_w1s bdk_sso_vhgrpx_int_ena_w1s_t;

static inline uint64_t BDK_SSO_VHGRPX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860800000110ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_INT_ENA_W1S(a) bdk_sso_vhgrpx_int_ena_w1s_t
#define bustype_BDK_SSO_VHGRPX_INT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_INT_ENA_W1S(a) "SSO_VHGRPX_INT_ENA_W1S"
#define device_bar_BDK_SSO_VHGRPX_INT_ENA_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_INT_ENA_W1S(a) (a)
#define arguments_BDK_SSO_VHGRPX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_int_thr
 *
 * SSO VF Hardware-Group Work-Queue Interrupt Threshold Registers
 * These registers contain the thresholds for enabling and setting work-queue interrupts (one per
 * hardware-group). For more information on this register, refer to Interrupts.
 */
union bdk_sso_vhgrpx_int_thr
{
    uint64_t u;
    struct bdk_sso_vhgrpx_int_thr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t tc_en                 : 1;  /**< [ 63: 63](R/W) Time counter interrupt enable for this hardware-group. This field must be zero
                                                                 when [TC_THR] is zero. */
        uint64_t reserved_61_62        : 2;
        uint64_t tc_thr                : 13; /**< [ 60: 48](R/W) Time counter interrupt threshold for this hardware-group. Compared against
                                                                 SSO_VHGRP()_INT_CNT[TC_CNT]. When this field is equal to zero,
                                                                 SSO_VHGRP()_INT_CNT[TC_CNT] is zero. */
        uint64_t reserved_45_47        : 3;
        uint64_t cq_thr                : 13; /**< [ 44: 32](R/W) Conflicted queue count threshold for this hardware-group. Compared against
                                                                 SSO_VHGRP()_INT_CNT[CQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled. */
        uint64_t reserved_29_31        : 3;
        uint64_t ds_thr                : 13; /**< [ 28: 16](R/W) Deschedule count threshold for this hardware-group. Compared against
                                                                 SSO_VHGRP()_INT_CNT[DS_CNT]. When
                                                                 this field is zero, the threshold interrupt is disabled. */
        uint64_t reserved_13_15        : 3;
        uint64_t iaq_thr               : 13; /**< [ 12:  0](R/W) In-unit admission queue threshold for this hardware-group. Compared against
                                                                 SSO_VHGRP()_INT_CNT[IAQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled. */
#else /* Word 0 - Little Endian */
        uint64_t iaq_thr               : 13; /**< [ 12:  0](R/W) In-unit admission queue threshold for this hardware-group. Compared against
                                                                 SSO_VHGRP()_INT_CNT[IAQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled. */
        uint64_t reserved_13_15        : 3;
        uint64_t ds_thr                : 13; /**< [ 28: 16](R/W) Deschedule count threshold for this hardware-group. Compared against
                                                                 SSO_VHGRP()_INT_CNT[DS_CNT]. When
                                                                 this field is zero, the threshold interrupt is disabled. */
        uint64_t reserved_29_31        : 3;
        uint64_t cq_thr                : 13; /**< [ 44: 32](R/W) Conflicted queue count threshold for this hardware-group. Compared against
                                                                 SSO_VHGRP()_INT_CNT[CQ_CNT]. When this field is zero, the threshold interrupt is
                                                                 disabled. */
        uint64_t reserved_45_47        : 3;
        uint64_t tc_thr                : 13; /**< [ 60: 48](R/W) Time counter interrupt threshold for this hardware-group. Compared against
                                                                 SSO_VHGRP()_INT_CNT[TC_CNT]. When this field is equal to zero,
                                                                 SSO_VHGRP()_INT_CNT[TC_CNT] is zero. */
        uint64_t reserved_61_62        : 2;
        uint64_t tc_en                 : 1;  /**< [ 63: 63](R/W) Time counter interrupt enable for this hardware-group. This field must be zero
                                                                 when [TC_THR] is zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_int_thr_s cn; */
};
typedef union bdk_sso_vhgrpx_int_thr bdk_sso_vhgrpx_int_thr_t;

static inline uint64_t BDK_SSO_VHGRPX_INT_THR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_INT_THR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860800000140ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_INT_THR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_INT_THR(a) bdk_sso_vhgrpx_int_thr_t
#define bustype_BDK_SSO_VHGRPX_INT_THR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_INT_THR(a) "SSO_VHGRPX_INT_THR"
#define device_bar_BDK_SSO_VHGRPX_INT_THR(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_INT_THR(a) (a)
#define arguments_BDK_SSO_VHGRPX_INT_THR(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_int_w1s
 *
 * SSO VF Hardware-Group Interrupt Set Register
 */
union bdk_sso_vhgrpx_int_w1s
{
    uint64_t u;
    struct bdk_sso_vhgrpx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1S/H) Executable interrupt temporary disable. Corresponding [EXE_INT] bit cannot be set due to
                                                                 IAQ_CNT/IAQ_THR check when this bit is set. [EXE_DIS] is cleared by hardware whenever:
                                                                 * SSO_VHGRP()_INT_CNT[IAQ_CNT] is zero.
                                                                 * Or, the hardware decrements the time counter for this hardware-group to zero, i.e.
                                                                 SSO_VHGRP()_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_WQ_INT_PC[PC] is
                                                                 equal to zero. */
        uint64_t reserved_4_62         : 59;
        uint64_t mbox                  : 1;  /**< [  3:  3](R/W1S/H) PF to VF mailbox interrupt. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1S/H) Hardware-group AQ exceeded allocation limit error; */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1S/H) Work-executable interrupt W1S. Generally used to indicate work is waiting for software. */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1S/H) Aq threshold interrupt. */
#else /* Word 0 - Little Endian */
        uint64_t aq_int                : 1;  /**< [  0:  0](R/W1S/H) Aq threshold interrupt. */
        uint64_t exe_int               : 1;  /**< [  1:  1](R/W1S/H) Work-executable interrupt W1S. Generally used to indicate work is waiting for software. */
        uint64_t xaq_limit             : 1;  /**< [  2:  2](R/W1S/H) Hardware-group AQ exceeded allocation limit error; */
        uint64_t mbox                  : 1;  /**< [  3:  3](R/W1S/H) PF to VF mailbox interrupt. */
        uint64_t reserved_4_62         : 59;
        uint64_t exe_dis               : 1;  /**< [ 63: 63](R/W1S/H) Executable interrupt temporary disable. Corresponding [EXE_INT] bit cannot be set due to
                                                                 IAQ_CNT/IAQ_THR check when this bit is set. [EXE_DIS] is cleared by hardware whenever:
                                                                 * SSO_VHGRP()_INT_CNT[IAQ_CNT] is zero.
                                                                 * Or, the hardware decrements the time counter for this hardware-group to zero, i.e.
                                                                 SSO_VHGRP()_INT_CNT[TC_CNT] is equal to one when periodic counter SSO_WQ_INT_PC[PC] is
                                                                 equal to zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_int_w1s_s cn; */
};
typedef union bdk_sso_vhgrpx_int_w1s bdk_sso_vhgrpx_int_w1s_t;

static inline uint64_t BDK_SSO_VHGRPX_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860800000108ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_INT_W1S(a) bdk_sso_vhgrpx_int_w1s_t
#define bustype_BDK_SSO_VHGRPX_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_INT_W1S(a) "SSO_VHGRPX_INT_W1S"
#define device_bar_BDK_SSO_VHGRPX_INT_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_INT_W1S(a) (a)
#define arguments_BDK_SSO_VHGRPX_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_op_add_work0
 *
 * SSO VF Hardware-Group Add Work Register 0
 * See SSO_VHGRP()_OP_ADD_WORK1.
 */
union bdk_sso_vhgrpx_op_add_work0
{
    uint64_t u;
    struct bdk_sso_vhgrpx_op_add_work0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) Tag type to add, enumerated by SSO_TT_E.  Must not be EMPTY. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag of the work-queue entry, if [TT] is ATOMIC or ORDERED. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag of the work-queue entry, if [TT] is ATOMIC or ORDERED. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) Tag type to add, enumerated by SSO_TT_E.  Must not be EMPTY. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_op_add_work0_s cn; */
};
typedef union bdk_sso_vhgrpx_op_add_work0 bdk_sso_vhgrpx_op_add_work0_t;

static inline uint64_t BDK_SSO_VHGRPX_OP_ADD_WORK0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_OP_ADD_WORK0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x862800000000ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_OP_ADD_WORK0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_OP_ADD_WORK0(a) bdk_sso_vhgrpx_op_add_work0_t
#define bustype_BDK_SSO_VHGRPX_OP_ADD_WORK0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_OP_ADD_WORK0(a) "SSO_VHGRPX_OP_ADD_WORK0"
#define device_bar_BDK_SSO_VHGRPX_OP_ADD_WORK0(a) 0x2 /* VF_BAR2 */
#define busnum_BDK_SSO_VHGRPX_OP_ADD_WORK0(a) (a)
#define arguments_BDK_SSO_VHGRPX_OP_ADD_WORK0(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_op_add_work1
 *
 * SSO VF Hardware-Group Add Work Register 1
 * A write to this register performs an add work. Either:
 * * A single-transaction 128-bit store (SDP) is used to ADD_WORK0 and ADD_WORK1 to
 * perform a single add work with both a tag and work pointer.
 * * Or, a single 64-bit store is used to ADD_WORK1 to perform a single add work which
 * is untagged.
 * * Writing SSO_VHGRP()_OP_ADD_WORK0 without a simultanious write to ADD_WORK1
 * as described above is ignored.
 */
union bdk_sso_vhgrpx_op_add_work1
{
    uint64_t u;
    struct bdk_sso_vhgrpx_op_add_work1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry.  Bits \<63:49\> and \<2:0\> are ignored. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry.  Bits \<63:49\> and \<2:0\> are ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_op_add_work1_s cn; */
};
typedef union bdk_sso_vhgrpx_op_add_work1 bdk_sso_vhgrpx_op_add_work1_t;

static inline uint64_t BDK_SSO_VHGRPX_OP_ADD_WORK1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_OP_ADD_WORK1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x862800000008ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_OP_ADD_WORK1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_OP_ADD_WORK1(a) bdk_sso_vhgrpx_op_add_work1_t
#define bustype_BDK_SSO_VHGRPX_OP_ADD_WORK1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_OP_ADD_WORK1(a) "SSO_VHGRPX_OP_ADD_WORK1"
#define device_bar_BDK_SSO_VHGRPX_OP_ADD_WORK1(a) 0x2 /* VF_BAR2 */
#define busnum_BDK_SSO_VHGRPX_OP_ADD_WORK1(a) (a)
#define arguments_BDK_SSO_VHGRPX_OP_ADD_WORK1(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_pf_mbox#
 *
 * SSO VF/PF Mailbox Registers
 */
union bdk_sso_vhgrpx_pf_mboxx
{
    uint64_t u;
    struct bdk_sso_vhgrpx_pf_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using SSO_PF_VHGRP()_MBOX(). MBOX(0)
                                                                 is typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 SSO_VHGRP(0..63)_PF_MBOX(1) (but not SSO_PF_VHGRP(0..63)_MBOX(1)) will set the
                                                                 corresponding SSO_PF_MBOX_INT() bit, which if appropriately enabled will send
                                                                 an interrupt to the PF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using SSO_PF_VHGRP()_MBOX(). MBOX(0)
                                                                 is typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 SSO_VHGRP(0..63)_PF_MBOX(1) (but not SSO_PF_VHGRP(0..63)_MBOX(1)) will set the
                                                                 corresponding SSO_PF_MBOX_INT() bit, which if appropriately enabled will send
                                                                 an interrupt to the PF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_pf_mboxx_s cn; */
};
typedef union bdk_sso_vhgrpx_pf_mboxx bdk_sso_vhgrpx_pf_mboxx_t;

static inline uint64_t BDK_SSO_VHGRPX_PF_MBOXX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_PF_MBOXX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=63) && (b<=1)))
        return 0x860800000200ll + 0x100000ll * ((a) & 0x3f) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("SSO_VHGRPX_PF_MBOXX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_PF_MBOXX(a,b) bdk_sso_vhgrpx_pf_mboxx_t
#define bustype_BDK_SSO_VHGRPX_PF_MBOXX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_PF_MBOXX(a,b) "SSO_VHGRPX_PF_MBOXX"
#define device_bar_BDK_SSO_VHGRPX_PF_MBOXX(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_PF_MBOXX(a,b) (a)
#define arguments_BDK_SSO_VHGRPX_PF_MBOXX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) sso_vhgrp#_qctl
 *
 * SSO Admission Queue Control Registers
 */
union bdk_sso_vhgrpx_qctl
{
    uint64_t u;
    struct bdk_sso_vhgrpx_qctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) VHGRP enable. If clear, add work is dropped.

                                                                 Cleared by hardware when SSO_GRP()_XAQ_LIMIT[XAQ_LIMIT] \>=
                                                                 SSO_VHGRP()_XAQ_CNT[XAQ_CNT]. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) VHGRP enable. If clear, add work is dropped.

                                                                 Cleared by hardware when SSO_GRP()_XAQ_LIMIT[XAQ_LIMIT] \>=
                                                                 SSO_VHGRP()_XAQ_CNT[XAQ_CNT]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_qctl_s cn; */
};
typedef union bdk_sso_vhgrpx_qctl bdk_sso_vhgrpx_qctl_t;

static inline uint64_t BDK_SSO_VHGRPX_QCTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_QCTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860800000010ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_QCTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_QCTL(a) bdk_sso_vhgrpx_qctl_t
#define bustype_BDK_SSO_VHGRPX_QCTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_QCTL(a) "SSO_VHGRPX_QCTL"
#define device_bar_BDK_SSO_VHGRPX_QCTL(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_QCTL(a) (a)
#define arguments_BDK_SSO_VHGRPX_QCTL(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_vhgrp#_xaq_cnt
 *
 * SSO VF Hardware-Group External Queue Count Registers
 */
union bdk_sso_vhgrpx_xaq_cnt
{
    uint64_t u;
    struct bdk_sso_vhgrpx_xaq_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t xaq_cnt               : 33; /**< [ 32:  0](RO/H) Number of external admission queue entries for this hardware-group. */
#else /* Word 0 - Little Endian */
        uint64_t xaq_cnt               : 33; /**< [ 32:  0](RO/H) Number of external admission queue entries for this hardware-group. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_vhgrpx_xaq_cnt_s cn; */
};
typedef union bdk_sso_vhgrpx_xaq_cnt bdk_sso_vhgrpx_xaq_cnt_t;

static inline uint64_t BDK_SSO_VHGRPX_XAQ_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_VHGRPX_XAQ_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x8608000001b0ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_VHGRPX_XAQ_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_VHGRPX_XAQ_CNT(a) bdk_sso_vhgrpx_xaq_cnt_t
#define bustype_BDK_SSO_VHGRPX_XAQ_CNT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_VHGRPX_XAQ_CNT(a) "SSO_VHGRPX_XAQ_CNT"
#define device_bar_BDK_SSO_VHGRPX_XAQ_CNT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSO_VHGRPX_XAQ_CNT(a) (a)
#define arguments_BDK_SSO_VHGRPX_XAQ_CNT(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_wq_int_pc
 *
 * SSO PF Work-Queue Interrupt Periodic Counter Register
 * Contains the threshold value for the work-executable interrupt periodic counter and also a
 * read-only copy of the periodic counter. For more information on this register, refer to
 * Interrupts.
 */
union bdk_sso_wq_int_pc
{
    uint64_t u;
    struct bdk_sso_wq_int_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t pc                    : 28; /**< [ 59: 32](RO/H) Work-executable interrupt periodic counter. */
        uint64_t reserved_28_31        : 4;
        uint64_t pc_thr                : 20; /**< [ 27:  8](R/W) Work-executable interrupt periodic counter threshold. Zero disables the counter.
                                                                 If nonzero, the value must be \>= 3. */
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t pc_thr                : 20; /**< [ 27:  8](R/W) Work-executable interrupt periodic counter threshold. Zero disables the counter.
                                                                 If nonzero, the value must be \>= 3. */
        uint64_t reserved_28_31        : 4;
        uint64_t pc                    : 28; /**< [ 59: 32](RO/H) Work-executable interrupt periodic counter. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_wq_int_pc_s cn; */
};
typedef union bdk_sso_wq_int_pc bdk_sso_wq_int_pc_t;

#define BDK_SSO_WQ_INT_PC BDK_SSO_WQ_INT_PC_FUNC()
static inline uint64_t BDK_SSO_WQ_INT_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_WQ_INT_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001020ll;
    __bdk_csr_fatal("SSO_WQ_INT_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_WQ_INT_PC bdk_sso_wq_int_pc_t
#define bustype_BDK_SSO_WQ_INT_PC BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_WQ_INT_PC "SSO_WQ_INT_PC"
#define device_bar_BDK_SSO_WQ_INT_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_WQ_INT_PC 0
#define arguments_BDK_SSO_WQ_INT_PC -1,-1,-1,-1

/**
 * Register (NCB) sso_ws_cfg
 *
 * SSO PF Configuration Register
 * This register contains various SSO work-slot configuration bits.
 */
union bdk_sso_ws_cfg
{
    uint64_t u;
    struct bdk_sso_ws_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t ocla_bp               : 8;  /**< [ 55: 48](R/W) Enable OCLA backpressure stalls. For diagnostic use only.
                                                                 Internal:
                                                                 \<55\> = NCBB input fifo stall (ncbo).
                                                                 \<54\> = Work-slot response. (arbrsp).
                                                                 \<53\> = Work-slot switching of descheduled work entries. (arbx).
                                                                 \<52\> = Work-slot SWTAG response. (arbs).
                                                                 \<51\> = Work-slot access to get-work engine. (arbgw).
                                                                 \<50\> = Work-slot CAM access. (arbc).
                                                                 \<49\> = Work-slot RAM access. (arbr).
                                                                 \<48\> = Work-slot pushes to AQ, CQ, DQ. (arbq). */
        uint64_t reserved_31_47        : 17;
        uint64_t bp_interval           : 3;  /**< [ 30: 28](R/W) Coprocessor-clock cycles between each 16 cycle interval of HWS backpressure.
                                                                 For diagnostic use only.
                                                                 0x0 = Disable this backpressure mechanism.
                                                                 0x1 =   64 cycles.
                                                                 0x2 =  128 cycles.
                                                                 0x3 =  256 cycles.
                                                                 0x4 =  512 cycles.
                                                                 0x5 = 1024 cycles.
                                                                 0x6 = 2048 cycles.
                                                                 0x7 = 4096 cycles. */
        uint64_t dqrd_replay_thr       : 12; /**< [ 27: 16](R/W) Theshold for the number of consecutive DQ reads that are aborted due
                                                                 to hazards without a successful DQ read. Equalling or exceeding the
                                                                 threshold indicates a potential deadlock due to a circular dependency
                                                                 of hazards and results in 16 cycles of backpressure to DQ readers
                                                                 to break free of the deadlock. A threshold of zero disables this
                                                                 backpressure mechanism.
                                                                 For diagnostic use only.

                                                                 Internal:
                                                                 The deadlock is caused by a HWS or AGTX making another HWS replay RAM
                                                                 reads while waiting for a CAM grant. The CAM grant gets aborted on
                                                                 seeing the replayed reads in progress, doesn't make forward progress,
                                                                 and makes other HWSs replay RAM reads. Applying backpressure to ARBR
                                                                 requests from the HWSs trying to replay RAM reads breaks the deadlock. */
        uint64_t reserved_8_15         : 8;
        uint64_t sai_flush             : 1;  /**< [  7:  7](R/W1) When written with one, send a pulse to invalidate the VHWS switch tag cache
                                                                 inside the cores.  Reads as zero. For diagnostic use only. */
        uint64_t aw_clk_dis            : 1;  /**< [  6:  6](R/W) Reserved. */
        uint64_t gw_clk_dis            : 1;  /**< [  5:  5](R/W) Reserved. */
        uint64_t disable_pw            : 1;  /**< [  4:  4](R/W) Reserved. */
        uint64_t arbc_step_en          : 1;  /**< [  3:  3](R/W) Enable single-stepping WS CAM arbiter, twice per 16 clocks. For diagnostic use only. */
        uint64_t ncbo_step_en          : 1;  /**< [  2:  2](R/W) Enable single-stepping commands from NCBO, once per 32 clocks. For diagnostic use only. */
        uint64_t soc_ccam_dis          : 1;  /**< [  1:  1](R/W) Disable power saving SOC conditional CAM. */
        uint64_t sso_cclk_dis          : 1;  /**< [  0:  0](R/W) Disable power saving SSO conditional clocking, */
#else /* Word 0 - Little Endian */
        uint64_t sso_cclk_dis          : 1;  /**< [  0:  0](R/W) Disable power saving SSO conditional clocking, */
        uint64_t soc_ccam_dis          : 1;  /**< [  1:  1](R/W) Disable power saving SOC conditional CAM. */
        uint64_t ncbo_step_en          : 1;  /**< [  2:  2](R/W) Enable single-stepping commands from NCBO, once per 32 clocks. For diagnostic use only. */
        uint64_t arbc_step_en          : 1;  /**< [  3:  3](R/W) Enable single-stepping WS CAM arbiter, twice per 16 clocks. For diagnostic use only. */
        uint64_t disable_pw            : 1;  /**< [  4:  4](R/W) Reserved. */
        uint64_t gw_clk_dis            : 1;  /**< [  5:  5](R/W) Reserved. */
        uint64_t aw_clk_dis            : 1;  /**< [  6:  6](R/W) Reserved. */
        uint64_t sai_flush             : 1;  /**< [  7:  7](R/W1) When written with one, send a pulse to invalidate the VHWS switch tag cache
                                                                 inside the cores.  Reads as zero. For diagnostic use only. */
        uint64_t reserved_8_15         : 8;
        uint64_t dqrd_replay_thr       : 12; /**< [ 27: 16](R/W) Theshold for the number of consecutive DQ reads that are aborted due
                                                                 to hazards without a successful DQ read. Equalling or exceeding the
                                                                 threshold indicates a potential deadlock due to a circular dependency
                                                                 of hazards and results in 16 cycles of backpressure to DQ readers
                                                                 to break free of the deadlock. A threshold of zero disables this
                                                                 backpressure mechanism.
                                                                 For diagnostic use only.

                                                                 Internal:
                                                                 The deadlock is caused by a HWS or AGTX making another HWS replay RAM
                                                                 reads while waiting for a CAM grant. The CAM grant gets aborted on
                                                                 seeing the replayed reads in progress, doesn't make forward progress,
                                                                 and makes other HWSs replay RAM reads. Applying backpressure to ARBR
                                                                 requests from the HWSs trying to replay RAM reads breaks the deadlock. */
        uint64_t bp_interval           : 3;  /**< [ 30: 28](R/W) Coprocessor-clock cycles between each 16 cycle interval of HWS backpressure.
                                                                 For diagnostic use only.
                                                                 0x0 = Disable this backpressure mechanism.
                                                                 0x1 =   64 cycles.
                                                                 0x2 =  128 cycles.
                                                                 0x3 =  256 cycles.
                                                                 0x4 =  512 cycles.
                                                                 0x5 = 1024 cycles.
                                                                 0x6 = 2048 cycles.
                                                                 0x7 = 4096 cycles. */
        uint64_t reserved_31_47        : 17;
        uint64_t ocla_bp               : 8;  /**< [ 55: 48](R/W) Enable OCLA backpressure stalls. For diagnostic use only.
                                                                 Internal:
                                                                 \<55\> = NCBB input fifo stall (ncbo).
                                                                 \<54\> = Work-slot response. (arbrsp).
                                                                 \<53\> = Work-slot switching of descheduled work entries. (arbx).
                                                                 \<52\> = Work-slot SWTAG response. (arbs).
                                                                 \<51\> = Work-slot access to get-work engine. (arbgw).
                                                                 \<50\> = Work-slot CAM access. (arbc).
                                                                 \<49\> = Work-slot RAM access. (arbr).
                                                                 \<48\> = Work-slot pushes to AQ, CQ, DQ. (arbq). */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ws_cfg_s cn; */
};
typedef union bdk_sso_ws_cfg bdk_sso_ws_cfg_t;

#define BDK_SSO_WS_CFG BDK_SSO_WS_CFG_FUNC()
static inline uint64_t BDK_SSO_WS_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_WS_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001088ll;
    __bdk_csr_fatal("SSO_WS_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_WS_CFG bdk_sso_ws_cfg_t
#define bustype_BDK_SSO_WS_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_WS_CFG "SSO_WS_CFG"
#define device_bar_BDK_SSO_WS_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_WS_CFG 0
#define arguments_BDK_SSO_WS_CFG -1,-1,-1,-1

/**
 * Register (NCB) sso_ws_eco
 *
 * INTERNAL: SSO PF WS ECO Register
 */
union bdk_sso_ws_eco
{
    uint64_t u;
    struct bdk_sso_ws_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 8;  /**< [  7:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_ws_eco_s cn; */
};
typedef union bdk_sso_ws_eco bdk_sso_ws_eco_t;

#define BDK_SSO_WS_ECO BDK_SSO_WS_ECO_FUNC()
static inline uint64_t BDK_SSO_WS_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_WS_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000001048ll;
    __bdk_csr_fatal("SSO_WS_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_WS_ECO bdk_sso_ws_eco_t
#define bustype_BDK_SSO_WS_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_WS_ECO "SSO_WS_ECO"
#define device_bar_BDK_SSO_WS_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_WS_ECO 0
#define arguments_BDK_SSO_WS_ECO -1,-1,-1,-1

/**
 * Register (NCB) sso_xaq#_head_next
 *
 * SSO PF Hardware-Group External Admission Queue Head Next Register
 * These registers contain the pointer to the next buffer to become the head when the final cache
 * line in this buffer is read.
 *
 * This register must not be written when SSO_VHGRP()_QCTL[ENA] is set.
 */
union bdk_sso_xaqx_head_next
{
    uint64_t u;
    struct bdk_sso_xaqx_head_next_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_xaqx_head_next_s cn; */
};
typedef union bdk_sso_xaqx_head_next bdk_sso_xaqx_head_next_t;

static inline uint64_t BDK_SSO_XAQX_HEAD_NEXT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_XAQX_HEAD_NEXT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x8600000a0000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_XAQX_HEAD_NEXT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_XAQX_HEAD_NEXT(a) bdk_sso_xaqx_head_next_t
#define bustype_BDK_SSO_XAQX_HEAD_NEXT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_XAQX_HEAD_NEXT(a) "SSO_XAQX_HEAD_NEXT"
#define device_bar_BDK_SSO_XAQX_HEAD_NEXT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_XAQX_HEAD_NEXT(a) (a)
#define arguments_BDK_SSO_XAQX_HEAD_NEXT(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_xaq#_head_ptr
 *
 * SSO PF Hardware-Group External Admission Queue Head Pointer Register
 * These registers contain the pointer to the first entry of the external linked
 * list(s) for a particular hardware-group. Software must initialize the external
 * linked list(s) by programming SSO_XAQ()_HEAD_PTR, SSO_XAQ()_HEAD_NEXT,
 * SSO_XAQ()_TAIL_PTR and SSO_XAQ()_TAIL_NEXT to identical values.
 *
 * This register must not be written when SSO_VHGRP()_QCTL[ENA] is set.
 */
union bdk_sso_xaqx_head_ptr
{
    uint64_t u;
    struct bdk_sso_xaqx_head_ptr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_5_6          : 2;
        uint64_t cl                    : 5;  /**< [  4:  0](R/W/H) Cache line number in buffer. Cache line zero contains the next pointer. */
#else /* Word 0 - Little Endian */
        uint64_t cl                    : 5;  /**< [  4:  0](R/W/H) Cache line number in buffer. Cache line zero contains the next pointer. */
        uint64_t reserved_5_6          : 2;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_xaqx_head_ptr_s cn; */
};
typedef union bdk_sso_xaqx_head_ptr bdk_sso_xaqx_head_ptr_t;

static inline uint64_t BDK_SSO_XAQX_HEAD_PTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_XAQX_HEAD_PTR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860000080000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_XAQX_HEAD_PTR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_XAQX_HEAD_PTR(a) bdk_sso_xaqx_head_ptr_t
#define bustype_BDK_SSO_XAQX_HEAD_PTR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_XAQX_HEAD_PTR(a) "SSO_XAQX_HEAD_PTR"
#define device_bar_BDK_SSO_XAQX_HEAD_PTR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_XAQX_HEAD_PTR(a) (a)
#define arguments_BDK_SSO_XAQX_HEAD_PTR(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_xaq#_tail_next
 *
 * SSO PF Hardware-Group External Admission Queue Tail Next Register
 * These registers contain the pointer to the next buffer to become the tail when the final cache
 * line in this buffer is written.  Register fields are identical to those in
 * SSO_XAQ()_HEAD_NEXT above.
 *
 * This register must not be written when SSO_VHGRP()_QCTL[ENA] is set.
 */
union bdk_sso_xaqx_tail_next
{
    uint64_t u;
    struct bdk_sso_xaqx_tail_next_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_xaqx_tail_next_s cn; */
};
typedef union bdk_sso_xaqx_tail_next bdk_sso_xaqx_tail_next_t;

static inline uint64_t BDK_SSO_XAQX_TAIL_NEXT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_XAQX_TAIL_NEXT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x8600000b0000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_XAQX_TAIL_NEXT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_XAQX_TAIL_NEXT(a) bdk_sso_xaqx_tail_next_t
#define bustype_BDK_SSO_XAQX_TAIL_NEXT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_XAQX_TAIL_NEXT(a) "SSO_XAQX_TAIL_NEXT"
#define device_bar_BDK_SSO_XAQX_TAIL_NEXT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_XAQX_TAIL_NEXT(a) (a)
#define arguments_BDK_SSO_XAQX_TAIL_NEXT(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_xaq#_tail_ptr
 *
 * SSO PF Hardware-Group External Admission Queue Tail Pointer Register
 * These registers contain the pointer to the last entry of the external linked list(s)
 * for a particular hardware-group. Register fields are identical to those in
 * SSO_XAQ()_HEAD_PTR above. Software must initialize the external linked list(s) by
 * programming SSO_XAQ()_HEAD_PTR, SSO_XAQ()_HEAD_NEXT, SSO_XAQ()_TAIL_PTR and
 * SSO_XAQ()_TAIL_NEXT to identical values.
 *
 * This register must not be written when SSO_VHGRP()_QCTL[ENA] is set.
 */
union bdk_sso_xaqx_tail_ptr
{
    uint64_t u;
    struct bdk_sso_xaqx_tail_ptr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_5_6          : 2;
        uint64_t cl                    : 5;  /**< [  4:  0](R/W/H) Cache line number in buffer. Cache line zero contains the next pointer. */
#else /* Word 0 - Little Endian */
        uint64_t cl                    : 5;  /**< [  4:  0](R/W/H) Cache line number in buffer. Cache line zero contains the next pointer. */
        uint64_t reserved_5_6          : 2;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) IOVA pointer, divided by 128 bytes.
                                                                 Internal:
                                                                 For peak performance, all XAQ buffers should reside on the local node's memory. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_xaqx_tail_ptr_s cn; */
};
typedef union bdk_sso_xaqx_tail_ptr bdk_sso_xaqx_tail_ptr_t;

static inline uint64_t BDK_SSO_XAQX_TAIL_PTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_XAQX_TAIL_PTR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x860000090000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSO_XAQX_TAIL_PTR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_XAQX_TAIL_PTR(a) bdk_sso_xaqx_tail_ptr_t
#define bustype_BDK_SSO_XAQX_TAIL_PTR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_XAQX_TAIL_PTR(a) "SSO_XAQX_TAIL_PTR"
#define device_bar_BDK_SSO_XAQX_TAIL_PTR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_XAQX_TAIL_PTR(a) (a)
#define arguments_BDK_SSO_XAQX_TAIL_PTR(a) (a),-1,-1,-1

/**
 * Register (NCB) sso_xaq_aura
 *
 * SSO PF External Admission Queue Aura Register
 */
union bdk_sso_xaq_aura
{
    uint64_t u;
    struct bdk_sso_xaq_aura_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t laura                 : 12; /**< [ 11:  0](R/W) FPA guest-aura to use for SSO XAQ allocations and frees. The FPA guest-aura
                                                                 selected by [LAURA] must correspond to a pool where the buffers (after any
                                                                 FPA_POOL()_CFG[BUF_OFFSET]) are at least 4 KB.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and SSO_XAQ_GMCTL[GMID] as valid. */
#else /* Word 0 - Little Endian */
        uint64_t laura                 : 12; /**< [ 11:  0](R/W) FPA guest-aura to use for SSO XAQ allocations and frees. The FPA guest-aura
                                                                 selected by [LAURA] must correspond to a pool where the buffers (after any
                                                                 FPA_POOL()_CFG[BUF_OFFSET]) are at least 4 KB.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and SSO_XAQ_GMCTL[GMID] as valid. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_xaq_aura_s cn; */
};
typedef union bdk_sso_xaq_aura bdk_sso_xaq_aura_t;

#define BDK_SSO_XAQ_AURA BDK_SSO_XAQ_AURA_FUNC()
static inline uint64_t BDK_SSO_XAQ_AURA_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_XAQ_AURA_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000002100ll;
    __bdk_csr_fatal("SSO_XAQ_AURA", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_XAQ_AURA bdk_sso_xaq_aura_t
#define bustype_BDK_SSO_XAQ_AURA BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_XAQ_AURA "SSO_XAQ_AURA"
#define device_bar_BDK_SSO_XAQ_AURA 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_XAQ_AURA 0
#define arguments_BDK_SSO_XAQ_AURA -1,-1,-1,-1

/**
 * Register (NCB) sso_xaq_gmctl
 *
 * SSO PF External Admission Queue Guest Machine Control Register
 */
union bdk_sso_xaq_gmctl
{
    uint64_t u;
    struct bdk_sso_xaq_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all buffer
                                                                 free/allocates.
                                                                 Must be nonzero or FPA will drop requests; see FPA_PF_MAP(). */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all buffer
                                                                 free/allocates.
                                                                 Must be nonzero or FPA will drop requests; see FPA_PF_MAP(). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_xaq_gmctl_s cn; */
};
typedef union bdk_sso_xaq_gmctl bdk_sso_xaq_gmctl_t;

#define BDK_SSO_XAQ_GMCTL BDK_SSO_XAQ_GMCTL_FUNC()
static inline uint64_t BDK_SSO_XAQ_GMCTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_XAQ_GMCTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x860000002110ll;
    __bdk_csr_fatal("SSO_XAQ_GMCTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_XAQ_GMCTL bdk_sso_xaq_gmctl_t
#define bustype_BDK_SSO_XAQ_GMCTL BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_XAQ_GMCTL "SSO_XAQ_GMCTL"
#define device_bar_BDK_SSO_XAQ_GMCTL 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_XAQ_GMCTL 0
#define arguments_BDK_SSO_XAQ_GMCTL -1,-1,-1,-1

/**
 * Register (NCB) sso_xaq_latency_pc
 *
 * SSO PF External Admission Queue Latency Perf-Count Register
 */
union bdk_sso_xaq_latency_pc
{
    uint64_t u;
    struct bdk_sso_xaq_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for XAQ read returns. This may be divided by SSO_XAQ_REQ_PC to
                                                                 determine the average read latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for XAQ read returns. This may be divided by SSO_XAQ_REQ_PC to
                                                                 determine the average read latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_xaq_latency_pc_s cn; */
};
typedef union bdk_sso_xaq_latency_pc bdk_sso_xaq_latency_pc_t;

#define BDK_SSO_XAQ_LATENCY_PC BDK_SSO_XAQ_LATENCY_PC_FUNC()
static inline uint64_t BDK_SSO_XAQ_LATENCY_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_XAQ_LATENCY_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000020b8ll;
    __bdk_csr_fatal("SSO_XAQ_LATENCY_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_XAQ_LATENCY_PC bdk_sso_xaq_latency_pc_t
#define bustype_BDK_SSO_XAQ_LATENCY_PC BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_XAQ_LATENCY_PC "SSO_XAQ_LATENCY_PC"
#define device_bar_BDK_SSO_XAQ_LATENCY_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_XAQ_LATENCY_PC 0
#define arguments_BDK_SSO_XAQ_LATENCY_PC -1,-1,-1,-1

/**
 * Register (NCB) sso_xaq_req_pc
 *
 * SSO PF External Admission Queue Requests Perf-Count Register
 */
union bdk_sso_xaq_req_pc
{
    uint64_t u;
    struct bdk_sso_xaq_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of XAQ read requests. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of XAQ read requests. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_sso_xaq_req_pc_s cn; */
};
typedef union bdk_sso_xaq_req_pc bdk_sso_xaq_req_pc_t;

#define BDK_SSO_XAQ_REQ_PC BDK_SSO_XAQ_REQ_PC_FUNC()
static inline uint64_t BDK_SSO_XAQ_REQ_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSO_XAQ_REQ_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8600000020b0ll;
    __bdk_csr_fatal("SSO_XAQ_REQ_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSO_XAQ_REQ_PC bdk_sso_xaq_req_pc_t
#define bustype_BDK_SSO_XAQ_REQ_PC BDK_CSR_TYPE_NCB
#define basename_BDK_SSO_XAQ_REQ_PC "SSO_XAQ_REQ_PC"
#define device_bar_BDK_SSO_XAQ_REQ_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_SSO_XAQ_REQ_PC 0
#define arguments_BDK_SSO_XAQ_REQ_PC -1,-1,-1,-1

#endif /* __BDK_CSRS_SSO_H__ */
