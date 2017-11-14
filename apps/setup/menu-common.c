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

/**
 * Callback used by menu_add_config() to edit a simple
 * configuration setting. It prompts for a new value, replacing
 * the existing value if the user enters one. Leaving the prompt
 * blanks causes no changes.
 *
 * @param parent Menu causing the prompt
 * @param key    Key pressed in menu
 * @param arg    struct menu_add_info for this entry
 */
static void do_prompt(bdk_menu_t *parent, char key, void *arg)
{
    char prompt[64];
    char units[12];
    const struct menu_add_info *info = arg;

    if (info->units)
        snprintf(units, sizeof(units), " %s", info->units);
    else
        units[0] = 0;

    printf("%s\n", bdk_config_get_help(info->config));

    switch (info->input)
    {
        case MENU_INPUT_STR:
        {
            /* Prompt for string value */
            const char *v = NULL;
            switch (info->param)
            {
                case MENU_PARAM_NONE: /* The config item takes no parameters */
                    v = bdk_config_get_str(info->config);
                    break;
                case MENU_PARAM_NODE: /* The config item takes one parameter, the node */
                    v = bdk_config_get_str(info->config, bdk_numa_local());
                    break;
            }
            if (v)
                snprintf(prompt, sizeof(prompt), "%s [%s%s]: ", info->name, v, units);
            else
                snprintf(prompt, sizeof(prompt), "%s: ", info->name);
            const char *result = bdk_readline(prompt, NULL, 0);
            if (result[0] && (result[0] != 3))
            {
                switch (info->param)
                {
                    case MENU_PARAM_NONE: /* The config item takes no parameters */
                        bdk_config_set_str(result, info->config);
                        break;
                    case MENU_PARAM_NODE: /* The config item takes one parameter, the node */
                        for (int node = 0; node < 2; node++)
                            bdk_config_set_str(result, info->config, node);
                        break;
                }
            }
            break;
        }
        case MENU_INPUT_DEC:
        case MENU_INPUT_HEX:
        {
            /* Prompt for int value */
            int64_t v = 0;
            switch (info->param)
            {
                case MENU_PARAM_NONE: /* The config item takes no parameters */
                    v = bdk_config_get_int(info->config);
                    break;
                case MENU_PARAM_NODE: /* The config item takes one parameter, the node */
                    v = bdk_config_get_int(info->config, bdk_numa_local());
                    break;
            }
            if (info->input == MENU_INPUT_DEC)
                snprintf(prompt, sizeof(prompt), "%s [%ld%s]: ", info->name, v, units);
            else
                snprintf(prompt, sizeof(prompt), "%s [0x%012lx%s]: ", info->name, v, units);
            const char *result = bdk_readline(prompt, NULL, 0);
            if (sscanf(result, "%li", &v) == 1)
            {
                switch (info->param)
                {
                    case MENU_PARAM_NONE: /* The config item takes no parameters */
                        bdk_config_set_int_no_param(v, info->config);
                        break;
                    case MENU_PARAM_NODE: /* The config item takes one parameter, the node */
                        for (int node = 0; node < 2; node++)
                            bdk_config_set_int(v, info->config, node);
                        break;
                }
            }
            break;
        }
        case MENU_INPUT_STR_LIST:
        {
            /* Show the current value */
            const char *old_blob = NULL;
            int old_blob_size = 0;
            switch (info->param)
            {
                case MENU_PARAM_NONE: /* The config item takes no parameters */
                    old_blob = bdk_config_get_blob(&old_blob_size, info->config);
                    break;
                case MENU_PARAM_NODE: /* The config item takes one parameter, the node */
                    old_blob = bdk_config_get_blob(&old_blob_size, info->config, bdk_numa_local());
                    break;
            }
            if (old_blob == NULL)
                old_blob_size = 0;
            const char *done = old_blob + old_blob_size;
            const char *str = old_blob;
            printf("Current value:\n");
            while (str < done)
            {
                printf("%s\n", str);
                /* Move to the next string */
                str += strlen(str) + 1;
            }
            /* Prompt for string list */
            printf("\n");
            printf("Enter multiple lines for new value. Input ends with a blank line\n");
            char blob[256];
            size_t blob_size = 0;
            int line_no = 0;
            while (1)
            {
                line_no++;
                snprintf(prompt, sizeof(prompt), "%s(line %d): ", info->name, line_no);
                const char *r = bdk_readline(prompt, NULL, 0);
                if (r[0] == 3)
                {
                    bdk_error("Input aborted, no changes made\n");
                    return;
                }
                /* Stop input list at blank line */
                if (r[0] == 0)
                    break;
                int rlen = strlen(r) + 1; /* +1 to include terminator */
                if (blob_size + rlen <= sizeof(blob))
                {
                    strcpy(blob + blob_size, r);
                    blob_size += rlen;
                }
                else
                {
                    bdk_error("Input list too long, no changes made\n");
                    return;
                }
            }
            switch (info->param)
            {
                case MENU_PARAM_NONE: /* The config item takes no parameters */
                    bdk_config_set_blob_no_param(blob_size, blob, info->config);
                    break;
                case MENU_PARAM_NODE: /* The config item takes one parameter, the node */
                    for (int node = 0; node < 2; node++)
                        bdk_config_set_blob(blob_size, blob, info->config, node);
                    break;
            }
            break;
        }
    }
}

/**
 * It is common to have a menu entry change a single configuration parameter. This
 * function makes it convientent to add these entries.
 *
 * @param menu   Menu to add the item onto
 * @param info   Information about the configuration item being added
 */
void menu_add_config(bdk_menu_t *menu, const struct menu_add_info *info)
{
    char str[64];
    char units[12];

    if (info->units)
        snprintf(units, sizeof(units), " %s", info->units);
    else
        units[0] = 0;

    switch (info->input)
    {
        case MENU_INPUT_STR:
        {
            const char *v = NULL;
            switch (info->param)
            {
                case MENU_PARAM_NONE: /* The config item takes no parameters */
                    v = bdk_config_get_str(info->config);
                    break;
                case MENU_PARAM_NODE: /* The config item takes one parameter, the node */
                    v = bdk_config_get_str(info->config, bdk_numa_local());
                    break;
            }
            snprintf(str, sizeof(str), "%s (%s%s)", info->name, v, units);
            break;
        }
        case MENU_INPUT_DEC:
        case MENU_INPUT_HEX:
        {
            int64_t v = 0;
            switch (info->param)
            {
                case MENU_PARAM_NONE: /* The config item takes no parameters */
                    v = bdk_config_get_int(info->config);
                    break;
                case MENU_PARAM_NODE: /* The config item takes one parameter, the node */
                    v = bdk_config_get_int(info->config, bdk_numa_local());
                    break;
            }
            if (info->input == MENU_INPUT_DEC)
                snprintf(str, sizeof(str), "%s (%ld%s)", info->name, v, units);
            else
                snprintf(str, sizeof(str), "%s (0x%012lx%s)", info->name, v, units);
            break;
        }
        case MENU_INPUT_STR_LIST:
        {
            snprintf(str, sizeof(str), "%s (%s)", info->name, units);
            break;
        }
    }
    bdk_menu_item(menu, info->key, str, do_prompt, (void*)info);
}

