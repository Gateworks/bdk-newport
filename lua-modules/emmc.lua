-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK eMMC menu.
-- Displays the GUI interface for accessing eMMC/SD.
require("strict")
require("utils")
require("fileio")
require("menu")
local readline = require("readline")

local option = ""

local function do_test(chip_sel)
    local chip_sel = menu.prompt_number("Chip select", 0, 0, 3)
    local filename = utils.devfile("mmc", chip_sel)
    return fileio.pattern_test(filename, 512, 128, 0)
end

while (option ~= "quit") do
    local m = menu.new("eMMC, MMC, or SD Menu")
    m:item_node() -- Adds option to choose the node number
    m:item("mmc-vw", "View eMMC, MMC, or SD", function()
        local chip_sel = menu.prompt_number("Chip select", 0, 0, 3)
        local offset = menu.prompt_number("Starting offset")
        local length = menu.prompt_number("Bytes to display")
        local filename = utils.devfile("mmc", chip_sel)
        fileio.hexdump(filename, offset, length)
    end)
    m:item("mmc-wr", "Write eMMC, MMC, or SD", function()
        local chip_sel = menu.prompt_number("Chip select", 0, 0, 3)
        local source = menu.prompt_filename("Enter source filename")
        local offset = menu.prompt_number("eMMC offset")
        local filename = utils.devfile("mmc", chip_sel)
        fileio.copy(source, nil, filename, offset)
    end)
    m:item("mmc-test", "Run automated pattern test", do_test)
    m:item("quit", "Main menu")
    option = m:show()
end

