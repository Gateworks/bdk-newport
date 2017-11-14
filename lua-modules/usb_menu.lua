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

-- BDK USB menu.
-- Displays the GUI interface for configuring and accessing USB.
require("strict")
require("utils")
require("menu")
require("fileio")

local usb_port = 0

local function usb_init(usb_port)
    local clock_type = 0
    if cavium.is_model(cavium.CN81XX) then
        clock_type = menu.prompt_number("Clock type 0:USB_REF_CLK 1:DLMC_REF_CLK0 2:DLMC_REF_CLK1\n3:USB_REF_CLK/PLL_REF_CLK 4:DLMC_RF_CLK0/PLL_REF_CLK 5:DELMC_REF_CLK1/PLL_REF_CLK")
    end
    local status = cavium.c.bdk_usb_initialize(menu.node, usb_port, clock_type)
    assert(status == 0, "Failed to initialize the USB port")
end

local function usb_test(usb_port, test)
    assert(cavium.c.bdk_usb_test_mode(menu.node, usb_port, test) == 0, "Failed to set USB test mode")
end

local function do_pattern_test(chip_sel)
    printf("\n")
    printf("The automated pattern test requires USB bulk storage devices. The\n")
    printf("names of these device are of the form \"/dev/n%d.usb#\", where the\n", menu.node)
    printf("\"#\" is a number that increments for each device found. Enter this\n")
    printf("number at the following prompt. The possible choices can be seen\n")
    printf("in the output for \"Show USB host controller state\".\n")
    printf("\n")
    local chip_sel = menu.prompt_number("USB storage device number", 0, 0, 255)
    local filename = utils.devfile("usb", chip_sel)
    return fileio.pattern_test(filename, 512, 128, 0)
end

repeat
    local m = menu.new("USB Menu")
    m:item_node() -- Adds option to choose the node number

    m:item("port", "Select USB port (Currently %d)" % usb_port,
        function()
            usb_port = menu.prompt_number("USB port", usb_port, 0, 1)
        end)

    m:item("init", "Initialize the port", usb_init, usb_port)
    local test = 0
    while true do
        local name = cavium.c.bdk_usb_get_test_mode_string(menu.node,usb_port,test)
        if name == nil then
            break
        end
        m:item("test" .. tostring(test), name, usb_test, usb_port, test)
        test = test + 1
    end

    m:item("pat-test", "Run automated pattern test", do_pattern_test)
    m:item("quit", "Main menu")
until m:show() == "quit"

