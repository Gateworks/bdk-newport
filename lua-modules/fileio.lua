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

---
-- Lua module supporting higher level file operations
-- that are common using the BDK's virtual filesystem.
--
-- * Written by Chad Reese
-- * Copyright (C) 2010-2017 Cavium Inc.
--
require("strict")
require("utils")
local readline = require("readline")

fileio = {}
--- Maximum size of block to transfer in one read/write
fileio.block_size = 4096
fileio.PATTERNS = {0x00, 0xff, 0x55, 0xaa}

--- Open a file, throwing an exception on failure
-- @param filename File to open.
-- @param mode File open mode to pass into io.open().
-- @param seek_to Location to seek to in the file, or nil
-- @return File handle
function fileio.open(filename, mode, seek_to)
    assert(type(filename) == "string")
    assert(type(mode) == "string")
    assert((seek_to == nil) or tonumber(seek_to))
    local handle
    if isglobal("cavium") and (filename:sub(1,5) == "/dev/") then
        handle = assert(cavium.devopen(filename, mode))
    else
        handle = assert(io.open(filename, mode))
    end
    if seek_to then
        local loc = handle:seek("set", seek_to)
        if not loc then
            error('Seek failed in file "' .. filename ..'"')
        end
    end
    return handle
end

--- Transfer data from one file handle to another.
function fileio.transfer(source_handle, dest_handle, length)
    local on_target, unused = pcall(require, "cavium-internal")
    if length == nil then
        -- Assume no file is larger than 64GB
        length = 0x1000000000
    end
    local transfer_count = 0
    while transfer_count < length do
        local l = length - transfer_count
        if l > fileio.block_size then
            l = fileio.block_size
        end
        local data = source_handle:read(l)
        if data == nil then
            break
        end
        dest_handle:write(data)
        transfer_count = transfer_count + #data
        if not on_target then
            printf("\rTransferred %7d bytes", transfer_count)
        end
    end
    if not on_target then
        printf("\n")
    end
    return transfer_count
end

--- Copy data from one file to another.
function fileio.copy(source, source_seek, dest, dest_seek, length)
    local close_source = false
    local close_dest = false
    if type(source) == "string" then
        source = fileio.open(source, "r", source_seek)
        close_source = true
    end
    if type(dest) == "string" then
        dest = fileio.open(dest, "w", dest_seek)
        close_dest = true
    end
    local count = fileio.transfer(source, dest, length)
    if close_source then
        source:close()
    end
    if close_dest then
        dest:close()
    end
    return count
end


--- Hex dump a file.
function fileio.hexdump(source, seek_to, length)
    local close_source = false
    if type(source) == "string" then
        source = fileio.open(source, "r", seek_to)
        close_source = true
    end

    local loc = source:seek("cur")
    local last_data
    local repeat_count = 0
    local data
    if (not length) or (length >= 16) then
        data = source:read(16)
    else
        data = source:read(length)
    end
    while data do
        if data == last_data then
            repeat_count = repeat_count + 1
            if repeat_count == 1 then
                printf("*\n")
            end
        else
            repeat_count = 0;
            last_data = data
            printf("%08x: ", loc)
            for i=1,#data do
                printf("%02x", data:byte(i))
                if (i%4 == 0) then
                    printf(" ")
                end
            end
            if #data < 16 then
                for i=#data+1,16 do
                    printf("  ")
                    if (i%4 == 0) then
                        printf(" ")
                    end
                end
            end
            printf("   ")
            for i=1,#data do
                local c = data:byte(i)
                if (c < 32) or (c > 127) then
                    printf(".")
                else
                    printf("%s", data:sub(i,i))
                end
            end
            printf("\n")
        end
        if length then
            length = length - #data
            if length >= 16 then
                data = source:read(16)
            elseif length == 0 then
                data = nil
            else
                data = source:read(length)
            end
        else
            data = source:read(16)
        end
        loc = loc + 16
    end
    if close_source then
        source:close()
    end
end

--
-- Create a "length" sector string for the given pattern. The string
-- length will be block_size * length.
--
function fileio.get_pattern(pattern, length, block_size)
    local pat = string.char(pattern)
    if block_size == nil then
        block_size = 512
    end
    pat = pat:rep(length * block_size)
    return pat
end

--
-- Run an automated test of bit patterns on a file
--
function fileio.pattern_test(filename, block_size, max_blocks, start_block)
    -- Allow this test to be repeated for long term testing
    local loop_count = menu.prompt_number("Repeat count (-1 for infinite)", 1)

    local handle = assert(cavium.devopen(filename, "r+"))
    local offset = start_block * block_size

    -- Get the end loop count
    if loop_count == -1 then
        loop_count = 0x7fffffffffffffff
    elseif loop_count < 1 then
        loop_count = 1
    end
    -- Loop running the test
    for count=1,loop_count do
        -- Show progress
        if loop_count == 0x7fffffffffffffff then
            printf("Pass %d - Press return to exit\n", count)
        else
            printf("Pass %d of %d - Press return to exit\n", count, loop_count)
        end
        -- Run the test
        for length=1,max_blocks do
            printf("Testing %d block accesses\n", length)
            for i,p in ipairs(fileio.PATTERNS) do
                local correct = fileio.get_pattern(p, length, block_size)
                assert(handle:seek("set", offset), "Write seek failed")
                handle:write(correct)
                assert(handle:seek("set", offset), "Read seek failed")
                local data = handle:read(length * block_size)
                assert(#data == length * block_size, "Read failed")
                assert(correct == data, "Data doesn't match pattern")
            end
            local key = readline.getkey()
            if key == '\r' then
                printf("\nAbort on key press\n")
                goto abort_key
            end
        end
    end
::abort_key::
    handle:close()
end

return fileio
