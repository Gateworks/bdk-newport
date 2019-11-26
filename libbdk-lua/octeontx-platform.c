/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
// Module for determining run platform

/**
 * Lua wrapper for bdk_is_platform
 *
 * @param L
 *
 * @return
 */
static int is_platform(lua_State* L)
{
    uint32_t m = luaL_checkinteger(L, 1);
    lua_pushboolean(L, bdk_is_platform(m));
    return 1;
}

/**
 * Called to register the platform module
 *
 * @param L
 *
 * @return
 */
void register_octeontx_platform(lua_State* L)
{
    lua_pushcfunction(L, is_platform);
    lua_setfield(L, -2, "is_platform");

    /* Add constants for the different platform that can be used with
        octeontx.is_platform() */
    lua_pushnumber(L, BDK_PLATFORM_HW);
    lua_setfield(L, -2, "PLATFORM_HW");
    lua_pushnumber(L, BDK_PLATFORM_EMULATOR);
    lua_setfield(L, -2, "PLATFORM_EMULATOR");
    lua_pushnumber(L, BDK_PLATFORM_RTL);
    lua_setfield(L, -2, "PLATFORM_RTL");
    lua_pushnumber(L, BDK_PLATFORM_ASIM);
    lua_setfield(L, -2, "PLATFORM_ASIM");
}

