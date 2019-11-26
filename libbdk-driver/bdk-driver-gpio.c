/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-gpio.h"

BDK_REQUIRE_DEFINE(DRIVER_GPIO);

/**
 * The GPIO probe function
 *
 * @param device GPIO to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    bdk_device_rename(device, "N%d.GPIO%d", device->node, device->instance);
    return 0;
}

/**
 * GPIO init() function
 *
 * @param device GPIO to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        BDK_CSR_MODIFY(c, device->priv.led_gpio.device->node, BDK_GPIO_BLINK_CFG,
           c.s.force_off = 2; /* 1/4 second */
           c.s.max_on = 1; /* 1/4 second */
           c.s.stretch_on = 15; /* 15/64 second */
           c.s.stretch_off = 15); /* 1/4 second */
        /* Reduce the default drive strength to reduce ringing and
           overshoot. Setting based on discussion with CE group */
        BDK_CSR_MODIFY(c, device->priv.led_gpio.device->node, BDK_GPIO_IO_CTL,
            c.s.drive2 = 2; /* 8mA */
            c.s.slew2 = 0; /* Low slew rate */
            c.s.drive1 = 2; /* 8mA */
            c.s.slew1 = 0; /* Low slew rate */
            c.s.drive0 = 2; /* 8mA */
            c.s.slew0 = 0); /* Low slew rate */
    }

    const int NUM_GPIO = bdk_device_gpio_get_num(device);
    for (int gpio = 0; gpio < NUM_GPIO; gpio++)
    {
        int pin_sel = bdk_config_get_int(BDK_CONFIG_GPIO_PIN_SELECT, gpio, device->node);
        if (pin_sel >= 0)
        {
            BDK_TRACE(DEVICE, "%s: Connecting GPIO%d to pin select 0x%x\n",
                device->name, gpio, pin_sel);
            BDK_CSR_MODIFY(c, device->node, BDK_GPIO_BIT_CFGX(gpio), c.s.pin_sel = pin_sel);
        }
        int invert = bdk_config_get_int(BDK_CONFIG_GPIO_POLARITY, gpio, device->node);
        if (invert)
            BDK_CSR_MODIFY(c, device->node, BDK_GPIO_BIT_CFGX(gpio), c.s.pin_xor = 1);
    }
    return 0;
}

/**
 * GPIO API function to read the number of GPIOs
 *
 * @param device Device to access
 *
 * @return Number of GPIOs
 */
static int get_num(bdk_device_t *device)
{
    if (bdk_is_model(OCTEONTX_CN81XX))
        return 48;
    else if (bdk_is_model(OCTEONTX_CN83XX))
        return 80;
    else if (bdk_is_model(OCTEONTX_CN96XX))
        return 64;
    else if (bdk_is_model(OCTEONTX_CNF95XX))
        return 64;
    else if (bdk_is_model(OCTEONTX_LOKI))
        return 64;
    else if (bdk_is_model(OCTEONTX_CN98XX))
        return 96;
    else
    {
        bdk_error("bdk_gpio_get_num(): Unsupported chip\n");
        return 0;
    }
}

/**
 * GPIO API function to read the state of all GPIOs
 *
 * @param device Device to access
 * @param group  Which group of 64 to access
 *
 * @return State of GPIOs as a bitmask
 */
static uint64_t readstate(bdk_device_t *device, int group)
{
    bdk_gpio_rx_dat_t gpio_rx_dat;
    switch (group)
    {
        case 0:
            gpio_rx_dat.u = BDK_CSR_READ(device->node, BDK_GPIO_RX_DAT);
            break;
        case 1:
            gpio_rx_dat.u = BDK_CSR_READ(device->node, BDK_GPIO_RX1_DAT);
            break;
        default:
            bdk_error("GPIO block %d not supported\n", device->instance);
            gpio_rx_dat.u = 0;
            break;
    }
    return gpio_rx_dat.s.dat;
}

/**
 * GPIO API function to drive GPIOs to logic zero
 *
 * @param device     Device to access
 * @param group      Which group of 64 to access
 * @param clear_mask Bitmask of GPIOs to drive to logic zero
 */
static void set0(bdk_device_t *device, int group, uint64_t clear_mask)
{
    switch (group)
    {
        case 0:
            BDK_CSR_WRITE(device->node, BDK_GPIO_TX_CLR, clear_mask);
            break;
        case 1:
            BDK_CSR_WRITE(device->node, BDK_GPIO_TX1_CLR, clear_mask);
            break;
        default:
            bdk_error("GPIO block %d not supported\n", device->instance);
            break;
    }
}

/**
 * GPIO API function to drive GPIOs to logic one
 *
 * @param device   Device to access
 * @param group    Which group of 64 to access
 * @param set_mask Bitmask of GPIOs to drive to logic one
 */
static void set1(bdk_device_t *device, int group, uint64_t set_mask)
{
    switch (group)
    {
        case 0:
            BDK_CSR_WRITE(device->node, BDK_GPIO_TX_SET, set_mask);
            break;
        case 1:
            BDK_CSR_WRITE(device->node, BDK_GPIO_TX1_SET, set_mask);
            break;
        default:
            bdk_error("GPIO block %d not supported\n", device->instance);
            break;
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
static void setup(bdk_device_t *device, int gpio, bool is_output, int output_value, bool active_high, bool tristate)
{
    if ((gpio >= 0) && (gpio < get_num(device)))
    {
        int gpio_group = gpio >> 6;
        int gpio_index = gpio & 63;
        if (output_value)
            set1(device, gpio_group, 1ull << gpio_index);
        else
            set0(device, gpio_group, 1ull << gpio_index);

        BDK_CSR_DEFINE(cfg, BDK_GPIO_BIT_CFGX(gpio));
        cfg.u = 0;
        cfg.s.tx_oe = !!is_output;
        cfg.s.tx_od = tristate;
        BDK_CSR_WRITE(device->node, BDK_GPIO_BIT_CFGX(gpio), cfg.u);
    }
    else
    {
        bdk_error("bdk_gpio_initialize: Illegal GPIO\n");
    }
}

bdk_driver_t __bdk_driver_gpio = {
    .api = BDK_DEVICE_API_GPIO,
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_GPIO),
    .name = "GPIO",
    .probe = probe,
    .init = init,
    .funcs.gpio.get_num = get_num,
    .funcs.gpio.readstate = readstate,
    .funcs.gpio.set0 = set0,
    .funcs.gpio.set1 = set1,
    .funcs.gpio.setup = setup,
};
