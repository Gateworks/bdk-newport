/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER_GPIO_PCA9535);

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
    BDK_TRACE(DEVICE, "%s: PCA9535 on TWSI=%s, ADDR=%d\n",
        device->name, device->priv.gpio.device->name, device->priv.gpio.address);
}

/**
 * Update the state of a PCA9535.  *
 * @param device Device to update
 */
static void do_update(bdk_device_t *device)
{
    int reg = device->priv.gpio.tristate;
    BDK_TRACE(DEVICE, "%s: Write 0x%x to config reg0.\n", device->name, reg & 0xff);

    if (bdk_device_twsi_write_ia(device->priv.gpio.device,
            device->priv.gpio.address, 6, 1, 1, reg & 0xff))
    {
        bdk_error("%s: Error updating config reg0\n", device->name);
    }

    BDK_TRACE(DEVICE, "%s: Write 0x%x to config reg1.\n", device->name, (reg >> 8) & 0xff);

    if (bdk_device_twsi_write_ia(device->priv.gpio.device,
            device->priv.gpio.address, 7, 1, 1, (reg >> 8) & 0xff))
    {
        bdk_error("%s: Error updating config reg1\n", device->name);
    }

    reg = device->priv.gpio.output_pins & device->priv.gpio.active_high;
    reg |= ~device->priv.gpio.output_pins & ~device->priv.gpio.active_high;

    BDK_TRACE(DEVICE, "%s: Write 0x%x to output reg0.\n", device->name, reg & 0xff);

    if (bdk_device_twsi_write_ia(device->priv.gpio.device,
            device->priv.gpio.address, 2, 1, 1, reg & 0xff))
    {
        bdk_error("%s: Error updating output reg\n", device->name);
    }

    BDK_TRACE(DEVICE, "%s: Write 0x%x to output reg1.\n", device->name, (reg >> 8) & 0xff);

    if (bdk_device_twsi_write_ia(device->priv.gpio.device,
            device->priv.gpio.address, 3, 1, 1, (reg >> 8) & 0xff))
    {
        bdk_error("%s: Error updating output reg1\n", device->name);
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
    device->priv.gpio.active_high = 0xffff; /* Which way is active. Set means active is 1 */

    /* Read back current direction of all GPIOs */
    int64_t data = bdk_device_twsi_read_ia(device->priv.gpio.device,
        device->priv.gpio.address, 6, 1, 1);
    if (data < 0)
        bdk_error("%s: Error reading control0\n", device->name);

    int reg = 0xff & data;
    data = bdk_device_twsi_read_ia(device->priv.gpio.device,
        device->priv.gpio.address, 7, 1, 1);
    if (data < 0)
        bdk_error("%s: Error reading control1\n", device->name);

    reg |= ((data & 0xff) << 8);
    reg &= 0xffff;

    device->priv.gpio.tristate = reg; /* Used to mark pins that are input */

    /* Read back current output pin settings */
    data = bdk_device_twsi_read_ia(device->priv.gpio.device,
        device->priv.gpio.address, 2, 1, 1);
    if (data < 0)
        bdk_error("%s: Error reading control0\n", device->name);

    reg = 0xff & data;
    data = bdk_device_twsi_read_ia(device->priv.gpio.device,
        device->priv.gpio.address, 3, 1, 1);
    if (data < 0)
        bdk_error("%s: Error reading control1\n", device->name);

    reg |= ((data & 0xff) << 8);
    reg &= 0xffff;

    device->priv.gpio.output_pins = reg; /* The logical state of any pins that are outputs, 1=active regardless of active_high */

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
    return 16; /* Device always implements 16 GPIOs */
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
        device->priv.gpio.address, 0, 1, 1);
    if (data < 0)
        bdk_error("%s: Error reading input0\n", device->name);

    int reg = 0xff & data;
    data = bdk_device_twsi_read_ia(device->priv.gpio.device,
        device->priv.gpio.address, 1, 1, 1);
    if (data < 0)
        bdk_error("%s: Error reading input1\n", device->name);

    reg |= ((data & 0xff) << 8);
    reg &= 0xffff;

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

bdk_driver_t __bdk_driver_gpio_pca9535 = {
    .name = "GPIO-PCA9535",
    .add = add,
    .init = init,
    .api = BDK_DEVICE_API_GPIO,
    .funcs.gpio.get_num = gpio_get_num,
    .funcs.gpio.readstate = gpio_readstate,
    .funcs.gpio.set0 = gpio_set0,
    .funcs.gpio.set1 = gpio_set1,
    .funcs.gpio.setup = gpio_setup,
};
