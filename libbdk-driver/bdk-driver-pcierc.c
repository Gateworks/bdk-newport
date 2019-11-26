/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-ecam.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-pem.h"

BDK_REQUIRE_DEFINE(DRIVER_PCIERC);

/**
 * The PCIe RC probe function needs to hide PEMs in EP mode
 *
 * @param device Device to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    /* PEMs in CN83XX show up as PCIERC on the internal ECAMs regardless of
       whether the device is RC or EP. Hide devices that are turned on and
       in EP mode */
    BDK_CSR_INIT(pemx_on, device->node, BDK_PEMX_ON(device->instance));
    if (pemx_on.s.pemon)
    {
        /* Check if RC or EP */
        BDK_CSR_INIT(pemx_cfg, device->node, BDK_PEMX_CFG(device->instance));
        if (!pemx_cfg.cn83xx.hostmd)
        {
            /* Change the device name so it is easy to tell device is EP */
            bdk_device_rename(device, "N%d.PCIEEP%d", device->node, device->instance);
            /* PCIe is a EP. Hide it */
            BDK_CSR_MODIFY(c, device->node, BDK_ECAMX_DEVX_SDIS(device->ecam, device->dev),
                c.s.dis = 1);
            BDK_CSR_MODIFY(c, device->node, BDK_ECAMX_DEVX_NSDIS(device->ecam, device->dev),
                c.s.dis = 1);
            BDK_TRACE(DEVICE, "%s: EP device hidden\n", device->name);
            return 0;
        }
    }
    /* Change the device name to PCIe RC. This ignores the possibility that
       software manually configures a EP after probing takes place. That is
       only done in specialized testing */
    bdk_device_rename(device, "N%d.PCIERC%d", device->node, device->instance);
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

bdk_driver_t __bdk_driver_pcierc = {
    .id = (BDK_PCC_PROD_E_CN83XX << 24) | BDK_PCC_VENDOR_E_CAVIUM | (BDK_PCC_DEV_IDL_E_PCIERC << 16),
    .name = "CN83XX-PCIERC",
    .probe = probe,
    .init = init,
};
