/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-smmu.h"

BDK_REQUIRE_DEFINE(DRIVER_SMMU);

/**
 * The SMMU probe function does all initialization so that other devices may do
 * DMAs in their init() functions. The assumption is that no DMAs will be needed
 * until the SMMU probe() is complete.
 *
 * @param device SMMU to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe_cn8xxx(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.SMMU%d", device->node, device->instance);

    /* Allow all IO units to access secure memory */
    for (int i = 0; i < 2048; i++)
        BDK_BAR_WRITE(device, BDK_SMMUX_SSDRX(device->instance, i), 0);
    return 0;
}

/**
 * The SMMU probe function does all initialization so that other devices may do
 * DMAs in their init() functions. The assumption is that no DMAs will be needed
 * until the SMMU probe() is complete.
 *
 * @param device SMMU to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe_cn9xxx(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.SMMU%d", device->node, device->instance);
    /* Force all DMAs to be secure */
    BDK_BAR_MODIFY(c, device, BDK_SMMUX_S_GBPA(device->instance),
        c.s.nscfg = 2);
    return 0;
}

/**
 * SMMU init() function
 *
 * @param device SMMU to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    /* Nothing to do here */
    return 0;
}

bdk_driver_t __bdk_driver_smmu = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_SMMU),
    .name = "SMMU",
    .probe = probe_cn8xxx,
    .init = init,
};


bdk_driver_t __bdk_driver_smmu3 = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_SMMU3),
    .name = "SMMU3",
    .probe = probe_cn9xxx,
    .init = init,
};
