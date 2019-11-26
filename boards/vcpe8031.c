/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

/* 
 * Read the GPIOs<28-25> to dynamically determine 
 * which M.2 module is connected to QLM3. Based on the GPIO config, 
 * QLM3 mode could be either a SATA_2X1 or PCIE_1X1
 *
 */ 
static void init_early(void)
{
    unsigned cfg[4] = {0};
    unsigned int m2_config =0;
    uint64_t gpio = 0;
    /* GPIO pins which are connected with M.2 configs*/
    int gpio_idx[4]={25,26,27,28};

    BDK_TRACE(INIT, "VCPE8031: Called %s\n", __FUNCTION__);
    
    /* Configure the GPIOs to read the M.2 settings */
    bdk_device_t *device = bdk_device_gpio_lookup(NULL, -1);
    for (int i=0; i<4; i++)
    {
        bdk_device_gpio_setup(device, gpio_idx[i], false, 0, false, false);
    }
    
    /* Read the GPIOs */
    gpio = bdk_device_gpio_readstate(device, 0);

    for (int i=0;i<4;i++ )
    {
        cfg[i] = !!(gpio & (1ULL<<gpio_idx[i]));
    }
    m2_config=cfg[0] | cfg[1]<<1 | cfg[2]<<2 | cfg[3]<<3;

    if(m2_config == 0)
    {
	/* Set QLM3 mode as SATA_2X1 in Gen3 */
        bdk_config_set_str("SATA_2X1", BDK_CONFIG_QLM_MODE, 0, 3, 0); /* node, qlm, lane */
        bdk_config_set_int(6000, BDK_CONFIG_QLM_FREQ, 0, 3, 0);
    }
    else if(m2_config <= 15)
    {
	/* Set QLM3 mode as PCIE_1X1 */
        bdk_config_set_str("PCIE_1X1", BDK_CONFIG_QLM_MODE, 0, 3, 0);
    }
    else
    {
	/* Disable QLM3 */
        bdk_config_set_str("DISABLED", BDK_CONFIG_QLM_MODE, 0, 3, 0);
    }

    
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "VCPE8031: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    BDK_TRACE(INIT, "VCPE8031: Called %s\n", __FUNCTION__);
}

static const bdk_boot_callbacks_t vcpe8031 = {
    .board_name = "VCPE8031",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(vcpe8031);
