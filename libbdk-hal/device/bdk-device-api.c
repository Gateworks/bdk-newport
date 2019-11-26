/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"

/**
 * GPIO API function to lookup a device in the configuration for use
 * with GPIO API
 *
 * @param gpio     GPIO number specified in the configuration
 * @param cfg_item Configuration item to lookup
 *
 * @return Pointer to device for API
 */
bdk_device_t* bdk_device_gpio_lookup(int *gpio, bdk_config_t cfg_item, ...)
{
    int64_t tmp = -1;

    if (gpio)
        *gpio = -1;

    if ((int)cfg_item != -1)
    {
        va_list args;
        va_start(args, cfg_item);
        const char *val = bdk_config_get_str_va(cfg_item, args);
        va_end(args);

        if (!val)
            return NULL;

        int count;
        if ((val[0] == '0') && (val[1] == 'x'))
            count = sscanf(val + 2, "%lx", &tmp);
        else
            count = sscanf(val, "%li", &tmp);
        if (count != 1)
            return NULL;
        if ((tmp < 0) || (tmp >= 128))
            return NULL;
    }

    bdk_device_t *device = bdk_device_lookup(bdk_numa_master(), BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_GPIO), 0);
    if (!device)
        return NULL;

    if (device->driver->api != BDK_DEVICE_API_GPIO)
        bdk_fatal("%s: Doesn't support the GPIO API\n", device->name);

    if (gpio)
        *gpio = tmp;
    return device;
}

/**
 * GPIO API function to read the number of GPIOs
 *
 * @param device Device to access
 *
 * @return Number of GPIOs
 */
int bdk_device_gpio_get_num(bdk_device_t *device)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_GPIO)
        bdk_fatal("%s: Doesn't support the GPIO API\n", device->name);
    return device->driver->funcs.gpio.get_num(device);
}

/**
 * GPIO API function to read the state of all GPIOs
 *
 * @param device Device to access
 * @param group  Which group of 64 to access
 *
 * @return State of GPIOs as a bitmask
 */
uint64_t bdk_device_gpio_readstate(bdk_device_t *device, int group)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_GPIO)
        bdk_fatal("%s: Doesn't support the GPIO API\n", device->name);
    return device->driver->funcs.gpio.readstate(device, group);
}

/**
 * GPIO API function to drive GPIOs to logic zero
 *
 * @param device     Device to access
 * @param group      Which group of 64 to access
 * @param clear_mask Bitmask of GPIOs to drive to logic zero
 */
void bdk_device_gpio_set0(bdk_device_t *device, int group, uint64_t clear_mask)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_GPIO)
        bdk_fatal("%s: Doesn't support the GPIO API\n", device->name);
    return device->driver->funcs.gpio.set0(device, group, clear_mask);
}

/**
 * GPIO API function to drive GPIOs to logic one
 *
 * @param device   Device to access
 * @param group    Which group of 64 to access
 * @param set_mask Bitmask of GPIOs to drive to logic one
 */
void bdk_device_gpio_set1(bdk_device_t *device, int group, uint64_t set_mask)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_GPIO)
        bdk_fatal("%s: Doesn't support the GPIO API\n", device->name);
    return device->driver->funcs.gpio.set1(device, group, set_mask);
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
void bdk_device_gpio_setup(bdk_device_t *device, int gpio, bool is_output, int output_value, bool active_high, bool tristate)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_GPIO)
        bdk_fatal("%s: Doesn't support the GPIO API\n", device->name);
    return device->driver->funcs.gpio.setup(device, gpio, is_output, output_value, active_high, tristate);
}

/**
 * TWSI API function to lookup a device in the configuration for use
 * with TWSI API
 *
 * @param dev_addr Device address (7 bit)
 * @param internal_addr
 *                 Internal address.  Can be 0, 1 or 2 bytes in width
 * @param ia_width_bytes
 *                 Internal address size in bytes (0, 1, or 2)
 * @param cfg_item Configuration item to lookup
 *
 * @return Pointer to device for API
 */
bdk_device_t* bdk_device_twsi_lookup(uint8_t *dev_addr, uint16_t *internal_addr, int *ia_width_bytes, bdk_config_t cfg_item, ...)
{
    int64_t tmp = 0;

    if (dev_addr)
        *dev_addr = 0;
    if (internal_addr)
        *internal_addr = 0;
    if (ia_width_bytes)
        *ia_width_bytes = 0;

    if ((int)cfg_item != -1)
    {
        va_list args;
        va_start(args, cfg_item);
        const char *val = bdk_config_get_str_va(cfg_item, args);
        va_end(args);

        if (!val)
            return NULL;

        int count;
        if ((val[0] == '0') && (val[1] == 'x'))
            count = sscanf(val + 2, "%lx", &tmp);
        else
            count = sscanf(val, "%li", &tmp);
        if (count != 1)
            return NULL;
        if ((tmp < 0) || (tmp >= 0x4000))
            return NULL;
    }

    int block = tmp >> 12;
    int addr = tmp & 0xff;

    bdk_device_t *device = bdk_device_lookup(bdk_numa_master(), BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_MIO_TWS), block);
    if (!device)
        return NULL;

    if (device->driver->api != BDK_DEVICE_API_TWSI)
        bdk_fatal("%s: Doesn't support the TWSI API\n", device->name);

    if (dev_addr)
        *dev_addr = addr;
    return device;
}

/**
 * Do a twsi read from a 7 bit device address using an (optional)
 * internal address. Up to 4 bytes can be read at a time.
 *
 * @param device    Device to access
 * @param dev_addr  Device address (7 bit)
 * @param internal_addr
 *                  Internal address.  Can be 0, 1 or 2 bytes in width
 * @param num_bytes Number of data bytes to read (1-4)
 * @param ia_width_bytes
 *                  Internal address size in bytes (0, 1, or 2)
 *
 * @return Read data, or -1 on failure
 */
int64_t bdk_device_twsi_read_ia(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_TWSI)
        bdk_fatal("%s: Doesn't support the TWSI API\n", device->name);
    return device->driver->funcs.twsi.read_ia(device, dev_addr, internal_addr, num_bytes, ia_width_bytes);
}

/**
 * Write 1-8 bytes to a TWSI device using an internal address.
 *
 * @param device    Device to access
 * @param dev_addr  TWSI device address (7 bit only)
 * @param internal_addr
 *                  TWSI internal address (0, 8, or 16 bits)
 * @param num_bytes Number of bytes to write (1-8)
 * @param ia_width_bytes
 *                  internal address width, in bytes (0, 1, 2)
 * @param data      Data to write.  Data is written MSB first on the twsi bus, and
 *                  only the lower num_bytes bytes of the argument are valid.  (If
 *                  a 2 byte write is done, only the low 2 bytes of the argument is
 *                  used.
 *
 * @return Zero on success, -1 on error
 */
int bdk_device_twsi_write_ia(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes, uint64_t data)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_TWSI)
        bdk_fatal("%s: Doesn't support the TWSI API\n", device->name);
    return device->driver->funcs.twsi.write_ia(device, dev_addr, internal_addr, num_bytes, ia_width_bytes, data);
}

/**
 * LED API function to lookup a device in the configuration for use
 * with LED API
 *
 * @param led      LED specified in configuration
 * @param cfg_item Configuration item to lookup
 *
 * @return Pointer to device for API
 */
bdk_device_t* bdk_device_led_lookup(int *led, bdk_config_t cfg_item, ...)
{
    va_list args;
    va_start(args, cfg_item);
    const char *val = bdk_config_get_str_va(cfg_item, args);
    va_end(args);

    if (!val)
        return NULL;

    bdk_device_t *device = bdk_device_lookup_by_name(val);
    if (!device)
        bdk_fatal("Unable to find LED device %s\n", val);

    const char *paren1 = strchr(val, '(');
    if (paren1 && led)
        *led = atoi(paren1 + 1);
    else if (led)
        *led = device->priv.led_gpio.gpio;
    return device;
}

/**
 * LED API function to determine how many LEDs are implemented on this device
 *
 * @param device Device to access
 *
 * @return Number of LEDs
 */
int bdk_device_led_get_num(bdk_device_t *device)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_LED)
        bdk_fatal("%s: Doesn't support the LED API\n", device->name);
    return device->driver->funcs.led.get_num(device);
}

/**
 * LED API function to set the state of a LED
 *
 * @param device Device to access
 * @param led    Which LED to access
 * @param on     True if the LED should be on
 */
void bdk_device_led_set(bdk_device_t *device, int led, bool on)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_LED)
        bdk_fatal("%s: Doesn't support the LED API\n", device->name);
    device->driver->funcs.led.set(device, led, on);
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
int bdk_device_led_attach(bdk_device_t *device, int led, int gpio_pin_sel)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_LED)
        bdk_fatal("%s: Doesn't support the LED API\n", device->name);
    return device->driver->funcs.led.attach(device, led, gpio_pin_sel);
}

/**
 * Network Port API function to lookup a device in the configuration for use
 * with Network Port API
 *
 * @param cfg_item Configuration item to lookup
 *
 * @return Pointer to device for API
 */
bdk_device_t* bdk_device_netport_lookup(bdk_config_t cfg_item, ...)
{
    va_list args;
    va_start(args, cfg_item);
    const char *val = bdk_config_get_str_va(cfg_item, args);
    va_end(args);

    if (!val)
        return NULL;

    bdk_device_t *device = bdk_device_lookup_by_name(val);
    if (!device)
        bdk_fatal("Unable to find network port %s\n", val);
    return device;
}

/**
 * Network Port API function to initialize a port
 *
 * @param device Device to access
 */
void bdk_device_netport_init(bdk_device_t *device)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_NETPORT)
        bdk_fatal("%s: Doesn't support the NETPORT API\n", device->name);
    device->driver->funcs.netport.init(device);
}

/**
 * Network Port API function to set the state of a port
 *
 * @param device     Device to access
 * @param mode       QLM mode of the network port connected to the network port
 * @param baud_mhz   QLM rate in MHz
 * @param allow_link True if a link is allowed on the port
 * @param link_up    True if the current link is up, ready to move data
 */
void bdk_device_netport_set(bdk_device_t *device, bdk_qlm_modes_t mode, int baud_mhz, bool allow_link, bool link_up)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_NETPORT)
        bdk_fatal("%s: Doesn't support the NETPORT API\n", device->name);
    device->driver->funcs.netport.set(device, mode, baud_mhz, allow_link, link_up);
}

/**
 * Network Port API function to get the state of a network port
 *
 * @param device Device to access
 * @param state
 */
void bdk_device_netport_get(bdk_device_t *device, bdk_device_netport_state_t *state)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_NETPORT)
        bdk_fatal("%s: Doesn't support the NETPORT API\n", device->name);
    device->driver->funcs.netport.get(device, state);
}

/**
 * Network port API to force an unplug, regardless if the cable is still connected
 *
 * @param device Device to unplug
 */
void bdk_device_netport_unplug(bdk_device_t *device)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_NETPORT)
        bdk_fatal("%s: Doesn't support the NETPORT API\n", device->name);
    if (device->driver->funcs.netport.unplug)
        device->driver->funcs.netport.unplug(device);
    else
        bdk_error("%s: Port doesn't support forced unplug\n", device->name);
}

/**
 * Network port API to undo a force unplug. For some ports the string
 * argument can be used to control what is plugged in. For example, this
 * selects which emulated ROM is used for SFPs in Asim.
 *
 * @param device Device to plug
 * @param param  Parameter for plug
 */
void bdk_device_netport_plug(bdk_device_t *device, const char *param)
{
    if (!device)
        bdk_fatal("%s: Device is NULL\n", __FUNCTION__);
    if (device->driver->api != BDK_DEVICE_API_NETPORT)
        bdk_fatal("%s: Doesn't support the NETPORT API\n", device->name);
    if (device->driver->funcs.netport.plug)
        device->driver->funcs.netport.plug(device, param);
    else
        bdk_error("%s: Port doesn't support forced plug\n", device->name);
}
