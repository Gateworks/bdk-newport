/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
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
        case BDK_TRACE_ENABLE_DRAM:         return "DRAM Initialization";
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
        case BDK_TRACE_ENABLE_CCS_DECODE:   return "CCS address decode";
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
    const int MENU_SIZE = 10;
    struct menu_add_info info[MENU_SIZE];
    int loc = 0;
    memset(info, 0, sizeof(info));

    info[loc].key = 'D';
    info[loc].name = "Delay for Boot Menu";
    info[loc].config = BDK_CONFIG_BOOT_MENU_TIMEOUT;
    info[loc].input = MENU_INPUT_DEC;
    info[loc].units = "s";
    loc++;

    info[loc].key = 'O';
    info[loc].name = "Strict PCIe Ordering";
    info[loc].config = BDK_CONFIG_PCIE_ORDERING;
    info[loc].input = MENU_INPUT_DEC;
    loc++;

    info[loc].key = 'P';
    info[loc].name = "PCIe Preset Request Vector Override";
    info[loc].config = BDK_CONFIG_PCIE_PRESET_REQUEST_VECTOR;
    info[loc].input = MENU_INPUT_HEX;
    info[loc].units = "bitmask";
    loc++;

    if (bdk_is_model(OCTEONTX_CN83XX))
    {
        info[loc].key = 'F';
        info[loc].name = "PCIe Endpoint Flash";
        info[loc].config = BDK_CONFIG_PCIE_FLASH;
        info[loc].input = MENU_INPUT_STR_LIST;
        info[loc].units = "List";
        loc++;
    }

    info[loc].key = 'W';
    info[loc].name = "Watchdog Timeout";
    info[loc].config = BDK_CONFIG_WATCHDOG_TIMEOUT;
    info[loc].input = MENU_INPUT_DEC;
    info[loc].units = "ms";
    loc++;

    info[loc].key = 'C';
    info[loc].name = "BDK Allowed Coremask";
    info[loc].config = BDK_CONFIG_COREMASK;
    info[loc].input = MENU_INPUT_HEX;
    info[loc].units = "bitmask";

    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        /* Errata 36412 Tx Tap Override selection       */
        /* Select this value from 0 to 10               */
        /* This will be the value used in selecting     */
        if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0))
                {
                /* This is for the RC port */
                info[loc].key = 'X';
                info[loc].name = "TXPRESET Vector For Errata 36412";
                info[loc].config = BDK_CONFIG_PCIE_TX_PRESET_OVERRIDE_VECTOR;
                info[loc].input = MENU_INPUT_HEX;
                info[loc].units = "RC-Preset";
                loc++;

                /* This is for the endpoint */
                info[loc].key    = 'Y';
                info[loc].name   = "ENDPOINT Mode TXPRESET Vector For Errata 36412";
                info[loc].config = BDK_CONFIG_PCIE_ENDPOINT_TX_PRESET_OVERRIDE;
                info[loc].input  = MENU_INPUT_DEC;
                info[loc].units  = "EP-Preset";
                loc++;
                }
    }

    info[loc].key = 0;
    loc++;
    if (loc > MENU_SIZE)
        bdk_fatal("Increase chip menu size\n");

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
