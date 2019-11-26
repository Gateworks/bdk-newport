/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <unistd.h>
// Module for interfacing with C functions

static const char *get_version(void)
{
    return bdk_version_string();
}

/**
 * Wrapper to call a generic C function from Lua. A maximum
 * of 8 arguments are supported. Each argument can either be a
 * number or string. Function can only return numbers.
 *
 * @param L
 *
 * @return
 */
static int octeontx_c_call(lua_State* L)
{
    /* The prototype of func(), its call below, and the array size
       MAX_ARGS of args[] must all match */
    long (*func)(long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, long arg7, long arg8,long arg9, long arg10);
    const int MAX_ARGS = 10;
    long args[MAX_ARGS];
    int num_args = lua_gettop(L);
    func = lua_topointer(L, lua_upvalueindex(1));

    if (num_args > MAX_ARGS)
    {
        luaL_error(L, "More than %d arguments to a C function", MAX_ARGS);
        return 0;
    }

    int i;
    for(i=0; i<num_args; i++)
    {
        /* Use lua_type() instead of lua_isX() so Lua doesn't do type
            conversion. I'll never understand the fascination with weakly
            typed languages */
        int arg_type = lua_type(L, i+1);
        if (arg_type == LUA_TNUMBER)
        {
            args[i] = lua_tonumber(L, i+1);
        }
        else if (arg_type == LUA_TSTRING)
        {
            const char *str = lua_tostring(L, i+1);
            args[i] = (long)str;
        }
        else if (arg_type == LUA_TNIL)
        {
            args[i] = 0;
        }
        else if (arg_type == LUA_TBOOLEAN)
        {
            args[i] = lua_toboolean(L, i+1);
        }
        else
        {
            luaL_error(L, "Invalid argument type");
            return 0;
        }
    }

    long result = func(args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7],args[8],args[9]);
    if ((func == (void*)bdk_qlm_mode_tostring) ||
        (func == (void*)bdk_qlm_mode_to_cfg_str) ||
        (func == (void*)bdk_dram_get_test_name) ||
        (func == (void*)bdk_dram_get_info_string) ||
        (func == (void*)bdk_usb_get_test_mode_string) ||
        (func == (void*)bdk_boot_info_wafer) ||
        (func == (void*)bdk_boot_info_serial) ||
        (func == (void*)bdk_boot_info_unique_id) ||
        (func == (void*)bdk_model_get_sku) ||
        (func == (void*)get_version) ||
        (func == (void*)bdk_config_get_str))
        lua_pushstring(L, (const char*)result);
    else
        lua_pushnumber(L, result);

    return 1;
}

static int get_sbrk(lua_State* L)
{
    lua_pushnumber(L, bdk_ptr_to_phys(sbrk(0)));
    return 1;
}

/**
 * Called to register the C module
 *
 * @param L
 *
 * @return
 */
void register_octeontx_c(lua_State* L)
{
    /* Create a new table of all C functions that can be called */
    lua_newtable(L);
    int i = 0;
    while(bdk_functions[i].name)
    {
        if (bdk_functions[i].func)
        {
            lua_pushlightuserdata(L, bdk_functions[i].func);
            lua_pushcclosure(L, octeontx_c_call, 1);
            lua_setfield(L, -2, bdk_functions[i].name);
        }
        else
        {
            //bdk_warn("Symbol %s is not defined\n", bdk_functions[i].name);
        }
        i++;
    }

    /* Manually add CSR read and write as these are inline functions
        that are missed by bdk_functions */
    lua_pushlightuserdata(L, bdk_csr_read);
    lua_pushcclosure(L, octeontx_c_call, 1);
    lua_setfield(L, -2, "bdk_csr_read");
    lua_pushlightuserdata(L, bdk_csr_write);
    lua_pushcclosure(L, octeontx_c_call, 1);
    lua_setfield(L, -2, "bdk_csr_write");

    /* Manually add version as this is a inline function, missed by bdk_functions */
    lua_pushlightuserdata(L, get_version);
    lua_pushcclosure(L, octeontx_c_call, 1);
    lua_setfield(L, -2, "bdk_version_string");

    /* Add function for seeing the size of the heap */
    lua_pushcfunction(L, get_sbrk);
    lua_setfield(L, -2, "get_sbrk");

    lua_setfield(L, -2, "c");
}

/**
 * This function should be called inside bdk_lua_callback() to add
 * custom functions to the octeontx.c table. This allows
 * applications to add functions without modifying bdk-function.
 *
 * @param L      Lua state
 * @param name   Name of the function to use in octeontx.c.NAME
 * @param func   Function to register. The function can take a maximum of eight
 *               arguments where each argument must be a type compatible with a
 *               int64_t or a constant string pointer. The return value of the
 *               function can be void or a type compatible with a int64_t.
 */
void bdk_lua_register_cfunc(lua_State* L, const char *name, void *func)
{
    lua_getglobal(L, "require");
    lua_pushstring(L, "octeontx-internal");
    lua_call(L, 1, 1);
    /* Only "octeontx-internal" on stack */
    lua_getfield(L, -1, "c");
    lua_pushlightuserdata(L, func);
    lua_pushcclosure(L, octeontx_c_call, 1);
    lua_setfield(L, -2, name);
    lua_pop(L, 1); /* Pop the "c" table */
    lua_pop(L, 1); /* Pop the "octeontx-internal" table */
}

