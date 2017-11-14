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

void menu_power(bdk_menu_t *parent, char key, void *arg)
{
    bdk_menu_t menu;
    const struct menu_add_info info[] =
    {
        { .key = 'T', .name = "Thermal Trip Temperature", .config = BDK_CONFIG_VRM_TEMP_TRIP,
            .input = MENU_INPUT_DEC, .units = "C", .param = MENU_PARAM_NODE },
        { .key = 'H', .name = "Maximum Operating Temperature", .config = BDK_CONFIG_VRM_TEMP_HIGH,
            .input = MENU_INPUT_DEC, .units = "C", .param = MENU_PARAM_NODE },
        { .key = 'L', .name = "Normal Operating Temperature", .config = BDK_CONFIG_VRM_TEMP_LOW,
            .input = MENU_INPUT_DEC, .units = "C", .param = MENU_PARAM_NODE },
        { .key = 'M', .name = "Maximum Operating Throttle", .config = BDK_CONFIG_VRM_THROTTLE_THERM,
            .input = MENU_INPUT_DEC, .units = "%", .param = MENU_PARAM_NODE },
        { .key = 'N', .name = "Normal Operating Throttle", .config = BDK_CONFIG_VRM_THROTTLE_NORMAL,
            .input = MENU_INPUT_DEC, .units = "%", .param = MENU_PARAM_NODE },
        { .key = 0, },
    };
    do
    {
        bdk_menu_init(&menu, "Setup - Power");
        int i = 0;
        while (info[i].key)
        {
            menu_add_config(&menu, &info[i]);
            i++;
        }
        bdk_menu_item(&menu, 'Q', "Return to main menu", NULL, NULL);
        key = bdk_menu_display(&menu);
    } while (key != 'Q');
}
