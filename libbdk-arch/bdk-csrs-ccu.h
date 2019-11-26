#ifndef __BDK_CSRS_CCU_H__
#define __BDK_CSRS_CCU_H__
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
 * OcteonTX CCU.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration ccu_bar_e
 *
 * CCU Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_CCU_BAR_E_CCUX_PF_BAR0(a) (0x87e050000000ll + 0x1000000ll * (a))
#define BDK_CCU_BAR_E_CCUX_PF_BAR0_SIZE 0x800000ull
#define BDK_CCU_BAR_E_CCUX_PF_BAR4(a) (0x87e050f00000ll + 0x1000000ll * (a))
#define BDK_CCU_BAR_E_CCUX_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration ccu_int_vec_e
 *
 * CCU MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_CCU_INT_VEC_E_TADX_INT(a) (0 + (a))

/**
 * Enumeration ccu_pic_prf_sel_e
 *
 * CCU PIC Performance Counter Select Enumeration
 * Enumerates the different PIC performance counter selects.
 */
#define BDK_CCU_PIC_PRF_SEL_E_ACK_IN (0xc)
#define BDK_CCU_PIC_PRF_SEL_E_ACK_OUT (0x10)
#define BDK_CCU_PIC_PRF_SEL_E_CMD_IN (0xd)
#define BDK_CCU_PIC_PRF_SEL_E_CMD_OUT (0x11)
#define BDK_CCU_PIC_PRF_SEL_E_CMT (0xa)
#define BDK_CCU_PIC_PRF_SEL_E_DAT_IN (0xe)
#define BDK_CCU_PIC_PRF_SEL_E_DAT_OUT (0x12)
#define BDK_CCU_PIC_PRF_SEL_E_HIT (3)
#define BDK_CCU_PIC_PRF_SEL_E_HIT_DLYD (4)
#define BDK_CCU_PIC_PRF_SEL_E_INV (0xb)
#define BDK_CCU_PIC_PRF_SEL_E_LFB_OCC (5)
#define BDK_CCU_PIC_PRF_SEL_E_NONE (0)
#define BDK_CCU_PIC_PRF_SEL_E_REPLAY (2)
#define BDK_CCU_PIC_PRF_SEL_E_RSC0 (6)
#define BDK_CCU_PIC_PRF_SEL_E_RSC1 (7)
#define BDK_CCU_PIC_PRF_SEL_E_RSD0 (8)
#define BDK_CCU_PIC_PRF_SEL_E_RSD1 (9)
#define BDK_CCU_PIC_PRF_SEL_E_TAG_RD (1)
#define BDK_CCU_PIC_PRF_SEL_E_VCC_IN (0xf)

/**
 * Enumeration ccu_tad_prf_sel_e
 *
 * CCU TAD Performance Counter Select Enumeration
 * Enumerates the different TAD performance counter selects.
 */
#define BDK_CCU_TAD_PRF_SEL_E_ACK_MSH_IN (3)
#define BDK_CCU_TAD_PRF_SEL_E_ACK_MSH_OUT (0x14)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_IN (2)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_OUT_ANY (0x13)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_OUT_BC (0xc)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_OUT_DINV (0xb)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_OUT_MCC_RD (0xd)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_OUT_MCC_WR (0xe)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_OUT_RSVD0 (0x10)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_OUT_RSVD1 (0x11)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_OUT_RSVD2 (0x12)
#define BDK_CCU_TAD_PRF_SEL_E_CMD_MSH_OUT_WBAR (0xf)
#define BDK_CCU_TAD_PRF_SEL_E_DAT_MSH_IN (1)
#define BDK_CCU_TAD_PRF_SEL_E_DAT_MSH_OUT_ANY (0xa)
#define BDK_CCU_TAD_PRF_SEL_E_DAT_MSH_OUT_BYP (6)
#define BDK_CCU_TAD_PRF_SEL_E_DAT_MSH_OUT_FILL (5)
#define BDK_CCU_TAD_PRF_SEL_E_DAT_MSH_OUT_MCC (7)
#define BDK_CCU_TAD_PRF_SEL_E_DAT_MSH_OUT_RSVD0 (8)
#define BDK_CCU_TAD_PRF_SEL_E_DAT_MSH_OUT_RSVD1 (9)
#define BDK_CCU_TAD_PRF_SEL_E_DAT_RD (0x19)
#define BDK_CCU_TAD_PRF_SEL_E_DAT_RD_HIT (0x1a)
#define BDK_CCU_TAD_PRF_SEL_E_DTG_HIT (0x1c)
#define BDK_CCU_TAD_PRF_SEL_E_LFB_OCC (0x1e)
#define BDK_CCU_TAD_PRF_SEL_E_LTG_HIT (0x1b)
#define BDK_CCU_TAD_PRF_SEL_E_NONE (0)
#define BDK_CCU_TAD_PRF_SEL_E_TAG_RD (0x1d)
#define BDK_CCU_TAD_PRF_SEL_E_VCC_MSH_IN (4)
#define BDK_CCU_TAD_PRF_SEL_E_VCC_MSH_OUT_ANY (0x18)
#define BDK_CCU_TAD_PRF_SEL_E_VCC_MSH_OUT_IOB (0x16)
#define BDK_CCU_TAD_PRF_SEL_E_VCC_MSH_OUT_PIC (0x15)
#define BDK_CCU_TAD_PRF_SEL_E_VCC_MSH_OUT_RSVD0 (0x17)

/**
 * Register (RSL) ccu#_msix_pba#
 *
 * CCU MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the CCU_INT_VEC_E
 * enumeration.
 */
union bdk_ccux_msix_pbax
{
    uint64_t u;
    struct bdk_ccux_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO) Pending message for the associated CCU()_MSIX_VEC()_CTL, enumerated by
                                                                 CCU_INT_VEC_E. Bits
                                                                 that have no associated CCU_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO) Pending message for the associated CCU()_MSIX_VEC()_CTL, enumerated by
                                                                 CCU_INT_VEC_E. Bits
                                                                 that have no associated CCU_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msix_pbax_s cn; */
};
typedef union bdk_ccux_msix_pbax bdk_ccux_msix_pbax_t;

static inline uint64_t BDK_CCUX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b==0)))
        return 0x87e050ff0000ll + 0x1000000ll * ((a) & 0x3) + 8ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b==0)))
        return 0x87e050ff0000ll + 0x1000000ll * ((a) & 0x7) + 8ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e050ff0000ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e050ff0000ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("CCUX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSIX_PBAX(a,b) bdk_ccux_msix_pbax_t
#define bustype_BDK_CCUX_MSIX_PBAX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSIX_PBAX(a,b) "CCUX_MSIX_PBAX"
#define device_bar_BDK_CCUX_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_CCUX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_CCUX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_msix_vec#_addr
 *
 * CCU MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the CCU_INT_VEC_E enumeration.
 */
union bdk_ccux_msix_vecx_addr
{
    uint64_t u;
    struct bdk_ccux_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's CCU()_MSIX_VEC()_ADDR, CCU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of CCU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_CCU_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] were set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's CCU()_MSIX_VEC()_ADDR, CCU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of CCU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_CCU_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] were set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msix_vecx_addr_s cn9; */
    /* struct bdk_ccux_msix_vecx_addr_s cn96xxp1; */
    struct bdk_ccux_msix_vecx_addr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's CCU()_MSIX_VEC()_ADDR, CCU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of CCU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_CCU_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] were set.

                                                                 Also note the following:
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_EN]=1, all secure vectors (including secure
                                                                 VF vectors) will act as if PCCPF/PCCVF_XXX_MSIX_CAP_HDR[MSIXEN]=1,
                                                                 PCCPF/PCCVF_XXX_MSIX_CAP_HDR[FUNM]=0 and PCCPF/PCCVF_XXX_CMD[ME]=1.
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1, all secure vectors (including
                                                                 secure VF vectors) are considered physical, regardless of
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's CCU()_MSIX_VEC()_ADDR, CCU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of CCU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_CCU_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] were set.

                                                                 Also note the following:
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_EN]=1, all secure vectors (including secure
                                                                 VF vectors) will act as if PCCPF/PCCVF_XXX_MSIX_CAP_HDR[MSIXEN]=1,
                                                                 PCCPF/PCCVF_XXX_MSIX_CAP_HDR[FUNM]=0 and PCCPF/PCCVF_XXX_CMD[ME]=1.
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1, all secure vectors (including
                                                                 secure VF vectors) are considered physical, regardless of
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_ccux_msix_vecx_addr_cn96xxp3 cn98xx; */
    /* struct bdk_ccux_msix_vecx_addr_cn96xxp3 cnf95xx; */
    /* struct bdk_ccux_msix_vecx_addr_cn96xxp3 loki; */
};
typedef union bdk_ccux_msix_vecx_addr bdk_ccux_msix_vecx_addr_t;

static inline uint64_t BDK_CCUX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050f00000ll + 0x1000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050f00000ll + 0x1000000ll * ((a) & 0x7) + 0x10ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050f00000ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050f00000ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSIX_VECX_ADDR(a,b) bdk_ccux_msix_vecx_addr_t
#define bustype_BDK_CCUX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSIX_VECX_ADDR(a,b) "CCUX_MSIX_VECX_ADDR"
#define device_bar_BDK_CCUX_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_CCUX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_CCUX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_msix_vec#_ctl
 *
 * CCU MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the CCU_INT_VEC_E enumeration.
 */
union bdk_ccux_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_ccux_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msix_vecx_ctl_s cn; */
};
typedef union bdk_ccux_msix_vecx_ctl bdk_ccux_msix_vecx_ctl_t;

static inline uint64_t BDK_CCUX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050f00008ll + 0x1000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050f00008ll + 0x1000000ll * ((a) & 0x7) + 0x10ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050f00008ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050f00008ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSIX_VECX_CTL(a,b) bdk_ccux_msix_vecx_ctl_t
#define bustype_BDK_CCUX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSIX_VECX_CTL(a,b) "CCUX_MSIX_VECX_CTL"
#define device_bar_BDK_CCUX_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_CCUX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_CCUX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_msw_bp_test
 *
 * INTERNAL: MSW TX Backpressure Test Register
 */
union bdk_ccux_msw_bp_test
{
    uint64_t u;
    struct bdk_ccux_msw_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 10; /**< [ 63: 54](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Enable 9 = Limit traffic into MSW from pic.
                                                                 \<62\> = Enable 8 = Limit traffic into MSW from tad1.
                                                                 \<61\> = Enable 7 = Limit traffic into MSW from tad0.
                                                                 \<60\> = Enable 6 = Limit traffic out of MSW to pic.
                                                                 \<59\> = Enable 5 = Limit traffic out of MSW to tad1.
                                                                 \<58\> = Enable 4 = Limit traffic out of MSW to tad0.
                                                                 \<57\> = Enable 3 = Limit traffic out of MSW to mesh west.
                                                                 \<56\> = Enable 2 = Limit traffic out of MSW to mesh south.
                                                                 \<55\> = Enable 1 = Limit traffic out of MSW to mesh east.
                                                                 \<54\> = Enable 0 = Limit traffic out of MSW to mesh north. */
        uint64_t reserved_36_53        : 18;
        uint64_t bp_cfg                : 20; /**< [ 35: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits defined as
                                                                 0x0=100% of the time, 0x1=75% of the time,
                                                                 0x2=50% of the time, 0x3=25% of the time.
                                                                   \<35:34\> = Config 9.
                                                                   \<33:32\> = Config 8.
                                                                   \<31:30\> = Config 7.
                                                                   \<29:28\> = Config 6.
                                                                   \<27:26\> = Config 5.
                                                                   \<25:24\> = Config 4.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 20; /**< [ 35: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits defined as
                                                                 0x0=100% of the time, 0x1=75% of the time,
                                                                 0x2=50% of the time, 0x3=25% of the time.
                                                                   \<35:34\> = Config 9.
                                                                   \<33:32\> = Config 8.
                                                                   \<31:30\> = Config 7.
                                                                   \<29:28\> = Config 6.
                                                                   \<27:26\> = Config 5.
                                                                   \<25:24\> = Config 4.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_36_53        : 18;
        uint64_t enable                : 10; /**< [ 63: 54](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Enable 9 = Limit traffic into MSW from pic.
                                                                 \<62\> = Enable 8 = Limit traffic into MSW from tad1.
                                                                 \<61\> = Enable 7 = Limit traffic into MSW from tad0.
                                                                 \<60\> = Enable 6 = Limit traffic out of MSW to pic.
                                                                 \<59\> = Enable 5 = Limit traffic out of MSW to tad1.
                                                                 \<58\> = Enable 4 = Limit traffic out of MSW to tad0.
                                                                 \<57\> = Enable 3 = Limit traffic out of MSW to mesh west.
                                                                 \<56\> = Enable 2 = Limit traffic out of MSW to mesh south.
                                                                 \<55\> = Enable 1 = Limit traffic out of MSW to mesh east.
                                                                 \<54\> = Enable 0 = Limit traffic out of MSW to mesh north. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msw_bp_test_s cn; */
};
typedef union bdk_ccux_msw_bp_test bdk_ccux_msw_bp_test_t;

static inline uint64_t BDK_CCUX_MSW_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSW_BP_TEST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050200010ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050200010ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050200010ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050200010ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_MSW_BP_TEST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSW_BP_TEST(a) bdk_ccux_msw_bp_test_t
#define bustype_BDK_CCUX_MSW_BP_TEST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSW_BP_TEST(a) "CCUX_MSW_BP_TEST"
#define device_bar_BDK_CCUX_MSW_BP_TEST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_MSW_BP_TEST(a) (a)
#define arguments_BDK_CCUX_MSW_BP_TEST(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_msw_crclk_force
 *
 * MSW Conditional Clock Force Register
 */
union bdk_ccux_msw_crclk_force
{
    uint64_t u;
    struct bdk_ccux_msw_crclk_force_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t trb1                  : 1;  /**< [ 13: 13](R/W) Force on TRB1 conditional clock. */
        uint64_t trb0                  : 1;  /**< [ 12: 12](R/W) Force on TRB0 conditional clock. */
        uint64_t prb                   : 1;  /**< [ 11: 11](R/W) Force on PRB conditional clock. */
        uint64_t tsb1                  : 1;  /**< [ 10: 10](R/W) Force on TSB1 conditional clock. */
        uint64_t tsb0                  : 1;  /**< [  9:  9](R/W) Force on TSB0 conditional clock. */
        uint64_t psb                   : 1;  /**< [  8:  8](R/W) Force on PSB conditional clock. */
        uint64_t mtx3                  : 1;  /**< [  7:  7](R/W) Force on MTX3 conditional clock. */
        uint64_t mtx2                  : 1;  /**< [  6:  6](R/W) Force on MTX2 conditional clock. */
        uint64_t mtx1                  : 1;  /**< [  5:  5](R/W) Force on MTX1 conditional clock. */
        uint64_t mtx0                  : 1;  /**< [  4:  4](R/W) Force on MTX0 conditional clock. */
        uint64_t mrx3                  : 1;  /**< [  3:  3](R/W) Force on MRX3 conditional clock. */
        uint64_t mrx2                  : 1;  /**< [  2:  2](R/W) Force on MRX2 conditional clock. */
        uint64_t mrx1                  : 1;  /**< [  1:  1](R/W) Force on MRX1 conditional clock. */
        uint64_t mrx0                  : 1;  /**< [  0:  0](R/W) Force on MRX0 conditional clock. */
#else /* Word 0 - Little Endian */
        uint64_t mrx0                  : 1;  /**< [  0:  0](R/W) Force on MRX0 conditional clock. */
        uint64_t mrx1                  : 1;  /**< [  1:  1](R/W) Force on MRX1 conditional clock. */
        uint64_t mrx2                  : 1;  /**< [  2:  2](R/W) Force on MRX2 conditional clock. */
        uint64_t mrx3                  : 1;  /**< [  3:  3](R/W) Force on MRX3 conditional clock. */
        uint64_t mtx0                  : 1;  /**< [  4:  4](R/W) Force on MTX0 conditional clock. */
        uint64_t mtx1                  : 1;  /**< [  5:  5](R/W) Force on MTX1 conditional clock. */
        uint64_t mtx2                  : 1;  /**< [  6:  6](R/W) Force on MTX2 conditional clock. */
        uint64_t mtx3                  : 1;  /**< [  7:  7](R/W) Force on MTX3 conditional clock. */
        uint64_t psb                   : 1;  /**< [  8:  8](R/W) Force on PSB conditional clock. */
        uint64_t tsb0                  : 1;  /**< [  9:  9](R/W) Force on TSB0 conditional clock. */
        uint64_t tsb1                  : 1;  /**< [ 10: 10](R/W) Force on TSB1 conditional clock. */
        uint64_t prb                   : 1;  /**< [ 11: 11](R/W) Force on PRB conditional clock. */
        uint64_t trb0                  : 1;  /**< [ 12: 12](R/W) Force on TRB0 conditional clock. */
        uint64_t trb1                  : 1;  /**< [ 13: 13](R/W) Force on TRB1 conditional clock. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msw_crclk_force_s cn9; */
    /* struct bdk_ccux_msw_crclk_force_s cn96xx; */
    /* struct bdk_ccux_msw_crclk_force_s cn98xx; */
    struct bdk_ccux_msw_crclk_force_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t trb1                  : 1;  /**< [ 13: 13](R/W) Force on TRB1 conditional clock. For diagnostic use only. */
        uint64_t trb0                  : 1;  /**< [ 12: 12](R/W) Force on TRB0 conditional clock. For diagnostic use only. */
        uint64_t prb                   : 1;  /**< [ 11: 11](R/W) Force on PRB conditional clock. For diagnostic use only. */
        uint64_t tsb1                  : 1;  /**< [ 10: 10](R/W) Force on TSB1 conditional clock. For diagnostic use only. */
        uint64_t tsb0                  : 1;  /**< [  9:  9](R/W) Force on TSB0 conditional clock. For diagnostic use only. */
        uint64_t psb                   : 1;  /**< [  8:  8](R/W) Force on PSB conditional clock. For diagnostic use only. */
        uint64_t mtx3                  : 1;  /**< [  7:  7](R/W) Force on MTX3 conditional clock. For diagnostic use only. */
        uint64_t mtx2                  : 1;  /**< [  6:  6](R/W) Force on MTX2 conditional clock. For diagnostic use only. */
        uint64_t mtx1                  : 1;  /**< [  5:  5](R/W) Force on MTX1 conditional clock. For diagnostic use only. */
        uint64_t mtx0                  : 1;  /**< [  4:  4](R/W) Force on MTX0 conditional clock. For diagnostic use only. */
        uint64_t mrx3                  : 1;  /**< [  3:  3](R/W) Force on MRX3 conditional clock. For diagnostic use only. */
        uint64_t mrx2                  : 1;  /**< [  2:  2](R/W) Force on MRX2 conditional clock. For diagnostic use only. */
        uint64_t mrx1                  : 1;  /**< [  1:  1](R/W) Force on MRX1 conditional clock. For diagnostic use only. */
        uint64_t mrx0                  : 1;  /**< [  0:  0](R/W) Force on MRX0 conditional clock. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t mrx0                  : 1;  /**< [  0:  0](R/W) Force on MRX0 conditional clock. For diagnostic use only. */
        uint64_t mrx1                  : 1;  /**< [  1:  1](R/W) Force on MRX1 conditional clock. For diagnostic use only. */
        uint64_t mrx2                  : 1;  /**< [  2:  2](R/W) Force on MRX2 conditional clock. For diagnostic use only. */
        uint64_t mrx3                  : 1;  /**< [  3:  3](R/W) Force on MRX3 conditional clock. For diagnostic use only. */
        uint64_t mtx0                  : 1;  /**< [  4:  4](R/W) Force on MTX0 conditional clock. For diagnostic use only. */
        uint64_t mtx1                  : 1;  /**< [  5:  5](R/W) Force on MTX1 conditional clock. For diagnostic use only. */
        uint64_t mtx2                  : 1;  /**< [  6:  6](R/W) Force on MTX2 conditional clock. For diagnostic use only. */
        uint64_t mtx3                  : 1;  /**< [  7:  7](R/W) Force on MTX3 conditional clock. For diagnostic use only. */
        uint64_t psb                   : 1;  /**< [  8:  8](R/W) Force on PSB conditional clock. For diagnostic use only. */
        uint64_t tsb0                  : 1;  /**< [  9:  9](R/W) Force on TSB0 conditional clock. For diagnostic use only. */
        uint64_t tsb1                  : 1;  /**< [ 10: 10](R/W) Force on TSB1 conditional clock. For diagnostic use only. */
        uint64_t prb                   : 1;  /**< [ 11: 11](R/W) Force on PRB conditional clock. For diagnostic use only. */
        uint64_t trb0                  : 1;  /**< [ 12: 12](R/W) Force on TRB0 conditional clock. For diagnostic use only. */
        uint64_t trb1                  : 1;  /**< [ 13: 13](R/W) Force on TRB1 conditional clock. For diagnostic use only. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_ccux_msw_crclk_force_cnf95xx loki; */
};
typedef union bdk_ccux_msw_crclk_force bdk_ccux_msw_crclk_force_t;

static inline uint64_t BDK_CCUX_MSW_CRCLK_FORCE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSW_CRCLK_FORCE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X) && (a<=3))
        return 0x87e050200020ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050200020ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050200020ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050200020ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_MSW_CRCLK_FORCE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSW_CRCLK_FORCE(a) bdk_ccux_msw_crclk_force_t
#define bustype_BDK_CCUX_MSW_CRCLK_FORCE(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSW_CRCLK_FORCE(a) "CCUX_MSW_CRCLK_FORCE"
#define device_bar_BDK_CCUX_MSW_CRCLK_FORCE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_MSW_CRCLK_FORCE(a) (a)
#define arguments_BDK_CCUX_MSW_CRCLK_FORCE(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_msw_ecc_dbg_en
 *
 * INTERNAL: CCU MSW ECC Detection Counter Control Registers
 *
 * This register enables counting of the number of single and double bit errors on the
 * dat mesh coming into the MSW in each cardinal direction.
 * For debug purposes only, no SBE correction.
 */
union bdk_ccux_msw_ecc_dbg_en
{
    uint64_t u;
    struct bdk_ccux_msw_ecc_dbg_en_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t sbe                   : 1;  /**< [  1:  1](R/W) Enable counting the number of SBEs seen on the dat mesh in CCU()_MSW_MSH()_ECC_DBG_CNT. */
        uint64_t dbe                   : 1;  /**< [  0:  0](R/W) Enable counting the number of DBEs seen on the dat mesh in CCU()_MSW_MSH()_ECC_DBG_CNT. */
#else /* Word 0 - Little Endian */
        uint64_t dbe                   : 1;  /**< [  0:  0](R/W) Enable counting the number of DBEs seen on the dat mesh in CCU()_MSW_MSH()_ECC_DBG_CNT. */
        uint64_t sbe                   : 1;  /**< [  1:  1](R/W) Enable counting the number of SBEs seen on the dat mesh in CCU()_MSW_MSH()_ECC_DBG_CNT. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msw_ecc_dbg_en_s cn; */
};
typedef union bdk_ccux_msw_ecc_dbg_en bdk_ccux_msw_ecc_dbg_en_t;

static inline uint64_t BDK_CCUX_MSW_ECC_DBG_EN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSW_ECC_DBG_EN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050200200ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050200200ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050200200ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050200200ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_MSW_ECC_DBG_EN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSW_ECC_DBG_EN(a) bdk_ccux_msw_ecc_dbg_en_t
#define bustype_BDK_CCUX_MSW_ECC_DBG_EN(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSW_ECC_DBG_EN(a) "CCUX_MSW_ECC_DBG_EN"
#define device_bar_BDK_CCUX_MSW_ECC_DBG_EN(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_MSW_ECC_DBG_EN(a) (a)
#define arguments_BDK_CCUX_MSW_ECC_DBG_EN(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_msw_eco
 *
 * INTERNAL: CCU MSW ECO Register
 *
 * These registers exist to provide CSR flops in case they are needed for ECOs.
 */
union bdk_ccux_msw_eco
{
    uint64_t u;
    struct bdk_ccux_msw_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msw_eco_s cn; */
};
typedef union bdk_ccux_msw_eco bdk_ccux_msw_eco_t;

static inline uint64_t BDK_CCUX_MSW_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSW_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050200008ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050200008ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050200008ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050200008ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_MSW_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSW_ECO(a) bdk_ccux_msw_eco_t
#define bustype_BDK_CCUX_MSW_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSW_ECO(a) "CCUX_MSW_ECO"
#define device_bar_BDK_CCUX_MSW_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_MSW_ECO(a) (a)
#define arguments_BDK_CCUX_MSW_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_msw_msh#_ecc_dbg_cnt
 *
 * INTERNAL: CCU MSW DBE Detection Counter Registers
 *
 * This register records the value of saturating counters that keep track of the
 * number of bit flip errors on the dat mesh coming into the MSW in each
 * cardinal direction. For debug purposes only - no correction.
 * _ MSH(0) = Mesh north to MSW.
 * _ MSH(1) = Mesh east to MSW.
 * _ MSH(2) = Mesh south to MSW.
 * _ MSH(3) = Mesh west to MSW.
 */
union bdk_ccux_msw_mshx_ecc_dbg_cnt
{
    uint64_t u;
    struct bdk_ccux_msw_mshx_ecc_dbg_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t sbe                   : 16; /**< [ 31: 16](R/W/H) Current single-bit error counter value. */
        uint64_t dbe                   : 16; /**< [ 15:  0](R/W/H) Current double-bit error counter value. */
#else /* Word 0 - Little Endian */
        uint64_t dbe                   : 16; /**< [ 15:  0](R/W/H) Current double-bit error counter value. */
        uint64_t sbe                   : 16; /**< [ 31: 16](R/W/H) Current single-bit error counter value. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msw_mshx_ecc_dbg_cnt_s cn; */
};
typedef union bdk_ccux_msw_mshx_ecc_dbg_cnt bdk_ccux_msw_mshx_ecc_dbg_cnt_t;

static inline uint64_t BDK_CCUX_MSW_MSHX_ECC_DBG_CNT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSW_MSHX_ECC_DBG_CNT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=3)))
        return 0x87e050200208ll + 0x1000000ll * ((a) & 0x3) + 0x40000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=3)))
        return 0x87e050200208ll + 0x1000000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=3)))
        return 0x87e050200208ll + 0x1000000ll * ((a) & 0x0) + 0x40000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=3)))
        return 0x87e050200208ll + 0x1000000ll * ((a) & 0x0) + 0x40000ll * ((b) & 0x3);
    __bdk_csr_fatal("CCUX_MSW_MSHX_ECC_DBG_CNT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSW_MSHX_ECC_DBG_CNT(a,b) bdk_ccux_msw_mshx_ecc_dbg_cnt_t
#define bustype_BDK_CCUX_MSW_MSHX_ECC_DBG_CNT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSW_MSHX_ECC_DBG_CNT(a,b) "CCUX_MSW_MSHX_ECC_DBG_CNT"
#define device_bar_BDK_CCUX_MSW_MSHX_ECC_DBG_CNT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_MSW_MSHX_ECC_DBG_CNT(a,b) (a)
#define arguments_BDK_CCUX_MSW_MSHX_ECC_DBG_CNT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_msw_msh#_pfc#
 *
 * CCU MSW Performance Counter Registers
 */
union bdk_ccux_msw_mshx_pfcx
{
    uint64_t u;
    struct bdk_ccux_msw_mshx_pfcx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Current counter value. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Current counter value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msw_mshx_pfcx_s cn; */
};
typedef union bdk_ccux_msw_mshx_pfcx bdk_ccux_msw_mshx_pfcx_t;

static inline uint64_t BDK_CCUX_MSW_MSHX_PFCX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSW_MSHX_PFCX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=3) && (c<=3)))
        return 0x87e050200100ll + 0x1000000ll * ((a) & 0x3) + 0x40000ll * ((b) & 0x3) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=3) && (c<=3)))
        return 0x87e050200100ll + 0x1000000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x3) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=3) && (c<=3)))
        return 0x87e050200100ll + 0x1000000ll * ((a) & 0x0) + 0x40000ll * ((b) & 0x3) + 8ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=3) && (c<=3)))
        return 0x87e050200100ll + 0x1000000ll * ((a) & 0x0) + 0x40000ll * ((b) & 0x3) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("CCUX_MSW_MSHX_PFCX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSW_MSHX_PFCX(a,b,c) bdk_ccux_msw_mshx_pfcx_t
#define bustype_BDK_CCUX_MSW_MSHX_PFCX(a,b,c) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSW_MSHX_PFCX(a,b,c) "CCUX_MSW_MSHX_PFCX"
#define device_bar_BDK_CCUX_MSW_MSHX_PFCX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_MSW_MSHX_PFCX(a,b,c) (a)
#define arguments_BDK_CCUX_MSW_MSHX_PFCX(a,b,c) (a),(b),(c),-1

/**
 * Register (RSL) ccu#_msw_msh#_prf
 *
 * CCU MSW Performance Counter Control Registers
 * This register controls measurement of the number of active cycles on each sub-mesh
 * out from MSW in one cardinal direction. Note a full cache line on the dat mesh
 * is counted as two active cycles.
 * _ MSH(0) = MSW to Mesh North.
 * _ MSH(1) = MSW to Mesh East.
 * _ MSH(2) = MSW to Mesh South.
 * _ MSH(3) = MSW to Mesh West.
 */
union bdk_ccux_msw_mshx_prf
{
    uint64_t u;
    struct bdk_ccux_msw_mshx_prf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t vcc_en                : 1;  /**< [  3:  3](R/W) Enable counting the number of active cycles out of MSW on the VCC submesh in CCU()_MSW_MSH()_PFC(3) */
        uint64_t dat_en                : 1;  /**< [  2:  2](R/W) Enable counting the number of active cycles out of MSW on the DAT submesh in CCU()_MSW_MSH()_PFC(2) */
        uint64_t cmd_en                : 1;  /**< [  1:  1](R/W) Enable counting the number of active cycles out of MSW on the CMD submesh in CCU()_MSW_MSH()_PFC(1) */
        uint64_t ack_en                : 1;  /**< [  0:  0](R/W) Enable counting the number of active cycles out of MSW on the ACK submesh in CCU()_MSW_MSH()_PFC(0) */
#else /* Word 0 - Little Endian */
        uint64_t ack_en                : 1;  /**< [  0:  0](R/W) Enable counting the number of active cycles out of MSW on the ACK submesh in CCU()_MSW_MSH()_PFC(0) */
        uint64_t cmd_en                : 1;  /**< [  1:  1](R/W) Enable counting the number of active cycles out of MSW on the CMD submesh in CCU()_MSW_MSH()_PFC(1) */
        uint64_t dat_en                : 1;  /**< [  2:  2](R/W) Enable counting the number of active cycles out of MSW on the DAT submesh in CCU()_MSW_MSH()_PFC(2) */
        uint64_t vcc_en                : 1;  /**< [  3:  3](R/W) Enable counting the number of active cycles out of MSW on the VCC submesh in CCU()_MSW_MSH()_PFC(3) */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msw_mshx_prf_s cn; */
};
typedef union bdk_ccux_msw_mshx_prf bdk_ccux_msw_mshx_prf_t;

static inline uint64_t BDK_CCUX_MSW_MSHX_PRF(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSW_MSHX_PRF(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=3)))
        return 0x87e050200018ll + 0x1000000ll * ((a) & 0x3) + 0x40000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=3)))
        return 0x87e050200018ll + 0x1000000ll * ((a) & 0x7) + 0x40000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=3)))
        return 0x87e050200018ll + 0x1000000ll * ((a) & 0x0) + 0x40000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=3)))
        return 0x87e050200018ll + 0x1000000ll * ((a) & 0x0) + 0x40000ll * ((b) & 0x3);
    __bdk_csr_fatal("CCUX_MSW_MSHX_PRF", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSW_MSHX_PRF(a,b) bdk_ccux_msw_mshx_prf_t
#define bustype_BDK_CCUX_MSW_MSHX_PRF(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSW_MSHX_PRF(a,b) "CCUX_MSW_MSHX_PRF"
#define device_bar_BDK_CCUX_MSW_MSHX_PRF(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_MSW_MSHX_PRF(a,b) (a)
#define arguments_BDK_CCUX_MSW_MSHX_PRF(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_msw_scratch
 *
 * INTERNAL: CCU MSW General Purpose Scratch Register
 *
 * These registers are reset only by hardware during chip cold reset. The values of the CSR
 * fields in these registers do not change during chip warm or soft resets.
 */
union bdk_ccux_msw_scratch
{
    uint64_t u;
    struct bdk_ccux_msw_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_msw_scratch_s cn; */
};
typedef union bdk_ccux_msw_scratch bdk_ccux_msw_scratch_t;

static inline uint64_t BDK_CCUX_MSW_SCRATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_MSW_SCRATCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050200000ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050200000ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050200000ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050200000ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_MSW_SCRATCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_MSW_SCRATCH(a) bdk_ccux_msw_scratch_t
#define bustype_BDK_CCUX_MSW_SCRATCH(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_MSW_SCRATCH(a) "CCUX_MSW_SCRATCH"
#define device_bar_BDK_CCUX_MSW_SCRATCH(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_MSW_SCRATCH(a) (a)
#define arguments_BDK_CCUX_MSW_SCRATCH(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_bist_status
 *
 * CCU PIC BIST Status Register
 */
union bdk_ccux_pic_bist_status
{
    uint64_t u;
    struct bdk_ccux_pic_bist_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t mlcd1fl               : 4;  /**< [  9:  6](RO/H) BIST failure status for MLC data arrays for ways 5-9. */
        uint64_t mlcd0fl               : 4;  /**< [  5:  2](RO/H) BIST failure status for MLC data arrays for ways 0-4. */
        uint64_t mlct1fl               : 1;  /**< [  1:  1](RO/H) BIST failure status for MLC tag arrays for ways 5-9. */
        uint64_t mlct0fl               : 1;  /**< [  0:  0](RO/H) BIST failure status for MLC tag arrays for ways 0-4. */
#else /* Word 0 - Little Endian */
        uint64_t mlct0fl               : 1;  /**< [  0:  0](RO/H) BIST failure status for MLC tag arrays for ways 0-4. */
        uint64_t mlct1fl               : 1;  /**< [  1:  1](RO/H) BIST failure status for MLC tag arrays for ways 5-9. */
        uint64_t mlcd0fl               : 4;  /**< [  5:  2](RO/H) BIST failure status for MLC data arrays for ways 0-4. */
        uint64_t mlcd1fl               : 4;  /**< [  9:  6](RO/H) BIST failure status for MLC data arrays for ways 5-9. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_bist_status_s cn; */
};
typedef union bdk_ccux_pic_bist_status bdk_ccux_pic_bist_status_t;

static inline uint64_t BDK_CCUX_PIC_BIST_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_BIST_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050000058ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050000058ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050000058ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050000058ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_PIC_BIST_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_BIST_STATUS(a) bdk_ccux_pic_bist_status_t
#define bustype_BDK_CCUX_PIC_BIST_STATUS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_BIST_STATUS(a) "CCUX_PIC_BIST_STATUS"
#define device_bar_BDK_CCUX_PIC_BIST_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_BIST_STATUS(a) (a)
#define arguments_BDK_CCUX_PIC_BIST_STATUS(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_bp_test
 *
 * INTERNAL: PIC Backpressure Test Register
 */
union bdk_ccux_pic_bp_test
{
    uint64_t u;
    struct bdk_ccux_pic_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit traffic out of PIC onto ACK mesh.
                                                                 \<62\> = Limit traffic out of PIC onto CMD mesh.
                                                                 \<61\> = Limit traffic out of PIC onto DAT mesh.
                                                                 \<60\> = Limit traffic out of PIC onto INV bus. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits defined as
                                                                 0x0=100% of the time, 0x1=99.2% (127/128) of the time,
                                                                 0x2=96.9% (31/32) of the time, 0x3=87.5% (7/8) of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits defined as
                                                                 0x0=100% of the time, 0x1=99.2% (127/128) of the time,
                                                                 0x2=96.9% (31/32) of the time, 0x3=87.5% (7/8) of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit traffic out of PIC onto ACK mesh.
                                                                 \<62\> = Limit traffic out of PIC onto CMD mesh.
                                                                 \<61\> = Limit traffic out of PIC onto DAT mesh.
                                                                 \<60\> = Limit traffic out of PIC onto INV bus. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_bp_test_s cn; */
};
typedef union bdk_ccux_pic_bp_test bdk_ccux_pic_bp_test_t;

static inline uint64_t BDK_CCUX_PIC_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_BP_TEST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050000018ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050000018ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050000018ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050000018ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_PIC_BP_TEST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_BP_TEST(a) bdk_ccux_pic_bp_test_t
#define bustype_BDK_CCUX_PIC_BP_TEST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_BP_TEST(a) "CCUX_PIC_BP_TEST"
#define device_bar_BDK_CCUX_PIC_BP_TEST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_BP_TEST(a) (a)
#define arguments_BDK_CCUX_PIC_BP_TEST(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_dll
 *
 * INTERNAL: CCU Core-Clock DLL Status Register
 *
 * Status of the CCU core-clock DLL. For diagnostic use only.
 */
union bdk_ccux_pic_dll
{
    uint64_t u;
    struct bdk_ccux_pic_dll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t dbg_window            : 3;  /**< [ 34: 32](R/W/H) Defines a debug window, during which the DLL settings and the phase detector
                                                                 outputs will be monitored. The min and the max DLL setting during that window is
                                                                 going to be reported as well as any illegal phase detector outputs. Every write
                                                                 to the [DBG_WINDOW] resets [ILLEGAL_PD_REVERSED], [ILLEGAL_PD_LATE],
                                                                 [ILLEGAL_PD_EARLY], [MAX_DLL_SETTING] and [MIN_DLL_SETTING]. The debug window
                                                                 will correspond to the following number of rclk cycles based on the [DBG_WINDOW]
                                                                 value.
                                                                 0x0 = Indefinetly.
                                                                 0x1 = 2 ^ 12 core clock cycles.
                                                                 0x2 = 2 ^ 18 core clock cycles.
                                                                 0x3 = 2 ^ 24 core clock cycles.
                                                                 0x4 = 2 ^ 30 core clock cycles.
                                                                 0x5 = 2 ^ 36 core clock cycles.
                                                                 0x6 = 2 ^ 42 core clock cycles.
                                                                 0x7 = 2 ^ 48 core clock cycles. */
        uint64_t dbg_window_done       : 1;  /**< [ 31: 31](RO/H) Indicates if the debug window set by [DBG_WINDOW] is completed. */
        uint64_t illegal_pd_reversed   : 1;  /**< [ 30: 30](RO/H) clk_fast_rgt and clk_fast_lft outputs of the phase detector had concurrently an
                                                                 illegal reading during the last debug window set by [DBG_WINDOW]. */
        uint64_t illegal_pd_late       : 1;  /**< [ 29: 29](RO/H) clk_fast_rgt output of the phase detector had an illegal reading (1) during the
                                                                 last debug window set by [DBG_WINDOW]. */
        uint64_t illegal_pd_early      : 1;  /**< [ 28: 28](RO/H) clk_fast_lft output of the phase detector had an illegal reading (0) during the
                                                                 last debug window set by [DBG_WINDOW]. */
        uint64_t reserved_27           : 1;
        uint64_t max_dll_setting       : 7;  /**< [ 26: 20](RO/H) Max reported DLL setting during the last debug window set by [DBG_WINDOW]. */
        uint64_t reserved_19           : 1;
        uint64_t min_dll_setting       : 7;  /**< [ 18: 12](RO/H) Min reported DLL setting during the last debug window set by [DBG_WINDOW]. */
        uint64_t pd_out                : 3;  /**< [ 11:  9](RO/H) Synchronized output from CCU phase detector:
                                                                 \<11\> = clk_fast_mid.
                                                                 \<10\> = clk_fast_lft.
                                                                 \<9\> = clk_fast_rgt. */
        uint64_t dll_lock              : 1;  /**< [  8:  8](RO/H) The dll_lock signal from ROC core-clock DLL, from the positive edge of refclk. */
        uint64_t reserved_7            : 1;
        uint64_t dll_setting           : 7;  /**< [  6:  0](RO/H) The ROC core-clock DLL setting, from the negative edge of refclk. */
#else /* Word 0 - Little Endian */
        uint64_t dll_setting           : 7;  /**< [  6:  0](RO/H) The ROC core-clock DLL setting, from the negative edge of refclk. */
        uint64_t reserved_7            : 1;
        uint64_t dll_lock              : 1;  /**< [  8:  8](RO/H) The dll_lock signal from ROC core-clock DLL, from the positive edge of refclk. */
        uint64_t pd_out                : 3;  /**< [ 11:  9](RO/H) Synchronized output from CCU phase detector:
                                                                 \<11\> = clk_fast_mid.
                                                                 \<10\> = clk_fast_lft.
                                                                 \<9\> = clk_fast_rgt. */
        uint64_t min_dll_setting       : 7;  /**< [ 18: 12](RO/H) Min reported DLL setting during the last debug window set by [DBG_WINDOW]. */
        uint64_t reserved_19           : 1;
        uint64_t max_dll_setting       : 7;  /**< [ 26: 20](RO/H) Max reported DLL setting during the last debug window set by [DBG_WINDOW]. */
        uint64_t reserved_27           : 1;
        uint64_t illegal_pd_early      : 1;  /**< [ 28: 28](RO/H) clk_fast_lft output of the phase detector had an illegal reading (0) during the
                                                                 last debug window set by [DBG_WINDOW]. */
        uint64_t illegal_pd_late       : 1;  /**< [ 29: 29](RO/H) clk_fast_rgt output of the phase detector had an illegal reading (1) during the
                                                                 last debug window set by [DBG_WINDOW]. */
        uint64_t illegal_pd_reversed   : 1;  /**< [ 30: 30](RO/H) clk_fast_rgt and clk_fast_lft outputs of the phase detector had concurrently an
                                                                 illegal reading during the last debug window set by [DBG_WINDOW]. */
        uint64_t dbg_window_done       : 1;  /**< [ 31: 31](RO/H) Indicates if the debug window set by [DBG_WINDOW] is completed. */
        uint64_t dbg_window            : 3;  /**< [ 34: 32](R/W/H) Defines a debug window, during which the DLL settings and the phase detector
                                                                 outputs will be monitored. The min and the max DLL setting during that window is
                                                                 going to be reported as well as any illegal phase detector outputs. Every write
                                                                 to the [DBG_WINDOW] resets [ILLEGAL_PD_REVERSED], [ILLEGAL_PD_LATE],
                                                                 [ILLEGAL_PD_EARLY], [MAX_DLL_SETTING] and [MIN_DLL_SETTING]. The debug window
                                                                 will correspond to the following number of rclk cycles based on the [DBG_WINDOW]
                                                                 value.
                                                                 0x0 = Indefinetly.
                                                                 0x1 = 2 ^ 12 core clock cycles.
                                                                 0x2 = 2 ^ 18 core clock cycles.
                                                                 0x3 = 2 ^ 24 core clock cycles.
                                                                 0x4 = 2 ^ 30 core clock cycles.
                                                                 0x5 = 2 ^ 36 core clock cycles.
                                                                 0x6 = 2 ^ 42 core clock cycles.
                                                                 0x7 = 2 ^ 48 core clock cycles. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_dll_s cn; */
};
typedef union bdk_ccux_pic_dll bdk_ccux_pic_dll_t;

static inline uint64_t BDK_CCUX_PIC_DLL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_DLL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050000080ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050000080ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050000080ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050000080ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_PIC_DLL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_DLL(a) bdk_ccux_pic_dll_t
#define bustype_BDK_CCUX_PIC_DLL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_DLL(a) "CCUX_PIC_DLL"
#define device_bar_BDK_CCUX_PIC_DLL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_DLL(a) (a)
#define arguments_BDK_CCUX_PIC_DLL(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_eco
 *
 * INTERNAL: CCU PIC ECO Register
 *
 * These registers exist to provide CSR flops in case they are needed for ECOs.
 */
union bdk_ccux_pic_eco
{
    uint64_t u;
    struct bdk_ccux_pic_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_eco_s cn; */
};
typedef union bdk_ccux_pic_eco bdk_ccux_pic_eco_t;

static inline uint64_t BDK_CCUX_PIC_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050000008ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050000008ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050000008ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050000008ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_PIC_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_ECO(a) bdk_ccux_pic_eco_t
#define bustype_BDK_CCUX_PIC_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_ECO(a) "CCUX_PIC_ECO"
#define device_bar_BDK_CCUX_PIC_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_ECO(a) (a)
#define arguments_BDK_CCUX_PIC_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_mlc_bp_test
 *
 * INTERNAL: MLC Backpressure Test Register
 */
union bdk_ccux_pic_mlc_bp_test
{
    uint64_t u;
    struct bdk_ccux_pic_mlc_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit requests for MSW, backpressure lfb.
                                                                 \<62\> = Limit access to RSC buses, backpressure RSC logic.
                                                                 \<61\> = Limit commit access, backpressure commit logic FIFO.
                                                                 \<60\> = Limit MLC arb xmc grants, backpressure xmc FIFOs. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits defined as
                                                                 0x0=100% of the time, 0x1=99.2% (127/128) of the time,
                                                                 0x2=96.9% (31/32) of the time, 0x3=87.5% (7/8) of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits defined as
                                                                 0x0=100% of the time, 0x1=99.2% (127/128) of the time,
                                                                 0x2=96.9% (31/32) of the time, 0x3=87.5% (7/8) of the time.
                                                                   \<23:22\> = Config 3.
                                                                   \<21:20\> = Config 2.
                                                                   \<19:18\> = Config 1.
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Limit requests for MSW, backpressure lfb.
                                                                 \<62\> = Limit access to RSC buses, backpressure RSC logic.
                                                                 \<61\> = Limit commit access, backpressure commit logic FIFO.
                                                                 \<60\> = Limit MLC arb xmc grants, backpressure xmc FIFOs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_mlc_bp_test_s cn; */
};
typedef union bdk_ccux_pic_mlc_bp_test bdk_ccux_pic_mlc_bp_test_t;

static inline uint64_t BDK_CCUX_PIC_MLC_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_MLC_BP_TEST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050000020ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050000020ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050000020ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050000020ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_PIC_MLC_BP_TEST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_MLC_BP_TEST(a) bdk_ccux_pic_mlc_bp_test_t
#define bustype_BDK_CCUX_PIC_MLC_BP_TEST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_MLC_BP_TEST(a) "CCUX_PIC_MLC_BP_TEST"
#define device_bar_BDK_CCUX_PIC_MLC_BP_TEST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_MLC_BP_TEST(a) (a)
#define arguments_BDK_CCUX_PIC_MLC_BP_TEST(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_mlc_tag
 *
 * CCU Mid-Level Cache Tag Data Registers
 * This register holds the tag information for IS:LTGI commands.
 */
union bdk_ccux_pic_mlc_tag
{
    uint64_t u;
    struct bdk_ccux_pic_mlc_tag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_46_63        : 18;
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t tag                   : 26; /**< [ 42: 17](RO/H) The tag. TAG\<42:17\> is the corresponding bits from the MLC+LMC internal MLC/DRAM byte
                                                                 address. */
        uint64_t reserved_6_16         : 11;
        uint64_t parity                : 2;  /**< [  5:  4](RO/H) Indicates the tag parity. */
        uint64_t val                   : 1;  /**< [  3:  3](RO/H) Indicates the tag valid bit. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t val                   : 1;  /**< [  3:  3](RO/H) Indicates the tag valid bit. */
        uint64_t parity                : 2;  /**< [  5:  4](RO/H) Indicates the tag parity. */
        uint64_t reserved_6_16         : 11;
        uint64_t tag                   : 26; /**< [ 42: 17](RO/H) The tag. TAG\<42:17\> is the corresponding bits from the MLC+LMC internal MLC/DRAM byte
                                                                 address. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit. */
        uint64_t reserved_46_63        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_mlc_tag_s cn; */
};
typedef union bdk_ccux_pic_mlc_tag bdk_ccux_pic_mlc_tag_t;

static inline uint64_t BDK_CCUX_PIC_MLC_TAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_MLC_TAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050000010ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050000010ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050000010ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050000010ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_PIC_MLC_TAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_MLC_TAG(a) bdk_ccux_pic_mlc_tag_t
#define bustype_BDK_CCUX_PIC_MLC_TAG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_MLC_TAG(a) "CCUX_PIC_MLC_TAG"
#define device_bar_BDK_CCUX_PIC_MLC_TAG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_MLC_TAG(a) (a)
#define arguments_BDK_CCUX_PIC_MLC_TAG(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_mlc_waydis
 *
 * CCU PIC MLC Way Disable Register
 * These registers disable allocation of ways in the MLC.  For diagnostic use only.
 */
union bdk_ccux_pic_mlc_waydis
{
    uint64_t u;
    struct bdk_ccux_pic_mlc_waydis_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t waydis                : 10; /**< [  9:  0](R/W) Each bit will disable allocation in the corresponding way.
                                                                 Internal:
                                                                 These bits do not affect the value read from CCS_MLC_CONST[WAYS]. (It can't,
                                                                 since this is CCU-specific and CCS_MLC_CONST is CCS-wide.) */
#else /* Word 0 - Little Endian */
        uint64_t waydis                : 10; /**< [  9:  0](R/W) Each bit will disable allocation in the corresponding way.
                                                                 Internal:
                                                                 These bits do not affect the value read from CCS_MLC_CONST[WAYS]. (It can't,
                                                                 since this is CCU-specific and CCS_MLC_CONST is CCS-wide.) */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_mlc_waydis_s cn; */
};
typedef union bdk_ccux_pic_mlc_waydis bdk_ccux_pic_mlc_waydis_t;

static inline uint64_t BDK_CCUX_PIC_MLC_WAYDIS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_MLC_WAYDIS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050000060ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050000060ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050000060ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050000060ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_PIC_MLC_WAYDIS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_MLC_WAYDIS(a) bdk_ccux_pic_mlc_waydis_t
#define bustype_BDK_CCUX_PIC_MLC_WAYDIS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_MLC_WAYDIS(a) "CCUX_PIC_MLC_WAYDIS"
#define device_bar_BDK_CCUX_PIC_MLC_WAYDIS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_MLC_WAYDIS(a) (a)
#define arguments_BDK_CCUX_PIC_MLC_WAYDIS(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_mtd#_err
 *
 * CCU PIC MTD DAT Error Info Registers
 * This register records error information for MDC DBE/SBE interrupts which map to the
 * MDC node in the PIC_CTL_MLC_MTD_BISR. The first [DBE] error will lock the register
 * until the logged error type is cleared; [SBE] errors lock the register until either
 * the logged error type is cleared or a [DBE] error is logged. Only one of [SBE],
 * [DBE] should be set at a time. In the event the register is read with both [SBE] and
 * [SBE] equal to 0 during interrupt handling that is an indication that, due to a
 * register set/clear race, information about one or more errors was lost while
 * processing an earlier error.
 *
 * Software should scrub the MTD error indicated by the corresponding MDC_ECC_STATUS[ROW]
 * via a SYS CVMCACHEWBIL2I instruction (see below).  Otherwise, hardware may encounter
 * the error again.  Software may also choose to count the number of these errors.
 *
 * The SYS CVMCACHEWBIL2I instruction payload should have:
 *     \<pre\>
 *       payload\<20:17\> select the way (MDC_ECC_STATUS[ROW] for CCUn_PIC_MTD0_ERR;
 *                                      MDC_ECC_STATUS[ROW]+5 for CCUn_PIC_MTD1_ERR)
 *       payload\<16:7\> select the set/index.
 *     \</pre\>
 */
union bdk_ccux_pic_mtdx_err
{
    uint64_t u;
    struct bdk_ccux_pic_mtdx_err_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sbe                   : 1;  /**< [ 63: 63](R/W1C/H) If [SBE]=1, then the logged information is for a MDC SBE error. */
        uint64_t dbe                   : 1;  /**< [ 62: 62](R/W1C/H) If [DBE]=1, then the logged information is for a MDC DBE error. */
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_IS should ever be logged. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_IS_SCMD_E. */
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) The sid of the core which issued the request causing the error. */
        uint64_t reserved_46_51        : 6;
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request which detected the error. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t addr                  : 36; /**< [ 42:  7](RO/H) Block address of the request which detected the error. */
        uint64_t way                   : 3;  /**< [  6:  4](RO/H) Reserved.
                                                                 Internal:
                                                                 Way within MTD, not MLC way number. Same as what is reported to MDC. */
        uint64_t dat                   : 4;  /**< [  3:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 A flat vector indicating the DAT slice of MTD, to identify which RAM had ECC error(s)
                                                                 (does not correspond to 128-bit word). */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 4;  /**< [  3:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 A flat vector indicating the DAT slice of MTD, to identify which RAM had ECC error(s)
                                                                 (does not correspond to 128-bit word). */
        uint64_t way                   : 3;  /**< [  6:  4](RO/H) Reserved.
                                                                 Internal:
                                                                 Way within MTD, not MLC way number. Same as what is reported to MDC. */
        uint64_t addr                  : 36; /**< [ 42:  7](RO/H) Block address of the request which detected the error. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request which detected the error. */
        uint64_t reserved_46_51        : 6;
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) The sid of the core which issued the request causing the error. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_IS_SCMD_E. */
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_IS should ever be logged. */
        uint64_t dbe                   : 1;  /**< [ 62: 62](R/W1C/H) If [DBE]=1, then the logged information is for a MDC DBE error. */
        uint64_t sbe                   : 1;  /**< [ 63: 63](R/W1C/H) If [SBE]=1, then the logged information is for a MDC SBE error. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_mtdx_err_s cn; */
};
typedef union bdk_ccux_pic_mtdx_err bdk_ccux_pic_mtdx_err_t;

static inline uint64_t BDK_CCUX_PIC_MTDX_ERR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_MTDX_ERR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050000068ll + 0x1000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050000068ll + 0x1000000ll * ((a) & 0x7) + 0x10000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050000068ll + 0x1000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050000068ll + 0x1000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_PIC_MTDX_ERR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_MTDX_ERR(a,b) bdk_ccux_pic_mtdx_err_t
#define bustype_BDK_CCUX_PIC_MTDX_ERR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_MTDX_ERR(a,b) "CCUX_PIC_MTDX_ERR"
#define device_bar_BDK_CCUX_PIC_MTDX_ERR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_MTDX_ERR(a,b) (a)
#define arguments_BDK_CCUX_PIC_MTDX_ERR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_pic_pfc#
 *
 * CCU PIC Performance Counter Registers
 */
union bdk_ccux_pic_pfcx
{
    uint64_t u;
    struct bdk_ccux_pic_pfcx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Current counter value. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Current counter value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_pfcx_s cn; */
};
typedef union bdk_ccux_pic_pfcx bdk_ccux_pic_pfcx_t;

static inline uint64_t BDK_CCUX_PIC_PFCX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_PFCX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=3)))
        return 0x87e050000090ll + 0x1000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=3)))
        return 0x87e050000090ll + 0x1000000ll * ((a) & 0x7) + 0x10000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=3)))
        return 0x87e050000090ll + 0x1000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=3)))
        return 0x87e050000090ll + 0x1000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3);
    __bdk_csr_fatal("CCUX_PIC_PFCX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_PFCX(a,b) bdk_ccux_pic_pfcx_t
#define bustype_BDK_CCUX_PIC_PFCX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_PFCX(a,b) "CCUX_PIC_PFCX"
#define device_bar_BDK_CCUX_PIC_PFCX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_PFCX(a,b) (a)
#define arguments_BDK_CCUX_PIC_PFCX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_pic_prf
 *
 * CCU PIC Performance Counter Control Registers
 * All four counters are equivalent and can use any of the defined selects.
 */
union bdk_ccux_pic_prf
{
    uint64_t u;
    struct bdk_ccux_pic_prf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cnt3sel               : 8;  /**< [ 31: 24](R/W) Selects event to count for CCU()_PIC_PFC(3). Enumerated by CCU_PIC_PRF_SEL_E. */
        uint64_t cnt2sel               : 8;  /**< [ 23: 16](R/W) Selects event to count for CCU()_PIC_PFC(2). Enumerated by CCU_PIC_PRF_SEL_E. */
        uint64_t cnt1sel               : 8;  /**< [ 15:  8](R/W) Selects event to count for CCU()_PIC_PFC(1). Enumerated by CCU_PIC_PRF_SEL_E. */
        uint64_t cnt0sel               : 8;  /**< [  7:  0](R/W) Selects event to count for CCU()_PIC_PFC(0). Enumerated by CCU_PIC_PRF_SEL_E. */
#else /* Word 0 - Little Endian */
        uint64_t cnt0sel               : 8;  /**< [  7:  0](R/W) Selects event to count for CCU()_PIC_PFC(0). Enumerated by CCU_PIC_PRF_SEL_E. */
        uint64_t cnt1sel               : 8;  /**< [ 15:  8](R/W) Selects event to count for CCU()_PIC_PFC(1). Enumerated by CCU_PIC_PRF_SEL_E. */
        uint64_t cnt2sel               : 8;  /**< [ 23: 16](R/W) Selects event to count for CCU()_PIC_PFC(2). Enumerated by CCU_PIC_PRF_SEL_E. */
        uint64_t cnt3sel               : 8;  /**< [ 31: 24](R/W) Selects event to count for CCU()_PIC_PFC(3). Enumerated by CCU_PIC_PRF_SEL_E. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_prf_s cn; */
};
typedef union bdk_ccux_pic_prf bdk_ccux_pic_prf_t;

static inline uint64_t BDK_CCUX_PIC_PRF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_PRF(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050000088ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050000088ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050000088ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050000088ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_PIC_PRF", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_PRF(a) bdk_ccux_pic_prf_t
#define bustype_BDK_CCUX_PIC_PRF(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_PRF(a) "CCUX_PIC_PRF"
#define device_bar_BDK_CCUX_PIC_PRF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_PRF(a) (a)
#define arguments_BDK_CCUX_PIC_PRF(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_scratch
 *
 * INTERNAL: CCU PIC General Purpose Scratch Register
 *
 * These registers are reset only by hardware during chip cold reset. The values of the CSR
 * fields in these registers do not change during chip warm or soft resets.
 */
union bdk_ccux_pic_scratch
{
    uint64_t u;
    struct bdk_ccux_pic_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_scratch_s cn; */
};
typedef union bdk_ccux_pic_scratch bdk_ccux_pic_scratch_t;

static inline uint64_t BDK_CCUX_PIC_SCRATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_SCRATCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=3))
        return 0x87e050000000ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=5))
        return 0x87e050000000ll + 0x1000000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e050000000ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e050000000ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("CCUX_PIC_SCRATCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_SCRATCH(a) bdk_ccux_pic_scratch_t
#define bustype_BDK_CCUX_PIC_SCRATCH(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_SCRATCH(a) "CCUX_PIC_SCRATCH"
#define device_bar_BDK_CCUX_PIC_SCRATCH(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_SCRATCH(a) (a)
#define arguments_BDK_CCUX_PIC_SCRATCH(a) (a),-1,-1,-1

/**
 * Register (RSL) ccu#_pic_tag#_err
 *
 * CCU PIC MTD TAG Error Info Registers
 * This register records error information for MDC tag parity interrupts which map to the
 * MDC node in the PIC_CTL_MLC_MTD_TBISR. The first error will lock the register until the
 * logged error type is cleared.  Note that tag entries that cause a parity error are automatically
 * invalidated. In the event the register is read with [PARERR] equal to
 * 0 during interrupt handling that is an indication that, due to a register set/clear
 * race, information about one or more errors was lost while processing an earlier
 * error. Note that no scrubbing is required for TAG parity errors.
 */
union bdk_ccux_pic_tagx_err
{
    uint64_t u;
    struct bdk_ccux_pic_tagx_err_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t parerr                : 1;  /**< [ 63: 63](R/W1C/H) Indicates a parity error. */
        uint64_t reserved_62           : 1;
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_IS or CCS_CMD_E::CMD_NOP
                                                                 (invalidate from LLC) should ever be logged. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_IS_SCMD_E.  Unpredictable if CMD is CCS_CMD_E::CMD_NOP. */
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) The sid of the core which issued the request causing the error.
                                                                 Internal:
                                                                 Unpredictable if CMD is CCS_CMD_E::CMD_NOP. */
        uint64_t reserved_46_51        : 6;
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request which detected the error. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t addr                  : 36; /**< [ 42:  7](RO/H) Block address of the request which detected the error. */
        uint64_t way                   : 3;  /**< [  6:  4](RO/H) Reserved.
                                                                 Internal:
                                                                 Way within MTD, not MLC way number. Same as what is reported to MDC. */
        uint64_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_3          : 4;
        uint64_t way                   : 3;  /**< [  6:  4](RO/H) Reserved.
                                                                 Internal:
                                                                 Way within MTD, not MLC way number. Same as what is reported to MDC. */
        uint64_t addr                  : 36; /**< [ 42:  7](RO/H) Block address of the request which detected the error. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request which detected the error. */
        uint64_t reserved_46_51        : 6;
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) The sid of the core which issued the request causing the error.
                                                                 Internal:
                                                                 Unpredictable if CMD is CCS_CMD_E::CMD_NOP. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_IS_SCMD_E.  Unpredictable if CMD is CCS_CMD_E::CMD_NOP. */
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_IS or CCS_CMD_E::CMD_NOP
                                                                 (invalidate from LLC) should ever be logged. */
        uint64_t reserved_62           : 1;
        uint64_t parerr                : 1;  /**< [ 63: 63](R/W1C/H) Indicates a parity error. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_pic_tagx_err_s cn; */
};
typedef union bdk_ccux_pic_tagx_err bdk_ccux_pic_tagx_err_t;

static inline uint64_t BDK_CCUX_PIC_TAGX_ERR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_PIC_TAGX_ERR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050000070ll + 0x1000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050000070ll + 0x1000000ll * ((a) & 0x7) + 0x10000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050000070ll + 0x1000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050000070ll + 0x1000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_PIC_TAGX_ERR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_PIC_TAGX_ERR(a,b) bdk_ccux_pic_tagx_err_t
#define bustype_BDK_CCUX_PIC_TAGX_ERR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_PIC_TAGX_ERR(a,b) "CCUX_PIC_TAGX_ERR"
#define device_bar_BDK_CCUX_PIC_TAGX_ERR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_PIC_TAGX_ERR(a,b) (a)
#define arguments_BDK_CCUX_PIC_TAGX_ERR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_dat_err
 *
 * CCU TAD DAT Error Info Registers
 * This register records error information for MDC DBE/SBE interrupts which map to the
 * MDC node in the TAD_CTL_DTC. The first [DBE] error will lock the register until the
 * logged error type is cleared; [SBE] errors lock the register until either the logged
 * error type is cleared or a [DBE] error is logged. Only one of [SBE], [DBE] should be
 * set at a time. In the event the register is read with both [SBE] and [SBE] equal to
 * 0 during interrupt handling that is an indication that, due to a register set/clear
 * race, information about one or more errors was lost while processing an earlier
 * error. Note that MDC_ECC_STATUS[ROW] is sufficient to scrub any DAT
 * error with an index/way command (DTG=0, WAY[4]=0, WAY[3:0]=ROW[29:26],
 * IDX[9:0]=ROW[25:16]).
 */
union bdk_ccux_tadx_dat_err
{
    uint64_t u;
    struct bdk_ccux_tadx_dat_err_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sbe                   : 1;  /**< [ 63: 63](R/W1C/H) If [SBE]=1, then the logged information is for a MDC SBE error. */
        uint64_t dbe                   : 1;  /**< [ 62: 62](R/W1C/H) If [DBE]=1, then the logged information is for a MDC DBE error. */
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_DS, CCS_CMD_E::CMD_IS, and
                                                                 CCS_CMD_E::CMD_AT should ever be logged. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request which detected the error.
                                                                 Internal:
                                                                 If [CMD]=CCS_CMD_E::CMD_DS, enumerated by CCS_DS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_IS, enumerated by CCS_IS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_AT, enumerated by CCS_AT_SCMD_E. */
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) If [MS] indicates the source is a cluster, [SID] is the sid of the core within
                                                                 the cluster which issued the request causing the error. If [MS] indicated the
                                                                 source is not a cluster, [SID] is unpredictable. */
        uint64_t ms                    : 6;  /**< [ 51: 46](RO/H) Mesh source of the request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_RID_E. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request which detected the error. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t addr                  : 36; /**< [ 42:  7](RO/H) Block address of the cache-line in which the error was detected. This can be the
                                                                 address of the request which detected the error or the address of an eviction
                                                                 caused by the request. This field is the physical address after TAD set aliasing
                                                                 (if enabled, see CCS_ADR_CTL[DISSETALIAS]). */
        uint64_t ow                    : 3;  /**< [  6:  4](RO/H) 128-bit word in which the error was detected. */
        uint64_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_3          : 4;
        uint64_t ow                    : 3;  /**< [  6:  4](RO/H) 128-bit word in which the error was detected. */
        uint64_t addr                  : 36; /**< [ 42:  7](RO/H) Block address of the cache-line in which the error was detected. This can be the
                                                                 address of the request which detected the error or the address of an eviction
                                                                 caused by the request. This field is the physical address after TAD set aliasing
                                                                 (if enabled, see CCS_ADR_CTL[DISSETALIAS]). */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request which detected the error. */
        uint64_t ms                    : 6;  /**< [ 51: 46](RO/H) Mesh source of the request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_RID_E. */
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) If [MS] indicates the source is a cluster, [SID] is the sid of the core within
                                                                 the cluster which issued the request causing the error. If [MS] indicated the
                                                                 source is not a cluster, [SID] is unpredictable. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request which detected the error.
                                                                 Internal:
                                                                 If [CMD]=CCS_CMD_E::CMD_DS, enumerated by CCS_DS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_IS, enumerated by CCS_IS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_AT, enumerated by CCS_AT_SCMD_E. */
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_DS, CCS_CMD_E::CMD_IS, and
                                                                 CCS_CMD_E::CMD_AT should ever be logged. */
        uint64_t dbe                   : 1;  /**< [ 62: 62](R/W1C/H) If [DBE]=1, then the logged information is for a MDC DBE error. */
        uint64_t sbe                   : 1;  /**< [ 63: 63](R/W1C/H) If [SBE]=1, then the logged information is for a MDC SBE error. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_dat_err_s cn; */
};
typedef union bdk_ccux_tadx_dat_err bdk_ccux_tadx_dat_err_t;

static inline uint64_t BDK_CCUX_TADX_DAT_ERR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_DAT_ERR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400018ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400018ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400018ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400018ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_DAT_ERR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_DAT_ERR(a,b) bdk_ccux_tadx_dat_err_t
#define bustype_BDK_CCUX_TADX_DAT_ERR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_DAT_ERR(a,b) "CCUX_TADX_DAT_ERR"
#define device_bar_BDK_CCUX_TADX_DAT_ERR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_DAT_ERR(a,b) (a)
#define arguments_BDK_CCUX_TADX_DAT_ERR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_dbe_dbg_cnt
 *
 * INTERNAL: CCU TAD DBE Detection Counter Registers
 *
 * This register keeps track of the number of double-bit errors arriving on the DAT
 * mesh into the TAD from MSW in saturating counters. For debug purposes only - no
 * correction.
 */
union bdk_ccux_tadx_dbe_dbg_cnt
{
    uint64_t u;
    struct bdk_ccux_tadx_dbe_dbg_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ow3                   : 16; /**< [ 63: 48](R/W/H) Current double-bit error counter value for OW3. */
        uint64_t ow2                   : 16; /**< [ 47: 32](R/W/H) Current double-bit error counter value for OW2. */
        uint64_t ow1                   : 16; /**< [ 31: 16](R/W/H) Current double-bit error counter value for OW1. */
        uint64_t ow0                   : 16; /**< [ 15:  0](R/W/H) Current double-bit error counter value for OW0. */
#else /* Word 0 - Little Endian */
        uint64_t ow0                   : 16; /**< [ 15:  0](R/W/H) Current double-bit error counter value for OW0. */
        uint64_t ow1                   : 16; /**< [ 31: 16](R/W/H) Current double-bit error counter value for OW1. */
        uint64_t ow2                   : 16; /**< [ 47: 32](R/W/H) Current double-bit error counter value for OW2. */
        uint64_t ow3                   : 16; /**< [ 63: 48](R/W/H) Current double-bit error counter value for OW3. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_dbe_dbg_cnt_s cn; */
};
typedef union bdk_ccux_tadx_dbe_dbg_cnt bdk_ccux_tadx_dbe_dbg_cnt_t;

static inline uint64_t BDK_CCUX_TADX_DBE_DBG_CNT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_DBE_DBG_CNT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400048ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400048ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400048ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400048ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_DBE_DBG_CNT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_DBE_DBG_CNT(a,b) bdk_ccux_tadx_dbe_dbg_cnt_t
#define bustype_BDK_CCUX_TADX_DBE_DBG_CNT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_DBE_DBG_CNT(a,b) "CCUX_TADX_DBE_DBG_CNT"
#define device_bar_BDK_CCUX_TADX_DBE_DBG_CNT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_DBE_DBG_CNT(a,b) (a)
#define arguments_BDK_CCUX_TADX_DBE_DBG_CNT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_ecc_dbg_en
 *
 * INTERNAL: CCU TAD ECC Error Detection Counter Control Registers
 *
 * This register enables counting of the number of single and double bit errors on the
 * DAT mesh coming into the TAD from MSW.
 * For debug purposes only, no SBE correction.
 */
union bdk_ccux_tadx_ecc_dbg_en
{
    uint64_t u;
    struct bdk_ccux_tadx_ecc_dbg_en_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t sbe                   : 1;  /**< [  1:  1](R/W) Enable counting the number of SBEs seen on the DAT mesh in CCU()_TAD()_SBE_DBG_CNT. */
        uint64_t dbe                   : 1;  /**< [  0:  0](R/W) Enable counting the number of DBEs seen on the DAT mesh in CCU()_TAD()_DBE_DBG_CNT. */
#else /* Word 0 - Little Endian */
        uint64_t dbe                   : 1;  /**< [  0:  0](R/W) Enable counting the number of DBEs seen on the DAT mesh in CCU()_TAD()_DBE_DBG_CNT. */
        uint64_t sbe                   : 1;  /**< [  1:  1](R/W) Enable counting the number of SBEs seen on the DAT mesh in CCU()_TAD()_SBE_DBG_CNT. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_ecc_dbg_en_s cn; */
};
typedef union bdk_ccux_tadx_ecc_dbg_en bdk_ccux_tadx_ecc_dbg_en_t;

static inline uint64_t BDK_CCUX_TADX_ECC_DBG_EN(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_ECC_DBG_EN(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400038ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400038ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400038ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400038ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_ECC_DBG_EN", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_ECC_DBG_EN(a,b) bdk_ccux_tadx_ecc_dbg_en_t
#define bustype_BDK_CCUX_TADX_ECC_DBG_EN(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_ECC_DBG_EN(a,b) "CCUX_TADX_ECC_DBG_EN"
#define device_bar_BDK_CCUX_TADX_ECC_DBG_EN(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_ECC_DBG_EN(a,b) (a)
#define arguments_BDK_CCUX_TADX_ECC_DBG_EN(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_eco
 *
 * INTERNAL: CCU TAD ECO Register
 *
 * These registers exist to provide CSR flops in case they are needed for ECOs.
 */
union bdk_ccux_tadx_eco
{
    uint64_t u;
    struct bdk_ccux_tadx_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_eco_s cn; */
};
typedef union bdk_ccux_tadx_eco bdk_ccux_tadx_eco_t;

static inline uint64_t BDK_CCUX_TADX_ECO(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_ECO(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400008ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400008ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400008ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400008ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_ECO", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_ECO(a,b) bdk_ccux_tadx_eco_t
#define bustype_BDK_CCUX_TADX_ECO(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_ECO(a,b) "CCUX_TADX_ECO"
#define device_bar_BDK_CCUX_TADX_ECO(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_ECO(a,b) (a)
#define arguments_BDK_CCUX_TADX_ECO(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_int_ena_w1c
 *
 * CCU TAD Interrupt Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_ccux_tadx_int_ena_w1c
{
    uint64_t u;
    struct bdk_ccux_tadx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CCU(0..3)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CCU(0..3)_TAD(0..1)_INT_W1C[RDNXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CCU(0..3)_TAD(0..1)_INT_W1C[RDNXM]. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CCU(0..3)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_int_ena_w1c_s cn9; */
    /* struct bdk_ccux_tadx_int_ena_w1c_s cn96xx; */
    struct bdk_ccux_tadx_int_ena_w1c_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CCU(0..5)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CCU(0..5)_TAD(0..1)_INT_W1C[RDNXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CCU(0..5)_TAD(0..1)_INT_W1C[RDNXM]. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CCU(0..5)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_ccux_tadx_int_ena_w1c_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CCU(0)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CCU(0)_TAD(0..1)_INT_W1C[RDNXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for CCU(0)_TAD(0..1)_INT_W1C[RDNXM]. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for CCU(0)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_ccux_tadx_int_ena_w1c_cnf95xx loki; */
};
typedef union bdk_ccux_tadx_int_ena_w1c bdk_ccux_tadx_int_ena_w1c_t;

static inline uint64_t BDK_CCUX_TADX_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050480010ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050480010ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050480010ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050480010ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_INT_ENA_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_INT_ENA_W1C(a,b) bdk_ccux_tadx_int_ena_w1c_t
#define bustype_BDK_CCUX_TADX_INT_ENA_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_INT_ENA_W1C(a,b) "CCUX_TADX_INT_ENA_W1C"
#define device_bar_BDK_CCUX_TADX_INT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_INT_ENA_W1C(a,b) (a)
#define arguments_BDK_CCUX_TADX_INT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_int_ena_w1s
 *
 * CCU TAD Interrupt Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_ccux_tadx_int_ena_w1s
{
    uint64_t u;
    struct bdk_ccux_tadx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CCU(0..3)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CCU(0..3)_TAD(0..1)_INT_W1C[RDNXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CCU(0..3)_TAD(0..1)_INT_W1C[RDNXM]. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CCU(0..3)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_int_ena_w1s_s cn9; */
    /* struct bdk_ccux_tadx_int_ena_w1s_s cn96xx; */
    struct bdk_ccux_tadx_int_ena_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CCU(0..5)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CCU(0..5)_TAD(0..1)_INT_W1C[RDNXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CCU(0..5)_TAD(0..1)_INT_W1C[RDNXM]. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CCU(0..5)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_ccux_tadx_int_ena_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CCU(0)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CCU(0)_TAD(0..1)_INT_W1C[RDNXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for CCU(0)_TAD(0..1)_INT_W1C[RDNXM]. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for CCU(0)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_ccux_tadx_int_ena_w1s_cnf95xx loki; */
};
typedef union bdk_ccux_tadx_int_ena_w1s bdk_ccux_tadx_int_ena_w1s_t;

static inline uint64_t BDK_CCUX_TADX_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050480018ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050480018ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050480018ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050480018ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_INT_ENA_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_INT_ENA_W1S(a,b) bdk_ccux_tadx_int_ena_w1s_t
#define bustype_BDK_CCUX_TADX_INT_ENA_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_INT_ENA_W1S(a,b) "CCUX_TADX_INT_ENA_W1S"
#define device_bar_BDK_CCUX_TADX_INT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_INT_ENA_W1S(a,b) (a)
#define arguments_BDK_CCUX_TADX_INT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_int_w1c
 *
 * CCU TAD Interrupt Register
 * This register is for TAD-based interrupts.
 */
union bdk_ccux_tadx_int_w1c
{
    uint64_t u;
    struct bdk_ccux_tadx_int_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1C/H) Write NxM error. Write reference to outside all the defined and enabled address
                                                                 space control (ASC) regions, or secure write reference to an ASC region
                                                                 not enabled for secure access, or nonsecure write reference to an
                                                                 ASC region not enabled for nonsecure access.
                                                                 See CCU()_TAD()_NXM_ERR for logged information.
                                                                 See CCS_ASC_REGION()_START, CCS_ASC_REGION()_END, and
                                                                 CCS_ASC_REGION()_ATTR for ASC region specification. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1C/H) Read NxM error. Read reference to outside all the defined and enabled address
                                                                 space control (ASC) regions, or secure read reference to an ASC region not
                                                                 enabled for secure access, or nonsecure read reference to an ASC region not
                                                                 enabled for nonsecure access.
                                                                 [RDNXM] interrupts can occur during normal operation as the cores are
                                                                 allowed to prefetch to nonexistent memory locations.  Therefore,
                                                                 [RDNXM] is for informational purposes only.
                                                                 See CCU()_TAD()_NXM_ERR for logged information.
                                                                 See CCS_ASC_REGION()_START, CCS_ASC_REGION()_END, and
                                                                 CCS_ASC_REGION()_ATTR for ASC region specification. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1C/H) Read NxM error. Read reference to outside all the defined and enabled address
                                                                 space control (ASC) regions, or secure read reference to an ASC region not
                                                                 enabled for secure access, or nonsecure read reference to an ASC region not
                                                                 enabled for nonsecure access.
                                                                 [RDNXM] interrupts can occur during normal operation as the cores are
                                                                 allowed to prefetch to nonexistent memory locations.  Therefore,
                                                                 [RDNXM] is for informational purposes only.
                                                                 See CCU()_TAD()_NXM_ERR for logged information.
                                                                 See CCS_ASC_REGION()_START, CCS_ASC_REGION()_END, and
                                                                 CCS_ASC_REGION()_ATTR for ASC region specification. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1C/H) Write NxM error. Write reference to outside all the defined and enabled address
                                                                 space control (ASC) regions, or secure write reference to an ASC region
                                                                 not enabled for secure access, or nonsecure write reference to an
                                                                 ASC region not enabled for nonsecure access.
                                                                 See CCU()_TAD()_NXM_ERR for logged information.
                                                                 See CCS_ASC_REGION()_START, CCS_ASC_REGION()_END, and
                                                                 CCS_ASC_REGION()_ATTR for ASC region specification. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_int_w1c_s cn; */
};
typedef union bdk_ccux_tadx_int_w1c bdk_ccux_tadx_int_w1c_t;

static inline uint64_t BDK_CCUX_TADX_INT_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_INT_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050480000ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050480000ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050480000ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050480000ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_INT_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_INT_W1C(a,b) bdk_ccux_tadx_int_w1c_t
#define bustype_BDK_CCUX_TADX_INT_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_INT_W1C(a,b) "CCUX_TADX_INT_W1C"
#define device_bar_BDK_CCUX_TADX_INT_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_INT_W1C(a,b) (a)
#define arguments_BDK_CCUX_TADX_INT_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_int_w1s
 *
 * CCU TAD Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_ccux_tadx_int_w1s
{
    uint64_t u;
    struct bdk_ccux_tadx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CCU(0..3)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CCU(0..3)_TAD(0..1)_INT_W1C[RDNXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CCU(0..3)_TAD(0..1)_INT_W1C[RDNXM]. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CCU(0..3)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_int_w1s_s cn9; */
    /* struct bdk_ccux_tadx_int_w1s_s cn96xx; */
    struct bdk_ccux_tadx_int_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CCU(0..5)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CCU(0..5)_TAD(0..1)_INT_W1C[RDNXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CCU(0..5)_TAD(0..1)_INT_W1C[RDNXM]. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CCU(0..5)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_ccux_tadx_int_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CCU(0)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CCU(0)_TAD(0..1)_INT_W1C[RDNXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rdnxm                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets CCU(0)_TAD(0..1)_INT_W1C[RDNXM]. */
        uint64_t wrnxm                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets CCU(0)_TAD(0..1)_INT_W1C[WRNXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_ccux_tadx_int_w1s_cnf95xx loki; */
};
typedef union bdk_ccux_tadx_int_w1s bdk_ccux_tadx_int_w1s_t;

static inline uint64_t BDK_CCUX_TADX_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050480008ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050480008ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050480008ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050480008ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_INT_W1S(a,b) bdk_ccux_tadx_int_w1s_t
#define bustype_BDK_CCUX_TADX_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_INT_W1S(a,b) "CCUX_TADX_INT_W1S"
#define device_bar_BDK_CCUX_TADX_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_INT_W1S(a,b) (a)
#define arguments_BDK_CCUX_TADX_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_mpar#_acnt
 *
 * CCU Memory Paritioning Allocate Count Registers
 */
union bdk_ccux_tadx_mparx_acnt
{
    uint64_t u;
    struct bdk_ccux_tadx_mparx_acnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Counter incremented whenever a request allocates while using the corresponding
                                                                 MPARID. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Counter incremented whenever a request allocates while using the corresponding
                                                                 MPARID. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_mparx_acnt_s cn; */
};
typedef union bdk_ccux_tadx_mparx_acnt bdk_ccux_tadx_mparx_acnt_t;

static inline uint64_t BDK_CCUX_TADX_MPARX_ACNT(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_MPARX_ACNT(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1) && (c<=255)))
        return 0x87e050401000ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1) && (c<=255)))
        return 0x87e050401000ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1) && (c<=255)))
        return 0x87e050401000ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1) && (c<=255)))
        return 0x87e050401000ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0xff);
    __bdk_csr_fatal("CCUX_TADX_MPARX_ACNT", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_MPARX_ACNT(a,b,c) bdk_ccux_tadx_mparx_acnt_t
#define bustype_BDK_CCUX_TADX_MPARX_ACNT(a,b,c) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_MPARX_ACNT(a,b,c) "CCUX_TADX_MPARX_ACNT"
#define device_bar_BDK_CCUX_TADX_MPARX_ACNT(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_MPARX_ACNT(a,b,c) (a)
#define arguments_BDK_CCUX_TADX_MPARX_ACNT(a,b,c) (a),(b),(c),-1

/**
 * Register (RSL) ccu#_tad#_mpar#_hcnt
 *
 * CCU Memory Paritioning Hit Count Registers
 */
union bdk_ccux_tadx_mparx_hcnt
{
    uint64_t u;
    struct bdk_ccux_tadx_mparx_hcnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Counter incremented whenever a request hits in the LTG or DTG while using the
                                                                 corresponding MPARID. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 48; /**< [ 47:  0](R/W/H) Counter incremented whenever a request hits in the LTG or DTG while using the
                                                                 corresponding MPARID. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_mparx_hcnt_s cn; */
};
typedef union bdk_ccux_tadx_mparx_hcnt bdk_ccux_tadx_mparx_hcnt_t;

static inline uint64_t BDK_CCUX_TADX_MPARX_HCNT(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_MPARX_HCNT(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1) && (c<=255)))
        return 0x87e050401008ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1) && (c<=255)))
        return 0x87e050401008ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1) && (c<=255)))
        return 0x87e050401008ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0xff);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1) && (c<=255)))
        return 0x87e050401008ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0xff);
    __bdk_csr_fatal("CCUX_TADX_MPARX_HCNT", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_MPARX_HCNT(a,b,c) bdk_ccux_tadx_mparx_hcnt_t
#define bustype_BDK_CCUX_TADX_MPARX_HCNT(a,b,c) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_MPARX_HCNT(a,b,c) "CCUX_TADX_MPARX_HCNT"
#define device_bar_BDK_CCUX_TADX_MPARX_HCNT(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_MPARX_HCNT(a,b,c) (a)
#define arguments_BDK_CCUX_TADX_MPARX_HCNT(a,b,c) (a),(b),(c),-1

/**
 * Register (RSL) ccu#_tad#_nxm_err
 *
 * CCU TAD ASC Error Info Registers
 * This register records error information for RDNXM and WRNXM interrupts. The NXM
 * logic only applies to local addresses. A command for a remote address does not cause
 * a [RDNXM]/[WRNXM] on the requesting node, but may on the remote node. The first
 * [WRNXM] error will lock the register until the logged error type is cleared; [RDNXM]
 * errors lock the register until either the logged error type is cleared or a [WRNXM]
 * error is logged.
 */
union bdk_ccux_tadx_nxm_err
{
    uint64_t u;
    struct bdk_ccux_tadx_nxm_err_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t rdnxm                 : 1;  /**< [ 63: 63](RO/H) Logged information is for a CCU()_TAD()_INT_W1C[RDNXM] error. */
        uint64_t wrnxm                 : 1;  /**< [ 62: 62](RO/H) Logged information is for a CCU()_TAD()_INT_W1C[WRNXM] error. */
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request causing error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_DS, CCS_CMD_E::CMD_IS, and
                                                                 CCS_CMD_E::CMD_AT should ever be logged. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request causing error.
                                                                 Internal:
                                                                 If [CMD]=CCS_CMD_E::CMD_DS, enumerated by CCS_DS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_IS, enumerated by CCS_IS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_AT, enumerated by CCS_AT_SCMD_E. */
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) If [MS] indicates the source is a cluster, [SID] is the sid of the core within
                                                                 the cluster which issued the request causing the error. If [MS] indicated the
                                                                 source is not a cluster, [SID] is unpredictable. */
        uint64_t ms                    : 6;  /**< [ 51: 46](RO/H) Mesh source of the request causing the error.
                                                                 Internal:
                                                                 Enumerated by CCS_RID_E. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request causing error. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t addr                  : 43; /**< [ 42:  0](RO/H) Address of the request causing the error. [ADDR]\<6:0\> is unpredictable. This
                                                                 field is the physical address after TAD set aliasing (if enabled, see
                                                                 CCS_ADR_CTL[DISSETALIAS]). */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 43; /**< [ 42:  0](RO/H) Address of the request causing the error. [ADDR]\<6:0\> is unpredictable. This
                                                                 field is the physical address after TAD set aliasing (if enabled, see
                                                                 CCS_ADR_CTL[DISSETALIAS]). */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request causing error. */
        uint64_t ms                    : 6;  /**< [ 51: 46](RO/H) Mesh source of the request causing the error.
                                                                 Internal:
                                                                 Enumerated by CCS_RID_E. */
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) If [MS] indicates the source is a cluster, [SID] is the sid of the core within
                                                                 the cluster which issued the request causing the error. If [MS] indicated the
                                                                 source is not a cluster, [SID] is unpredictable. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request causing error.
                                                                 Internal:
                                                                 If [CMD]=CCS_CMD_E::CMD_DS, enumerated by CCS_DS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_IS, enumerated by CCS_IS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_AT, enumerated by CCS_AT_SCMD_E. */
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request causing error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_DS, CCS_CMD_E::CMD_IS, and
                                                                 CCS_CMD_E::CMD_AT should ever be logged. */
        uint64_t wrnxm                 : 1;  /**< [ 62: 62](RO/H) Logged information is for a CCU()_TAD()_INT_W1C[WRNXM] error. */
        uint64_t rdnxm                 : 1;  /**< [ 63: 63](RO/H) Logged information is for a CCU()_TAD()_INT_W1C[RDNXM] error. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_nxm_err_s cn; */
};
typedef union bdk_ccux_tadx_nxm_err bdk_ccux_tadx_nxm_err_t;

static inline uint64_t BDK_CCUX_TADX_NXM_ERR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_NXM_ERR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400010ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400010ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400010ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400010ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_NXM_ERR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_NXM_ERR(a,b) bdk_ccux_tadx_nxm_err_t
#define bustype_BDK_CCUX_TADX_NXM_ERR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_NXM_ERR(a,b) "CCUX_TADX_NXM_ERR"
#define device_bar_BDK_CCUX_TADX_NXM_ERR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_NXM_ERR(a,b) (a)
#define arguments_BDK_CCUX_TADX_NXM_ERR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_pfc#
 *
 * CCU TAD Performance Counter Registers
 */
union bdk_ccux_tadx_pfcx
{
    uint64_t u;
    struct bdk_ccux_tadx_pfcx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Current counter value. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Current counter value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_pfcx_s cn; */
};
typedef union bdk_ccux_tadx_pfcx bdk_ccux_tadx_pfcx_t;

static inline uint64_t BDK_CCUX_TADX_PFCX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_PFCX(unsigned long a, unsigned long b, unsigned long c)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1) && (c<=3)))
        return 0x87e050420040ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1) && (c<=3)))
        return 0x87e050420040ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1) && (c<=3)))
        return 0x87e050420040ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0x3);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1) && (c<=3)))
        return 0x87e050420040ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1) + 0x10ll * ((c) & 0x3);
    __bdk_csr_fatal("CCUX_TADX_PFCX", 3, a, b, c, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_PFCX(a,b,c) bdk_ccux_tadx_pfcx_t
#define bustype_BDK_CCUX_TADX_PFCX(a,b,c) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_PFCX(a,b,c) "CCUX_TADX_PFCX"
#define device_bar_BDK_CCUX_TADX_PFCX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_PFCX(a,b,c) (a)
#define arguments_BDK_CCUX_TADX_PFCX(a,b,c) (a),(b),(c),-1

/**
 * Register (RSL) ccu#_tad#_prf
 *
 * CCU TAD Performance Counter Control Registers
 * All four counters are equivalent and can use any of the defined selects.
 */
union bdk_ccux_tadx_prf
{
    uint64_t u;
    struct bdk_ccux_tadx_prf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cnt3sel               : 8;  /**< [ 31: 24](R/W) Selects event to count for CCU()_TAD()_PFC(3). Enumerated by CCU_TAD_PRF_SEL_E. */
        uint64_t cnt2sel               : 8;  /**< [ 23: 16](R/W) Selects event to count for CCU()_TAD()_PFC(2). Enumerated by CCU_TAD_PRF_SEL_E. */
        uint64_t cnt1sel               : 8;  /**< [ 15:  8](R/W) Selects event to count for CCU()_TAD()_PFC(1). Enumerated by CCU_TAD_PRF_SEL_E. */
        uint64_t cnt0sel               : 8;  /**< [  7:  0](R/W) Selects event to count for CCU()_TAD()_PFC(0). Enumerated by CCU_TAD_PRF_SEL_E. */
#else /* Word 0 - Little Endian */
        uint64_t cnt0sel               : 8;  /**< [  7:  0](R/W) Selects event to count for CCU()_TAD()_PFC(0). Enumerated by CCU_TAD_PRF_SEL_E. */
        uint64_t cnt1sel               : 8;  /**< [ 15:  8](R/W) Selects event to count for CCU()_TAD()_PFC(1). Enumerated by CCU_TAD_PRF_SEL_E. */
        uint64_t cnt2sel               : 8;  /**< [ 23: 16](R/W) Selects event to count for CCU()_TAD()_PFC(2). Enumerated by CCU_TAD_PRF_SEL_E. */
        uint64_t cnt3sel               : 8;  /**< [ 31: 24](R/W) Selects event to count for CCU()_TAD()_PFC(3). Enumerated by CCU_TAD_PRF_SEL_E. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_prf_s cn; */
};
typedef union bdk_ccux_tadx_prf bdk_ccux_tadx_prf_t;

static inline uint64_t BDK_CCUX_TADX_PRF(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_PRF(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050420000ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050420000ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050420000ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050420000ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_PRF", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_PRF(a,b) bdk_ccux_tadx_prf_t
#define bustype_BDK_CCUX_TADX_PRF(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_PRF(a,b) "CCUX_TADX_PRF"
#define device_bar_BDK_CCUX_TADX_PRF(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_PRF(a,b) (a)
#define arguments_BDK_CCUX_TADX_PRF(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_sbe_dbg_cnt
 *
 * INTERNAL: CCU TAD SBE Detection Counter Registers
 *
 * This register keeps track of the number of single-bit errors arriving on the DAT
 * mesh into the TAD from MSW in saturating counters. For debug purposes only - no
 * correction.
 */
union bdk_ccux_tadx_sbe_dbg_cnt
{
    uint64_t u;
    struct bdk_ccux_tadx_sbe_dbg_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ow3                   : 16; /**< [ 63: 48](R/W/H) Current single-bit error counter value for OW3. */
        uint64_t ow2                   : 16; /**< [ 47: 32](R/W/H) Current single-bit error counter value for OW2. */
        uint64_t ow1                   : 16; /**< [ 31: 16](R/W/H) Current single-bit error counter value for OW1. */
        uint64_t ow0                   : 16; /**< [ 15:  0](R/W/H) Current single-bit error counter value for OW0. */
#else /* Word 0 - Little Endian */
        uint64_t ow0                   : 16; /**< [ 15:  0](R/W/H) Current single-bit error counter value for OW0. */
        uint64_t ow1                   : 16; /**< [ 31: 16](R/W/H) Current single-bit error counter value for OW1. */
        uint64_t ow2                   : 16; /**< [ 47: 32](R/W/H) Current single-bit error counter value for OW2. */
        uint64_t ow3                   : 16; /**< [ 63: 48](R/W/H) Current single-bit error counter value for OW3. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_sbe_dbg_cnt_s cn; */
};
typedef union bdk_ccux_tadx_sbe_dbg_cnt bdk_ccux_tadx_sbe_dbg_cnt_t;

static inline uint64_t BDK_CCUX_TADX_SBE_DBG_CNT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_SBE_DBG_CNT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400040ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400040ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400040ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400040ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_SBE_DBG_CNT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_SBE_DBG_CNT(a,b) bdk_ccux_tadx_sbe_dbg_cnt_t
#define bustype_BDK_CCUX_TADX_SBE_DBG_CNT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_SBE_DBG_CNT(a,b) "CCUX_TADX_SBE_DBG_CNT"
#define device_bar_BDK_CCUX_TADX_SBE_DBG_CNT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_SBE_DBG_CNT(a,b) (a)
#define arguments_BDK_CCUX_TADX_SBE_DBG_CNT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_scratch
 *
 * INTERNAL: CCU TAD General Purpose Scratch Register
 *
 * These registers are reset only by hardware during chip cold reset. The values of the CSR
 * fields in these registers do not change during chip warm or soft resets.
 */
union bdk_ccux_tadx_scratch
{
    uint64_t u;
    struct bdk_ccux_tadx_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_scratch_s cn; */
};
typedef union bdk_ccux_tadx_scratch bdk_ccux_tadx_scratch_t;

static inline uint64_t BDK_CCUX_TADX_SCRATCH(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_SCRATCH(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400000ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400000ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400000ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400000ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_SCRATCH", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_SCRATCH(a,b) bdk_ccux_tadx_scratch_t
#define bustype_BDK_CCUX_TADX_SCRATCH(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_SCRATCH(a,b) "CCUX_TADX_SCRATCH"
#define device_bar_BDK_CCUX_TADX_SCRATCH(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_SCRATCH(a,b) (a)
#define arguments_BDK_CCUX_TADX_SCRATCH(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_tag
 *
 * CCU TAD TAG Data Register
 * This register records the tag information read by a LTGI command.
 */
union bdk_ccux_tadx_tag
{
    uint64_t u;
    struct bdk_ccux_tadx_tag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t is                    : 1;  /**< [ 63: 63](RO/H) The i-stream bit. */
        uint64_t sblkdty               : 4;  /**< [ 62: 59](RO/H) The sub-block dirty bits. */
        uint64_t ci                    : 10; /**< [ 58: 49](RO/H) The cluster info. */
        uint64_t ts                    : 3;  /**< [ 48: 46](RO/H) The tag state. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) The node bits. */
        uint64_t tag                   : 25; /**< [ 42: 18](RO/H) The tag bits. */
        uint64_t reserved_0_17         : 18;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_17         : 18;
        uint64_t tag                   : 25; /**< [ 42: 18](RO/H) The tag bits. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) The node bits. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit. */
        uint64_t ts                    : 3;  /**< [ 48: 46](RO/H) The tag state. */
        uint64_t ci                    : 10; /**< [ 58: 49](RO/H) The cluster info. */
        uint64_t sblkdty               : 4;  /**< [ 62: 59](RO/H) The sub-block dirty bits. */
        uint64_t is                    : 1;  /**< [ 63: 63](RO/H) The i-stream bit. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_tag_s cn; */
};
typedef union bdk_ccux_tadx_tag bdk_ccux_tadx_tag_t;

static inline uint64_t BDK_CCUX_TADX_TAG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_TAG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400028ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400028ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400028ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400028ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_TAG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_TAG(a,b) bdk_ccux_tadx_tag_t
#define bustype_BDK_CCUX_TADX_TAG(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_TAG(a,b) "CCUX_TADX_TAG"
#define device_bar_BDK_CCUX_TADX_TAG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_TAG(a,b) (a)
#define arguments_BDK_CCUX_TADX_TAG(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_wbar
 *
 * CCU TAD Write Barrier Register
 * This register allows the initiation of a WBAR/WRFL sequence and provides status of
 * its completion. If a new sequence is requested before the first is completed INPROG
 * will remain asserted until all memory writes preceding the last CSR write to [START]
 * have been followed by a WBAR/WRFL sequence.
 */
union bdk_ccux_tadx_wbar
{
    uint64_t u;
    struct bdk_ccux_tadx_wbar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t inprog                : 1;  /**< [ 63: 63](RO/H) In progress. Set after [START] is written to one, and will clear when the
                                                                 requested WBAR/WRFL sequence has completed. */
        uint64_t reserved_4_62         : 59;
        uint64_t lmcmsk                : 3;  /**< [  3:  1](R/W) Mask of which LMCs to send WBAR/WRFL sequences to. A value of 0x0 will send to all. */
        uint64_t start                 : 1;  /**< [  0:  0](R/W1/H) Start. Writing a one requests a WBAR/WRFL sequence with the persist bit
                                                                 set. [START] will clear once the sequence has been logged as a request. [INPROG]
                                                                 will remain one until all requested sequences are complete. Writing a zero to
                                                                 this bit has no effect. */
#else /* Word 0 - Little Endian */
        uint64_t start                 : 1;  /**< [  0:  0](R/W1/H) Start. Writing a one requests a WBAR/WRFL sequence with the persist bit
                                                                 set. [START] will clear once the sequence has been logged as a request. [INPROG]
                                                                 will remain one until all requested sequences are complete. Writing a zero to
                                                                 this bit has no effect. */
        uint64_t lmcmsk                : 3;  /**< [  3:  1](R/W) Mask of which LMCs to send WBAR/WRFL sequences to. A value of 0x0 will send to all. */
        uint64_t reserved_4_62         : 59;
        uint64_t inprog                : 1;  /**< [ 63: 63](RO/H) In progress. Set after [START] is written to one, and will clear when the
                                                                 requested WBAR/WRFL sequence has completed. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_wbar_s cn; */
};
typedef union bdk_ccux_tadx_wbar bdk_ccux_tadx_wbar_t;

static inline uint64_t BDK_CCUX_TADX_WBAR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_WBAR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400030ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400030ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400030ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400030ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_WBAR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_WBAR(a,b) bdk_ccux_tadx_wbar_t
#define bustype_BDK_CCUX_TADX_WBAR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_WBAR(a,b) "CCUX_TADX_WBAR"
#define device_bar_BDK_CCUX_TADX_WBAR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_WBAR(a,b) (a)
#define arguments_BDK_CCUX_TADX_WBAR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) ccu#_tad#_xbf_err
 *
 * CCU TAD XBF Error Info Registers
 * This register records error information for XBF MDC DBE/SBE interrupts which map to
 * the MDC node in the TAD DAT XBF. The first [DBE] error will lock the register until the
 * logged error type is cleared; [SBE] errors lock the register until either the logged
 * error type is cleared or a [DBE] error is logged. Only one of [SBE], [DBE] should be
 * set at a time. In the event the register is read with both [SBE] and [SBE] equal to
 * 0 during interrupt handling that is an indication that, due to a register set/clear
 * race, information about one or more errors was lost while processing an earlier
 * error. Note that no scrubbing is required for XBF errors.
 */
union bdk_ccux_tadx_xbf_err
{
    uint64_t u;
    struct bdk_ccux_tadx_xbf_err_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sbe                   : 1;  /**< [ 63: 63](R/W1C/H) If [SBE]=1, then the logged information is for a MDC SBE error. */
        uint64_t dbe                   : 1;  /**< [ 62: 62](R/W1C/H) If [DBE]=1, then the logged information is for a MDC DBE error. */
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_DS, CCS_CMD_E::CMD_IS, and
                                                                 CCS_CMD_E::CMD_AT shoule ever be logged. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request which detected the error.
                                                                 Internal:
                                                                 If [CMD]=CCS_CMD_E::CMD_DS, enumerated by CCS_DS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_IS, enumerated by CCS_IS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_AT, enumerated by CCS_AT_SCMD_E. */
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) If [MS] indicates the source is a cluster, [SID] is the sid of the core within
                                                                 the cluster which issued the request causing the error. If [MS] indicated the
                                                                 source is not a cluster, [SID] is unpredictable. */
        uint64_t ms                    : 6;  /**< [ 51: 46](RO/H) Mesh source of the request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_RID_E. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request which detected the error. */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t addr                  : 36; /**< [ 42:  7](RO/H) Block address of the request which detected the error. This field is the
                                                                 physical address after TAD set aliasing (if enabled, see
                                                                 CCS_ADR_CTL[DISSETALIAS]). */
        uint64_t ow                    : 3;  /**< [  6:  4](RO/H) 128-bit word in which the error was detected. */
        uint64_t reserved_1_3          : 3;
        uint64_t fbf                   : 1;  /**< [  0:  0](RO/H) If =1 error was found by the FBF ECC checker, if =0 found by the SBF ECC
                                                                 checker. */
#else /* Word 0 - Little Endian */
        uint64_t fbf                   : 1;  /**< [  0:  0](RO/H) If =1 error was found by the FBF ECC checker, if =0 found by the SBF ECC
                                                                 checker. */
        uint64_t reserved_1_3          : 3;
        uint64_t ow                    : 3;  /**< [  6:  4](RO/H) 128-bit word in which the error was detected. */
        uint64_t addr                  : 36; /**< [ 42:  7](RO/H) Block address of the request which detected the error. This field is the
                                                                 physical address after TAD set aliasing (if enabled, see
                                                                 CCS_ADR_CTL[DISSETALIAS]). */
        uint64_t node                  : 2;  /**< [ 44: 43](RO/H) Reserved. */
        uint64_t nonsec                : 1;  /**< [ 45: 45](RO/H) Nonsecure (NS) bit of request which detected the error. */
        uint64_t ms                    : 6;  /**< [ 51: 46](RO/H) Mesh source of the request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_RID_E. */
        uint64_t sid                   : 3;  /**< [ 54: 52](RO/H) If [MS] indicates the source is a cluster, [SID] is the sid of the core within
                                                                 the cluster which issued the request causing the error. If [MS] indicated the
                                                                 source is not a cluster, [SID] is unpredictable. */
        uint64_t scmd                  : 4;  /**< [ 58: 55](RO/H) Sub-command of request which detected the error.
                                                                 Internal:
                                                                 If [CMD]=CCS_CMD_E::CMD_DS, enumerated by CCS_DS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_IS, enumerated by CCS_IS_SCMD_E. If
                                                                 [CMD]=CCS_CMD_E::CMD_AT, enumerated by CCS_AT_SCMD_E. */
        uint64_t cmd                   : 3;  /**< [ 61: 59](RO/H) Major command of request which detected the error.
                                                                 Internal:
                                                                 Enumerated by CCS_CMD_E. Only CCS_CMD_E::CMD_DS, CCS_CMD_E::CMD_IS, and
                                                                 CCS_CMD_E::CMD_AT shoule ever be logged. */
        uint64_t dbe                   : 1;  /**< [ 62: 62](R/W1C/H) If [DBE]=1, then the logged information is for a MDC DBE error. */
        uint64_t sbe                   : 1;  /**< [ 63: 63](R/W1C/H) If [SBE]=1, then the logged information is for a MDC SBE error. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccux_tadx_xbf_err_s cn; */
};
typedef union bdk_ccux_tadx_xbf_err bdk_ccux_tadx_xbf_err_t;

static inline uint64_t BDK_CCUX_TADX_XBF_ERR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCUX_TADX_XBF_ERR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=3) && (b<=1)))
        return 0x87e050400020ll + 0x1000000ll * ((a) & 0x3) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=5) && (b<=1)))
        return 0x87e050400020ll + 0x1000000ll * ((a) & 0x7) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e050400020ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e050400020ll + 0x1000000ll * ((a) & 0x0) + 0x200000ll * ((b) & 0x1);
    __bdk_csr_fatal("CCUX_TADX_XBF_ERR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_CCUX_TADX_XBF_ERR(a,b) bdk_ccux_tadx_xbf_err_t
#define bustype_BDK_CCUX_TADX_XBF_ERR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_CCUX_TADX_XBF_ERR(a,b) "CCUX_TADX_XBF_ERR"
#define device_bar_BDK_CCUX_TADX_XBF_ERR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCUX_TADX_XBF_ERR(a,b) (a)
#define arguments_BDK_CCUX_TADX_XBF_ERR(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_CCU_H__ */
