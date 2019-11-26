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

local qlm_tuning
if octeontx.is_model(octeontx.CN8XXX) then
    qlm_tuning = require("qlm_tuning_cn8xxx")
elseif octeontx.is_model(octeontx.CN96XXP1)  or octeontx.is_model(octeontx.CNF95XXP1) then
    qlm_tuning = require("qlm_tuning_gsern")
else
    qlm_tuning = require("qlm_tuning_gserx")
end

--
-- Build the main QLM/DLM menu
--
local m = menu.new("QLM/DLM Menu")
repeat
    m:item_node() -- Adds option to choose the node number
    -- Only chips before the rambus serdes support reconfiguration
    if octeontx.is_model(octeontx.CN8XXX) or octeontx.is_model(octeontx.CN96XXP1) or octeontx.is_model(octeontx.CNF95XXP1) then
        require("qlm_setup")
        m:item("set", "Change QLM/DLM configuration", qlm_setup)
    end
    -- Build a list of QLMs showing the current config. Selecting them
    -- does nothing
    local num_qlms = octeontx.c.bdk_qlm_get_num(menu.node)
    for qlm_num = 0, num_qlms-1 do
        local last_mode = nil
        local last_speed = nil
        local force_display = false
        local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
        local ref_clock = octeontx.c.bdk_qlm_measure_clock(menu.node, qlm_num)
        -- Round ref clock to the nearest KHz and change to Khz
        ref_clock = (ref_clock + 500) / 1000
        -- Loop through all lanes
        for qlm_lane = 0, num_lanes-1 do
            local mode = octeontx.c.bdk_qlm_get_mode(menu.node, qlm_num, qlm_lane)
            local speed = octeontx.c.bdk_qlm_get_gbaud_mhz(menu.node, qlm_num, qlm_lane)
            mode = octeontx.c.bdk_qlm_mode_tostring(mode)
            -- Only show lanes 1-3 if different from 0
            if (mode ~= last_mode) or (speed ~= last_speed) or force_display then
                local menu_label = "qlm%d" % qlm_num
                local label = "QLM%d" % qlm_num
                if num_lanes <= 2 then
                    label = "DLM%d" % qlm_num
                end
                if qlm_lane ~= 0 then
                    label = label .. (".%d" % qlm_lane)
                    menu_label = menu_label .. (".%d" % qlm_lane)
                end
                local option
                if speed == 0 then
                    option = "%s - Disabled, ref %3d.%03d Mhz" % {label, ref_clock / 1000, ref_clock % 1000}
                else
                    option = "%s - %s @%2d.%03d GBaud, ref %3d.%03d Mhz" % {label, mode, speed / 1000, speed % 1000, ref_clock / 1000, ref_clock % 1000}
                end
                m:item(menu_label, option)
                last_mode = mode
                last_speed = speed
                force_display = (qlm_lane ~= 0)
            end
        end
    end
    m:item("tune", "PRBS and SERDES Tuning", qlm_tuning.run)
    m:item("quit", "Main menu")
until (m:show() == "quit")


