/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pbus.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"

BDK_REQUIRE_DEFINE(DRIVER_PBUS);

/**
 * The PBUS probe function
 *
 * @param device PBUS to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    bdk_device_rename(device, "N%d.PBUS%d", device->node, device->instance);
    return 0;
}

/**
 * PBUS init() function
 *
 * @param device PBUS to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    /* Enable all 8 PBUS regions */
    for (int region = 0; region < 8;region++)
    {
        BDK_CSR_INIT(pbus_cfg, device->node, BDK_PBUS_REGX_CFG(region));
        /* Default the region to be enabled */
        pbus_cfg.s.en = 1;
        /* Set each region to be 512MB. This is the largest size possible with
           8 regions. The upper 3 of the 32 address bits are used for selecting
           the region */
        pbus_cfg.s.size = 0x1fff;
        /* Allow the device tree to override PBUS_REGX_CFG. Note that the
           size and base can't be changed in the device tree as that affects
           code */
        int64_t cfg = bdk_config_get_int(BDK_CONFIG_PBUS_CFG, region, device->node);
        if (cfg)
            pbus_cfg.u = cfg;
        /* The upper 3 of the 32 address bits are used for selecting the region */
        pbus_cfg.s.base = region << 13;
        BDK_CSR_WRITE(device->node, BDK_PBUS_REGX_CFG(region), pbus_cfg.u);
        /* Allow the device tree to override PBUS_REGX_TIM */
        int64_t tim = bdk_config_get_int(BDK_CONFIG_PBUS_TIM, region, device->node);
        if (tim)
            BDK_CSR_WRITE(device->node, BDK_PBUS_REGX_TIM(region), tim);
    }
    return 0;
}

bdk_driver_t __bdk_driver_pbus = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_PBUS),
    .name = "PBUS",
    .probe = probe,
    .init = init,
};
