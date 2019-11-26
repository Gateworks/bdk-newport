/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

/**
 * Configure USB on all nodes as part of booting
 */
void bdk_boot_usb(void)
{
    if (!bdk_is_model(OCTEONTX_CN8XXX) && !bdk_is_model(OCTEONTX_CN96XX_PASS1_X))
        return;
    /* Initialize USB, ready for standard XHCI driver */
    for (bdk_node_t n = BDK_NODE_0; n < BDK_NUMA_MAX_NODES; n++)
    {
        if (bdk_numa_exists(n))
        {
            for (int p = 0; p < 2; p++)
            {
                int usb_refclock = bdk_config_get_int(BDK_CONFIG_USB_REFCLK_SRC, n,p);
                BDK_TRACE(INIT, "Initializing USB%d on Node %d clock type %d\n", p, n, usb_refclock);
                bdk_usb_initialize(n, p, usb_refclock);
            }
        }
    }
}
