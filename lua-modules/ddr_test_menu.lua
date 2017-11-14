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

-- BDK DRAM test menu.
-- Displays the GUI interface for configuring and testing DRAM.
require("strict")
require("utils")
require("menu")
local bit64 = require("bit64")

local range_repeat = 1
local range_start = 0
local range_length = -1
local test_flags = 0

local function toggle_abort_on_error()
    test_flags = bit64.bxor(test_flags, cavium.DRAM_TEST_NO_STOP_ERROR)
end

local function toggle_batch_mode()
    test_flags = bit64.bxor(test_flags, cavium.DRAM_TEST_NO_PROGRESS)
end

local function toggle_use_ccpi()
    test_flags = bit64.bxor(test_flags, cavium.DRAM_TEST_USE_CCPI)
end

local function set_range_repeat()
    local count = menu.prompt_number("Number of times to repeat the test, or -1 for infinite", range_repeat)
    if (count < -1) or (count == 0) then
        print("Invalid repeat count")
    else
        range_repeat = count
    end
end

local function set_range_start()
    local start_address = menu.prompt_number("Physical byte address to start memory test at", range_start)
    if start_address < 0 then
        print("Invalid start address")
    else
        range_start = start_address
    end
end

local function set_range_length()
    local length = menu.prompt_number("Length of region in bytes, or -1 for all of memory", range_length)
    if length < -1 then
        print("Invalid length")
    else
        range_length = length
    end
end

local function run_one_test(test_number, show_result)
    local length = range_length
    if length == -1 then
        length = 0x10000000000
    end
    local errors = cavium.c.bdk_dram_test(test_number, range_start, length, test_flags)
    if show_result then
        if errors == 0 then
            printf("Test passed\n")
        else
            printf("Test reported %d errors\n", errors)
        end
    end
    return errors
end

local function run_all_tests()
    local errors = 0
    local start_time = os.time()
    for test_number=0,100 do
	local one_errors = 0
        local name = cavium.c.bdk_dram_get_test_name(test_number);
        if not name then
            break
        end
        one_errors = run_one_test(test_number, false)
	errors = errors + one_errors
        if (one_errors ~= 0) and not bit64.btest(test_flags, cavium.DRAM_TEST_NO_STOP_ERROR) then
	    break
        end
    end
    local end_time = os.time()
    if errors == 0 then
        local total_time = os.difftime(end_time, start_time)
        local hour = total_time / 3600
        local min = (total_time % 3600) / 60
        local sec = (total_time % 3600) % 60
        printf("All tests passed (time %02d:%02d:%02d)\n", hour, min, sec)
    else
        printf("Tests reported %d errors\n", errors)
    end
    return errors
end

local function run_special_tests()
    local errors = 0
    local start_time = os.time()
    local special_tests = { 2, 3, 4, 12 }
    for _,test_number in ipairs(special_tests)  do
	local one_errors = 0
        local name = cavium.c.bdk_dram_get_test_name(test_number);
        if not name then
            break
        end
        one_errors = run_one_test(test_number, false)
	errors = errors + one_errors
        if (one_errors ~= 0) and not bit64.btest(test_flags, cavium.DRAM_TEST_NO_STOP_ERROR) then
	    break
        end
    end
    local end_time = os.time()
    if errors == 0 then
        local total_time = os.difftime(end_time, start_time)
        local hour = total_time / 3600
        local min = (total_time % 3600) / 60
        local sec = (total_time % 3600) % 60
        printf("All tests passed (time %02d:%02d:%02d)\n", hour, min, sec)

    else
        printf("Tests reported %d errors\n", errors)
    end
    return errors
end

local function do_test(test_func, arg, show_errors)
    local total = range_repeat
    if total == -1 then
        total = 0x7fffffffffffffff
    end
    local start_time = os.time()
    local sum_errors = 0
    local pass = 1
    for count=1,total do
        pass = count
        if range_repeat == -1 then
            printf("Pass %d\n", count)
        else
            printf("Pass %d of %d\n", count, total)
        end
        local errors = test_func(arg, show_errors)
	sum_errors = sum_errors + errors
        -- print running summary if more than 1 pass was to be made and there have been errors
        if (count < total) and (sum_errors ~= 0) then
            printf("Testing has run %d passes with %d total errors\n", count, sum_errors)
        end
        local end_time = os.time()
        local total_time = os.difftime(end_time, start_time)
        local hour = total_time / 3600
        local min = (total_time % 3600) / 60
        local sec = (total_time % 3600) % 60
        printf("Total time %02d:%02d:%02d\n", hour, min, sec)
        if (errors ~= 0) and not bit64.btest(test_flags, cavium.DRAM_TEST_NO_STOP_ERROR) then
            break
        end
    end
    -- always print final summary if more than 1 pass was to be made
    if total > 1 then
        printf("Test ran %d passes with %d total errors\n", pass, sum_errors)
    end
end

local function inject_error(double_bit)
    local address = menu.prompt_number("Physical byte address to inject error at", range_start)
    local bit = -1
    if not double_bit then
        bit = menu.prompt_number("Bit position to enject error at", 0, 0, 7)
    end
    cavium.c.bdk_dram_test_inject_error(address, bit)
end

repeat
    local info = cavium.c.bdk_dram_get_info_string(menu.node);
    local m = menu.new("DRAM Test Menu - %s" % info)
    m:item("cores", "Bringup Cores for multi-core testing (%d)" % cavium.c.bdk_get_num_running_cores(menu.node),
           cavium.c.bdk_init_nodes, 0, 0)
    if range_repeat == -1 then
        m:item("repeat", "Number of times to repeat the test (Forever)" % range_repeat, set_range_repeat)
    else
        m:item("repeat", "Number of times to repeat the test (%d)" % range_repeat, set_range_repeat)
    end
    m:item("start", "Starting address (0x%x)" % range_start, set_range_start)
    if range_length == -1 then
        m:item("length", "Length of the range to check (All)" % range_length, set_range_length)
    else
        m:item("length", "Length of the range to check (0x%x)" % range_length, set_range_length)
    end
    m:item("64MB", "Set test range from 64MB to 128MB", function()
        range_start = 0x4000000
        range_length = 0x4000000
    end)
    m:item("all", "Run all DRAM tests", do_test, run_all_tests, nil)
    for test_number=0,100 do
        local name = cavium.c.bdk_dram_get_test_name(test_number);
        if not name then
            break
        end
        m:item("test%d" % test_number, name, do_test, run_one_test, test_number, true)
    end
    m:item("spec", "Run special DRAM tests", do_test, run_special_tests, nil)

    if bit64.btest(test_flags, cavium.DRAM_TEST_NO_STOP_ERROR) then
        m:item("abort", "Abort on Errors (Currently OFF)", toggle_abort_on_error)
    else
        m:item("abort", "Abort on Errors (Currently ON)", toggle_abort_on_error)
    end

    if bit64.btest(test_flags, cavium.DRAM_TEST_NO_PROGRESS) then
        m:item("batch", "Batch mode (Currently ON)", toggle_batch_mode)
    else
        m:item("batch", "Batch mode (Currently OFF)", toggle_batch_mode)
    end

    if cavium.c.bdk_numa_is_only_one() == 0 then
        if bit64.btest(test_flags, cavium.DRAM_TEST_USE_CCPI) then
            m:item("ccpi", "Use CCPI cross node (Currently ON)", toggle_use_ccpi)
        else
            m:item("ccpi", "Use CCPI cross node (Currently OFF)", toggle_use_ccpi)
        end
    end
    m:item("inject_s", "Inject a single bit memory error", inject_error, false)
    m:item("inject_d", "Inject a double bit memory error", inject_error, true)
    m:item("quit", "Main menu")
until m:show() == "quit"

