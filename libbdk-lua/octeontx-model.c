/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
// Module for determining chips models

/**
 * Lua wrapper for bdk_is_model
 *
 * @param L
 *
 * @return
 */
static int is_model(lua_State* L)
{
    uint32_t m = luaL_checkinteger(L, 1);
    lua_pushboolean(L, bdk_is_model(m));
    return 1;
}

/**
 * Lua wrapper for bdk_is_altpkg
 *
 * @param L
 *
 * @return
 */
static int is_altpkg(lua_State* L)
{
    uint32_t m = luaL_checkinteger(L, 1);
    lua_pushboolean(L, bdk_is_altpkg(m));
    return 1;
}

/**
 * Called to register the chip model module
 *
 * @param L
 *
 * @return
 */
void register_octeontx_model(lua_State* L)
{
    lua_pushcfunction(L, is_model);
    lua_setfield(L, -2, "is_model");
    lua_pushcfunction(L, is_altpkg);
    lua_setfield(L, -2, "is_altpkg");

    /* Add constants for the different models that can be used with
        octeontx.is_model() */
    lua_pushnumber(L, OCTEONTX_CN8XXX);
    lua_setfield(L, -2, "CN8XXX");
    lua_pushnumber(L, OCTEONTX_CN83XX);
    lua_setfield(L, -2, "CN83XX");
    lua_pushnumber(L, OCTEONTX_CN83XX_PASS1_X);
    lua_setfield(L, -2, "CN83XXP1");
    lua_pushnumber(L, OCTEONTX_CN81XX);
    lua_setfield(L, -2, "CN81XX");
    lua_pushnumber(L, OCTEONTX_CN81XX_PASS1_X);
    lua_setfield(L, -2, "CN81XXP1");

    lua_pushnumber(L, OCTEONTX_CN9XXX);
    lua_setfield(L, -2, "CN9XXX");
    lua_pushnumber(L, OCTEONTX_CN96XX);
    lua_setfield(L, -2, "CN96XX");
    lua_pushnumber(L, OCTEONTX_CN96XX_PASS1_X);
    lua_setfield(L, -2, "CN96XXP1");
    lua_pushnumber(L, OCTEONTX_CN96XX_PASS3_X);
    lua_setfield(L, -2, "CN96XXP3");
    lua_pushnumber(L, OCTEONTX_CNF95XX);
    lua_setfield(L, -2, "CNF95XX");
    lua_pushnumber(L, OCTEONTX_CNF95XX_PASS1_X);
    lua_setfield(L, -2, "CNF95XXP1");

    /* Constants for alternate packages */
    lua_pushnumber(L, OCTEONTX_ALT_CN96XX);
    lua_setfield(L, -2, "ALT_CN96XX");
    lua_pushnumber(L, OCTEONTX_ALT_CN93XX);
    lua_setfield(L, -2, "ALT_CN93XX");
    lua_pushnumber(L, OCTEONTX_ALT_CN93XXC);
    lua_setfield(L, -2, "ALT_CN93XXC");
    lua_pushnumber(L, OCTEONTX_ALT_CN95XXE);
    lua_setfield(L, -2, "ALT_CN95XXE");
    lua_pushnumber(L, OCTEONTX_ALT_CN96XXH);
    lua_setfield(L, -2, "ALT_CN96XXH");
    lua_pushnumber(L, OCTEONTX_ALT_CN93XXJ);
    lua_setfield(L, -2, "ALT_CN93XXJ");
    lua_pushnumber(L, OCTEONTX_ALT_CN96XXM);
    lua_setfield(L, -2, "ALT_CN96XXM");
    lua_pushnumber(L, OCTEONTX_ALT_CN96XXP);
    lua_setfield(L, -2, "ALT_CN96XXP");
}

