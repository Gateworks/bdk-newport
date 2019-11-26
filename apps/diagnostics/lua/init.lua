-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************
require("octeontx")

-- Print out a banner
print("")
print("OcteonTX Diagnostics")
print("Copyright (C) 2018 Marvell International Ltd.")
print("BDK Version: ".. octeontx.c.bdk_version_string())
print("")

local debug = require("debug")

-- Start the main menu.
while true do
    local main_name = assert(package.searchpath("main", package.path))
    local status, result = xpcall(dofile, debug.traceback, main_name)
    if not status then
        print("ERROR:", result)
    end
end
