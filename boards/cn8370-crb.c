/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"

static void init_early(void)
{
    BDK_TRACE(INIT, "CN8370-CRB: Called %s\n", __FUNCTION__);
    /* Disable PCA9547 internal TWSI mux to avoid SFP module EEPROM confilict with SPD */  
    bdk_device_t *twsi_device = bdk_device_lookup(0, BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_MIO_TWS), 0);
    if (bdk_device_twsi_write_ia(twsi_device, 0x70, 0, 1, 0, 0)) {
        bdk_error("TWSI write failed\n");
    }
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "CN8370-CRB: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    BDK_TRACE(INIT, "CN8370-CRB: Called %s\n", __FUNCTION__);
extern int load_88X33x0_fw(int node, int bus_id, int addr, int is_rate_match_on, int is_load_firmware, int is_multi_port);
    load_88X33x0_fw(0, 0, 0, 1, 1, 1);
    load_88X33x0_fw(0, 0, 1, 1, 0, 0);
    load_88X33x0_fw(0, 0, 2, 1, 0, 0);
    load_88X33x0_fw(0, 0, 3, 1, 0, 0);
}

static const bdk_boot_callbacks_t cn8370_crb = {
    .board_name = "CN8370-CRB",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(cn8370_crb);
