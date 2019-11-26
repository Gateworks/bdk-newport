/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER_NETPORT_CONSOLE);

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    BDK_TRACE(DEVICE, "%s: NETPORT console added\n", device->name);
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
 * Network Port API function to initialize a port
 *
 * @param device Device to access
 */
static void netport_init(bdk_device_t *device)
{
    printf("%s: Initialized\n", device->name);
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
static void netport_set(bdk_device_t *device, bdk_qlm_modes_t mode, int baud_mhz, bool allow_link, bool link_up)
{
    printf("%s: Set mode %s, baud %d, allow_link=%d, link %s\n",
        device->name, bdk_qlm_mode_tostring(mode), baud_mhz, allow_link,
        link_up ? "up" : "down");
}

/**
 * Network Port API function to get the state of a network port
 *
 * @param device Device to access
 * @param state
 */
static void netport_get(bdk_device_t *device, bdk_device_netport_state_t *state)
{
    state->max_speed = 100000;
    state->flags = 0;
}

bdk_driver_t __bdk_driver_netport_console = {
    .name = "NETPORT-CONSOLE",
    .add = add,
    .init = init,
    .api = BDK_DEVICE_API_NETPORT,
    .funcs.netport.init = netport_init,
    .funcs.netport.set = netport_set,
    .funcs.netport.get = netport_get,
};
