/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

#define MAX_PHYS 32

struct
{
    bdk_device_t *device;
    bdk_netphy_t handle;
} phy_table[MAX_PHYS];

/**
 * Get the actual PHY device used by a handle
 *
 * @param phy    Handle to get
 *
 * @return PHY device or NULL on failure
 */
static bdk_device_t* phy_get_device(bdk_netphy_t phy)
{
    for (int i = 0; i < MAX_PHYS; i++)
    {
        if (phy_table[i].handle.u == phy.u)
            return phy_table[i].device;
    }
    return NULL;
}

/**
 * Return a PHY handle for the given QLM lane. The handle simplifies future
 * calls to the PHY API.
 *
 * @param qlm_node Node the QLM is on
 * @param qlm      Which QLM
 * @param qlm_lane Which lane inside the QLM
 *
 * @return Handle to the PHY. If a PHY isn't found, a zero handle is returned. The zero
 *         handle safely does nothing in future API calls.
 */
bdk_netphy_t bdk_netphy_get_handle(bdk_node_t qlm_node, int qlm, int qlm_lane)
{
    for (int i = 0; i < MAX_PHYS; i++)
    {
        if (!phy_table[i].handle.s.valid)
            continue;
        if (phy_table[i].handle.s.qlm_node != qlm_node)
            continue;
        if (phy_table[i].handle.s.qlm != qlm)
            continue;
        if (phy_table[i].handle.s.qlm_lane != qlm_lane)
            continue;
        return phy_table[i].handle;
    }

    bdk_netphy_t zero;
    zero.u = 0;
    return zero;
}

/**
 * Get the currently operating speed of the PHY. This is often the results of
 * auto negotiation.
 *
 * @param phy    Handle to PHY to query
 *
 * @return PHY speed
 */
bdk_if_link_t bdk_netphy_get_speed(bdk_netphy_t phy)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.get_speed)
        return device->driver->funcs.netphy.get_speed(device, phy);

    bdk_if_link_t speed;
    speed.u64 = 0;
    return speed;
}

/**
 * One time initialization of a PHY. Called after networking is started, but before
 * any links are allowed.
 *
 * @param phy    Handle to PHY to initialize
 *
 * @return Zero on success, negative on failure
 */
int bdk_netphy_init(bdk_netphy_t phy)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.init)
        return device->driver->funcs.netphy.init(device, phy);
    return 0;
}

/**
 * Setup the PHY in loopback mode
 *
 * @param phy       PHY handle to access
 * @param host_side True if the host's data should return to the host. False if the host data is
 *                  forwarded to the line.
 * @param line_side True if the line side's data should return out the line side. The host may or
 *                  may not received the line side also, depending on the PHY and driver
 *                  capabilities.
 *
 * @return Zero on success, negative on failure
 */
int bdk_netphy_loopback(bdk_netphy_t phy, bool host_side, bool line_side)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.loopback)
        return device->driver->funcs.netphy.loopback(device, phy, host_side, line_side);
    bdk_error("%s: Loopback not supported\n", device->name);
    return -1;
}

/**
 * Setup the PHY to advertise specific AN modes
 *
 * @param phy        PHY handle to setup
 * @param num_modes  Number of QLM modes in the list
 * @param qlm_modes  List of QLM modes to allow
 * @param qlm_speeds List of QLM speeds to allow
 * @param flags      Optional mode flags
 *
 * @return Zero on success, negative on failure
 */
int bdk_netphy_setup_an(bdk_netphy_t phy, int num_modes, bdk_qlm_modes_t qlm_modes[], int qlm_speeds[], bdk_netphy_flags_t flags)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.setup_an)
        return device->driver->funcs.netphy.setup_an(device, phy, num_modes, qlm_modes, qlm_speeds, flags);
    return 0;
}

/**
 * Tune the PHYs transmitters
 *
 * @param phy       PHY handle to tune
 * @param host_side True if the host side should be tuned, false if the line side
 * @param cmain     Main tap value (0-255). The driver converts this value to whatever the PHY
 *                  hardware requires. 0 is minimum amplitide, while 255 is max.
 * @param cpre      Pre tap value (0-255). The driver converts this value to whatever the PHY
 *                  hardware requires. 0 is none, while 255 is max.
 * @param cpost     Post tap value (0-255). The driver converts this value to whatever the PHY
 *                  hardware requires. 0 is none, while 255 is max.
 *
 * @return Zero on success, negative on failure
 */
int bdk_netphy_tune_tx(bdk_netphy_t phy, bool host_side, int cmain, int cpre, int cpost)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.tune_tx)
        return device->driver->funcs.netphy.tune_tx(device, phy, host_side, cmain, cpre, cpost);
    bdk_error("%s: Tuning not supported\n", device->name);
    return -1;
}

/**
 * Capture a figure of merit (FOM). The result is scaled by the PHY driver
 * such that 0 is bad and 255 is good.
 *
 * @param phy       PHY handle to capture from
 * @param host_side True if the host side should be captured, false if the line side
 *
 * @return FOM value, or negative on failure
 */
int bdk_netphy_get_fom(bdk_netphy_t phy, bool host_side)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.get_fom)
        return device->driver->funcs.netphy.get_fom(device, phy, host_side);
    bdk_error("%s: FOM not supported\n", device->name);
    return -1;
}

/**
 * Capture an Eye diagram from the PHY
 *
 * @param phy       PHY handle to capture from
 * @param host_side True if the host side should be captured, false if the line side
 * @param eye       Eye data in the same format as bdk-qlm
 *
 * @return Zero on success, negative on failure
 */
int bdk_netphy_eye_capture(bdk_netphy_t phy, bool host_side, bdk_qlm_eye_t *eye)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.eye_capture)
        return device->driver->funcs.netphy.eye_capture(device, phy, host_side, eye);
    bdk_error("%s: Eye capture not supported\n", device->name);
    return -1;
}
/**
 * Enable PRBS on a PHY
 *
 * @param phy       PHY handle to access
 * @param host_side True if the host side should be enabled, false if the line side
 * @param prbs      PRBS mode (31, etc)
 * @param dir       Directions to enable. This is so you can enable TX and later
 *                  enable RX after TX has run for a time
 *
 * @return Zero on success, negative on failure
 */
int bdk_netphy_enable_prbs(bdk_netphy_t phy, bool host_side, int prbs, bdk_qlm_direction_t dir)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.enable_prbs)
        return device->driver->funcs.netphy.enable_prbs(device, phy, host_side, prbs, dir);
    bdk_error("%s: PRBS not supported\n", device->name);
    return -1;
}

/**
 * Disable PRBS on a PHY
 *
 * @param phy       PHY handle to access
 * @param host_side True if the host side should be enabled, false if the line side
 *
 * @return Zero on success, negative on failure
 */
int bdk_netphy_disable_prbs(bdk_netphy_t phy, bool host_side)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.disable_prbs)
        return device->driver->funcs.netphy.disable_prbs(device, phy, host_side);
    //bdk_error("%s: PRBS not supported\n", device->name);
    return -1;
}

/**
 * Return the number of PRBS errors since PRBS started running
 *
 * @param phy       PHY handle to access
 * @param host_side True if the host side should be enabled, false if the line side
 * @param lane      Which lane in the port
 * @param clear     Clear the counter after returning its value
 *
 * @return Number of errors
 */
uint64_t bdk_netphy_get_prbs_errors(bdk_netphy_t phy, bool host_side, int lane, int clear)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.get_prbs_errors)
        return device->driver->funcs.netphy.get_prbs_errors(device, phy, host_side, lane, clear);
    return -1;
}

/**
 * Inject an error into PRBS
 *
 * @param phy       PHY handle to access
 * @param host_side True if the host side should be enabled, false if the line side
 * @param lane      Which lane in the port
 */
void bdk_netphy_inject_prbs_error(bdk_netphy_t phy, bool host_side, int lane)
{
    bdk_device_t *device = phy_get_device(phy);
    if (device && device->driver->funcs.netphy.inject_prbs_error)
        return device->driver->funcs.netphy.inject_prbs_error(device, phy, host_side, lane);
    bdk_error("%s(%d): PRBS error injection not supported\n", device->name, lane);
}

/**
 * Register a PHY device with the API
 *
 * @param device   Device representing the PHY
 * @param slice    Which slice is being registered
 * @param qlm_node The node for the QLM this slice connects to
 * @param qlm      The qlm this slice connects to
 * @param qlm_lane The lane inside the qlm this slice connects to
 *
 * @return Zero on success, negative on failure
 */
int bdk_netphy_register(bdk_device_t *device, int slice, bdk_node_t qlm_node, int qlm, int qlm_lane)
{
    if (!device->driver)
        return 0;
    if (device->driver->api != BDK_DEVICE_API_NETPHY)
        bdk_fatal("%s: Doesn't support the NETPHY API\n", device->name);

    bdk_netphy_t handle = bdk_netphy_get_handle(qlm_node, qlm, qlm_lane);
    if (handle.s.valid)
    {
        bdk_error("%s: Requested a QLM lane already connected to another PHY\n",
            device->name);
        return -1;
    }
    for (int i = 0; i < MAX_PHYS; i++)
    {
        if (phy_table[i].handle.s.valid)
            continue;
        phy_table[i].device = device;
        phy_table[i].handle.s.valid = true;
        phy_table[i].handle.s.qlm_node = qlm_node;
        phy_table[i].handle.s.qlm = qlm;
        phy_table[i].handle.s.qlm_lane = qlm_lane;
        phy_table[i].handle.s.slice = slice;
        return 0;
    }
    bdk_error("%s: Too many PHYs\n", device->name);
    return -1;
}

