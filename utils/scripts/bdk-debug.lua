#!/usr/bin/env bdk-lua
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

--
-- Lua interactive debugger
-- Run without arguments for help
--

require("strict")
require("utils")
local debug = require("debug")
local readline = require("readline")

local GOTO_TOP      = "\27[1;1H"
local GOTO_BOTTOM   = "\27[100;1H"  -- ESC[1;1H begins output at the bottom of the terminal (actually line 100)
local ERASE_EOL     = "\27[0K"      -- Erase to end of line
local ERASE_EOS     = "\27[0J"      -- Erase to end screen
local ERASE_WIN     = "\27[2J"      -- Erase the window

local bdkdebug = {}

bdkdebug.stack_depth = 1    -- Example top of stack
bdkdebug.running = false    -- Stop the program by default
bdkdebug.breakpoints = {}   -- No breakpoints to begin with
bdkdebug.nest_level = 0     -- Nesting level used for step over
bdkdebug.step_over = false  -- Are we doing a step over
bdkdebug.stack_adjust = 0
bdkdebug.show_gui = true    -- Should the text base GUI be shown
bdkdebug.skip_list = {}     -- List of source files to skip through when debugging

local tab_complete = {"help", "h", "s", "n", "c", "b", "db", "bt", "p", "e", "up", "down", gui = {"on", "off"}, "where", "locals", "skip", "quit"}

--
-- Display comamnd line usage to the user
--
function bdkdebug.help()
    local message =
[[
Usage:
    bdk-debug <filename> [args...]

Execute the Lua script <filename> in an interactive debugger. The optional
arguments will be passed to the script.
]]
    print(message)
end

--
-- Return a array where each element is a string representing a function
-- on the call stack. Element 1 is the stack top
--
function bdkdebug.getstack()
    bdkdebug.stack_adjust = bdkdebug.stack_adjust + 1
    local stack_info = {}
    local sindex = 1
    while true do
        local info = debug.getinfo(sindex + bdkdebug.stack_adjust, "nSluf")
        if info == nil then
            break
        end
        local name = info.name
        if not name then
            name = "[unknown]"
        end
        local stack_label = "%s:%d %s" % {tostring(info.short_src), info.currentline, name}
        local nparams = info.nparams
        local param_sep = "("
        if nparams < 1 then
            stack_label = stack_label .. "("
        end
        for pindex = 1,nparams do
            local var, value = debug.getlocal(sindex + bdkdebug.stack_adjust, pindex)
            stack_label = "%s%s%s=%s" % {stack_label, param_sep, var, tostring(value)}
            param_sep = ", "
        end
        stack_label = stack_label .. ")"
        table.insert(stack_info, stack_label)
        sindex = sindex + 1
    end
    bdkdebug.stack_adjust = bdkdebug.stack_adjust - 1
    return stack_info
end

--
-- Get the source filename and line number for the function on the supplied
-- stack index
-- return filename, lineno
--
function bdkdebug.getsource(stack_depth)
    bdkdebug.stack_adjust = bdkdebug.stack_adjust + 1
    local info = debug.getinfo(stack_depth + bdkdebug.stack_adjust, "Sl")
    bdkdebug.stack_adjust = bdkdebug.stack_adjust - 1
    return tostring(info.short_src), info.currentline
end

--
-- Return a table of all local variables
-- result[1-n] = {name, value}
--
function bdkdebug.getlocals(stack_depth)
    bdkdebug.stack_adjust = bdkdebug.stack_adjust + 1
    local var_table = {name = {}, value = {}, index = {}}
    local info = debug.getinfo(stack_depth + bdkdebug.stack_adjust, "uf")
    for index = 1, info.nups do
        local var, value = debug.getupvalue(info.func, index)
        table.insert(var_table.name, var)
        table.insert(var_table.value, value)
        table.insert(var_table.index, -index)
    end
    for index = 1, 9999 do
        local var, value = debug.getlocal(stack_depth + bdkdebug.stack_adjust, index)
        if var == nil then
            break
        end
        if var:sub(1,1) ~= "(" then
            table.insert(var_table.name, var)
            table.insert(var_table.value, value)
            table.insert(var_table.index, index)
        end
    end
    bdkdebug.stack_adjust = bdkdebug.stack_adjust - 1
    return var_table
end

--
-- Display the debugger GUI
--
function bdkdebug.display(stack_depth)
    bdkdebug.stack_adjust = bdkdebug.stack_adjust + 1
    local WIDTH_LEFT    = 50
    local WIDTH_RIGHT   = 30
    local HEIGHT_TOP    = 4
    local HEIGHT_BOTTOM = 13
    local FORMAT_INVERT = "\27[7m"          -- Invert
    local FORMAT_NORMAL = "\27[0m"          -- Normal
    local FORMAT_NONE   = "\27[39m\27[49m"  -- Normal display
    local FORMAT_STACK  = "\27[37m\27[46m"  -- White on cyan
    local FORMAT_LOCALS = "\27[37m\27[42m"  -- White on green
    local FORMAT_SOURCE = "\27[37m\27[44m"  -- White on blue
    local FORMAT_BREAKPOINT = "\27[37m\27[41m"  -- White on red
    local FORMAT_HIGH   = "\27[1m"          -- Bold
    local FORMAT_STR    = "%s%-" .. WIDTH_LEFT .. "s%s%-" .. WIDTH_RIGHT .. "s" .. FORMAT_NORMAL .. ERASE_EOL .. "\n"
    local stack = bdkdebug.getstack()
    local source, lineno = bdkdebug.getsource(stack_depth)
    local vars = bdkdebug.getlocals(stack_depth)

    -- Convert the local variables into a lsit of strings for display
    local vars_str = {}
    for i = 1, #vars.name do
        local name = vars.name[i]
        local value = vars.value[i]
        local s = "%s = %s" % {name, tostring(value)}
        s = s:gsub("\27", "ESC"):gsub("\n", "\\n"):sub(1, WIDTH_RIGHT)
        table.insert(vars_str, s)
    end
    table.sort(vars_str)
    vars = vars_str

    -- Start at the top of the screen and print titles
    printf(GOTO_TOP .. FORMAT_INVERT)
    printf(FORMAT_STR, FORMAT_STACK, "Call Stack", FORMAT_LOCALS, "Local Variables")
    printf(FORMAT_NORMAL)
    -- Print the call stack and the first local variables
    local vindex = 1
    for row = 1, HEIGHT_TOP do
        local s = ""
        if stack[row] then
            s = stack[row]
        end
        local v = ""
        if vars[vindex] then
            v = vars[vindex]
            vindex = vindex + 1
        end
        s = s:sub(1, WIDTH_LEFT)
        if row == stack_depth then
            printf(FORMAT_STR, FORMAT_STACK .. FORMAT_HIGH, s, FORMAT_NORMAL .. FORMAT_LOCALS, v)
        else
            printf(FORMAT_STR, FORMAT_STACK, s, FORMAT_LOCALS, v)
        end
    end
    -- Print the source title and one local variable
    local v = ""
    if vars[vindex] then
        v = vars[vindex]
        vindex = vindex + 1
    end
    printf(FORMAT_INVERT)
    printf(FORMAT_STR, FORMAT_SOURCE, source .. ":" .. lineno, FORMAT_NORMAL .. FORMAT_LOCALS, v)
    -- Get the source file
    local source_lines = {}
    local inf = io.open(source, "r")
    if inf then
        for l in inf:lines() do
            table.insert(source_lines, l)
        end
        inf:close()
    end
    -- Print the source file and the rest of the locals
    for row = 1, HEIGHT_BOTTOM do
        local lno = lineno + row - HEIGHT_BOTTOM/2 - 1
        local s = ""
        -- Only show line if it is in the source file
        if (lno >= 1) and (lno <= #source_lines) then
            s = "%3d %s" % {lno, source_lines[lno]}
            s = s:sub(1, WIDTH_LEFT)
        end
        -- Figure out which local varaible needs to be displayed
        local v = ""
        if vars[vindex] then
            v = vars[vindex]
            vindex = vindex + 1
        end
        -- Figure out what color the source should be
        local format_source = FORMAT_SOURCE
        for _,b in ipairs(bdkdebug.breakpoints) do
            if (source == b[1]) and (lno == b[2]) then
            format_source  = FORMAT_BREAKPOINT
            end
        end
        -- Highlight the current execution line
        if lno == lineno then
            format_source  = format_source .. FORMAT_HIGH
        end
        printf(FORMAT_STR, format_source, s, FORMAT_NORMAL .. FORMAT_LOCALS, v)
    end
    -- Move back to the bottom of the screen
    printf(FORMAT_NONE .. GOTO_BOTTOM)
    bdkdebug.stack_adjust = bdkdebug.stack_adjust - 1
end

function do_commandline()
    bdkdebug.stack_adjust = bdkdebug.stack_adjust + 1
    -- Loop executing commands from the user
    while true do
        if bdkdebug.show_gui then
            -- Display the GUI
            bdkdebug.display(bdkdebug.stack_depth)
        end
        -- Ask for input
        local cmdline
        repeat
            cmdline = readline.readline("dbg> ", tab_complete, 0)
        until cmdline
        local cmd = cmdline:match("%g+")

        -- Process the command
        if cmd == "s" then
            -- Step into
            bdkdebug.stack_depth = 1
            bdkdebug.running = false
            bdkdebug.step_over = false
            return

        elseif (cmd == "n") or (cmd == nil) then
            -- Step over
            bdkdebug.stack_depth = 1
            bdkdebug.step_over = true
            bdkdebug.running = true
            bdkdebug.nest_level = 0
            return

        elseif cmd == "c" then
            -- Continue
            bdkdebug.stack_depth = 1
            bdkdebug.running = true
            return

        elseif cmd == "b" then
            -- Breakpoint command
            local arg = cmdline:match("%g+", 2)
            if arg == nil then
                for n,b in ipairs(bdkdebug.breakpoints) do
                    printf("Breakpoint%d: %s:%d\n", n, b[1], b[2])
                end
                print()
            elseif tonumber(arg) then
                local source, lineno = bdkdebug.getsource(bdkdebug.stack_depth)
                table.insert(bdkdebug.breakpoints, {source, tonumber(arg)})
            else
                local file, lno = arg:match("(%g+):(%d+)")
                lno = tonumber(lno)
                if file and lno then
                    table.insert(bdkdebug.breakpoints, {file, lno})
                else
                    print("Breakpoint syntax error. Must be \"file:line\".")
                end
            end

        elseif cmd == "db" then
            -- Delete breakpoint
            local arg = tonumber(cmdline:match("%g+", 3))
            if arg then
                table.remove(bdkdebug.breakpoints, arg)
            else
                print("Expected breakpoint number to delete")
            end

        elseif cmd == "bt" then
            local stack = bdkdebug.getstack()
            for r = 1,#stack do
                printf("Backtrace%d: %s\n", r, stack[r])
            end

        elseif cmd == "p" then
            local arg = cmdline:match("%g+", 2)
            local vars = bdkdebug.getlocals(bdkdebug.stack_depth)
            local found = false
            for i = 1,#vars.name do
                if vars.name[i] == arg then
                    printf("Variable: %s ", arg)
                    pprint(vars.value[i])
                    found = true
                    break
                end
            end
            if not found then
                local t = rawget(_G, arg)
                if t then
                    printf("Variable: %s ", arg)
                    pprint(t)
                else
                    print("Not a local or global variable")
                end
            end

        elseif cmd == "e" then
            -- Build a fake environment that can simulate the code running
            -- in the debug functions's context. This allows access to local
            -- and global variables.
            local vars = bdkdebug.getlocals(bdkdebug.stack_depth)
            local real_env = vars.value[1]
            local meta = {}
            meta.__index = function(table, name)
                -- search for the name in the list of locals
                for i = 1,#vars.name do
                    if vars.name[i] == name then
                        -- Return the local's value
                        return vars.value[i]
                    end
                end
                -- Not found, attempt to use a global
                return real_env[name]
            end
            meta.__newindex = function(table, name, value)
                -- search for the name in the list of locals
                for i = 1,#vars.name do
                    if vars.name[i] == name then
                        if vars.index[i] > 0 then
                            local n = debug.setlocal(bdkdebug.stack_depth + bdkdebug.stack_adjust + 3, vars.index[i], value)
                            assert(n == name, "Setting local %s mistakenly set %s" % {name, tostring(n)})
                            break
                        else
                            -- FIXME: Set the up values
                            error("Assignment to function up values not supported")
                        end
                    end
                end
                -- Not found, set a global. Use rawset to bypass strict
                rawset(real_env, name, value)
            end
            local env = {}
            setmetatable(env, meta)
            -- Compile the command line
            local arg = cmdline:sub(2)
            local result, message = loadin(env, arg, arg, "t")
            if not result then
                print(message)
            else
                -- Execute the command line
                result, message = pcall(result)
                if message then
                    print(message)
                end
            end

        elseif cmd == "up" then
            -- Move up the call stack
            bdkdebug.stack_depth = bdkdebug.stack_depth + 1

        elseif cmd == "down" then
            -- Move down the call stack
            bdkdebug.stack_depth = bdkdebug.stack_depth - 1
            if bdkdebug.stack_depth < 1 then
                bdkdebug.stack_depth = 1
            end

        elseif cmd == "gui" then
            local arg = cmdline:match("%g+", 4)
            if arg == "on" then
                bdkdebug.show_gui = true
            elseif arg == "off" then
                bdkdebug.show_gui = false
            else
                print("Expected argument \"on\" or \"off\"")
            end

        elseif  cmd == "where" then
            local source, lineno = bdkdebug.getsource(bdkdebug.stack_depth)
            printf("Stackframe: %d\n", bdkdebug.stack_depth)
            printf("File: %s\n", source)
            printf("Line: %d\n", lineno)

        elseif  cmd == "locals" then
            local vars = bdkdebug.getlocals(bdkdebug.stack_depth)
            for i = 1, #vars.name do
                printf("Local: %s %s\n", vars.name[i], tostring(vars.value[i]))
            end

        elseif  cmd == "skip" then
            -- Breakpoint command
            local arg = cmdline:match("%g+", 5)
            if arg then
                if arg == "-" then
                    arg = bdkdebug.getsource(bdkdebug.stack_depth)
                end
                local found = nil
                for n,f in ipairs(bdkdebug.skip_list) do
                    if arg == f then
                        found = n
                    end
                end
                if found then
                    table.remove(bdkdebug.skip_list, found)
                else
                    table.insert(bdkdebug.skip_list, arg)
                end
            else
                for n,f in ipairs(bdkdebug.skip_list) do
                    printf("Skip%d: %s\n", n, f)
                end
                print()
            end

        elseif cmd == "quit" then
            os.exit(true)

        elseif (cmd == "help") or (cmd == "h") then
            -- Help
            print("help             Show list of supported commands.")
            print("h                Shortcut for \"help\".")
            print("s                Step into.")
            print("n                Step over.")
            print("c                Continue execution.")
            print("b                Display all breakpoints.")
            print("b <line>         Insert breakpoint into the current file for <line>.")
            print("b <file>:<line>  Insert breakpoint into <file> for <line>.")
            print("db <num>         Delete breakpoint <num>. Use the index from the \"b\" command.")
            print("bt               Display a backtrace of the stack.")
            print("p <variable>     Print the value of a variable.")
            print("e <expression>   Execute the Lua expression.")
            print("up               Move up the call stack.")
            print("down             Move down the call stack.")
            print("gui on           Enable the text based GUI")
            print("gui off          Disable the text based GUI")
            print("where            Show the current stackframe, file, and line")
            print("locals           Show a list of all active local variables")
            print("skip             Display the files the debugger will skip.")
            print("skip <file>      Add/remove file to/from skip list.")
            print("skip -           Add/remove the current file to/from skip list.")
            print("quit             Quit the debugger.")
            print("An empty line is the same as \"n\".")
        else
            print("Illegal command")
        end
    end
end

--
-- The main debug hook
--
function bdkdebug.debughook(reason, lineno)
    bdkdebug.stack_adjust = 1
    -- Handle step over nesting. FIXME: This doesn't work if an exception happens
    if reason == "call" then
        local info = debug.getinfo(2, "t")
        if not info.istailcall then
            bdkdebug.nest_level = bdkdebug.nest_level + 1
        end
        return
    elseif reason == "return" then
        bdkdebug.nest_level = bdkdebug.nest_level - 1
        return
    end
    -- Get the current debug source and lineno
    local source, lineno = bdkdebug.getsource(1)
    -- Return if we're trying to debug something that should be skipped
    for _,skip_file in ipairs(bdkdebug.skip_list) do
        if skip_file == source then
            return
        end
    end
    -- Stop for step over
    if bdkdebug.step_over and (bdkdebug.nest_level <= 0) then
        bdkdebug.step_over = false
        bdkdebug.running = false
    end
    -- Check if we've hit any breakpoints
    for _,b in ipairs(bdkdebug.breakpoints) do
        if (source == b[1]) and (lineno == b[2]) then
            printf("Break at %s:%d\n", source, lineno)
            bdkdebug.running = false
            break
        end
    end
    -- Check if the user hit Control-C
    if rawget(_G, "debug_interrupt") then
        bdkdebug.running = false
        rawset(_G, "debug_interrupt", false)
    end
    -- Continue if we should be running
    if bdkdebug.running then
        return
    end
    do_commandline()
end

function bdkdebug.errorhook(message)
    -- Disconnect the debugger, program is dead
    debug.sethook()
    bdkdebug.stack_adjust = 1
    print("Error: " .. tostring(message))
    do_commandline()
    return debug.traceback(message)
end

--
-- Main function for the debugger
--
function bdkdebug.main()
    -- Look for our one option to disable the GUI. This is
    -- used by SciTE to remotely control the debugger
    if #arg >= 1 then
        if arg[1] == "-nogui" then
            bdkdebug.show_gui = false
            table.remove(arg, 1)
        end
    end

    -- Show help if required argument not there
    if #arg < 1 then
        return bdkdebug.help()
    end

    -- Add the debugger's source to the skip list. Most people
    -- aren't interested in debugging the debugger.
    local my_source = bdkdebug.getsource(0)
    table.insert(bdkdebug.skip_list, my_source)

    -- Clear the screen and start debugging
    --printf(ERASE_WIN .. GOTO_BOTTOM)
    rawset(_G, "debug_interrupt", false)
    debug.sethook(bdkdebug.debughook, "crl")
    -- Execute the user's file
    local filename = arg[1]
    table.remove(arg, 1)
    local status, result = xpcall(dofile, bdkdebug.errorhook, filename)
    if not status then
        print("ERROR:", result)
    end
    -- Disconnect the debugger
    debug.sethook()
    print("Program terminated")
end

bdkdebug.main()
