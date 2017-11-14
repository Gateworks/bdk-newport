#ifndef __BDK_CSRS_L2C_MCI_H__
#define __BDK_CSRS_L2C_MCI_H__
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
 * Cavium L2C_MCI.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration l2c_mci_bar_e
 *
 * L2C MCI Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_L2C_MCI_BAR_E_L2C_MCIX_PF_BAR0(a) (0x87e05c000000ll + 0x1000000ll * (a))
#define BDK_L2C_MCI_BAR_E_L2C_MCIX_PF_BAR0_SIZE 0x800000ull
#define BDK_L2C_MCI_BAR_E_L2C_MCIX_PF_BAR4(a) (0x87e05cf00000ll + 0x1000000ll * (a))
#define BDK_L2C_MCI_BAR_E_L2C_MCIX_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration l2c_mci_int_vec_e
 *
 * L2C MCI MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_L2C_MCI_INT_VEC_E_INTS (0)

/**
 * Register (RSL) l2c_mci#_int_ena_w1c
 *
 * L2C MCI Interrupt Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_l2c_mcix_int_ena_w1c
{
    uint64_t u;
    struct bdk_l2c_mcix_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for L2C_MCI(0..3)_INT_W1C[VBFDBE]. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for L2C_MCI(0..3)_INT_W1C[VBFSBE]. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for L2C_MCI(0..3)_INT_W1C[VBFSBE]. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for L2C_MCI(0..3)_INT_W1C[VBFDBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    struct bdk_l2c_mcix_int_ena_w1c_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for L2C_MCI(0)_INT_W1C[VBFDBE]. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for L2C_MCI(0)_INT_W1C[VBFSBE]. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for L2C_MCI(0)_INT_W1C[VBFSBE]. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for L2C_MCI(0)_INT_W1C[VBFDBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_l2c_mcix_int_ena_w1c_s cn88xx; */
    struct bdk_l2c_mcix_int_ena_w1c_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for L2C_MCI(0..2)_INT_W1C[VBFDBE]. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for L2C_MCI(0..2)_INT_W1C[VBFSBE]. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for L2C_MCI(0..2)_INT_W1C[VBFSBE]. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for L2C_MCI(0..2)_INT_W1C[VBFDBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_l2c_mcix_int_ena_w1c bdk_l2c_mcix_int_ena_w1c_t;

static inline uint64_t BDK_L2C_MCIX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_L2C_MCIX_INT_ENA_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e05c000020ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=2))
        return 0x87e05c000020ll + 0x1000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x87e05c000020ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("L2C_MCIX_INT_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_L2C_MCIX_INT_ENA_W1C(a) bdk_l2c_mcix_int_ena_w1c_t
#define bustype_BDK_L2C_MCIX_INT_ENA_W1C(a) BDK_CSR_TYPE_RSL
#define basename_BDK_L2C_MCIX_INT_ENA_W1C(a) "L2C_MCIX_INT_ENA_W1C"
#define device_bar_BDK_L2C_MCIX_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_L2C_MCIX_INT_ENA_W1C(a) (a)
#define arguments_BDK_L2C_MCIX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RSL) l2c_mci#_int_ena_w1s
 *
 * L2C MCI Interrupt Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_l2c_mcix_int_ena_w1s
{
    uint64_t u;
    struct bdk_l2c_mcix_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for L2C_MCI(0..3)_INT_W1C[VBFDBE]. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for L2C_MCI(0..3)_INT_W1C[VBFSBE]. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for L2C_MCI(0..3)_INT_W1C[VBFSBE]. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for L2C_MCI(0..3)_INT_W1C[VBFDBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    struct bdk_l2c_mcix_int_ena_w1s_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for L2C_MCI(0)_INT_W1C[VBFDBE]. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for L2C_MCI(0)_INT_W1C[VBFSBE]. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for L2C_MCI(0)_INT_W1C[VBFSBE]. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for L2C_MCI(0)_INT_W1C[VBFDBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_l2c_mcix_int_ena_w1s_s cn88xx; */
    struct bdk_l2c_mcix_int_ena_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for L2C_MCI(0..2)_INT_W1C[VBFDBE]. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for L2C_MCI(0..2)_INT_W1C[VBFSBE]. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for L2C_MCI(0..2)_INT_W1C[VBFSBE]. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for L2C_MCI(0..2)_INT_W1C[VBFDBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_l2c_mcix_int_ena_w1s bdk_l2c_mcix_int_ena_w1s_t;

static inline uint64_t BDK_L2C_MCIX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_L2C_MCIX_INT_ENA_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e05c000028ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=2))
        return 0x87e05c000028ll + 0x1000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x87e05c000028ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("L2C_MCIX_INT_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_L2C_MCIX_INT_ENA_W1S(a) bdk_l2c_mcix_int_ena_w1s_t
#define bustype_BDK_L2C_MCIX_INT_ENA_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_L2C_MCIX_INT_ENA_W1S(a) "L2C_MCIX_INT_ENA_W1S"
#define device_bar_BDK_L2C_MCIX_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_L2C_MCIX_INT_ENA_W1S(a) (a)
#define arguments_BDK_L2C_MCIX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) l2c_mci#_int_w1c
 *
 * L2C MCI Interrupt Registers
 * This register is for MCI-based interrupts.
 */
union bdk_l2c_mcix_int_w1c
{
    uint64_t u;
    struct bdk_l2c_mcix_int_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1C/H) VBF double-bit error occurred. See L2C_MCI()_ERR for logged information.
                                                                 An indication of a hardware failure and may be considered fatal. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1C/H) VBF single-bit error occurred. See L2C_MCI()_ERR for logged information.
                                                                 Hardware corrected the failure. Software may choose to count these single-bit errors. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1C/H) VBF single-bit error occurred. See L2C_MCI()_ERR for logged information.
                                                                 Hardware corrected the failure. Software may choose to count these single-bit errors. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1C/H) VBF double-bit error occurred. See L2C_MCI()_ERR for logged information.
                                                                 An indication of a hardware failure and may be considered fatal. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_l2c_mcix_int_w1c_s cn; */
};
typedef union bdk_l2c_mcix_int_w1c bdk_l2c_mcix_int_w1c_t;

static inline uint64_t BDK_L2C_MCIX_INT_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_L2C_MCIX_INT_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e05c000000ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=2))
        return 0x87e05c000000ll + 0x1000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x87e05c000000ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("L2C_MCIX_INT_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_L2C_MCIX_INT_W1C(a) bdk_l2c_mcix_int_w1c_t
#define bustype_BDK_L2C_MCIX_INT_W1C(a) BDK_CSR_TYPE_RSL
#define basename_BDK_L2C_MCIX_INT_W1C(a) "L2C_MCIX_INT_W1C"
#define device_bar_BDK_L2C_MCIX_INT_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_L2C_MCIX_INT_W1C(a) (a)
#define arguments_BDK_L2C_MCIX_INT_W1C(a) (a),-1,-1,-1

/**
 * Register (RSL) l2c_mci#_int_w1s
 *
 * L2C MCI Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_l2c_mcix_int_w1s
{
    uint64_t u;
    struct bdk_l2c_mcix_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets L2C_MCI(0..3)_INT_W1C[VBFDBE]. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets L2C_MCI(0..3)_INT_W1C[VBFSBE]. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets L2C_MCI(0..3)_INT_W1C[VBFSBE]. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets L2C_MCI(0..3)_INT_W1C[VBFDBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    struct bdk_l2c_mcix_int_w1s_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets L2C_MCI(0)_INT_W1C[VBFDBE]. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets L2C_MCI(0)_INT_W1C[VBFSBE]. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets L2C_MCI(0)_INT_W1C[VBFSBE]. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets L2C_MCI(0)_INT_W1C[VBFDBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_l2c_mcix_int_w1s_s cn88xx; */
    struct bdk_l2c_mcix_int_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets L2C_MCI(0..2)_INT_W1C[VBFDBE]. */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets L2C_MCI(0..2)_INT_W1C[VBFSBE]. */
#else /* Word 0 - Little Endian */
        uint64_t vbfsbe                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets L2C_MCI(0..2)_INT_W1C[VBFSBE]. */
        uint64_t vbfdbe                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets L2C_MCI(0..2)_INT_W1C[VBFDBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_l2c_mcix_int_w1s bdk_l2c_mcix_int_w1s_t;

static inline uint64_t BDK_L2C_MCIX_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_L2C_MCIX_INT_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e05c000008ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=2))
        return 0x87e05c000008ll + 0x1000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x87e05c000008ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("L2C_MCIX_INT_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_L2C_MCIX_INT_W1S(a) bdk_l2c_mcix_int_w1s_t
#define bustype_BDK_L2C_MCIX_INT_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_L2C_MCIX_INT_W1S(a) "L2C_MCIX_INT_W1S"
#define device_bar_BDK_L2C_MCIX_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_L2C_MCIX_INT_W1S(a) (a)
#define arguments_BDK_L2C_MCIX_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) l2c_mci#_msix_pba#
 *
 * L2C MCI MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the L2C_MCI_INT_VEC_E
 * enumeration.
 */
union bdk_l2c_mcix_msix_pbax
{
    uint64_t u;
    struct bdk_l2c_mcix_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO) Pending message for the associated L2C_MCI()_MSIX_VEC()_CTL, enumerated by
                                                                 L2C_MCI_INT_VEC_E. Bits that have no associated L2C_MCI_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO) Pending message for the associated L2C_MCI()_MSIX_VEC()_CTL, enumerated by
                                                                 L2C_MCI_INT_VEC_E. Bits that have no associated L2C_MCI_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_l2c_mcix_msix_pbax_s cn; */
};
typedef union bdk_l2c_mcix_msix_pbax bdk_l2c_mcix_msix_pbax_t;

static inline uint64_t BDK_L2C_MCIX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_L2C_MCIX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b==0)))
        return 0x87e05cff0000ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=2) && (b==0)))
        return 0x87e05cff0000ll + 0x1000000ll * ((a) & 0x3) + 8ll * ((b) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b==0)))
        return 0x87e05cff0000ll + 0x1000000ll * ((a) & 0x3) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("L2C_MCIX_MSIX_PBAX", 2, a, b, 0, 0);
}

#define typedef_BDK_L2C_MCIX_MSIX_PBAX(a,b) bdk_l2c_mcix_msix_pbax_t
#define bustype_BDK_L2C_MCIX_MSIX_PBAX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_L2C_MCIX_MSIX_PBAX(a,b) "L2C_MCIX_MSIX_PBAX"
#define device_bar_BDK_L2C_MCIX_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_L2C_MCIX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_L2C_MCIX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) l2c_mci#_msix_vec#_addr
 *
 * L2C MCI MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the L2C_MCI_INT_VEC_E enumeration.
 */
union bdk_l2c_mcix_msix_vecx_addr
{
    uint64_t u;
    struct bdk_l2c_mcix_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's L2C_MCI()_MSIX_VEC()_ADDR, L2C_MCI()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of L2C_MCI()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_L2C_MCI_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's L2C_MCI()_MSIX_VEC()_ADDR, L2C_MCI()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of L2C_MCI()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_L2C_MCI_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_l2c_mcix_msix_vecx_addr_s cn; */
};
typedef union bdk_l2c_mcix_msix_vecx_addr bdk_l2c_mcix_msix_vecx_addr_t;

static inline uint64_t BDK_L2C_MCIX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_L2C_MCIX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b==0)))
        return 0x87e05cf00000ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=2) && (b==0)))
        return 0x87e05cf00000ll + 0x1000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b==0)))
        return 0x87e05cf00000ll + 0x1000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("L2C_MCIX_MSIX_VECX_ADDR", 2, a, b, 0, 0);
}

#define typedef_BDK_L2C_MCIX_MSIX_VECX_ADDR(a,b) bdk_l2c_mcix_msix_vecx_addr_t
#define bustype_BDK_L2C_MCIX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_L2C_MCIX_MSIX_VECX_ADDR(a,b) "L2C_MCIX_MSIX_VECX_ADDR"
#define device_bar_BDK_L2C_MCIX_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_L2C_MCIX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_L2C_MCIX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) l2c_mci#_msix_vec#_ctl
 *
 * L2C MCI MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the L2C_MCI_INT_VEC_E enumeration.
 */
union bdk_l2c_mcix_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_l2c_mcix_msix_vecx_ctl_s
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
    /* struct bdk_l2c_mcix_msix_vecx_ctl_s cn; */
};
typedef union bdk_l2c_mcix_msix_vecx_ctl bdk_l2c_mcix_msix_vecx_ctl_t;

static inline uint64_t BDK_L2C_MCIX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_L2C_MCIX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b==0)))
        return 0x87e05cf00008ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=2) && (b==0)))
        return 0x87e05cf00008ll + 0x1000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b==0)))
        return 0x87e05cf00008ll + 0x1000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("L2C_MCIX_MSIX_VECX_CTL", 2, a, b, 0, 0);
}

#define typedef_BDK_L2C_MCIX_MSIX_VECX_CTL(a,b) bdk_l2c_mcix_msix_vecx_ctl_t
#define bustype_BDK_L2C_MCIX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_L2C_MCIX_MSIX_VECX_CTL(a,b) "L2C_MCIX_MSIX_VECX_CTL"
#define device_bar_BDK_L2C_MCIX_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_L2C_MCIX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_L2C_MCIX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) l2c_mci#_scratch
 *
 * INTERNAL: L2C MCI General Purpose Scratch Register
 *
 * These registers are only reset by hardware during chip cold reset. The values of the CSR
 * fields in these registers do not change during chip warm or soft resets.
 */
union bdk_l2c_mcix_scratch
{
    uint64_t u;
    struct bdk_l2c_mcix_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_l2c_mcix_scratch_s cn; */
};
typedef union bdk_l2c_mcix_scratch bdk_l2c_mcix_scratch_t;

static inline uint64_t BDK_L2C_MCIX_SCRATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_L2C_MCIX_SCRATCH(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e05c030000ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=2))
        return 0x87e05c030000ll + 0x1000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x87e05c030000ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("L2C_MCIX_SCRATCH", 1, a, 0, 0, 0);
}

#define typedef_BDK_L2C_MCIX_SCRATCH(a) bdk_l2c_mcix_scratch_t
#define bustype_BDK_L2C_MCIX_SCRATCH(a) BDK_CSR_TYPE_RSL
#define basename_BDK_L2C_MCIX_SCRATCH(a) "L2C_MCIX_SCRATCH"
#define device_bar_BDK_L2C_MCIX_SCRATCH(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_L2C_MCIX_SCRATCH(a) (a)
#define arguments_BDK_L2C_MCIX_SCRATCH(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_L2C_MCI_H__ */
