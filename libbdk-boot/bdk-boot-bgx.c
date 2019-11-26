/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-bgx.h"

/**
 * Configure BGX on all nodes as part of booting
 */
void bdk_boot_bgx(void)
{
    int max_bgx = 2;
    if (bdk_is_model(OCTEONTX_CN83XX)) max_bgx = 4;

    /* Initialize BGX, ready for driver */
    for (bdk_node_t n = BDK_NODE_0; n < BDK_NUMA_MAX_NODES; n++)
    {
        if (bdk_numa_exists(n))
        {
            /* Enable ports based on config file. */
            for (int bgx = 0; bgx < max_bgx; bgx++)
            {
                for (int p = 0; p < 4; p++)
                {
                    int en = bdk_config_get_int(BDK_CONFIG_BGX_ENABLE, n, bgx, p);
                    if (en == 0)
                    {
                        /* Mark this port as disabled */
                        BDK_CSR_WRITE(n, BDK_BGXX_CMRX_RX_DMAC_CTL(bgx, p), 0);
                    }
                }
            }
        }
    }
}
