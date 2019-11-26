-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK power burn menu.
require("strict")
require("utils")
require("menu")

local function do_throttle()
    -- Get the current setting
    local percent = octeontx.c.bdk_config_get_int(octeontx.CONFIG_VRM_THROTTLE_NORMAL, menu.node);
    percent = menu.prompt_number("Throttle level (percent)", percent, 1, 100)
    -- Apply the throttling
    octeontx.c.bdk_power_throttle(menu.node, percent)
    -- Update the config with the current throttle percentage
    octeontx.c.bdk_config_set_int(percent, octeontx.CONFIG_VRM_THROTTLE_NORMAL, menu.node);
end

local function do_coremark()
    local coremask = menu.prompt_number("Coremask to run on", -1, -1, 0xffffffffffff)
    octeontx.c.bdk_power_coremark(menu.node, coremask)
end

repeat
    local m = menu.new("Power Burn Menu")
    m:item_node() -- Adds option to choose the node number

    m:item("off", "Disable power burn", octeontx.c.bdk_power_burn, menu.node, octeontx.POWER_BURN_NONE)
    m:item("full", "Full power burn", octeontx.c.bdk_power_burn, menu.node, octeontx.POWER_BURN_FULL)
    -- The generically namd transient is 1s on, 1s idle
    m:item("tran", "Transient power burn", octeontx.c.bdk_power_burn, menu.node, octeontx.POWER_BURN_CYCLE_1S)
    -- These other options are disabled by default to reduce confusion
    --m:item("10ms", "Cycle 10ms power burn, 10ms idle", octeontx.c.bdk_power_burn, menu.node, octeontx.POWER_BURN_CYCLE_10MS)
    --m:item("1s", "Cycle 1s power burn, 1s idle", octeontx.c.bdk_power_burn, menu.node, octeontx.POWER_BURN_CYCLE_1S)
    --m:item("5s", "Cycle 5s power burn, 5s idle", octeontx.c.bdk_power_burn, menu.node, octeontx.POWER_BURN_CYCLE_5S)
    --m:item("1m", "Cycle 1m power burn, 1m idle", octeontx.c.bdk_power_burn, menu.node, octeontx.POWER_BURN_CYCLE_1M)
    --m:item("5m", "Cycle 5m power burn, 5m idle", octeontx.c.bdk_power_burn, menu.node, octeontx.POWER_BURN_CYCLE_5M)
    m:item("wfe", "WFE loop for low power", octeontx.c.bdk_power_burn, menu.node, octeontx.POWER_BURN_WFE)
    m:item("cmark", "Run coremark", do_coremark)
    if octeontx.is_model(octeontx.CN8XXX) then
        m:item("throt", "Set power throttle level", do_throttle)
    end

    m:item("quit", "Main menu")
until m:show() == "quit"

