#ifndef __BDK_CSRS_MCC_H__
#define __BDK_CSRS_MCC_H__
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
 * Cavium MCC.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration mcc_bar_e
 *
 * MCC Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_MCC_BAR_E_MCCX_PF_BAR0(a) (0x87e03c000000ll + 0x1000000ll * (a))
#define BDK_MCC_BAR_E_MCCX_PF_BAR0_SIZE 0x800000ull
#define BDK_MCC_BAR_E_MCCX_PF_BAR4(a) (0x87e03cf00000ll + 0x1000000ll * (a))
#define BDK_MCC_BAR_E_MCCX_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration mcc_int_vec_e
 *
 * MCC MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_MCC_INT_VEC_E_LMCOEX_INT(a) (2 + (a))
#define BDK_MCC_INT_VEC_E_MCIX_INT(a) (0 + (a))

/**
 * Register (RSL) mcc#_config
 *
 * MCC Configuration Register
 * This register controls certain parameters required for memory configuration.
 */
union bdk_mccx_config
{
    uint64_t u;
    struct bdk_mccx_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t mci_cclk_dis          : 1;  /**< [  7:  7](R/W) Force coarse grained conditional clocks on.
                                                                 For diagnostic use only. */
        uint64_t early_rsp_val_ena     : 1;  /**< [  6:  6](R/W) Reserved.
                                                                 Internal:
                                                                 FIXME rename CSR + description update. */
        uint64_t background_scrub_ena  : 1;  /**< [  5:  5](R/W) Reserved.
                                                                 Internal:
                                                                 FIXME rename CSR + description update. */
        uint64_t demand_scrub_ena      : 1;  /**< [  4:  4](R/W) When a ECC error occurs, write back to DRAM the corrected data.
                                                                 Internal:
                                                                 FIXME rename CSR + description update. */
        uint64_t scramble_ena          : 1;  /**< [  3:  3](R/W) When set, enable the scramble/descramble logic for secure transactions. */
        uint64_t dram_ecc_ena          : 1;  /**< [  2:  2](R/W) ECC enable. When set, enables the 8b ECC check/correct logic. Should be one when used with
                                                                 DIMMs with ECC; zero, otherwise.

                                                                 0 = DQ\<71:64\> are driven to 0x0.

                                                                 1 = DQ\<71:64\> on write operations contains the ECC code generated for the 64
                                                                 bits of data which will be written in the memory. Later on read operations, used
                                                                 to check for single-bit error (which will be auto-corrected) and double-bit
                                                                 error (which will be reported).
                                                                 See MCC()_LMCOE()_INT[DED_ERR], MCC()_LMCOE()_INT[SEC_ERR]. */
        uint64_t dis_tadpsn            : 1;  /**< [  1:  1](R/W) When set, disable both Poison notification on incoming write data from TAD and
                                                                 poison generation on outgoing read data to the mesh. */
        uint64_t dis_tadecc            : 1;  /**< [  0:  0](R/W) When set, disable ECC correction on incoming write data from TAD. */
#else /* Word 0 - Little Endian */
        uint64_t dis_tadecc            : 1;  /**< [  0:  0](R/W) When set, disable ECC correction on incoming write data from TAD. */
        uint64_t dis_tadpsn            : 1;  /**< [  1:  1](R/W) When set, disable both Poison notification on incoming write data from TAD and
                                                                 poison generation on outgoing read data to the mesh. */
        uint64_t dram_ecc_ena          : 1;  /**< [  2:  2](R/W) ECC enable. When set, enables the 8b ECC check/correct logic. Should be one when used with
                                                                 DIMMs with ECC; zero, otherwise.

                                                                 0 = DQ\<71:64\> are driven to 0x0.

                                                                 1 = DQ\<71:64\> on write operations contains the ECC code generated for the 64
                                                                 bits of data which will be written in the memory. Later on read operations, used
                                                                 to check for single-bit error (which will be auto-corrected) and double-bit
                                                                 error (which will be reported).
                                                                 See MCC()_LMCOE()_INT[DED_ERR], MCC()_LMCOE()_INT[SEC_ERR]. */
        uint64_t scramble_ena          : 1;  /**< [  3:  3](R/W) When set, enable the scramble/descramble logic for secure transactions. */
        uint64_t demand_scrub_ena      : 1;  /**< [  4:  4](R/W) When a ECC error occurs, write back to DRAM the corrected data.
                                                                 Internal:
                                                                 FIXME rename CSR + description update. */
        uint64_t background_scrub_ena  : 1;  /**< [  5:  5](R/W) Reserved.
                                                                 Internal:
                                                                 FIXME rename CSR + description update. */
        uint64_t early_rsp_val_ena     : 1;  /**< [  6:  6](R/W) Reserved.
                                                                 Internal:
                                                                 FIXME rename CSR + description update. */
        uint64_t mci_cclk_dis          : 1;  /**< [  7:  7](R/W) Force coarse grained conditional clocks on.
                                                                 For diagnostic use only. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_config_s cn; */
};
typedef union bdk_mccx_config bdk_mccx_config_t;

static inline uint64_t BDK_MCCX_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_CONFIG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e03c000060ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MCCX_CONFIG", 1, a, 0, 0, 0);
}

#define typedef_BDK_MCCX_CONFIG(a) bdk_mccx_config_t
#define bustype_BDK_MCCX_CONFIG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_CONFIG(a) "MCCX_CONFIG"
#define device_bar_BDK_MCCX_CONFIG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_CONFIG(a) (a)
#define arguments_BDK_MCCX_CONFIG(a) (a),-1,-1,-1

/**
 * Register (RSL) mcc#_const
 *
 * MCC Constants Register
 * This register is for software discovery of MCC features.
 */
union bdk_mccx_const
{
    uint64_t u;
    struct bdk_mccx_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t lmcs                  : 8;  /**< [  7:  0](RO/H) Number of LMCs attached to corresponding MCC.
                                                                 _ MCC(0)_CONST[LMCS] = 0x2.
                                                                 _ MCC(1)_CONST[LMCS] = 0x1. */
#else /* Word 0 - Little Endian */
        uint64_t lmcs                  : 8;  /**< [  7:  0](RO/H) Number of LMCs attached to corresponding MCC.
                                                                 _ MCC(0)_CONST[LMCS] = 0x2.
                                                                 _ MCC(1)_CONST[LMCS] = 0x1. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_const_s cn; */
};
typedef union bdk_mccx_const bdk_mccx_const_t;

static inline uint64_t BDK_MCCX_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_CONST(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e03c000000ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MCCX_CONST", 1, a, 0, 0, 0);
}

#define typedef_BDK_MCCX_CONST(a) bdk_mccx_const_t
#define bustype_BDK_MCCX_CONST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_CONST(a) "MCCX_CONST"
#define device_bar_BDK_MCCX_CONST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_CONST(a) (a)
#define arguments_BDK_MCCX_CONST(a) (a),-1,-1,-1

/**
 * Register (RSL) mcc#_ctl_active_pc
 *
 * MCC_CTL Conditional Clock Counter Register
 * This register counts conditional clocks for power management.
 * This register is reset on MCC domain reset.
 */
union bdk_mccx_ctl_active_pc
{
    uint64_t u;
    struct bdk_mccx_ctl_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_ctl_active_pc_s cn; */
};
typedef union bdk_mccx_ctl_active_pc bdk_mccx_ctl_active_pc_t;

static inline uint64_t BDK_MCCX_CTL_ACTIVE_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_CTL_ACTIVE_PC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e03c000040ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MCCX_CTL_ACTIVE_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_MCCX_CTL_ACTIVE_PC(a) bdk_mccx_ctl_active_pc_t
#define bustype_BDK_MCCX_CTL_ACTIVE_PC(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_CTL_ACTIVE_PC(a) "MCCX_CTL_ACTIVE_PC"
#define device_bar_BDK_MCCX_CTL_ACTIVE_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_CTL_ACTIVE_PC(a) (a)
#define arguments_BDK_MCCX_CTL_ACTIVE_PC(a) (a),-1,-1,-1

/**
 * Register (RSL) mcc#_eco
 *
 * INTERNAL: MCC ECO Register
 */
union bdk_mccx_eco
{
    uint64_t u;
    struct bdk_mccx_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_eco_s cn; */
};
typedef union bdk_mccx_eco bdk_mccx_eco_t;

static inline uint64_t BDK_MCCX_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_ECO(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e03c000080ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MCCX_ECO", 1, a, 0, 0, 0);
}

#define typedef_BDK_MCCX_ECO(a) bdk_mccx_eco_t
#define bustype_BDK_MCCX_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_ECO(a) "MCCX_ECO"
#define device_bar_BDK_MCCX_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_ECO(a) (a)
#define arguments_BDK_MCCX_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_bscrub_cfg
 *
 * LMC Background Scrub Control Register
 * This register controls background scrubbing.
 * _ MCC(0)_LMCOE(0)_* = LMC1's background scrub control.
 * _ MCC(0)_LMCOE(1)_* = Reserved.
 * _ MCC(1)_LMCOE(0)_* = LMC0's background scrub control.
 * _ MCC(1)_LMCOE(1)_* = LMC2's background scrub control.
 */
union bdk_mccx_lmcoex_bscrub_cfg
{
    uint64_t u;
    struct bdk_mccx_lmcoex_bscrub_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t start_address         : 35; /**< [ 42:  8](R/W) Specifies the start of LMCx's DRAM address range to be background scrubbed. This
                                                                 field may not be modified when [ENABLE] is already set to 1.
                                                                 Refer to the description above to get the actual LMC number. */
        uint64_t reserved_3_7          : 5;
        uint64_t busy                  : 1;  /**< [  2:  2](RO/H) Indicates LMCx's background scrubber is busy. */
        uint64_t reserved_1            : 1;
        uint64_t enable                : 1;  /**< [  0:  0](R/W) LMCx's background scrub enable.
                                                                 0 = Stop or disable the background scrub.
                                                                 1 = Enable the background scrub operation. Software needs to ensure that
                                                                 MCC()_LMCOE()_BSCRUB_CFG[BUSY] is not set anytime it wants to enable the
                                                                 background scrub operation. */
#else /* Word 0 - Little Endian */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) LMCx's background scrub enable.
                                                                 0 = Stop or disable the background scrub.
                                                                 1 = Enable the background scrub operation. Software needs to ensure that
                                                                 MCC()_LMCOE()_BSCRUB_CFG[BUSY] is not set anytime it wants to enable the
                                                                 background scrub operation. */
        uint64_t reserved_1            : 1;
        uint64_t busy                  : 1;  /**< [  2:  2](RO/H) Indicates LMCx's background scrubber is busy. */
        uint64_t reserved_3_7          : 5;
        uint64_t start_address         : 35; /**< [ 42:  8](R/W) Specifies the start of LMCx's DRAM address range to be background scrubbed. This
                                                                 field may not be modified when [ENABLE] is already set to 1.
                                                                 Refer to the description above to get the actual LMC number. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_bscrub_cfg_s cn; */
};
typedef union bdk_mccx_lmcoex_bscrub_cfg bdk_mccx_lmcoex_bscrub_cfg_t;

static inline uint64_t BDK_MCCX_LMCOEX_BSCRUB_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_BSCRUB_CFG(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000400ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_BSCRUB_CFG", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_BSCRUB_CFG(a,b) bdk_mccx_lmcoex_bscrub_cfg_t
#define bustype_BDK_MCCX_LMCOEX_BSCRUB_CFG(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_BSCRUB_CFG(a,b) "MCCX_LMCOEX_BSCRUB_CFG"
#define device_bar_BDK_MCCX_LMCOEX_BSCRUB_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_BSCRUB_CFG(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_BSCRUB_CFG(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_bscrub_cfg2
 *
 * LMC Background Scrub Control Register
 * This register controls background scrubbing.
 * _ MCC(0)_LMCOE(0)_* = LMC1's background scrub control.
 * _ MCC(0)_LMCOE(1)_* = Reserved.
 * _ MCC(1)_LMCOE(0)_* = LMC0's background scrub control.
 * _ MCC(1)_LMCOE(1)_* = LMC2's background scrub control.
 */
union bdk_mccx_lmcoex_bscrub_cfg2
{
    uint64_t u;
    struct bdk_mccx_lmcoex_bscrub_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t stop_address          : 35; /**< [ 34:  0](R/W) Specifies the end of LMCx's DRAM address range to be background scrubbed. This
                                                                 field may not be modified when MCC()_LMCOE()_BSCRUB_CFG[ENABLE] is
                                                                 already set to 1.
                                                                 Refer to the register description above to get the actual LMC number. */
#else /* Word 0 - Little Endian */
        uint64_t stop_address          : 35; /**< [ 34:  0](R/W) Specifies the end of LMCx's DRAM address range to be background scrubbed. This
                                                                 field may not be modified when MCC()_LMCOE()_BSCRUB_CFG[ENABLE] is
                                                                 already set to 1.
                                                                 Refer to the register description above to get the actual LMC number. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_bscrub_cfg2_s cn; */
};
typedef union bdk_mccx_lmcoex_bscrub_cfg2 bdk_mccx_lmcoex_bscrub_cfg2_t;

static inline uint64_t BDK_MCCX_LMCOEX_BSCRUB_CFG2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_BSCRUB_CFG2(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000420ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_BSCRUB_CFG2", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) bdk_mccx_lmcoex_bscrub_cfg2_t
#define bustype_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) "MCCX_LMCOEX_BSCRUB_CFG2"
#define device_bar_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_const
 *
 * MCC LMC Odd/Even Constants Register
 * This register is for software discovery of absolute LMC number attached to the
 * MCC/LMCOE combination.
 */
union bdk_mccx_lmcoex_const
{
    uint64_t u;
    struct bdk_mccx_lmcoex_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t lmc                   : 8;  /**< [  7:  0](RO/H) Absolute LMC number attached to this MCC/LMCOE combination.
                                                                 _ MCC(0)_LMCOE(0)_CONST[LMC] = 0x1 = LMC1.
                                                                 _ MCC(0)_LMCOE(1)_CONST[LMC] = Reserved. (MCC(1)_CONST[LMCS] is 0x1, so
                                                                 indicates this should not be read).
                                                                 _ MCC(1)_LMCOE(0)_CONST[LMC] = 0x0 = LMC0.
                                                                 _ MCC(1)_LMCOE(1)_CONST[LMC] = 0x2 = LMC2. */
#else /* Word 0 - Little Endian */
        uint64_t lmc                   : 8;  /**< [  7:  0](RO/H) Absolute LMC number attached to this MCC/LMCOE combination.
                                                                 _ MCC(0)_LMCOE(0)_CONST[LMC] = 0x1 = LMC1.
                                                                 _ MCC(0)_LMCOE(1)_CONST[LMC] = Reserved. (MCC(1)_CONST[LMCS] is 0x1, so
                                                                 indicates this should not be read).
                                                                 _ MCC(1)_LMCOE(0)_CONST[LMC] = 0x0 = LMC0.
                                                                 _ MCC(1)_LMCOE(1)_CONST[LMC] = 0x2 = LMC2. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_const_s cn; */
};
typedef union bdk_mccx_lmcoex_const bdk_mccx_lmcoex_const_t;

static inline uint64_t BDK_MCCX_LMCOEX_CONST(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_CONST(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000020ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_CONST", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_CONST(a,b) bdk_mccx_lmcoex_const_t
#define bustype_BDK_MCCX_LMCOEX_CONST(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_CONST(a,b) "MCCX_LMCOEX_CONST"
#define device_bar_BDK_MCCX_LMCOEX_CONST(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_CONST(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_CONST(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ded_fadr
 *
 * LMCx Double-bit Error Correctable by retry Failing Address Register
 * This register captures the first LMC read transaction with a double-bit error.
 * Software must clear MCC()_LMCOE()_INT[DED_ERR] interrupt to enable capturing the
 * next failing address.
 * _ MCC(0)_LMCOE(0)_* = LMC1's double-bit error failing address.
 * _ MCC(0)_LMCOE(1)_* = Reserved.
 * _ MCC(1)_LMCOE(0)_* = LMC0's double-bit error failing address.
 * _ MCC(1)_LMCOE(1)_* = LMC2's double-bit error failing address.
 *
 * Internal:
 * Demand or Background Scruber Double-bit Error corrected by retry.
 */
union bdk_mccx_lmcoex_ded_fadr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ded_fadr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ded_fadr_s cn; */
};
typedef union bdk_mccx_lmcoex_ded_fadr bdk_mccx_lmcoex_ded_fadr_t;

static inline uint64_t BDK_MCCX_LMCOEX_DED_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_DED_FADR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c0002a0ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_DED_FADR", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_DED_FADR(a,b) bdk_mccx_lmcoex_ded_fadr_t
#define bustype_BDK_MCCX_LMCOEX_DED_FADR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_DED_FADR(a,b) "MCCX_LMCOEX_DED_FADR"
#define device_bar_BDK_MCCX_LMCOEX_DED_FADR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_DED_FADR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_DED_FADR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_int
 *
 * MCC Interrupt Register
 * This register contains the different interrupt-summary bits of the MCC.
 * _ MCC(0)_LMCOE(0)_* = LMC1's interrupt.
 * _ MCC(0)_LMCOE(1)_* = Reserved.
 * _ MCC(1)_LMCOE(0)_* = LMC0's interrupt.
 * _ MCC(1)_LMCOE(1)_* = LMC2's interrupt.
 */
union bdk_mccx_lmcoex_int
{
    uint64_t u;
    struct bdk_mccx_lmcoex_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t wr_nxm                : 1;  /**< [  5:  5](R/W1C/H) When set, indicates an LMC write transaction to nonexistent memory address.
                                                                 See MCC()_LMCOE()_WRNXM_FADR for recorded read nxm address.
                                                                 Refer to the register description above to get the LMC number. */
        uint64_t rd_nxm                : 1;  /**< [  4:  4](R/W1C/H) When set, indicates an LMC read transaction to nonexistent memory address.
                                                                 See MCC()_LMCOE()_RDNXM_FADR for recorded read nxm address.
                                                                 Refer to the register description above to get the LMC number. */
        uint64_t reserved_2_3          : 2;
        uint64_t ded_err               : 1;  /**< [  1:  1](R/W1C/H) Double-bit error detected from an LMC read.
                                                                 Refer to the register description above to get the LMC number.

                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t sec_err               : 1;  /**< [  0:  0](R/W1C/H) Single-bit error detected on an LMC read.
                                                                 Refer to the register description above to get the LMC number.

                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
#else /* Word 0 - Little Endian */
        uint64_t sec_err               : 1;  /**< [  0:  0](R/W1C/H) Single-bit error detected on an LMC read.
                                                                 Refer to the register description above to get the LMC number.

                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t ded_err               : 1;  /**< [  1:  1](R/W1C/H) Double-bit error detected from an LMC read.
                                                                 Refer to the register description above to get the LMC number.

                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_2_3          : 2;
        uint64_t rd_nxm                : 1;  /**< [  4:  4](R/W1C/H) When set, indicates an LMC read transaction to nonexistent memory address.
                                                                 See MCC()_LMCOE()_RDNXM_FADR for recorded read nxm address.
                                                                 Refer to the register description above to get the LMC number. */
        uint64_t wr_nxm                : 1;  /**< [  5:  5](R/W1C/H) When set, indicates an LMC write transaction to nonexistent memory address.
                                                                 See MCC()_LMCOE()_WRNXM_FADR for recorded read nxm address.
                                                                 Refer to the register description above to get the LMC number. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_int_s cn; */
};
typedef union bdk_mccx_lmcoex_int bdk_mccx_lmcoex_int_t;

static inline uint64_t BDK_MCCX_LMCOEX_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_INT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000200ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_INT", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_INT(a,b) bdk_mccx_lmcoex_int_t
#define bustype_BDK_MCCX_LMCOEX_INT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_INT(a,b) "MCCX_LMCOEX_INT"
#define device_bar_BDK_MCCX_LMCOEX_INT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_INT(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_INT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_int_ena_w1c
 *
 * MCC Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_mccx_lmcoex_int_ena_w1c
{
    uint64_t u;
    struct bdk_mccx_lmcoex_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t wr_nxm                : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t reserved_2_3          : 2;
        uint64_t ded_err               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t sec_err               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
#else /* Word 0 - Little Endian */
        uint64_t sec_err               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t ded_err               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_2_3          : 2;
        uint64_t rd_nxm                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_int_ena_w1c_s cn; */
};
typedef union bdk_mccx_lmcoex_int_ena_w1c bdk_mccx_lmcoex_int_ena_w1c_t;

static inline uint64_t BDK_MCCX_LMCOEX_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000240ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_INT_ENA_W1C", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_INT_ENA_W1C(a,b) bdk_mccx_lmcoex_int_ena_w1c_t
#define bustype_BDK_MCCX_LMCOEX_INT_ENA_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_INT_ENA_W1C(a,b) "MCCX_LMCOEX_INT_ENA_W1C"
#define device_bar_BDK_MCCX_LMCOEX_INT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_INT_ENA_W1C(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_INT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_int_ena_w1s
 *
 * MCC Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_mccx_lmcoex_int_ena_w1s
{
    uint64_t u;
    struct bdk_mccx_lmcoex_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t wr_nxm                : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t reserved_2_3          : 2;
        uint64_t ded_err               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t sec_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
#else /* Word 0 - Little Endian */
        uint64_t sec_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t ded_err               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_2_3          : 2;
        uint64_t rd_nxm                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_int_ena_w1s_s cn; */
};
typedef union bdk_mccx_lmcoex_int_ena_w1s bdk_mccx_lmcoex_int_ena_w1s_t;

static inline uint64_t BDK_MCCX_LMCOEX_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000260ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_INT_ENA_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_INT_ENA_W1S(a,b) bdk_mccx_lmcoex_int_ena_w1s_t
#define bustype_BDK_MCCX_LMCOEX_INT_ENA_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_INT_ENA_W1S(a,b) "MCCX_LMCOEX_INT_ENA_W1S"
#define device_bar_BDK_MCCX_LMCOEX_INT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_INT_ENA_W1S(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_INT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_int_w1s
 *
 * MCC Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_mccx_lmcoex_int_w1s
{
    uint64_t u;
    struct bdk_mccx_lmcoex_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t wr_nxm                : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t reserved_2_3          : 2;
        uint64_t ded_err               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t sec_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
#else /* Word 0 - Little Endian */
        uint64_t sec_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t ded_err               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_2_3          : 2;
        uint64_t rd_nxm                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_int_w1s_s cn; */
};
typedef union bdk_mccx_lmcoex_int_w1s bdk_mccx_lmcoex_int_w1s_t;

static inline uint64_t BDK_MCCX_LMCOEX_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_INT_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000220ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_INT_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_INT_W1S(a,b) bdk_mccx_lmcoex_int_w1s_t
#define bustype_BDK_MCCX_LMCOEX_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_INT_W1S(a,b) "MCCX_LMCOEX_INT_W1S"
#define device_bar_BDK_MCCX_LMCOEX_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_INT_W1S(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_rdnxm_fadr
 *
 * LMCx Read NXM Failing Address Register
 * This register captures the first transaction when MCC()_LMCOE()_INT[RD_NXM] is set,
 * recording the address of the associated RD command sent that triggered the
 * error. Software must clear MCC()_LMCOE()_INT[RD_NXM] interrupt to enable capturing
 * the next failing address.
 * _ MCC(0)_LMCOE(0)_* = LMC1's Read NXM Failing Address.
 * _ MCC(0)_LMCOE(1)_* = Reserved.
 * _ MCC(1)_LMCOE(0)_* = LMC0's Read NXM Failing Address.
 * _ MCC(1)_LMCOE(1)_* = LMC2's Read NXM Failing Address.
 */
union bdk_mccx_lmcoex_rdnxm_fadr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_rdnxm_fadr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_rdnxm_fadr_s cn; */
};
typedef union bdk_mccx_lmcoex_rdnxm_fadr bdk_mccx_lmcoex_rdnxm_fadr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RDNXM_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RDNXM_FADR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000300ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RDNXM_FADR", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) bdk_mccx_lmcoex_rdnxm_fadr_t
#define bustype_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) "MCCX_LMCOEX_RDNXM_FADR"
#define device_bar_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_sec_fadr
 *
 * LMCx Single-bit Error Correctable Failing Address Register
 * This register captures the first LMC read transaction with a single-bit correctable
 * data error. It records the address of the associated RD command sent that triggered
 * the correctable data error.
 * Software must clear MCC()_LMCOE()_INT[SEC_ERR] interrupt to enable capturing the
 * next failing address.
 * _ MCC(0)_LMCOE(0)_* = LMC1's single-bit error read failing address.
 * _ MCC(0)_LMCOE(1)_* = Reserved.
 * _ MCC(1)_LMCOE(0)_* = LMC0's single-bit error read failing address.
 * _ MCC(1)_LMCOE(1)_* = LMC2's single-bit error read failing address.
 *
 * Internal:
 * Demand or Background scrubber read ECC correctable
 */
union bdk_mccx_lmcoex_sec_fadr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_sec_fadr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_sec_fadr_s cn; */
};
typedef union bdk_mccx_lmcoex_sec_fadr bdk_mccx_lmcoex_sec_fadr_t;

static inline uint64_t BDK_MCCX_LMCOEX_SEC_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_SEC_FADR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000280ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_SEC_FADR", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_SEC_FADR(a,b) bdk_mccx_lmcoex_sec_fadr_t
#define bustype_BDK_MCCX_LMCOEX_SEC_FADR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_SEC_FADR(a,b) "MCCX_LMCOEX_SEC_FADR"
#define device_bar_BDK_MCCX_LMCOEX_SEC_FADR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_SEC_FADR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_SEC_FADR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_wrnxm_fadr
 *
 * LMCx Write NXM Failing Address Register
 * This register captures the first transaction when MCC()_LMCOE()_INT[WR_NXM] is set,
 * recording the address of the associated WR command sent that triggered the
 * error. Software must clear MCC()_LMCOE()_INT[WR_NXM] interrupt to enable capturing
 * the next failing address.
 * _ MCC(0)_LMCOE(0)_* = LMC1's Write NXM Failing Address.
 * _ MCC(0)_LMCOE(1)_* = Reserved.
 * _ MCC(1)_LMCOE(0)_* = LMC0's Write NXM Failing Address.
 * _ MCC(1)_LMCOE(1)_* = LMC2's Write NXM Failing Address.
 */
union bdk_mccx_lmcoex_wrnxm_fadr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_wrnxm_fadr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_wrnxm_fadr_s cn; */
};
typedef union bdk_mccx_lmcoex_wrnxm_fadr bdk_mccx_lmcoex_wrnxm_fadr_t;

static inline uint64_t BDK_MCCX_LMCOEX_WRNXM_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_WRNXM_FADR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c000320ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_WRNXM_FADR", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_WRNXM_FADR(a,b) bdk_mccx_lmcoex_wrnxm_fadr_t
#define bustype_BDK_MCCX_LMCOEX_WRNXM_FADR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_WRNXM_FADR(a,b) "MCCX_LMCOEX_WRNXM_FADR"
#define device_bar_BDK_MCCX_LMCOEX_WRNXM_FADR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_WRNXM_FADR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_WRNXM_FADR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_bp_test
 *
 * INTERNAL: MCC MCI Backpressure Test Register
 */
union bdk_mccx_mcix_bp_test
{
    uint64_t u;
    struct bdk_mccx_mcix_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = When set, disables popping of Read Command FIFOs from TADs.
                                                                 \<62\> = When set, disables popping of Write/WBar Command FIFOs from TADs.
                                                                 \<61\> = When set, disables popping of Read Data from CTL.
                                                                 \<60\> = When set, disables popping of ACKs from CTL. */
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
                                                                 \<63\> = When set, disables popping of Read Command FIFOs from TADs.
                                                                 \<62\> = When set, disables popping of Write/WBar Command FIFOs from TADs.
                                                                 \<61\> = When set, disables popping of Read Data from CTL.
                                                                 \<60\> = When set, disables popping of ACKs from CTL. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_bp_test_s cn; */
};
typedef union bdk_mccx_mcix_bp_test bdk_mccx_mcix_bp_test_t;

static inline uint64_t BDK_MCCX_MCIX_BP_TEST(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_BP_TEST(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400048ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_BP_TEST", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_BP_TEST(a,b) bdk_mccx_mcix_bp_test_t
#define bustype_BDK_MCCX_MCIX_BP_TEST(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_BP_TEST(a,b) "MCCX_MCIX_BP_TEST"
#define device_bar_BDK_MCCX_MCIX_BP_TEST(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_BP_TEST(a,b) (a)
#define arguments_BDK_MCCX_MCIX_BP_TEST(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_dbe_dbg_cnt
 *
 * INTERNAL: MCC MCI DBE Detection Counter Registers
 *
 * This register keeps track of the number of double-bit errors arriving on the DAT
 * mesh into MCI from MSW in saturating counters. For debug purposes only - no
 * correction.
 */
union bdk_mccx_mcix_dbe_dbg_cnt
{
    uint64_t u;
    struct bdk_mccx_mcix_dbe_dbg_cnt_s
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
    /* struct bdk_mccx_mcix_dbe_dbg_cnt_s cn; */
};
typedef union bdk_mccx_mcix_dbe_dbg_cnt bdk_mccx_mcix_dbe_dbg_cnt_t;

static inline uint64_t BDK_MCCX_MCIX_DBE_DBG_CNT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_DBE_DBG_CNT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400060ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_DBE_DBG_CNT", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) bdk_mccx_mcix_dbe_dbg_cnt_t
#define bustype_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) "MCCX_MCIX_DBE_DBG_CNT"
#define device_bar_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) (a)
#define arguments_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ded_fadr
 *
 * MCC MCI Double-bit Error Uncorrectable Failing Address Register
 * This register captures the first Mesh write transaction with a double-bit uncorrectable
 * data error. It records the address of the associated WR command sent that triggered the error.
 * Software must clear MCC()_MCI()_INT[DED_ERR] interrupt to enable capturing the
 * next failing address.
 */
union bdk_mccx_mcix_ded_fadr
{
    uint64_t u;
    struct bdk_mccx_mcix_ded_fadr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ded_fadr_s cn; */
};
typedef union bdk_mccx_mcix_ded_fadr bdk_mccx_mcix_ded_fadr_t;

static inline uint64_t BDK_MCCX_MCIX_DED_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_DED_FADR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400238ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_DED_FADR", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_DED_FADR(a,b) bdk_mccx_mcix_ded_fadr_t
#define bustype_BDK_MCCX_MCIX_DED_FADR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_DED_FADR(a,b) "MCCX_MCIX_DED_FADR"
#define device_bar_BDK_MCCX_MCIX_DED_FADR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_DED_FADR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_DED_FADR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ecc_dbg_en
 *
 * INTERNAL: MCC MCI Mesh ECC Error Detection Counter Control Register
 *
 * This register enables counting of the number of single and double bit errors on the
 * DAT mesh coming into MCI from MSW.
 * For debug purposes only, no SBE correction.
 */
union bdk_mccx_mcix_ecc_dbg_en
{
    uint64_t u;
    struct bdk_mccx_mcix_ecc_dbg_en_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t sbe                   : 1;  /**< [  1:  1](R/W) Enable counting the number of SBEs seen on the DAT mesh in MCC()_MCI()_SBE_DBG_CNT. */
        uint64_t dbe                   : 1;  /**< [  0:  0](R/W) Enable counting the number of DBEs seen on the DAT mesh in MCC()_MCI()_DBE_DBG_CNT. */
#else /* Word 0 - Little Endian */
        uint64_t dbe                   : 1;  /**< [  0:  0](R/W) Enable counting the number of DBEs seen on the DAT mesh in MCC()_MCI()_DBE_DBG_CNT. */
        uint64_t sbe                   : 1;  /**< [  1:  1](R/W) Enable counting the number of SBEs seen on the DAT mesh in MCC()_MCI()_SBE_DBG_CNT. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ecc_dbg_en_s cn; */
};
typedef union bdk_mccx_mcix_ecc_dbg_en bdk_mccx_mcix_ecc_dbg_en_t;

static inline uint64_t BDK_MCCX_MCIX_ECC_DBG_EN(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_ECC_DBG_EN(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400050ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_ECC_DBG_EN", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_ECC_DBG_EN(a,b) bdk_mccx_mcix_ecc_dbg_en_t
#define bustype_BDK_MCCX_MCIX_ECC_DBG_EN(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_ECC_DBG_EN(a,b) "MCCX_MCIX_ECC_DBG_EN"
#define device_bar_BDK_MCCX_MCIX_ECC_DBG_EN(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_ECC_DBG_EN(a,b) (a)
#define arguments_BDK_MCCX_MCIX_ECC_DBG_EN(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_eco
 *
 * INTERNAL: MCC MCI ECO Register
 */
union bdk_mccx_mcix_eco
{
    uint64_t u;
    struct bdk_mccx_mcix_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_eco_s cn; */
};
typedef union bdk_mccx_mcix_eco bdk_mccx_mcix_eco_t;

static inline uint64_t BDK_MCCX_MCIX_ECO(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_ECO(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400040ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_ECO", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_ECO(a,b) bdk_mccx_mcix_eco_t
#define bustype_BDK_MCCX_MCIX_ECO(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_ECO(a,b) "MCCX_MCIX_ECO"
#define device_bar_BDK_MCCX_MCIX_ECO(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_ECO(a,b) (a)
#define arguments_BDK_MCCX_MCIX_ECO(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_int
 *
 * MCC MCI Interrupt Register
 * This register contains the different interrupt-summary bits of MCI.
 */
union bdk_mccx_mcix_int
{
    uint64_t u;
    struct bdk_mccx_mcix_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ded_err               : 1;  /**< [  9:  9](R/W1C/H) Double-bit error detected on CCU's Mesh write data.
                                                                 See MCC()_MCI()_DED_FADR for address.

                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t sec_err               : 1;  /**< [  8:  8](R/W1C/H) Single-bit error detected on CCU's Mesh write data.
                                                                 See MCC()_MCI()_DED_FADR for address.

                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_7            : 1;
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1C/H) Illegal write to disabled LMC error. A DRAM write arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_WRDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1C/H) Illegal write to disabled LMC error. A DRAM write arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_WRDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1C/H) Illegal write to disabled LMC error. A DRAM write arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_WRDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t reserved_3            : 1;
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1C/H) Illegal read to disabled LMC error. A DRAM read arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_RDDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1C/H) Illegal read to disabled LMC error. A DRAM read arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_RDDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1C/H) Illegal read to disabled LMC error. A DRAM read arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_RDDISLMC_FADR for address.
                                                                 This may be considered fatal. */
#else /* Word 0 - Little Endian */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1C/H) Illegal read to disabled LMC error. A DRAM read arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_RDDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1C/H) Illegal read to disabled LMC error. A DRAM read arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_RDDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1C/H) Illegal read to disabled LMC error. A DRAM read arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_RDDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t reserved_3            : 1;
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1C/H) Illegal write to disabled LMC error. A DRAM write arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_WRDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1C/H) Illegal write to disabled LMC error. A DRAM write arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_WRDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1C/H) Illegal write to disabled LMC error. A DRAM write arrived before LMC was enabled.
                                                                 Should not occur during normal operation. See MCC()_MCI()_WRDISLMC_FADR for address.
                                                                 This may be considered fatal. */
        uint64_t reserved_7            : 1;
        uint64_t sec_err               : 1;  /**< [  8:  8](R/W1C/H) Single-bit error detected on CCU's Mesh write data.
                                                                 See MCC()_MCI()_DED_FADR for address.

                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t ded_err               : 1;  /**< [  9:  9](R/W1C/H) Double-bit error detected on CCU's Mesh write data.
                                                                 See MCC()_MCI()_DED_FADR for address.

                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_int_s cn; */
};
typedef union bdk_mccx_mcix_int bdk_mccx_mcix_int_t;

static inline uint64_t BDK_MCCX_MCIX_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_INT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400200ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_INT", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_INT(a,b) bdk_mccx_mcix_int_t
#define bustype_BDK_MCCX_MCIX_INT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_INT(a,b) "MCCX_MCIX_INT"
#define device_bar_BDK_MCCX_MCIX_INT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_INT(a,b) (a)
#define arguments_BDK_MCCX_MCIX_INT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_int_ena_w1c
 *
 * MCC Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_mccx_mcix_int_ena_w1c
{
    uint64_t u;
    struct bdk_mccx_mcix_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ded_err               : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t sec_err               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_7            : 1;
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC45]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC23]. */
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC01]. */
        uint64_t reserved_3            : 1;
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC45]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC23]. */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC01]. */
#else /* Word 0 - Little Endian */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC01]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC23]. */
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC45]. */
        uint64_t reserved_3            : 1;
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC01]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC23]. */
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC45]. */
        uint64_t reserved_7            : 1;
        uint64_t sec_err               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t ded_err               : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_int_ena_w1c_s cn; */
};
typedef union bdk_mccx_mcix_int_ena_w1c bdk_mccx_mcix_int_ena_w1c_t;

static inline uint64_t BDK_MCCX_MCIX_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400210ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_INT_ENA_W1C", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_INT_ENA_W1C(a,b) bdk_mccx_mcix_int_ena_w1c_t
#define bustype_BDK_MCCX_MCIX_INT_ENA_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_INT_ENA_W1C(a,b) "MCCX_MCIX_INT_ENA_W1C"
#define device_bar_BDK_MCCX_MCIX_INT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_INT_ENA_W1C(a,b) (a)
#define arguments_BDK_MCCX_MCIX_INT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_int_ena_w1s
 *
 * MCC Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_mccx_mcix_int_ena_w1s
{
    uint64_t u;
    struct bdk_mccx_mcix_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ded_err               : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t sec_err               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_7            : 1;
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC45]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC23]. */
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC01]. */
        uint64_t reserved_3            : 1;
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC45]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC23]. */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC01]. */
#else /* Word 0 - Little Endian */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC01]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC23]. */
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[RDDISLMC45]. */
        uint64_t reserved_3            : 1;
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC01]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC23]. */
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[WRDISLMC45]. */
        uint64_t reserved_7            : 1;
        uint64_t sec_err               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t ded_err               : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_int_ena_w1s_s cn; */
};
typedef union bdk_mccx_mcix_int_ena_w1s bdk_mccx_mcix_int_ena_w1s_t;

static inline uint64_t BDK_MCCX_MCIX_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400218ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_INT_ENA_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_INT_ENA_W1S(a,b) bdk_mccx_mcix_int_ena_w1s_t
#define bustype_BDK_MCCX_MCIX_INT_ENA_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_INT_ENA_W1S(a,b) "MCCX_MCIX_INT_ENA_W1S"
#define device_bar_BDK_MCCX_MCIX_INT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_INT_ENA_W1S(a,b) (a)
#define arguments_BDK_MCCX_MCIX_INT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_int_w1s
 *
 * MCC Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_mccx_mcix_int_w1s
{
    uint64_t u;
    struct bdk_mccx_mcix_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ded_err               : 1;  /**< [  9:  9](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t sec_err               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_7            : 1;
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[WRDISLMC45]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[WRDISLMC23]. */
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[WRDISLMC01]. */
        uint64_t reserved_3            : 1;
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[RDDISLMC45]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[RDDISLMC23]. */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[RDDISLMC01]. */
#else /* Word 0 - Little Endian */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[RDDISLMC01]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[RDDISLMC23]. */
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[RDDISLMC45]. */
        uint64_t reserved_3            : 1;
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[WRDISLMC01]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[WRDISLMC23]. */
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[WRDISLMC45]. */
        uint64_t reserved_7            : 1;
        uint64_t sec_err               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[SEC_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t ded_err               : 1;  /**< [  9:  9](R/W1S/H) Reads or sets MCC(0..1)_MCI(0..1)_INT[DED_ERR].
                                                                 Internal:
                                                                 FIXME better description once this register is fixed. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_int_w1s_s cn; */
};
typedef union bdk_mccx_mcix_int_w1s bdk_mccx_mcix_int_w1s_t;

static inline uint64_t BDK_MCCX_MCIX_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_INT_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400208ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_INT_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_INT_W1S(a,b) bdk_mccx_mcix_int_w1s_t
#define bustype_BDK_MCCX_MCIX_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_INT_W1S(a,b) "MCCX_MCIX_INT_W1S"
#define device_bar_BDK_MCCX_MCIX_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_INT_W1S(a,b) (a)
#define arguments_BDK_MCCX_MCIX_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_rddislmc_fadr
 *
 * MCC MCI Disabled LMC Read Failing Address Register
 * This register captures the first transaction with DISLMC error. It records
 * the address of the associated RD command sent that triggered the error.
 * Software must clear all MCC()_MCI()_INT[RDDISLMC*] interrupts to enable capturing the
 * next failing address.
 */
union bdk_mccx_mcix_rddislmc_fadr
{
    uint64_t u;
    struct bdk_mccx_mcix_rddislmc_fadr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_rddislmc_fadr_s cn; */
};
typedef union bdk_mccx_mcix_rddislmc_fadr bdk_mccx_mcix_rddislmc_fadr_t;

static inline uint64_t BDK_MCCX_MCIX_RDDISLMC_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RDDISLMC_FADR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400220ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_RDDISLMC_FADR", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RDDISLMC_FADR(a,b) bdk_mccx_mcix_rddislmc_fadr_t
#define bustype_BDK_MCCX_MCIX_RDDISLMC_FADR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RDDISLMC_FADR(a,b) "MCCX_MCIX_RDDISLMC_FADR"
#define device_bar_BDK_MCCX_MCIX_RDDISLMC_FADR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RDDISLMC_FADR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RDDISLMC_FADR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_sbe_dbg_cnt
 *
 * INTERNAL: MCC MCI SBE Detection Counter Registers
 *
 * This register keeps track of the number of single-bit errors arriving on the DAT
 * mesh into MCI from MSW in saturating counters. For debug purposes only - no
 * correction.
 */
union bdk_mccx_mcix_sbe_dbg_cnt
{
    uint64_t u;
    struct bdk_mccx_mcix_sbe_dbg_cnt_s
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
    /* struct bdk_mccx_mcix_sbe_dbg_cnt_s cn; */
};
typedef union bdk_mccx_mcix_sbe_dbg_cnt bdk_mccx_mcix_sbe_dbg_cnt_t;

static inline uint64_t BDK_MCCX_MCIX_SBE_DBG_CNT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_SBE_DBG_CNT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400058ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_SBE_DBG_CNT", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) bdk_mccx_mcix_sbe_dbg_cnt_t
#define bustype_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) "MCCX_MCIX_SBE_DBG_CNT"
#define device_bar_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) (a)
#define arguments_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_sec_fadr
 *
 * MCC MCI Single-bit Error Correctable Failing Address Register
 * This register captures the first Mesh write transaction with a single-bit correctable
 * data error. It records the address of the associated WR command sent that triggered the error.
 * Software must clear MCC()_MCI()_INT[SEC_ERR] interrupt to enable capturing the
 * next failing address.
 */
union bdk_mccx_mcix_sec_fadr
{
    uint64_t u;
    struct bdk_mccx_mcix_sec_fadr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_sec_fadr_s cn; */
};
typedef union bdk_mccx_mcix_sec_fadr bdk_mccx_mcix_sec_fadr_t;

static inline uint64_t BDK_MCCX_MCIX_SEC_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_SEC_FADR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400230ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_SEC_FADR", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_SEC_FADR(a,b) bdk_mccx_mcix_sec_fadr_t
#define bustype_BDK_MCCX_MCIX_SEC_FADR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_SEC_FADR(a,b) "MCCX_MCIX_SEC_FADR"
#define device_bar_BDK_MCCX_MCIX_SEC_FADR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_SEC_FADR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_SEC_FADR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_wrdislmc_fadr
 *
 * MCC MCI Disabled LMC Failing Address Register
 * This register captures the first transaction with DISLMC error. It records
 * the address of the associated WR command sent that triggered the error.
 * Software must clear all MCC()_MCI()_INT[WRDISLMC*] interrupts to enable capturing the
 * next failing address.
 */
union bdk_mccx_mcix_wrdislmc_fadr
{
    uint64_t u;
    struct bdk_mccx_mcix_wrdislmc_fadr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_wrdislmc_fadr_s cn; */
};
typedef union bdk_mccx_mcix_wrdislmc_fadr bdk_mccx_mcix_wrdislmc_fadr_t;

static inline uint64_t BDK_MCCX_MCIX_WRDISLMC_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_WRDISLMC_FADR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x87e03c400228ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_MCIX_WRDISLMC_FADR", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_WRDISLMC_FADR(a,b) bdk_mccx_mcix_wrdislmc_fadr_t
#define bustype_BDK_MCCX_MCIX_WRDISLMC_FADR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_WRDISLMC_FADR(a,b) "MCCX_MCIX_WRDISLMC_FADR"
#define device_bar_BDK_MCCX_MCIX_WRDISLMC_FADR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_WRDISLMC_FADR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_WRDISLMC_FADR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_msix_pba#
 *
 * MCC MSI-X Pending Bit Array Registers
 * This register is the MCC-X PBA table; the bit number is indexed by the MCC_INT_VEC_E enumeration.
 */
union bdk_mccx_msix_pbax
{
    uint64_t u;
    struct bdk_mccx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MCC()_MSIX_VEC()_CTL, enumerated by MCC_INT_VEC_E. Bits
                                                                 that have no associated MCC_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MCC()_MSIX_VEC()_CTL, enumerated by MCC_INT_VEC_E. Bits
                                                                 that have no associated MCC_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_msix_pbax_s cn; */
};
typedef union bdk_mccx_msix_pbax bdk_mccx_msix_pbax_t;

static inline uint64_t BDK_MCCX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b==0)))
        return 0x87e03cff0000ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MSIX_PBAX", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MSIX_PBAX(a,b) bdk_mccx_msix_pbax_t
#define bustype_BDK_MCCX_MSIX_PBAX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MSIX_PBAX(a,b) "MCCX_MSIX_PBAX"
#define device_bar_BDK_MCCX_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_MCCX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_MCCX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_msix_vec#_addr
 *
 * MCC MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the MCC_INT_VEC_E enumeration.
 */
union bdk_mccx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_mccx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MCC()_MSIX_VEC()_ADDR, MCC()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MCC()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MCC()_MSIX_VEC()_ADDR, MCC()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MCC()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_msix_vecx_addr_s cn; */
};
typedef union bdk_mccx_msix_vecx_addr bdk_mccx_msix_vecx_addr_t;

static inline uint64_t BDK_MCCX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x87e03cf00000ll + 0x1000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("MCCX_MSIX_VECX_ADDR", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MSIX_VECX_ADDR(a,b) bdk_mccx_msix_vecx_addr_t
#define bustype_BDK_MCCX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MSIX_VECX_ADDR(a,b) "MCCX_MSIX_VECX_ADDR"
#define device_bar_BDK_MCCX_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_MCCX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_MCCX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_msix_vec#_ctl
 *
 * MCC MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the MCC_INT_VEC_E enumeration.
 */
union bdk_mccx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_mccx_msix_vecx_ctl_s
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
    /* struct bdk_mccx_msix_vecx_ctl_s cn; */
};
typedef union bdk_mccx_msix_vecx_ctl bdk_mccx_msix_vecx_ctl_t;

static inline uint64_t BDK_MCCX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x87e03cf00008ll + 0x1000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("MCCX_MSIX_VECX_CTL", 2, a, b, 0, 0);
}

#define typedef_BDK_MCCX_MSIX_VECX_CTL(a,b) bdk_mccx_msix_vecx_ctl_t
#define bustype_BDK_MCCX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MSIX_VECX_CTL(a,b) "MCCX_MSIX_VECX_CTL"
#define device_bar_BDK_MCCX_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_MCCX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_MCCX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_scramble_cfg0
 *
 * MCC Scramble Configuration 0 Register
 */
union bdk_mccx_scramble_cfg0
{
    uint64_t u;
    struct bdk_mccx_scramble_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t key                   : 64; /**< [ 63:  0](R/W) Lower 64-bit scramble key for data. Prior to enabling scrambling this key should be
                                                                 generated from a cryptographically-secure random number generator such as RNM_RANDOM. */
#else /* Word 0 - Little Endian */
        uint64_t key                   : 64; /**< [ 63:  0](R/W) Lower 64-bit scramble key for data. Prior to enabling scrambling this key should be
                                                                 generated from a cryptographically-secure random number generator such as RNM_RANDOM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_scramble_cfg0_s cn; */
};
typedef union bdk_mccx_scramble_cfg0 bdk_mccx_scramble_cfg0_t;

static inline uint64_t BDK_MCCX_SCRAMBLE_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_SCRAMBLE_CFG0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e03c000070ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MCCX_SCRAMBLE_CFG0", 1, a, 0, 0, 0);
}

#define typedef_BDK_MCCX_SCRAMBLE_CFG0(a) bdk_mccx_scramble_cfg0_t
#define bustype_BDK_MCCX_SCRAMBLE_CFG0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_SCRAMBLE_CFG0(a) "MCCX_SCRAMBLE_CFG0"
#define device_bar_BDK_MCCX_SCRAMBLE_CFG0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_SCRAMBLE_CFG0(a) (a)
#define arguments_BDK_MCCX_SCRAMBLE_CFG0(a) (a),-1,-1,-1

/**
 * Register (RSL) mcc#_scramble_cfg1
 *
 * MCC Scramble Configuration 1 Register
 */
union bdk_mccx_scramble_cfg1
{
    uint64_t u;
    struct bdk_mccx_scramble_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t key                   : 64; /**< [ 63:  0](R/W) Upper 64-bit scramble key for data. Prior to enabling scrambling this key should be
                                                                 generated from a cryptographically-secure random number generator such as RNM_RANDOM. */
#else /* Word 0 - Little Endian */
        uint64_t key                   : 64; /**< [ 63:  0](R/W) Upper 64-bit scramble key for data. Prior to enabling scrambling this key should be
                                                                 generated from a cryptographically-secure random number generator such as RNM_RANDOM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_scramble_cfg1_s cn; */
};
typedef union bdk_mccx_scramble_cfg1 bdk_mccx_scramble_cfg1_t;

static inline uint64_t BDK_MCCX_SCRAMBLE_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_SCRAMBLE_CFG1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e03c000078ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MCCX_SCRAMBLE_CFG1", 1, a, 0, 0, 0);
}

#define typedef_BDK_MCCX_SCRAMBLE_CFG1(a) bdk_mccx_scramble_cfg1_t
#define bustype_BDK_MCCX_SCRAMBLE_CFG1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_SCRAMBLE_CFG1(a) "MCCX_SCRAMBLE_CFG1"
#define device_bar_BDK_MCCX_SCRAMBLE_CFG1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_SCRAMBLE_CFG1(a) (a)
#define arguments_BDK_MCCX_SCRAMBLE_CFG1(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_MCC_H__ */
