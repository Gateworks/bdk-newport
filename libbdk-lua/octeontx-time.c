/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
// Module for tracjing time from Lua

/**
 * Lua wrapper for time
 *
 * @param L
 *
 * @return
 */
static int time_us(lua_State* L)
{
    uint64_t rate = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
    uint64_t count = bdk_clock_get_count(BDK_CLOCK_TIME);
    count /= rate / 1000000;
    lua_pushinteger(L, count);
    return 1;
}

/**
 * Called to register the module
 *
 * @param L
 *
 * @return
 */
void register_octeontx_time(lua_State* L)
{
    lua_pushcfunction(L, time_us);
    lua_setfield(L, -2, "time_us");
}

