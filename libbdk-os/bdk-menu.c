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
#include <ctype.h>

/**
 * Initialize a menu before adding items
 *
 * @param menu   Menu to init
 * @param title  Title for the menu
 */
void bdk_menu_init(bdk_menu_t *menu, const char *title)
{
    memset(menu, 0, sizeof(*menu));
    strncpy(menu->title, title, sizeof(menu->title));
    menu->title[sizeof(menu->title) - 1] = 0;
}

/**
 * Add an item to the menu. Note that if the same key is used, it replaces the
 * existing item for that key
 *
 * @param menu     Menu to update
 * @param key      Key pressed by the user to select this item
 * @param name     Display string for this item
 * @param callback Function to call when item is selected
 * @param arg      Argument for callback
 */
void bdk_menu_item(bdk_menu_t *menu, char key, const char *name, bdk_menu_callback_t callback, void *arg)
{
    const int MAX_MENU_ITEMS = sizeof(menu->item) / sizeof(menu->item[0]);
    for (int i = 0; i < MAX_MENU_ITEMS; i++)
    {
        if ((menu->item[i].key == key) || (menu->item[i].key == 0))
        {
            menu->item[i].key = toupper((int)key);
            strncpy(menu->item[i].name, name, sizeof(menu->item[i].name));
            menu->item[i].name[sizeof(menu->item[i].name) - 1] = 0;
            menu->item[i].callback = callback;
            menu->item[i].arg = arg;
            return;
        }
    }
    bdk_fatal("bdk-menu: Attempted to create menu with more that %d items\n", MAX_MENU_ITEMS);
}

/**
 * Display the menu to the user and wait for intput. On item selection the callback
 * is called, then the key is returned here
 *
 * @param menu   Menu to display
 *
 * @return Key pressed by the user. If supplied, the menu item callback is called before
 *         return
 */
int bdk_menu_display(bdk_menu_t *menu)
{
    const int MAX_MENU_ITEMS = sizeof(menu->item) / sizeof(menu->item[0]);

    while (1)
    {
        printf("\n");
        printf("=================================\n");
        printf("%s\n", menu->title);
        printf("=================================\n");
        for (int i = 0; i < MAX_MENU_ITEMS; i++)
        {
            if (!menu->item[i].key)
                break;
            printf("%c) %s\n", menu->item[i].key, menu->item[i].name);
        }
        printf("\n");
        printf("Choice: ");
        int key = toupper(bdk_readline_getkey(-1));
        printf("%c\n\n", key);

        for (int i = 0; i < MAX_MENU_ITEMS; i++)
        {
            if (menu->item[i].key == key)
            {
                if (menu->item[i].callback)
                    menu->item[i].callback(menu, key, menu->item[i].arg);
                return menu->item[i].key;
            }
        }
        printf("Invalid choice\n");
    }
}
