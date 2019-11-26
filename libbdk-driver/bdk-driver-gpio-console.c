/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER_GPIO_CONSOLE);

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    BDK_TRACE(DEVICE, "%s: GPIO console added\n", device->name);
}

/**
 * Initialize the device, nothing needed
 *
 * @param device to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    return 0;
}

/**
 * GPIO API function to read the number of GPIOs
 *
 * @param device Device to access
 *
 * @return Number of GPIOs
 */
static int gpio_get_num(bdk_device_t *device)
{
    return 64;
}

/**
 * GPIO API function to read the state of all GPIOs
 *
 * @param device Device to access
 * @param group  Which group of 64 to access
 *
 * @return State of GPIOs as a bitmask
 */
static uint64_t gpio_readstate(bdk_device_t *device, int group)
{
    if (group != 0)
        bdk_fatal("%s: Pass a non-zero GPIO group number (%d)\n", device->name, group);
    return device->priv.state;
}

static void display_gpio(bdk_device_t *device, int gpio)
{
    int state = (device->priv.state >> gpio) & 1;
    printf("%s: GPIO %d is %d\n", device->name, gpio, state);
}

/**
 * GPIO API function to drive GPIOs to logic zero
 *
 * @param device     Device to access
 * @param group      Which group of 64 to access
 * @param clear_mask Bitmask of GPIOs to drive to logic zero
 */
static void gpio_set0(bdk_device_t *device, int group, uint64_t clear_mask)
{
    if (group != 0)
        bdk_fatal("%s: Pass a non-zero GPIO group number (%d)\n", device->name, group);

    int num = gpio_get_num(device);
    for (int gpio = 0; gpio < num; gpio++)
    {
        uint64_t gpio_mask = 1ull << gpio;
        if (clear_mask & gpio_mask & device->priv.state)
        {
            device->priv.state &= ~gpio_mask;
            display_gpio(device, gpio);
        }
    }
}

/**
 * GPIO API function to drive GPIOs to logic one
 *
 * @param device   Device to access
 * @param group    Which group of 64 to access
 * @param set_mask Bitmask of GPIOs to drive to logic one
 */
static void gpio_set1(bdk_device_t *device, int group, uint64_t set_mask)
{
    if (group != 0)
        bdk_fatal("%s: Pass a non-zero GPIO group number (%d)\n", device->name, group);

    int num = gpio_get_num(device);
    for (int gpio = 0; gpio < num; gpio++)
    {
        uint64_t gpio_mask = 1ull << gpio;
        if (set_mask & gpio_mask & ~device->priv.state)
        {
            device->priv.state |= gpio_mask;
            display_gpio(device, gpio);
        }
    }
}

/**
 * GPIO API function to setup a GPIO for use
 *
 * @param device    Device to access
 * @param gpio      Which GPIO to setup
 * @param is_output True if this GPIO is an output
 * @param output_value
 *                  Logic value to set if an output
 * @param active_high
 *                  True if logic one drives GPIO high, false if the GPIO should be inverted
 * @param tristate  If true, the GPIO will be tristated when not active. If false, it will be driven
 *                  the opposite of active.
 */
static void gpio_setup(bdk_device_t *device, int gpio, bool is_output, int output_value, bool active_high, bool tristate)
{
    if (is_output)
    {
        printf("%s: GPIO %d is an output, active %s, %s when idle\n", device->name, gpio,
            (active_high) ? "high" : "low", (tristate) ? "tri-state" : "drive");
        if (output_value)
            gpio_set1(device, gpio / 64, 1ull << (gpio & 63));
        else
            gpio_set0(device, gpio / 64, 1ull << (gpio & 63));
    }
    else
        printf("%s: GPIO %d is an input, active %s\n", device->name, gpio,
            (active_high) ? "high" : "low");
}

bdk_driver_t __bdk_driver_gpio_console = {
    .name = "GPIO-CONSOLE",
    .add = add,
    .init = init,
    .api = BDK_DEVICE_API_GPIO,
    .funcs.gpio.get_num = gpio_get_num,
    .funcs.gpio.readstate = gpio_readstate,
    .funcs.gpio.set0 = gpio_set0,
    .funcs.gpio.set1 = gpio_set1,
    .funcs.gpio.setup = gpio_setup,
};
