/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
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
 * UAA init() registers the uart as a devcie and connects it to the BDK console
 *
 * @param device UAA uart to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
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
    .id = (BDK_PCC_PROD_E_GEN << 24) | BDK_PCC_VENDOR_E_CAVIUM | (BDK_PCC_DEV_IDL_E_UAA << 16),
    .probe = probe,
    .init = init,
};
