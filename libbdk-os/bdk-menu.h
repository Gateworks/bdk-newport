#ifndef __BDK_MENU_H__
#define __BDK_MENU_H__
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for dsiplaying a menu to the user.
 *
 * @addtogroup stdio
 * @{
 */

struct bdk_menu_s;
/**
 * Function call prototype for meny callbacks
 */
typedef void (*bdk_menu_callback_t)(struct bdk_menu_s *menu, char key, void *arg);

/**
 * Definition of a menu
 */
typedef struct bdk_menu_s
{
    char title[32];         /* Menu will truncate titles that are too long */
    struct
    {
        char key;           /* Key to press for the user */
        char name[64];      /* Menu will truncate names that are too long */
        bdk_menu_callback_t callback; /* Optional callback */
        void *arg;          /* Optional argument to callback */
    } item[32];             /* Menus have a fixed max size */
} bdk_menu_t;

/**
 * Initialize a menu before adding items
 *
 * @param menu   Menu to init
 * @param title  Title for the menu
 */
void bdk_menu_init(bdk_menu_t *menu, const char *title);

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
void bdk_menu_item(bdk_menu_t *menu, char key, const char *name, bdk_menu_callback_t callback, void *arg);

/**
 * Display the menu to the user and wait for intput. On item selection the callback
 * is called, then the key is returned here
 *
 * @param menu   Menu to display
 *
 * @return Key pressed by the user. If supplied, the menu item callback is called before
 *         return
 */
int bdk_menu_display(bdk_menu_t *menu);

/** @} */
#endif /* __BDK_MENU_H__ */

