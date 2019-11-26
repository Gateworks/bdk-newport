/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER_PCIEEP);
#include "libbdk-arch/bdk-csrs-ecam.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"

/**
 * The PCIe EP probe function needs to hide PEMs in EP mode
 *
 * @param device Device to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    static int count = 0; /* device->instance is not set, provide unique name*/
    /* Workaround for bug#28612
       PEMs in CN83XX populate entries for PCIEEP in internal ECAM
       for devices in EP mode. They need to be removed.
       VFs of EP will also be removed. It is a desired side-effect.
    */
    /* Change the device name so it is easy to tell device is EP */
    bdk_device_rename(device, "N%d.PCIEEP%d", device->node, count);
    count++;
    /* PCIe is a EP. Hide it */
    BDK_CSR_MODIFY(c, device->node, BDK_ECAMX_DEVX_SDIS(device->ecam, device->dev),
                   c.s.dis = 1);
    BDK_CSR_MODIFY(c, device->node, BDK_ECAMX_DEVX_NSDIS(device->ecam, device->dev),
                   c.s.dis = 1);
    BDK_TRACE(DEVICE, "%s: EP device hidden\n", device->name);
    return 0;

}

/**
 * init() currently does nothing
 *
 * @param device Device to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    return 0;
}

bdk_driver_t __bdk_driver_pcieep = {
    .id = (BDK_PCC_PROD_E_CN83XX << 24) | BDK_PCC_VENDOR_E_CAVIUM | (BDK_PCC_DEV_IDL_E_CHIP << 16),
    .name = "CN83XX-PCIEEP",
    .probe = probe,
    .init = init,
};
