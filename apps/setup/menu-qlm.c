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

static bdk_node_t node;

static void do_qlm_mode(bdk_menu_t *parent, char key, void *arg)
{
    int qlm = (long)arg;

    printf("%s\n", bdk_config_get_help(BDK_CONFIG_QLM_MODE));
    const char *new_mode = bdk_readline("QLM Mode: ", NULL, 0);
    if ((new_mode[0] == 0) || (new_mode[0] == 3))
        return;
    printf("%s\n", bdk_config_get_help(BDK_CONFIG_QLM_FREQ));
    const char *new_freq = bdk_readline("QLM Frequency: ", NULL, 0);
    if ((new_freq[0] == 0) || (new_freq[0] == 3))
        return;
    printf("%s\n", bdk_config_get_help(BDK_CONFIG_QLM_CLK));
    const char *new_clk = bdk_readline("QLM Clock: ", NULL, 0);
    if ((new_freq[0] == 0) || (new_freq[0] == 3))
        return;

    bdk_config_set_str(new_mode, BDK_CONFIG_QLM_MODE, node, qlm);
    bdk_config_set_int(atoi(new_freq), BDK_CONFIG_QLM_FREQ, node, qlm);
    bdk_config_set_int(atoi(new_clk), BDK_CONFIG_QLM_CLK, node, qlm);
}

static void do_node(bdk_menu_t *parent, char key, void *arg)
{
    node ^= 1;
}

void menu_qlm(bdk_menu_t *parent, char key, void *arg)
{
    const struct menu_add_info info[] =
    {
        { .key = '1', .name = "Auto configure QLMs based on MCU", .config = BDK_CONFIG_QLM_AUTO_CONFIG,
            .input = MENU_INPUT_DEC },
        { .key = 0, },
    };

    const int multinode = bdk_config_get_int(BDK_CONFIG_MULTI_NODE);
    int num_qlm = bdk_qlm_get_num(node);
    if (num_qlm > 8)
        num_qlm = 8;
    node = bdk_numa_master();

    bdk_menu_t menu;
    do
    {
        bdk_menu_init(&menu, "Setup - Chip");
        if (multinode)
        {
            if (node)
                bdk_menu_item(&menu, '2', "Switch Nodes (1)", do_node, NULL);
            else
                bdk_menu_item(&menu, '2', "Switch Nodes (0)", do_node, NULL);
        }

        int i = 0;
        while (info[i].key)
        {
            menu_add_config(&menu, &info[i]);
            i++;
        }

        int automode = bdk_config_get_int(BDK_CONFIG_QLM_AUTO_CONFIG);
        if (automode == 0)
        {
            for (int qlm = 0; qlm < num_qlm; qlm++)
            {
                int num_lanes = bdk_qlm_get_lanes(node, qlm);
                const char *prefix = (num_lanes == 2) ? "DLM" : "QLM";
                const char *mode = bdk_config_get_str(BDK_CONFIG_QLM_MODE, node, qlm);
                int freq = bdk_config_get_int(BDK_CONFIG_QLM_FREQ, node, qlm);
                int clk = bdk_config_get_int(BDK_CONFIG_QLM_CLK, node, qlm);
                const char *clock;
                switch (clk)
                {
                    case 0:
                        clock = "Common Clock 0";
                        break;
                    case 1:
                        clock = "Common Clock 1";
                        break;
                    default:
                        clock = "External Reference";
                        break;
                }
                char str[80];
                snprintf(str, sizeof(str), "N%d.%s%d - %s, %d.%03d Gbaud, %s",
                    node, prefix, qlm, mode, freq / 1000, freq % 1000, clock);
                bdk_menu_item(&menu, 'A' + qlm, str, do_qlm_mode, (void*)(long)qlm);
            }
        }
        bdk_menu_item(&menu, 'Q', "Return to main menu", NULL, NULL);
        key = bdk_menu_display(&menu);
    } while (key != 'Q');
}
