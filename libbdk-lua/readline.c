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
#include <bdk.h>

// Module for interfacing with readline

/**
 * getkey()
 * Return a pending input byte if available
 *
 * @param L
 *
 * @return
 */
static int lgetkey(lua_State* L)
{
    int key = bdk_readline_getkey(1000);
    if (key != -1)
    {
        char c = key;
        lua_pushlstring(L, &c, 1);
    }
    else
        lua_pushnil(L);
    return 1;
}

static const bdk_readline_tab_t *table_to_tab(lua_State* L, int tindex)
{
    /* Find how many entries we will need */
    int length = 0;

    lua_pushnil(L);  /* first key */
    while (lua_next(L, tindex) != 0)
    {
        length++;
        /* removes 'value'; keeps 'key' for next iteration */
        lua_pop(L, 1);
    }

    /* Allocate the tab completion structure */
    bdk_readline_tab_t *tab = calloc(sizeof(bdk_readline_tab_t), length+1);
    if (!tab)
        return NULL;

    /* Loop through and fill the tab compeltion structure */
    int loc = 0;
    lua_pushnil(L);  /* first key */
    while (lua_next(L, tindex) != 0)
    {
        if (lua_istable(L, -1))
        {
            /* Entry is a name:table that needs a sub tree */
            tab[loc].str = lua_tostring(L, -2);
            tab[loc].next = table_to_tab(L, lua_absindex(L, -1));
        }
        else
        {
            /* Entry is a simple entry with no children */
            tab[loc].str = lua_tostring(L, -1);
            tab[loc].next = NULL;
        }
        /* removes 'value'; keeps 'key' for next iteration */
        lua_pop(L, 1);
        loc++;
    }
    return tab;
}

static void tabfree(const bdk_readline_tab_t *tab)
{
    const bdk_readline_tab_t *ptr = tab;
    while (ptr->str)
    {
        if (ptr->next)
            tabfree(ptr->next);
        ptr++;
    }
    free((void*)tab);
}

static int lreadline(lua_State* L)
{
    const bdk_readline_tab_t *tab = NULL;
    const char *prompt = luaL_checkstring(L, 1);
    luaL_checkany(L, 2);
    uint32_t timeout_us = luaL_checkinteger(L, 3);

    /* Get the table of pending input from the registry */
    lua_pushlightuserdata(L, lreadline);
    lua_gettable(L, LUA_REGISTRYINDEX);
    if (!lua_isnil(L, -1))
    {
        if (luaL_len(L, -1) > 0)
        {
            /* Use table.remove to get the first item */
            lua_getglobal(L, "table");
            lua_getfield(L, -1, "remove");
            lua_pushvalue(L, -3); /* Input table */
            lua_pushinteger(L, 1); /* Index */
            lua_call(L, 2, 1); /* Pops func and args */
            lua_remove(L, -2); /* Pops the "table" global */
            lua_remove(L, -2); /* Pops the input table */
            /* Return first element from pending input */
            return 1;
        }
        /* Pop the input table */
        lua_pop(L, 1);
    }

    if (lua_istable(L, 2))
        tab = table_to_tab(L, 2);

    const char *result = bdk_readline(prompt, tab, timeout_us);
    if (tab)
        tabfree(tab);

    if (result && (result[0] == 3))
    {
        lua_getglobal(L, "debug_interrupt");
        int isnil = lua_isnil(L, -1);
        lua_pop(L, 1);
        if (isnil)
        {
            return luaL_error(L, "interrupted!");
        }
        else
        {
            /* The BDK debugger looks for a global debug_interrupt=true */
            lua_pushboolean(L, 1);
            lua_setglobal(L, "debug_interrupt");
            result = NULL;
        }
    }
    lua_pushstring(L, result);
    return 1;
}

static int lfakeinput(lua_State* L)
{
    /* Expect one argument, a string for readline input */
    luaL_checkstring(L, 1);
    /* Get the table of pending input from the registry */
    lua_pushlightuserdata(L, lreadline);
    lua_gettable(L, LUA_REGISTRYINDEX);
    if (lua_isnil(L, -1))
    {
        /* Table doesn't exist, create it */
        lua_pop(L, 1); /* Pop the nil */
        lua_pushlightuserdata(L, lreadline);
        lua_newtable(L);
        lua_settable(L, LUA_REGISTRYINDEX);
        /* Get the table back again after adding it to the registry */
        lua_pushlightuserdata(L, lreadline);
        lua_gettable(L, LUA_REGISTRYINDEX);
    }
    /* My input table is at the top of the stack */
    lua_pushinteger(L, luaL_len(L, -1) + 1); /* Get the table length+1 */
    lua_pushvalue(L, 1);    /* Get our argument */
    lua_settable(L, -3);    /* Push the new value onto the end of the table */
    lua_pop(L, 1);          /* Pop the input table */
    return 0;
}

static lua_State *globalL;
void __bdk_rpc_serve(void)
{
    lua_State *L = globalL;
    lua_getglobal(L, "require");
    lua_pushstring(L, "rpc");
    lua_call(L, 1, 1);
    lua_getfield(L, -1, "serve");
    lua_pushboolean(L, 1);
    lua_call(L, 1, 0);
    lua_pop(L, 1); /* Pop rpc object */
}

LUALIB_API int luaopen_readline(lua_State *L)
{
    globalL = L;
    lua_newtable(L);
    lua_pushcfunction(L, lgetkey);
    lua_setfield(L, -2, "getkey");
    lua_pushcfunction(L, lreadline);
    lua_setfield(L, -2, "readline");
    lua_pushcfunction(L, lfakeinput);
    lua_setfield(L, -2, "fakeinput");
    return 1;
}

