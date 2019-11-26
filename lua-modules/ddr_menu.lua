-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK DRAM menu.
-- Displays the GUI interface for configuring and testing DRAM.
require("strict")
require("utils")
require("menu")
require("fileio")

local getenv = os.getenv
if octeontx.global then
    getenv = octeontx.global.os.getenv
end

local m
local function update_verbosity_label()
    local cur_verb = octeontx.c.bdk_config_get_int(octeontx.CONFIG_DRAM_VERBOSE)
    local label = "Change verbosity level (Currently %d)" % cur_verb
    m:item("verbose", label, function()
        local new_verb = menu.prompt_number("New verbosity level, return for default", cur_verb, 0, 255)
        if new_verb ~= cur_verb then
            octeontx.c.bdk_config_set_int(new_verb, octeontx.CONFIG_DRAM_VERBOSE)
        end
        update_verbosity_label()
    end)
end

repeat
    m = menu.new("DRAM Menu")
    m:item_node() -- Adds option to choose the node number
    update_verbosity_label()

    m:item("setenv", "Set environment variable", function()
        local name = menu.prompt_string("Name")
        local value = menu.prompt_string("Value", "")
        if value == "" then
            value = nil
        end
        octeontx.c.bdk_setenv(name, value)
    end)

    m:item("getenv", "Get environment variable", function()
        local name = menu.prompt_string("Name")
        local value = getenv(name)
        if value then
            printf("%s = %s\n", name, value)
        else
            printf("%s is not in the environment\n", name)
        end
    end)

    m:item("showenv", "Show environment variables", function()
        printf("Environment variable:\n")
        octeontx.c.bdk_showenv()
    end)

    if octeontx.c.bdk_dram_get_size_mbytes(menu.node) == 0 then
        m:item("init", "Initialize DRAM", function()
            local ddr_speed = octeontx.c.bdk_config_get_int(octeontx.CONFIG_DDR_SPEED, menu.node)
            local new_speed = menu.prompt_number("DRAM speed in MT/s, return for default", ddr_speed)
            if new_speed ~= ddr_speed then
                octeontx.c.bdk_config_set_int(new_speed, octeontx.CONFIG_DDR_SPEED, menu.node)
            end
            local dram_mbytes = octeontx.c.bdk_dram_config(menu.node, 0)
            printf("BDK DRAM:%s\n", octeontx.c.bdk_dram_get_info_string(menu.node))
        end)
    else
        m:item("tune", "DDR Read Tuning", function()
            local start_time = os.time()
            octeontx.c.bdk_dram_tune(menu.node)
            local end_time = os.time()
            local total_time = os.difftime(end_time, start_time)
            local hour = total_time / 3600
            local min = (total_time % 3600) / 60
            local sec = (total_time % 3600) % 60
            printf("DDR Read Tuning took %02d:%02d:%02d\n", hour, min, sec)
        end)
	m:item("margin", "DDR Margining Tool", function()
	    octeontx.c.bdk_dram_margin(menu.node)
	end)
    end
    m:item("test", "Memory Testing Menu", menu.dofile, "ddr_test_menu")
    m:item("quit", "Main menu")
until (m:show() == "quit")

