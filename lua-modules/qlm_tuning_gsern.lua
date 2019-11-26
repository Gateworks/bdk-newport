-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK QLM tuning menu for CN9XXX.
-- Displays the GUI interface for accessing QLM settings.
require("strict")
require("utils")
require("menu")
local bit64 = require("bit64")
local readline = require("readline")

-- The rules for programming the transmitter equalizer taps are (all
-- values in decimal):
-- [TX_CMAIN] + [TX_CPRE] + [TX_CPOST] <= 48
-- [TX_CMAIN] - [TX_CPRE] - [TX_CPOST] >= 6
-- 48 >= [TX_CMAIN] >= 24
-- 16 >= [TX_CPRE] >= 0
-- 16 >= [TX_CPOST] >= 0
local TUNING_TX_PRE_MIN = 0
local TUNING_TX_PRE_MAX = 16
local TUNING_TX_MAIN_MIN = 24
local TUNING_TX_MAIN_MAX = 48
local TUNING_TX_POST_MIN = 0
local TUNING_TX_POST_MAX = 16
local TUNING_TX_BS_MIN = 0
local TUNING_TX_BS_MAX = 63

local qlm_tuning = {}
qlm_tuning.qlm = 0                  -- Active QLM for tuning and menu items
qlm_tuning.stop_on_error = false    -- True if display should stop on first error
qlm_tuning.repeat_rx_errors = false -- True if TX should inject an error for every RX error received
qlm_tuning.runtime = -1             -- Time to run pattern, -1 for infinite
qlm_tuning.show_phy_host = true     -- Show PRBS for PHY host side
qlm_tuning.show_phy_line = true     -- Show PRBS for PHY line side
qlm_tuning.last_error = {}          -- Used to store error counts when using repeat_rx_errors

--
-- Prompt for which QLM/DLM to edit
--
local function select_qlm()
    local num_qlms = octeontx.c.bdk_qlm_get_num(menu.node)
    qlm_tuning.qlm = menu.prompt_number("QLM/DLM", qlm_tuning.qlm, 0, num_qlms-1)
    return qlm_tuning.qlm
end

--
-- Prompt for which lane to edit
--
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

--
-- Select a list of QLMs to perform operations on
--
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

local function netphy_get(qlm, lane)
    if octeontx.c.bdk_netphy_get_handle then
        return octeontx.c.bdk_netphy_get_handle(menu.node, qlm, lane)
    else
        return 0
    end
end

--
-- Start PRBS on a list of QLMs
--
local function start_prbs(mode, qlm_list, pat0, pat1)
    -- Program the pattern if needed
    if mode == 0 then
        for _,qlm_num in ipairs(qlm_list) do
            local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
            for lane=0, num_lanes-1 do
                octeontx.csr[menu.node].GSERNX_LANEX_PATX(qlm_num, lane, 0).write(pat0)
                octeontx.csr[menu.node].GSERNX_LANEX_PATX(qlm_num, lane, 1).write(pat1)
            end
        end
    end
    -- Start PRBS on the QLMs.
    qlm_tuning.show_phy_host = true
    qlm_tuning.show_phy_line = true
    for _,qlm_num in ipairs(qlm_list) do
        octeontx.c.bdk_qlm_enable_prbs(menu.node, qlm_num, mode, 1)
        local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
        for lane=0, num_lanes-1 do
            local phy = netphy_get(qlm_num, lane);
            if phy ~= 0 then
                if qlm_tuning.show_phy_host then
                    if octeontx.c.bdk_netphy_enable_prbs(phy, true, mode, 1) ~= 0 then
                        qlm_tuning.show_phy_host = false
                    end
                end
                if qlm_tuning.show_phy_host then
                    if octeontx.c.bdk_netphy_enable_prbs(phy, false, mode, 1) ~= 0 then
                        qlm_tuning.show_phy_line = false
                    end
                end
            end
        end
    end
    -- Let TX run for 1ms before starting RX
    octeontx.c.bdk_wait_usec(1000)
    for _,qlm_num in ipairs(qlm_list) do
        octeontx.c.bdk_qlm_enable_prbs(menu.node, qlm_num, mode, 2)
        local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
        for lane=0, num_lanes-1 do
            local phy = netphy_get(qlm_num, lane);
            if phy ~= 0 then
                if qlm_tuning.show_phy_host then
                    if octeontx.c.bdk_netphy_enable_prbs(phy, true, mode, 2) ~= 0 then
                        qlm_tuning.show_phy_host = false
                    end
                end
                if qlm_tuning.show_phy_host then
                    if octeontx.c.bdk_netphy_enable_prbs(phy, false, mode, 2) ~= 0 then
                        qlm_tuning.show_phy_line = false
                    end
                end
            end
        end
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
    local pat0 = 0
    local pat1 = 0
    if mode == 0 then
        pat0 = menu.prompt_number("Pattern 0", 0)
        pat1 = menu.prompt_number("Pattern 1", 0)
    end
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
            if qlm_tuning.show_phy_host then
                output_line(qlm_base, "PHY Host Errors", function(qlm, lane)
                    local phy = netphy_get(qlm, lane)
                    if phy == 0 then
                        return ""
                    end
                    local v = octeontx.c.bdk_netphy_get_prbs_errors(phy, true, lane, false)
                    if v == -1 then
                        return "No Lock"
                    else
                        if v < 1000000 then
                            return v
                        elseif v < 1000000000 then
                            return tostring(v / 1000000) .. "M"
                        else
                            return tostring(v / 1000000000) .. "B"
                        end
                    end
                end)
            end
            if qlm_tuning.show_phy_line then
                output_line(qlm_base, "PHY Line Errors", function(qlm, lane)
                    local phy = netphy_get(qlm, lane)
                    if phy == 0 then
                        return ""
                    end
                    local v = octeontx.c.bdk_netphy_get_prbs_errors(phy, false, lane, false)
                    if v == -1 then
                        return "No Lock"
                    else
                        if v < 1000000 then
                            return v
                        elseif v < 1000000000 then
                            return tostring(v / 1000000) .. "M"
                        else
                            return tostring(v / 1000000000) .. "B"
                        end
                    end
                end)
            end
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
    start_prbs(mode, qlm_list, pat0, pat1)

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
                    local phy = netphy_get(qlm_num, lane);
                    if (phy ~= 0) then
                        if qlm_tuning.show_phy_host then
                            octeontx.c.bdk_netphy_inject_prbs_error(phy, true, lane)
                        end
                        if qlm_tuning.show_phy_line then
                            octeontx.c.bdk_netphy_inject_prbs_error(phy, false, lane)
                        end
                    end
                end
            end
        end
        if (key == 'c') or (key == 'C') then
            print("Clearing error counts")
            for _,qlm_num in ipairs(qlm_list) do
                local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
                for lane=0, num_lanes-1 do
                    octeontx.c.bdk_qlm_get_prbs_errors(menu.node, qlm_num, lane, true)
                    local phy = netphy_get(qlm_num, lane)
                    if (phy ~= 0) then
                        if qlm_tuning.show_phy_host then
                            octeontx.c.bdk_netphy_get_prbs_errors(phy, true, lane, true)
                        end
                        if qlm_tuning.show_phy_line then
                            octeontx.c.bdk_netphy_get_prbs_errors(phy, false, lane, true)
                        end
                    end
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
            octeontx.c.bdk_qlm_disable_prbs(menu.node, qlm_num)
            local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
            for lane=0, num_lanes-1 do
                local phy = netphy_get(qlm_num, lane);
                if phy ~= 0 then
                    if qlm_tuning.show_phy_host then
                        octeontx.c.bdk_netphy_disable_prbs(phy, true)
                    end
                    if qlm_tuning.show_phy_host then
                        octeontx.c.bdk_netphy_disable_prbs(phy, false)
                    end
                end
            end
        end
    else
        print("Leaving pattern generator running")
    end
end

--
-- Change the TX Bias, TX Main (C0), TX Pre (C-1) and TX Post (C+1) equalizer tap coefficients
-- on a per lane basis
--
local function tuning_tx_eq(qlm)
    local qlm_lane = select_lane(qlm_tuning.qlm, true)
    local tx_pre = nil
    local tx_main = nil
    local tx_post = nil
    local tx_bs = nil
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        if (qlm_lane == -1) or (qlm_lane == lane) then
            octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
            tx_bs = octeontx.csr.GSERNX_LANEX_TX_DRV_BSTS(qlm,lane).TX_BS
            tx_pre = menu.prompt_number("New setting for TX Pre (C-1) equalizer tap coefficient",
                                        tx_pre, TUNING_TX_PRE_MIN, TUNING_TX_PRE_MAX)
            tx_main = menu.prompt_number("New setting for TX Main (C0) equalizer tap coefficient",
                                         tx_main, TUNING_TX_MAIN_MIN, TUNING_TX_MAIN_MAX)
            tx_post = menu.prompt_number("New setting for TX Post (C+1) equalizer tap coefficient",
                                         tx_post, TUNING_TX_POST_MIN, TUNING_TX_POST_MAX)
            tx_bs = menu.prompt_number("New setting for TX Bias", tx_bs,
                                       TUNING_TX_BS_MIN, TUNING_TX_BS_MAX)
            octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, tx_main, tx_pre, tx_post, tx_bs, -1);
        end
    end
end

--
-- Change the TX Main (C0) equalizer tap coefficient
--
local function tuning_set_tx_cmain(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
    end
    local setting = menu.prompt_number("TX Main (C0) equalizer tap coefficient",
                                       nil, TUNING_TX_MAIN_MIN, TUNING_TX_MAIN_MAX)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, setting, -1, -1, -1, -1)
    end
end

--
-- Change the TX Pre (C-1) equalizer tap coefficient
--
local function tuning_set_tx_cpre(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
    end
    local setting = menu.prompt_number("TX Pre (C-1) equalizer tap coefficient",
                                       nil, TUNING_TX_PRE_MIN, TUNING_TX_PRE_MAX)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, -1, setting, -1, -1, -1)
    end
end

--
-- Change the TX Post (C+1) equalizer tap coefficient
--
local function tuning_set_tx_cpost(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
    end
    local setting = menu.prompt_number("TX Post (C+1) equalizer tap coefficient",
                                       nil, TUNING_TX_POST_MIN, TUNING_TX_POST_MAX)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, -1, -1, setting, -1, -1)
    end
end

--
-- Change the TX Bias selection
--
local function tuning_set_tx_bs(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_display_settings(menu.node, qlm, lane, true, false)
    end
    local setting = menu.prompt_number("TX Bias selection", nil,
                                       TUNING_TX_BS_MIN, TUNING_TX_BS_MAX)
    for lane=0, num_lanes-1 do
        octeontx.c.bdk_qlm_tune_lane_tx(menu.node, qlm, lane, -1, -1, -1, setting, -1)
    end
end

--
-- Change the PHY tuning
--
local function tuning_phy(qlm)
    local host = menu.prompt_yes_no("PHY - Tune host (yes) or line (no) side", true)
    local cmain = menu.prompt_number("PHY - TX Main (C0) equalizer tap coefficient")
    local cpre = menu.prompt_number("PHY - TX Pre (C-1) equalizer tap coefficient")
    local cpost = menu.prompt_number("PHY - TX Post (C+1) equalizer tap coefficient")
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    for lane=0, num_lanes-1 do
        local phy = netphy_get(qlm, lane);
        if (phy ~= 0) then
            octeontx.c.bdk_netphy_tune_tx(phy, host, cmain, cpre, cpost);
        end
    end
end

--
-- Perform a manual RX equalization
--
local function manual_rx_evaluation(qlm)
    printf("Performing RX equalization evaluation\n")
    octeontx.c.bdk_qlm_rx_equalization(menu.node, qlm, -1)
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

--
-- Change the loopback mode
--
local function do_loopback()
    local m = menu.new("Loopback Type")
    m:item("none", "No loopback", octeontx.c.bdk_qlm_enable_loop,
           menu.node, qlm_tuning.qlm, octeontx.QLM_LOOP_DISABLED)
    m:item("core", "Core loopback, TX to RX in digital domain",
           octeontx.c.bdk_qlm_enable_loop, menu.node, qlm_tuning.qlm,
           octeontx.QLM_LOOP_CORE)
    m:item("near", "Near end, TX to RX in analog domain",
           octeontx.c.bdk_qlm_enable_loop, menu.node, qlm_tuning.qlm,
           octeontx.QLM_LOOP_NEAR_END)
    m:item("sh", "Shallow loopback, line side RX to TX",
           octeontx.c.bdk_qlm_enable_loop, menu.node, qlm_tuning.qlm,
           octeontx.QLM_LOOP_SHALLOW)
    m:item("quit",   "No change")
    m:show()
end

--
-- Do an Eye measurement
--
local function do_eye()
    local lane = select_lane(qlm_tuning.qlm, false)
    local detail = menu.prompt_yes_no("Show eye raw data", false)
    octeontx.c.bdk_qlm_eye_display(menu.node, qlm_tuning.qlm, lane, detail and 2 or 1, nil)
end

--
-- Display KR history
--
local function display_kr(qlm)
    local lane = select_lane(qlm, false)
    local num_moves = octeontx.csr.GSERNX_LANEX_TRAIN_10_BCFG(qlm,lane).TTRK_MOVES
    printf("TTRK_MOVES = %d\n", num_moves);
    if num_moves > 128 then
        num_moves = 128
    end
    for nmoves = 0,num_moves-1 do
        octeontx.csr.GSERNX_LANEX_TRAIN_10_BCFG(qlm,lane).TTRK_ARRAY_ADDR = nmoves
        octeontx.csr.GSERNX_LANEX_TRAIN_10_BCFG(qlm,lane).TTRK_ARRAY_RD = 1
        local pre = octeontx.csr.GSERNX_LANEX_TRAIN_10_BCFG(qlm,lane).TTRK_PRE
        local main = octeontx.csr.GSERNX_LANEX_TRAIN_10_BCFG(qlm,lane).TTRK_MAIN
        local post = octeontx.csr.GSERNX_LANEX_TRAIN_10_BCFG(qlm,lane).TTRK_POST
        octeontx.csr.GSERNX_LANEX_TRAIN_10_BCFG(qlm,lane).TTRK_ARRAY_RD = 0
        printf("    %3d: pre=%2d, main=%2d, post=%2d\n", nmoves, pre, main, post);
    end
end

--
-- Main menu
--
function qlm_tuning.run()
    repeat
        local m = menu.new("PRBS and SERDES Tuning Menu")
        local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_tuning.qlm)
        local current_qlm = (num_lanes == 2) and "DLM" or "QLM"
        current_qlm = current_qlm .. qlm_tuning.qlm
        m:item("qlm",    "Select active QLM/DLM (Currently %s)" % current_qlm, select_qlm)
        m:item("down",   "Reset and power down %s" % current_qlm, octeontx.c.bdk_qlm_reset, menu.node, qlm_tuning.qlm)
        m:item("prbs7",  "PRBS-7", do_prbs, 7)
        m:item("prbs9",  "PRBS-9", do_prbs, 9)
        m:item("prbs11", "PRBS-11", do_prbs, 11)
        m:item("prbs15", "PRBS-15", do_prbs, 15)
        m:item("prbs20", "PRBS-20", do_prbs, 20)
        m:item("prbs23", "PRBS-23", do_prbs, 23)
        m:item("prbs29", "PRBS-29", do_prbs, 29)
        m:item("prbs31", "PRBS-31", do_prbs, 31)
        m:item("pat",    "Fixed pattern generator", do_prbs, 0)
        m:item("txeq",   "Set %s TX Equalization settings per lane" % current_qlm, tuning_tx_eq, qlm_tuning.qlm)
        m:item("cmain",  "Set %s TX Main (C0)  equalizer tap coefficient" % current_qlm, tuning_set_tx_cmain, qlm_tuning.qlm)
        m:item("cpre",   "Set %s TX Pre  (C-1) equalizer tap coefficient" % current_qlm, tuning_set_tx_cpre, qlm_tuning.qlm)
        m:item("cpost",  "Set %s TX Post (C+1) equalizer tap coefficient" % current_qlm, tuning_set_tx_cpost, qlm_tuning.qlm)
        m:item("bs",     "Set %s TX Bias selection" % current_qlm, tuning_set_tx_bs, qlm_tuning.qlm)
        m:item("rx_eval","Perform a RX equalization evaluation on %s" % current_qlm, manual_rx_evaluation, qlm_tuning.qlm)
        m:item("disp",   "Display SERDES state of %s" % current_qlm, display_state, qlm_tuning.qlm)
        m:item("kr",     "Display KR history %s" % current_qlm, display_kr, qlm_tuning.qlm)
        m:item("loop",   "Change loopback mode on %s" % current_qlm, do_loopback)
        m:item("eye",    "Display Eye", do_eye)

        local phy = netphy_get(qlm_tuning.qlm, 0);
        if (phy ~= 0) then
            m:item("phytune",  "Tune the PHY connected to %s" % current_qlm, tuning_phy, qlm_tuning.qlm)
        end

        m:item("quit",   "Main menu")
    until (m:show() == "quit")
end

return qlm_tuning
