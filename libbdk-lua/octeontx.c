/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <unistd.h>
// Module for interfacing with the chip

/**
 * Called to register the octeontx module
 *
 * @param L
 *
 * @return
 */
LUALIB_API int luaopen_octeontx(lua_State* L)
{
    #define REGISTER(L, name) \
        extern void register_##name(lua_State* L); \
        register_##name(L)

    /* Create a new table for the module */
    lua_newtable(L);

    /* Add function for opening device files. Used by RPC. This is just
        another way to get to the local io.open */
    lua_getglobal(L, "io");
    lua_getfield (L, -1, "open");
    lua_setfield(L, -3, "devopen");
    lua_pop(L, 1);

    REGISTER(L, octeontx_model);
    REGISTER(L, octeontx_platform);
    REGISTER(L, octeontx_c);
    REGISTER(L, octeontx_config);
    REGISTER(L, octeontx_constants);
    REGISTER(L, octeontx_perf);
    REGISTER(L, octeontx_time);

    if (BDK_IS_REQUIRED(TRAFFIC_GEN))
    {
        extern void register_trafficgen(lua_State* L) BDK_WEAK;
        register_trafficgen(L);
    }

    if (BDK_IS_REQUIRED(CSR_DB))
    {
        extern void register_octeontx_csr(lua_State* L) BDK_WEAK;
        register_octeontx_csr(L);
    }

    return 1;
}

