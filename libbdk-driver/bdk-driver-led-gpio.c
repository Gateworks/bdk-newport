/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gpio.h"

BDK_REQUIRE_DEFINE(DRIVER_LED_GPIO);

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    bdk_device_t *parent = bdk_driver_extract_device(config_str, "dev");
    int gpio_num = bdk_device_gpio_get_num(parent);
    int gpio = bdk_driver_extract_int(config_str, "gpio", 0, gpio_num - 1);
    int high = bdk_driver_extract_int(config_str, "active_high", 0, 1);
    int tristate = bdk_driver_extract_int(config_str, "tristate", 0, 1);

    BDK_TRACE(DEVICE, "%s: LED on dev=%s, gpio=%d, active_high=%d, tristate=%d\n",
        device->name, parent->name, gpio, high, tristate);

    device->priv.led_gpio.device = parent;
    device->priv.led_gpio.gpio = gpio;
    device->priv.led_gpio.active_high = high;
    device->priv.led_gpio.tristate = tristate;
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
    bdk_device_gpio_setup(device->priv.led_gpio.device,
        device->priv.led_gpio.gpio, true, 0, device->priv.led_gpio.active_high,
        device->priv.led_gpio.tristate);
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
    return 1;
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
    int group = device->priv.led_gpio.gpio >> 6;
    int gpio = device->priv.led_gpio.gpio & 63;
    if (on)
        bdk_device_gpio_set1(device->priv.led_gpio.device, group, 1ull << gpio);
    else
        bdk_device_gpio_set0(device->priv.led_gpio.device, group, 1ull << gpio);
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

    BDK_CSR_MODIFY(c, device->priv.led_gpio.device->node, BDK_GPIO_BIT_CFGX(led),
        c.s.blink_en = 1;
        c.s.pin_sel = gpio_pin_sel);
    return 0;
}

bdk_driver_t __bdk_driver_led_gpio = {
    .name = "LED-GPIO",
    .add = add,
    .init = init,
    .api = BDK_DEVICE_API_LED,
    .funcs.led.get_num = led_get_num,
    .funcs.led.set = led_set,
    .funcs.led.attach = led_attach,
};
