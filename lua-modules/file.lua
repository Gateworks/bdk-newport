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
    local result =  cavium.c.bdk_fs_list(ls_path, 0, 0);
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


