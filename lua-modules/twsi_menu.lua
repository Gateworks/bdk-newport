-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK TWSI menu.
-- Displays the GUI interface for accessing TWSI.
require("strict")
require("utils")
require("menu")

local function twsi_scan(twsi_device)
    printf("Scanning bus...\n")
    for dev_addr = 0, 127 do
        local data = octeontx.c.bdk_device_twsi_read_ia(twsi_device, dev_addr, 0, 1, 0)
        if data >= 0 then
            printf("    Address %3d (0x%02x) responded\n", dev_addr, dev_addr)
        end
    end
end

local function twsi_read(twsi_device)
    local dev_addr = menu.prompt_number("Device address", nil, 0, 127)
    local ia_width = menu.prompt_number("Internal address width", nil, 0, 2)
    local ia_address = 0
    if ia_width > 0 then
        ia_address = menu.prompt_number("Internal address")
    end
    local num_bytes = menu.prompt_number("Number of bytes to read", nil, 1, 4)
    local result = octeontx.c.bdk_device_twsi_read_ia(twsi_device, dev_addr, ia_address, num_bytes, ia_width)
    assert(result ~= -1, "TWSI read failed")
    printf("Result: %d (0x%x)\n", result, result)
end

local function twsi_write(twsi_device)
    local dev_addr = menu.prompt_number("Device address", nil, 0, 127)
    local ia_width = menu.prompt_number("Internal address width", nil, 0, 2)
    local ia_address = 0
    if ia_width > 0 then
        ia_address = menu.prompt_number("Internal address")
    end
    local num_bytes = menu.prompt_number("Number of bytes to write", nil, 1, 4)
    local data = menu.prompt_number("Data to write")
    local result = octeontx.c.bdk_device_twsi_write_ia(twsi_device, dev_addr, ia_address, num_bytes, ia_width, data)
    assert(result ~= -1, "TWSI write failed")
end

local function twsi_submenu(twsi_bus)
    local twsi_device = octeontx.c.bdk_device_lookup_by_name("N%d.TWSI%d" % {menu.node, twsi_bus})
    local m = menu.new("TWSI Menu - Bus " .. twsi_bus)
    m:item("scan", "Scan bus", twsi_scan, twsi_device)
    m:item("read", "Read", twsi_read, twsi_device)
    m:item("write", "Write", twsi_write, twsi_device)
    m:item("quit", "Main menu")

    while (m:show() ~= "quit") do
    -- Spinning on menu
    end
end


local m = menu.new("TWSI Menu")
m:item_node() -- Adds option to choose the node number

-- Build a list of TWSI buses
local twsi_busses = 2
if octeontx.is_model(octeontx.CN9XXX) then
    twsi_busses = 6
end
for bus = 0, twsi_busses-1 do
    m:item("bus" .. bus, "TWSI bus " .. bus, twsi_submenu, bus)
end
m:item("quit", "Main menu")

while (m:show() ~= "quit") do
    -- Spinning on menu
end


