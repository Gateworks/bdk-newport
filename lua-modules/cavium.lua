-- ***********************license start***********************************
-- Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
-- reserved.
--
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions are
-- met:
--
--   * Redistributions of source code must retain the above copyright
--     notice, this list of conditions and the following disclaimer.
--
--   * Redistributions in binary form must reproduce the above
--     copyright notice, this list of conditions and the following
--     disclaimer in the documentation and/or other materials provided
--     with the distribution.
--
--   * Neither the name of Cavium Inc. nor the names of
--     its contributors may be used to endorse or promote products
--     derived from this software without specific prior written
--     permission.
--
-- This Software, including technical data, may be subject to U.S. export
-- control laws, including the U.S. Export Administration Act and its
-- associated regulations, and may be subject to export or import
-- regulations in other countries.
--
-- TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
-- AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
-- WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
-- TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
-- REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
-- DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
-- OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
-- PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
-- QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
-- ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
-- **********************license end**************************************

--
-- Lua module supporting remote connections through
-- RPC or locally on the target. When running on the target,
-- the module "cavium-internal" is already pre-loaded, so
-- this file use it as a base. On the host, this will be
-- called when a script does a "require(cavium)". We then
-- use RPC to connect this host "cavium" module with the
-- one on the target.
--
-- * Written by Chad Reese
-- * Copyright (C) 2010-2017 Cavium Inc.
--
if rawget(_G, "cavium") then
    return cavium
end

require("utils")

local status, base = pcall(require, "cavium-internal")

if not status then
    -- Create a connection to the remote system
    local cnx = os.getenv("CAVIUM_REMOTE_CONSOLE")
    assert(cnx,
[[
Missing environment.

The environment variable CAVIUM_REMOTE_CONSOLE must be defined.
CAVIUM_REMOTE_CONSOLE should be a serial device (/dev/ttyS0),
an IPv4 address and port number for TCP/IP (10.0.0.2:23), or the
special value "remote". A hostname can also be used for IPv4
address name lookup. The TCP port will default to 23 if omitted.
The special value of "remote" uses the CAVIUM_REMOTE_PROTOCOL to
access the remote console.
]])
    require("rpc")
    local remote = rpc.connect(cnx)
    base = remote.cavium

    -- Add a global member that has access to the global context on the remote
    -- system
    base.global = remote
else
    base.global = false
end

-- Make the cavium module global by default
cavium = base

return base

