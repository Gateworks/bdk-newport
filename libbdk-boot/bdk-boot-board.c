/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

/**
 * Lookup callback structure for this board
 *
 * @return Structure, or NULL if not found
 */
static const bdk_boot_callbacks_t* lookup_board(void)
{
    extern const bdk_boot_callbacks_t * const board_callbacks_start[];
    extern const bdk_boot_callbacks_t * const board_callbacks_end[];
    const char *board = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
    const bdk_boot_callbacks_t * const *ptr = board_callbacks_start;
    while (ptr < board_callbacks_end)
    {
        if (strcasecmp((*ptr)->board_name, board) == 0)
            return *ptr;
        ptr++;
    }
    return NULL;
}

/**
 * Called by the initialization phase to call the board specific callbacks
 */
void bdk_boot_board_init_early(void)
{
    const bdk_boot_callbacks_t *callbacks = lookup_board();
    if (callbacks && callbacks->init_early)
    {
        BDK_TRACE(INIT, "Calling init_early() for %s\n", callbacks->board_name);
        callbacks->init_early();
    }
}

/**
 * Called by the initialization phase to call the board specific callbacks
 */
void bdk_boot_board_init_dram(void)
{
    const bdk_boot_callbacks_t *callbacks = lookup_board();
    if (callbacks && callbacks->init_dram)
    {
        BDK_TRACE(INIT, "Calling init_dram() for %s\n", callbacks->board_name);
        callbacks->init_dram();
    }
}

/**
 * Called by the initialization phase to call the board specific callbacks
 */
void bdk_boot_board_init_complete(void)
{
    const bdk_boot_callbacks_t *callbacks = lookup_board();
    if (callbacks && callbacks->init_complete)
    {
        BDK_TRACE(INIT, "Calling init_complete() for %s\n", callbacks->board_name);
        callbacks->init_complete();
    }
}

