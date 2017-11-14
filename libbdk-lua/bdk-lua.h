#ifndef __BDK_LUA_H__
#define __BDK_LUA_H__
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

#include "../liblua/lua.h"
#include "../liblua/lualib.h"
#include "../liblua/lauxlib.h"

/**
 * @file
 *
 * Master include file for Lua support. Use bdk.h instead of
 * including this file directly.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @defgroup lua Lua support routines
 * @{
 */

/**
 * Create a new Lua interpreter and execute it in another thread.
 * The Lua instance starts in a new thread so the stack size can
 * be adjusted. Lua requires more stacj space than most BDK
 * threads. This means this routine returns immediately and the
 * Lua instance continues. It is expected that this function
 * will be called as the last line of main().
 *
 *     int main(void)
 *     {
 *         return bdk_lua_start();
 *     }
 *
 * @return Zero for use as return value for main()
 */
extern int bdk_lua_start(void);

/**
 * This function is called by bdk_lua_start() after the Lua state
 * is initialized but before Lua starts executing /rom/init/lua.
 * It is a weak symbol so that applications not needing it don't
 * have to define the function. The normal use for it is to add
 * new functions and modules to the Lua state. customizing it for
 * this specific application.
 *
 * @param L      Lua state
 */
extern void bdk_lua_callback(lua_State* L) __attribute__((weak));

/**
 * This function should be called inside bdk_lua_callback() to add
 * custom functions to the cavium.c table. This allows
 * applications to add functions without modifying bdk-function.
 *
 * @param L      Lua state
 * @param name   Name of the function to use in cavium.c.NAME
 * @param func   Function to register. The function can take a maximum of eight
 *               arguments where each argument must be a type compatible with a
 *               int64_t or a constant string pointer. The return value of the
 *               function can be void or a type compatible with a int64_t.
 */
extern void bdk_lua_register_cfunc(lua_State* L, const char *name, void *func);

/** @} */
#endif
