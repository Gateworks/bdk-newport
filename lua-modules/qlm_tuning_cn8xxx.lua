-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK QLM menu.
-- Displays the GUI interface for accessing QLM settings.
require("strict")
require("utils")
require("menu")
local bit64 = require("bit64")
local readline = require("readline")

local TUNING_TX_PRE_MIN = 0
local TUNING_TX_PRE_MAX = 10
local TUNING_TX_MAIN_MIN = 0
local TUNING_TX_MAIN_MAX = 25
local TUNING_TX_POST_MIN = 0
local TUNING_TX_POST_MAX = 15

local qlm_tuning = {}
qlm_tuning.qlm = 0                  -- Active QLM for tuning and menu items
qlm_tuning.stop_on_error = false    -- True if display should stop on first error
qlm_tuning.repeat_rx_errors = false -- True if TX should inject an error for every RX error received
qlm_tuning.runtime = -1             -- Time to run pattern, -1 for infinite
qlm_tuning.last_error = {}          -- Used to store error counts when using repeat_rx_errors

-- Prompt for which QLM/DLM to edit
local function select_qlm()
    local num_qlms = octeontx.c.bdk_qlm_get_num(menu.node)
    qlm_tuning.qlm = menu.prompt_number("QLM/DLM", qlm_tuning.qlm, 0, num_qlms-1)
    return qlm_tuning.qlm
end

-- Prompt for which lane to edit
local function select_lane(qlm_num, allow_all)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
    local default = allow_all and -1 or 0
    local lane
    if allow_all then
        lane = menu.prompt_number("QLM/DLM Lane, or -1 for all", default, -1, num_lanes-1)
    else
        lane = menu.prompt_number("QLM/DLM Lane", default, 0, num_lanes-1)
    end
    return lane
end

-- Select a list of QLMs to perform operations on
local function select_qlm_list(qlm_list)
    local num_qlms = octeontx.c.bdk_qlm_get_num(menu.node)
    -- Default to all QLMs if the list wasn't supplied
    if not qlm_list then
        qlm_list = {}
        for qlm_num=0,num_qlms-1 do
            table.insert(qlm_list, qlm_num)
        end
    end
    -- Convert the default list to a string
    local s = ""
    for _,qlm_num in ipairs(qlm_list) do
        assert((qlm_num >= 0) and (qlm_num < num_qlms), "Invalid QLM/DLM number")
        s = s .. "," .. tostring(qlm_num)
    end
    -- Remove the extra ","
    s = s:sub(2)
    -- Ask the user
    s = menu.prompt_string("List of QLM/DLM to use", s)
    qlm_list = {}
    for w in string.gmatch(s, "%d+") do
        local qlm_num = tonumber(w)
        assert((qlm_num >= 0) and (qlm_num < num_qlms), "Invalid QLM/DLM number")
        table.insert(qlm_list, qlm_num)
    end
    return qlm_list
end

-- Polarity swap P/N on all lanes of QLMs
local function do_polarity_swap()
    local qlm_list = select_qlm_list()
    for _,qlm in pairs(qlm_list) do
        local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
        for lane=0,num_lanes-1 do
            local v = octeontx.csr[menu.node].GSERX_LANEX_RX_CFG_0(qlm,lane).cfg_rx_pol_invert
            v = (v == 1) and 0 or 1
            octeontx.csr[menu.node].GSERX_LANEX_RX_CFG_0(qlm,lane).cfg_rx_pol_invert = v
        end
    end
end

-- Start PRBS on a list of QLMs
local function start_prbs(mode, qlm_list)
    -- Start PRBS on the QLMs.
    for _,qlm_num in ipairs(qlm_list) do
        octeontx.c.bdk_qlm_enable_prbs(menu.node, qlm_num, mode, 1)
    end
    -- Let TX run for 1ms before starting RX
    octeontx.c.bdk_wait_usec(1000)
    for _,qlm_num in ipairs(qlm_list) do
        octeontx.c.bdk_qlm_enable_prbs(menu.node, qlm_num, mode, 2)
    end
end

---
--- Called by PRBS code when the user selects to inject errors into TX
--- for every RX error received
---
local function do_repeat_rx_errors(node, qlm, lane, total_errors)
    if qlm_tuning.last_error[qlm] == nil then
        qlm_tuning.last_error[qlm] = {}
    end
    if qlm_tuning.last_error[qlm][lane] == nil then
        qlm_tuning.last_error[qlm][lane] = 0
    end
    local err = total_errors - qlm_tuning.last_error[qlm][lane]
    while err > 0 do
        octeontx.c.bdk_qlm_inject_prbs_error(node, qlm, lane)
        err = err - 1
    end
    qlm_tuning.last_error[qlm][lane] = total_errors
end

--
-- Run PRBS on all QLMs
--
local function do_prbs(mode)
    -- Ask the user which QLMs to run
    local qlm_list = select_qlm_list()
    -- Ask how long to run for
    qlm_tuning.runtime = menu.prompt_number("Runtime in seconds (-1 for infinite)", qlm_tuning.runtime)
    -- Should we stop on errors?
    qlm_tuning.stop_on_error = menu.prompt_yes_no("Stop on error", qlm_tuning.stop_on_error)
    -- Should we echo out and RX errors with a TX error injection
    qlm_tuning.repeat_rx_errors = menu.prompt_yes_no("Inject TX error for every RX error", qlm_tuning.repeat_rx_errors)

    local function output_line(qlm_base, label, get_value)
        printf("%21s", label)
        local qlm_max = qlm_base + 2
        if qlm_max >= #qlm_list then
            qlm_max = #qlm_list
        end
        for qlm_index = qlm_base,qlm_max do
            local qlm_num = qlm_list[qlm_index]
            local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
            for lane=0, num_lanes-1 do
                local v = get_value(qlm_num, lane)
                if lane == 0 then
                    printf("|%10s", tostring(v))
                else
                    printf(" %10s", tostring(v))
                end
            end
        end
        printf("|\n")
    end
    -- Display PRBS status on the console. Returns true if any errors were seen,
    -- false if there were no errors
    local function display_status(run_time)
        local has_error = false
        printf("\n\n")
        printf("Time: %d seconds (Press 'Q' to quit patterns, 'E' to inject an error, 'C' to clear errors,\n", run_time / 1000000)
        printf("                  'X' to exit output and leave the pattern generators running,\n")
        printf("                  '0' - '3' to display the eye diagram for the lane on QLM %d)\n", qlm_tuning.qlm)
        for qlm_base=1,#qlm_list,3 do
            output_line(qlm_base, "", function(qlm, lane)
                return (lane == 0) and ("--- QLM " .. qlm) or "----------"
            end)
            output_line(qlm_base, "", function(qlm, lane)
                return "Lane " .. lane
            end)
            output_line(qlm_base, "Errors", function(qlm, lane)
                local v = octeontx.c.bdk_qlm_get_prbs_errors(menu.node, qlm, lane, false)
                if v == -1 then
                    return "No Lock"
                else
                    if qlm_tuning.repeat_rx_errors then
                        do_repeat_rx_errors(menu.node, qlm, lane, v)
                    end
                    if v ~= 0 then
                        has_error = true
                    end
                    if v < 1000000 then
                        return v
                    elseif v < 1000000000 then
                        return tostring(v / 1000000) .. "M"
                    else
                        return tostring(v / 1000000000) .. "B"
                    end
                end
            end)
            output_line(qlm_base, "Error Rate", function(qlm, lane)
                local qlm_speed = octeontx.c.bdk_qlm_get_gbaud_mhz(menu.node, qlm, 0)
                local v = octeontx.c.bdk_qlm_get_prbs_errors(menu.node, qlm, lane, false)
                if v == -1 then
                    return "-"
                else
                    -- Calculate the error rate as a fraction of the bits
                    -- transmitted
                    local total_bits = qlm_speed * run_time / 1000000
                    if total_bits == 0 then
                        total_bits = 1
                    end
                    local rate_exponent = -6 -- Since qlm_speed is in Mbps
                    local rate
                    -- If no errors then act like the next bit is an error
                    -- This way we always can calculate an error rate
                    if v == 0 then
                        v = 1
                    end
                    -- Scale v such that integer division will give decent results
                    while v < total_bits * 100 do
                        rate_exponent = rate_exponent - 1
                        v = v * 10
                    end
                    -- Calculate the error rate
                    rate = v / total_bits
                    -- Scale the error rate to be three digits
                    while rate >= 1000 do
                        rate_exponent = rate_exponent + 1
                        rate = rate / 10
                    end
                    while rate < 100 do
                        rate_exponent = rate_exponent - 1
                        rate = rate * 10
                    end
                    -- Convert the three digit error rate into scientific notation
                    return "%d.%02dE%d" % {rate/100, rate%100, rate_exponent + 2}
                end
            end)
            output_line(qlm_base, "", function(qlm, lane)
                return "----------"
            end)
            printf("\n")
        end
        return has_error
    end

    local DISPLAY_INTERVAL = 5000000
    if octeontx.is_platform(octeontx.PLATFORM_EMULATOR) then
        DISPLAY_INTERVAL = 1000 -- 1ms
    end
    printf("Running. Statistics shown every %d seconds\n", DISPLAY_INTERVAL / 1000000)
    start_prbs(mode, qlm_list)

    local start_time = octeontx.time_us()
    local next_print = start_time + DISPLAY_INTERVAL
    local end_time = 0x7fffffffffffffff
    if qlm_tuning.runtime ~= -1 then
        end_time = start_time + qlm_tuning.runtime * 1000000
    end
    local key
    repeat
        local t = octeontx.time_us()
        -- Periodically show the PRBS error counter and other status fields.
        if (t >= next_print) or (t >= end_time) then
            local has_error = display_status(t - start_time)
            if has_error and qlm_tuning.stop_on_error then
                print("Stopping on error")
                break
            end
            if t >= end_time then
                -- End time reached
                break
            end
            next_print = next_print + DISPLAY_INTERVAL
        end
        key = readline.getkey()
        if (key == 'e') or (key == 'E') then
            print("Injecting error into bit stream")
            for _,qlm_num in ipairs(qlm_list) do
                local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
                for lane=0, num_lanes-1 do
                    octeontx.c.bdk_qlm_inject_prbs_error(menu.node, qlm_num, lane)
                end
            end
        end
        if (key == 'c') or (key == 'C') then
            print("Clearing error counts")
            for _,qlm_num in ipairs(qlm_list) do
                local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
                for lane=0, num_lanes-1 do
                    octeontx.c.bdk_qlm_get_prbs_errors(menu.node, qlm_num, lane, true)
                end
            end
            start_time = octeontx.time_us()
        end
        if key and (key >= '0') and (key <= '3') then
            local lane = tonumber(key)
            local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_tuning.qlm)
            if lane < num_lanes then
                octeontx.c.bdk_qlm_eye_display(menu.node, qlm_tuning.qlm, lane, 1, nil)
            end
        end
    until (key == 'x') or (key == 'X') or (key == 'q') or (key == 'Q')

    -- Stop the pattern generator unless the user specifically wants it to
    -- continue (X or x)
    if (key ~= 'x') and (key ~= 'X') then
        print("Stopping pattern generator")
        for _,qlm_num in ipairs(qlm_list) do
            local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
            for lane=0, num_lanes-1 do
                octeontx.c.bdk_qlm_disable_prbs(menu.node, qlm_num)
            end
        end
    else
        print("Leaving pattern generator running")
    end
end

local function tuning_tx_eq(qlm)
    local qlm_lane = select_lane(qlm_tuning.qlm, true)
    local tx_pre = nil
    local tx_main = nil
    local tx_post = nil
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        if (qlm_lane == -1) or (qlm_lane == lane) then
            octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
            tx_pre = menu.prompt_number("New setting for pre-cursor emphasis", tx_pre, TUNING_TX_PRE_MIN, TUNING_TX_PRE_MAX)
            tx_main = menu.prompt_number("New setting for cursor swing", tx_main, TUNING_TX_MAIN_MIN, TUNING_TX_MAIN_MAX)
            tx_post = menu.prompt_number("New setting for post-cursor emphasis", tx_post, TUNING_TX_POST_MIN, TUNING_TX_POST_MAX)
            octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, tx_main, tx_pre, tx_post, -1, -1);
            octeontx.c.bdk_qlm_rx_equalization(menu.node, qlm, lane)
        end
    end
end

local function tuning_set_pre(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
    end
    local csr_setting = menu.prompt_number("New setting for pre-cursor emphasis", nil, TUNING_TX_PRE_MIN, TUNING_TX_PRE_MAX)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, -1, csr_setting, -1, -1, -1);
    end
    octeontx.c.bdk_qlm_rx_equalization(menu.node, qlm, -1)
end

local function tuning_set_post(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
    end
    local csr_setting = menu.prompt_number("New setting for post-cursor emphasis", nil, TUNING_TX_POST_MIN, TUNING_TX_POST_MAX)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, -1, -1, csr_setting, -1, -1);
    end
    octeontx.c.bdk_qlm_rx_equalization(menu.node, qlm, -1)
end

local function tuning_set_swing(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
    end
    local csr_setting = menu.prompt_number("New setting for cursor swing", nil, TUNING_TX_MAIN_MIN, TUNING_TX_MAIN_MAX)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, csr_setting, -1, -1, -1, -1);
    end
    octeontx.c.bdk_qlm_rx_equalization(menu.node, qlm, -1)
end

local function tuning_set_gain(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
    end
    local csr_setting = menu.prompt_number("New setting for PCS_SDS_TX_GAIN", nil, 0, 7)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, -1, -1, -1, csr_setting, -1);
    end
    octeontx.c.bdk_qlm_rx_equalization(menu.node, qlm, -1)
end

local function tuning_set_vboost(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
    end
    local csr_setting = menu.prompt_number("New setting for CFG_TX_VBOOST_EN", nil, 0, 1)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, -1, -1, -1, -1, csr_setting);
    end
    octeontx.c.bdk_qlm_rx_equalization(menu.node, qlm, -1)
end

function qlm_tuning.display_tuning_state(node, qlm, lane)
    octeontx.c.bdk_qlm_display_settings(node, qlm, lane, true, true)
end

local function manual_rx_evaluation(qlm)
    octeontx.c.bdk_qlm_rx_equalization(menu.node, qlm, -1)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_tuning.qlm)
    for lane=0, num_lanes-1 do
        qlm_tuning.display_tuning_state(menu.node, qlm, lane)
    end
end

--
-- Display SERDES state
--
local function display_state(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_tuning.qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, true)
    end
end

local function do_custom(mode)
    local pattern = menu.prompt_number("10 bit pattern", 0x155, 0, 0x3ff)
    do_prbs(pattern * 256 + mode)
end

local function do_eye()
    local lane = select_lane(qlm_tuning.qlm, false)
    octeontx.c.bdk_qlm_eye_display(menu.node, qlm_tuning.qlm, lane, 1, nil)
end

local function do_loopback()
    local m = menu.new("Loopback Type")
    m:item("none", "No loopback", octeontx.c.bdk_qlm_enable_loop, menu.node, qlm_tuning.qlm, octeontx.QLM_LOOP_DISABLED)
    m:item("core", "Core loopback, TX to RX in digital domain", octeontx.c.bdk_qlm_enable_loop, menu.node, qlm_tuning.qlm, octeontx.QLM_LOOP_CORE)
    m:item("quit",   "No change")
    m:show()
end

-- Main menu
function qlm_tuning.run()
    local m = menu.new("PRBS and SERDES Tuning Menu")
    repeat
        local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_tuning.qlm)
        local current_qlm = (num_lanes == 2) and "DLM" or "QLM"
        current_qlm = current_qlm .. qlm_tuning.qlm
        m:item("qlm",    "Select active QLM/DLM (Currently %s)" % current_qlm, select_qlm)
        m:item("down",   "Reset and power down %s" % current_qlm, octeontx.c.bdk_qlm_reset, menu.node, qlm_tuning.qlm)
        m:item("invert", "Polarity swap receive P/N on %s" % current_qlm, do_polarity_swap)
        m:item("prbs7",  "PRBS-7", do_prbs, 7)
        m:item("prbs11", "PRBS-11", do_prbs, 11)
        m:item("prbs15", "PRBS-15", do_prbs, 15)
        m:item("prbs16", "PRBS-16", do_prbs, 16)
        m:item("prbs23", "PRBS-23", do_prbs, 23)
        m:item("prbs31", "PRBS-31", do_prbs, 31)
        m:item("fixedw", "Fixed 10 bit word (PAT)", do_custom, 0x8)
        m:item("dc-bal", "DC-balanced word (PAT, ~PAT)", do_custom, 0x9)
        m:item("fixedp", "Fixed pattern (000, PAT, 3ff, ~PAT)", do_custom, 0xa)
        m:item("txeq",   "Set %s TX Equalization settings per lane" % current_qlm, tuning_tx_eq, qlm_tuning.qlm)
        m:item("swing",  "Set %s TX Cursor swing" % current_qlm, tuning_set_swing, qlm_tuning.qlm)
        m:item("pre",    "Set %s TX Pre-cursor emphasis" % current_qlm, tuning_set_pre, qlm_tuning.qlm)
        m:item("post",   "Set %s TX Post-cursor emphasis" % current_qlm, tuning_set_post, qlm_tuning.qlm)
        m:item("gain",   "Set %s TX Gain" % current_qlm, tuning_set_gain, qlm_tuning.qlm)
        m:item("vboost", "Set %s TX VBoost" % current_qlm, tuning_set_vboost, qlm_tuning.qlm)
        m:item("rx_eval","Perform a RX equalization evaluation on %s" % current_qlm, manual_rx_evaluation, qlm_tuning.qlm)
        m:item("disp",   "Display SERDES state of %s" % current_qlm, display_state, qlm_tuning.qlm)
        m:item("loop",   "Change loopback mode on %s" % current_qlm, do_loopback)
        m:item("eye",    "Display Eye", do_eye)

        m:item("quit",   "Main menu")
    until (m:show() == "quit")
end

return qlm_tuning
