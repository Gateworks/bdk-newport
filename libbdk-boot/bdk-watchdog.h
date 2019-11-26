/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Utility functions for controlling the watchdog during boot
 *
 * @defgroup watchdog Watchdog related functions
 * @{
 */

/**
 * Setup the watchdog to expire in timeout_ms milliseconds. When the watchdog
 * expires, the chip three things happen:
 * 1) Expire 1: interrupt that is ignored by the BDK
 * 2) Expire 2: DEL3T interrupt, which is disabled and ignored
 * 3) Expire 3: Soft reset of the chip
 *
 * Since we want a soft reset, we actually program the watchdog to expire at
 * the timeout / 3.
 *
 * @param timeout_ms Timeout in milliseconds. If this is zero, the timeout is taken from the
 *                   global configuration option BDK_BRD_CFG_WATCHDOG_TIMEOUT
 */
extern void bdk_watchdog_set(unsigned int timeout_ms);

/**
 * Signal the watchdog that we are still running
 */
extern void bdk_watchdog_poke(void);

/**
 * Disable the hardware watchdog
 */
extern void bdk_watchdog_disable(void);

/**
 * Return true if the watchdog is configured and running
 *
 * @return Non-zero if watchdog is running
 */
extern int bdk_watchdog_is_running(void);

/** @} */
