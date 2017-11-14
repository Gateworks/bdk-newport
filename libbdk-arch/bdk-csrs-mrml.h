#ifndef __BDK_CSRS_MRML_H__
#define __BDK_CSRS_MRML_H__
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
 * Cavium MRML.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration mrml_bar_e
 *
 * MRML Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_MRML_BAR_E_MRML_PF_BAR0_CN8 (0x87e0fc000000ll)
#define BDK_MRML_BAR_E_MRML_PF_BAR0_CN8_SIZE 0x100000ull
#define BDK_MRML_BAR_E_MRML_PF_BAR0_CN9 (0x87e0fc000000ll)
#define BDK_MRML_BAR_E_MRML_PF_BAR0_CN9_SIZE 0x40000ull
#define BDK_MRML_BAR_E_MRML_PF_BAR4 (0x87e0fcf00000ll)
#define BDK_MRML_BAR_E_MRML_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration mrml_int_vec_e
 *
 * MRML MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_MRML_INT_VEC_E_INTS (0)

/**
 * Register (RSL) mrml_config
 *
 * MRML Configuration Register
 */
union bdk_mrml_config
{
    uint64_t u;
    struct bdk_mrml_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t disable_cseen         : 1;  /**< [  1:  1](SR/W) Disable MRML waiting for command seen. For diagnostic use only. */
        uint64_t force_clk_en          : 1;  /**< [  0:  0](SR/W) Force the conditional clocks to be always enabled. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t force_clk_en          : 1;  /**< [  0:  0](SR/W) Force the conditional clocks to be always enabled. For diagnostic use only. */
        uint64_t disable_cseen         : 1;  /**< [  1:  1](SR/W) Disable MRML waiting for command seen. For diagnostic use only. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_config_s cn; */
};
typedef union bdk_mrml_config bdk_mrml_config_t;

#define BDK_MRML_CONFIG BDK_MRML_CONFIG_FUNC()
static inline uint64_t BDK_MRML_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_CONFIG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0fc002000ll;
    __bdk_csr_fatal("MRML_CONFIG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MRML_CONFIG bdk_mrml_config_t
#define bustype_BDK_MRML_CONFIG BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_CONFIG "MRML_CONFIG"
#define device_bar_BDK_MRML_CONFIG 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_CONFIG 0
#define arguments_BDK_MRML_CONFIG -1,-1,-1,-1

/**
 * Register (RSL) mrml_int_ena_w1c
 *
 * MRML Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_mrml_int_ena_w1c
{
    uint64_t u;
    struct bdk_mrml_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1C/H) Reads or clears enable for MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1C/H) Reads or clears enable for MRML_INT_SUM[OCX_TOE]. */
#else /* Word 0 - Little Endian */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1C/H) Reads or clears enable for MRML_INT_SUM[OCX_TOE]. */
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1C/H) Reads or clears enable for MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_int_ena_w1c_s cn8; */
    struct bdk_mrml_int_ena_w1c_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1C/H) Reads or clears enable for MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1C/H) Reads or clears enable for MRML_INT_SUM[OCX_TOE].
                                                                 Internal:
                                                                 OCX timeout error. When set, an OCX timeout error has occurred. */
#else /* Word 0 - Little Endian */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1C/H) Reads or clears enable for MRML_INT_SUM[OCX_TOE].
                                                                 Internal:
                                                                 OCX timeout error. When set, an OCX timeout error has occurred. */
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1C/H) Reads or clears enable for MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_mrml_int_ena_w1c bdk_mrml_int_ena_w1c_t;

#define BDK_MRML_INT_ENA_W1C BDK_MRML_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_MRML_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_INT_ENA_W1C_FUNC(void)
{
    return 0x87e0fc000880ll;
}

#define typedef_BDK_MRML_INT_ENA_W1C bdk_mrml_int_ena_w1c_t
#define bustype_BDK_MRML_INT_ENA_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_INT_ENA_W1C "MRML_INT_ENA_W1C"
#define device_bar_BDK_MRML_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_INT_ENA_W1C 0
#define arguments_BDK_MRML_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RSL) mrml_int_ena_w1s
 *
 * MRML Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_mrml_int_ena_w1s
{
    uint64_t u;
    struct bdk_mrml_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets enable for MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets enable for MRML_INT_SUM[OCX_TOE]. */
#else /* Word 0 - Little Endian */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets enable for MRML_INT_SUM[OCX_TOE]. */
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets enable for MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_int_ena_w1s_s cn8; */
    struct bdk_mrml_int_ena_w1s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets enable for MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets enable for MRML_INT_SUM[OCX_TOE].
                                                                 Internal:
                                                                 OCX timeout error. When set, an OCX timeout error has occurred. */
#else /* Word 0 - Little Endian */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets enable for MRML_INT_SUM[OCX_TOE].
                                                                 Internal:
                                                                 OCX timeout error. When set, an OCX timeout error has occurred. */
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets enable for MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_mrml_int_ena_w1s bdk_mrml_int_ena_w1s_t;

#define BDK_MRML_INT_ENA_W1S BDK_MRML_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_MRML_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_INT_ENA_W1S_FUNC(void)
{
    return 0x87e0fc001000ll;
}

#define typedef_BDK_MRML_INT_ENA_W1S bdk_mrml_int_ena_w1s_t
#define bustype_BDK_MRML_INT_ENA_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_INT_ENA_W1S "MRML_INT_ENA_W1S"
#define device_bar_BDK_MRML_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_INT_ENA_W1S 0
#define arguments_BDK_MRML_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RSL) mrml_int_local_to
 *
 * MRML Local Node Timeout Register
 * Configures local node timeouts.
 */
union bdk_mrml_int_local_to
{
    uint64_t u;
    struct bdk_mrml_int_local_to_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t tovalue               : 32; /**< [ 31:  0](SR/W) Local timeout value, in coprocessor clocks. */
#else /* Word 0 - Little Endian */
        uint64_t tovalue               : 32; /**< [ 31:  0](SR/W) Local timeout value, in coprocessor clocks. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_int_local_to_s cn8; */
    struct bdk_mrml_int_local_to_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t tovalue               : 32; /**< [ 31:  0](SR/W) Local timeout value, in coprocessor clocks. A value of zero disables the timeout.
                                                                 If nonzero, this timeout must be less than the timeout represented in
                                                                 IOBN()_NCBO_TO[SUB_TIME]. */
#else /* Word 0 - Little Endian */
        uint64_t tovalue               : 32; /**< [ 31:  0](SR/W) Local timeout value, in coprocessor clocks. A value of zero disables the timeout.
                                                                 If nonzero, this timeout must be less than the timeout represented in
                                                                 IOBN()_NCBO_TO[SUB_TIME]. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_mrml_int_local_to bdk_mrml_int_local_to_t;

#define BDK_MRML_INT_LOCAL_TO BDK_MRML_INT_LOCAL_TO_FUNC()
static inline uint64_t BDK_MRML_INT_LOCAL_TO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_INT_LOCAL_TO_FUNC(void)
{
    return 0x87e0fc000800ll;
}

#define typedef_BDK_MRML_INT_LOCAL_TO bdk_mrml_int_local_to_t
#define bustype_BDK_MRML_INT_LOCAL_TO BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_INT_LOCAL_TO "MRML_INT_LOCAL_TO"
#define device_bar_BDK_MRML_INT_LOCAL_TO 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_INT_LOCAL_TO 0
#define arguments_BDK_MRML_INT_LOCAL_TO -1,-1,-1,-1

/**
 * Register (RSL) mrml_int_ocx_to
 *
 * INTERNAL: MRML OCX Timeout Register
 *
 * Configures remote node timeouts.
 */
union bdk_mrml_int_ocx_to
{
    uint64_t u;
    struct bdk_mrml_int_ocx_to_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t tovalue               : 32; /**< [ 31:  0](SR/W) OCX timeout value, in coprocessor clocks. */
#else /* Word 0 - Little Endian */
        uint64_t tovalue               : 32; /**< [ 31:  0](SR/W) OCX timeout value, in coprocessor clocks. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_int_ocx_to_s cn8; */
    struct bdk_mrml_int_ocx_to_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t tovalue               : 32; /**< [ 31:  0](SR/W) OCX timeout value, in coprocessor clocks. A value of zero disables the timeout.
                                                                 If nonzero, this timeout must be at least double MRML_INT_LOCAL_TO.
                                                                 Ignored in non-CCPI systems. */
#else /* Word 0 - Little Endian */
        uint64_t tovalue               : 32; /**< [ 31:  0](SR/W) OCX timeout value, in coprocessor clocks. A value of zero disables the timeout.
                                                                 If nonzero, this timeout must be at least double MRML_INT_LOCAL_TO.
                                                                 Ignored in non-CCPI systems. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_mrml_int_ocx_to bdk_mrml_int_ocx_to_t;

#define BDK_MRML_INT_OCX_TO BDK_MRML_INT_OCX_TO_FUNC()
static inline uint64_t BDK_MRML_INT_OCX_TO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_INT_OCX_TO_FUNC(void)
{
    return 0x87e0fc000808ll;
}

#define typedef_BDK_MRML_INT_OCX_TO bdk_mrml_int_ocx_to_t
#define bustype_BDK_MRML_INT_OCX_TO BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_INT_OCX_TO "MRML_INT_OCX_TO"
#define device_bar_BDK_MRML_INT_OCX_TO 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_INT_OCX_TO 0
#define arguments_BDK_MRML_INT_OCX_TO -1,-1,-1,-1

/**
 * Register (RSL) mrml_int_sum
 *
 * MRML Interrupt Summary Register
 * This register contains the different interrupt summary bits of the MRML.
 */
union bdk_mrml_int_sum
{
    uint64_t u;
    struct bdk_mrml_int_sum_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1C/H) Local timeout error. When set, a local timeout error has occurred. */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1C/H) OCX timeout error. When set, an OCX timeout error has occurred. */
#else /* Word 0 - Little Endian */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1C/H) OCX timeout error. When set, an OCX timeout error has occurred. */
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1C/H) Local timeout error. When set, a local timeout error has occurred. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_int_sum_s cn8; */
    struct bdk_mrml_int_sum_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1C/H) Local timeout error. When set, a local timeout error has occurred. */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1C/H) Reserved.
                                                                 Internal:
                                                                 OCX timeout error. When set, an OCX timeout error has occurred. */
#else /* Word 0 - Little Endian */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1C/H) Reserved.
                                                                 Internal:
                                                                 OCX timeout error. When set, an OCX timeout error has occurred. */
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1C/H) Local timeout error. When set, a local timeout error has occurred. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_mrml_int_sum bdk_mrml_int_sum_t;

#define BDK_MRML_INT_SUM BDK_MRML_INT_SUM_FUNC()
static inline uint64_t BDK_MRML_INT_SUM_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_INT_SUM_FUNC(void)
{
    return 0x87e0fc000810ll;
}

#define typedef_BDK_MRML_INT_SUM bdk_mrml_int_sum_t
#define bustype_BDK_MRML_INT_SUM BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_INT_SUM "MRML_INT_SUM"
#define device_bar_BDK_MRML_INT_SUM 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_INT_SUM 0
#define arguments_BDK_MRML_INT_SUM -1,-1,-1,-1

/**
 * Register (RSL) mrml_int_sum_w1s
 *
 * MRML Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_mrml_int_sum_w1s
{
    uint64_t u;
    struct bdk_mrml_int_sum_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets MRML_INT_SUM[OCX_TOE]. */
#else /* Word 0 - Little Endian */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets MRML_INT_SUM[OCX_TOE]. */
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_int_sum_w1s_s cn8; */
    struct bdk_mrml_int_sum_w1s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets MRML_INT_SUM[OCX_TOE].
                                                                 Internal:
                                                                 OCX timeout error. When set, an OCX timeout error has occurred. */
#else /* Word 0 - Little Endian */
        uint64_t ocx_toe               : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets MRML_INT_SUM[OCX_TOE].
                                                                 Internal:
                                                                 OCX timeout error. When set, an OCX timeout error has occurred. */
        uint64_t local_toe             : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets MRML_INT_SUM[LOCAL_TOE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_mrml_int_sum_w1s bdk_mrml_int_sum_w1s_t;

#define BDK_MRML_INT_SUM_W1S BDK_MRML_INT_SUM_W1S_FUNC()
static inline uint64_t BDK_MRML_INT_SUM_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_INT_SUM_W1S_FUNC(void)
{
    return 0x87e0fc000818ll;
}

#define typedef_BDK_MRML_INT_SUM_W1S bdk_mrml_int_sum_w1s_t
#define bustype_BDK_MRML_INT_SUM_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_INT_SUM_W1S "MRML_INT_SUM_W1S"
#define device_bar_BDK_MRML_INT_SUM_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_INT_SUM_W1S 0
#define arguments_BDK_MRML_INT_SUM_W1S -1,-1,-1,-1

/**
 * Register (RSL) mrml_msix_pba#
 *
 * MRML MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the MRML_INT_VEC_E enumeration.
 */
union bdk_mrml_msix_pbax
{
    uint64_t u;
    struct bdk_mrml_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MRML_MSIX_VEC()_CTL, enumerated by MRML_INT_VEC_E.
                                                                 Bits that have no associated MRML_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MRML_MSIX_VEC()_CTL, enumerated by MRML_INT_VEC_E.
                                                                 Bits that have no associated MRML_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_msix_pbax_s cn; */
};
typedef union bdk_mrml_msix_pbax bdk_mrml_msix_pbax_t;

static inline uint64_t BDK_MRML_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_MSIX_PBAX(unsigned long a)
{
    if (a==0)
        return 0x87e0fcff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("MRML_MSIX_PBAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_MRML_MSIX_PBAX(a) bdk_mrml_msix_pbax_t
#define bustype_BDK_MRML_MSIX_PBAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_MSIX_PBAX(a) "MRML_MSIX_PBAX"
#define device_bar_BDK_MRML_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MRML_MSIX_PBAX(a) (a)
#define arguments_BDK_MRML_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (RSL) mrml_msix_vec#_addr
 *
 * MRML MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the MRML_INT_VEC_E enumeration.
 */
union bdk_mrml_msix_vecx_addr
{
    uint64_t u;
    struct bdk_mrml_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MRML_MSIX_VEC()_ADDR, MRML_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MRML_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MRML_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MRML_MSIX_VEC()_ADDR, MRML_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MRML_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MRML_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_mrml_msix_vecx_addr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MRML_MSIX_VEC()_ADDR, MRML_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MRML_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MRML_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MRML_MSIX_VEC()_ADDR, MRML_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MRML_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MRML_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC])
                                                                 is set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mrml_msix_vecx_addr_s cn9; */
};
typedef union bdk_mrml_msix_vecx_addr bdk_mrml_msix_vecx_addr_t;

static inline uint64_t BDK_MRML_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_MSIX_VECX_ADDR(unsigned long a)
{
    if (a==0)
        return 0x87e0fcf00000ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("MRML_MSIX_VECX_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_MRML_MSIX_VECX_ADDR(a) bdk_mrml_msix_vecx_addr_t
#define bustype_BDK_MRML_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_MSIX_VECX_ADDR(a) "MRML_MSIX_VECX_ADDR"
#define device_bar_BDK_MRML_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MRML_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_MRML_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) mrml_msix_vec#_ctl
 *
 * MRML MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the MRML_INT_VEC_E enumeration.
 */
union bdk_mrml_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_mrml_msix_vecx_ctl_s
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
    struct bdk_mrml_msix_vecx_ctl_cn8
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
    } cn8;
    /* struct bdk_mrml_msix_vecx_ctl_s cn9; */
};
typedef union bdk_mrml_msix_vecx_ctl bdk_mrml_msix_vecx_ctl_t;

static inline uint64_t BDK_MRML_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_MSIX_VECX_CTL(unsigned long a)
{
    if (a==0)
        return 0x87e0fcf00008ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("MRML_MSIX_VECX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_MRML_MSIX_VECX_CTL(a) bdk_mrml_msix_vecx_ctl_t
#define bustype_BDK_MRML_MSIX_VECX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_MSIX_VECX_CTL(a) "MRML_MSIX_VECX_CTL"
#define device_bar_BDK_MRML_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MRML_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_MRML_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) mrml_ncb#_permit
 *
 * MRML NCB Bus Permit Registers
 * This register sets the permissions for access to NCBDIDs address bits \<43:36\>.
 */
union bdk_mrml_ncbx_permit
{
    uint64_t u;
    struct bdk_mrml_ncbx_permit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t kill                  : 1;  /**< [  7:  7](SR/W1S) Kill the device. Once written with one, stays
                                                                 set until warm chip reset.  If set, no access
                                                                 allowed by any initiator. */
        uint64_t reserved_4_6          : 3;
        uint64_t xcp1_dis              : 1;  /**< [  3:  3](SR/W) XCP1 disable. As with [SEC_DIS], but for accesses initiated by XCP1 (MCP). */
        uint64_t xcp0_dis              : 1;  /**< [  2:  2](SR/W) XCP0 disable. As with [SEC_DIS], but for accesses initiated by XCP0 (SCP). */
        uint64_t nsec_dis              : 1;  /**< [  1:  1](SR/W) Nonsecure disable. As with [SEC_DIS], but for accesses initiated by non-secure devices
                                                                 excluding XCP0/XCP1. */
        uint64_t sec_dis               : 1;  /**< [  0:  0](SR/W) Secure disable. */
#else /* Word 0 - Little Endian */
        uint64_t sec_dis               : 1;  /**< [  0:  0](SR/W) Secure disable. */
        uint64_t nsec_dis              : 1;  /**< [  1:  1](SR/W) Nonsecure disable. As with [SEC_DIS], but for accesses initiated by non-secure devices
                                                                 excluding XCP0/XCP1. */
        uint64_t xcp0_dis              : 1;  /**< [  2:  2](SR/W) XCP0 disable. As with [SEC_DIS], but for accesses initiated by XCP0 (SCP). */
        uint64_t xcp1_dis              : 1;  /**< [  3:  3](SR/W) XCP1 disable. As with [SEC_DIS], but for accesses initiated by XCP1 (MCP). */
        uint64_t reserved_4_6          : 3;
        uint64_t kill                  : 1;  /**< [  7:  7](SR/W1S) Kill the device. Once written with one, stays
                                                                 set until warm chip reset.  If set, no access
                                                                 allowed by any initiator. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_ncbx_permit_s cn; */
};
typedef union bdk_mrml_ncbx_permit bdk_mrml_ncbx_permit_t;

static inline uint64_t BDK_MRML_NCBX_PERMIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_NCBX_PERMIT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=255))
        return 0x87e0fc020000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("MRML_NCBX_PERMIT", 1, a, 0, 0, 0);
}

#define typedef_BDK_MRML_NCBX_PERMIT(a) bdk_mrml_ncbx_permit_t
#define bustype_BDK_MRML_NCBX_PERMIT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_NCBX_PERMIT(a) "MRML_NCBX_PERMIT"
#define device_bar_BDK_MRML_NCBX_PERMIT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_NCBX_PERMIT(a) (a)
#define arguments_BDK_MRML_NCBX_PERMIT(a) (a),-1,-1,-1

/**
 * Register (RSL) mrml_ncb#_sdev
 *
 * MRML NCB Secure Device Registers
 */
union bdk_mrml_ncbx_sdev
{
    uint64_t u;
    struct bdk_mrml_ncbx_sdev_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sec                   : 64; /**< [ 63:  0](SR/W) NCB function secure.  Similar to MRML_RSL()_SDEV except applies to NCB devices.
                                                                 Should be programmed identically to IOBN()_NCB0_SDIS(). */
#else /* Word 0 - Little Endian */
        uint64_t sec                   : 64; /**< [ 63:  0](SR/W) NCB function secure.  Similar to MRML_RSL()_SDEV except applies to NCB devices.
                                                                 Should be programmed identically to IOBN()_NCB0_SDIS(). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_ncbx_sdev_s cn; */
};
typedef union bdk_mrml_ncbx_sdev bdk_mrml_ncbx_sdev_t;

static inline uint64_t BDK_MRML_NCBX_SDEV(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_NCBX_SDEV(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a<=3))
        return 0x87e0fc000400ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("MRML_NCBX_SDEV", 1, a, 0, 0, 0);
}

#define typedef_BDK_MRML_NCBX_SDEV(a) bdk_mrml_ncbx_sdev_t
#define bustype_BDK_MRML_NCBX_SDEV(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_NCBX_SDEV(a) "MRML_NCBX_SDEV"
#define device_bar_BDK_MRML_NCBX_SDEV(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_NCBX_SDEV(a) (a)
#define arguments_BDK_MRML_NCBX_SDEV(a) (a),-1,-1,-1

/**
 * Register (RSL) mrml_ncb#_skill
 *
 * MRML RSL Secure Kill-Device Registers
 */
union bdk_mrml_ncbx_skill
{
    uint64_t u;
    struct bdk_mrml_ncbx_skill_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t skill                 : 64; /**< [ 63:  0](SR/W1S) NCB function kill.  Similar to MRML_RSL()_SKILL except applies to NCB devices.
                                                                 Should be programmed identically to IOBN()_NCB0_SKILL(). */
#else /* Word 0 - Little Endian */
        uint64_t skill                 : 64; /**< [ 63:  0](SR/W1S) NCB function kill.  Similar to MRML_RSL()_SKILL except applies to NCB devices.
                                                                 Should be programmed identically to IOBN()_NCB0_SKILL(). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_ncbx_skill_s cn; */
};
typedef union bdk_mrml_ncbx_skill bdk_mrml_ncbx_skill_t;

static inline uint64_t BDK_MRML_NCBX_SKILL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_NCBX_SKILL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87e0fc000500ll + 8ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=3))
        return 0x87e0fc000500ll + 8ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x87e0fc000500ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("MRML_NCBX_SKILL", 1, a, 0, 0, 0);
}

#define typedef_BDK_MRML_NCBX_SKILL(a) bdk_mrml_ncbx_skill_t
#define bustype_BDK_MRML_NCBX_SKILL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_NCBX_SKILL(a) "MRML_NCBX_SKILL"
#define device_bar_BDK_MRML_NCBX_SKILL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_NCBX_SKILL(a) (a)
#define arguments_BDK_MRML_NCBX_SKILL(a) (a),-1,-1,-1

/**
 * Register (RSL) mrml_rsl#_permit
 *
 * MRML RSL Bus Permit Registers
 * This register sets the permissions for access to the device's physical address bits \<31:24\>.
 */
union bdk_mrml_rslx_permit
{
    uint64_t u;
    struct bdk_mrml_rslx_permit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t kill                  : 1;  /**< [  7:  7](SR/W1S) Kill the device. Once written with one, stays
                                                                 set until warm chip reset.  If set, no access
                                                                 allowed by any initiator. */
        uint64_t reserved_4_6          : 3;
        uint64_t xcp1_dis              : 1;  /**< [  3:  3](SR/W) XCP1 disable. As with [SEC_DIS], but for accesses initiated by XCP1 (MCP). */
        uint64_t xcp0_dis              : 1;  /**< [  2:  2](SR/W) XCP0 disable. As with [SEC_DIS], but for accesses initiated by XCP0 (SCP). */
        uint64_t nsec_dis              : 1;  /**< [  1:  1](SR/W) Nonsecure disable. As with [SEC_DIS], but for accesses initiated by non-secure devices
                                                                 excluding XCP0/XCP1. */
        uint64_t sec_dis               : 1;  /**< [  0:  0](SR/W) Secure disable. */
#else /* Word 0 - Little Endian */
        uint64_t sec_dis               : 1;  /**< [  0:  0](SR/W) Secure disable. */
        uint64_t nsec_dis              : 1;  /**< [  1:  1](SR/W) Nonsecure disable. As with [SEC_DIS], but for accesses initiated by non-secure devices
                                                                 excluding XCP0/XCP1. */
        uint64_t xcp0_dis              : 1;  /**< [  2:  2](SR/W) XCP0 disable. As with [SEC_DIS], but for accesses initiated by XCP0 (SCP). */
        uint64_t xcp1_dis              : 1;  /**< [  3:  3](SR/W) XCP1 disable. As with [SEC_DIS], but for accesses initiated by XCP1 (MCP). */
        uint64_t reserved_4_6          : 3;
        uint64_t kill                  : 1;  /**< [  7:  7](SR/W1S) Kill the device. Once written with one, stays
                                                                 set until warm chip reset.  If set, no access
                                                                 allowed by any initiator. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_rslx_permit_s cn; */
};
typedef union bdk_mrml_rslx_permit bdk_mrml_rslx_permit_t;

static inline uint64_t BDK_MRML_RSLX_PERMIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_RSLX_PERMIT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=255))
        return 0x87e0fc010000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("MRML_RSLX_PERMIT", 1, a, 0, 0, 0);
}

#define typedef_BDK_MRML_RSLX_PERMIT(a) bdk_mrml_rslx_permit_t
#define bustype_BDK_MRML_RSLX_PERMIT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_RSLX_PERMIT(a) "MRML_RSLX_PERMIT"
#define device_bar_BDK_MRML_RSLX_PERMIT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_RSLX_PERMIT(a) (a)
#define arguments_BDK_MRML_RSLX_PERMIT(a) (a),-1,-1,-1

/**
 * Register (RSL) mrml_rsl#_sdev
 *
 * MRML RSL Secure Device Registers
 */
union bdk_mrml_rslx_sdev
{
    uint64_t u;
    struct bdk_mrml_rslx_sdev_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sec                   : 64; /**< [ 63:  0](SR/W) RSL function secure. If set, the corresponding RSL device ID will be secure access
                                                                 only. Read/writes from nonsecure agents will be RAZ/WI.
                                                                 The register index 0..3 indicates which group of 64 functions, and bit index indicates
                                                                 which mod-64 function, for 256 function bits total.

                                                                 For compatibility with ARM secure boot at least the following RSL devices typically
                                                                 need to be marked secure: DAP, DTX, FUSF, IOBN, KEY, L2C, L2C_CBC, L2C_MCI,
                                                                 L2C_TAD, LMC, MIO_BOOT, MIO_FUS, MRML, OCLA, OCX, PCCBR_MRML, RST, SLI, VRM.
                                                                 It is recommended that as many devices be made secure as possible.

                                                                 RSL function number 0xFF, which is not present but used internally by MRML, must
                                                                 be marked secure. */
#else /* Word 0 - Little Endian */
        uint64_t sec                   : 64; /**< [ 63:  0](SR/W) RSL function secure. If set, the corresponding RSL device ID will be secure access
                                                                 only. Read/writes from nonsecure agents will be RAZ/WI.
                                                                 The register index 0..3 indicates which group of 64 functions, and bit index indicates
                                                                 which mod-64 function, for 256 function bits total.

                                                                 For compatibility with ARM secure boot at least the following RSL devices typically
                                                                 need to be marked secure: DAP, DTX, FUSF, IOBN, KEY, L2C, L2C_CBC, L2C_MCI,
                                                                 L2C_TAD, LMC, MIO_BOOT, MIO_FUS, MRML, OCLA, OCX, PCCBR_MRML, RST, SLI, VRM.
                                                                 It is recommended that as many devices be made secure as possible.

                                                                 RSL function number 0xFF, which is not present but used internally by MRML, must
                                                                 be marked secure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_rslx_sdev_s cn; */
};
typedef union bdk_mrml_rslx_sdev bdk_mrml_rslx_sdev_t;

static inline uint64_t BDK_MRML_RSLX_SDEV(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_RSLX_SDEV(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a<=3))
        return 0x87e0fc000200ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("MRML_RSLX_SDEV", 1, a, 0, 0, 0);
}

#define typedef_BDK_MRML_RSLX_SDEV(a) bdk_mrml_rslx_sdev_t
#define bustype_BDK_MRML_RSLX_SDEV(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_RSLX_SDEV(a) "MRML_RSLX_SDEV"
#define device_bar_BDK_MRML_RSLX_SDEV(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_RSLX_SDEV(a) (a)
#define arguments_BDK_MRML_RSLX_SDEV(a) (a),-1,-1,-1

/**
 * Register (RSL) mrml_rsl#_skill
 *
 * MRML RSL Secure Kill-Device Registers
 */
union bdk_mrml_rslx_skill
{
    uint64_t u;
    struct bdk_mrml_rslx_skill_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t skill                 : 64; /**< [ 63:  0](SR/W1S) RSL function kill. Write one to set, once set cannot be cleared
                                                                 until soft reset. If set, read/writes from any agent
                                                                 (secure/nonsecure) will be RAZ/WI.
                                                                 The register index 0..3 indicates which group of 64 functions, and bit index indicates
                                                                 which mod-64 function, for 256 function bits total. */
#else /* Word 0 - Little Endian */
        uint64_t skill                 : 64; /**< [ 63:  0](SR/W1S) RSL function kill. Write one to set, once set cannot be cleared
                                                                 until soft reset. If set, read/writes from any agent
                                                                 (secure/nonsecure) will be RAZ/WI.
                                                                 The register index 0..3 indicates which group of 64 functions, and bit index indicates
                                                                 which mod-64 function, for 256 function bits total. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_rslx_skill_s cn; */
};
typedef union bdk_mrml_rslx_skill bdk_mrml_rslx_skill_t;

static inline uint64_t BDK_MRML_RSLX_SKILL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_RSLX_SKILL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87e0fc000300ll + 8ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=3))
        return 0x87e0fc000300ll + 8ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x87e0fc000300ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("MRML_RSLX_SKILL", 1, a, 0, 0, 0);
}

#define typedef_BDK_MRML_RSLX_SKILL(a) bdk_mrml_rslx_skill_t
#define bustype_BDK_MRML_RSLX_SKILL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_RSLX_SKILL(a) "MRML_RSLX_SKILL"
#define device_bar_BDK_MRML_RSLX_SKILL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_RSLX_SKILL(a) (a)
#define arguments_BDK_MRML_RSLX_SKILL(a) (a),-1,-1,-1

/**
 * Register (RSL) mrml_scfg
 *
 * MRML RSL Secure Configuration Register
 */
union bdk_mrml_scfg
{
    uint64_t u;
    struct bdk_mrml_scfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mrml_scfg_s cn; */
};
typedef union bdk_mrml_scfg bdk_mrml_scfg_t;

#define BDK_MRML_SCFG BDK_MRML_SCFG_FUNC()
static inline uint64_t BDK_MRML_SCFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MRML_SCFG_FUNC(void)
{
    return 0x87e0fc000000ll;
}

#define typedef_BDK_MRML_SCFG bdk_mrml_scfg_t
#define bustype_BDK_MRML_SCFG BDK_CSR_TYPE_RSL
#define basename_BDK_MRML_SCFG "MRML_SCFG"
#define device_bar_BDK_MRML_SCFG 0x0 /* PF_BAR0 */
#define busnum_BDK_MRML_SCFG 0
#define arguments_BDK_MRML_SCFG -1,-1,-1,-1

#endif /* __BDK_CSRS_MRML_H__ */
