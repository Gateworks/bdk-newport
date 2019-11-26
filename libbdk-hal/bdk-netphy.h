/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to external PHYs connected to QLM/DLM used in networking
 *
 * @addtogroup hal
 * @{
 */

/* The biggest PHY seen has 8 serdes connections for the host. Many
   vendors call these slices, so this define controls the max number of
   slices we support */
#define BDK_NETPHY_MAX_SLICES 8

/**
 * Structure for representing a network PHY
 */
typedef struct
{
    bdk_node_t smi_node;    /* The node of the MDIO/SMI bus */
    int smi_bus;            /* Which SMI/MDIO bus connects to the PHY */
    int smi_address;        /* SMI/MDIO address */
    int num_slices;         /* Number of slices implemented by this PHY */
    struct                  /* List of each QLM lane this PHY connects to */
    {
        bdk_node_t qlm_node;
        int qlm;
        int qlm_lane;
    } slice[BDK_NETPHY_MAX_SLICES];
    void *priv;             /* Pointer for use to PHY driver internals */
} bdk_netphy_state_t;

/**
 * Represents a handle to a network PHY so API calls don't
 * have to continuously pass the full lane specifications.
 */
typedef union
{
    uint32_t u;
    struct
    {
        bool valid : 1;
        bdk_node_t qlm_node : 7;
        int8_t qlm;
        int8_t qlm_lane;
        int8_t slice;
    } s;
} bdk_netphy_t;

typedef enum
{
    BDK_NETPHY_FLAG_NONE,
    BDK_NETPHY_FLAG_FEC = 1,    /* Port uses BASE-R FEC */
    BDK_NETPHY_FLAG_RS_FEC = 2, /* Port uses Reed-Solomon FEC */
} bdk_netphy_flags_t;

/**
 * Convert a uint32_t to a NETPHY handle
 *
 * @param handle
 *
 * @return
 */
static inline bdk_netphy_t bdk_netphy_handle(uint32_t handle)
{
    bdk_netphy_t h;
    h.u = handle;
    return h;
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
extern bdk_netphy_t bdk_netphy_get_handle(bdk_node_t qlm_node, int qlm, int qlm_lane);

/**
 * Get the currently operating speed of the PHY. This is often the results of
 * auto negotiation.
 *
 * @param phy    Handle to PHY to query
 *
 * @return PHY speed
 */
extern bdk_if_link_t bdk_netphy_get_speed(bdk_netphy_t phy);

/**
 * One time initialization of a PHY. Called after networking is started, but before
 * any links are allowed.
 *
 * @param phy    Handle to PHY to initialize
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_netphy_init(bdk_netphy_t phy);

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
extern int bdk_netphy_loopback(bdk_netphy_t phy, bool host_side, bool line_side);

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
extern int bdk_netphy_setup_an(bdk_netphy_t phy, int num_modes, bdk_qlm_modes_t qlm_modes[], int qlm_speeds[], bdk_netphy_flags_t flags);

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
extern int bdk_netphy_tune_tx(bdk_netphy_t phy, bool host_side, int cmain, int cpre, int cpost);

/**
 * Capture a figure of merit (FOM). The result is scaled by the PHY driver
 * such that 0 is bad and 255 is good.
 *
 * @param phy       PHY handle to capture from
 * @param host_side True if the host side should be captured, false if the line side
 *
 * @return FOM value, or negative on failure
 */
extern int bdk_netphy_get_fom(bdk_netphy_t phy, bool host_side);

/**
 * Capture an Eye diagram from the PHY
 *
 * @param phy       PHY handle to capture from
 * @param host_side True if the host side should be captured, false if the line side
 * @param eye       Eye data in the same format as bdk-qlm
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_netphy_eye_capture(bdk_netphy_t phy, bool host_side, bdk_qlm_eye_t *eye);

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
extern int bdk_netphy_enable_prbs(bdk_netphy_t phy, bool host_side, int prbs, bdk_qlm_direction_t dir);

/**
 * Disable PRBS on a PHY
 *
 * @param phy       PHY handle to access
 * @param host_side True if the host side should be enabled, false if the line side
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_netphy_disable_prbs(bdk_netphy_t phy, bool host_side);

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
extern uint64_t bdk_netphy_get_prbs_errors(bdk_netphy_t phy, bool host_side, int lane, int clear);

/**
 * Inject an error into PRBS
 *
 * @param phy       PHY handle to access
 * @param host_side True if the host side should be enabled, false if the line side
 * @param lane      Which lane in the port
 */
extern void bdk_netphy_inject_prbs_error(bdk_netphy_t phy, bool host_side, int lane);

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
extern int bdk_netphy_register(bdk_device_t *device, int slice, bdk_node_t qlm_node, int qlm, int qlm_lane);

/** @} */
