#ifndef __BDK_CSRS_CDE_H__
#define __BDK_CSRS_CDE_H__
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
 * OcteonTX CDE.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration cde_bar_e
 *
 * CDE Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_CDE_BAR_E_CDEX_PF_BAR0(a) (0x80c000000000ll + 0x1000000000ll * (a))
#define BDK_CDE_BAR_E_CDEX_PF_BAR0_SIZE 0x10000000ull
#define BDK_CDE_BAR_E_CDEX_PF_BAR4(a) (0x80c010000000ll + 0x1000000000ll * (a))
#define BDK_CDE_BAR_E_CDEX_PF_BAR4_SIZE 0x100000ull
#define BDK_CDE_BAR_E_CDEX_VFX_BAR0(a,b) (0x80c020000000ll + 0x1000000000ll * (a) + 0x100000ll * (b))
#define BDK_CDE_BAR_E_CDEX_VFX_BAR0_SIZE 0x100000ull
#define BDK_CDE_BAR_E_CDEX_VFX_BAR4(a,b) (0x80c030000000ll + 0x1000000000ll * (a) + 0x100000ll * (b))
#define BDK_CDE_BAR_E_CDEX_VFX_BAR4_SIZE 0x100000ull

/**
 * Enumeration cde_pf_int_vec_e
 *
 * CDE PF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_CDE_PF_INT_VEC_E_MBOXX_CN81XX(a) (2 + (a))
#define BDK_CDE_PF_INT_VEC_E_MBOXX_CN83XX(a) (3 + (a))

/**
 * Enumeration cde_vf_int_vec_e
 *
 * CDE VF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_CDE_VF_INT_VEC_E_DONE (2)
#define BDK_CDE_VF_INT_VEC_E_MISC (0)

/**
 * Structure cde_inst_s
 *
 * CDE Instruction Structure
 * This structure specifies the instruction layout. Instructions are stored in memory
 * as little-endian unless CDE()_PF_Q()_CTL[INST_BE] is set.
 */
union bdk_cde_inst_s
{
    uint64_t u[16];
    struct bdk_cde_inst_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, CDE()_VQ()_DONE[DONE] will be incremented,
                                                                 and based on the rules described there an interrupt may occur. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, CDE()_VQ()_DONE[DONE] will be incremented,
                                                                 and based on the rules described there an interrupt may occur. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write CDE_RES_S.
                                                                 If zero, no result structure will be written.

                                                                 Bits \<3:0\> must be zero; address must be 16-byte aligned.  Bits \<63:49\> are
                                                                 ignored by hardware; software should use a sign-extended bit \<48\> for forward
                                                                 compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<3:0\> are ignored by hardware, treated as always 0x0. */
#else /* Word 1 - Little Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write CDE_RES_S.
                                                                 If zero, no result structure will be written.

                                                                 Bits \<3:0\> must be zero; address must be 16-byte aligned.  Bits \<63:49\> are
                                                                 ignored by hardware; software should use a sign-extended bit \<48\> for forward
                                                                 compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<3:0\> are ignored by hardware, treated as always 0x0. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_172_191      : 20;
        uint64_t grp                   : 10; /**< [171:162] If [WQ_PTR] is nonzero, the SSO guest-group to use when CDE submits work to
                                                                 SSO.
                                                                 For the SSO to not discard the add-work request, FPA_PF_MAP() must map
                                                                 [GRP] and CDE()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t tt                    : 2;  /**< [161:160] If [WQ_PTR] is nonzero, the SSO tag type to use when CDE submits work to SSO. */
        uint64_t tag                   : 32; /**< [159:128] If [WQ_PTR] is nonzero, the SSO tag to use when CDE submits work to SSO. */
#else /* Word 2 - Little Endian */
        uint64_t tag                   : 32; /**< [159:128] If [WQ_PTR] is nonzero, the SSO tag to use when CDE submits work to SSO. */
        uint64_t tt                    : 2;  /**< [161:160] If [WQ_PTR] is nonzero, the SSO tag type to use when CDE submits work to SSO. */
        uint64_t grp                   : 10; /**< [171:162] If [WQ_PTR] is nonzero, the SSO guest-group to use when CDE submits work to
                                                                 SSO.
                                                                 For the SSO to not discard the add-work request, FPA_PF_MAP() must map
                                                                 [GRP] and CDE()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t reserved_172_191      : 20;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that CDE submits
                                                                 work to SSO after all context, output data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:49\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<48\> for forward compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#else /* Word 3 - Little Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that CDE submits
                                                                 work to SSO after all context, output data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:49\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<48\> for forward compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t ei0                   : 64; /**< [319:256] Defined by engines. */
#else /* Word 4 - Little Endian */
        uint64_t ei0                   : 64; /**< [319:256] Defined by engines. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t ei1                   : 64; /**< [383:320] Defined by engines. */
#else /* Word 5 - Little Endian */
        uint64_t ei1                   : 64; /**< [383:320] Defined by engines. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t ei2                   : 64; /**< [447:384] Defined by engines. */
#else /* Word 6 - Little Endian */
        uint64_t ei2                   : 64; /**< [447:384] Defined by engines. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t ei3                   : 64; /**< [511:448] Defined by engines. */
#else /* Word 7 - Little Endian */
        uint64_t ei3                   : 64; /**< [511:448] Defined by engines. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t ei4                   : 64; /**< [575:512] Defined by engines. */
#else /* Word 8 - Little Endian */
        uint64_t ei4                   : 64; /**< [575:512] Defined by engines. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t ei5                   : 64; /**< [639:576] Defined by engines. */
#else /* Word 9 - Little Endian */
        uint64_t ei5                   : 64; /**< [639:576] Defined by engines. */
#endif /* Word 9 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 10 - Big Endian */
        uint64_t ei6                   : 64; /**< [703:640] Defined by engines. */
#else /* Word 10 - Little Endian */
        uint64_t ei6                   : 64; /**< [703:640] Defined by engines. */
#endif /* Word 10 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 11 - Big Endian */
        uint64_t ei7                   : 64; /**< [767:704] Defined by engines. */
#else /* Word 11 - Little Endian */
        uint64_t ei7                   : 64; /**< [767:704] Defined by engines. */
#endif /* Word 11 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 12 - Big Endian */
        uint64_t ei8                   : 64; /**< [831:768] Defined by engines. */
#else /* Word 12 - Little Endian */
        uint64_t ei8                   : 64; /**< [831:768] Defined by engines. */
#endif /* Word 12 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 13 - Big Endian */
        uint64_t ei9                   : 64; /**< [895:832] Defined by engines. */
#else /* Word 13 - Little Endian */
        uint64_t ei9                   : 64; /**< [895:832] Defined by engines. */
#endif /* Word 13 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 14 - Big Endian */
        uint64_t ei10                  : 64; /**< [959:896] Defined by engines. */
#else /* Word 14 - Little Endian */
        uint64_t ei10                  : 64; /**< [959:896] Defined by engines. */
#endif /* Word 14 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 15 - Big Endian */
        uint64_t ei11                  : 64; /**< [1023:960] Defined by engines. */
#else /* Word 15 - Little Endian */
        uint64_t ei11                  : 64; /**< [1023:960] Defined by engines. */
#endif /* Word 15 - End */
    } s;
    struct bdk_cde_inst_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, CDE()_VQ()_DONE[DONE] will be incremented,
                                                                 and based on the rules described there an interrupt may occur. */
        uint64_t reserved_8_15         : 8;
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t reserved_8_15         : 8;
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, CDE()_VQ()_DONE[DONE] will be incremented,
                                                                 and based on the rules described there an interrupt may occur. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write CDE_RES_S.
                                                                 If zero, no result structure will be written.

                                                                 Bits \<3:0\> must be zero; address must be 16-byte aligned.  Bits \<63:49\> are
                                                                 ignored by hardware; software should use a sign-extended bit \<48\> for forward
                                                                 compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<3:0\> are ignored by hardware, treated as always 0x0. */
#else /* Word 1 - Little Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write CDE_RES_S.
                                                                 If zero, no result structure will be written.

                                                                 Bits \<3:0\> must be zero; address must be 16-byte aligned.  Bits \<63:49\> are
                                                                 ignored by hardware; software should use a sign-extended bit \<48\> for forward
                                                                 compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<3:0\> are ignored by hardware, treated as always 0x0. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_172_191      : 20;
        uint64_t grp                   : 10; /**< [171:162] If [WQ_PTR] is nonzero, the SSO guest-group to use when CDE submits work to
                                                                 SSO.
                                                                 For the SSO to not discard the add-work request, FPA_PF_MAP() must map
                                                                 [GRP] and CDE()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t tt                    : 2;  /**< [161:160] If [WQ_PTR] is nonzero, the SSO tag type to use when CDE submits work to SSO. */
        uint64_t tag                   : 32; /**< [159:128] If [WQ_PTR] is nonzero, the SSO tag to use when CDE submits work to SSO. */
#else /* Word 2 - Little Endian */
        uint64_t tag                   : 32; /**< [159:128] If [WQ_PTR] is nonzero, the SSO tag to use when CDE submits work to SSO. */
        uint64_t tt                    : 2;  /**< [161:160] If [WQ_PTR] is nonzero, the SSO tag type to use when CDE submits work to SSO. */
        uint64_t grp                   : 10; /**< [171:162] If [WQ_PTR] is nonzero, the SSO guest-group to use when CDE submits work to
                                                                 SSO.
                                                                 For the SSO to not discard the add-work request, FPA_PF_MAP() must map
                                                                 [GRP] and CDE()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t reserved_172_191      : 20;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that CDE submits
                                                                 work to SSO after all context, output data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:49\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<48\> for forward compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#else /* Word 3 - Little Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that CDE submits
                                                                 work to SSO after all context, output data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:49\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<48\> for forward compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t ei0                   : 64; /**< [319:256] Defined by engines. */
#else /* Word 4 - Little Endian */
        uint64_t ei0                   : 64; /**< [319:256] Defined by engines. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t ei1                   : 64; /**< [383:320] Defined by engines. */
#else /* Word 5 - Little Endian */
        uint64_t ei1                   : 64; /**< [383:320] Defined by engines. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t ei2                   : 64; /**< [447:384] Defined by engines. */
#else /* Word 6 - Little Endian */
        uint64_t ei2                   : 64; /**< [447:384] Defined by engines. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t ei3                   : 64; /**< [511:448] Defined by engines. */
#else /* Word 7 - Little Endian */
        uint64_t ei3                   : 64; /**< [511:448] Defined by engines. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t ei4                   : 64; /**< [575:512] Defined by engines. */
#else /* Word 8 - Little Endian */
        uint64_t ei4                   : 64; /**< [575:512] Defined by engines. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t ei5                   : 64; /**< [639:576] Defined by engines. */
#else /* Word 9 - Little Endian */
        uint64_t ei5                   : 64; /**< [639:576] Defined by engines. */
#endif /* Word 9 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 10 - Big Endian */
        uint64_t ei6                   : 64; /**< [703:640] Defined by engines. */
#else /* Word 10 - Little Endian */
        uint64_t ei6                   : 64; /**< [703:640] Defined by engines. */
#endif /* Word 10 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 11 - Big Endian */
        uint64_t ei7                   : 64; /**< [767:704] Defined by engines. */
#else /* Word 11 - Little Endian */
        uint64_t ei7                   : 64; /**< [767:704] Defined by engines. */
#endif /* Word 11 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 12 - Big Endian */
        uint64_t ei8                   : 64; /**< [831:768] Defined by engines. */
#else /* Word 12 - Little Endian */
        uint64_t ei8                   : 64; /**< [831:768] Defined by engines. */
#endif /* Word 12 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 13 - Big Endian */
        uint64_t ei9                   : 64; /**< [895:832] Defined by engines. */
#else /* Word 13 - Little Endian */
        uint64_t ei9                   : 64; /**< [895:832] Defined by engines. */
#endif /* Word 13 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 14 - Big Endian */
        uint64_t ei10                  : 64; /**< [959:896] Defined by engines. */
#else /* Word 14 - Little Endian */
        uint64_t ei10                  : 64; /**< [959:896] Defined by engines. */
#endif /* Word 14 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 15 - Big Endian */
        uint64_t ei11                  : 64; /**< [1023:960] Defined by engines. */
#else /* Word 15 - Little Endian */
        uint64_t ei11                  : 64; /**< [1023:960] Defined by engines. */
#endif /* Word 15 - End */
    } cn;
};

/**
 * Structure cde_res_s
 *
 * CDE Result Structure
 * The CDE coprocessor writes the result structure after it completes a CDE_INST_S
 * instruction.
 * The result structure is exactly 16 bytes, and each instruction completion
 * produces exactly one result structure.
 *
 * This structure is stored in memory as little-endian unless CDE()_PF_Q()_CTL[INST_BE]
 * is set.
 */
union bdk_cde_res_s
{
    uint64_t u[2];
    struct bdk_cde_res_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt. This bit is copied from the corresponding instruction's
                                                                 CDE_INST_S[DONEINT]. */
        uint64_t reserved_8_15         : 8;
        uint64_t compcode              : 8;  /**< [  7:  0] Indicates completion/error status of the CDE coprocessor for the
                                                                 associated instruction, as enumerated by CDE_COMP_E. Core
                                                                 software may write the memory location containing [COMPCODE] to 0x0
                                                                 before ringing the doorbell, and then poll for completion by
                                                                 checking for a nonzero value.

                                                                 Once the core observes a nonzero [COMPCODE] value in this case, the CDE
                                                                 coprocessor will have also completed L2/DRAM write operations. */
#else /* Word 0 - Little Endian */
        uint64_t compcode              : 8;  /**< [  7:  0] Indicates completion/error status of the CDE coprocessor for the
                                                                 associated instruction, as enumerated by CDE_COMP_E. Core
                                                                 software may write the memory location containing [COMPCODE] to 0x0
                                                                 before ringing the doorbell, and then poll for completion by
                                                                 checking for a nonzero value.

                                                                 Once the core observes a nonzero [COMPCODE] value in this case, the CDE
                                                                 coprocessor will have also completed L2/DRAM write operations. */
        uint64_t reserved_8_15         : 8;
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt. This bit is copied from the corresponding instruction's
                                                                 CDE_INST_S[DONEINT]. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_64_127       : 64;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_127       : 64;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_cde_res_s_s cn; */
};

/**
 * Register (NCB) cde#_cqm_core_obs0
 *
 * INTERNAL: CDE CQM Core Observability Debug Register
 */
union bdk_cdex_cqm_core_obs0
{
    uint64_t u;
    struct bdk_cdex_cqm_core_obs0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t instfif7_cnt          : 8;  /**< [ 63: 56](RO/H) Number of instruction words prefetched for group 7. */
        uint64_t instfif6_cnt          : 8;  /**< [ 55: 48](RO/H) Number of instruction words prefetched for group 6. */
        uint64_t instfif5_cnt          : 8;  /**< [ 47: 40](RO/H) Number of instruction words prefetched for group 5. */
        uint64_t instfif4_cnt          : 8;  /**< [ 39: 32](RO/H) Number of instruction words prefetched for group 4. */
        uint64_t instfif3_cnt          : 8;  /**< [ 31: 24](RO/H) Number of instruction words prefetched for group 3. */
        uint64_t instfif2_cnt          : 8;  /**< [ 23: 16](RO/H) Number of instruction words prefetched for group 2. */
        uint64_t instfif1_cnt          : 8;  /**< [ 15:  8](RO/H) Number of instruction words prefetched for group 1. */
        uint64_t instfif0_cnt          : 8;  /**< [  7:  0](RO/H) Number of instruction words prefetched for group 0. */
#else /* Word 0 - Little Endian */
        uint64_t instfif0_cnt          : 8;  /**< [  7:  0](RO/H) Number of instruction words prefetched for group 0. */
        uint64_t instfif1_cnt          : 8;  /**< [ 15:  8](RO/H) Number of instruction words prefetched for group 1. */
        uint64_t instfif2_cnt          : 8;  /**< [ 23: 16](RO/H) Number of instruction words prefetched for group 2. */
        uint64_t instfif3_cnt          : 8;  /**< [ 31: 24](RO/H) Number of instruction words prefetched for group 3. */
        uint64_t instfif4_cnt          : 8;  /**< [ 39: 32](RO/H) Number of instruction words prefetched for group 4. */
        uint64_t instfif5_cnt          : 8;  /**< [ 47: 40](RO/H) Number of instruction words prefetched for group 5. */
        uint64_t instfif6_cnt          : 8;  /**< [ 55: 48](RO/H) Number of instruction words prefetched for group 6. */
        uint64_t instfif7_cnt          : 8;  /**< [ 63: 56](RO/H) Number of instruction words prefetched for group 7. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_cqm_core_obs0_s cn; */
};
typedef union bdk_cdex_cqm_core_obs0 bdk_cdex_cqm_core_obs0_t;

static inline uint64_t BDK_CDEX_CQM_CORE_OBS0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_CQM_CORE_OBS0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c0000001a0ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_CQM_CORE_OBS0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_CQM_CORE_OBS0(a) bdk_cdex_cqm_core_obs0_t
#define bustype_BDK_CDEX_CQM_CORE_OBS0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_CQM_CORE_OBS0(a) "CDEX_CQM_CORE_OBS0"
#define device_bar_BDK_CDEX_CQM_CORE_OBS0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_CQM_CORE_OBS0(a) (a)
#define arguments_BDK_CDEX_CQM_CORE_OBS0(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_cqm_core_obs1
 *
 * INTERNAL: CDE CQM Core Observability Debug Register
 */
union bdk_cdex_cqm_core_obs1
{
    uint64_t u;
    struct bdk_cdex_cqm_core_obs1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t ncbi_ptr_req          : 1;  /**< [ 49: 49](RO/H) CQM_CORE is waiting to issue an NCBI Request for instruction pointer fetch */
        uint64_t ncbi_req_rdy          : 1;  /**< [ 48: 48](RO/H) CQM_CORE is waiting to issue an NCBI Request for instruction fetch */
        uint64_t grp_rdy_hi_pri        : 8;  /**< [ 47: 40](RO/H) If set the corresponding group has high priority queues waiting to fetch
                                                                 instructions. */
        uint64_t grp_rdy_lo_pri        : 8;  /**< [ 39: 32](RO/H) If set the corresponding group has low priority queues waiting to fetch */
        uint64_t vqfif7_cnt            : 4;  /**< [ 31: 28](RO/H) Number of instructions getting prefetched for group 7. */
        uint64_t vqfif6_cnt            : 4;  /**< [ 27: 24](RO/H) Number of instructions getting prefetched for group 6. */
        uint64_t vqfif5_cnt            : 4;  /**< [ 23: 20](RO/H) Number of instructions getting prefetched for group 5. */
        uint64_t vqfif4_cnt            : 4;  /**< [ 19: 16](RO/H) Number of instructions getting prefetched for group 4. */
        uint64_t vqfif3_cnt            : 4;  /**< [ 15: 12](RO/H) Number of instructions getting prefetched for group 3. */
        uint64_t vqfif2_cnt            : 4;  /**< [ 11:  8](RO/H) Number of instructions getting prefetched for group 2. */
        uint64_t vqfif1_cnt            : 4;  /**< [  7:  4](RO/H) Number of instructions getting prefetched for group 1. */
        uint64_t vqfif0_cnt            : 4;  /**< [  3:  0](RO/H) Number of instructions getting prefetched for group 0. */
#else /* Word 0 - Little Endian */
        uint64_t vqfif0_cnt            : 4;  /**< [  3:  0](RO/H) Number of instructions getting prefetched for group 0. */
        uint64_t vqfif1_cnt            : 4;  /**< [  7:  4](RO/H) Number of instructions getting prefetched for group 1. */
        uint64_t vqfif2_cnt            : 4;  /**< [ 11:  8](RO/H) Number of instructions getting prefetched for group 2. */
        uint64_t vqfif3_cnt            : 4;  /**< [ 15: 12](RO/H) Number of instructions getting prefetched for group 3. */
        uint64_t vqfif4_cnt            : 4;  /**< [ 19: 16](RO/H) Number of instructions getting prefetched for group 4. */
        uint64_t vqfif5_cnt            : 4;  /**< [ 23: 20](RO/H) Number of instructions getting prefetched for group 5. */
        uint64_t vqfif6_cnt            : 4;  /**< [ 27: 24](RO/H) Number of instructions getting prefetched for group 6. */
        uint64_t vqfif7_cnt            : 4;  /**< [ 31: 28](RO/H) Number of instructions getting prefetched for group 7. */
        uint64_t grp_rdy_lo_pri        : 8;  /**< [ 39: 32](RO/H) If set the corresponding group has low priority queues waiting to fetch */
        uint64_t grp_rdy_hi_pri        : 8;  /**< [ 47: 40](RO/H) If set the corresponding group has high priority queues waiting to fetch
                                                                 instructions. */
        uint64_t ncbi_req_rdy          : 1;  /**< [ 48: 48](RO/H) CQM_CORE is waiting to issue an NCBI Request for instruction fetch */
        uint64_t ncbi_ptr_req          : 1;  /**< [ 49: 49](RO/H) CQM_CORE is waiting to issue an NCBI Request for instruction pointer fetch */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_cqm_core_obs1_s cn; */
};
typedef union bdk_cdex_cqm_core_obs1 bdk_cdex_cqm_core_obs1_t;

static inline uint64_t BDK_CDEX_CQM_CORE_OBS1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_CQM_CORE_OBS1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c0000001a8ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_CQM_CORE_OBS1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_CQM_CORE_OBS1(a) bdk_cdex_cqm_core_obs1_t
#define bustype_BDK_CDEX_CQM_CORE_OBS1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_CQM_CORE_OBS1(a) "CDEX_CQM_CORE_OBS1"
#define device_bar_BDK_CDEX_CQM_CORE_OBS1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_CQM_CORE_OBS1(a) (a)
#define arguments_BDK_CDEX_CQM_CORE_OBS1(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_ncbi_obs
 *
 * INTERNAL: CDE NCBI Observability Debug Register
 */
union bdk_cdex_ncbi_obs
{
    uint64_t u;
    struct bdk_cdex_ncbi_obs_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t datfif_cnt            : 8;  /**< [ 39: 32](RO/H) Number of pending data cycles to be sent to NCBI. */
        uint64_t cmdfif_cnt            : 8;  /**< [ 31: 24](RO/H) Number of pending commands to be sent to NCBI. */
        uint64_t reserved_22_23        : 2;
        uint64_t csr_rsp_dat           : 1;  /**< [ 21: 21](RO/H) CSR Response data available to be sent to NCBI.                                            . */
        uint64_t csr_rsp_val           : 1;  /**< [ 20: 20](RO/H) CSR Response available to be sent to NCBI. */
        uint64_t csr_cc_req            : 4;  /**< [ 19: 16](RO/H) Transfer cycles requested for CSR responses. */
        uint64_t res_cc_req            : 4;  /**< [ 15: 12](RO/H) Transfer cycles requested for result structure stores. */
        uint64_t ifc_cc_req            : 4;  /**< [ 11:  8](RO/H) Transfer cycles requested for instruction fetches. */
        uint64_t eng_cc_req            : 4;  /**< [  7:  4](RO/H) Transfer cycles requested from the engines. */
        uint64_t cdei_cc_left          : 4;  /**< [  3:  0](RO/H) Transfer cycles remaining to complete receiving transaction from CDE_NCBI input. */
#else /* Word 0 - Little Endian */
        uint64_t cdei_cc_left          : 4;  /**< [  3:  0](RO/H) Transfer cycles remaining to complete receiving transaction from CDE_NCBI input. */
        uint64_t eng_cc_req            : 4;  /**< [  7:  4](RO/H) Transfer cycles requested from the engines. */
        uint64_t ifc_cc_req            : 4;  /**< [ 11:  8](RO/H) Transfer cycles requested for instruction fetches. */
        uint64_t res_cc_req            : 4;  /**< [ 15: 12](RO/H) Transfer cycles requested for result structure stores. */
        uint64_t csr_cc_req            : 4;  /**< [ 19: 16](RO/H) Transfer cycles requested for CSR responses. */
        uint64_t csr_rsp_val           : 1;  /**< [ 20: 20](RO/H) CSR Response available to be sent to NCBI. */
        uint64_t csr_rsp_dat           : 1;  /**< [ 21: 21](RO/H) CSR Response data available to be sent to NCBI.                                            . */
        uint64_t reserved_22_23        : 2;
        uint64_t cmdfif_cnt            : 8;  /**< [ 31: 24](RO/H) Number of pending commands to be sent to NCBI. */
        uint64_t datfif_cnt            : 8;  /**< [ 39: 32](RO/H) Number of pending data cycles to be sent to NCBI. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_ncbi_obs_s cn; */
};
typedef union bdk_cdex_ncbi_obs bdk_cdex_ncbi_obs_t;

static inline uint64_t BDK_CDEX_NCBI_OBS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_NCBI_OBS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000000190ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_NCBI_OBS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_NCBI_OBS(a) bdk_cdex_ncbi_obs_t
#define bustype_BDK_CDEX_NCBI_OBS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_NCBI_OBS(a) "CDEX_NCBI_OBS"
#define device_bar_BDK_CDEX_NCBI_OBS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_NCBI_OBS(a) (a)
#define arguments_BDK_CDEX_NCBI_OBS(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_active_cycles_pc
 *
 * CDE PF Active Cycles Register
 */
union bdk_cdex_pf_active_cycles_pc
{
    uint64_t u;
    struct bdk_cdex_pf_active_cycles_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the conditional clocks are active.
                                                                 Internal:
                                                                 Includes CDE internal or any engine clock being enabled. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the conditional clocks are active.
                                                                 Internal:
                                                                 Includes CDE internal or any engine clock being enabled. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_active_cycles_pc_s cn; */
};
typedef union bdk_cdex_pf_active_cycles_pc bdk_cdex_pf_active_cycles_pc_t;

static inline uint64_t BDK_CDEX_PF_ACTIVE_CYCLES_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_ACTIVE_CYCLES_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000010100ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_PF_ACTIVE_CYCLES_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_ACTIVE_CYCLES_PC(a) bdk_cdex_pf_active_cycles_pc_t
#define bustype_BDK_CDEX_PF_ACTIVE_CYCLES_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_ACTIVE_CYCLES_PC(a) "CDEX_PF_ACTIVE_CYCLES_PC"
#define device_bar_BDK_CDEX_PF_ACTIVE_CYCLES_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_ACTIVE_CYCLES_PC(a) (a)
#define arguments_BDK_CDEX_PF_ACTIVE_CYCLES_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_bp_test
 *
 * INTERNAL: CDE PF Backpressure Test Register
 */
union bdk_cdex_pf_bp_test
{
    uint64_t u;
    struct bdk_cdex_pf_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = NCBI requests.
                                                                 \<62\> = Instruction prefetching.
                                                                 \<61\> = GMID RAM access arbitration.
                                                                 \<60\> = Reserved. */
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
                                                                 \<63\> = NCBI requests.
                                                                 \<62\> = Instruction prefetching.
                                                                 \<61\> = GMID RAM access arbitration.
                                                                 \<60\> = Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_bp_test_s cn; */
};
typedef union bdk_cdex_pf_bp_test bdk_cdex_pf_bp_test_t;

static inline uint64_t BDK_CDEX_PF_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_BP_TEST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000000180ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_PF_BP_TEST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_BP_TEST(a) bdk_cdex_pf_bp_test_t
#define bustype_BDK_CDEX_PF_BP_TEST(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_BP_TEST(a) "CDEX_PF_BP_TEST"
#define device_bar_BDK_CDEX_PF_BP_TEST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_BP_TEST(a) (a)
#define arguments_BDK_CDEX_PF_BP_TEST(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_diag
 *
 * CDE PF Diagnostic Control Register
 * This register controls diagnostic features.
 */
union bdk_cdex_pf_diag
{
    uint64_t u;
    struct bdk_cdex_pf_diag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t forceclk              : 1;  /**< [  8:  8](R/W) When this bit is set to 1, it forces CDE clocks on. For diagnostic use only. */
        uint64_t ld_infl               : 8;  /**< [  7:  0](R/W) Maximum number of in-flight data fetch transactions on the NCB. Larger values
                                                                 may improve CDE performance but may starve other devices on the same NCB. Values
                                                                 \> 64 are treated as 64. */
#else /* Word 0 - Little Endian */
        uint64_t ld_infl               : 8;  /**< [  7:  0](R/W) Maximum number of in-flight data fetch transactions on the NCB. Larger values
                                                                 may improve CDE performance but may starve other devices on the same NCB. Values
                                                                 \> 64 are treated as 64. */
        uint64_t forceclk              : 1;  /**< [  8:  8](R/W) When this bit is set to 1, it forces CDE clocks on. For diagnostic use only. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_diag_s cn; */
};
typedef union bdk_cdex_pf_diag bdk_cdex_pf_diag_t;

static inline uint64_t BDK_CDEX_PF_DIAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_DIAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000000120ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_PF_DIAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_DIAG(a) bdk_cdex_pf_diag_t
#define bustype_BDK_CDEX_PF_DIAG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_DIAG(a) "CDEX_PF_DIAG"
#define device_bar_BDK_CDEX_PF_DIAG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_DIAG(a) (a)
#define arguments_BDK_CDEX_PF_DIAG(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_eco
 *
 * INTERNAL: CDE PF ECO Register
 */
union bdk_cdex_pf_eco
{
    uint64_t u;
    struct bdk_cdex_pf_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_eco_s cn; */
};
typedef union bdk_cdex_pf_eco bdk_cdex_pf_eco_t;

static inline uint64_t BDK_CDEX_PF_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000000140ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_PF_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_ECO(a) bdk_cdex_pf_eco_t
#define bustype_BDK_CDEX_PF_ECO(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_ECO(a) "CDEX_PF_ECO"
#define device_bar_BDK_CDEX_PF_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_ECO(a) (a)
#define arguments_BDK_CDEX_PF_ECO(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_inst_latency_pc
 *
 * CDE PF Instruction Latency Counter Register
 */
union bdk_cdex_pf_inst_latency_pc
{
    uint64_t u;
    struct bdk_cdex_pf_inst_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for an instruction to complete (have the store of
                                                                 CDE_RES_S reach the commit point). Incremented every coprocessor-clock by the
                                                                 number of instructions active in that cycle. This may be divided by
                                                                 CDE()_PF_RD_REQ_PC to determine the average hardware instruction latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for an instruction to complete (have the store of
                                                                 CDE_RES_S reach the commit point). Incremented every coprocessor-clock by the
                                                                 number of instructions active in that cycle. This may be divided by
                                                                 CDE()_PF_RD_REQ_PC to determine the average hardware instruction latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_inst_latency_pc_s cn; */
};
typedef union bdk_cdex_pf_inst_latency_pc bdk_cdex_pf_inst_latency_pc_t;

static inline uint64_t BDK_CDEX_PF_INST_LATENCY_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_INST_LATENCY_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000010020ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_PF_INST_LATENCY_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_INST_LATENCY_PC(a) bdk_cdex_pf_inst_latency_pc_t
#define bustype_BDK_CDEX_PF_INST_LATENCY_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_INST_LATENCY_PC(a) "CDEX_PF_INST_LATENCY_PC"
#define device_bar_BDK_CDEX_PF_INST_LATENCY_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_INST_LATENCY_PC(a) (a)
#define arguments_BDK_CDEX_PF_INST_LATENCY_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_inst_req_pc
 *
 * CDE PF Instruction Request Performance Counter Register
 */
union bdk_cdex_pf_inst_req_pc
{
    uint64_t u;
    struct bdk_cdex_pf_inst_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of instructions that have started processing. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of instructions that have started processing. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_inst_req_pc_s cn; */
};
typedef union bdk_cdex_pf_inst_req_pc bdk_cdex_pf_inst_req_pc_t;

static inline uint64_t BDK_CDEX_PF_INST_REQ_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_INST_REQ_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000010000ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_PF_INST_REQ_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_INST_REQ_PC(a) bdk_cdex_pf_inst_req_pc_t
#define bustype_BDK_CDEX_PF_INST_REQ_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_INST_REQ_PC(a) "CDEX_PF_INST_REQ_PC"
#define device_bar_BDK_CDEX_PF_INST_REQ_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_INST_REQ_PC(a) (a)
#define arguments_BDK_CDEX_PF_INST_REQ_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_mbox_ena_w1c#
 *
 * CDE PF Mailbox Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_cdex_pf_mbox_ena_w1cx
{
    uint64_t u;
    struct bdk_cdex_pf_mbox_ena_w1cx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for CDE(0)_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for CDE(0)_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_mbox_ena_w1cx_s cn; */
};
typedef union bdk_cdex_pf_mbox_ena_w1cx bdk_cdex_pf_mbox_ena_w1cx_t;

static inline uint64_t BDK_CDEX_PF_MBOX_ENA_W1CX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_MBOX_ENA_W1CX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && ((a==0) && (b==0)))
        return 0x80c000000440ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("CDEX_PF_MBOX_ENA_W1CX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_MBOX_ENA_W1CX(a,b) bdk_cdex_pf_mbox_ena_w1cx_t
#define bustype_BDK_CDEX_PF_MBOX_ENA_W1CX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_MBOX_ENA_W1CX(a,b) "CDEX_PF_MBOX_ENA_W1CX"
#define device_bar_BDK_CDEX_PF_MBOX_ENA_W1CX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_MBOX_ENA_W1CX(a,b) (a)
#define arguments_BDK_CDEX_PF_MBOX_ENA_W1CX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_pf_mbox_ena_w1s#
 *
 * CDE PF Mailbox Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_cdex_pf_mbox_ena_w1sx
{
    uint64_t u;
    struct bdk_cdex_pf_mbox_ena_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for CDE(0)_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for CDE(0)_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_mbox_ena_w1sx_s cn; */
};
typedef union bdk_cdex_pf_mbox_ena_w1sx bdk_cdex_pf_mbox_ena_w1sx_t;

static inline uint64_t BDK_CDEX_PF_MBOX_ENA_W1SX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_MBOX_ENA_W1SX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && ((a==0) && (b==0)))
        return 0x80c000000460ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("CDEX_PF_MBOX_ENA_W1SX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_MBOX_ENA_W1SX(a,b) bdk_cdex_pf_mbox_ena_w1sx_t
#define bustype_BDK_CDEX_PF_MBOX_ENA_W1SX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_MBOX_ENA_W1SX(a,b) "CDEX_PF_MBOX_ENA_W1SX"
#define device_bar_BDK_CDEX_PF_MBOX_ENA_W1SX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_MBOX_ENA_W1SX(a,b) (a)
#define arguments_BDK_CDEX_PF_MBOX_ENA_W1SX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_pf_mbox_int#
 *
 * CDE PF Mailbox Interrupt Registers
 */
union bdk_cdex_pf_mbox_intx
{
    uint64_t u;
    struct bdk_cdex_pf_mbox_intx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF. Each bit is set when the associated
                                                                 CDE()_VF()_PF_MBOX(1) is written. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF. Each bit is set when the associated
                                                                 CDE()_VF()_PF_MBOX(1) is written. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_mbox_intx_s cn; */
};
typedef union bdk_cdex_pf_mbox_intx bdk_cdex_pf_mbox_intx_t;

static inline uint64_t BDK_CDEX_PF_MBOX_INTX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_MBOX_INTX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && ((a==0) && (b==0)))
        return 0x80c000000400ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("CDEX_PF_MBOX_INTX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_MBOX_INTX(a,b) bdk_cdex_pf_mbox_intx_t
#define bustype_BDK_CDEX_PF_MBOX_INTX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_MBOX_INTX(a,b) "CDEX_PF_MBOX_INTX"
#define device_bar_BDK_CDEX_PF_MBOX_INTX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_MBOX_INTX(a,b) (a)
#define arguments_BDK_CDEX_PF_MBOX_INTX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_pf_mbox_int_w1s#
 *
 * CDE PF Mailbox Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_cdex_pf_mbox_int_w1sx
{
    uint64_t u;
    struct bdk_cdex_pf_mbox_int_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets CDE(0)_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets CDE(0)_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_mbox_int_w1sx_s cn; */
};
typedef union bdk_cdex_pf_mbox_int_w1sx bdk_cdex_pf_mbox_int_w1sx_t;

static inline uint64_t BDK_CDEX_PF_MBOX_INT_W1SX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_MBOX_INT_W1SX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && ((a==0) && (b==0)))
        return 0x80c000000420ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("CDEX_PF_MBOX_INT_W1SX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_MBOX_INT_W1SX(a,b) bdk_cdex_pf_mbox_int_w1sx_t
#define bustype_BDK_CDEX_PF_MBOX_INT_W1SX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_MBOX_INT_W1SX(a,b) "CDEX_PF_MBOX_INT_W1SX"
#define device_bar_BDK_CDEX_PF_MBOX_INT_W1SX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_MBOX_INT_W1SX(a,b) (a)
#define arguments_BDK_CDEX_PF_MBOX_INT_W1SX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_pf_msix_pba#
 *
 * CDE PF MSI-X Pending-Bit-Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the
 * CDE_PF_INT_VEC_E enumeration.
 */
union bdk_cdex_pf_msix_pbax
{
    uint64_t u;
    struct bdk_cdex_pf_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated CDE()_PF_MSIX_VEC()_CTL, enumerated by
                                                                 CDE_PF_INT_VEC_E. Bits that have no associated CDE_PF_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated CDE()_PF_MSIX_VEC()_CTL, enumerated by
                                                                 CDE_PF_INT_VEC_E. Bits that have no associated CDE_PF_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_msix_pbax_s cn; */
};
typedef union bdk_cdex_pf_msix_pbax bdk_cdex_pf_msix_pbax_t;

static inline uint64_t BDK_CDEX_PF_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && ((a==0) && (b==0)))
        return 0x80c0100f0000ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("CDEX_PF_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_MSIX_PBAX(a,b) bdk_cdex_pf_msix_pbax_t
#define bustype_BDK_CDEX_PF_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_MSIX_PBAX(a,b) "CDEX_PF_MSIX_PBAX"
#define device_bar_BDK_CDEX_PF_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_CDEX_PF_MSIX_PBAX(a,b) (a)
#define arguments_BDK_CDEX_PF_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_pf_msix_vec#_addr
 *
 * CDE PF MSI-X Vector-Table Address Registers
 * This register is the MSI-X vector table, indexed by the CDE_PF_INT_VEC_E enumeration.
 */
union bdk_cdex_pf_msix_vecx_addr
{
    uint64_t u;
    struct bdk_cdex_pf_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's CDE()_PF_MSIX_VEC()_ADDR, CDE()_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of CDE()_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_CDE_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's CDE()_PF_MSIX_VEC()_ADDR, CDE()_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of CDE()_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_CDE_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_msix_vecx_addr_s cn; */
};
typedef union bdk_cdex_pf_msix_vecx_addr bdk_cdex_pf_msix_vecx_addr_t;

static inline uint64_t BDK_CDEX_PF_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=2)))
        return 0x80c010000000ll + 0x1000000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=3)))
        return 0x80c010000000ll + 0x1000000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("CDEX_PF_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_MSIX_VECX_ADDR(a,b) bdk_cdex_pf_msix_vecx_addr_t
#define bustype_BDK_CDEX_PF_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_MSIX_VECX_ADDR(a,b) "CDEX_PF_MSIX_VECX_ADDR"
#define device_bar_BDK_CDEX_PF_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_CDEX_PF_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_CDEX_PF_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_pf_msix_vec#_ctl
 *
 * CDE PF MSI-X Vector-Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the CDE_PF_INT_VEC_E enumeration.
 */
union bdk_cdex_pf_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_cdex_pf_msix_vecx_ctl_s
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
    /* struct bdk_cdex_pf_msix_vecx_ctl_s cn; */
};
typedef union bdk_cdex_pf_msix_vecx_ctl bdk_cdex_pf_msix_vecx_ctl_t;

static inline uint64_t BDK_CDEX_PF_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=2)))
        return 0x80c010000008ll + 0x1000000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=3)))
        return 0x80c010000008ll + 0x1000000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("CDEX_PF_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_MSIX_VECX_CTL(a,b) bdk_cdex_pf_msix_vecx_ctl_t
#define bustype_BDK_CDEX_PF_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_MSIX_VECX_CTL(a,b) "CDEX_PF_MSIX_VECX_CTL"
#define device_bar_BDK_CDEX_PF_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_CDEX_PF_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_CDEX_PF_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_pf_q#_ctl
 *
 * CDE Queue Control Register
 * This register configures queues. This register should be changed only when quiescent
 * (see CDE()_VQ()_INPROG[INFLIGHT]).
 */
union bdk_cdex_pf_qx_ctl
{
    uint64_t u;
    struct bdk_cdex_pf_qx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t aura                  : 12; /**< [ 59: 48](R/W) Guest-aura for returning this queue's instruction-chunk buffers to FPA.
                                                                 Only used when [INST_FREE] is set.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and CDE()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t reserved_45_47        : 3;
        uint64_t size                  : 13; /**< [ 44: 32](R/W) Command-buffer size, in number of 64-bit words per command buffer segment.
                                                                 Must be {a}*n + 1, where n is the number of instructions per buffer segment,
                                                                 and {a} is 8 for CPT or 16 for DDF. The plus one is for the next-chunk pointer. */
        uint64_t reserved_11_31        : 21;
        uint64_t cont_err              : 1;  /**< [ 10: 10](R/W) Continue on error.

                                                                 0 = When CDE()_VQ()_MISC_INT[HWERR], CDE()_VQ()_MISC_INT[SWERR],
                                                                 CDE()_VQ()_MISC_INT[NWRP], CDE()_VQ()_MISC_INT[IRDE],
                                                                 CDE()_VQ()_MISC_INT[FAULT], or
                                                                 CDE()_VQ()_MISC_INT[DOVF] are set by hardware or software via
                                                                 CDE()_VQ()_MISC_INT_W1S, then CDE()_VQ()_CTL[ENA] is cleared.  Due to
                                                                 pipelining, additional instructions may have been processed between the
                                                                 instruction causing the error and the next instruction in the disabled queue
                                                                 (the instruction at CDE()_VQ()_SADDR).

                                                                 1 = Ignore errors and continue processing instructions. For diagnostic use only. */
        uint64_t inst_free             : 1;  /**< [  9:  9](R/W) Instruction FPA free. When set, when CDE reaches the end of an instruction
                                                                 chunk, that chunk will be freed to the FPA. */
        uint64_t inst_be               : 1;  /**< [  8:  8](R/W) Instruction big-endian control. When set, instructions, instruction next chunk
                                                                 pointers, and result structures are stored in big-endian format in memory. */
        uint64_t iqb_ldwb              : 1;  /**< [  7:  7](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues NCB transient load (LDT) towards the cache, which if the
                                                                 line hits and is is dirty will cause the line to be written back before being
                                                                 replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Reads that do not consume the last word of a cache line always use LDI. */
        uint64_t reserved_4_6          : 3;
        uint64_t grp                   : 3;  /**< [  3:  1](R/W) Engine group. */
        uint64_t pri                   : 1;  /**< [  0:  0](R/W) Queue priority.
                                                                 1 = This queue has higher priority. Round-robin between higher priority queues.
                                                                 0 = This queue has lower priority. Round-robin between lower priority queues. */
#else /* Word 0 - Little Endian */
        uint64_t pri                   : 1;  /**< [  0:  0](R/W) Queue priority.
                                                                 1 = This queue has higher priority. Round-robin between higher priority queues.
                                                                 0 = This queue has lower priority. Round-robin between lower priority queues. */
        uint64_t grp                   : 3;  /**< [  3:  1](R/W) Engine group. */
        uint64_t reserved_4_6          : 3;
        uint64_t iqb_ldwb              : 1;  /**< [  7:  7](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues NCB transient load (LDT) towards the cache, which if the
                                                                 line hits and is is dirty will cause the line to be written back before being
                                                                 replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Reads that do not consume the last word of a cache line always use LDI. */
        uint64_t inst_be               : 1;  /**< [  8:  8](R/W) Instruction big-endian control. When set, instructions, instruction next chunk
                                                                 pointers, and result structures are stored in big-endian format in memory. */
        uint64_t inst_free             : 1;  /**< [  9:  9](R/W) Instruction FPA free. When set, when CDE reaches the end of an instruction
                                                                 chunk, that chunk will be freed to the FPA. */
        uint64_t cont_err              : 1;  /**< [ 10: 10](R/W) Continue on error.

                                                                 0 = When CDE()_VQ()_MISC_INT[HWERR], CDE()_VQ()_MISC_INT[SWERR],
                                                                 CDE()_VQ()_MISC_INT[NWRP], CDE()_VQ()_MISC_INT[IRDE],
                                                                 CDE()_VQ()_MISC_INT[FAULT], or
                                                                 CDE()_VQ()_MISC_INT[DOVF] are set by hardware or software via
                                                                 CDE()_VQ()_MISC_INT_W1S, then CDE()_VQ()_CTL[ENA] is cleared.  Due to
                                                                 pipelining, additional instructions may have been processed between the
                                                                 instruction causing the error and the next instruction in the disabled queue
                                                                 (the instruction at CDE()_VQ()_SADDR).

                                                                 1 = Ignore errors and continue processing instructions. For diagnostic use only. */
        uint64_t reserved_11_31        : 21;
        uint64_t size                  : 13; /**< [ 44: 32](R/W) Command-buffer size, in number of 64-bit words per command buffer segment.
                                                                 Must be {a}*n + 1, where n is the number of instructions per buffer segment,
                                                                 and {a} is 8 for CPT or 16 for DDF. The plus one is for the next-chunk pointer. */
        uint64_t reserved_45_47        : 3;
        uint64_t aura                  : 12; /**< [ 59: 48](R/W) Guest-aura for returning this queue's instruction-chunk buffers to FPA.
                                                                 Only used when [INST_FREE] is set.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and CDE()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_qx_ctl_s cn8; */
    /* struct bdk_cdex_pf_qx_ctl_s cn81xx; */
    struct bdk_cdex_pf_qx_ctl_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t aura                  : 12; /**< [ 59: 48](R/W) Guest-aura for returning this queue's instruction-chunk buffers to FPA.
                                                                 Only used when [INST_FREE] is set.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and CDE()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t reserved_45_47        : 3;
        uint64_t size                  : 13; /**< [ 44: 32](R/W) Command-buffer size, in number of 64-bit words per command buffer segment.
                                                                 Must be {a}*n + 1, where n is the number of instructions per buffer segment,
                                                                 and {a} is 8 for CPT or 16 for DDF. The plus one is for the next-chunk pointer. */
        uint64_t reserved_11_31        : 21;
        uint64_t cont_err              : 1;  /**< [ 10: 10](R/W) Continue on error.

                                                                 0 = When CDE()_VQ()_MISC_INT[SWERR],
                                                                 CDE()_VQ()_MISC_INT[NWRP], CDE()_VQ()_MISC_INT[IRDE],
                                                                 CDE()_VQ()_MISC_INT[FAULT], or
                                                                 CDE()_VQ()_MISC_INT[DOVF] are set by hardware or software via
                                                                 CDE()_VQ()_MISC_INT_W1S, then CDE()_VQ()_CTL[ENA] is cleared.  Due to
                                                                 pipelining, additional instructions may have been processed between the
                                                                 instruction causing the error and the next instruction in the disabled queue
                                                                 (the instruction at CDE()_VQ()_SADDR).

                                                                 1 = Ignore errors and continue processing instructions. For diagnostic use only. */
        uint64_t inst_free             : 1;  /**< [  9:  9](R/W) Instruction FPA free. When set, when CDE reaches the end of an instruction
                                                                 chunk, that chunk will be freed to the FPA. */
        uint64_t inst_be               : 1;  /**< [  8:  8](R/W) Instruction big-endian control. When set, instructions, instruction next chunk
                                                                 pointers, and result structures are stored in big-endian format in memory. */
        uint64_t iqb_ldwb              : 1;  /**< [  7:  7](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues NCB transient load (LDT) towards the cache, which if the
                                                                 line hits and is is dirty will cause the line to be written back before being
                                                                 replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Reads that do not consume the last word of a cache line always use LDI. */
        uint64_t reserved_4_6          : 3;
        uint64_t grp                   : 3;  /**< [  3:  1](R/W) Engine group. */
        uint64_t pri                   : 1;  /**< [  0:  0](R/W) Queue priority.
                                                                 1 = This queue has higher priority. Round-robin between higher priority queues.
                                                                 0 = This queue has lower priority. Round-robin between lower priority queues. */
#else /* Word 0 - Little Endian */
        uint64_t pri                   : 1;  /**< [  0:  0](R/W) Queue priority.
                                                                 1 = This queue has higher priority. Round-robin between higher priority queues.
                                                                 0 = This queue has lower priority. Round-robin between lower priority queues. */
        uint64_t grp                   : 3;  /**< [  3:  1](R/W) Engine group. */
        uint64_t reserved_4_6          : 3;
        uint64_t iqb_ldwb              : 1;  /**< [  7:  7](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues NCB transient load (LDT) towards the cache, which if the
                                                                 line hits and is is dirty will cause the line to be written back before being
                                                                 replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Reads that do not consume the last word of a cache line always use LDI. */
        uint64_t inst_be               : 1;  /**< [  8:  8](R/W) Instruction big-endian control. When set, instructions, instruction next chunk
                                                                 pointers, and result structures are stored in big-endian format in memory. */
        uint64_t inst_free             : 1;  /**< [  9:  9](R/W) Instruction FPA free. When set, when CDE reaches the end of an instruction
                                                                 chunk, that chunk will be freed to the FPA. */
        uint64_t cont_err              : 1;  /**< [ 10: 10](R/W) Continue on error.

                                                                 0 = When CDE()_VQ()_MISC_INT[SWERR],
                                                                 CDE()_VQ()_MISC_INT[NWRP], CDE()_VQ()_MISC_INT[IRDE],
                                                                 CDE()_VQ()_MISC_INT[FAULT], or
                                                                 CDE()_VQ()_MISC_INT[DOVF] are set by hardware or software via
                                                                 CDE()_VQ()_MISC_INT_W1S, then CDE()_VQ()_CTL[ENA] is cleared.  Due to
                                                                 pipelining, additional instructions may have been processed between the
                                                                 instruction causing the error and the next instruction in the disabled queue
                                                                 (the instruction at CDE()_VQ()_SADDR).

                                                                 1 = Ignore errors and continue processing instructions. For diagnostic use only. */
        uint64_t reserved_11_31        : 21;
        uint64_t size                  : 13; /**< [ 44: 32](R/W) Command-buffer size, in number of 64-bit words per command buffer segment.
                                                                 Must be {a}*n + 1, where n is the number of instructions per buffer segment,
                                                                 and {a} is 8 for CPT or 16 for DDF. The plus one is for the next-chunk pointer. */
        uint64_t reserved_45_47        : 3;
        uint64_t aura                  : 12; /**< [ 59: 48](R/W) Guest-aura for returning this queue's instruction-chunk buffers to FPA.
                                                                 Only used when [INST_FREE] is set.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and CDE()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_cdex_pf_qx_ctl bdk_cdex_pf_qx_ctl_t;

static inline uint64_t BDK_CDEX_PF_QX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_QX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c008000000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c008000000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_PF_QX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_QX_CTL(a,b) bdk_cdex_pf_qx_ctl_t
#define bustype_BDK_CDEX_PF_QX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_QX_CTL(a,b) "CDEX_PF_QX_CTL"
#define device_bar_BDK_CDEX_PF_QX_CTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_QX_CTL(a,b) (a)
#define arguments_BDK_CDEX_PF_QX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_pf_q#_gmctl
 *
 * CDE Queue Guest Machine Control Register
 * This register configures queues. This register should be changed only when quiescent
 * (see CDE()_VQ()_INPROG[INFLIGHT]).
 */
union bdk_cdex_pf_qx_gmctl
{
    uint64_t u;
    struct bdk_cdex_pf_qx_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Low 8 bits of the SMMU stream identifier to use when issuing requests.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc. */
        uint64_t gmid                  : 16; /**< [ 15:  0](RO) Reserved.
                                                                 Internal:
                                                                 Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer free, or to SSO for all submit work operations initiated by this queue.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](RO) Reserved.
                                                                 Internal:
                                                                 Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer free, or to SSO for all submit work operations initiated by this queue.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Low 8 bits of the SMMU stream identifier to use when issuing requests.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_qx_gmctl_s cn8; */
    /* struct bdk_cdex_pf_qx_gmctl_s cn81xx; */
    struct bdk_cdex_pf_qx_gmctl_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Low 8 bits of the SMMU stream identifier to use when issuing requests.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc.

                                                                 Maximum legal value is 64. */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer free, or to SSO for all submit work operations initiated by this queue.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer free, or to SSO for all submit work operations initiated by this queue.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Low 8 bits of the SMMU stream identifier to use when issuing requests.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc.

                                                                 Maximum legal value is 64. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_cdex_pf_qx_gmctl bdk_cdex_pf_qx_gmctl_t;

static inline uint64_t BDK_CDEX_PF_QX_GMCTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_QX_GMCTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c008000020ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c008000020ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_PF_QX_GMCTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_QX_GMCTL(a,b) bdk_cdex_pf_qx_gmctl_t
#define bustype_BDK_CDEX_PF_QX_GMCTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_QX_GMCTL(a,b) "CDEX_PF_QX_GMCTL"
#define device_bar_BDK_CDEX_PF_QX_GMCTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_QX_GMCTL(a,b) (a)
#define arguments_BDK_CDEX_PF_QX_GMCTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_pf_rd_latency_pc
 *
 * CDE PF Read Latency Counter Register
 */
union bdk_cdex_pf_rd_latency_pc
{
    uint64_t u;
    struct bdk_cdex_pf_rd_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for L2C read returns. Incremented every
                                                                 coprocessor-clock by the number of transactions outstanding in that cycle. This
                                                                 may be divided by CDE()_PF_RD_REQ_PC to determine the average read latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for L2C read returns. Incremented every
                                                                 coprocessor-clock by the number of transactions outstanding in that cycle. This
                                                                 may be divided by CDE()_PF_RD_REQ_PC to determine the average read latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_rd_latency_pc_s cn; */
};
typedef union bdk_cdex_pf_rd_latency_pc bdk_cdex_pf_rd_latency_pc_t;

static inline uint64_t BDK_CDEX_PF_RD_LATENCY_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_RD_LATENCY_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000010060ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_PF_RD_LATENCY_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_RD_LATENCY_PC(a) bdk_cdex_pf_rd_latency_pc_t
#define bustype_BDK_CDEX_PF_RD_LATENCY_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_RD_LATENCY_PC(a) "CDEX_PF_RD_LATENCY_PC"
#define device_bar_BDK_CDEX_PF_RD_LATENCY_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_RD_LATENCY_PC(a) (a)
#define arguments_BDK_CDEX_PF_RD_LATENCY_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_rd_req_pc
 *
 * CDE PF Read Request Performance Counter Register
 */
union bdk_cdex_pf_rd_req_pc
{
    uint64_t u;
    struct bdk_cdex_pf_rd_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of L2C read requests. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of L2C read requests. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_rd_req_pc_s cn; */
};
typedef union bdk_cdex_pf_rd_req_pc bdk_cdex_pf_rd_req_pc_t;

static inline uint64_t BDK_CDEX_PF_RD_REQ_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_RD_REQ_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000010040ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_PF_RD_REQ_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_RD_REQ_PC(a) bdk_cdex_pf_rd_req_pc_t
#define bustype_BDK_CDEX_PF_RD_REQ_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_RD_REQ_PC(a) "CDEX_PF_RD_REQ_PC"
#define device_bar_BDK_CDEX_PF_RD_REQ_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_RD_REQ_PC(a) (a)
#define arguments_BDK_CDEX_PF_RD_REQ_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_reset
 *
 * CDE PF Reset Register
 * This register controls clock and reset.
 */
union bdk_cdex_pf_reset
{
    uint64_t u;
    struct bdk_cdex_pf_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1) Reset one-shot pulse to reset CDE subsystem. */
#else /* Word 0 - Little Endian */
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1) Reset one-shot pulse to reset CDE subsystem. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_reset_s cn; */
};
typedef union bdk_cdex_pf_reset bdk_cdex_pf_reset_t;

static inline uint64_t BDK_CDEX_PF_RESET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_RESET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x80c000000100ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CDEX_PF_RESET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_RESET(a) bdk_cdex_pf_reset_t
#define bustype_BDK_CDEX_PF_RESET(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_RESET(a) "CDEX_PF_RESET"
#define device_bar_BDK_CDEX_PF_RESET(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_RESET(a) (a)
#define arguments_BDK_CDEX_PF_RESET(a) (a),-1,-1,-1

/**
 * Register (NCB) cde#_pf_vf#_mbox#
 *
 * CDE PF/VF Mailbox Registers
 */
union bdk_cdex_pf_vfx_mboxx
{
    uint64_t u;
    struct bdk_cdex_pf_vfx_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 CDE()_VF()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing CDE()_PF_VF()_MBOX(0) (but not
                                                                 CDE()_VF()_PF_MBOX(0)) will set the corresponding
                                                                 CDE()_VQ()_MISC_INT[MBOX] which if appropriately enabled will send an interrupt
                                                                 to the VF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 CDE()_VF()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing CDE()_PF_VF()_MBOX(0) (but not
                                                                 CDE()_VF()_PF_MBOX(0)) will set the corresponding
                                                                 CDE()_VQ()_MISC_INT[MBOX] which if appropriately enabled will send an interrupt
                                                                 to the VF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_pf_vfx_mboxx_s cn; */
};
typedef union bdk_cdex_pf_vfx_mboxx bdk_cdex_pf_vfx_mboxx_t;

static inline uint64_t BDK_CDEX_PF_VFX_MBOXX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_PF_VFX_MBOXX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15) && (c<=1)))
        return 0x80c008001000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf) + 0x100ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63) && (c<=1)))
        return 0x80c008001000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 0x100ll * ((c) & 0x1);
    __bdk_csr_fatal("CDEX_PF_VFX_MBOXX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_CDEX_PF_VFX_MBOXX(a,b,c) bdk_cdex_pf_vfx_mboxx_t
#define bustype_BDK_CDEX_PF_VFX_MBOXX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_PF_VFX_MBOXX(a,b,c) "CDEX_PF_VFX_MBOXX"
#define device_bar_BDK_CDEX_PF_VFX_MBOXX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_CDEX_PF_VFX_MBOXX(a,b,c) (a)
#define arguments_BDK_CDEX_PF_VFX_MBOXX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) cde#_vf#_msix_pba#
 *
 * CDE VF MSI-X Pending-Bit-Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the CDE_VF_INT_VEC_E
 * enumeration.
 */
union bdk_cdex_vfx_msix_pbax
{
    uint64_t u;
    struct bdk_cdex_vfx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated CDE()_PF_MSIX_VEC()_CTL, enumerated by
                                                                 CDE_PF_INT_VEC_E. Bits that have no associated CDE_PF_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated CDE()_PF_MSIX_VEC()_CTL, enumerated by
                                                                 CDE_PF_INT_VEC_E. Bits that have no associated CDE_PF_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vfx_msix_pbax_s cn; */
};
typedef union bdk_cdex_vfx_msix_pbax bdk_cdex_vfx_msix_pbax_t;

static inline uint64_t BDK_CDEX_VFX_MSIX_PBAX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VFX_MSIX_PBAX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15) && (c==0)))
        return 0x80c0300f0000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf) + 8ll * ((c) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63) && (c==0)))
        return 0x80c0300f0000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 8ll * ((c) & 0x0);
    __bdk_csr_fatal("CDEX_VFX_MSIX_PBAX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_CDEX_VFX_MSIX_PBAX(a,b,c) bdk_cdex_vfx_msix_pbax_t
#define bustype_BDK_CDEX_VFX_MSIX_PBAX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VFX_MSIX_PBAX(a,b,c) "CDEX_VFX_MSIX_PBAX"
#define device_bar_BDK_CDEX_VFX_MSIX_PBAX(a,b,c) 0x4 /* VF_BAR4 */
#define busnum_BDK_CDEX_VFX_MSIX_PBAX(a,b,c) (a)
#define arguments_BDK_CDEX_VFX_MSIX_PBAX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) cde#_vf#_msix_vec#_addr
 *
 * CDE VF MSI-X Vector-Table Address Registers
 * This register is the MSI-X vector table, indexed by the CDE_VF_INT_VEC_E enumeration.
 */
union bdk_cdex_vfx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_cdex_vfx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_CDE_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_CDE_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vfx_msix_vecx_addr_s cn; */
};
typedef union bdk_cdex_vfx_msix_vecx_addr bdk_cdex_vfx_msix_vecx_addr_t;

static inline uint64_t BDK_CDEX_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15) && (c<=1)))
        return 0x80c030000000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf) + 0x10ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63) && (c<=1)))
        return 0x80c030000000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 0x10ll * ((c) & 0x1);
    __bdk_csr_fatal("CDEX_VFX_MSIX_VECX_ADDR", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_CDEX_VFX_MSIX_VECX_ADDR(a,b,c) bdk_cdex_vfx_msix_vecx_addr_t
#define bustype_BDK_CDEX_VFX_MSIX_VECX_ADDR(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VFX_MSIX_VECX_ADDR(a,b,c) "CDEX_VFX_MSIX_VECX_ADDR"
#define device_bar_BDK_CDEX_VFX_MSIX_VECX_ADDR(a,b,c) 0x4 /* VF_BAR4 */
#define busnum_BDK_CDEX_VFX_MSIX_VECX_ADDR(a,b,c) (a)
#define arguments_BDK_CDEX_VFX_MSIX_VECX_ADDR(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) cde#_vf#_msix_vec#_ctl
 *
 * CDE VF MSI-X Vector-Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the CDE_VF_INT_VEC_E enumeration.
 */
union bdk_cdex_vfx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_cdex_vfx_msix_vecx_ctl_s
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
    /* struct bdk_cdex_vfx_msix_vecx_ctl_s cn; */
};
typedef union bdk_cdex_vfx_msix_vecx_ctl bdk_cdex_vfx_msix_vecx_ctl_t;

static inline uint64_t BDK_CDEX_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15) && (c<=1)))
        return 0x80c030000008ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf) + 0x10ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63) && (c<=1)))
        return 0x80c030000008ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 0x10ll * ((c) & 0x1);
    __bdk_csr_fatal("CDEX_VFX_MSIX_VECX_CTL", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_CDEX_VFX_MSIX_VECX_CTL(a,b,c) bdk_cdex_vfx_msix_vecx_ctl_t
#define bustype_BDK_CDEX_VFX_MSIX_VECX_CTL(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VFX_MSIX_VECX_CTL(a,b,c) "CDEX_VFX_MSIX_VECX_CTL"
#define device_bar_BDK_CDEX_VFX_MSIX_VECX_CTL(a,b,c) 0x4 /* VF_BAR4 */
#define busnum_BDK_CDEX_VFX_MSIX_VECX_CTL(a,b,c) (a)
#define arguments_BDK_CDEX_VFX_MSIX_VECX_CTL(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) cde#_vf#_pf_mbox#
 *
 * CDE VF/PF Mailbox Registers
 */
union bdk_cdex_vfx_pf_mboxx
{
    uint64_t u;
    struct bdk_cdex_vfx_pf_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using CDE()_PF_VF()_MBOX(). MBOX(0) is
                                                                 typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 CDE()_VF()_PF_MBOX(1) (but not CDE()_PF_VF()_MBOX(1)) will set the
                                                                 corresponding CDE()_PF_MBOX_INT() bit, which if appropriately enabled will send an
                                                                 interrupt to the PF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using CDE()_PF_VF()_MBOX(). MBOX(0) is
                                                                 typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 CDE()_VF()_PF_MBOX(1) (but not CDE()_PF_VF()_MBOX(1)) will set the
                                                                 corresponding CDE()_PF_MBOX_INT() bit, which if appropriately enabled will send an
                                                                 interrupt to the PF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vfx_pf_mboxx_s cn; */
};
typedef union bdk_cdex_vfx_pf_mboxx bdk_cdex_vfx_pf_mboxx_t;

static inline uint64_t BDK_CDEX_VFX_PF_MBOXX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VFX_PF_MBOXX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15) && (c<=1)))
        return 0x80c020001000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf) + 8ll * ((c) & 0x1);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63) && (c<=1)))
        return 0x80c020001000ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("CDEX_VFX_PF_MBOXX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_CDEX_VFX_PF_MBOXX(a,b,c) bdk_cdex_vfx_pf_mboxx_t
#define bustype_BDK_CDEX_VFX_PF_MBOXX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VFX_PF_MBOXX(a,b,c) "CDEX_VFX_PF_MBOXX"
#define device_bar_BDK_CDEX_VFX_PF_MBOXX(a,b,c) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VFX_PF_MBOXX(a,b,c) (a)
#define arguments_BDK_CDEX_VFX_PF_MBOXX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) cde#_vq#_ctl
 *
 * CDE VF Queue Control Registers
 * This register configures queues. This register should be changed (other than
 * clearing [ENA]) only when quiescent (see CDE()_VQ()_INPROG[INFLIGHT]).
 */
union bdk_cdex_vqx_ctl
{
    uint64_t u;
    struct bdk_cdex_vqx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) Enables the logical instruction queue. See also CDE()_PF_Q()_CTL[CONT_ERR] and
                                                                 CDE()_VQ()_INPROG[INFLIGHT].
                                                                 1 = Queue is enabled.
                                                                 0 = Queue is disabled. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) Enables the logical instruction queue. See also CDE()_PF_Q()_CTL[CONT_ERR] and
                                                                 CDE()_VQ()_INPROG[INFLIGHT].
                                                                 1 = Queue is enabled.
                                                                 0 = Queue is disabled. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_ctl_s cn; */
};
typedef union bdk_cdex_vqx_ctl bdk_cdex_vqx_ctl_t;

static inline uint64_t BDK_CDEX_VQX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000100ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000100ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_CTL(a,b) bdk_cdex_vqx_ctl_t
#define bustype_BDK_CDEX_VQX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_CTL(a,b) "CDEX_VQX_CTL"
#define device_bar_BDK_CDEX_VQX_CTL(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_CTL(a,b) (a)
#define arguments_BDK_CDEX_VQX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_done
 *
 * CDE Queue Done Count Registers
 * These registers contain the per-queue instruction done count.
 */
union bdk_cdex_vqx_done
{
    uint64_t u;
    struct bdk_cdex_vqx_done_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t done                  : 20; /**< [ 19:  0](R/W/H) Done count. When CDE_INST_S[DONEINT] set and that instruction completes,
                                                                 CDE()_VQ()_DONE[DONE] is incremented when the instruction finishes. Write to
                                                                 this field are for diagnostic use only; instead software writes
                                                                 CDE()_VQ()_DONE_ACK with the number of decrements for this field.

                                                                 Interrupts are sent as follows:

                                                                 * When CDE()_VQ()_DONE[DONE] = 0, then no results are pending, the interrupt
                                                                 coalescing timer is held to zero, and an interrupt is not sent.

                                                                 * When CDE()_VQ()_DONE[DONE] != 0, then the interrupt coalescing timer
                                                                 counts. If the counter is \>= CDE()_VQ()_DONE_WAIT[TIME_WAIT]*1024, or
                                                                 CDE()_VQ()_DONE[DONE] \>= CDE()_VQ()_DONE_WAIT[NUM_WAIT], i.e. enough time has
                                                                 passed or enough results have arrived, then the interrupt is sent.  Otherwise,
                                                                 it is not sent due to coalescing.

                                                                 * When CDE()_VQ()_DONE_ACK is written (or CDE()_VQ()_DONE is written but this is
                                                                 not typical), the interrupt coalescing timer restarts.  Note after decrementing
                                                                 this interrupt equation is recomputed, for example if CDE()_VQ()_DONE[DONE] \>=
                                                                 CDE()_VQ()_DONE_WAIT[NUM_WAIT] and because the timer is zero, the interrupt will
                                                                 be resent immediately.  (This covers the race case between software
                                                                 acknowledging an interrupt and a result returning.)

                                                                 * When CDE()_VQ()_DONE_ENA_W1S[DONE] = 0, interrupts are not sent, but the
                                                                 counting described above still occurs.

                                                                 Since CDE instructions complete out-of-order, if software is using completion
                                                                 interrupts the suggested scheme is to request a DONEINT on each request, and
                                                                 when an interrupt arrives perform a "greedy" scan for completions; even if a
                                                                 later command is acknowledged first this will not result in missing a
                                                                 completion.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 20; /**< [ 19:  0](R/W/H) Done count. When CDE_INST_S[DONEINT] set and that instruction completes,
                                                                 CDE()_VQ()_DONE[DONE] is incremented when the instruction finishes. Write to
                                                                 this field are for diagnostic use only; instead software writes
                                                                 CDE()_VQ()_DONE_ACK with the number of decrements for this field.

                                                                 Interrupts are sent as follows:

                                                                 * When CDE()_VQ()_DONE[DONE] = 0, then no results are pending, the interrupt
                                                                 coalescing timer is held to zero, and an interrupt is not sent.

                                                                 * When CDE()_VQ()_DONE[DONE] != 0, then the interrupt coalescing timer
                                                                 counts. If the counter is \>= CDE()_VQ()_DONE_WAIT[TIME_WAIT]*1024, or
                                                                 CDE()_VQ()_DONE[DONE] \>= CDE()_VQ()_DONE_WAIT[NUM_WAIT], i.e. enough time has
                                                                 passed or enough results have arrived, then the interrupt is sent.  Otherwise,
                                                                 it is not sent due to coalescing.

                                                                 * When CDE()_VQ()_DONE_ACK is written (or CDE()_VQ()_DONE is written but this is
                                                                 not typical), the interrupt coalescing timer restarts.  Note after decrementing
                                                                 this interrupt equation is recomputed, for example if CDE()_VQ()_DONE[DONE] \>=
                                                                 CDE()_VQ()_DONE_WAIT[NUM_WAIT] and because the timer is zero, the interrupt will
                                                                 be resent immediately.  (This covers the race case between software
                                                                 acknowledging an interrupt and a result returning.)

                                                                 * When CDE()_VQ()_DONE_ENA_W1S[DONE] = 0, interrupts are not sent, but the
                                                                 counting described above still occurs.

                                                                 Since CDE instructions complete out-of-order, if software is using completion
                                                                 interrupts the suggested scheme is to request a DONEINT on each request, and
                                                                 when an interrupt arrives perform a "greedy" scan for completions; even if a
                                                                 later command is acknowledged first this will not result in missing a
                                                                 completion.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_done_s cn; */
};
typedef union bdk_cdex_vqx_done bdk_cdex_vqx_done_t;

static inline uint64_t BDK_CDEX_VQX_DONE(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_DONE(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000420ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000420ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_DONE", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_DONE(a,b) bdk_cdex_vqx_done_t
#define bustype_BDK_CDEX_VQX_DONE(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_DONE(a,b) "CDEX_VQX_DONE"
#define device_bar_BDK_CDEX_VQX_DONE(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_DONE(a,b) (a)
#define arguments_BDK_CDEX_VQX_DONE(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_done_ack
 *
 * CDE Queue Done Count Ack Registers
 * This register is written by software to acknowledge interrupts.
 */
union bdk_cdex_vqx_done_ack
{
    uint64_t u;
    struct bdk_cdex_vqx_done_ack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to CDE()_VQ()_DONE[DONE]. Reads CDE()_VQ()_DONE[DONE].

                                                                 Written by software to acknowledge interrupts. If CDE()_VQ()_DONE[DONE] is still
                                                                 nonzero the interrupt will be re-sent if the conditions described in
                                                                 CDE()_VQ()_DONE[DONE] are satisfied. */
#else /* Word 0 - Little Endian */
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to CDE()_VQ()_DONE[DONE]. Reads CDE()_VQ()_DONE[DONE].

                                                                 Written by software to acknowledge interrupts. If CDE()_VQ()_DONE[DONE] is still
                                                                 nonzero the interrupt will be re-sent if the conditions described in
                                                                 CDE()_VQ()_DONE[DONE] are satisfied. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_done_ack_s cn; */
};
typedef union bdk_cdex_vqx_done_ack bdk_cdex_vqx_done_ack_t;

static inline uint64_t BDK_CDEX_VQX_DONE_ACK(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_DONE_ACK(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000440ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000440ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_DONE_ACK", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_DONE_ACK(a,b) bdk_cdex_vqx_done_ack_t
#define bustype_BDK_CDEX_VQX_DONE_ACK(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_DONE_ACK(a,b) "CDEX_VQX_DONE_ACK"
#define device_bar_BDK_CDEX_VQX_DONE_ACK(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_DONE_ACK(a,b) (a)
#define arguments_BDK_CDEX_VQX_DONE_ACK(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_done_ena_w1c
 *
 * CDE Queue Done Interrupt Enable Clear Registers
 */
union bdk_cdex_vqx_done_ena_w1c
{
    uint64_t u;
    struct bdk_cdex_vqx_done_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Read or clears CDE()_VQ()_DONE_ENA_W1S[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Read or clears CDE()_VQ()_DONE_ENA_W1S[DONE]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_done_ena_w1c_s cn; */
};
typedef union bdk_cdex_vqx_done_ena_w1c bdk_cdex_vqx_done_ena_w1c_t;

static inline uint64_t BDK_CDEX_VQX_DONE_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_DONE_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000478ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000478ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_DONE_ENA_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_DONE_ENA_W1C(a,b) bdk_cdex_vqx_done_ena_w1c_t
#define bustype_BDK_CDEX_VQX_DONE_ENA_W1C(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_DONE_ENA_W1C(a,b) "CDEX_VQX_DONE_ENA_W1C"
#define device_bar_BDK_CDEX_VQX_DONE_ENA_W1C(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_DONE_ENA_W1C(a,b) (a)
#define arguments_BDK_CDEX_VQX_DONE_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_done_ena_w1s
 *
 * CDE Queue Done Interrupt Enable Set Registers
 * Write 1 to these registers will enable the DONEINT interrupt for the queue.
 */
union bdk_cdex_vqx_done_ena_w1s
{
    uint64_t u;
    struct bdk_cdex_vqx_done_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Write 1 will enable DONEINT for this queue. Write 0 has no effect.
                                                                 Read will return the enable bit. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Write 1 will enable DONEINT for this queue. Write 0 has no effect.
                                                                 Read will return the enable bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_done_ena_w1s_s cn; */
};
typedef union bdk_cdex_vqx_done_ena_w1s bdk_cdex_vqx_done_ena_w1s_t;

static inline uint64_t BDK_CDEX_VQX_DONE_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_DONE_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000470ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000470ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_DONE_ENA_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_DONE_ENA_W1S(a,b) bdk_cdex_vqx_done_ena_w1s_t
#define bustype_BDK_CDEX_VQX_DONE_ENA_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_DONE_ENA_W1S(a,b) "CDEX_VQX_DONE_ENA_W1S"
#define device_bar_BDK_CDEX_VQX_DONE_ENA_W1S(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_DONE_ENA_W1S(a,b) (a)
#define arguments_BDK_CDEX_VQX_DONE_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_done_int_w1c
 *
 * CDE Queue Done Interrupt Clear Registers
 */
union bdk_cdex_vqx_done_int_w1c
{
    uint64_t u;
    struct bdk_cdex_vqx_done_int_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See CDE()_VQ()_DONE[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use CDE()_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 CDE()_VQ()_DONE[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See CDE()_VQ()_DONE[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use CDE()_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 CDE()_VQ()_DONE[DONE]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_done_int_w1c_s cn; */
};
typedef union bdk_cdex_vqx_done_int_w1c bdk_cdex_vqx_done_int_w1c_t;

static inline uint64_t BDK_CDEX_VQX_DONE_INT_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_DONE_INT_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000468ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000468ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_DONE_INT_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_DONE_INT_W1C(a,b) bdk_cdex_vqx_done_int_w1c_t
#define bustype_BDK_CDEX_VQX_DONE_INT_W1C(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_DONE_INT_W1C(a,b) "CDEX_VQX_DONE_INT_W1C"
#define device_bar_BDK_CDEX_VQX_DONE_INT_W1C(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_DONE_INT_W1C(a,b) (a)
#define arguments_BDK_CDEX_VQX_DONE_INT_W1C(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_done_int_w1s
 *
 * CDE Queue Done Interrupt Set Registers
 */
union bdk_cdex_vqx_done_int_w1s
{
    uint64_t u;
    struct bdk_cdex_vqx_done_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See CDE()_VQ()_DONE[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use CDE()_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 CDE()_VQ()_DONE[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See CDE()_VQ()_DONE[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use CDE()_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 CDE()_VQ()_DONE[DONE]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_done_int_w1s_s cn; */
};
typedef union bdk_cdex_vqx_done_int_w1s bdk_cdex_vqx_done_int_w1s_t;

static inline uint64_t BDK_CDEX_VQX_DONE_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_DONE_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000460ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000460ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_DONE_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_DONE_INT_W1S(a,b) bdk_cdex_vqx_done_int_w1s_t
#define bustype_BDK_CDEX_VQX_DONE_INT_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_DONE_INT_W1S(a,b) "CDEX_VQX_DONE_INT_W1S"
#define device_bar_BDK_CDEX_VQX_DONE_INT_W1S(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_DONE_INT_W1S(a,b) (a)
#define arguments_BDK_CDEX_VQX_DONE_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_done_wait
 *
 * CDE Queue Done Interrupt Coalescing Wait Registers
 * Specifies the per queue interrupt coalescing settings.
 */
union bdk_cdex_vqx_done_wait
{
    uint64_t u;
    struct bdk_cdex_vqx_done_wait_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t time_wait             : 16; /**< [ 47: 32](R/W) Time hold-off. When CDE()_VQ()_DONE[DONE] = 0, or CDE()_VQ()_DONE_ACK is written
                                                                 a timer is cleared. When the timer reaches [TIME_WAIT]*1024 then interrupt
                                                                 coalescing ends; see CDE()_VQ()_DONE[DONE]. If 0x0, time coalescing is disabled. */
        uint64_t reserved_20_31        : 12;
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of messages hold-off. When CDE()_VQ()_DONE[DONE] \>= [NUM_WAIT] then
                                                                 interrupt coalescing ends; see CDE()_VQ()_DONE[DONE]. If 0x0, same behavior as
                                                                 0x1. */
#else /* Word 0 - Little Endian */
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of messages hold-off. When CDE()_VQ()_DONE[DONE] \>= [NUM_WAIT] then
                                                                 interrupt coalescing ends; see CDE()_VQ()_DONE[DONE]. If 0x0, same behavior as
                                                                 0x1. */
        uint64_t reserved_20_31        : 12;
        uint64_t time_wait             : 16; /**< [ 47: 32](R/W) Time hold-off. When CDE()_VQ()_DONE[DONE] = 0, or CDE()_VQ()_DONE_ACK is written
                                                                 a timer is cleared. When the timer reaches [TIME_WAIT]*1024 then interrupt
                                                                 coalescing ends; see CDE()_VQ()_DONE[DONE]. If 0x0, time coalescing is disabled. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_done_wait_s cn; */
};
typedef union bdk_cdex_vqx_done_wait bdk_cdex_vqx_done_wait_t;

static inline uint64_t BDK_CDEX_VQX_DONE_WAIT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_DONE_WAIT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000400ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000400ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_DONE_WAIT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_DONE_WAIT(a,b) bdk_cdex_vqx_done_wait_t
#define bustype_BDK_CDEX_VQX_DONE_WAIT(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_DONE_WAIT(a,b) "CDEX_VQX_DONE_WAIT"
#define device_bar_BDK_CDEX_VQX_DONE_WAIT(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_DONE_WAIT(a,b) (a)
#define arguments_BDK_CDEX_VQX_DONE_WAIT(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_doorbell
 *
 * CDE Queue Doorbell Registers
 * Doorbells for the CDE instruction queues.
 */
union bdk_cdex_vqx_doorbell
{
    uint64_t u;
    struct bdk_cdex_vqx_doorbell_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) Number of instruction queue 64-bit words to add to the CDE instruction doorbell
                                                                 count.  Readback value is the current number of pending doorbell requests.
                                                                 If counter overflows CDE()_VQ()_MISC_INT[DBELL_DOVF] is set.

                                                                 To reset the count back to zero, write one to clear
                                                                 CDE()_VQ()_MISC_INT_ENA_W1C[DBELL_DOVF], then write a value of 2^20 minus the
                                                                 read [DBELL_CNT], then write one to CDE()_VQ()_MISC_INT_W1C[DBELL_DOVF] and
                                                                 CDE()_VQ()_MISC_INT_ENA_W1S[DBELL_DOVF].

                                                                 CPT: Must be a multiple of 8. All CPT instructions are 8 words and require a
                                                                 doorbell count of multiple of 8.

                                                                 DDF: Must be a multiple of 16. All DDF instructions are 16 words and require a
                                                                 doorbell count of multiple of 16. */
#else /* Word 0 - Little Endian */
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) Number of instruction queue 64-bit words to add to the CDE instruction doorbell
                                                                 count.  Readback value is the current number of pending doorbell requests.
                                                                 If counter overflows CDE()_VQ()_MISC_INT[DBELL_DOVF] is set.

                                                                 To reset the count back to zero, write one to clear
                                                                 CDE()_VQ()_MISC_INT_ENA_W1C[DBELL_DOVF], then write a value of 2^20 minus the
                                                                 read [DBELL_CNT], then write one to CDE()_VQ()_MISC_INT_W1C[DBELL_DOVF] and
                                                                 CDE()_VQ()_MISC_INT_ENA_W1S[DBELL_DOVF].

                                                                 CPT: Must be a multiple of 8. All CPT instructions are 8 words and require a
                                                                 doorbell count of multiple of 8.

                                                                 DDF: Must be a multiple of 16. All DDF instructions are 16 words and require a
                                                                 doorbell count of multiple of 16. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_doorbell_s cn; */
};
typedef union bdk_cdex_vqx_doorbell bdk_cdex_vqx_doorbell_t;

static inline uint64_t BDK_CDEX_VQX_DOORBELL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_DOORBELL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000600ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000600ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_DOORBELL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_DOORBELL(a,b) bdk_cdex_vqx_doorbell_t
#define bustype_BDK_CDEX_VQX_DOORBELL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_DOORBELL(a,b) "CDEX_VQX_DOORBELL"
#define device_bar_BDK_CDEX_VQX_DOORBELL(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_DOORBELL(a,b) (a)
#define arguments_BDK_CDEX_VQX_DOORBELL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_inprog
 *
 * CDE Queue In Progress Count Registers
 * These registers contain the per-queue instruction in flight registers.
 */
union bdk_cdex_vqx_inprog
{
    uint64_t u;
    struct bdk_cdex_vqx_inprog_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t inflight              : 8;  /**< [  7:  0](RO/H) Inflight count. Counts the number of instructions for the VF for which CDE is
                                                                 fetching, executing or responding to instructions. However this does not include
                                                                 any interrupts that are awaiting software handling (CDE()_VQ()_DONE[DONE] !=
                                                                 0x0).

                                                                 A queue may not be reconfigured until:
                                                                   1. CDE()_VQ()_CTL[ENA] is cleared by software.
                                                                   2. [INFLIGHT] is polled until equals to zero. */
#else /* Word 0 - Little Endian */
        uint64_t inflight              : 8;  /**< [  7:  0](RO/H) Inflight count. Counts the number of instructions for the VF for which CDE is
                                                                 fetching, executing or responding to instructions. However this does not include
                                                                 any interrupts that are awaiting software handling (CDE()_VQ()_DONE[DONE] !=
                                                                 0x0).

                                                                 A queue may not be reconfigured until:
                                                                   1. CDE()_VQ()_CTL[ENA] is cleared by software.
                                                                   2. [INFLIGHT] is polled until equals to zero. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_inprog_s cn; */
};
typedef union bdk_cdex_vqx_inprog bdk_cdex_vqx_inprog_t;

static inline uint64_t BDK_CDEX_VQX_INPROG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_INPROG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000410ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000410ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_INPROG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_INPROG(a,b) bdk_cdex_vqx_inprog_t
#define bustype_BDK_CDEX_VQX_INPROG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_INPROG(a,b) "CDEX_VQX_INPROG"
#define device_bar_BDK_CDEX_VQX_INPROG(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_INPROG(a,b) (a)
#define arguments_BDK_CDEX_VQX_INPROG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_misc_ena_w1c
 *
 * CDE Queue Misc Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_cdex_vqx_misc_ena_w1c
{
    uint64_t u;
    struct bdk_cdex_vqx_misc_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_misc_ena_w1c_s cn8; */
    struct bdk_cdex_vqx_misc_ena_w1c_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_cdex_vqx_misc_ena_w1c_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_cdex_vqx_misc_ena_w1c bdk_cdex_vqx_misc_ena_w1c_t;

static inline uint64_t BDK_CDEX_VQX_MISC_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_MISC_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000518ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000518ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_MISC_ENA_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_MISC_ENA_W1C(a,b) bdk_cdex_vqx_misc_ena_w1c_t
#define bustype_BDK_CDEX_VQX_MISC_ENA_W1C(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_MISC_ENA_W1C(a,b) "CDEX_VQX_MISC_ENA_W1C"
#define device_bar_BDK_CDEX_VQX_MISC_ENA_W1C(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_MISC_ENA_W1C(a,b) (a)
#define arguments_BDK_CDEX_VQX_MISC_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_misc_ena_w1s
 *
 * CDE Queue Misc Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_cdex_vqx_misc_ena_w1s
{
    uint64_t u;
    struct bdk_cdex_vqx_misc_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_misc_ena_w1s_s cn8; */
    struct bdk_cdex_vqx_misc_ena_w1s_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_cdex_vqx_misc_ena_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_cdex_vqx_misc_ena_w1s bdk_cdex_vqx_misc_ena_w1s_t;

static inline uint64_t BDK_CDEX_VQX_MISC_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_MISC_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000510ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000510ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_MISC_ENA_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_MISC_ENA_W1S(a,b) bdk_cdex_vqx_misc_ena_w1s_t
#define bustype_BDK_CDEX_VQX_MISC_ENA_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_MISC_ENA_W1S(a,b) "CDEX_VQX_MISC_ENA_W1S"
#define device_bar_BDK_CDEX_VQX_MISC_ENA_W1S(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_MISC_ENA_W1S(a,b) (a)
#define arguments_BDK_CDEX_VQX_MISC_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_misc_int
 *
 * CDE Queue Misc Interrupt Register
 * These registers contain the per-queue miscellaneous interrupts.
 */
union bdk_cdex_vqx_misc_int
{
    uint64_t u;
    struct bdk_cdex_vqx_misc_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Translation fault detected. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Hardware error from engines. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Software error from engines. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) NCB result write response error. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Instruction NCB read response error. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Doorbell overflow. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) PF to VF mailbox interrupt. Set when CDE()_VF()_PF_MBOX(0)
                                                                 is written. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) PF to VF mailbox interrupt. Set when CDE()_VF()_PF_MBOX(0)
                                                                 is written. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Doorbell overflow. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Instruction NCB read response error. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) NCB result write response error. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Software error from engines. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Hardware error from engines. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Translation fault detected. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_misc_int_s cn8; */
    struct bdk_cdex_vqx_misc_int_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Software error from engines. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) NCB result write response error. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Instruction NCB read response error. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Doorbell overflow. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) PF to VF mailbox interrupt. Set when CDE()_VF()_PF_MBOX(0)
                                                                 is written. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) PF to VF mailbox interrupt. Set when CDE()_VF()_PF_MBOX(0)
                                                                 is written. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Doorbell overflow. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Instruction NCB read response error. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) NCB result write response error. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Software error from engines. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_cdex_vqx_misc_int_s cn83xx; */
};
typedef union bdk_cdex_vqx_misc_int bdk_cdex_vqx_misc_int_t;

static inline uint64_t BDK_CDEX_VQX_MISC_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_MISC_INT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000500ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000500ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_MISC_INT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_MISC_INT(a,b) bdk_cdex_vqx_misc_int_t
#define bustype_BDK_CDEX_VQX_MISC_INT(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_MISC_INT(a,b) "CDEX_VQX_MISC_INT"
#define device_bar_BDK_CDEX_VQX_MISC_INT(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_MISC_INT(a,b) (a)
#define arguments_BDK_CDEX_VQX_MISC_INT(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_misc_int_w1s
 *
 * CDE Queue Misc Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_cdex_vqx_misc_int_w1s
{
    uint64_t u;
    struct bdk_cdex_vqx_misc_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_misc_int_w1s_s cn8; */
    struct bdk_cdex_vqx_misc_int_w1s_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets CDE(0)_VQ(0..15)_MISC_INT[SWERR]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_cdex_vqx_misc_int_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets CDE(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_cdex_vqx_misc_int_w1s bdk_cdex_vqx_misc_int_w1s_t;

static inline uint64_t BDK_CDEX_VQX_MISC_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_MISC_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000508ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000508ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_MISC_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_MISC_INT_W1S(a,b) bdk_cdex_vqx_misc_int_w1s_t
#define bustype_BDK_CDEX_VQX_MISC_INT_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_MISC_INT_W1S(a,b) "CDEX_VQX_MISC_INT_W1S"
#define device_bar_BDK_CDEX_VQX_MISC_INT_W1S(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_MISC_INT_W1S(a,b) (a)
#define arguments_BDK_CDEX_VQX_MISC_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB) cde#_vq#_saddr
 *
 * CDE Queue Starting Buffer Address Registers
 * These registers set the instruction buffer starting address.
 */
union bdk_cdex_vqx_saddr
{
    uint64_t u;
    struct bdk_cdex_vqx_saddr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t ptr                   : 43; /**< [ 48:  6](R/W/H) Instruction buffer IOVA \<48:6\> (64-byte aligned). When written, it is the initial
                                                                 buffer starting address; when read, it is the next read pointer to be requested from L2C.
                                                                 The PTR field is overwritten with the next pointer each time that the command buffer
                                                                 segment is exhausted. New commands will then be read from the newly specified command
                                                                 buffer pointer.

                                                                 CPT: 64-byte aligned.

                                                                 DDF: 128-byte aligned. */
        uint64_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_5          : 6;
        uint64_t ptr                   : 43; /**< [ 48:  6](R/W/H) Instruction buffer IOVA \<48:6\> (64-byte aligned). When written, it is the initial
                                                                 buffer starting address; when read, it is the next read pointer to be requested from L2C.
                                                                 The PTR field is overwritten with the next pointer each time that the command buffer
                                                                 segment is exhausted. New commands will then be read from the newly specified command
                                                                 buffer pointer.

                                                                 CPT: 64-byte aligned.

                                                                 DDF: 128-byte aligned. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cdex_vqx_saddr_s cn; */
};
typedef union bdk_cdex_vqx_saddr bdk_cdex_vqx_saddr_t;

static inline uint64_t BDK_CDEX_VQX_SADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CDEX_VQX_SADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=15)))
        return 0x80c020000200ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=63)))
        return 0x80c020000200ll + 0x1000000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("CDEX_VQX_SADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CDEX_VQX_SADDR(a,b) bdk_cdex_vqx_saddr_t
#define bustype_BDK_CDEX_VQX_SADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_CDEX_VQX_SADDR(a,b) "CDEX_VQX_SADDR"
#define device_bar_BDK_CDEX_VQX_SADDR(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_CDEX_VQX_SADDR(a,b) (a)
#define arguments_BDK_CDEX_VQX_SADDR(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_CDE_H__ */
