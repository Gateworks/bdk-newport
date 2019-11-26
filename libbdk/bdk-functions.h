/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * This maps of all BDK functions by name. This can be used
 * to lookup functions for non C code, like Lua.
 *
 * <hr>$Revision: 49448 $<hr>
 */

typedef struct
{
    const char *name;
    void *func;
} bdk_functions_t;

/**
 * This table is a map of all BDK functions by name. This can be used
 * to lookup functions for non C code, like Lua.
 */
extern const bdk_functions_t bdk_functions[];

