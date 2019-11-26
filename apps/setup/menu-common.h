/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
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

