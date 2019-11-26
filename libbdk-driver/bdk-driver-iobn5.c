/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-iobn.h"
#include "libbdk-arch/bdk-csrs-ecam.h"

BDK_REQUIRE_DEFINE(DRIVER_IOBN5);

/**
 * The SMMU probe function does all initialization so that other devices may do
 * DMAs in their init() functions. The assumption is that no DMAs will be needed
 * until the SMMU probe() is complete.
 *
 * @param device SMMU to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.IOBN5%d", device->node, device->instance);

    /* Allow all IO units to access secure memory */
    for (int pcc = 0; pcc < 256; pcc++)
        BDK_BAR_WRITE(device, BDK_IOBNX_RSLX_STREAMS(device->instance, pcc), 0);

    /* Loop through all possible domains. ECAMX_DOMX_CONST is supposed to tells
       us what exists, but it lies. Just hardcode the ranges and hope for the
       best. Talk about overly complicated hardware */
    for (int domain = 0; domain < 7; domain++)
    {
        for (int bus = 0; bus < 256; bus++)
            BDK_BAR_WRITE(device, BDK_IOBNX_DOMX_BUSX_STREAMS(device->instance, domain, bus), 0);
        for (int dev = 0; dev < 32; dev++)
            BDK_BAR_WRITE(device, BDK_IOBNX_DOMX_DEVX_STREAMS(device->instance, domain, dev), 0);
    }
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

bdk_driver_t __bdk_driver_iobn5 = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_IOBN5),
    .name = "IOBN5",
    .probe = probe,
    .init = init,
};
