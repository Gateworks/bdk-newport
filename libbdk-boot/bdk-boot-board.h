/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Boot services hook for board specific callbacks
 *
 * @addtogroup boot
 * @{
 */

/**
 * This structure defines callback for board specific functionality
 * during boot. The callbacks are found by comparing the current device
 * tree board name with the name in this structure. If a case
 * insensitive match happens, the associated callback is called. Any
 * callback may be NULL, which means no call is made. Instances of this
 * structure must be registered with the macro
 * BDK_REGISTER_BOOT_CALLBACK.
 */
typedef struct
{
    const char *board_name;
    void (*init_early)(void);       /* Called very early by init.bin */
    void (*init_dram)(void);        /* Called after DRAM is setup */
    void (*init_complete)(void);    /* Called after init.bin is complete, before next stage */
} bdk_boot_callbacks_t;

/**
 * Called by the initialization phase to call the board specific callbacks
 */
extern void bdk_boot_board_init_early(void);

/**
 * Called by the initialization phase to call the board specific callbacks
 */
extern void bdk_boot_board_init_dram(void);

/**
 * Called by the initialization phase to call the board specific callbacks
 */
extern void bdk_boot_board_init_complete(void);

/**
 * Called to register a callback structure with the system
 */
#define BDK_REGISTER_BOOT_CALLBACK(callbacks_t)                         \
    const bdk_boot_callbacks_t *__bdk_board_callbacks##callbacks_t      \
    __attribute__((used, section("board_callbacks"))) = &callbacks_t

/** @} */
