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
-- Simple utilities for Lua to do common operations.
--
-- * Written by Chad Reese
-- * Copyright (C) 2010-2017 Cavium Inc.
-- * This module is released under the standard Lua MIT license
--

utils = {}

---
-- C style printf function. printf("format", ...).
--
function utils.printf(...)
    io.write(string.format(...))
end
printf = utils.printf

---
-- Python style string formatting
-- * str = "format" % value
-- * str = "format" % {...}
--
getmetatable("").__mod = function(format, param)
    if not param then
        return format
    elseif type(param) == "table" then
        return string.format(format, table.unpack(param))
    else
        return string.format(format, param)
    end
end

local function pprint_str(param, indent, visited)
    if type(param) == "nil" then
        return "nil"
    elseif type(param) == "boolean" then
        if param then
            return "true"
        else
            return "false"
        end
    elseif type(param) == "number" then
        return "%d (0x%x)" % {param, param}
    elseif type(param) == "string" then
        return "%q" % param
    elseif type(param) == "function" then
        return tostring(param)
    elseif type(param) == "userdata" then
        return tostring(param)
    elseif type(param) == "thread" then
        return "thread (%s)" % param:status()
    elseif type(param) == "table" then
        local keys = table.sorted_keys(param)
        visited[param] = 1
        local table_indent = indent .. "    "
        local result = {"{\n"}
        for k=1, #keys do
            local key = keys[k]
            local value = param[key]
            table.insert(result, table_indent)
            if (type(value) == "table") and visited[value] then
                if type(key) == "number" then
                    table.insert(result, "[%d] = {...}\n" % key)
                else
                    table.insert(result, tostring(key))
                    table.insert(result, " = {...}\n")
                end
            elseif type(key) == "number" then
                table.insert(result, "[%d] = " % key)
                table.insert(result, pprint_str(value, table_indent, visited))
                table.insert(result, "\n")
            else
                table.insert(result, tostring(key))
                table.insert(result, " = ")
                table.insert(result, pprint_str(value, table_indent, visited))
                table.insert(result, "\n")
            end
        end
        table.insert(result, indent)
        table.insert(result, "}")
        return table.concat(result)
    else
        error("Unsupported type %s" % type(param))
    end
end

---
-- Pretty print any Lua object
-- @param ... One or more Lua objects to display
--
function utils.pprint(...)
    local p
    if rawget(table, "pack") == nil then
        p = {...}
        p.n = #p
    else
        p = table.pack(...)
    end
    local visited = {}
    local r = {}
    for i=1,p.n do
        r[i] = pprint_str(p[i], "", visited)
    end
    print(table.concat(r, " "))
end
pprint = utils.pprint

local function compare(a,b)
    local na = tonumber(a)
    local nb = tonumber(b)
    if na and nb then
        return na < nb
    else
        return tostring(a) < tostring(b)
    end
end

---
-- Return a table's keys in sorted order
-- @param tbl Table to sort keys of
-- @return Table of sorted keys
--
function table.sorted_keys(tbl)
    local result = {}
    for k,_ in pairs(tbl) do
        table.insert(result, k)
    end
    table.sort(result, compare)
    return result
end

---
-- Return a table's values in sorted order
-- @param tbl Table to sort values of
-- @return Table of sorted values
--
function table.sorted_values(tbl)
    local result = {}
    for _,v in pairs(tbl) do
        table.insert(result, v)
    end
    table.sort(result, compare)
    return result
end

---
-- Return if the string name is defiend as a global variable
-- @param name Name of a variable to check
--
function utils.isglobal(name)
    return rawget(_G, name) ~= nil
end
isglobal = utils.isglobal

---
-- Convert a string to hex
-- @function string:hex()
--
function string.hex(str)
    local hex = {}
    for i = 1,#str do
        hex[i] = "%02x" % str:byte(i,i)
    end
    return table.concat(hex)
end

---
-- Used by the BDK to automatically run files as key parts of the Lua code.
-- This allows the BDK to be modified or extended without changing the
-- original Lua code.
-- @param filename Filename to run, if it exists
-- @return Nothing
--
function utils.run(filename, ...)
    local fullname = package.searchpath(filename, package.path)
    if fullname then
        local tmp = arg
        arg = table.pack(...)
        arg[0] = fullname
        dofile(fullname)
        arg = tmp
    end
end

---
-- Function to simplify creating an device filename for the current work node.
-- @param dev_name Device base name
-- @param index Which device on the node to get
-- @return Device filename
function utils.devfile(dev_name, index)
    return "/dev/n%d.%s%d" % {menu.node, dev_name, index}
end

return utils
