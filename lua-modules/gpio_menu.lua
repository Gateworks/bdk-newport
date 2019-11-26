-- ***********************license start***********************************
-- Copyright (C) 2018 Marvell International Ltd.
-- SPDX-License-Identifier: BSD-3-Clause
-- https://spdx.org/licenses
-- **********************license end**************************************

-- BDK GPIO menu.
-- Displays the GUI interface for configuring and accessing GPIO pins.
--
require("strict")
require("utils")
require("menu")
local bit64 = require("bit64")
local gpio_device = octeontx.c.bdk_device_lookup_by_name("N%d.GPIO0" % menu.node)

local function gpio_config()
    local num_gpio = octeontx.c.bdk_device_gpio_get_num(gpio_device)
    local gpio = menu.prompt_number("GPIO number", 0, 0, num_gpio-1)
    local is_output = menu.prompt_yes_no("Configure as output")
    local value
    if is_output then
        value = menu.prompt_number("GPIO state", nil, 0, 1)
    else
        value = 0
    end
    octeontx.c.bdk_device_gpio_setup(gpio_device, gpio, is_output, value, true)
end

local function gpio_read()
    local num_gpio = octeontx.c.bdk_device_gpio_get_num(gpio_device)
    local gpio = menu.prompt_number("GPIO number", 0, 0, num_gpio-1)
    local state = octeontx.c.bdk_device_gpio_readstate(gpio_device, bit64.rshift(gpio, 6), bit64.band(gpio, 63))
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

