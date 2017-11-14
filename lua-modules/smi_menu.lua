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

-- BDK SMI/MDIO menu.
-- Displays the GUI interface for configuring and accessing SMI/MDIO.
require("strict")
require("utils")
require("menu")

local function smi_scan(smi_bus)
    printf("SMI%d: Scanning bus...\n", smi_bus)
    for dev_addr = 0, 31 do
        --try clause 22
        local data = cavium.c.bdk_mdio_read(menu.node, smi_bus, dev_addr, 0)
        if (data > 0) and (data ~= 0xffff) then
            printf("SMI%d: (Scan22) Address %3d (0x%02x) responded with 0x%04x  dev id %04x:%04x\n", 
                   smi_bus, dev_addr, dev_addr, data,
                   cavium.c.bdk_mdio_read(menu.node, smi_bus, dev_addr, 2),
                   cavium.c.bdk_mdio_read(menu.node, smi_bus, dev_addr, 3) 
            )
        else
		-- if clause 22 failed, try clause 45, probe mmd 1 reg 2 msb of device id
                data = cavium.c.bdk_mdio_45_read(menu.node, smi_bus, dev_addr, 1, 2)
	        if (data >= 0) and (data ~= 0xffff) then
                    printf("SMI%d: (Scan45) PHY Address %3d (0x%02x) mmd 1 responded with 0x%04x dev id %04x:%04x\n", 
                           smi_bus, dev_addr, dev_addr, data, 
                           data,
                           cavium.c.bdk_mdio_45_read(menu.node, smi_bus, dev_addr, 1, 3)
                    )
	        end
        end
    end
end

local function smi_read(smi_bus)
    local dev_addr = menu.prompt_number("Device address", nil, 0, 63)
    local reg = menu.prompt_number("Device register")
    local data = cavium.c.bdk_mdio_read(menu.node, smi_bus, dev_addr, reg)
    assert(data ~= -1, "SMI/MDIO read failed")
    printf("SMI%d: Address %3d (0x%02x) reg %d (0x%x) responded with 0x%04x\n",
        smi_bus, dev_addr, dev_addr, reg, reg, data)
end

local function smi_write(smi_bus)
    local dev_addr = menu.prompt_number("Device address", nil, 0, 63)
    local reg = menu.prompt_number("Device register")
    local data = menu.prompt_number("Data")
    assert(cavium.c.bdk_mdio_write(menu.node, smi_bus, dev_addr, reg, data) ~= -1, "SMI/MDIO write failed")
end

local function smi_read45(smi_bus)
    local phy_addr = menu.prompt_number("PHY address")
    local dev_addr = menu.prompt_number("Device address")
    local reg = menu.prompt_number("Device register")
    local data = cavium.c.bdk_mdio_45_read(menu.node, smi_bus, phy_addr, dev_addr, reg)
    assert(data ~= -1, "SMI/MDIO read failed")
    printf("SMI%d: PHY Address %3d (0x%02x) Device Address %3d (0x%02x) reg %d (0x%x) responded with 0x%04x\n",
        smi_bus, phy_addr, phy_addr, dev_addr, dev_addr, reg, reg, data)
end

local function smi_write45(smi_bus)
    local phy_addr = menu.prompt_number("PHY address")
    local dev_addr = menu.prompt_number("Device address")
    local reg = menu.prompt_number("Device register")
    local data = menu.prompt_number("Data")
    assert(cavium.c.bdk_mdio_45_write(menu.node, smi_bus, phy_addr, dev_addr, reg, data) ~= -1, "SMI/MDIO write failed")
end

local function smi_submenu(smi_bus)
    local m = menu.new("SMI/MDIO Menu - Bus " .. smi_bus)
    m:item("scan", "Scan bus (Clause 22 and 45)", smi_scan, smi_bus)
    m:item("read", "Read a register (Clause 22)", smi_read, smi_bus)
    m:item("write", "Write a register (Clause 22)", smi_write, smi_bus)
    m:item("read45", "Read a register (Clause 45)", smi_read45, smi_bus)
    m:item("write45", "Write a register (Clause 45)", smi_write45, smi_bus)
    m:item("quit", "Main menu")

    while (m:show() ~= "quit") do
    -- Spinning on menu
    end
end


local m = menu.new("SMI/MDIO Menu")
m:item_node() -- Adds option to choose the node number

-- Build a list of smi busses
local smi_busses = 2
for bus = 0, smi_busses-1 do
    m:item("bus" .. bus, "SMI/MDIO bus " .. bus, smi_submenu, bus)
end
m:item("quit", "Main menu")

while (m:show() ~= "quit") do
    -- Spinning on menu
end


