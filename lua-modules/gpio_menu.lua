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

-- BDK GPIO menu.
-- Displays the GUI interface for configuring and accessing GPIO pins.
--
-- * Written by Chad Reese
-- * Copyright (C) 2010-2017 Cavium Inc.
--
require("strict")
require("utils")
require("menu")
local bit64 = require("bit64")

local function gpio_config()
    local num_gpio = cavium.c.bdk_gpio_get_num()
    local gpio = menu.prompt_number("GPIO number", 0, 0, num_gpio-1)
    local is_output = menu.prompt_yes_no("Configure as output")
    local value
    if is_output then
        value = menu.prompt_number("GPIO state", nil, 0, 1)
    else
        value = 0
    end
    assert(cavium.c.bdk_gpio_initialize(menu.node, gpio, is_output, value) == 0, "GPIO configure failed")
end

local function gpio_read()
    local num_gpio = cavium.c.bdk_gpio_get_num()
    local gpio = menu.prompt_number("GPIO number", 0, 0, num_gpio-1)
    local state = cavium.c.bdk_gpio_read(menu.node, bit64.rshift(gpio, 6), bit64.band(gpio, 63))
    if bit64.btest(state, bit64.lshift(1, bit64.band(gpio, 63))) then
        printf("GPIO %d: 1\n", gpio)
    else
        printf("GPIO %d: 0\n", gpio)
    end
end

local m = menu.new("GPIO Menu")

m:item_node() -- Adds option to choose the node number
m:item("cfg", "Configure a GPIO", gpio_config)
m:item("read", "Read GPIO state", gpio_read)
m:item("quit", "Main menu")

while (m:show() ~= "quit") do
    -- Spinning on menu
end

