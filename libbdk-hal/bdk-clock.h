/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to Core, IO and DDR Clock.
 *
 * <hr>$Revision: 45089 $<hr>
 *
 * @addtogroup hal
 * @{
 */

#define BDK_GTI_RATE 100000000ull

/**
 * Enumeration of different Clocks.
 */
typedef enum{
    BDK_CLOCK_TIME,     /**< Clock for telling time with fast access. Uses GTI in core */
    BDK_CLOCK_MAIN_REF, /**< Main reference clock */
    BDK_CLOCK_RCLK,     /**< Clock used by cores, coherent bus and L2 cache. */
    BDK_CLOCK_SCLK,     /**< Clock used by IO blocks. */
} bdk_clock_t;

/**
 * Called in __bdk_init to setup the global timer
 */
extern void bdk_clock_setup();

/**
 * Get cycle count based on the clock type.
 *
 * @param clock - Enumeration of the clock type.
 * @return      - Get the number of cycles executed so far.
 */
static inline uint64_t bdk_clock_get_count(bdk_clock_t clock) __attribute__ ((always_inline));
static inline uint64_t bdk_clock_get_count(bdk_clock_t clock)
{
    extern uint64_t __bdk_clock_get_count_slow(bdk_clock_t clock);
    if (clock == BDK_CLOCK_TIME)
    {
        uint64_t clk;
        BDK_MRS(CNTPCT_EL0, clk);
        return clk;
    }
    else
        return __bdk_clock_get_count_slow(clock);
}

/**
 * Get clock rate based on the clock type.
 *
 * @param node    Node to use in a Numa setup. Can be an exact ID or a special value.
 * @param clock - Enumeration of the clock type.
 * @return      - return the clock rate.
 */
static inline uint64_t bdk_clock_get_rate(bdk_node_t node, bdk_clock_t clock) __attribute__ ((always_inline, pure));
static inline uint64_t bdk_clock_get_rate(bdk_node_t node, bdk_clock_t clock)
{
    extern uint64_t __bdk_clock_get_rate_slow(bdk_node_t node, bdk_clock_t clock) __attribute__ ((pure));
    if (clock == BDK_CLOCK_TIME)
        return BDK_GTI_RATE; /* Programed as part of setup */
    else
        return __bdk_clock_get_rate_slow(node, clock);
}

/** @} */
