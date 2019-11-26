/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER_GPIO_PCA8574);

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    device->priv.gpio.device = bdk_driver_extract_device(config_str, "twsi");
    device->priv.gpio.address = bdk_driver_extract_int(config_str, "addr", 0, 127);
    BDK_TRACE(DEVICE, "%s: PCA8574 on TWSI=%s, ADDR=%d\n",
        device->name, device->priv.gpio.device->name, device->priv.gpio.address);
}

/**
 * Update the state of a PCA8574. The device is very simple, containing
 * only a single 8 bit register. Each bit corresponds to one of the 8
 * GPIO pins. If a bit is 1, that pin is an input and also a weak output
 * of high. If a bit is 0, then the pin is pulled toward ground. We use
 * the private variable output_pins to track which pin is an output and
 * currently low. Any pin in this state is stored as a zero in
 * output_pins, all others are a one. This matches the internal register
 * state of the device.
 *
 * @param device Device to update
 */
static void do_update(bdk_device_t *device)
{
    int reg = device->priv.gpio.tristate;
    reg |= device->priv.gpio.output_pins & device->priv.gpio.active_high;
    reg |= ~device->priv.gpio.output_pins & ~device->priv.gpio.active_high;
    reg &= 0xff;

    BDK_TRACE(DEVICE, "%s: Write 0x%x\n", device->name, reg);

    if (bdk_device_twsi_write_ia(device->priv.gpio.device,
            device->priv.gpio.address, 0, 1, 0, reg))
    {
        bdk_error("%s: Error updating state\n", device->name);
    }
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
    /* Set all GPIOs=1, which makes them inputs and weak high outputs */
    device->priv.gpio.active_high = 0xff; /* Which way is active. Set means active is 1 */
    device->priv.gpio.tristate = 0xff; /* Used to mark pins that are input */
    device->priv.gpio.output_pins = 0; /* The logical state of any pins that are outputs, 1=active regardless of active_high */
    do_update(device);
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
    return 8; /* Device always implements 8 GPIOs */
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
    int64_t data = bdk_device_twsi_read_ia(device->priv.gpio.device,
        device->priv.gpio.address, 0, 1, 0);
    if (data < 0)
        bdk_error("%s: Error reading state\n", device->name);

    int reg = 0xff & data;
    BDK_TRACE(DEVICE, "%s: Read 0x%x\n", device->name, reg);
    reg ^= ~device->priv.gpio.active_high; /* Pins that aren't active high must be XORed */
    return reg;
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

    device->priv.gpio.output_pins &= ~clear_mask;
    do_update(device);
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

    device->priv.gpio.output_pins |= set_mask;
    do_update(device);
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
    if (gpio >= gpio_get_num(device))
        bdk_fatal("%s: Invalid GPIO number (%d)\n", device->name, gpio);

    uint64_t mask = 1ull << gpio;

    /* Update tristate with input or output */
    if (is_output)
        device->priv.gpio.tristate &= ~mask;
    else
        device->priv.gpio.tristate |= mask;

    if (!output_value)
        device->priv.gpio.output_pins &= ~mask;
    else
        device->priv.gpio.output_pins |= mask;

    /* Update active high/low */
    if (active_high)
        device->priv.gpio.active_high |= mask;
    else
        device->priv.gpio.active_high &= ~mask;

    do_update(device);
}

bdk_driver_t __bdk_driver_gpio_pca8574 = {
    .name = "GPIO-PCA8574",
    .add = add,
    .init = init,
    .api = BDK_DEVICE_API_GPIO,
    .funcs.gpio.get_num = gpio_get_num,
    .funcs.gpio.readstate = gpio_readstate,
    .funcs.gpio.set0 = gpio_set0,
    .funcs.gpio.set1 = gpio_set1,
    .funcs.gpio.setup = gpio_setup,
};
