#ifndef __READLINE_H__
#define __READLINE_H__
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
 * Functions for reading input.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup stdio
 * @{
 */

/**
 * Format of a tab completion entry. Pass an array of these to bdk_readline()
 * to get tab completion of words. Once the first word is completed from "str",
 * the next is pointer is used to find the completions of the next word. This
 * can be NULL if there are no completions available. The list of completions
 * ends with the first item with str==NULL.
 */
typedef struct bdk_readline_tab
{
    const char *str;
    const struct bdk_readline_tab *next;
} bdk_readline_tab_t;

/**
 * Prompt for a line from the user and return it. Full line
 * editing and history are supported.
 *
 * @param prompt     Prompt to show
 * @param tab        Information about tab completion
 * @param timeout_us Return NULL if a line isn't entered in this amount of time. Next
 *                   call will continue the partial line.
 *
 * @return Line that was read. Return is a persistent pointer into the
 *         command history and should not be freed.
 */
extern const char *bdk_readline(const char *prompt, const bdk_readline_tab_t *tab, int timeout_us);

/**
 * Get a single input character from stdin.
 *
 * @param timeout_us How long to wait for a key
 *
 * @return The key, or -1 on timeout
 */
extern int bdk_readline_getkey(uint64_t timeout_us);

/** @} */
#endif /* __READLINE_H__ */

