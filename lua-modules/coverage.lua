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

--- Lua coverage implementation.
--
-- Monitor which Lua script lines are executed. As each Lua script is
-- run, the file and line executed is stored. Once the script completes,
-- the coverage information for each Lua file is written to a new file
-- with ".coverage" appended to the name.
--
-- The simplest way to use this modules is to add it to the Lua command line.
--
-- bdk-lua -l coverage script.lua
--

local debug = require("debug")

coverage = {}
coverage.data = {}

local function update_count(filename, lineno, count)
    local file_data = coverage.data[filename]
    if not file_data then
        file_data = {}
        coverage.data[filename] = file_data
    end
    local old = file_data[lineno]
    if old then
        file_data[lineno] = old + count
    else
        file_data[lineno] = count
    end
end

--
-- Called every time Lua executes a line
--
local function coverage_hook(reason, lineno)
    local info = debug.getinfo(2, "Sl")
    local filename = tostring(info.short_src)
    local lineno = info.currentline
    update_count(filename, lineno, 1)
end

--
-- Read previous coverage results from old coverage files so we can give
-- cumulative results.
--
local function read_old_results(filename, coverage_filename)
    local infile = io.open(coverage_filename, "r")
    if not infile then
        return
    end
    local lineno = 0
    local line = infile:read("*L")
    while line do
        lineno = lineno + 1
        local prefix = line:match("(%d+):")
        if prefix then
            local count = tonumber(prefix)
            assert(count > 0, "Illegal value when reading previous coverage run")
            update_count(filename, lineno, count)
        end
        line = infile:read("*L")
    end
    infile:close()
end

---
-- Start coverage analysis
--
function coverage.start()
    debug.sethook(coverage_hook, "l")
end

---
-- Stop coverage analysis
--
function coverage.stop()
    debug.sethook()
end

---
-- Report coverage analysis
--
function coverage.report()
    coverage.stop()
    local skip_expressions = {
        "^ *[-][-]", -- Comment lines
        "^ *\n$", -- Empty lines
        "^ *}\n$", -- Lines ending table defines
        "^ *end\n$", -- end by itself
        "^ *else\n$", -- else by itself
        "^local function", -- Local function prototypes
        "^ *repeat\n$", -- repeat by itself
    }
    print("Coverage Report")
    for filename, filedata in pairs(coverage.data) do
        local infile = io.open(filename, "r")
        if infile then
            local coverage_filename = filename .. ".coverage"
            read_old_results(filename, coverage_filename)
            local outfile = assert(io.open(coverage_filename, "w"))
            local count = 0
            local hit = 0
            local miss = 0
            local line = infile:read("*L")
            while line do
                count = count + 1
                local prefix = nil
                if filedata[count] then
                    prefix = string.format("%7d:", filedata[count])
                    hit = hit + 1
                else
                    for _,pattern in ipairs(skip_expressions) do
                        if line:match(pattern) then
                            prefix = "       :"
                            break
                        end
                    end
                    if not prefix then
                        prefix = "#######:"
                        miss = miss + 1
                    end
                end
                outfile:write(prefix)
                outfile:write(line)
                line = infile:read("*L")
            end
            outfile:close()
            infile:close()
            if count > 0 then
                print(filename, tostring(100 * hit / (hit + miss)) .. "%")
            end
        end
    end
end

-- Create a report when Lua exits
local meta = {}
meta.__gc = coverage.report
coverage.on_gc = setmetatable({}, meta)

-- Start coverage by default
coverage.start()

return coverage
