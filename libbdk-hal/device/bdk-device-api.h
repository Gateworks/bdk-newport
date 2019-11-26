/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Generic API access functions for devices
 *
 * @defgroup device ECAM Attached Devices
 * @addtogroup device
 * @{
 */

/**
 * GPIO API function to lookup a device in the configuration for use
 * with GPIO API
 *
 * @param gpio     GPIO number specified in the configuration
 * @param cfg_item Configuration item to lookup
 *
 * @return Pointer to device for API
 */
extern bdk_device_t *bdk_device_gpio_lookup(int *gpio, bdk_config_t cfg_item, ...);

/**
 * GPIO API function to read the number of GPIOs
 *
 * @param device Device to access
 *
 * @return Number of GPIOs
 */
extern int bdk_device_gpio_get_num(bdk_device_t *device);

/**
 * GPIO API function to read the state of all GPIOs
 *
 * @param device Device to access
 * @param group  Which group of 64 to access
 *
 * @return State of GPIOs as a bitmask
 */
extern uint64_t bdk_device_gpio_readstate(bdk_device_t *device, int group);

/**
 * GPIO API function to drive GPIOs to logic zero
 *
 * @param device     Device to access
 * @param group      Which group of 64 to access
 * @param clear_mask Bitmask of GPIOs to drive to logic zero
 */
extern void bdk_device_gpio_set0(bdk_device_t *device, int group, uint64_t clear_mask);

/**
 * GPIO API function to drive GPIOs to logic one
 *
 * @param device   Device to access
 * @param group    Which group of 64 to access
 * @param set_mask Bitmask of GPIOs to drive to logic one
 */
extern void bdk_device_gpio_set1(bdk_device_t *device, int group, uint64_t set_mask);

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
extern void bdk_device_gpio_setup(bdk_device_t *device, int gpio, bool is_output, int output_value, bool active_high, bool tristate);

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
extern bdk_device_t *bdk_device_twsi_lookup(uint8_t *dev_addr, uint16_t *internal_addr, int *ia_width_bytes, bdk_config_t cfg_item, ...);

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
extern int64_t bdk_device_twsi_read_ia(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes);

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
extern int bdk_device_twsi_write_ia(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes, uint64_t data);

/**
 * LED API function to lookup a device in the configuration for use
 * with LED API
 *
 * @param led      LED specified in configuration
 * @param cfg_item Configuration item to lookup
 *
 * @return Pointer to device for API
 */
extern bdk_device_t *bdk_device_led_lookup(int *led, bdk_config_t cfg_item, ...);

/**
 * LED API function to determine how many LEDs are implemented on this device
 *
 * @param device Device to access
 *
 * @return Number of LEDs
 */
extern int bdk_device_led_get_num(bdk_device_t *device);

/**
 * LED API function to set the state of a LED
 *
 * @param device Device to access
 * @param led    Which LED to access
 * @param on     True if the LED should be on
 */
extern void bdk_device_led_set(bdk_device_t *device, int led, bool on);

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
extern int bdk_device_led_attach(bdk_device_t *device, int led, int gpio_pin_sel);

/**
 * Network Port API function to lookup a device in the configuration for use
 * with Network Port API
 *
 * @param cfg_item Configuration item to lookup
 *
 * @return Pointer to device for API
 */
extern bdk_device_t *bdk_device_netport_lookup(bdk_config_t cfg_item, ...);

/**
 * Network Port API function to initialize a port
 *
 * @param device Device to access
 */
extern void bdk_device_netport_init(bdk_device_t *device);

/**
 * Network Port API function to set the state of a port
 *
 * @param device     Device to access
 * @param mode       QLM mode of the network port connected to the network port
 * @param baud_mhz   QLM rate in MHz
 * @param allow_link True if a link is allowed on the port
 * @param link_up    True if the current link is up, ready to move data
 */
extern void bdk_device_netport_set(bdk_device_t *device, bdk_qlm_modes_t mode, int baud_mhz, bool allow_link, bool link_up);

/**
 * Network port API to force an unplug, regardless if the cable is still connected
 *
 * @param device Device to unplug
 */
extern void bdk_device_netport_unplug(bdk_device_t *device);

/**
 * Network port API to undo a force unplug. For some ports the string
 * argument can be used to control what is plugged in. For example, this
 * selects which emulated ROM is used for SFPs in Asim.
 *
 * @param device Device to plug
 * @param param  Parameter for plug
 */
extern void bdk_device_netport_plug(bdk_device_t *device, const char *param);

/**
 * Flags for describing the state of a network port
 */
typedef enum
{
    BDK_DEVICE_NETPORT_FLAG_MISSING     = 1,    /* Module is missing */
    BDK_DEVICE_NETPORT_FLAG_RX_ERROR    = 2,    /* RX error or fault detected */
    BDK_DEVICE_NETPORT_FLAG_TX_ERROR    = 4,    /* TX error or fault detected */
    BDK_DEVICE_NETPORT_FLAG_DUALLANE    = 8,    /* Port uses two lanes as one port */
    BDK_DEVICE_NETPORT_FLAG_QUADLANE    = 16,   /* Port uses four lanes as one port */
} bdk_device_netport_flag_t;

/**
 * Structure for describing the state of a network port
 */
typedef struct
{
    int max_speed;                              /* Max speed in Mhz */
    bdk_device_netport_flag_t flags;            /* Current flags */
} bdk_device_netport_state_t;

/**
 * Network Port API function to get the state of a network port
 *
 * @param device Device to access
 * @param state
 */
extern void bdk_device_netport_get(bdk_device_t *device, bdk_device_netport_state_t *state);

/** @} */
