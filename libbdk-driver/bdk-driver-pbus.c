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
    .id = (BDK_PCC_PROD_E_GEN << 24) | BDK_PCC_VENDOR_E_CAVIUM | (BDK_PCC_DEV_IDL_E_PBUS << 16),
    .probe = probe,
    .init = init,
};
