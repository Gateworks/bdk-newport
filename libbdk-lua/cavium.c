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
#include <unistd.h>
// Module for interfacing with the chip

/**
 * Called to register the cavium module
 *
 * @param L
 *
 * @return
 */
LUALIB_API int luaopen_cavium(lua_State* L)
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

    REGISTER(L, cavium_model);
    REGISTER(L, cavium_platform);
    REGISTER(L, cavium_c);
    REGISTER(L, cavium_config);
    REGISTER(L, cavium_constants);
    REGISTER(L, cavium_perf);
    REGISTER(L, cavium_mmc);

    if (BDK_IS_REQUIRED(TRAFFIC_GEN))
    {
        extern void register_trafficgen(lua_State* L) BDK_WEAK;
        register_trafficgen(L);
    }

    if (BDK_IS_REQUIRED(CSR_DB))
    {
        extern void register_cavium_csr(lua_State* L) BDK_WEAK;
        register_cavium_csr(L);
    }

    if (BDK_IS_REQUIRED(AQR107_SUPPORT))
    {
        extern void register_aqr107(lua_State* L) BDK_WEAK;
        register_aqr107(L);
    }


    return 1;
}

