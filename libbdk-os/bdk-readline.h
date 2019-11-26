#ifndef __READLINE_H__
#define __READLINE_H__
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
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

