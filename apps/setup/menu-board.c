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
#include <libfdt.h>
#include "menu-common.h"

static void write_board_fdt(bdk_menu_t *parent, char key, void *arg)
{
    const int FDT_SIZE = 0x10000;
    FILE *outf = NULL;
    void *fdt = calloc(1, FDT_SIZE);
    if (!fdt)
    {
        bdk_error("Unable to allocate memory for FDT\n");
        goto cleanup;
    }
    if (fdt_create_empty_tree(fdt, FDT_SIZE) < 0)
    {
        bdk_error("Unable to create FDT for board\n");
        goto cleanup;
    }
    int node = fdt_add_subnode(fdt, 0, "cavium,bdk");
    if (node < 0)
    {
        bdk_error("Unable to create cavium,bdk node in FDT\n");
        goto cleanup;
    }

    const char *model = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
    const char *revision = bdk_config_get_str(BDK_CONFIG_BOARD_REVISION);
    const char *serial = bdk_config_get_str(BDK_CONFIG_BOARD_SERIAL);
    int64_t mac = bdk_config_get_int(BDK_CONFIG_MAC_ADDRESS);
    int64_t num_mac = bdk_config_get_int(BDK_CONFIG_MAC_ADDRESS_NUM);
    char str[20];

    int status = fdt_setprop_string(fdt, node, "BOARD-MODEL", model);
    if (status < 0)
    {
        bdk_error("FDT error %d: %s\n", status, fdt_strerror(status));
        goto cleanup;
    }

    status = fdt_setprop_string(fdt, node, "BOARD-REVISION", revision);
    if (status < 0)
    {
        bdk_error("FDT error %d: %s\n", status, fdt_strerror(status));
        goto cleanup;
    }

    status = fdt_setprop_string(fdt, node, "BOARD-SERIAL", serial);
    if (status < 0)
    {
        bdk_error("FDT error %d: %s\n", status, fdt_strerror(status));
        goto cleanup;
    }

    snprintf(str, sizeof(str), "0x%lx", mac);
    status = fdt_setprop_string(fdt, node, "BOARD-MAC-ADDRESS", str);
    if (status < 0)
    {
        bdk_error("FDT error %d: %s\n", status, fdt_strerror(status));
        goto cleanup;
    }

    snprintf(str, sizeof(str), "%ld", num_mac);
    status = fdt_setprop_string(fdt, node, "BOARD-MAC-ADDRESS-NUM", str);
    if (status < 0)
    {
        bdk_error("FDT error %d: %s\n", status, fdt_strerror(status));
        goto cleanup;
    }
    status = fdt_pack(fdt);
    if (status < 0)
    {
        bdk_error("FDT error %d: %s\n", status, fdt_strerror(status));
        goto cleanup;
    }

    /* Calculate a CRC32 of the FDT */
    int fdt_size = fdt_totalsize(fdt);
    uint32_t crc32 = bdk_crc32(fdt, fdt_size, 0);

    outf = fopen("/boot", "wb");
    if (!outf)
    {
        bdk_error("Failed to open flash");
        goto cleanup;
    }
    fseek(outf, BDK_CONFIG_MANUFACTURING_ADDRESS, SEEK_SET);
    if (fwrite(fdt, fdt_size, 1, outf) != 1)
    {
        bdk_error("Failed to write flash");
        goto cleanup;
    }
    /* Save the CRC32 in the same endianness as the FDT */
    crc32 = cpu_to_fdt32(crc32);
    if (fwrite(&crc32, sizeof(crc32), 1, outf) != 1)
    {
        bdk_error("Failed to write flash");
        goto cleanup;
    }
    printf("Board information written to flash\n");
cleanup:
    if (outf)
        fclose(outf);
    if (fdt)
        free(fdt);
}

void menu_board(bdk_menu_t *parent, char key, void *arg)
{
    bdk_menu_t menu;
    const struct menu_add_info info[] =
    {
        { .key = 'B', .name = "Board Model Number", .config = BDK_CONFIG_BOARD_MODEL },
        { .key = 'R', .name = "Board Revision", .config = BDK_CONFIG_BOARD_REVISION },
        { .key = 'S', .name = "Serial Number", .config = BDK_CONFIG_BOARD_SERIAL },
        { .key = 'M', .name = "Base MAC Address", .config = BDK_CONFIG_MAC_ADDRESS, .input = MENU_INPUT_HEX },
        { .key = 'N', .name = "Number of MAC Addresses", .config = BDK_CONFIG_MAC_ADDRESS_NUM, .input = MENU_INPUT_DEC },
        { .key = 0, },
    };

    printf("Board manufacturing data is stored in a different location in\n"
        "flash than other configuration items, so the settings in this\n"
        "menu persist across software upgrades. Once set, these should\n"
        "normally not be changed.\n");

    do
    {
        bdk_menu_init(&menu, "Setup - Board");
        int i = 0;
        while (info[i].key)
        {
            menu_add_config(&menu, &info[i]);
            i++;
        }
        bdk_menu_item(&menu, 'W', "Save Board Manufacturing Data to Flash", write_board_fdt, NULL);
        bdk_menu_item(&menu, 'Q', "Return to main menu", NULL, NULL);
        key = bdk_menu_display(&menu);
    } while (key != 'Q');
}
