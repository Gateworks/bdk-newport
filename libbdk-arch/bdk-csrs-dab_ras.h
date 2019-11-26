#ifndef __BDK_CSRS_DAB_RAS_H__
#define __BDK_CSRS_DAB_RAS_H__
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
 * OcteonTX DAB_RAS.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration ras_serr_e
 *
 * RAS Error Record Type Enumeration
 * Enumerates the error record types in RAS_ERRnSTATUS[SERR].
 */
#define BDK_RAS_SERR_E_ASSERTION (4)
#define BDK_RAS_SERR_E_CAM_DATA (6)
#define BDK_RAS_SERR_E_CAM_TAG (7)
#define BDK_RAS_SERR_E_DATAPATH (5)
#define BDK_RAS_SERR_E_DEF_MAS (0x15)
#define BDK_RAS_SERR_E_EXT_DATA (0xc)
#define BDK_RAS_SERR_E_EXT_TO (0x13)
#define BDK_RAS_SERR_E_IMPDEF1 (1)
#define BDK_RAS_SERR_E_INT_TO (0x14)
#define BDK_RAS_SERR_E_NONE (0)
#define BDK_RAS_SERR_E_PIN (3)
#define BDK_RAS_SERR_E_PRODUCER_ADDRCTL (0xb)
#define BDK_RAS_SERR_E_PRODUCER_DATA (0xa)
#define BDK_RAS_SERR_E_REG_CTL (0x11)
#define BDK_RAS_SERR_E_REG_DATA (0x10)
#define BDK_RAS_SERR_E_SLAVE (0x12)
#define BDK_RAS_SERR_E_SRAM_DATA (2)
#define BDK_RAS_SERR_E_SW_BAD_ACCESS (0xe)
#define BDK_RAS_SERR_E_SW_BAD_ADDR (0xd)
#define BDK_RAS_SERR_E_SW_BAD_STATE (0xf)
#define BDK_RAS_SERR_E_TLB_ADDRCTL (9)
#define BDK_RAS_SERR_E_TLB_DATA (8)

/**
 * Enumeration ras_uet_e
 *
 * RAS Uncorrected Error Type Enumeration
 * Enumerates the uncorrected error types in RAS()_ERR00STATUS[UET].
 */
#define BDK_RAS_UET_E_UC (0)
#define BDK_RAS_UET_E_UEO (2)
#define BDK_RAS_UET_E_UER (3)
#define BDK_RAS_UET_E_UEU (1)

/**
 * Register (DAB32b) ras#_cidr0
 *
 * RAS Component Identification Register 0
 * This register provides information to identify a debug component.
 */
union bdk_rasx_cidr0
{
    uint32_t u;
    struct bdk_rasx_cidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_cidr0_s cn; */
};
typedef union bdk_rasx_cidr0 bdk_rasx_cidr0_t;

static inline uint64_t BDK_RASX_CIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_CIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050ff0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050ff0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050ff0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050ff0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_CIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_CIDR0(a) bdk_rasx_cidr0_t
#define bustype_BDK_RASX_CIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_CIDR0(a) "RASX_CIDR0"
#define busnum_BDK_RASX_CIDR0(a) (a)
#define arguments_BDK_RASX_CIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_cidr1
 *
 * RAS Component Identification Register 1
 * This register provides information to identify a debug component.
 */
union bdk_rasx_cidr1
{
    uint32_t u;
    struct bdk_rasx_cidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0xF = General component. */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble identification value. */
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0xF = General component. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_cidr1_s cn; */
};
typedef union bdk_rasx_cidr1 bdk_rasx_cidr1_t;

static inline uint64_t BDK_RASX_CIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_CIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050ff4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050ff4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050ff4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050ff4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_CIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_CIDR1(a) bdk_rasx_cidr1_t
#define bustype_BDK_RASX_CIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_CIDR1(a) "RASX_CIDR1"
#define busnum_BDK_RASX_CIDR1(a) (a)
#define arguments_BDK_RASX_CIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_cidr2
 *
 * RAS Component Identification Register 2
 * This register provides information to identify a debug component.
 */
union bdk_rasx_cidr2
{
    uint32_t u;
    struct bdk_rasx_cidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_cidr2_s cn; */
};
typedef union bdk_rasx_cidr2 bdk_rasx_cidr2_t;

static inline uint64_t BDK_RASX_CIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_CIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050ff8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050ff8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050ff8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050ff8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_CIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_CIDR2(a) bdk_rasx_cidr2_t
#define bustype_BDK_RASX_CIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_CIDR2(a) "RASX_CIDR2"
#define busnum_BDK_RASX_CIDR2(a) (a)
#define arguments_BDK_RASX_CIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_cidr3
 *
 * RAS Component Identification Register 3
 * This register provides information to identify a debug component.
 */
union bdk_rasx_cidr3
{
    uint32_t u;
    struct bdk_rasx_cidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_cidr3_s cn; */
};
typedef union bdk_rasx_cidr3 bdk_rasx_cidr3_t;

static inline uint64_t BDK_RASX_CIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_CIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050ffcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050ffcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050ffcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050ffcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_CIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_CIDR3(a) bdk_rasx_cidr3_t
#define bustype_BDK_RASX_CIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_CIDR3(a) "RASX_CIDR3"
#define busnum_BDK_RASX_CIDR3(a) (a)
#define arguments_BDK_RASX_CIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err00addr
 *
 * RAS Error Record 00 Address Register
 * This per-record register contains the error address for those error records which
 * set RAS()_ERR00STATUS[AV].
 *
 * See the individual per-record CSRs for the record-specific meaning of each field,
 * e.g. RAS()_ERR09ADDR.
 */
union bdk_rasx_err00addr
{
    uint64_t u;
    struct bdk_rasx_err00addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err00addr_s cn; */
};
typedef union bdk_rasx_err00addr bdk_rasx_err00addr_t;

static inline uint64_t BDK_RASX_ERR00ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR00ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050018ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050018ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050018ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050018ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR00ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR00ADDR(a) bdk_rasx_err00addr_t
#define bustype_BDK_RASX_ERR00ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR00ADDR(a) "RASX_ERR00ADDR"
#define busnum_BDK_RASX_ERR00ADDR(a) (a)
#define arguments_BDK_RASX_ERR00ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err00ctlr
 *
 * RAS Error Record 00 Control Register
 * This per-record register contains enables bits for the node that writes to this record.
 * See the individual per-record CSRs for the record-specific values of each field.
 *
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err00ctlr
{
    uint64_t u;
    struct bdk_rasx_err00ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) Error recovery for deferred read error interrupt enable. When enabled the error
                                                                 recovery interrupt is also generated for all deferred read errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) Fault handling interrupt for corrected errors enable.
                                                                 When enabled:

                                                                 * If the node implements a corrected error counter, the fault handling interrupt
                                                                 is only generated when the counter overflows and the overflow bit is set.

                                                                 * Otherwise the fault handling interrupt is also generated for all detected
                                                                 corrected errors.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) Uncorrected error reporting enable. When enabled, responses to
                                                                 transactions that detect an uncorrected error that cannot be deferred are
                                                                 signaled as a detected error (external abort).

                                                                 0 = External abort response for uncorrected errors disabled.
                                                                 1 = External abort response for uncorrected errors enabled.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) Fault handling interrupt enable. When enabled the fault handling interrupt
                                                                 is generated for all detected deferred errors and uncorrected errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. The fault handling
                                                                 interrupt is never generated for consumed errors. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) Uncorrected error recovery interrupt enable. When enabled, the error
                                                                 recovery interrupt is generated for all detected uncorrected errors that are not
                                                                 deferred.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) Implementation defined.

                                                                 For CNXXXX force error.
                                                                 * For records where RAS()_ERRn[IMP_FE] = 0x2, this bit is R/W and when set
                                                                 injects an error.
                                                                 * For other records, reserved. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) Enable error detection and correction at the node.
                                                                 0 = Error detection and correction disabled.
                                                                 1 = Error detection and correction enabled.

                                                                 For CNXXXX, all records similar. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) Enable error detection and correction at the node.
                                                                 0 = Error detection and correction disabled.
                                                                 1 = Error detection and correction enabled.

                                                                 For CNXXXX, all records similar. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) Implementation defined.

                                                                 For CNXXXX force error.
                                                                 * For records where RAS()_ERRn[IMP_FE] = 0x2, this bit is R/W and when set
                                                                 injects an error.
                                                                 * For other records, reserved. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) Uncorrected error recovery interrupt enable. When enabled, the error
                                                                 recovery interrupt is generated for all detected uncorrected errors that are not
                                                                 deferred.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) Fault handling interrupt enable. When enabled the fault handling interrupt
                                                                 is generated for all detected deferred errors and uncorrected errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. The fault handling
                                                                 interrupt is never generated for consumed errors. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) Uncorrected error reporting enable. When enabled, responses to
                                                                 transactions that detect an uncorrected error that cannot be deferred are
                                                                 signaled as a detected error (external abort).

                                                                 0 = External abort response for uncorrected errors disabled.
                                                                 1 = External abort response for uncorrected errors enabled.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) Fault handling interrupt for corrected errors enable.
                                                                 When enabled:

                                                                 * If the node implements a corrected error counter, the fault handling interrupt
                                                                 is only generated when the counter overflows and the overflow bit is set.

                                                                 * Otherwise the fault handling interrupt is also generated for all detected
                                                                 corrected errors.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) Error recovery for deferred read error interrupt enable. When enabled the error
                                                                 recovery interrupt is also generated for all deferred read errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err00ctlr_s cn9; */
    /* struct bdk_rasx_err00ctlr_s cn96xxp1; */
    struct bdk_rasx_err00ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) Error recovery for deferred read error interrupt enable. When enabled the error
                                                                 recovery interrupt is also generated for all deferred read errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) Fault handling interrupt for corrected errors enable.
                                                                 When enabled:

                                                                 * If the node implements a corrected error counter, the fault handling interrupt
                                                                 is only generated when the counter overflows and the overflow bit is set.

                                                                 * Otherwise the fault handling interrupt is also generated for all detected
                                                                 corrected errors.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) Uncorrected error reporting enable. When enabled, responses to
                                                                 transactions that detect an uncorrected error that cannot be deferred are
                                                                 signaled as a detected error (external abort).

                                                                 0 = External abort response for uncorrected errors disabled.
                                                                 1 = External abort response for uncorrected errors enabled.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) Fault handling interrupt enable. When enabled the fault handling interrupt
                                                                 is generated for all detected deferred errors and uncorrected errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. The fault handling
                                                                 interrupt is never generated for consumed errors. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) Uncorrected error recovery interrupt enable. When enabled, the error
                                                                 recovery interrupt is generated for all detected uncorrected errors that are not
                                                                 deferred.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) Implementation defined.

                                                                 For CNXXXX force error.
                                                                 * For records where RAS()_ERRn[IMP_FE] = 0x2, this bit is R/W and when set
                                                                 injects an error.
                                                                 * For other records, reserved. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) Enable error detection and correction at the node.
                                                                 0 = Error detection and correction disabled.
                                                                 1 = Error detection and correction enabled.

                                                                 For CNXXXX, all records similar. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) Enable error detection and correction at the node.
                                                                 0 = Error detection and correction disabled.
                                                                 1 = Error detection and correction enabled.

                                                                 For CNXXXX, all records similar. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) Implementation defined.

                                                                 For CNXXXX force error.
                                                                 * For records where RAS()_ERRn[IMP_FE] = 0x2, this bit is R/W and when set
                                                                 injects an error.
                                                                 * For other records, reserved. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) Uncorrected error recovery interrupt enable. When enabled, the error
                                                                 recovery interrupt is generated for all detected uncorrected errors that are not
                                                                 deferred.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) Fault handling interrupt enable. When enabled the fault handling interrupt
                                                                 is generated for all detected deferred errors and uncorrected errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. The fault handling
                                                                 interrupt is never generated for consumed errors. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) Uncorrected error reporting enable. When enabled, responses to
                                                                 transactions that detect an uncorrected error that cannot be deferred are
                                                                 signaled as a detected error (external abort).

                                                                 0 = External abort response for uncorrected errors disabled.
                                                                 1 = External abort response for uncorrected errors enabled.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) Fault handling interrupt for corrected errors enable.
                                                                 When enabled:

                                                                 * If the node implements a corrected error counter, the fault handling interrupt
                                                                 is only generated when the counter overflows and the overflow bit is set.

                                                                 * Otherwise the fault handling interrupt is also generated for all detected
                                                                 corrected errors.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) Error recovery for deferred read error interrupt enable. When enabled the error
                                                                 recovery interrupt is also generated for all deferred read errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err00ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err00ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err00ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err00ctlr bdk_rasx_err00ctlr_t;

static inline uint64_t BDK_RASX_ERR00CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR00CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050008ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050008ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050008ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050008ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR00CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR00CTLR(a) bdk_rasx_err00ctlr_t
#define bustype_BDK_RASX_ERR00CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR00CTLR(a) "RASX_ERR00CTLR"
#define busnum_BDK_RASX_ERR00CTLR(a) (a)
#define arguments_BDK_RASX_ERR00CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err00fr
 *
 * RAS Error Record 00 Feature Register
 * This per-record register defines which of the common architecturally-defined
 * features are implemented. and of the implemented features which are software
 * programmable.
 * See the individual per-record CSRs for the record-specific values of each field.
 */
union bdk_rasx_err00fr
{
    uint64_t u;
    struct bdk_rasx_err00fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. RAS()_ERR\<n\>STATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If RAS()_ERR\<n\>STATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, RAS()_ERR\<n\>STATUS[OF] is set to 1.

                                                                 In CNXXXX, no corrected error counter is implemented in any records, always 0x0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature separately.  See [FI].
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 If [CEC] = 0x0, this bit is 0.

                                                                 For CNXXXX no CEC in any records, always 0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) Indicates a standard correctable error counter mechanism in CDC_ERR()_MISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in CDC_ERR()_MISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in CDC_ERR()_MISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 For CNXXXX no CEC in any records, always 0x0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) Fault handling interrupt for corrected errors. If this feature is implemented,
                                                                 then the fault handling interrupt must be implemented.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) Uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature. See [FI].
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Cavium force error feature is supported.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX depends on the record.
                                                                 * For records where forcing is supported, 0x2.
                                                                 * For other records, 0x0. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 For CNXXXX all records controllable, always 0x2.

                                                                 Internal:
                                                                 Hardcoded. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 For CNXXXX all records controllable, always 0x2.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Cavium force error feature is supported.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX depends on the record.
                                                                 * For records where forcing is supported, 0x2.
                                                                 * For other records, 0x0. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature. See [FI].
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) Uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) Fault handling interrupt for corrected errors. If this feature is implemented,
                                                                 then the fault handling interrupt must be implemented.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) Indicates a standard correctable error counter mechanism in CDC_ERR()_MISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in CDC_ERR()_MISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in CDC_ERR()_MISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 For CNXXXX no CEC in any records, always 0x0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 If [CEC] = 0x0, this bit is 0.

                                                                 For CNXXXX no CEC in any records, always 0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature separately.  See [FI].
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. RAS()_ERR\<n\>STATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If RAS()_ERR\<n\>STATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, RAS()_ERR\<n\>STATUS[OF] is set to 1.

                                                                 In CNXXXX, no corrected error counter is implemented in any records, always 0x0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err00fr_s cn9; */
    /* struct bdk_rasx_err00fr_s cn96xxp1; */
    struct bdk_rasx_err00fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. RAS()_ERR\<n\>STATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If RAS()_ERR\<n\>STATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, RAS()_ERR\<n\>STATUS[OF] is set to 1.

                                                                 In CNXXXX, no corrected error counter is implemented in any records, always 0x0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature separately.  See [FI].
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 If [CEC] = 0x0, this bit is 0.

                                                                 For CNXXXX no CEC in any records, always 0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) Indicates a standard correctable error counter mechanism in CDC_ERR()_MISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in CDC_ERR()_MISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in CDC_ERR()_MISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 For CNXXXX no CEC in any records, always 0x0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) Fault handling interrupt for corrected errors. If this feature is implemented,
                                                                 then the fault handling interrupt must be implemented.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) Uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature. See [FI].
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Marvell force error feature is supported.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX depends on the record.
                                                                 * For records where forcing is supported, 0x2.
                                                                 * For other records, 0x0. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 For CNXXXX all records controllable, always 0x2.

                                                                 Internal:
                                                                 Hardcoded. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 For CNXXXX all records controllable, always 0x2.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Marvell force error feature is supported.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX depends on the record.
                                                                 * For records where forcing is supported, 0x2.
                                                                 * For other records, 0x0. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature. See [FI].
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) Uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) Fault handling interrupt for corrected errors. If this feature is implemented,
                                                                 then the fault handling interrupt must be implemented.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) Indicates a standard correctable error counter mechanism in CDC_ERR()_MISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in CDC_ERR()_MISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in CDC_ERR()_MISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 For CNXXXX no CEC in any records, always 0x0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 If [CEC] = 0x0, this bit is 0.

                                                                 For CNXXXX no CEC in any records, always 0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature separately.  See [FI].
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. RAS()_ERR\<n\>STATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If RAS()_ERR\<n\>STATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, RAS()_ERR\<n\>STATUS[OF] is set to 1.

                                                                 In CNXXXX, no corrected error counter is implemented in any records, always 0x0.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err00fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err00fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err00fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err00fr bdk_rasx_err00fr_t;

static inline uint64_t BDK_RASX_ERR00FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR00FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050000ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050000ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050000ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050000ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR00FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR00FR(a) bdk_rasx_err00fr_t
#define bustype_BDK_RASX_ERR00FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR00FR(a) "RASX_ERR00FR"
#define busnum_BDK_RASX_ERR00FR(a) (a)
#define arguments_BDK_RASX_ERR00FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err00misc0
 *
 * RAS Error Record 00 Miscellaneous 0 Register
 * This register contains other record-specific information not
 * present in the corresponding status and address registers.
 *
 * Bits \<31:0\> are implementation-defined; see the individual per-record CSRs for the
 * record-specific implementation-defined meaning of each field.
 */
union bdk_rasx_err00misc0
{
    uint64_t u;
    struct bdk_rasx_err00misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) Corrected error count.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t reserved_16_31        : 16;
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t reserved_16_31        : 16;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) Corrected error count.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err00misc0_s cn; */
};
typedef union bdk_rasx_err00misc0 bdk_rasx_err00misc0_t;

static inline uint64_t BDK_RASX_ERR00MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR00MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050020ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050020ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050020ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050020ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR00MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR00MISC0(a) bdk_rasx_err00misc0_t
#define bustype_BDK_RASX_ERR00MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR00MISC0(a) "RASX_ERR00MISC0"
#define busnum_BDK_RASX_ERR00MISC0(a) (a)
#define arguments_BDK_RASX_ERR00MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err00misc1
 *
 * RAS Error Record 00 Miscellaneous 1 Register
 * This register contains other record-specific implementation-defined information not
 * present in the corresponding status and address registers.
 *
 * See the individual per-record CSRs for the record-specific implementation-defined
 * meaning of each field.
 */
union bdk_rasx_err00misc1
{
    uint64_t u;
    struct bdk_rasx_err00misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err00misc1_s cn; */
};
typedef union bdk_rasx_err00misc1 bdk_rasx_err00misc1_t;

static inline uint64_t BDK_RASX_ERR00MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR00MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050028ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050028ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050028ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050028ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR00MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR00MISC1(a) bdk_rasx_err00misc1_t
#define bustype_BDK_RASX_ERR00MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR00MISC1(a) "RASX_ERR00MISC1"
#define busnum_BDK_RASX_ERR00MISC1(a) (a)
#define arguments_BDK_RASX_ERR00MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err00status
 *
 * RAS Error Record 00 Primary Syndrome Register
 * This per-record register contains the error record. After reading the status
 * register, software must clear the valid bits to allow new errors to be recorded.
 * See the individual per-record CSRs for the record-specific values of each field.
 */
union bdk_rasx_err00status
{
    uint64_t u;
    struct bdk_rasx_err00status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) Address valid. CER_ERR()_ADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) Status register valid.  CER_ERR()_STATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the CER_ERR()_CTLR{WUE},[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) Miscellaneous registers valid. The CER_ERR()_MISC0 and CER_ERR()_MISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) Miscellaneous registers valid. The CER_ERR()_MISC0 and CER_ERR()_MISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the CER_ERR()_CTLR{WUE},[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) Status register valid.  CER_ERR()_STATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) Address valid. CER_ERR()_ADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err00status_s cn9; */
    /* struct bdk_rasx_err00status_s cn96xxp1; */
    struct bdk_rasx_err00status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) Address valid. CER_ERR()_ADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) Status register valid.  CER_ERR()_STATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the CER_ERR()_CTLR{WUE},[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) Miscellaneous registers valid. The CER_ERR()_MISC0 and CER_ERR()_MISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) Miscellaneous registers valid. The CER_ERR()_MISC0 and CER_ERR()_MISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the CER_ERR()_CTLR{WUE},[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) Status register valid.  CER_ERR()_STATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) Address valid. CER_ERR()_ADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err00status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err00status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err00status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err00status bdk_rasx_err00status_t;

static inline uint64_t BDK_RASX_ERR00STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR00STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050010ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050010ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050010ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050010ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR00STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR00STATUS(a) bdk_rasx_err00status_t
#define bustype_BDK_RASX_ERR00STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR00STATUS(a) "RASX_ERR00STATUS"
#define busnum_BDK_RASX_ERR00STATUS(a) (a)
#define arguments_BDK_RASX_ERR00STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err01addr
 *
 * RAS Error Record 01 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err01addr
{
    uint64_t u;
    struct bdk_rasx_err01addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err01addr_s cn; */
};
typedef union bdk_rasx_err01addr bdk_rasx_err01addr_t;

static inline uint64_t BDK_RASX_ERR01ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR01ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050058ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050058ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050058ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050058ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR01ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR01ADDR(a) bdk_rasx_err01addr_t
#define bustype_BDK_RASX_ERR01ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR01ADDR(a) "RASX_ERR01ADDR"
#define busnum_BDK_RASX_ERR01ADDR(a) (a)
#define arguments_BDK_RASX_ERR01ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err01ctlr
 *
 * RAS Error Record 01 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err01ctlr
{
    uint64_t u;
    struct bdk_rasx_err01ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err01ctlr_s cn9; */
    /* struct bdk_rasx_err01ctlr_s cn96xxp1; */
    struct bdk_rasx_err01ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err01ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err01ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err01ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err01ctlr bdk_rasx_err01ctlr_t;

static inline uint64_t BDK_RASX_ERR01CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR01CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050048ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050048ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050048ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050048ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR01CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR01CTLR(a) bdk_rasx_err01ctlr_t
#define bustype_BDK_RASX_ERR01CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR01CTLR(a) "RASX_ERR01CTLR"
#define busnum_BDK_RASX_ERR01CTLR(a) (a)
#define arguments_BDK_RASX_ERR01CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err01fr
 *
 * RAS Error Record 01 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err01fr
{
    uint64_t u;
    struct bdk_rasx_err01fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err01fr_s cn9; */
    /* struct bdk_rasx_err01fr_s cn96xxp1; */
    struct bdk_rasx_err01fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err01fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err01fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err01fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err01fr bdk_rasx_err01fr_t;

static inline uint64_t BDK_RASX_ERR01FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR01FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050040ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050040ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050040ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050040ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR01FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR01FR(a) bdk_rasx_err01fr_t
#define bustype_BDK_RASX_ERR01FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR01FR(a) "RASX_ERR01FR"
#define busnum_BDK_RASX_ERR01FR(a) (a)
#define arguments_BDK_RASX_ERR01FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err01misc0
 *
 * RAS Error Record 01 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err01misc0
{
    uint64_t u;
    struct bdk_rasx_err01misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_16_31        : 16;
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t reserved_16_31        : 16;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err01misc0_s cn; */
};
typedef union bdk_rasx_err01misc0 bdk_rasx_err01misc0_t;

static inline uint64_t BDK_RASX_ERR01MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR01MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050060ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050060ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050060ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050060ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR01MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR01MISC0(a) bdk_rasx_err01misc0_t
#define bustype_BDK_RASX_ERR01MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR01MISC0(a) "RASX_ERR01MISC0"
#define busnum_BDK_RASX_ERR01MISC0(a) (a)
#define arguments_BDK_RASX_ERR01MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err01misc1
 *
 * RAS Error Record 01 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err01misc1
{
    uint64_t u;
    struct bdk_rasx_err01misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err01misc1_s cn; */
};
typedef union bdk_rasx_err01misc1 bdk_rasx_err01misc1_t;

static inline uint64_t BDK_RASX_ERR01MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR01MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050068ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050068ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050068ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050068ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR01MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR01MISC1(a) bdk_rasx_err01misc1_t
#define bustype_BDK_RASX_ERR01MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR01MISC1(a) "RASX_ERR01MISC1"
#define busnum_BDK_RASX_ERR01MISC1(a) (a)
#define arguments_BDK_RASX_ERR01MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err01status
 *
 * RAS Error Record 01 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err01status
{
    uint64_t u;
    struct bdk_rasx_err01status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err01status_s cn9; */
    /* struct bdk_rasx_err01status_s cn96xxp1; */
    struct bdk_rasx_err01status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err01status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err01status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err01status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err01status bdk_rasx_err01status_t;

static inline uint64_t BDK_RASX_ERR01STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR01STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050050ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050050ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050050ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050050ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR01STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR01STATUS(a) bdk_rasx_err01status_t
#define bustype_BDK_RASX_ERR01STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR01STATUS(a) "RASX_ERR01STATUS"
#define busnum_BDK_RASX_ERR01STATUS(a) (a)
#define arguments_BDK_RASX_ERR01STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err02addr
 *
 * RAS Error Record 02 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err02addr
{
    uint64_t u;
    struct bdk_rasx_err02addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err02addr_s cn; */
};
typedef union bdk_rasx_err02addr bdk_rasx_err02addr_t;

static inline uint64_t BDK_RASX_ERR02ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR02ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050098ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050098ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050098ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050098ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR02ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR02ADDR(a) bdk_rasx_err02addr_t
#define bustype_BDK_RASX_ERR02ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR02ADDR(a) "RASX_ERR02ADDR"
#define busnum_BDK_RASX_ERR02ADDR(a) (a)
#define arguments_BDK_RASX_ERR02ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err02ctlr
 *
 * RAS Error Record 02 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err02ctlr
{
    uint64_t u;
    struct bdk_rasx_err02ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err02ctlr_s cn9; */
    /* struct bdk_rasx_err02ctlr_s cn96xxp1; */
    struct bdk_rasx_err02ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err02ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err02ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err02ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err02ctlr bdk_rasx_err02ctlr_t;

static inline uint64_t BDK_RASX_ERR02CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR02CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050088ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050088ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050088ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050088ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR02CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR02CTLR(a) bdk_rasx_err02ctlr_t
#define bustype_BDK_RASX_ERR02CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR02CTLR(a) "RASX_ERR02CTLR"
#define busnum_BDK_RASX_ERR02CTLR(a) (a)
#define arguments_BDK_RASX_ERR02CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err02fr
 *
 * RAS Error Record 02 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err02fr
{
    uint64_t u;
    struct bdk_rasx_err02fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err02fr_s cn9; */
    /* struct bdk_rasx_err02fr_s cn96xxp1; */
    struct bdk_rasx_err02fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err02fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err02fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err02fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err02fr bdk_rasx_err02fr_t;

static inline uint64_t BDK_RASX_ERR02FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR02FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050080ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050080ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050080ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050080ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR02FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR02FR(a) bdk_rasx_err02fr_t
#define bustype_BDK_RASX_ERR02FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR02FR(a) "RASX_ERR02FR"
#define busnum_BDK_RASX_ERR02FR(a) (a)
#define arguments_BDK_RASX_ERR02FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err02misc0
 *
 * RAS Error Record 02 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err02misc0
{
    uint64_t u;
    struct bdk_rasx_err02misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_16_31        : 16;
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t reserved_16_31        : 16;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err02misc0_s cn; */
};
typedef union bdk_rasx_err02misc0 bdk_rasx_err02misc0_t;

static inline uint64_t BDK_RASX_ERR02MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR02MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080500a0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080500a0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080500a0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080500a0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR02MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR02MISC0(a) bdk_rasx_err02misc0_t
#define bustype_BDK_RASX_ERR02MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR02MISC0(a) "RASX_ERR02MISC0"
#define busnum_BDK_RASX_ERR02MISC0(a) (a)
#define arguments_BDK_RASX_ERR02MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err02misc1
 *
 * RAS Error Record 02 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err02misc1
{
    uint64_t u;
    struct bdk_rasx_err02misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err02misc1_s cn; */
};
typedef union bdk_rasx_err02misc1 bdk_rasx_err02misc1_t;

static inline uint64_t BDK_RASX_ERR02MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR02MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080500a8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080500a8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080500a8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080500a8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR02MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR02MISC1(a) bdk_rasx_err02misc1_t
#define bustype_BDK_RASX_ERR02MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR02MISC1(a) "RASX_ERR02MISC1"
#define busnum_BDK_RASX_ERR02MISC1(a) (a)
#define arguments_BDK_RASX_ERR02MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err02status
 *
 * RAS Error Record 02 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err02status
{
    uint64_t u;
    struct bdk_rasx_err02status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err02status_s cn9; */
    /* struct bdk_rasx_err02status_s cn96xxp1; */
    struct bdk_rasx_err02status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err02status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err02status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err02status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err02status bdk_rasx_err02status_t;

static inline uint64_t BDK_RASX_ERR02STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR02STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050090ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050090ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050090ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050090ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR02STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR02STATUS(a) bdk_rasx_err02status_t
#define bustype_BDK_RASX_ERR02STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR02STATUS(a) "RASX_ERR02STATUS"
#define busnum_BDK_RASX_ERR02STATUS(a) (a)
#define arguments_BDK_RASX_ERR02STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err03addr
 *
 * RAS Error Record 03 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err03addr
{
    uint64_t u;
    struct bdk_rasx_err03addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err03addr_s cn; */
};
typedef union bdk_rasx_err03addr bdk_rasx_err03addr_t;

static inline uint64_t BDK_RASX_ERR03ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR03ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080500d8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080500d8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080500d8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080500d8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR03ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR03ADDR(a) bdk_rasx_err03addr_t
#define bustype_BDK_RASX_ERR03ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR03ADDR(a) "RASX_ERR03ADDR"
#define busnum_BDK_RASX_ERR03ADDR(a) (a)
#define arguments_BDK_RASX_ERR03ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err03ctlr
 *
 * RAS Error Record 03 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err03ctlr
{
    uint64_t u;
    struct bdk_rasx_err03ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err03ctlr_s cn9; */
    /* struct bdk_rasx_err03ctlr_s cn96xxp1; */
    struct bdk_rasx_err03ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err03ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err03ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err03ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err03ctlr bdk_rasx_err03ctlr_t;

static inline uint64_t BDK_RASX_ERR03CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR03CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080500c8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080500c8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080500c8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080500c8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR03CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR03CTLR(a) bdk_rasx_err03ctlr_t
#define bustype_BDK_RASX_ERR03CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR03CTLR(a) "RASX_ERR03CTLR"
#define busnum_BDK_RASX_ERR03CTLR(a) (a)
#define arguments_BDK_RASX_ERR03CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err03fr
 *
 * RAS Error Record 03 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err03fr
{
    uint64_t u;
    struct bdk_rasx_err03fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err03fr_s cn9; */
    /* struct bdk_rasx_err03fr_s cn96xxp1; */
    struct bdk_rasx_err03fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err03fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err03fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err03fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err03fr bdk_rasx_err03fr_t;

static inline uint64_t BDK_RASX_ERR03FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR03FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080500c0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080500c0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080500c0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080500c0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR03FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR03FR(a) bdk_rasx_err03fr_t
#define bustype_BDK_RASX_ERR03FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR03FR(a) "RASX_ERR03FR"
#define busnum_BDK_RASX_ERR03FR(a) (a)
#define arguments_BDK_RASX_ERR03FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err03misc0
 *
 * RAS Error Record 03 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err03misc0
{
    uint64_t u;
    struct bdk_rasx_err03misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_16_31        : 16;
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t reserved_16_31        : 16;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err03misc0_s cn; */
};
typedef union bdk_rasx_err03misc0 bdk_rasx_err03misc0_t;

static inline uint64_t BDK_RASX_ERR03MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR03MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080500e0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080500e0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080500e0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080500e0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR03MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR03MISC0(a) bdk_rasx_err03misc0_t
#define bustype_BDK_RASX_ERR03MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR03MISC0(a) "RASX_ERR03MISC0"
#define busnum_BDK_RASX_ERR03MISC0(a) (a)
#define arguments_BDK_RASX_ERR03MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err03misc1
 *
 * RAS Error Record 03 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err03misc1
{
    uint64_t u;
    struct bdk_rasx_err03misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err03misc1_s cn; */
};
typedef union bdk_rasx_err03misc1 bdk_rasx_err03misc1_t;

static inline uint64_t BDK_RASX_ERR03MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR03MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080500e8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080500e8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080500e8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080500e8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR03MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR03MISC1(a) bdk_rasx_err03misc1_t
#define bustype_BDK_RASX_ERR03MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR03MISC1(a) "RASX_ERR03MISC1"
#define busnum_BDK_RASX_ERR03MISC1(a) (a)
#define arguments_BDK_RASX_ERR03MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err03status
 *
 * RAS Error Record 03 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err03status
{
    uint64_t u;
    struct bdk_rasx_err03status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err03status_s cn9; */
    /* struct bdk_rasx_err03status_s cn96xxp1; */
    struct bdk_rasx_err03status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err03status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err03status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err03status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err03status bdk_rasx_err03status_t;

static inline uint64_t BDK_RASX_ERR03STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR03STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080500d0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080500d0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080500d0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080500d0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR03STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR03STATUS(a) bdk_rasx_err03status_t
#define bustype_BDK_RASX_ERR03STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR03STATUS(a) "RASX_ERR03STATUS"
#define busnum_BDK_RASX_ERR03STATUS(a) (a)
#define arguments_BDK_RASX_ERR03STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err04addr
 *
 * RAS Error Record 04 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err04addr
{
    uint64_t u;
    struct bdk_rasx_err04addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err04addr_s cn; */
};
typedef union bdk_rasx_err04addr bdk_rasx_err04addr_t;

static inline uint64_t BDK_RASX_ERR04ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR04ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050118ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050118ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050118ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050118ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR04ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR04ADDR(a) bdk_rasx_err04addr_t
#define bustype_BDK_RASX_ERR04ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR04ADDR(a) "RASX_ERR04ADDR"
#define busnum_BDK_RASX_ERR04ADDR(a) (a)
#define arguments_BDK_RASX_ERR04ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err04ctlr
 *
 * RAS Error Record 04 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err04ctlr
{
    uint64_t u;
    struct bdk_rasx_err04ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err04ctlr_s cn9; */
    /* struct bdk_rasx_err04ctlr_s cn96xxp1; */
    struct bdk_rasx_err04ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err04ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err04ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err04ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err04ctlr bdk_rasx_err04ctlr_t;

static inline uint64_t BDK_RASX_ERR04CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR04CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050108ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050108ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050108ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050108ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR04CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR04CTLR(a) bdk_rasx_err04ctlr_t
#define bustype_BDK_RASX_ERR04CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR04CTLR(a) "RASX_ERR04CTLR"
#define busnum_BDK_RASX_ERR04CTLR(a) (a)
#define arguments_BDK_RASX_ERR04CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err04fr
 *
 * RAS Error Record 04 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err04fr
{
    uint64_t u;
    struct bdk_rasx_err04fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err04fr_s cn9; */
    /* struct bdk_rasx_err04fr_s cn96xxp1; */
    struct bdk_rasx_err04fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err04fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err04fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err04fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err04fr bdk_rasx_err04fr_t;

static inline uint64_t BDK_RASX_ERR04FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR04FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050100ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050100ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050100ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050100ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR04FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR04FR(a) bdk_rasx_err04fr_t
#define bustype_BDK_RASX_ERR04FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR04FR(a) "RASX_ERR04FR"
#define busnum_BDK_RASX_ERR04FR(a) (a)
#define arguments_BDK_RASX_ERR04FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err04misc0
 *
 * RAS Error Record 04 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err04misc0
{
    uint64_t u;
    struct bdk_rasx_err04misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_16_31        : 16;
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t reserved_16_31        : 16;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err04misc0_s cn; */
};
typedef union bdk_rasx_err04misc0 bdk_rasx_err04misc0_t;

static inline uint64_t BDK_RASX_ERR04MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR04MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050120ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050120ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050120ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050120ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR04MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR04MISC0(a) bdk_rasx_err04misc0_t
#define bustype_BDK_RASX_ERR04MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR04MISC0(a) "RASX_ERR04MISC0"
#define busnum_BDK_RASX_ERR04MISC0(a) (a)
#define arguments_BDK_RASX_ERR04MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err04misc1
 *
 * RAS Error Record 04 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err04misc1
{
    uint64_t u;
    struct bdk_rasx_err04misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err04misc1_s cn; */
};
typedef union bdk_rasx_err04misc1 bdk_rasx_err04misc1_t;

static inline uint64_t BDK_RASX_ERR04MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR04MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050128ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050128ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050128ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050128ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR04MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR04MISC1(a) bdk_rasx_err04misc1_t
#define bustype_BDK_RASX_ERR04MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR04MISC1(a) "RASX_ERR04MISC1"
#define busnum_BDK_RASX_ERR04MISC1(a) (a)
#define arguments_BDK_RASX_ERR04MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err04status
 *
 * RAS Error Record 04 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err04status
{
    uint64_t u;
    struct bdk_rasx_err04status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err04status_s cn9; */
    /* struct bdk_rasx_err04status_s cn96xxp1; */
    struct bdk_rasx_err04status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err04status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err04status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err04status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err04status bdk_rasx_err04status_t;

static inline uint64_t BDK_RASX_ERR04STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR04STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050110ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050110ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050110ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050110ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR04STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR04STATUS(a) bdk_rasx_err04status_t
#define bustype_BDK_RASX_ERR04STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR04STATUS(a) "RASX_ERR04STATUS"
#define busnum_BDK_RASX_ERR04STATUS(a) (a)
#define arguments_BDK_RASX_ERR04STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err05addr
 *
 * RAS Error Record 05 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err05addr
{
    uint64_t u;
    struct bdk_rasx_err05addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err05addr_s cn; */
};
typedef union bdk_rasx_err05addr bdk_rasx_err05addr_t;

static inline uint64_t BDK_RASX_ERR05ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR05ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050158ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050158ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050158ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050158ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR05ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR05ADDR(a) bdk_rasx_err05addr_t
#define bustype_BDK_RASX_ERR05ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR05ADDR(a) "RASX_ERR05ADDR"
#define busnum_BDK_RASX_ERR05ADDR(a) (a)
#define arguments_BDK_RASX_ERR05ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err05ctlr
 *
 * RAS Error Record 05 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err05ctlr
{
    uint64_t u;
    struct bdk_rasx_err05ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err05ctlr_s cn9; */
    /* struct bdk_rasx_err05ctlr_s cn96xxp1; */
    struct bdk_rasx_err05ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err05ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err05ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err05ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err05ctlr bdk_rasx_err05ctlr_t;

static inline uint64_t BDK_RASX_ERR05CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR05CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050148ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050148ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050148ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050148ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR05CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR05CTLR(a) bdk_rasx_err05ctlr_t
#define bustype_BDK_RASX_ERR05CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR05CTLR(a) "RASX_ERR05CTLR"
#define busnum_BDK_RASX_ERR05CTLR(a) (a)
#define arguments_BDK_RASX_ERR05CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err05fr
 *
 * RAS Error Record 05 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err05fr
{
    uint64_t u;
    struct bdk_rasx_err05fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err05fr_s cn9; */
    /* struct bdk_rasx_err05fr_s cn96xxp1; */
    struct bdk_rasx_err05fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err05fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err05fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err05fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err05fr bdk_rasx_err05fr_t;

static inline uint64_t BDK_RASX_ERR05FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR05FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050140ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050140ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050140ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050140ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR05FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR05FR(a) bdk_rasx_err05fr_t
#define bustype_BDK_RASX_ERR05FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR05FR(a) "RASX_ERR05FR"
#define busnum_BDK_RASX_ERR05FR(a) (a)
#define arguments_BDK_RASX_ERR05FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err05misc0
 *
 * RAS Error Record 05 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err05misc0
{
    uint64_t u;
    struct bdk_rasx_err05misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_16_31        : 16;
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t imp_set               : 8;  /**< [ 15:  8](SR/W) The set number with the error. */
        uint64_t reserved_16_31        : 16;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err05misc0_s cn; */
};
typedef union bdk_rasx_err05misc0 bdk_rasx_err05misc0_t;

static inline uint64_t BDK_RASX_ERR05MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR05MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050160ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050160ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050160ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050160ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR05MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR05MISC0(a) bdk_rasx_err05misc0_t
#define bustype_BDK_RASX_ERR05MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR05MISC0(a) "RASX_ERR05MISC0"
#define busnum_BDK_RASX_ERR05MISC0(a) (a)
#define arguments_BDK_RASX_ERR05MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err05misc1
 *
 * RAS Error Record 05 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err05misc1
{
    uint64_t u;
    struct bdk_rasx_err05misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err05misc1_s cn; */
};
typedef union bdk_rasx_err05misc1 bdk_rasx_err05misc1_t;

static inline uint64_t BDK_RASX_ERR05MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR05MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050168ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050168ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050168ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050168ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR05MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR05MISC1(a) bdk_rasx_err05misc1_t
#define bustype_BDK_RASX_ERR05MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR05MISC1(a) "RASX_ERR05MISC1"
#define busnum_BDK_RASX_ERR05MISC1(a) (a)
#define arguments_BDK_RASX_ERR05MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err05status
 *
 * RAS Error Record 05 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err05status
{
    uint64_t u;
    struct bdk_rasx_err05status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err05status_s cn9; */
    /* struct bdk_rasx_err05status_s cn96xxp1; */
    struct bdk_rasx_err05status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err05status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err05status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err05status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err05status bdk_rasx_err05status_t;

static inline uint64_t BDK_RASX_ERR05STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR05STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050150ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050150ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050150ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050150ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR05STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR05STATUS(a) bdk_rasx_err05status_t
#define bustype_BDK_RASX_ERR05STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR05STATUS(a) "RASX_ERR05STATUS"
#define busnum_BDK_RASX_ERR05STATUS(a) (a)
#define arguments_BDK_RASX_ERR05STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err06addr
 *
 * RAS Error Record 06 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err06addr
{
    uint64_t u;
    struct bdk_rasx_err06addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err06addr_s cn; */
};
typedef union bdk_rasx_err06addr bdk_rasx_err06addr_t;

static inline uint64_t BDK_RASX_ERR06ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR06ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050198ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050198ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050198ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050198ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR06ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR06ADDR(a) bdk_rasx_err06addr_t
#define bustype_BDK_RASX_ERR06ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR06ADDR(a) "RASX_ERR06ADDR"
#define busnum_BDK_RASX_ERR06ADDR(a) (a)
#define arguments_BDK_RASX_ERR06ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err06ctlr
 *
 * RAS Error Record 06 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err06ctlr
{
    uint64_t u;
    struct bdk_rasx_err06ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err06ctlr_s cn9; */
    /* struct bdk_rasx_err06ctlr_s cn96xxp1; */
    struct bdk_rasx_err06ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err06ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err06ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err06ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err06ctlr bdk_rasx_err06ctlr_t;

static inline uint64_t BDK_RASX_ERR06CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR06CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050188ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050188ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050188ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050188ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR06CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR06CTLR(a) bdk_rasx_err06ctlr_t
#define bustype_BDK_RASX_ERR06CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR06CTLR(a) "RASX_ERR06CTLR"
#define busnum_BDK_RASX_ERR06CTLR(a) (a)
#define arguments_BDK_RASX_ERR06CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err06fr
 *
 * RAS Error Record 06 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err06fr
{
    uint64_t u;
    struct bdk_rasx_err06fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err06fr_s cn9; */
    /* struct bdk_rasx_err06fr_s cn96xxp1; */
    struct bdk_rasx_err06fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err06fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err06fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err06fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err06fr bdk_rasx_err06fr_t;

static inline uint64_t BDK_RASX_ERR06FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR06FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050180ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050180ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050180ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050180ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR06FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR06FR(a) bdk_rasx_err06fr_t
#define bustype_BDK_RASX_ERR06FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR06FR(a) "RASX_ERR06FR"
#define busnum_BDK_RASX_ERR06FR(a) (a)
#define arguments_BDK_RASX_ERR06FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err06misc0
 *
 * RAS Error Record 06 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err06misc0
{
    uint64_t u;
    struct bdk_rasx_err06misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err06misc0_s cn; */
};
typedef union bdk_rasx_err06misc0 bdk_rasx_err06misc0_t;

static inline uint64_t BDK_RASX_ERR06MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR06MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080501a0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080501a0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080501a0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080501a0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR06MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR06MISC0(a) bdk_rasx_err06misc0_t
#define bustype_BDK_RASX_ERR06MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR06MISC0(a) "RASX_ERR06MISC0"
#define busnum_BDK_RASX_ERR06MISC0(a) (a)
#define arguments_BDK_RASX_ERR06MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err06misc1
 *
 * RAS Error Record 06 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err06misc1
{
    uint64_t u;
    struct bdk_rasx_err06misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err06misc1_s cn; */
};
typedef union bdk_rasx_err06misc1 bdk_rasx_err06misc1_t;

static inline uint64_t BDK_RASX_ERR06MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR06MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080501a8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080501a8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080501a8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080501a8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR06MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR06MISC1(a) bdk_rasx_err06misc1_t
#define bustype_BDK_RASX_ERR06MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR06MISC1(a) "RASX_ERR06MISC1"
#define busnum_BDK_RASX_ERR06MISC1(a) (a)
#define arguments_BDK_RASX_ERR06MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err06status
 *
 * RAS Error Record 06 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err06status
{
    uint64_t u;
    struct bdk_rasx_err06status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err06status_s cn9; */
    /* struct bdk_rasx_err06status_s cn96xxp1; */
    struct bdk_rasx_err06status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err06status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err06status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err06status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err06status bdk_rasx_err06status_t;

static inline uint64_t BDK_RASX_ERR06STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR06STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050190ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050190ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050190ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050190ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR06STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR06STATUS(a) bdk_rasx_err06status_t
#define bustype_BDK_RASX_ERR06STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR06STATUS(a) "RASX_ERR06STATUS"
#define busnum_BDK_RASX_ERR06STATUS(a) (a)
#define arguments_BDK_RASX_ERR06STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err07addr
 *
 * RAS Error Record 07 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err07addr
{
    uint64_t u;
    struct bdk_rasx_err07addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err07addr_s cn; */
};
typedef union bdk_rasx_err07addr bdk_rasx_err07addr_t;

static inline uint64_t BDK_RASX_ERR07ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR07ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080501d8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080501d8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080501d8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080501d8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR07ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR07ADDR(a) bdk_rasx_err07addr_t
#define bustype_BDK_RASX_ERR07ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR07ADDR(a) "RASX_ERR07ADDR"
#define busnum_BDK_RASX_ERR07ADDR(a) (a)
#define arguments_BDK_RASX_ERR07ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err07ctlr
 *
 * RAS Error Record 07 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err07ctlr
{
    uint64_t u;
    struct bdk_rasx_err07ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err07ctlr_s cn9; */
    /* struct bdk_rasx_err07ctlr_s cn96xxp1; */
    struct bdk_rasx_err07ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err07ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err07ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err07ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err07ctlr bdk_rasx_err07ctlr_t;

static inline uint64_t BDK_RASX_ERR07CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR07CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080501c8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080501c8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080501c8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080501c8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR07CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR07CTLR(a) bdk_rasx_err07ctlr_t
#define bustype_BDK_RASX_ERR07CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR07CTLR(a) "RASX_ERR07CTLR"
#define busnum_BDK_RASX_ERR07CTLR(a) (a)
#define arguments_BDK_RASX_ERR07CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err07fr
 *
 * RAS Error Record 07 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err07fr
{
    uint64_t u;
    struct bdk_rasx_err07fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err07fr_s cn9; */
    /* struct bdk_rasx_err07fr_s cn96xxp1; */
    struct bdk_rasx_err07fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err07fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err07fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err07fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err07fr bdk_rasx_err07fr_t;

static inline uint64_t BDK_RASX_ERR07FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR07FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080501c0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080501c0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080501c0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080501c0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR07FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR07FR(a) bdk_rasx_err07fr_t
#define bustype_BDK_RASX_ERR07FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR07FR(a) "RASX_ERR07FR"
#define busnum_BDK_RASX_ERR07FR(a) (a)
#define arguments_BDK_RASX_ERR07FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err07misc0
 *
 * RAS Error Record 07 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err07misc0
{
    uint64_t u;
    struct bdk_rasx_err07misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_8_31         : 24;
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t reserved_8_31         : 24;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err07misc0_s cn; */
};
typedef union bdk_rasx_err07misc0 bdk_rasx_err07misc0_t;

static inline uint64_t BDK_RASX_ERR07MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR07MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080501e0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080501e0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080501e0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080501e0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR07MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR07MISC0(a) bdk_rasx_err07misc0_t
#define bustype_BDK_RASX_ERR07MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR07MISC0(a) "RASX_ERR07MISC0"
#define busnum_BDK_RASX_ERR07MISC0(a) (a)
#define arguments_BDK_RASX_ERR07MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err07misc1
 *
 * RAS Error Record 07 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err07misc1
{
    uint64_t u;
    struct bdk_rasx_err07misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err07misc1_s cn; */
};
typedef union bdk_rasx_err07misc1 bdk_rasx_err07misc1_t;

static inline uint64_t BDK_RASX_ERR07MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR07MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080501e8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080501e8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080501e8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080501e8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR07MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR07MISC1(a) bdk_rasx_err07misc1_t
#define bustype_BDK_RASX_ERR07MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR07MISC1(a) "RASX_ERR07MISC1"
#define busnum_BDK_RASX_ERR07MISC1(a) (a)
#define arguments_BDK_RASX_ERR07MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err07status
 *
 * RAS Error Record 07 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err07status
{
    uint64_t u;
    struct bdk_rasx_err07status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err07status_s cn9; */
    /* struct bdk_rasx_err07status_s cn96xxp1; */
    struct bdk_rasx_err07status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err07status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err07status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err07status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err07status bdk_rasx_err07status_t;

static inline uint64_t BDK_RASX_ERR07STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR07STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080501d0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080501d0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080501d0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080501d0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR07STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR07STATUS(a) bdk_rasx_err07status_t
#define bustype_BDK_RASX_ERR07STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR07STATUS(a) "RASX_ERR07STATUS"
#define busnum_BDK_RASX_ERR07STATUS(a) (a)
#define arguments_BDK_RASX_ERR07STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err08addr
 *
 * RAS Error Record 08 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err08addr
{
    uint64_t u;
    struct bdk_rasx_err08addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err08addr_s cn; */
};
typedef union bdk_rasx_err08addr bdk_rasx_err08addr_t;

static inline uint64_t BDK_RASX_ERR08ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR08ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050218ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050218ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050218ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050218ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR08ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR08ADDR(a) bdk_rasx_err08addr_t
#define bustype_BDK_RASX_ERR08ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR08ADDR(a) "RASX_ERR08ADDR"
#define busnum_BDK_RASX_ERR08ADDR(a) (a)
#define arguments_BDK_RASX_ERR08ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err08ctlr
 *
 * RAS Error Record 08 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err08ctlr
{
    uint64_t u;
    struct bdk_rasx_err08ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err08ctlr_s cn9; */
    /* struct bdk_rasx_err08ctlr_s cn96xxp1; */
    struct bdk_rasx_err08ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err08ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err08ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err08ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err08ctlr bdk_rasx_err08ctlr_t;

static inline uint64_t BDK_RASX_ERR08CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR08CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050208ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050208ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050208ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050208ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR08CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR08CTLR(a) bdk_rasx_err08ctlr_t
#define bustype_BDK_RASX_ERR08CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR08CTLR(a) "RASX_ERR08CTLR"
#define busnum_BDK_RASX_ERR08CTLR(a) (a)
#define arguments_BDK_RASX_ERR08CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err08fr
 *
 * RAS Error Record 08 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err08fr
{
    uint64_t u;
    struct bdk_rasx_err08fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err08fr_s cn9; */
    /* struct bdk_rasx_err08fr_s cn96xxp1; */
    struct bdk_rasx_err08fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err08fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err08fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err08fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err08fr bdk_rasx_err08fr_t;

static inline uint64_t BDK_RASX_ERR08FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR08FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050200ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050200ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050200ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050200ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR08FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR08FR(a) bdk_rasx_err08fr_t
#define bustype_BDK_RASX_ERR08FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR08FR(a) "RASX_ERR08FR"
#define busnum_BDK_RASX_ERR08FR(a) (a)
#define arguments_BDK_RASX_ERR08FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err08misc0
 *
 * RAS Error Record 08 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err08misc0
{
    uint64_t u;
    struct bdk_rasx_err08misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_8_31         : 24;
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t reserved_8_31         : 24;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err08misc0_s cn; */
};
typedef union bdk_rasx_err08misc0 bdk_rasx_err08misc0_t;

static inline uint64_t BDK_RASX_ERR08MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR08MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050220ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050220ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050220ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050220ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR08MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR08MISC0(a) bdk_rasx_err08misc0_t
#define bustype_BDK_RASX_ERR08MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR08MISC0(a) "RASX_ERR08MISC0"
#define busnum_BDK_RASX_ERR08MISC0(a) (a)
#define arguments_BDK_RASX_ERR08MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err08misc1
 *
 * RAS Error Record 08 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err08misc1
{
    uint64_t u;
    struct bdk_rasx_err08misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err08misc1_s cn; */
};
typedef union bdk_rasx_err08misc1 bdk_rasx_err08misc1_t;

static inline uint64_t BDK_RASX_ERR08MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR08MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050228ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050228ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050228ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050228ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR08MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR08MISC1(a) bdk_rasx_err08misc1_t
#define bustype_BDK_RASX_ERR08MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR08MISC1(a) "RASX_ERR08MISC1"
#define busnum_BDK_RASX_ERR08MISC1(a) (a)
#define arguments_BDK_RASX_ERR08MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err08status
 *
 * RAS Error Record 08 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err08status
{
    uint64_t u;
    struct bdk_rasx_err08status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err08status_s cn9; */
    /* struct bdk_rasx_err08status_s cn96xxp1; */
    struct bdk_rasx_err08status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err08status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err08status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err08status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err08status bdk_rasx_err08status_t;

static inline uint64_t BDK_RASX_ERR08STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR08STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050210ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050210ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050210ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050210ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR08STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR08STATUS(a) bdk_rasx_err08status_t
#define bustype_BDK_RASX_ERR08STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR08STATUS(a) "RASX_ERR08STATUS"
#define busnum_BDK_RASX_ERR08STATUS(a) (a)
#define arguments_BDK_RASX_ERR08STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err09addr
 *
 * RAS Error Record 09 Address Register
 * This register returns the address associated with the error in this error record.
 */
union bdk_rasx_err09addr
{
    uint64_t u;
    struct bdk_rasx_err09addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err09addr_s cn; */
};
typedef union bdk_rasx_err09addr bdk_rasx_err09addr_t;

static inline uint64_t BDK_RASX_ERR09ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR09ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050258ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050258ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050258ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050258ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR09ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR09ADDR(a) bdk_rasx_err09addr_t
#define bustype_BDK_RASX_ERR09ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR09ADDR(a) "RASX_ERR09ADDR"
#define busnum_BDK_RASX_ERR09ADDR(a) (a)
#define arguments_BDK_RASX_ERR09ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err09ctlr
 *
 * RAS Error Record 09 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err09ctlr
{
    uint64_t u;
    struct bdk_rasx_err09ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err09ctlr_s cn9; */
    /* struct bdk_rasx_err09ctlr_s cn96xxp1; */
    struct bdk_rasx_err09ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err09ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err09ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err09ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err09ctlr bdk_rasx_err09ctlr_t;

static inline uint64_t BDK_RASX_ERR09CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR09CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050248ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050248ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050248ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050248ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR09CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR09CTLR(a) bdk_rasx_err09ctlr_t
#define bustype_BDK_RASX_ERR09CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR09CTLR(a) "RASX_ERR09CTLR"
#define busnum_BDK_RASX_ERR09CTLR(a) (a)
#define arguments_BDK_RASX_ERR09CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err09fr
 *
 * RAS Error Record 09 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err09fr
{
    uint64_t u;
    struct bdk_rasx_err09fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err09fr_s cn9; */
    /* struct bdk_rasx_err09fr_s cn96xxp1; */
    struct bdk_rasx_err09fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err09fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err09fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err09fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err09fr bdk_rasx_err09fr_t;

static inline uint64_t BDK_RASX_ERR09FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR09FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050240ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050240ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050240ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050240ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR09FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR09FR(a) bdk_rasx_err09fr_t
#define bustype_BDK_RASX_ERR09FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR09FR(a) "RASX_ERR09FR"
#define busnum_BDK_RASX_ERR09FR(a) (a)
#define arguments_BDK_RASX_ERR09FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err09misc0
 *
 * RAS Error Record 09 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err09misc0
{
    uint64_t u;
    struct bdk_rasx_err09misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_8_31         : 24;
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t reserved_8_31         : 24;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err09misc0_s cn; */
};
typedef union bdk_rasx_err09misc0 bdk_rasx_err09misc0_t;

static inline uint64_t BDK_RASX_ERR09MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR09MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050260ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050260ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050260ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050260ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR09MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR09MISC0(a) bdk_rasx_err09misc0_t
#define bustype_BDK_RASX_ERR09MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR09MISC0(a) "RASX_ERR09MISC0"
#define busnum_BDK_RASX_ERR09MISC0(a) (a)
#define arguments_BDK_RASX_ERR09MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err09misc1
 *
 * RAS Error Record 09 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err09misc1
{
    uint64_t u;
    struct bdk_rasx_err09misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err09misc1_s cn; */
};
typedef union bdk_rasx_err09misc1 bdk_rasx_err09misc1_t;

static inline uint64_t BDK_RASX_ERR09MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR09MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050268ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050268ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050268ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050268ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR09MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR09MISC1(a) bdk_rasx_err09misc1_t
#define bustype_BDK_RASX_ERR09MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR09MISC1(a) "RASX_ERR09MISC1"
#define busnum_BDK_RASX_ERR09MISC1(a) (a)
#define arguments_BDK_RASX_ERR09MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err09status
 *
 * RAS Error Record 09 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err09status
{
    uint64_t u;
    struct bdk_rasx_err09status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err09status_s cn9; */
    /* struct bdk_rasx_err09status_s cn96xxp1; */
    struct bdk_rasx_err09status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err09status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err09status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err09status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err09status bdk_rasx_err09status_t;

static inline uint64_t BDK_RASX_ERR09STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR09STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050250ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050250ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050250ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050250ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR09STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR09STATUS(a) bdk_rasx_err09status_t
#define bustype_BDK_RASX_ERR09STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR09STATUS(a) "RASX_ERR09STATUS"
#define busnum_BDK_RASX_ERR09STATUS(a) (a)
#define arguments_BDK_RASX_ERR09STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err10addr
 *
 * RAS Error Record 10 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err10addr
{
    uint64_t u;
    struct bdk_rasx_err10addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err10addr_s cn; */
};
typedef union bdk_rasx_err10addr bdk_rasx_err10addr_t;

static inline uint64_t BDK_RASX_ERR10ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR10ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050298ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050298ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050298ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050298ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR10ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR10ADDR(a) bdk_rasx_err10addr_t
#define bustype_BDK_RASX_ERR10ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR10ADDR(a) "RASX_ERR10ADDR"
#define busnum_BDK_RASX_ERR10ADDR(a) (a)
#define arguments_BDK_RASX_ERR10ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err10ctlr
 *
 * RAS Error Record 10 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err10ctlr
{
    uint64_t u;
    struct bdk_rasx_err10ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err10ctlr_s cn9; */
    /* struct bdk_rasx_err10ctlr_s cn96xxp1; */
    struct bdk_rasx_err10ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err10ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err10ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err10ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err10ctlr bdk_rasx_err10ctlr_t;

static inline uint64_t BDK_RASX_ERR10CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR10CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050288ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050288ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050288ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050288ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR10CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR10CTLR(a) bdk_rasx_err10ctlr_t
#define bustype_BDK_RASX_ERR10CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR10CTLR(a) "RASX_ERR10CTLR"
#define busnum_BDK_RASX_ERR10CTLR(a) (a)
#define arguments_BDK_RASX_ERR10CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err10fr
 *
 * RAS Error Record 10 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err10fr
{
    uint64_t u;
    struct bdk_rasx_err10fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err10fr_s cn9; */
    /* struct bdk_rasx_err10fr_s cn96xxp1; */
    struct bdk_rasx_err10fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err10fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err10fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err10fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err10fr bdk_rasx_err10fr_t;

static inline uint64_t BDK_RASX_ERR10FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR10FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050280ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050280ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050280ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050280ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR10FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR10FR(a) bdk_rasx_err10fr_t
#define bustype_BDK_RASX_ERR10FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR10FR(a) "RASX_ERR10FR"
#define busnum_BDK_RASX_ERR10FR(a) (a)
#define arguments_BDK_RASX_ERR10FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err10misc0
 *
 * RAS Error Record 10 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err10misc0
{
    uint64_t u;
    struct bdk_rasx_err10misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err10misc0_s cn; */
};
typedef union bdk_rasx_err10misc0 bdk_rasx_err10misc0_t;

static inline uint64_t BDK_RASX_ERR10MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR10MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080502a0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080502a0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080502a0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080502a0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR10MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR10MISC0(a) bdk_rasx_err10misc0_t
#define bustype_BDK_RASX_ERR10MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR10MISC0(a) "RASX_ERR10MISC0"
#define busnum_BDK_RASX_ERR10MISC0(a) (a)
#define arguments_BDK_RASX_ERR10MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err10misc1
 *
 * RAS Error Record 10 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err10misc1
{
    uint64_t u;
    struct bdk_rasx_err10misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err10misc1_s cn; */
};
typedef union bdk_rasx_err10misc1 bdk_rasx_err10misc1_t;

static inline uint64_t BDK_RASX_ERR10MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR10MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080502a8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080502a8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080502a8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080502a8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR10MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR10MISC1(a) bdk_rasx_err10misc1_t
#define bustype_BDK_RASX_ERR10MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR10MISC1(a) "RASX_ERR10MISC1"
#define busnum_BDK_RASX_ERR10MISC1(a) (a)
#define arguments_BDK_RASX_ERR10MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err10status
 *
 * RAS Error Record 10 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err10status
{
    uint64_t u;
    struct bdk_rasx_err10status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err10status_s cn9; */
    /* struct bdk_rasx_err10status_s cn96xxp1; */
    struct bdk_rasx_err10status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err10status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err10status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err10status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err10status bdk_rasx_err10status_t;

static inline uint64_t BDK_RASX_ERR10STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR10STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050290ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050290ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050290ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050290ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR10STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR10STATUS(a) bdk_rasx_err10status_t
#define bustype_BDK_RASX_ERR10STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR10STATUS(a) "RASX_ERR10STATUS"
#define busnum_BDK_RASX_ERR10STATUS(a) (a)
#define arguments_BDK_RASX_ERR10STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err11addr
 *
 * RAS Error Record 11 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err11addr
{
    uint64_t u;
    struct bdk_rasx_err11addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err11addr_s cn; */
};
typedef union bdk_rasx_err11addr bdk_rasx_err11addr_t;

static inline uint64_t BDK_RASX_ERR11ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR11ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080502d8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080502d8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080502d8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080502d8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR11ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR11ADDR(a) bdk_rasx_err11addr_t
#define bustype_BDK_RASX_ERR11ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR11ADDR(a) "RASX_ERR11ADDR"
#define busnum_BDK_RASX_ERR11ADDR(a) (a)
#define arguments_BDK_RASX_ERR11ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err11ctlr
 *
 * RAS Error Record 11 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err11ctlr
{
    uint64_t u;
    struct bdk_rasx_err11ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err11ctlr_s cn9; */
    /* struct bdk_rasx_err11ctlr_s cn96xxp1; */
    struct bdk_rasx_err11ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err11ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err11ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err11ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err11ctlr bdk_rasx_err11ctlr_t;

static inline uint64_t BDK_RASX_ERR11CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR11CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080502c8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080502c8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080502c8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080502c8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR11CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR11CTLR(a) bdk_rasx_err11ctlr_t
#define bustype_BDK_RASX_ERR11CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR11CTLR(a) "RASX_ERR11CTLR"
#define busnum_BDK_RASX_ERR11CTLR(a) (a)
#define arguments_BDK_RASX_ERR11CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err11fr
 *
 * RAS Error Record 11 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err11fr
{
    uint64_t u;
    struct bdk_rasx_err11fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err11fr_s cn9; */
    /* struct bdk_rasx_err11fr_s cn96xxp1; */
    struct bdk_rasx_err11fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err11fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err11fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err11fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err11fr bdk_rasx_err11fr_t;

static inline uint64_t BDK_RASX_ERR11FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR11FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080502c0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080502c0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080502c0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080502c0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR11FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR11FR(a) bdk_rasx_err11fr_t
#define bustype_BDK_RASX_ERR11FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR11FR(a) "RASX_ERR11FR"
#define busnum_BDK_RASX_ERR11FR(a) (a)
#define arguments_BDK_RASX_ERR11FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err11misc0
 *
 * RAS Error Record 11 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err11misc0
{
    uint64_t u;
    struct bdk_rasx_err11misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err11misc0_s cn; */
};
typedef union bdk_rasx_err11misc0 bdk_rasx_err11misc0_t;

static inline uint64_t BDK_RASX_ERR11MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR11MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080502e0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080502e0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080502e0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080502e0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR11MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR11MISC0(a) bdk_rasx_err11misc0_t
#define bustype_BDK_RASX_ERR11MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR11MISC0(a) "RASX_ERR11MISC0"
#define busnum_BDK_RASX_ERR11MISC0(a) (a)
#define arguments_BDK_RASX_ERR11MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err11misc1
 *
 * RAS Error Record 11 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err11misc1
{
    uint64_t u;
    struct bdk_rasx_err11misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err11misc1_s cn; */
};
typedef union bdk_rasx_err11misc1 bdk_rasx_err11misc1_t;

static inline uint64_t BDK_RASX_ERR11MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR11MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080502e8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080502e8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080502e8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080502e8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR11MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR11MISC1(a) bdk_rasx_err11misc1_t
#define bustype_BDK_RASX_ERR11MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR11MISC1(a) "RASX_ERR11MISC1"
#define busnum_BDK_RASX_ERR11MISC1(a) (a)
#define arguments_BDK_RASX_ERR11MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err11status
 *
 * RAS Error Record 11 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err11status
{
    uint64_t u;
    struct bdk_rasx_err11status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN] */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN] */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err11status_s cn9; */
    /* struct bdk_rasx_err11status_s cn96xxp1; */
    struct bdk_rasx_err11status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN] */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN] */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err11status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err11status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err11status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err11status bdk_rasx_err11status_t;

static inline uint64_t BDK_RASX_ERR11STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR11STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080502d0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080502d0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080502d0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080502d0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR11STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR11STATUS(a) bdk_rasx_err11status_t
#define bustype_BDK_RASX_ERR11STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR11STATUS(a) "RASX_ERR11STATUS"
#define busnum_BDK_RASX_ERR11STATUS(a) (a)
#define arguments_BDK_RASX_ERR11STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err12addr
 *
 * RAS Error Record 12 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err12addr
{
    uint64_t u;
    struct bdk_rasx_err12addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err12addr_s cn; */
};
typedef union bdk_rasx_err12addr bdk_rasx_err12addr_t;

static inline uint64_t BDK_RASX_ERR12ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR12ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050318ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050318ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050318ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050318ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR12ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR12ADDR(a) bdk_rasx_err12addr_t
#define bustype_BDK_RASX_ERR12ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR12ADDR(a) "RASX_ERR12ADDR"
#define busnum_BDK_RASX_ERR12ADDR(a) (a)
#define arguments_BDK_RASX_ERR12ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err12ctlr
 *
 * RAS Error Record 12 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err12ctlr
{
    uint64_t u;
    struct bdk_rasx_err12ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err12ctlr_s cn9; */
    /* struct bdk_rasx_err12ctlr_s cn96xxp1; */
    struct bdk_rasx_err12ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err12ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err12ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err12ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err12ctlr bdk_rasx_err12ctlr_t;

static inline uint64_t BDK_RASX_ERR12CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR12CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050308ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050308ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050308ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050308ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR12CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR12CTLR(a) bdk_rasx_err12ctlr_t
#define bustype_BDK_RASX_ERR12CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR12CTLR(a) "RASX_ERR12CTLR"
#define busnum_BDK_RASX_ERR12CTLR(a) (a)
#define arguments_BDK_RASX_ERR12CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err12fr
 *
 * RAS Error Record 12 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err12fr
{
    uint64_t u;
    struct bdk_rasx_err12fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err12fr_s cn9; */
    /* struct bdk_rasx_err12fr_s cn96xxp1; */
    struct bdk_rasx_err12fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err12fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err12fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err12fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err12fr bdk_rasx_err12fr_t;

static inline uint64_t BDK_RASX_ERR12FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR12FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050300ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050300ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050300ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050300ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR12FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR12FR(a) bdk_rasx_err12fr_t
#define bustype_BDK_RASX_ERR12FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR12FR(a) "RASX_ERR12FR"
#define busnum_BDK_RASX_ERR12FR(a) (a)
#define arguments_BDK_RASX_ERR12FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err12misc0
 *
 * RAS Error Record 12 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err12misc0
{
    uint64_t u;
    struct bdk_rasx_err12misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_4_31         : 28;
        uint64_t consumer              : 4;  /**< [  3:  0](SR/W) Consumer code:
                                                                   0 = Unknown.
                                                                   1 = Instruction cache.
                                                                   2 = Data cache.
                                                                   3 = Walker Cache.
                                                                   4-15 = Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t consumer              : 4;  /**< [  3:  0](SR/W) Consumer code:
                                                                   0 = Unknown.
                                                                   1 = Instruction cache.
                                                                   2 = Data cache.
                                                                   3 = Walker Cache.
                                                                   4-15 = Reserved. */
        uint64_t reserved_4_31         : 28;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err12misc0_s cn; */
};
typedef union bdk_rasx_err12misc0 bdk_rasx_err12misc0_t;

static inline uint64_t BDK_RASX_ERR12MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR12MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050320ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050320ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050320ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050320ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR12MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR12MISC0(a) bdk_rasx_err12misc0_t
#define bustype_BDK_RASX_ERR12MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR12MISC0(a) "RASX_ERR12MISC0"
#define busnum_BDK_RASX_ERR12MISC0(a) (a)
#define arguments_BDK_RASX_ERR12MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err12misc1
 *
 * RAS Error Record 12 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err12misc1
{
    uint64_t u;
    struct bdk_rasx_err12misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err12misc1_s cn; */
};
typedef union bdk_rasx_err12misc1 bdk_rasx_err12misc1_t;

static inline uint64_t BDK_RASX_ERR12MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR12MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050328ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050328ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050328ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050328ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR12MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR12MISC1(a) bdk_rasx_err12misc1_t
#define bustype_BDK_RASX_ERR12MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR12MISC1(a) "RASX_ERR12MISC1"
#define busnum_BDK_RASX_ERR12MISC1(a) (a)
#define arguments_BDK_RASX_ERR12MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err12status
 *
 * RAS Error Record 12 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err12status
{
    uint64_t u;
    struct bdk_rasx_err12status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err12status_s cn9; */
    /* struct bdk_rasx_err12status_s cn96xxp1; */
    struct bdk_rasx_err12status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err12status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err12status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err12status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err12status bdk_rasx_err12status_t;

static inline uint64_t BDK_RASX_ERR12STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR12STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050310ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050310ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050310ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050310ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR12STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR12STATUS(a) bdk_rasx_err12status_t
#define bustype_BDK_RASX_ERR12STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR12STATUS(a) "RASX_ERR12STATUS"
#define busnum_BDK_RASX_ERR12STATUS(a) (a)
#define arguments_BDK_RASX_ERR12STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err13addr
 *
 * RAS Error Record 13 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err13addr
{
    uint64_t u;
    struct bdk_rasx_err13addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err13addr_s cn; */
};
typedef union bdk_rasx_err13addr bdk_rasx_err13addr_t;

static inline uint64_t BDK_RASX_ERR13ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR13ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050358ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050358ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050358ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050358ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR13ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR13ADDR(a) bdk_rasx_err13addr_t
#define bustype_BDK_RASX_ERR13ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR13ADDR(a) "RASX_ERR13ADDR"
#define busnum_BDK_RASX_ERR13ADDR(a) (a)
#define arguments_BDK_RASX_ERR13ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err13ctlr
 *
 * RAS Error Record 13 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err13ctlr
{
    uint64_t u;
    struct bdk_rasx_err13ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err13ctlr_s cn9; */
    /* struct bdk_rasx_err13ctlr_s cn96xxp1; */
    struct bdk_rasx_err13ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err13ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err13ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err13ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err13ctlr bdk_rasx_err13ctlr_t;

static inline uint64_t BDK_RASX_ERR13CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR13CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050348ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050348ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050348ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050348ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR13CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR13CTLR(a) bdk_rasx_err13ctlr_t
#define bustype_BDK_RASX_ERR13CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR13CTLR(a) "RASX_ERR13CTLR"
#define busnum_BDK_RASX_ERR13CTLR(a) (a)
#define arguments_BDK_RASX_ERR13CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err13fr
 *
 * RAS Error Record 13 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err13fr
{
    uint64_t u;
    struct bdk_rasx_err13fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err13fr_s cn9; */
    /* struct bdk_rasx_err13fr_s cn96xxp1; */
    struct bdk_rasx_err13fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err13fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err13fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err13fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err13fr bdk_rasx_err13fr_t;

static inline uint64_t BDK_RASX_ERR13FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR13FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050340ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050340ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050340ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050340ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR13FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR13FR(a) bdk_rasx_err13fr_t
#define bustype_BDK_RASX_ERR13FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR13FR(a) "RASX_ERR13FR"
#define busnum_BDK_RASX_ERR13FR(a) (a)
#define arguments_BDK_RASX_ERR13FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err13misc0
 *
 * RAS Error Record 13 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err13misc0
{
    uint64_t u;
    struct bdk_rasx_err13misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err13misc0_s cn; */
};
typedef union bdk_rasx_err13misc0 bdk_rasx_err13misc0_t;

static inline uint64_t BDK_RASX_ERR13MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR13MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050360ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050360ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050360ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050360ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR13MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR13MISC0(a) bdk_rasx_err13misc0_t
#define bustype_BDK_RASX_ERR13MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR13MISC0(a) "RASX_ERR13MISC0"
#define busnum_BDK_RASX_ERR13MISC0(a) (a)
#define arguments_BDK_RASX_ERR13MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err13misc1
 *
 * RAS Error Record 13 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err13misc1
{
    uint64_t u;
    struct bdk_rasx_err13misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err13misc1_s cn; */
};
typedef union bdk_rasx_err13misc1 bdk_rasx_err13misc1_t;

static inline uint64_t BDK_RASX_ERR13MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR13MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050368ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050368ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050368ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050368ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR13MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR13MISC1(a) bdk_rasx_err13misc1_t
#define bustype_BDK_RASX_ERR13MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR13MISC1(a) "RASX_ERR13MISC1"
#define busnum_BDK_RASX_ERR13MISC1(a) (a)
#define arguments_BDK_RASX_ERR13MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err13status
 *
 * RAS Error Record 13 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err13status
{
    uint64_t u;
    struct bdk_rasx_err13status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err13status_s cn9; */
    /* struct bdk_rasx_err13status_s cn96xxp1; */
    struct bdk_rasx_err13status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err13status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err13status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err13status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err13status bdk_rasx_err13status_t;

static inline uint64_t BDK_RASX_ERR13STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR13STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050350ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050350ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050350ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050350ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR13STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR13STATUS(a) bdk_rasx_err13status_t
#define bustype_BDK_RASX_ERR13STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR13STATUS(a) "RASX_ERR13STATUS"
#define busnum_BDK_RASX_ERR13STATUS(a) (a)
#define arguments_BDK_RASX_ERR13STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err14addr
 *
 * RAS Error Record 14 Address Register
 * See RAS()_ERR09ADDR.
 */
union bdk_rasx_err14addr
{
    uint64_t u;
    struct bdk_rasx_err14addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) See RAS()_ERR09ADDR[NSE]. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) See RAS()_ERR09ADDR[SI]. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) See RAS()_ERR09ADDR[AI]. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) See RAS()_ERR09ADDR[PADDR]. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) See RAS()_ERR09ADDR[PADDR]. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) See RAS()_ERR09ADDR[AI]. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) See RAS()_ERR09ADDR[SI]. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) See RAS()_ERR09ADDR[NSE]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err14addr_s cn; */
};
typedef union bdk_rasx_err14addr bdk_rasx_err14addr_t;

static inline uint64_t BDK_RASX_ERR14ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR14ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050398ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050398ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050398ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050398ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR14ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR14ADDR(a) bdk_rasx_err14addr_t
#define bustype_BDK_RASX_ERR14ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR14ADDR(a) "RASX_ERR14ADDR"
#define busnum_BDK_RASX_ERR14ADDR(a) (a)
#define arguments_BDK_RASX_ERR14ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err14ctlr
 *
 * RAS Error Record 14 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err14ctlr
{
    uint64_t u;
    struct bdk_rasx_err14ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err14ctlr_s cn9; */
    /* struct bdk_rasx_err14ctlr_s cn96xxp1; */
    struct bdk_rasx_err14ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err14ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err14ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err14ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err14ctlr bdk_rasx_err14ctlr_t;

static inline uint64_t BDK_RASX_ERR14CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR14CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050388ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050388ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050388ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050388ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR14CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR14CTLR(a) bdk_rasx_err14ctlr_t
#define bustype_BDK_RASX_ERR14CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR14CTLR(a) "RASX_ERR14CTLR"
#define busnum_BDK_RASX_ERR14CTLR(a) (a)
#define arguments_BDK_RASX_ERR14CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err14fr
 *
 * RAS Error Record 14 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err14fr
{
    uint64_t u;
    struct bdk_rasx_err14fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err14fr_s cn9; */
    /* struct bdk_rasx_err14fr_s cn96xxp1; */
    struct bdk_rasx_err14fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err14fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err14fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err14fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err14fr bdk_rasx_err14fr_t;

static inline uint64_t BDK_RASX_ERR14FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR14FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050380ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050380ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050380ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050380ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR14FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR14FR(a) bdk_rasx_err14fr_t
#define bustype_BDK_RASX_ERR14FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR14FR(a) "RASX_ERR14FR"
#define busnum_BDK_RASX_ERR14FR(a) (a)
#define arguments_BDK_RASX_ERR14FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err14misc0
 *
 * RAS Error Record 14 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err14misc0
{
    uint64_t u;
    struct bdk_rasx_err14misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_8_31         : 24;
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
#else /* Word 0 - Little Endian */
        uint64_t imp_way               : 8;  /**< [  7:  0](SR/W) The way number with the error. */
        uint64_t reserved_8_31         : 24;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err14misc0_s cn; */
};
typedef union bdk_rasx_err14misc0 bdk_rasx_err14misc0_t;

static inline uint64_t BDK_RASX_ERR14MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR14MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080503a0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080503a0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080503a0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080503a0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR14MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR14MISC0(a) bdk_rasx_err14misc0_t
#define bustype_BDK_RASX_ERR14MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR14MISC0(a) "RASX_ERR14MISC0"
#define busnum_BDK_RASX_ERR14MISC0(a) (a)
#define arguments_BDK_RASX_ERR14MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err14misc1
 *
 * RAS Error Record 14 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err14misc1
{
    uint64_t u;
    struct bdk_rasx_err14misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err14misc1_s cn; */
};
typedef union bdk_rasx_err14misc1 bdk_rasx_err14misc1_t;

static inline uint64_t BDK_RASX_ERR14MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR14MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080503a8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080503a8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080503a8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080503a8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR14MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR14MISC1(a) bdk_rasx_err14misc1_t
#define bustype_BDK_RASX_ERR14MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR14MISC1(a) "RASX_ERR14MISC1"
#define busnum_BDK_RASX_ERR14MISC1(a) (a)
#define arguments_BDK_RASX_ERR14MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err14status
 *
 * RAS Error Record 14 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err14status
{
    uint64_t u;
    struct bdk_rasx_err14status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err14status_s cn9; */
    /* struct bdk_rasx_err14status_s cn96xxp1; */
    struct bdk_rasx_err14status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err14status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err14status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err14status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err14status bdk_rasx_err14status_t;

static inline uint64_t BDK_RASX_ERR14STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR14STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050390ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050390ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050390ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050390ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR14STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR14STATUS(a) bdk_rasx_err14status_t
#define bustype_BDK_RASX_ERR14STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR14STATUS(a) "RASX_ERR14STATUS"
#define busnum_BDK_RASX_ERR14STATUS(a) (a)
#define arguments_BDK_RASX_ERR14STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err15addr
 *
 * RAS Error Record 15 Address Register
 * See RAS()_ERR00ADDR.
 */
union bdk_rasx_err15addr
{
    uint64_t u;
    struct bdk_rasx_err15addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](SR/W) Physical address. For CNXXXX, \<55:51\> are read-only 0x0. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](SR/W) Address incomplete or incorrect.
                                                                 0 = [PADDR] is correct. That is, it matches the programmers' view of the
                                                                 physical address for this recorded location.
                                                                 1 = [PADDR] might not be correct. */
        uint64_t si                    : 1;  /**< [ 62: 62](SR/W) Secure incorrect.
                                                                 0 = [NS] is correct. That is, it matches the programmers' view of the nonsecure
                                                                 attribute for this recorded location.
                                                                 1 = [NS] might not be correct. */
        uint64_t nse                   : 1;  /**< [ 63: 63](SR/W) Nonsecure.
                                                                 0 = The physical address is secure.
                                                                 1 = The physical address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err15addr_s cn; */
};
typedef union bdk_rasx_err15addr bdk_rasx_err15addr_t;

static inline uint64_t BDK_RASX_ERR15ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR15ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080503d8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080503d8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080503d8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080503d8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR15ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR15ADDR(a) bdk_rasx_err15addr_t
#define bustype_BDK_RASX_ERR15ADDR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR15ADDR(a) "RASX_ERR15ADDR"
#define busnum_BDK_RASX_ERR15ADDR(a) (a)
#define arguments_BDK_RASX_ERR15ADDR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err15ctlr
 *
 * RAS Error Record 15 Control Register
 * See RAS()_ERR00CTLR.
 */
union bdk_rasx_err15ctlr
{
    uint64_t u;
    struct bdk_rasx_err15ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [RU].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err15ctlr_s cn9; */
    /* struct bdk_rasx_err15ctlr_s cn96xxp1; */
    struct bdk_rasx_err15ctlr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](SR/W) See RAS()_ERR00CTLR[ED]. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](SR/W) See RAS()_ERR00CTLR[IMP_FE]. */
        uint64_t ui                    : 1;  /**< [  2:  2](SR/W) See RAS()_ERR00CTLR[UI]. */
        uint64_t fi                    : 1;  /**< [  3:  3](SR/W) See RAS()_ERR00CTLR[FI]. */
        uint64_t ue                    : 1;  /**< [  4:  4](SR/W) See RAS()_ERR00CTLR[UE]. */
        uint64_t wui                   : 1;  /**< [  5:  5](SRO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](SRO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](SRO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](SR/W) See RAS()_ERR00CTLR[CFI]. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](SRO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](SR/W) See RAS()_ERR00CTLR[DUI]. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](SRO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err15ctlr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err15ctlr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err15ctlr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err15ctlr bdk_rasx_err15ctlr_t;

static inline uint64_t BDK_RASX_ERR15CTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR15CTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080503c8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080503c8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080503c8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080503c8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR15CTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR15CTLR(a) bdk_rasx_err15ctlr_t
#define bustype_BDK_RASX_ERR15CTLR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR15CTLR(a) "RASX_ERR15CTLR"
#define busnum_BDK_RASX_ERR15CTLR(a) (a)
#define arguments_BDK_RASX_ERR15CTLR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err15fr
 *
 * RAS Error Record 15 Feature Register
 * See RAS()_ERR00FR.
 * Internal:
 * If adding/removing records, update RAS()_ERRDEVID[NUM].
 */
union bdk_rasx_err15fr
{
    uint64_t u;
    struct bdk_rasx_err15fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err15fr_s cn9; */
    /* struct bdk_rasx_err15fr_s cn96xxp1; */
    struct bdk_rasx_err15fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](SRO) See RAS()_ERR00FR[ED]. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](SRO) See RAS()_ERR00FR[IMP_FE]. */
        uint64_t ui                    : 2;  /**< [  5:  4](SRO) See RAS()_ERR00FR[UI]. */
        uint64_t fi                    : 2;  /**< [  7:  6](SRO) See RAS()_ERR00FR[FI]. */
        uint64_t ue                    : 2;  /**< [  9:  8](SRO) See RAS()_ERR00FR[UE]. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](SRO) See RAS()_ERR00FR[CFI]. */
        uint64_t cec                   : 3;  /**< [ 14: 12](SRO) See RAS()_ERR00FR[CEC]. */
        uint64_t rp                    : 1;  /**< [ 15: 15](SRO) See RAS()_ERR00FR[RP]. */
        uint64_t dui                   : 2;  /**< [ 17: 16](SRO) See RAS()_ERR00FR[DUI]. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](SRO) See RAS()_ERR00FR[CEO]. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err15fr_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err15fr_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err15fr_cn96xxp3 loki; */
};
typedef union bdk_rasx_err15fr bdk_rasx_err15fr_t;

static inline uint64_t BDK_RASX_ERR15FR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR15FR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080503c0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080503c0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080503c0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080503c0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR15FR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR15FR(a) bdk_rasx_err15fr_t
#define bustype_BDK_RASX_ERR15FR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR15FR(a) "RASX_ERR15FR"
#define busnum_BDK_RASX_ERR15FR(a) (a)
#define arguments_BDK_RASX_ERR15FR(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err15misc0
 *
 * RAS Error Record 15 Miscellaneous 0 Register
 * See RAS()_ERR00MISC0.
 */
union bdk_rasx_err15misc0
{
    uint64_t u;
    struct bdk_rasx_err15misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t cec                   : 15; /**< [ 46: 32](SRO) See RAS()_ERR00MISC0[CEC]. */
        uint64_t of                    : 1;  /**< [ 47: 47](SRO) See RAS()_ERR00MISC0[OF]. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err15misc0_s cn; */
};
typedef union bdk_rasx_err15misc0 bdk_rasx_err15misc0_t;

static inline uint64_t BDK_RASX_ERR15MISC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR15MISC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080503e0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080503e0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080503e0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080503e0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR15MISC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR15MISC0(a) bdk_rasx_err15misc0_t
#define bustype_BDK_RASX_ERR15MISC0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR15MISC0(a) "RASX_ERR15MISC0"
#define busnum_BDK_RASX_ERR15MISC0(a) (a)
#define arguments_BDK_RASX_ERR15MISC0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err15misc1
 *
 * RAS Error Record 15 Miscellaneous 1 Register
 * See RAS()_ERR00MISC1.
 */
union bdk_rasx_err15misc1
{
    uint64_t u;
    struct bdk_rasx_err15misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err15misc1_s cn; */
};
typedef union bdk_rasx_err15misc1 bdk_rasx_err15misc1_t;

static inline uint64_t BDK_RASX_ERR15MISC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR15MISC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080503e8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080503e8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080503e8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080503e8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR15MISC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR15MISC1(a) bdk_rasx_err15misc1_t
#define bustype_BDK_RASX_ERR15MISC1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR15MISC1(a) "RASX_ERR15MISC1"
#define busnum_BDK_RASX_ERR15MISC1(a) (a)
#define arguments_BDK_RASX_ERR15MISC1(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_err15status
 *
 * RAS Error Record 15 Primary Syndrome Register
 * See RAS()_ERR00STATUS.
 */
union bdk_rasx_err15status
{
    uint64_t u;
    struct bdk_rasx_err15status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OV]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_err15status_s cn9; */
    /* struct bdk_rasx_err15status_s cn96xxp1; */
    struct bdk_rasx_err15status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](SR/W) See RAS()_ERR00STATUS[SERR]. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](SR/W) See RAS()_ERR00STATUS[IERR]. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](SR/W1C/H) See RAS()_ERR00STATUS[UET]. */
        uint64_t pn                    : 1;  /**< [ 22: 22](SR/W1C/H) See RAS()_ERR00STATUS[PN]. */
        uint64_t de                    : 1;  /**< [ 23: 23](SR/W1C/H) See RAS()_ERR00STATUS[DE]. */
        uint64_t ce                    : 2;  /**< [ 25: 24](SR/W1C/H) See RAS()_ERR00STATUS[CE]. */
        uint64_t mv                    : 1;  /**< [ 26: 26](SR/W1C/H) See RAS()_ERR00STATUS[MV]. */
        uint64_t of                    : 1;  /**< [ 27: 27](SR/W1C/H) See RAS()_ERR00STATUS[OF]. */
        uint64_t er                    : 1;  /**< [ 28: 28](SR/W1C/H) See RAS()_ERR00STATUS[ER]. */
        uint64_t ue                    : 1;  /**< [ 29: 29](SR/W1C/H) See RAS()_ERR00STATUS[UE]. */
        uint64_t v                     : 1;  /**< [ 30: 30](SR/W1C/H) See RAS()_ERR00STATUS[V]. */
        uint64_t av                    : 1;  /**< [ 31: 31](SR/W1C/H) See RAS()_ERR00STATUS[AV]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_err15status_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_err15status_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_err15status_cn96xxp3 loki; */
};
typedef union bdk_rasx_err15status bdk_rasx_err15status_t;

static inline uint64_t BDK_RASX_ERR15STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERR15STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080503d0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080503d0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080503d0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080503d0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERR15STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERR15STATUS(a) bdk_rasx_err15status_t
#define bustype_BDK_RASX_ERR15STATUS(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERR15STATUS(a) "RASX_ERR15STATUS"
#define busnum_BDK_RASX_ERR15STATUS(a) (a)
#define arguments_BDK_RASX_ERR15STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_errdevaff
 *
 * RAS Device Affinity Register
 * For a group that has an affinity to a PE or cluster of PEs, this register is a
 * read-only copy of AP_MPIDR_EL1.
 */
union bdk_rasx_errdevaff
{
    uint64_t u;
    struct bdk_rasx_errdevaff_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t aff3                  : 8;  /**< [ 39: 32](SRO) Reserved. */
        uint64_t fov                   : 1;  /**< [ 31: 31](SRO) If set, the [AFF0] fields are valid.
                                                                 For noncore RAS blocks, this is zero and all other fields are zero. */
        uint64_t u                     : 1;  /**< [ 30: 30](SRO) Set to indicate processor is part of a multiprocessor system. */
        uint64_t reserved_25_29        : 5;
        uint64_t mt                    : 1;  /**< [ 24: 24](SRO) Set to indicate multithreaded, and [AFF0] is thread number in core. */
        uint64_t aff2                  : 8;  /**< [ 23: 16](SRO/H) Affinity 2. In CNXXXX, the node id. */
        uint64_t aff1                  : 8;  /**< [ 15:  8](SRO/H) Affinity 1. In CNXXXX, the cluster id within a node. */
        uint64_t aff0                  : 8;  /**< [  7:  0](SRO/H) Affinity 0. In CNXXXX, the core number within a cluster. */
#else /* Word 0 - Little Endian */
        uint64_t aff0                  : 8;  /**< [  7:  0](SRO/H) Affinity 0. In CNXXXX, the core number within a cluster. */
        uint64_t aff1                  : 8;  /**< [ 15:  8](SRO/H) Affinity 1. In CNXXXX, the cluster id within a node. */
        uint64_t aff2                  : 8;  /**< [ 23: 16](SRO/H) Affinity 2. In CNXXXX, the node id. */
        uint64_t mt                    : 1;  /**< [ 24: 24](SRO) Set to indicate multithreaded, and [AFF0] is thread number in core. */
        uint64_t reserved_25_29        : 5;
        uint64_t u                     : 1;  /**< [ 30: 30](SRO) Set to indicate processor is part of a multiprocessor system. */
        uint64_t fov                   : 1;  /**< [ 31: 31](SRO) If set, the [AFF0] fields are valid.
                                                                 For noncore RAS blocks, this is zero and all other fields are zero. */
        uint64_t aff3                  : 8;  /**< [ 39: 32](SRO) Reserved. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_errdevaff_s cn; */
};
typedef union bdk_rasx_errdevaff bdk_rasx_errdevaff_t;

static inline uint64_t BDK_RASX_ERRDEVAFF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERRDEVAFF(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fa8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fa8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fa8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fa8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERRDEVAFF", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERRDEVAFF(a) bdk_rasx_errdevaff_t
#define bustype_BDK_RASX_ERRDEVAFF(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERRDEVAFF(a) "RASX_ERRDEVAFF"
#define busnum_BDK_RASX_ERRDEVAFF(a) (a)
#define arguments_BDK_RASX_ERRDEVAFF(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_errdevarch
 *
 * RAS Device Architecture Register
 * This register identifies the programmers' model architecture of the component.
 */
union bdk_rasx_errdevarch
{
    uint32_t u;
    struct bdk_rasx_errdevarch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](SRO) Defines the architecture of the component. Indicates ARM. */
        uint32_t present               : 1;  /**< [ 20: 20](SRO) When set to 1, indicates that this register is present. */
        uint32_t revision              : 4;  /**< [ 19: 16](SRO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archver               : 4;  /**< [ 15: 12](SRO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archpart              : 12; /**< [ 11:  0](SRO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
#else /* Word 0 - Little Endian */
        uint32_t archpart              : 12; /**< [ 11:  0](SRO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
        uint32_t archver               : 4;  /**< [ 15: 12](SRO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t revision              : 4;  /**< [ 19: 16](SRO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t present               : 1;  /**< [ 20: 20](SRO) When set to 1, indicates that this register is present. */
        uint32_t architect             : 11; /**< [ 31: 21](SRO) Defines the architecture of the component. Indicates ARM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_errdevarch_s cn9; */
    /* struct bdk_rasx_errdevarch_s cn96xxp1; */
    struct bdk_rasx_errdevarch_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](SRO) Defines the architecture of the component. Indicates Arm. */
        uint32_t present               : 1;  /**< [ 20: 20](SRO) When set to 1, indicates that this register is present. */
        uint32_t revision              : 4;  /**< [ 19: 16](SRO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archver               : 4;  /**< [ 15: 12](SRO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archpart              : 12; /**< [ 11:  0](SRO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
#else /* Word 0 - Little Endian */
        uint32_t archpart              : 12; /**< [ 11:  0](SRO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
        uint32_t archver               : 4;  /**< [ 15: 12](SRO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t revision              : 4;  /**< [ 19: 16](SRO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t present               : 1;  /**< [ 20: 20](SRO) When set to 1, indicates that this register is present. */
        uint32_t architect             : 11; /**< [ 31: 21](SRO) Defines the architecture of the component. Indicates Arm. */
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_errdevarch_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_errdevarch_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_errdevarch_cn96xxp3 loki; */
};
typedef union bdk_rasx_errdevarch bdk_rasx_errdevarch_t;

static inline uint64_t BDK_RASX_ERRDEVARCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERRDEVARCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fbcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fbcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fbcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fbcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERRDEVARCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERRDEVARCH(a) bdk_rasx_errdevarch_t
#define bustype_BDK_RASX_ERRDEVARCH(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_ERRDEVARCH(a) "RASX_ERRDEVARCH"
#define busnum_BDK_RASX_ERRDEVARCH(a) (a)
#define arguments_BDK_RASX_ERRDEVARCH(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_errdevid
 *
 * RAS Error Record ID Register
 * Defines the highest numbered index of the error records that can be accessed
 * through the Error Record registers.
 */
union bdk_rasx_errdevid
{
    uint32_t u;
    struct bdk_rasx_errdevid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t num                   : 16; /**< [ 15:  0](SRO) Highest numbered index of the error records that can be accessed. */
#else /* Word 0 - Little Endian */
        uint32_t num                   : 16; /**< [ 15:  0](SRO) Highest numbered index of the error records that can be accessed. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_errdevid_s cn; */
};
typedef union bdk_rasx_errdevid bdk_rasx_errdevid_t;

static inline uint64_t BDK_RASX_ERRDEVID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERRDEVID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fc8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fc8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fc8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fc8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERRDEVID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERRDEVID(a) bdk_rasx_errdevid_t
#define bustype_BDK_RASX_ERRDEVID(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_ERRDEVID(a) "RASX_ERRDEVID"
#define busnum_BDK_RASX_ERRDEVID(a) (a)
#define arguments_BDK_RASX_ERRDEVID(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_errfhicr0
 *
 * RAS Error Interrupt Configuration Register 0
 * This register configures interrupt delivery.
 */
union bdk_rasx_errfhicr0
{
    uint64_t u;
    struct bdk_rasx_errfhicr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](SR/W) Message Signaled Interrupt IOVA. Specifies the address that the node writes to
                                                                 signal an interrupt. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 51; /**< [ 52:  2](SR/W) Message Signaled Interrupt IOVA. Specifies the address that the node writes to
                                                                 signal an interrupt. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_errfhicr0_s cn; */
};
typedef union bdk_rasx_errfhicr0 bdk_rasx_errfhicr0_t;

static inline uint64_t BDK_RASX_ERRFHICR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERRFHICR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050e80ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050e80ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050e80ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050e80ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERRFHICR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERRFHICR0(a) bdk_rasx_errfhicr0_t
#define bustype_BDK_RASX_ERRFHICR0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERRFHICR0(a) "RASX_ERRFHICR0"
#define busnum_BDK_RASX_ERRFHICR0(a) (a)
#define arguments_BDK_RASX_ERRFHICR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_errfhicr1
 *
 * RAS Error Interrupt Configuration Register 1
 * This register configures interrupt delivery.
 */
union bdk_rasx_errfhicr1
{
    uint32_t u;
    struct bdk_rasx_errfhicr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](SR/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](SR/W) Data to use for MSI-X delivery of this vector. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_errfhicr1_s cn; */
};
typedef union bdk_rasx_errfhicr1 bdk_rasx_errfhicr1_t;

static inline uint64_t BDK_RASX_ERRFHICR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERRFHICR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050e88ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050e88ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050e88ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050e88ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERRFHICR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERRFHICR1(a) bdk_rasx_errfhicr1_t
#define bustype_BDK_RASX_ERRFHICR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_ERRFHICR1(a) "RASX_ERRFHICR1"
#define busnum_BDK_RASX_ERRFHICR1(a) (a)
#define arguments_BDK_RASX_ERRFHICR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_errfhicr2
 *
 * RAS Error Interrupt Configuration Register 0
 * This register configures interrupt delivery.
 */
union bdk_rasx_errfhicr2
{
    uint32_t u;
    struct bdk_rasx_errfhicr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t msien                 : 1;  /**< [  7:  7](SR/W) This bit enables message-signaled sending of interrupts. */
        uint32_t nsmsi                 : 1;  /**< [  6:  6](SR/W) This bit is an optional extension for Secure-only error records.
                                                                 It provides the nonsecure attribute for the MSI.
                                                                   0 = Secure.
                                                                   1 = Nonsecure. */
        uint32_t sh                    : 2;  /**< [  5:  4](SRO) Shareability. Defines the shareability domain for message signaled interrupts.
                                                                 This field is RES0 if the ETR does not support configuring the shareability domain.
                                                                   0x0 = Not shared.
                                                                   0x2 = Outer shareable.
                                                                   0x3 = Inner shareable.

                                                                 In CNXXXX, ignored. */
        uint32_t memattr               : 4;  /**< [  3:  0](SRO) MSI-X memory attributes. In CNXXXX, ignored.
                                                                 This field is RES0 if RAS does not support configuring the shareability domain. */
#else /* Word 0 - Little Endian */
        uint32_t memattr               : 4;  /**< [  3:  0](SRO) MSI-X memory attributes. In CNXXXX, ignored.
                                                                 This field is RES0 if RAS does not support configuring the shareability domain. */
        uint32_t sh                    : 2;  /**< [  5:  4](SRO) Shareability. Defines the shareability domain for message signaled interrupts.
                                                                 This field is RES0 if the ETR does not support configuring the shareability domain.
                                                                   0x0 = Not shared.
                                                                   0x2 = Outer shareable.
                                                                   0x3 = Inner shareable.

                                                                 In CNXXXX, ignored. */
        uint32_t nsmsi                 : 1;  /**< [  6:  6](SR/W) This bit is an optional extension for Secure-only error records.
                                                                 It provides the nonsecure attribute for the MSI.
                                                                   0 = Secure.
                                                                   1 = Nonsecure. */
        uint32_t msien                 : 1;  /**< [  7:  7](SR/W) This bit enables message-signaled sending of interrupts. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_errfhicr2_s cn; */
};
typedef union bdk_rasx_errfhicr2 bdk_rasx_errfhicr2_t;

static inline uint64_t BDK_RASX_ERRFHICR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERRFHICR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050e8cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050e8cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050e8cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050e8cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERRFHICR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERRFHICR2(a) bdk_rasx_errfhicr2_t
#define bustype_BDK_RASX_ERRFHICR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_ERRFHICR2(a) "RASX_ERRFHICR2"
#define busnum_BDK_RASX_ERRFHICR2(a) (a)
#define arguments_BDK_RASX_ERRFHICR2(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_errgsr0
 *
 * RAS Error Group Status Register
 * This register shows the status for the records in the group.
 */
union bdk_rasx_errgsr0
{
    uint64_t u;
    struct bdk_rasx_errgsr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t s                     : 64; /**< [ 63:  0](SRO/H) Shows the status for the records, a read-only copy of CER_ERR()_STATUS[V]:
                                                                    0 = No error.
                                                                    1 = One or more errors.

                                                                 Each bit corresponds to the status for 64 records, in groups of
                                                                 64 determined by the address index to this register.

                                                                 Bits above the maximum implemented index number (RAS()_ERRDEVID[NUM]) are 0. */
#else /* Word 0 - Little Endian */
        uint64_t s                     : 64; /**< [ 63:  0](SRO/H) Shows the status for the records, a read-only copy of CER_ERR()_STATUS[V]:
                                                                    0 = No error.
                                                                    1 = One or more errors.

                                                                 Each bit corresponds to the status for 64 records, in groups of
                                                                 64 determined by the address index to this register.

                                                                 Bits above the maximum implemented index number (RAS()_ERRDEVID[NUM]) are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_errgsr0_s cn; */
};
typedef union bdk_rasx_errgsr0 bdk_rasx_errgsr0_t;

static inline uint64_t BDK_RASX_ERRGSR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERRGSR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050e00ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050e00ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050e00ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050e00ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERRGSR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERRGSR0(a) bdk_rasx_errgsr0_t
#define bustype_BDK_RASX_ERRGSR0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERRGSR0(a) "RASX_ERRGSR0"
#define busnum_BDK_RASX_ERRGSR0(a) (a)
#define arguments_BDK_RASX_ERRGSR0(a) (a),-1,-1,-1

/**
 * Register (DAB) ras#_errirqsr
 *
 * RAS Error Interrupt Status Register
 * This register uses the recommended Arm interrupt configuration register format.
 */
union bdk_rasx_errirqsr
{
    uint64_t u;
    struct bdk_rasx_errirqsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t erierr                : 1;  /**< [  3:  3](SRO) Error recovery interrupt error.
                                                                 0 = Error recovery interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Error recovery interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t eri                   : 1;  /**< [  2:  2](SRO/H) Error recovery interrupt write in progress.
                                                                 0 = Error recovery interrupt write not in progress.
                                                                 1 = Error recovery interrupt write in progress.

                                                                 In CNXXXX, reads same as [FHI].

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
        uint64_t fhierr                : 1;  /**< [  1:  1](SRO) Fault handling interrupt error.
                                                                 0 = Fault handling interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Fault handling interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t fhi                   : 1;  /**< [  0:  0](SRO/H) Fault handling interrupt write in progress.
                                                                 0 = Fault handling interrupt write not in progress.
                                                                 1 = Fault handling interrupt write in progress.

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
#else /* Word 0 - Little Endian */
        uint64_t fhi                   : 1;  /**< [  0:  0](SRO/H) Fault handling interrupt write in progress.
                                                                 0 = Fault handling interrupt write not in progress.
                                                                 1 = Fault handling interrupt write in progress.

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
        uint64_t fhierr                : 1;  /**< [  1:  1](SRO) Fault handling interrupt error.
                                                                 0 = Fault handling interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Fault handling interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t eri                   : 1;  /**< [  2:  2](SRO/H) Error recovery interrupt write in progress.
                                                                 0 = Error recovery interrupt write not in progress.
                                                                 1 = Error recovery interrupt write in progress.

                                                                 In CNXXXX, reads same as [FHI].

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
        uint64_t erierr                : 1;  /**< [  3:  3](SRO) Error recovery interrupt error.
                                                                 0 = Error recovery interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Error recovery interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_errirqsr_s cn; */
};
typedef union bdk_rasx_errirqsr bdk_rasx_errirqsr_t;

static inline uint64_t BDK_RASX_ERRIRQSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_ERRIRQSR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050ef8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050ef8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050ef8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050ef8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_ERRIRQSR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_ERRIRQSR(a) bdk_rasx_errirqsr_t
#define bustype_BDK_RASX_ERRIRQSR(a) BDK_CSR_TYPE_DAB
#define basename_BDK_RASX_ERRIRQSR(a) "RASX_ERRIRQSR"
#define busnum_BDK_RASX_ERRIRQSR(a) (a)
#define arguments_BDK_RASX_ERRIRQSR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_pidr0
 *
 * RAS Peripheral Identification Register 0
 * This register provides information to identify a debug component.
 */
union bdk_rasx_pidr0
{
    uint32_t u;
    struct bdk_rasx_pidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::RAS.

                                                                 Internal:
                                                                 This value needs to change when used in different blocks. */
#else /* Word 0 - Little Endian */
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::RAS.

                                                                 Internal:
                                                                 This value needs to change when used in different blocks. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_pidr0_s cn; */
};
typedef union bdk_rasx_pidr0 bdk_rasx_pidr0_t;

static inline uint64_t BDK_RASX_PIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_PIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fe0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fe0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fe0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fe0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_PIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_PIDR0(a) bdk_rasx_pidr0_t
#define bustype_BDK_RASX_PIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_PIDR0(a) "RASX_PIDR0"
#define busnum_BDK_RASX_PIDR0(a) (a)
#define arguments_BDK_RASX_PIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_pidr1
 *
 * RAS Peripheral Identification Register 1
 * This register provides information to identify a debug component.
 */
union bdk_rasx_pidr1
{
    uint32_t u;
    struct bdk_rasx_pidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Cavium code is 0x4C. */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
#else /* Word 0 - Little Endian */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Cavium code is 0x4C. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_pidr1_s cn9; */
    /* struct bdk_rasx_pidr1_s cn96xxp1; */
    struct bdk_rasx_pidr1_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Marvell (Cavium) code is 0x4C. */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
#else /* Word 0 - Little Endian */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Marvell (Cavium) code is 0x4C. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_pidr1_cn96xxp3 cn98xx; */
    /* struct bdk_rasx_pidr1_cn96xxp3 cnf95xx; */
    /* struct bdk_rasx_pidr1_cn96xxp3 loki; */
};
typedef union bdk_rasx_pidr1 bdk_rasx_pidr1_t;

static inline uint64_t BDK_RASX_PIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_PIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fe4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fe4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fe4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fe4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_PIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_PIDR1(a) bdk_rasx_pidr1_t
#define bustype_BDK_RASX_PIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_PIDR1(a) "RASX_PIDR1"
#define busnum_BDK_RASX_PIDR1(a) (a)
#define arguments_BDK_RASX_PIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_pidr2
 *
 * RAS Peripheral Identification Register 2
 * This register provides information to identify a debug component.
 */
union bdk_rasx_pidr2
{
    uint32_t u;
    struct bdk_rasx_pidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) Implementation-defined RAS revision. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Implementation-defined RAS revision. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_pidr2_s cn9; */
    /* struct bdk_rasx_pidr2_s cn96xxp1; */
    struct bdk_rasx_pidr2_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) Implementation-defined RAS revision. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Marvell (Cavium) code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Marvell (Cavium) code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Implementation-defined RAS revision. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_pidr2_s cn98xx; */
    /* struct bdk_rasx_pidr2_s cnf95xxp1; */
    /* struct bdk_rasx_pidr2_cn96xxp3 cnf95xxp2; */
    /* struct bdk_rasx_pidr2_cn96xxp3 loki; */
};
typedef union bdk_rasx_pidr2 bdk_rasx_pidr2_t;

static inline uint64_t BDK_RASX_PIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_PIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fe8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fe8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fe8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fe8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_PIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_PIDR2(a) bdk_rasx_pidr2_t
#define bustype_BDK_RASX_PIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_PIDR2(a) "RASX_PIDR2"
#define busnum_BDK_RASX_PIDR2(a) (a)
#define arguments_BDK_RASX_PIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_pidr3
 *
 * RAS Peripheral Identification Register 3
 * This register provides information to identify a debug component.
 */
union bdk_rasx_pidr3
{
    uint32_t u;
    struct bdk_rasx_pidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer modified. 0x1 = Overall product information should be consulted for
                                                                 product, major and minor pass numbers. */
#else /* Word 0 - Little Endian */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer modified. 0x1 = Overall product information should be consulted for
                                                                 product, major and minor pass numbers. */
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_pidr3_s cn; */
};
typedef union bdk_rasx_pidr3 bdk_rasx_pidr3_t;

static inline uint64_t BDK_RASX_PIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_PIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fecll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fecll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fecll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fecll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_PIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_PIDR3(a) bdk_rasx_pidr3_t
#define bustype_BDK_RASX_PIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_PIDR3(a) "RASX_PIDR3"
#define busnum_BDK_RASX_PIDR3(a) (a)
#define arguments_BDK_RASX_PIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_pidr4
 *
 * RAS Peripheral Identification Register 4
 * This register provides information to identify a debug component.
 */
union bdk_rasx_pidr4
{
    uint32_t u;
    struct bdk_rasx_pidr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t fourkbcount           : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4 KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t jep106cont            : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
#else /* Word 0 - Little Endian */
        uint32_t jep106cont            : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
        uint32_t fourkbcount           : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4 KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_pidr4_s cn9; */
    /* struct bdk_rasx_pidr4_s cn96xxp1; */
    struct bdk_rasx_pidr4_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t fourkbcount           : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4 KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t jep106cont            : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Marvell (Cavium). */
#else /* Word 0 - Little Endian */
        uint32_t jep106cont            : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Marvell (Cavium). */
        uint32_t fourkbcount           : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4 KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rasx_pidr4_s cn98xx; */
    /* struct bdk_rasx_pidr4_s cnf95xxp1; */
    /* struct bdk_rasx_pidr4_cn96xxp3 cnf95xxp2; */
    /* struct bdk_rasx_pidr4_cn96xxp3 loki; */
};
typedef union bdk_rasx_pidr4 bdk_rasx_pidr4_t;

static inline uint64_t BDK_RASX_PIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_PIDR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fd0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fd0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fd0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fd0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_PIDR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_PIDR4(a) bdk_rasx_pidr4_t
#define bustype_BDK_RASX_PIDR4(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_PIDR4(a) "RASX_PIDR4"
#define busnum_BDK_RASX_PIDR4(a) (a)
#define arguments_BDK_RASX_PIDR4(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_pidr5
 *
 * RAS Peripheral Identification Register 5
 * This register provides information to identify a debug component.
 */
union bdk_rasx_pidr5
{
    uint32_t u;
    struct bdk_rasx_pidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_pidr5_s cn; */
};
typedef union bdk_rasx_pidr5 bdk_rasx_pidr5_t;

static inline uint64_t BDK_RASX_PIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_PIDR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fd4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fd4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fd4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fd4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_PIDR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_PIDR5(a) bdk_rasx_pidr5_t
#define bustype_BDK_RASX_PIDR5(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_PIDR5(a) "RASX_PIDR5"
#define busnum_BDK_RASX_PIDR5(a) (a)
#define arguments_BDK_RASX_PIDR5(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_pidr6
 *
 * RAS Peripheral Identification Register 6
 * This register provides information to identify a debug component.
 */
union bdk_rasx_pidr6
{
    uint32_t u;
    struct bdk_rasx_pidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_pidr6_s cn; */
};
typedef union bdk_rasx_pidr6 bdk_rasx_pidr6_t;

static inline uint64_t BDK_RASX_PIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_PIDR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fd8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fd8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fd8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fd8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_PIDR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_PIDR6(a) bdk_rasx_pidr6_t
#define bustype_BDK_RASX_PIDR6(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_PIDR6(a) "RASX_PIDR6"
#define busnum_BDK_RASX_PIDR6(a) (a)
#define arguments_BDK_RASX_PIDR6(a) (a),-1,-1,-1

/**
 * Register (DAB32b) ras#_pidr7
 *
 * RAS Peripheral Identification Register 7
 * This register provides information to identify a debug component.
 */
union bdk_rasx_pidr7
{
    uint32_t u;
    struct bdk_rasx_pidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rasx_pidr7_s cn; */
};
typedef union bdk_rasx_pidr7 bdk_rasx_pidr7_t;

static inline uint64_t BDK_RASX_PIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RASX_PIDR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008050fdcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008050fdcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008050fdcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008050fdcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("RASX_PIDR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RASX_PIDR7(a) bdk_rasx_pidr7_t
#define bustype_BDK_RASX_PIDR7(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_RASX_PIDR7(a) "RASX_PIDR7"
#define busnum_BDK_RASX_PIDR7(a) (a)
#define arguments_BDK_RASX_PIDR7(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_DAB_RAS_H__ */
