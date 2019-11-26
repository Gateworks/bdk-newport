/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pem.h"

static void init_early(void)
{
    BDK_TRACE(INIT, "SFF8304: Called %s\n", __FUNCTION__);
    
    int node = bdk_numa_master();
    BDK_CSR_INIT(pemx_strap, node, BDK_PEMX_STRAP(0));
    /* on sff8304, don't initialize QLM0/1 if PEM0 is in endpoint mode */
    if (pemx_strap.cn8.pimode != 3)
    {
        bdk_config_set_str(NULL, BDK_CONFIG_QLM_MODE, node, 0, 0); /* node, qlm, lane */
        bdk_config_set_str(NULL, BDK_CONFIG_QLM_MODE, node, 1, 0);
    }
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "SFF8304: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    BDK_TRACE(INIT, "SFF8304: Called %s\n", __FUNCTION__);
}

static const bdk_boot_callbacks_t sff8304 = {
    .board_name = "SFF8304",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(sff8304);

