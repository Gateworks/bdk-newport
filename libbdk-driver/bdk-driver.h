/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * bdk_driver_t represents drivers for devices connected using
 * ECAMs. This are discover by scanning the ECAMs and
 * instantiating devices for what is found.
 *
 * @defgroup driver ECAM Attached Drivers
 * @addtogroup driver
 * @{
 */

/**
 * Standard APIs that a device may implement. Devices implementing
 * one of these can be described in the configuration and used seamlessly
 * as a replacement for internal devices.
 */
typedef enum
{
    BDK_DEVICE_API_NONE = 0,        /* Device doesn't implement one of the standard APIs */
    BDK_DEVICE_API_GPIO,            /* Device controls GPIOs */
    BDK_DEVICE_API_TWSI,            /* Device acts like a TWSI bus */
    BDK_DEVICE_API_LED,             /* Device controls LEDs */
    BDK_DEVICE_API_NETPORT,         /* Device implements the networks port API */
    BDK_DEVICE_API_NETPHY,          /* Device implements the network PHY API */
} bdk_driver_api_t;

typedef struct
{
    int (*get_num)(bdk_device_t *device);
    uint64_t (*readstate)(bdk_device_t *device, int group);
    void (*set0)(bdk_device_t *device, int group, uint64_t clear_mask);
    void (*set1)(bdk_device_t *device, int group, uint64_t set_mask);
    void (*setup)(bdk_device_t *device, int gpio, bool is_output, int output_value, bool active_high, bool tristate);
} bdk_driver_api_gpio_t;

typedef struct
{
    int64_t (*read_ia)(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes);
    int (*write_ia)(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes, uint64_t data);
} bdk_driver_api_twsi_t;

typedef struct
{
    int (*get_num)(bdk_device_t *device);
    void (*set)(bdk_device_t *device, int led, bool on);
    int (*attach)(bdk_device_t *device, int led, int gpio_pin_sel);
} bdk_driver_api_led_t;

typedef struct
{
    void (*init)(bdk_device_t *device);
    void (*set)(bdk_device_t *device, bdk_qlm_modes_t mode, int baud_mhz, bool allow_link, bool link_up);
    void (*get)(bdk_device_t *device, bdk_device_netport_state_t *state);
    void (*unplug)(bdk_device_t *device);
    void (*plug)(bdk_device_t *device, const char *param);
} bdk_driver_api_netport_t;

typedef struct
{
    bdk_if_link_t (*get_speed)(bdk_device_t *device, bdk_netphy_t phy);
    int (*init)(bdk_device_t *device, bdk_netphy_t phy);
    int (*loopback)(bdk_device_t *device, bdk_netphy_t phy, bool host_side, bool line_side);
    int (*setup_an)(bdk_device_t *device, bdk_netphy_t phy, int num_modes, bdk_qlm_modes_t qlm_modes[], int qlm_speeds[], bdk_netphy_flags_t flags);
    int (*tune_tx)(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int cmain, int cpre, int cpost);
    int (*get_fom)(bdk_device_t *device, bdk_netphy_t phy, bool host_side);
    int (*eye_capture)(bdk_device_t *device, bdk_netphy_t phy, bool host_side, bdk_qlm_eye_t *eye);
    int (*enable_prbs)(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int prbs, bdk_qlm_direction_t dir);
    int (*disable_prbs)(bdk_device_t *device, bdk_netphy_t phy, bool host_side);
    uint64_t (*get_prbs_errors)(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int lane, int clear);
    void (*inject_prbs_error)(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int lane);
} bdk_driver_api_netphy_t;

/**
 * Defines the main entry points for a device driver
 */
typedef struct bdk_driver_s
{
    struct bdk_driver_s *next;  /* Used by bdk-device to maintian list */
    bdk_driver_api_t api : 32;  /* Standard API implemented by this driver */
    uint32_t id;                /* ECAM device ID */
    const char *name;           /* Driver name */
    void (*add)(bdk_device_t *device, const char *config_str);
    int (*probe)(bdk_device_t *device);
    int (*init)(bdk_device_t *device);
    union                       /* API support functions */
    {
        bdk_driver_api_gpio_t gpio; /* GPIO functions */
        bdk_driver_api_twsi_t twsi; /* TWSI functions */
        bdk_driver_api_led_t led;   /* LED functions */
        bdk_driver_api_netport_t netport; /* Network port functions */
        bdk_driver_api_netphy_t netphy; /* Network PHY functions */
    } funcs;
} bdk_driver_t;

/**
 * Called by the BDK to register all loaded drivers with bdk-device.
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_driver_register_all(void) BDK_WEAK;

/**
 * Called by drivers to parse the config string defined by DEVICES. This searches
 * for a parameter "name" and looks up the device matching it.
 *
 * @param config_str Config string to parse
 * @param name       Name of parameter
 *
 * @return Device found. Fatal error raise on failure
 */
extern bdk_device_t *bdk_driver_extract_device(const char *config_str, const char *name);

/**
 * Called by drivers to parse the config string defined by DEVICES. This searches
 * for a parameter "name" and looks up the device matching it. If there is a value
 * in parens then it is returned in "arg".
 *
 * @param config_str Config string to parse
 * @param name       Name of parameter
 * @param arg        Argument to the device name, or 0 if it was missing
 *
 * @return Device found. Fatal error raise on failure
 */
extern bdk_device_t* bdk_driver_extract_device_arg(const char *config_str, const char *name, int *arg);

/**
 * Called by drivers to parse the config string defined by DEVICES. This searches
 * for a parameter "name" and looks up the integer value.
 *
 * @param config_str Config string to parse
 * @param name       Name of parameter
 * @param min_value  Minimum value of the integer
 * @param max_value  Maximum value of the integer
 *
 * @return Integer value. Fatal error raise on failure
 */
extern int bdk_driver_extract_int(const char *config_str, const char *name, int min_value, int max_value);

/**
 * Tell SCP to start DVFS and program the clocks. Note that this function
 * is called on all chips, even those without a SCP.
 *
 * @return Zero on success, negative on failure
 */
extern int bdK_scp_init_dvfs(void);

/** @} */
