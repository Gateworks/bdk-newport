/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-mcc.h"

BDK_REQUIRE_DEFINE(DRIVER_MCC);

/**
 * The MCC probe function
 *
 * @param device MCC to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.MCC%d", device->node, device->instance);
    return 0;
}

/**
 * MCC init() function
 *
 * @param device MCC to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    /* Disable ECC on the emulator */
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
    {
        for (int i = 0; i < 2; i++)
        {
            BDK_BAR_MODIFY(c, device, BDK_MCCX_LMCOEX_CFG(device->instance, i),
                c.s.dram_ecc_ena = 0);
        }
    }
    return 0;
}

bdk_driver_t __bdk_driver_mcc = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_MCC),
    .name = "MMC",
    .probe = probe,
    .init = init,
};
