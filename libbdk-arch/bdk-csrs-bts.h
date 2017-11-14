#ifndef __BDK_CSRS_BTS_H__
#define __BDK_CSRS_BTS_H__
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
 * Cavium BTS.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration bts_bar_e
 *
 * BTS Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_BTS_BAR_E_BTS_PF_BAR0 (0x87e012000000ll)
#define BDK_BTS_BAR_E_BTS_PF_BAR0_SIZE 0x10000ull
#define BDK_BTS_BAR_E_BTS_PF_BAR4 (0x87e012f00000ll)
#define BDK_BTS_BAR_E_BTS_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration bts_int_vec_e
 *
 * BTS MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_BTS_INT_VEC_E_BTS_PDBANK0_DONE (0)
#define BDK_BTS_INT_VEC_E_BTS_PDBANK1_DONE (1)
#define BDK_BTS_INT_VEC_E_BTS_PDBANK2_DONE (2)
#define BDK_BTS_INT_VEC_E_BTS_PDBANK3_DONE (3)
#define BDK_BTS_INT_VEC_E_BTS_PDBANK4_DONE (4)
#define BDK_BTS_INT_VEC_E_BTS_PDBANK5_DONE (5)

/**
 * Enumeration bts_pd1pps_div_cfg0_ref_in_sel_e
 *
 * BTS Reference Input Select Enumeration
 * Enumerates BTS_PD1PPS_DIV_CFG0[REF_IN_SEL].
 */
#define BDK_BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E_EXT_REF0_1PPS (3)
#define BDK_BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E_EXT_REF1_1PPS (4)
#define BDK_BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E_EXT_REF2_1PPS (5)
#define BDK_BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E_PD_BFN_1PPS (2)
#define BDK_BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E_PTP_1PPS (1)
#define BDK_BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E_RSVD0_1PPS (6)
#define BDK_BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E_RSVD1_1PPS (7)
#define BDK_BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E_RSVD_GNSS_1PPS (0)

/**
 * Enumeration bts_pd_slicex_ctl_ref_in_sel_e
 *
 * BTS Slice Input Select Enumeration
 * Enumerates BTS_PD_SLICE()_CTL[REF_IN_SEL].
 */
#define BDK_BTS_PD_SLICEX_CTL_REF_IN_SEL_E_CG_1PPS (3)
#define BDK_BTS_PD_SLICEX_CTL_REF_IN_SEL_E_EXT_REF0_1PPS (4)
#define BDK_BTS_PD_SLICEX_CTL_REF_IN_SEL_E_EXT_REF1_1PPS (5)
#define BDK_BTS_PD_SLICEX_CTL_REF_IN_SEL_E_EXT_REF2_1PPS (6)
#define BDK_BTS_PD_SLICEX_CTL_REF_IN_SEL_E_PD_BFN_1PPS (2)
#define BDK_BTS_PD_SLICEX_CTL_REF_IN_SEL_E_PTP_1PPS (1)
#define BDK_BTS_PD_SLICEX_CTL_REF_IN_SEL_E_RSVD0_1PPS (7)
#define BDK_BTS_PD_SLICEX_CTL_REF_IN_SEL_E_RSVD_GNSS_1PPS (0)

/**
 * Enumeration bts_pdbfn_div_cfg0_ref_in_sel_e
 *
 * BTS Division Input Select Enumeration
 * Enumerates BTS_PDBFN_DIV_CFG0[REF_IN_SEL].
 */
#define BDK_BTS_PDBFN_DIV_CFG0_REF_IN_SEL_E_CG_1PPS (2)
#define BDK_BTS_PDBFN_DIV_CFG0_REF_IN_SEL_E_EXT_REF0_1PPS (3)
#define BDK_BTS_PDBFN_DIV_CFG0_REF_IN_SEL_E_EXT_REF1_1PPS (4)
#define BDK_BTS_PDBFN_DIV_CFG0_REF_IN_SEL_E_EXT_REF2_1PPS (5)
#define BDK_BTS_PDBFN_DIV_CFG0_REF_IN_SEL_E_PTP_1PPS (1)
#define BDK_BTS_PDBFN_DIV_CFG0_REF_IN_SEL_E_RSVD0_1PPS (6)
#define BDK_BTS_PDBFN_DIV_CFG0_REF_IN_SEL_E_RSVD1_1PPS (7)
#define BDK_BTS_PDBFN_DIV_CFG0_REF_IN_SEL_E_RSVD_GNSS_1PPS (0)

/**
 * Enumeration bts_pwm_ctl_tick_sel_e
 *
 * BTS PWM Tick Selection Enumeration
 * Enumerates BTS_PWM_CTL[TICK_SEL].
 */
#define BDK_BTS_PWM_CTL_TICK_SEL_E_DIV16 (4)
#define BDK_BTS_PWM_CTL_TICK_SEL_E_DIV2 (1)
#define BDK_BTS_PWM_CTL_TICK_SEL_E_DIV32 (5)
#define BDK_BTS_PWM_CTL_TICK_SEL_E_DIV4 (2)
#define BDK_BTS_PWM_CTL_TICK_SEL_E_DIV8 (3)
#define BDK_BTS_PWM_CTL_TICK_SEL_E_RSVD0 (6)
#define BDK_BTS_PWM_CTL_TICK_SEL_E_RSVD1 (7)
#define BDK_BTS_PWM_CTL_TICK_SEL_E_RSVD_DIV1 (0)

/**
 * Register (RSL) bts_cg_1pps_cfg
 *
 * BTS CG 1PPS Configuration Register
 */
union bdk_bts_cg_1pps_cfg
{
    uint64_t u;
    struct bdk_bts_cg_1pps_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t reverse               : 1;  /**< [  0:  0](R/W) Set to 1 to invert the polarity of the CG_1PPS signal. */
#else /* Word 0 - Little Endian */
        uint64_t reverse               : 1;  /**< [  0:  0](R/W) Set to 1 to invert the polarity of the CG_1PPS signal. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_cg_1pps_cfg_s cn; */
};
typedef union bdk_bts_cg_1pps_cfg bdk_bts_cg_1pps_cfg_t;

#define BDK_BTS_CG_1PPS_CFG BDK_BTS_CG_1PPS_CFG_FUNC()
static inline uint64_t BDK_BTS_CG_1PPS_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_CG_1PPS_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000260ll;
    __bdk_csr_fatal("BTS_CG_1PPS_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_CG_1PPS_CFG bdk_bts_cg_1pps_cfg_t
#define bustype_BDK_BTS_CG_1PPS_CFG BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_CG_1PPS_CFG "BTS_CG_1PPS_CFG"
#define device_bar_BDK_BTS_CG_1PPS_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_CG_1PPS_CFG 0
#define arguments_BDK_BTS_CG_1PPS_CFG -1,-1,-1,-1

/**
 * Register (RSL) bts_cg_cfg
 *
 * BTS Clock Generation Configuration Register
 */
union bdk_bts_cg_cfg
{
    uint64_t u;
    struct bdk_bts_cg_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_46_63        : 18;
        uint64_t cnt_max_125us         : 14; /**< [ 45: 32](R/W) Maximum value for the 125 us counter used to time the BFN data signal.
                                                                 Set to the number of cycles per 125 us minus 1. Default is 0xEFF
                                                                 (3839) for a BFN clock. */
        uint64_t reserved_20_31        : 12;
        uint64_t cnt_max_10ms          : 20; /**< [ 19:  0](R/W) Maximum value for the 10 ms counter used for the BTS_RFP_OUT signal. Set to
                                                                 the number of cycles per 10 ms minus 1. Default is 0x4AFFFF (307199)
                                                                 for a BFN clock. */
#else /* Word 0 - Little Endian */
        uint64_t cnt_max_10ms          : 20; /**< [ 19:  0](R/W) Maximum value for the 10 ms counter used for the BTS_RFP_OUT signal. Set to
                                                                 the number of cycles per 10 ms minus 1. Default is 0x4AFFFF (307199)
                                                                 for a BFN clock. */
        uint64_t reserved_20_31        : 12;
        uint64_t cnt_max_125us         : 14; /**< [ 45: 32](R/W) Maximum value for the 125 us counter used to time the BFN data signal.
                                                                 Set to the number of cycles per 125 us minus 1. Default is 0xEFF
                                                                 (3839) for a BFN clock. */
        uint64_t reserved_46_63        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_cg_cfg_s cn; */
};
typedef union bdk_bts_cg_cfg bdk_bts_cg_cfg_t;

#define BDK_BTS_CG_CFG BDK_BTS_CG_CFG_FUNC()
static inline uint64_t BDK_BTS_CG_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_CG_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000408ll;
    __bdk_csr_fatal("BTS_CG_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_CG_CFG bdk_bts_cg_cfg_t
#define bustype_BDK_BTS_CG_CFG BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_CG_CFG "BTS_CG_CFG"
#define device_bar_BDK_BTS_CG_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_CG_CFG 0
#define arguments_BDK_BTS_CG_CFG -1,-1,-1,-1

/**
 * Register (RSL) bts_cg_ctl
 *
 * BTS Clock Generation Control Register
 * This register controls the BFN and clocks produced by the clock generator.
 */
union bdk_bts_cg_ctl
{
    uint64_t u;
    struct bdk_bts_cg_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sw_1pps_delay         : 32; /**< [ 63: 32](R/W) Delay between PD_1PPS and CG_1PPS in 30.72 MHz cycles. */
        uint64_t reserved_28_31        : 4;
        uint64_t sw_bfn                : 12; /**< [ 27: 16](R/W) BFN sequence start number. This value is only loaded by hardware when
                                                                 [SW_BFN_2MSB_VLD]=1 or [SW_BFN_10LSB_VLD]=1. */
        uint64_t smcell                : 1;  /**< [ 15: 15](R/W) Small cell mode:
                                                                 0 = Bypass clock generator and output BTS_RFP_OUT and BTS_BFN_OUT directly from
                                                                 external pins (i.e., BTS_RFP_IN and BTS_BFN_IN).
                                                                 1 = Output RFP and BFN produced by clock generator. */
        uint64_t reserved_5_14         : 10;
        uint64_t sw_bfn_2msb_vld       : 1;  /**< [  4:  4](R/W/H) Set by software to indicate [SW_BFN] bits \<11:10\> are valid. The BFN
                                                                 value will be updated at the next SW_1PPS pulse. Hardware will
                                                                 automatically clear this bit once the value has been updated. */
        uint64_t reserved_1_3          : 3;
        uint64_t sw_bfn_10lsb_vld      : 1;  /**< [  0:  0](R/W/H) Set by software to indicate [SW_BFN] bits \<9:0\> are valid. The BFN
                                                                 value will be updated at the next SW_1PPS pulse. Hardware will
                                                                 automatically clear this bit once the value has been updated. */
#else /* Word 0 - Little Endian */
        uint64_t sw_bfn_10lsb_vld      : 1;  /**< [  0:  0](R/W/H) Set by software to indicate [SW_BFN] bits \<9:0\> are valid. The BFN
                                                                 value will be updated at the next SW_1PPS pulse. Hardware will
                                                                 automatically clear this bit once the value has been updated. */
        uint64_t reserved_1_3          : 3;
        uint64_t sw_bfn_2msb_vld       : 1;  /**< [  4:  4](R/W/H) Set by software to indicate [SW_BFN] bits \<11:10\> are valid. The BFN
                                                                 value will be updated at the next SW_1PPS pulse. Hardware will
                                                                 automatically clear this bit once the value has been updated. */
        uint64_t reserved_5_14         : 10;
        uint64_t smcell                : 1;  /**< [ 15: 15](R/W) Small cell mode:
                                                                 0 = Bypass clock generator and output BTS_RFP_OUT and BTS_BFN_OUT directly from
                                                                 external pins (i.e., BTS_RFP_IN and BTS_BFN_IN).
                                                                 1 = Output RFP and BFN produced by clock generator. */
        uint64_t sw_bfn                : 12; /**< [ 27: 16](R/W) BFN sequence start number. This value is only loaded by hardware when
                                                                 [SW_BFN_2MSB_VLD]=1 or [SW_BFN_10LSB_VLD]=1. */
        uint64_t reserved_28_31        : 4;
        uint64_t sw_1pps_delay         : 32; /**< [ 63: 32](R/W) Delay between PD_1PPS and CG_1PPS in 30.72 MHz cycles. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_cg_ctl_s cn; */
};
typedef union bdk_bts_cg_ctl bdk_bts_cg_ctl_t;

#define BDK_BTS_CG_CTL BDK_BTS_CG_CTL_FUNC()
static inline uint64_t BDK_BTS_CG_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_CG_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000400ll;
    __bdk_csr_fatal("BTS_CG_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_CG_CTL bdk_bts_cg_ctl_t
#define bustype_BDK_BTS_CG_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_CG_CTL "BTS_CG_CTL"
#define device_bar_BDK_BTS_CG_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_CG_CTL 0
#define arguments_BDK_BTS_CG_CTL -1,-1,-1,-1

/**
 * Register (RSL) bts_csclk_active_pc
 *
 * BTS Conditional Coprocessor Clock Counter Register
 * This register counts conditional clocks for power management.
 *
 * This register is reset on chip reset.
 */
union bdk_bts_csclk_active_pc
{
    uint64_t u;
    struct bdk_bts_csclk_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_csclk_active_pc_s cn; */
};
typedef union bdk_bts_csclk_active_pc bdk_bts_csclk_active_pc_t;

#define BDK_BTS_CSCLK_ACTIVE_PC BDK_BTS_CSCLK_ACTIVE_PC_FUNC()
static inline uint64_t BDK_BTS_CSCLK_ACTIVE_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_CSCLK_ACTIVE_PC_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000020ll;
    __bdk_csr_fatal("BTS_CSCLK_ACTIVE_PC", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_CSCLK_ACTIVE_PC bdk_bts_csclk_active_pc_t
#define bustype_BDK_BTS_CSCLK_ACTIVE_PC BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_CSCLK_ACTIVE_PC "BTS_CSCLK_ACTIVE_PC"
#define device_bar_BDK_BTS_CSCLK_ACTIVE_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_CSCLK_ACTIVE_PC 0
#define arguments_BDK_BTS_CSCLK_ACTIVE_PC -1,-1,-1,-1

/**
 * Register (RSL) bts_dac_clk_ctl
 *
 * BTS DAC Clock Control Register
 */
union bdk_bts_dac_clk_ctl
{
    uint64_t u;
    struct bdk_bts_dac_clk_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t div                   : 4;  /**< [  3:  0](R/W) The BTS_DAC_CLK divider. The output BTS_DAC_CLK will have frequency of (BTS_BFN_CLK / (2 x
                                                                 (DIV + 4))). E.g., set DIV=3 to output BTS_BFN_CLK/14.

                                                                 Note. Do not change while PWM is enabled. */
#else /* Word 0 - Little Endian */
        uint64_t div                   : 4;  /**< [  3:  0](R/W) The BTS_DAC_CLK divider. The output BTS_DAC_CLK will have frequency of (BTS_BFN_CLK / (2 x
                                                                 (DIV + 4))). E.g., set DIV=3 to output BTS_BFN_CLK/14.

                                                                 Note. Do not change while PWM is enabled. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_dac_clk_ctl_s cn; */
};
typedef union bdk_bts_dac_clk_ctl bdk_bts_dac_clk_ctl_t;

#define BDK_BTS_DAC_CLK_CTL BDK_BTS_DAC_CLK_CTL_FUNC()
static inline uint64_t BDK_BTS_DAC_CLK_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_DAC_CLK_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000880ll;
    __bdk_csr_fatal("BTS_DAC_CLK_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_DAC_CLK_CTL bdk_bts_dac_clk_ctl_t
#define bustype_BDK_BTS_DAC_CLK_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_DAC_CLK_CTL "BTS_DAC_CLK_CTL"
#define device_bar_BDK_BTS_DAC_CLK_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_DAC_CLK_CTL 0
#define arguments_BDK_BTS_DAC_CLK_CTL -1,-1,-1,-1

/**
 * Register (RSL) bts_eco
 *
 * INTERNAL: BTS ECO Register
 *
 * An ECO CSR.
 */
union bdk_bts_eco
{
    uint64_t u;
    struct bdk_bts_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t eco_rw                : 64; /**< [ 63:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 64; /**< [ 63:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_eco_s cn; */
};
typedef union bdk_bts_eco bdk_bts_eco_t;

#define BDK_BTS_ECO BDK_BTS_ECO_FUNC()
static inline uint64_t BDK_BTS_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_ECO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000090ll;
    __bdk_csr_fatal("BTS_ECO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_ECO bdk_bts_eco_t
#define bustype_BDK_BTS_ECO BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_ECO "BTS_ECO"
#define device_bar_BDK_BTS_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_ECO 0
#define arguments_BDK_BTS_ECO -1,-1,-1,-1

/**
 * Register (RSL) bts_ext_ref#_div_cfg0
 *
 * BTS External Reference (0..2) Divider Configuration 0 Register
 * This register configures the clock divider used to generate a 1PPS signal
 * from external reference clock 0..2 (i.e., BTS_EXTREF(0..2)_CLK).
 * Do not change these during operation.
 */
union bdk_bts_ext_refx_div_cfg0
{
    uint64_t u;
    struct bdk_bts_ext_refx_div_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t clkout_bypass         : 1;  /**< [  3:  3](R/W) Set to 1 to bypass the clock divider (clock out = BTS_EXTREF(0)_CLK). */
        uint64_t clkout_inv            : 1;  /**< [  2:  2](R/W) Set to 1 to inverse the clock output polarity. */
        uint64_t clkout_5050_duty      : 1;  /**< [  1:  1](R/W) Clock divider duty cycle:
                                                                 0 = One cycle pulse (i.e., one cycle of external reference clock).
                                                                 1 = 50/50 duty-cycle. */
        uint64_t divider_en            : 1;  /**< [  0:  0](R/W) Set to 1 to enable the clock divider. The divider counter is reset to 0 when
                                                                 [DIVIDER_EN] is set to 0 and the clock output is disabled. */
#else /* Word 0 - Little Endian */
        uint64_t divider_en            : 1;  /**< [  0:  0](R/W) Set to 1 to enable the clock divider. The divider counter is reset to 0 when
                                                                 [DIVIDER_EN] is set to 0 and the clock output is disabled. */
        uint64_t clkout_5050_duty      : 1;  /**< [  1:  1](R/W) Clock divider duty cycle:
                                                                 0 = One cycle pulse (i.e., one cycle of external reference clock).
                                                                 1 = 50/50 duty-cycle. */
        uint64_t clkout_inv            : 1;  /**< [  2:  2](R/W) Set to 1 to inverse the clock output polarity. */
        uint64_t clkout_bypass         : 1;  /**< [  3:  3](R/W) Set to 1 to bypass the clock divider (clock out = BTS_EXTREF(0)_CLK). */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_ext_refx_div_cfg0_s cn; */
};
typedef union bdk_bts_ext_refx_div_cfg0 bdk_bts_ext_refx_div_cfg0_t;

static inline uint64_t BDK_BTS_EXT_REFX_DIV_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_EXT_REFX_DIV_CFG0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x87e012000700ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("BTS_EXT_REFX_DIV_CFG0", 1, a, 0, 0, 0);
}

#define typedef_BDK_BTS_EXT_REFX_DIV_CFG0(a) bdk_bts_ext_refx_div_cfg0_t
#define bustype_BDK_BTS_EXT_REFX_DIV_CFG0(a) BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_EXT_REFX_DIV_CFG0(a) "BTS_EXT_REFX_DIV_CFG0"
#define device_bar_BDK_BTS_EXT_REFX_DIV_CFG0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_EXT_REFX_DIV_CFG0(a) (a)
#define arguments_BDK_BTS_EXT_REFX_DIV_CFG0(a) (a),-1,-1,-1

/**
 * Register (RSL) bts_ext_ref#_div_cfg1
 *
 * BTS External Reference (0..2) Divider Configuration 1 Register
 * This register configures the clock divider used to generate a 1PPS signal
 * from external reference clock 0 (i.e., BTS_EXTREF(0..2)_CLK).
 * Do not change these during operation.
 */
union bdk_bts_ext_refx_div_cfg1
{
    uint64_t u;
    struct bdk_bts_ext_refx_div_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t divider_start_pos     : 32; /**< [ 63: 32](R/W) Divider start position. When a new value is written to
                                                                 [DIVIDER_START_POS], the counter will reset to 0 the next time the
                                                                 counter value is equal to [DIVIDER_START_POS]. Subsequently, the counter
                                                                 will reset to 0 when the counter is equal to [DIVIDER_TC].

                                                                 Writing [DIVIDER_START_POS] effectively applies a positive phase shift
                                                                 of [DIVIDER_START_POS]+1 cycles to the 1PPS signal.

                                                                 Note that a phase shift is only applied when this value changes, thus
                                                                 it might be necessary to write this field to zero before applying a
                                                                 new phase shift. */
        uint64_t divider_tc            : 32; /**< [ 31:  0](R/W) Divider counter terminal count value.

                                                                 When BTS_EXT_REF(0..2)_DIV_CFG0[CLKOUT_5050_DUTY]=0, this field should be
                                                                 set to the clock frequency minus one.

                                                                 When BTS_EXT_REF(0..2)_DIV_CFG0[CLKOUT_5050_DUTY]=1, this field should be
                                                                 set to half the clock frequency minus one. */
#else /* Word 0 - Little Endian */
        uint64_t divider_tc            : 32; /**< [ 31:  0](R/W) Divider counter terminal count value.

                                                                 When BTS_EXT_REF(0..2)_DIV_CFG0[CLKOUT_5050_DUTY]=0, this field should be
                                                                 set to the clock frequency minus one.

                                                                 When BTS_EXT_REF(0..2)_DIV_CFG0[CLKOUT_5050_DUTY]=1, this field should be
                                                                 set to half the clock frequency minus one. */
        uint64_t divider_start_pos     : 32; /**< [ 63: 32](R/W) Divider start position. When a new value is written to
                                                                 [DIVIDER_START_POS], the counter will reset to 0 the next time the
                                                                 counter value is equal to [DIVIDER_START_POS]. Subsequently, the counter
                                                                 will reset to 0 when the counter is equal to [DIVIDER_TC].

                                                                 Writing [DIVIDER_START_POS] effectively applies a positive phase shift
                                                                 of [DIVIDER_START_POS]+1 cycles to the 1PPS signal.

                                                                 Note that a phase shift is only applied when this value changes, thus
                                                                 it might be necessary to write this field to zero before applying a
                                                                 new phase shift. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_ext_refx_div_cfg1_s cn; */
};
typedef union bdk_bts_ext_refx_div_cfg1 bdk_bts_ext_refx_div_cfg1_t;

static inline uint64_t BDK_BTS_EXT_REFX_DIV_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_EXT_REFX_DIV_CFG1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=2))
        return 0x87e012000708ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("BTS_EXT_REFX_DIV_CFG1", 1, a, 0, 0, 0);
}

#define typedef_BDK_BTS_EXT_REFX_DIV_CFG1(a) bdk_bts_ext_refx_div_cfg1_t
#define bustype_BDK_BTS_EXT_REFX_DIV_CFG1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_EXT_REFX_DIV_CFG1(a) "BTS_EXT_REFX_DIV_CFG1"
#define device_bar_BDK_BTS_EXT_REFX_DIV_CFG1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_EXT_REFX_DIV_CFG1(a) (a)
#define arguments_BDK_BTS_EXT_REFX_DIV_CFG1(a) (a),-1,-1,-1

/**
 * Register (RSL) bts_global_ctl
 *
 * BTS Global Control Register
 */
union bdk_bts_global_ctl
{
    uint64_t u;
    struct bdk_bts_global_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t bts_enable            : 1;  /**< [  9:  9](R/W) Set to 1 to enable the BTS clock. */
        uint64_t reserved_6_8          : 3;
        uint64_t mon_bfn_clk_en        : 1;  /**< [  5:  5](R/W) Set to 1 to enable 61.44 MHz clock divider and its output (491 MHz/8).
                                                                 The 61.44 MHz can be output to BTS_TP2 by setting
                                                                 BTS_TP_MUX_SEL[TP2_SEL] = 0x6. */
        uint64_t ptp_1pps_out_en       : 1;  /**< [  4:  4](R/W) Set to 1 to enable PTP 1 pps output to the PTP_1PPS_OUT external pin. */
        uint64_t reserved_3            : 1;
        uint64_t dac_clk_en            : 1;  /**< [  2:  2](R/W) Set to 1 to enable BTS_DAC_CLK external pin output of the (30.72 MHz/14) clock
                                                                 divider. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t dac_clk_en            : 1;  /**< [  2:  2](R/W) Set to 1 to enable BTS_DAC_CLK external pin output of the (30.72 MHz/14) clock
                                                                 divider. */
        uint64_t reserved_3            : 1;
        uint64_t ptp_1pps_out_en       : 1;  /**< [  4:  4](R/W) Set to 1 to enable PTP 1 pps output to the PTP_1PPS_OUT external pin. */
        uint64_t mon_bfn_clk_en        : 1;  /**< [  5:  5](R/W) Set to 1 to enable 61.44 MHz clock divider and its output (491 MHz/8).
                                                                 The 61.44 MHz can be output to BTS_TP2 by setting
                                                                 BTS_TP_MUX_SEL[TP2_SEL] = 0x6. */
        uint64_t reserved_6_8          : 3;
        uint64_t bts_enable            : 1;  /**< [  9:  9](R/W) Set to 1 to enable the BTS clock. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_global_ctl_s cn; */
};
typedef union bdk_bts_global_ctl bdk_bts_global_ctl_t;

#define BDK_BTS_GLOBAL_CTL BDK_BTS_GLOBAL_CTL_FUNC()
static inline uint64_t BDK_BTS_GLOBAL_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_GLOBAL_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000010ll;
    __bdk_csr_fatal("BTS_GLOBAL_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_GLOBAL_CTL bdk_bts_global_ctl_t
#define bustype_BDK_BTS_GLOBAL_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_GLOBAL_CTL "BTS_GLOBAL_CTL"
#define device_bar_BDK_BTS_GLOBAL_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_GLOBAL_CTL 0
#define arguments_BDK_BTS_GLOBAL_CTL -1,-1,-1,-1

/**
 * Register (RSL) bts_global_status
 *
 * BTS Status Register
 */
union bdk_bts_global_status
{
    uint64_t u;
    struct bdk_bts_global_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t bts_pll_lock          : 1;  /**< [  0:  0](RO/H) BTS hardware sets to one when the BTS PLL is locked. */
#else /* Word 0 - Little Endian */
        uint64_t bts_pll_lock          : 1;  /**< [  0:  0](RO/H) BTS hardware sets to one when the BTS PLL is locked. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_global_status_s cn; */
};
typedef union bdk_bts_global_status bdk_bts_global_status_t;

#define BDK_BTS_GLOBAL_STATUS BDK_BTS_GLOBAL_STATUS_FUNC()
static inline uint64_t BDK_BTS_GLOBAL_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_GLOBAL_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000018ll;
    __bdk_csr_fatal("BTS_GLOBAL_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_GLOBAL_STATUS bdk_bts_global_status_t
#define bustype_BDK_BTS_GLOBAL_STATUS BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_GLOBAL_STATUS "BTS_GLOBAL_STATUS"
#define device_bar_BDK_BTS_GLOBAL_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_GLOBAL_STATUS 0
#define arguments_BDK_BTS_GLOBAL_STATUS -1,-1,-1,-1

/**
 * Register (RSL) bts_int_sum_ena_w1c
 *
 * BTS Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_bts_int_sum_ena_w1c
{
    uint64_t u;
    struct bdk_bts_int_sum_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t pdbank5_done          : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK5_DONE]. */
        uint64_t pdbank4_done          : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK4_DONE]. */
        uint64_t pdbank3_done          : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK3_DONE]. */
        uint64_t pdbank2_done          : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK2_DONE]. */
        uint64_t pdbank1_done          : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK1_DONE]. */
        uint64_t pdbank0_done          : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK0_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t pdbank0_done          : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK0_DONE]. */
        uint64_t pdbank1_done          : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK1_DONE]. */
        uint64_t pdbank2_done          : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK2_DONE]. */
        uint64_t pdbank3_done          : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK3_DONE]. */
        uint64_t pdbank4_done          : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK4_DONE]. */
        uint64_t pdbank5_done          : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for BTS_INT_SUM_W1C[PDBANK5_DONE]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_int_sum_ena_w1c_s cn; */
};
typedef union bdk_bts_int_sum_ena_w1c bdk_bts_int_sum_ena_w1c_t;

#define BDK_BTS_INT_SUM_ENA_W1C BDK_BTS_INT_SUM_ENA_W1C_FUNC()
static inline uint64_t BDK_BTS_INT_SUM_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_INT_SUM_ENA_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012001148ll;
    __bdk_csr_fatal("BTS_INT_SUM_ENA_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_INT_SUM_ENA_W1C bdk_bts_int_sum_ena_w1c_t
#define bustype_BDK_BTS_INT_SUM_ENA_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_INT_SUM_ENA_W1C "BTS_INT_SUM_ENA_W1C"
#define device_bar_BDK_BTS_INT_SUM_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_INT_SUM_ENA_W1C 0
#define arguments_BDK_BTS_INT_SUM_ENA_W1C -1,-1,-1,-1

/**
 * Register (RSL) bts_int_sum_ena_w1s
 *
 * BTS Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_bts_int_sum_ena_w1s
{
    uint64_t u;
    struct bdk_bts_int_sum_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t pdbank5_done          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK5_DONE]. */
        uint64_t pdbank4_done          : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK4_DONE]. */
        uint64_t pdbank3_done          : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK3_DONE]. */
        uint64_t pdbank2_done          : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK2_DONE]. */
        uint64_t pdbank1_done          : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK1_DONE]. */
        uint64_t pdbank0_done          : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK0_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t pdbank0_done          : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK0_DONE]. */
        uint64_t pdbank1_done          : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK1_DONE]. */
        uint64_t pdbank2_done          : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK2_DONE]. */
        uint64_t pdbank3_done          : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK3_DONE]. */
        uint64_t pdbank4_done          : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK4_DONE]. */
        uint64_t pdbank5_done          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for BTS_INT_SUM_W1C[PDBANK5_DONE]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_int_sum_ena_w1s_s cn; */
};
typedef union bdk_bts_int_sum_ena_w1s bdk_bts_int_sum_ena_w1s_t;

#define BDK_BTS_INT_SUM_ENA_W1S BDK_BTS_INT_SUM_ENA_W1S_FUNC()
static inline uint64_t BDK_BTS_INT_SUM_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_INT_SUM_ENA_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012001150ll;
    __bdk_csr_fatal("BTS_INT_SUM_ENA_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_INT_SUM_ENA_W1S bdk_bts_int_sum_ena_w1s_t
#define bustype_BDK_BTS_INT_SUM_ENA_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_INT_SUM_ENA_W1S "BTS_INT_SUM_ENA_W1S"
#define device_bar_BDK_BTS_INT_SUM_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_INT_SUM_ENA_W1S 0
#define arguments_BDK_BTS_INT_SUM_ENA_W1S -1,-1,-1,-1

/**
 * Register (RSL) bts_int_sum_w1c
 *
 * BTS Interrupt Summary Clear Register
 * This register contains the status for various BTS interrupts.
 */
union bdk_bts_int_sum_w1c
{
    uint64_t u;
    struct bdk_bts_int_sum_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t pdbank5_done          : 1;  /**< [  5:  5](R/W1C/H) Phase difference measurement done on PD bank 5. */
        uint64_t pdbank4_done          : 1;  /**< [  4:  4](R/W1C/H) Phase difference measurement done on PD bank 4. */
        uint64_t pdbank3_done          : 1;  /**< [  3:  3](R/W1C/H) Phase difference measurement done on PD bank 3. */
        uint64_t pdbank2_done          : 1;  /**< [  2:  2](R/W1C/H) Phase difference measurement done on PD bank 2. */
        uint64_t pdbank1_done          : 1;  /**< [  1:  1](R/W1C/H) Phase difference measurement done on PD bank 1. */
        uint64_t pdbank0_done          : 1;  /**< [  0:  0](R/W1C/H) Phase difference measurement done on PD bank 0. */
#else /* Word 0 - Little Endian */
        uint64_t pdbank0_done          : 1;  /**< [  0:  0](R/W1C/H) Phase difference measurement done on PD bank 0. */
        uint64_t pdbank1_done          : 1;  /**< [  1:  1](R/W1C/H) Phase difference measurement done on PD bank 1. */
        uint64_t pdbank2_done          : 1;  /**< [  2:  2](R/W1C/H) Phase difference measurement done on PD bank 2. */
        uint64_t pdbank3_done          : 1;  /**< [  3:  3](R/W1C/H) Phase difference measurement done on PD bank 3. */
        uint64_t pdbank4_done          : 1;  /**< [  4:  4](R/W1C/H) Phase difference measurement done on PD bank 4. */
        uint64_t pdbank5_done          : 1;  /**< [  5:  5](R/W1C/H) Phase difference measurement done on PD bank 5. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_int_sum_w1c_s cn; */
};
typedef union bdk_bts_int_sum_w1c bdk_bts_int_sum_w1c_t;

#define BDK_BTS_INT_SUM_W1C BDK_BTS_INT_SUM_W1C_FUNC()
static inline uint64_t BDK_BTS_INT_SUM_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_INT_SUM_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012001138ll;
    __bdk_csr_fatal("BTS_INT_SUM_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_INT_SUM_W1C bdk_bts_int_sum_w1c_t
#define bustype_BDK_BTS_INT_SUM_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_INT_SUM_W1C "BTS_INT_SUM_W1C"
#define device_bar_BDK_BTS_INT_SUM_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_INT_SUM_W1C 0
#define arguments_BDK_BTS_INT_SUM_W1C -1,-1,-1,-1

/**
 * Register (RSL) bts_int_sum_w1s
 *
 * BTS Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_bts_int_sum_w1s
{
    uint64_t u;
    struct bdk_bts_int_sum_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t pdbank5_done          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK5_DONE]. */
        uint64_t pdbank4_done          : 1;  /**< [  4:  4](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK4_DONE]. */
        uint64_t pdbank3_done          : 1;  /**< [  3:  3](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK3_DONE]. */
        uint64_t pdbank2_done          : 1;  /**< [  2:  2](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK2_DONE]. */
        uint64_t pdbank1_done          : 1;  /**< [  1:  1](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK1_DONE]. */
        uint64_t pdbank0_done          : 1;  /**< [  0:  0](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK0_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t pdbank0_done          : 1;  /**< [  0:  0](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK0_DONE]. */
        uint64_t pdbank1_done          : 1;  /**< [  1:  1](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK1_DONE]. */
        uint64_t pdbank2_done          : 1;  /**< [  2:  2](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK2_DONE]. */
        uint64_t pdbank3_done          : 1;  /**< [  3:  3](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK3_DONE]. */
        uint64_t pdbank4_done          : 1;  /**< [  4:  4](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK4_DONE]. */
        uint64_t pdbank5_done          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets BTS_INT_SUM_W1C[PDBANK5_DONE]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_int_sum_w1s_s cn; */
};
typedef union bdk_bts_int_sum_w1s bdk_bts_int_sum_w1s_t;

#define BDK_BTS_INT_SUM_W1S BDK_BTS_INT_SUM_W1S_FUNC()
static inline uint64_t BDK_BTS_INT_SUM_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_INT_SUM_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012001140ll;
    __bdk_csr_fatal("BTS_INT_SUM_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_INT_SUM_W1S bdk_bts_int_sum_w1s_t
#define bustype_BDK_BTS_INT_SUM_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_INT_SUM_W1S "BTS_INT_SUM_W1S"
#define device_bar_BDK_BTS_INT_SUM_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_INT_SUM_W1S 0
#define arguments_BDK_BTS_INT_SUM_W1S -1,-1,-1,-1

/**
 * Register (RSL) bts_msix_pba#
 *
 * BTS MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the BTS_INT_VEC_E enumeration.
 */
union bdk_bts_msix_pbax
{
    uint64_t u;
    struct bdk_bts_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated BTS_MSIX_VEC()_CTL, enumerated by BTS_INT_VEC_E. Bits
                                                                 that have no associated BTS_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated BTS_MSIX_VEC()_CTL, enumerated by BTS_INT_VEC_E. Bits
                                                                 that have no associated BTS_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_msix_pbax_s cn; */
};
typedef union bdk_bts_msix_pbax bdk_bts_msix_pbax_t;

static inline uint64_t BDK_BTS_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_MSIX_PBAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x87e012ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("BTS_MSIX_PBAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_BTS_MSIX_PBAX(a) bdk_bts_msix_pbax_t
#define bustype_BDK_BTS_MSIX_PBAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_MSIX_PBAX(a) "BTS_MSIX_PBAX"
#define device_bar_BDK_BTS_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_BTS_MSIX_PBAX(a) (a)
#define arguments_BDK_BTS_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (RSL) bts_msix_vec#_addr
 *
 * BTS MSI-X Vector Table Address Registers
 * This register is the MSI-X vector table, indexed by the BTS_INT_VEC_E enumeration.
 */
union bdk_bts_msix_vecx_addr
{
    uint64_t u;
    struct bdk_bts_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's BTS_MSIX_VEC()_ADDR, BTS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of BTS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_BTS_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's BTS_MSIX_VEC()_ADDR, BTS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of BTS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_BTS_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_msix_vecx_addr_s cn; */
};
typedef union bdk_bts_msix_vecx_addr bdk_bts_msix_vecx_addr_t;

static inline uint64_t BDK_BTS_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_MSIX_VECX_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=5))
        return 0x87e012f00000ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("BTS_MSIX_VECX_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_BTS_MSIX_VECX_ADDR(a) bdk_bts_msix_vecx_addr_t
#define bustype_BDK_BTS_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_MSIX_VECX_ADDR(a) "BTS_MSIX_VECX_ADDR"
#define device_bar_BDK_BTS_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_BTS_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_BTS_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) bts_msix_vec#_ctl
 *
 * BTS MSI-X Vector Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the BTS_INT_VEC_E enumeration.
 */
union bdk_bts_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_bts_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_msix_vecx_ctl_s cn; */
};
typedef union bdk_bts_msix_vecx_ctl bdk_bts_msix_vecx_ctl_t;

static inline uint64_t BDK_BTS_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_MSIX_VECX_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=5))
        return 0x87e012f00008ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("BTS_MSIX_VECX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_BTS_MSIX_VECX_CTL(a) bdk_bts_msix_vecx_ctl_t
#define bustype_BDK_BTS_MSIX_VECX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_MSIX_VECX_CTL(a) "BTS_MSIX_VECX_CTL"
#define device_bar_BDK_BTS_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_BTS_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_BTS_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) bts_pd1pps_div_cfg0
 *
 * BTS PD bank 1PPS Divider Configuration 0 Register
 * This register configures the clock divider used to generate the PD_1PPS
 * signal derived from the 30.72 MHz clock (BTS_BFN_CLK). This signal is
 * used by the clock generation block to control RFP timing.
 *
 * This register configures the clock divder used to generate the
 * PD_BFN_1PPS signal derived from the 30.72 MHz clock (BTS_BFN_CLK).
 *
 * When [FREE_RUN]=1, the initial alignment depends on when [DIVIDER_EN] is written
 * to 1, and the value in BTS_PD1PPS_DIV_CFG1[DIVIDER_START_POS].
 *
 * When [FREE_RUN]=0, the initial alignment will be
 * BTS_PD1PPS_DIV_CFG1[DIVIDER_START_POS]+4 cycles after the reference clock
 * selected by [REF_IN_SEL] (where cycles are counted in the 30.72 MHz clock).
 *
 * In both cases, after the initial pulse, subsequent 1PPS pulses are
 * generated at a constant period.
 */
union bdk_bts_pd1pps_div_cfg0
{
    uint64_t u;
    struct bdk_bts_pd1pps_div_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t ref_in_sel            : 3;  /**< [  6:  4](R/W) Select the reference 1PPS source:
                                                                 Use BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E for the selects. */
        uint64_t free_run              : 1;  /**< [  3:  3](R/W) Set to 1 to enable free running mode. In free running mode, all input
                                                                 1PPS references are ignored. The initial start position is set by
                                                                 BTS_PD1PPS_DIV_CFG1[DIVIDER_START_POS]. */
        uint64_t reserved_2            : 1;
        uint64_t clkout_5050_duty      : 1;  /**< [  1:  1](R/W) Clock divider duty cycle:
                                                                 0 = One cycle pulse (i.e., one 30.72 MHz cycle).
                                                                 1 = 50/50 duty-cycle. */
        uint64_t divider_en            : 1;  /**< [  0:  0](R/W) Set to 1 to enable the clock divider. The divider counter is reset to 0 when
                                                                 [DIVIDER_EN] is set to 0. */
#else /* Word 0 - Little Endian */
        uint64_t divider_en            : 1;  /**< [  0:  0](R/W) Set to 1 to enable the clock divider. The divider counter is reset to 0 when
                                                                 [DIVIDER_EN] is set to 0. */
        uint64_t clkout_5050_duty      : 1;  /**< [  1:  1](R/W) Clock divider duty cycle:
                                                                 0 = One cycle pulse (i.e., one 30.72 MHz cycle).
                                                                 1 = 50/50 duty-cycle. */
        uint64_t reserved_2            : 1;
        uint64_t free_run              : 1;  /**< [  3:  3](R/W) Set to 1 to enable free running mode. In free running mode, all input
                                                                 1PPS references are ignored. The initial start position is set by
                                                                 BTS_PD1PPS_DIV_CFG1[DIVIDER_START_POS]. */
        uint64_t ref_in_sel            : 3;  /**< [  6:  4](R/W) Select the reference 1PPS source:
                                                                 Use BTS_PD1PPS_DIV_CFG0_REF_IN_SEL_E for the selects. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_pd1pps_div_cfg0_s cn; */
};
typedef union bdk_bts_pd1pps_div_cfg0 bdk_bts_pd1pps_div_cfg0_t;

#define BDK_BTS_PD1PPS_DIV_CFG0 BDK_BTS_PD1PPS_DIV_CFG0_FUNC()
static inline uint64_t BDK_BTS_PD1PPS_DIV_CFG0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PD1PPS_DIV_CFG0_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000240ll;
    __bdk_csr_fatal("BTS_PD1PPS_DIV_CFG0", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_PD1PPS_DIV_CFG0 bdk_bts_pd1pps_div_cfg0_t
#define bustype_BDK_BTS_PD1PPS_DIV_CFG0 BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PD1PPS_DIV_CFG0 "BTS_PD1PPS_DIV_CFG0"
#define device_bar_BDK_BTS_PD1PPS_DIV_CFG0 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PD1PPS_DIV_CFG0 0
#define arguments_BDK_BTS_PD1PPS_DIV_CFG0 -1,-1,-1,-1

/**
 * Register (RSL) bts_pd1pps_div_cfg1
 *
 * BTS PD bank 1PPS Divider Configuration 1 Register
 * This register configures the clock divider used to generate the PD_1PPS
 * signal derived from the 30.72 MHz clock (BTS_BFN_CLK). This signal is
 * used by the clock generation block to control RFP timing.
 *
 * When enabled, the divider counts from 0 to [DIVIDER_TC], and then resets
 * to 0. When it resets to zero, it either generates a single cycle pulse, or
 * flips the polarity of the output, depending on the setting of
 * BTS_PD1PPS_DIV_CFG0[CLKOUT_5050_DUTY].
 */
union bdk_bts_pd1pps_div_cfg1
{
    uint64_t u;
    struct bdk_bts_pd1pps_div_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t divider_start_pos     : 32; /**< [ 63: 32](R/W) Divider start position. When a new value is written to
                                                                 [DIVIDER_START_POS], the counter will reset to 0 the next time the
                                                                 counter value is equal to [DIVIDER_START_POS]. Subsequently, the counter
                                                                 will reset to 0 when the counter is equal to [DIVIDER_TC].

                                                                 Writing [DIVIDER_START_POS] effectively applies a positive phase shift
                                                                 of [DIVIDER_START_POS]+1 cycles to the 1PPS signal.

                                                                 Note that a phase shift is only applied when this value changes, thus
                                                                 it might be necessary to write this field to zero before applying a
                                                                 new phase shift. */
        uint64_t divider_tc            : 32; /**< [ 31:  0](R/W) Divider counter terminal count value.

                                                                 When BTS_PD1PPS_DIV_CFG0[CLKOUT_5050_DUTY]=0, this field should be
                                                                 set to the clock frequency minus one, i.e., 0x1D4BFFF (307199999 for the 30.72
                                                                 MHz clock.

                                                                 When BTS_PD1PPS_DIV_CFG0[CLKOUT_5050_DUTY]=1, this field should be
                                                                 set to half the clock frequency minus one, i.e., 0xEA5FFF (153599999 for the
                                                                 30.72 MHz clock. */
#else /* Word 0 - Little Endian */
        uint64_t divider_tc            : 32; /**< [ 31:  0](R/W) Divider counter terminal count value.

                                                                 When BTS_PD1PPS_DIV_CFG0[CLKOUT_5050_DUTY]=0, this field should be
                                                                 set to the clock frequency minus one, i.e., 0x1D4BFFF (307199999 for the 30.72
                                                                 MHz clock.

                                                                 When BTS_PD1PPS_DIV_CFG0[CLKOUT_5050_DUTY]=1, this field should be
                                                                 set to half the clock frequency minus one, i.e., 0xEA5FFF (153599999 for the
                                                                 30.72 MHz clock. */
        uint64_t divider_start_pos     : 32; /**< [ 63: 32](R/W) Divider start position. When a new value is written to
                                                                 [DIVIDER_START_POS], the counter will reset to 0 the next time the
                                                                 counter value is equal to [DIVIDER_START_POS]. Subsequently, the counter
                                                                 will reset to 0 when the counter is equal to [DIVIDER_TC].

                                                                 Writing [DIVIDER_START_POS] effectively applies a positive phase shift
                                                                 of [DIVIDER_START_POS]+1 cycles to the 1PPS signal.

                                                                 Note that a phase shift is only applied when this value changes, thus
                                                                 it might be necessary to write this field to zero before applying a
                                                                 new phase shift. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_pd1pps_div_cfg1_s cn; */
};
typedef union bdk_bts_pd1pps_div_cfg1 bdk_bts_pd1pps_div_cfg1_t;

#define BDK_BTS_PD1PPS_DIV_CFG1 BDK_BTS_PD1PPS_DIV_CFG1_FUNC()
static inline uint64_t BDK_BTS_PD1PPS_DIV_CFG1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PD1PPS_DIV_CFG1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000248ll;
    __bdk_csr_fatal("BTS_PD1PPS_DIV_CFG1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_PD1PPS_DIV_CFG1 bdk_bts_pd1pps_div_cfg1_t
#define bustype_BDK_BTS_PD1PPS_DIV_CFG1 BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PD1PPS_DIV_CFG1 "BTS_PD1PPS_DIV_CFG1"
#define device_bar_BDK_BTS_PD1PPS_DIV_CFG1 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PD1PPS_DIV_CFG1 0
#define arguments_BDK_BTS_PD1PPS_DIV_CFG1 -1,-1,-1,-1

/**
 * Register (RSL) bts_pd_history
 *
 * BTS PD Bank History Register
 * This is a scratch register to facilitate saving the values used for PD
 * bank control registers.
 */
union bdk_bts_pd_history
{
    uint64_t u;
    struct bdk_bts_pd_history_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t value                 : 64; /**< [ 63:  0](R/W) Scratch data. */
#else /* Word 0 - Little Endian */
        uint64_t value                 : 64; /**< [ 63:  0](R/W) Scratch data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_pd_history_s cn; */
};
typedef union bdk_bts_pd_history bdk_bts_pd_history_t;

#define BDK_BTS_PD_HISTORY BDK_BTS_PD_HISTORY_FUNC()
static inline uint64_t BDK_BTS_PD_HISTORY_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PD_HISTORY_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000380ll;
    __bdk_csr_fatal("BTS_PD_HISTORY", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_PD_HISTORY bdk_bts_pd_history_t
#define bustype_BDK_BTS_PD_HISTORY BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PD_HISTORY "BTS_PD_HISTORY"
#define device_bar_BDK_BTS_PD_HISTORY 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PD_HISTORY 0
#define arguments_BDK_BTS_PD_HISTORY -1,-1,-1,-1

/**
 * Register (RSL) bts_pd_slice#_ctl
 *
 * BTS PD Bank Control Register
 * These registers control the operation of each PD bank.
 *
 * The PD bank must be disabled when changing any of these configuration
 * parameters (i.e., [ENABLE]=0). The PD bank should be enabled with a
 * separate register write after updating the other parameters (i.e., perform
 * one write to change the settings, and use a second write to enable the PD
 * bank).
 */
union bdk_bts_pd_slicex_ctl
{
    uint64_t u;
    struct bdk_bts_pd_slicex_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t mea_clk_sel           : 2;  /**< [  8:  7](R/W) Measurement clock select:
                                                                 0x0 = 491 MHz clock, both edges.
                                                                 0x1 = 491 MHz clock, rising edge only.
                                                                 0x2, 0x3 = Coprocessor clock, rising edge only.

                                                                 Refer to BTS_PLL_CTL for how to configure the 491 MHz clock.

                                                                 Do not change these during operation. */
        uint64_t ref_in_sel            : 3;  /**< [  6:  4](R/W) Reference 1pps source select.
                                                                 Use BTS_PD_SLICEX_CTL_REF_IN_SEL_E for select.
                                                                 Do not change these during operation. */
        uint64_t loop_in_sel           : 3;  /**< [  3:  1](R/W) Loop 1pps source select.
                                                                 0x0 = Reserved.
                                                                 0x1 = PTP_1PPS.
                                                                 0x2 = PD_BFN_1PPS.
                                                                 0x3 = CG_1PPS.
                                                                 0x4 = External reference 0 1PPS.
                                                                 0x5 = External reference 1 1PPS.
                                                                 0x6 = External reference 2 1PPS.
                                                                 0x7 = Reserved.

                                                                 Do not change these during operation. */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) Set to 1 to enable the PD bank. */
#else /* Word 0 - Little Endian */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) Set to 1 to enable the PD bank. */
        uint64_t loop_in_sel           : 3;  /**< [  3:  1](R/W) Loop 1pps source select.
                                                                 0x0 = Reserved.
                                                                 0x1 = PTP_1PPS.
                                                                 0x2 = PD_BFN_1PPS.
                                                                 0x3 = CG_1PPS.
                                                                 0x4 = External reference 0 1PPS.
                                                                 0x5 = External reference 1 1PPS.
                                                                 0x6 = External reference 2 1PPS.
                                                                 0x7 = Reserved.

                                                                 Do not change these during operation. */
        uint64_t ref_in_sel            : 3;  /**< [  6:  4](R/W) Reference 1pps source select.
                                                                 Use BTS_PD_SLICEX_CTL_REF_IN_SEL_E for select.
                                                                 Do not change these during operation. */
        uint64_t mea_clk_sel           : 2;  /**< [  8:  7](R/W) Measurement clock select:
                                                                 0x0 = 491 MHz clock, both edges.
                                                                 0x1 = 491 MHz clock, rising edge only.
                                                                 0x2, 0x3 = Coprocessor clock, rising edge only.

                                                                 Refer to BTS_PLL_CTL for how to configure the 491 MHz clock.

                                                                 Do not change these during operation. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_pd_slicex_ctl_s cn; */
};
typedef union bdk_bts_pd_slicex_ctl bdk_bts_pd_slicex_ctl_t;

static inline uint64_t BDK_BTS_PD_SLICEX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PD_SLICEX_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=5))
        return 0x87e012000300ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("BTS_PD_SLICEX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_BTS_PD_SLICEX_CTL(a) bdk_bts_pd_slicex_ctl_t
#define bustype_BDK_BTS_PD_SLICEX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PD_SLICEX_CTL(a) "BTS_PD_SLICEX_CTL"
#define device_bar_BDK_BTS_PD_SLICEX_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PD_SLICEX_CTL(a) (a)
#define arguments_BDK_BTS_PD_SLICEX_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) bts_pd_slice#_status
 *
 * BTS PD Bank Slice Status Register
 * This register reports the calculated phase difference for each PD bank.
 *
 * BTS triggers a BTS_INT_SUM_W1C[PDBANKn_DONE] interrupt each time the PD bank
 * completes a measurement and updates this status register.
 */
union bdk_bts_pd_slicex_status
{
    uint64_t u;
    struct bdk_bts_pd_slicex_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t pd_result             : 33; /**< [ 32:  0](RO/H) The phase difference as a signed, two's complement value. A positive value indicates that
                                                                 the REF clock is ahead of LOOP, and a negative value indicates that LOOP is ahead of REF.
                                                                 The phase difference is measured based on the clock selected by
                                                                 BTS_PD_SLICE()_CTL[MEA_CLK_SEL], and can represent either coprocessor-clock cycles,
                                                                 491 MHz cycles, or 982 MHz cycles (1.0183 ns). */
#else /* Word 0 - Little Endian */
        uint64_t pd_result             : 33; /**< [ 32:  0](RO/H) The phase difference as a signed, two's complement value. A positive value indicates that
                                                                 the REF clock is ahead of LOOP, and a negative value indicates that LOOP is ahead of REF.
                                                                 The phase difference is measured based on the clock selected by
                                                                 BTS_PD_SLICE()_CTL[MEA_CLK_SEL], and can represent either coprocessor-clock cycles,
                                                                 491 MHz cycles, or 982 MHz cycles (1.0183 ns). */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_pd_slicex_status_s cn; */
};
typedef union bdk_bts_pd_slicex_status bdk_bts_pd_slicex_status_t;

static inline uint64_t BDK_BTS_PD_SLICEX_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PD_SLICEX_STATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=5))
        return 0x87e012000340ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("BTS_PD_SLICEX_STATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_BTS_PD_SLICEX_STATUS(a) bdk_bts_pd_slicex_status_t
#define bustype_BDK_BTS_PD_SLICEX_STATUS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PD_SLICEX_STATUS(a) "BTS_PD_SLICEX_STATUS"
#define device_bar_BDK_BTS_PD_SLICEX_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PD_SLICEX_STATUS(a) (a)
#define arguments_BDK_BTS_PD_SLICEX_STATUS(a) (a),-1,-1,-1

/**
 * Register (RSL) bts_pdbfn_div_cfg0
 *
 * BTS 30.72 MHz Divider Configuration 0 Register
 * This register configures the clock divider used to generate the
 * PD_BFN_1PPS signal derived from the 30.72 MHz clock (BTS_BFN_CLK).
 *
 * When [FREE_RUN]=1, the initial alignment depends on when [DIVIDER_EN] is written
 * to 1, and the value in BTS_PDBFN_DIV_CFG1[DIVIDER_START_POS].
 *
 * When [FREE_RUN]=0, the initial alignment will be
 * BTS_PDBFN_DIV_CFG1[DIVIDER_START_POS]+4 cycles after the reference clock
 * selected by [REF_IN_SEL] (where cycles are counted in the 30.72 MHz clock).
 *
 * In both cases, after the initial pulse, subsequent 1PPS pulses are
 * generated at a constant period.
 */
union bdk_bts_pdbfn_div_cfg0
{
    uint64_t u;
    struct bdk_bts_pdbfn_div_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t ref_in_sel            : 3;  /**< [  6:  4](R/W) Select the reference 1PPS source:
                                                                 Use BTS_PDBFN_DIV_CFG0[REF_IN_SEL] for selects. */
        uint64_t free_run              : 1;  /**< [  3:  3](R/W) Set to 1 to enable free running mode. In free running mode, all input
                                                                 1PPS references are ignored. The initial start position is set by
                                                                 BTS_PDBFN_DIV_CFG1[DIVIDER_START_POS] and the timing of the write to
                                                                 set [DIVIDER_EN]=1. */
        uint64_t clkout_inv            : 1;  /**< [  2:  2](R/W) Set to 1 to inverse the output polarity for the PDBFN_1PPS
                                                                 signal. */
        uint64_t clkout_5050_duty      : 1;  /**< [  1:  1](R/W) Clock divider duty cycle:
                                                                 0 = One cycle pulse (i.e., one 30.72 MHz cycle).
                                                                 1 = 50/50 duty-cycle. */
        uint64_t divider_en            : 1;  /**< [  0:  0](R/W) Set to 1 to enable the clock divider. The divider counter is reset to 0 when
                                                                 [DIVIDER_EN] is set to 0 and the clock output is disabled. */
#else /* Word 0 - Little Endian */
        uint64_t divider_en            : 1;  /**< [  0:  0](R/W) Set to 1 to enable the clock divider. The divider counter is reset to 0 when
                                                                 [DIVIDER_EN] is set to 0 and the clock output is disabled. */
        uint64_t clkout_5050_duty      : 1;  /**< [  1:  1](R/W) Clock divider duty cycle:
                                                                 0 = One cycle pulse (i.e., one 30.72 MHz cycle).
                                                                 1 = 50/50 duty-cycle. */
        uint64_t clkout_inv            : 1;  /**< [  2:  2](R/W) Set to 1 to inverse the output polarity for the PDBFN_1PPS
                                                                 signal. */
        uint64_t free_run              : 1;  /**< [  3:  3](R/W) Set to 1 to enable free running mode. In free running mode, all input
                                                                 1PPS references are ignored. The initial start position is set by
                                                                 BTS_PDBFN_DIV_CFG1[DIVIDER_START_POS] and the timing of the write to
                                                                 set [DIVIDER_EN]=1. */
        uint64_t ref_in_sel            : 3;  /**< [  6:  4](R/W) Select the reference 1PPS source:
                                                                 Use BTS_PDBFN_DIV_CFG0[REF_IN_SEL] for selects. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_pdbfn_div_cfg0_s cn; */
};
typedef union bdk_bts_pdbfn_div_cfg0 bdk_bts_pdbfn_div_cfg0_t;

#define BDK_BTS_PDBFN_DIV_CFG0 BDK_BTS_PDBFN_DIV_CFG0_FUNC()
static inline uint64_t BDK_BTS_PDBFN_DIV_CFG0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PDBFN_DIV_CFG0_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000230ll;
    __bdk_csr_fatal("BTS_PDBFN_DIV_CFG0", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_PDBFN_DIV_CFG0 bdk_bts_pdbfn_div_cfg0_t
#define bustype_BDK_BTS_PDBFN_DIV_CFG0 BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PDBFN_DIV_CFG0 "BTS_PDBFN_DIV_CFG0"
#define device_bar_BDK_BTS_PDBFN_DIV_CFG0 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PDBFN_DIV_CFG0 0
#define arguments_BDK_BTS_PDBFN_DIV_CFG0 -1,-1,-1,-1

/**
 * Register (RSL) bts_pdbfn_div_cfg1
 *
 * BTS 30.72 MHz Divider Configuration 1 Register
 * This register configures the clock divder used to generate the PDBFN_1PPS
 * signal derived from the 30.72 MHz clock (BTS_BFN_CLK).
 *
 * When enabled, the divider counts from 0 to [DIVIDER_TC], and then resets
 * to 0. When it resets to zero, it either generates a single cycle pulse, or
 * flips the polarity of the output, depending on the setting of
 * BTS_PDBFN_DIV_CFG0[CLKOUT_5050_DUTY].
 */
union bdk_bts_pdbfn_div_cfg1
{
    uint64_t u;
    struct bdk_bts_pdbfn_div_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t divider_start_pos     : 32; /**< [ 63: 32](R/W) Divider start position. When a new value is written to
                                                                 [DIVIDER_START_POS], the counter will reset to 0 the next time the
                                                                 counter value is equal to [DIVIDER_START_POS]. Subsequently, the counter
                                                                 will reset to 0 when the counter is equal to [DIVIDER_TC].

                                                                 Writing [DIVIDER_START_POS] effectively applies a positive phase shift
                                                                 of [DIVIDER_START_POS]+1 cycles to the 1PPS signal.

                                                                 Note that a phase shift is only applied when this value changes, thus
                                                                 it might be necessary to write this field to zero before applying a
                                                                 new phase shift. */
        uint64_t divider_tc            : 32; /**< [ 31:  0](R/W) Divider counter terminal count value.

                                                                 When BTS_PDBFN_DIV_CFG0[CLKOUT_5050_DUTY]=0, this field should be
                                                                 set to the clock frequency minus one, i.e., 0x1D4BFFF (30719999) for the 30.72
                                                                 MHz clock.

                                                                 When BTS_PDBFN_DIV_CFG0[CLKOUT_5050_DUTY]=1, this field should be
                                                                 set to half the clock frequency minus one, i.e., 0xEA5FFF (15359999) for the
                                                                 30.72 MHz clock. */
#else /* Word 0 - Little Endian */
        uint64_t divider_tc            : 32; /**< [ 31:  0](R/W) Divider counter terminal count value.

                                                                 When BTS_PDBFN_DIV_CFG0[CLKOUT_5050_DUTY]=0, this field should be
                                                                 set to the clock frequency minus one, i.e., 0x1D4BFFF (30719999) for the 30.72
                                                                 MHz clock.

                                                                 When BTS_PDBFN_DIV_CFG0[CLKOUT_5050_DUTY]=1, this field should be
                                                                 set to half the clock frequency minus one, i.e., 0xEA5FFF (15359999) for the
                                                                 30.72 MHz clock. */
        uint64_t divider_start_pos     : 32; /**< [ 63: 32](R/W) Divider start position. When a new value is written to
                                                                 [DIVIDER_START_POS], the counter will reset to 0 the next time the
                                                                 counter value is equal to [DIVIDER_START_POS]. Subsequently, the counter
                                                                 will reset to 0 when the counter is equal to [DIVIDER_TC].

                                                                 Writing [DIVIDER_START_POS] effectively applies a positive phase shift
                                                                 of [DIVIDER_START_POS]+1 cycles to the 1PPS signal.

                                                                 Note that a phase shift is only applied when this value changes, thus
                                                                 it might be necessary to write this field to zero before applying a
                                                                 new phase shift. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_pdbfn_div_cfg1_s cn; */
};
typedef union bdk_bts_pdbfn_div_cfg1 bdk_bts_pdbfn_div_cfg1_t;

#define BDK_BTS_PDBFN_DIV_CFG1 BDK_BTS_PDBFN_DIV_CFG1_FUNC()
static inline uint64_t BDK_BTS_PDBFN_DIV_CFG1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PDBFN_DIV_CFG1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000238ll;
    __bdk_csr_fatal("BTS_PDBFN_DIV_CFG1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_PDBFN_DIV_CFG1 bdk_bts_pdbfn_div_cfg1_t
#define bustype_BDK_BTS_PDBFN_DIV_CFG1 BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PDBFN_DIV_CFG1 "BTS_PDBFN_DIV_CFG1"
#define device_bar_BDK_BTS_PDBFN_DIV_CFG1 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PDBFN_DIV_CFG1 0
#define arguments_BDK_BTS_PDBFN_DIV_CFG1 -1,-1,-1,-1

/**
 * Register (RSL) bts_pll_ctl
 *
 * BTS PD Bank PLL Control Register
 * This register controls the sample clock frequency into PD Bank slices.
 * The following sequence is the PLL-bringup sequence:
 *   1. Write [RESET_N]=0 and [DIV_RESET]=1.
 *   2. Set [CLKF] and [PS_EN].
 *   3. Wait 128 reference-clock cycles.
 *   4. Write [RESET_N]=1.
 *   5. Wait 1152 reference-clock cycles.
 *   6. Write [DIV_RESET]=0.
 *   7. Wait 10 reference-clock cycles before using the PLL clock out.
 *
 * Internal:
 * In JTAG test mode, at step 2, also write jtg__tns_pll_tm_en2, jtg__tns_pll_tm_en4,
 * jtg__tns_pll_tm_en12 and jtg__tns_pll_tm_en24.
 * If test mode is going to be activated, wait for an additional 8191 reference-clock
 * cycles to allow PLL clock to align.
 */
union bdk_bts_pll_ctl
{
    uint64_t u;
    struct bdk_bts_pll_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_37_63        : 27;
        uint64_t alt_ref_clk_sel       : 2;  /**< [ 36: 35](R/W) Alternate reference clock select.
                                                                 0x0 = DLM6 reference clock.
                                                                 0x1 = DLM7 reference clock.
                                                                 0x2 or 0x3 = DLM8 reference clock.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 FIXME update these old encodings; note on 93 the DLM ports are tied off. */
        uint64_t reserved_33_34        : 2;
        uint64_t pll_bypass            : 1;  /**< [ 32: 32](R/W) Set to 1 to bypass PLL. In PLL bypass mode, the PLL clock out is BTS_BFN_CLK (30.72 MHz). */
        uint64_t reserved_30_31        : 2;
        uint64_t ref_clk_sel           : 2;  /**< [ 29: 28](R/W) Reference clock select:
                                                                 0x0 = Reserved.
                                                                 0x1 = GPIO clock input. 30.72 MHz (BTS_BFN_CLK).
                                                                 0x2 = 100 MHz reference clock.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 0x0 = 122.88 MHz (alternate reference clock selected by [ALT_REF_CLK_SEL]). */
        uint64_t reserved_21_27        : 7;
        uint64_t ps_en                 : 3;  /**< [ 20: 18](R/W) PLL postscalar divide ratio. Determines the network clock speed.
                                                                 0x0 = Divide BTS PLL by 1.
                                                                 0x1 = Divide BTS PLL by 2.
                                                                 0x2 = Divide BTS PLL by 4.
                                                                 0x3 = Divide BTS PLL by 8.
                                                                 0x4-0x7 = Reserved.

                                                                 [PS_EN] is not used when DIV_RESET = 1. See CLKF for supported settings.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 FIXME where is DIV_RESET?  Also mentioned in register description. */
        uint64_t reserved_12_17        : 6;
        uint64_t en                    : 1;  /**< [ 11: 11](R/W) PLL enable. Rising edge causes a 1 clock ref_clk pulse on pll_update signal. */
        uint64_t reserved_9_10         : 2;
        uint64_t clkf                  : 9;  /**< [  8:  0](R/W) PLL multiplier. PLL out frequency = PLL in clk(MHz)/2 * [CLKF] / (1\<\<[PS_EN])

                                                                 To generate a 491 MHz clock from  a 30.72 MHz reference (i.e., when
                                                                 [REF_CLK_SEL]=0x1), set [CLKF] to 0x20 and [PS_EN] to 0x0. This results in an
                                                                 overall 16x multplier. */
#else /* Word 0 - Little Endian */
        uint64_t clkf                  : 9;  /**< [  8:  0](R/W) PLL multiplier. PLL out frequency = PLL in clk(MHz)/2 * [CLKF] / (1\<\<[PS_EN])

                                                                 To generate a 491 MHz clock from  a 30.72 MHz reference (i.e., when
                                                                 [REF_CLK_SEL]=0x1), set [CLKF] to 0x20 and [PS_EN] to 0x0. This results in an
                                                                 overall 16x multplier. */
        uint64_t reserved_9_10         : 2;
        uint64_t en                    : 1;  /**< [ 11: 11](R/W) PLL enable. Rising edge causes a 1 clock ref_clk pulse on pll_update signal. */
        uint64_t reserved_12_17        : 6;
        uint64_t ps_en                 : 3;  /**< [ 20: 18](R/W) PLL postscalar divide ratio. Determines the network clock speed.
                                                                 0x0 = Divide BTS PLL by 1.
                                                                 0x1 = Divide BTS PLL by 2.
                                                                 0x2 = Divide BTS PLL by 4.
                                                                 0x3 = Divide BTS PLL by 8.
                                                                 0x4-0x7 = Reserved.

                                                                 [PS_EN] is not used when DIV_RESET = 1. See CLKF for supported settings.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 FIXME where is DIV_RESET?  Also mentioned in register description. */
        uint64_t reserved_21_27        : 7;
        uint64_t ref_clk_sel           : 2;  /**< [ 29: 28](R/W) Reference clock select:
                                                                 0x0 = Reserved.
                                                                 0x1 = GPIO clock input. 30.72 MHz (BTS_BFN_CLK).
                                                                 0x2 = 100 MHz reference clock.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 0x0 = 122.88 MHz (alternate reference clock selected by [ALT_REF_CLK_SEL]). */
        uint64_t reserved_30_31        : 2;
        uint64_t pll_bypass            : 1;  /**< [ 32: 32](R/W) Set to 1 to bypass PLL. In PLL bypass mode, the PLL clock out is BTS_BFN_CLK (30.72 MHz). */
        uint64_t reserved_33_34        : 2;
        uint64_t alt_ref_clk_sel       : 2;  /**< [ 36: 35](R/W) Alternate reference clock select.
                                                                 0x0 = DLM6 reference clock.
                                                                 0x1 = DLM7 reference clock.
                                                                 0x2 or 0x3 = DLM8 reference clock.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 FIXME update these old encodings; note on 93 the DLM ports are tied off. */
        uint64_t reserved_37_63        : 27;
#endif /* Word 0 - End */
    } s;
    struct bdk_bts_pll_ctl_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_37_63        : 27;
        uint64_t alt_ref_clk_sel       : 2;  /**< [ 36: 35](R/W) Alternate reference clock select.
                                                                 0x0 = DLM6 reference clock.
                                                                 0x1 = DLM7 reference clock.
                                                                 0x2 or 0x3 = DLM8 reference clock.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 FIXME update these old encodings; note on 93 the DLM ports are tied off. */
        uint64_t reserved_33_34        : 2;
        uint64_t pll_bypass            : 1;  /**< [ 32: 32](R/W) Set to 1 to bypass PLL. In PLL bypass mode, the PLL clock out is BTS_BFN_CLK (30.72 MHz). */
        uint64_t reserved_30_31        : 2;
        uint64_t ref_clk_sel           : 2;  /**< [ 29: 28](R/W) Reference clock select:
                                                                 0x0 = Reserved.
                                                                 0x1 = GPIO clock input. 30.72 MHz (BTS_BFN_CLK).
                                                                 0x2 = 100 MHz reference clock.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 0x0 = 122.88 MHz (alternate reference clock selected by [ALT_REF_CLK_SEL]). */
        uint64_t reserved_26_27        : 2;
        uint64_t reserved_21_25        : 5;
        uint64_t ps_en                 : 3;  /**< [ 20: 18](R/W) PLL postscalar divide ratio. Determines the network clock speed.
                                                                 0x0 = Divide BTS PLL by 1.
                                                                 0x1 = Divide BTS PLL by 2.
                                                                 0x2 = Divide BTS PLL by 4.
                                                                 0x3 = Divide BTS PLL by 8.
                                                                 0x4-0x7 = Reserved.

                                                                 [PS_EN] is not used when DIV_RESET = 1. See CLKF for supported settings.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 FIXME where is DIV_RESET?  Also mentioned in register description. */
        uint64_t reserved_12_17        : 6;
        uint64_t en                    : 1;  /**< [ 11: 11](R/W) PLL enable. Rising edge causes a 1 clock ref_clk pulse on pll_update signal. */
        uint64_t reserved_9_10         : 2;
        uint64_t clkf                  : 9;  /**< [  8:  0](R/W) PLL multiplier. PLL out frequency = PLL in clk(MHz)/2 * [CLKF] / (1\<\<[PS_EN])

                                                                 To generate a 491 MHz clock from  a 30.72 MHz reference (i.e., when
                                                                 [REF_CLK_SEL]=0x1), set [CLKF] to 0x20 and [PS_EN] to 0x0. This results in an
                                                                 overall 16x multplier. */
#else /* Word 0 - Little Endian */
        uint64_t clkf                  : 9;  /**< [  8:  0](R/W) PLL multiplier. PLL out frequency = PLL in clk(MHz)/2 * [CLKF] / (1\<\<[PS_EN])

                                                                 To generate a 491 MHz clock from  a 30.72 MHz reference (i.e., when
                                                                 [REF_CLK_SEL]=0x1), set [CLKF] to 0x20 and [PS_EN] to 0x0. This results in an
                                                                 overall 16x multplier. */
        uint64_t reserved_9_10         : 2;
        uint64_t en                    : 1;  /**< [ 11: 11](R/W) PLL enable. Rising edge causes a 1 clock ref_clk pulse on pll_update signal. */
        uint64_t reserved_12_17        : 6;
        uint64_t ps_en                 : 3;  /**< [ 20: 18](R/W) PLL postscalar divide ratio. Determines the network clock speed.
                                                                 0x0 = Divide BTS PLL by 1.
                                                                 0x1 = Divide BTS PLL by 2.
                                                                 0x2 = Divide BTS PLL by 4.
                                                                 0x3 = Divide BTS PLL by 8.
                                                                 0x4-0x7 = Reserved.

                                                                 [PS_EN] is not used when DIV_RESET = 1. See CLKF for supported settings.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 FIXME where is DIV_RESET?  Also mentioned in register description. */
        uint64_t reserved_21_25        : 5;
        uint64_t reserved_26_27        : 2;
        uint64_t ref_clk_sel           : 2;  /**< [ 29: 28](R/W) Reference clock select:
                                                                 0x0 = Reserved.
                                                                 0x1 = GPIO clock input. 30.72 MHz (BTS_BFN_CLK).
                                                                 0x2 = 100 MHz reference clock.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 0x0 = 122.88 MHz (alternate reference clock selected by [ALT_REF_CLK_SEL]). */
        uint64_t reserved_30_31        : 2;
        uint64_t pll_bypass            : 1;  /**< [ 32: 32](R/W) Set to 1 to bypass PLL. In PLL bypass mode, the PLL clock out is BTS_BFN_CLK (30.72 MHz). */
        uint64_t reserved_33_34        : 2;
        uint64_t alt_ref_clk_sel       : 2;  /**< [ 36: 35](R/W) Alternate reference clock select.
                                                                 0x0 = DLM6 reference clock.
                                                                 0x1 = DLM7 reference clock.
                                                                 0x2 or 0x3 = DLM8 reference clock.

                                                                 Do not change these during operation.

                                                                 Internal:
                                                                 FIXME update these old encodings; note on 93 the DLM ports are tied off. */
        uint64_t reserved_37_63        : 27;
#endif /* Word 0 - End */
    } cn;
};
typedef union bdk_bts_pll_ctl bdk_bts_pll_ctl_t;

#define BDK_BTS_PLL_CTL BDK_BTS_PLL_CTL_FUNC()
static inline uint64_t BDK_BTS_PLL_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PLL_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000000ll;
    __bdk_csr_fatal("BTS_PLL_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_PLL_CTL bdk_bts_pll_ctl_t
#define bustype_BDK_BTS_PLL_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PLL_CTL "BTS_PLL_CTL"
#define device_bar_BDK_BTS_PLL_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PLL_CTL 0
#define arguments_BDK_BTS_PLL_CTL -1,-1,-1,-1

/**
 * Register (RSL) bts_pll_pc
 *
 * BTS PLL Counter Register
 */
union bdk_bts_pll_pc
{
    uint64_t u;
    struct bdk_bts_pll_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Counts each rising edge of the PLL output clock. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Counts each rising edge of the PLL output clock. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_pll_pc_s cn; */
};
typedef union bdk_bts_pll_pc bdk_bts_pll_pc_t;

#define BDK_BTS_PLL_PC BDK_BTS_PLL_PC_FUNC()
static inline uint64_t BDK_BTS_PLL_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PLL_PC_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0120000a0ll;
    __bdk_csr_fatal("BTS_PLL_PC", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_PLL_PC bdk_bts_pll_pc_t
#define bustype_BDK_BTS_PLL_PC BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PLL_PC "BTS_PLL_PC"
#define device_bar_BDK_BTS_PLL_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PLL_PC 0
#define arguments_BDK_BTS_PLL_PC -1,-1,-1,-1

/**
 * Register (RSL) bts_ptp_1pps_cfg
 *
 * BTS PTP 1PPS Configuration Register
 */
union bdk_bts_ptp_1pps_cfg
{
    uint64_t u;
    struct bdk_bts_ptp_1pps_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t reverse               : 1;  /**< [  0:  0](R/W) Set to 1 to invert the polarity of the PTP_1PPS signal. */
#else /* Word 0 - Little Endian */
        uint64_t reverse               : 1;  /**< [  0:  0](R/W) Set to 1 to invert the polarity of the PTP_1PPS signal. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_ptp_1pps_cfg_s cn; */
};
typedef union bdk_bts_ptp_1pps_cfg bdk_bts_ptp_1pps_cfg_t;

#define BDK_BTS_PTP_1PPS_CFG BDK_BTS_PTP_1PPS_CFG_FUNC()
static inline uint64_t BDK_BTS_PTP_1PPS_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PTP_1PPS_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000258ll;
    __bdk_csr_fatal("BTS_PTP_1PPS_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_PTP_1PPS_CFG bdk_bts_ptp_1pps_cfg_t
#define bustype_BDK_BTS_PTP_1PPS_CFG BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PTP_1PPS_CFG "BTS_PTP_1PPS_CFG"
#define device_bar_BDK_BTS_PTP_1PPS_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PTP_1PPS_CFG 0
#define arguments_BDK_BTS_PTP_1PPS_CFG -1,-1,-1,-1

/**
 * Register (RSL) bts_pwm_ctl
 *
 * BTS PWM Control Register
 */
union bdk_bts_pwm_ctl
{
    uint64_t u;
    struct bdk_bts_pwm_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_59_63        : 5;
        uint64_t clk_sel               : 2;  /**< [ 58: 57](R/W) Select the clock for the PWM module. Must not be changed while operating.
                                                                 0x0 = Refclk (100 MHz).
                                                                 0x1 = PLL output (should be but not guarenteed to be 491 MHz clock).
                                                                 0x2 = Coprocessor-clock (use caution if coprocessor-clock can change frequency).
                                                                 0x3 = Reserved. */
        uint64_t reserved_56           : 1;
        uint64_t fall_pos              : 20; /**< [ 55: 36](R/W) Pulse low duration minus one, measured in ticks, as determined by
                                                                 [TICK_SEL]. */
        uint64_t reserved_28_35        : 8;
        uint64_t rise_pos              : 20; /**< [ 27:  8](R/W) Pulse high duration minus one, measured in ticks, as determined by
                                                                 [TICK_SEL]. */
        uint64_t reserved_4_7          : 4;
        uint64_t tick_sel              : 3;  /**< [  3:  1](R/W) PWM tick clock select. enumerated by BTS_PWM_CTL_TICK_SEL_E. */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) Set to 1 to enable PWM clock and output. */
#else /* Word 0 - Little Endian */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) Set to 1 to enable PWM clock and output. */
        uint64_t tick_sel              : 3;  /**< [  3:  1](R/W) PWM tick clock select. enumerated by BTS_PWM_CTL_TICK_SEL_E. */
        uint64_t reserved_4_7          : 4;
        uint64_t rise_pos              : 20; /**< [ 27:  8](R/W) Pulse high duration minus one, measured in ticks, as determined by
                                                                 [TICK_SEL]. */
        uint64_t reserved_28_35        : 8;
        uint64_t fall_pos              : 20; /**< [ 55: 36](R/W) Pulse low duration minus one, measured in ticks, as determined by
                                                                 [TICK_SEL]. */
        uint64_t reserved_56           : 1;
        uint64_t clk_sel               : 2;  /**< [ 58: 57](R/W) Select the clock for the PWM module. Must not be changed while operating.
                                                                 0x0 = Refclk (100 MHz).
                                                                 0x1 = PLL output (should be but not guarenteed to be 491 MHz clock).
                                                                 0x2 = Coprocessor-clock (use caution if coprocessor-clock can change frequency).
                                                                 0x3 = Reserved. */
        uint64_t reserved_59_63        : 5;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_pwm_ctl_s cn; */
};
typedef union bdk_bts_pwm_ctl bdk_bts_pwm_ctl_t;

#define BDK_BTS_PWM_CTL BDK_BTS_PWM_CTL_FUNC()
static inline uint64_t BDK_BTS_PWM_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_PWM_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000440ll;
    __bdk_csr_fatal("BTS_PWM_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_PWM_CTL bdk_bts_pwm_ctl_t
#define bustype_BDK_BTS_PWM_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_PWM_CTL "BTS_PWM_CTL"
#define device_bar_BDK_BTS_PWM_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_PWM_CTL 0
#define arguments_BDK_BTS_PWM_CTL -1,-1,-1,-1

/**
 * Register (RSL) bts_tp_mux_sel
 *
 * BTS Test Point Mux Select Register
 */
union bdk_bts_tp_mux_sel
{
    uint64_t u;
    struct bdk_bts_tp_mux_sel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t tp4_sel               : 4;  /**< [ 15: 12](R/W) Select the source for the BTS_TP4 output signal:
                                                                 0x0 = PD bank 0 PD positive done.
                                                                 0x1 = PD bank 1 PD positive done.
                                                                 0x2 = PD bank 2 PD positive done.
                                                                 0x3 = PD bank 3 PD positive done.
                                                                 0x4 = PD bank 4 PD positive done.
                                                                 0x5 = PD bank 5 PD positive done.
                                                                 0x6 = PD_1PPS.
                                                                 0x7 = Reserved.
                                                                 0x8 = PD bank 0 PD negative clear.
                                                                 0x9 = PD bank 1 PD negative clear.
                                                                 0xA = PD bank 2 PD negative clear.
                                                                 0xB = PD bank 3 PD negative clear.
                                                                 0xC = PD bank 4 PD negative clear.
                                                                 0xD = PD bank 5 PD negative clear.
                                                                 0xE-0xF = Reserved. */
        uint64_t tp3_sel               : 4;  /**< [ 11:  8](R/W) Select the source for the BTS_TP3 output signal:
                                                                 0x0 = PD bank 0 PD positive clear.
                                                                 0x1 = PD bank 1 PD positive clear.
                                                                 0x2 = PD bank 2 PD positive clear.
                                                                 0x3 = PD bank 3 PD positive clear.
                                                                 0x4 = PD bank 4 PD positive clear.
                                                                 0x5 = PD bank 5 PD positive clear.
                                                                 0x6 = CG_1pps.
                                                                 0x7 = Reserved.
                                                                 0x8 = PD bank 0 PD negative done.
                                                                 0x9 = PD bank 1 PD negative done.
                                                                 0xA = PD bank 2 PD negative done.
                                                                 0xB = PD bank 3 PD negative done.
                                                                 0xC = PD bank 4 PD negative done.
                                                                 0xD = PD bank 5 PD negative done.
                                                                 0xE-0xF = Reserved. */
        uint64_t tp2_sel               : 4;  /**< [  7:  4](R/W) Select the source for the BTS_TP2 output signal:
                                                                 0x0 = PD bank 0 LOOP_1pps.
                                                                 0x1 = PD bank 1 LOOP_1pps.
                                                                 0x2 = PD bank 2 LOOP_1pps.
                                                                 0x3 = PD bank 3 LOOP_1pps.
                                                                 0x4 = PD bank 4 LOOP_1pps.
                                                                 0x5 = PD bank 5 LOOP_1pps.
                                                                 0x6 = PLL out clk /16.
                                                                 0x7-0xF = Reserved. */
        uint64_t tp1_sel               : 4;  /**< [  3:  0](R/W) Select the source for the BTS_TP1 output signal:
                                                                 0x0 = PD bank 0 REF_1pps.
                                                                 0x1 = PD bank 1 REF_1pps.
                                                                 0x2 = PD bank 2 REF_1pps.
                                                                 0x3 = PD bank 3 REF_1pps.
                                                                 0x4 = PD bank 4 REF_1pps.
                                                                 0x5 = PD bank 5 REF_1pps.
                                                                 0x6-0xF = Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t tp1_sel               : 4;  /**< [  3:  0](R/W) Select the source for the BTS_TP1 output signal:
                                                                 0x0 = PD bank 0 REF_1pps.
                                                                 0x1 = PD bank 1 REF_1pps.
                                                                 0x2 = PD bank 2 REF_1pps.
                                                                 0x3 = PD bank 3 REF_1pps.
                                                                 0x4 = PD bank 4 REF_1pps.
                                                                 0x5 = PD bank 5 REF_1pps.
                                                                 0x6-0xF = Reserved. */
        uint64_t tp2_sel               : 4;  /**< [  7:  4](R/W) Select the source for the BTS_TP2 output signal:
                                                                 0x0 = PD bank 0 LOOP_1pps.
                                                                 0x1 = PD bank 1 LOOP_1pps.
                                                                 0x2 = PD bank 2 LOOP_1pps.
                                                                 0x3 = PD bank 3 LOOP_1pps.
                                                                 0x4 = PD bank 4 LOOP_1pps.
                                                                 0x5 = PD bank 5 LOOP_1pps.
                                                                 0x6 = PLL out clk /16.
                                                                 0x7-0xF = Reserved. */
        uint64_t tp3_sel               : 4;  /**< [ 11:  8](R/W) Select the source for the BTS_TP3 output signal:
                                                                 0x0 = PD bank 0 PD positive clear.
                                                                 0x1 = PD bank 1 PD positive clear.
                                                                 0x2 = PD bank 2 PD positive clear.
                                                                 0x3 = PD bank 3 PD positive clear.
                                                                 0x4 = PD bank 4 PD positive clear.
                                                                 0x5 = PD bank 5 PD positive clear.
                                                                 0x6 = CG_1pps.
                                                                 0x7 = Reserved.
                                                                 0x8 = PD bank 0 PD negative done.
                                                                 0x9 = PD bank 1 PD negative done.
                                                                 0xA = PD bank 2 PD negative done.
                                                                 0xB = PD bank 3 PD negative done.
                                                                 0xC = PD bank 4 PD negative done.
                                                                 0xD = PD bank 5 PD negative done.
                                                                 0xE-0xF = Reserved. */
        uint64_t tp4_sel               : 4;  /**< [ 15: 12](R/W) Select the source for the BTS_TP4 output signal:
                                                                 0x0 = PD bank 0 PD positive done.
                                                                 0x1 = PD bank 1 PD positive done.
                                                                 0x2 = PD bank 2 PD positive done.
                                                                 0x3 = PD bank 3 PD positive done.
                                                                 0x4 = PD bank 4 PD positive done.
                                                                 0x5 = PD bank 5 PD positive done.
                                                                 0x6 = PD_1PPS.
                                                                 0x7 = Reserved.
                                                                 0x8 = PD bank 0 PD negative clear.
                                                                 0x9 = PD bank 1 PD negative clear.
                                                                 0xA = PD bank 2 PD negative clear.
                                                                 0xB = PD bank 3 PD negative clear.
                                                                 0xC = PD bank 4 PD negative clear.
                                                                 0xD = PD bank 5 PD negative clear.
                                                                 0xE-0xF = Reserved. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_bts_tp_mux_sel_s cn; */
};
typedef union bdk_bts_tp_mux_sel bdk_bts_tp_mux_sel_t;

#define BDK_BTS_TP_MUX_SEL BDK_BTS_TP_MUX_SEL_FUNC()
static inline uint64_t BDK_BTS_TP_MUX_SEL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_BTS_TP_MUX_SEL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e012000480ll;
    __bdk_csr_fatal("BTS_TP_MUX_SEL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_BTS_TP_MUX_SEL bdk_bts_tp_mux_sel_t
#define bustype_BDK_BTS_TP_MUX_SEL BDK_CSR_TYPE_RSL
#define basename_BDK_BTS_TP_MUX_SEL "BTS_TP_MUX_SEL"
#define device_bar_BDK_BTS_TP_MUX_SEL 0x0 /* PF_BAR0 */
#define busnum_BDK_BTS_TP_MUX_SEL 0
#define arguments_BDK_BTS_TP_MUX_SEL -1,-1,-1,-1

#endif /* __BDK_CSRS_BTS_H__ */
