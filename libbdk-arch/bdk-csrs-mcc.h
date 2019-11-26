#ifndef __BDK_CSRS_MCC_H__
#define __BDK_CSRS_MCC_H__
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
 * OcteonTX MCC.
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
#define BDK_MCC_INT_VEC_E_LMCOEX_RAS_INT_CN96XX(a) (4 + (a))
#define BDK_MCC_INT_VEC_E_LMCOEX_RAS_INT_CN98XX(a) (5 + (a))
#define BDK_MCC_INT_VEC_E_LMCOEX_RAS_INT_CNF95XX(a) (4 + (a))
#define BDK_MCC_INT_VEC_E_LMCOEX_RAS_INT_LOKI(a) (4 + (a))
#define BDK_MCC_INT_VEC_E_MCIX_INT(a) (0 + (a))
#define BDK_MCC_INT_VEC_E_MCIX_RAS_INT_CN96XX(a) (6 + (a))
#define BDK_MCC_INT_VEC_E_MCIX_RAS_INT_CN98XX(a) (8 + (a))
#define BDK_MCC_INT_VEC_E_MCIX_RAS_INT_CNF95XX(a) (6 + (a))
#define BDK_MCC_INT_VEC_E_MCIX_RAS_INT_LOKI(a) (6 + (a))

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
        uint64_t reserved_12_63        : 52;
        uint64_t ifb_force_wait_rdrsp  : 1;  /**< [ 11: 11](R/W) For diagnostic use only. Only applicable when [RETRY_SCRUB_ENA]=0. When this
                                                                 field is one, CTL's in-flight buffer is forced to wait until the last
                                                                 read-response data tick is seen before clearing the buffer. */
        uint64_t rd_ecc_flip           : 2;  /**< [ 10:  9](R/W) Flip syndrome bits on the read response to the mesh. */
        uint64_t mci_early_crd_dis     : 1;  /**< [  8:  8](R/W) Disable early credit returns when using the scramble pipeline.
                                                                 For diagnostic use only. */
        uint64_t ctl_cclk_dis          : 1;  /**< [  7:  7](R/W) Force coarse grained conditional clocks on for CTL module.
                                                                 For diagnostic use only. */
        uint64_t mci_cclk_dis          : 1;  /**< [  6:  6](R/W) Force coarse grained conditional clocks on for MCI module.
                                                                 For diagnostic use only. */
        uint64_t early_rsp_val_ena     : 1;  /**< [  5:  5](R/W) Return DRAM response early.
                                                                 0 = Return DRAM demand read data after retries, after ECC resolution. Wait for
                                                                 all ECC correction and retries if needed before returning read data to the
                                                                 requestor.  This may improve reliability.
                                                                 1 = Return DRAM demand read data response early, before ECC resolution is known.
                                                                 This may improve performance, but if a double-bit error is detected and a retry
                                                                 of the read does not have the double-bit error, the mesh will have already
                                                                 received the (first) poisoned read data.

                                                                 This does not affect background scrubber reads. */
        uint64_t retry_scrub_ena       : 1;  /**< [  4:  4](R/W) When an ECC error occurs, write back to DRAM the corrected data. */
        uint64_t scramble_ns_ena       : 1;  /**< [  3:  3](R/W) When set, enable the scramble/descramble logic for non-secure transactions. */
        uint64_t scramble_s_ena        : 1;  /**< [  2:  2](R/W) When set, enable the scramble/descramble logic for secure transactions. */
        uint64_t dis_tadpsn            : 1;  /**< [  1:  1](R/W) When set, disable both Poison notification on incoming write data from TAD and
                                                                 poison generation on outgoing read data to the mesh. */
        uint64_t dis_tadecc            : 1;  /**< [  0:  0](R/W) When set, disable ECC correction on incoming write data from TAD. */
#else /* Word 0 - Little Endian */
        uint64_t dis_tadecc            : 1;  /**< [  0:  0](R/W) When set, disable ECC correction on incoming write data from TAD. */
        uint64_t dis_tadpsn            : 1;  /**< [  1:  1](R/W) When set, disable both Poison notification on incoming write data from TAD and
                                                                 poison generation on outgoing read data to the mesh. */
        uint64_t scramble_s_ena        : 1;  /**< [  2:  2](R/W) When set, enable the scramble/descramble logic for secure transactions. */
        uint64_t scramble_ns_ena       : 1;  /**< [  3:  3](R/W) When set, enable the scramble/descramble logic for non-secure transactions. */
        uint64_t retry_scrub_ena       : 1;  /**< [  4:  4](R/W) When an ECC error occurs, write back to DRAM the corrected data. */
        uint64_t early_rsp_val_ena     : 1;  /**< [  5:  5](R/W) Return DRAM response early.
                                                                 0 = Return DRAM demand read data after retries, after ECC resolution. Wait for
                                                                 all ECC correction and retries if needed before returning read data to the
                                                                 requestor.  This may improve reliability.
                                                                 1 = Return DRAM demand read data response early, before ECC resolution is known.
                                                                 This may improve performance, but if a double-bit error is detected and a retry
                                                                 of the read does not have the double-bit error, the mesh will have already
                                                                 received the (first) poisoned read data.

                                                                 This does not affect background scrubber reads. */
        uint64_t mci_cclk_dis          : 1;  /**< [  6:  6](R/W) Force coarse grained conditional clocks on for MCI module.
                                                                 For diagnostic use only. */
        uint64_t ctl_cclk_dis          : 1;  /**< [  7:  7](R/W) Force coarse grained conditional clocks on for CTL module.
                                                                 For diagnostic use only. */
        uint64_t mci_early_crd_dis     : 1;  /**< [  8:  8](R/W) Disable early credit returns when using the scramble pipeline.
                                                                 For diagnostic use only. */
        uint64_t rd_ecc_flip           : 2;  /**< [ 10:  9](R/W) Flip syndrome bits on the read response to the mesh. */
        uint64_t ifb_force_wait_rdrsp  : 1;  /**< [ 11: 11](R/W) For diagnostic use only. Only applicable when [RETRY_SCRUB_ENA]=0. When this
                                                                 field is one, CTL's in-flight buffer is forced to wait until the last
                                                                 read-response data tick is seen before clearing the buffer. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_config_s cn9; */
    /* struct bdk_mccx_config_s cn96xx; */
    /* struct bdk_mccx_config_s cn98xx; */
    struct bdk_mccx_config_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t ifb_force_wait_rdrsp  : 1;  /**< [ 11: 11](R/W) For diagnostic use only. Only applicable when [RETRY_SCRUB_ENA]=0. When this
                                                                 field is one, CTL's in-flight buffer is forced to wait until the last
                                                                 read-response data tick is seen before clearing the buffer. */
        uint64_t rd_ecc_flip           : 2;  /**< [ 10:  9](R/W) Flip syndrome bits on the read response to the mesh. */
        uint64_t reserved_8            : 1;
        uint64_t ctl_cclk_dis          : 1;  /**< [  7:  7](R/W) Force coarse grained conditional clocks on for CTL module.
                                                                 For diagnostic use only. */
        uint64_t mci_cclk_dis          : 1;  /**< [  6:  6](R/W) Force coarse grained conditional clocks on for MCI module.
                                                                 For diagnostic use only. */
        uint64_t early_rsp_val_ena     : 1;  /**< [  5:  5](R/W) Return DRAM response early.
                                                                 0 = Return DRAM demand read data after retries, after ECC resolution. Wait for
                                                                 all ECC correction and retries if needed before returning read data to the
                                                                 requestor.  This may improve reliability.
                                                                 1 = Return DRAM demand read data response early, before ECC resolution is known.
                                                                 This may improve performance, but if a double-bit error is detected and a retry
                                                                 of the read does not have the double-bit error, the mesh will have already
                                                                 received the (first) poisoned read data.

                                                                 This does not affect background scrubber reads. */
        uint64_t retry_scrub_ena       : 1;  /**< [  4:  4](R/W) When an ECC error occurs, write back to DRAM the corrected data. */
        uint64_t scramble_ns_ena       : 1;  /**< [  3:  3](R/W) When set, enable the scramble/descramble logic for non-secure transactions. */
        uint64_t scramble_s_ena        : 1;  /**< [  2:  2](R/W) When set, enable the scramble/descramble logic for secure transactions. */
        uint64_t dis_tadpsn            : 1;  /**< [  1:  1](R/W) When set, disable both Poison notification on incoming write data from TAD and
                                                                 poison generation on outgoing read data to the mesh. */
        uint64_t dis_tadecc            : 1;  /**< [  0:  0](R/W) When set, disable ECC correction on incoming write data from TAD. */
#else /* Word 0 - Little Endian */
        uint64_t dis_tadecc            : 1;  /**< [  0:  0](R/W) When set, disable ECC correction on incoming write data from TAD. */
        uint64_t dis_tadpsn            : 1;  /**< [  1:  1](R/W) When set, disable both Poison notification on incoming write data from TAD and
                                                                 poison generation on outgoing read data to the mesh. */
        uint64_t scramble_s_ena        : 1;  /**< [  2:  2](R/W) When set, enable the scramble/descramble logic for secure transactions. */
        uint64_t scramble_ns_ena       : 1;  /**< [  3:  3](R/W) When set, enable the scramble/descramble logic for non-secure transactions. */
        uint64_t retry_scrub_ena       : 1;  /**< [  4:  4](R/W) When an ECC error occurs, write back to DRAM the corrected data. */
        uint64_t early_rsp_val_ena     : 1;  /**< [  5:  5](R/W) Return DRAM response early.
                                                                 0 = Return DRAM demand read data after retries, after ECC resolution. Wait for
                                                                 all ECC correction and retries if needed before returning read data to the
                                                                 requestor.  This may improve reliability.
                                                                 1 = Return DRAM demand read data response early, before ECC resolution is known.
                                                                 This may improve performance, but if a double-bit error is detected and a retry
                                                                 of the read does not have the double-bit error, the mesh will have already
                                                                 received the (first) poisoned read data.

                                                                 This does not affect background scrubber reads. */
        uint64_t mci_cclk_dis          : 1;  /**< [  6:  6](R/W) Force coarse grained conditional clocks on for MCI module.
                                                                 For diagnostic use only. */
        uint64_t ctl_cclk_dis          : 1;  /**< [  7:  7](R/W) Force coarse grained conditional clocks on for CTL module.
                                                                 For diagnostic use only. */
        uint64_t reserved_8            : 1;
        uint64_t rd_ecc_flip           : 2;  /**< [ 10:  9](R/W) Flip syndrome bits on the read response to the mesh. */
        uint64_t ifb_force_wait_rdrsp  : 1;  /**< [ 11: 11](R/W) For diagnostic use only. Only applicable when [RETRY_SCRUB_ENA]=0. When this
                                                                 field is one, CTL's in-flight buffer is forced to wait until the last
                                                                 read-response data tick is seen before clearing the buffer. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_config_cnf95xx loki; */
};
typedef union bdk_mccx_config bdk_mccx_config_t;

static inline uint64_t BDK_MCCX_CONFIG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_CONFIG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e03c000060ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e03c000060ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e03c000060ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e03c000060ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("MCCX_CONFIG", 1, a, 0, 0, 0, 0, 0);
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
    /* struct bdk_mccx_const_s cn9; */
    /* struct bdk_mccx_const_s cn96xx; */
    struct bdk_mccx_const_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t lmcs                  : 8;  /**< [  7:  0](RO/H) Number of LMCs attached to corresponding MCC.
                                                                 _ MCC(0)_CONST[LMCS] = 0x3.
                                                                 _ MCC(1)_CONST[LMCS] = 0x3. */
#else /* Word 0 - Little Endian */
        uint64_t lmcs                  : 8;  /**< [  7:  0](RO/H) Number of LMCs attached to corresponding MCC.
                                                                 _ MCC(0)_CONST[LMCS] = 0x3.
                                                                 _ MCC(1)_CONST[LMCS] = 0x3. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_mccx_const_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t lmcs                  : 8;  /**< [  7:  0](RO/H) Number of LMCs attached to corresponding MCC.
                                                                 _ MCC(0)_CONST[LMCS] = 0x2. */
#else /* Word 0 - Little Endian */
        uint64_t lmcs                  : 8;  /**< [  7:  0](RO/H) Number of LMCs attached to corresponding MCC.
                                                                 _ MCC(0)_CONST[LMCS] = 0x2. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_const_cnf95xx loki; */
};
typedef union bdk_mccx_const bdk_mccx_const_t;

static inline uint64_t BDK_MCCX_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_CONST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e03c000000ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e03c000000ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e03c000000ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e03c000000ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("MCCX_CONST", 1, a, 0, 0, 0, 0, 0);
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
 * This register counts the number of clocks cycles during which MCC has in-flight transactions.
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
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e03c000040ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e03c000040ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e03c000040ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e03c000040ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("MCCX_CTL_ACTIVE_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_CTL_ACTIVE_PC(a) bdk_mccx_ctl_active_pc_t
#define bustype_BDK_MCCX_CTL_ACTIVE_PC(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_CTL_ACTIVE_PC(a) "MCCX_CTL_ACTIVE_PC"
#define device_bar_BDK_MCCX_CTL_ACTIVE_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_CTL_ACTIVE_PC(a) (a)
#define arguments_BDK_MCCX_CTL_ACTIVE_PC(a) (a),-1,-1,-1

/**
 * Register (RSL) mcc#_ctl_bp_test1
 *
 * INTERNAL: MCC CTL Backpressure Test Register
 */
union bdk_mccx_ctl_bp_test1
{
    uint64_t u;
    struct bdk_mccx_ctl_bp_test1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = When set, disables popping of Read Response to MCI1.
                                                                 \<62\> = When set, disables popping of Read Response to MCI0.
                                                                 \<61\> = When set, disables popping of Read Response from LMC1.
                                                                 \<60\> = When set, disables popping of Read Response from LMC0. */
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
                                                                 \<63\> = When set, disables popping of Read Response to MCI1.
                                                                 \<62\> = When set, disables popping of Read Response to MCI0.
                                                                 \<61\> = When set, disables popping of Read Response from LMC1.
                                                                 \<60\> = When set, disables popping of Read Response from LMC0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_ctl_bp_test1_s cn; */
};
typedef union bdk_mccx_ctl_bp_test1 bdk_mccx_ctl_bp_test1_t;

static inline uint64_t BDK_MCCX_CTL_BP_TEST1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_CTL_BP_TEST1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e03c000460ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e03c000460ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e03c000460ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e03c000460ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("MCCX_CTL_BP_TEST1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_CTL_BP_TEST1(a) bdk_mccx_ctl_bp_test1_t
#define bustype_BDK_MCCX_CTL_BP_TEST1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_CTL_BP_TEST1(a) "MCCX_CTL_BP_TEST1"
#define device_bar_BDK_MCCX_CTL_BP_TEST1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_CTL_BP_TEST1(a) (a)
#define arguments_BDK_MCCX_CTL_BP_TEST1(a) (a),-1,-1,-1

/**
 * Register (RSL) mcc#_ctl_bp_test2
 *
 * INTERNAL: MCC CTL Backpressure Test Register
 */
union bdk_mccx_ctl_bp_test2
{
    uint64_t u;
    struct bdk_mccx_ctl_bp_test2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = When set, disables popping of Read command to LMC1.
                                                                 \<62\> = When set, disables popping of Read command to LMC0.
                                                                 \<61\> = When set, disables popping of Write command to LMC1.
                                                                 \<60\> = When set, disables popping of Write command to LMC0. */
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
                                                                 \<63\> = When set, disables popping of Read command to LMC1.
                                                                 \<62\> = When set, disables popping of Read command to LMC0.
                                                                 \<61\> = When set, disables popping of Write command to LMC1.
                                                                 \<60\> = When set, disables popping of Write command to LMC0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_ctl_bp_test2_s cn; */
};
typedef union bdk_mccx_ctl_bp_test2 bdk_mccx_ctl_bp_test2_t;

static inline uint64_t BDK_MCCX_CTL_BP_TEST2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_CTL_BP_TEST2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e03c000468ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e03c000468ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e03c000468ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e03c000468ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("MCCX_CTL_BP_TEST2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_CTL_BP_TEST2(a) bdk_mccx_ctl_bp_test2_t
#define bustype_BDK_MCCX_CTL_BP_TEST2(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_CTL_BP_TEST2(a) "MCCX_CTL_BP_TEST2"
#define device_bar_BDK_MCCX_CTL_BP_TEST2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_CTL_BP_TEST2(a) (a)
#define arguments_BDK_MCCX_CTL_BP_TEST2(a) (a),-1,-1,-1

/**
 * Register (RSL) mcc#_ctl_bp_test3
 *
 * INTERNAL: MCC CTL Backpressure Test Register 3
 */
union bdk_mccx_ctl_bp_test3
{
    uint64_t u;
    struct bdk_mccx_ctl_bp_test3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = When set, disables popping of Read command to LMC2.
                                                                 \<61\> = When set, disables popping of Write command to LMC2.
                                                                 \<60\> = When set, disables popping of Read Response from LMC2. */
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
                                                                 \<62\> = When set, disables popping of Read command to LMC2.
                                                                 \<61\> = When set, disables popping of Write command to LMC2.
                                                                 \<60\> = When set, disables popping of Read Response from LMC2. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_ctl_bp_test3_s cn; */
};
typedef union bdk_mccx_ctl_bp_test3 bdk_mccx_ctl_bp_test3_t;

static inline uint64_t BDK_MCCX_CTL_BP_TEST3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_CTL_BP_TEST3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e03c000470ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MCCX_CTL_BP_TEST3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_CTL_BP_TEST3(a) bdk_mccx_ctl_bp_test3_t
#define bustype_BDK_MCCX_CTL_BP_TEST3(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_CTL_BP_TEST3(a) "MCCX_CTL_BP_TEST3"
#define device_bar_BDK_MCCX_CTL_BP_TEST3(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_CTL_BP_TEST3(a) (a)
#define arguments_BDK_MCCX_CTL_BP_TEST3(a) (a),-1,-1,-1

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
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e03c000080ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e03c000080ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e03c000080ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e03c000080ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("MCCX_ECO", 1, a, 0, 0, 0, 0, 0);
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
        uint64_t reserved_51_63        : 13;
        uint64_t start_address         : 35; /**< [ 50: 16](R/W) Specifies the start of LMCx's DRAM address range to be background scrubbed. This
                                                                 field may not be modified when [ENABLE] is already set to 1.
                                                                 Refer to the description above to get the actual LMC number. */
        uint64_t bs_idle_cnt           : 8;  /**< [ 15:  8](R/W) The idle count for which the background scrubber waits in between consecutive
                                                                 operations. Set this field as follows:
                                                                 RNDUP[wait_time(ns)/core_clock_period(ns)/256]. */
        uint64_t reserved_2_7          : 6;
        uint64_t busy                  : 1;  /**< [  1:  1](RO/H) Indicates LMCx's background scrubber is busy. */
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
        uint64_t busy                  : 1;  /**< [  1:  1](RO/H) Indicates LMCx's background scrubber is busy. */
        uint64_t reserved_2_7          : 6;
        uint64_t bs_idle_cnt           : 8;  /**< [ 15:  8](R/W) The idle count for which the background scrubber waits in between consecutive
                                                                 operations. Set this field as follows:
                                                                 RNDUP[wait_time(ns)/core_clock_period(ns)/256]. */
        uint64_t start_address         : 35; /**< [ 50: 16](R/W) Specifies the start of LMCx's DRAM address range to be background scrubbed. This
                                                                 field may not be modified when [ENABLE] is already set to 1.
                                                                 Refer to the description above to get the actual LMC number. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_bscrub_cfg_s cn; */
};
typedef union bdk_mccx_lmcoex_bscrub_cfg bdk_mccx_lmcoex_bscrub_cfg_t;

static inline uint64_t BDK_MCCX_LMCOEX_BSCRUB_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_BSCRUB_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000420ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000420ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000420ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000420ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_BSCRUB_CFG", 2, a, b, 0, 0, 0, 0);
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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000440ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000440ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000440ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000440ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_BSCRUB_CFG2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) bdk_mccx_lmcoex_bscrub_cfg2_t
#define bustype_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) "MCCX_LMCOEX_BSCRUB_CFG2"
#define device_bar_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_BSCRUB_CFG2(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_cfg
 *
 * General LMC Interface Configuration Register
 * This register controls the general configuration per LMC Interface.
 * _ MCC(0)_LMCOE(0)_* = LMC1 interface config.
 * _ MCC(0)_LMCOE(1)_* = Reserved.
 * _ MCC(1)_LMCOE(0)_* = LMC0's interface config.
 * _ MCC(1)_LMCOE(1)_* = LMC2's interface config.
 */
union bdk_mccx_lmcoex_cfg
{
    uint64_t u;
    struct bdk_mccx_lmcoex_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t dram_ecc_adr          : 1;  /**< [  1:  1](R/W) Include memory reference address in the ECC calculation when [DRAM_ECC_ENA] is set.
                                                                 0 = disabled, 1 = enabled. */
        uint64_t dram_ecc_ena          : 1;  /**< [  0:  0](R/W) ECC enable. When set, enables the 8b ECC check/correct logic.
                                                                 Set this field to 1 when the corresponding LMC()_CONFIG[ECC_ENA] is set to 1.

                                                                 0 = DQ\<71:64\> are driven to 0x0.

                                                                 1 = DQ\<71:64\> on write operations contains the ECC code generated for the 64
                                                                 bits of data which will be written in the memory. Later on read operations, used
                                                                 to check for single-bit error (which will be auto-corrected) and double-bit
                                                                 error (which will be reported).
                                                                 See MCC()_LMCOE()_RAS_INT[ERR0x]. */
#else /* Word 0 - Little Endian */
        uint64_t dram_ecc_ena          : 1;  /**< [  0:  0](R/W) ECC enable. When set, enables the 8b ECC check/correct logic.
                                                                 Set this field to 1 when the corresponding LMC()_CONFIG[ECC_ENA] is set to 1.

                                                                 0 = DQ\<71:64\> are driven to 0x0.

                                                                 1 = DQ\<71:64\> on write operations contains the ECC code generated for the 64
                                                                 bits of data which will be written in the memory. Later on read operations, used
                                                                 to check for single-bit error (which will be auto-corrected) and double-bit
                                                                 error (which will be reported).
                                                                 See MCC()_LMCOE()_RAS_INT[ERR0x]. */
        uint64_t dram_ecc_adr          : 1;  /**< [  1:  1](R/W) Include memory reference address in the ECC calculation when [DRAM_ECC_ENA] is set.
                                                                 0 = disabled, 1 = enabled. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_cfg_s cn; */
};
typedef union bdk_mccx_lmcoex_cfg bdk_mccx_lmcoex_cfg_t;

static inline uint64_t BDK_MCCX_LMCOEX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000400ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000400ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000400ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000400ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_CFG(a,b) bdk_mccx_lmcoex_cfg_t
#define bustype_BDK_MCCX_LMCOEX_CFG(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_CFG(a,b) "MCCX_LMCOEX_CFG"
#define device_bar_BDK_MCCX_LMCOEX_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_CFG(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_CFG(a,b) (a),(b),-1,-1

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
    /* struct bdk_mccx_lmcoex_const_s cn9; */
    /* struct bdk_mccx_lmcoex_const_s cn96xx; */
    struct bdk_mccx_lmcoex_const_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t lmc                   : 8;  /**< [  7:  0](RO/H) Absolute LMC number attached to this MCC/LMCOE combination.
                                                                 _ MCC(0)_LMCOE(0)_CONST[LMC] = 0x1 = LMC1.
                                                                 _ MCC(0)_LMCOE(1)_CONST[LMC] = 0x3 = LMC3.
                                                                 _ MCC(0)_LMCOE(2)_CONST[LMC] = 0x5 = LMC5.
                                                                 _ MCC(1)_LMCOE(0)_CONST[LMC] = 0x0 = LMC0.
                                                                 _ MCC(1)_LMCOE(1)_CONST[LMC] = 0x2 = LMC2.
                                                                 _ MCC(1)_LMCOE(2)_CONST[LMC] = 0x4 = LMC4. */
#else /* Word 0 - Little Endian */
        uint64_t lmc                   : 8;  /**< [  7:  0](RO/H) Absolute LMC number attached to this MCC/LMCOE combination.
                                                                 _ MCC(0)_LMCOE(0)_CONST[LMC] = 0x1 = LMC1.
                                                                 _ MCC(0)_LMCOE(1)_CONST[LMC] = 0x3 = LMC3.
                                                                 _ MCC(0)_LMCOE(2)_CONST[LMC] = 0x5 = LMC5.
                                                                 _ MCC(1)_LMCOE(0)_CONST[LMC] = 0x0 = LMC0.
                                                                 _ MCC(1)_LMCOE(1)_CONST[LMC] = 0x2 = LMC2.
                                                                 _ MCC(1)_LMCOE(2)_CONST[LMC] = 0x4 = LMC4. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_mccx_lmcoex_const_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t lmc                   : 8;  /**< [  7:  0](RO/H) Absolute LMC number attached to this MCC/LMCOE combination.
                                                                 _ MCC(0)_LMCOE(0)_CONST[LMC] = 0x0 = LMC0.
                                                                 _ MCC(0)_LMCOE(1)_CONST[LMC] = 0x2 = LMC2. */
#else /* Word 0 - Little Endian */
        uint64_t lmc                   : 8;  /**< [  7:  0](RO/H) Absolute LMC number attached to this MCC/LMCOE combination.
                                                                 _ MCC(0)_LMCOE(0)_CONST[LMC] = 0x0 = LMC0.
                                                                 _ MCC(0)_LMCOE(1)_CONST[LMC] = 0x2 = LMC2. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_lmcoex_const_cnf95xx loki; */
};
typedef union bdk_mccx_lmcoex_const bdk_mccx_lmcoex_const_t;

static inline uint64_t BDK_MCCX_LMCOEX_CONST(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_CONST(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000020ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000020ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000020ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000020ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_CONST", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_CONST(a,b) bdk_mccx_lmcoex_const_t
#define bustype_BDK_MCCX_LMCOEX_CONST(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_CONST(a,b) "MCCX_LMCOEX_CONST"
#define device_bar_BDK_MCCX_LMCOEX_CONST(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_CONST(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_CONST(a,b) (a),(b),-1,-1

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
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1C/H) When set, indicates an LMC write transaction to nonexistent memory address.
                                                                 See MCC()_LMCOE()_WRNXM_FADR for recorded read NXM address.
                                                                 Refer to the register description above to get the LMC number. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1C/H) When set, indicates an LMC read transaction to nonexistent memory address.
                                                                 See MCC()_LMCOE()_RDNXM_FADR for recorded read NXM address.
                                                                 Refer to the register description above to get the LMC number. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1C/H) When set, indicates an LMC read transaction to nonexistent memory address.
                                                                 See MCC()_LMCOE()_RDNXM_FADR for recorded read NXM address.
                                                                 Refer to the register description above to get the LMC number. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1C/H) When set, indicates an LMC write transaction to nonexistent memory address.
                                                                 See MCC()_LMCOE()_WRNXM_FADR for recorded read NXM address.
                                                                 Refer to the register description above to get the LMC number. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_int_s cn; */
};
typedef union bdk_mccx_lmcoex_int bdk_mccx_lmcoex_int_t;

static inline uint64_t BDK_MCCX_LMCOEX_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_INT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000200ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000200ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000200ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000200ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_INT", 2, a, b, 0, 0, 0, 0);
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
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_int_ena_w1c_s cn9; */
    /* struct bdk_mccx_lmcoex_int_ena_w1c_s cn96xx; */
    struct bdk_mccx_lmcoex_int_ena_w1c_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_INT[RD_NXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_INT[WR_NXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_mccx_lmcoex_int_ena_w1c_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_INT[RD_NXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_lmcoex_int_ena_w1c_cnf95xx loki; */
};
typedef union bdk_mccx_lmcoex_int_ena_w1c bdk_mccx_lmcoex_int_ena_w1c_t;

static inline uint64_t BDK_MCCX_LMCOEX_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000240ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000240ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000240ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000240ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_INT_ENA_W1C", 2, a, b, 0, 0, 0, 0);
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
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_int_ena_w1s_s cn9; */
    /* struct bdk_mccx_lmcoex_int_ena_w1s_s cn96xx; */
    struct bdk_mccx_lmcoex_int_ena_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_INT[RD_NXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_INT[WR_NXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_mccx_lmcoex_int_ena_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_INT[RD_NXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_lmcoex_int_ena_w1s_cnf95xx loki; */
};
typedef union bdk_mccx_lmcoex_int_ena_w1s bdk_mccx_lmcoex_int_ena_w1s_t;

static inline uint64_t BDK_MCCX_LMCOEX_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000260ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000260ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000260ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000260ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_INT_ENA_W1S", 2, a, b, 0, 0, 0, 0);
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
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_int_w1s_s cn9; */
    /* struct bdk_mccx_lmcoex_int_w1s_s cn96xx; */
    struct bdk_mccx_lmcoex_int_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..2)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..2)_INT[RD_NXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..2)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0..1)_LMCOE(0..2)_INT[WR_NXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_mccx_lmcoex_int_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0)_LMCOE(0..1)_INT[RD_NXM]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_nxm                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0)_LMCOE(0..1)_INT[RD_NXM]. */
        uint64_t wr_nxm                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0)_LMCOE(0..1)_INT[WR_NXM]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_lmcoex_int_w1s_cnf95xx loki; */
};
typedef union bdk_mccx_lmcoex_int_w1s bdk_mccx_lmcoex_int_w1s_t;

static inline uint64_t BDK_MCCX_LMCOEX_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000220ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000220ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000220ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000220ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_INT_W1S(a,b) bdk_mccx_lmcoex_int_w1s_t
#define bustype_BDK_MCCX_LMCOEX_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_INT_W1S(a,b) "MCCX_LMCOEX_INT_W1S"
#define device_bar_BDK_MCCX_LMCOEX_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_INT_W1S(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err00addr
 *
 * LMC RAS Error Record 00 Address Register
 * This per-record register contains the error address for those error records which
 * set MCC()_LMCOE()_RAS_ERR00STATUS[AV].
 *
 * See the individual per-record CSRs for the record-specific meaning of each field,
 * e.g. MCC()_LMCOE()_RAS_ERR00ADDR.
 */
union bdk_mccx_lmcoex_ras_err00addr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err00addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err00addr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err00addr bdk_mccx_lmcoex_ras_err00addr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010018ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010018ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010018ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010018ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR00ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR00ADDR(a,b) bdk_mccx_lmcoex_ras_err00addr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR00ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR00ADDR(a,b) "MCCX_LMCOEX_RAS_ERR00ADDR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR00ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR00ADDR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR00ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err00ctlr
 *
 * LMC RAS Error Record 00 Control Register
 * This per-record register contains enables bits for the node that writes to this record.
 * See the individual per-record CSRs for the record-specific values of each field.
 *
 * Internal:
 * If adding/removing records, update MCC()_MCI()_RAS_ERRDEVID[NUM].
 */
union bdk_mccx_lmcoex_ras_err00ctlr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err00ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](RO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](RO) Error recovery for deferred read error interrupt enable. When enabled the error
                                                                 recovery interrupt is also generated for all deferred read errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](RO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](R/W) Fault handling interrupt for corrected errors enable.
                                                                 When enabled:

                                                                 * If the node implements a corrected error counter, the fault handling interrupt
                                                                 is only generated when the counter overflows and the overflow bit is set.

                                                                 * Otherwise the fault handling interrupt is also generated for all detected
                                                                 corrected errors.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](RO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](RO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](RO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](RO) Uncorrected error reporting enable. When enabled, responses to
                                                                 transactions that detect an uncorrected error that cannot be deferred are
                                                                 signaled as a detected error (external abort).

                                                                 0 = External abort response for uncorrected errors disabled.
                                                                 1 = External abort response for uncorrected errors enabled.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t fi                    : 1;  /**< [  3:  3](R/W) Fault handling interrupt enable. When enabled the fault handling interrupt
                                                                 is generated for all detected deferred errors and uncorrected errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. The fault handling
                                                                 interrupt is never generated for consumed errors. */
        uint64_t ui                    : 1;  /**< [  2:  2](RO) Uncorrected error recovery interrupt enable. When enabled, the error
                                                                 recovery interrupt is generated for all detected uncorrected errors that are not
                                                                 deferred.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](R/W) Implementation defined.

                                                                 For CNXXXX force error.
                                                                 * For records where *_RAS_ERRn[IMP_FE] = 0x2, this bit is R/W and when set
                                                                 injects an error.
                                                                 * For other records, reserved. */
        uint64_t ed                    : 1;  /**< [  0:  0](RO) Enable error detection and correction at the node.
                                                                 0 = Error detection and correction disabled.
                                                                 1 = Error detection and correction enabled.

                                                                 For CNXXXX, all records similar.

                                                                 Internal:
                                                                 This feature is always enabled, so this field has no control. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](RO) Enable error detection and correction at the node.
                                                                 0 = Error detection and correction disabled.
                                                                 1 = Error detection and correction enabled.

                                                                 For CNXXXX, all records similar.

                                                                 Internal:
                                                                 This feature is always enabled, so this field has no control. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](R/W) Implementation defined.

                                                                 For CNXXXX force error.
                                                                 * For records where *_RAS_ERRn[IMP_FE] = 0x2, this bit is R/W and when set
                                                                 injects an error.
                                                                 * For other records, reserved. */
        uint64_t ui                    : 1;  /**< [  2:  2](RO) Uncorrected error recovery interrupt enable. When enabled, the error
                                                                 recovery interrupt is generated for all detected uncorrected errors that are not
                                                                 deferred.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t fi                    : 1;  /**< [  3:  3](R/W) Fault handling interrupt enable. When enabled the fault handling interrupt
                                                                 is generated for all detected deferred errors and uncorrected errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. The fault handling
                                                                 interrupt is never generated for consumed errors. */
        uint64_t ue                    : 1;  /**< [  4:  4](RO) Uncorrected error reporting enable. When enabled, responses to
                                                                 transactions that detect an uncorrected error that cannot be deferred are
                                                                 signaled as a detected error (external abort).

                                                                 0 = External abort response for uncorrected errors disabled.
                                                                 1 = External abort response for uncorrected errors enabled.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](RO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](RO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](RO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](R/W) Fault handling interrupt for corrected errors enable.
                                                                 When enabled:

                                                                 * If the node implements a corrected error counter, the fault handling interrupt
                                                                 is only generated when the counter overflows and the overflow bit is set.

                                                                 * Otherwise the fault handling interrupt is also generated for all detected
                                                                 corrected errors.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, SR/W.
                                                                 * For other records, always 0. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](RO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](RO) Error recovery for deferred read error interrupt enable. When enabled the error
                                                                 recovery interrupt is also generated for all deferred read errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](RO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err00ctlr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err00ctlr bdk_mccx_lmcoex_ras_err00ctlr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010008ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010008ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010008ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010008ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR00CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR00CTLR(a,b) bdk_mccx_lmcoex_ras_err00ctlr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR00CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR00CTLR(a,b) "MCCX_LMCOEX_RAS_ERR00CTLR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR00CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR00CTLR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR00CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err00fr
 *
 * LMC RAS Error Record 00 Feature Register
 * This per-record register defines which of the common architecturally-defined
 * features are implemented. and of the implemented features which are software
 * programmable.
 * See the individual per-record CSRs for the record-specific values of each field.
 *
 * Internal:
 * If adding/removing records, update MCC()_LMCOE()_RAS_ERRDEVID[NUM].
 */
union bdk_mccx_lmcoex_ras_err00fr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err00fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](RO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. *_RAS_ERRnSTATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If *_RAS_ERRnSTATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, *_RAS_ERRnSTATUS[OF] is set to 1.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t dui                   : 2;  /**< [ 17: 16](RO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](RO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cec                   : 3;  /**< [ 14: 12](RO) Indicates a standard correctable error counter mechanism in *_RAS_ERRnMISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in *_RAS_ERRnMISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in *_RAS_ERRnMISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](RO) Fault handling interrupt for corrected errors. If this feature is implemented,
                                                                 then the fault handling interrupt must be implemented.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable using ERR\<n\>CTLR.CFI.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](RO) In-band uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t fi                    : 2;  /**< [  7:  6](RO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ui                    : 2;  /**< [  5:  4](RO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](RO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Cavium force error feature is supported.
                                                                 0x3 = Reserved. */
        uint64_t ed                    : 2;  /**< [  1:  0](RO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 Internal:
                                                                 Hardcoded. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](RO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](RO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Cavium force error feature is supported.
                                                                 0x3 = Reserved. */
        uint64_t ui                    : 2;  /**< [  5:  4](RO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t fi                    : 2;  /**< [  7:  6](RO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](RO) In-band uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](RO) Fault handling interrupt for corrected errors. If this feature is implemented,
                                                                 then the fault handling interrupt must be implemented.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable using ERR\<n\>CTLR.CFI.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cec                   : 3;  /**< [ 14: 12](RO) Indicates a standard correctable error counter mechanism in *_RAS_ERRnMISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in *_RAS_ERRnMISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in *_RAS_ERRnMISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](RO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t dui                   : 2;  /**< [ 17: 16](RO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](RO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. *_RAS_ERRnSTATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If *_RAS_ERRnSTATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, *_RAS_ERRnSTATUS[OF] is set to 1.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err00fr_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_err00fr_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_err00fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](RO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. *_RAS_ERRnSTATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If *_RAS_ERRnSTATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, *_RAS_ERRnSTATUS[OF] is set to 1.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t dui                   : 2;  /**< [ 17: 16](RO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](RO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cec                   : 3;  /**< [ 14: 12](RO) Indicates a standard correctable error counter mechanism in *_RAS_ERRnMISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in *_RAS_ERRnMISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in *_RAS_ERRnMISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](RO) Fault handling interrupt for corrected errors. If this feature is implemented,
                                                                 then the fault handling interrupt must be implemented.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable using ERR\<n\>CTLR.CFI.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](RO) In-band uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t fi                    : 2;  /**< [  7:  6](RO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ui                    : 2;  /**< [  5:  4](RO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](RO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Marvell force error feature is supported.
                                                                 0x3 = Reserved. */
        uint64_t ed                    : 2;  /**< [  1:  0](RO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 Internal:
                                                                 Hardcoded. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](RO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](RO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Marvell force error feature is supported.
                                                                 0x3 = Reserved. */
        uint64_t ui                    : 2;  /**< [  5:  4](RO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t fi                    : 2;  /**< [  7:  6](RO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](RO) In-band uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](RO) Fault handling interrupt for corrected errors. If this feature is implemented,
                                                                 then the fault handling interrupt must be implemented.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable using ERR\<n\>CTLR.CFI.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cec                   : 3;  /**< [ 14: 12](RO) Indicates a standard correctable error counter mechanism in *_RAS_ERRnMISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in *_RAS_ERRnMISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in *_RAS_ERRnMISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](RO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t dui                   : 2;  /**< [ 17: 16](RO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](RO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. *_RAS_ERRnSTATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If *_RAS_ERRnSTATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, *_RAS_ERRnSTATUS[OF] is set to 1.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_err00fr_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_err00fr_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_err00fr_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_err00fr bdk_mccx_lmcoex_ras_err00fr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010000ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010000ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010000ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010000ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR00FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR00FR(a,b) bdk_mccx_lmcoex_ras_err00fr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR00FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR00FR(a,b) "MCCX_LMCOEX_RAS_ERR00FR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR00FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR00FR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR00FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err00misc0
 *
 * LMC RAS Error Record 00 Miscellaneous 0 Register
 * This register contains other record-specific information not
 * present in the corresponding status and address registers.
 *
 * Bits \<31:0\> are implementation defined; see the individual per-record CSRs for the
 * record-specific implementation-defined meaning of each field.
 */
union bdk_mccx_lmcoex_ras_err00misc0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err00misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err00misc0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err00misc0 bdk_mccx_lmcoex_ras_err00misc0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010020ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010020ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010020ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010020ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR00MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR00MISC0(a,b) bdk_mccx_lmcoex_ras_err00misc0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR00MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR00MISC0(a,b) "MCCX_LMCOEX_RAS_ERR00MISC0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR00MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR00MISC0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR00MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err00misc1
 *
 * LMC RAS Error Record 00 Miscellaneous 1 Register
 * This register contains other record-specific implementation-defined information not
 * present in the corresponding status and address registers.
 *
 * See the individual per-record CSRs for the record-specific implementation-defined
 * meaning of each field.
 */
union bdk_mccx_lmcoex_ras_err00misc1
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err00misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err00misc1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err00misc1 bdk_mccx_lmcoex_ras_err00misc1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010028ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010028ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010028ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010028ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR00MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR00MISC1(a,b) bdk_mccx_lmcoex_ras_err00misc1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR00MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR00MISC1(a,b) "MCCX_LMCOEX_RAS_ERR00MISC1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR00MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR00MISC1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR00MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err00status
 *
 * LMC RAS Error Record 00 Primary Syndrome Register
 * This per-record register contains the error record. After reading the status
 * register, software must clear the valid bits to allow new errors to be recorded.
 * See the individual per-record CSRs for the record-specific values of each field.
 */
union bdk_mccx_lmcoex_ras_err00status
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err00status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err00status_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_err00status_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_err00status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_err00status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_err00status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_err00status_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_err00status bdk_mccx_lmcoex_ras_err00status_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR00STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010010ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010010ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010010ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010010ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR00STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR00STATUS(a,b) bdk_mccx_lmcoex_ras_err00status_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR00STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR00STATUS(a,b) "MCCX_LMCOEX_RAS_ERR00STATUS"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR00STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR00STATUS(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR00STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err01addr
 *
 * LMC RAS Error Record 01 Address Register
 * See MCC()_LMCOE()_RAS_ERR00ADDR.
 */
union bdk_mccx_lmcoex_ras_err01addr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err01addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err01addr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err01addr bdk_mccx_lmcoex_ras_err01addr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010058ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010058ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010058ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010058ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR01ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR01ADDR(a,b) bdk_mccx_lmcoex_ras_err01addr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR01ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR01ADDR(a,b) "MCCX_LMCOEX_RAS_ERR01ADDR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR01ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR01ADDR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR01ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err01ctlr
 *
 * LMC RAS Error Record 01 Control Register
 * See MCC()_LMCOE()_RAS_ERR00CTLR.
 * Internal:
 * Only ERR00CTLR is necessary to describe the node.
 */
union bdk_mccx_lmcoex_ras_err01ctlr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err01ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err01ctlr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err01ctlr bdk_mccx_lmcoex_ras_err01ctlr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010048ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010048ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010048ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010048ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR01CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR01CTLR(a,b) bdk_mccx_lmcoex_ras_err01ctlr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR01CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR01CTLR(a,b) "MCCX_LMCOEX_RAS_ERR01CTLR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR01CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR01CTLR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR01CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err01fr
 *
 * LMC RAS Error Record 01 Feature Register
 * See MCC()_LMCOE()_RAS_ERR00FR.
 * Internal:
 * Only ERR00FR is necessary to describe the node.
 */
union bdk_mccx_lmcoex_ras_err01fr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err01fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err01fr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err01fr bdk_mccx_lmcoex_ras_err01fr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010040ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010040ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010040ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010040ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR01FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR01FR(a,b) bdk_mccx_lmcoex_ras_err01fr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR01FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR01FR(a,b) "MCCX_LMCOEX_RAS_ERR01FR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR01FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR01FR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR01FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err01misc0
 *
 * LMC RAS Error Record 01 Miscellaneous 0 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC0.
 */
union bdk_mccx_lmcoex_ras_err01misc0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err01misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err01misc0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err01misc0 bdk_mccx_lmcoex_ras_err01misc0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010060ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010060ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010060ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010060ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR01MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR01MISC0(a,b) bdk_mccx_lmcoex_ras_err01misc0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR01MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR01MISC0(a,b) "MCCX_LMCOEX_RAS_ERR01MISC0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR01MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR01MISC0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR01MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err01misc1
 *
 * LMC RAS Error Record 01 Miscellaneous 1 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC1.
 */
union bdk_mccx_lmcoex_ras_err01misc1
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err01misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err01misc1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err01misc1 bdk_mccx_lmcoex_ras_err01misc1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010068ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010068ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010068ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010068ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR01MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR01MISC1(a,b) bdk_mccx_lmcoex_ras_err01misc1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR01MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR01MISC1(a,b) "MCCX_LMCOEX_RAS_ERR01MISC1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR01MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR01MISC1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR01MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err01status
 *
 * LMC RAS Error Record 01 Primary Syndrome Register
 * See MCC()_LMCOE()_RAS_ERR00STATUS.
 */
union bdk_mccx_lmcoex_ras_err01status
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err01status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err01status_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_err01status_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_err01status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_err01status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_err01status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_err01status_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_err01status bdk_mccx_lmcoex_ras_err01status_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR01STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010050ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010050ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010050ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010050ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR01STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR01STATUS(a,b) bdk_mccx_lmcoex_ras_err01status_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR01STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR01STATUS(a,b) "MCCX_LMCOEX_RAS_ERR01STATUS"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR01STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR01STATUS(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR01STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err02addr
 *
 * LMC RAS Error record 02 Address Register
 * See MCC()_LMCOE()_RAS_ERR00ADDR.
 */
union bdk_mccx_lmcoex_ras_err02addr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err02addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err02addr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err02addr bdk_mccx_lmcoex_ras_err02addr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010098ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010098ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010098ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010098ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR02ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR02ADDR(a,b) bdk_mccx_lmcoex_ras_err02addr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR02ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR02ADDR(a,b) "MCCX_LMCOEX_RAS_ERR02ADDR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR02ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR02ADDR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR02ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err02ctlr
 *
 * LMC RAS Error record 02 Control Register
 * See MCC()_LMCOE()_RAS_ERR00CTLR.
 */
union bdk_mccx_lmcoex_ras_err02ctlr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err02ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err02ctlr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err02ctlr bdk_mccx_lmcoex_ras_err02ctlr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010088ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010088ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010088ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010088ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR02CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR02CTLR(a,b) bdk_mccx_lmcoex_ras_err02ctlr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR02CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR02CTLR(a,b) "MCCX_LMCOEX_RAS_ERR02CTLR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR02CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR02CTLR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR02CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err02fr
 *
 * LMC RAS Error record 02 Feature Register
 * See MCC()_LMCOE()_RAS_ERR00FR.
 */
union bdk_mccx_lmcoex_ras_err02fr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err02fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err02fr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err02fr bdk_mccx_lmcoex_ras_err02fr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010080ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010080ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010080ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010080ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR02FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR02FR(a,b) bdk_mccx_lmcoex_ras_err02fr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR02FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR02FR(a,b) "MCCX_LMCOEX_RAS_ERR02FR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR02FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR02FR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR02FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err02misc0
 *
 * LMC RAS Error record 02 Miscellaneous 0 Register
 * No Miscellaneous register support for ECC Deferred error.
 */
union bdk_mccx_lmcoex_ras_err02misc0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err02misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err02misc0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err02misc0 bdk_mccx_lmcoex_ras_err02misc0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0100a0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0100a0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0100a0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0100a0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR02MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR02MISC0(a,b) bdk_mccx_lmcoex_ras_err02misc0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR02MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR02MISC0(a,b) "MCCX_LMCOEX_RAS_ERR02MISC0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR02MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR02MISC0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR02MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err02misc1
 *
 * LMC RAS Error record 02 Miscellaneous 1 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC1.
 */
union bdk_mccx_lmcoex_ras_err02misc1
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err02misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err02misc1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err02misc1 bdk_mccx_lmcoex_ras_err02misc1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0100a8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0100a8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0100a8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0100a8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR02MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR02MISC1(a,b) bdk_mccx_lmcoex_ras_err02misc1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR02MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR02MISC1(a,b) "MCCX_LMCOEX_RAS_ERR02MISC1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR02MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR02MISC1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR02MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err02status
 *
 * LMC RAS Error record 02 Primary Syndrome Register
 * See MCC()_LMCOE()_RAS_ERR00STATUS.
 */
union bdk_mccx_lmcoex_ras_err02status
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err02status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err02status_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_err02status_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_err02status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_err02status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_err02status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_err02status_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_err02status bdk_mccx_lmcoex_ras_err02status_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR02STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010090ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010090ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010090ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010090ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR02STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR02STATUS(a,b) bdk_mccx_lmcoex_ras_err02status_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR02STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR02STATUS(a,b) "MCCX_LMCOEX_RAS_ERR02STATUS"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR02STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR02STATUS(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR02STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err03addr
 *
 * LMC RAS Error record 03 Address Register
 * See MCC()_LMCOE()_RAS_ERR00ADDR.
 */
union bdk_mccx_lmcoex_ras_err03addr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err03addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err03addr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err03addr bdk_mccx_lmcoex_ras_err03addr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0100d8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0100d8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0100d8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0100d8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR03ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR03ADDR(a,b) bdk_mccx_lmcoex_ras_err03addr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR03ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR03ADDR(a,b) "MCCX_LMCOEX_RAS_ERR03ADDR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR03ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR03ADDR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR03ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err03ctlr
 *
 * LMC RAS Error record 03 Control Register
 * See MCC()_LMCOE()_RAS_ERR00CTLR.
 */
union bdk_mccx_lmcoex_ras_err03ctlr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err03ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err03ctlr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err03ctlr bdk_mccx_lmcoex_ras_err03ctlr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0100c8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0100c8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0100c8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0100c8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR03CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR03CTLR(a,b) bdk_mccx_lmcoex_ras_err03ctlr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR03CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR03CTLR(a,b) "MCCX_LMCOEX_RAS_ERR03CTLR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR03CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR03CTLR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR03CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err03fr
 *
 * LMC RAS Error record 03 Feature Register
 * See MCC()_LMCOE()_RAS_ERR00FR.
 */
union bdk_mccx_lmcoex_ras_err03fr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err03fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err03fr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err03fr bdk_mccx_lmcoex_ras_err03fr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0100c0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0100c0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0100c0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0100c0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR03FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR03FR(a,b) bdk_mccx_lmcoex_ras_err03fr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR03FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR03FR(a,b) "MCCX_LMCOEX_RAS_ERR03FR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR03FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR03FR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR03FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err03misc0
 *
 * LMC RAS Error record 03 Miscellaneous 0 Register
 * No miscellaneous register support for uncorrectable non-deferred error.
 */
union bdk_mccx_lmcoex_ras_err03misc0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err03misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err03misc0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err03misc0 bdk_mccx_lmcoex_ras_err03misc0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0100e0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0100e0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0100e0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0100e0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR03MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR03MISC0(a,b) bdk_mccx_lmcoex_ras_err03misc0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR03MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR03MISC0(a,b) "MCCX_LMCOEX_RAS_ERR03MISC0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR03MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR03MISC0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR03MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err03misc1
 *
 * LMC RAS Error record 03 Miscellaneous 1 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC1.
 */
union bdk_mccx_lmcoex_ras_err03misc1
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err03misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err03misc1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err03misc1 bdk_mccx_lmcoex_ras_err03misc1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0100e8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0100e8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0100e8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0100e8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR03MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR03MISC1(a,b) bdk_mccx_lmcoex_ras_err03misc1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR03MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR03MISC1(a,b) "MCCX_LMCOEX_RAS_ERR03MISC1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR03MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR03MISC1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR03MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err03status
 *
 * LMC RAS Error record 03 Primary Syndrome Register
 * See MCC()_LMCOE()_RAS_ERR00STATUS.
 */
union bdk_mccx_lmcoex_ras_err03status
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err03status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err03status_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_err03status_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_err03status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_err03status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_err03status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_err03status_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_err03status bdk_mccx_lmcoex_ras_err03status_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR03STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0100d0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0100d0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0100d0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0100d0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR03STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR03STATUS(a,b) bdk_mccx_lmcoex_ras_err03status_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR03STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR03STATUS(a,b) "MCCX_LMCOEX_RAS_ERR03STATUS"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR03STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR03STATUS(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR03STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err04addr
 *
 * LMC RAS Error record 04 Address Register
 * See MCC()_LMCOE()_RAS_ERR00ADDR.
 */
union bdk_mccx_lmcoex_ras_err04addr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err04addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err04addr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err04addr bdk_mccx_lmcoex_ras_err04addr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010118ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010118ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010118ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010118ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR04ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR04ADDR(a,b) bdk_mccx_lmcoex_ras_err04addr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR04ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR04ADDR(a,b) "MCCX_LMCOEX_RAS_ERR04ADDR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR04ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR04ADDR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR04ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err04ctlr
 *
 * LMC RAS Error record 04 Control Register
 * See MCC()_LMCOE()_RAS_ERR00CTLR.
 */
union bdk_mccx_lmcoex_ras_err04ctlr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err04ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err04ctlr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err04ctlr bdk_mccx_lmcoex_ras_err04ctlr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010108ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010108ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010108ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010108ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR04CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR04CTLR(a,b) bdk_mccx_lmcoex_ras_err04ctlr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR04CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR04CTLR(a,b) "MCCX_LMCOEX_RAS_ERR04CTLR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR04CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR04CTLR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR04CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err04fr
 *
 * LMC RAS Error record 04 Feature Register
 * See MCC()_LMCOE()_RAS_ERR00FR.
 */
union bdk_mccx_lmcoex_ras_err04fr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err04fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err04fr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err04fr bdk_mccx_lmcoex_ras_err04fr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010100ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010100ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010100ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010100ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR04FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR04FR(a,b) bdk_mccx_lmcoex_ras_err04fr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR04FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR04FR(a,b) "MCCX_LMCOEX_RAS_ERR04FR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR04FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR04FR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR04FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err04misc0
 *
 * LMC RAS Error record 04 Miscellaneous 0 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC0.
 */
union bdk_mccx_lmcoex_ras_err04misc0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err04misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err04misc0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err04misc0 bdk_mccx_lmcoex_ras_err04misc0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010120ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010120ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010120ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010120ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR04MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR04MISC0(a,b) bdk_mccx_lmcoex_ras_err04misc0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR04MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR04MISC0(a,b) "MCCX_LMCOEX_RAS_ERR04MISC0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR04MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR04MISC0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR04MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err04misc1
 *
 * LMC RAS Error record 04 Miscellaneous 1 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC1.
 */
union bdk_mccx_lmcoex_ras_err04misc1
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err04misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err04misc1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err04misc1 bdk_mccx_lmcoex_ras_err04misc1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010128ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010128ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010128ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010128ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR04MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR04MISC1(a,b) bdk_mccx_lmcoex_ras_err04misc1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR04MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR04MISC1(a,b) "MCCX_LMCOEX_RAS_ERR04MISC1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR04MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR04MISC1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR04MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err04status
 *
 * LMC RAS Error record 04 Primary Syndrome Register
 * See MCC()_LMCOE()_RAS_ERR00STATUS.
 */
union bdk_mccx_lmcoex_ras_err04status
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err04status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err04status_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_err04status_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_err04status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_err04status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_err04status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_err04status_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_err04status bdk_mccx_lmcoex_ras_err04status_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR04STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010110ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010110ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010110ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010110ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR04STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR04STATUS(a,b) bdk_mccx_lmcoex_ras_err04status_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR04STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR04STATUS(a,b) "MCCX_LMCOEX_RAS_ERR04STATUS"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR04STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR04STATUS(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR04STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err05addr
 *
 * LMC RAS Error record 05 Address Register
 * See MCC()_LMCOE()_RAS_ERR00ADDR.
 */
union bdk_mccx_lmcoex_ras_err05addr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err05addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err05addr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err05addr bdk_mccx_lmcoex_ras_err05addr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010158ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010158ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010158ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010158ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR05ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR05ADDR(a,b) bdk_mccx_lmcoex_ras_err05addr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR05ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR05ADDR(a,b) "MCCX_LMCOEX_RAS_ERR05ADDR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR05ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR05ADDR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR05ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err05ctlr
 *
 * LMC RAS Error record 05 Control Register
 * See MCC()_LMCOE()_RAS_ERR00CTLR.
 */
union bdk_mccx_lmcoex_ras_err05ctlr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err05ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err05ctlr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err05ctlr bdk_mccx_lmcoex_ras_err05ctlr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010148ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010148ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010148ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010148ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR05CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR05CTLR(a,b) bdk_mccx_lmcoex_ras_err05ctlr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR05CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR05CTLR(a,b) "MCCX_LMCOEX_RAS_ERR05CTLR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR05CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR05CTLR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR05CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err05fr
 *
 * LMC RAS Error record 05 Feature Register
 * See MCC()_LMCOE()_RAS_ERR00FR.
 */
union bdk_mccx_lmcoex_ras_err05fr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err05fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err05fr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err05fr bdk_mccx_lmcoex_ras_err05fr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010140ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010140ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010140ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010140ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR05FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR05FR(a,b) bdk_mccx_lmcoex_ras_err05fr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR05FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR05FR(a,b) "MCCX_LMCOEX_RAS_ERR05FR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR05FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR05FR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR05FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err05misc0
 *
 * LMC RAS Error record 05 Miscellaneous 0 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC0.
 */
union bdk_mccx_lmcoex_ras_err05misc0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err05misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err05misc0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err05misc0 bdk_mccx_lmcoex_ras_err05misc0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010160ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010160ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010160ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010160ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR05MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR05MISC0(a,b) bdk_mccx_lmcoex_ras_err05misc0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR05MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR05MISC0(a,b) "MCCX_LMCOEX_RAS_ERR05MISC0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR05MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR05MISC0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR05MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err05misc1
 *
 * LMC RAS Error record 05 Miscellaneous 1 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC1.
 */
union bdk_mccx_lmcoex_ras_err05misc1
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err05misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err05misc1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err05misc1 bdk_mccx_lmcoex_ras_err05misc1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010168ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010168ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010168ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010168ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR05MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR05MISC1(a,b) bdk_mccx_lmcoex_ras_err05misc1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR05MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR05MISC1(a,b) "MCCX_LMCOEX_RAS_ERR05MISC1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR05MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR05MISC1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR05MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err05status
 *
 * LMC RAS Error record 05 Primary Syndrome Register
 * See MCC()_LMCOE()_RAS_ERR00STATUS.
 */
union bdk_mccx_lmcoex_ras_err05status
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err05status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err05status_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_err05status_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_err05status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_err05status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_err05status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_err05status_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_err05status bdk_mccx_lmcoex_ras_err05status_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR05STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010150ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010150ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010150ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010150ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR05STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR05STATUS(a,b) bdk_mccx_lmcoex_ras_err05status_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR05STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR05STATUS(a,b) "MCCX_LMCOEX_RAS_ERR05STATUS"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR05STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR05STATUS(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR05STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err06addr
 *
 * LMC RAS Error record 06 Address Register
 * See MCC()_LMCOE()_RAS_ERR00ADDR.
 */
union bdk_mccx_lmcoex_ras_err06addr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err06addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err06addr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err06addr bdk_mccx_lmcoex_ras_err06addr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010198ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010198ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010198ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010198ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR06ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR06ADDR(a,b) bdk_mccx_lmcoex_ras_err06addr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR06ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR06ADDR(a,b) "MCCX_LMCOEX_RAS_ERR06ADDR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR06ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR06ADDR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR06ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err06ctlr
 *
 * LMC RAS Error record 06 Control Register
 * See MCC()_LMCOE()_RAS_ERR00CTLR.
 */
union bdk_mccx_lmcoex_ras_err06ctlr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err06ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err06ctlr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err06ctlr bdk_mccx_lmcoex_ras_err06ctlr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010188ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010188ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010188ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010188ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR06CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR06CTLR(a,b) bdk_mccx_lmcoex_ras_err06ctlr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR06CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR06CTLR(a,b) "MCCX_LMCOEX_RAS_ERR06CTLR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR06CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR06CTLR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR06CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err06fr
 *
 * LMC RAS Error record 06 Feature Register
 * See MCC()_LMCOE()_RAS_ERR00FR.
 */
union bdk_mccx_lmcoex_ras_err06fr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err06fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err06fr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err06fr bdk_mccx_lmcoex_ras_err06fr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010180ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010180ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010180ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010180ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR06FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR06FR(a,b) bdk_mccx_lmcoex_ras_err06fr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR06FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR06FR(a,b) "MCCX_LMCOEX_RAS_ERR06FR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR06FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR06FR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR06FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err06misc0
 *
 * LMC RAS Error record 06 Miscellaneous 0 Register
 * No miscellaneous register support for scrubber ECC deferred error.
 */
union bdk_mccx_lmcoex_ras_err06misc0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err06misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err06misc0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err06misc0 bdk_mccx_lmcoex_ras_err06misc0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0101a0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0101a0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0101a0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0101a0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR06MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR06MISC0(a,b) bdk_mccx_lmcoex_ras_err06misc0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR06MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR06MISC0(a,b) "MCCX_LMCOEX_RAS_ERR06MISC0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR06MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR06MISC0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR06MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err06misc1
 *
 * LMC RAS Error record 06 Miscellaneous 1 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC1.
 */
union bdk_mccx_lmcoex_ras_err06misc1
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err06misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err06misc1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err06misc1 bdk_mccx_lmcoex_ras_err06misc1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0101a8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0101a8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0101a8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0101a8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR06MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR06MISC1(a,b) bdk_mccx_lmcoex_ras_err06misc1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR06MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR06MISC1(a,b) "MCCX_LMCOEX_RAS_ERR06MISC1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR06MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR06MISC1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR06MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err06status
 *
 * LMC RAS Error record 06 Primary Syndrome Register
 * See MCC()_LMCOE()_RAS_ERR00STATUS.
 */
union bdk_mccx_lmcoex_ras_err06status
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err06status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err06status_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_err06status_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_err06status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_err06status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_err06status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_err06status_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_err06status bdk_mccx_lmcoex_ras_err06status_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR06STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010190ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010190ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010190ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010190ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR06STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR06STATUS(a,b) bdk_mccx_lmcoex_ras_err06status_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR06STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR06STATUS(a,b) "MCCX_LMCOEX_RAS_ERR06STATUS"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR06STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR06STATUS(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR06STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err07addr
 *
 * LMC RAS Error record 07 Address Register
 * See MCC()_LMCOE()_RAS_ERR00ADDR.
 */
union bdk_mccx_lmcoex_ras_err07addr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err07addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](RO/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:48] = 0x0.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address
                                                                 that is known to match the programmers' view of the physical address for the
                                                                 recorded location. The possible values of this bit are:
                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not match
                                                                     the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:
                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the Non
                                                                     secure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view
                                                                     of the Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](RO/H) Non-secure attribute. The possible values of this bit are:
                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err07addr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err07addr bdk_mccx_lmcoex_ras_err07addr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0101d8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0101d8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0101d8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0101d8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR07ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR07ADDR(a,b) bdk_mccx_lmcoex_ras_err07addr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR07ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR07ADDR(a,b) "MCCX_LMCOEX_RAS_ERR07ADDR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR07ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR07ADDR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR07ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err07ctlr
 *
 * LMC RAS Error record 07 Control Register
 * See MCC()_LMCOE()_RAS_ERR00CTLR.
 */
union bdk_mccx_lmcoex_ras_err07ctlr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err07ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err07ctlr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err07ctlr bdk_mccx_lmcoex_ras_err07ctlr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0101c8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0101c8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0101c8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0101c8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR07CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR07CTLR(a,b) bdk_mccx_lmcoex_ras_err07ctlr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR07CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR07CTLR(a,b) "MCCX_LMCOEX_RAS_ERR07CTLR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR07CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR07CTLR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR07CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err07fr
 *
 * LMC RAS Error record 07 Feature Register
 * See MCC()_LMCOE()_RAS_ERR00FR.
 */
union bdk_mccx_lmcoex_ras_err07fr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err07fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err07fr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err07fr bdk_mccx_lmcoex_ras_err07fr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0101c0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0101c0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0101c0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0101c0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR07FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR07FR(a,b) bdk_mccx_lmcoex_ras_err07fr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR07FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR07FR(a,b) "MCCX_LMCOEX_RAS_ERR07FR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR07FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR07FR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR07FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err07misc0
 *
 * LMC RAS Error record 07 Miscellaneous 0 Register
 * No Miscellaneous register support for scrubber ECC uncorrectable nondeferred error.
 */
union bdk_mccx_lmcoex_ras_err07misc0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err07misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err07misc0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err07misc0 bdk_mccx_lmcoex_ras_err07misc0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0101e0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0101e0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0101e0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0101e0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR07MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR07MISC0(a,b) bdk_mccx_lmcoex_ras_err07misc0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR07MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR07MISC0(a,b) "MCCX_LMCOEX_RAS_ERR07MISC0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR07MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR07MISC0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR07MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err07misc1
 *
 * LMC RAS Error record 07 Miscellaneous 1 Register
 * See MCC()_LMCOE()_RAS_ERR00MISC1.
 */
union bdk_mccx_lmcoex_ras_err07misc1
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err07misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t synd                  : 64; /**< [ 63:  0](R/W/H) ECC failed syndrome register. Only valid when MCC()_LMCOE()_RAS_ERR00STATUS.MV
                                                                 field is 1. Software is responsible to clear the
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS.MV field to 1 in order for a new failed syndrome
                                                                 to be loaded in the event of SBE.
                                                                 The 64-bit SYND represents 16 8-bits syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err07misc1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_err07misc1 bdk_mccx_lmcoex_ras_err07misc1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0101e8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0101e8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0101e8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0101e8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR07MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR07MISC1(a,b) bdk_mccx_lmcoex_ras_err07misc1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR07MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR07MISC1(a,b) "MCCX_LMCOEX_RAS_ERR07MISC1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR07MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR07MISC1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR07MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_err07status
 *
 * LMC RAS Error record 07 Primary Syndrome Register
 * See MCC()_LMCOE()_RAS_ERR00STATUS.
 */
union bdk_mccx_lmcoex_ras_err07status
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_err07status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_err07status_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_err07status_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_err07status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid. *_RAS_ERRn_STATUS valid. At least one error
                                                                 has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnSTATUS contains a physical address
                                                                 associated with the highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_err07status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_err07status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_err07status_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_err07status bdk_mccx_lmcoex_ras_err07status_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERR07STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0101d0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0101d0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0101d0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0101d0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERR07STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERR07STATUS(a,b) bdk_mccx_lmcoex_ras_err07status_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERR07STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERR07STATUS(a,b) "MCCX_LMCOEX_RAS_ERR07STATUS"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERR07STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERR07STATUS(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERR07STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errcidr0
 *
 * LMC RAS Component Identification Register 0
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errcidr0
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errcidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errcidr0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errcidr0 bdk_mccx_lmcoex_ras_errcidr0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRCIDR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRCIDR0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010ff0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010ff0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010ff0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010ff0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRCIDR0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRCIDR0(a,b) bdk_mccx_lmcoex_ras_errcidr0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRCIDR0(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRCIDR0(a,b) "MCCX_LMCOEX_RAS_ERRCIDR0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRCIDR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRCIDR0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRCIDR0(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errcidr1
 *
 * LMC RAS Component Identification Register 1
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errcidr1
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errcidr1_s
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
    /* struct bdk_mccx_lmcoex_ras_errcidr1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errcidr1 bdk_mccx_lmcoex_ras_errcidr1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRCIDR1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRCIDR1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010ff4ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010ff4ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010ff4ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010ff4ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRCIDR1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRCIDR1(a,b) bdk_mccx_lmcoex_ras_errcidr1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRCIDR1(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRCIDR1(a,b) "MCCX_LMCOEX_RAS_ERRCIDR1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRCIDR1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRCIDR1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRCIDR1(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errcidr2
 *
 * LMC RAS Component Identification Register 2
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errcidr2
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errcidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errcidr2_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errcidr2 bdk_mccx_lmcoex_ras_errcidr2_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRCIDR2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRCIDR2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010ff8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010ff8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010ff8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010ff8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRCIDR2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRCIDR2(a,b) bdk_mccx_lmcoex_ras_errcidr2_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRCIDR2(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRCIDR2(a,b) "MCCX_LMCOEX_RAS_ERRCIDR2"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRCIDR2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRCIDR2(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRCIDR2(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errcidr3
 *
 * LMC RAS Component Identification Register 3
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errcidr3
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errcidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errcidr3_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errcidr3 bdk_mccx_lmcoex_ras_errcidr3_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRCIDR3(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRCIDR3(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010ffcll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010ffcll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010ffcll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010ffcll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRCIDR3", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRCIDR3(a,b) bdk_mccx_lmcoex_ras_errcidr3_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRCIDR3(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRCIDR3(a,b) "MCCX_LMCOEX_RAS_ERRCIDR3"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRCIDR3(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRCIDR3(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRCIDR3(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_errdevaff
 *
 * LMC RAS Device Affinity Register
 * For a group that has an affinity to a PE or cluster of PEs, this register is a
 * read-only copy of AP_MPIDR_EL1.
 */
union bdk_mccx_lmcoex_ras_errdevaff
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_errdevaff_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t aff3                  : 8;  /**< [ 39: 32](RO) Reserved. */
        uint64_t fov                   : 1;  /**< [ 31: 31](RO) If set, the [AFF0] fields are valid.
                                                                 For noncore RAS blocks, this is zero and all other fields are zero. */
        uint64_t u                     : 1;  /**< [ 30: 30](RO) Set to indicate processor is part of a multiprocessor system. */
        uint64_t reserved_25_29        : 5;
        uint64_t mt                    : 1;  /**< [ 24: 24](RO) Set to indicate multithreaded, and [AFF0] is thread number in core. */
        uint64_t aff2                  : 8;  /**< [ 23: 16](RO) Affinity 2. In CNXXXX, the node id. */
        uint64_t aff1                  : 8;  /**< [ 15:  8](RO) Affinity 1. In CNXXXX, the cluster id within a node. */
        uint64_t aff0                  : 8;  /**< [  7:  0](RO) Affinity 0. In CNXXXX, the core number within a cluster. */
#else /* Word 0 - Little Endian */
        uint64_t aff0                  : 8;  /**< [  7:  0](RO) Affinity 0. In CNXXXX, the core number within a cluster. */
        uint64_t aff1                  : 8;  /**< [ 15:  8](RO) Affinity 1. In CNXXXX, the cluster id within a node. */
        uint64_t aff2                  : 8;  /**< [ 23: 16](RO) Affinity 2. In CNXXXX, the node id. */
        uint64_t mt                    : 1;  /**< [ 24: 24](RO) Set to indicate multithreaded, and [AFF0] is thread number in core. */
        uint64_t reserved_25_29        : 5;
        uint64_t u                     : 1;  /**< [ 30: 30](RO) Set to indicate processor is part of a multiprocessor system. */
        uint64_t fov                   : 1;  /**< [ 31: 31](RO) If set, the [AFF0] fields are valid.
                                                                 For noncore RAS blocks, this is zero and all other fields are zero. */
        uint64_t aff3                  : 8;  /**< [ 39: 32](RO) Reserved. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errdevaff_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errdevaff bdk_mccx_lmcoex_ras_errdevaff_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRDEVAFF(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRDEVAFF(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fa8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fa8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fa8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fa8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRDEVAFF", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRDEVAFF(a,b) bdk_mccx_lmcoex_ras_errdevaff_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRDEVAFF(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERRDEVAFF(a,b) "MCCX_LMCOEX_RAS_ERRDEVAFF"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRDEVAFF(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRDEVAFF(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRDEVAFF(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errdevarch
 *
 * LMC_RAS Device Architecture Register
 * This register identifies the programmers' model architecture of the component.
 */
union bdk_mccx_lmcoex_ras_errdevarch
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errdevarch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. Indicates ARM. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to 1, indicates that this register is present. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archver               : 4;  /**< [ 15: 12](RO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archpart              : 12; /**< [ 11:  0](RO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
#else /* Word 0 - Little Endian */
        uint32_t archpart              : 12; /**< [ 11:  0](RO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
        uint32_t archver               : 4;  /**< [ 15: 12](RO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to 1, indicates that this register is present. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. Indicates ARM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errdevarch_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_errdevarch_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_errdevarch_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. Indicates Arm. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to 1, indicates that this register is present. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archver               : 4;  /**< [ 15: 12](RO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archpart              : 12; /**< [ 11:  0](RO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
#else /* Word 0 - Little Endian */
        uint32_t archpart              : 12; /**< [ 11:  0](RO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
        uint32_t archver               : 4;  /**< [ 15: 12](RO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to 1, indicates that this register is present. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. Indicates Arm. */
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_lmcoex_ras_errdevarch_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_errdevarch_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_errdevarch_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_errdevarch bdk_mccx_lmcoex_ras_errdevarch_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRDEVARCH(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRDEVARCH(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fbcll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fbcll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fbcll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fbcll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRDEVARCH", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRDEVARCH(a,b) bdk_mccx_lmcoex_ras_errdevarch_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRDEVARCH(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRDEVARCH(a,b) "MCCX_LMCOEX_RAS_ERRDEVARCH"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRDEVARCH(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRDEVARCH(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRDEVARCH(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errdevid
 *
 * LMC_RAS Error Record Device ID Register
 * Defines the highest numbered index of the error records that can be accessed
 * through the Error Record registers.
 */
union bdk_mccx_lmcoex_ras_errdevid
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errdevid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t num                   : 16; /**< [ 15:  0](RO) Highest numbered index of the error records that can be accessed. */
#else /* Word 0 - Little Endian */
        uint32_t num                   : 16; /**< [ 15:  0](RO) Highest numbered index of the error records that can be accessed. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errdevid_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errdevid bdk_mccx_lmcoex_ras_errdevid_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRDEVID(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRDEVID(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fc8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fc8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fc8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fc8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRDEVID", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRDEVID(a,b) bdk_mccx_lmcoex_ras_errdevid_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRDEVID(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRDEVID(a,b) "MCCX_LMCOEX_RAS_ERRDEVID"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRDEVID(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRDEVID(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRDEVID(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_errgsr0
 *
 * LMC RAS Error Group Status Register
 * This register shows the status for the records in the group.
 */
union bdk_mccx_lmcoex_ras_errgsr0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_errgsr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t s                     : 64; /**< [ 63:  0](RO/H) Shows the status for the records, a read-only copy of MCC()_LMCOE()_RAS_ERR00STATUS[V]:
                                                                    0 = No error.
                                                                    1 = One or more errors.

                                                                 Each bit corresponds to the status for 64 records, in groups of
                                                                 64 determined by the address index to this register.

                                                                 Bits above the maximum implemented index number (MCC()_LMCOE()_RAS_ERRDEVID[NUM]) are 0. */
#else /* Word 0 - Little Endian */
        uint64_t s                     : 64; /**< [ 63:  0](RO/H) Shows the status for the records, a read-only copy of MCC()_LMCOE()_RAS_ERR00STATUS[V]:
                                                                    0 = No error.
                                                                    1 = One or more errors.

                                                                 Each bit corresponds to the status for 64 records, in groups of
                                                                 64 determined by the address index to this register.

                                                                 Bits above the maximum implemented index number (MCC()_LMCOE()_RAS_ERRDEVID[NUM]) are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errgsr0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errgsr0 bdk_mccx_lmcoex_ras_errgsr0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRGSR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRGSR0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010e00ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010e00ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010e00ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010e00ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRGSR0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRGSR0(a,b) bdk_mccx_lmcoex_ras_errgsr0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRGSR0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERRGSR0(a,b) "MCCX_LMCOEX_RAS_ERRGSR0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRGSR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRGSR0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRGSR0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_errirqcr0
 *
 * LMC RAS Error Interrupt Configuration Register 0
 * This register configures interrupt delivery.
 */
union bdk_mccx_lmcoex_ras_errirqcr0
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_errirqcr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) Message Signaled Interrupt address. Specifies the address that the node writes to
                                                                 Signaling an interrupt. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) Message Signaled Interrupt address. Specifies the address that the node writes to
                                                                 Signaling an interrupt. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errirqcr0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errirqcr0 bdk_mccx_lmcoex_ras_errirqcr0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQCR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQCR0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010e80ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010e80ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010e80ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010e80ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRIRQCR0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRIRQCR0(a,b) bdk_mccx_lmcoex_ras_errirqcr0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRIRQCR0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERRIRQCR0(a,b) "MCCX_LMCOEX_RAS_ERRIRQCR0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRIRQCR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRIRQCR0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRIRQCR0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_errirqcr1
 *
 * LMC RAS Error Interrupt Configuration Register 1
 * This register configures interrupt delivery.
 */
union bdk_mccx_lmcoex_ras_errirqcr1
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_errirqcr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errirqcr1_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errirqcr1 bdk_mccx_lmcoex_ras_errirqcr1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQCR1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQCR1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010e88ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010e88ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010e88ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010e88ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRIRQCR1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRIRQCR1(a,b) bdk_mccx_lmcoex_ras_errirqcr1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRIRQCR1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERRIRQCR1(a,b) "MCCX_LMCOEX_RAS_ERRIRQCR1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRIRQCR1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRIRQCR1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRIRQCR1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_errirqcr2
 *
 * LMC RAS Error Interrupt Configuration Register 2
 * This register configures interrupt delivery.
 */
union bdk_mccx_lmcoex_ras_errirqcr2
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_errirqcr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errirqcr2_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errirqcr2 bdk_mccx_lmcoex_ras_errirqcr2_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQCR2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQCR2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010e90ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010e90ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010e90ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010e90ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRIRQCR2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRIRQCR2(a,b) bdk_mccx_lmcoex_ras_errirqcr2_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRIRQCR2(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERRIRQCR2(a,b) "MCCX_LMCOEX_RAS_ERRIRQCR2"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRIRQCR2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRIRQCR2(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRIRQCR2(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_errirqcr3
 *
 * LMC RAS Error Interrupt Configuration Register 3
 * This register configures interrupt delivery.
 */
union bdk_mccx_lmcoex_ras_errirqcr3
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_errirqcr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errirqcr3_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errirqcr3 bdk_mccx_lmcoex_ras_errirqcr3_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQCR3(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQCR3(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010e98ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010e98ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010e98ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010e98ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRIRQCR3", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRIRQCR3(a,b) bdk_mccx_lmcoex_ras_errirqcr3_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRIRQCR3(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERRIRQCR3(a,b) "MCCX_LMCOEX_RAS_ERRIRQCR3"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRIRQCR3(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRIRQCR3(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRIRQCR3(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_errirqsr
 *
 * LMC RAS Error Interrupt Status Register
 * This register uses the recommended Arm interrupt configuration register format.
 */
union bdk_mccx_lmcoex_ras_errirqsr
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_errirqsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t erierr                : 1;  /**< [  3:  3](RO) Error recovery interrupt error.
                                                                 0 = Error recovery interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Error recovery interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t eri                   : 1;  /**< [  2:  2](RO) Error recovery interrupt write in progress.
                                                                 0 = Error recovery interrupt write not in progress.
                                                                 1 = Error recovery interrupt write in progress.

                                                                 In CNXXXX, reads same as [FHI].

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
        uint64_t fhierr                : 1;  /**< [  1:  1](RO) Fault handling interrupt error.
                                                                 0 = Fault handling interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Fault handling interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t fhi                   : 1;  /**< [  0:  0](RO/H) Fault handling interrupt write in progress.
                                                                 0 = Fault handling interrupt write not in progress.
                                                                 1 = Fault handling interrupt write in progress.

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
#else /* Word 0 - Little Endian */
        uint64_t fhi                   : 1;  /**< [  0:  0](RO/H) Fault handling interrupt write in progress.
                                                                 0 = Fault handling interrupt write not in progress.
                                                                 1 = Fault handling interrupt write in progress.

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
        uint64_t fhierr                : 1;  /**< [  1:  1](RO) Fault handling interrupt error.
                                                                 0 = Fault handling interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Fault handling interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t eri                   : 1;  /**< [  2:  2](RO) Error recovery interrupt write in progress.
                                                                 0 = Error recovery interrupt write not in progress.
                                                                 1 = Error recovery interrupt write in progress.

                                                                 In CNXXXX, reads same as [FHI].

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
        uint64_t erierr                : 1;  /**< [  3:  3](RO) Error recovery interrupt error.
                                                                 0 = Error recovery interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Error recovery interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errirqsr_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errirqsr bdk_mccx_lmcoex_ras_errirqsr_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQSR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRIRQSR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010ef8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010ef8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010ef8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010ef8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRIRQSR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRIRQSR(a,b) bdk_mccx_lmcoex_ras_errirqsr_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRIRQSR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_ERRIRQSR(a,b) "MCCX_LMCOEX_RAS_ERRIRQSR"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRIRQSR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRIRQSR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRIRQSR(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errpidr0
 *
 * LMC RAS Peripheral Identification Register 0
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errpidr0
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errpidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::RAS_MCC. */
#else /* Word 0 - Little Endian */
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::RAS_MCC. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errpidr0_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errpidr0 bdk_mccx_lmcoex_ras_errpidr0_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fe0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fe0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fe0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fe0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRPIDR0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRPIDR0(a,b) bdk_mccx_lmcoex_ras_errpidr0_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRPIDR0(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRPIDR0(a,b) "MCCX_LMCOEX_RAS_ERRPIDR0"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRPIDR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRPIDR0(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRPIDR0(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errpidr1
 *
 * LMC RAS Peripheral Identification Register 1
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errpidr1
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errpidr1_s
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
    /* struct bdk_mccx_lmcoex_ras_errpidr1_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_errpidr1_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_errpidr1_cn96xxp3
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
    /* struct bdk_mccx_lmcoex_ras_errpidr1_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_errpidr1_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_errpidr1_cn96xxp3 loki; */
};
typedef union bdk_mccx_lmcoex_ras_errpidr1 bdk_mccx_lmcoex_ras_errpidr1_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fe4ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fe4ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fe4ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fe4ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRPIDR1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRPIDR1(a,b) bdk_mccx_lmcoex_ras_errpidr1_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRPIDR1(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRPIDR1(a,b) "MCCX_LMCOEX_RAS_ERRPIDR1"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRPIDR1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRPIDR1(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRPIDR1(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errpidr2
 *
 * LMC RAS Peripheral Identification Register 2
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errpidr2
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errpidr2_s
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
    /* struct bdk_mccx_lmcoex_ras_errpidr2_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_errpidr2_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_errpidr2_cn96xxp3
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
    /* struct bdk_mccx_lmcoex_ras_errpidr2_s cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_errpidr2_s cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_errpidr2_s loki; */
};
typedef union bdk_mccx_lmcoex_ras_errpidr2 bdk_mccx_lmcoex_ras_errpidr2_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fe8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fe8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fe8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fe8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRPIDR2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRPIDR2(a,b) bdk_mccx_lmcoex_ras_errpidr2_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRPIDR2(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRPIDR2(a,b) "MCCX_LMCOEX_RAS_ERRPIDR2"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRPIDR2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRPIDR2(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRPIDR2(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errpidr3
 *
 * LMC RAS Peripheral Identification Register 3
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errpidr3
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errpidr3_s
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
    /* struct bdk_mccx_lmcoex_ras_errpidr3_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errpidr3 bdk_mccx_lmcoex_ras_errpidr3_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR3(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR3(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fecll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fecll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fecll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fecll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRPIDR3", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRPIDR3(a,b) bdk_mccx_lmcoex_ras_errpidr3_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRPIDR3(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRPIDR3(a,b) "MCCX_LMCOEX_RAS_ERRPIDR3"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRPIDR3(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRPIDR3(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRPIDR3(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errpidr4
 *
 * LMC RAS Peripheral Identification Register 4
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errpidr4
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errpidr4_s
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
    /* struct bdk_mccx_lmcoex_ras_errpidr4_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_errpidr4_s cn96xxp1; */
    struct bdk_mccx_lmcoex_ras_errpidr4_cn96xxp3
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
    /* struct bdk_mccx_lmcoex_ras_errpidr4_s cn98xx; */
    /* struct bdk_mccx_lmcoex_ras_errpidr4_s cnf95xx; */
    /* struct bdk_mccx_lmcoex_ras_errpidr4_s loki; */
};
typedef union bdk_mccx_lmcoex_ras_errpidr4 bdk_mccx_lmcoex_ras_errpidr4_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR4(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR4(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fd0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fd0ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fd0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fd0ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRPIDR4", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRPIDR4(a,b) bdk_mccx_lmcoex_ras_errpidr4_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRPIDR4(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRPIDR4(a,b) "MCCX_LMCOEX_RAS_ERRPIDR4"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRPIDR4(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRPIDR4(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRPIDR4(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errpidr5
 *
 * LMC RAS Peripheral Identification Register 5
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errpidr5
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errpidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errpidr5_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errpidr5 bdk_mccx_lmcoex_ras_errpidr5_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR5(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR5(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fd4ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fd4ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fd4ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fd4ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRPIDR5", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRPIDR5(a,b) bdk_mccx_lmcoex_ras_errpidr5_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRPIDR5(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRPIDR5(a,b) "MCCX_LMCOEX_RAS_ERRPIDR5"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRPIDR5(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRPIDR5(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRPIDR5(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errpidr6
 *
 * LMC RAS Peripheral Identification Register 6
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errpidr6
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errpidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errpidr6_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errpidr6 bdk_mccx_lmcoex_ras_errpidr6_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR6(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR6(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fd8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fd8ll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fd8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fd8ll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRPIDR6", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRPIDR6(a,b) bdk_mccx_lmcoex_ras_errpidr6_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRPIDR6(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRPIDR6(a,b) "MCCX_LMCOEX_RAS_ERRPIDR6"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRPIDR6(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRPIDR6(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRPIDR6(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_lmcoe#_ras_errpidr7
 *
 * LMC RAS Peripheral Identification Register 7
 * This register provides information to identify a debug component.
 */
union bdk_mccx_lmcoex_ras_errpidr7
{
    uint32_t u;
    struct bdk_mccx_lmcoex_ras_errpidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_errpidr7_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_errpidr7 bdk_mccx_lmcoex_ras_errpidr7_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR7(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_ERRPIDR7(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c010fdcll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c010fdcll + 0x1000000ll * ((a) & 0x1) + 0x1000ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c010fdcll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c010fdcll + 0x1000000ll * ((a) & 0x0) + 0x1000ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_ERRPIDR7", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_ERRPIDR7(a,b) bdk_mccx_lmcoex_ras_errpidr7_t
#define bustype_BDK_MCCX_LMCOEX_RAS_ERRPIDR7(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_LMCOEX_RAS_ERRPIDR7(a,b) "MCCX_LMCOEX_RAS_ERRPIDR7"
#define device_bar_BDK_MCCX_LMCOEX_RAS_ERRPIDR7(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_ERRPIDR7(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_ERRPIDR7(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_int
 *
 * MCC CTL RAS Interrupt Clear Register
 * This register contains the different interrupt-summary bits of the LMC RAS.
 * _ MCC(0)_LMCOE(0)_* = LMC1's RAS interrupt.
 * _ MCC(0)_LMCOE(1)_* = Reserved.
 * _ MCC(1)_LMCOE(0)_* = LMC0's RAS interrupt.
 * _ MCC(1)_LMCOE(1)_* = LMC2's RAS interrupt.
 */
union bdk_mccx_lmcoex_ras_int
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t err07                 : 1;  /**< [  7:  7](RO/H) Interrupt for scrubber read uncorrectable nondeferred. Clear this field by
                                                                 writing a 1 to MCC()_LMCOE()_RAS_ERR07STATUS[V]. */
        uint64_t err06                 : 1;  /**< [  6:  6](RO/H) Interrupt for scrubber read ECC deferred. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR06STATUS[V]. */
        uint64_t err05                 : 1;  /**< [  5:  5](RO/H) Interrupt for scrubber read corrected by retry. Clear this field by writing a 1
                                                                 to MCC()_LMCOE()_RAS_ERR05STATUS[V]. */
        uint64_t err04                 : 1;  /**< [  4:  4](RO/H) Interrupt for scrubber read corrected by ECC. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR04STATUS[V]. */
        uint64_t err03                 : 1;  /**< [  3:  3](RO/H) Interrupt for demand read uncorrectable nondeferred. Clear this field by
                                                                 writing a 1 to MCC()_LMCOE()_RAS_ERR03STATUS[V]. */
        uint64_t err02                 : 1;  /**< [  2:  2](RO/H) Interrupt for demand read ECC deferred. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR02STATUS[V]. */
        uint64_t err01                 : 1;  /**< [  1:  1](RO/H) Interrupt for demand read corrected by retry. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR01STATUS[V]. */
        uint64_t err00                 : 1;  /**< [  0:  0](RO/H) Interrupt for demand read corrected by ECC. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS[V]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](RO/H) Interrupt for demand read corrected by ECC. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS[V]. */
        uint64_t err01                 : 1;  /**< [  1:  1](RO/H) Interrupt for demand read corrected by retry. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR01STATUS[V]. */
        uint64_t err02                 : 1;  /**< [  2:  2](RO/H) Interrupt for demand read ECC deferred. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR02STATUS[V]. */
        uint64_t err03                 : 1;  /**< [  3:  3](RO/H) Interrupt for demand read uncorrectable nondeferred. Clear this field by
                                                                 writing a 1 to MCC()_LMCOE()_RAS_ERR03STATUS[V]. */
        uint64_t err04                 : 1;  /**< [  4:  4](RO/H) Interrupt for scrubber read corrected by ECC. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR04STATUS[V]. */
        uint64_t err05                 : 1;  /**< [  5:  5](RO/H) Interrupt for scrubber read corrected by retry. Clear this field by writing a 1
                                                                 to MCC()_LMCOE()_RAS_ERR05STATUS[V]. */
        uint64_t err06                 : 1;  /**< [  6:  6](RO/H) Interrupt for scrubber read ECC deferred. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR06STATUS[V]. */
        uint64_t err07                 : 1;  /**< [  7:  7](RO/H) Interrupt for scrubber read uncorrectable nondeferred. Clear this field by
                                                                 writing a 1 to MCC()_LMCOE()_RAS_ERR07STATUS[V]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_int_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_int bdk_mccx_lmcoex_ras_int_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_INT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000340ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000340ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000340ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000340ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_INT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_INT(a,b) bdk_mccx_lmcoex_ras_int_t
#define bustype_BDK_MCCX_LMCOEX_RAS_INT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_INT(a,b) "MCCX_LMCOEX_RAS_INT"
#define device_bar_BDK_MCCX_LMCOEX_RAS_INT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_INT(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_INT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_int_ena_w1c
 *
 * MCC RAS Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_mccx_lmcoex_ras_int_ena_w1c
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR07]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR06]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR05]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR04]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR03]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR02]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR01]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR02]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR03]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR04]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR05]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR06]. */
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR07]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_int_ena_w1c_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_int_ena_w1c_s cn96xx; */
    struct bdk_mccx_lmcoex_ras_int_ena_w1c_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR07]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR06]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR05]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR04]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR03]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR02]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR01]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR02]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR03]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR04]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR05]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR06]. */
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR07]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_mccx_lmcoex_ras_int_ena_w1c_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR07]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR06]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR05]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR04]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR03]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR02]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR01]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR02]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR03]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR04]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR05]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR06]. */
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR07]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_lmcoex_ras_int_ena_w1c_cnf95xx loki; */
};
typedef union bdk_mccx_lmcoex_ras_int_ena_w1c bdk_mccx_lmcoex_ras_int_ena_w1c_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000380ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000380ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000380ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000380ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_INT_ENA_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(a,b) bdk_mccx_lmcoex_ras_int_ena_w1c_t
#define bustype_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(a,b) "MCCX_LMCOEX_RAS_INT_ENA_W1C"
#define device_bar_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_int_ena_w1s
 *
 * MCC RAS Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_mccx_lmcoex_ras_int_ena_w1s
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR07]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR06]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR05]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR04]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR03]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR02]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR01]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR02]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR03]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR04]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR05]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR06]. */
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..1)_RAS_INT[ERR07]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_int_ena_w1s_s cn9; */
    /* struct bdk_mccx_lmcoex_ras_int_ena_w1s_s cn96xx; */
    struct bdk_mccx_lmcoex_ras_int_ena_w1s_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR07]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR06]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR05]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR04]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR03]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR02]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR01]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR02]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR03]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR04]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR05]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR06]. */
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for MCC(0..1)_LMCOE(0..2)_RAS_INT[ERR07]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_mccx_lmcoex_ras_int_ena_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR07]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR06]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR05]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR04]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR03]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR02]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR01]. */
        uint64_t err02                 : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR02]. */
        uint64_t err03                 : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR03]. */
        uint64_t err04                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR04]. */
        uint64_t err05                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR05]. */
        uint64_t err06                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR06]. */
        uint64_t err07                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for MCC(0)_LMCOE(0..1)_RAS_INT[ERR07]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_lmcoex_ras_int_ena_w1s_cnf95xx loki; */
};
typedef union bdk_mccx_lmcoex_ras_int_ena_w1s bdk_mccx_lmcoex_ras_int_ena_w1s_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c0003a0ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c0003a0ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c0003a0ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c0003a0ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_INT_ENA_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(a,b) bdk_mccx_lmcoex_ras_int_ena_w1s_t
#define bustype_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(a,b) "MCCX_LMCOEX_RAS_INT_ENA_W1S"
#define device_bar_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_lmcoe#_ras_int_w1s
 *
 * MCC RAS Interrupt Set Register
 */
union bdk_mccx_lmcoex_ras_int_w1s
{
    uint64_t u;
    struct bdk_mccx_lmcoex_ras_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t err07                 : 1;  /**< [  7:  7](RO/H) Interrupt for scrubber read uncorrectable nondeferred. Clear this field by
                                                                 writing a 1 to MCC()_LMCOE()_RAS_ERR07STATUS[V]. */
        uint64_t err06                 : 1;  /**< [  6:  6](RO/H) Interrupt for scrubber read ECC deferred. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR06STATUS[V]. */
        uint64_t err05                 : 1;  /**< [  5:  5](RO/H) Interrupt for scrubber read corrected by retry. Clear this field by writing a 1
                                                                 to MCC()_LMCOE()_RAS_ERR05STATUS[V]. */
        uint64_t err04                 : 1;  /**< [  4:  4](RO/H) Interrupt for scrubber read corrected by ECC. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR04STATUS[V]. */
        uint64_t err03                 : 1;  /**< [  3:  3](RO/H) Interrupt for demand read uncorrectable nondeferred. Clear this field by
                                                                 writing a 1 to MCC()_LMCOE()_RAS_ERR03STATUS[V]. */
        uint64_t err02                 : 1;  /**< [  2:  2](RO/H) Interrupt for demand read ECC deferred. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR02STATUS[V]. */
        uint64_t err01                 : 1;  /**< [  1:  1](RO/H) Interrupt for demand read corrected by retry. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR01STATUS[V]. */
        uint64_t err00                 : 1;  /**< [  0:  0](RO/H) Interrupt for demand read corrected by ECC. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS[V]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](RO/H) Interrupt for demand read corrected by ECC. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR00STATUS[V]. */
        uint64_t err01                 : 1;  /**< [  1:  1](RO/H) Interrupt for demand read corrected by retry. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR01STATUS[V]. */
        uint64_t err02                 : 1;  /**< [  2:  2](RO/H) Interrupt for demand read ECC deferred. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR02STATUS[V]. */
        uint64_t err03                 : 1;  /**< [  3:  3](RO/H) Interrupt for demand read uncorrectable nondeferred. Clear this field by
                                                                 writing a 1 to MCC()_LMCOE()_RAS_ERR03STATUS[V]. */
        uint64_t err04                 : 1;  /**< [  4:  4](RO/H) Interrupt for scrubber read corrected by ECC. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR04STATUS[V]. */
        uint64_t err05                 : 1;  /**< [  5:  5](RO/H) Interrupt for scrubber read corrected by retry. Clear this field by writing a 1
                                                                 to MCC()_LMCOE()_RAS_ERR05STATUS[V]. */
        uint64_t err06                 : 1;  /**< [  6:  6](RO/H) Interrupt for scrubber read ECC deferred. Clear this field by writing a 1 to
                                                                 MCC()_LMCOE()_RAS_ERR06STATUS[V]. */
        uint64_t err07                 : 1;  /**< [  7:  7](RO/H) Interrupt for scrubber read uncorrectable nondeferred. Clear this field by
                                                                 writing a 1 to MCC()_LMCOE()_RAS_ERR07STATUS[V]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_lmcoex_ras_int_w1s_s cn; */
};
typedef union bdk_mccx_lmcoex_ras_int_w1s bdk_mccx_lmcoex_ras_int_w1s_t;

static inline uint64_t BDK_MCCX_LMCOEX_RAS_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_LMCOEX_RAS_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000360ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000360ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000360ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000360ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RAS_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RAS_INT_W1S(a,b) bdk_mccx_lmcoex_ras_int_w1s_t
#define bustype_BDK_MCCX_LMCOEX_RAS_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RAS_INT_W1S(a,b) "MCCX_LMCOEX_RAS_INT_W1S"
#define device_bar_BDK_MCCX_LMCOEX_RAS_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RAS_INT_W1S(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RAS_INT_W1S(a,b) (a),(b),-1,-1

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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000300ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000300ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000300ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000300ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_RDNXM_FADR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) bdk_mccx_lmcoex_rdnxm_fadr_t
#define bustype_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) "MCCX_LMCOEX_RDNXM_FADR"
#define device_bar_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) (a)
#define arguments_BDK_MCCX_LMCOEX_RDNXM_FADR(a,b) (a),(b),-1,-1

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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c000320ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=2)))
        return 0x87e03c000320ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=1)))
        return 0x87e03c000320ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=1)))
        return 0x87e03c000320ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MCCX_LMCOEX_WRNXM_FADR", 2, a, b, 0, 0, 0, 0);
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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400048ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400048ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400048ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400048ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_BP_TEST", 2, a, b, 0, 0, 0, 0);
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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400060ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400060ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400060ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400060ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_DBE_DBG_CNT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) bdk_mccx_mcix_dbe_dbg_cnt_t
#define bustype_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) "MCCX_MCIX_DBE_DBG_CNT"
#define device_bar_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) (a)
#define arguments_BDK_MCCX_MCIX_DBE_DBG_CNT(a,b) (a),(b),-1,-1

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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400050ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400050ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400050ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400050ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_ECC_DBG_EN", 2, a, b, 0, 0, 0, 0);
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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400040ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400040ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400040ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400040ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_ECO", 2, a, b, 0, 0, 0, 0);
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
        uint64_t reserved_7_63         : 57;
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
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_int_s cn; */
};
typedef union bdk_mccx_mcix_int bdk_mccx_mcix_int_t;

static inline uint64_t BDK_MCCX_MCIX_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_INT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400200ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400200ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400200ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400200ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_INT", 2, a, b, 0, 0, 0, 0);
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
        uint64_t reserved_7_63         : 57;
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
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_int_ena_w1c_s cn9; */
    /* struct bdk_mccx_mcix_int_ena_w1c_s cn96xx; */
    /* struct bdk_mccx_mcix_int_ena_w1c_s cn98xx; */
    struct bdk_mccx_mcix_int_ena_w1c_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[WRDISLMC45]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[WRDISLMC23]. */
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[WRDISLMC01]. */
        uint64_t reserved_3            : 1;
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[RDDISLMC45]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[RDDISLMC23]. */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[RDDISLMC01]. */
#else /* Word 0 - Little Endian */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[RDDISLMC01]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[RDDISLMC23]. */
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[RDDISLMC45]. */
        uint64_t reserved_3            : 1;
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[WRDISLMC01]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[WRDISLMC23]. */
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_INT[WRDISLMC45]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_mcix_int_ena_w1c_cnf95xx loki; */
};
typedef union bdk_mccx_mcix_int_ena_w1c bdk_mccx_mcix_int_ena_w1c_t;

static inline uint64_t BDK_MCCX_MCIX_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400210ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400210ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400210ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400210ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_INT_ENA_W1C", 2, a, b, 0, 0, 0, 0);
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
        uint64_t reserved_7_63         : 57;
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
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_int_ena_w1s_s cn9; */
    /* struct bdk_mccx_mcix_int_ena_w1s_s cn96xx; */
    /* struct bdk_mccx_mcix_int_ena_w1s_s cn98xx; */
    struct bdk_mccx_mcix_int_ena_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[WRDISLMC45]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[WRDISLMC23]. */
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[WRDISLMC01]. */
        uint64_t reserved_3            : 1;
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[RDDISLMC45]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[RDDISLMC23]. */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[RDDISLMC01]. */
#else /* Word 0 - Little Endian */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[RDDISLMC01]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[RDDISLMC23]. */
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[RDDISLMC45]. */
        uint64_t reserved_3            : 1;
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[WRDISLMC01]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[WRDISLMC23]. */
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_INT[WRDISLMC45]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_mcix_int_ena_w1s_cnf95xx loki; */
};
typedef union bdk_mccx_mcix_int_ena_w1s bdk_mccx_mcix_int_ena_w1s_t;

static inline uint64_t BDK_MCCX_MCIX_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400218ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400218ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400218ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400218ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_INT_ENA_W1S", 2, a, b, 0, 0, 0, 0);
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
        uint64_t reserved_7_63         : 57;
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
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_int_w1s_s cn9; */
    /* struct bdk_mccx_mcix_int_w1s_s cn96xx; */
    /* struct bdk_mccx_mcix_int_w1s_s cn98xx; */
    struct bdk_mccx_mcix_int_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[WRDISLMC45]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[WRDISLMC23]. */
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[WRDISLMC01]. */
        uint64_t reserved_3            : 1;
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[RDDISLMC45]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[RDDISLMC23]. */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[RDDISLMC01]. */
#else /* Word 0 - Little Endian */
        uint64_t rddislmc01            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[RDDISLMC01]. */
        uint64_t rddislmc23            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[RDDISLMC23]. */
        uint64_t rddislmc45            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[RDDISLMC45]. */
        uint64_t reserved_3            : 1;
        uint64_t wrdislmc01            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[WRDISLMC01]. */
        uint64_t wrdislmc23            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[WRDISLMC23]. */
        uint64_t wrdislmc45            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets MCC(0)_MCI(0)_INT[WRDISLMC45]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_mcix_int_w1s_cnf95xx loki; */
};
typedef union bdk_mccx_mcix_int_w1s bdk_mccx_mcix_int_w1s_t;

static inline uint64_t BDK_MCCX_MCIX_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400208ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400208ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400208ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400208ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_INT_W1S(a,b) bdk_mccx_mcix_int_w1s_t
#define bustype_BDK_MCCX_MCIX_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_INT_W1S(a,b) "MCCX_MCIX_INT_W1S"
#define device_bar_BDK_MCCX_MCIX_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_INT_W1S(a,b) (a)
#define arguments_BDK_MCCX_MCIX_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err00addr
 *
 * MCC MCI RAS Error Record 00 Address Register
 * This per-record register contains the error address for those error records which
 * set MCC()_MCI()_RAS_ERR00STATUS[AV].
 *
 * See the individual per-record CSRs for the record-specific meaning of each field.
 */
union bdk_mccx_mcix_ras_err00addr
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err00addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In ARM spec it is named NS. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In ARM spec it is named NS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err00addr_s cn9; */
    /* struct bdk_mccx_mcix_ras_err00addr_s cn96xxp1; */
    struct bdk_mccx_mcix_ras_err00addr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In Arm spec it is named NS. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In Arm spec it is named NS. */
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_mcix_ras_err00addr_cn96xxp3 cn98xx; */
    struct bdk_mccx_mcix_ras_err00addr_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In Arm spec it is named NS. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address first cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address first cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In Arm spec it is named NS. */
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_mcix_ras_err00addr_cnf95xx loki; */
};
typedef union bdk_mccx_mcix_ras_err00addr bdk_mccx_mcix_ras_err00addr_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410018ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410018ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410018ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410018ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR00ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR00ADDR(a,b) bdk_mccx_mcix_ras_err00addr_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR00ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR00ADDR(a,b) "MCCX_MCIX_RAS_ERR00ADDR"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR00ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR00ADDR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR00ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err00ctlr
 *
 * MCC MCI RAS Error Record 00 Control Register
 * This per-record register contains enables bits for the node that writes to this record.
 * See the individual per-record CSRs for the record-specific values of each field.
 *
 * Internal:
 * If adding/removing records, update MCC()_MCI()_RAS_ERRDEVID[NUM].
 */
union bdk_mccx_mcix_ras_err00ctlr
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err00ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t wdui                  : 1;  /**< [ 11: 11](RO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](RO) Error recovery interrupt for deferred error enable. When enabled the error
                                                                 recovery interrupt is also generated for all deferred read errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](RO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](R/W) Fault handling interrupt for corrected errors enable.
                                                                 When enabled:

                                                                 * If the node implements a corrected error counter, the fault handling interrupt
                                                                 is only generated when the counter overflows and the overflow bit is set.

                                                                 * Otherwise the fault handling interrupt is also generated for all detected
                                                                 corrected errors.

                                                                 0 = Fault handling interrupt not generated for corrected errors.
                                                                 1 = Fault handling interrupt generated for corrected errors.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, R/W.
                                                                 * For other records, always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](RO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](RO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](RO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t ue                    : 1;  /**< [  4:  4](RO) Uncorrected error reporting enable. When enabled, responses to
                                                                 transactions that detect an uncorrected error that cannot be deferred are
                                                                 signaled as a detected error (external abort).

                                                                 0 = External abort response for uncorrected errors disabled.
                                                                 1 = External abort response for uncorrected errors enabled.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, R/W.
                                                                 * For other records, always 0. */
        uint64_t fi                    : 1;  /**< [  3:  3](R/W) Fault handling interrupt enable. When enabled the fault handling interrupt
                                                                 is generated for all detected deferred errors and uncorrected errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. The fault handling
                                                                 interrupt is never generated for consumed errors. */
        uint64_t ui                    : 1;  /**< [  2:  2](RO) Uncorrected error recovery interrupt enable. When enabled, the error
                                                                 recovery interrupt is generated for all detected uncorrected errors that are not
                                                                 deferred.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, R/W.
                                                                 * For other records, always 0. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](R/W) Implementation defined.

                                                                 For CNXXXX force error.
                                                                 * For records where MCC()_MCI()_RAS_ERRn[IMP_FE] = 0x2, this bit is R/W and when set
                                                                 injects an error.
                                                                 * For other records, reserved. */
        uint64_t ed                    : 1;  /**< [  0:  0](R/W) Enable error detection and correction at the node.
                                                                 0 = Error detection and correction disabled.
                                                                 1 = Error detection and correction enabled.

                                                                 For CNXXXX, all records similar.

                                                                 Internal:
                                                                 This feature is always enabled, so this field has no control. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 1;  /**< [  0:  0](R/W) Enable error detection and correction at the node.
                                                                 0 = Error detection and correction disabled.
                                                                 1 = Error detection and correction enabled.

                                                                 For CNXXXX, all records similar.

                                                                 Internal:
                                                                 This feature is always enabled, so this field has no control. */
        uint64_t imp_fe                : 1;  /**< [  1:  1](R/W) Implementation defined.

                                                                 For CNXXXX force error.
                                                                 * For records where MCC()_MCI()_RAS_ERRn[IMP_FE] = 0x2, this bit is R/W and when set
                                                                 injects an error.
                                                                 * For other records, reserved. */
        uint64_t ui                    : 1;  /**< [  2:  2](RO) Uncorrected error recovery interrupt enable. When enabled, the error
                                                                 recovery interrupt is generated for all detected uncorrected errors that are not
                                                                 deferred.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, R/W.
                                                                 * For other records, always 0. */
        uint64_t fi                    : 1;  /**< [  3:  3](R/W) Fault handling interrupt enable. When enabled the fault handling interrupt
                                                                 is generated for all detected deferred errors and uncorrected errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. The fault handling
                                                                 interrupt is never generated for consumed errors. */
        uint64_t ue                    : 1;  /**< [  4:  4](RO) Uncorrected error reporting enable. When enabled, responses to
                                                                 transactions that detect an uncorrected error that cannot be deferred are
                                                                 signaled as a detected error (external abort).

                                                                 0 = External abort response for uncorrected errors disabled.
                                                                 1 = External abort response for uncorrected errors enabled.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, R/W.
                                                                 * For other records, always 0. */
        uint64_t wui                   : 1;  /**< [  5:  5](RO) Error recovery interrupt on writes. See [UI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wfi                   : 1;  /**< [  6:  6](RO) Fault handling interrupt on writes. See [FI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t wue                   : 1;  /**< [  7:  7](RO) Error reporting on writes. See [UE].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t cfi                   : 1;  /**< [  8:  8](R/W) Fault handling interrupt for corrected errors enable.
                                                                 When enabled:

                                                                 * If the node implements a corrected error counter, the fault handling interrupt
                                                                 is only generated when the counter overflows and the overflow bit is set.

                                                                 * Otherwise the fault handling interrupt is also generated for all detected
                                                                 corrected errors.

                                                                 0 = Fault handling interrupt not generated for corrected errors.
                                                                 1 = Fault handling interrupt generated for corrected errors.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to correctable errors, R/W.
                                                                 * For other records, always 0. */
        uint64_t wcfi                  : 1;  /**< [  9:  9](RO) Fault handling interrupt for corrected errors on writes. See [CFI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t dui                   : 1;  /**< [ 10: 10](RO) Error recovery interrupt for deferred error enable. When enabled the error
                                                                 recovery interrupt is also generated for all deferred read errors.

                                                                 The interrupt is generated even if the error syndrome is discarded because the
                                                                 error record already records a higher priority error. */
        uint64_t wdui                  : 1;  /**< [ 11: 11](RO) Error recovery interrupt for deferred errors on writes. See [DUI].

                                                                 For CNXXXX does not distinguish between reads and writes, so always 0. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err00ctlr_s cn; */
};
typedef union bdk_mccx_mcix_ras_err00ctlr bdk_mccx_mcix_ras_err00ctlr_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410008ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410008ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410008ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410008ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR00CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR00CTLR(a,b) bdk_mccx_mcix_ras_err00ctlr_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR00CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR00CTLR(a,b) "MCCX_MCIX_RAS_ERR00CTLR"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR00CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR00CTLR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR00CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err00fr
 *
 * MCC MCI RAS Error Record 00 Feature Register
 * This per-record register defines which of the common architecturally-defined
 * features are implemented. and of the implemented features which are software
 * programmable.
 * See the individual per-record CSRs for the record-specific values of each field.
 *
 * Internal:
 * If adding/removing records, update MCC()_MCI()_RAS_ERRDEVID[NUM].
 */
union bdk_mccx_mcix_ras_err00fr
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err00fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](RO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. MCC()_MCI()_RAS_ERRnSTATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If MCC()_MCI()_RAS_ERRnSTATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, MCC()_MCI()_RAS_ERRnSTATUS[OF] is set to 1. */
        uint64_t dui                   : 2;  /**< [ 17: 16](RO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes. */
        uint64_t rp                    : 1;  /**< [ 15: 15](RO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 If [CEC] = 0x0, this bit is 0.

                                                                 For CNXXXX no RP in any records, always 0. */
        uint64_t cec                   : 3;  /**< [ 14: 12](RO) Indicates a standard correctable error counter mechanism in *_RAS_ERRnMISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in *_RAS_ERRnMISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in *_RAS_ERRnMISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](RO) Fault handling interrupt for corrected errors. If this feature is implemented,
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
        uint64_t ue                    : 2;  /**< [  9:  8](RO) In-band uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t fi                    : 2;  /**< [  7:  6](RO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ui                    : 2;  /**< [  5:  4](RO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](RO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Cavium force error feature is supported.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX depends on the record.
                                                                 * For records where forcing is supported, 0x2.
                                                                 * For other records, 0x0. */
        uint64_t ed                    : 2;  /**< [  1:  0](RO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 For CNXXXX all records controllable, always 0x2.

                                                                 Internal:
                                                                 Hardcoded. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](RO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 For CNXXXX all records controllable, always 0x2.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](RO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Cavium force error feature is supported.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX depends on the record.
                                                                 * For records where forcing is supported, 0x2.
                                                                 * For other records, 0x0. */
        uint64_t ui                    : 2;  /**< [  5:  4](RO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t fi                    : 2;  /**< [  7:  6](RO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](RO) In-band uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](RO) Fault handling interrupt for corrected errors. If this feature is implemented,
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
        uint64_t cec                   : 3;  /**< [ 14: 12](RO) Indicates a standard correctable error counter mechanism in *_RAS_ERRnMISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in *_RAS_ERRnMISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in *_RAS_ERRnMISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](RO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 If [CEC] = 0x0, this bit is 0.

                                                                 For CNXXXX no RP in any records, always 0. */
        uint64_t dui                   : 2;  /**< [ 17: 16](RO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](RO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. MCC()_MCI()_RAS_ERRnSTATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If MCC()_MCI()_RAS_ERRnSTATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, MCC()_MCI()_RAS_ERRnSTATUS[OF] is set to 1. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err00fr_s cn9; */
    /* struct bdk_mccx_mcix_ras_err00fr_s cn96xxp1; */
    struct bdk_mccx_mcix_ras_err00fr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ceo                   : 2;  /**< [ 19: 18](RO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. MCC()_MCI()_RAS_ERRnSTATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If MCC()_MCI()_RAS_ERRnSTATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, MCC()_MCI()_RAS_ERRnSTATUS[OF] is set to 1. */
        uint64_t dui                   : 2;  /**< [ 17: 16](RO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes. */
        uint64_t rp                    : 1;  /**< [ 15: 15](RO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 If [CEC] = 0x0, this bit is 0.

                                                                 For CNXXXX no RP in any records, always 0. */
        uint64_t cec                   : 3;  /**< [ 14: 12](RO) Indicates a standard correctable error counter mechanism in *_RAS_ERRnMISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in *_RAS_ERRnMISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in *_RAS_ERRnMISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](RO) Fault handling interrupt for corrected errors. If this feature is implemented,
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
        uint64_t ue                    : 2;  /**< [  9:  8](RO) In-band uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t fi                    : 2;  /**< [  7:  6](RO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ui                    : 2;  /**< [  5:  4](RO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](RO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Marvell force error feature is supported.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX depends on the record.
                                                                 * For records where forcing is supported, 0x2.
                                                                 * For other records, 0x0. */
        uint64_t ed                    : 2;  /**< [  1:  0](RO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 For CNXXXX all records controllable, always 0x2.

                                                                 Internal:
                                                                 Hardcoded. */
#else /* Word 0 - Little Endian */
        uint64_t ed                    : 2;  /**< [  1:  0](RO) Error detection and correction.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.

                                                                 For CNXXXX all records controllable, always 0x2.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t imp_fe                : 2;  /**< [  3:  2](RO) Implementation defined.
                                                                 0x0 = No additional feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Marvell force error feature is supported.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX depends on the record.
                                                                 * For records where forcing is supported, 0x2.
                                                                 * For other records, 0x0. */
        uint64_t ui                    : 2;  /**< [  5:  4](RO) Uncorrected error recovery interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t fi                    : 2;  /**< [  7:  6](RO) Fault handling interrupt.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t ue                    : 2;  /**< [  9:  8](RO) In-band uncorrected error reporting.
                                                                 0x0 = Does not support feature.
                                                                 0x1 = Feature always enabled.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes.

                                                                 For CNXXXX depends on the record.
                                                                 * For records corresponding to uncorrectable errors, 0x2.
                                                                 * For other records, 0x0.

                                                                 Internal:
                                                                 Hardcoded per record. */
        uint64_t cfi                   : 2;  /**< [ 11: 10](RO) Fault handling interrupt for corrected errors. If this feature is implemented,
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
        uint64_t cec                   : 3;  /**< [ 14: 12](RO) Indicates a standard correctable error counter mechanism in *_RAS_ERRnMISC0.
                                                                 0x0 = Does not implement the standardized error counter model.
                                                                 0x2 = Implements an 8-bit error counter in *_RAS_ERRnMISC0\<39:32\>.
                                                                 0x4 = Implements a 16-bit error counter in *_RAS_ERRnMISC0\<47:32\>.
                                                                 _ All other values are reserved.

                                                                 Internal:
                                                                 Hardcoded. */
        uint64_t rp                    : 1;  /**< [ 15: 15](RO) Repeat counter. Indicates whether the node implements a repeat corrected error counter.
                                                                 0 = A single CE counter is implemented.
                                                                 1 = A first (repeat) counter and a second (other) counter are implemented. The
                                                                 repeat counter is the same size as the primary error counter.

                                                                 If [CEC] = 0x0, this bit is 0.

                                                                 For CNXXXX no RP in any records, always 0. */
        uint64_t dui                   : 2;  /**< [ 17: 16](RO) Error recovery interrupt for deferred errors. If this feature is implemented,
                                                                 then the error recovery interrupt must be implemented.

                                                                 0x0 = Does not support feature.
                                                                 0x1 = Reserved.
                                                                 0x2 = Feature is controllable.
                                                                 0x3 = Feature is controllable with independent controls for reads and writes. */
        uint64_t ceo                   : 2;  /**< [ 19: 18](RO) Corrected error overwrite. Indicates the behavior when a second corrected error
                                                                 is detected after a first corrected error has been recorded by the node.
                                                                 0x0 = Count corrected error if a counter is implemented. Keep the previous error
                                                                 syndrome. If the counter overflows, or no counter is
                                                                 implemented. MCC()_MCI()_RAS_ERRnSTATUS[OF] is set to 1.
                                                                 0x1 = Count corrected error. If MCC()_MCI()_RAS_ERRnSTATUS[OF] = 1 before the corrected
                                                                 error is counted, keep the previous syndrome. Otherwise the previous syndrome is
                                                                 overwritten. If the counter overflows, MCC()_MCI()_RAS_ERRnSTATUS[OF] is set to 1. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_mcix_ras_err00fr_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_mcix_ras_err00fr_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_mcix_ras_err00fr_cn96xxp3 loki; */
};
typedef union bdk_mccx_mcix_ras_err00fr bdk_mccx_mcix_ras_err00fr_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410000ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410000ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410000ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410000ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR00FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR00FR(a,b) bdk_mccx_mcix_ras_err00fr_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR00FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR00FR(a,b) "MCCX_MCIX_RAS_ERR00FR"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR00FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR00FR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR00FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err00misc0
 *
 * MCC MCI RAS Error Record 00 Miscellaneous 0 Register
 * This register contains other record-specific information not
 * present in the corresponding status and address registers.
 *
 * Bits \<31:0\> are implementation defined; see the individual per-record CSRs for the
 * record-specific implementation-defined meaning of each field.
 */
union bdk_mccx_mcix_ras_err00misc0
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err00misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t odd_synd1             : 8;  /**< [ 63: 56](R/W/H) Odd syndrome. */
        uint64_t even_synd1            : 8;  /**< [ 55: 48](R/W/H) Even syndrome. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_20_31        : 12;
        uint64_t odd_valid1            : 1;  /**< [ 19: 19](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid1           : 1;  /**< [ 18: 18](R/W/H) Error detected with even syndrome. */
        uint64_t reserved_0_17         : 18;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_17         : 18;
        uint64_t even_valid1           : 1;  /**< [ 18: 18](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid1            : 1;  /**< [ 19: 19](R/W/H) Error detected with odd syndrome. */
        uint64_t reserved_20_31        : 12;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t even_synd1            : 8;  /**< [ 55: 48](R/W/H) Even syndrome. */
        uint64_t odd_synd1             : 8;  /**< [ 63: 56](R/W/H) Odd syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err00misc0_s cn9; */
    struct bdk_mccx_mcix_ras_err00misc0_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_18_31        : 14;
        uint64_t odd_valid             : 1;  /**< [ 17: 17](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid            : 1;  /**< [ 16: 16](R/W/H) Error detected with even syndrome. */
        uint64_t odd_synd              : 8;  /**< [ 15:  8](R/W/H) Odd syndrome. */
        uint64_t even_synd             : 8;  /**< [  7:  0](R/W/H) Even syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t even_synd             : 8;  /**< [  7:  0](R/W/H) Even syndrome. */
        uint64_t odd_synd              : 8;  /**< [ 15:  8](R/W/H) Odd syndrome. */
        uint64_t even_valid            : 1;  /**< [ 16: 16](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid             : 1;  /**< [ 17: 17](R/W/H) Error detected with odd syndrome. */
        uint64_t reserved_18_31        : 14;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_mccx_mcix_ras_err00misc0_cn96xx cn98xx; */
    struct bdk_mccx_mcix_ras_err00misc0_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t odd_synd1             : 8;  /**< [ 63: 56](R/W/H) Odd syndrome. */
        uint64_t even_synd1            : 8;  /**< [ 55: 48](R/W/H) Even syndrome. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_20_31        : 12;
        uint64_t odd_valid1            : 1;  /**< [ 19: 19](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid1           : 1;  /**< [ 18: 18](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid0            : 1;  /**< [ 17: 17](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid0           : 1;  /**< [ 16: 16](R/W/H) Error detected with even syndrome. */
        uint64_t odd_synd0             : 8;  /**< [ 15:  8](R/W/H) Odd syndrome. */
        uint64_t even_synd0            : 8;  /**< [  7:  0](R/W/H) Even syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t even_synd0            : 8;  /**< [  7:  0](R/W/H) Even syndrome. */
        uint64_t odd_synd0             : 8;  /**< [ 15:  8](R/W/H) Odd syndrome. */
        uint64_t even_valid0           : 1;  /**< [ 16: 16](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid0            : 1;  /**< [ 17: 17](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid1           : 1;  /**< [ 18: 18](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid1            : 1;  /**< [ 19: 19](R/W/H) Error detected with odd syndrome. */
        uint64_t reserved_20_31        : 12;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t even_synd1            : 8;  /**< [ 55: 48](R/W/H) Even syndrome. */
        uint64_t odd_synd1             : 8;  /**< [ 63: 56](R/W/H) Odd syndrome. */
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_mcix_ras_err00misc0_cnf95xx loki; */
};
typedef union bdk_mccx_mcix_ras_err00misc0 bdk_mccx_mcix_ras_err00misc0_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410020ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410020ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410020ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410020ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR00MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR00MISC0(a,b) bdk_mccx_mcix_ras_err00misc0_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR00MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR00MISC0(a,b) "MCCX_MCIX_RAS_ERR00MISC0"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR00MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR00MISC0(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR00MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err00misc1
 *
 * MCC MCI RAS Error Record 00 Miscellaneous 1 Register
 * This register contains other record-specific implementation-defined information not
 * present in the corresponding status and address registers.
 *
 * See the individual per-record CSRs for the record-specific implementation-defined
 * meaning of each field.
 */
union bdk_mccx_mcix_ras_err00misc1
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err00misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err00misc1_s cn; */
};
typedef union bdk_mccx_mcix_ras_err00misc1 bdk_mccx_mcix_ras_err00misc1_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410028ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410028ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410028ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410028ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR00MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR00MISC1(a,b) bdk_mccx_mcix_ras_err00misc1_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR00MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR00MISC1(a,b) "MCCX_MCIX_RAS_ERR00MISC1"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR00MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR00MISC1(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR00MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err00status
 *
 * MCC MCI RAS Error Record 00 Primary Syndrome Register
 * This per-record register contains the error record. After reading the status
 * register, software must clear the valid bits to allow new errors to be recorded.
 * See the individual per-record CSRs for the record-specific values of each field.
 */
union bdk_mccx_mcix_ras_err00status
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err00status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid.  *_RAS_ERRnSTATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid.  *_RAS_ERRnSTATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err00status_s cn9; */
    /* struct bdk_mccx_mcix_ras_err00status_s cn96xxp1; */
    struct bdk_mccx_mcix_ras_err00status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid.  *_RAS_ERRnSTATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid.  *_RAS_ERRnSTATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_mcix_ras_err00status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_mcix_ras_err00status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_mcix_ras_err00status_cn96xxp3 loki; */
};
typedef union bdk_mccx_mcix_ras_err00status bdk_mccx_mcix_ras_err00status_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR00STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410010ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410010ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410010ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410010ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR00STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR00STATUS(a,b) bdk_mccx_mcix_ras_err00status_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR00STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR00STATUS(a,b) "MCCX_MCIX_RAS_ERR00STATUS"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR00STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR00STATUS(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR00STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err01addr
 *
 * MCC MCI RAS Error Record 01 Address Register
 * See MCC()_MCI()_RAS_ERR00ADDR.
 */
union bdk_mccx_mcix_ras_err01addr
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err01addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In ARM spec it is named NS. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In ARM spec it is named NS. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err01addr_s cn9; */
    /* struct bdk_mccx_mcix_ras_err01addr_s cn96xxp1; */
    struct bdk_mccx_mcix_ras_err01addr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In Arm spec it is named NS. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In Arm spec it is named NS. */
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_mcix_ras_err01addr_cn96xxp3 cn98xx; */
    struct bdk_mccx_mcix_ras_err01addr_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In Arm spec it is named NS. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t reserved_56_60        : 5;
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address first cache-line index. */
#else /* Word 0 - Little Endian */
        uint64_t paddr                 : 56; /**< [ 55:  0](R/W/H) Physical Address. Address of the recorded location.
                                                                 See CCS_ASC_REGION_* to extract system address.

                                                                 [55:51] = 0x0.
                                                                 [50:48] = FLMCMSK. Failing LMC mask.
                                                                 [47]    = FLRBIT.  Failing left/right bit.
                                                                 [46:43] = FAREM.   Failing address remainder number.
                                                                 [42:39] = FREGION. Failing ASC region matched.
                                                                 [38]    = FO.      Failing address bit 6 (Fill Order).
                                                                 [37: 3] = FOFFSET. Failing LLC/LMC address offset number.
                                                                 [2:0]   = FIDX.    Failing address first cache-line index. */
        uint64_t reserved_56_60        : 5;
        uint64_t ai                    : 1;  /**< [ 61: 61](RO) Address Incorrect. Indicates whether the PADDR field is a valid physical address that is
                                                                 known to match the programmers' view of the physical address for the recorded location.
                                                                 The possible values of this bit are:

                                                                 0 = The PADDR field is a valid physical address. That is, it matches the
                                                                     programmers' view of the physical address for the recorded location.
                                                                 1 = The PADDR field might not be a valid physical address, and might not
                                                                     match the programmers' view of the physical address for the recorded location. */
        uint64_t si                    : 1;  /**< [ 62: 62](RO) Secure Incorrect. Indicates whether the NS bit is valid. The possible values of this bit are:

                                                                 0 = The NS bit is correct. That is, it matches the programmers' view of the
                                                                     Nonsecure attribute for this recorded location.
                                                                 1 = The NS bit might not be correct, and might not match the programmers' view of the
                                                                     Nonsecure attribute for the recorded location. */
        uint64_t nsec                  : 1;  /**< [ 63: 63](R/W/H) Non-secure attribute. The possible values of this bit are:

                                                                 0 = The address is secure.
                                                                 1 = The address is nonsecure.

                                                                 Internal:
                                                                 In Arm spec it is named NS. */
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_mcix_ras_err01addr_cnf95xx loki; */
};
typedef union bdk_mccx_mcix_ras_err01addr bdk_mccx_mcix_ras_err01addr_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410058ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410058ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410058ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410058ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR01ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR01ADDR(a,b) bdk_mccx_mcix_ras_err01addr_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR01ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR01ADDR(a,b) "MCCX_MCIX_RAS_ERR01ADDR"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR01ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR01ADDR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR01ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err01ctlr
 *
 * MCC MCI RAS Error Record 01 Control Register
 * See MCC()_MCI()_RAS_ERR00CTLR.
 */
union bdk_mccx_mcix_ras_err01ctlr
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err01ctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err01ctlr_s cn; */
};
typedef union bdk_mccx_mcix_ras_err01ctlr bdk_mccx_mcix_ras_err01ctlr_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01CTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01CTLR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410048ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410048ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410048ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410048ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR01CTLR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR01CTLR(a,b) bdk_mccx_mcix_ras_err01ctlr_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR01CTLR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR01CTLR(a,b) "MCCX_MCIX_RAS_ERR01CTLR"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR01CTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR01CTLR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR01CTLR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err01fr
 *
 * MCC MCI RAS Error Record 01 Feature Register
 * See MCC()_MCI()_RAS_ERR00FR.
 */
union bdk_mccx_mcix_ras_err01fr
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err01fr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err01fr_s cn; */
};
typedef union bdk_mccx_mcix_ras_err01fr bdk_mccx_mcix_ras_err01fr_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01FR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01FR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410040ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410040ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410040ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410040ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR01FR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR01FR(a,b) bdk_mccx_mcix_ras_err01fr_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR01FR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR01FR(a,b) "MCCX_MCIX_RAS_ERR01FR"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR01FR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR01FR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR01FR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err01misc0
 *
 * MCC MCI RAS Error Record 01 Miscellaneous 0 Register
 * See MCC()_MCI()_RAS_ERR00MISC0.
 */
union bdk_mccx_mcix_ras_err01misc0
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err01misc0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t odd_synd1             : 8;  /**< [ 63: 56](R/W/H) Odd syndrome. */
        uint64_t even_synd1            : 8;  /**< [ 55: 48](R/W/H) Even syndrome. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_20_31        : 12;
        uint64_t odd_valid1            : 1;  /**< [ 19: 19](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid1           : 1;  /**< [ 18: 18](R/W/H) Error detected with even syndrome. */
        uint64_t reserved_0_17         : 18;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_17         : 18;
        uint64_t even_valid1           : 1;  /**< [ 18: 18](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid1            : 1;  /**< [ 19: 19](R/W/H) Error detected with odd syndrome. */
        uint64_t reserved_20_31        : 12;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t even_synd1            : 8;  /**< [ 55: 48](R/W/H) Even syndrome. */
        uint64_t odd_synd1             : 8;  /**< [ 63: 56](R/W/H) Odd syndrome. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err01misc0_s cn9; */
    struct bdk_mccx_mcix_ras_err01misc0_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_18_31        : 14;
        uint64_t odd_valid             : 1;  /**< [ 17: 17](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid            : 1;  /**< [ 16: 16](R/W/H) Error detected with even syndrome. */
        uint64_t odd_synd              : 8;  /**< [ 15:  8](R/W/H) Odd syndrome. */
        uint64_t even_synd             : 8;  /**< [  7:  0](R/W/H) Even syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t even_synd             : 8;  /**< [  7:  0](R/W/H) Even syndrome. */
        uint64_t odd_synd              : 8;  /**< [ 15:  8](R/W/H) Odd syndrome. */
        uint64_t even_valid            : 1;  /**< [ 16: 16](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid             : 1;  /**< [ 17: 17](R/W/H) Error detected with odd syndrome. */
        uint64_t reserved_18_31        : 14;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_mccx_mcix_ras_err01misc0_cn96xx cn98xx; */
    struct bdk_mccx_mcix_ras_err01misc0_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t odd_synd1             : 8;  /**< [ 63: 56](R/W/H) Odd syndrome. */
        uint64_t even_synd1            : 8;  /**< [ 55: 48](R/W/H) Even syndrome. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t reserved_20_31        : 12;
        uint64_t odd_valid1            : 1;  /**< [ 19: 19](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid1           : 1;  /**< [ 18: 18](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid0            : 1;  /**< [ 17: 17](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid0           : 1;  /**< [ 16: 16](R/W/H) Error detected with even syndrome. */
        uint64_t odd_synd0             : 8;  /**< [ 15:  8](R/W/H) Odd syndrome. */
        uint64_t even_synd0            : 8;  /**< [  7:  0](R/W/H) Even syndrome. */
#else /* Word 0 - Little Endian */
        uint64_t even_synd0            : 8;  /**< [  7:  0](R/W/H) Even syndrome. */
        uint64_t odd_synd0             : 8;  /**< [ 15:  8](R/W/H) Odd syndrome. */
        uint64_t even_valid0           : 1;  /**< [ 16: 16](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid0            : 1;  /**< [ 17: 17](R/W/H) Error detected with odd syndrome. */
        uint64_t even_valid1           : 1;  /**< [ 18: 18](R/W/H) Error detected with even syndrome. */
        uint64_t odd_valid1            : 1;  /**< [ 19: 19](R/W/H) Error detected with odd syndrome. */
        uint64_t reserved_20_31        : 12;
        uint64_t cec                   : 15; /**< [ 46: 32](R/W/H) Corrected error count. */
        uint64_t of                    : 1;  /**< [ 47: 47](R/W/H) Sticky overflow bit.
                                                                 0 = Counter has not overflowed.
                                                                 1 = Counter has overflowed.

                                                                 The fault handling interrupt is generated when the corrected fault handling interrupt is
                                                                 enabled and the
                                                                 overflow bit is set to 1.

                                                                 For CNXXXX, CE counter is not implemented, always 0. */
        uint64_t even_synd1            : 8;  /**< [ 55: 48](R/W/H) Even syndrome. */
        uint64_t odd_synd1             : 8;  /**< [ 63: 56](R/W/H) Odd syndrome. */
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_mcix_ras_err01misc0_cnf95xx loki; */
};
typedef union bdk_mccx_mcix_ras_err01misc0 bdk_mccx_mcix_ras_err01misc0_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01MISC0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01MISC0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410060ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410060ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410060ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410060ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR01MISC0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR01MISC0(a,b) bdk_mccx_mcix_ras_err01misc0_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR01MISC0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR01MISC0(a,b) "MCCX_MCIX_RAS_ERR01MISC0"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR01MISC0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR01MISC0(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR01MISC0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err01misc1
 *
 * MCC MCI RAS Error Record 01 Miscellaneous 1 Register
 * See MCC()_MCI()_RAS_ERR00MISC1.
 */
union bdk_mccx_mcix_ras_err01misc1
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err01misc1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err01misc1_s cn; */
};
typedef union bdk_mccx_mcix_ras_err01misc1 bdk_mccx_mcix_ras_err01misc1_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01MISC1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01MISC1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410068ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410068ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410068ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410068ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR01MISC1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR01MISC1(a,b) bdk_mccx_mcix_ras_err01misc1_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR01MISC1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR01MISC1(a,b) "MCCX_MCIX_RAS_ERR01MISC1"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR01MISC1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR01MISC1(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR01MISC1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_err01status
 *
 * MCC MCI RAS Error Record 01 Primary Syndrome Register
 * See MCC()_MCI()_RAS_ERR00STATUS.
 */
union bdk_mccx_mcix_ras_err01status
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_err01status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid.  *_RAS_ERRnSTATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the ARM RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid.  *_RAS_ERRnSTATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_err01status_s cn9; */
    /* struct bdk_mccx_mcix_ras_err01status_s cn96xxp1; */
    struct bdk_mccx_mcix_ras_err01status_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid.  *_RAS_ERRnSTATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t reserved_16_19        : 4;
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
#else /* Word 0 - Little Endian */
        uint64_t serr                  : 8;  /**< [  7:  0](RO) Architecturally-defined primary error code. Indicates the type of error
                                                                 enumerated by RAS_SERR_E.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write.

                                                                 For CNXXXX, value depends on the error record. */
        uint64_t ierr                  : 8;  /**< [ 15:  8](RO) Implementation-defined error code.

                                                                 Direct writes to this field are ignored if any of the [CE], [DE], or [UE] is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_16_19        : 4;
        uint64_t uet                   : 2;  /**< [ 21: 20](R/W1C/H) Uncorrected error type. Describes the state of the component after detecting
                                                                 or consuming an uncorrected error. Enumerated by RAS_UET_E.

                                                                 Valid only if [UE] is set, otherwise 0x0.

                                                                 Direct writes to this field are ignored if any of [CE], [DE], or [UE] is set,
                                                                 and the highest priority of these is not being cleared to 0 in the same write. */
        uint64_t pn                    : 1;  /**< [ 22: 22](R/W1C/H) Poison.
                                                                 0 = Uncorrected or deferred error from a corrupted value. If a node
                                                                 detects a corrupted value and defers the error by producing poison, then this
                                                                 bit is set to 0 at the producer node.

                                                                 1 = Uncorrected error or Deferred error from a poisoned value. Indicates that an
                                                                 error was due to detecting a poison value rather than detecting a corrupted
                                                                 value. */
        uint64_t de                    : 1;  /**< [ 23: 23](R/W1C/H) Deferred error(s). At least one error was not corrected and deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared
                                                                 to 0 in the same write. */
        uint64_t ce                    : 2;  /**< [ 25: 24](R/W1C/H) Corrected error:
                                                                   0x0 = No corrected errors recorded.
                                                                   0x1 = At least one transient corrected error recored.
                                                                   0x2 = At least one corrected error recored.
                                                                   0x3 = At least one persistent corrected error recored.

                                                                 For CNXXXX, only codes 0x0 and 0x3 are used. */
        uint64_t mv                    : 1;  /**< [ 26: 26](R/W1C/H) Miscellaneous registers valid. The *_RAS_ERRnMISC0 and *_RAS_ERRnMISC1 contains
                                                                 additional information for an error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write. This
                                                                 bit is read/write-one-to-clear. */
        uint64_t of                    : 1;  /**< [ 27: 27](R/W1C/H) Overflow. Multiple errors detected. This bit is set when:

                                                                 * An uncorrected error is detected and the previous error syndrome is kept
                                                                 because [UE] = 1.

                                                                 * A deferred error is detected and the previous error syndrome is kept is
                                                                 discarded because [DE] = 1.

                                                                 * A corrected error is detected and the corrected error counter overflows (or
                                                                 is not implemented).

                                                                 For more information see the Arm RAS standard. */
        uint64_t er                    : 1;  /**< [ 28: 28](RO) Error reported.
                                                                 0 = No external abort reported.
                                                                 1 = The applicable one of the *_RAS_ERRnCTLR[WUE],[RUE],[UE] bits was set when
                                                                 an uncorrected error was detected, meaning an external abort was signaled to the
                                                                 master making the access.

                                                                 Direct writes to this bit are ignored if any of [CE], [DE], or [UE] is set, and
                                                                 the highest priority of these is not being cleared to 0 in the same write.

                                                                 Cleared for a corrected error. */
        uint64_t ue                    : 1;  /**< [ 29: 29](R/W1C/H) Uncorrected error(s).
                                                                 0 = No errors that could not be corrected or deferred.
                                                                 1 = At least one error detected that has not been corrected or deferred.

                                                                 Direct writes to this bit are ignored if [OF] is set and is not being cleared to
                                                                 zero in the same write. */
        uint64_t v                     : 1;  /**< [ 30: 30](R/W1C/H) Status register valid.  *_RAS_ERRnSTATUS valid. At least one error has been recorded.

                                                                 Direct writes to this bit are ignored if any of the [UE], [DE], or [CE] bits is
                                                                 set and is not being cleared to 0 in the same write. */
        uint64_t av                    : 1;  /**< [ 31: 31](R/W1C/H) Address valid. *_RAS_ERRnADDR contains a physical address associated with the
                                                                 highest priority error recorded by this record.

                                                                 Direct writes to this bit are ignored if any of the [CE], [DE], or [UE] bits is
                                                                 set, and the highest priority of these is not being cleared to 0 in the same
                                                                 write. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_mcix_ras_err01status_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_mcix_ras_err01status_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_mcix_ras_err01status_cn96xxp3 loki; */
};
typedef union bdk_mccx_mcix_ras_err01status bdk_mccx_mcix_ras_err01status_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERR01STATUS(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410050ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410050ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410050ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410050ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERR01STATUS", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERR01STATUS(a,b) bdk_mccx_mcix_ras_err01status_t
#define bustype_BDK_MCCX_MCIX_RAS_ERR01STATUS(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERR01STATUS(a,b) "MCCX_MCIX_RAS_ERR01STATUS"
#define device_bar_BDK_MCCX_MCIX_RAS_ERR01STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERR01STATUS(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERR01STATUS(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errcidr0
 *
 * MCC MCI RAS Component Identification Register 0
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errcidr0
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errcidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errcidr0_s cn; */
};
typedef union bdk_mccx_mcix_ras_errcidr0 bdk_mccx_mcix_ras_errcidr0_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRCIDR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRCIDR0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ff0ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ff0ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410ff0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410ff0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRCIDR0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRCIDR0(a,b) bdk_mccx_mcix_ras_errcidr0_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRCIDR0(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRCIDR0(a,b) "MCCX_MCIX_RAS_ERRCIDR0"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRCIDR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRCIDR0(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRCIDR0(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errcidr1
 *
 * MCC MCI RAS Component Identification Register 1
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errcidr1
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errcidr1_s
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
    /* struct bdk_mccx_mcix_ras_errcidr1_s cn; */
};
typedef union bdk_mccx_mcix_ras_errcidr1 bdk_mccx_mcix_ras_errcidr1_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRCIDR1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRCIDR1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ff4ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ff4ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410ff4ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410ff4ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRCIDR1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRCIDR1(a,b) bdk_mccx_mcix_ras_errcidr1_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRCIDR1(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRCIDR1(a,b) "MCCX_MCIX_RAS_ERRCIDR1"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRCIDR1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRCIDR1(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRCIDR1(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errcidr2
 *
 * MCC MCI RAS Component Identification Register 2
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errcidr2
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errcidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errcidr2_s cn; */
};
typedef union bdk_mccx_mcix_ras_errcidr2 bdk_mccx_mcix_ras_errcidr2_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRCIDR2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRCIDR2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ff8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ff8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410ff8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410ff8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRCIDR2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRCIDR2(a,b) bdk_mccx_mcix_ras_errcidr2_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRCIDR2(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRCIDR2(a,b) "MCCX_MCIX_RAS_ERRCIDR2"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRCIDR2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRCIDR2(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRCIDR2(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errcidr3
 *
 * MCC MCI RAS Component Identification Register 3
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errcidr3
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errcidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errcidr3_s cn; */
};
typedef union bdk_mccx_mcix_ras_errcidr3 bdk_mccx_mcix_ras_errcidr3_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRCIDR3(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRCIDR3(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ffcll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ffcll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410ffcll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410ffcll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRCIDR3", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRCIDR3(a,b) bdk_mccx_mcix_ras_errcidr3_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRCIDR3(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRCIDR3(a,b) "MCCX_MCIX_RAS_ERRCIDR3"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRCIDR3(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRCIDR3(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRCIDR3(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_errdevaff
 *
 * MCC MCI RAS Device Affinity Register
 * For a group that has an affinity to a PE or cluster of PEs, this register is a
 * read-only copy of AP_MPIDR_EL1.
 */
union bdk_mccx_mcix_ras_errdevaff
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_errdevaff_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t aff3                  : 8;  /**< [ 39: 32](RO) Reserved. */
        uint64_t fov                   : 1;  /**< [ 31: 31](RO) If set, the [AFF0] fields are valid.
                                                                 For noncore RAS blocks, this is zero and all other fields are zero. */
        uint64_t u                     : 1;  /**< [ 30: 30](RO) Set to indicate processor is part of a multiprocessor system. */
        uint64_t reserved_25_29        : 5;
        uint64_t mt                    : 1;  /**< [ 24: 24](RO) Set to indicate multithreaded, and [AFF0] is thread number in core. */
        uint64_t aff2                  : 8;  /**< [ 23: 16](RO) Affinity 2. In CNXXXX, the node id. */
        uint64_t aff1                  : 8;  /**< [ 15:  8](RO) Affinity 1. In CNXXXX, the cluster id within a node. */
        uint64_t aff0                  : 8;  /**< [  7:  0](RO) Affinity 0. In CNXXXX, the core number within a cluster. */
#else /* Word 0 - Little Endian */
        uint64_t aff0                  : 8;  /**< [  7:  0](RO) Affinity 0. In CNXXXX, the core number within a cluster. */
        uint64_t aff1                  : 8;  /**< [ 15:  8](RO) Affinity 1. In CNXXXX, the cluster id within a node. */
        uint64_t aff2                  : 8;  /**< [ 23: 16](RO) Affinity 2. In CNXXXX, the node id. */
        uint64_t mt                    : 1;  /**< [ 24: 24](RO) Set to indicate multithreaded, and [AFF0] is thread number in core. */
        uint64_t reserved_25_29        : 5;
        uint64_t u                     : 1;  /**< [ 30: 30](RO) Set to indicate processor is part of a multiprocessor system. */
        uint64_t fov                   : 1;  /**< [ 31: 31](RO) If set, the [AFF0] fields are valid.
                                                                 For noncore RAS blocks, this is zero and all other fields are zero. */
        uint64_t aff3                  : 8;  /**< [ 39: 32](RO) Reserved. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errdevaff_s cn; */
};
typedef union bdk_mccx_mcix_ras_errdevaff bdk_mccx_mcix_ras_errdevaff_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRDEVAFF(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRDEVAFF(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fa8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fa8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fa8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fa8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRDEVAFF", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRDEVAFF(a,b) bdk_mccx_mcix_ras_errdevaff_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRDEVAFF(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERRDEVAFF(a,b) "MCCX_MCIX_RAS_ERRDEVAFF"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRDEVAFF(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRDEVAFF(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRDEVAFF(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errdevarch
 *
 * MCC MCI RAS Device Architecture Register
 * This register identifies the programmers' model architecture of the component.
 */
union bdk_mccx_mcix_ras_errdevarch
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errdevarch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. Indicates ARM. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to 1, indicates that this register is present. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archver               : 4;  /**< [ 15: 12](RO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archpart              : 12; /**< [ 11:  0](RO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
#else /* Word 0 - Little Endian */
        uint32_t archpart              : 12; /**< [ 11:  0](RO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
        uint32_t archver               : 4;  /**< [ 15: 12](RO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to 1, indicates that this register is present. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. Indicates ARM. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errdevarch_s cn9; */
    /* struct bdk_mccx_mcix_ras_errdevarch_s cn96xxp1; */
    struct bdk_mccx_mcix_ras_errdevarch_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. Indicates Arm. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to 1, indicates that this register is present. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archver               : 4;  /**< [ 15: 12](RO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t archpart              : 12; /**< [ 11:  0](RO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
#else /* Word 0 - Little Endian */
        uint32_t archpart              : 12; /**< [ 11:  0](RO) Defines the architecture of the component.
                                                                 0xA00 = RAS system architecture. */
        uint32_t archver               : 4;  /**< [ 15: 12](RO) Defines the architecture version of the component.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision.
                                                                 0x0 = RAS system architecture v1.0. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to 1, indicates that this register is present. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. Indicates Arm. */
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mccx_mcix_ras_errdevarch_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_mcix_ras_errdevarch_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_mcix_ras_errdevarch_cn96xxp3 loki; */
};
typedef union bdk_mccx_mcix_ras_errdevarch bdk_mccx_mcix_ras_errdevarch_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRDEVARCH(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRDEVARCH(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fbcll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fbcll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fbcll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fbcll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRDEVARCH", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRDEVARCH(a,b) bdk_mccx_mcix_ras_errdevarch_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRDEVARCH(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRDEVARCH(a,b) "MCCX_MCIX_RAS_ERRDEVARCH"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRDEVARCH(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRDEVARCH(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRDEVARCH(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errdevid
 *
 * MCC MCI RAS Error Record Device ID Register
 * Defines the highest numbered index of the error records that can be accessed
 * through the Error Record registers.
 */
union bdk_mccx_mcix_ras_errdevid
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errdevid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t num                   : 16; /**< [ 15:  0](RO) Highest numbered index of the error records that can be accessed. */
#else /* Word 0 - Little Endian */
        uint32_t num                   : 16; /**< [ 15:  0](RO) Highest numbered index of the error records that can be accessed. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errdevid_s cn; */
};
typedef union bdk_mccx_mcix_ras_errdevid bdk_mccx_mcix_ras_errdevid_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRDEVID(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRDEVID(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fc8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fc8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fc8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fc8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRDEVID", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRDEVID(a,b) bdk_mccx_mcix_ras_errdevid_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRDEVID(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRDEVID(a,b) "MCCX_MCIX_RAS_ERRDEVID"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRDEVID(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRDEVID(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRDEVID(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_errgsr0
 *
 * MCC MCI RAS Error Group Status Register
 * This register shows the status for the records in the group.
 */
union bdk_mccx_mcix_ras_errgsr0
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_errgsr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t s                     : 64; /**< [ 63:  0](RO/H) Shows the status for the records, a read-only copy of MCC()_LMCOE()_RAS_ERR00STATUS[V]:
                                                                    0 = No error.
                                                                    1 = One or more errors.

                                                                 Each bit corresponds to the status for 64 records, in groups of
                                                                 64 determined by the address index to this register.

                                                                 Bits above the maximum implemented index number (MCC()_LMCOE()_RAS_ERRDEVID[NUM]) are 0. */
#else /* Word 0 - Little Endian */
        uint64_t s                     : 64; /**< [ 63:  0](RO/H) Shows the status for the records, a read-only copy of MCC()_LMCOE()_RAS_ERR00STATUS[V]:
                                                                    0 = No error.
                                                                    1 = One or more errors.

                                                                 Each bit corresponds to the status for 64 records, in groups of
                                                                 64 determined by the address index to this register.

                                                                 Bits above the maximum implemented index number (MCC()_LMCOE()_RAS_ERRDEVID[NUM]) are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errgsr0_s cn; */
};
typedef union bdk_mccx_mcix_ras_errgsr0 bdk_mccx_mcix_ras_errgsr0_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRGSR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRGSR0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e00ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e00ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410e00ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410e00ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRGSR0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRGSR0(a,b) bdk_mccx_mcix_ras_errgsr0_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRGSR0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERRGSR0(a,b) "MCCX_MCIX_RAS_ERRGSR0"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRGSR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRGSR0(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRGSR0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_errirqcr0
 *
 * MCC MCI RAS Error Interrupt Configuration Register 0
 * This register configures interrupt delivery.
 */
union bdk_mccx_mcix_ras_errirqcr0
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_errirqcr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) Message Signaled Interrupt address. Specifies the address that the node writes to
                                                                 Signaling an interrupt. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) Message Signaled Interrupt address. Specifies the address that the node writes to
                                                                 Signaling an interrupt. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errirqcr0_s cn; */
};
typedef union bdk_mccx_mcix_ras_errirqcr0 bdk_mccx_mcix_ras_errirqcr0_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQCR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQCR0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e80ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e80ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410e80ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410e80ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRIRQCR0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRIRQCR0(a,b) bdk_mccx_mcix_ras_errirqcr0_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRIRQCR0(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERRIRQCR0(a,b) "MCCX_MCIX_RAS_ERRIRQCR0"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRIRQCR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRIRQCR0(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRIRQCR0(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_errirqcr1
 *
 * MCC MCI RAS Error Interrupt Configuration Register 1
 * This register configures interrupt delivery.
 */
union bdk_mccx_mcix_ras_errirqcr1
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_errirqcr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errirqcr1_s cn; */
};
typedef union bdk_mccx_mcix_ras_errirqcr1 bdk_mccx_mcix_ras_errirqcr1_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQCR1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQCR1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e88ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e88ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410e88ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410e88ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRIRQCR1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRIRQCR1(a,b) bdk_mccx_mcix_ras_errirqcr1_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRIRQCR1(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERRIRQCR1(a,b) "MCCX_MCIX_RAS_ERRIRQCR1"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRIRQCR1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRIRQCR1(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRIRQCR1(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_errirqcr2
 *
 * MCC MCI RAS Error Interrupt Configuration Register 2
 * This register configures interrupt delivery.
 */
union bdk_mccx_mcix_ras_errirqcr2
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_errirqcr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errirqcr2_s cn; */
};
typedef union bdk_mccx_mcix_ras_errirqcr2 bdk_mccx_mcix_ras_errirqcr2_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQCR2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQCR2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e90ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e90ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410e90ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410e90ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRIRQCR2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRIRQCR2(a,b) bdk_mccx_mcix_ras_errirqcr2_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRIRQCR2(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERRIRQCR2(a,b) "MCCX_MCIX_RAS_ERRIRQCR2"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRIRQCR2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRIRQCR2(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRIRQCR2(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_errirqcr3
 *
 * MCC MCI RAS Error Interrupt Configuration Register 3
 * This register configures interrupt delivery.
 */
union bdk_mccx_mcix_ras_errirqcr3
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_errirqcr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errirqcr3_s cn; */
};
typedef union bdk_mccx_mcix_ras_errirqcr3 bdk_mccx_mcix_ras_errirqcr3_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQCR3(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQCR3(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e98ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410e98ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410e98ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410e98ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRIRQCR3", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRIRQCR3(a,b) bdk_mccx_mcix_ras_errirqcr3_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRIRQCR3(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERRIRQCR3(a,b) "MCCX_MCIX_RAS_ERRIRQCR3"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRIRQCR3(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRIRQCR3(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRIRQCR3(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_errirqsr
 *
 * MCC MCI RAS Error Interrupt Status Register
 * This register uses the recommended Arm interrupt configuration register format.
 */
union bdk_mccx_mcix_ras_errirqsr
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_errirqsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t erierr                : 1;  /**< [  3:  3](RO) Error recovery interrupt error.
                                                                 0 = Error recovery interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Error recovery interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t eri                   : 1;  /**< [  2:  2](RO) Error recovery interrupt write in progress.
                                                                 0 = Error recovery interrupt write not in progress.
                                                                 1 = Error recovery interrupt write in progress.

                                                                 In CNXXXX, reads same as [FHI].

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
        uint64_t fhierr                : 1;  /**< [  1:  1](RO) Fault handling interrupt error.
                                                                 0 = Fault handling interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Fault handling interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t fhi                   : 1;  /**< [  0:  0](RO/H) Fault handling interrupt write in progress.
                                                                 0 = Fault handling interrupt write not in progress.
                                                                 1 = Fault handling interrupt write in progress.

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
#else /* Word 0 - Little Endian */
        uint64_t fhi                   : 1;  /**< [  0:  0](RO/H) Fault handling interrupt write in progress.
                                                                 0 = Fault handling interrupt write not in progress.
                                                                 1 = Fault handling interrupt write in progress.

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
        uint64_t fhierr                : 1;  /**< [  1:  1](RO) Fault handling interrupt error.
                                                                 0 = Fault handling interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Fault handling interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t eri                   : 1;  /**< [  2:  2](RO) Error recovery interrupt write in progress.
                                                                 0 = Error recovery interrupt write not in progress.
                                                                 1 = Error recovery interrupt write in progress.

                                                                 In CNXXXX, reads same as [FHI].

                                                                 Internal:
                                                                 Connects to GIB/GIA counter being nonzero. */
        uint64_t erierr                : 1;  /**< [  3:  3](RO) Error recovery interrupt error.
                                                                 0 = Error recovery interrupt write has not returned an error since this bit was
                                                                 last cleared to 0.
                                                                 1 = Error recovery interrupt write has returned an error since this bit was last
                                                                 cleared to 0.

                                                                 In CNXXXX, always 0. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errirqsr_s cn; */
};
typedef union bdk_mccx_mcix_ras_errirqsr bdk_mccx_mcix_ras_errirqsr_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQSR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRIRQSR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ef8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410ef8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410ef8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410ef8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRIRQSR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRIRQSR(a,b) bdk_mccx_mcix_ras_errirqsr_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRIRQSR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_ERRIRQSR(a,b) "MCCX_MCIX_RAS_ERRIRQSR"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRIRQSR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRIRQSR(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRIRQSR(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errpidr0
 *
 * MCC MCI RAS Peripheral Identification Register 0
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errpidr0
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errpidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::RAS_MCC. */
#else /* Word 0 - Little Endian */
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::RAS_MCC. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errpidr0_s cn; */
};
typedef union bdk_mccx_mcix_ras_errpidr0 bdk_mccx_mcix_ras_errpidr0_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR0(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fe0ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fe0ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fe0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fe0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRPIDR0", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRPIDR0(a,b) bdk_mccx_mcix_ras_errpidr0_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRPIDR0(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRPIDR0(a,b) "MCCX_MCIX_RAS_ERRPIDR0"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRPIDR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRPIDR0(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRPIDR0(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errpidr1
 *
 * MCC MCI RAS Peripheral Identification Register 1
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errpidr1
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errpidr1_s
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
    /* struct bdk_mccx_mcix_ras_errpidr1_s cn9; */
    /* struct bdk_mccx_mcix_ras_errpidr1_s cn96xxp1; */
    struct bdk_mccx_mcix_ras_errpidr1_cn96xxp3
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
    /* struct bdk_mccx_mcix_ras_errpidr1_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_mcix_ras_errpidr1_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_mcix_ras_errpidr1_cn96xxp3 loki; */
};
typedef union bdk_mccx_mcix_ras_errpidr1 bdk_mccx_mcix_ras_errpidr1_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR1(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fe4ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fe4ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fe4ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fe4ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRPIDR1", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRPIDR1(a,b) bdk_mccx_mcix_ras_errpidr1_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRPIDR1(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRPIDR1(a,b) "MCCX_MCIX_RAS_ERRPIDR1"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRPIDR1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRPIDR1(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRPIDR1(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errpidr2
 *
 * MCC MCI RAS Peripheral Identification Register 2
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errpidr2
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errpidr2_s
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
    /* struct bdk_mccx_mcix_ras_errpidr2_s cn9; */
    /* struct bdk_mccx_mcix_ras_errpidr2_s cn96xxp1; */
    struct bdk_mccx_mcix_ras_errpidr2_cn96xxp3
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
    /* struct bdk_mccx_mcix_ras_errpidr2_s cn98xx; */
    /* struct bdk_mccx_mcix_ras_errpidr2_s cnf95xx; */
    /* struct bdk_mccx_mcix_ras_errpidr2_s loki; */
};
typedef union bdk_mccx_mcix_ras_errpidr2 bdk_mccx_mcix_ras_errpidr2_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR2(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fe8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fe8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fe8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fe8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRPIDR2", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRPIDR2(a,b) bdk_mccx_mcix_ras_errpidr2_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRPIDR2(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRPIDR2(a,b) "MCCX_MCIX_RAS_ERRPIDR2"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRPIDR2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRPIDR2(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRPIDR2(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errpidr3
 *
 * MCC MCI RAS Peripheral Identification Register 3
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errpidr3
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errpidr3_s
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
    /* struct bdk_mccx_mcix_ras_errpidr3_s cn; */
};
typedef union bdk_mccx_mcix_ras_errpidr3 bdk_mccx_mcix_ras_errpidr3_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR3(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR3(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fecll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fecll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fecll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fecll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRPIDR3", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRPIDR3(a,b) bdk_mccx_mcix_ras_errpidr3_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRPIDR3(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRPIDR3(a,b) "MCCX_MCIX_RAS_ERRPIDR3"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRPIDR3(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRPIDR3(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRPIDR3(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errpidr4
 *
 * MCC MCI RAS Peripheral Identification Register 4
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errpidr4
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errpidr4_s
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
    /* struct bdk_mccx_mcix_ras_errpidr4_s cn9; */
    /* struct bdk_mccx_mcix_ras_errpidr4_s cn96xxp1; */
    struct bdk_mccx_mcix_ras_errpidr4_cn96xxp3
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
    /* struct bdk_mccx_mcix_ras_errpidr4_s cn98xx; */
    /* struct bdk_mccx_mcix_ras_errpidr4_s cnf95xx; */
    /* struct bdk_mccx_mcix_ras_errpidr4_s loki; */
};
typedef union bdk_mccx_mcix_ras_errpidr4 bdk_mccx_mcix_ras_errpidr4_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR4(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR4(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fd0ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fd0ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fd0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fd0ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRPIDR4", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRPIDR4(a,b) bdk_mccx_mcix_ras_errpidr4_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRPIDR4(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRPIDR4(a,b) "MCCX_MCIX_RAS_ERRPIDR4"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRPIDR4(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRPIDR4(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRPIDR4(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errpidr5
 *
 * MCC MCI RAS Peripheral Identification Register 5
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errpidr5
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errpidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errpidr5_s cn; */
};
typedef union bdk_mccx_mcix_ras_errpidr5 bdk_mccx_mcix_ras_errpidr5_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR5(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR5(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fd4ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fd4ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fd4ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fd4ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRPIDR5", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRPIDR5(a,b) bdk_mccx_mcix_ras_errpidr5_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRPIDR5(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRPIDR5(a,b) "MCCX_MCIX_RAS_ERRPIDR5"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRPIDR5(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRPIDR5(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRPIDR5(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errpidr6
 *
 * RAS Peripheral Identification Register 6
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errpidr6
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errpidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errpidr6_s cn; */
};
typedef union bdk_mccx_mcix_ras_errpidr6 bdk_mccx_mcix_ras_errpidr6_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR6(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR6(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fd8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fd8ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fd8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fd8ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRPIDR6", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRPIDR6(a,b) bdk_mccx_mcix_ras_errpidr6_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRPIDR6(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRPIDR6(a,b) "MCCX_MCIX_RAS_ERRPIDR6"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRPIDR6(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRPIDR6(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRPIDR6(a,b) (a),(b),-1,-1

/**
 * Register (RSL32b) mcc#_mci#_ras_errpidr7
 *
 * MCC MCI RAS Peripheral Identification Register 7
 * This register provides information to identify a debug component.
 */
union bdk_mccx_mcix_ras_errpidr7
{
    uint32_t u;
    struct bdk_mccx_mcix_ras_errpidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_errpidr7_s cn; */
};
typedef union bdk_mccx_mcix_ras_errpidr7 bdk_mccx_mcix_ras_errpidr7_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR7(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_ERRPIDR7(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fdcll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c410fdcll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c410fdcll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c410fdcll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_ERRPIDR7", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_ERRPIDR7(a,b) bdk_mccx_mcix_ras_errpidr7_t
#define bustype_BDK_MCCX_MCIX_RAS_ERRPIDR7(a,b) BDK_CSR_TYPE_RSL32b
#define basename_BDK_MCCX_MCIX_RAS_ERRPIDR7(a,b) "MCCX_MCIX_RAS_ERRPIDR7"
#define device_bar_BDK_MCCX_MCIX_RAS_ERRPIDR7(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_ERRPIDR7(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_ERRPIDR7(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_int
 *
 * MCC MCI RAS Interrupt Clear Register
 * This register contains the different interrupt-summary bits of the MCC MCI RAS.
 */
union bdk_mccx_mcix_ras_int
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t err01                 : 1;  /**< [  1:  1](RO/H) Interrupt for uncorrectable error from the mesh. Clear this field by writing a 1 to
                                                                 MCC()_MCI()_RAS_ERR01STATUS[V]. */
        uint64_t err00                 : 1;  /**< [  0:  0](RO/H) Interrupt for correctable error from the mesh. Clear this field by writing a 1 to
                                                                 MCC()_MCI()_RAS_ERR00STATUS[V]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](RO/H) Interrupt for correctable error from the mesh. Clear this field by writing a 1 to
                                                                 MCC()_MCI()_RAS_ERR00STATUS[V]. */
        uint64_t err01                 : 1;  /**< [  1:  1](RO/H) Interrupt for uncorrectable error from the mesh. Clear this field by writing a 1 to
                                                                 MCC()_MCI()_RAS_ERR01STATUS[V]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_int_s cn; */
};
typedef union bdk_mccx_mcix_ras_int bdk_mccx_mcix_ras_int_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_INT(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400300ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400300ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400300ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400300ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_INT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_INT(a,b) bdk_mccx_mcix_ras_int_t
#define bustype_BDK_MCCX_MCIX_RAS_INT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_INT(a,b) "MCCX_MCIX_RAS_INT"
#define device_bar_BDK_MCCX_MCIX_RAS_INT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_INT(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_INT(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_int_ena_w1c
 *
 * MCC MCI RAS Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_mccx_mcix_ras_int_ena_w1c
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0..1)_MCI(0..1)_RAS_INT[ERR01]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_int_ena_w1c_s cn9; */
    /* struct bdk_mccx_mcix_ras_int_ena_w1c_s cn96xx; */
    /* struct bdk_mccx_mcix_ras_int_ena_w1c_s cn98xx; */
    struct bdk_mccx_mcix_ras_int_ena_w1c_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MCC(0)_MCI(0)_RAS_INT[ERR01]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_mcix_ras_int_ena_w1c_cnf95xx loki; */
};
typedef union bdk_mccx_mcix_ras_int_ena_w1c bdk_mccx_mcix_ras_int_ena_w1c_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_INT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_INT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400310ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400310ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400310ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400310ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_INT_ENA_W1C", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_INT_ENA_W1C(a,b) bdk_mccx_mcix_ras_int_ena_w1c_t
#define bustype_BDK_MCCX_MCIX_RAS_INT_ENA_W1C(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_INT_ENA_W1C(a,b) "MCCX_MCIX_RAS_INT_ENA_W1C"
#define device_bar_BDK_MCCX_MCIX_RAS_INT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_INT_ENA_W1C(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_INT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_int_ena_w1s
 *
 * MCC MCI RAS Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_mccx_mcix_ras_int_ena_w1s
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0..1)_MCI(0..1)_RAS_INT[ERR01]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_int_ena_w1s_s cn9; */
    /* struct bdk_mccx_mcix_ras_int_ena_w1s_s cn96xx; */
    /* struct bdk_mccx_mcix_ras_int_ena_w1s_s cn98xx; */
    struct bdk_mccx_mcix_ras_int_ena_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_RAS_INT[ERR01]. */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_RAS_INT[ERR00]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_RAS_INT[ERR00]. */
        uint64_t err01                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MCC(0)_MCI(0)_RAS_INT[ERR01]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_mccx_mcix_ras_int_ena_w1s_cnf95xx loki; */
};
typedef union bdk_mccx_mcix_ras_int_ena_w1s bdk_mccx_mcix_ras_int_ena_w1s_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_INT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_INT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400318ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400318ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400318ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400318ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_INT_ENA_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_INT_ENA_W1S(a,b) bdk_mccx_mcix_ras_int_ena_w1s_t
#define bustype_BDK_MCCX_MCIX_RAS_INT_ENA_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_INT_ENA_W1S(a,b) "MCCX_MCIX_RAS_INT_ENA_W1S"
#define device_bar_BDK_MCCX_MCIX_RAS_INT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_INT_ENA_W1S(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_INT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (RSL) mcc#_mci#_ras_int_w1s
 *
 * MCC MCI RAS Interrupt Set Register
 */
union bdk_mccx_mcix_ras_int_w1s
{
    uint64_t u;
    struct bdk_mccx_mcix_ras_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t err01                 : 1;  /**< [  1:  1](RO/H) Interrupt for uncorrectable error from the mesh. Clear this field by writing a 1 to
                                                                 MCC()_MCI()_RAS_ERR01STATUS[V]. */
        uint64_t err00                 : 1;  /**< [  0:  0](RO/H) Interrupt for correctable error from the mesh. Clear this field by writing a 1 to
                                                                 MCC()_MCI()_RAS_ERR00STATUS[V]. */
#else /* Word 0 - Little Endian */
        uint64_t err00                 : 1;  /**< [  0:  0](RO/H) Interrupt for correctable error from the mesh. Clear this field by writing a 1 to
                                                                 MCC()_MCI()_RAS_ERR00STATUS[V]. */
        uint64_t err01                 : 1;  /**< [  1:  1](RO/H) Interrupt for uncorrectable error from the mesh. Clear this field by writing a 1 to
                                                                 MCC()_MCI()_RAS_ERR01STATUS[V]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_ras_int_w1s_s cn; */
};
typedef union bdk_mccx_mcix_ras_int_w1s bdk_mccx_mcix_ras_int_w1s_t;

static inline uint64_t BDK_MCCX_MCIX_RAS_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RAS_INT_W1S(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400308ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400308ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400308ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400308ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RAS_INT_W1S", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_RAS_INT_W1S(a,b) bdk_mccx_mcix_ras_int_w1s_t
#define bustype_BDK_MCCX_MCIX_RAS_INT_W1S(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_RAS_INT_W1S(a,b) "MCCX_MCIX_RAS_INT_W1S"
#define device_bar_BDK_MCCX_MCIX_RAS_INT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_RAS_INT_W1S(a,b) (a)
#define arguments_BDK_MCCX_MCIX_RAS_INT_W1S(a,b) (a),(b),-1,-1

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
        uint64_t reserved_47_63        : 17;
        uint64_t flmcmsk               : 3;  /**< [ 46: 44](RO/H) Failing LMC mask. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flmcmsk               : 3;  /**< [ 46: 44](RO/H) Failing LMC mask. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_47_63        : 17;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_rddislmc_fadr_s cn; */
};
typedef union bdk_mccx_mcix_rddislmc_fadr bdk_mccx_mcix_rddislmc_fadr_t;

static inline uint64_t BDK_MCCX_MCIX_RDDISLMC_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_RDDISLMC_FADR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400220ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400220ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400220ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400220ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_RDDISLMC_FADR", 2, a, b, 0, 0, 0, 0);
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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400058ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400058ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400058ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400058ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_SBE_DBG_CNT", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) bdk_mccx_mcix_sbe_dbg_cnt_t
#define bustype_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) "MCCX_MCIX_SBE_DBG_CNT"
#define device_bar_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) (a)
#define arguments_BDK_MCCX_MCIX_SBE_DBG_CNT(a,b) (a),(b),-1,-1

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
        uint64_t reserved_47_63        : 17;
        uint64_t flmcmsk               : 3;  /**< [ 46: 44](RO/H) Failing LMC mask. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
#else /* Word 0 - Little Endian */
        uint64_t fadr                  : 35; /**< [ 34:  0](RO/H) Failing address offset number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t fregion               : 4;  /**< [ 38: 35](RO/H) Failing ASC region matched. See CCS_ASC_REGION_* to extract system address. */
        uint64_t farem                 : 4;  /**< [ 42: 39](RO/H) Failing address remainder number. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flrbit                : 1;  /**< [ 43: 43](RO/H) Failing left/right bit. See CCS_ASC_REGION_* to extract system address. */
        uint64_t flmcmsk               : 3;  /**< [ 46: 44](RO/H) Failing LMC mask. See CCS_ASC_REGION_* to extract system address. */
        uint64_t reserved_47_63        : 17;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mccx_mcix_wrdislmc_fadr_s cn; */
};
typedef union bdk_mccx_mcix_wrdislmc_fadr bdk_mccx_mcix_wrdislmc_fadr_t;

static inline uint64_t BDK_MCCX_MCIX_WRDISLMC_FADR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MCIX_WRDISLMC_FADR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400228ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=1)))
        return 0x87e03c400228ll + 0x1000000ll * ((a) & 0x1) + 0x100000ll * ((b) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03c400228ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03c400228ll + 0x1000000ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MCIX_WRDISLMC_FADR", 2, a, b, 0, 0, 0, 0);
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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b==0)))
        return 0x87e03cff0000ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b==0)))
        return 0x87e03cff0000ll + 0x1000000ll * ((a) & 0x1) + 8ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b==0)))
        return 0x87e03cff0000ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b==0)))
        return 0x87e03cff0000ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("MCCX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
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
    /* struct bdk_mccx_msix_vecx_addr_s cn9; */
    /* struct bdk_mccx_msix_vecx_addr_s cn96xxp1; */
    struct bdk_mccx_msix_vecx_addr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's MCC()_MSIX_VEC()_ADDR, MCC()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MCC()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

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

                                                                 1 = This vector's MCC()_MSIX_VEC()_ADDR, MCC()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MCC()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

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
    /* struct bdk_mccx_msix_vecx_addr_cn96xxp3 cn98xx; */
    /* struct bdk_mccx_msix_vecx_addr_cn96xxp3 cnf95xx; */
    /* struct bdk_mccx_msix_vecx_addr_cn96xxp3 loki; */
};
typedef union bdk_mccx_msix_vecx_addr bdk_mccx_msix_vecx_addr_t;

static inline uint64_t BDK_MCCX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MCCX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=7)))
        return 0x87e03cf00000ll + 0x1000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=9)))
        return 0x87e03cf00000ll + 0x1000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=6)))
        return 0x87e03cf00000ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=6)))
        return 0x87e03cf00000ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x7);
    __bdk_csr_fatal("MCCX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
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
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=1) && (b<=7)))
        return 0x87e03cf00008ll + 0x1000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=9)))
        return 0x87e03cf00008ll + 0x1000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0xf);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=6)))
        return 0x87e03cf00008ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=6)))
        return 0x87e03cf00008ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x7);
    __bdk_csr_fatal("MCCX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
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
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e03c000070ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e03c000070ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e03c000070ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e03c000070ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("MCCX_SCRAMBLE_CFG0", 1, a, 0, 0, 0, 0, 0);
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
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=1))
        return 0x87e03c000078ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x87e03c000078ll + 0x1000000ll * ((a) & 0x1);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e03c000078ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e03c000078ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("MCCX_SCRAMBLE_CFG1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MCCX_SCRAMBLE_CFG1(a) bdk_mccx_scramble_cfg1_t
#define bustype_BDK_MCCX_SCRAMBLE_CFG1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MCCX_SCRAMBLE_CFG1(a) "MCCX_SCRAMBLE_CFG1"
#define device_bar_BDK_MCCX_SCRAMBLE_CFG1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MCCX_SCRAMBLE_CFG1(a) (a)
#define arguments_BDK_MCCX_SCRAMBLE_CFG1(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_MCC_H__ */
