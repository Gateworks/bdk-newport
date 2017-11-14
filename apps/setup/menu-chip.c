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
#include "menu-common.h"

/**
 * Convert a trace enum value into a friendly name
 *
 * @param e      Enum to convert
 *
 * @return String name
 */
static const char* get_trace_name(bdk_trace_enable_t e)
{
    switch (e)
    {
        case BDK_TRACE_ENABLE_BGX:          return "BGX Networking";
        case BDK_TRACE_ENABLE_DRAM:         return "DRAM Initialzation";
        case BDK_TRACE_ENABLE_DRAM_TEST:    return "DRAM Tests";
        case BDK_TRACE_ENABLE_INIT:         return "Early Initialization";
        case BDK_TRACE_ENABLE_ECAM:         return "ECAM Initialization";
        case BDK_TRACE_ENABLE_QLM:          return "QLM / SERDES";
        case BDK_TRACE_ENABLE_EMMC:         return "eMMC / SD";
        case BDK_TRACE_ENABLE_PCIE:         return "PCIe Link";
        case BDK_TRACE_ENABLE_PCIE_CONFIG:  return "PCIe config space reads / writes";
        case BDK_TRACE_ENABLE_SATA:         return "SATA/AHCI";
        case BDK_TRACE_ENABLE_CCPI:         return "CCPI - Multi-node";
        case BDK_TRACE_ENABLE_FATFS:        return "FatFs";
        case BDK_TRACE_ENABLE_MPI:          return "SPI / MPI";
        case BDK_TRACE_ENABLE_ENV:          return "Environment variables";
        case BDK_TRACE_ENABLE_FPA:          return "FPA - Free Pool Allocator";
        case BDK_TRACE_ENABLE_PKI:          return "PKI - Packet Input";
        case BDK_TRACE_ENABLE_PKO:          return "PKO - Packet Output";
        case BDK_TRACE_ENABLE_SSO:          return "SSO - Packet Scheduling";
        case BDK_TRACE_ENABLE_DEVICE:       return "ECAM Device Framework";
        case BDK_TRACE_ENABLE_DEVICE_SCAN:  return "ECAM Device Scan";
        case BDK_TRACE_ENABLE_NIC:          return "NIC - Virtual NIC";
        case BDK_TRACE_ENABLE_FDT_OS:       return "Device tree passed to OS";
        case BDK_TRACE_ENABLE_USB_XHCI:     return "USB XHCI";
        case BDK_TRACE_ENABLE_PHY:          return "Ethernet PHY driver";
        case __BDK_TRACE_ENABLE_LAST:       return "ERROR, last not valid";
        /* Default case missing so compile will warn on missing */
    }
    return "TBD";
}

/**
 * Called when a user toggles a tracing level option
 *
 * @param parent
 * @param key
 * @param arg
 */
static void trace_callback(bdk_menu_t *parent, char key, void *arg)
{
    bdk_trace_enable_t e = (bdk_trace_enable_t)arg;
    int trace_level = bdk_config_get_int(BDK_CONFIG_TRACE);
    trace_level ^= 1ull << e;
    bdk_config_set_int(trace_level, BDK_CONFIG_TRACE);
}

/**
 * Display the trace menu
 *
 * @param parent
 * @param key
 * @param arg
 */
static void menu_trace(bdk_menu_t *parent, char key, void *arg)
{
    bdk_menu_t menu;
    bdk_menu_init(&menu, "Toggle Tracing of Units");

    do
    {
        int trace_level = bdk_config_get_int(BDK_CONFIG_TRACE);
        for (bdk_trace_enable_t e = 0; e < __BDK_TRACE_ENABLE_LAST; e++)
        {
            const char *message = get_trace_name(e);
            const char *enabled = "";
            if (trace_level & (1ull<<e))
                enabled = " (Enabled)";
            char s[64];
            snprintf(s, sizeof(s), "%-40s%s", message, enabled);
            char key = (e <= 8) ? '1' + e : 'A' + e - 9;
            bdk_menu_item(&menu, key, s, trace_callback, (void*)e);
        }
        bdk_menu_item(&menu, 'Q', "Return to main menu", NULL, NULL);
        key = bdk_menu_display(&menu);
    } while (key != 'Q');
}

/**
 * Display the chip menu
 *
 * @param parent
 * @param key
 * @param arg
 */
void menu_chip(bdk_menu_t *parent, char key, void *arg)
{
    bdk_menu_t menu;
    const struct menu_add_info info[] =
    {
        { .key = 'D', .name = "Delay for Boot Menu", .config = BDK_CONFIG_BOOT_MENU_TIMEOUT,
            .input = MENU_INPUT_DEC, .units = "s" },
        { .key = 'N', .name = "Support Multi-node", .config = BDK_CONFIG_MULTI_NODE,
            .input = MENU_INPUT_DEC },
        { .key = 'E', .name = "Support PCIe ECAM Enhanced Allocation (EA)", .config = BDK_CONFIG_PCIE_EA,
            .input = MENU_INPUT_DEC },
        { .key = 'O', .name = "Strict PCIe Ordering", .config = BDK_CONFIG_PCIE_ORDERING,
            .input = MENU_INPUT_DEC },
        { .key = 'P', .name = "PCIe Preset Request Vector Override", .config = BDK_CONFIG_PCIE_PRESET_REQUEST_VECTOR,
            .input = MENU_INPUT_HEX, .units = "bitmask" },
        { .key = 'F', .name = "PCIe Endpoint Flash", .config = BDK_CONFIG_PCIE_FLASH,
            .input = MENU_INPUT_STR_LIST, .units = "List" },
        { .key = 'W', .name = "Watchdog Timeout", .config = BDK_CONFIG_WATCHDOG_TIMEOUT,
            .input = MENU_INPUT_DEC, .units = "ms" },
        { .key = 'C', .name = "BDK Allowed Coremask", .config = BDK_CONFIG_COREMASK,
            .input = MENU_INPUT_HEX, .units = "bitmask" },
        { .key = 0, },
    };
    do
    {
        bdk_menu_init(&menu, "Setup - Chip");
        int i = 0;
        while (info[i].key)
        {
            menu_add_config(&menu, &info[i]);
            i++;
        }
        bdk_menu_item(&menu, 'T', "BDK Tracing Level", menu_trace, NULL);
        bdk_menu_item(&menu, 'Q', "Return to main menu", NULL, NULL);
        key = bdk_menu_display(&menu);
    } while (key != 'Q');
}
