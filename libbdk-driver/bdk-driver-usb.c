/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"

BDK_REQUIRE_DEFINE(DRIVER_USB);

/**
 * The USB probe function doesn't need to do anything with the hardware
 *
 * @param device USB to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.USB%d", device->node, device->instance);
    return 0;
}

/**
 * USB init()
 *
 * @param device USB to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        /* Enable the PCI master control bits */
        bdk_pccpf_xxx_cmd_t cmd;
        cmd.u = bdk_ecam_read32(device, BDK_PCCPF_XXX_CMD);
        cmd.s.me = 1;
        cmd.s.msae = 1;
        bdk_ecam_write32(device, BDK_PCCPF_XXX_CMD, cmd.u);
    }
    return 0;
}

bdk_driver_t __bdk_driver_usb = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_USBDRD),
    .name = "USB",
    .probe = probe,
    .init = init,
};
