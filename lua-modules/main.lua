#!/usr/bin/env bdk-lua
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

-- BDK Main menu

require("strict")
require("utils")
require("menu")
require("rpc")
require("cavium")

-- Set the baudrate. Many messages have already been printed, but we needed
-- to wait for the cavium module.
-- The first argument is the node number (0-1)
-- The second argument is the uart number (0-1)
-- The third argument is the baud rate (9600, 19200, 115200, etc).
-- The fourth argument is whether flow control is enabled.
-- cavium.c.bdk_set_baudrate(cavium.MASTER_NODE, 0, 115200, true)
-- cavium.c.bdk_set_baudrate(cavium.MASTER_NODE, 1, 115200, true)

-- Do board specific setup
--
-- When there is a general board setup file present in the filesystem, execute
-- that. Otherwise, execute the board setup based on the chip model.
if utils.isglobal("BOARD_SETUP_DONE") then
    -- Board setup is already complete, don't do it again
elseif package.searchpath("board-setup", package.path) then
    menu.dofile("board-setup")
end
BOARD_SETUP_DONE = true

local function do_trafficgen()
    local trafficgen = require("trafficgen")
    local tg = trafficgen.new()
    if cavium.is_platform(cavium.PLATFORM_EMULATOR) then
        tg:command("csr RST_PP_RESET")
        tg:command("csr RST_PP_AVAILABLE")
        tg:command("loopback all internal")
        cavium.c.bdk_if_link_wait_all(100000);
        tg:command("default up")
        tg:command("perf_test")
        tg:command("tx_packets_total")
        tg:command("rx_packets_total")
        tg:command("rx_errors")
    end
    return tg:run()
end

if cavium.is_platform(cavium.PLATFORM_EMULATOR) then
    do_trafficgen()
end

local m = menu.new("Main Menu")
m:item("cfg",   "Display current configuration", cavium.c.bdk_config_show)
m:item("qlm",   "SERDES configuration",     menu.dofile, "qlm_menu")
m:item("file",  "File options",             menu.dofile, "file")
m:item("ddr",   "DDR options",              menu.dofile, "ddr_menu")
m:item("pcie",  "PCIe options",             menu.dofile, "pcie_menu")
m:item("twsi",  "TWSI options",             menu.dofile, "twsi_menu")
m:item("smi",   "SMI/MDIO options",         menu.dofile, "smi_menu")
m:item("mpi",   "SPI/MPI options",          menu.dofile, "mpi_menu")
m:item("emmc",  "eMMC/SD options",          menu.dofile, "emmc")
m:item("sata",  "SATA options",             menu.dofile, "sata")
m:item("gpio",  "GPIO options",             menu.dofile, "gpio_menu")
m:item("sgpio", "SGPIO options",            menu.dofile, "sgpio_menu")
m:item("usb",   "USB options",              menu.dofile, "usb_menu")
m:item("ilua",  "Interactive Lua prompt",   menu.dofile, "ilua")
m:item("tg",    "Traffic Generator",        do_trafficgen)
m:item("burn",  "Power Burn options",       menu.dofile, "power_burn_menu")
m:item("vsc7224",   "VSC7224 options",      menu.dofile, "vsc7224_menu")
if  cavium.c.bdk_aqr_flashinfo then
    m:item("aqr",   "aqr-107 phy support",      menu.dofile, "aqr107_menu")
end
if cavium.is_model(cavium.CN88XX) then
    m:item("ccpi",  "CCPI options",         menu.dofile, "ccpi_menu")
end
if not cavium.is_model(cavium.CN88XX) then
    m:item("pbus",  "PBUS options",         menu.dofile, "pbus_menu")
end
m:item("trust", "Trusted Boot options",     menu.dofile, "trusted_boot")
-- Look for a custom board test file
local board = cavium.c.bdk_config_get_str(cavium.CONFIG_BOARD_MODEL)
local board_test_name = ("board-test-%s" % board):lower()
if package.searchpath(board_test_name, package.path) then
    local test = require(board_test_name)
    m:item("brdtest", "Run board test", test)
end
m:item("rbt",   "Reboot",                   cavium.c.bdk_reset_chip, cavium.MASTER_NODE)
if cavium.global then
    m:item("quit", "Exit menu")
end

while (m:show() ~= "quit") do
    -- Spinning on menu
end

