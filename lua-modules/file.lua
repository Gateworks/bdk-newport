-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK File menu.
-- Displays the GUI interface for accessing the filesystem.
require("strict")
require("utils")
require("fileio")
require("menu")

local m = menu.new("File Menu")
local ls_path = "/"

m:item("view",  "View file", function()
    local name = menu.prompt_filename("Enter filename")
    fileio.copy(name, nil, io.output())
end)

m:item("hex",   "Hexdump file", function()
    local name = menu.prompt_filename("Enter filename")
    local offset = menu.prompt_number("Starting offset")
    local length = menu.prompt_number("Bytes to display")
    fileio.hexdump(name, offset, length)
end)

m:item("base64", "BASE64 encode a file", function()
    local name = menu.prompt_filename("Enter filename")
    local offset = menu.prompt_number("Starting offset")
    local length = menu.prompt_number("Bytes to display")
    fileio.copy(name, offset, "/base64", nil, length)
end)

m:item("copy",  "Copy file", function()
    local source = menu.prompt_filename("Enter source filename")
    local dest = menu.prompt_filename("Enter destination filename")
    fileio.copy(source, nil, dest)
end)

m:item("rm",    "Delete file", function()
    local name = menu.prompt_filename("Enter filename")
    local status, result = os.remove(name)
    if not status then
        printf("ERROR: %s\n", result)
    end
end)

m:item("lua",   "Execute Lua file", function()
    local name = menu.prompt_filename("Enter filename")
    local status, result = pcall(dofile, name)
    if not status then
        printf("ERROR: %s\n", result)
    end
end)

m:item("listfs",   "List files", function()
    ls_path = menu.prompt_filename("Enter directory name", ls_path)
    local result =  octeontx.c.bdk_fs_list(ls_path, 0, 0);
    if not result then
        printf("ERROR: %s\n", result)
    end
end)

m:item("pattern", "Run automated pattern test", function()
    local name = menu.prompt_filename("Enter filename")
    local block_size = menu.prompt_number("Read/write block size", 512, 1, 65536)
    local start_block = menu.prompt_number("Starting block", 0)
    local max_blocks = menu.prompt_number("Blocks to read/write", 128, 1, 65536)
    return fileio.pattern_test(name, block_size, max_blocks, start_block)
end)

m:item("quit",  "Main menu")

while (m:show() ~= "quit") do
    -- Spinning on menu
end


