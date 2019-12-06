/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <libfdt.h>
#include <gsc.h>
#include "menu-common.h"

static void write_board_fdt(bdk_menu_t *parent, char key, void *arg)
{
#if 0 // NEWPORT
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
    int node = fdt_add_subnode(fdt, 0, BDK_DEVICE_TREE_ROOT);
    if (node < 0)
    {
        bdk_error("Unable to create %s node in FDT\n", BDK_DEVICE_TREE_ROOT);
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
#else
	if (gsc_eeprom_update(bdk_numa_master()))
		bdk_error("Failed to write to GSC EEPROM");
	else
		printf("Board information written to GSC EEPROM\n");
#endif
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
