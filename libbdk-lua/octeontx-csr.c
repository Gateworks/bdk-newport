/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <unistd.h>
// Module for interfacing with octeontx CSRs

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(CSR_DB);

static int create_csr_table(lua_State* L, bdk_node_t node);

static uint64_t build_mask(int bits, int left_shift)
{
    uint64_t mask = ~((~0x0ull) << bits);
    if (bits == 64)
        mask = -1;
    return mask << left_shift;
}

/**
 * Called when octeontx.csr.NAME.read() is invoked
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_read(lua_State* L)
{
    bdk_node_t node = lua_tointeger(L, lua_upvalueindex(1));
    int db_index = lua_tointeger(L, lua_upvalueindex(2));
    int params[BDK_CSR_DB_MAX_PARAM];
    for (int i = 0; i < BDK_CSR_DB_MAX_PARAM; i++)
        params[i] = lua_tointeger(L, lua_upvalueindex(3 + i));
    luaL_argcheck(L, lua_gettop(L) == 0, 1, "No arguments expected");
    lua_pushnumber(L, bdk_csr_read_indexed(node, db_index, params));
    return 1;
}

/**
 * Called when octeontx.csr.NAME.write(value) is invoked
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_write(lua_State* L)
{
    const char *name = lua_tostring(L, lua_upvalueindex(1));
    bdk_node_t node = lua_tointeger(L, lua_upvalueindex(2));
    bdk_csr_write_by_name(node, name, luaL_checknumber(L, 1));
    return 0;
}

/**
 * Called when octeontx.csr.NAME.load_add(value) is invoked
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_load_add(lua_State* L)
{
    const char *name = lua_tostring(L, lua_upvalueindex(1));
    bdk_node_t node = lua_tointeger(L, lua_upvalueindex(2));
    lua_pushnumber(L, bdk_csr_load_add_by_name(node, name, luaL_checknumber(L, 1)));
    return 1;
}

/**
 * Called when octeontx.csr.NAME.display(optional) is invoked
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_display(lua_State* L)
{
    bdk_node_t node = lua_tointeger(L, lua_upvalueindex(1));
    int db_index = lua_tointeger(L, lua_upvalueindex(2));
    int params[BDK_CSR_DB_MAX_PARAM];
    for (int i = 0; i < BDK_CSR_DB_MAX_PARAM; i++)
        params[i] = lua_tointeger(L, lua_upvalueindex(3 + i));

    uint64_t value;
    if (lua_isnumber(L, 1))
        value = luaL_checknumber(L, 1);
    else
        value = bdk_csr_read_indexed(node, db_index, params);
    if (bdk_csr_decode_indexed(db_index, params, value))
        return luaL_error(L, "%s: CSR not found", __FUNCTION__);
    return 0;
}

/**
 * Called when octeontx.csr.NAME.decode(optional) is invoked
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_decode(lua_State* L)
{
    const char *csr_name = lua_tostring(L, lua_upvalueindex(1));
    bdk_node_t node = lua_tointeger(L, lua_upvalueindex(2));
    uint64_t value;
    if (lua_isnumber(L, 1))
        value = luaL_checknumber(L, 1);
    else
        value = bdk_csr_read_by_name(node, csr_name);

    const char *fieldn;
    int start_bit = 0;
    int field_width = bdk_csr_field(csr_name, start_bit, &fieldn);

    if (field_width < 0)
        return luaL_error(L, "%s: CSR not found", __FUNCTION__);

    lua_newtable(L);
    while (field_width > 0)
    {
        uint64_t v = value >> start_bit;
        v &= build_mask(field_width, 0);
        lua_pushnumber(L, v);
        lua_setfield(L, -2, fieldn);
        start_bit += field_width;
        field_width = bdk_csr_field(csr_name, start_bit, &fieldn);
    }
    return 1;
}

/**
 * Called when octeontx.csr.NAME.encode(table) is invoked
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_encode(lua_State* L)
{
    const char *csr_name = lua_tostring(L, lua_upvalueindex(1));
    bdk_node_t node = lua_tointeger(L, lua_upvalueindex(2));
    luaL_checktype(L, 1, LUA_TTABLE);

    uint64_t value = 0;
    const char *fieldn;
    int start_bit = 0;
    int field_width = bdk_csr_field(csr_name, start_bit, &fieldn);

    if (field_width < 0)
        return luaL_error(L, "%s: CSR not found", __FUNCTION__);

    while (field_width > 0)
    {
        lua_getfield(L, 1, fieldn);
        if (!lua_isnil(L, -1))
        {
            uint64_t fieldv = luaL_checknumber(L, -1);
            value &= ~build_mask(field_width, start_bit);
            fieldv &= build_mask(field_width, 0);
            value |= fieldv << start_bit;
        }
        lua_pop(L, 1);
        start_bit += field_width;
        field_width = bdk_csr_field(csr_name, start_bit, &fieldn);
    }
    bdk_csr_write_by_name(node, csr_name, value);
    lua_pushnumber(L, value);
    return 1;
}

/**
 * Called when a CSR field is read using octeontx.csr.NAME.FIELD
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_field_index(lua_State* L)
{
    const char *csr_name = lua_tostring(L, lua_upvalueindex(1));
    bdk_node_t node = lua_tointeger(L, lua_upvalueindex(2));
    const char *field_name = luaL_checkstring(L, 2);

    const char *fieldn;
    int start_bit = 0;
    int field_width = bdk_csr_field(csr_name, start_bit, &fieldn);
    while (field_width > 0)
    {
        if (strcasecmp(field_name, fieldn) == 0)
        {
            uint64_t value = bdk_csr_read_by_name(node, csr_name);
            value >>= start_bit;
            value &= build_mask(field_width, 0);
            lua_pushnumber(L, value);
            return 1;
        }
        start_bit += field_width;
        field_width = bdk_csr_field(csr_name, start_bit, &fieldn);
    }
    return luaL_error(L, "%s: Field not found", __FUNCTION__);
}

/**
 * Called when a CSR field is set using octeontx.csr.NAME.FIELD
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_field_newindex(lua_State* L)
{
    const char *csr_name = lua_tostring(L, lua_upvalueindex(1));
    bdk_node_t node = lua_tointeger(L, lua_upvalueindex(2));
    const char *field_name = luaL_checkstring(L, 2);
    uint64_t new_value = luaL_checknumber(L, 3);


    const char *fieldn;
    int start_bit = 0;
    int field_width = bdk_csr_field(csr_name, start_bit, &fieldn);
    while (field_width > 0)
    {
        if (strcasecmp(field_name, fieldn) == 0)
        {
            uint64_t value = bdk_csr_read_by_name(node, csr_name);
            value &= ~build_mask(field_width, start_bit);
            new_value &= build_mask(field_width, 0);
            value |= new_value << start_bit;
            bdk_csr_write_by_name(node, csr_name, value);
            return 0;
        }
        start_bit += field_width;
        field_width = bdk_csr_field(csr_name, start_bit, &fieldn);
    }
    return luaL_error(L, "%s: Field not found", __FUNCTION__);
}

/**
 * Returns a table representing a CSR. One argument is expected, the
 * CSR name to lookup. The name contains "()" for indexed CSRs
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_lookup(lua_State* L)
{
    /* This function is always called with one
       upvalue, the node number. It expects one
       Lua parameter, the name of the CSR */
    int node = lua_tointeger(L, lua_upvalueindex(1));
    const char *name = luaL_checkstring(L, -1);

    int params[BDK_CSR_DB_MAX_PARAM] = {-1, -1, -1, -1};
    int db_index = __bdk_csr_lookup_index(name, params);
    if (db_index < 0)
        luaL_error(L, "Invalid CSR");

    lua_newtable(L);
    lua_pushinteger(L, node);
    lua_pushinteger(L, db_index);
    for (int i = 0; i < BDK_CSR_DB_MAX_PARAM; i++)
        lua_pushinteger(L, params[i]);
    lua_pushcclosure(L, octeontx_csr_read, 2 + BDK_CSR_DB_MAX_PARAM);
    lua_setfield(L, -2, "read");
    lua_pushstring(L, name);
    lua_pushinteger(L, node);
    lua_pushcclosure(L, octeontx_csr_write, 2);
    lua_setfield(L, -2, "write");
    lua_pushstring(L, name);
    lua_pushinteger(L, node);
    lua_pushcclosure(L, octeontx_csr_load_add, 2);
    lua_setfield(L, -2, "load_add");
    lua_pushinteger(L, node);
    lua_pushinteger(L, db_index);
    for (int i = 0; i < BDK_CSR_DB_MAX_PARAM; i++)
        lua_pushinteger(L, params[i]);
    lua_pushcclosure(L, octeontx_csr_display, 2 + BDK_CSR_DB_MAX_PARAM);
    lua_setfield(L, -2, "display");
    lua_pushstring(L, name);
    lua_pushinteger(L, node);
    lua_pushcclosure(L, octeontx_csr_decode, 2);
    lua_setfield(L, -2, "decode");
    lua_pushstring(L, name);
    lua_pushinteger(L, node);
    lua_pushcclosure(L, octeontx_csr_encode, 2);
    lua_setfield(L, -2, "encode");

    lua_newtable(L);
    lua_pushstring(L, name);
    lua_pushinteger(L, node);
    lua_pushcclosure(L, octeontx_csr_field_index, 2);
    lua_setfield(L, -2, "__index");
    lua_pushstring(L, name);
    lua_pushinteger(L, node);
    lua_pushcclosure(L, octeontx_csr_field_newindex, 2);
    lua_setfield(L, -2, "__newindex");
    lua_setmetatable(L, -2);
    return 1;
}

/**
 * This function is called for CSRs that need indexed arguments.
 * It is given to Lua as the response to octeontx.csr.NAME, which
 * Lua calls as a function when the () is added.
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_namecall(lua_State* L)
{
    /* This function expects two up values:
       1) The node number
       2) The base name of the CSR before the parens */
    char fullname[64];
    //int node = lua_tointeger(L, lua_upvalueindex(1));
    const char *basename = lua_tostring(L, lua_upvalueindex(2));
    int num_args = lua_gettop(L);

    if(num_args == 4)
    {
        int arg1 = luaL_checkinteger(L, 1);
        int arg2 = luaL_checkinteger(L, 2);
        int arg3 = luaL_checkinteger(L, 3);
        int arg4 = luaL_checkinteger(L, 4);
        snprintf(fullname, sizeof(fullname), "%s(%d,%d,%d,%d)", basename, arg1, arg2, arg3, arg4);
    }
    else if(num_args == 3)
    {
        int arg1 = luaL_checkinteger(L, 1);
        int arg2 = luaL_checkinteger(L, 2);
        int arg3 = luaL_checkinteger(L, 3);
        snprintf(fullname, sizeof(fullname), "%s(%d,%d,%d)", basename, arg1, arg2, arg3);
    }
    else if(num_args == 2)
    {
        int arg1 = luaL_checkinteger(L, 1);
        int arg2 = luaL_checkinteger(L, 2);
        snprintf(fullname, sizeof(fullname), "%s(%d,%d)", basename, arg1, arg2);
    }
    else if(num_args == 1)
    {
        int arg1 = luaL_checkinteger(L, 1);
        snprintf(fullname, sizeof(fullname), "%s(%d)", basename, arg1);
    }
    else
        luaL_error(L, "Invalid number of arguments to CSR");

    fullname[sizeof(fullname)-1] = 0;
    lua_pushstring(L, fullname);
    return octeontx_csr_lookup(L);
}

/**
 * Called when octeontx.csr.NAME needs to be resolved to a CSR
 * table or function.
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_index(lua_State* L)
{
    /* This function is called with one upvalue, the node number of the
       master. This is used for the default case where you specify
       csr.NAME */
    int node = lua_tointeger(L, lua_upvalueindex(1));

    /* If the argument is a number, then the user is specifying the
       node using the syntax csr[node].NAME */
    if (lua_isnumber(L, 2))
    {
        /* Make sure the node number is valid */
        node = luaL_checkinteger(L, 2);
        if ((node < 0) || (node >= (int)BDK_NUMA_MAX_NODES) || !bdk_numa_exists(node))
            luaL_error(L, "Invalid Node");
        return create_csr_table(L, node);
    }

    const char *name = luaL_checkstring(L, 2);

    if(bdk_csr_get_name(name, NULL, false))
    {
        /* Can't find CSR, assume it is an indexed function */
        /* Put the node in as the first upvalue */
        /* Use our argument as the second upvalue for the function */
        lua_pushinteger(L, node);
        lua_pushstring(L, name);
        lua_pushcclosure(L, octeontx_csr_namecall, 2);
        return 1;
    }
    else
    {
        /* We found it, so do the function call directly */
        return octeontx_csr_lookup(L);
    }
}

/**
 * Called when someone attempts to add something to the
 * octeontx.csr table. This is not allowed.
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_newindex(lua_State* L)
{
    luaL_error(L, "CSR table doesn't allow new indexes");
    return 0;
}

/**
 * Iterator function returned by octeontx.csr(). It is used by for
 * loops to show all possible CSR strings.
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_iter(lua_State* L)
{
    char buffer[64];
    const char *last = NULL;
    if (lua_gettop(L) >= 2)
    {
        if(!lua_isnil(L, 2))
            last = luaL_checkstring(L, 2);
    }
    int status = bdk_csr_get_name(last, buffer, false);
    if (status)
        status = bdk_csr_get_name(last, buffer, true);
    if (status)
    {
        lua_pushnil(L);
        lua_pushnil(L);
    }
    else
    {
        lua_pushstring(L, buffer);
        lua_pushnil(L);
    }
    return 2;
}

/**
 * Called when octeontx.csr() is invoked. It returns an iterator
 * used in for loops.
 *
 * @param L
 *
 * @return
 */
static int octeontx_csr_call(lua_State* L)
{
    lua_pushcfunction(L, octeontx_csr_iter);
    lua_pushnil(L);
    if (lua_gettop(L) >= 1)
    {
        if (!lua_isnil(L, 1))
        {
            const char *prefix = luaL_checkstring(L, 2);
            lua_pushstring(L, prefix);
            return 3;
        }
    }
    return 2;
}

static int create_csr_table(lua_State* L, bdk_node_t node)
{
    /* Add octeontx.csr, magic table access to CSRs */
    lua_newtable(L); /* csr table */
    lua_pushinteger(L, node);
    lua_pushcclosure(L, octeontx_csr_lookup, 1);
    lua_setfield(L, -2, "lookup");
    lua_newtable(L); /* csr metatable */
    lua_pushinteger(L, node);
    lua_pushcclosure(L, octeontx_csr_index, 1);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, octeontx_csr_newindex);
    lua_setfield(L, -2, "__newindex");
    lua_pushcfunction(L, octeontx_csr_call);
    lua_setfield(L, -2, "__call");
    lua_setmetatable(L, -2);
    return 1;
}

/**
 * Called to register the octeontx module
 *
 * @param L
 *
 * @return
 */
void register_octeontx_csr(lua_State* L)
{
    bdk_node_t node = bdk_numa_local();
    create_csr_table(L, node);
    lua_setfield(L, -2, "csr");
}

