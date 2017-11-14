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
