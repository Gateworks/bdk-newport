/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

static void init_early(void)
{

    bdk_qlm_clock_t qlm0_clk, qlm1_clk, qlm2_clk;

    BDK_TRACE(INIT, "CN96XX-CRB: Called %s\n", __FUNCTION__);

    /*
     * Disable the SSC of clock generator if the reference clock of PCIe
     * QLM is using non-SSC clock (common clock 0)
     *
    */

    /* Get QLM0/1/2 clock source */
    qlm0_clk = bdk_config_get_int(BDK_CONFIG_QLM_CLK, BDK_NODE_0, 0);
    qlm1_clk = bdk_config_get_int(BDK_CONFIG_QLM_CLK, BDK_NODE_0, 1);
    qlm2_clk = bdk_config_get_int(BDK_CONFIG_QLM_CLK, BDK_NODE_0, 2);

    /* If any of the PCIe clock source is refclk0, then we need to disable SSC */
    if (qlm0_clk == BDK_QLM_CLK_COMMON_0 ||
        qlm1_clk == BDK_QLM_CLK_COMMON_0 ||
        qlm2_clk == BDK_QLM_CLK_COMMON_0)
    {
        bdk_device_t *device = bdk_device_gpio_lookup(NULL, -1);
        bdk_device_gpio_setup(device, 5, true, 1, true, false);
    }
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "CN96XX-CRB: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    BDK_TRACE(INIT, "CN96XX-CRB: Called %s\n", __FUNCTION__);
}

static const bdk_boot_callbacks_t cn96xx_crb = {
    .board_name = "CN96XX-CRB",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(cn96xx_crb);
