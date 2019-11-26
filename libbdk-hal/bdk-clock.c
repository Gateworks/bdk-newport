/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gti.h"

/**
 * Called in __bdk_init to setup the global timer
 */
void bdk_clock_setup(bdk_node_t node)
{
    const bdk_node_t local_node = bdk_numa_local();

    /* Check if the counter was already setup */
    BDK_CSR_INIT(cntcr, node, BDK_GTI_CC_CNTCR);
    if (cntcr.s.en)
        return;

    /* Configure GTI to tick at BDK_GTI_RATE */
    uint64_t sclk = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
    uint64_t inc = (BDK_GTI_RATE << 32) / sclk;
    BDK_CSR_WRITE(node, BDK_GTI_CC_CNTRATE, inc);
    BDK_CSR_WRITE(node, BDK_GTI_CTL_CNTFRQ, BDK_GTI_RATE);
    cntcr.s.en = 1;
    if (node != local_node)
    {
        /* Synchronize with local node. Very simple set of counter, will be
           off a little */
        BDK_CSR_WRITE(node, BDK_GTI_CC_CNTCV, bdk_clock_get_count(BDK_CLOCK_TIME));
    }
    /* Enable the counter */
    BDK_CSR_WRITE(node, BDK_GTI_CC_CNTCR, cntcr.u);
    BDK_CSR_READ(node, BDK_GTI_CC_CNTCR);
}

/**
 * Get cycle count based on the clock type.
 *
 * @param clock - Enumeration of the clock type.
 * @return      - Get the number of cycles executed so far.
 */
uint64_t __bdk_clock_get_count_slow(bdk_clock_t clock)
{
    bdk_node_t node = bdk_numa_local();
    BDK_CSR_INIT(rst_boot, node, BDK_RST_BOOT);
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
    {
        /* Force RCLK and SCLK to be 1GHz on emulator */
        rst_boot.s.c_mul = 20;
        rst_boot.s.pnr_mul = 20;
    }
    uint64_t ref_cntr = BDK_CSR_READ(node, BDK_RST_REF_CNTR);
    switch(clock)
    {
        case BDK_CLOCK_TIME:
            return 0; /* Handled in fast path */
        case BDK_CLOCK_MAIN_REF:
            return ref_cntr;
        case BDK_CLOCK_RCLK:
            if (bdk_is_model(OCTEONTX_CN8XXX))
                return ref_cntr * rst_boot.s.c_mul;
            else /* Multiplier is based on 50Mhz, not 100Mhz */
                return ref_cntr * rst_boot.s.c_mul / 2;
        case BDK_CLOCK_SCLK:
            if (bdk_is_model(OCTEONTX_CN8XXX))
                return ref_cntr * rst_boot.s.pnr_mul;
            else /* Multiplier is based on 50Mhz, not 100Mhz */
                return ref_cntr * rst_boot.s.pnr_mul / 2;
    }
    return 0;
}

/**
 * Get clock rate based on the clock type.
 *
 * @param node    Node to use in a Numa setup. Can be an exact ID or a special value.
 * @param clock - Enumeration of the clock type.
 * @return      - return the clock rate.
 */
uint64_t __bdk_clock_get_rate_slow(bdk_node_t node, bdk_clock_t clock)
{
    /* For all chips the multipliers are defined based on a 50Mhz
       clock, even though the main reference is 50Mhz for CN8XXX and
       100Mhz for CN9XXX */
    const uint64_t MUL_REF = 50000000;

    /* Get the multipliers for RCLK and SCLK */
    BDK_CSR_INIT(mio_rst_boot, node, BDK_RST_BOOT);
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
    {
        /* Force RCLK and SCLK to be 1GHz on emulator */
        mio_rst_boot.s.c_mul = 20;
        mio_rst_boot.s.pnr_mul = 20;
    }

    switch (clock)
    {
        case BDK_CLOCK_TIME:
            return BDK_GTI_RATE; /* Programed as part of setup */
        case BDK_CLOCK_MAIN_REF:
            /* This is currently defined to be 50Mhz for CN8XXX and 100Mhz
               for CN9XXX */
            return bdk_is_model(OCTEONTX_CN8XXX) ? 50000000 : 100000000;
        case BDK_CLOCK_RCLK:
            return MUL_REF * mio_rst_boot.s.c_mul;
        case BDK_CLOCK_SCLK:
            return MUL_REF * mio_rst_boot.s.pnr_mul;
    }
    return 0;
}

