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
typedef enum
{
    MENU_PARAM_NONE, /* The config item takes no parameters */
    MENU_PARAM_NODE, /* The config item takes one parameter, the node */
} menu_param_type_t;

typedef enum
{
    MENU_INPUT_STR = 0, /* User input is a string */
    MENU_INPUT_DEC,     /* User input is a decimal number */
    MENU_INPUT_HEX,     /* User input is a hexadecimal number */
    MENU_INPUT_STR_LIST,/* User input is a list of strings */
} menu_input_type_t;

/**
 * Passed to menu_add_config() to add simple configuration items to menus. This
 * structure must not go out of scope until the menu is closed.
 */
struct menu_add_info
{
    char key;           /* Key user should press */
    const char *name;   /* Menu item name */
    const char *units;  /* Menu item units, or NULL if N/A */
    bdk_config_t config;/* Config entry matching this item */
    menu_input_type_t input; /* Type of user input required */
    menu_param_type_t param; /* Type of parameters the config item takes */
};

/**
 * It is common to have a menu entry change a single configuration parameter. This
 * function makes it convientent to add these entries.
 *
 * @param menu   Menu to add the item onto
 * @param info   Information about the configuration item being added
 */
void menu_add_config(bdk_menu_t *menu, const struct menu_add_info *info);

