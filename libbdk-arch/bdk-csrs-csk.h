#ifndef __BDK_CSRS_CSK_H__
#define __BDK_CSRS_CSK_H__
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
 * OcteonTX CSK.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration csk_bar_e
 *
 * CSK Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_CSK_BAR_E_CSK_PF_BAR0 (0x87e00e000000ll)
#define BDK_CSK_BAR_E_CSK_PF_BAR0_SIZE 0x100000ull

/**
 * Register (RSL) csk_ap_sel
 *
 * CSK AP Select Register
 * This register selects blocks for clock shrink/stop testing.
 */
union bdk_csk_ap_sel
{
    uint64_t u;
    struct bdk_csk_ap_sel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ct_sel                : 3;  /**< [ 63: 61](R/W) test */
        uint64_t reserved_6_60         : 55;
        uint64_t ap_sel                : 6;  /**< [  5:  0](R/W) Bit-mask of enable bits that selects which blocks are used for a clock
                                                                 shrink/stop test. */
#else /* Word 0 - Little Endian */
        uint64_t ap_sel                : 6;  /**< [  5:  0](R/W) Bit-mask of enable bits that selects which blocks are used for a clock
                                                                 shrink/stop test. */
        uint64_t reserved_6_60         : 55;
        uint64_t ct_sel                : 3;  /**< [ 63: 61](R/W) test */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_csk_ap_sel_s cn; */
};
typedef union bdk_csk_ap_sel bdk_csk_ap_sel_t;

#define BDK_CSK_AP_SEL BDK_CSK_AP_SEL_FUNC()
static inline uint64_t BDK_CSK_AP_SEL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CSK_AP_SEL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00e000018ll;
    __bdk_csr_fatal("CSK_AP_SEL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CSK_AP_SEL bdk_csk_ap_sel_t
#define bustype_BDK_CSK_AP_SEL BDK_CSR_TYPE_RSL
#define basename_BDK_CSK_AP_SEL "CSK_AP_SEL"
#define device_bar_BDK_CSK_AP_SEL 0x0 /* PF_BAR0 */
#define busnum_BDK_CSK_AP_SEL 0
#define arguments_BDK_CSK_AP_SEL -1,-1,-1,-1

/**
 * Register (RSL) csk_clk_stop_index
 *
 * CSK Clock Stop Cycle Index Register
 */
union bdk_csk_clk_stop_index
{
    uint64_t u;
    struct bdk_csk_clk_stop_index_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t clk_stop              : 64; /**< [ 63:  0](R/W) Core-clock cycle number to trigger stop clk signal if CSK_CTRL[STOP_CLK_MODE] is set. */
#else /* Word 0 - Little Endian */
        uint64_t clk_stop              : 64; /**< [ 63:  0](R/W) Core-clock cycle number to trigger stop clk signal if CSK_CTRL[STOP_CLK_MODE] is set. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_csk_clk_stop_index_s cn; */
};
typedef union bdk_csk_clk_stop_index bdk_csk_clk_stop_index_t;

#define BDK_CSK_CLK_STOP_INDEX BDK_CSK_CLK_STOP_INDEX_FUNC()
static inline uint64_t BDK_CSK_CLK_STOP_INDEX_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CSK_CLK_STOP_INDEX_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00e000030ll;
    __bdk_csr_fatal("CSK_CLK_STOP_INDEX", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CSK_CLK_STOP_INDEX bdk_csk_clk_stop_index_t
#define bustype_BDK_CSK_CLK_STOP_INDEX BDK_CSR_TYPE_RSL
#define basename_BDK_CSK_CLK_STOP_INDEX "CSK_CLK_STOP_INDEX"
#define device_bar_BDK_CSK_CLK_STOP_INDEX 0x0 /* PF_BAR0 */
#define busnum_BDK_CSK_CLK_STOP_INDEX 0
#define arguments_BDK_CSK_CLK_STOP_INDEX -1,-1,-1,-1

/**
 * Register (RSL) csk_ctrl
 *
 * CSK Control Register
 * This register controls the clock shrink/stop module.
 */
union bdk_csk_ctrl
{
    uint64_t u;
    struct bdk_csk_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t csk_send              : 55; /**< [ 63:  9](R/W) Bits reserved for a generic send struct if needed. */
        uint64_t stop_test             : 1;  /**< [  8:  8](R/W) Stop the cycle counter from counting, e.g. set when the test is finished.
                                                                 Software sets this to 1 to stop the test.  This bit must be cleared
                                                                 by software in the IDLE FSM state before another test can be run. */
        uint64_t clock_delay_select    : 3;  /**< [  7:  5](R/W) Delay amount in number of delay taps for the PDLY module. */
        uint64_t shrink_settings       : 2;  /**< [  4:  3](R/W) Type of clock shrink for a given test.
                                                                 0x0 = Falling edge shrink and negative phase shrink.
                                                                 0x1 = Falling edge shrink and positive phase shrink.
                                                                 0x2 = Rising edge shrink and negative phase shrink.
                                                                 0x3 = Rising edge shrink and positive phase shrink. */
        uint64_t stop_clk_mode         : 1;  /**< [  2:  2](R/W) If set, the clock will be stopped on a given test. */
        uint64_t shrink_clk_mode       : 1;  /**< [  1:  1](R/W) If set, the clk will be shrunk on a given test. */
        uint64_t csk_en                : 1;  /**< [  0:  0](R/W) Enables the control FSM.
                                                                 0 = Reset FSM, e.g. after a test has completed.
                                                                 1 = Load settings into clk shrink/stop FSM. */
#else /* Word 0 - Little Endian */
        uint64_t csk_en                : 1;  /**< [  0:  0](R/W) Enables the control FSM.
                                                                 0 = Reset FSM, e.g. after a test has completed.
                                                                 1 = Load settings into clk shrink/stop FSM. */
        uint64_t shrink_clk_mode       : 1;  /**< [  1:  1](R/W) If set, the clk will be shrunk on a given test. */
        uint64_t stop_clk_mode         : 1;  /**< [  2:  2](R/W) If set, the clock will be stopped on a given test. */
        uint64_t shrink_settings       : 2;  /**< [  4:  3](R/W) Type of clock shrink for a given test.
                                                                 0x0 = Falling edge shrink and negative phase shrink.
                                                                 0x1 = Falling edge shrink and positive phase shrink.
                                                                 0x2 = Rising edge shrink and negative phase shrink.
                                                                 0x3 = Rising edge shrink and positive phase shrink. */
        uint64_t clock_delay_select    : 3;  /**< [  7:  5](R/W) Delay amount in number of delay taps for the PDLY module. */
        uint64_t stop_test             : 1;  /**< [  8:  8](R/W) Stop the cycle counter from counting, e.g. set when the test is finished.
                                                                 Software sets this to 1 to stop the test.  This bit must be cleared
                                                                 by software in the IDLE FSM state before another test can be run. */
        uint64_t csk_send              : 55; /**< [ 63:  9](R/W) Bits reserved for a generic send struct if needed. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_csk_ctrl_s cn; */
};
typedef union bdk_csk_ctrl bdk_csk_ctrl_t;

#define BDK_CSK_CTRL BDK_CSK_CTRL_FUNC()
static inline uint64_t BDK_CSK_CTRL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CSK_CTRL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00e000010ll;
    __bdk_csr_fatal("CSK_CTRL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CSK_CTRL bdk_csk_ctrl_t
#define bustype_BDK_CSK_CTRL BDK_CSR_TYPE_RSL
#define basename_BDK_CSK_CTRL "CSK_CTRL"
#define device_bar_BDK_CSK_CTRL 0x0 /* PF_BAR0 */
#define busnum_BDK_CSK_CTRL 0
#define arguments_BDK_CSK_CTRL -1,-1,-1,-1

/**
 * Register (RSL) csk_cycle_count
 *
 * CSK Cycle Count Register
 */
union bdk_csk_cycle_count
{
    uint64_t u;
    struct bdk_csk_cycle_count_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cycle_count           : 64; /**< [ 63:  0](R/W/H) Current core-clock cycle counter value. */
#else /* Word 0 - Little Endian */
        uint64_t cycle_count           : 64; /**< [ 63:  0](R/W/H) Current core-clock cycle counter value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_csk_cycle_count_s cn; */
};
typedef union bdk_csk_cycle_count bdk_csk_cycle_count_t;

#define BDK_CSK_CYCLE_COUNT BDK_CSK_CYCLE_COUNT_FUNC()
static inline uint64_t BDK_CSK_CYCLE_COUNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CSK_CYCLE_COUNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00e000038ll;
    __bdk_csr_fatal("CSK_CYCLE_COUNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CSK_CYCLE_COUNT bdk_csk_cycle_count_t
#define bustype_BDK_CSK_CYCLE_COUNT BDK_CSR_TYPE_RSL
#define basename_BDK_CSK_CYCLE_COUNT "CSK_CYCLE_COUNT"
#define device_bar_BDK_CSK_CYCLE_COUNT 0x0 /* PF_BAR0 */
#define busnum_BDK_CSK_CYCLE_COUNT 0
#define arguments_BDK_CSK_CYCLE_COUNT -1,-1,-1,-1

/**
 * Register (RSL) csk_scratch
 *
 * INTERNAL: CSK Scratch Register
 *
 * This register is a scratch register for software use.
 */
union bdk_csk_scratch
{
    uint64_t u;
    struct bdk_csk_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data, not used by hardware. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data, not used by hardware. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_csk_scratch_s cn; */
};
typedef union bdk_csk_scratch bdk_csk_scratch_t;

#define BDK_CSK_SCRATCH BDK_CSK_SCRATCH_FUNC()
static inline uint64_t BDK_CSK_SCRATCH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CSK_SCRATCH_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00e000000ll;
    __bdk_csr_fatal("CSK_SCRATCH", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CSK_SCRATCH bdk_csk_scratch_t
#define bustype_BDK_CSK_SCRATCH BDK_CSR_TYPE_RSL
#define basename_BDK_CSK_SCRATCH "CSK_SCRATCH"
#define device_bar_BDK_CSK_SCRATCH 0x0 /* PF_BAR0 */
#define busnum_BDK_CSK_SCRATCH 0
#define arguments_BDK_CSK_SCRATCH -1,-1,-1,-1

/**
 * Register (RSL) csk_shrink_start_index
 *
 * CSK Start Cycle Index Register
 */
union bdk_csk_shrink_start_index
{
    uint64_t u;
    struct bdk_csk_shrink_start_index_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t shrink_start          : 64; /**< [ 63:  0](R/W) Core-clock cycle number to start clk shrink. */
#else /* Word 0 - Little Endian */
        uint64_t shrink_start          : 64; /**< [ 63:  0](R/W) Core-clock cycle number to start clk shrink. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_csk_shrink_start_index_s cn; */
};
typedef union bdk_csk_shrink_start_index bdk_csk_shrink_start_index_t;

#define BDK_CSK_SHRINK_START_INDEX BDK_CSK_SHRINK_START_INDEX_FUNC()
static inline uint64_t BDK_CSK_SHRINK_START_INDEX_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CSK_SHRINK_START_INDEX_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00e000020ll;
    __bdk_csr_fatal("CSK_SHRINK_START_INDEX", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CSK_SHRINK_START_INDEX bdk_csk_shrink_start_index_t
#define bustype_BDK_CSK_SHRINK_START_INDEX BDK_CSR_TYPE_RSL
#define basename_BDK_CSK_SHRINK_START_INDEX "CSK_SHRINK_START_INDEX"
#define device_bar_BDK_CSK_SHRINK_START_INDEX 0x0 /* PF_BAR0 */
#define busnum_BDK_CSK_SHRINK_START_INDEX 0
#define arguments_BDK_CSK_SHRINK_START_INDEX -1,-1,-1,-1

/**
 * Register (RSL) csk_shrink_stop_index
 *
 * CSK Stop Cycle Index Register
 */
union bdk_csk_shrink_stop_index
{
    uint64_t u;
    struct bdk_csk_shrink_stop_index_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t shrink_stop           : 64; /**< [ 63:  0](R/W) Core-clock cycle number to stop clk shrink. */
#else /* Word 0 - Little Endian */
        uint64_t shrink_stop           : 64; /**< [ 63:  0](R/W) Core-clock cycle number to stop clk shrink. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_csk_shrink_stop_index_s cn; */
};
typedef union bdk_csk_shrink_stop_index bdk_csk_shrink_stop_index_t;

#define BDK_CSK_SHRINK_STOP_INDEX BDK_CSK_SHRINK_STOP_INDEX_FUNC()
static inline uint64_t BDK_CSK_SHRINK_STOP_INDEX_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CSK_SHRINK_STOP_INDEX_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00e000028ll;
    __bdk_csr_fatal("CSK_SHRINK_STOP_INDEX", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CSK_SHRINK_STOP_INDEX bdk_csk_shrink_stop_index_t
#define bustype_BDK_CSK_SHRINK_STOP_INDEX BDK_CSR_TYPE_RSL
#define basename_BDK_CSK_SHRINK_STOP_INDEX "CSK_SHRINK_STOP_INDEX"
#define device_bar_BDK_CSK_SHRINK_STOP_INDEX 0x0 /* PF_BAR0 */
#define busnum_BDK_CSK_SHRINK_STOP_INDEX 0
#define arguments_BDK_CSK_SHRINK_STOP_INDEX -1,-1,-1,-1

#endif /* __BDK_CSRS_CSK_H__ */
