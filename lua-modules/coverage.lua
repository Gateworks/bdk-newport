-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
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
