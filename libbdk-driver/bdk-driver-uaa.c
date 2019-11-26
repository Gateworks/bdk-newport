/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-uaa.h"

BDK_REQUIRE_DEFINE(DRIVER_UAA);

/**
 * The UAA probe function doesn't need to do anything with the hardware
 *
 * @param device UAA uart to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.UAA%d", device->node, device->instance);
    return 0;
}

/**
 * UAA init() registers the uart as a device and connects it to the BDK console
 *
 * @param device UAA uart to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    /* Enable the PCI master control bits */
    bdk_pccpf_xxx_cmd_t cmd;
    cmd.u = bdk_ecam_read32(device, BDK_PCCPF_XXX_CMD);
    cmd.s.me = 1;
    cmd.s.msae = 1;
    bdk_ecam_write32(device, BDK_PCCPF_XXX_CMD, cmd.u);

    /* The first two uarts are setup very early during init, so this driver only needs to
       cover uarts 2 and above on the master node */
    if ((device->node == bdk_numa_master()) && (device->instance < 2))
        return 0;

    /* Set the baud rate if it isn't already set */
    BDK_CSR_INIT(uctl_ctl, device->node, BDK_UAAX_UCTL_CTL(device->instance));
    if (!uctl_ctl.s.h_clk_en)
        bdk_set_baudrate(device->node, device->instance, 115200, false);

    /* Register the device */
    extern const __bdk_fs_dev_ops_t bdk_fs_uart_ops;
    if (bdk_fs_register_dev("uart", device->instance, &bdk_fs_uart_ops))
        return -1;

    /* Connect the console to the uart */
    char filename[16];
    snprintf(filename, sizeof(filename), "/dev/n%d.uart%d", device->node, device->instance);
    return bdk_console_open_file(filename);
}

bdk_driver_t __bdk_driver_uaa = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_UAA),
    .name = "UAA",
    .probe = probe,
    .init = init,
};
