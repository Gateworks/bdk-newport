/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
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
