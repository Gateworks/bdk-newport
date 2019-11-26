#ifndef __BDK_CSRS_DAB_TRC_H__
#define __BDK_CSRS_DAB_TRC_H__
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
 * OcteonTX DAB_TRC.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Register (DAB) trc#_trcacatr0
 *
 * TRC/ETM Address Comparator Access Type Register 0
 * This register defines the type of access for the corresponding TRC()_TRCACVRn. This
 * register configures the context type, exception levels, alignment and masking that
 * is applied by the address comparator and how the address comparator behaves when it
 * is one half of an address range comparator.
 */
union bdk_trcx_trcacatr0
{
    uint64_t u;
    struct bdk_trcx_trcacatr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t reserved_7            : 1;
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t reserved_7            : 1;
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcacatr0_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcacatr0_s cn9; */
};
typedef union bdk_trcx_trcacatr0 bdk_trcx_trcacatr0_t;

static inline uint64_t BDK_TRCX_TRCACATR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACATR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30480ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030480ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030480ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030480ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030480ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACATR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACATR0(a) bdk_trcx_trcacatr0_t
#define bustype_BDK_TRCX_TRCACATR0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACATR0(a) "TRCX_TRCACATR0"
#define busnum_BDK_TRCX_TRCACATR0(a) (a)
#define arguments_BDK_TRCX_TRCACATR0(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacatr1
 *
 * TRC/ETM Address Comparator Access Type Register 1
 * This register defines the type of access for the corresponding TRC()_TRCACVRn. This
 * register configures the context type, exception levels, alignment and masking that
 * is applied by the address comparator and how the address comparator behaves when it
 * is one half of an address range comparator.
 */
union bdk_trcx_trcacatr1
{
    uint64_t u;
    struct bdk_trcx_trcacatr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t reserved_7            : 1;
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t reserved_7            : 1;
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcacatr1_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcacatr1_s cn9; */
};
typedef union bdk_trcx_trcacatr1 bdk_trcx_trcacatr1_t;

static inline uint64_t BDK_TRCX_TRCACATR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACATR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30488ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030488ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030488ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030488ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030488ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACATR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACATR1(a) bdk_trcx_trcacatr1_t
#define bustype_BDK_TRCX_TRCACATR1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACATR1(a) "TRCX_TRCACATR1"
#define busnum_BDK_TRCX_TRCACATR1(a) (a)
#define arguments_BDK_TRCX_TRCACATR1(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacatr2
 *
 * TRC/ETM Address Comparator Access Type Register 2
 * This register defines the type of access for the corresponding TRC()_TRCACVRn. This
 * register configures the context type, exception levels, alignment and masking that
 * is applied by the address comparator and how the address comparator behaves when it
 * is one half of an address range comparator.
 */
union bdk_trcx_trcacatr2
{
    uint64_t u;
    struct bdk_trcx_trcacatr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t reserved_7            : 1;
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t reserved_7            : 1;
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcacatr2_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcacatr2_s cn9; */
};
typedef union bdk_trcx_trcacatr2 bdk_trcx_trcacatr2_t;

static inline uint64_t BDK_TRCX_TRCACATR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACATR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30490ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030490ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030490ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030490ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030490ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACATR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACATR2(a) bdk_trcx_trcacatr2_t
#define bustype_BDK_TRCX_TRCACATR2(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACATR2(a) "TRCX_TRCACATR2"
#define busnum_BDK_TRCX_TRCACATR2(a) (a)
#define arguments_BDK_TRCX_TRCACATR2(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacatr3
 *
 * TRC/ETM Address Comparator Access Type Register 3
 * This register defines the type of access for the corresponding TRC()_TRCACVRn. This
 * register configures the context type, exception levels, alignment and masking that
 * is applied by the address comparator and how the address comparator behaves when it
 * is one half of an address range comparator.
 */
union bdk_trcx_trcacatr3
{
    uint64_t u;
    struct bdk_trcx_trcacatr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t reserved_7            : 1;
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t reserved_7            : 1;
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcacatr3_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcacatr3_s cn9; */
};
typedef union bdk_trcx_trcacatr3 bdk_trcx_trcacatr3_t;

static inline uint64_t BDK_TRCX_TRCACATR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACATR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30498ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030498ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030498ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030498ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030498ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACATR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACATR3(a) bdk_trcx_trcacatr3_t
#define bustype_BDK_TRCX_TRCACATR3(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACATR3(a) "TRCX_TRCACATR3"
#define busnum_BDK_TRCX_TRCACATR3(a) (a)
#define arguments_BDK_TRCX_TRCACATR3(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacatr4
 *
 * TRC/ETM Address Comparator Access Type Register 4
 * Defines the type of access for the correspoding TRCACVRn register. This register configures
 * the context type, exception levels, alignment and masking that is applied bt the address
 * comparator and how the address comparator behaves when it is one half of an address range
 * comparator.
 */
union bdk_trcx_trcacatr4
{
    uint64_t u;
    struct bdk_trcx_trcacatr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t reserved_7            : 1;
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t reserved_7            : 1;
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcacatr4_s cn; */
};
typedef union bdk_trcx_trcacatr4 bdk_trcx_trcacatr4_t;

static inline uint64_t BDK_TRCX_TRCACATR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACATR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080304a0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080304a0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080304a0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080304a0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACATR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACATR4(a) bdk_trcx_trcacatr4_t
#define bustype_BDK_TRCX_TRCACATR4(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACATR4(a) "TRCX_TRCACATR4"
#define busnum_BDK_TRCX_TRCACATR4(a) (a)
#define arguments_BDK_TRCX_TRCACATR4(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacatr5
 *
 * TRC/ETM Address Comparator Access Type Register 5
 * Defines the type of access for the correspoding TRCACVRn register. This register configures
 * the context type, exception levels, alignment and masking that is applied bt the address
 * comparator and how the address comparator behaves when it is one half of an address range
 * comparator.
 */
union bdk_trcx_trcacatr5
{
    uint64_t u;
    struct bdk_trcx_trcacatr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t reserved_7            : 1;
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t reserved_7            : 1;
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcacatr5_s cn; */
};
typedef union bdk_trcx_trcacatr5 bdk_trcx_trcacatr5_t;

static inline uint64_t BDK_TRCX_TRCACATR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACATR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080304a8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080304a8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080304a8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080304a8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACATR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACATR5(a) bdk_trcx_trcacatr5_t
#define bustype_BDK_TRCX_TRCACATR5(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACATR5(a) "TRCX_TRCACATR5"
#define busnum_BDK_TRCX_TRCACATR5(a) (a)
#define arguments_BDK_TRCX_TRCACATR5(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacatr6
 *
 * TRC/ETM Address Comparator Access Type Register 6
 * Defines the type of access for the correspoding TRCACVRn register. This register configures
 * the context type, exception levels, alignment and masking that is applied bt the address
 * comparator and how the address comparator behaves when it is one half of an address range
 * comparator.
 */
union bdk_trcx_trcacatr6
{
    uint64_t u;
    struct bdk_trcx_trcacatr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t reserved_7            : 1;
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t reserved_7            : 1;
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcacatr6_s cn; */
};
typedef union bdk_trcx_trcacatr6 bdk_trcx_trcacatr6_t;

static inline uint64_t BDK_TRCX_TRCACATR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACATR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080304b0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080304b0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080304b0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080304b0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACATR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACATR6(a) bdk_trcx_trcacatr6_t
#define bustype_BDK_TRCX_TRCACATR6(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACATR6(a) "TRCX_TRCACATR6"
#define busnum_BDK_TRCX_TRCACATR6(a) (a)
#define arguments_BDK_TRCX_TRCACATR6(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacatr7
 *
 * TRC/ETM Address Comparator Access Type Register 7
 * Defines the type of access for the correspoding TRCACVRn register. This register configures
 * the context type, exception levels, alignment and masking that is applied bt the address
 * comparator and how the address comparator behaves when it is one half of an address range
 * comparator.
 */
union bdk_trcx_trcacatr7
{
    uint64_t u;
    struct bdk_trcx_trcacatr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t reserved_7            : 1;
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t comtype               : 2;  /**< [  1:  0](RAZ) Reserved. */
        uint64_t contexttype           : 2;  /**< [  3:  2](R/W) Controls the type of comparison the trace unit performs:
                                                                   0x0 = The trace unit will not perform a context ID comparison.
                                                                   0x1 = The trace unit performs a context ID comparison.
                                                                   0x2 = The trace unit performs a virtual context ID comparison.
                                                                   0x3 = The trace unit performs a context ID comparison and a virtual context ID
                                                                 comparison. */
        uint64_t contxt                : 3;  /**< [  6:  4](RAZ) Reserved. */
        uint64_t reserved_7            : 1;
        uint64_t exlevel_s             : 4;  /**< [ 11:  8](R/W) In secure state, each bit controls whether a comparison can occur for the corresponding
                                                                 exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[8] = Exception level 0.
                                                                   Bit[9] = Exception level 1.
                                                                   Bit[10] = RES0.
                                                                   Bit[11] = Exception level 3. */
        uint64_t exlevel_ns            : 4;  /**< [ 15: 12](R/W) In nonsecure state, each bit controls whether a comparison can occur for the
                                                                 corresponding exception level:
                                                                   0 = the trace unit performs a comparison for exception level n.
                                                                   1 = the trace unit does not perform a comparison for exception level n.
                                                                 The exception levels are:
                                                                   Bit[12] = Exception level 0.
                                                                   Bit[13] = Exception level 1.
                                                                   Bit[14] = Exception level 2.
                                                                   Bit[15] = RES0. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcacatr7_s cn; */
};
typedef union bdk_trcx_trcacatr7 bdk_trcx_trcacatr7_t;

static inline uint64_t BDK_TRCX_TRCACATR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACATR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080304b8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080304b8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080304b8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080304b8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACATR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACATR7(a) bdk_trcx_trcacatr7_t
#define bustype_BDK_TRCX_TRCACATR7(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACATR7(a) "TRCX_TRCACATR7"
#define busnum_BDK_TRCX_TRCACATR7(a) (a)
#define arguments_BDK_TRCX_TRCACATR7(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacvr0
 *
 * TRC/ETM Address Comparator Value Register 0
 * This register contains an address value.
 */
union bdk_trcx_trcacvr0
{
    uint64_t u;
    struct bdk_trcx_trcacvr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcacvr0_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcacvr0_s cn9; */
};
typedef union bdk_trcx_trcacvr0 bdk_trcx_trcacvr0_t;

static inline uint64_t BDK_TRCX_TRCACVR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACVR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30400ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030400ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030400ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030400ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030400ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACVR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACVR0(a) bdk_trcx_trcacvr0_t
#define bustype_BDK_TRCX_TRCACVR0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACVR0(a) "TRCX_TRCACVR0"
#define busnum_BDK_TRCX_TRCACVR0(a) (a)
#define arguments_BDK_TRCX_TRCACVR0(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacvr1
 *
 * TRC/ETM Address Comparator Value Register 1
 * This register contains an address value.
 */
union bdk_trcx_trcacvr1
{
    uint64_t u;
    struct bdk_trcx_trcacvr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcacvr1_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcacvr1_s cn9; */
};
typedef union bdk_trcx_trcacvr1 bdk_trcx_trcacvr1_t;

static inline uint64_t BDK_TRCX_TRCACVR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACVR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30408ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030408ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030408ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030408ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030408ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACVR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACVR1(a) bdk_trcx_trcacvr1_t
#define bustype_BDK_TRCX_TRCACVR1(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACVR1(a) "TRCX_TRCACVR1"
#define busnum_BDK_TRCX_TRCACVR1(a) (a)
#define arguments_BDK_TRCX_TRCACVR1(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacvr2
 *
 * TRC/ETM Address Comparator Value Register 2
 * This register contains an address value.
 */
union bdk_trcx_trcacvr2
{
    uint64_t u;
    struct bdk_trcx_trcacvr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcacvr2_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcacvr2_s cn9; */
};
typedef union bdk_trcx_trcacvr2 bdk_trcx_trcacvr2_t;

static inline uint64_t BDK_TRCX_TRCACVR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACVR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30410ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030410ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030410ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030410ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030410ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACVR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACVR2(a) bdk_trcx_trcacvr2_t
#define bustype_BDK_TRCX_TRCACVR2(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACVR2(a) "TRCX_TRCACVR2"
#define busnum_BDK_TRCX_TRCACVR2(a) (a)
#define arguments_BDK_TRCX_TRCACVR2(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacvr3
 *
 * TRC/ETM Address Comparator Value Register 3
 * This register contains an address value.
 */
union bdk_trcx_trcacvr3
{
    uint64_t u;
    struct bdk_trcx_trcacvr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addrhi                : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#else /* Word 0 - Little Endian */
        uint64_t addrhi                : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcacvr3_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcacvr3_s cn9; */
};
typedef union bdk_trcx_trcacvr3 bdk_trcx_trcacvr3_t;

static inline uint64_t BDK_TRCX_TRCACVR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACVR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30418ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030418ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030418ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030418ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030418ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACVR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACVR3(a) bdk_trcx_trcacvr3_t
#define bustype_BDK_TRCX_TRCACVR3(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACVR3(a) "TRCX_TRCACVR3"
#define busnum_BDK_TRCX_TRCACVR3(a) (a)
#define arguments_BDK_TRCX_TRCACVR3(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacvr4
 *
 * TRC/ETM Address Comparator Value Register 4
 * Contains an address value.
 */
union bdk_trcx_trcacvr4
{
    uint64_t u;
    struct bdk_trcx_trcacvr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcacvr4_s cn; */
};
typedef union bdk_trcx_trcacvr4 bdk_trcx_trcacvr4_t;

static inline uint64_t BDK_TRCX_TRCACVR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACVR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030420ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030420ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030420ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030420ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACVR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACVR4(a) bdk_trcx_trcacvr4_t
#define bustype_BDK_TRCX_TRCACVR4(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACVR4(a) "TRCX_TRCACVR4"
#define busnum_BDK_TRCX_TRCACVR4(a) (a)
#define arguments_BDK_TRCX_TRCACVR4(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacvr5
 *
 * TRC/ETM Address Comparator Value Register 5
 * Contains an address value.
 */
union bdk_trcx_trcacvr5
{
    uint64_t u;
    struct bdk_trcx_trcacvr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcacvr5_s cn; */
};
typedef union bdk_trcx_trcacvr5 bdk_trcx_trcacvr5_t;

static inline uint64_t BDK_TRCX_TRCACVR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACVR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030428ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030428ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030428ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030428ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACVR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACVR5(a) bdk_trcx_trcacvr5_t
#define bustype_BDK_TRCX_TRCACVR5(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACVR5(a) "TRCX_TRCACVR5"
#define busnum_BDK_TRCX_TRCACVR5(a) (a)
#define arguments_BDK_TRCX_TRCACVR5(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacvr6
 *
 * TRC/ETM Address Comparator Value Register 6
 * Contains an address value.
 */
union bdk_trcx_trcacvr6
{
    uint64_t u;
    struct bdk_trcx_trcacvr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcacvr6_s cn; */
};
typedef union bdk_trcx_trcacvr6 bdk_trcx_trcacvr6_t;

static inline uint64_t BDK_TRCX_TRCACVR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACVR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030430ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030430ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030430ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030430ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACVR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACVR6(a) bdk_trcx_trcacvr6_t
#define bustype_BDK_TRCX_TRCACVR6(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACVR6(a) "TRCX_TRCACVR6"
#define busnum_BDK_TRCX_TRCACVR6(a) (a)
#define arguments_BDK_TRCX_TRCACVR6(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcacvr7
 *
 * TRC/ETM Address Comparator Value Register 7
 * Contains an address value.
 */
union bdk_trcx_trcacvr7
{
    uint64_t u;
    struct bdk_trcx_trcacvr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0](R/W) 64-bit address for comparison. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcacvr7_s cn; */
};
typedef union bdk_trcx_trcacvr7 bdk_trcx_trcacvr7_t;

static inline uint64_t BDK_TRCX_TRCACVR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCACVR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030438ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030438ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030438ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030438ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCACVR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCACVR7(a) bdk_trcx_trcacvr7_t
#define bustype_BDK_TRCX_TRCACVR7(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCACVR7(a) "TRCX_TRCACVR7"
#define busnum_BDK_TRCX_TRCACVR7(a) (a)
#define arguments_BDK_TRCX_TRCACVR7(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcauthstatus
 *
 * TRC/ETM Authentication Status Register
 * Provides information about the state of the implementation defined authentication
 * interface.
 */
union bdk_trcx_trcauthstatus
{
    uint32_t u;
    struct bdk_trcx_trcauthstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_12_31        : 20;
        uint32_t hnid                  : 2;  /**< [ 11: 10](RAZ) Reserved. */
        uint32_t hid                   : 2;  /**< [  9:  8](RAZ) Reserved. */
        uint32_t snid                  : 2;  /**< [  7:  6](RAZ) Reserved. */
        uint32_t sid                   : 2;  /**< [  5:  4](RAZ) Reserved. */
        uint32_t nsnid                 : 2;  /**< [  3:  2](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as TRC()_DBGAUTHSTATUS_EL1[SNID].
                                                                 Otherwise, holds the same value as TRC()_DBGAUTHSTATUS_EL1[NSNID]. */
        uint32_t nsid                  : 2;  /**< [  1:  0](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as TRC()_DBGAUTHSTATUS_EL1[SID].
                                                                 Otherwise, holds the same value as TRC()_DBGAUTHSTATUS_EL1[NSID]. */
#else /* Word 0 - Little Endian */
        uint32_t nsid                  : 2;  /**< [  1:  0](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as TRC()_DBGAUTHSTATUS_EL1[SID].
                                                                 Otherwise, holds the same value as TRC()_DBGAUTHSTATUS_EL1[NSID]. */
        uint32_t nsnid                 : 2;  /**< [  3:  2](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as TRC()_DBGAUTHSTATUS_EL1[SNID].
                                                                 Otherwise, holds the same value as TRC()_DBGAUTHSTATUS_EL1[NSNID]. */
        uint32_t sid                   : 2;  /**< [  5:  4](RAZ) Reserved. */
        uint32_t snid                  : 2;  /**< [  7:  6](RAZ) Reserved. */
        uint32_t hid                   : 2;  /**< [  9:  8](RAZ) Reserved. */
        uint32_t hnid                  : 2;  /**< [ 11: 10](RAZ) Reserved. */
        uint32_t reserved_12_31        : 20;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcauthstatus_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t nsnid                 : 2;  /**< [  3:  2](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as TRC()_DBGAUTHSTATUS_EL1[SNID].
                                                                 Otherwise, holds the same value as TRC()_DBGAUTHSTATUS_EL1[NSNID]. */
        uint32_t nsid                  : 2;  /**< [  1:  0](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as TRC()_DBGAUTHSTATUS_EL1[SID].
                                                                 Otherwise, holds the same value as TRC()_DBGAUTHSTATUS_EL1[NSID]. */
#else /* Word 0 - Little Endian */
        uint32_t nsid                  : 2;  /**< [  1:  0](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as TRC()_DBGAUTHSTATUS_EL1[SID].
                                                                 Otherwise, holds the same value as TRC()_DBGAUTHSTATUS_EL1[NSID]. */
        uint32_t nsnid                 : 2;  /**< [  3:  2](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as TRC()_DBGAUTHSTATUS_EL1[SNID].
                                                                 Otherwise, holds the same value as TRC()_DBGAUTHSTATUS_EL1[NSNID]. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcauthstatus_s cn9; */
};
typedef union bdk_trcx_trcauthstatus bdk_trcx_trcauthstatus_t;

static inline uint64_t BDK_TRCX_TRCAUTHSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCAUTHSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fb8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fb8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fb8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fb8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fb8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCAUTHSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCAUTHSTATUS(a) bdk_trcx_trcauthstatus_t
#define bustype_BDK_TRCX_TRCAUTHSTATUS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCAUTHSTATUS(a) "TRCX_TRCAUTHSTATUS"
#define busnum_BDK_TRCX_TRCAUTHSTATUS(a) (a)
#define arguments_BDK_TRCX_TRCAUTHSTATUS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcauxctlr
 *
 * TRC/ETM Auxiliary Control Register
 * implementation defines
 */
union bdk_trcx_trcauxctlr
{
    uint32_t u;
    struct bdk_trcx_trcauxctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcauxctlr_s cn; */
};
typedef union bdk_trcx_trcauxctlr bdk_trcx_trcauxctlr_t;

static inline uint64_t BDK_TRCX_TRCAUXCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCAUXCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30018ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030018ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030018ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030018ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030018ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCAUXCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCAUXCTLR(a) bdk_trcx_trcauxctlr_t
#define bustype_BDK_TRCX_TRCAUXCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCAUXCTLR(a) "TRCX_TRCAUXCTLR"
#define busnum_BDK_TRCX_TRCAUXCTLR(a) (a)
#define arguments_BDK_TRCX_TRCAUXCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcbbctlr
 *
 * TRC/ETM Branch Broadcast Control Register
 * This register controls which region in the memory map is enabled to use branch broadcasting.
 */
union bdk_trcx_trcbbctlr
{
    uint32_t u;
    struct bdk_trcx_trcbbctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t mode                  : 1;  /**< [  8:  8](R/W) Mode bit.
                                                                 0 = Exclude mode. Branch broadcasting is not enabled for
                                                                     branch instructions in the address range that the Range defines.
                                                                 1 = Include mode. Branch broadcasting is enabled for
                                                                     branch instructions in the address range that the Range defines. */
        uint32_t range                 : 8;  /**< [  7:  0](R/W) Address range fields. Select which address range comparator pairs is in use
                                                                 with branch broadcasting. Bit[n] controls address comparator pair[n]:
                                                                 0 = pair[n] is not selected.
                                                                 1 = pair[n] is selected. */
#else /* Word 0 - Little Endian */
        uint32_t range                 : 8;  /**< [  7:  0](R/W) Address range fields. Select which address range comparator pairs is in use
                                                                 with branch broadcasting. Bit[n] controls address comparator pair[n]:
                                                                 0 = pair[n] is not selected.
                                                                 1 = pair[n] is selected. */
        uint32_t mode                  : 1;  /**< [  8:  8](R/W) Mode bit.
                                                                 0 = Exclude mode. Branch broadcasting is not enabled for
                                                                     branch instructions in the address range that the Range defines.
                                                                 1 = Include mode. Branch broadcasting is enabled for
                                                                     branch instructions in the address range that the Range defines. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcbbctlr_s cn; */
};
typedef union bdk_trcx_trcbbctlr bdk_trcx_trcbbctlr_t;

static inline uint64_t BDK_TRCX_TRCBBCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCBBCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3003cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00803003cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00803003cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00803003cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00803003cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCBBCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCBBCTLR(a) bdk_trcx_trcbbctlr_t
#define bustype_BDK_TRCX_TRCBBCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCBBCTLR(a) "TRCX_TRCBBCTLR"
#define busnum_BDK_TRCX_TRCBBCTLR(a) (a)
#define arguments_BDK_TRCX_TRCBBCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcccctlr
 *
 * TRC/ETM Cycle Count Control Register
 * Set the threshold value for cycle counting.
 */
union bdk_trcx_trcccctlr
{
    uint32_t u;
    struct bdk_trcx_trcccctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_12_31        : 20;
        uint32_t threshold             : 12; /**< [ 11:  0](R/W) Set the threshold value for the instruction cycle counting. */
#else /* Word 0 - Little Endian */
        uint32_t threshold             : 12; /**< [ 11:  0](R/W) Set the threshold value for the instruction cycle counting. */
        uint32_t reserved_12_31        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcccctlr_s cn8; */
    struct bdk_trcx_trcccctlr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_12_31        : 20;
        uint32_t threshold             : 12; /**< [ 11:  0](RO) Set the threshold value for the instruction cycle counting. */
#else /* Word 0 - Little Endian */
        uint32_t threshold             : 12; /**< [ 11:  0](RO) Set the threshold value for the instruction cycle counting. */
        uint32_t reserved_12_31        : 20;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcccctlr bdk_trcx_trcccctlr_t;

static inline uint64_t BDK_TRCX_TRCCCCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCCCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30038ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030038ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030038ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030038ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030038ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCCCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCCCTLR(a) bdk_trcx_trcccctlr_t
#define bustype_BDK_TRCX_TRCCCCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCCCTLR(a) "TRCX_TRCCCCTLR"
#define busnum_BDK_TRCX_TRCCCCTLR(a) (a)
#define arguments_BDK_TRCX_TRCCCCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccidcctlr0
 *
 * TRC/ETM Context ID Comparator Control Register 0
 * This register contains the virtual machine identifier mask values for the TRCVMIDCVRn
 * registers, where n=0-3.
 */
union bdk_trcx_trccidcctlr0
{
    uint32_t u;
    struct bdk_trcx_trccidcctlr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t comp0                 : 4;  /**< [  3:  0](R/W) Controls the mask value that the trace unit applies to TRCCIDCVRn, where
                                                                 n=0. Each bit in this field corresponds to a byte in TRCCIDCVR0. When a bit is:
                                                                   0 = The trace unit includes the relevant byte in TRCCIDCVR0 when it performs
                                                                       the context ID comparison.
                                                                   1 = The trace unit ignores the relevant byte in TRCCIDCVR0 when it performs
                                                                       the context ID comparison. */
#else /* Word 0 - Little Endian */
        uint32_t comp0                 : 4;  /**< [  3:  0](R/W) Controls the mask value that the trace unit applies to TRCCIDCVRn, where
                                                                 n=0. Each bit in this field corresponds to a byte in TRCCIDCVR0. When a bit is:
                                                                   0 = The trace unit includes the relevant byte in TRCCIDCVR0 when it performs
                                                                       the context ID comparison.
                                                                   1 = The trace unit ignores the relevant byte in TRCCIDCVR0 when it performs
                                                                       the context ID comparison. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trccidcctlr0_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trccidcctlr0_s cn9; */
};
typedef union bdk_trcx_trccidcctlr0 bdk_trcx_trccidcctlr0_t;

static inline uint64_t BDK_TRCX_TRCCIDCCTLR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCIDCCTLR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30680ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030680ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030680ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030680ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030680ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCIDCCTLR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCIDCCTLR0(a) bdk_trcx_trccidcctlr0_t
#define bustype_BDK_TRCX_TRCCIDCCTLR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCIDCCTLR0(a) "TRCX_TRCCIDCCTLR0"
#define busnum_BDK_TRCX_TRCCIDCCTLR0(a) (a)
#define arguments_BDK_TRCX_TRCCIDCCTLR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccidcctlr1
 *
 * TRC/ETM Context ID Comparator Control Register 1
 * This register contains the virtual machine identifier mask values for the TRCVMIDCVRn
 * registers, where n=1.
 */
union bdk_trcx_trccidcctlr1
{
    uint32_t u;
    struct bdk_trcx_trccidcctlr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccidcctlr1_s cn; */
};
typedef union bdk_trcx_trccidcctlr1 bdk_trcx_trccidcctlr1_t;

static inline uint64_t BDK_TRCX_TRCCIDCCTLR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCIDCCTLR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30684ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCIDCCTLR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCIDCCTLR1(a) bdk_trcx_trccidcctlr1_t
#define bustype_BDK_TRCX_TRCCIDCCTLR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCIDCCTLR1(a) "TRCX_TRCCIDCCTLR1"
#define busnum_BDK_TRCX_TRCCIDCCTLR1(a) (a)
#define arguments_BDK_TRCX_TRCCIDCCTLR1(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trccidcvr0
 *
 * TRC/ETM Context ID Comparator Value Register
 * Contains a context ID value.
 */
union bdk_trcx_trccidcvr0
{
    uint64_t u;
    struct bdk_trcx_trccidcvr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t value                 : 32; /**< [ 31:  0](R/W) Context identifier value. The implemented width of this field is
                                                                 implementation-defined, and is set by TRCIDR2.CIDSIZE. */
#else /* Word 0 - Little Endian */
        uint64_t value                 : 32; /**< [ 31:  0](R/W) Context identifier value. The implemented width of this field is
                                                                 implementation-defined, and is set by TRCIDR2.CIDSIZE. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trccidcvr0_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trccidcvr0_s cn9; */
};
typedef union bdk_trcx_trccidcvr0 bdk_trcx_trccidcvr0_t;

static inline uint64_t BDK_TRCX_TRCCIDCVR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCIDCVR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30600ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030600ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030600ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030600ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030600ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCIDCVR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCIDCVR0(a) bdk_trcx_trccidcvr0_t
#define bustype_BDK_TRCX_TRCCIDCVR0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCCIDCVR0(a) "TRCX_TRCCIDCVR0"
#define busnum_BDK_TRCX_TRCCIDCVR0(a) (a)
#define arguments_BDK_TRCX_TRCCIDCVR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccidr0
 *
 * TRC/ETM Component Identification Register 0
 * Provides information to identify a component.
 */
union bdk_trcx_trccidr0
{
    uint32_t u;
    struct bdk_trcx_trccidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0x0D. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0x0D. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccidr0_s cn; */
};
typedef union bdk_trcx_trccidr0 bdk_trcx_trccidr0_t;

static inline uint64_t BDK_TRCX_TRCCIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30ff0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030ff0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030ff0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030ff0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030ff0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCIDR0(a) bdk_trcx_trccidr0_t
#define bustype_BDK_TRCX_TRCCIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCIDR0(a) "TRCX_TRCCIDR0"
#define busnum_BDK_TRCX_TRCCIDR0(a) (a)
#define arguments_BDK_TRCX_TRCCIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccidr1
 *
 * TRC/ETM Component Identification Register 1
 * Provides information to identify a component.
 */
union bdk_trcx_trccidr1
{
    uint32_t u;
    struct bdk_trcx_trccidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0x9 = Debug component. */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble. */
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0x9 = Debug component. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccidr1_s cn; */
};
typedef union bdk_trcx_trccidr1 bdk_trcx_trccidr1_t;

static inline uint64_t BDK_TRCX_TRCCIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30ff4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030ff4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030ff4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030ff4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030ff4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCIDR1(a) bdk_trcx_trccidr1_t
#define bustype_BDK_TRCX_TRCCIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCIDR1(a) "TRCX_TRCCIDR1"
#define busnum_BDK_TRCX_TRCCIDR1(a) (a)
#define arguments_BDK_TRCX_TRCCIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccidr2
 *
 * TRC/ETM Component Identification Register 2
 * Provides information to identify a component.
 */
union bdk_trcx_trccidr2
{
    uint32_t u;
    struct bdk_trcx_trccidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0x05. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0x05. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccidr2_s cn; */
};
typedef union bdk_trcx_trccidr2 bdk_trcx_trccidr2_t;

static inline uint64_t BDK_TRCX_TRCCIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30ff8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030ff8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030ff8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030ff8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030ff8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCIDR2(a) bdk_trcx_trccidr2_t
#define bustype_BDK_TRCX_TRCCIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCIDR2(a) "TRCX_TRCCIDR2"
#define busnum_BDK_TRCX_TRCCIDR2(a) (a)
#define arguments_BDK_TRCX_TRCCIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccidr3
 *
 * TRC/ETM Component Identification Register 3
 * Provides information to identify a component.
 */
union bdk_trcx_trccidr3
{
    uint32_t u;
    struct bdk_trcx_trccidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0xB1. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0xB1. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccidr3_s cn; */
};
typedef union bdk_trcx_trccidr3 bdk_trcx_trccidr3_t;

static inline uint64_t BDK_TRCX_TRCCIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30ffcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030ffcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030ffcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030ffcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030ffcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCIDR3(a) bdk_trcx_trccidr3_t
#define bustype_BDK_TRCX_TRCCIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCIDR3(a) "TRCX_TRCCIDR3"
#define busnum_BDK_TRCX_TRCCIDR3(a) (a)
#define arguments_BDK_TRCX_TRCCIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcclaimclr
 *
 * TRC/ETM Claim Tag Clear Register
 * Software can use this to:
 *   1. Clear bits in the claim tag to zero.
 *   2. Read the value of the claim tag.
 */
union bdk_trcx_trcclaimclr
{
    uint32_t u;
    struct bdk_trcx_trcclaimclr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t clr                   : 8;  /**< [  7:  0](R/W1C) When a write to one of these bits occurs, with the value:
                                                                   0 = The register ignores the write.
                                                                   1 = If the bit is supported then it is set to zero.
                                                                      A single write operation can set multiple bits to zero.

                                                                 A Read returns the value of the claim tag. */
#else /* Word 0 - Little Endian */
        uint32_t clr                   : 8;  /**< [  7:  0](R/W1C) When a write to one of these bits occurs, with the value:
                                                                   0 = The register ignores the write.
                                                                   1 = If the bit is supported then it is set to zero.
                                                                      A single write operation can set multiple bits to zero.

                                                                 A Read returns the value of the claim tag. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcclaimclr_s cn; */
};
typedef union bdk_trcx_trcclaimclr bdk_trcx_trcclaimclr_t;

static inline uint64_t BDK_TRCX_TRCCLAIMCLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCLAIMCLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fa4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fa4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fa4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fa4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCLAIMCLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCLAIMCLR(a) bdk_trcx_trcclaimclr_t
#define bustype_BDK_TRCX_TRCCLAIMCLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCLAIMCLR(a) "TRCX_TRCCLAIMCLR"
#define busnum_BDK_TRCX_TRCCLAIMCLR(a) (a)
#define arguments_BDK_TRCX_TRCCLAIMCLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcclaimset
 *
 * TRC/ETM Claim Tag Set Register
 * Software can use this to:
 *   1. Set bits in the claim tag to one.
 *   2. discover the number of bits that the claim tag supports.
 */
union bdk_trcx_trcclaimset
{
    uint32_t u;
    struct bdk_trcx_trcclaimset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t set                   : 8;  /**< [  7:  0](R/W1S) When a write to one of these bits occurs, with the value:
                                                                   0 = The register ignores the write.
                                                                   1 = If the bit is supported then it is set to one.
                                                                      A single write operation can set multiple bits to one.

                                                                 Software must use the TRCCLAIMCLR register to:
                                                                   Read the value of the claim tag.
                                                                   Clear a claim tag bit to zero. */
#else /* Word 0 - Little Endian */
        uint32_t set                   : 8;  /**< [  7:  0](R/W1S) When a write to one of these bits occurs, with the value:
                                                                   0 = The register ignores the write.
                                                                   1 = If the bit is supported then it is set to one.
                                                                      A single write operation can set multiple bits to one.

                                                                 Software must use the TRCCLAIMCLR register to:
                                                                   Read the value of the claim tag.
                                                                   Clear a claim tag bit to zero. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcclaimset_s cn; */
};
typedef union bdk_trcx_trcclaimset bdk_trcx_trcclaimset_t;

static inline uint64_t BDK_TRCX_TRCCLAIMSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCLAIMSET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fa0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fa0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fa0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fa0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCLAIMSET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCLAIMSET(a) bdk_trcx_trcclaimset_t
#define bustype_BDK_TRCX_TRCCLAIMSET(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCLAIMSET(a) "TRCX_TRCCLAIMSET"
#define busnum_BDK_TRCX_TRCCLAIMSET(a) (a)
#define arguments_BDK_TRCX_TRCCLAIMSET(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccntctlr0
 *
 * TRC/ETM Counter Control Register 0
 * This register controls the operation of counter n.
 */
union bdk_trcx_trccntctlr0
{
    uint32_t u;
    struct bdk_trcx_trccntctlr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t cntchain              : 1;  /**< [ 17: 17](R/W) Control whether counter n decrements when the reload event of counter n-1 occurs.
                                                                 0 = Counter n does not decrement when the reload event of counter n-1 occurs.
                                                                 1 = Counter n decrement when the reload event of counter n-1 occurs. */
        uint32_t rldself               : 1;  /**< [ 16: 16](R/W) Control whether counter n reload occur when counter n reaches zero.
                                                                 0 = Counter is in normal mode.
                                                                 1 = Counter is in reload mode. */
        uint32_t rldevent              : 8;  /**< [ 15:  8](R/W) Select an event when it occurs, cause a reload event for counter n. */
        uint32_t cntevent              : 8;  /**< [  7:  0](R/W) Select an event when it occurs, cause counter n to decrement. */
#else /* Word 0 - Little Endian */
        uint32_t cntevent              : 8;  /**< [  7:  0](R/W) Select an event when it occurs, cause counter n to decrement. */
        uint32_t rldevent              : 8;  /**< [ 15:  8](R/W) Select an event when it occurs, cause a reload event for counter n. */
        uint32_t rldself               : 1;  /**< [ 16: 16](R/W) Control whether counter n reload occur when counter n reaches zero.
                                                                 0 = Counter is in normal mode.
                                                                 1 = Counter is in reload mode. */
        uint32_t cntchain              : 1;  /**< [ 17: 17](R/W) Control whether counter n decrements when the reload event of counter n-1 occurs.
                                                                 0 = Counter n does not decrement when the reload event of counter n-1 occurs.
                                                                 1 = Counter n decrement when the reload event of counter n-1 occurs. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccntctlr0_s cn; */
};
typedef union bdk_trcx_trccntctlr0 bdk_trcx_trccntctlr0_t;

static inline uint64_t BDK_TRCX_TRCCNTCTLR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCNTCTLR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30150ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030150ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030150ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030150ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030150ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCNTCTLR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCNTCTLR0(a) bdk_trcx_trccntctlr0_t
#define bustype_BDK_TRCX_TRCCNTCTLR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCNTCTLR0(a) "TRCX_TRCCNTCTLR0"
#define busnum_BDK_TRCX_TRCCNTCTLR0(a) (a)
#define arguments_BDK_TRCX_TRCCNTCTLR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccntctlr1
 *
 * TRC/ETM Counter Control Register 1
 * This register controls the operation of counter n.
 */
union bdk_trcx_trccntctlr1
{
    uint32_t u;
    struct bdk_trcx_trccntctlr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t cntchain              : 1;  /**< [ 17: 17](R/W) Control whether counter n decrements when the reload event of counter n-1 occurs.
                                                                 0 = Counter n does not decrement when the reload event of counter n-1 occurs.
                                                                 1 = Counter n decrement when the reload event of counter n-1 occurs. */
        uint32_t rldself               : 1;  /**< [ 16: 16](R/W) Control whether counter n reload occur when counter n reaches zero.
                                                                 0 = Counter is in normal mode.
                                                                 1 = Counter is in reload mode. */
        uint32_t rldevent              : 8;  /**< [ 15:  8](R/W) Select an event when it occurs, cause a reload event for counter n. */
        uint32_t cntevent              : 8;  /**< [  7:  0](R/W) Select an event when it occurs, cause counter n to decrement. */
#else /* Word 0 - Little Endian */
        uint32_t cntevent              : 8;  /**< [  7:  0](R/W) Select an event when it occurs, cause counter n to decrement. */
        uint32_t rldevent              : 8;  /**< [ 15:  8](R/W) Select an event when it occurs, cause a reload event for counter n. */
        uint32_t rldself               : 1;  /**< [ 16: 16](R/W) Control whether counter n reload occur when counter n reaches zero.
                                                                 0 = Counter is in normal mode.
                                                                 1 = Counter is in reload mode. */
        uint32_t cntchain              : 1;  /**< [ 17: 17](R/W) Control whether counter n decrements when the reload event of counter n-1 occurs.
                                                                 0 = Counter n does not decrement when the reload event of counter n-1 occurs.
                                                                 1 = Counter n decrement when the reload event of counter n-1 occurs. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccntctlr1_s cn; */
};
typedef union bdk_trcx_trccntctlr1 bdk_trcx_trccntctlr1_t;

static inline uint64_t BDK_TRCX_TRCCNTCTLR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCNTCTLR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30154ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030154ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030154ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030154ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030154ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCNTCTLR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCNTCTLR1(a) bdk_trcx_trccntctlr1_t
#define bustype_BDK_TRCX_TRCCNTCTLR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCNTCTLR1(a) "TRCX_TRCCNTCTLR1"
#define busnum_BDK_TRCX_TRCCNTCTLR1(a) (a)
#define arguments_BDK_TRCX_TRCCNTCTLR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccntrldvr0
 *
 * TRC/ETM Counter Reload Value Register 0
 * Set or read the reload counter value for counter n.
 */
union bdk_trcx_trccntrldvr0
{
    uint32_t u;
    struct bdk_trcx_trccntrldvr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t value                 : 16; /**< [ 15:  0](R/W) Contains the reload counter value for counter n. */
#else /* Word 0 - Little Endian */
        uint32_t value                 : 16; /**< [ 15:  0](R/W) Contains the reload counter value for counter n. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccntrldvr0_s cn; */
};
typedef union bdk_trcx_trccntrldvr0 bdk_trcx_trccntrldvr0_t;

static inline uint64_t BDK_TRCX_TRCCNTRLDVR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCNTRLDVR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30140ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030140ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030140ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030140ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030140ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCNTRLDVR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCNTRLDVR0(a) bdk_trcx_trccntrldvr0_t
#define bustype_BDK_TRCX_TRCCNTRLDVR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCNTRLDVR0(a) "TRCX_TRCCNTRLDVR0"
#define busnum_BDK_TRCX_TRCCNTRLDVR0(a) (a)
#define arguments_BDK_TRCX_TRCCNTRLDVR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccntrldvr1
 *
 * TRC/ETM Counter Reload Value Register 1
 * Set or read the reload counter value for counter n.
 */
union bdk_trcx_trccntrldvr1
{
    uint32_t u;
    struct bdk_trcx_trccntrldvr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t value                 : 16; /**< [ 15:  0](R/W) Contains the reload counter value for counter n. */
#else /* Word 0 - Little Endian */
        uint32_t value                 : 16; /**< [ 15:  0](R/W) Contains the reload counter value for counter n. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccntrldvr1_s cn; */
};
typedef union bdk_trcx_trccntrldvr1 bdk_trcx_trccntrldvr1_t;

static inline uint64_t BDK_TRCX_TRCCNTRLDVR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCNTRLDVR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30144ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030144ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030144ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030144ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030144ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCNTRLDVR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCNTRLDVR1(a) bdk_trcx_trccntrldvr1_t
#define bustype_BDK_TRCX_TRCCNTRLDVR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCNTRLDVR1(a) "TRCX_TRCCNTRLDVR1"
#define busnum_BDK_TRCX_TRCCNTRLDVR1(a) (a)
#define arguments_BDK_TRCX_TRCCNTRLDVR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccntvr0
 *
 * TRC/ETM Counter Value Register 0
 * This register returns the value of counter n.
 */
union bdk_trcx_trccntvr0
{
    uint32_t u;
    struct bdk_trcx_trccntvr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t value                 : 16; /**< [ 15:  0](R/W) Contains the count value of counter n. */
#else /* Word 0 - Little Endian */
        uint32_t value                 : 16; /**< [ 15:  0](R/W) Contains the count value of counter n. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccntvr0_s cn; */
};
typedef union bdk_trcx_trccntvr0 bdk_trcx_trccntvr0_t;

static inline uint64_t BDK_TRCX_TRCCNTVR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCNTVR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30160ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030160ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030160ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030160ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030160ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCNTVR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCNTVR0(a) bdk_trcx_trccntvr0_t
#define bustype_BDK_TRCX_TRCCNTVR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCNTVR0(a) "TRCX_TRCCNTVR0"
#define busnum_BDK_TRCX_TRCCNTVR0(a) (a)
#define arguments_BDK_TRCX_TRCCNTVR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trccntvr1
 *
 * TRC/ETM Counter Value Register 1
 * This register returns the value of counter n.
 */
union bdk_trcx_trccntvr1
{
    uint32_t u;
    struct bdk_trcx_trccntvr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t value                 : 16; /**< [ 15:  0](R/W) Contains the count value of counter n. */
#else /* Word 0 - Little Endian */
        uint32_t value                 : 16; /**< [ 15:  0](R/W) Contains the count value of counter n. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trccntvr1_s cn; */
};
typedef union bdk_trcx_trccntvr1 bdk_trcx_trccntvr1_t;

static inline uint64_t BDK_TRCX_TRCCNTVR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCNTVR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30164ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030164ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030164ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030164ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030164ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCNTVR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCNTVR1(a) bdk_trcx_trccntvr1_t
#define bustype_BDK_TRCX_TRCCNTVR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCNTVR1(a) "TRCX_TRCCNTVR1"
#define busnum_BDK_TRCX_TRCCNTVR1(a) (a)
#define arguments_BDK_TRCX_TRCCNTVR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcconfigr
 *
 * TRC/ETM Trace Configuration Register
 * This register controls the trace unit options.
 */
union bdk_trcx_trcconfigr
{
    uint32_t u;
    struct bdk_trcx_trcconfigr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t dv                    : 1;  /**< [ 17: 17](R/W) Data value tracing bit.
                                                                 0 = The data value tracing is disabled.
                                                                 1 = The data value tracing is enabled when INSTP0 is not 0x0. */
        uint32_t da                    : 1;  /**< [ 16: 16](R/W) Data address tracing bit.
                                                                 0 = The data address tracing is disabled.
                                                                 1 = The data address tracing is enabled when INSTP0 is not 0x0. */
        uint32_t vmidopt               : 1;  /**< [ 15: 15](R/W) Reserved. */
        uint32_t qe                    : 2;  /**< [ 14: 13](R/W) Q element enable field.
                                                                 0x0 = Q elements are disabled.
                                                                 0x1 = Q elements with instruction counts are enabled.
                                                                      Q elements without instruction counts are disabled.
                                                                 0x2 = Reserved.
                                                                 0x3 = Q elements with and without instruction counts are enabled.

                                                                 These fields must be set to 0x0 if any of the following are true:
                                                                      1. TRC()_TRCCONFIGR[INSTP0] is not 0x0.
                                                                      2. TRC()_TRCCONFIGR[COND] is not 0x0.
                                                                      3. TRC()_TRCCONFIGR[BB] is not 0. */
        uint32_t rs                    : 1;  /**< [ 12: 12](R/W) Return stack enable bit.
                                                                 0 = Return stack is not enabled.
                                                                 1 = Return stack is enabled. */
        uint32_t ts                    : 1;  /**< [ 11: 11](R/W) Global timestamp tracing bit.
                                                                 0 = Global timestamp tracing is not enabled.
                                                                 1 = Global timestamp tracing is enabled. */
        uint32_t cond                  : 3;  /**< [ 10:  8](R/W) Conditional instruction tracing bit. The permitted values are:
                                                                 0x0 = Conditional instruction tracing is disabled.
                                                                 0x1 = Conditional load instructions are traced.
                                                                 0x2 = Conditional store instructions are traced.
                                                                 0x3 = Conditional load and store instructions are traced.
                                                                 0x7 = All conditional instructions are traced.
                                                                 All other values are reserved. */
        uint32_t vmid                  : 1;  /**< [  7:  7](R/W) VMID tracing bit.
                                                                 0 = VMID tracing is disabled.
                                                                 1 = VMID tracing is enabled. */
        uint32_t cid                   : 1;  /**< [  6:  6](R/W) Context ID tracing bit.
                                                                 0 = Context ID tracing is disabled.
                                                                 1 = Context ID tracing is enabled. */
        uint32_t reserved_5            : 1;
        uint32_t cci                   : 1;  /**< [  4:  4](R/W) Cycle counting instruction trace bit.
                                                                 0 = Cycle counting in instruction trace is disabled.
                                                                 1 = Cycle counting in instruction trace is enabled. */
        uint32_t bb                    : 1;  /**< [  3:  3](R/W) Branch broadcast mode bit.
                                                                 0 = Branch broadcast mode is disabled.
                                                                 1 = Branch broadcast mode is enabled. */
        uint32_t instp0                : 2;  /**< [  2:  1](R/W) Instruction P0 fields. This field control whether load and store instructions
                                                                   trace are traced as P0 instructions:
                                                                 0x0 = Do not trace load and store instructions as P0 instructions.
                                                                 0x1 = Trace load instructions as P0 instructions.
                                                                 0x2 = Trace store instructions as P0 instructions.
                                                                 0x3 = Trace load and store instructions as P0 instructions. */
        uint32_t b0                    : 1;  /**< [  0:  0](RO)  */
#else /* Word 0 - Little Endian */
        uint32_t b0                    : 1;  /**< [  0:  0](RO)  */
        uint32_t instp0                : 2;  /**< [  2:  1](R/W) Instruction P0 fields. This field control whether load and store instructions
                                                                   trace are traced as P0 instructions:
                                                                 0x0 = Do not trace load and store instructions as P0 instructions.
                                                                 0x1 = Trace load instructions as P0 instructions.
                                                                 0x2 = Trace store instructions as P0 instructions.
                                                                 0x3 = Trace load and store instructions as P0 instructions. */
        uint32_t bb                    : 1;  /**< [  3:  3](R/W) Branch broadcast mode bit.
                                                                 0 = Branch broadcast mode is disabled.
                                                                 1 = Branch broadcast mode is enabled. */
        uint32_t cci                   : 1;  /**< [  4:  4](R/W) Cycle counting instruction trace bit.
                                                                 0 = Cycle counting in instruction trace is disabled.
                                                                 1 = Cycle counting in instruction trace is enabled. */
        uint32_t reserved_5            : 1;
        uint32_t cid                   : 1;  /**< [  6:  6](R/W) Context ID tracing bit.
                                                                 0 = Context ID tracing is disabled.
                                                                 1 = Context ID tracing is enabled. */
        uint32_t vmid                  : 1;  /**< [  7:  7](R/W) VMID tracing bit.
                                                                 0 = VMID tracing is disabled.
                                                                 1 = VMID tracing is enabled. */
        uint32_t cond                  : 3;  /**< [ 10:  8](R/W) Conditional instruction tracing bit. The permitted values are:
                                                                 0x0 = Conditional instruction tracing is disabled.
                                                                 0x1 = Conditional load instructions are traced.
                                                                 0x2 = Conditional store instructions are traced.
                                                                 0x3 = Conditional load and store instructions are traced.
                                                                 0x7 = All conditional instructions are traced.
                                                                 All other values are reserved. */
        uint32_t ts                    : 1;  /**< [ 11: 11](R/W) Global timestamp tracing bit.
                                                                 0 = Global timestamp tracing is not enabled.
                                                                 1 = Global timestamp tracing is enabled. */
        uint32_t rs                    : 1;  /**< [ 12: 12](R/W) Return stack enable bit.
                                                                 0 = Return stack is not enabled.
                                                                 1 = Return stack is enabled. */
        uint32_t qe                    : 2;  /**< [ 14: 13](R/W) Q element enable field.
                                                                 0x0 = Q elements are disabled.
                                                                 0x1 = Q elements with instruction counts are enabled.
                                                                      Q elements without instruction counts are disabled.
                                                                 0x2 = Reserved.
                                                                 0x3 = Q elements with and without instruction counts are enabled.

                                                                 These fields must be set to 0x0 if any of the following are true:
                                                                      1. TRC()_TRCCONFIGR[INSTP0] is not 0x0.
                                                                      2. TRC()_TRCCONFIGR[COND] is not 0x0.
                                                                      3. TRC()_TRCCONFIGR[BB] is not 0. */
        uint32_t vmidopt               : 1;  /**< [ 15: 15](R/W) Reserved. */
        uint32_t da                    : 1;  /**< [ 16: 16](R/W) Data address tracing bit.
                                                                 0 = The data address tracing is disabled.
                                                                 1 = The data address tracing is enabled when INSTP0 is not 0x0. */
        uint32_t dv                    : 1;  /**< [ 17: 17](R/W) Data value tracing bit.
                                                                 0 = The data value tracing is disabled.
                                                                 1 = The data value tracing is enabled when INSTP0 is not 0x0. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcconfigr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t dv                    : 1;  /**< [ 17: 17](R/W) Data value tracing bit.
                                                                 0 = The data value tracing is disabled.
                                                                 1 = The data value tracing is enabled when INSTP0 is not 0x0. */
        uint32_t da                    : 1;  /**< [ 16: 16](R/W) Data address tracing bit.
                                                                 0 = The data address tracing is disabled.
                                                                 1 = The data address tracing is enabled when INSTP0 is not 0x0. */
        uint32_t reserved_15           : 1;
        uint32_t qe                    : 2;  /**< [ 14: 13](R/W) Q element enable field.
                                                                 0x0 = Q elements are disabled.
                                                                 0x1 = Q elements with instruction counts are enabled.
                                                                      Q elements without instruction counts are disabled.
                                                                 0x2 = Reserved.
                                                                 0x3 = Q elements with and without instruction counts are enabled.

                                                                 These fields must be set to 0x0 if any of the following are true:
                                                                      1. TRC()_TRCCONFIGR[INSTP0] is not 0x0.
                                                                      2. TRC()_TRCCONFIGR[COND] is not 0x0.
                                                                      3. TRC()_TRCCONFIGR[BB] is not 0. */
        uint32_t rs                    : 1;  /**< [ 12: 12](R/W) Return stack enable bit.
                                                                 0 = Return stack is not enabled.
                                                                 1 = Return stack is enabled. */
        uint32_t ts                    : 1;  /**< [ 11: 11](R/W) Global timestamp tracing bit.
                                                                 0 = Global timestamp tracing is not enabled.
                                                                 1 = Global timestamp tracing is enabled. */
        uint32_t cond                  : 3;  /**< [ 10:  8](R/W) Conditional instruction tracing bit. The permitted values are:
                                                                 0x0 = Conditional instruction tracing is disabled.
                                                                 0x1 = Conditional load instructions are traced.
                                                                 0x2 = Conditional store instructions are traced.
                                                                 0x3 = Conditional load and store instructions are traced.
                                                                 0x7 = All conditional instructions are traced.
                                                                 All other values are reserved. */
        uint32_t vmid                  : 1;  /**< [  7:  7](R/W) VMID tracing bit.
                                                                 0 = VMID tracing is disabled.
                                                                 1 = VMID tracing is enabled. */
        uint32_t cid                   : 1;  /**< [  6:  6](R/W) Context ID tracing bit.
                                                                 0 = Context ID tracing is disabled.
                                                                 1 = Context ID tracing is enabled. */
        uint32_t reserved_5            : 1;
        uint32_t cci                   : 1;  /**< [  4:  4](R/W) Cycle counting instruction trace bit.
                                                                 0 = Cycle counting in instruction trace is disabled.
                                                                 1 = Cycle counting in instruction trace is enabled. */
        uint32_t bb                    : 1;  /**< [  3:  3](R/W) Branch broadcast mode bit.
                                                                 0 = Branch broadcast mode is disabled.
                                                                 1 = Branch broadcast mode is enabled. */
        uint32_t instp0                : 2;  /**< [  2:  1](R/W) Instruction P0 fields. This field control whether load and store instructions
                                                                   trace are traced as P0 instructions:
                                                                 0x0 = Do not trace load and store instructions as P0 instructions.
                                                                 0x1 = Trace load instructions as P0 instructions.
                                                                 0x2 = Trace store instructions as P0 instructions.
                                                                 0x3 = Trace load and store instructions as P0 instructions. */
        uint32_t b0                    : 1;  /**< [  0:  0](RO)  */
#else /* Word 0 - Little Endian */
        uint32_t b0                    : 1;  /**< [  0:  0](RO)  */
        uint32_t instp0                : 2;  /**< [  2:  1](R/W) Instruction P0 fields. This field control whether load and store instructions
                                                                   trace are traced as P0 instructions:
                                                                 0x0 = Do not trace load and store instructions as P0 instructions.
                                                                 0x1 = Trace load instructions as P0 instructions.
                                                                 0x2 = Trace store instructions as P0 instructions.
                                                                 0x3 = Trace load and store instructions as P0 instructions. */
        uint32_t bb                    : 1;  /**< [  3:  3](R/W) Branch broadcast mode bit.
                                                                 0 = Branch broadcast mode is disabled.
                                                                 1 = Branch broadcast mode is enabled. */
        uint32_t cci                   : 1;  /**< [  4:  4](R/W) Cycle counting instruction trace bit.
                                                                 0 = Cycle counting in instruction trace is disabled.
                                                                 1 = Cycle counting in instruction trace is enabled. */
        uint32_t reserved_5            : 1;
        uint32_t cid                   : 1;  /**< [  6:  6](R/W) Context ID tracing bit.
                                                                 0 = Context ID tracing is disabled.
                                                                 1 = Context ID tracing is enabled. */
        uint32_t vmid                  : 1;  /**< [  7:  7](R/W) VMID tracing bit.
                                                                 0 = VMID tracing is disabled.
                                                                 1 = VMID tracing is enabled. */
        uint32_t cond                  : 3;  /**< [ 10:  8](R/W) Conditional instruction tracing bit. The permitted values are:
                                                                 0x0 = Conditional instruction tracing is disabled.
                                                                 0x1 = Conditional load instructions are traced.
                                                                 0x2 = Conditional store instructions are traced.
                                                                 0x3 = Conditional load and store instructions are traced.
                                                                 0x7 = All conditional instructions are traced.
                                                                 All other values are reserved. */
        uint32_t ts                    : 1;  /**< [ 11: 11](R/W) Global timestamp tracing bit.
                                                                 0 = Global timestamp tracing is not enabled.
                                                                 1 = Global timestamp tracing is enabled. */
        uint32_t rs                    : 1;  /**< [ 12: 12](R/W) Return stack enable bit.
                                                                 0 = Return stack is not enabled.
                                                                 1 = Return stack is enabled. */
        uint32_t qe                    : 2;  /**< [ 14: 13](R/W) Q element enable field.
                                                                 0x0 = Q elements are disabled.
                                                                 0x1 = Q elements with instruction counts are enabled.
                                                                      Q elements without instruction counts are disabled.
                                                                 0x2 = Reserved.
                                                                 0x3 = Q elements with and without instruction counts are enabled.

                                                                 These fields must be set to 0x0 if any of the following are true:
                                                                      1. TRC()_TRCCONFIGR[INSTP0] is not 0x0.
                                                                      2. TRC()_TRCCONFIGR[COND] is not 0x0.
                                                                      3. TRC()_TRCCONFIGR[BB] is not 0. */
        uint32_t reserved_15           : 1;
        uint32_t da                    : 1;  /**< [ 16: 16](R/W) Data address tracing bit.
                                                                 0 = The data address tracing is disabled.
                                                                 1 = The data address tracing is enabled when INSTP0 is not 0x0. */
        uint32_t dv                    : 1;  /**< [ 17: 17](R/W) Data value tracing bit.
                                                                 0 = The data value tracing is disabled.
                                                                 1 = The data value tracing is enabled when INSTP0 is not 0x0. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_trcx_trcconfigr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t dv                    : 1;  /**< [ 17: 17](RO) Data value tracing bit.
                                                                 0 = The data value tracing is disabled.
                                                                 1 = The data value tracing is enabled when [INSTP0] is not 0x0. */
        uint32_t da                    : 1;  /**< [ 16: 16](RO) Data address tracing bit.
                                                                 0 = The data address tracing is disabled.
                                                                 1 = The data address tracing is enabled when [INSTP0] is not 0x0. */
        uint32_t vmidopt               : 1;  /**< [ 15: 15](R/W) Reserved. */
        uint32_t qe                    : 2;  /**< [ 14: 13](RO) Q element enable field.
                                                                 0x0 = Q elements are disabled.
                                                                 0x1 = Q elements with instruction counts are enabled.
                                                                      Q elements without instruction counts are disabled.
                                                                 0x2 = Reserved.
                                                                 0x3 = Q elements with and without instruction counts are enabled.

                                                                 These fields must be set to 0x0 if any of the following are true:
                                                                      1. TRC()_TRCCONFIGR[INSTP0] is not 0x0.
                                                                      2. TRC()_TRCCONFIGR[COND] is not 0x0.
                                                                      3. TRC()_TRCCONFIGR[BB] is not 0. */
        uint32_t rs                    : 1;  /**< [ 12: 12](R/W) Return stack enable bit.
                                                                 0 = Return stack is not enabled.
                                                                 1 = Return stack is enabled. */
        uint32_t ts                    : 1;  /**< [ 11: 11](R/W) Global timestamp tracing bit.
                                                                 0 = Global timestamp tracing is not enabled.
                                                                 1 = Global timestamp tracing is enabled. */
        uint32_t cond                  : 3;  /**< [ 10:  8](RO) Conditional instruction tracing bit. The permitted values are:
                                                                 0x0 = Conditional instruction tracing is disabled.
                                                                 0x1 = Conditional load instructions are traced.
                                                                 0x2 = Conditional store instructions are traced.
                                                                 0x3 = Conditional load and store instructions are traced.
                                                                 0x7 = All conditional instructions are traced.
                                                                 All other values are reserved. */
        uint32_t vmid                  : 1;  /**< [  7:  7](R/W) VMID tracing bit.
                                                                 0 = VMID tracing is disabled.
                                                                 1 = VMID tracing is enabled. */
        uint32_t cid                   : 1;  /**< [  6:  6](R/W) Context ID tracing bit.
                                                                 0 = Context ID tracing is disabled.
                                                                 1 = Context ID tracing is enabled. */
        uint32_t reserved_5            : 1;
        uint32_t cci                   : 1;  /**< [  4:  4](RO) Cycle counting instruction trace bit.
                                                                 0 = Cycle counting in instruction trace is disabled.
                                                                 1 = Cycle counting in instruction trace is enabled. */
        uint32_t bb                    : 1;  /**< [  3:  3](RO) Branch broadcast mode bit.
                                                                 0 = Branch broadcast mode is disabled.
                                                                 1 = Branch broadcast mode is enabled. */
        uint32_t instp0                : 2;  /**< [  2:  1](RO) Instruction P0 fields. This field control whether load and store instructions
                                                                   trace are traced as P0 instructions:
                                                                 0x0 = Do not trace load and store instructions as P0 instructions.
                                                                 0x1 = Trace load instructions as P0 instructions.
                                                                 0x2 = Trace store instructions as P0 instructions.
                                                                 0x3 = Trace load and store instructions as P0 instructions. */
        uint32_t b0                    : 1;  /**< [  0:  0](RO)  */
#else /* Word 0 - Little Endian */
        uint32_t b0                    : 1;  /**< [  0:  0](RO)  */
        uint32_t instp0                : 2;  /**< [  2:  1](RO) Instruction P0 fields. This field control whether load and store instructions
                                                                   trace are traced as P0 instructions:
                                                                 0x0 = Do not trace load and store instructions as P0 instructions.
                                                                 0x1 = Trace load instructions as P0 instructions.
                                                                 0x2 = Trace store instructions as P0 instructions.
                                                                 0x3 = Trace load and store instructions as P0 instructions. */
        uint32_t bb                    : 1;  /**< [  3:  3](RO) Branch broadcast mode bit.
                                                                 0 = Branch broadcast mode is disabled.
                                                                 1 = Branch broadcast mode is enabled. */
        uint32_t cci                   : 1;  /**< [  4:  4](RO) Cycle counting instruction trace bit.
                                                                 0 = Cycle counting in instruction trace is disabled.
                                                                 1 = Cycle counting in instruction trace is enabled. */
        uint32_t reserved_5            : 1;
        uint32_t cid                   : 1;  /**< [  6:  6](R/W) Context ID tracing bit.
                                                                 0 = Context ID tracing is disabled.
                                                                 1 = Context ID tracing is enabled. */
        uint32_t vmid                  : 1;  /**< [  7:  7](R/W) VMID tracing bit.
                                                                 0 = VMID tracing is disabled.
                                                                 1 = VMID tracing is enabled. */
        uint32_t cond                  : 3;  /**< [ 10:  8](RO) Conditional instruction tracing bit. The permitted values are:
                                                                 0x0 = Conditional instruction tracing is disabled.
                                                                 0x1 = Conditional load instructions are traced.
                                                                 0x2 = Conditional store instructions are traced.
                                                                 0x3 = Conditional load and store instructions are traced.
                                                                 0x7 = All conditional instructions are traced.
                                                                 All other values are reserved. */
        uint32_t ts                    : 1;  /**< [ 11: 11](R/W) Global timestamp tracing bit.
                                                                 0 = Global timestamp tracing is not enabled.
                                                                 1 = Global timestamp tracing is enabled. */
        uint32_t rs                    : 1;  /**< [ 12: 12](R/W) Return stack enable bit.
                                                                 0 = Return stack is not enabled.
                                                                 1 = Return stack is enabled. */
        uint32_t qe                    : 2;  /**< [ 14: 13](RO) Q element enable field.
                                                                 0x0 = Q elements are disabled.
                                                                 0x1 = Q elements with instruction counts are enabled.
                                                                      Q elements without instruction counts are disabled.
                                                                 0x2 = Reserved.
                                                                 0x3 = Q elements with and without instruction counts are enabled.

                                                                 These fields must be set to 0x0 if any of the following are true:
                                                                      1. TRC()_TRCCONFIGR[INSTP0] is not 0x0.
                                                                      2. TRC()_TRCCONFIGR[COND] is not 0x0.
                                                                      3. TRC()_TRCCONFIGR[BB] is not 0. */
        uint32_t vmidopt               : 1;  /**< [ 15: 15](R/W) Reserved. */
        uint32_t da                    : 1;  /**< [ 16: 16](RO) Data address tracing bit.
                                                                 0 = The data address tracing is disabled.
                                                                 1 = The data address tracing is enabled when [INSTP0] is not 0x0. */
        uint32_t dv                    : 1;  /**< [ 17: 17](RO) Data value tracing bit.
                                                                 0 = The data value tracing is disabled.
                                                                 1 = The data value tracing is enabled when [INSTP0] is not 0x0. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcconfigr bdk_trcx_trcconfigr_t;

static inline uint64_t BDK_TRCX_TRCCONFIGR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCCONFIGR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30010ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030010ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030010ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030010ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030010ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCCONFIGR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCCONFIGR(a) bdk_trcx_trcconfigr_t
#define bustype_BDK_TRCX_TRCCONFIGR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCCONFIGR(a) "TRCX_TRCCONFIGR"
#define busnum_BDK_TRCX_TRCCONFIGR(a) (a)
#define arguments_BDK_TRCX_TRCCONFIGR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcdevaff0
 *
 * TRC/ETM Management Device Affinity Register 0
 * This register returns the lower 32 bits of the PE MPIDR, that is MPIDR[31:0].
 */
union bdk_trcx_trcdevaff0
{
    uint32_t u;
    struct bdk_trcx_trcdevaff0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t aff2                  : 8;  /**< [ 23: 16](RO/H) AFF2, this is node id. */
        uint32_t aff1                  : 8;  /**< [ 15:  8](RO/H) AFF1, this is the group of 16 cores within a node */
        uint32_t aff0                  : 8;  /**< [  7:  0](RO/H) AFF0, this is the core within a group of 16 */
#else /* Word 0 - Little Endian */
        uint32_t aff0                  : 8;  /**< [  7:  0](RO/H) AFF0, this is the core within a group of 16 */
        uint32_t aff1                  : 8;  /**< [ 15:  8](RO/H) AFF1, this is the group of 16 cores within a node */
        uint32_t aff2                  : 8;  /**< [ 23: 16](RO/H) AFF2, this is node id. */
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcdevaff0_s cn; */
};
typedef union bdk_trcx_trcdevaff0 bdk_trcx_trcdevaff0_t;

static inline uint64_t BDK_TRCX_TRCDEVAFF0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCDEVAFF0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fa8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fa8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fa8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fa8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fa8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCDEVAFF0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCDEVAFF0(a) bdk_trcx_trcdevaff0_t
#define bustype_BDK_TRCX_TRCDEVAFF0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCDEVAFF0(a) "TRCX_TRCDEVAFF0"
#define busnum_BDK_TRCX_TRCDEVAFF0(a) (a)
#define arguments_BDK_TRCX_TRCDEVAFF0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcdevaff1
 *
 * TRC/ETM Management Device Affinity Register 1
 * This register returns the upper 32 bits of the PE MPIDR, that is MPIDR[63:32].
 */
union bdk_trcx_trcdevaff1
{
    uint32_t u;
    struct bdk_trcx_trcdevaff1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcdevaff1_s cn; */
};
typedef union bdk_trcx_trcdevaff1 bdk_trcx_trcdevaff1_t;

static inline uint64_t BDK_TRCX_TRCDEVAFF1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCDEVAFF1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30facll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030facll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030facll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030facll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030facll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCDEVAFF1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCDEVAFF1(a) bdk_trcx_trcdevaff1_t
#define bustype_BDK_TRCX_TRCDEVAFF1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCDEVAFF1(a) "TRCX_TRCDEVAFF1"
#define busnum_BDK_TRCX_TRCDEVAFF1(a) (a)
#define arguments_BDK_TRCX_TRCDEVAFF1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcdevarch
 *
 * TRC/ETM Device Architecture Register
 * Identifies the programmers' model architecture.
 */
union bdk_trcx_trcdevarch
{
    uint32_t u;
    struct bdk_trcx_trcdevarch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. This is ARM-limited.

                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.

                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by Arm this is the minor revision.
                                                                 For TRC, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by Arm this is further subdivided.
                                                                 For TRC:
                                                                  Bits [15:12] are the architecture version, 0x1.
                                                                  Bits [11:0] are the architecture part number, 0xA14.
                                                                 This corresponds to TRC architecture version TRCv2. */
#else /* Word 0 - Little Endian */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by Arm this is further subdivided.
                                                                 For TRC:
                                                                  Bits [15:12] are the architecture version, 0x1.
                                                                  Bits [11:0] are the architecture part number, 0xA14.
                                                                 This corresponds to TRC architecture version TRCv2. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by Arm this is the minor revision.
                                                                 For TRC, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. This is ARM-limited.

                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.

                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcdevarch_s cn8; */
    struct bdk_trcx_trcdevarch_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. This is Arm Limited.

                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.

                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by Arm this is the minor revision.
                                                                 For TRC, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by Arm this is further subdivided.
                                                                 For TRC:
                                                                  Bits [15:12] are the architecture version, 0x1.
                                                                  Bits [11:0] are the architecture part number, 0xA14.
                                                                 This corresponds to TRC architecture version TRCv2. */
#else /* Word 0 - Little Endian */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by Arm this is further subdivided.
                                                                 For TRC:
                                                                  Bits [15:12] are the architecture version, 0x1.
                                                                  Bits [11:0] are the architecture part number, 0xA14.
                                                                 This corresponds to TRC architecture version TRCv2. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by Arm this is the minor revision.
                                                                 For TRC, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. This is Arm Limited.

                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.

                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcdevarch bdk_trcx_trcdevarch_t;

static inline uint64_t BDK_TRCX_TRCDEVARCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCDEVARCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fbcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fbcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fbcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fbcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fbcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCDEVARCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCDEVARCH(a) bdk_trcx_trcdevarch_t
#define bustype_BDK_TRCX_TRCDEVARCH(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCDEVARCH(a) "TRCX_TRCDEVARCH"
#define busnum_BDK_TRCX_TRCDEVARCH(a) (a)
#define arguments_BDK_TRCX_TRCDEVARCH(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcdevid
 *
 * TRC/ETM Device ID Register 0
 * Describes the component to the debugger.
 */
union bdk_trcx_trcdevid
{
    uint32_t u;
    struct bdk_trcx_trcdevid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_26_31        : 6;
        uint32_t inout_gate            : 2;  /**< [ 25: 24](RO) Input/output options. Indicates presence of the input gate. If
                                                                     the CTM is not implemented, this field is 0x0.
                                                                 All other values are reserved.
                                                                 0x0 = TRC()_TRCGATE does not mask propagation of input events from
                                                                     external channels.
                                                                 0x1 = TRC()_TRCGATE masks propagation of input events from external
                                                                     channels. */
        uint32_t reserved_22_23        : 2;
        uint32_t numchan               : 6;  /**< [ 21: 16](RO) Number of ECT channels implemented. Implementation defined.
                                                                 For v8-A, valid values are:
                                                                 0x3 = 3 channels (0..2) implemented.
                                                                 0x4 = 4 channels (0..3) implemented.
                                                                 0x5 = 5 channels (0..4) implemented.
                                                                 0x6 = 6 channels (0..5) implemented.
                                                                 and so on up to 0x20.
                                                                 All other values are reserved. */
        uint32_t reserved_14_15        : 2;
        uint32_t numtrig               : 6;  /**< [ 13:  8](RO) Number of triggers implemented. implementation defined. This
                                                                     is one more than the index of the largest trigger, rather than
                                                                     the actual number of triggers.
                                                                 For v8-A, valid values are:
                                                                 0x3 = Up to three triggers (0..2) implemented.
                                                                 0x8 = Up to eight triggers (0..7) implemented.
                                                                 0x9 = Up to nine triggers (0..8) implemented.
                                                                 0xa = Up to 10 triggers (0..9) implemented.
                                                                 and so on up to 0x20.

                                                                 All other values are reserved. If the trace extension is implemented, this field
                                                                 must be at least 0x8. There is no guarantee that any of the implemented
                                                                 triggers, including the highest numbered, are connected to any components. */
        uint32_t reserved_5_7          : 3;
        uint32_t extmuxnum             : 5;  /**< [  4:  0](RO) Maximum number of external triggers available for multiplexing
                                                                     into the TRC. This relates only to additional external
                                                                     triggers outside those defined for v8-A. */
#else /* Word 0 - Little Endian */
        uint32_t extmuxnum             : 5;  /**< [  4:  0](RO) Maximum number of external triggers available for multiplexing
                                                                     into the TRC. This relates only to additional external
                                                                     triggers outside those defined for v8-A. */
        uint32_t reserved_5_7          : 3;
        uint32_t numtrig               : 6;  /**< [ 13:  8](RO) Number of triggers implemented. implementation defined. This
                                                                     is one more than the index of the largest trigger, rather than
                                                                     the actual number of triggers.
                                                                 For v8-A, valid values are:
                                                                 0x3 = Up to three triggers (0..2) implemented.
                                                                 0x8 = Up to eight triggers (0..7) implemented.
                                                                 0x9 = Up to nine triggers (0..8) implemented.
                                                                 0xa = Up to 10 triggers (0..9) implemented.
                                                                 and so on up to 0x20.

                                                                 All other values are reserved. If the trace extension is implemented, this field
                                                                 must be at least 0x8. There is no guarantee that any of the implemented
                                                                 triggers, including the highest numbered, are connected to any components. */
        uint32_t reserved_14_15        : 2;
        uint32_t numchan               : 6;  /**< [ 21: 16](RO) Number of ECT channels implemented. Implementation defined.
                                                                 For v8-A, valid values are:
                                                                 0x3 = 3 channels (0..2) implemented.
                                                                 0x4 = 4 channels (0..3) implemented.
                                                                 0x5 = 5 channels (0..4) implemented.
                                                                 0x6 = 6 channels (0..5) implemented.
                                                                 and so on up to 0x20.
                                                                 All other values are reserved. */
        uint32_t reserved_22_23        : 2;
        uint32_t inout_gate            : 2;  /**< [ 25: 24](RO) Input/output options. Indicates presence of the input gate. If
                                                                     the CTM is not implemented, this field is 0x0.
                                                                 All other values are reserved.
                                                                 0x0 = TRC()_TRCGATE does not mask propagation of input events from
                                                                     external channels.
                                                                 0x1 = TRC()_TRCGATE masks propagation of input events from external
                                                                     channels. */
        uint32_t reserved_26_31        : 6;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcdevid_s cn; */
};
typedef union bdk_trcx_trcdevid bdk_trcx_trcdevid_t;

static inline uint64_t BDK_TRCX_TRCDEVID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCDEVID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fc8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fc8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fc8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fc8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fc8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCDEVID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCDEVID(a) bdk_trcx_trcdevid_t
#define bustype_BDK_TRCX_TRCDEVID(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCDEVID(a) "TRCX_TRCDEVID"
#define busnum_BDK_TRCX_TRCDEVID(a) (a)
#define arguments_BDK_TRCX_TRCDEVID(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcdevtype
 *
 * TRC/ETM Device Type Register
 * Indicates to a debugger that this component is part of a processor's cross-trigger
 * interface.
 */
union bdk_trcx_trcdevtype
{
    uint32_t u;
    struct bdk_trcx_trcdevtype_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Subtype. Must read as 0x1. */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major type. Must read as 0x3. */
#else /* Word 0 - Little Endian */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major type. Must read as 0x3. */
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Subtype. Must read as 0x1. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcdevtype_s cn; */
};
typedef union bdk_trcx_trcdevtype bdk_trcx_trcdevtype_t;

static inline uint64_t BDK_TRCX_TRCDEVTYPE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCDEVTYPE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fccll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fccll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fccll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fccll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fccll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCDEVTYPE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCDEVTYPE(a) bdk_trcx_trcdevtype_t
#define bustype_BDK_TRCX_TRCDEVTYPE(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCDEVTYPE(a) "TRCX_TRCDEVTYPE"
#define busnum_BDK_TRCX_TRCDEVTYPE(a) (a)
#define arguments_BDK_TRCX_TRCDEVTYPE(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcdvcmr0
 *
 * TRC/ETM Data Value Comparator Mask Register
 * This register contains a data mask value.
 */
union bdk_trcx_trcdvcmr0
{
    uint32_t u;
    struct bdk_trcx_trcdvcmr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcdvcmr0_s cn; */
};
typedef union bdk_trcx_trcdvcmr0 bdk_trcx_trcdvcmr0_t;

static inline uint64_t BDK_TRCX_TRCDVCMR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCDVCMR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30580ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCDVCMR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCDVCMR0(a) bdk_trcx_trcdvcmr0_t
#define bustype_BDK_TRCX_TRCDVCMR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCDVCMR0(a) "TRCX_TRCDVCMR0"
#define busnum_BDK_TRCX_TRCDVCMR0(a) (a)
#define arguments_BDK_TRCX_TRCDVCMR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcdvcvr0
 *
 * TRC/ETM Data Value Comparator Value Register
 * This register contains a data value.
 */
union bdk_trcx_trcdvcvr0
{
    uint32_t u;
    struct bdk_trcx_trcdvcvr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcdvcvr0_s cn; */
};
typedef union bdk_trcx_trcdvcvr0 bdk_trcx_trcdvcvr0_t;

static inline uint64_t BDK_TRCX_TRCDVCVR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCDVCVR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30500ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCDVCVR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCDVCVR0(a) bdk_trcx_trcdvcvr0_t
#define bustype_BDK_TRCX_TRCDVCVR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCDVCVR0(a) "TRCX_TRCDVCVR0"
#define busnum_BDK_TRCX_TRCDVCVR0(a) (a)
#define arguments_BDK_TRCX_TRCDVCVR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trceventctl0r
 *
 * TRC/ETM Event Control 0 Register
 * This register controls the tracing of arbitrary event.
 */
union bdk_trcx_trceventctl0r
{
    uint32_t u;
    struct bdk_trcx_trceventctl0r_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t event3                : 8;  /**< [ 31: 24](R/W) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3. */
        uint32_t event2                : 8;  /**< [ 23: 16](R/W) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3, 0x2. */
        uint32_t event1                : 8;  /**< [ 15:  8](R/W) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3, 0x2, 0x1. */
        uint32_t event0                : 8;  /**< [  7:  0](R/W) Always supported. */
#else /* Word 0 - Little Endian */
        uint32_t event0                : 8;  /**< [  7:  0](R/W) Always supported. */
        uint32_t event1                : 8;  /**< [ 15:  8](R/W) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3, 0x2, 0x1. */
        uint32_t event2                : 8;  /**< [ 23: 16](R/W) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3, 0x2. */
        uint32_t event3                : 8;  /**< [ 31: 24](R/W) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trceventctl0r_s cn8; */
    struct bdk_trcx_trceventctl0r_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t event3                : 8;  /**< [ 31: 24](R/W) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3. */
        uint32_t event2                : 8;  /**< [ 23: 16](RO) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3, 0x2. */
        uint32_t event1                : 8;  /**< [ 15:  8](RO) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3, 0x2, 0x1. */
        uint32_t event0                : 8;  /**< [  7:  0](RO) Always supported. */
#else /* Word 0 - Little Endian */
        uint32_t event0                : 8;  /**< [  7:  0](RO) Always supported. */
        uint32_t event1                : 8;  /**< [ 15:  8](RO) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3, 0x2, 0x1. */
        uint32_t event2                : 8;  /**< [ 23: 16](RO) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3, 0x2. */
        uint32_t event3                : 8;  /**< [ 31: 24](R/W) Only supported if TRC()_TRCIDR0[NUMEVENT] = 0x3. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trceventctl0r bdk_trcx_trceventctl0r_t;

static inline uint64_t BDK_TRCX_TRCEVENTCTL0R(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCEVENTCTL0R(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30020ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030020ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030020ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030020ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030020ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCEVENTCTL0R", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCEVENTCTL0R(a) bdk_trcx_trceventctl0r_t
#define bustype_BDK_TRCX_TRCEVENTCTL0R(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCEVENTCTL0R(a) "TRCX_TRCEVENTCTL0R"
#define busnum_BDK_TRCX_TRCEVENTCTL0R(a) (a)
#define arguments_BDK_TRCX_TRCEVENTCTL0R(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trceventctl1r
 *
 * TRC/ETM Event Control 1 Register
 * This register controls the behavior of events that TRC()_TRCEVENTCTL0R selects.
 */
union bdk_trcx_trceventctl1r
{
    uint32_t u;
    struct bdk_trcx_trceventctl1r_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_13_31        : 19;
        uint32_t lpoverride            : 1;  /**< [ 12: 12](R/W) Low power state over ride bit.
                                                                   0 = Trace unit low power state is not affected.
                                                                        The trace unit is enabled to enter low power state.
                                                                   1 = Trace unit low power behavior is overridden. */
        uint32_t atb                   : 1;  /**< [ 11: 11](R/W) AMBA trace bus trigger enable bit.
                                                                   0 = ATB trigger is disabled.
                                                                   1 = ATB trigger is enabled. */
        uint32_t reserved_5_10         : 6;
        uint32_t dataen                : 1;  /**< [  4:  4](R/W) Data event enable bit.
                                                                   0 = The trace unit does not generate an event element.
                                                                   1 = The trace unit generates an event element in the data trace stream. */
        uint32_t insten                : 4;  /**< [  3:  0](R/W) Instruction event[n] enable fields.
                                                                   0 = The trace unit does not generate an event[n] element.
                                                                   1 = The trace unit generates an event[n] element in the instruction trace stream. */
#else /* Word 0 - Little Endian */
        uint32_t insten                : 4;  /**< [  3:  0](R/W) Instruction event[n] enable fields.
                                                                   0 = The trace unit does not generate an event[n] element.
                                                                   1 = The trace unit generates an event[n] element in the instruction trace stream. */
        uint32_t dataen                : 1;  /**< [  4:  4](R/W) Data event enable bit.
                                                                   0 = The trace unit does not generate an event element.
                                                                   1 = The trace unit generates an event element in the data trace stream. */
        uint32_t reserved_5_10         : 6;
        uint32_t atb                   : 1;  /**< [ 11: 11](R/W) AMBA trace bus trigger enable bit.
                                                                   0 = ATB trigger is disabled.
                                                                   1 = ATB trigger is enabled. */
        uint32_t lpoverride            : 1;  /**< [ 12: 12](R/W) Low power state over ride bit.
                                                                   0 = Trace unit low power state is not affected.
                                                                        The trace unit is enabled to enter low power state.
                                                                   1 = Trace unit low power behavior is overridden. */
        uint32_t reserved_13_31        : 19;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trceventctl1r_s cn8; */
    struct bdk_trcx_trceventctl1r_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_13_31        : 19;
        uint32_t lpoverride            : 1;  /**< [ 12: 12](RAZ) Low power state over ride bit.
                                                                   0 = Trace unit low power state is not affected.
                                                                        The trace unit is enabled to enter low power state.
                                                                   1 = Trace unit low power behavior is overridden. */
        uint32_t atb                   : 1;  /**< [ 11: 11](RAZ) AMBA trace bus trigger enable bit.
                                                                   0 = ATB trigger is disabled.
                                                                   1 = ATB trigger is enabled. */
        uint32_t reserved_5_10         : 6;
        uint32_t dataen                : 1;  /**< [  4:  4](RAZ) Data event enable bit.
                                                                   0 = The trace unit does not generate an event element.
                                                                   1 = The trace unit generates an event element in the data trace stream. */
        uint32_t insten                : 4;  /**< [  3:  0](R/W) Instruction event[n] enable fields.
                                                                   0 = The trace unit does not generate an event[n] element.
                                                                   1 = The trace unit generates an event[n] element in the instruction trace stream. */
#else /* Word 0 - Little Endian */
        uint32_t insten                : 4;  /**< [  3:  0](R/W) Instruction event[n] enable fields.
                                                                   0 = The trace unit does not generate an event[n] element.
                                                                   1 = The trace unit generates an event[n] element in the instruction trace stream. */
        uint32_t dataen                : 1;  /**< [  4:  4](RAZ) Data event enable bit.
                                                                   0 = The trace unit does not generate an event element.
                                                                   1 = The trace unit generates an event element in the data trace stream. */
        uint32_t reserved_5_10         : 6;
        uint32_t atb                   : 1;  /**< [ 11: 11](RAZ) AMBA trace bus trigger enable bit.
                                                                   0 = ATB trigger is disabled.
                                                                   1 = ATB trigger is enabled. */
        uint32_t lpoverride            : 1;  /**< [ 12: 12](RAZ) Low power state over ride bit.
                                                                   0 = Trace unit low power state is not affected.
                                                                        The trace unit is enabled to enter low power state.
                                                                   1 = Trace unit low power behavior is overridden. */
        uint32_t reserved_13_31        : 19;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trceventctl1r bdk_trcx_trceventctl1r_t;

static inline uint64_t BDK_TRCX_TRCEVENTCTL1R(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCEVENTCTL1R(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30024ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030024ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030024ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030024ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030024ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCEVENTCTL1R", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCEVENTCTL1R(a) bdk_trcx_trceventctl1r_t
#define bustype_BDK_TRCX_TRCEVENTCTL1R(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCEVENTCTL1R(a) "TRCX_TRCEVENTCTL1R"
#define busnum_BDK_TRCX_TRCEVENTCTL1R(a) (a)
#define arguments_BDK_TRCX_TRCEVENTCTL1R(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcextinselr
 *
 * TRC/ETM External Input Select Register
 * Set or read which external inputs are resources to trace unit.
 */
union bdk_trcx_trcextinselr
{
    uint32_t u;
    struct bdk_trcx_trcextinselr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sel3                  : 8;  /**< [ 31: 24](R/W) Select which external input is a resources to the trace unit. */
        uint32_t sel2                  : 8;  /**< [ 23: 16](R/W) Select which external input is a resources to the trace unit. */
        uint32_t sel1                  : 8;  /**< [ 15:  8](R/W) Select which external input is a resources to the trace unit. */
        uint32_t sel0                  : 8;  /**< [  7:  0](R/W) Select which external input is a resources to the trace unit. */
#else /* Word 0 - Little Endian */
        uint32_t sel0                  : 8;  /**< [  7:  0](R/W) Select which external input is a resources to the trace unit. */
        uint32_t sel1                  : 8;  /**< [ 15:  8](R/W) Select which external input is a resources to the trace unit. */
        uint32_t sel2                  : 8;  /**< [ 23: 16](R/W) Select which external input is a resources to the trace unit. */
        uint32_t sel3                  : 8;  /**< [ 31: 24](R/W) Select which external input is a resources to the trace unit. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcextinselr_s cn; */
};
typedef union bdk_trcx_trcextinselr bdk_trcx_trcextinselr_t;

static inline uint64_t BDK_TRCX_TRCEXTINSELR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCEXTINSELR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30120ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCEXTINSELR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCEXTINSELR(a) bdk_trcx_trcextinselr_t
#define bustype_BDK_TRCX_TRCEXTINSELR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCEXTINSELR(a) "TRCX_TRCEXTINSELR"
#define busnum_BDK_TRCX_TRCEXTINSELR(a) (a)
#define arguments_BDK_TRCX_TRCEXTINSELR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr0
 *
 * TRC/ETM ID Register 0
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr0
{
    uint32_t u;
    struct bdk_trcx_trcidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_30_31        : 2;
        uint32_t commopt               : 1;  /**< [ 29: 29](RO) Common mode field:
                                                                    0 = Common mode 0.
                                                                    1 = Common mode 1.

                                                                 For CNXXXX irrelevant since cycle counting is not implemented. */
        uint32_t tssize                : 5;  /**< [ 28: 24](RO) Global timestamp size field. The permitted values are:
                                                                    0x0 = Global timestamping is not implemented.
                                                                    0x6 = Implementation supports a maximum global timestamp of 48 bits.
                                                                    0x8 = Implementation supports a maximum global timestamp of 64 bits.
                                                                    _ all other values are reserved. */
        uint32_t reserved_18_23        : 6;
        uint32_t trcexdata             : 1;  /**< [ 17: 17](RO) Indicate support for tracing of data transfer for exceptions and exception returns.
                                                                    0 = Implemented.
                                                                    1 = Not Implemented. */
        uint32_t qsupp                 : 2;  /**< [ 16: 15](RO) Q elements support field. The permitted values:
                                                                    0x0 = Q Elements support is not implemented.
                                                                    0x1 = Q Elements support is implemented and only support Q elements
                                                                               with instruction count.
                                                                    0x2 = Q Elements support is implemented and only support Q elements
                                                                               without instruction count.
                                                                    0x3 = Q Elements support is implemented and support Q elements
                                                                               with and without instruction count. */
        uint32_t qfilt                 : 1;  /**< [ 14: 14](RO) When [QSUPP] \> 0x0, this is Q element filtering support field.
                                                                    0 = Q element filtering is not implemented.
                                                                    1 = Q element filtering is implemented. */
        uint32_t condtype              : 2;  /**< [ 13: 12](RO) Conditional tracing field.  The permitted values are:
                                                                    0x0 = The trace unit indicates only if the conditional instruction
                                                                          pass or fail its condition code check.
                                                                    0x1 = The trace unit provides the value of APSR condition flags, for
                                                                          a conditional instruction.
                                                                    all other values are reserved. */
        uint32_t numevent              : 2;  /**< [ 11: 10](RO) Number of event field. Indicates how many event a trace unit support.
                                                                    0x0 = The trace unit supports 1 event.
                                                                    0x1 = The trace unit supports 2 events.
                                                                    0x2 = The trace unit supports 3 events.
                                                                    0x3 = The trace unit supports 4 events. */
        uint32_t retstack              : 1;  /**< [  9:  9](RO) Return stack bit.
                                                                    0 = The return stack is not implemented.
                                                                    1 = The return stack is implemented. */
        uint32_t reserved_8            : 1;
        uint32_t trccci                : 1;  /**< [  7:  7](RO) Cycle count instruction bit.
                                                                    0 = Cycle count in instruction trace is not implemented.
                                                                    1 = Cycle count in instruction trace is implemented. */
        uint32_t trccond               : 1;  /**< [  6:  6](RO) Conditional instruction tracing support bit.
                                                                    0 = Conditional instruction tracing is not supported.
                                                                    1 = Conditional instruction tracing is supported. */
        uint32_t trcbb                 : 1;  /**< [  5:  5](RO) Branch broadcast tracing support bit.
                                                                    0 = Branch broadcast tracing is not supported.
                                                                    1 = Branch broadcast tracing is supported. */
        uint32_t trcdata               : 2;  /**< [  4:  3](RO) Conditional tracing field. The permitted values are:
                                                                    0x0 = Data tracing is not supported.
                                                                    0x3 = Data tracing is supported. */
        uint32_t reserved_1_2          : 2;
        uint32_t bit0                  : 1;  /**< [  0:  0](RO) Reserved 1. */
#else /* Word 0 - Little Endian */
        uint32_t bit0                  : 1;  /**< [  0:  0](RO) Reserved 1. */
        uint32_t reserved_1_2          : 2;
        uint32_t trcdata               : 2;  /**< [  4:  3](RO) Conditional tracing field. The permitted values are:
                                                                    0x0 = Data tracing is not supported.
                                                                    0x3 = Data tracing is supported. */
        uint32_t trcbb                 : 1;  /**< [  5:  5](RO) Branch broadcast tracing support bit.
                                                                    0 = Branch broadcast tracing is not supported.
                                                                    1 = Branch broadcast tracing is supported. */
        uint32_t trccond               : 1;  /**< [  6:  6](RO) Conditional instruction tracing support bit.
                                                                    0 = Conditional instruction tracing is not supported.
                                                                    1 = Conditional instruction tracing is supported. */
        uint32_t trccci                : 1;  /**< [  7:  7](RO) Cycle count instruction bit.
                                                                    0 = Cycle count in instruction trace is not implemented.
                                                                    1 = Cycle count in instruction trace is implemented. */
        uint32_t reserved_8            : 1;
        uint32_t retstack              : 1;  /**< [  9:  9](RO) Return stack bit.
                                                                    0 = The return stack is not implemented.
                                                                    1 = The return stack is implemented. */
        uint32_t numevent              : 2;  /**< [ 11: 10](RO) Number of event field. Indicates how many event a trace unit support.
                                                                    0x0 = The trace unit supports 1 event.
                                                                    0x1 = The trace unit supports 2 events.
                                                                    0x2 = The trace unit supports 3 events.
                                                                    0x3 = The trace unit supports 4 events. */
        uint32_t condtype              : 2;  /**< [ 13: 12](RO) Conditional tracing field.  The permitted values are:
                                                                    0x0 = The trace unit indicates only if the conditional instruction
                                                                          pass or fail its condition code check.
                                                                    0x1 = The trace unit provides the value of APSR condition flags, for
                                                                          a conditional instruction.
                                                                    all other values are reserved. */
        uint32_t qfilt                 : 1;  /**< [ 14: 14](RO) When [QSUPP] \> 0x0, this is Q element filtering support field.
                                                                    0 = Q element filtering is not implemented.
                                                                    1 = Q element filtering is implemented. */
        uint32_t qsupp                 : 2;  /**< [ 16: 15](RO) Q elements support field. The permitted values:
                                                                    0x0 = Q Elements support is not implemented.
                                                                    0x1 = Q Elements support is implemented and only support Q elements
                                                                               with instruction count.
                                                                    0x2 = Q Elements support is implemented and only support Q elements
                                                                               without instruction count.
                                                                    0x3 = Q Elements support is implemented and support Q elements
                                                                               with and without instruction count. */
        uint32_t trcexdata             : 1;  /**< [ 17: 17](RO) Indicate support for tracing of data transfer for exceptions and exception returns.
                                                                    0 = Implemented.
                                                                    1 = Not Implemented. */
        uint32_t reserved_18_23        : 6;
        uint32_t tssize                : 5;  /**< [ 28: 24](RO) Global timestamp size field. The permitted values are:
                                                                    0x0 = Global timestamping is not implemented.
                                                                    0x6 = Implementation supports a maximum global timestamp of 48 bits.
                                                                    0x8 = Implementation supports a maximum global timestamp of 64 bits.
                                                                    _ all other values are reserved. */
        uint32_t commopt               : 1;  /**< [ 29: 29](RO) Common mode field:
                                                                    0 = Common mode 0.
                                                                    1 = Common mode 1.

                                                                 For CNXXXX irrelevant since cycle counting is not implemented. */
        uint32_t reserved_30_31        : 2;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcidr0_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_30_31        : 2;
        uint32_t commopt               : 1;  /**< [ 29: 29](RO) Common mode field:
                                                                    0 = Common mode 0.
                                                                    1 = Common mode 1.

                                                                 For CNXXXX irrelevant since cycle counting is not implemented. */
        uint32_t tssize                : 5;  /**< [ 28: 24](RO) Global timestamp size field. The permitted values are:
                                                                    0x0 = Global timestamping is not implemented.
                                                                    0x6 = Implementation supports a maximum global timestamp of 48 bits.
                                                                    0x8 = Implementation supports a maximum global timestamp of 64 bits.
                                                                    _ all other values are reserved. */
        uint32_t reserved_18_23        : 6;
        uint32_t trcexdata             : 1;  /**< [ 17: 17](RO) Indicate support for tracing of data transfer for exceptions and exception returns.
                                                                    0 = Implemented.
                                                                    1 = Not Implemented. */
        uint32_t qsupp                 : 2;  /**< [ 16: 15](RO) Q elements support field. The permitted values:
                                                                    0x0 = Q Elements support is not implemented.
                                                                    0x1 = Q Elements support is implemented and only support Q elements
                                                                               with instruction count.
                                                                    0x2 = Q Elements support is implemented and only support Q elements
                                                                               without instruction count.
                                                                    0x3 = Q Elements support is implemented and support Q elements
                                                                               with and without instruction count. */
        uint32_t qfilt                 : 1;  /**< [ 14: 14](RO) When [QSUPP] \> 0x0, this is Q element filtering support field.
                                                                    0 = Q element filtering is not implemented.
                                                                    1 = Q element filtering is implemented. */
        uint32_t condtype              : 2;  /**< [ 13: 12](RO) Conditional tracing field.  The permitted values are:
                                                                    0x0 = The trace unit indicates only if the conditional instruction
                                                                          pass or fail its condition code check.
                                                                    0x1 = The trace unit provides the value of APSR condition flags, for
                                                                          a conditional instruction.
                                                                    all other values are reserved. */
        uint32_t numevent              : 2;  /**< [ 11: 10](RO) Number of event field. Indicates how many event a trace unit support.
                                                                    0x0 = The trace unit supports 1 event.
                                                                    0x1 = The trace unit supports 2 events.
                                                                    0x2 = The trace unit supports 3 events.
                                                                    0x3 = The trace unit supports 4 events. */
        uint32_t retstack              : 1;  /**< [  9:  9](RO) Return stack bit.
                                                                    0 = The return stack is not implemented.
                                                                    1 = The return stack is implemented. */
        uint32_t reserved_8            : 1;
        uint32_t trccci                : 1;  /**< [  7:  7](RO) Cycle count instruction bit.
                                                                    0 = Cycle count in instruction trace is not implemented.
                                                                    1 = Cycle count in instruction trace is implemented. */
        uint32_t trccond               : 1;  /**< [  6:  6](RO) Conditional instruction tracing support bit.
                                                                    0 = Conditional instruction tracing is not supported.
                                                                    1 = Conditional instruction tracing is supported. */
        uint32_t trcbb                 : 1;  /**< [  5:  5](RO) Branch broadcast tracing support bit.
                                                                    0 = Branch broadcast tracing is not supported.
                                                                    1 = Branch broadcast tracing is supported. */
        uint32_t trcdata               : 2;  /**< [  4:  3](RO) Conditional tracing field. The permitted values are:
                                                                    0x0 = Data tracing is not supported.
                                                                    0x3 = Data tracing is supported. */
        uint32_t intp0                 : 2;  /**< [  2:  1](RO) P0 tracing support field. The permitted values are:
                                                                    0x0 = Tracing of load and store instruction as P0 element is not supported.
                                                                    0x3 = Tracing of load and store instruction as P0 element is supported. */
        uint32_t bit0                  : 1;  /**< [  0:  0](RO) Reserved 1. */
#else /* Word 0 - Little Endian */
        uint32_t bit0                  : 1;  /**< [  0:  0](RO) Reserved 1. */
        uint32_t intp0                 : 2;  /**< [  2:  1](RO) P0 tracing support field. The permitted values are:
                                                                    0x0 = Tracing of load and store instruction as P0 element is not supported.
                                                                    0x3 = Tracing of load and store instruction as P0 element is supported. */
        uint32_t trcdata               : 2;  /**< [  4:  3](RO) Conditional tracing field. The permitted values are:
                                                                    0x0 = Data tracing is not supported.
                                                                    0x3 = Data tracing is supported. */
        uint32_t trcbb                 : 1;  /**< [  5:  5](RO) Branch broadcast tracing support bit.
                                                                    0 = Branch broadcast tracing is not supported.
                                                                    1 = Branch broadcast tracing is supported. */
        uint32_t trccond               : 1;  /**< [  6:  6](RO) Conditional instruction tracing support bit.
                                                                    0 = Conditional instruction tracing is not supported.
                                                                    1 = Conditional instruction tracing is supported. */
        uint32_t trccci                : 1;  /**< [  7:  7](RO) Cycle count instruction bit.
                                                                    0 = Cycle count in instruction trace is not implemented.
                                                                    1 = Cycle count in instruction trace is implemented. */
        uint32_t reserved_8            : 1;
        uint32_t retstack              : 1;  /**< [  9:  9](RO) Return stack bit.
                                                                    0 = The return stack is not implemented.
                                                                    1 = The return stack is implemented. */
        uint32_t numevent              : 2;  /**< [ 11: 10](RO) Number of event field. Indicates how many event a trace unit support.
                                                                    0x0 = The trace unit supports 1 event.
                                                                    0x1 = The trace unit supports 2 events.
                                                                    0x2 = The trace unit supports 3 events.
                                                                    0x3 = The trace unit supports 4 events. */
        uint32_t condtype              : 2;  /**< [ 13: 12](RO) Conditional tracing field.  The permitted values are:
                                                                    0x0 = The trace unit indicates only if the conditional instruction
                                                                          pass or fail its condition code check.
                                                                    0x1 = The trace unit provides the value of APSR condition flags, for
                                                                          a conditional instruction.
                                                                    all other values are reserved. */
        uint32_t qfilt                 : 1;  /**< [ 14: 14](RO) When [QSUPP] \> 0x0, this is Q element filtering support field.
                                                                    0 = Q element filtering is not implemented.
                                                                    1 = Q element filtering is implemented. */
        uint32_t qsupp                 : 2;  /**< [ 16: 15](RO) Q elements support field. The permitted values:
                                                                    0x0 = Q Elements support is not implemented.
                                                                    0x1 = Q Elements support is implemented and only support Q elements
                                                                               with instruction count.
                                                                    0x2 = Q Elements support is implemented and only support Q elements
                                                                               without instruction count.
                                                                    0x3 = Q Elements support is implemented and support Q elements
                                                                               with and without instruction count. */
        uint32_t trcexdata             : 1;  /**< [ 17: 17](RO) Indicate support for tracing of data transfer for exceptions and exception returns.
                                                                    0 = Implemented.
                                                                    1 = Not Implemented. */
        uint32_t reserved_18_23        : 6;
        uint32_t tssize                : 5;  /**< [ 28: 24](RO) Global timestamp size field. The permitted values are:
                                                                    0x0 = Global timestamping is not implemented.
                                                                    0x6 = Implementation supports a maximum global timestamp of 48 bits.
                                                                    0x8 = Implementation supports a maximum global timestamp of 64 bits.
                                                                    _ all other values are reserved. */
        uint32_t commopt               : 1;  /**< [ 29: 29](RO) Common mode field:
                                                                    0 = Common mode 0.
                                                                    1 = Common mode 1.

                                                                 For CNXXXX irrelevant since cycle counting is not implemented. */
        uint32_t reserved_30_31        : 2;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_trcx_trcidr0_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_30_31        : 2;
        uint32_t commopt               : 1;  /**< [ 29: 29](RO) Common mode field:
                                                                    0 = Common mode 0.
                                                                    1 = Common mode 1.

                                                                 For CNXXXX irrelevant since cycle counting is not implemented. */
        uint32_t tssize                : 5;  /**< [ 28: 24](RO) Global timestamp size field. The permitted values are:
                                                                    0x0 = Global timestamping is not implemented.
                                                                    0x6 = Implementation supports a maximum global timestamp of 48 bits.
                                                                    0x8 = Implementation supports a maximum global timestamp of 64 bits.
                                                                    _ all other values are reserved. */
        uint32_t reserved_18_23        : 6;
        uint32_t trcexdata             : 1;  /**< [ 17: 17](RO) Indicate support for tracing of data transfer for exceptions and exception returns.
                                                                    0 = Implemented.
                                                                    1 = Not Implemented. */
        uint32_t qsupp                 : 2;  /**< [ 16: 15](RO) Q elements support field. The permitted values:
                                                                    0x0 = Q Elements support is not implemented.
                                                                    0x1 = Q Elements support is implemented and only support Q elements
                                                                               with instruction count.
                                                                    0x2 = Q Elements support is implemented and only support Q elements
                                                                               without instruction count.
                                                                    0x3 = Q Elements support is implemented and support Q elements
                                                                               with and without instruction count. */
        uint32_t qfilt                 : 1;  /**< [ 14: 14](RO) When [QSUPP] \> 0x0, this is Q element filtering support field.
                                                                    0 = Q element filtering is not implemented.
                                                                    1 = Q element filtering is implemented. */
        uint32_t condtype              : 2;  /**< [ 13: 12](RO) Conditional tracing field.  The permitted values are:
                                                                    0x0 = The trace unit indicates only if the conditional instruction
                                                                          pass or fail its condition code check.
                                                                    0x1 = The trace unit provides the value of APSR condition flags, for
                                                                          a conditional instruction.
                                                                    all other values are reserved. */
        uint32_t numevent              : 2;  /**< [ 11: 10](RO) Number of event field. Indicates how many event a trace unit support.
                                                                    0x0 = The trace unit supports 1 event.
                                                                    0x1 = The trace unit supports 2 events.
                                                                    0x2 = The trace unit supports 3 events.
                                                                    0x3 = The trace unit supports 4 events. */
        uint32_t retstack              : 1;  /**< [  9:  9](RO) Return stack bit.
                                                                    0 = The return stack is not implemented.
                                                                    1 = The return stack is implemented. */
        uint32_t reserved_8            : 1;
        uint32_t trccci                : 1;  /**< [  7:  7](RO) Cycle count instruction bit.
                                                                    0 = Cycle count in instruction trace is not implemented.
                                                                    1 = Cycle count in instruction trace is implemented. */
        uint32_t trccond               : 1;  /**< [  6:  6](RO) Conditional instruction tracing support bit.
                                                                    0 = Conditional instruction tracing is not supported.
                                                                    1 = Conditional instruction tracing is supported. */
        uint32_t trcbb                 : 1;  /**< [  5:  5](RO) Branch broadcast tracing support bit.
                                                                    0 = Branch broadcast tracing is not supported.
                                                                    1 = Branch broadcast tracing is supported. */
        uint32_t trcdata               : 2;  /**< [  4:  3](RO) Conditional tracing field. The permitted values are:
                                                                    0x0 = Data tracing is not supported.
                                                                    0x3 = Data tracing is supported. */
        uint32_t instp0                : 2;  /**< [  2:  1](RO) P0 tracing support field. The permitted values are:
                                                                    0x0 = Tracing of load and store instruction as P0 element is not supported.
                                                                    0x3 = Tracing of load and store instruction as P0 element is supported. */
        uint32_t bit0                  : 1;  /**< [  0:  0](RO) Reserved 1. */
#else /* Word 0 - Little Endian */
        uint32_t bit0                  : 1;  /**< [  0:  0](RO) Reserved 1. */
        uint32_t instp0                : 2;  /**< [  2:  1](RO) P0 tracing support field. The permitted values are:
                                                                    0x0 = Tracing of load and store instruction as P0 element is not supported.
                                                                    0x3 = Tracing of load and store instruction as P0 element is supported. */
        uint32_t trcdata               : 2;  /**< [  4:  3](RO) Conditional tracing field. The permitted values are:
                                                                    0x0 = Data tracing is not supported.
                                                                    0x3 = Data tracing is supported. */
        uint32_t trcbb                 : 1;  /**< [  5:  5](RO) Branch broadcast tracing support bit.
                                                                    0 = Branch broadcast tracing is not supported.
                                                                    1 = Branch broadcast tracing is supported. */
        uint32_t trccond               : 1;  /**< [  6:  6](RO) Conditional instruction tracing support bit.
                                                                    0 = Conditional instruction tracing is not supported.
                                                                    1 = Conditional instruction tracing is supported. */
        uint32_t trccci                : 1;  /**< [  7:  7](RO) Cycle count instruction bit.
                                                                    0 = Cycle count in instruction trace is not implemented.
                                                                    1 = Cycle count in instruction trace is implemented. */
        uint32_t reserved_8            : 1;
        uint32_t retstack              : 1;  /**< [  9:  9](RO) Return stack bit.
                                                                    0 = The return stack is not implemented.
                                                                    1 = The return stack is implemented. */
        uint32_t numevent              : 2;  /**< [ 11: 10](RO) Number of event field. Indicates how many event a trace unit support.
                                                                    0x0 = The trace unit supports 1 event.
                                                                    0x1 = The trace unit supports 2 events.
                                                                    0x2 = The trace unit supports 3 events.
                                                                    0x3 = The trace unit supports 4 events. */
        uint32_t condtype              : 2;  /**< [ 13: 12](RO) Conditional tracing field.  The permitted values are:
                                                                    0x0 = The trace unit indicates only if the conditional instruction
                                                                          pass or fail its condition code check.
                                                                    0x1 = The trace unit provides the value of APSR condition flags, for
                                                                          a conditional instruction.
                                                                    all other values are reserved. */
        uint32_t qfilt                 : 1;  /**< [ 14: 14](RO) When [QSUPP] \> 0x0, this is Q element filtering support field.
                                                                    0 = Q element filtering is not implemented.
                                                                    1 = Q element filtering is implemented. */
        uint32_t qsupp                 : 2;  /**< [ 16: 15](RO) Q elements support field. The permitted values:
                                                                    0x0 = Q Elements support is not implemented.
                                                                    0x1 = Q Elements support is implemented and only support Q elements
                                                                               with instruction count.
                                                                    0x2 = Q Elements support is implemented and only support Q elements
                                                                               without instruction count.
                                                                    0x3 = Q Elements support is implemented and support Q elements
                                                                               with and without instruction count. */
        uint32_t trcexdata             : 1;  /**< [ 17: 17](RO) Indicate support for tracing of data transfer for exceptions and exception returns.
                                                                    0 = Implemented.
                                                                    1 = Not Implemented. */
        uint32_t reserved_18_23        : 6;
        uint32_t tssize                : 5;  /**< [ 28: 24](RO) Global timestamp size field. The permitted values are:
                                                                    0x0 = Global timestamping is not implemented.
                                                                    0x6 = Implementation supports a maximum global timestamp of 48 bits.
                                                                    0x8 = Implementation supports a maximum global timestamp of 64 bits.
                                                                    _ all other values are reserved. */
        uint32_t commopt               : 1;  /**< [ 29: 29](RO) Common mode field:
                                                                    0 = Common mode 0.
                                                                    1 = Common mode 1.

                                                                 For CNXXXX irrelevant since cycle counting is not implemented. */
        uint32_t reserved_30_31        : 2;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcidr0 bdk_trcx_trcidr0_t;

static inline uint64_t BDK_TRCX_TRCIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc301e0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301e0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301e0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301e0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301e0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR0(a) bdk_trcx_trcidr0_t
#define bustype_BDK_TRCX_TRCIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR0(a) "TRCX_TRCIDR0"
#define busnum_BDK_TRCX_TRCIDR0(a) (a)
#define arguments_BDK_TRCX_TRCIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr1
 *
 * TRC/ETM ID Register 1
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr1
{
    uint32_t u;
    struct bdk_trcx_trcidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t designer              : 8;  /**< [ 31: 24](RO) Designer Cavium. */
        uint32_t reserved_16_23        : 8;
        uint32_t val1                  : 4;  /**< [ 15: 12](RO) Read as one for all 4 bits. */
        uint32_t archmaj               : 4;  /**< [ 11:  8](RO) ETMv4. */
        uint32_t archmin               : 4;  /**< [  7:  4](RO) ETMv4.1. */
        uint32_t revision              : 4;  /**< [  3:  0](RO) Revision 0. */
#else /* Word 0 - Little Endian */
        uint32_t revision              : 4;  /**< [  3:  0](RO) Revision 0. */
        uint32_t archmin               : 4;  /**< [  7:  4](RO) ETMv4.1. */
        uint32_t archmaj               : 4;  /**< [ 11:  8](RO) ETMv4. */
        uint32_t val1                  : 4;  /**< [ 15: 12](RO) Read as one for all 4 bits. */
        uint32_t reserved_16_23        : 8;
        uint32_t designer              : 8;  /**< [ 31: 24](RO) Designer Cavium. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr1_s cn8; */
    struct bdk_trcx_trcidr1_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t designer              : 8;  /**< [ 31: 24](RO) Designer Marvell (Cavium). */
        uint32_t reserved_16_23        : 8;
        uint32_t val1                  : 4;  /**< [ 15: 12](RO) Read as one for all 4 bits. */
        uint32_t archmaj               : 4;  /**< [ 11:  8](RO) ETMv4. */
        uint32_t archmin               : 4;  /**< [  7:  4](RO) ETMv4.1. */
        uint32_t revision              : 4;  /**< [  3:  0](RO) Revision 0. */
#else /* Word 0 - Little Endian */
        uint32_t revision              : 4;  /**< [  3:  0](RO) Revision 0. */
        uint32_t archmin               : 4;  /**< [  7:  4](RO) ETMv4.1. */
        uint32_t archmaj               : 4;  /**< [ 11:  8](RO) ETMv4. */
        uint32_t val1                  : 4;  /**< [ 15: 12](RO) Read as one for all 4 bits. */
        uint32_t reserved_16_23        : 8;
        uint32_t designer              : 8;  /**< [ 31: 24](RO) Designer Marvell (Cavium). */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcidr1 bdk_trcx_trcidr1_t;

static inline uint64_t BDK_TRCX_TRCIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc301e4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301e4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301e4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301e4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301e4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR1(a) bdk_trcx_trcidr1_t
#define bustype_BDK_TRCX_TRCIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR1(a) "TRCX_TRCIDR1"
#define busnum_BDK_TRCX_TRCIDR1(a) (a)
#define arguments_BDK_TRCX_TRCIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr10
 *
 * TRC/ETM ID Register 10
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr10
{
    uint32_t u;
    struct bdk_trcx_trcidr10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t nump1key              : 32; /**< [ 31:  0](RO) Indicates the number of P1 right-hand keys that the trace unit can use. The
                                                                 number includes normal and special keys. */
#else /* Word 0 - Little Endian */
        uint32_t nump1key              : 32; /**< [ 31:  0](RO) Indicates the number of P1 right-hand keys that the trace unit can use. The
                                                                 number includes normal and special keys. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr10_s cn; */
};
typedef union bdk_trcx_trcidr10 bdk_trcx_trcidr10_t;

static inline uint64_t BDK_TRCX_TRCIDR10(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR10(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30188ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030188ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030188ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030188ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030188ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR10", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR10(a) bdk_trcx_trcidr10_t
#define bustype_BDK_TRCX_TRCIDR10(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR10(a) "TRCX_TRCIDR10"
#define busnum_BDK_TRCX_TRCIDR10(a) (a)
#define arguments_BDK_TRCX_TRCIDR10(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr11
 *
 * TRC/ETM ID Register 11
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr11
{
    uint32_t u;
    struct bdk_trcx_trcidr11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t nump1spc              : 32; /**< [ 31:  0](RO) Indicates the number of special P1 right-hand keys that the trace unit can use. */
#else /* Word 0 - Little Endian */
        uint32_t nump1spc              : 32; /**< [ 31:  0](RO) Indicates the number of special P1 right-hand keys that the trace unit can use. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr11_s cn; */
};
typedef union bdk_trcx_trcidr11 bdk_trcx_trcidr11_t;

static inline uint64_t BDK_TRCX_TRCIDR11(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR11(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3018cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00803018cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00803018cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00803018cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00803018cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR11", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR11(a) bdk_trcx_trcidr11_t
#define bustype_BDK_TRCX_TRCIDR11(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR11(a) "TRCX_TRCIDR11"
#define busnum_BDK_TRCX_TRCIDR11(a) (a)
#define arguments_BDK_TRCX_TRCIDR11(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr12
 *
 * TRC/ETM ID Register 12
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr12
{
    uint32_t u;
    struct bdk_trcx_trcidr12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t numcondkey            : 32; /**< [ 31:  0](RO) Indicates the number of conditional instruction right-hand keys that the trace
                                                                 unit can use. The number includes normal and special keys. */
#else /* Word 0 - Little Endian */
        uint32_t numcondkey            : 32; /**< [ 31:  0](RO) Indicates the number of conditional instruction right-hand keys that the trace
                                                                 unit can use. The number includes normal and special keys. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr12_s cn; */
};
typedef union bdk_trcx_trcidr12 bdk_trcx_trcidr12_t;

static inline uint64_t BDK_TRCX_TRCIDR12(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR12(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30190ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030190ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030190ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030190ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030190ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR12", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR12(a) bdk_trcx_trcidr12_t
#define bustype_BDK_TRCX_TRCIDR12(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR12(a) "TRCX_TRCIDR12"
#define busnum_BDK_TRCX_TRCIDR12(a) (a)
#define arguments_BDK_TRCX_TRCIDR12(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr13
 *
 * TRC/ETM ID Register 13
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr13
{
    uint32_t u;
    struct bdk_trcx_trcidr13_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t numcondspc            : 32; /**< [ 31:  0](RO) Indicates the number of special conditional instruction right-hand keys that the
                                                                 trace unit can use. */
#else /* Word 0 - Little Endian */
        uint32_t numcondspc            : 32; /**< [ 31:  0](RO) Indicates the number of special conditional instruction right-hand keys that the
                                                                 trace unit can use. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr13_s cn; */
};
typedef union bdk_trcx_trcidr13 bdk_trcx_trcidr13_t;

static inline uint64_t BDK_TRCX_TRCIDR13(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR13(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30194ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030194ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030194ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030194ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030194ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR13", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR13(a) bdk_trcx_trcidr13_t
#define bustype_BDK_TRCX_TRCIDR13(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR13(a) "TRCX_TRCIDR13"
#define busnum_BDK_TRCX_TRCIDR13(a) (a)
#define arguments_BDK_TRCX_TRCIDR13(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr2
 *
 * TRC/ETM ID Register 2
 * This register returns the maximum size of data address and data value.
 */
union bdk_trcx_trcidr2
{
    uint32_t u;
    struct bdk_trcx_trcidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t vmidopt               : 2;  /**< [ 30: 29](RO) Read as one. */
        uint32_t ccsize                : 4;  /**< [ 28: 25](RO) Indicates the size of the cycle counter in bits minus 12. This field is 0x0 if
                                                                 cycle counting is not implemented, as indicated by TRC()_TRCIDR0[TRCCCI].

                                                                 For CNXXXX, 0x0 as does not implement a counter. */
        uint32_t dvsize                : 5;  /**< [ 24: 20](RO) Indicates the data value size in bytes.
                                                                   0x0 = Data value tracing is not supported. Therefore, an implementation must set
                                                                   TRCIDR0[TRCDATA]=0x0.
                                                                   0x4 = Maximum of 32-bit data value size.
                                                                   0x8 = Maximum of 64-bit data value size. This value is not permitted when tracing
                                                                   Armv6 and Armv7 PEs. */
        uint32_t dasize                : 5;  /**< [ 19: 15](RO) Indicates the data address size in bytes.
                                                                 0x0 = Data address tracing is not supported. Therefore, an implementation must
                                                                 also set TRC()_TRCIDR0[TRCDATA]=0x0.
                                                                 0x4 = Maximum of 32-bit data address size.
                                                                 0x8 = Maximum of 64-bit data address size. This value is not permitted when
                                                                 tracing Armv6 and Armv7 PEs.

                                                                 For CNXXXX, not supported. */
        uint32_t vmidsize              : 5;  /**< [ 14: 10](RO) Indicates the VMID size. 0x0 = VMID tracing is not supported. 0x1 = Maximum of
                                                                 eight-bit VMID
                                                                 size, so TRC()_TRCCONFIGR[VMID] is supported. 0x4 = Maximum of 16-bit VMID size, so
                                                                 TRC()_TRCCONFIGR[VMID] is supported.
                                                                 For CNXXXX, 16-bit. */
        uint32_t cidsize               : 5;  /**< [  9:  5](RO) Indicates the context ID size. The permitted values are:
                                                                   0x0 = Context ID tracing is not supported.
                                                                   0x4 = Maximum of 32-bit context ID size, so TRC()_TRCCONFIGR[CID] is
                                                                 supported.  32 bit contextID supported.

                                                                 For CNXXXX, 32-bit. */
        uint32_t iasize                : 5;  /**< [  4:  0](RO) Indicates the instruction address size.
                                                                 0x4 = Maximum of 32-bit address size.
                                                                 0x8 = Maximum of 64-bit address size. This value is not permitted when
                                                                 tracing Armv6 and Armv7 PEs.

                                                                 For CNXXXX, 64-bit. */
#else /* Word 0 - Little Endian */
        uint32_t iasize                : 5;  /**< [  4:  0](RO) Indicates the instruction address size.
                                                                 0x4 = Maximum of 32-bit address size.
                                                                 0x8 = Maximum of 64-bit address size. This value is not permitted when
                                                                 tracing Armv6 and Armv7 PEs.

                                                                 For CNXXXX, 64-bit. */
        uint32_t cidsize               : 5;  /**< [  9:  5](RO) Indicates the context ID size. The permitted values are:
                                                                   0x0 = Context ID tracing is not supported.
                                                                   0x4 = Maximum of 32-bit context ID size, so TRC()_TRCCONFIGR[CID] is
                                                                 supported.  32 bit contextID supported.

                                                                 For CNXXXX, 32-bit. */
        uint32_t vmidsize              : 5;  /**< [ 14: 10](RO) Indicates the VMID size. 0x0 = VMID tracing is not supported. 0x1 = Maximum of
                                                                 eight-bit VMID
                                                                 size, so TRC()_TRCCONFIGR[VMID] is supported. 0x4 = Maximum of 16-bit VMID size, so
                                                                 TRC()_TRCCONFIGR[VMID] is supported.
                                                                 For CNXXXX, 16-bit. */
        uint32_t dasize                : 5;  /**< [ 19: 15](RO) Indicates the data address size in bytes.
                                                                 0x0 = Data address tracing is not supported. Therefore, an implementation must
                                                                 also set TRC()_TRCIDR0[TRCDATA]=0x0.
                                                                 0x4 = Maximum of 32-bit data address size.
                                                                 0x8 = Maximum of 64-bit data address size. This value is not permitted when
                                                                 tracing Armv6 and Armv7 PEs.

                                                                 For CNXXXX, not supported. */
        uint32_t dvsize                : 5;  /**< [ 24: 20](RO) Indicates the data value size in bytes.
                                                                   0x0 = Data value tracing is not supported. Therefore, an implementation must set
                                                                   TRCIDR0[TRCDATA]=0x0.
                                                                   0x4 = Maximum of 32-bit data value size.
                                                                   0x8 = Maximum of 64-bit data value size. This value is not permitted when tracing
                                                                   Armv6 and Armv7 PEs. */
        uint32_t ccsize                : 4;  /**< [ 28: 25](RO) Indicates the size of the cycle counter in bits minus 12. This field is 0x0 if
                                                                 cycle counting is not implemented, as indicated by TRC()_TRCIDR0[TRCCCI].

                                                                 For CNXXXX, 0x0 as does not implement a counter. */
        uint32_t vmidopt               : 2;  /**< [ 30: 29](RO) Read as one. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr2_s cn; */
};
typedef union bdk_trcx_trcidr2 bdk_trcx_trcidr2_t;

static inline uint64_t BDK_TRCX_TRCIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc301e8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301e8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301e8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301e8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301e8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR2(a) bdk_trcx_trcidr2_t
#define bustype_BDK_TRCX_TRCIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR2(a) "TRCX_TRCIDR2"
#define busnum_BDK_TRCX_TRCIDR2(a) (a)
#define arguments_BDK_TRCX_TRCIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr3
 *
 * TRC/ETM ID Register 3
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr3
{
    uint32_t u;
    struct bdk_trcx_trcidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t noovflw               : 1;  /**< [ 31: 31](RO) Indicates if TRC()_TRCSTALLCTLR[NOOVERFLOW] is supported.

                                                                 For CNXXXX not supported. */
        uint32_t numproc               : 3;  /**< [ 30: 28](RO/H) Indicates the number of PEs available for tracing minus one.
                                                                 The reset value depends on the number of cores fuse-enabled in this part. */
        uint32_t sysstall              : 1;  /**< [ 27: 27](RO) Indicates if the implementation can support stall control:
                                                                   0 = The system does not support stall control of the PE.
                                                                   1 = The system can support stall control of the PE.

                                                                 CNXXXX supports stalling the PE. */
        uint32_t stallctl              : 1;  /**< [ 26: 26](RO) Indicates if the implementation can support stall control. */
        uint32_t syncpr                : 1;  /**< [ 25: 25](RO) Indicates if an implementation has a fixed synchronization period:
                                                                   0 = TRC()_TRCSYNCPR is read-write so software can change the synchronization period.
                                                                   1 = TRC()_TRCSYNCPR is read-only so the synchronization period is fixed. */
        uint32_t trcerr                : 1;  /**< [ 24: 24](RO) Indicates if TRC()_TRCVICTLR[TRCERR] is supported.

                                                                 For CNXXXX not supported, this means system errors are not traced. */
        uint32_t elns                  : 4;  /**< [ 23: 20](RO) In nonsecure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_NS] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_NS] are supported. */
        uint32_t els                   : 4;  /**< [ 19: 16](RO) In secure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_S] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_S] are supported.

                                                                 For CNXXXX, secure exception level tracing of EL0, EL1, and EL3 is supported. */
        uint32_t reserved_14_15        : 2;
        uint32_t numprocext            : 2;  /**< [ 13: 12](RO/H) Number of processors extension bits. Expands [NUMPROC] from 3 bits to 5
                                                                 bits. See [NUMPROC]. */
        uint32_t ccitmin               : 12; /**< [ 11:  0](RO) Indicates the minimum value that can be programmed in
                                                                 TRC()_TRCCCCTLR[THRESHOLD]. When cycle counting in the instruction trace is
                                                                 supported, that is TRC()_TRCIDR0[TRCCCI]=1, then the minimum value of this field
                                                                 is 0x1, otherwise it is 0x0.

                                                                 For CNXXXX, no support for cycle counting so this field is not applicable. */
#else /* Word 0 - Little Endian */
        uint32_t ccitmin               : 12; /**< [ 11:  0](RO) Indicates the minimum value that can be programmed in
                                                                 TRC()_TRCCCCTLR[THRESHOLD]. When cycle counting in the instruction trace is
                                                                 supported, that is TRC()_TRCIDR0[TRCCCI]=1, then the minimum value of this field
                                                                 is 0x1, otherwise it is 0x0.

                                                                 For CNXXXX, no support for cycle counting so this field is not applicable. */
        uint32_t numprocext            : 2;  /**< [ 13: 12](RO/H) Number of processors extension bits. Expands [NUMPROC] from 3 bits to 5
                                                                 bits. See [NUMPROC]. */
        uint32_t reserved_14_15        : 2;
        uint32_t els                   : 4;  /**< [ 19: 16](RO) In secure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_S] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_S] are supported.

                                                                 For CNXXXX, secure exception level tracing of EL0, EL1, and EL3 is supported. */
        uint32_t elns                  : 4;  /**< [ 23: 20](RO) In nonsecure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_NS] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_NS] are supported. */
        uint32_t trcerr                : 1;  /**< [ 24: 24](RO) Indicates if TRC()_TRCVICTLR[TRCERR] is supported.

                                                                 For CNXXXX not supported, this means system errors are not traced. */
        uint32_t syncpr                : 1;  /**< [ 25: 25](RO) Indicates if an implementation has a fixed synchronization period:
                                                                   0 = TRC()_TRCSYNCPR is read-write so software can change the synchronization period.
                                                                   1 = TRC()_TRCSYNCPR is read-only so the synchronization period is fixed. */
        uint32_t stallctl              : 1;  /**< [ 26: 26](RO) Indicates if the implementation can support stall control. */
        uint32_t sysstall              : 1;  /**< [ 27: 27](RO) Indicates if the implementation can support stall control:
                                                                   0 = The system does not support stall control of the PE.
                                                                   1 = The system can support stall control of the PE.

                                                                 CNXXXX supports stalling the PE. */
        uint32_t numproc               : 3;  /**< [ 30: 28](RO/H) Indicates the number of PEs available for tracing minus one.
                                                                 The reset value depends on the number of cores fuse-enabled in this part. */
        uint32_t noovflw               : 1;  /**< [ 31: 31](RO) Indicates if TRC()_TRCSTALLCTLR[NOOVERFLOW] is supported.

                                                                 For CNXXXX not supported. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr3_s cn8; */
    struct bdk_trcx_trcidr3_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t noovflw               : 1;  /**< [ 31: 31](RO) Indicates if TRC()_TRCSTALLCTLR[NOOVERFLOW] is supported.

                                                                 For CNXXXX not supported. */
        uint32_t numproc               : 3;  /**< [ 30: 28](RO/H) Indicates the number of PEs available for tracing minus one.
                                                                 The reset value depends on the number of cores fuse-enabled in this part. */
        uint32_t sysstall              : 1;  /**< [ 27: 27](RO) Indicates if the implementation can support stall control:
                                                                   0 = The system does not support stall control of the PE.
                                                                   1 = The system can support stall control of the PE.

                                                                 CNXXXX supports stalling the PE. */
        uint32_t stallctl              : 1;  /**< [ 26: 26](RO) Indicates if the implementation can support stall control. */
        uint32_t syncpr                : 1;  /**< [ 25: 25](RO) Indicates if an implementation has a fixed synchronization period:
                                                                   0 = TRC()_TRCSYNCPR is read-write so software can change the synchronization period.
                                                                   1 = TRC()_TRCSYNCPR is read-only so the synchronization period is fixed. */
        uint32_t trcerr                : 1;  /**< [ 24: 24](RO) Indicates if TRC()_TRCVICTLR[TRCERR] is supported.

                                                                 For CNXXXX not supported, this means system errors are not traced. */
        uint32_t elns                  : 4;  /**< [ 23: 20](RO) In nonsecure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_NS] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_NS] are supported. */
        uint32_t els                   : 4;  /**< [ 19: 16](RO) In secure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_S] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_S] are supported.

                                                                 For CNXXXX, secure exception level tracing of EL0, EL1, and EL3 is supported. */
        uint32_t reserved_12_15        : 4;
        uint32_t ccitmin               : 12; /**< [ 11:  0](RO) Indicates the minimum value that can be programmed in
                                                                 TRC()_TRCCCCTLR[THRESHOLD]. When cycle counting in the instruction trace is
                                                                 supported, that is TRC()_TRCIDR0[TRCCCI]=1, then the minimum value of this field
                                                                 is 0x1, otherwise it is 0x0.

                                                                 For CNXXXX, no support for cycle counting so this field is not applicable. */
#else /* Word 0 - Little Endian */
        uint32_t ccitmin               : 12; /**< [ 11:  0](RO) Indicates the minimum value that can be programmed in
                                                                 TRC()_TRCCCCTLR[THRESHOLD]. When cycle counting in the instruction trace is
                                                                 supported, that is TRC()_TRCIDR0[TRCCCI]=1, then the minimum value of this field
                                                                 is 0x1, otherwise it is 0x0.

                                                                 For CNXXXX, no support for cycle counting so this field is not applicable. */
        uint32_t reserved_12_15        : 4;
        uint32_t els                   : 4;  /**< [ 19: 16](RO) In secure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_S] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_S] are supported.

                                                                 For CNXXXX, secure exception level tracing of EL0, EL1, and EL3 is supported. */
        uint32_t elns                  : 4;  /**< [ 23: 20](RO) In nonsecure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_NS] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_NS] are supported. */
        uint32_t trcerr                : 1;  /**< [ 24: 24](RO) Indicates if TRC()_TRCVICTLR[TRCERR] is supported.

                                                                 For CNXXXX not supported, this means system errors are not traced. */
        uint32_t syncpr                : 1;  /**< [ 25: 25](RO) Indicates if an implementation has a fixed synchronization period:
                                                                   0 = TRC()_TRCSYNCPR is read-write so software can change the synchronization period.
                                                                   1 = TRC()_TRCSYNCPR is read-only so the synchronization period is fixed. */
        uint32_t stallctl              : 1;  /**< [ 26: 26](RO) Indicates if the implementation can support stall control. */
        uint32_t sysstall              : 1;  /**< [ 27: 27](RO) Indicates if the implementation can support stall control:
                                                                   0 = The system does not support stall control of the PE.
                                                                   1 = The system can support stall control of the PE.

                                                                 CNXXXX supports stalling the PE. */
        uint32_t numproc               : 3;  /**< [ 30: 28](RO/H) Indicates the number of PEs available for tracing minus one.
                                                                 The reset value depends on the number of cores fuse-enabled in this part. */
        uint32_t noovflw               : 1;  /**< [ 31: 31](RO) Indicates if TRC()_TRCSTALLCTLR[NOOVERFLOW] is supported.

                                                                 For CNXXXX not supported. */
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_trcx_trcidr3_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t noovflw               : 1;  /**< [ 31: 31](RO) Indicates if TRC()_TRCSTALLCTLR[NOOVERFLOW] is supported.

                                                                 For CNXXXX not supported. */
        uint32_t numproc               : 3;  /**< [ 30: 28](RO/H) Indicates the number of PEs available for tracing minus one.
                                                                 See also [NUMPROCEXT].
                                                                 The reset value depends on the number of cores fuse-enabled in this part. */
        uint32_t sysstall              : 1;  /**< [ 27: 27](RO) Indicates if the implementation can support stall control:
                                                                   0 = The system does not support stall control of the PE.
                                                                   1 = The system can support stall control of the PE.

                                                                 CNXXXX supports stalling the PE. */
        uint32_t stallctl              : 1;  /**< [ 26: 26](RO) Indicates if the implementation can support stall control. */
        uint32_t syncpr                : 1;  /**< [ 25: 25](RO) Indicates if an implementation has a fixed synchronization period:
                                                                   0 = TRC()_TRCSYNCPR is read-write so software can change the synchronization period.
                                                                   1 = TRC()_TRCSYNCPR is read-only so the synchronization period is fixed. */
        uint32_t trcerr                : 1;  /**< [ 24: 24](RO) Indicates if TRC()_TRCVICTLR[TRCERR] is supported.

                                                                 For CNXXXX not supported, this means system errors are not traced. */
        uint32_t elns                  : 4;  /**< [ 23: 20](RO) In nonsecure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_NS] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_NS] are supported. */
        uint32_t els                   : 4;  /**< [ 19: 16](RO) In secure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_S] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_S] are supported.

                                                                 For CNXXXX, secure exception level tracing of EL0, EL1, and EL3 is supported. */
        uint32_t reserved_14_15        : 2;
        uint32_t numprocext            : 2;  /**< [ 13: 12](RO/H) Number of processors extension bits. Expands [NUMPROC] from 3 bits to 5
                                                                 bits. See [NUMPROC]. */
        uint32_t ccitmin               : 12; /**< [ 11:  0](RO) Indicates the minimum value that can be programmed in
                                                                 TRC()_TRCCCCTLR[THRESHOLD]. When cycle counting in the instruction trace is
                                                                 supported, that is TRC()_TRCIDR0[TRCCCI]=1, then the minimum value of this field
                                                                 is 0x1, otherwise it is 0x0.

                                                                 For CNXXXX, no support for cycle counting so this field is not applicable. */
#else /* Word 0 - Little Endian */
        uint32_t ccitmin               : 12; /**< [ 11:  0](RO) Indicates the minimum value that can be programmed in
                                                                 TRC()_TRCCCCTLR[THRESHOLD]. When cycle counting in the instruction trace is
                                                                 supported, that is TRC()_TRCIDR0[TRCCCI]=1, then the minimum value of this field
                                                                 is 0x1, otherwise it is 0x0.

                                                                 For CNXXXX, no support for cycle counting so this field is not applicable. */
        uint32_t numprocext            : 2;  /**< [ 13: 12](RO/H) Number of processors extension bits. Expands [NUMPROC] from 3 bits to 5
                                                                 bits. See [NUMPROC]. */
        uint32_t reserved_14_15        : 2;
        uint32_t els                   : 4;  /**< [ 19: 16](RO) In secure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_S] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_S] are supported.

                                                                 For CNXXXX, secure exception level tracing of EL0, EL1, and EL3 is supported. */
        uint32_t elns                  : 4;  /**< [ 23: 20](RO) In nonsecure state, each bit indicates whether instruction tracing is supported
                                                                 for the corresponding exception level, and TRC()_TRCACATR()[EXLEVEL_NS] and
                                                                 TRC()_TRCVICTLR[EXLEVEL_NS] are supported. */
        uint32_t trcerr                : 1;  /**< [ 24: 24](RO) Indicates if TRC()_TRCVICTLR[TRCERR] is supported.

                                                                 For CNXXXX not supported, this means system errors are not traced. */
        uint32_t syncpr                : 1;  /**< [ 25: 25](RO) Indicates if an implementation has a fixed synchronization period:
                                                                   0 = TRC()_TRCSYNCPR is read-write so software can change the synchronization period.
                                                                   1 = TRC()_TRCSYNCPR is read-only so the synchronization period is fixed. */
        uint32_t stallctl              : 1;  /**< [ 26: 26](RO) Indicates if the implementation can support stall control. */
        uint32_t sysstall              : 1;  /**< [ 27: 27](RO) Indicates if the implementation can support stall control:
                                                                   0 = The system does not support stall control of the PE.
                                                                   1 = The system can support stall control of the PE.

                                                                 CNXXXX supports stalling the PE. */
        uint32_t numproc               : 3;  /**< [ 30: 28](RO/H) Indicates the number of PEs available for tracing minus one.
                                                                 See also [NUMPROCEXT].
                                                                 The reset value depends on the number of cores fuse-enabled in this part. */
        uint32_t noovflw               : 1;  /**< [ 31: 31](RO) Indicates if TRC()_TRCSTALLCTLR[NOOVERFLOW] is supported.

                                                                 For CNXXXX not supported. */
#endif /* Word 0 - End */
    } cn83xx;
    /* struct bdk_trcx_trcidr3_cn83xx cn9; */
};
typedef union bdk_trcx_trcidr3 bdk_trcx_trcidr3_t;

static inline uint64_t BDK_TRCX_TRCIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc301ecll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301ecll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301ecll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301ecll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301ecll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR3(a) bdk_trcx_trcidr3_t
#define bustype_BDK_TRCX_TRCIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR3(a) "TRCX_TRCIDR3"
#define busnum_BDK_TRCX_TRCIDR3(a) (a)
#define arguments_BDK_TRCX_TRCIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr4
 *
 * TRC/ETM ID Register 4
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr4
{
    uint32_t u;
    struct bdk_trcx_trcidr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t numvmidc              : 4;  /**< [ 31: 28](RO) Indicates the number of VMID comparators that are available for tracing.
                                                                 For CNXXXX, one VMID comparator supported. */
        uint32_t numcidc               : 4;  /**< [ 27: 24](RO) Indicates the number of context ID comparators that are available for tracing.
                                                                 For CNXXXX, one contextID comparator supported. */
        uint32_t numsscc               : 4;  /**< [ 23: 20](RO) Indicates the number of single-shot comparator controls that are available for tracing.
                                                                 For CNXXXX, no single-shot comparators supported. */
        uint32_t numrspair             : 4;  /**< [ 19: 16](RO) Indicates the number of resource selection pairs that are available for tracing
                                                                 minus one.
                                                                 For CNXXXX, two source selection pairs. */
        uint32_t numpc                 : 4;  /**< [ 15: 12](RO) Indicates the number of PE comparator inputs that are available for tracing.
                                                                 For CNXXXX, No PE comparator inputs. */
        uint32_t reserved_9_11         : 3;
        uint32_t suppdac               : 1;  /**< [  8:  8](RO) Indicates if the implementation can support data address comparisons.
                                                                 For CNXXXX, no data address comparators supported. */
        uint32_t numdvc                : 4;  /**< [  7:  4](RO) Indicates if the implementation can support data address comparisons.
                                                                 For CNXXXX, no data address comparators. */
        uint32_t numacpairs            : 4;  /**< [  3:  0](RO) Indicates the number of address comparator pairs that are available for tracing.
                                                                 For CNXXXX, no address comparators. */
#else /* Word 0 - Little Endian */
        uint32_t numacpairs            : 4;  /**< [  3:  0](RO) Indicates the number of address comparator pairs that are available for tracing.
                                                                 For CNXXXX, no address comparators. */
        uint32_t numdvc                : 4;  /**< [  7:  4](RO) Indicates if the implementation can support data address comparisons.
                                                                 For CNXXXX, no data address comparators. */
        uint32_t suppdac               : 1;  /**< [  8:  8](RO) Indicates if the implementation can support data address comparisons.
                                                                 For CNXXXX, no data address comparators supported. */
        uint32_t reserved_9_11         : 3;
        uint32_t numpc                 : 4;  /**< [ 15: 12](RO) Indicates the number of PE comparator inputs that are available for tracing.
                                                                 For CNXXXX, No PE comparator inputs. */
        uint32_t numrspair             : 4;  /**< [ 19: 16](RO) Indicates the number of resource selection pairs that are available for tracing
                                                                 minus one.
                                                                 For CNXXXX, two source selection pairs. */
        uint32_t numsscc               : 4;  /**< [ 23: 20](RO) Indicates the number of single-shot comparator controls that are available for tracing.
                                                                 For CNXXXX, no single-shot comparators supported. */
        uint32_t numcidc               : 4;  /**< [ 27: 24](RO) Indicates the number of context ID comparators that are available for tracing.
                                                                 For CNXXXX, one contextID comparator supported. */
        uint32_t numvmidc              : 4;  /**< [ 31: 28](RO) Indicates the number of VMID comparators that are available for tracing.
                                                                 For CNXXXX, one VMID comparator supported. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr4_s cn8; */
    struct bdk_trcx_trcidr4_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t numvmidc              : 4;  /**< [ 31: 28](RO) Indicates the number of VMID comparators that are available for tracing.
                                                                 For CNXXXX, one VMID comparator supported. */
        uint32_t numcidc               : 4;  /**< [ 27: 24](RO) Indicates the number of context ID comparators that are available for tracing.
                                                                 For CNXXXX, one contextID comparator supported. */
        uint32_t numsscc               : 4;  /**< [ 23: 20](RO) Indicates the number of single-shot comparator controls that are available for tracing.
                                                                 For CNXXXX, no single-shot comparators supported. */
        uint32_t numrspair             : 4;  /**< [ 19: 16](RO) Indicates the number of resource selection pairs that are available for tracing
                                                                 minus one.
                                                                 For CNXXXX, two source selection pairs. */
        uint32_t numpc                 : 4;  /**< [ 15: 12](RO) Indicates the number of PE comparator inputs that are available for tracing.
                                                                 For CNXXXX, 4 PE comparator inputs. */
        uint32_t reserved_9_11         : 3;
        uint32_t suppdac               : 1;  /**< [  8:  8](RO) Indicates if the implementation can support data address comparisons.
                                                                 For CNXXXX, no data address comparators supported. */
        uint32_t numdvc                : 4;  /**< [  7:  4](RO) Indicates if the implementation can support data address comparisons.
                                                                 For CNXXXX, no data address comparators. */
        uint32_t numacpairs            : 4;  /**< [  3:  0](RO) Indicates the number of address comparator pairs that are available for tracing.
                                                                 For CNXXXX, no address comparators. */
#else /* Word 0 - Little Endian */
        uint32_t numacpairs            : 4;  /**< [  3:  0](RO) Indicates the number of address comparator pairs that are available for tracing.
                                                                 For CNXXXX, no address comparators. */
        uint32_t numdvc                : 4;  /**< [  7:  4](RO) Indicates if the implementation can support data address comparisons.
                                                                 For CNXXXX, no data address comparators. */
        uint32_t suppdac               : 1;  /**< [  8:  8](RO) Indicates if the implementation can support data address comparisons.
                                                                 For CNXXXX, no data address comparators supported. */
        uint32_t reserved_9_11         : 3;
        uint32_t numpc                 : 4;  /**< [ 15: 12](RO) Indicates the number of PE comparator inputs that are available for tracing.
                                                                 For CNXXXX, 4 PE comparator inputs. */
        uint32_t numrspair             : 4;  /**< [ 19: 16](RO) Indicates the number of resource selection pairs that are available for tracing
                                                                 minus one.
                                                                 For CNXXXX, two source selection pairs. */
        uint32_t numsscc               : 4;  /**< [ 23: 20](RO) Indicates the number of single-shot comparator controls that are available for tracing.
                                                                 For CNXXXX, no single-shot comparators supported. */
        uint32_t numcidc               : 4;  /**< [ 27: 24](RO) Indicates the number of context ID comparators that are available for tracing.
                                                                 For CNXXXX, one contextID comparator supported. */
        uint32_t numvmidc              : 4;  /**< [ 31: 28](RO) Indicates the number of VMID comparators that are available for tracing.
                                                                 For CNXXXX, one VMID comparator supported. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcidr4 bdk_trcx_trcidr4_t;

static inline uint64_t BDK_TRCX_TRCIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc301f0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301f0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301f0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301f0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301f0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR4(a) bdk_trcx_trcidr4_t
#define bustype_BDK_TRCX_TRCIDR4(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR4(a) "TRCX_TRCIDR4"
#define busnum_BDK_TRCX_TRCIDR4(a) (a)
#define arguments_BDK_TRCX_TRCIDR4(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr5
 *
 * TRC/ETM ID Register 5
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr5
{
    uint32_t u;
    struct bdk_trcx_trcidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t redfuncntr            : 1;  /**< [ 31: 31](RO/H) Indicates if the reduced function counter is implemented:
                                                                   0 = The reduced function counter is not supported.
                                                                   1 = Counter 0 is implemented as a reduced function counter. */
        uint32_t numcntr               : 3;  /**< [ 30: 28](RO/H) Indicates the number of counters that are available for tracing.
                                                                 For CNXXXX, one counter supported. */
        uint32_t numseqstate           : 3;  /**< [ 27: 25](RO) Indicates the number of sequencer states that are implemented.
                                                                 For CNXXXX, no sequencer states are implemented. */
        uint32_t reserved_24           : 1;
        uint32_t lpoverride            : 1;  /**< [ 23: 23](RO) Indicates if the implementation can support low-power state override:
                                                                   0 = The implementation does not support low-power state override.
                                                                   1 = The implementation supports low-power state override, and the
                                                                   TRC()_TRCEVENTCTL1R[LPOVERRIDE] field is implemented.

                                                                 The trace unit must support low-power state override if it can enter a
                                                                 low-power mode where the resources and event trace generation are disabled.

                                                                 For CNXXXX, low power state overwrite is not implemented. */
        uint32_t atbtrig               : 1;  /**< [ 22: 22](RO) Indicates if the implementation can support ATB triggers:
                                                                   0 = The implementation does not support ATB triggers.
                                                                   1 = The implementation supports ATB triggers, and the
                                                                   TRC()_TRCEVENTCTL1R[ATBTRIG] field is implemented.

                                                                   For CNXXXX, no support for ATB triggers. */
        uint32_t traceidsize           : 6;  /**< [ 21: 16](RO) Indicates the trace ID width.
                                                                 0x07 = The implementation supports a 7-bit trace ID. This defines the width of
                                                                 the TRC()_TRCTRACEIDR[TRACEID] field.

                                                                 For CNXXXX, 7 bit trace ID size. */
        uint32_t reserved_12_15        : 4;
        uint32_t numextinsel           : 3;  /**< [ 11:  9](RO) Indicates how many external input select resources are implemented.
                                                                 0x0 = No external input select resources are available and TRC()_TRCEXTINSELR is
                                                                 not implemented.
                                                                 0x1 = The implementation has one external input select resource.
                                                                 0x2 = The implementation has two external input select resources.
                                                                 0x3 = The implementation has three external input select resources.
                                                                 0x4 = The implementation has four external input select resources.

                                                                 For CNXXXX, no external inputs are implemented. */
        uint32_t numextin              : 9;  /**< [  8:  0](RO) Indicates how many external inputs are implemented.
                                                                 For CNXXXX, no external inputs are implemented. */
#else /* Word 0 - Little Endian */
        uint32_t numextin              : 9;  /**< [  8:  0](RO) Indicates how many external inputs are implemented.
                                                                 For CNXXXX, no external inputs are implemented. */
        uint32_t numextinsel           : 3;  /**< [ 11:  9](RO) Indicates how many external input select resources are implemented.
                                                                 0x0 = No external input select resources are available and TRC()_TRCEXTINSELR is
                                                                 not implemented.
                                                                 0x1 = The implementation has one external input select resource.
                                                                 0x2 = The implementation has two external input select resources.
                                                                 0x3 = The implementation has three external input select resources.
                                                                 0x4 = The implementation has four external input select resources.

                                                                 For CNXXXX, no external inputs are implemented. */
        uint32_t reserved_12_15        : 4;
        uint32_t traceidsize           : 6;  /**< [ 21: 16](RO) Indicates the trace ID width.
                                                                 0x07 = The implementation supports a 7-bit trace ID. This defines the width of
                                                                 the TRC()_TRCTRACEIDR[TRACEID] field.

                                                                 For CNXXXX, 7 bit trace ID size. */
        uint32_t atbtrig               : 1;  /**< [ 22: 22](RO) Indicates if the implementation can support ATB triggers:
                                                                   0 = The implementation does not support ATB triggers.
                                                                   1 = The implementation supports ATB triggers, and the
                                                                   TRC()_TRCEVENTCTL1R[ATBTRIG] field is implemented.

                                                                   For CNXXXX, no support for ATB triggers. */
        uint32_t lpoverride            : 1;  /**< [ 23: 23](RO) Indicates if the implementation can support low-power state override:
                                                                   0 = The implementation does not support low-power state override.
                                                                   1 = The implementation supports low-power state override, and the
                                                                   TRC()_TRCEVENTCTL1R[LPOVERRIDE] field is implemented.

                                                                 The trace unit must support low-power state override if it can enter a
                                                                 low-power mode where the resources and event trace generation are disabled.

                                                                 For CNXXXX, low power state overwrite is not implemented. */
        uint32_t reserved_24           : 1;
        uint32_t numseqstate           : 3;  /**< [ 27: 25](RO) Indicates the number of sequencer states that are implemented.
                                                                 For CNXXXX, no sequencer states are implemented. */
        uint32_t numcntr               : 3;  /**< [ 30: 28](RO/H) Indicates the number of counters that are available for tracing.
                                                                 For CNXXXX, one counter supported. */
        uint32_t redfuncntr            : 1;  /**< [ 31: 31](RO/H) Indicates if the reduced function counter is implemented:
                                                                   0 = The reduced function counter is not supported.
                                                                   1 = Counter 0 is implemented as a reduced function counter. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr5_s cn; */
};
typedef union bdk_trcx_trcidr5 bdk_trcx_trcidr5_t;

static inline uint64_t BDK_TRCX_TRCIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc301f4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301f4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301f4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301f4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301f4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR5(a) bdk_trcx_trcidr5_t
#define bustype_BDK_TRCX_TRCIDR5(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR5(a) "TRCX_TRCIDR5"
#define busnum_BDK_TRCX_TRCIDR5(a) (a)
#define arguments_BDK_TRCX_TRCIDR5(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr6
 *
 * TRC/ETM ID Register 6
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr6
{
    uint32_t u;
    struct bdk_trcx_trcidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr6_s cn; */
};
typedef union bdk_trcx_trcidr6 bdk_trcx_trcidr6_t;

static inline uint64_t BDK_TRCX_TRCIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc301f8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301f8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301f8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301f8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301f8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR6(a) bdk_trcx_trcidr6_t
#define bustype_BDK_TRCX_TRCIDR6(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR6(a) "TRCX_TRCIDR6"
#define busnum_BDK_TRCX_TRCIDR6(a) (a)
#define arguments_BDK_TRCX_TRCIDR6(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr7
 *
 * TRC/ETM ID Register 7
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr7
{
    uint32_t u;
    struct bdk_trcx_trcidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr7_s cn; */
};
typedef union bdk_trcx_trcidr7 bdk_trcx_trcidr7_t;

static inline uint64_t BDK_TRCX_TRCIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc301fcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301fcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301fcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301fcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301fcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR7(a) bdk_trcx_trcidr7_t
#define bustype_BDK_TRCX_TRCIDR7(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR7(a) "TRCX_TRCIDR7"
#define busnum_BDK_TRCX_TRCIDR7(a) (a)
#define arguments_BDK_TRCX_TRCIDR7(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr8
 *
 * TRC/ETM ID Register 8
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr8
{
    uint32_t u;
    struct bdk_trcx_trcidr8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t maxspec               : 32; /**< [ 31:  0](RO) Indicates the maximum speculation depth of the instruction trace stream. This is
                                                                 the maximum number of P0 elements in the trace stream that can be speculative at
                                                                 any time.

                                                                 For CNXXXX, speculative tracing is not supported. */
#else /* Word 0 - Little Endian */
        uint32_t maxspec               : 32; /**< [ 31:  0](RO) Indicates the maximum speculation depth of the instruction trace stream. This is
                                                                 the maximum number of P0 elements in the trace stream that can be speculative at
                                                                 any time.

                                                                 For CNXXXX, speculative tracing is not supported. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr8_s cn; */
};
typedef union bdk_trcx_trcidr8 bdk_trcx_trcidr8_t;

static inline uint64_t BDK_TRCX_TRCIDR8(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR8(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30180ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030180ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030180ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030180ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030180ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR8", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR8(a) bdk_trcx_trcidr8_t
#define bustype_BDK_TRCX_TRCIDR8(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR8(a) "TRCX_TRCIDR8"
#define busnum_BDK_TRCX_TRCIDR8(a) (a)
#define arguments_BDK_TRCX_TRCIDR8(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcidr9
 *
 * TRC/ETM ID Register 9
 * This register indicates the capabilities of the trace unit.
 */
union bdk_trcx_trcidr9
{
    uint32_t u;
    struct bdk_trcx_trcidr9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t nump0key              : 32; /**< [ 31:  0](RO) Indicates the number of P0 right-hand keys that the trace unit can use. A value of 0 or 1
                                                                 indicates one P0 key.

                                                                 The value of this bit can be less than the value of TRC()_TRCIDR8[MAXSPEC].

                                                                 Arm recommends a minimum of 32 P0 keys for an implementation that supports data
                                                                 tracing. If TRC()_TRCIDR9[NUMP0KEY] \< 32 this can result in a large number of
                                                                 data synchronization markers in the trace stream.

                                                                 For CNXXXX, one right-hand key. */
#else /* Word 0 - Little Endian */
        uint32_t nump0key              : 32; /**< [ 31:  0](RO) Indicates the number of P0 right-hand keys that the trace unit can use. A value of 0 or 1
                                                                 indicates one P0 key.

                                                                 The value of this bit can be less than the value of TRC()_TRCIDR8[MAXSPEC].

                                                                 Arm recommends a minimum of 32 P0 keys for an implementation that supports data
                                                                 tracing. If TRC()_TRCIDR9[NUMP0KEY] \< 32 this can result in a large number of
                                                                 data synchronization markers in the trace stream.

                                                                 For CNXXXX, one right-hand key. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcidr9_s cn; */
};
typedef union bdk_trcx_trcidr9 bdk_trcx_trcidr9_t;

static inline uint64_t BDK_TRCX_TRCIDR9(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIDR9(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30184ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030184ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030184ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030184ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030184ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIDR9", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIDR9(a) bdk_trcx_trcidr9_t
#define bustype_BDK_TRCX_TRCIDR9(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIDR9(a) "TRCX_TRCIDR9"
#define busnum_BDK_TRCX_TRCIDR9(a) (a)
#define arguments_BDK_TRCX_TRCIDR9(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcimspec0
 *
 * TRC/ETM Implementation Defined Register 0
 * TRCIMPSEC0 shows the presence of any implementation-defined features, and
 * provides an interface to enable the features that are provided.
 */
union bdk_trcx_trcimspec0
{
    uint32_t u;
    struct bdk_trcx_trcimspec0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t en                    : 4;  /**< [  7:  4](R/W) If [SUPPORT] \> 0, this field controls whether the implementation-defined features
                                                                 are enabled. The permitted values are:
                                                                   0bXXX1 = Enables the corresponding op-code compare feature described in [SUPPORT]. */
        uint32_t support               : 4;  /**< [  3:  0](RO) Indicates whether the implementation supports the implementation-defined features.
                                                                 This field is read-only. The permitted values are:
                                                                   0x1 = PE op-code comparator results can be used as events or to control the start/stop logic. */
#else /* Word 0 - Little Endian */
        uint32_t support               : 4;  /**< [  3:  0](RO) Indicates whether the implementation supports the implementation-defined features.
                                                                 This field is read-only. The permitted values are:
                                                                   0x1 = PE op-code comparator results can be used as events or to control the start/stop logic. */
        uint32_t en                    : 4;  /**< [  7:  4](R/W) If [SUPPORT] \> 0, this field controls whether the implementation-defined features
                                                                 are enabled. The permitted values are:
                                                                   0bXXX1 = Enables the corresponding op-code compare feature described in [SUPPORT]. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcimspec0_s cn; */
};
typedef union bdk_trcx_trcimspec0 bdk_trcx_trcimspec0_t;

static inline uint64_t BDK_TRCX_TRCIMSPEC0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIMSPEC0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301c0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301c0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301c0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301c0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIMSPEC0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIMSPEC0(a) bdk_trcx_trcimspec0_t
#define bustype_BDK_TRCX_TRCIMSPEC0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIMSPEC0(a) "TRCX_TRCIMSPEC0"
#define busnum_BDK_TRCX_TRCIMSPEC0(a) (a)
#define arguments_BDK_TRCX_TRCIMSPEC0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcimspec1
 *
 * TRC/ETM Implementation Defined Register 1
 * This register shows the presence of any future implementation defined features, and
 * provides an interface to enable the features that are provided.
 */
union bdk_trcx_trcimspec1
{
    uint32_t u;
    struct bdk_trcx_trcimspec1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t select                : 4;  /**< [  3:  0](R/W) Indicates the implementation-defined features.
                                                                 This field is read write. The permitted values are:
                                                                    0x0 = Select instruction comparator 0.
                                                                    0x1 =  Select instruction comparator 1.
                                                                    0x2 = Select instruction comparator 2.
                                                                    0x3 = Select instruction comparator 3.
                                                                    0x8 =  Select mask 0.
                                                                    0x9 = Select mask 1.
                                                                    0xA = Select mask 2.
                                                                    0xB = Select mask 3.

                                                                 The rest are reserved. */
#else /* Word 0 - Little Endian */
        uint32_t select                : 4;  /**< [  3:  0](R/W) Indicates the implementation-defined features.
                                                                 This field is read write. The permitted values are:
                                                                    0x0 = Select instruction comparator 0.
                                                                    0x1 =  Select instruction comparator 1.
                                                                    0x2 = Select instruction comparator 2.
                                                                    0x3 = Select instruction comparator 3.
                                                                    0x8 =  Select mask 0.
                                                                    0x9 = Select mask 1.
                                                                    0xA = Select mask 2.
                                                                    0xB = Select mask 3.

                                                                 The rest are reserved. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcimspec1_s cn; */
};
typedef union bdk_trcx_trcimspec1 bdk_trcx_trcimspec1_t;

static inline uint64_t BDK_TRCX_TRCIMSPEC1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIMSPEC1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301c4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301c4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301c4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301c4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIMSPEC1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIMSPEC1(a) bdk_trcx_trcimspec1_t
#define bustype_BDK_TRCX_TRCIMSPEC1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIMSPEC1(a) "TRCX_TRCIMSPEC1"
#define busnum_BDK_TRCX_TRCIMSPEC1(a) (a)
#define arguments_BDK_TRCX_TRCIMSPEC1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcimspec2
 *
 * TRC/ETM Implementation Defined Register 2
 * TRCIMPSEC2 shows the presence of any future implementation-defined features, and
 * provides an interface to enable the features that are provided.
 */
union bdk_trcx_trcimspec2
{
    uint32_t u;
    struct bdk_trcx_trcimspec2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t value                 : 32; /**< [ 31:  0](R/W) Write to TRCIMSPEC2 will write the 32-bit value into the register indicated by
                                                                 TRCIMSPEC1[SELECT].
                                                                 Read from TRCIMSPEC2 will return the 32-bit value of the register indicated by
                                                                 TRCIMSPEC1[SELECT]. */
#else /* Word 0 - Little Endian */
        uint32_t value                 : 32; /**< [ 31:  0](R/W) Write to TRCIMSPEC2 will write the 32-bit value into the register indicated by
                                                                 TRCIMSPEC1[SELECT].
                                                                 Read from TRCIMSPEC2 will return the 32-bit value of the register indicated by
                                                                 TRCIMSPEC1[SELECT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcimspec2_s cn; */
};
typedef union bdk_trcx_trcimspec2 bdk_trcx_trcimspec2_t;

static inline uint64_t BDK_TRCX_TRCIMSPEC2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCIMSPEC2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080301c8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080301c8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080301c8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080301c8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCIMSPEC2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCIMSPEC2(a) bdk_trcx_trcimspec2_t
#define bustype_BDK_TRCX_TRCIMSPEC2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCIMSPEC2(a) "TRCX_TRCIMSPEC2"
#define busnum_BDK_TRCX_TRCIMSPEC2(a) (a)
#define arguments_BDK_TRCX_TRCIMSPEC2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcitctrl
 *
 * TRC/ETM TRC Integration mode Control Register
 * Enables the TRC to switch from its default mode into
 *     integration mode, where test software can control directly the
 *     inputs and outputs of the processor, for integration testing
 *     or topology detection.
 */
union bdk_trcx_trcitctrl
{
    uint32_t u;
    struct bdk_trcx_trcitctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable. When IME == 1, the device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. */
#else /* Word 0 - Little Endian */
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable. When IME == 1, the device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcitctrl_s cn8; */
    struct bdk_trcx_trcitctrl_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. The device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
#else /* Word 0 - Little Endian */
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. The device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcitctrl bdk_trcx_trcitctrl_t;

static inline uint64_t BDK_TRCX_TRCITCTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCITCTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30f00ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030f00ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030f00ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030f00ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030f00ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCITCTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCITCTRL(a) bdk_trcx_trcitctrl_t
#define bustype_BDK_TRCX_TRCITCTRL(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCITCTRL(a) "TRCX_TRCITCTRL"
#define busnum_BDK_TRCX_TRCITCTRL(a) (a)
#define arguments_BDK_TRCX_TRCITCTRL(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trclar
 *
 * TRC/ETM Management Software Lock Access Register
 * Allows or disallows access to the TRC registers through a
 *     memory-mapped interface.
 */
union bdk_trcx_trclar
{
    uint32_t u;
    struct bdk_trcx_trclar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t key                   : 32; /**< [ 31:  0](WO) Lock access control. Writing the key value 0xC5ACCE55 unlocks the lock.
                                                                 Writing any other value to this register locks the lock, disabling write
                                                                 accesses to this component's registers through a memory mapped interface. */
#else /* Word 0 - Little Endian */
        uint32_t key                   : 32; /**< [ 31:  0](WO) Lock access control. Writing the key value 0xC5ACCE55 unlocks the lock.
                                                                 Writing any other value to this register locks the lock, disabling write
                                                                 accesses to this component's registers through a memory mapped interface. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trclar_s cn; */
};
typedef union bdk_trcx_trclar bdk_trcx_trclar_t;

static inline uint64_t BDK_TRCX_TRCLAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCLAR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fb0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fb0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fb0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fb0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fb0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCLAR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCLAR(a) bdk_trcx_trclar_t
#define bustype_BDK_TRCX_TRCLAR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCLAR(a) "TRCX_TRCLAR"
#define busnum_BDK_TRCX_TRCLAR(a) (a)
#define arguments_BDK_TRCX_TRCLAR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trclsr
 *
 * TRC/ETM Management Software Lock Status Register
 * Indicates the current status of the software lock for TRC
 *     registers.
 */
union bdk_trcx_trclsr
{
    uint32_t u;
    struct bdk_trcx_trclsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t ntt                   : 1;  /**< [  2:  2](RO) Not thirty-two bit access required. */
        uint32_t slk                   : 1;  /**< [  1:  1](RO/H) Software lock status for this component. For an access to LSR
                                                                     that is not a memory-mapped access, or when the software lock
                                                                     is not implemented, this field is 0.
                                                                 For memory-mapped accesses when the software lock is
                                                                     implemented, possible values of this field are:
                                                                 0 = Lock clear. Writes are permitted to this component's
                                                                     registers.
                                                                 1 = Lock set. Writes to this component's registers are ignored,
                                                                     and reads have no side effects. */
        uint32_t sli                   : 1;  /**< [  0:  0](RO) Software lock implemented. For an access to LSR that is not a
                                                                     memory-mapped access, this field is 0. For memory-mapped
                                                                     accesses, the value of this field is implementation defined.
                                                                     Permitted values are:
                                                                 0 = Software lock not implemented or not memory-mapped access.
                                                                 1 = Software lock implemented and memory-mapped access. */
#else /* Word 0 - Little Endian */
        uint32_t sli                   : 1;  /**< [  0:  0](RO) Software lock implemented. For an access to LSR that is not a
                                                                     memory-mapped access, this field is 0. For memory-mapped
                                                                     accesses, the value of this field is implementation defined.
                                                                     Permitted values are:
                                                                 0 = Software lock not implemented or not memory-mapped access.
                                                                 1 = Software lock implemented and memory-mapped access. */
        uint32_t slk                   : 1;  /**< [  1:  1](RO/H) Software lock status for this component. For an access to LSR
                                                                     that is not a memory-mapped access, or when the software lock
                                                                     is not implemented, this field is 0.
                                                                 For memory-mapped accesses when the software lock is
                                                                     implemented, possible values of this field are:
                                                                 0 = Lock clear. Writes are permitted to this component's
                                                                     registers.
                                                                 1 = Lock set. Writes to this component's registers are ignored,
                                                                     and reads have no side effects. */
        uint32_t ntt                   : 1;  /**< [  2:  2](RO) Not thirty-two bit access required. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trclsr_s cn; */
};
typedef union bdk_trcx_trclsr bdk_trcx_trclsr_t;

static inline uint64_t BDK_TRCX_TRCLSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCLSR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fb4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fb4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fb4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fb4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fb4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCLSR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCLSR(a) bdk_trcx_trclsr_t
#define bustype_BDK_TRCX_TRCLSR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCLSR(a) "TRCX_TRCLSR"
#define busnum_BDK_TRCX_TRCLSR(a) (a)
#define arguments_BDK_TRCX_TRCLSR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcoslar
 *
 * TRC/ETM OS Lock Access Register
 * This register clears bits of the application trigger register.
 */
union bdk_trcx_trcoslar
{
    uint32_t u;
    struct bdk_trcx_trcoslar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t oslk                  : 1;  /**< [  0:  0](WO) The OS lock status bit.
                                                                 0 = The OS lock is unlocked.
                                                                 1 = The OS lock is locked. */
#else /* Word 0 - Little Endian */
        uint32_t oslk                  : 1;  /**< [  0:  0](WO) The OS lock status bit.
                                                                 0 = The OS lock is unlocked.
                                                                 1 = The OS lock is locked. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcoslar_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcoslar_s cn9; */
};
typedef union bdk_trcx_trcoslar bdk_trcx_trcoslar_t;

static inline uint64_t BDK_TRCX_TRCOSLAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCOSLAR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30300ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030300ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030300ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030300ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030300ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCOSLAR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCOSLAR(a) bdk_trcx_trcoslar_t
#define bustype_BDK_TRCX_TRCOSLAR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCOSLAR(a) "TRCX_TRCOSLAR"
#define busnum_BDK_TRCX_TRCOSLAR(a) (a)
#define arguments_BDK_TRCX_TRCOSLAR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcoslsr
 *
 * TRC/ETM OS lock status Register
 * This register returns the status of the OS lock.
 */
union bdk_trcx_trcoslsr
{
    uint32_t u;
    struct bdk_trcx_trcoslsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t oslm1                 : 1;  /**< [  3:  3](RO) Define with OSLM0. [OSLM1, OSLM0] values:
                                                                 0x0 = OS Lock is not implemented.
                                                                 0x2 = OS Lock is implemented. */
        uint32_t ntt                   : 1;  /**< [  2:  2](RAZ) This bit is RAZ which indicates that the software must perform a 32-bit write to
                                                                 update the TRCOSLAR. */
        uint32_t oslk                  : 1;  /**< [  1:  1](RO/H) The OS lock status bit.
                                                                 0 = The OS lock is unlocked.
                                                                 1 = The OS lock is locked.

                                                                 If the OS Lock is not implemented this bit is RES0. */
        uint32_t oslm0                 : 1;  /**< [  0:  0](RO) Defined with [OSLM1]. */
#else /* Word 0 - Little Endian */
        uint32_t oslm0                 : 1;  /**< [  0:  0](RO) Defined with [OSLM1]. */
        uint32_t oslk                  : 1;  /**< [  1:  1](RO/H) The OS lock status bit.
                                                                 0 = The OS lock is unlocked.
                                                                 1 = The OS lock is locked.

                                                                 If the OS Lock is not implemented this bit is RES0. */
        uint32_t ntt                   : 1;  /**< [  2:  2](RAZ) This bit is RAZ which indicates that the software must perform a 32-bit write to
                                                                 update the TRCOSLAR. */
        uint32_t oslm1                 : 1;  /**< [  3:  3](RO) Define with OSLM0. [OSLM1, OSLM0] values:
                                                                 0x0 = OS Lock is not implemented.
                                                                 0x2 = OS Lock is implemented. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcoslsr_s cn8; */
    struct bdk_trcx_trcoslsr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t oslm1                 : 1;  /**< [  3:  3](RO) Define with OSLM0. [OSLM1, OSLM0] values:
                                                                 0x0 = OS lock is not implemented.
                                                                 0x2 = OS lock is implemented. */
        uint32_t ntt                   : 1;  /**< [  2:  2](RAZ) This bit is RAZ which indicates that the software must perform a 32-bit write to
                                                                 update the TRCOSLAR. */
        uint32_t oslk                  : 1;  /**< [  1:  1](RO/H) The OS lock status bit.
                                                                 0 = The OS lock is unlocked.
                                                                 1 = The OS lock is locked.

                                                                 If the OS lock is not implemented this bit is RES0. */
        uint32_t oslm0                 : 1;  /**< [  0:  0](RO) Defined with [OSLM1]. */
#else /* Word 0 - Little Endian */
        uint32_t oslm0                 : 1;  /**< [  0:  0](RO) Defined with [OSLM1]. */
        uint32_t oslk                  : 1;  /**< [  1:  1](RO/H) The OS lock status bit.
                                                                 0 = The OS lock is unlocked.
                                                                 1 = The OS lock is locked.

                                                                 If the OS lock is not implemented this bit is RES0. */
        uint32_t ntt                   : 1;  /**< [  2:  2](RAZ) This bit is RAZ which indicates that the software must perform a 32-bit write to
                                                                 update the TRCOSLAR. */
        uint32_t oslm1                 : 1;  /**< [  3:  3](RO) Define with OSLM0. [OSLM1, OSLM0] values:
                                                                 0x0 = OS lock is not implemented.
                                                                 0x2 = OS lock is implemented. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcoslsr bdk_trcx_trcoslsr_t;

static inline uint64_t BDK_TRCX_TRCOSLSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCOSLSR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30304ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030304ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030304ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030304ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030304ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCOSLSR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCOSLSR(a) bdk_trcx_trcoslsr_t
#define bustype_BDK_TRCX_TRCOSLSR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCOSLSR(a) "TRCX_TRCOSLSR"
#define busnum_BDK_TRCX_TRCOSLSR(a) (a)
#define arguments_BDK_TRCX_TRCOSLSR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpdcr
 *
 * TRC/ETM PowerDown Control Register
 * Enables the signaling of an event on output channels when
 *     input trigger event n is received by the TRC.
 */
union bdk_trcx_trcpdcr
{
    uint32_t u;
    struct bdk_trcx_trcpdcr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t pu                    : 1;  /**< [  3:  3](R/W) 0 = The system may remove power from the trace unit. TRC()_TRCPDSR indicates the power
                                                                 state.
                                                                 1 = The system must provide power to the trace unit. */
        uint32_t inen                  : 3;  /**< [  2:  0](R/W) Input trigger \<n\> to output channel \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by the
                                                                     TRC()_TRCDEVID[NUMCHAN] field.
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = Input trigger \<n\> will not generate an event on output channel
                                                                     \<x\>.
                                                                 1 = Input trigger \<n\> will generate an event on output channel
                                                                     \<x\>.

                                                                 In CNXXXX TRC()_TRCINEN(3..31) are ignored as there are only 3 channels. */
#else /* Word 0 - Little Endian */
        uint32_t inen                  : 3;  /**< [  2:  0](R/W) Input trigger \<n\> to output channel \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by the
                                                                     TRC()_TRCDEVID[NUMCHAN] field.
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = Input trigger \<n\> will not generate an event on output channel
                                                                     \<x\>.
                                                                 1 = Input trigger \<n\> will generate an event on output channel
                                                                     \<x\>.

                                                                 In CNXXXX TRC()_TRCINEN(3..31) are ignored as there are only 3 channels. */
        uint32_t pu                    : 1;  /**< [  3:  3](R/W) 0 = The system may remove power from the trace unit. TRC()_TRCPDSR indicates the power
                                                                 state.
                                                                 1 = The system must provide power to the trace unit. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcpdcr_s cn8; */
    struct bdk_trcx_trcpdcr_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t inen                  : 3;  /**< [  2:  0](R/W) Input trigger \<n\> to output channel \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by the
                                                                     TRC()_TRCDEVID[NUMCHAN] field.
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = Input trigger \<n\> will not generate an event on output channel
                                                                     \<x\>.
                                                                 1 = Input trigger \<n\> will generate an event on output channel
                                                                     \<x\>.

                                                                 In CNXXXX TRC()_TRCINEN(3..31) are ignored as there are only 3 channels. */
#else /* Word 0 - Little Endian */
        uint32_t inen                  : 3;  /**< [  2:  0](R/W) Input trigger \<n\> to output channel \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by the
                                                                     TRC()_TRCDEVID[NUMCHAN] field.
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = Input trigger \<n\> will not generate an event on output channel
                                                                     \<x\>.
                                                                 1 = Input trigger \<n\> will generate an event on output channel
                                                                     \<x\>.

                                                                 In CNXXXX TRC()_TRCINEN(3..31) are ignored as there are only 3 channels. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_trcx_trcpdcr_s cn83xx; */
    struct bdk_trcx_trcpdcr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t pu                    : 1;  /**< [  3:  3](R/W) 0 = The system may remove power from the trace unit. TRC()_TRCPDSR indicates the power
                                                                 state.
                                                                 1 = The system must provide power to the trace unit. */
        uint32_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_2          : 3;
        uint32_t pu                    : 1;  /**< [  3:  3](R/W) 0 = The system may remove power from the trace unit. TRC()_TRCPDSR indicates the power
                                                                 state.
                                                                 1 = The system must provide power to the trace unit. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcpdcr bdk_trcx_trcpdcr_t;

static inline uint64_t BDK_TRCX_TRCPDCR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPDCR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30310ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030310ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030310ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030310ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030310ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPDCR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPDCR(a) bdk_trcx_trcpdcr_t
#define bustype_BDK_TRCX_TRCPDCR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPDCR(a) "TRCX_TRCPDCR"
#define busnum_BDK_TRCX_TRCPDCR(a) (a)
#define arguments_BDK_TRCX_TRCPDCR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpdsr
 *
 * TRC/ETM PowerDown Status Register
 * This register returns the following information about the trace unit:
 * OS lock status, Core power domain status, and power interruption stauts.
 */
union bdk_trcx_trcpdsr
{
    uint32_t u;
    struct bdk_trcx_trcpdsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t oslk                  : 1;  /**< [  5:  5](RO/H) 0 =  The OS lock is unlocked.
                                                                 1 =  The OS lock is locked.

                                                                 This field is reset to 1 on a trace unit reset. */
        uint32_t reserved_0_4          : 5;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_4          : 5;
        uint32_t oslk                  : 1;  /**< [  5:  5](RO/H) 0 =  The OS lock is unlocked.
                                                                 1 =  The OS lock is locked.

                                                                 This field is reset to 1 on a trace unit reset. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcpdsr_s cn8; */
    struct bdk_trcx_trcpdsr_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t outen                 : 3;  /**< [  2:  0](R/W) Input channel \<x\> to output trigger \<n\> enable.
                                                                 N is the number of ECT channels implemented as defined by the
                                                                     TRC()_TRCDEVID[NUMCHAN] field.
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = An event on input channel \<x\> will not cause output trigger
                                                                     \<n\> to be asserted.
                                                                 1 = An event on input channel \<x\> will cause output trigger \<n\> to
                                                                     be asserted.

                                                                 In CNXXXX TRC()_TRCOUTEN(3..31) are ignored as there are only 3 channels. */
#else /* Word 0 - Little Endian */
        uint32_t outen                 : 3;  /**< [  2:  0](R/W) Input channel \<x\> to output trigger \<n\> enable.
                                                                 N is the number of ECT channels implemented as defined by the
                                                                     TRC()_TRCDEVID[NUMCHAN] field.
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = An event on input channel \<x\> will not cause output trigger
                                                                     \<n\> to be asserted.
                                                                 1 = An event on input channel \<x\> will cause output trigger \<n\> to
                                                                     be asserted.

                                                                 In CNXXXX TRC()_TRCOUTEN(3..31) are ignored as there are only 3 channels. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_trcx_trcpdsr_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t oslk                  : 1;  /**< [  5:  5](RO/H) 0 =  The OS lock is unlocked.
                                                                 1 =  The OS lock is locked.

                                                                 This field is reset to 1 on a trace unit reset. */
        uint32_t reserved_2_4          : 3;
        uint32_t stickypd              : 1;  /**< [  1:  1](RO/H) Sticky powerdown status bit. Indicates whether the trace register state is valid.

                                                                 0 = If [POWER]=1 then the state of TRC()_TRCOSLSR and the trace registers are
                                                                    valid.  If [POWER]=0 then it is unknown whether the state of TRC()_TRCOSLSR
                                                                    and the trace registers are valid.

                                                                 1 =  The state of TRC()_TRCOSLSR and the trace registers might not be valid.
                                                                    The trace unit sets this bit to 1 if either:
                                                                        a. The trace unit is reset.
                                                                        b. The power to the trace unit core power domain is removed and
                                                                           the trace register state is not valid.

                                                                 This field is reset to one on a trace unit reset. */
        uint32_t power                 : 1;  /**< [  0:  0](RO/H) Power status bit:
                                                                   0 = The trace unit core power domain is not powered. The trace registers are not
                                                                      accessible and they all return an error response.
                                                                   1 = The trace unit core power domain is powered. The trace registers are
                                                                      accessible. */
#else /* Word 0 - Little Endian */
        uint32_t power                 : 1;  /**< [  0:  0](RO/H) Power status bit:
                                                                   0 = The trace unit core power domain is not powered. The trace registers are not
                                                                      accessible and they all return an error response.
                                                                   1 = The trace unit core power domain is powered. The trace registers are
                                                                      accessible. */
        uint32_t stickypd              : 1;  /**< [  1:  1](RO/H) Sticky powerdown status bit. Indicates whether the trace register state is valid.

                                                                 0 = If [POWER]=1 then the state of TRC()_TRCOSLSR and the trace registers are
                                                                    valid.  If [POWER]=0 then it is unknown whether the state of TRC()_TRCOSLSR
                                                                    and the trace registers are valid.

                                                                 1 =  The state of TRC()_TRCOSLSR and the trace registers might not be valid.
                                                                    The trace unit sets this bit to 1 if either:
                                                                        a. The trace unit is reset.
                                                                        b. The power to the trace unit core power domain is removed and
                                                                           the trace register state is not valid.

                                                                 This field is reset to one on a trace unit reset. */
        uint32_t reserved_2_4          : 3;
        uint32_t oslk                  : 1;  /**< [  5:  5](RO/H) 0 =  The OS lock is unlocked.
                                                                 1 =  The OS lock is locked.

                                                                 This field is reset to 1 on a trace unit reset. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } cn83xx;
    struct bdk_trcx_trcpdsr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t oslk                  : 1;  /**< [  5:  5](RO/H) 0 =  The OS lock is unlocked.
                                                                 1 =  The OS lock is locked.

                                                                 This field is reset to one on a trace unit reset. */
        uint32_t reserved_2_4          : 3;
        uint32_t stickypd              : 1;  /**< [  1:  1](RO/H) Sticky powerdown status bit. Indicates whether the trace register state is valid.

                                                                 0 = If [POWER]=1 then the state of TRC()_TRCOSLSR and the trace registers are
                                                                    valid.  If [POWER]=0 then it is unknown whether the state of TRC()_TRCOSLSR
                                                                    and the trace registers are valid.

                                                                 1 =  The state of TRC()_TRCOSLSR and the trace registers might not be valid.
                                                                    The trace unit sets this bit to one if either:
                                                                        a. The trace unit is reset.
                                                                        b. The power to the trace unit core power domain is removed and
                                                                           the trace register state is not valid.

                                                                 This field is reset to one on a trace unit reset. */
        uint32_t power                 : 1;  /**< [  0:  0](RO/H) Power status bit:
                                                                   0 = The trace unit core power domain is not powered. The trace registers are not
                                                                      accessible and they all return an error response.
                                                                   1 = The trace unit core power domain is powered. The trace registers are
                                                                      accessible. */
#else /* Word 0 - Little Endian */
        uint32_t power                 : 1;  /**< [  0:  0](RO/H) Power status bit:
                                                                   0 = The trace unit core power domain is not powered. The trace registers are not
                                                                      accessible and they all return an error response.
                                                                   1 = The trace unit core power domain is powered. The trace registers are
                                                                      accessible. */
        uint32_t stickypd              : 1;  /**< [  1:  1](RO/H) Sticky powerdown status bit. Indicates whether the trace register state is valid.

                                                                 0 = If [POWER]=1 then the state of TRC()_TRCOSLSR and the trace registers are
                                                                    valid.  If [POWER]=0 then it is unknown whether the state of TRC()_TRCOSLSR
                                                                    and the trace registers are valid.

                                                                 1 =  The state of TRC()_TRCOSLSR and the trace registers might not be valid.
                                                                    The trace unit sets this bit to one if either:
                                                                        a. The trace unit is reset.
                                                                        b. The power to the trace unit core power domain is removed and
                                                                           the trace register state is not valid.

                                                                 This field is reset to one on a trace unit reset. */
        uint32_t reserved_2_4          : 3;
        uint32_t oslk                  : 1;  /**< [  5:  5](RO/H) 0 =  The OS lock is unlocked.
                                                                 1 =  The OS lock is locked.

                                                                 This field is reset to one on a trace unit reset. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcpdsr bdk_trcx_trcpdsr_t;

static inline uint64_t BDK_TRCX_TRCPDSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPDSR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30314ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030314ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030314ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030314ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030314ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPDSR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPDSR(a) bdk_trcx_trcpdsr_t
#define bustype_BDK_TRCX_TRCPDSR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPDSR(a) "TRCX_TRCPDSR"
#define busnum_BDK_TRCX_TRCPDSR(a) (a)
#define arguments_BDK_TRCX_TRCPDSR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpidr0
 *
 * TRC/ETM Peripheral Identification Register 0
 * Provides information to identify a component.
 */
union bdk_trcx_trcpidr0
{
    uint32_t u;
    struct bdk_trcx_trcpidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::TRC. */
#else /* Word 0 - Little Endian */
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::TRC. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcpidr0_s cn; */
};
typedef union bdk_trcx_trcpidr0 bdk_trcx_trcpidr0_t;

static inline uint64_t BDK_TRCX_TRCPIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fe0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fe0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fe0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fe0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fe0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPIDR0(a) bdk_trcx_trcpidr0_t
#define bustype_BDK_TRCX_TRCPIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPIDR0(a) "TRCX_TRCPIDR0"
#define busnum_BDK_TRCX_TRCPIDR0(a) (a)
#define arguments_BDK_TRCX_TRCPIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpidr1
 *
 * TRC/ETM Peripheral Identification Register 1
 * Provides information to identify a component.
 */
union bdk_trcx_trcpidr1
{
    uint32_t u;
    struct bdk_trcx_trcpidr1_s
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
    /* struct bdk_trcx_trcpidr1_s cn8; */
    struct bdk_trcx_trcpidr1_cn9
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
    } cn9;
};
typedef union bdk_trcx_trcpidr1 bdk_trcx_trcpidr1_t;

static inline uint64_t BDK_TRCX_TRCPIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fe4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fe4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fe4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fe4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fe4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPIDR1(a) bdk_trcx_trcpidr1_t
#define bustype_BDK_TRCX_TRCPIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPIDR1(a) "TRCX_TRCPIDR1"
#define busnum_BDK_TRCX_TRCPIDR1(a) (a)
#define arguments_BDK_TRCX_TRCPIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpidr2
 *
 * TRC/ETM Peripheral Identification Register 2
 * Provides information to identify a component.
 */
union bdk_trcx_trcpidr2
{
    uint32_t u;
    struct bdk_trcx_trcpidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by Arm. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by Arm. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcpidr2_s cn8; */
    struct bdk_trcx_trcpidr2_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by Arm. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Marvell (Cavium) code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Marvell (Cavium) code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by Arm. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn9;
    /* struct bdk_trcx_trcpidr2_cn9 cn96xx; */
    /* struct bdk_trcx_trcpidr2_s cn98xx; */
    /* struct bdk_trcx_trcpidr2_s cnf95xxp1; */
    /* struct bdk_trcx_trcpidr2_cn9 cnf95xxp2; */
    /* struct bdk_trcx_trcpidr2_cn9 loki; */
};
typedef union bdk_trcx_trcpidr2 bdk_trcx_trcpidr2_t;

static inline uint64_t BDK_TRCX_TRCPIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fe8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fe8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fe8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fe8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fe8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPIDR2(a) bdk_trcx_trcpidr2_t
#define bustype_BDK_TRCX_TRCPIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPIDR2(a) "TRCX_TRCPIDR2"
#define busnum_BDK_TRCX_TRCPIDR2(a) (a)
#define arguments_BDK_TRCX_TRCPIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpidr3
 *
 * TRC/ETM Peripheral Identification Register 3
 * Provides information to identify a component.
 */
union bdk_trcx_trcpidr3
{
    uint32_t u;
    struct bdk_trcx_trcpidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer modified. Indicates someone other than the designer
                                                                     has modified the component. */
#else /* Word 0 - Little Endian */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer modified. Indicates someone other than the designer
                                                                     has modified the component. */
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcpidr3_s cn; */
};
typedef union bdk_trcx_trcpidr3 bdk_trcx_trcpidr3_t;

static inline uint64_t BDK_TRCX_TRCPIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fecll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fecll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fecll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fecll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fecll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPIDR3(a) bdk_trcx_trcpidr3_t
#define bustype_BDK_TRCX_TRCPIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPIDR3(a) "TRCX_TRCPIDR3"
#define busnum_BDK_TRCX_TRCPIDR3(a) (a)
#define arguments_BDK_TRCX_TRCPIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpidr4
 *
 * TRC/ETM Peripheral Identification Register 4
 * Provides information to identify a component.
 */
union bdk_trcx_trcpidr4
{
    uint32_t u;
    struct bdk_trcx_trcpidr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t size                  : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
#else /* Word 0 - Little Endian */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
        uint32_t size                  : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcpidr4_s cn8; */
    struct bdk_trcx_trcpidr4_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t size                  : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Marvell (Cavium). */
#else /* Word 0 - Little Endian */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Marvell (Cavium). */
        uint32_t size                  : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn9;
    /* struct bdk_trcx_trcpidr4_cn9 cn96xx; */
    /* struct bdk_trcx_trcpidr4_s cn98xx; */
    /* struct bdk_trcx_trcpidr4_s cnf95xxp1; */
    /* struct bdk_trcx_trcpidr4_cn9 cnf95xxp2; */
    /* struct bdk_trcx_trcpidr4_cn9 loki; */
};
typedef union bdk_trcx_trcpidr4 bdk_trcx_trcpidr4_t;

static inline uint64_t BDK_TRCX_TRCPIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPIDR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fd0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fd0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fd0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fd0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fd0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPIDR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPIDR4(a) bdk_trcx_trcpidr4_t
#define bustype_BDK_TRCX_TRCPIDR4(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPIDR4(a) "TRCX_TRCPIDR4"
#define busnum_BDK_TRCX_TRCPIDR4(a) (a)
#define arguments_BDK_TRCX_TRCPIDR4(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpidr5
 *
 * TRC/ETM Peripheral Identification Register 5
 * Provides information to identify an external debug component.
 */
union bdk_trcx_trcpidr5
{
    uint32_t u;
    struct bdk_trcx_trcpidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcpidr5_s cn; */
};
typedef union bdk_trcx_trcpidr5 bdk_trcx_trcpidr5_t;

static inline uint64_t BDK_TRCX_TRCPIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPIDR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fd4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fd4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fd4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fd4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fd4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPIDR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPIDR5(a) bdk_trcx_trcpidr5_t
#define bustype_BDK_TRCX_TRCPIDR5(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPIDR5(a) "TRCX_TRCPIDR5"
#define busnum_BDK_TRCX_TRCPIDR5(a) (a)
#define arguments_BDK_TRCX_TRCPIDR5(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpidr6
 *
 * TRC/ETM Peripheral Identification Register 6
 * Provides information to identify an external debug component.
 */
union bdk_trcx_trcpidr6
{
    uint32_t u;
    struct bdk_trcx_trcpidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcpidr6_s cn; */
};
typedef union bdk_trcx_trcpidr6 bdk_trcx_trcpidr6_t;

static inline uint64_t BDK_TRCX_TRCPIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPIDR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fd8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fd8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fd8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fd8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fd8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPIDR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPIDR6(a) bdk_trcx_trcpidr6_t
#define bustype_BDK_TRCX_TRCPIDR6(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPIDR6(a) "TRCX_TRCPIDR6"
#define busnum_BDK_TRCX_TRCPIDR6(a) (a)
#define arguments_BDK_TRCX_TRCPIDR6(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcpidr7
 *
 * TRC/ETM Peripheral Identification Register 7
 * Provides information to identify an external debug component.
 */
union bdk_trcx_trcpidr7
{
    uint32_t u;
    struct bdk_trcx_trcpidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcpidr7_s cn; */
};
typedef union bdk_trcx_trcpidr7 bdk_trcx_trcpidr7_t;

static inline uint64_t BDK_TRCX_TRCPIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPIDR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30fdcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030fdcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030fdcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030fdcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030fdcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPIDR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPIDR7(a) bdk_trcx_trcpidr7_t
#define bustype_BDK_TRCX_TRCPIDR7(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPIDR7(a) "TRCX_TRCPIDR7"
#define busnum_BDK_TRCX_TRCPIDR7(a) (a)
#define arguments_BDK_TRCX_TRCPIDR7(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcprgctlr
 *
 * TRC/ETM Programming Control Register
 * This register controls whether the TRC is enabled.
 */
union bdk_trcx_trcprgctlr
{
    uint32_t u;
    struct bdk_trcx_trcprgctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t en                    : 1;  /**< [  0:  0](R/W) Enables or disables the trace unit:
                                                                 0 = Trace unit is disabled.
                                                                     All trace resources are inactive and no trace is generated.
                                                                 1 = Trace unit is enabled. */
#else /* Word 0 - Little Endian */
        uint32_t en                    : 1;  /**< [  0:  0](R/W) Enables or disables the trace unit:
                                                                 0 = Trace unit is disabled.
                                                                     All trace resources are inactive and no trace is generated.
                                                                 1 = Trace unit is enabled. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcprgctlr_s cn; */
};
typedef union bdk_trcx_trcprgctlr bdk_trcx_trcprgctlr_t;

static inline uint64_t BDK_TRCX_TRCPRGCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPRGCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30004ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030004ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030004ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030004ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030004ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPRGCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPRGCTLR(a) bdk_trcx_trcprgctlr_t
#define bustype_BDK_TRCX_TRCPRGCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPRGCTLR(a) "TRCX_TRCPRGCTLR"
#define busnum_BDK_TRCX_TRCPRGCTLR(a) (a)
#define arguments_BDK_TRCX_TRCPRGCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcprocselr
 *
 * TRC/ETM PE Select Control Register
 * Programmed to select which PE to trace.
 */
union bdk_trcx_trcprocselr
{
    uint32_t u;
    struct bdk_trcx_trcprocselr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t procsel               : 6;  /**< [  5:  0](R/W) Only accepts writes when the trace unit is disabled. Before writing to this
                                                                   register, ensure that TRC()_TRCSTATR[IDLE] = 1 so that the trace unit can synchronize
                                                                   with the chosen PE. */
#else /* Word 0 - Little Endian */
        uint32_t procsel               : 6;  /**< [  5:  0](R/W) Only accepts writes when the trace unit is disabled. Before writing to this
                                                                   register, ensure that TRC()_TRCSTATR[IDLE] = 1 so that the trace unit can synchronize
                                                                   with the chosen PE. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcprocselr_s cn; */
};
typedef union bdk_trcx_trcprocselr bdk_trcx_trcprocselr_t;

static inline uint64_t BDK_TRCX_TRCPROCSELR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCPROCSELR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30008ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030008ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030008ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030008ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030008ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCPROCSELR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCPROCSELR(a) bdk_trcx_trcprocselr_t
#define bustype_BDK_TRCX_TRCPROCSELR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCPROCSELR(a) "TRCX_TRCPROCSELR"
#define busnum_BDK_TRCX_TRCPROCSELR(a) (a)
#define arguments_BDK_TRCX_TRCPROCSELR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcqctlr
 *
 * TRC/ETM Q Element Control Register
 * This register controls when Q elements are enabled.
 */
union bdk_trcx_trcqctlr
{
    uint32_t u;
    struct bdk_trcx_trcqctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t mode                  : 1;  /**< [  8:  8](R/W) Select whether address range comparator is permitted to generate Q element.
                                                                 0 = Exclude mode. The address range comparator which is selected by range
                                                                     is not permitted to generate Q element.
                                                                 1 = Include mode. The address range comparator which is selected by range
                                                                     is permitted to generate Q element. */
        uint32_t range                 : 8;  /**< [  7:  0](R/W) Specify the address range comparator to be used for controlling Q elements.
                                                                 0 = Address range comparator[n] is not selected.
                                                                 1 = Address range comparator[n] is selected. */
#else /* Word 0 - Little Endian */
        uint32_t range                 : 8;  /**< [  7:  0](R/W) Specify the address range comparator to be used for controlling Q elements.
                                                                 0 = Address range comparator[n] is not selected.
                                                                 1 = Address range comparator[n] is selected. */
        uint32_t mode                  : 1;  /**< [  8:  8](R/W) Select whether address range comparator is permitted to generate Q element.
                                                                 0 = Exclude mode. The address range comparator which is selected by range
                                                                     is not permitted to generate Q element.
                                                                 1 = Include mode. The address range comparator which is selected by range
                                                                     is permitted to generate Q element. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcqctlr_s cn; */
};
typedef union bdk_trcx_trcqctlr bdk_trcx_trcqctlr_t;

static inline uint64_t BDK_TRCX_TRCQCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCQCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30044ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030044ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030044ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030044ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030044ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCQCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCQCTLR(a) bdk_trcx_trcqctlr_t
#define bustype_BDK_TRCX_TRCQCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCQCTLR(a) "TRCX_TRCQCTLR"
#define busnum_BDK_TRCX_TRCQCTLR(a) (a)
#define arguments_BDK_TRCX_TRCQCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcrsctlr0
 *
 * TRC/ETM Resource Selection Control Register 0
 * This register controls the selection of the resources in the trace unit.
 */
union bdk_trcx_trcrsctlr0
{
    uint32_t u;
    struct bdk_trcx_trcrsctlr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcrsctlr0_s cn; */
};
typedef union bdk_trcx_trcrsctlr0 bdk_trcx_trcrsctlr0_t;

static inline uint64_t BDK_TRCX_TRCRSCTLR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCRSCTLR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30200ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030200ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030200ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030200ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030200ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCRSCTLR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCRSCTLR0(a) bdk_trcx_trcrsctlr0_t
#define bustype_BDK_TRCX_TRCRSCTLR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCRSCTLR0(a) "TRCX_TRCRSCTLR0"
#define busnum_BDK_TRCX_TRCRSCTLR0(a) (a)
#define arguments_BDK_TRCX_TRCRSCTLR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcrsctlr1
 *
 * TRC/ETM Resource Selection Control Register 1
 * This register controls the selection of the resources in the trace unit.
 */
union bdk_trcx_trcrsctlr1
{
    uint32_t u;
    struct bdk_trcx_trcrsctlr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcrsctlr1_s cn; */
};
typedef union bdk_trcx_trcrsctlr1 bdk_trcx_trcrsctlr1_t;

static inline uint64_t BDK_TRCX_TRCRSCTLR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCRSCTLR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30204ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030204ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030204ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030204ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030204ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCRSCTLR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCRSCTLR1(a) bdk_trcx_trcrsctlr1_t
#define bustype_BDK_TRCX_TRCRSCTLR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCRSCTLR1(a) "TRCX_TRCRSCTLR1"
#define busnum_BDK_TRCX_TRCRSCTLR1(a) (a)
#define arguments_BDK_TRCX_TRCRSCTLR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcrsctlr2
 *
 * TRC/ETM Resource Selection Control Register 2
 * This register controls the selection of the resources in the trace unit.
 */
union bdk_trcx_trcrsctlr2
{
    uint32_t u;
    struct bdk_trcx_trcrsctlr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_22_31        : 10;
        uint32_t pairinv               : 1;  /**< [ 21: 21](R/W) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
#else /* Word 0 - Little Endian */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t pairinv               : 1;  /**< [ 21: 21](R/W) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t reserved_22_31        : 10;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcrsctlr2_s cn8; */
    struct bdk_trcx_trcrsctlr2_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_trcx_trcrsctlr2_s cn83xx; */
    /* struct bdk_trcx_trcrsctlr2_s cn9; */
};
typedef union bdk_trcx_trcrsctlr2 bdk_trcx_trcrsctlr2_t;

static inline uint64_t BDK_TRCX_TRCRSCTLR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCRSCTLR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30208ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030208ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030208ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030208ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030208ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCRSCTLR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCRSCTLR2(a) bdk_trcx_trcrsctlr2_t
#define bustype_BDK_TRCX_TRCRSCTLR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCRSCTLR2(a) "TRCX_TRCRSCTLR2"
#define busnum_BDK_TRCX_TRCRSCTLR2(a) (a)
#define arguments_BDK_TRCX_TRCRSCTLR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcrsctlr3
 *
 * TRC/ETM Resource Selection Control Register 3
 * This register controls the selection of the resources in the trace unit.
 */
union bdk_trcx_trcrsctlr3
{
    uint32_t u;
    struct bdk_trcx_trcrsctlr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_22_31        : 10;
        uint32_t pairinv               : 1;  /**< [ 21: 21](RAZ) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
#else /* Word 0 - Little Endian */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t pairinv               : 1;  /**< [ 21: 21](RAZ) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t reserved_22_31        : 10;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcrsctlr3_s cn8; */
    struct bdk_trcx_trcrsctlr3_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_trcx_trcrsctlr3_s cn83xx; */
    struct bdk_trcx_trcrsctlr3_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_22_31        : 10;
        uint32_t pairinv               : 1;  /**< [ 21: 21](R/W) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
#else /* Word 0 - Little Endian */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t pairinv               : 1;  /**< [ 21: 21](R/W) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t reserved_22_31        : 10;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcrsctlr3 bdk_trcx_trcrsctlr3_t;

static inline uint64_t BDK_TRCX_TRCRSCTLR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCRSCTLR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3020cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00803020cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00803020cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00803020cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00803020cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCRSCTLR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCRSCTLR3(a) bdk_trcx_trcrsctlr3_t
#define bustype_BDK_TRCX_TRCRSCTLR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCRSCTLR3(a) "TRCX_TRCRSCTLR3"
#define busnum_BDK_TRCX_TRCRSCTLR3(a) (a)
#define arguments_BDK_TRCX_TRCRSCTLR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcrsctlr4
 *
 * TRC/ETM Resource Selection Control Register 4
 * This register controls the selection of the resources in the trace unit.
 */
union bdk_trcx_trcrsctlr4
{
    uint32_t u;
    struct bdk_trcx_trcrsctlr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_22_31        : 10;
        uint32_t pairinv               : 1;  /**< [ 21: 21](R/W) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
#else /* Word 0 - Little Endian */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t pairinv               : 1;  /**< [ 21: 21](R/W) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t reserved_22_31        : 10;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcrsctlr4_s cn8; */
    struct bdk_trcx_trcrsctlr4_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_trcx_trcrsctlr4_s cn83xx; */
    /* struct bdk_trcx_trcrsctlr4_s cn9; */
};
typedef union bdk_trcx_trcrsctlr4 bdk_trcx_trcrsctlr4_t;

static inline uint64_t BDK_TRCX_TRCRSCTLR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCRSCTLR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30210ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030210ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030210ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030210ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030210ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCRSCTLR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCRSCTLR4(a) bdk_trcx_trcrsctlr4_t
#define bustype_BDK_TRCX_TRCRSCTLR4(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCRSCTLR4(a) "TRCX_TRCRSCTLR4"
#define busnum_BDK_TRCX_TRCRSCTLR4(a) (a)
#define arguments_BDK_TRCX_TRCRSCTLR4(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcrsctlr5
 *
 * TRC/ETM Resource Selection Control Register 5
 * This register controls the selection of the resources in the trace unit.
 */
union bdk_trcx_trcrsctlr5
{
    uint32_t u;
    struct bdk_trcx_trcrsctlr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_22_31        : 10;
        uint32_t pairinv               : 1;  /**< [ 21: 21](RAZ) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
#else /* Word 0 - Little Endian */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t pairinv               : 1;  /**< [ 21: 21](RAZ) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t reserved_22_31        : 10;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcrsctlr5_s cn8; */
    struct bdk_trcx_trcrsctlr5_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_trcx_trcrsctlr5_s cn83xx; */
    struct bdk_trcx_trcrsctlr5_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_22_31        : 10;
        uint32_t pairinv               : 1;  /**< [ 21: 21](R/W) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
#else /* Word 0 - Little Endian */
        uint32_t select                : 16; /**< [ 15:  0](R/W) Selects one or more resources from the group that the GROUP field selects.
                                                                 Each bit represents a resource from the selected group.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t group                 : 4;  /**< [ 19: 16](R/W) Selects a group of resource.
                                                                 It is implementation defined whether all of the bits are supported. */
        uint32_t inv                   : 1;  /**< [ 20: 20](R/W) Controls whether the resource, that GROUP and SELECT selects, is inverted:
                                                                 0 = The selected resource is not inverted.
                                                                 1 = The selected resource is inverted. */
        uint32_t pairinv               : 1;  /**< [ 21: 21](R/W) For TRCRSCTLRn where n=2,4, this bit controls whether the
                                                                 combined result from a resource pair is inverted:
                                                                 0 = The combined result is not inverted.
                                                                 1 = The combined result is inverted.

                                                                 For TRCRSCTLRn where n=3,5, this bit is RES0.
                                                                 Even is combined with odd. */
        uint32_t reserved_22_31        : 10;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcrsctlr5 bdk_trcx_trcrsctlr5_t;

static inline uint64_t BDK_TRCX_TRCRSCTLR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCRSCTLR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30214ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030214ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030214ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030214ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030214ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCRSCTLR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCRSCTLR5(a) bdk_trcx_trcrsctlr5_t
#define bustype_BDK_TRCX_TRCRSCTLR5(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCRSCTLR5(a) "TRCX_TRCRSCTLR5"
#define busnum_BDK_TRCX_TRCRSCTLR5(a) (a)
#define arguments_BDK_TRCX_TRCRSCTLR5(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcrsctlr6
 *
 * TRC/ETM Resource Selection Control Register 6
 * This register controls the selection of the resources in the trace unit.
 */
union bdk_trcx_trcrsctlr6
{
    uint32_t u;
    struct bdk_trcx_trcrsctlr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcrsctlr6_s cn; */
};
typedef union bdk_trcx_trcrsctlr6 bdk_trcx_trcrsctlr6_t;

static inline uint64_t BDK_TRCX_TRCRSCTLR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCRSCTLR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30218ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030218ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030218ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030218ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030218ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCRSCTLR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCRSCTLR6(a) bdk_trcx_trcrsctlr6_t
#define bustype_BDK_TRCX_TRCRSCTLR6(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCRSCTLR6(a) "TRCX_TRCRSCTLR6"
#define busnum_BDK_TRCX_TRCRSCTLR6(a) (a)
#define arguments_BDK_TRCX_TRCRSCTLR6(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcrsctlr7
 *
 * TRC/ETM Resource Selection Control Register 7
 * This register controls the selection of the resources in the trace unit.
 */
union bdk_trcx_trcrsctlr7
{
    uint32_t u;
    struct bdk_trcx_trcrsctlr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcrsctlr7_s cn; */
};
typedef union bdk_trcx_trcrsctlr7 bdk_trcx_trcrsctlr7_t;

static inline uint64_t BDK_TRCX_TRCRSCTLR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCRSCTLR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3021cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00803021cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00803021cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00803021cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00803021cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCRSCTLR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCRSCTLR7(a) bdk_trcx_trcrsctlr7_t
#define bustype_BDK_TRCX_TRCRSCTLR7(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCRSCTLR7(a) "TRCX_TRCRSCTLR7"
#define busnum_BDK_TRCX_TRCRSCTLR7(a) (a)
#define arguments_BDK_TRCX_TRCRSCTLR7(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcseqevr0
 *
 * TRC/ETM Sequencer State Transition Control Register 0
 * Move sequencer state forwards or backwards.
 */
union bdk_trcx_trcseqevr0
{
    uint32_t u;
    struct bdk_trcx_trcseqevr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t bak                   : 8;  /**< [ 15:  8](R/W) Backwards field: an event selector. */
        uint32_t f                     : 8;  /**< [  7:  0](R/W) Forwards field: an event selector. */
#else /* Word 0 - Little Endian */
        uint32_t f                     : 8;  /**< [  7:  0](R/W) Forwards field: an event selector. */
        uint32_t bak                   : 8;  /**< [ 15:  8](R/W) Backwards field: an event selector. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcseqevr0_s cn; */
};
typedef union bdk_trcx_trcseqevr0 bdk_trcx_trcseqevr0_t;

static inline uint64_t BDK_TRCX_TRCSEQEVR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSEQEVR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30100ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSEQEVR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSEQEVR0(a) bdk_trcx_trcseqevr0_t
#define bustype_BDK_TRCX_TRCSEQEVR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSEQEVR0(a) "TRCX_TRCSEQEVR0"
#define busnum_BDK_TRCX_TRCSEQEVR0(a) (a)
#define arguments_BDK_TRCX_TRCSEQEVR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcseqevr1
 *
 * TRC/ETM Sequencer State Transition Control Register 1
 * Move sequencer state forwards or backwards.
 */
union bdk_trcx_trcseqevr1
{
    uint32_t u;
    struct bdk_trcx_trcseqevr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t bak                   : 8;  /**< [ 15:  8](R/W) Backwards field: an event selector. */
        uint32_t f                     : 8;  /**< [  7:  0](R/W) Forwards field: an event selector. */
#else /* Word 0 - Little Endian */
        uint32_t f                     : 8;  /**< [  7:  0](R/W) Forwards field: an event selector. */
        uint32_t bak                   : 8;  /**< [ 15:  8](R/W) Backwards field: an event selector. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcseqevr1_s cn; */
};
typedef union bdk_trcx_trcseqevr1 bdk_trcx_trcseqevr1_t;

static inline uint64_t BDK_TRCX_TRCSEQEVR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSEQEVR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30104ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSEQEVR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSEQEVR1(a) bdk_trcx_trcseqevr1_t
#define bustype_BDK_TRCX_TRCSEQEVR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSEQEVR1(a) "TRCX_TRCSEQEVR1"
#define busnum_BDK_TRCX_TRCSEQEVR1(a) (a)
#define arguments_BDK_TRCX_TRCSEQEVR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcseqevr2
 *
 * TRC/ETM Sequencer State Transition Control Register 2
 * Move sequencer state forwards or backwards.
 */
union bdk_trcx_trcseqevr2
{
    uint32_t u;
    struct bdk_trcx_trcseqevr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t bak                   : 8;  /**< [ 15:  8](R/W) Backwards field: an event selector. */
        uint32_t f                     : 8;  /**< [  7:  0](R/W) Forwards field: an event selector. */
#else /* Word 0 - Little Endian */
        uint32_t f                     : 8;  /**< [  7:  0](R/W) Forwards field: an event selector. */
        uint32_t bak                   : 8;  /**< [ 15:  8](R/W) Backwards field: an event selector. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcseqevr2_s cn; */
};
typedef union bdk_trcx_trcseqevr2 bdk_trcx_trcseqevr2_t;

static inline uint64_t BDK_TRCX_TRCSEQEVR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSEQEVR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30108ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSEQEVR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSEQEVR2(a) bdk_trcx_trcseqevr2_t
#define bustype_BDK_TRCX_TRCSEQEVR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSEQEVR2(a) "TRCX_TRCSEQEVR2"
#define busnum_BDK_TRCX_TRCSEQEVR2(a) (a)
#define arguments_BDK_TRCX_TRCSEQEVR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcseqevr3
 *
 * TRC/ETM Sequencer State Transition Control Register 3
 * Move sequencer state forwards or backwards.
 */
union bdk_trcx_trcseqevr3
{
    uint32_t u;
    struct bdk_trcx_trcseqevr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t bak                   : 8;  /**< [ 15:  8](R/W) Backwards field: an event selector. */
        uint32_t f                     : 8;  /**< [  7:  0](R/W) Forwards field: an event selector. */
#else /* Word 0 - Little Endian */
        uint32_t f                     : 8;  /**< [  7:  0](R/W) Forwards field: an event selector. */
        uint32_t bak                   : 8;  /**< [ 15:  8](R/W) Backwards field: an event selector. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcseqevr3_s cn; */
};
typedef union bdk_trcx_trcseqevr3 bdk_trcx_trcseqevr3_t;

static inline uint64_t BDK_TRCX_TRCSEQEVR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSEQEVR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3010cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSEQEVR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSEQEVR3(a) bdk_trcx_trcseqevr3_t
#define bustype_BDK_TRCX_TRCSEQEVR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSEQEVR3(a) "TRCX_TRCSEQEVR3"
#define busnum_BDK_TRCX_TRCSEQEVR3(a) (a)
#define arguments_BDK_TRCX_TRCSEQEVR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcseqrstevr
 *
 * TRC/ETM Sequencer Reset Control Register
 * Move the sequencer to state 0 when a programmed event occurs.
 */
union bdk_trcx_trcseqrstevr
{
    uint32_t u;
    struct bdk_trcx_trcseqrstevr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t rst                   : 8;  /**< [  7:  0](R/W) An event selector: when event occurs, move sequencer state to state 0. */
#else /* Word 0 - Little Endian */
        uint32_t rst                   : 8;  /**< [  7:  0](R/W) An event selector: when event occurs, move sequencer state to state 0. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcseqrstevr_s cn; */
};
typedef union bdk_trcx_trcseqrstevr bdk_trcx_trcseqrstevr_t;

static inline uint64_t BDK_TRCX_TRCSEQRSTEVR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSEQRSTEVR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30118ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSEQRSTEVR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSEQRSTEVR(a) bdk_trcx_trcseqrstevr_t
#define bustype_BDK_TRCX_TRCSEQRSTEVR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSEQRSTEVR(a) "TRCX_TRCSEQRSTEVR"
#define busnum_BDK_TRCX_TRCSEQRSTEVR(a) (a)
#define arguments_BDK_TRCX_TRCSEQRSTEVR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcseqstr
 *
 * TRC/ETM Sequencer State Register
 * Set or read the sequencer state.
 */
union bdk_trcx_trcseqstr
{
    uint32_t u;
    struct bdk_trcx_trcseqstr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_2_31         : 30;
        uint32_t state                 : 2;  /**< [  1:  0](R/W) Set or return the state of sequencer.
                                                                     0x0 = state0.
                                                                     0x1 = state1.
                                                                     0x2 = state2.
                                                                     0x3 = state3. */
#else /* Word 0 - Little Endian */
        uint32_t state                 : 2;  /**< [  1:  0](R/W) Set or return the state of sequencer.
                                                                     0x0 = state0.
                                                                     0x1 = state1.
                                                                     0x2 = state2.
                                                                     0x3 = state3. */
        uint32_t reserved_2_31         : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcseqstr_s cn; */
};
typedef union bdk_trcx_trcseqstr bdk_trcx_trcseqstr_t;

static inline uint64_t BDK_TRCX_TRCSEQSTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSEQSTR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3011cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSEQSTR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSEQSTR(a) bdk_trcx_trcseqstr_t
#define bustype_BDK_TRCX_TRCSEQSTR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSEQSTR(a) "TRCX_TRCSEQSTR"
#define busnum_BDK_TRCX_TRCSEQSTR(a) (a)
#define arguments_BDK_TRCX_TRCSEQSTR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcssccr0
 *
 * TRC/ETM Single-Shot Comparator Control Register
 * This register controls the corresponding single-shot comparator resource.
 */
union bdk_trcx_trcssccr0
{
    uint32_t u;
    struct bdk_trcx_trcssccr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcssccr0_s cn; */
};
typedef union bdk_trcx_trcssccr0 bdk_trcx_trcssccr0_t;

static inline uint64_t BDK_TRCX_TRCSSCCR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSSCCR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30280ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030280ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030280ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030280ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030280ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSSCCR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSSCCR0(a) bdk_trcx_trcssccr0_t
#define bustype_BDK_TRCX_TRCSSCCR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSSCCR0(a) "TRCX_TRCSSCCR0"
#define busnum_BDK_TRCX_TRCSSCCR0(a) (a)
#define arguments_BDK_TRCX_TRCSSCCR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcsscsr0
 *
 * TRC/ETM Single-Shot Comparator Status Register
 * This register returns the status of the corresponding single-shot comparator.
 */
union bdk_trcx_trcsscsr0
{
    uint32_t u;
    struct bdk_trcx_trcsscsr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcsscsr0_s cn; */
};
typedef union bdk_trcx_trcsscsr0 bdk_trcx_trcsscsr0_t;

static inline uint64_t BDK_TRCX_TRCSSCSR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSSCSR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc302a0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080302a0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080302a0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080302a0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080302a0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSSCSR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSSCSR0(a) bdk_trcx_trcsscsr0_t
#define bustype_BDK_TRCX_TRCSSCSR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSSCSR0(a) "TRCX_TRCSSCSR0"
#define busnum_BDK_TRCX_TRCSSCSR0(a) (a)
#define arguments_BDK_TRCX_TRCSSCSR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcsspcicr0
 *
 * TRC/ETM Single-Shot PE Comparator Input Control Register
 * This register returns the status of the corresponding single-shot comparator.
 */
union bdk_trcx_trcsspcicr0
{
    uint32_t u;
    struct bdk_trcx_trcsspcicr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcsspcicr0_s cn; */
};
typedef union bdk_trcx_trcsspcicr0 bdk_trcx_trcsspcicr0_t;

static inline uint64_t BDK_TRCX_TRCSSPCICR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSSPCICR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc302c0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080302c0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080302c0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080302c0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080302c0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSSPCICR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSSPCICR0(a) bdk_trcx_trcsspcicr0_t
#define bustype_BDK_TRCX_TRCSSPCICR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSSPCICR0(a) "TRCX_TRCSSPCICR0"
#define busnum_BDK_TRCX_TRCSSPCICR0(a) (a)
#define arguments_BDK_TRCX_TRCSSPCICR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcstallctlr
 *
 * TRC/ETM Stall Control Register
 * Enable trace unit functionality that prevents trace unit buffer overflow.
 */
union bdk_trcx_trcstallctlr
{
    uint32_t u;
    struct bdk_trcx_trcstallctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t nooverflow            : 1;  /**< [ 13: 13](R/W) Trace overflow prevention bit.
                                                                   0 = Trace overflow prevention is disabled.
                                                                   1 = Trace overflow prevention is enabled. This might
                                                                        cause significant performance impact. */
        uint32_t datadiscard           : 2;  /**< [ 12: 11](R/W) Data discard field. Control if a trace unit can discard data trace elements when
                                                                   data trace buffer space is less than [LEVEL]:
                                                                   0x0 = The trace unit must not discard any data trace elements.
                                                                   0x1 = The trace unit can discard P1 and P2 elements associated with data loads.
                                                                   0x2 = The trace unit can discard P1 and P2 elements associated with data stores.
                                                                   0x3 = The trace unit can discard P1 and P2 elements associated with
                                                                         data loads and stores. */
        uint32_t instpriority          : 1;  /**< [ 10: 10](R/W) Prioritize instruction trace bit. Control if a trace unit can prioritize the
                                                                   instruction trace when the instruction trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not prioritize the instruction trace.
                                                                   1 = The trace unit can prioritize the instruction trace. */
        uint32_t dstall                : 1;  /**< [  9:  9](R/W) Data stall bit. Control if a trace unit can stall the PE
                                                                   when the data trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not stall the PE.
                                                                   1 = The trace unit can stall the PE. */
        uint32_t istall                : 1;  /**< [  8:  8](R/W) Instruction stall bit. Control if a trace unit can stall the PE
                                                                   when the instruction trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not stall the PE.
                                                                   1 = The trace unit can stall the PE. */
        uint32_t reserved_4_7          : 4;
        uint32_t level                 : 4;  /**< [  3:  0](R/W) Threshold level field. The field can support 16 monotonic lvel from 0x0 to 0xF.
                                                                   where:
                                                                   0x0 = Zero invasion. The setting has greater risk of FIFO overflow.
                                                                   0xF = Maximum invasion. But the FIFO has less risk of overflow. */
#else /* Word 0 - Little Endian */
        uint32_t level                 : 4;  /**< [  3:  0](R/W) Threshold level field. The field can support 16 monotonic lvel from 0x0 to 0xF.
                                                                   where:
                                                                   0x0 = Zero invasion. The setting has greater risk of FIFO overflow.
                                                                   0xF = Maximum invasion. But the FIFO has less risk of overflow. */
        uint32_t reserved_4_7          : 4;
        uint32_t istall                : 1;  /**< [  8:  8](R/W) Instruction stall bit. Control if a trace unit can stall the PE
                                                                   when the instruction trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not stall the PE.
                                                                   1 = The trace unit can stall the PE. */
        uint32_t dstall                : 1;  /**< [  9:  9](R/W) Data stall bit. Control if a trace unit can stall the PE
                                                                   when the data trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not stall the PE.
                                                                   1 = The trace unit can stall the PE. */
        uint32_t instpriority          : 1;  /**< [ 10: 10](R/W) Prioritize instruction trace bit. Control if a trace unit can prioritize the
                                                                   instruction trace when the instruction trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not prioritize the instruction trace.
                                                                   1 = The trace unit can prioritize the instruction trace. */
        uint32_t datadiscard           : 2;  /**< [ 12: 11](R/W) Data discard field. Control if a trace unit can discard data trace elements when
                                                                   data trace buffer space is less than [LEVEL]:
                                                                   0x0 = The trace unit must not discard any data trace elements.
                                                                   0x1 = The trace unit can discard P1 and P2 elements associated with data loads.
                                                                   0x2 = The trace unit can discard P1 and P2 elements associated with data stores.
                                                                   0x3 = The trace unit can discard P1 and P2 elements associated with
                                                                         data loads and stores. */
        uint32_t nooverflow            : 1;  /**< [ 13: 13](R/W) Trace overflow prevention bit.
                                                                   0 = Trace overflow prevention is disabled.
                                                                   1 = Trace overflow prevention is enabled. This might
                                                                        cause significant performance impact. */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcstallctlr_s cn8; */
    struct bdk_trcx_trcstallctlr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t nooverflow            : 1;  /**< [ 13: 13](RAZ) Trace overflow prevention bit.
                                                                   0 = Trace overflow prevention is disabled.
                                                                   1 = Trace overflow prevention is enabled. This might
                                                                        cause significant performance impact. */
        uint32_t datadiscard           : 2;  /**< [ 12: 11](RAZ) Data discard field. Control if a trace unit can discard data trace elements when
                                                                   data trace buffer space is less than [LEVEL]:
                                                                   0x0 = The trace unit must not discard any data trace elements.
                                                                   0x1 = The trace unit can discard P1 and P2 elements associated with data loads.
                                                                   0x2 = The trace unit can discard P1 and P2 elements associated with data stores.
                                                                   0x3 = The trace unit can discard P1 and P2 elements associated with
                                                                         data loads and stores. */
        uint32_t instpriority          : 1;  /**< [ 10: 10](RAZ) Prioritize instruction trace bit. Control if a trace unit can prioritize the
                                                                   instruction trace when the instruction trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not prioritize the instruction trace.
                                                                   1 = The trace unit can prioritize the instruction trace. */
        uint32_t dstall                : 1;  /**< [  9:  9](RAZ) Data stall bit. Control if a trace unit can stall the PE
                                                                   when the data trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not stall the PE.
                                                                   1 = The trace unit can stall the PE. */
        uint32_t istall                : 1;  /**< [  8:  8](R/W) Instruction stall bit. Control if a trace unit can stall the PE
                                                                   when the instruction trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not stall the PE.
                                                                   1 = The trace unit can stall the PE. */
        uint32_t reserved_4_7          : 4;
        uint32_t level                 : 4;  /**< [  3:  0](R/W) Threshold level field. The field can support 16 monotonic lvel from 0x0 to 0xF.
                                                                   where:
                                                                   0x0 = Zero invasion. The setting has greater risk of FIFO overflow.
                                                                   0xF = Maximum invasion. But the FIFO has less risk of overflow. */
#else /* Word 0 - Little Endian */
        uint32_t level                 : 4;  /**< [  3:  0](R/W) Threshold level field. The field can support 16 monotonic lvel from 0x0 to 0xF.
                                                                   where:
                                                                   0x0 = Zero invasion. The setting has greater risk of FIFO overflow.
                                                                   0xF = Maximum invasion. But the FIFO has less risk of overflow. */
        uint32_t reserved_4_7          : 4;
        uint32_t istall                : 1;  /**< [  8:  8](R/W) Instruction stall bit. Control if a trace unit can stall the PE
                                                                   when the instruction trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not stall the PE.
                                                                   1 = The trace unit can stall the PE. */
        uint32_t dstall                : 1;  /**< [  9:  9](RAZ) Data stall bit. Control if a trace unit can stall the PE
                                                                   when the data trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not stall the PE.
                                                                   1 = The trace unit can stall the PE. */
        uint32_t instpriority          : 1;  /**< [ 10: 10](RAZ) Prioritize instruction trace bit. Control if a trace unit can prioritize the
                                                                   instruction trace when the instruction trace buffer space is less than [LEVEL]:
                                                                   0 = The trace unit must not prioritize the instruction trace.
                                                                   1 = The trace unit can prioritize the instruction trace. */
        uint32_t datadiscard           : 2;  /**< [ 12: 11](RAZ) Data discard field. Control if a trace unit can discard data trace elements when
                                                                   data trace buffer space is less than [LEVEL]:
                                                                   0x0 = The trace unit must not discard any data trace elements.
                                                                   0x1 = The trace unit can discard P1 and P2 elements associated with data loads.
                                                                   0x2 = The trace unit can discard P1 and P2 elements associated with data stores.
                                                                   0x3 = The trace unit can discard P1 and P2 elements associated with
                                                                         data loads and stores. */
        uint32_t nooverflow            : 1;  /**< [ 13: 13](RAZ) Trace overflow prevention bit.
                                                                   0 = Trace overflow prevention is disabled.
                                                                   1 = Trace overflow prevention is enabled. This might
                                                                        cause significant performance impact. */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcstallctlr bdk_trcx_trcstallctlr_t;

static inline uint64_t BDK_TRCX_TRCSTALLCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSTALLCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3002cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00803002cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00803002cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00803002cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00803002cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSTALLCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSTALLCTLR(a) bdk_trcx_trcstallctlr_t
#define bustype_BDK_TRCX_TRCSTALLCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSTALLCTLR(a) "TRCX_TRCSTALLCTLR"
#define busnum_BDK_TRCX_TRCSTALLCTLR(a) (a)
#define arguments_BDK_TRCX_TRCSTALLCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcstatr
 *
 * TRC/ETM Trace Status Register
 * Trace unit status.
 */
union bdk_trcx_trcstatr
{
    uint32_t u;
    struct bdk_trcx_trcstatr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_2_31         : 30;
        uint32_t pmstable              : 1;  /**< [  1:  1](RO) This bit is valid only when either TRC()_TRCPRGCTRL[EN] = 0 or the OS lock is locked.
                                                                 0 = Programmer's model is not stable.
                                                                 1 = Programmer's model is stable. */
        uint32_t idle                  : 1;  /**< [  0:  0](RO) Idle status bit.
                                                                 0 = The trace unit is not idle.
                                                                 1 = The trace unit is idle. */
#else /* Word 0 - Little Endian */
        uint32_t idle                  : 1;  /**< [  0:  0](RO) Idle status bit.
                                                                 0 = The trace unit is not idle.
                                                                 1 = The trace unit is idle. */
        uint32_t pmstable              : 1;  /**< [  1:  1](RO) This bit is valid only when either TRC()_TRCPRGCTRL[EN] = 0 or the OS lock is locked.
                                                                 0 = Programmer's model is not stable.
                                                                 1 = Programmer's model is stable. */
        uint32_t reserved_2_31         : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcstatr_s cn; */
};
typedef union bdk_trcx_trcstatr bdk_trcx_trcstatr_t;

static inline uint64_t BDK_TRCX_TRCSTATR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSTATR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3000cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00803000cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00803000cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00803000cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00803000cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSTATR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSTATR(a) bdk_trcx_trcstatr_t
#define bustype_BDK_TRCX_TRCSTATR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSTATR(a) "TRCX_TRCSTATR"
#define busnum_BDK_TRCX_TRCSTATR(a) (a)
#define arguments_BDK_TRCX_TRCSTATR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcsyncpr
 *
 * TRC/ETM Synchronization Period Register
 * This register controls how often trace synchronization request occurs.
 */
union bdk_trcx_trcsyncpr
{
    uint32_t u;
    struct bdk_trcx_trcsyncpr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_5_31         : 27;
        uint32_t period                : 5;  /**< [  4:  0](R/W) Control how many bytes of trace that a trace unit can generate
                                                                   before the trace synchronization request occurs.
                                                                   0x00 = Trace synchronization requests are disabled.
                                                                   0x10 = Trace synchronization requests occur after 256 bytes of trace.
                                                                   0x11 = Trace synchronization requests occur after 512 bytes of trace.
                                                                   0x14 = Trace synchronization requests occur after 20 power of 2 bytes of trace. */
#else /* Word 0 - Little Endian */
        uint32_t period                : 5;  /**< [  4:  0](R/W) Control how many bytes of trace that a trace unit can generate
                                                                   before the trace synchronization request occurs.
                                                                   0x00 = Trace synchronization requests are disabled.
                                                                   0x10 = Trace synchronization requests occur after 256 bytes of trace.
                                                                   0x11 = Trace synchronization requests occur after 512 bytes of trace.
                                                                   0x14 = Trace synchronization requests occur after 20 power of 2 bytes of trace. */
        uint32_t reserved_5_31         : 27;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcsyncpr_s cn; */
};
typedef union bdk_trcx_trcsyncpr bdk_trcx_trcsyncpr_t;

static inline uint64_t BDK_TRCX_TRCSYNCPR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCSYNCPR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30034ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030034ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030034ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030034ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030034ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCSYNCPR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCSYNCPR(a) bdk_trcx_trcsyncpr_t
#define bustype_BDK_TRCX_TRCSYNCPR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCSYNCPR(a) "TRCX_TRCSYNCPR"
#define busnum_BDK_TRCX_TRCSYNCPR(a) (a)
#define arguments_BDK_TRCX_TRCSYNCPR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trctraceidr
 *
 * TRC/ETM Trace ID Register
 * Set the Trace ID value for instruction trace.
 */
union bdk_trcx_trctraceidr
{
    uint32_t u;
    struct bdk_trcx_trctraceidr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_7_31         : 25;
        uint32_t traceid               : 7;  /**< [  6:  0](R/W) Trace ID value for instruction trace. */
#else /* Word 0 - Little Endian */
        uint32_t traceid               : 7;  /**< [  6:  0](R/W) Trace ID value for instruction trace. */
        uint32_t reserved_7_31         : 25;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trctraceidr_s cn; */
};
typedef union bdk_trcx_trctraceidr bdk_trcx_trctraceidr_t;

static inline uint64_t BDK_TRCX_TRCTRACEIDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCTRACEIDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30040ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030040ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030040ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030040ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030040ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCTRACEIDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCTRACEIDR(a) bdk_trcx_trctraceidr_t
#define bustype_BDK_TRCX_TRCTRACEIDR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCTRACEIDR(a) "TRCX_TRCTRACEIDR"
#define busnum_BDK_TRCX_TRCTRACEIDR(a) (a)
#define arguments_BDK_TRCX_TRCTRACEIDR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trctsctlr
 *
 * TRC/ETM Global Timestamp Control Register
 * This register controls the insertion of global timestamps in the trace streams.
 */
union bdk_trcx_trctsctlr
{
    uint32_t u;
    struct bdk_trcx_trctsctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t eventsel              : 8;  /**< [  7:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t eventsel              : 8;  /**< [  7:  0](RAZ) Reserved. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trctsctlr_s cn8; */
    struct bdk_trcx_trctsctlr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t eventsel              : 8;  /**< [  7:  0](R/W) An event selector. When the selected event is triggered, the trace unit
                                                                   inserts a global timestamp into the trace streams. */
#else /* Word 0 - Little Endian */
        uint32_t eventsel              : 8;  /**< [  7:  0](R/W) An event selector. When the selected event is triggered, the trace unit
                                                                   inserts a global timestamp into the trace streams. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trctsctlr bdk_trcx_trctsctlr_t;

static inline uint64_t BDK_TRCX_TRCTSCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCTSCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30030ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030030ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030030ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030030ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030030ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCTSCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCTSCTLR(a) bdk_trcx_trctsctlr_t
#define bustype_BDK_TRCX_TRCTSCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCTSCTLR(a) "TRCX_TRCTSCTLR"
#define busnum_BDK_TRCX_TRCTSCTLR(a) (a)
#define arguments_BDK_TRCX_TRCTSCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcvdarcctlr
 *
 * TRC/ETM ViewData Include/Exclude Address Range Comparator Control Register
 * Set or read the address range comparator for ViewData include/exclude control.
 */
union bdk_trcx_trcvdarcctlr
{
    uint32_t u;
    struct bdk_trcx_trcvdarcctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t exclude               : 4;  /**< [ 19: 16](R/W) Select which address range comparators are in use with ViewData exclude control.
                                                                 0 = The address range that the address comparator pair[m-16] defines is not
                                                                      selected for the ViewData exclude control.
                                                                 1 = The address range that the address comparator pair[m-16] defines is
                                                                      selected for the ViewData exclude control. */
        uint32_t reserved_4_15         : 12;
        uint32_t incld                 : 4;  /**< [  3:  0](R/W) Select which address range comparators are in use with ViewData include control.
                                                                 0 = The address range that the address comparator pair[m] defines is not
                                                                      selected for the ViewData include control.
                                                                 1 = The address range that the address comparator pair[m] defines is
                                                                      selected for the ViewData include control. */
#else /* Word 0 - Little Endian */
        uint32_t incld                 : 4;  /**< [  3:  0](R/W) Select which address range comparators are in use with ViewData include control.
                                                                 0 = The address range that the address comparator pair[m] defines is not
                                                                      selected for the ViewData include control.
                                                                 1 = The address range that the address comparator pair[m] defines is
                                                                      selected for the ViewData include control. */
        uint32_t reserved_4_15         : 12;
        uint32_t exclude               : 4;  /**< [ 19: 16](R/W) Select which address range comparators are in use with ViewData exclude control.
                                                                 0 = The address range that the address comparator pair[m-16] defines is not
                                                                      selected for the ViewData exclude control.
                                                                 1 = The address range that the address comparator pair[m-16] defines is
                                                                      selected for the ViewData exclude control. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcvdarcctlr_s cn; */
};
typedef union bdk_trcx_trcvdarcctlr bdk_trcx_trcvdarcctlr_t;

static inline uint64_t BDK_TRCX_TRCVDARCCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVDARCCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc300a8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080300a8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080300a8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080300a8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080300a8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVDARCCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVDARCCTLR(a) bdk_trcx_trcvdarcctlr_t
#define bustype_BDK_TRCX_TRCVDARCCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCVDARCCTLR(a) "TRCX_TRCVDARCCTLR"
#define busnum_BDK_TRCX_TRCVDARCCTLR(a) (a)
#define arguments_BDK_TRCX_TRCVDARCCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcvdctlr
 *
 * TRC/ETM ViewData Main Control Register
 * This register controls data trace filtering.
 */
union bdk_trcx_trcvdctlr
{
    uint32_t u;
    struct bdk_trcx_trcvdctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_13_31        : 19;
        uint32_t trcexdata             : 1;  /**< [ 12: 12](R/W) Control the tracing of data transfer for exception and exception return.
                                                                 0 = exception and exception return data transfers are not traced.
                                                                 1 = exception and exception return data transfers are traced. */
        uint32_t tbi                   : 1;  /**< [ 11: 11](R/W) Control which information a trace unit populates in bit[63:56] of the data address.
                                                                 0 = The trace unit assign bit[63:56] have the value of bit[55] of the data address,
                                                                     which is sign extension.
                                                                 1 = The trace unit assign bit[63:56] have the value of bit[63:56] of the data address. */
        uint32_t pcrel                 : 1;  /**< [ 10: 10](R/W) Control whether a trace unit trace data for transfers that are
                                                                   relative to PC (program counter).
                                                                 0 = The trace unit does not affect tracing of PC relative transfers.
                                                                 1 = The trace unit does not trace the address or value portions of PC relative transfers. */
        uint32_t sprel                 : 2;  /**< [  9:  8](R/W) Control whether a trace unit trace data for transfers that are
                                                                   relative to SP (stack pointer).
                                                                 0x0 = The trace unit does not affect tracing of SP relative transfers.
                                                                 0x1 = Reserved
                                                                 0x2 = The trace unit does not trace the address portions of SP relative transfers.
                                                                 0x3 = The trace unit does not trace the address or value portions of SP relative
                                                                 transfers. */
        uint32_t evnt                  : 8;  /**< [  7:  0](R/W) An event selector. */
#else /* Word 0 - Little Endian */
        uint32_t evnt                  : 8;  /**< [  7:  0](R/W) An event selector. */
        uint32_t sprel                 : 2;  /**< [  9:  8](R/W) Control whether a trace unit trace data for transfers that are
                                                                   relative to SP (stack pointer).
                                                                 0x0 = The trace unit does not affect tracing of SP relative transfers.
                                                                 0x1 = Reserved
                                                                 0x2 = The trace unit does not trace the address portions of SP relative transfers.
                                                                 0x3 = The trace unit does not trace the address or value portions of SP relative
                                                                 transfers. */
        uint32_t pcrel                 : 1;  /**< [ 10: 10](R/W) Control whether a trace unit trace data for transfers that are
                                                                   relative to PC (program counter).
                                                                 0 = The trace unit does not affect tracing of PC relative transfers.
                                                                 1 = The trace unit does not trace the address or value portions of PC relative transfers. */
        uint32_t tbi                   : 1;  /**< [ 11: 11](R/W) Control which information a trace unit populates in bit[63:56] of the data address.
                                                                 0 = The trace unit assign bit[63:56] have the value of bit[55] of the data address,
                                                                     which is sign extension.
                                                                 1 = The trace unit assign bit[63:56] have the value of bit[63:56] of the data address. */
        uint32_t trcexdata             : 1;  /**< [ 12: 12](R/W) Control the tracing of data transfer for exception and exception return.
                                                                 0 = exception and exception return data transfers are not traced.
                                                                 1 = exception and exception return data transfers are traced. */
        uint32_t reserved_13_31        : 19;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcvdctlr_s cn; */
};
typedef union bdk_trcx_trcvdctlr bdk_trcx_trcvdctlr_t;

static inline uint64_t BDK_TRCX_TRCVDCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVDCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc300a0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080300a0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080300a0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080300a0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080300a0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVDCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVDCTLR(a) bdk_trcx_trcvdctlr_t
#define bustype_BDK_TRCX_TRCVDCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCVDCTLR(a) "TRCX_TRCVDCTLR"
#define busnum_BDK_TRCX_TRCVDCTLR(a) (a)
#define arguments_BDK_TRCX_TRCVDCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcvdsacctlr
 *
 * TRC/ETM ViewData Include/Exclude Single Address Comparator Control Register
 * Set or read the single address comparator for ViewData include/exclude control.
 */
union bdk_trcx_trcvdsacctlr
{
    uint32_t u;
    struct bdk_trcx_trcvdsacctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t exclude               : 4;  /**< [ 19: 16](R/W) Select which single address comparators are in use with ViewData exclude control.
                                                                 0 = The single address comparator[m-16] is not
                                                                      selected for the ViewData exclude control.
                                                                 1 = The single address comparator[m-16] is
                                                                      selected for the ViewData exclude control. */
        uint32_t reserved_4_15         : 12;
        uint32_t incld                 : 4;  /**< [  3:  0](R/W) Select which single address comparators are in use with ViewData include control.
                                                                 0 = The single address comparator[m] is not
                                                                      selected for the ViewData include control.
                                                                 1 = The single address comparator[m] is
                                                                      selected for the ViewData include control. */
#else /* Word 0 - Little Endian */
        uint32_t incld                 : 4;  /**< [  3:  0](R/W) Select which single address comparators are in use with ViewData include control.
                                                                 0 = The single address comparator[m] is not
                                                                      selected for the ViewData include control.
                                                                 1 = The single address comparator[m] is
                                                                      selected for the ViewData include control. */
        uint32_t reserved_4_15         : 12;
        uint32_t exclude               : 4;  /**< [ 19: 16](R/W) Select which single address comparators are in use with ViewData exclude control.
                                                                 0 = The single address comparator[m-16] is not
                                                                      selected for the ViewData exclude control.
                                                                 1 = The single address comparator[m-16] is
                                                                      selected for the ViewData exclude control. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcvdsacctlr_s cn; */
};
typedef union bdk_trcx_trcvdsacctlr bdk_trcx_trcvdsacctlr_t;

static inline uint64_t BDK_TRCX_TRCVDSACCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVDSACCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc300a4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080300a4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080300a4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080300a4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080300a4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVDSACCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVDSACCTLR(a) bdk_trcx_trcvdsacctlr_t
#define bustype_BDK_TRCX_TRCVDSACCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCVDSACCTLR(a) "TRCX_TRCVDSACCTLR"
#define busnum_BDK_TRCX_TRCVDSACCTLR(a) (a)
#define arguments_BDK_TRCX_TRCVDSACCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcvictlr
 *
 * TRC/ETM ViewInst Main Control Register
 * This register controls instruction trace filtering.
 */
union bdk_trcx_trcvictlr
{
    uint32_t u;
    struct bdk_trcx_trcvictlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t level_ns              : 4;  /**< [ 23: 20](R/W) In nonsecure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<20\>  exception level 0.
                                                                    \<21\>  exception level 1.
                                                                    \<22\>  exception level 2.
                                                                    \<23\>  RAZ/WI. */
        uint32_t reserved_12_19        : 8;
        uint32_t trcerr                : 1;  /**< [ 11: 11](R/W) Control whether a trace unit must trace a system error exception.
                                                                 0 = The trace unit does not trace a system error exception.
                                                                 1 = The trace unit always traces a system error exception. */
        uint32_t trcreset              : 1;  /**< [ 10: 10](R/W) Control whether a trace unit must trace a reset exception.
                                                                 0 = The trace unit does not trace a reset exception.
                                                                 1 = The trace unit always traces a reset exception. */
        uint32_t ssstatus              : 1;  /**< [  9:  9](R/W) This bit return the status of start-stop logic.
                                                                 0 = The start-stop logic is in stop state.
                                                                 1 = The start-stop logic is in start state. */
        uint32_t reserved_8            : 1;
        uint32_t evnt                  : 8;  /**< [  7:  0](R/W) An event selector. */
#else /* Word 0 - Little Endian */
        uint32_t evnt                  : 8;  /**< [  7:  0](R/W) An event selector. */
        uint32_t reserved_8            : 1;
        uint32_t ssstatus              : 1;  /**< [  9:  9](R/W) This bit return the status of start-stop logic.
                                                                 0 = The start-stop logic is in stop state.
                                                                 1 = The start-stop logic is in start state. */
        uint32_t trcreset              : 1;  /**< [ 10: 10](R/W) Control whether a trace unit must trace a reset exception.
                                                                 0 = The trace unit does not trace a reset exception.
                                                                 1 = The trace unit always traces a reset exception. */
        uint32_t trcerr                : 1;  /**< [ 11: 11](R/W) Control whether a trace unit must trace a system error exception.
                                                                 0 = The trace unit does not trace a system error exception.
                                                                 1 = The trace unit always traces a system error exception. */
        uint32_t reserved_12_19        : 8;
        uint32_t level_ns              : 4;  /**< [ 23: 20](R/W) In nonsecure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<20\>  exception level 0.
                                                                    \<21\>  exception level 1.
                                                                    \<22\>  exception level 2.
                                                                    \<23\>  RAZ/WI. */
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcvictlr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t level_ns              : 4;  /**< [ 23: 20](R/W) In nonsecure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<20\>  exception level 0.
                                                                    \<21\>  exception level 1.
                                                                    \<22\>  exception level 2.
                                                                    \<23\>  RAZ/WI. */
        uint32_t level_s               : 4;  /**< [ 19: 16](R/W) In secure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<16\> = exception level 0.
                                                                    \<17\> = exception level 1.
                                                                    \<18\> = RAZ/WI.
                                                                    \<19\> = exception level 3. */
        uint32_t reserved_12_15        : 4;
        uint32_t trcerr                : 1;  /**< [ 11: 11](R/W) Control whether a trace unit must trace a system error exception.
                                                                 0 = The trace unit does not trace a system error exception.
                                                                 1 = The trace unit always traces a system error exception. */
        uint32_t trcreset              : 1;  /**< [ 10: 10](R/W) Control whether a trace unit must trace a reset exception.
                                                                 0 = The trace unit does not trace a reset exception.
                                                                 1 = The trace unit always traces a reset exception. */
        uint32_t ssstatus              : 1;  /**< [  9:  9](R/W) This bit return the status of start-stop logic.
                                                                 0 = The start-stop logic is in stop state.
                                                                 1 = The start-stop logic is in start state. */
        uint32_t reserved_8            : 1;
        uint32_t evnt                  : 8;  /**< [  7:  0](R/W) An event selector. */
#else /* Word 0 - Little Endian */
        uint32_t evnt                  : 8;  /**< [  7:  0](R/W) An event selector. */
        uint32_t reserved_8            : 1;
        uint32_t ssstatus              : 1;  /**< [  9:  9](R/W) This bit return the status of start-stop logic.
                                                                 0 = The start-stop logic is in stop state.
                                                                 1 = The start-stop logic is in start state. */
        uint32_t trcreset              : 1;  /**< [ 10: 10](R/W) Control whether a trace unit must trace a reset exception.
                                                                 0 = The trace unit does not trace a reset exception.
                                                                 1 = The trace unit always traces a reset exception. */
        uint32_t trcerr                : 1;  /**< [ 11: 11](R/W) Control whether a trace unit must trace a system error exception.
                                                                 0 = The trace unit does not trace a system error exception.
                                                                 1 = The trace unit always traces a system error exception. */
        uint32_t reserved_12_15        : 4;
        uint32_t level_s               : 4;  /**< [ 19: 16](R/W) In secure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<16\> = exception level 0.
                                                                    \<17\> = exception level 1.
                                                                    \<18\> = RAZ/WI.
                                                                    \<19\> = exception level 3. */
        uint32_t level_ns              : 4;  /**< [ 23: 20](R/W) In nonsecure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<20\>  exception level 0.
                                                                    \<21\>  exception level 1.
                                                                    \<22\>  exception level 2.
                                                                    \<23\>  RAZ/WI. */
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_trcx_trcvictlr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_23_31        : 9;
        uint32_t level_ns              : 3;  /**< [ 22: 20](R/W) In nonsecure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<20\>  exception level 0.
                                                                    \<21\>  exception level 1.
                                                                    \<22\>  exception level 2. */
        uint32_t level_s2              : 1;  /**< [ 19: 19](R/W) Used with [17:16]. See  LEVEL_S */
        uint32_t reserved_18           : 1;
        uint32_t level_s               : 2;  /**< [ 17: 16](R/W) In secure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<16\> = exception level 0.
                                                                    \<17\> = exception level 1.
                                                                    \<18\> = RAZ/WI.
                                                                    \<19\> = exception level 3. */
        uint32_t reserved_12_15        : 4;
        uint32_t trcerr                : 1;  /**< [ 11: 11](RAZ) Control whether a trace unit must trace a system error exception.
                                                                 0 = The trace unit does not trace a system error exception.
                                                                 1 = The trace unit always traces a system error exception. */
        uint32_t trcreset              : 1;  /**< [ 10: 10](R/W) Control whether a trace unit must trace a reset exception.
                                                                 0 = The trace unit does not trace a reset exception.
                                                                 1 = The trace unit always traces a reset exception. */
        uint32_t ssstatus              : 1;  /**< [  9:  9](RO) This bit return the status of start-stop logic.
                                                                 0 = The start-stop logic is in stop state.
                                                                 1 = The start-stop logic is in start state. */
        uint32_t reserved_8            : 1;
        uint32_t evnt                  : 8;  /**< [  7:  0](R/W) An event selector. */
#else /* Word 0 - Little Endian */
        uint32_t evnt                  : 8;  /**< [  7:  0](R/W) An event selector. */
        uint32_t reserved_8            : 1;
        uint32_t ssstatus              : 1;  /**< [  9:  9](RO) This bit return the status of start-stop logic.
                                                                 0 = The start-stop logic is in stop state.
                                                                 1 = The start-stop logic is in start state. */
        uint32_t trcreset              : 1;  /**< [ 10: 10](R/W) Control whether a trace unit must trace a reset exception.
                                                                 0 = The trace unit does not trace a reset exception.
                                                                 1 = The trace unit always traces a reset exception. */
        uint32_t trcerr                : 1;  /**< [ 11: 11](RAZ) Control whether a trace unit must trace a system error exception.
                                                                 0 = The trace unit does not trace a system error exception.
                                                                 1 = The trace unit always traces a system error exception. */
        uint32_t reserved_12_15        : 4;
        uint32_t level_s               : 2;  /**< [ 17: 16](R/W) In secure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<16\> = exception level 0.
                                                                    \<17\> = exception level 1.
                                                                    \<18\> = RAZ/WI.
                                                                    \<19\> = exception level 3. */
        uint32_t reserved_18           : 1;
        uint32_t level_s2              : 1;  /**< [ 19: 19](R/W) Used with [17:16]. See  LEVEL_S */
        uint32_t level_ns              : 3;  /**< [ 22: 20](R/W) In nonsecure state, each bit control whether instruction tracing is enabled for
                                                                   the corresponding exception level.
                                                                 0 = the trace unit generates the instruction trace for exception level n.
                                                                 1 = the trace unit dos not generate the instruction trace for exception level n.
                                                                    \<20\>  exception level 0.
                                                                    \<21\>  exception level 1.
                                                                    \<22\>  exception level 2. */
        uint32_t reserved_23_31        : 9;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcvictlr bdk_trcx_trcvictlr_t;

static inline uint64_t BDK_TRCX_TRCVICTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVICTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30080ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030080ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030080ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030080ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030080ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVICTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVICTLR(a) bdk_trcx_trcvictlr_t
#define bustype_BDK_TRCX_TRCVICTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCVICTLR(a) "TRCX_TRCVICTLR"
#define busnum_BDK_TRCX_TRCVICTLR(a) (a)
#define arguments_BDK_TRCX_TRCVICTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcviiectlr
 *
 * TRC/ETM ViewInst Include/Exclude Control Register
 * Set or read ViewInst include/exclude address comparator.
 */
union bdk_trcx_trcviiectlr
{
    uint32_t u;
    struct bdk_trcx_trcviiectlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t exclude               : 4;  /**< [ 19: 16](R/W) Exclude range field. Bit[m]
                                                                 0 = The address range that the address comparator pair[m-16] defines is not
                                                                      selected for the ViewInst exclude control.
                                                                 1 = The address range that the address comparator pair[m-16] defines is
                                                                      selected for the ViewInst exclude control. */
        uint32_t reserved_4_15         : 12;
        uint32_t incld                 : 4;  /**< [  3:  0](R/W) Include range field.
                                                                 0 = The address range that the address comparator pair[m] defines is not
                                                                      selected for the ViewInst include control.
                                                                 1 = The address range that the address comparator pair[m] defines is
                                                                      selected for the ViewInst include control. */
#else /* Word 0 - Little Endian */
        uint32_t incld                 : 4;  /**< [  3:  0](R/W) Include range field.
                                                                 0 = The address range that the address comparator pair[m] defines is not
                                                                      selected for the ViewInst include control.
                                                                 1 = The address range that the address comparator pair[m] defines is
                                                                      selected for the ViewInst include control. */
        uint32_t reserved_4_15         : 12;
        uint32_t exclude               : 4;  /**< [ 19: 16](R/W) Exclude range field. Bit[m]
                                                                 0 = The address range that the address comparator pair[m-16] defines is not
                                                                      selected for the ViewInst exclude control.
                                                                 1 = The address range that the address comparator pair[m-16] defines is
                                                                      selected for the ViewInst exclude control. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcviiectlr_s cn; */
};
typedef union bdk_trcx_trcviiectlr bdk_trcx_trcviiectlr_t;

static inline uint64_t BDK_TRCX_TRCVIIECTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVIIECTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30084ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030084ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030084ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030084ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030084ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVIIECTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVIIECTLR(a) bdk_trcx_trcviiectlr_t
#define bustype_BDK_TRCX_TRCVIIECTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCVIIECTLR(a) "TRCX_TRCVIIECTLR"
#define busnum_BDK_TRCX_TRCVIIECTLR(a) (a)
#define arguments_BDK_TRCX_TRCVIIECTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcvipcssctlr
 *
 * TRC/ETM ViewInst Start/Stop PE Comparator Control Register
 * Read which PE comparator can control ViewInst start-stop logic.
 */
union bdk_trcx_trcvipcssctlr
{
    uint32_t u;
    struct bdk_trcx_trcvipcssctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t stop                  : 4;  /**< [ 19: 16](R/W) Select which PE comparator inputs are in use with ViewInst start-stop control,
                                                                   for the purpose of stopping trace.
                                                                 0 = The single PE comparator[m-16] is not
                                                                      selected as a stop resource.
                                                                 1 = The single PE comparator[m-16] is
                                                                      selected as a stop resource. */
        uint32_t reserved_4_15         : 12;
        uint32_t start                 : 4;  /**< [  3:  0](R/W) Select which PE comparator inputs are in use with ViewInst start-stop control,
                                                                   for the purpose of starting trace.
                                                                 0 = The single PE comparator[m] is not
                                                                      selected as a start resource.
                                                                 1 = The single PE comparator[m] is
                                                                      selected as a start resource. */
#else /* Word 0 - Little Endian */
        uint32_t start                 : 4;  /**< [  3:  0](R/W) Select which PE comparator inputs are in use with ViewInst start-stop control,
                                                                   for the purpose of starting trace.
                                                                 0 = The single PE comparator[m] is not
                                                                      selected as a start resource.
                                                                 1 = The single PE comparator[m] is
                                                                      selected as a start resource. */
        uint32_t reserved_4_15         : 12;
        uint32_t stop                  : 4;  /**< [ 19: 16](R/W) Select which PE comparator inputs are in use with ViewInst start-stop control,
                                                                   for the purpose of stopping trace.
                                                                 0 = The single PE comparator[m-16] is not
                                                                      selected as a stop resource.
                                                                 1 = The single PE comparator[m-16] is
                                                                      selected as a stop resource. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcvipcssctlr_s cn; */
};
typedef union bdk_trcx_trcvipcssctlr bdk_trcx_trcvipcssctlr_t;

static inline uint64_t BDK_TRCX_TRCVIPCSSCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVIPCSSCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3008cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00803008cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00803008cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00803008cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00803008cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVIPCSSCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVIPCSSCTLR(a) bdk_trcx_trcvipcssctlr_t
#define bustype_BDK_TRCX_TRCVIPCSSCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCVIPCSSCTLR(a) "TRCX_TRCVIPCSSCTLR"
#define busnum_BDK_TRCX_TRCVIPCSSCTLR(a) (a)
#define arguments_BDK_TRCX_TRCVIPCSSCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcvissctlr
 *
 * TRC/ETM ViewInst Start/Stop Control Register
 * Set or read the single address comparator that controls start-stop logic.
 */
union bdk_trcx_trcvissctlr
{
    uint32_t u;
    struct bdk_trcx_trcvissctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t stop                  : 8;  /**< [ 23: 16](R/W) Select which address comparators are in use with ViewInst start-stop control,
                                                                   for the purpose of stopping trace.
                                                                 0 = The single address comparator[m-16] is not
                                                                      selected as a stop resource.
                                                                 1 = The single address comparator[m-16] is
                                                                      selected as a stop resource. */
        uint32_t reserved_8_15         : 8;
        uint32_t start                 : 8;  /**< [  7:  0](R/W) Select which address comparators are in use with ViewInst start-stop control,
                                                                   for the purpose of starting trace.
                                                                 0 = The single address comparator[m] is not
                                                                      selected as a start resource.
                                                                 1 = The single address comparator[m] is
                                                                      selected as a start resource. */
#else /* Word 0 - Little Endian */
        uint32_t start                 : 8;  /**< [  7:  0](R/W) Select which address comparators are in use with ViewInst start-stop control,
                                                                   for the purpose of starting trace.
                                                                 0 = The single address comparator[m] is not
                                                                      selected as a start resource.
                                                                 1 = The single address comparator[m] is
                                                                      selected as a start resource. */
        uint32_t reserved_8_15         : 8;
        uint32_t stop                  : 8;  /**< [ 23: 16](R/W) Select which address comparators are in use with ViewInst start-stop control,
                                                                   for the purpose of stopping trace.
                                                                 0 = The single address comparator[m-16] is not
                                                                      selected as a stop resource.
                                                                 1 = The single address comparator[m-16] is
                                                                      selected as a stop resource. */
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcvissctlr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t stop                  : 4;  /**< [ 19: 16](R/W) Select which address comparators are in use with ViewInst start-stop control,
                                                                   for the purpose of stopping trace.
                                                                 0 = The single address comparator[m-16] is not
                                                                      selected as a stop resource.
                                                                 1 = The single address comparator[m-16] is
                                                                      selected as a stop resource. */
        uint32_t reserved_4_15         : 12;
        uint32_t start                 : 4;  /**< [  3:  0](R/W) Select which address comparators are in use with ViewInst start-stop control,
                                                                   for the purpose of starting trace.
                                                                 0 = The single address comparator[m] is not
                                                                      selected as a start resource.
                                                                 1 = The single address comparator[m] is
                                                                      selected as a start resource. */
#else /* Word 0 - Little Endian */
        uint32_t start                 : 4;  /**< [  3:  0](R/W) Select which address comparators are in use with ViewInst start-stop control,
                                                                   for the purpose of starting trace.
                                                                 0 = The single address comparator[m] is not
                                                                      selected as a start resource.
                                                                 1 = The single address comparator[m] is
                                                                      selected as a start resource. */
        uint32_t reserved_4_15         : 12;
        uint32_t stop                  : 4;  /**< [ 19: 16](R/W) Select which address comparators are in use with ViewInst start-stop control,
                                                                   for the purpose of stopping trace.
                                                                 0 = The single address comparator[m-16] is not
                                                                      selected as a stop resource.
                                                                 1 = The single address comparator[m-16] is
                                                                      selected as a stop resource. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcvissctlr_s cn9; */
};
typedef union bdk_trcx_trcvissctlr bdk_trcx_trcvissctlr_t;

static inline uint64_t BDK_TRCX_TRCVISSCTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVISSCTLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30088ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030088ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030088ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030088ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030088ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVISSCTLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVISSCTLR(a) bdk_trcx_trcvissctlr_t
#define bustype_BDK_TRCX_TRCVISSCTLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCVISSCTLR(a) "TRCX_TRCVISSCTLR"
#define busnum_BDK_TRCX_TRCVISSCTLR(a) (a)
#define arguments_BDK_TRCX_TRCVISSCTLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcvmidcctlr0
 *
 * TRC/ETM VMID Comparator Control Register 0
 * This register contains the virtual machine identifier mask values for the TRCVMIDCVRn
 * registers, where n=4-7.
 */
union bdk_trcx_trcvmidcctlr0
{
    uint32_t u;
    struct bdk_trcx_trcvmidcctlr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t comp3                 : 8;  /**< [ 31: 24](RAZ) Reserved. */
        uint32_t comp2                 : 8;  /**< [ 23: 16](RAZ) Reserved. */
        uint32_t comp1                 : 8;  /**< [ 15:  8](RAZ) Reserved. */
        uint32_t comp0                 : 8;  /**< [  7:  0](R/W) Controls the mask value that the trace unit applies to TRCVMIDCVRn, where
                                                                 n=0. Each bit in this field corresponds to a byte in TRCVMIDCVR0. When a bit is:
                                                                   0 = The trace unit includes the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the Context ID comparison.
                                                                   1 = The trace unit ignores the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the Context ID comparison. */
#else /* Word 0 - Little Endian */
        uint32_t comp0                 : 8;  /**< [  7:  0](R/W) Controls the mask value that the trace unit applies to TRCVMIDCVRn, where
                                                                 n=0. Each bit in this field corresponds to a byte in TRCVMIDCVR0. When a bit is:
                                                                   0 = The trace unit includes the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the Context ID comparison.
                                                                   1 = The trace unit ignores the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the Context ID comparison. */
        uint32_t comp1                 : 8;  /**< [ 15:  8](RAZ) Reserved. */
        uint32_t comp2                 : 8;  /**< [ 23: 16](RAZ) Reserved. */
        uint32_t comp3                 : 8;  /**< [ 31: 24](RAZ) Reserved. */
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcvmidcctlr0_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t comp0                 : 4;  /**< [  3:  0](R/W) Controls the mask value that the trace unit applies to TRCVMIDCVRn, where
                                                                 n=0. Each bit in this field corresponds to a byte in TRCVMIDCVR0. When a bit is:
                                                                   0 = The trace unit includes the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the Context ID comparison.
                                                                   1 = The trace unit ignores the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the Context ID comparison. */
#else /* Word 0 - Little Endian */
        uint32_t comp0                 : 4;  /**< [  3:  0](R/W) Controls the mask value that the trace unit applies to TRCVMIDCVRn, where
                                                                 n=0. Each bit in this field corresponds to a byte in TRCVMIDCVR0. When a bit is:
                                                                   0 = The trace unit includes the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the Context ID comparison.
                                                                   1 = The trace unit ignores the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the Context ID comparison. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_trcx_trcvmidcctlr0_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_trcx_trcvmidcctlr0_cn8 cn83xx; */
    struct bdk_trcx_trcvmidcctlr0_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t comp3                 : 8;  /**< [ 31: 24](RAZ) Reserved. */
        uint32_t comp2                 : 8;  /**< [ 23: 16](RAZ) Reserved. */
        uint32_t comp1                 : 8;  /**< [ 15:  8](RAZ) Reserved. */
        uint32_t comp0                 : 8;  /**< [  7:  0](R/W) Controls the mask value that the trace unit applies to TRCVMIDCVRn, where
                                                                 n=0. Each bit in this field corresponds to a byte in TRCVMIDCVR0. When a bit is:
                                                                   0 = The trace unit includes the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the context ID comparison.
                                                                   1 = The trace unit ignores the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the context ID comparison.
                                                                   bit[7:4] = 0x0. */
#else /* Word 0 - Little Endian */
        uint32_t comp0                 : 8;  /**< [  7:  0](R/W) Controls the mask value that the trace unit applies to TRCVMIDCVRn, where
                                                                 n=0. Each bit in this field corresponds to a byte in TRCVMIDCVR0. When a bit is:
                                                                   0 = The trace unit includes the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the context ID comparison.
                                                                   1 = The trace unit ignores the relevant byte in TRCVMIDCVR0 when it performs
                                                                       the context ID comparison.
                                                                   bit[7:4] = 0x0. */
        uint32_t comp1                 : 8;  /**< [ 15:  8](RAZ) Reserved. */
        uint32_t comp2                 : 8;  /**< [ 23: 16](RAZ) Reserved. */
        uint32_t comp3                 : 8;  /**< [ 31: 24](RAZ) Reserved. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_trcx_trcvmidcctlr0 bdk_trcx_trcvmidcctlr0_t;

static inline uint64_t BDK_TRCX_TRCVMIDCCTLR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVMIDCCTLR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30688ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030688ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030688ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030688ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030688ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVMIDCCTLR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVMIDCCTLR0(a) bdk_trcx_trcvmidcctlr0_t
#define bustype_BDK_TRCX_TRCVMIDCCTLR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCVMIDCCTLR0(a) "TRCX_TRCVMIDCCTLR0"
#define busnum_BDK_TRCX_TRCVMIDCCTLR0(a) (a)
#define arguments_BDK_TRCX_TRCVMIDCCTLR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) trc#_trcvmidcctlr1
 *
 * TRC/ETM VMID Comparator Control Register 1
 * This register contains the virtual machine identifier mask values for the TRCVMIDCVRn
 * registers, where n=4-7.
 */
union bdk_trcx_trcvmidcctlr1
{
    uint32_t u;
    struct bdk_trcx_trcvmidcctlr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_trcx_trcvmidcctlr1_s cn; */
};
typedef union bdk_trcx_trcvmidcctlr1 bdk_trcx_trcvmidcctlr1_t;

static inline uint64_t BDK_TRCX_TRCVMIDCCTLR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVMIDCCTLR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc3068cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVMIDCCTLR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVMIDCCTLR1(a) bdk_trcx_trcvmidcctlr1_t
#define bustype_BDK_TRCX_TRCVMIDCCTLR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_TRCX_TRCVMIDCCTLR1(a) "TRCX_TRCVMIDCCTLR1"
#define busnum_BDK_TRCX_TRCVMIDCCTLR1(a) (a)
#define arguments_BDK_TRCX_TRCVMIDCCTLR1(a) (a),-1,-1,-1

/**
 * Register (DAB) trc#_trcvmidcvr0
 *
 * TRC/ETM VMID Comparator Value Register
 * Contains a Virtual Context identifier value.
 */
union bdk_trcx_trcvmidcvr0
{
    uint64_t u;
    struct bdk_trcx_trcvmidcvr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t value                 : 32; /**< [ 31:  0](R/W) Virtual context identifier value. The implemented width of this field is
                                                                 implementation-defined, and is set by TRCIDR2.VMIDSIZE. */
#else /* Word 0 - Little Endian */
        uint64_t value                 : 32; /**< [ 31:  0](R/W) Virtual context identifier value. The implemented width of this field is
                                                                 implementation-defined, and is set by TRCIDR2.VMIDSIZE. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    struct bdk_trcx_trcvmidcvr0_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_trcx_trcvmidcvr0_s cn9; */
};
typedef union bdk_trcx_trcvmidcvr0 bdk_trcx_trcvmidcvr0_t;

static inline uint64_t BDK_TRCX_TRCVMIDCVR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TRCX_TRCVMIDCVR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=7))
        return 0x87a00fc30640ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008030640ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008030640ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008030640ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008030640ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("TRCX_TRCVMIDCVR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TRCX_TRCVMIDCVR0(a) bdk_trcx_trcvmidcvr0_t
#define bustype_BDK_TRCX_TRCVMIDCVR0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_TRCX_TRCVMIDCVR0(a) "TRCX_TRCVMIDCVR0"
#define busnum_BDK_TRCX_TRCVMIDCVR0(a) (a)
#define arguments_BDK_TRCX_TRCVMIDCVR0(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_DAB_TRC_H__ */
