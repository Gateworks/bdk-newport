#ifndef __BDK_MENU_H__
#define __BDK_MENU_H__
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

