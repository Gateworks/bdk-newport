-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

---
-- Lua RPC implementation.
--
require("utils")
local bit64 = require("bit64")
local debug = require("debug")
local rpc_support = require("rpc-support")

local is_server = false

--
-- Table to contain our module
--
rpc = {}
rpc.debug = false

--
-- Pack arguments into a remote param string
--
local function do_pack(...)
    local result = {}
    local args = table.pack(...)
    for i=1, args.n do
        local arg = args[i]
        local argtype = type(arg)
        if arg == nil then
            table.insert(result, "n")
        elseif argtype == "boolean" then
            if arg then
                table.insert(result, "t")
            else
                table.insert(result, "f")
            end
        elseif argtype == "number" then
            table.insert(result, "#")
            table.insert(result, arg)
        elseif argtype == "string" then
            table.insert(result, rpc_support.string_pack(arg))
        elseif argtype == "table" then
            table.insert(result, "{")
            for k,v in pairs(arg) do
                table.insert(result, do_pack(k))
                table.insert(result, do_pack(v))
            end
            table.insert(result, "}")
        elseif argtype == "userdata" then
            local meta = getmetatable(arg)
            table.insert(result, "@")
            table.insert(result, meta.getid(arg))
        else
            error("Unsupported type '" .. argtype .. "'")
        end
    end
    return table.concat(result)
end

--
-- Unpack return data from a string
--
local function do_unpack(remote, start_index, str, is_server)
    local index = start_index   -- Current index in the string
    local length = #str         -- End of the string
    local result = {}           -- The container for unpacked results
    result.n = 0                -- Number of items in result

    -- print("Call do_unpack(" .. start_index .. ", \"" .. str .. "\")")

    -- Loop until we consume the string. We will exit early if we hit a table
    -- end marker. This is so we can recursively handle tables
    while index <= length do
        local v                         -- Value extracted from the string
        local c = str:sub(index,index)  -- Type char used to determine which type
        index = index + 1
        if c == "n" then    -- Nil
            v = nil
        elseif c == "t" then    -- Boolean true
            v = true
        elseif c == "f" then    -- Boolean false
            v = false
        elseif c == '"' then    -- String
            index, v = rpc_support.string_unpack(index, str)
        elseif c == "#" then    -- Number
            -- Numbers are a sequnce of decimal digits. The protocol guarantees
            -- that either a non digit follows a number or it is at the EOL
            local start, fin = str:find("[0-9]+", index)
            v = tonumber(str:sub(index, fin))
            index = fin + 1
        elseif c == "@" then    -- Remote object
            -- Remote object id is similar to a number
            local start, fin = str:find("[0-9]+", index)
            v = tonumber(str:sub(index, fin))
            if is_server then
                v = rpc.objects[v]
            else
                v = getmetatable(remote).new(remote, v)
            end
            index = fin + 1
        elseif c == "{" then    -- Table begin
            -- Tables are stored as a sequence of key value pairs ended with a
            -- "}". Call do_unpack recursively to handle these.
            local t
            index, t = do_unpack(remote, index, str, is_server)
            -- Change the sequence into a table
            v = {}
            for i=1,#t,2 do
                v[t[i]] = t[i+1]
            end
        elseif c == "}" then    -- Table end
            -- End of table. Break out and let the caller finish the string
            break
        elseif c == "e" then    -- Error exception
            local t
            index, t = do_unpack(remote, index, str, is_server)
            error(t[1])
        else
            error('Unexpected format char at ' .. (index-1) .. ' in  "' .. str .. '"')
        end
        -- Add the latest value to the end of the results
        result.n = result.n + 1
        result[result.n] = v
    end
    -- print("return do_unpack(" .. index .. ")")
    return index, result
end

--
-- Calculate the correct checksum for a line and return it in a string read
-- for transmit
--
local function get_checksum(line)
    local checksum = 0
    for i=1,#line do
        checksum = checksum + line:sub(i,i):byte()
    end
    checksum = bit64.band(checksum, 0xff)
    return "#%02x" % checksum
end

--
-- Send a RPC command
--
local function send_command(stream, line)
    -- Debug output as necessary
    if rpc.debug then
        if is_server then
            io.write("[RPC Server Response]" .. line .. "\n")
        else
            io.write("[RPC Send]" .. line .. "\n")
        end
    end
    rpc_support.send_message(stream, line)
end

--
-- Receive a RPC command
--
local function receive_command(stream, already_began)
    local result = rpc_support.receive_message(stream, already_began)
    -- Log debug output of what we received
    if rpc.debug then
        if is_server then
            io.write("[RPC Server Request]" .. result .. "\n")
        else
            io.write("[RPC Receive]" .. result .. "\n")
        end
    end
    return result
end

--
-- Do a remote command
--
local function do_remote_command(remote, line)
    local meta = getmetatable(remote)
    local command
    repeat
        local status
        send_command(meta.stream, line)
        status, command = pcall(receive_command, meta.stream)
        if not status then
            print("ERROR:", command)
            command = nil
        end
    until command
    -- Convert the response to Lua data structures
    local len, r = do_unpack(remote, 1, command, false)
    -- Make sure we consumed all the input
    assert(len == #command+1)
    -- Returned unpack data so calls work right
    return table.unpack(r, 1, r.n)
end

--
-- Do a remote on a specific object
--
local function rpc_object_remote(self, command, ...)
    local meta = getmetatable(self)
    -- Cleanup any remote objects that have been garbage collected
    if #meta.need_cleanup > 0 then
        do_remote_command(self, "~" .. table.concat(meta.need_cleanup, "#"))
        meta.need_cleanup = {}
    end
    -- Build the command
    local line = command .. meta.getid(self) .. do_pack(...)
    -- Do the command and return the results
    return do_remote_command(self, line)
end

local function rpc_object_getid(self)
    local meta = getmetatable(self)
    return meta.remoteid[self]
end

local function rpc_object_call(self, ...)
    return rpc_object_remote(self, "c", ...)
end

local function rpc_object_index(self, key)
    return rpc_object_remote(self, "[", key)
end

local function rpc_object_setindex(self, key, value)
    rpc_object_remote(self, "=", key, value)
end

local function rpc_object_len(self)
    return rpc_object_remote(self, "#")
end

local function rpc_object_gc(self)
    local meta = getmetatable(self)
    local remoteid = meta.remoteid[self]
    table.insert(meta.need_cleanup, remoteid)
    meta.remoteid[self] = nil
end

--
-- Create a new local object representing a remote object
--
local function rpc_object_new(self, remoteid)
    local mymeta = getmetatable(self)
    local object = rpc_support.newproxy(self)
    mymeta.remoteid[object] = tostring(remoteid)
    return object
end

local function rpc_object_pairs(self)
    local g = rpc_object_new(self, 0)
    local p = rpc_object_remote(g, "[", "pairs")
    return rpc_object_remote(p, "c", self)
end

local function rpc_object_ipairs(self)
    local g = rpc_object_new(self, 0)
    local p = rpc_object_remote(g, "[", "ipairs")
    return rpc_object_remote(p, "c", self)
end

---
-- Create a new RPC connection to a remote rpc.serve
-- @param stream_name Can be a filename, TCP host, nil (stdin).
-- @return Returns a RPC object that represents the top level global environment of the remote system.
--
function rpc.connect(stream_name)
    local object = rpc_support.newproxy(true)
    local meta = getmetatable(object)
    -- Table used to track remote numeric IDs
    local m = {}
    m.__mode = "k"
    meta.remoteid = {}
    setmetatable(meta.remoteid, m)
    meta.remoteid[object] = "0"
    -- Table used to track objects to delete
    meta.need_cleanup = {}
    -- Methods for the remote object
    meta.new = rpc_object_new
    meta.getid = rpc_object_getid
    meta.__call = rpc_object_call
    meta.__index = rpc_object_index
    meta.__newindex = rpc_object_setindex
    meta.__len  = rpc_object_len
    meta.__gc = rpc_object_gc
    meta.__pairs = rpc_object_pairs
    meta.__ipairs = rpc_object_ipairs
    -- File handles for communications
    meta.stream = rpc_support.connect(stream_name)
    return object
end

--
-- Create a RPC server
--
local function rpc_serve(stream, only_one)
    -- We keep a table of all objects that remote connections have a ref_id
    -- to. We can't let these objects garbage collect until all references are
    -- gone. The objects table is accessed either by reference number or
    -- the actual object. The reference number returns the object. The object
    -- returns a tuple containing the ref_id and the reference count.
    if not rpc.objects then
        rpc.objects = {}
        rpc.objects[0] = _ENV
        rpc.objects[_ENV] = {0, 1}
    end
    repeat
        local status, full_command = pcall(receive_command, stream, only_one)
        if status and full_command then
            local command = full_command:sub(1,1)
            local obj = full_command:match("^%d+", 2)
            local line = full_command:sub(#obj + 2)
            obj = tonumber(obj)

            -- Convert the command into an object reference and arguments
            local object = rpc.objects[obj]
            local _, args = do_unpack(nil, 1, line, true)
            local result = {}
            result.n = 0

            if command == "c" then      -- Function call
                result = table.pack(object(table.unpack(args, 1, args.n)))
            elseif command == "[" then  -- Index to get table value
                result[1] = object[args[1]]
                result.n = 1
            elseif command == "=" then  -- Assignment of a table value
                if object == _G then
                    -- Strict might be loaded and not allow setting globals
                    -- Bypass it by using rawset
                    rawset(object, args[1], args[2])
                else
                    object[args[1]] = args[2]
                end
            elseif command == "#" then  -- Get the length of an object
                result[1] = #object
                result.n = 1
            elseif command == "~" then  -- Delete reference to object
                table.insert(args, obj)
                for _,obj in ipairs(args) do
                    local object = rpc.objects[obj]
                    local obj_info = rpc.objects[object]
                    obj_info[2] = obj_info[2] - 1
                    if (obj ~= 0) and (obj_info[2] == 0) then
                        -- All references are gone, allow garbage collection
                        rpc.objects[object] = nil
                        rpc.objects[obj] = nil
                    end
                end
            else
                error ("Illegal remote command " .. command)
            end
            line = rpc_support.server_do_pack(rpc.objects, table.unpack(result, 1, result.n))
            -- Write the response and flush it
            send_command(stream, line)
        end
    until only_one
end

---
-- Create a RPC server
-- @param only_one If true, then accept a single RPC command and return. Otherwise loop forever servicing RPC.
--
function rpc.serve(only_one)
    local stream = -1
    is_server = true
    local status, message = xpcall(rpc_serve, debug.traceback, stream, only_one)
    if not status then
        send_command(stream, "e" .. rpc_support.server_do_pack(rpc.objects, message))
    end
    is_server = false
end

--
-- Needed for compatibility with Lua 5.1
--
if rawget(table, "unpack") == nil then
    table.unpack = unpack
end

return rpc
