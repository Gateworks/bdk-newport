/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include "libbdk-arch/bdk-csrs-uaa.h"

/**
 * Wait for the specified number of micro seconds
 *
 * @param usec   micro seconds to wait
 */
void bdk_wait_usec(uint64_t usec)
{
    uint64_t done = bdk_clock_get_count(BDK_CLOCK_TIME) + usec * bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;
    do
    {
        bdk_thread_yield();
    } while (bdk_clock_get_count(BDK_CLOCK_TIME) < done);
}

/**
 * Wait for the specified number of core clock cycles
 *
 * @param cycles
 */
void bdk_wait(uint64_t cycles)
{
    uint64_t done = bdk_clock_get_count(BDK_CLOCK_TIME) + cycles;

    while (bdk_clock_get_count(BDK_CLOCK_TIME) < done)
    {
        /* Spin */
    }
}

/**
 * Perform a soft reset of the chip
 *
 * @return
 */
void bdk_reset_chip(bdk_node_t node)
{
    fflush(NULL);

    /* Wait for TX fifo to empty */
    while (1)
    {
        BDK_CSR_INIT(fr, node, BDK_UAAX_FR(0));
        if (fr.s.txfe)
            break;
        bdk_thread_yield();
    }

    /* RST_OCX is not cleared by a chip reset. Clear it now to avoid repeated
       resets due to CCPI state changes during reset */
    BDK_CSR_WRITE(node, BDK_RST_OCX, 0);
    BDK_CSR_READ(node, BDK_RST_OCX);

    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        bdk_rst_soft_rst_t rst_soft_rst;
        rst_soft_rst.u = 0;
        rst_soft_rst.s.soft_rst = 1;
        BDK_CSR_WRITE(node, BDK_RST_SOFT_RST, rst_soft_rst.u);
    }
    else
    {
        bdk_rst_chip_domain_w1s_t rst_chip;
        rst_chip.u = 0;
        rst_chip.s.soft_rst = 1;
        BDK_CSR_WRITE(node, BDK_RST_CHIP_DOMAIN_W1S, rst_chip.u);
    }
}

/**
 * Perform a cold reset of the chip
 *
 * @return
 */
void bdk_reset_cold(bdk_node_t node)
{
    fflush(NULL);

    /* Wait for TX fifo to empty */
    while (1)
    {
        BDK_CSR_INIT(fr, node, BDK_UAAX_FR(0));
        if (fr.s.txfe)
            break;
        bdk_thread_yield();
    }

    /* RST_OCX is not cleared by a chip reset. Clear it now to avoid repeated
       resets due to CCPI state changes during reset */
    BDK_CSR_WRITE(node, BDK_RST_OCX, 0);
    BDK_CSR_READ(node, BDK_RST_OCX);

    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        bdk_rst_soft_rst_t rst_soft_rst;
        rst_soft_rst.u = 0;
        rst_soft_rst.s.soft_rst = 1;
        BDK_CSR_WRITE(node, BDK_RST_SOFT_RST, rst_soft_rst.u);
    }
    else
    {
        bdk_rst_cold_domain_w1s_t rst_cold;
        rst_cold.u = 0;
        rst_cold.s.soft_rst = 1;
        BDK_CSR_WRITE(node, BDK_RST_COLD_DOMAIN_W1S, rst_cold.u);
    }
}

