-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK QLM menu for changing configuration.
require("strict")
require("utils")
require("menu")

--
-- Do the actual mode set
--
local function do_setup(qlm, index)
    local mode = octeontx.c.bdk_qlm_get_mode_desc_mode(menu.node, qlm, index)
    local flags = octeontx.c.bdk_qlm_get_mode_desc_flags(menu.node, qlm, index)
    local ref_clk = octeontx.c.bdk_qlm_get_mode_desc_ref_clk(menu.node, qlm, index)
    local baud_mhz = octeontx.c.bdk_qlm_get_mode_desc_speed(menu.node, qlm, index)

    octeontx.c.bdk_qlm_set_clock(menu.node, qlm, ref_clk)
    -- Reset the QLM after changing the reference clock
    octeontx.c.bdk_qlm_reset(menu.node, qlm)
    octeontx.c.bdk_qlm_set_mode(menu.node, qlm, -1, mode, baud_mhz, flags)
end

--
-- This is called when the user selects a QLM to change its config
--
local function do_menu(qlm)
    local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm)
    local label = (num_lanes == 2) and "DLM" or "QLM"
    local m = menu.new("Select a mode for %s%d" % {label, qlm})
    local index = 0
    while true do
        local mode = octeontx.c.bdk_qlm_get_mode_desc_mode(menu.node, qlm, index)
        local flags = octeontx.c.bdk_qlm_get_mode_desc_flags(menu.node, qlm, index)
        local baud_mhz = octeontx.c.bdk_qlm_get_mode_desc_speed(menu.node, qlm, index)
        local label = octeontx.c.bdk_qlm_mode_to_cfg_str(mode);
        if flags ~= 0 then
            label = label .. "-EP"
        end
        if baud_mhz ~= 0 then
            label = label .. ("-%d" % baud_mhz)
        end
        local descr
        if baud_mhz == 0 then
            descr = "Disabled"
        elseif flags ~= 0 then
            descr = "Endpoint %s @%2d.%03d GBaud" % {octeontx.c.bdk_qlm_mode_tostring(mode), baud_mhz / 1000, baud_mhz % 1000}
        else
            descr = "%s @%2d.%03d GBaud" % {octeontx.c.bdk_qlm_mode_tostring(mode), baud_mhz / 1000, baud_mhz % 1000}
        end
        m:item(label:lower(), descr, do_setup, qlm, index)
        if mode == octeontx.QLM_MODE_DISABLED then
            return m:show()
        end
        index = index + 1
    end
end

--
-- Configuration prompting
--
function qlm_setup()
    local qlm_max = octeontx.c.bdk_qlm_get_num(menu.node) - 1
    local m = menu.new("Select a QLM to Configure")
    repeat
        for qlm_num = 0, qlm_max do
            local mode = octeontx.c.bdk_qlm_get_mode(menu.node, qlm_num, 0)
            local config_mode = octeontx.c.bdk_qlm_mode_tostring(mode)
            local config_speed = octeontx.c.bdk_qlm_get_gbaud_mhz(menu.node, qlm_num, 0)
            local num_lanes = octeontx.c.bdk_qlm_get_lanes(menu.node, qlm_num)
            local label = (num_lanes == 2) and "DLM" or "QLM"
            local ref_clock = octeontx.c.bdk_qlm_measure_clock(menu.node, qlm_num)
            local option
            if config_speed == 0 then
                option = "%s%d - Disabled" % {label, qlm_num}
            else
                option = "%s%d - %s @%2d.%03d GBaud, ref %3d.%03d Mhz" % {label, qlm_num, config_mode, config_speed / 1000, config_speed % 1000, ref_clock / 1000000, ref_clock / 1000 % 1000}
            end
            m:item("qlm" .. qlm_num, option, do_menu, qlm_num)
        end
        m:item("quit", "Exit menu")
    until (m:show() == "quit")
end

