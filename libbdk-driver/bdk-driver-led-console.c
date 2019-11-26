/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER_LED_CONSOLE);

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    BDK_TRACE(DEVICE, "%s: LED console added\n", device->name);
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
 * LED API function to determine how many LEDs are implemented on this device
 *
 * @param device Device to access
 *
 * @return Number of LEDs
 */
static int led_get_num(bdk_device_t *device)
{
    return 64;
}

/**
 * LED API function to set the state of a LED
 *
 * @param device Device to access
 * @param led    Which LED to access
 * @param on     True if the LED should be on
 */
static void led_set(bdk_device_t *device, int led, bool on)
{
    printf("%s: LED %d is %s\n", device->name, led, (on) ? "on" : "off");
}

/**
 * LED API function to attach a LED to an internal GPIO pin select
 *
 * @param device Device to access
 * @param led    Which LED to access
 * @param gpio_pin_sel
 *               GPIO pin select to attach
 *
 * @return Zero on success, negative on failure
 */
static int led_attach(bdk_device_t *device, int led, int gpio_pin_sel)
{
    bdk_warn("%s: LED %d can't be connected to a GPIO_PIN_SEL\n", device->name, led);
    return -1;
}

bdk_driver_t __bdk_driver_led_console = {
    .name = "LED-CONSOLE",
    .add = add,
    .init = init,
    .api = BDK_DEVICE_API_LED,
    .funcs.led.get_num = led_get_num,
    .funcs.led.set = led_set,
    .funcs.led.attach = led_attach,
};
