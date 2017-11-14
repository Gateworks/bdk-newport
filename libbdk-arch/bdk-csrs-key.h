#ifndef __BDK_CSRS_KEY_H__
#define __BDK_CSRS_KEY_H__
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
 * Cavium KEY.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration key_bar_e
 *
 * KEY Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_KEY_BAR_E_KEY_PF_BAR0 (0x87e041000000ll)
#define BDK_KEY_BAR_E_KEY_PF_BAR0_SIZE 0x800000ull
#define BDK_KEY_BAR_E_KEY_PF_BAR2 (0x841000400000ll)
#define BDK_KEY_BAR_E_KEY_PF_BAR2_SIZE 0x100000ull
#define BDK_KEY_BAR_E_KEY_PF_BAR4 (0x87e041f00000ll)
#define BDK_KEY_BAR_E_KEY_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration key_int_vec_e
 *
 * KEY MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_KEY_INT_VEC_E_INTS (0)

/**
 * Register (RSL) key_bist_reg
 *
 * KEY BIST Status Register
 * This register provides the BIST run status for KEY's memories (0 = pass, 1 = fail).
 */
union bdk_key_bist_reg
{
    uint64_t u;
    struct bdk_key_bist_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t rrc                   : 1;  /**< [  1:  1](SRO/H) Status of the KRC memory block BIST. 0 = passed BIST, 1 = failed BIST. */
        uint64_t kmem                  : 1;  /**< [  0:  0](SRO/H) Status of the MEM memory block BIST. 0 = passed BIST, 1 = failed BIST. */
#else /* Word 0 - Little Endian */
        uint64_t kmem                  : 1;  /**< [  0:  0](SRO/H) Status of the MEM memory block BIST. 0 = passed BIST, 1 = failed BIST. */
        uint64_t rrc                   : 1;  /**< [  1:  1](SRO/H) Status of the KRC memory block BIST. 0 = passed BIST, 1 = failed BIST. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_key_bist_reg_s cn; */
};
typedef union bdk_key_bist_reg bdk_key_bist_reg_t;

#define BDK_KEY_BIST_REG BDK_KEY_BIST_REG_FUNC()
static inline uint64_t BDK_KEY_BIST_REG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_BIST_REG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x87e041000018ll;
    __bdk_csr_fatal("KEY_BIST_REG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_KEY_BIST_REG bdk_key_bist_reg_t
#define bustype_BDK_KEY_BIST_REG BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_BIST_REG "KEY_BIST_REG"
#define device_bar_BDK_KEY_BIST_REG 0x0 /* PF_BAR0 */
#define busnum_BDK_KEY_BIST_REG 0
#define arguments_BDK_KEY_BIST_REG -1,-1,-1,-1

/**
 * Register (RSL) key_ctl_status
 *
 * KEY Control and Status Register
 * This register provides control and status information for KEY memory.
 */
union bdk_key_ctl_status
{
    uint64_t u;
    struct bdk_key_ctl_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t kmem_dcor             : 1;  /**< [  2:  2](SR/W) Disable ECC correction in KEY MEM. */
        uint64_t kmem_fs               : 2;  /**< [  1:  0](SR/W) Flip syndrome bits. On the next write operation, flip the syndrome bits written into KEY MEM. */
#else /* Word 0 - Little Endian */
        uint64_t kmem_fs               : 2;  /**< [  1:  0](SR/W) Flip syndrome bits. On the next write operation, flip the syndrome bits written into KEY MEM. */
        uint64_t kmem_dcor             : 1;  /**< [  2:  2](SR/W) Disable ECC correction in KEY MEM. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_key_ctl_status_s cn; */
};
typedef union bdk_key_ctl_status bdk_key_ctl_status_t;

#define BDK_KEY_CTL_STATUS BDK_KEY_CTL_STATUS_FUNC()
static inline uint64_t BDK_KEY_CTL_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_CTL_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x87e041000010ll;
    __bdk_csr_fatal("KEY_CTL_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_KEY_CTL_STATUS bdk_key_ctl_status_t
#define bustype_BDK_KEY_CTL_STATUS BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_CTL_STATUS "KEY_CTL_STATUS"
#define device_bar_BDK_KEY_CTL_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_KEY_CTL_STATUS 0
#define arguments_BDK_KEY_CTL_STATUS -1,-1,-1,-1

/**
 * Register (RSL) key_int_ena_w1c
 *
 * KEY Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_key_int_ena_w1c
{
    uint64_t u;
    struct bdk_key_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t ked0_dbe              : 1;  /**< [  1:  1](SR/W1C/H) Reads or clears enable for KEY_INT_SUM[KED0_DBE]. */
        uint64_t ked0_sbe              : 1;  /**< [  0:  0](SR/W1C/H) Reads or clears enable for KEY_INT_SUM[KED0_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ked0_sbe              : 1;  /**< [  0:  0](SR/W1C/H) Reads or clears enable for KEY_INT_SUM[KED0_SBE]. */
        uint64_t ked0_dbe              : 1;  /**< [  1:  1](SR/W1C/H) Reads or clears enable for KEY_INT_SUM[KED0_DBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_key_int_ena_w1c_s cn; */
};
typedef union bdk_key_int_ena_w1c bdk_key_int_ena_w1c_t;

#define BDK_KEY_INT_ENA_W1C BDK_KEY_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_KEY_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_INT_ENA_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x87e041000120ll;
    __bdk_csr_fatal("KEY_INT_ENA_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_KEY_INT_ENA_W1C bdk_key_int_ena_w1c_t
#define bustype_BDK_KEY_INT_ENA_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_INT_ENA_W1C "KEY_INT_ENA_W1C"
#define device_bar_BDK_KEY_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_KEY_INT_ENA_W1C 0
#define arguments_BDK_KEY_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RSL) key_int_ena_w1s
 *
 * KEY Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_key_int_ena_w1s
{
    uint64_t u;
    struct bdk_key_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t ked0_dbe              : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets enable for KEY_INT_SUM[KED0_DBE]. */
        uint64_t ked0_sbe              : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets enable for KEY_INT_SUM[KED0_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ked0_sbe              : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets enable for KEY_INT_SUM[KED0_SBE]. */
        uint64_t ked0_dbe              : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets enable for KEY_INT_SUM[KED0_DBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_key_int_ena_w1s_s cn; */
};
typedef union bdk_key_int_ena_w1s bdk_key_int_ena_w1s_t;

#define BDK_KEY_INT_ENA_W1S BDK_KEY_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_KEY_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_INT_ENA_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x87e041000128ll;
    __bdk_csr_fatal("KEY_INT_ENA_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_KEY_INT_ENA_W1S bdk_key_int_ena_w1s_t
#define bustype_BDK_KEY_INT_ENA_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_INT_ENA_W1S "KEY_INT_ENA_W1S"
#define device_bar_BDK_KEY_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_KEY_INT_ENA_W1S 0
#define arguments_BDK_KEY_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RSL) key_int_sum
 *
 * KEY Interrupt Summary Register
 * This register contains the different interrupt-summary bits of the KEY.
 */
union bdk_key_int_sum
{
    uint64_t u;
    struct bdk_key_int_sum_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t ked0_dbe              : 1;  /**< [  1:  1](SR/W1C/H) KED0 double-bit error. When set, a KED0 double-bit error has occurred. */
        uint64_t ked0_sbe              : 1;  /**< [  0:  0](SR/W1C/H) KED0 single-bit error. When set, a KED0 single-bit error has occurred. */
#else /* Word 0 - Little Endian */
        uint64_t ked0_sbe              : 1;  /**< [  0:  0](SR/W1C/H) KED0 single-bit error. When set, a KED0 single-bit error has occurred. */
        uint64_t ked0_dbe              : 1;  /**< [  1:  1](SR/W1C/H) KED0 double-bit error. When set, a KED0 double-bit error has occurred. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_key_int_sum_s cn; */
};
typedef union bdk_key_int_sum bdk_key_int_sum_t;

#define BDK_KEY_INT_SUM BDK_KEY_INT_SUM_FUNC()
static inline uint64_t BDK_KEY_INT_SUM_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_INT_SUM_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x87e041000100ll;
    __bdk_csr_fatal("KEY_INT_SUM", 0, 0, 0, 0, 0);
}

#define typedef_BDK_KEY_INT_SUM bdk_key_int_sum_t
#define bustype_BDK_KEY_INT_SUM BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_INT_SUM "KEY_INT_SUM"
#define device_bar_BDK_KEY_INT_SUM 0x0 /* PF_BAR0 */
#define busnum_BDK_KEY_INT_SUM 0
#define arguments_BDK_KEY_INT_SUM -1,-1,-1,-1

/**
 * Register (RSL) key_int_sum_w1s
 *
 * KEY Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_key_int_sum_w1s
{
    uint64_t u;
    struct bdk_key_int_sum_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t ked0_dbe              : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets KEY_INT_SUM[KED0_DBE]. */
        uint64_t ked0_sbe              : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets KEY_INT_SUM[KED0_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ked0_sbe              : 1;  /**< [  0:  0](SR/W1S/H) Reads or sets KEY_INT_SUM[KED0_SBE]. */
        uint64_t ked0_dbe              : 1;  /**< [  1:  1](SR/W1S/H) Reads or sets KEY_INT_SUM[KED0_DBE]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_key_int_sum_w1s_s cn; */
};
typedef union bdk_key_int_sum_w1s bdk_key_int_sum_w1s_t;

#define BDK_KEY_INT_SUM_W1S BDK_KEY_INT_SUM_W1S_FUNC()
static inline uint64_t BDK_KEY_INT_SUM_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_INT_SUM_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x87e041000108ll;
    __bdk_csr_fatal("KEY_INT_SUM_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_KEY_INT_SUM_W1S bdk_key_int_sum_w1s_t
#define bustype_BDK_KEY_INT_SUM_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_INT_SUM_W1S "KEY_INT_SUM_W1S"
#define device_bar_BDK_KEY_INT_SUM_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_KEY_INT_SUM_W1S 0
#define arguments_BDK_KEY_INT_SUM_W1S -1,-1,-1,-1

/**
 * Register (NCB) key_mem#
 *
 * KEY Memory Registers
 */
union bdk_key_memx
{
    uint64_t u;
    struct bdk_key_memx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t kmem                  : 64; /**< [ 63:  0](SR/W) Key memory. KMEM is accessible using 8-, 16-, 32-, or 64-bit load or store operations.
                                                                 Internal:
                                                                 This was accessible only on NCB in pass 1 but both NCB and RSL in pass 2 */
#else /* Word 0 - Little Endian */
        uint64_t kmem                  : 64; /**< [ 63:  0](SR/W) Key memory. KMEM is accessible using 8-, 16-, 32-, or 64-bit load or store operations.
                                                                 Internal:
                                                                 This was accessible only on NCB in pass 1 but both NCB and RSL in pass 2 */
#endif /* Word 0 - End */
    } s;
    struct bdk_key_memx_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t kmem                  : 64; /**< [ 63:  0](SR/W) Key memory. KMEM is accessible using 8-, 16-, 32-, or 64-bit load or store operations. */
#else /* Word 0 - Little Endian */
        uint64_t kmem                  : 64; /**< [ 63:  0](SR/W) Key memory. KMEM is accessible using 8-, 16-, 32-, or 64-bit load or store operations. */
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_key_memx_s cn88xx; */
    /* struct bdk_key_memx_cn81xx cn83xx; */
};
typedef union bdk_key_memx bdk_key_memx_t;

static inline uint64_t BDK_KEY_MEMX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_MEMX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a<=2047))
        return 0x841000400000ll + 8ll * ((a) & 0x7ff);
    __bdk_csr_fatal("KEY_MEMX", 1, a, 0, 0, 0);
}

#define typedef_BDK_KEY_MEMX(a) bdk_key_memx_t
#define bustype_BDK_KEY_MEMX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_KEY_MEMX(a) "KEY_MEMX"
#define device_bar_BDK_KEY_MEMX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_KEY_MEMX(a) (a)
#define arguments_BDK_KEY_MEMX(a) (a),-1,-1,-1

/**
 * Register (RSL) key_mem_access
 *
 * KEY BIST Status Register
 * This register contains the controls to allow local and remote RSL access to KEY MEM.
 */
union bdk_key_mem_access
{
    uint64_t u;
    struct bdk_key_mem_access_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t rsldis                : 1;  /**< [  0:  0](SR/W1S) Disable RSL access to KEY_MEM.
                                                                   0 = RSL accesses to KEY_MEM are processed (and do not fault).
                                                                   1 = RSL accesses to KEY_MEM will fault.

                                                                 Once this bit is written with one it will remain set until chip reset. */
#else /* Word 0 - Little Endian */
        uint64_t rsldis                : 1;  /**< [  0:  0](SR/W1S) Disable RSL access to KEY_MEM.
                                                                   0 = RSL accesses to KEY_MEM are processed (and do not fault).
                                                                   1 = RSL accesses to KEY_MEM will fault.

                                                                 Once this bit is written with one it will remain set until chip reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_key_mem_access_s cn; */
};
typedef union bdk_key_mem_access bdk_key_mem_access_t;

#define BDK_KEY_MEM_ACCESS BDK_KEY_MEM_ACCESS_FUNC()
static inline uint64_t BDK_KEY_MEM_ACCESS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_MEM_ACCESS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
        return 0x87e041000020ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
        return 0x87e041000020ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X))
        return 0x87e041000020ll;
    __bdk_csr_fatal("KEY_MEM_ACCESS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_KEY_MEM_ACCESS bdk_key_mem_access_t
#define bustype_BDK_KEY_MEM_ACCESS BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_MEM_ACCESS "KEY_MEM_ACCESS"
#define device_bar_BDK_KEY_MEM_ACCESS 0x0 /* PF_BAR0 */
#define busnum_BDK_KEY_MEM_ACCESS 0
#define arguments_BDK_KEY_MEM_ACCESS -1,-1,-1,-1

/**
 * Register (RSL) key_msix_pba#
 *
 * KEY MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the KEY_INT_VEC_E enumeration.
 */
union bdk_key_msix_pbax
{
    uint64_t u;
    struct bdk_key_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](SRO/H) Pending message for the associated KEY_MSIX_VEC()_CTL, enumerated by KEY_INT_VEC_E. Bits
                                                                 that have no associated KEY_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](SRO/H) Pending message for the associated KEY_MSIX_VEC()_CTL, enumerated by KEY_INT_VEC_E. Bits
                                                                 that have no associated KEY_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    struct bdk_key_msix_pbax_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated KEY_MSIX_VEC()_CTL, enumerated by KEY_INT_VEC_E. Bits
                                                                 that have no associated KEY_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated KEY_MSIX_VEC()_CTL, enumerated by KEY_INT_VEC_E. Bits
                                                                 that have no associated KEY_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_key_msix_pbax_s cn88xx; */
    /* struct bdk_key_msix_pbax_cn81xx cn83xx; */
};
typedef union bdk_key_msix_pbax bdk_key_msix_pbax_t;

static inline uint64_t BDK_KEY_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_MSIX_PBAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a==0))
        return 0x87e041ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("KEY_MSIX_PBAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_KEY_MSIX_PBAX(a) bdk_key_msix_pbax_t
#define bustype_BDK_KEY_MSIX_PBAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_MSIX_PBAX(a) "KEY_MSIX_PBAX"
#define device_bar_BDK_KEY_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_KEY_MSIX_PBAX(a) (a)
#define arguments_BDK_KEY_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (RSL) key_msix_vec#_addr
 *
 * KEY MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the KEY_INT_VEC_E enumeration.
 */
union bdk_key_msix_vecx_addr
{
    uint64_t u;
    struct bdk_key_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](SR/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's KEY_MSIX_VEC()_ADDR, KEY_MSIX_VEC()_CTL, and corresponding
                                                                 bit of KEY_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_KEY_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's KEY_MSIX_VEC()_ADDR, KEY_MSIX_VEC()_CTL, and corresponding
                                                                 bit of KEY_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_KEY_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](SR/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    struct bdk_key_msix_vecx_addr_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's KEY_MSIX_VEC()_ADDR, KEY_MSIX_VEC()_CTL, and corresponding
                                                                 bit of KEY_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_KEY_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's KEY_MSIX_VEC()_ADDR, KEY_MSIX_VEC()_CTL, and corresponding
                                                                 bit of KEY_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_KEY_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_key_msix_vecx_addr_s cn88xx; */
    /* struct bdk_key_msix_vecx_addr_cn81xx cn83xx; */
};
typedef union bdk_key_msix_vecx_addr bdk_key_msix_vecx_addr_t;

static inline uint64_t BDK_KEY_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_MSIX_VECX_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a==0))
        return 0x87e041f00000ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("KEY_MSIX_VECX_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_KEY_MSIX_VECX_ADDR(a) bdk_key_msix_vecx_addr_t
#define bustype_BDK_KEY_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_MSIX_VECX_ADDR(a) "KEY_MSIX_VECX_ADDR"
#define device_bar_BDK_KEY_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_KEY_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_KEY_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) key_msix_vec#_ctl
 *
 * KEY MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the KEY_INT_VEC_E enumeration.
 */
union bdk_key_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_key_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](SR/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t data                  : 20; /**< [ 19:  0](SR/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 20; /**< [ 19:  0](SR/W) Data to use for MSI-X delivery of this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t mask                  : 1;  /**< [ 32: 32](SR/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    struct bdk_key_msix_vecx_ctl_cn81xx
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
    } cn81xx;
    /* struct bdk_key_msix_vecx_ctl_s cn88xx; */
    /* struct bdk_key_msix_vecx_ctl_cn81xx cn83xx; */
};
typedef union bdk_key_msix_vecx_ctl bdk_key_msix_vecx_ctl_t;

static inline uint64_t BDK_KEY_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_KEY_MSIX_VECX_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a==0))
        return 0x87e041f00008ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("KEY_MSIX_VECX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_KEY_MSIX_VECX_CTL(a) bdk_key_msix_vecx_ctl_t
#define bustype_BDK_KEY_MSIX_VECX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_KEY_MSIX_VECX_CTL(a) "KEY_MSIX_VECX_CTL"
#define device_bar_BDK_KEY_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_KEY_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_KEY_MSIX_VECX_CTL(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_KEY_H__ */
