/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "menu-common.h"

void dram_speed(bdk_menu_t *parent, char key, void *arg)
{
    char prompt[64];
    printf("%s\n", bdk_config_get_help(BDK_CONFIG_DDR_SPEED));

    /* Prompt for int value */
    int64_t v = bdk_config_get_int(BDK_CONFIG_DDR_SPEED, bdk_numa_local());
    if (v)
        snprintf(prompt, sizeof(prompt), "DRAM Speed [%ld MT/s]: ", v);
    else
        snprintf(prompt, sizeof(prompt), "DRAM Speed [auto]: ");
    const char *result = bdk_readline(prompt, NULL, 0);
    if (sscanf(result, "%li", &v) == 1)
    {
        for (bdk_node_t node = BDK_NODE_0; node < BDK_NUMA_MAX_NODES; node++)
            bdk_config_set_int(v, BDK_CONFIG_DDR_SPEED, node);
    }
}

void dram_alt_refclk(bdk_menu_t *parent, char key, void *arg)
{
    char prompt[64];
    printf("%s\n", bdk_config_get_help(BDK_CONFIG_DDR_ALT_REFCLK));

    /* Prompt for int value */
    int64_t v = bdk_config_get_int(BDK_CONFIG_DDR_ALT_REFCLK, bdk_numa_local());
    if (v)
        snprintf(prompt, sizeof(prompt), "DRAM Alt Refclk [%ld MHz]: ", v);
    else
        snprintf(prompt, sizeof(prompt), "DRAM Alt Refclk [factory default]: ");
    const char *result = bdk_readline(prompt, NULL, 0);
    if (sscanf(result, "%li", &v) == 1)
    {
        for (bdk_node_t node = BDK_NODE_0; node < BDK_NUMA_MAX_NODES; node++)
            bdk_config_set_int(v, BDK_CONFIG_DDR_ALT_REFCLK, node);
    }
}

void menu_dram(bdk_menu_t *parent, char key, void *arg)
{
    bdk_menu_t menu;
    const struct menu_add_info info[] =
    {
        { .key = 'V', .name = "DRAM Verbose level", .config = BDK_CONFIG_DRAM_VERBOSE,
            .input = MENU_INPUT_DEC },
        { .key = 'T', .name = "Test DRAM on boot", .config = BDK_CONFIG_DRAM_BOOT_TEST,
            .input = MENU_INPUT_DEC },
        { .key = 0, },
    };
    do
    {
        bdk_menu_init(&menu, "Setup - DRAM");
        int i = 0;
        while (info[i].key)
        {
            menu_add_config(&menu, &info[i]);
            i++;
        }
        //bdk_menu_item(&menu, 'N', "Number of LMC Controllers", NULL, NULL);
        //bdk_menu_item(&menu, 'D', "DRAM Type", NULL, NULL);
        //bdk_menu_item(&menu, 'A', "DIMM SPD Addresses", NULL, NULL);
        bdk_menu_item(&menu, 'S', "DRAM Speed", dram_speed, NULL);
        bdk_menu_item(&menu, 'R', "DRAM Alt Refclk", dram_alt_refclk, NULL);
        bdk_menu_item(&menu, 'Q', "Return to main menu", NULL, NULL);
        key = bdk_menu_display(&menu);
    } while (key != 'Q');
}
