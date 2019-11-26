/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

static void init_early(void)
{
    BDK_TRACE(INIT, "ASIM-CN96XX: Called %s\n", __FUNCTION__);
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "ASIM-CN96XX: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    BDK_TRACE(INIT, "ASIM-CN96XX: Called %s\n", __FUNCTION__);
}

static const bdk_boot_callbacks_t asim_cn96xx = {
    .board_name = "ASIM-CN96XX-A0",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(asim_cn96xx);

