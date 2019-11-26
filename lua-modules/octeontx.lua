-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

--
-- Lua module supporting remote connections through
-- RPC or locally on the target. When running on the target,
-- the module "octeontx-internal" is already pre-loaded, so
-- this file use it as a base. On the host, this will be
-- called when a script does a "require(octeontx)". We then
-- use RPC to connect this host "octeontx" module with the
-- one on the target.
--
if rawget(_G, "octeontx") then
    return octeontx
end

require("utils")

local status, base = pcall(require, "octeontx-internal")

if not status then
    -- Create a connection to the remote system
    local cnx = os.getenv("OCTEONTX_REMOTE_CONSOLE")
    assert(cnx,
[[
Missing environment.

The environment variable OCTEONTX_REMOTE_CONSOLE must be defined.
OCTEONTX_REMOTE_CONSOLE should be a serial device (/dev/ttyS0),
an IPv4 address and port number for TCP/IP (10.0.0.2:23), or the
special value "remote". A hostname can also be used for IPv4
address name lookup. The TCP port will default to 23 if omitted.
The special value of "remote" uses the OCTEONTX_REMOTE_PROTOCOL to
access the remote console.
]])
    require("rpc")
    local remote = rpc.connect(cnx)
    base = remote.octeontx

    -- Add a global member that has access to the global context on the remote
    -- system
    base.global = remote
else
    base.global = false
end

-- Make the octeontx module global by default
octeontx = base

return base

