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

-- BDK QLM menu.
-- Displays the GUI interface for accessing QLM settings.
require("strict")
require("utils")
require("menu")
local qlm_tuning = require("qlm_tuning")

--
-- Build the main QLM/DLM menu
--
local m = menu.new("QLM/DLM Menu")
repeat
    m:item_node() -- Adds option to choose the node number
    if cavium.is_model(cavium.CN88XX) then
        require("qlm_menu_cn88xx")
        m:item("set", "Change QLM/DLM configuration", qlm_setup_cn88xx)
    end
    if cavium.is_model(cavium.CN83XX) then
        require("qlm_menu_cn83xx")
        m:item("set", "Change QLM/DLM configuration", qlm_setup_cn83xx)
    end
    if cavium.is_model(cavium.CN81XX) then
        require("qlm_menu_cn81xx")
        m:item("set", "Change QLM/DLM configuration", qlm_setup_cn81xx)
    end
    -- Build a list of QLMs showing the current config. Selecting them
    -- does nothing
    local num_qlms = cavium.c.bdk_qlm_get_num(menu.node)
    for qlm_num = 0, num_qlms-1 do
        local mode = cavium.c.bdk_qlm_get_mode(menu.node, qlm_num)
        local config_mode = cavium.c.bdk_qlm_mode_tostring(mode)
        local config_speed = cavium.c.bdk_qlm_get_gbaud_mhz(menu.node, qlm_num)
        local num_lanes = cavium.c.bdk_qlm_get_lanes(menu.node, qlm_num)
        local label = (num_lanes <= 2) and "DLM" or "QLM"
        local ref_clock = cavium.c.bdk_qlm_measure_clock(menu.node, qlm_num)
        -- Round ref clock to the nearest KHz and change to Khz
        ref_clock = (ref_clock + 500) / 1000
        local option
        if config_speed == 0 then
            option = "%s %d - Disabled, ref %3d.%03d Mhz" % {label, qlm_num, ref_clock / 1000, ref_clock % 1000}
        else
            option = "%s %d - %s @%2d.%03d GBaud, ref %3d.%03d Mhz" % {label, qlm_num, config_mode, config_speed / 1000, config_speed % 1000, ref_clock / 1000, ref_clock % 1000}
        end
        m:item("qlm" .. qlm_num, option)
    end
    m:item("tune", "PRBS and SERDES Tuning", qlm_tuning.run)
    m:item("quit", "Main menu")
until (m:show() == "quit")


