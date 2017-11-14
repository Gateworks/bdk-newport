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

-- BDK TWSI menu.
-- Displays the GUI interface for accessing TWSI.
require("strict")
require("utils")
require("menu")

local function twsi_scan(twsi_bus)
    printf("TWSI%d: Scanning bus...\n", twsi_bus)
    for dev_addr = 0, 127 do
        local data = cavium.c.bdk_twsix_read_ia(menu.node, twsi_bus, dev_addr, 0, 1, 0)
        if data >= 0 then
            printf("TWSI%d: Address %3d (0x%02x) responded\n", twsi_bus, dev_addr, dev_addr)
        end
    end
end

local function twsi_read(twsi_bus)
    local dev_addr = menu.prompt_number("Device address", nil, 0, 127)
    local ia_width = menu.prompt_number("Internal address width", nil, 0, 2)
    local ia_address = 0
    if ia_width > 0 then
        ia_address = menu.prompt_number("Internal address")
    end
    local num_bytes = menu.prompt_number("Number of bytes to read", nil, 1, 4)
    local result = cavium.c.bdk_twsix_read_ia(menu.node, twsi_bus, dev_addr, ia_address, num_bytes, ia_width)
    assert(result ~= -1, "TWSI read failed")
    printf("Result: %d (0x%x)\n", result, result)
end

local function twsi_write(twsi_bus)
    local dev_addr = menu.prompt_number("Device address", nil, 0, 127)
    local ia_width = menu.prompt_number("Internal address width", nil, 0, 2)
    local ia_address = 0
    if ia_width > 0 then
        ia_address = menu.prompt_number("Internal address")
    end
    local num_bytes = menu.prompt_number("Number of bytes to write", nil, 1, 4)
    local data = menu.prompt_number("Data to write")
    local result = cavium.c.bdk_twsix_write_ia(menu.node, twsi_bus, dev_addr, ia_address, num_bytes, ia_width, data)
    assert(result ~= -1, "TWSI write failed")
end

local function spd_dump(twsi_bus)
    local dev_addr = menu.prompt_number("Device address", nil, 0, 127)
    local result = cavium.c.bdk_spd_eeprom_dump(twsi_bus, dev_addr)
    assert(result ~= -1, "TWSI write failed")
end
local function spd_prog(twsi_bus)
    local dev_addr = menu.prompt_number("Device address", nil, 0, 127)
    local result = cavium.c.bdk_spd_eeprom_prog(twsi_bus, dev_addr)
    assert(result ~= -1, "TWSI write failed")
end

local function twsi_submenu(twsi_bus)
    local m = menu.new("TWSI Menu - Bus " .. twsi_bus)
    m:item("scan", "Scan bus", twsi_scan, twsi_bus)
    m:item("read", "Read", twsi_read, twsi_bus)
    m:item("write", "Write", twsi_write, twsi_bus)
    m:item("spd_dump", "Dump", spd_dump, twsi_bus)
    m:item("spd_prog", "Prog", spd_prog, twsi_bus)
    m:item("quit", "Main menu")

    while (m:show() ~= "quit") do
    -- Spinning on menu
    end
end


local m = menu.new("TWSI Menu")
m:item_node() -- Adds option to choose the node number

-- Build a list of TWSI busses
local twsi_busses = 2
if cavium.is_model(cavium.CN88XX) then
    twsi_busses = 6
end
for bus = 0, twsi_busses-1 do
    m:item("bus" .. bus, "TWSI bus " .. bus, twsi_submenu, bus)
end
m:item("quit", "Main menu")

while (m:show() ~= "quit") do
    -- Spinning on menu
end


