-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK USB menu.
-- Displays the GUI interface for configuring and accessing USB.
require("strict")
require("utils")
require("menu")
require("fileio")

if not octeontx.is_model(octeontx.CN8XXX) and not octeontx.is_model(octeontx.CN96XXP1) then
    print("\nUSB not supported on this chip\n")
    return
end

local usb_port = 0

local function usb_init(usb_port)
    local clock_type = 0
    if octeontx.is_model(octeontx.CN81XX) then
        clock_type = menu.prompt_number("Clock type 0:USB_REF_CLK 1:DLMC_REF_CLK0 2:DLMC_REF_CLK1\n3:USB_REF_CLK/PLL_REF_CLK 4:DLMC_RF_CLK0/PLL_REF_CLK 5:DELMC_REF_CLK1/PLL_REF_CLK")
    end
    local status = octeontx.c.bdk_usb_initialize(menu.node, usb_port, clock_type)
    assert(status == 0, "Failed to initialize the USB port")
end

local function usb_test(usb_port, test)
    assert(octeontx.c.bdk_usb_test_mode(menu.node, usb_port, test) == 0, "Failed to set USB test mode")
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
        local name = octeontx.c.bdk_usb_get_test_mode_string(menu.node,usb_port,test)
        if name == nil then
            break
        end
        m:item("test" .. tostring(test), name, usb_test, usb_port, test)
        test = test + 1
    end

    m:item("pat-test", "Run automated pattern test", do_pattern_test)
    m:item("quit", "Main menu")
until m:show() == "quit"

