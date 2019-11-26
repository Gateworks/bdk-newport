/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"

BDK_REQUIRE_DEFINE(DRIVER_SATA);

/**
 * The SATA probe function doesn't need to do anything with the hardware
 *
 * @param device SATA to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.SATA%d", device->node, device->instance);
    return 0;
}

/**
 * SATA init() enables bus mastering
 *
 * @param device SATA to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    bdk_pccpf_xxx_cmd_t cmd;
    cmd.u = bdk_ecam_read32(device, BDK_PCCPF_XXX_CMD);
    cmd.s.me = 1;
    cmd.s.msae = 1;
    bdk_ecam_write32(device, BDK_PCCPF_XXX_CMD, cmd.u);
    return 0;
}

bdk_driver_t __bdk_driver_sata = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_SATA),
    .name = "SATA",
    .probe = probe,
    .init = init,
};

bdk_driver_t __bdk_driver_sata5 = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_SATA5),
    .name = "SATA5",
    .probe = probe,
    .init = init,
};
