/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gti.h"

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
void bdk_watchdog_set(unsigned int timeout_ms)
{
    if (timeout_ms == 0)
        timeout_ms = bdk_config_get_int(BDK_CONFIG_WATCHDOG_TIMEOUT);

    if (timeout_ms > 0)
    {
        uint64_t sclk = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_SCLK);
        uint64_t timeout_sclk = sclk * timeout_ms / 1000;
        /* Per comment above, we want the watchdog to expire at 3x the rate specified */
        timeout_sclk /= 3;
        /* Watchdog counts in 1024 cycle steps */
        uint64_t timeout_wdog = timeout_sclk >> 10;
        /* We can only specify the upper 16 bits of a 24 bit value. Round up */
        timeout_wdog = (timeout_wdog + 0xff) >> 8;
        /* If the timeout overflows the hardware limit, set max */
        if (timeout_wdog >= 0x10000)
            timeout_wdog = 0xffff;

        BDK_TRACE(INIT, "Watchdog: Set to expire %lu SCLK cycles\n", timeout_wdog << 18);
        BDK_CSR_MODIFY(c, bdk_numa_local(), BDK_GTI_CWD_WDOGX(bdk_get_core_num()),
            c.s.len = timeout_wdog;
            c.s.mode = 3);
    }
}

/**
 * Signal the watchdog that we are still running
 */
void bdk_watchdog_poke(void)
{
    BDK_CSR_WRITE(bdk_numa_local(), BDK_GTI_CWD_POKEX(bdk_get_core_num()), 0);
}

/**
 * Disable the hardware watchdog
 */
void bdk_watchdog_disable(void)
{
    BDK_CSR_WRITE(bdk_numa_local(), BDK_GTI_CWD_WDOGX(bdk_get_core_num()), 0);
    BDK_TRACE(INIT, "Watchdog: Disabled\n");
}

/**
 * Return true if the watchdog is configured and running
 *
 * @return Non-zero if watchdog is running
 */
int bdk_watchdog_is_running(void)
{
    BDK_CSR_INIT(wdog, bdk_numa_local(), BDK_GTI_CWD_WDOGX(bdk_get_core_num()));
    return wdog.s.mode != 0;
}

