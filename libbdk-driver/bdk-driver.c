    /***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER);

/**
 * Called by the BDK to register all loaded drivers with bdk-device.
 *
 * @return Zero on success, negative on failure
 */
int __bdk_driver_register_all(void)
{
    /* All drivers follow a standard naming convention. Use a macro
       to reduce the amount of cut/paste code */
    #define DRIVER(name)                                    \
        extern bdk_driver_t __bdk_driver_##name BDK_WEAK;   \
        if (&__bdk_driver_##name)                           \
            bdk_device_add_driver(&__bdk_driver_##name)

    DRIVER(gpio);
    DRIVER(gpio_console);
    DRIVER(gpio_pca8574);
    DRIVER(gpio_pca9535);
    DRIVER(iobn5);
    DRIVER(led_console);
    DRIVER(led_gpio);
    DRIVER(mcc);
    DRIVER(mdio);
    DRIVER(netphy_88e1514);
    DRIVER(netphy_88x5113);
    DRIVER(netphy_88x5121);
    DRIVER(netphy_88x5123);
    DRIVER(netphy_88x3310p);
    DRIVER(netphy_88x3340p);
    DRIVER(netphy_88x6141);
    DRIVER(netphy_vsc8574);
    DRIVER(netport_console);
    DRIVER(netport_sfp28);
    DRIVER(netport_qsfp28);
    DRIVER(pbus);
    DRIVER(pcieep);
    DRIVER(pcierc);
    DRIVER(pwm_isl6813x);
    DRIVER(rnm);
    DRIVER(sata);
    DRIVER(sata5);
    DRIVER(smmu);
    DRIVER(smmu3);
    DRIVER(twsi);
    DRIVER(twsi_pca9547);
    DRIVER(twsi_pca9548);
    DRIVER(uaa);
    DRIVER(usb);
    DRIVER(xcp);

    return 0;
}

static const char *find_param(const char *name, const char **end_ptr, const char *orig_config_str)
{
    const char *config_str = orig_config_str;
    int name_len = strlen(name);
    while (config_str && *config_str)
    {
        const char *comma = strchr(config_str, ',');
        if (!comma)
            comma = config_str + strlen(config_str);

        if (strncmp(name, config_str, name_len) == 0)
        {
            if (config_str[name_len] == '=')
            {
                *end_ptr = comma;
                return config_str + name_len + 1;
            }
        }
        config_str = (*comma) ? comma + 1 : NULL;
    }
    bdk_fatal("Parameter %s missing from device %s\n", name, orig_config_str);
}

/**
 * Called by drivers to parse the config string defined by DEVICES. This searches
 * for a parameter "name" and looks up the device matching it.
 *
 * @param config_str Config string to parse
 * @param name       Name of parameter
 *
 * @return Device found. Fatal error raise on failure
 */
bdk_device_t *bdk_driver_extract_device(const char *config_str, const char *name)
{
    const char *end_ptr = NULL;
    const char *dev_name = find_param(name, &end_ptr, config_str);
    int param_len = end_ptr - dev_name;
    char *n = alloca(param_len + 1);
    strncpy(n, dev_name, param_len);
    n[param_len] = 0;
    bdk_device_t *dev = bdk_device_lookup_by_name(n);
    if (!dev)
        bdk_fatal("Unable to find device %s for %s in %s\n", n, name, config_str);
    if (!dev->driver)
        bdk_fatal("%s: Doesn't have a driver and it is referenced in %s\n", dev->name, config_str);
    return dev;
}

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
bdk_device_t *bdk_driver_extract_device_arg(const char *config_str, const char *name, int *arg)
{
    *arg = 0;
    const char *end_ptr = NULL;
    const char *dev_name = find_param(name, &end_ptr, config_str);
    int param_len = end_ptr - dev_name;
    char *n = alloca(param_len + 1);
    strncpy(n, dev_name, param_len);
    n[param_len] = 0;
    char *paren = strchr(n, '(');
    if (paren)
    {
        *arg = atoi(paren + 1);
        *paren = 0;
    }
    bdk_device_t *dev = bdk_device_lookup_by_name(n);
    if (!dev)
        bdk_fatal("Unable to find device %s for %s in %s\n", n, name, config_str);
    return dev;
}

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
int bdk_driver_extract_int(const char *config_str, const char *name, int min_value, int max_value)
{
    const char *end_ptr = NULL;
    const char *val_str = find_param(name, &end_ptr, config_str);

    int count;
    int value = -1;
    if ((val_str[0] == '0') && (val_str[1] == 'x'))
        count = sscanf(val_str + 2, "%x", &value);
    else
        count = sscanf(val_str, "%i", &value);

    if ((count != 1) || (value < min_value) || (value > max_value))
        bdk_fatal("Invalid value %d for %s in %s\n", value, name, config_str);
    return value;
}

