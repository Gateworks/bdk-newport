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

-- BDK power burn menu.
require("strict")
require("utils")
require("menu")

local function do_throttle()
    -- Get the current setting
    local percent = cavium.c.bdk_config_get_int(cavium.CONFIG_VRM_THROTTLE_NORMAL, menu.node);
    percent = menu.prompt_number("Throttle level (percent)", percent, 1, 100)
    -- Apply the throttling
    cavium.c.bdk_power_throttle(menu.node, percent)
    -- Update the config with the current throttle percentage
    cavium.c.bdk_config_set_int(percent, cavium.CONFIG_VRM_THROTTLE_NORMAL, menu.node);
end

repeat
    local m = menu.new("Power Burn Menu")
    m:item_node() -- Adds option to choose the node number

    m:item("off", "Disable power burn", cavium.c.bdk_power_burn, menu.node, cavium.POWER_BURN_NONE)
    m:item("full", "Full power burn", cavium.c.bdk_power_burn, menu.node, cavium.POWER_BURN_FULL)
    -- The generically namd transient is 1s on, 1s idle
    m:item("tran", "Transient power burn", cavium.c.bdk_power_burn, menu.node, cavium.POWER_BURN_CYCLE_1S)
    -- These other options are disabled by default to reduce confusion
    --m:item("10ms", "Cycle 10ms power burn, 10ms idle", cavium.c.bdk_power_burn, menu.node, cavium.POWER_BURN_CYCLE_10MS)
    --m:item("1s", "Cycle 1s power burn, 1s idle", cavium.c.bdk_power_burn, menu.node, cavium.POWER_BURN_CYCLE_1S)
    --m:item("5s", "Cycle 5s power burn, 5s idle", cavium.c.bdk_power_burn, menu.node, cavium.POWER_BURN_CYCLE_5S)
    --m:item("1m", "Cycle 1m power burn, 1m idle", cavium.c.bdk_power_burn, menu.node, cavium.POWER_BURN_CYCLE_1M)
    --m:item("5m", "Cycle 5m power burn, 5m idle", cavium.c.bdk_power_burn, menu.node, cavium.POWER_BURN_CYCLE_5M)
    -- Disable on multi-node due to errata DAP-24000
    if (not cavium.is_model(cavium.CN88XXP1)) or (cavium.c.bdk_numa_is_only_one() == 1) then
        m:item("throt", "Set power throttle level", do_throttle)
    end

    m:item("quit", "Main menu")
until m:show() == "quit"

