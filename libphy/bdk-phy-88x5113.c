/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "mxdApiTypes.h"
#include "mxdAPI.h"
#include "mxdApiRegs.h"
#include "mxdInitialization.h"
#include "mxdDiagnostics.h"
#include "mxdHwSerdesCntl.h"
#include "mxdHwCntl.h"
#include "mxdAPIInternal.h"

BDK_REQUIRE_DEFINE(DRIVER_NETPHY_88X5113);

typedef struct
{
    MXD_DEV mxddev;
    bdk_device_t *device;
    bool host_line_swapped;
    bdk_spinlock_t lock;
    struct
    {
        bool use_an;
        bool completed_an;
        uint64_t prbs_errors_host;
        uint64_t prbs_errors_line;
    } slice[MXD_NUM_LANES];
} phy_priv_t;

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    device->priv.phy.smi = bdk_driver_extract_int(config_str, "smi", 0, 31);
    device->priv.phy.address = bdk_driver_extract_int(config_str, "addr", 0, 31);
    int qlm = bdk_driver_extract_int(config_str, "qlm", 0, bdk_qlm_get_num(device->node) - 1);
    int qlm_lane = bdk_driver_extract_int(config_str, "qlm_lane", 0, 3);
    int num_lanes = bdk_qlm_get_lanes(device->node, qlm);

    BDK_TRACE(DEVICE, "%s: 88X5113 PHY on SMI=%d, ADDR=%d QLM=%d\n",
        device->name, device->priv.phy.smi, device->priv.phy.address, qlm);

    if (qlm_lane == 3)  // If lanes are swizzled
    {
        if (num_lanes == 2)
        {
            bdk_netphy_register(device, 0, device->node, qlm+1, 1);
            bdk_netphy_register(device, 1, device->node, qlm+1, 0);
        }
        else
        {
            bdk_netphy_register(device, 0, device->node, qlm, 3);
            bdk_netphy_register(device, 1, device->node, qlm, 2);
        }
        bdk_netphy_register(device, 2, device->node, qlm, 1);
        bdk_netphy_register(device, 3, device->node, qlm, 0);
    }
    else
    {
        bdk_netphy_register(device, 0, device->node, qlm, 0);
        bdk_netphy_register(device, 1, device->node, qlm, 1);
        if (num_lanes == 2)
        {
            bdk_netphy_register(device, 2, device->node, qlm+1, 0);
            bdk_netphy_register(device, 3, device->node, qlm+1, 1);
        }
        else
        {
            bdk_netphy_register(device, 2, device->node, qlm, 2);
            bdk_netphy_register(device, 3, device->node, qlm, 3);
        }
    }
}

static MXD_STATUS read_mdio(MXD_DEV_PTR pDev, MXD_U16 mdioPort, MXD_U16 mmd, MXD_U16 reg, MXD_U16 *value)
{
    phy_priv_t *priv = pDev->hostContext;
    int mdio_bus = priv->device->priv.phy.smi;
    int status = bdk_mdio_45_read(priv->device->node, mdio_bus, mdioPort, mmd, reg);
    if (status >= 0)
    {
        *value = status;
        return MXD_OK;
    }
    else
        return MXD_FAIL;
}

static MXD_STATUS write_mdio(MXD_DEV_PTR pDev, MXD_U16 mdioPort, MXD_U16 mmd, MXD_U16 reg, MXD_U16 value)
{
    phy_priv_t *priv = pDev->hostContext;
    int mdio_bus = priv->device->priv.phy.smi;
    if (bdk_mdio_45_write(priv->device->node, mdio_bus, mdioPort, mmd, reg, value))
        return MXD_FAIL;
    else
        return MXD_OK;
}

/**
 * Network Port API function to initialize a port
 *
 * @param device Device to access
 * @param phy    PHY handle
 *
 * @return Zero on success, negative on failure
 */
static int phy_init(bdk_device_t *device, bdk_netphy_t phy)
{
    if (device->priv.phy.priv == NULL)
    {
        phy_priv_t *priv = calloc(1, sizeof(phy_priv_t));
        priv->device = device;
        priv->host_line_swapped = !strncasecmp(bdk_config_get_str(BDK_CONFIG_BOARD_MODEL), "EBB9", 4);
        device->priv.phy.priv = priv;
        MXD_STATUS status = mxdInitDriver(
            read_mdio,
            write_mdio,
            device->priv.phy.address,
            NULL,
            0,
            NULL,
            0,
            NULL,
            0,
            priv,
            &priv->mxddev);
        if (status != MXD_OK)
        {
            bdk_error("%s(%d): mxdInitDriver() failed (MDIO.0x%x), status.0x%lx\n", device->name, phy.s.slice, device->priv.phy.address, status);
            return -1;
        }
        MXD_U16 serdesRevision;
        MXD_U16 sbmRevision;
        status = mxdSerdesGetRevision(&priv->mxddev, &serdesRevision, &sbmRevision);
        if (status != MXD_OK)
        {
            bdk_error("%s: mxdSerdesGetRevision() failed\n", device->name);
            return -1;
        }
        printf("%s: SERDES FW revision 0x%x BUS MASTER FW revision 0x%x\n",
            device->name, serdesRevision, sbmRevision);

        /* EBB9604 88x5113 module LEDs */
        bool is_ebb9 = !strncasecmp(bdk_config_get_str(BDK_CONFIG_BOARD_MODEL), "EBB9", 4);
        if (is_ebb9)
        {
            // GPIO[0] in LED mode
            write_mdio(&priv->mxddev, device->priv.phy.address, 31, 0xF437, 0x8000);
            // LED[0] behavior
            write_mdio(&priv->mxddev, device->priv.phy.address, 31, 0xF438, 0x1160);
            // GPIO[1] in LED mode
            write_mdio(&priv->mxddev, device->priv.phy.address, 31, 0xF439, 0x8000);
            // LED[1] behavior
            write_mdio(&priv->mxddev, device->priv.phy.address, 31, 0xF43A, 0x1160);
            // GPIO[2] in LED mode
            write_mdio(&priv->mxddev, device->priv.phy.address, 31, 0xF43B, 0x8000);
            // LED[2] behavior
            write_mdio(&priv->mxddev, device->priv.phy.address, 31, 0xF43C, 0x1160);
            // GPIO[3] in LED mode
            write_mdio(&priv->mxddev, device->priv.phy.address, 31, 0xF43D, 0x8000);
            // LED[3] behavior
            write_mdio(&priv->mxddev, device->priv.phy.address, 31, 0xF43E, 0x1160);
        }
    }
    return 0;
}

/**
 * Get the currently negotiated speed for the PHY
 *
 * @param device Device to access
 * @param phy    PHY handle
 *
 * @return PHY link status
 */
static bdk_if_link_t phy_get_speed(bdk_device_t *device, bdk_netphy_t phy)
{
    phy_priv_t *priv = device->priv.phy.priv;
    bdk_if_link_t result;
    result.u64 = 0;

    if (!priv->slice[phy.s.slice].use_an)
    {
        /* For repeater mode, nothing to do */
        return result;
    }

    /* Do nothing if AN already completed */
    if (priv->slice[phy.s.slice].completed_an)
        return result;

    MXD_U16 host_side = priv->host_line_swapped ? MXD_LINE_SIDE : MXD_HOST_SIDE;

    bdk_spinlock_lock(&priv->lock);
    MXD_U8 autoNegComplete = -1;
    MXD_STATUS status = mxdAutoNegCheckComplete(&priv->mxddev, phy.s.slice,
        host_side, phy.s.slice, &autoNegComplete);
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdAutoNegCheckComplete() failed", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return result;
    }
    if (!autoNegComplete)
    {
        BDK_TRACE(DEVICE, "%s(%d): 88X5113 PHY AN not complete\n", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return result;
    }

    MXD_U16 speed_bits = 0;
    status = mxdGetAutoNegResolution(&priv->mxddev, phy.s.slice, host_side,
        phy.s.slice, &speed_bits);
    bdk_spinlock_unlock(&priv->lock);
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdGetAutoNegResolution() failed", device->name, phy.s.slice);
        return result;
    }
    BDK_TRACE(DEVICE, "%s(%d): 88X5113 PHY returned speed_bits 0x%x\n", device->name, phy.s.slice, speed_bits);

    /* Sadly the 5113 driver doesn't define any constants for these bits, so we
       have hard coded values. */
    /* 10GB-KR = 0x0008 */
    if (speed_bits & 0x0008)
    {
        result.s.full_duplex = 1;
        result.s.speed = 10000;
        result.s.up = 1;
    }
    /* 40GB-KR4 = 0x0020 */
    /* 40GB-CR4 = 0x0040 */
    else if (speed_bits & 0x0060)
    {
        result.s.full_duplex = 1;
        result.s.lanes = 4;
        result.s.speed = 40000;
        result.s.up = 1;
    }
    /* 100GB-KR4 = 0x0400 */
    /* 100GB-CR4 = 0x0800 */
    else if (speed_bits & 0x0c00)
    {
        result.s.full_duplex = 1;
        result.s.lanes = 4;
        result.s.speed = 100000;
        result.s.up = 1;
    }
    /* 25GB-KR-S/CR-S = 0x1000 */
    /* 25GB-KR/CR     = 0x2000 */
    else if (speed_bits & 0x3000)
    {
        result.s.full_duplex = 1;
        result.s.speed = 25000;
        result.s.up = 1;
    }
    else
        result.u64 = 0;
     return result;
}

/**
 * Control the PHY loopback mode
 *
 * @param device    Device to access
 * @param phy       PHY handle
 * @param host_side True if host TX should loop to host RX
 * @param line_side True if line RX should loop to line TX
 *
 * @return Zero on success, negative in failure
 */
static int phy_loopback(bdk_device_t *device, bdk_netphy_t phy, bool host_side, bool line_side)
{
    phy_priv_t *priv = device->priv.phy.priv;

    /* Swap the host and line loopbacks if PHY is hooked up backwards */
    bool host_enable = priv->host_line_swapped ? line_side : host_side;
    bool line_enable = priv->host_line_swapped ? host_side : line_side;

    bdk_spinlock_lock(&priv->lock);

    MXD_STATUS status = mxdSetHostLoopback(&priv->mxddev,
        device->priv.phy.address, phy.s.slice, MXD_SHALLOW_PCS_LB,
        host_enable ? MXD_ENABLE : MXD_DISABLE);
    if (status != MXD_OK)
    {
        bdk_error("%s: mxdSetHostLoopback() failed", device->name);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }

    status = mxdSetLineLoopback(&priv->mxddev, device->priv.phy.address,
        phy.s.slice, MXD_SHALLOW_PCS_LB, line_enable ? MXD_ENABLE : MXD_DISABLE);
    if (status != MXD_OK)
    {
        bdk_error("%s: mxdSetLineLoopback() failed", device->name);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }
    bdk_spinlock_unlock(&priv->lock);
    return 0;
}

/**
 * Tune the PHYs transmitters
 *
 * @param device
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
static int phy_tune_tx(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int cmain, int cpre, int cpost)
{
    phy_priv_t *priv = device->priv.phy.priv;

    MXD_U16 phy_side = host_side ? MXD_HOST_SIDE : MXD_LINE_SIDE;
    if (priv->host_line_swapped)
        phy_side = host_side ? MXD_LINE_SIDE : MXD_HOST_SIDE;

    int lane = phy.s.slice;

    bdk_spinlock_lock(&priv->lock);

    MXD_STATUS status = mxdSetTxFFE(&priv->mxddev, device->priv.phy.address,
            phy_side, lane, cpre, cmain, cpost, 1);
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdSetTxFFE() failed\n", device->name, lane);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }
    bdk_spinlock_unlock(&priv->lock);
    return 0;
}

/**
 * Setup PHY auto-neg settings
 *
 * @param device     Device to access
 * @param phy        PHY handle
 * @param num_modes  Number of QLM modes/speeds in the following arrays
 * @param qlm_modes  Array of QLM modes to support
 * @param qlm_speeds Array of QLM speeds to support
 *
 * @return Zero on success, negative on failure
 */
static int phy_setup_an(bdk_device_t *device, bdk_netphy_t phy, int num_modes, bdk_qlm_modes_t qlm_modes[], int qlm_speeds[], bdk_netphy_flags_t flags)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (num_modes != 1)
    {
        bdk_error("%s: 88x5113 PHY driver doesn't support AN yet\n", device->name);
        return -1;
    }

    MXD_FIXED_OP_MODE phy_mode = MXD_MODE_R10L_R10L; /* 10G-BASE-R, repeater mode */
    priv->slice[phy.s.slice].use_an = false;
    int num_slices = 1;
    const char *mode_name = "10G-BASE-R";
    switch (qlm_speeds[0])
    {
        case 1250:
            if (qlm_modes[0] == BDK_QLM_MODE_SGMII)
            {
                phy_mode = MXD_MODE_P1X_P1P; /* 1G-BASE-X / SGMII */
                mode_name = "SGMII/1G-X";
                priv->slice[phy.s.slice].use_an = true;
            }
            else
            {
                phy_mode = MXD_MODE_R1_R1; /* 1G-BASE-R, repeater mode */
                mode_name = "1G Repeater";
            }
            break;
        case 10312:
            if (qlm_modes[0] == BDK_QLM_MODE_10G_KR)
            {
                if (flags & BDK_NETPHY_FLAG_FEC)
                {
                    phy_mode = MXD_MODE_P10KF_P10KF; /* 10G-BASE-KR, FEC */
                    mode_name = "10G-KR,FEC";
                    priv->slice[phy.s.slice].use_an = true;
                }
                else
                {
                    phy_mode = MXD_MODE_P10KN_P10KN; /* 10G-BASE-KR, No FEC */
                    mode_name = "10G-KR";
                    priv->slice[phy.s.slice].use_an = true;
                }
            }
            else if (qlm_modes[0] == BDK_QLM_MODE_40G_KR4)
            {
                if (flags & BDK_NETPHY_FLAG_FEC)
                {
                    phy_mode = MXD_MODE_P40KF_P40KF; /* 40G-BASE-KR4, FEC */
                    mode_name = "40G-KR4,FEC";
                    priv->slice[phy.s.slice].use_an = true;
                }
                else
                {
                    phy_mode = MXD_MODE_P40KN_P40KN; /* 40G-BASE-KR4, No FEC */
                    mode_name = "40G-KR4";
                    priv->slice[phy.s.slice].use_an = true;
                }
            }
            else
            {
                phy_mode = MXD_MODE_R10L_R10L; /* 10G-BASE-R, repeater mode */
                mode_name = "10G Repeater";
                if ((qlm_modes[0] == BDK_QLM_MODE_XLAUI) ||
                    (qlm_modes[0] == BDK_QLM_MODE_XLAUI_C2M) ||
                    (qlm_modes[0] == BDK_QLM_MODE_40G_CR4))
                    num_slices = 4;
            }
            break;
        case 20625:
            /* Tell PHY driver to program 20G for 25G mode constants */
            priv->mxddev.use20G = true;
            phy_mode = MXD_MODE_R25L_R25L; /* 25G-BASE-R, repeater mode */
            mode_name = "20G Repeater";
            if (qlm_modes[0] == BDK_QLM_MODE_40GAUI_2_C2C)
                num_slices = 2;
            else if (qlm_modes[0] == BDK_QLM_MODE_80GAUI_4_C2C)
                num_slices = 4;
            break;
        case 25781:
            if (qlm_modes[0] == BDK_QLM_MODE_25G_KR)
            {
                if (flags & BDK_NETPHY_FLAG_RS_FEC)
                {
                    phy_mode = MXD_MODE_P25KR_P25KR; /* 25G-BASE-KR, RS-FEC */
                    mode_name = "25G-KR,RS-FEC";
                    priv->slice[phy.s.slice].use_an = true;
                }
                else
                {
                    phy_mode = MXD_MODE_P25KN_P25KN; /* 25G-BASE-KR, No FEC */
                    mode_name = "25G-KR";
                    priv->slice[phy.s.slice].use_an = true;
                }
            }
            else if (qlm_modes[0] == BDK_QLM_MODE_50G_KR2)
            {
                if (flags & BDK_NETPHY_FLAG_RS_FEC)
                {
                    phy_mode = MXD_MODE_P50JR_P50JR; /* 50G-BASE-KR2, FEC */
                    mode_name = "50G-KR2,RS-FEC";
                    priv->slice[phy.s.slice].use_an = true;
                }
                else
                {
                    phy_mode = MXD_MODE_P50JN_P50JN; /* 50G-BASE-KR2, No FEC */
                    mode_name = "50G-KR2";
                    priv->slice[phy.s.slice].use_an = true;
                }
            }
            else if (qlm_modes[0] == BDK_QLM_MODE_100G_KR4)
            {
                if (flags & BDK_NETPHY_FLAG_RS_FEC)
                {
                    phy_mode = MXD_MODE_P100KR_P100KR; /* 100G-BASE-KR4, RS-FEC */
                    mode_name = "100G-KR4,RS-FEC";
                    priv->slice[phy.s.slice].use_an = true;
                }
                else
                {
                    /* PHY doesn't have a mode constant for 100G No FEC */
                    phy_mode = MXD_MODE_P100KR_P100KR; /* 100G-BASE-KR4, RS-FEC */
                    mode_name = "100G-KR4,RS-FEC";
                    priv->slice[phy.s.slice].use_an = true;
                }
            }
            else
            {
                phy_mode = MXD_MODE_R25L_R25L; /* 25G-BASE-R, repeater mode */
                mode_name = "25G Repeater";
                if ((qlm_modes[0] == BDK_QLM_MODE_50GAUI_2_C2C) ||
                    (qlm_modes[0] == BDK_QLM_MODE_50GAUI_2_C2M) ||
                    (qlm_modes[0] == BDK_QLM_MODE_50G_CR2))
                    num_slices = 2;
                else if ((qlm_modes[0] == BDK_QLM_MODE_CAUI_4_C2C) ||
                    (qlm_modes[0] == BDK_QLM_MODE_CAUI_4_C2M) ||
                    (qlm_modes[0] == BDK_QLM_MODE_100G_CR4))
                    num_slices = 4;
            }
            break;
    }

    for (int i = 0; i < num_slices; i++)
    {
        MXD_U16 error_result = -1;
        MXD_BOOL forceReConfig = (phy.s.slice + i) ? MXD_FALSE : MXD_TRUE;
        printf("%s(%d): Setting %s\n", device->name, phy.s.slice + i, mode_name);
        bdk_spinlock_lock(&priv->lock);
        MXD_STATUS status = mxdSetFixedModeSelection(&priv->mxddev,
            device->priv.phy.address, phy.s.slice + i, phy_mode, forceReConfig,
            &error_result);
        bdk_spinlock_unlock(&priv->lock);
        if ((status != MXD_OK) || error_result)
        {
            bdk_error("%s: mxdSetUserFixedModeSelection() failed, error_result.0x%x\n", device->name, error_result);
            return -1;
        }
    }

    /* EBB9604 88x5113 module LED and polarity inversions */
    bool is_ebb9 = !strncasecmp(bdk_config_get_str(BDK_CONFIG_BOARD_MODEL), "EBB9", 4);
    if (is_ebb9 && (phy.s.slice == 0))
    {
        // Invert host-side input lanes 3 and 1
        // Invert line-side input lanes 1 and 0 and line-side output lanes 3 and 2
        // Invert host-side output lane 2
        MXD_U16 HostRxPolarities[4] = {0,1,0,1};
        MXD_U16 HostTxPolarities[4] = {0,0,1,0};
        MXD_U16 LineRxPolarities[4] = {1,1,0,0};
        MXD_U16 LineTxPolarities[4] = {0,0,1,1};

        bdk_spinlock_lock(&priv->lock);
        for (int lane = 0; lane < 4; lane++)
        {
            MXD_U16 swReset = 1; // SW reset each lane after programming
            MXD_STATUS status = mxdSetRxPolarity(&priv->mxddev,
                device->priv.phy.address, MXD_HOST_SIDE, lane,
                HostRxPolarities[lane], swReset);
            if (status != MXD_OK)
                bdk_error("%s: mxdSetRxPolarity() host lane %d failed\n", device->name, lane);

            status = mxdSetTxPolarity(&priv->mxddev, device->priv.phy.address,
                MXD_HOST_SIDE, lane, HostTxPolarities[lane], swReset);
            if (status != MXD_OK)
                bdk_error("%s: mxdSetTxPolarity() host lane %d failed\n", device->name, lane);

            status = mxdSetRxPolarity(&priv->mxddev, device->priv.phy.address,
                MXD_LINE_SIDE, lane, LineRxPolarities[lane], swReset);
            if (status != MXD_OK)
                bdk_error("%s: mxdSetRxPolarity() line lane %d failed\n", device->name, lane);

            status = mxdSetTxPolarity(&priv->mxddev, device->priv.phy.address,
                MXD_LINE_SIDE, lane, LineTxPolarities[lane], swReset);
            if (status != MXD_OK)
                bdk_error("%s: mxdSetTxPolarity() line lane %d failed\n", device->name, lane);
        }
        bdk_spinlock_unlock(&priv->lock);
    }
    return 0;
}

static int phy_enable_prbs(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int prbs, bdk_qlm_direction_t dir)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (priv == NULL)
    {
        bdk_warn("%s: For PHY PRBS you must first start traffic-gen\n", device->name);
        return -1;
    }
    int lane = phy.s.slice;

    bdk_spinlock_lock(&priv->lock);

    MXD_STATUS status = mxdSetPRBSClearOnRead(&priv->mxddev, priv->mxddev.mdioPort, MXD_HOST_SIDE, lane, 1);
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdSetPRBSClearOnRead() failed\n", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }
    status = mxdSetPRBSClearOnRead(&priv->mxddev, priv->mxddev.mdioPort, MXD_LINE_SIDE, lane, 1);
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdSetPRBSClearOnRead() failed\n", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }


    bool enable_tx = ((dir & BDK_QLM_DIRECTION_TX) != 0);
    bool enable_rx = ((dir & BDK_QLM_DIRECTION_RX) != 0);
    MXD_PRBS_SELECTOR_TYPE linepat;
    switch (prbs)
    {
        case 7:
            linepat = MXD_PRBS7;
            break;
        case 9:
            linepat = MXD_PRBS9;
            break;
        case 13:
            linepat = MXD_PRBS13;
            break;
        case 15:
            linepat = MXD_PRBS15;
            break;
        case 23:
            linepat = MXD_PRBS23;
            break;
        case 31:
            linepat = MXD_PRBS31;
            break;
        default:
            bdk_error("%s(%d): Unsupported PRBS mode %d, using 7\n", device->name, phy.s.slice, prbs);
            linepat = MXD_PRBS7;
            break;
    }

    status = mxdSetLineSidePRBSPattern(&priv->mxddev, priv->mxddev.mdioPort, lane, linepat,
        MXD_PRBS_NONE, MXD_ALL_ZERO);
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdSetLineSidePRBSPattern() failed\n", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }

    status = mxdSetHostSidePRBSPattern(&priv->mxddev, priv->mxddev.mdioPort, lane, linepat,
        MXD_PRBS_NONE, MXD_ALL_ZERO);
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdSetHostSidePRBSPattern() failed\n", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }

    status = mxdSetPRBSEnableTxRx(&priv->mxddev, priv->mxddev.mdioPort,
        (host_side ^ priv->host_line_swapped) ? MXD_HOST_SIDE : MXD_LINE_SIDE,
        lane,
        (enable_tx | enable_rx) ? MXD_ENABLE : MXD_DISABLE, /* TX */
        (enable_rx) ? MXD_ENABLE : MXD_DISABLE); /* RX */
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdSetPRBSEnableTxRx() failed\n", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }
    bdk_spinlock_unlock(&priv->lock);
    return 0;
}

static int phy_disable_prbs(bdk_device_t *device, bdk_netphy_t phy, bool host_side)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (priv == NULL)
        return -1;
    if (!host_side)
        return -1;

    bdk_spinlock_lock(&priv->lock);

    MXD_STATUS status = mxdSetPRBSEnableTxRx(&priv->mxddev, priv->mxddev.mdioPort,
        (host_side) ? MXD_HOST_SIDE : MXD_LINE_SIDE,
        0, /* lane */
        MXD_DISABLE, /* TX */
        MXD_DISABLE); /* RX */
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdSetPRBSEnableTxRx() failed\n", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }
    bdk_spinlock_unlock(&priv->lock);
    return 0;
}

static uint64_t phy_get_prbs_errors(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int lane, int clear)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (priv == NULL)
        return -1;

    MXD_U16 phy_side = host_side ? MXD_HOST_SIDE : MXD_LINE_SIDE;
    if (priv->host_line_swapped)
        phy_side = host_side ? MXD_LINE_SIDE : MXD_HOST_SIDE;

    bdk_spinlock_lock(&priv->lock);

    MXD_BOOL locked = false;
    MXD_STATUS status = mxdGetPRBSLocked(&priv->mxddev, priv->mxddev.mdioPort, phy_side, lane, &locked);
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdGetPRBSLocked() failed\n", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }

    if (!locked)
    {
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }

    MXD_U64 txBitCount;
    MXD_U64 rxBitCount;
    MXD_U64 rxBitErrorCount;

    status = mxdGetPRBSCounts(&priv->mxddev, priv->mxddev.mdioPort, phy_side, lane, &txBitCount, &rxBitCount, &rxBitErrorCount);
    if (status != MXD_OK)
    {
        bdk_error("%s(%d): mxdGetPRBSCounts() failed\n", device->name, phy.s.slice);
        bdk_spinlock_unlock(&priv->lock);
        return -1;
    }

    bdk_spinlock_unlock(&priv->lock);

    if (host_side && !priv->host_line_swapped)
    {
        uint64_t errors = priv->slice[phy.s.slice].prbs_errors_host + rxBitErrorCount;
        priv->slice[phy.s.slice].prbs_errors_host = (clear) ? 0 : errors;
        return errors;
    }
    else
    {
        uint64_t errors = priv->slice[phy.s.slice].prbs_errors_line + rxBitErrorCount;
        priv->slice[phy.s.slice].prbs_errors_line = (clear) ? 0 : errors;
        return errors;
    }
}

static void phy_inject_prbs_error(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int lane)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (priv == NULL)
        return;
    if (priv->host_line_swapped)
        host_side = !host_side;

    bdk_spinlock_lock(&priv->lock);
    MXD_STATUS status = mxdSerdesTxInjectError(&priv->mxddev,
        ((host_side) ? 1 : 5) + phy.s.slice, 1);
    if (status != MXD_OK)
        bdk_error("%s(%d): mxdSerdesTxInjectError() failed\n", device->name, phy.s.slice);
    bdk_spinlock_unlock(&priv->lock);
}

bdk_driver_t __bdk_driver_netphy_88x5113 = {
    .name = "PHY-88X5113",
    .add = add,
    .api = BDK_DEVICE_API_NETPHY,
    .funcs.netphy.init = phy_init,
    .funcs.netphy.get_speed = phy_get_speed,
    .funcs.netphy.loopback = phy_loopback,
    .funcs.netphy.setup_an = phy_setup_an,
    .funcs.netphy.tune_tx = phy_tune_tx,
    .funcs.netphy.enable_prbs = phy_enable_prbs,
    .funcs.netphy.disable_prbs = phy_disable_prbs,
    .funcs.netphy.get_prbs_errors = phy_get_prbs_errors,
    .funcs.netphy.inject_prbs_error = phy_inject_prbs_error,
};
