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

-- BDK PCIe menu.
-- Displays the GUI interface for accessing PCIe.
require("strict")
require("utils")
require("menu")
require("fileio")
local pcie = require("pcie")
local bit64 = require("bit64")
local qlm_tuning = require("qlm_tuning")

local pcie_root = {}

--
-- PCIe host mode functions
--

local function do_initialize(pcie_port)
    pcie_root[pcie_port] = pcie.initialize(menu.node, pcie_port)
end

local function prefix(pcie_port)
    if pcie_port < 100 then
        return "PCIe" .. pcie_port
    else
        return "ECAM" .. (pcie_port-100)
    end
end

local function do_scan(pcie_port)
    assert(pcie_root[pcie_port], prefix(pcie_port) .. " not initialized")
    pcie_root[pcie_port]:scan()
end

local function do_enumerate(pcie_port)
    assert(pcie_root[pcie_port], prefix(pcie_port) .. " not initialized")
    pcie_root[pcie_port]:enumerate()
end

local function do_display(pcie_port)
    assert(pcie_root[pcie_port], prefix(pcie_port) .. " not initialized")
    local show_vfs = menu.prompt_yes_no("Display VirtualFunctions",false)
    pcie_root[pcie_port]:display(show_vfs)
end

local function do_cfg_read(pcie_port)
    local def_bus = cavium.csr[menu.node].PCIERCX_CFG006(pcie_port).SBNUM
    local bus = menu.prompt_number("Bus", def_bus, 0, 255)
    local dev = menu.prompt_number("Device", 0, 0, 31)
    local fn = menu.prompt_number("Function", 0, 0, 7)
    local reg = menu.prompt_number("Register", 0, 0, 65535)
    local value = cavium.c.bdk_pcie_config_read32(menu.node, pcie_port, bus, dev, fn, reg)
    printf("%d:%d.%d[0x%x]: 0x%08x\n", bus, dev, fn, reg, value)
end

local function do_cfg_write(pcie_port)
    local def_bus = cavium.csr[menu.node].PCIERCX_CFG006(pcie_port).SBNUM
    local bus = menu.prompt_number("Bus", def_bus, 0, 255)
    local dev = menu.prompt_number("Device", 0, 0, 31)
    local fn = menu.prompt_number("Function", 0, 0, 7)
    local reg = menu.prompt_number("Register", 0, 0, 65535)
    local value = menu.prompt_number("Value to write", 0)
    printf("%d:%d.%d[0x%x] = 0x%08x\n", bus, dev, fn, reg, value)
    cavium.c.bdk_pcie_config_write32(menu.node, pcie_port, bus, dev, fn, reg, value)
end

local function do_read(pcie_port)
    assert(pcie_root[pcie_port], prefix(pcie_port) .. " not initialized")
    local address = menu.prompt_number("PCIe bus address")
    local length = menu.prompt_number("Number of bytes to read", nil, 1, 65536)
    local dev_file = utils.devfile("pcie", pcie_port)
    local f = fileio.open(dev_file, "r", address)
    f:setvbuf("full", length)
    local data = f:read(length)
    f:close()
    printf("Data: ")
    for i=1, #data do
        printf("%02x", data:byte(i))
    end
    printf("\n")
end

local function do_write(pcie_port)
    assert(pcie_root[pcie_port], prefix(pcie_port) .. " not initialized")
    local address = menu.prompt_number("PCIe bus address")
    local hex_data = menu.prompt_string("Data to write in hex")
    local data = ""
    for i=1,#hex_data,2 do
        local c = tonumber(hex_data:sub(i,i+1), 16)
        data = data .. string.char(c)
    end

    local dev_file = utils.devfile("pcie", pcie_port)
    local f = fileio.open(dev_file, "w", address)
    f:setvbuf("full", #data)
    f:write(data)
    f:close()
end

local function do_shutdown(pcie_port)
    assert(pcie_root[pcie_port], prefix(pcie_port) .. " not initialized")
    pcie_root[pcie_port]:shutdown()
    pcie_root[pcie_port] = nil
end

local function pcie_get_num_lane(pcie_port)
    local hostmd = 1
    -- Sadly HOSTMD is zero on chips that don't support EP, so we can't read
    -- it except on CN83XX
    if cavium.is_model(cavium.CN83XX) then
        hostmd = cavium.csr[menu.node].PEMX_CFG(pcie_port).HOSTMD
    end
    local pcie_lanes
    if hostmd == 1 then
        pcie_lanes = cavium.csr[menu.node].PCIERCX_CFG032(pcie_port).NLW
    else
        pcie_lanes = cavium.csr[menu.node].PCIEEPX_CFG032(pcie_port).NLW
    end
    if pcie_lanes == 0 then
        pcie_lanes = 1
    end
    return pcie_lanes
end

local function do_margin_rx(pcie_port)
    local MARGIN_PASS = 7 -- To pass, max-min must be greater than equal to this
    -- Figure out the first QLM for this PCIe port
    local qlm = cavium.c.bdk_qlm_get(menu.node, cavium.IF_PCIE, pcie_port, 0)
    assert(qlm >=0, "Invalid PCIe port")
    -- Setup the PCIe port for use
    do_initialize(pcie_port)
    do_scan(pcie_port)
    do_enumerate(pcie_port)
    -- Get the first PCIe device. There should only be one, a CN73XX
    local devices = pcie_root[pcie_port]:get_devices()
    local device = devices[1]
    assert(device, "Test device not found")
    local id = device:read32(0)
    printf("Device ID: 0x%x\n", id)
    assert(id == 0x9700177d, "Incorrect device found")
    -- Get the location of Octeon's BAR0 and BAR1
    local bar0_address = device:read32(0x10) -- BAR0
    bar0_address = bar0_address + bit64.lshift(device:read32(0x14), 32)
    bar0_address = bit64.band(bar0_address, -16)
    local bar1_address = device:read32(0x18) -- BAR1
    bar1_address = bar1_address + bit64.lshift(device:read32(0x1c), 32)
    bar1_address = bit64.band(bar1_address, -16)
    --printf("Octeon BAR0=0x%x, BAR1=0x%x\n", bar0_address, bar1_address)
    local function octeon_csr_write(address, data)
        local SLI_WIN_WR_ADDR = bar0_address + 0x20000
        local SLI_WIN_WR_DATA = bar0_address + 0x20020
        local SLI_WIN_WR_MASK = bar0_address + 0x20030
        cavium.c.bdk_pcie_mem_write64(menu.node, pcie_port, SLI_WIN_WR_MASK, 0xff)
        cavium.c.bdk_pcie_mem_read64(menu.node, pcie_port, SLI_WIN_WR_MASK)
        cavium.c.bdk_pcie_mem_write64(menu.node, pcie_port, SLI_WIN_WR_ADDR, address)
        cavium.c.bdk_pcie_mem_read64(menu.node, pcie_port, SLI_WIN_WR_ADDR)
        cavium.c.bdk_pcie_mem_write64(menu.node, pcie_port, SLI_WIN_WR_DATA, data)
        cavium.c.bdk_pcie_mem_read64(menu.node, pcie_port, SLI_WIN_WR_DATA)
    end
    -- Force all cores in reset
    octeon_csr_write(0x1010000000100, -1) -- CIU_PP_RST = -1
    -- Setup BAR1 region to allow access
    octeon_csr_write(0x11800c0000100, 0x1) -- SPEMX_BAR1_INDEXX(0,0) = 1
    -- Write a test pattern to Octeon
    cavium.c.bdk_pcie_mem_write64(menu.node, pcie_port, bar1_address,    0x0123456789abcdef)
    cavium.c.bdk_pcie_mem_write64(menu.node, pcie_port, bar1_address+8,  0xfedcba9876543210)
    cavium.c.bdk_pcie_mem_write64(menu.node, pcie_port, bar1_address+16, 0x0123456789abcdef)
    cavium.c.bdk_pcie_mem_write64(menu.node, pcie_port, bar1_address+24, 0xfedcba9876543210)
    -- Define the function that runs a data read test
    local function do_test()
        local errors = 0
        cavium.csr[menu.node].PEMX_DBG_INFO(pcie_port).write(-1)
        for count=1,2000 do
            local d1 = cavium.c.bdk_pcie_mem_read64(menu.node, pcie_port, bar1_address)
            local d2 = cavium.c.bdk_pcie_mem_read64(menu.node, pcie_port, bar1_address+8)
            local d3 = cavium.c.bdk_pcie_mem_read64(menu.node, pcie_port, bar1_address+16)
            local d4 = cavium.c.bdk_pcie_mem_read64(menu.node, pcie_port, bar1_address+24)
            if d1 ~= 0x0123456789abcdef then
                errors = errors + 1
            end
            if d2 ~= 0xfedcba9876543210 then
                errors = errors + 1
            end
            if d3 ~= 0x0123456789abcdef then
                errors = errors + 1
            end
            if d4 ~= 0xfedcba9876543210 then
                errors = errors + 1
            end
            if cavium.csr[menu.node].PEMX_DBG_INFO(pcie_port).read() ~= 0 then
                errors = errors + 1
            end
            if errors > 0 then
                break
            end
        end
        return errors
    end
    -- Figure out how many lanes we will use
    local pcie_lanes = pcie_get_num_lane(pcie_port)
    local qlm_lanes = cavium.c.bdk_qlm_get_lanes(menu.node, qlm)
    local qlm_lane = 0
    printf("N%d.PCIe%d: Measuring Eye Height %d lanes\n", menu.node, pcie_port, pcie_lanes)
    for lane = 0, pcie_lanes-1 do
        local avg_eye_height = 0
        local avg_count = 3
        for avg_repeat=1,avg_count do
            local node = menu.node
            local vert_center = cavium.c.bdk_qlm_margin_rx_get(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL);
            local vert_min = cavium.c.bdk_qlm_margin_rx_get_min(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL);
            local vert_max = cavium.c.bdk_qlm_margin_rx_get_max(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL);

            for vert = vert_center,vert_max do
                cavium.c.bdk_qlm_margin_rx_set(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert);
                local have_error = do_test() > 0
                --printf("    %d - %s\n", vert, have_error and "FAIL" or "PASS")
                if have_error then
                    vert_max = vert - 1
                    break
                end
            end

            for vert = vert_center,vert_min,-1 do
                cavium.c.bdk_qlm_margin_rx_set(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert);
                local have_error = do_test() > 0
                --printf("    %d - %s\n", vert, have_error and "FAIL" or "PASS")
                if have_error then
                    vert_min = vert + 1
                    break
                end
            end
            cavium.c.bdk_qlm_margin_rx_restore(node, qlm, qlm_lane, cavium.QLM_MARGIN_VERTICAL, vert_center);
            --printf("N%d.PCIe%d QLM%d Lane %d: Min=%d, Middle=%d, Max=%d\n", menu.node, pcie_port, qlm, qlm_lane, vert_min, vert_center, vert_max)
            local eye_height = (vert_max - vert_min) + 1
            avg_eye_height = avg_eye_height + eye_height
        end
        local eye_height = avg_eye_height / avg_count
        local status = (eye_height >= MARGIN_PASS) and "PASS" or "FAIL"
        printf("N%d.PCIe%d QLM%d Lane %d: Eye Height %2d - %s\n", menu.node, pcie_port, qlm, qlm_lane, eye_height, status)
        qlm_lane = qlm_lane + 1
        if qlm_lane >= qlm_lanes then
            qlm_lane = 0
            qlm = qlm + 1
            qlm_lanes = cavium.c.bdk_qlm_get_lanes(menu.node, qlm)
        end
    end
end

local function disp_tuning(pcie_port)
    local qlm = cavium.c.bdk_qlm_get(menu.node, cavium.IF_PCIE, pcie_port, 0)
    assert(qlm >=0, "Invalid PCIe port")
    local pcie_lanes = pcie_get_num_lane(pcie_port)
    local qlm_lanes = cavium.c.bdk_qlm_get_lanes(menu.node, qlm)
    local qlm_lane = 0
    for lane = 0, pcie_lanes-1 do
        qlm_tuning.display_tuning_state(menu.node, qlm, qlm_lane)
        qlm_lane = qlm_lane + 1
        if qlm_lane >= qlm_lanes then
            qlm_lane = 0
            qlm = qlm + 1
            qlm_lanes = cavium.c.bdk_qlm_get_lanes(menu.node, qlm)
        end
    end
end

local function disp_eye(pcie_port)
    local qlm = cavium.c.bdk_qlm_get(menu.node, cavium.IF_PCIE, pcie_port, 0)
    assert(qlm >=0, "Invalid PCIe port")
    local pcie_lanes = pcie_get_num_lane(pcie_port)
    local qlm_lanes = cavium.c.bdk_qlm_get_lanes(menu.node, qlm)

    local lane = menu.prompt_number("PCIe Lane", 0, 0, pcie_lanes-1)
    while lane >= qlm_lanes do
        lane = lane - qlm_lanes
        qlm = qlm + 1
        qlm_lanes = cavium.c.bdk_qlm_get_lanes(menu.node, qlm)
    end
    cavium.c.bdk_qlm_eye_display(menu.node, qlm, lane, 1, nil)
end

local function disp_flash(pcie_port)
    cavium.c.bdk_pcie_flash_dump(menu.node, pcie_port)
end

local function do_port_menu(pcie_port)
    local prefix = prefix(pcie_port)
    local m = menu.new(prefix .." Menu")
    m:item("init", prefix .. ": Initialize", do_initialize, pcie_port)
    m:item("scan", prefix .. ": Scan for devices", do_scan, pcie_port)
    if pcie_port < 100 then
        m:item("enum", prefix .. ": Enumerate devices", do_enumerate, pcie_port)
    end
    m:item("disp", prefix .. ": Display devices", do_display, pcie_port)
    m:item("cfgr", prefix .. ": Perform a config read", do_cfg_read, pcie_port)
    m:item("cfgw", prefix .. ": Perform a config write", do_cfg_write, pcie_port)
    if pcie_port < 100 then
        m:item("read", prefix .. ": Perform a memory read", do_read, pcie_port)
        m:item("write", prefix .. ": Perform a memory write", do_write, pcie_port)
        m:item("shut", prefix .. ": Shutdown", do_shutdown, pcie_port)
        m:item("margin", prefix .. ": Run margining tool", do_margin_rx, pcie_port)
        m:item("disp_tuning", prefix .. ": Display SERDES tuning", disp_tuning, pcie_port)
        m:item("eye", prefix .. ": Display RX eye", disp_eye, pcie_port)
        if cavium.is_model(cavium.CN83XX) then
            m:item("flash", prefix .. ": Display SPI flash ROM", disp_flash, pcie_port)
        end
    end
    m:item("quit", "Main menu")
    while (m:show() ~= "quit") do
        -- Spinning on menu
    end
end

--
-- PCIe main menu
--

local m = menu.new("PCIe Menu")
m:item_node() -- Adds option to choose the node number
local max_ports = cavium.c.bdk_pcie_get_num_ports(menu.node)
for pcie_port=0,max_ports-1 do
    m:item("p" .. pcie_port, "PCIe port " .. pcie_port, do_port_menu, pcie_port)
end
-- Add entries for accessing the internal ECAMs
local num_ecams = cavium.c.bdk_ecam_get_num(menu.node);
for ecam=0,num_ecams-1 do
    m:item("e" .. ecam, "Internal ECAM" .. ecam, do_port_menu, ecam + 100)
end

m:item("quit", "Main menu")

while (m:show() ~= "quit") do
    -- Spinning on menu
end
