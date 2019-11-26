/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "mydApiTypes.h"
#include "mydApiRegs.h"
#include "mydAPI.h"
#include "mydUtils.h"
#include "mydInitialization.h"
#include "mydDiagnostics.h"
#include "mydHwSerdesCntl.h"
#include "mydFwImages.h"

BDK_REQUIRE_DEFINE(DRIVER_NETPHY_88X6141);

typedef struct
{
    MYD_DEV myddev;
    bdk_device_t *device;
    struct
    {
        MYD_PRBS_SELECTOR_TYPE prbs_sel;
        uint64_t prbs_errors_host;
        uint64_t prbs_errors_line;
    } slice[4];
} phy_priv_t;

static MYD_STATUS read_mdio(MYD_DEV_PTR pDev, MYD_U16 mdioPort, MYD_U16 mmd, MYD_U16 reg, MYD_U16* value)
{
    phy_priv_t *priv = pDev->hostContext;
    bdk_device_t *device = priv->device;
    int mdio_bus = device->priv.phy.smi;
    int phy_address = device->priv.phy.address;
    int status = bdk_mdio_45_read(device->node, mdio_bus, phy_address, mmd, reg);
    if (status >= 0)
    {
        *value = status;
        return MYD_OK;
    }
    else
        return MYD_FAIL;
}

static MYD_STATUS write_mdio(MYD_DEV_PTR pDev, MYD_U16 mdioPort, MYD_U16 mmd, MYD_U16 reg, MYD_U16 value)
{
    phy_priv_t *priv = pDev->hostContext;
    bdk_device_t *device = priv->device;
    int mdio_bus = device->priv.phy.smi;
    int phy_address = device->priv.phy.address;
    if (bdk_mdio_45_write(device->node, mdio_bus, phy_address, mmd, reg, value))
        return MYD_FAIL;
    else
        return MYD_OK;
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
    MYD_STATUS status;

    if (device->priv.phy.priv == NULL)
    {
        printf("%s: Initializing the 88X6141 PHY.\n", device->name);
        phy_priv_t *priv = calloc(1, sizeof(phy_priv_t));
        priv->device = device;
        device->priv.phy.priv = priv;
        MYD_U16 x6141_sbus_master_image_size = x6141_sbus_master_image_end - x6141_sbus_master_image_start;
        MYD_U16 x6141_serdes_image_size = x6141_serdes_image_end - x6141_serdes_image_start;
        status = mydInitDriver(
            read_mdio,
            write_mdio,
            device->priv.phy.address,
            NULL,
            0,
            x6141_sbus_master_image_start,
            x6141_sbus_master_image_size,
            x6141_serdes_image_start,
            x6141_serdes_image_size,
            priv,
            &priv->myddev);
        if (status != MYD_OK)
        {
            bdk_error("%s: mydInitDriver() failed\n", device->name);
            return -1;
        }
        MYD_U16 serdesRevision = 0;
        MYD_U16 sbmRevision = 0;
        status = mydSerdesGetRevision(&priv->myddev,
                                      device->priv.phy.address,
                                      &serdesRevision, &sbmRevision);
        if (status != MYD_OK)
        {
            bdk_error("%s: mydSerdesGetRevision() failed\n", device->name);
            return -1;
        }
        printf("%s: SERDES FW revision 0x%x BUS MASTER FW revision 0x%x\n",
               device->name, serdesRevision, sbmRevision);
    }

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
    MYD_STATUS status;
    MYD_U16 result;
    MYD_OP_MODE host_mode, line_mode;

    if (num_modes != 1)
    {
        bdk_error("%s: 88X6141 PHY driver doesn't support AN yet\n", device->name);
        return -1;
    }

    const char *qlm_mode_str = bdk_qlm_mode_tostring(qlm_modes[0]);

    switch (qlm_modes[0])
    {
        case BDK_QLM_MODE_10G_KR:
            host_mode = MYD_P10KN; /* 10GBASE-KR, no FEC */
            line_mode = MYD_P10LN; /* 10GBASE-LR/SR */
            break;

        case BDK_QLM_MODE_25GAUI_C2C:
            host_mode = MYD_P25LR; /* 25GBASE-R, RS-FEC, no AN */
            line_mode = MYD_P25LN; /* 25GBASE-R, no FEC, no AN */
            break;

	case BDK_QLM_MODE_25GAUI_2_C2C:
            host_mode = MYD_P25YN; /* 25GBASE-R2, no FEC, no AN */
            line_mode = MYD_P25LN; /* 25GBASE-R, no FEC, no AN */
            break;

        case BDK_QLM_MODE_50GAUI_2_C2C:
            host_mode = MYD_P50MR; /* 50GBASE-R2, RS-FEC, no AN */
            line_mode = MYD_P50MN; /* 50GBASE-R2, no FEC, no AN */
            break;

        case BDK_QLM_MODE_50GAUI_4_C2C:
            host_mode = MYD_P50LN; /* 50GBASE-R4, no FEC, no AN */
            line_mode = MYD_P50MN; /* 50GBASE-R2, no FEC, no AN */
            break;

        default:
            bdk_error("%s: QLM mode %s is not supported for 88X6141 PHY\n", device->name, qlm_mode_str);
            return -1;
            break;
    }

    phy_priv_t *priv = device->priv.phy.priv;
    status = mydSetModeSelection(&priv->myddev,
                                 device->priv.phy.address,
                                 phy.s.slice,
                                 host_mode,
                                 line_mode,
                                 MYD_MODE_ICAL_EFFORT_0,
                                 &result);

    if (status != MYD_OK)
    {
        bdk_error("%s(%d): mydSetModeSelection() failed, result=%hu\n",
                  device->name, phy.s.slice, result);
        return -1;
    }

    if (host_mode == MYD_P25YN) {
        /* Hack the P25YN mode to make its 25GBASE-R2 PCS conform to ours.
         * Our 25GBASE-R2 looks like a scaled down 50GBASE-R2.
         * These settings came from the 6141 design team.
         */

        /* fix alignment markers */
        write_mdio(&priv->myddev, 0, MYD_HOST_SIDE, 0xF06C, 0xF000);

        /* host-side sw reset */
        write_mdio(&priv->myddev, 0, MYD_PORT_REG,  0xF003, 0x0080);
    }

    return 0;
}

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    const char *qlm_mode_str[2];
    int qlm_mode[2];
    int qlm[2];
    int is_true_qlm[2];
    int i;

    device->priv.phy.smi = bdk_driver_extract_int(config_str, "smi", 0, 2);
    device->priv.phy.address = bdk_driver_extract_int(config_str, "addr", 0, 31);
    qlm[0] = bdk_driver_extract_int(config_str, "qlm0", 0, bdk_qlm_get_num(device->node) - 1);
    if (qlm[0] == 4 || qlm[0] == 5)
    {
        is_true_qlm[0] = false;
        /* "qlm0" is actually a DLM.  Get the second DLM (or QLM) specified by "qlm1". */
        qlm[1] = bdk_driver_extract_int(config_str, "qlm1", 0, bdk_qlm_get_num(device->node) - 1);
        if (qlm[1] == 4 || qlm[1] == 5)
            is_true_qlm[1] = false;
        else
            is_true_qlm[1] = true;
    }
    else
    {
        is_true_qlm[0] = true;
        /* "qlm0" is a true QLM. Assign -1 to qlm[1] to indicate there is no second QLM. */
        qlm[1] = -1;
        is_true_qlm[1] = false;
    }

    BDK_TRACE(DEVICE, "%s: 88X6141 PHY on SMI=%d, ADDR=%d QLM0=%d, QLM1=%d\n",
        device->name, device->priv.phy.smi, device->priv.phy.address, qlm[0], qlm[1]);

    for (i = 0; i < 2; i++)
    {
        if (qlm[i] < 0)
            continue;

        qlm_mode_str[i] = bdk_config_get_str(BDK_CONFIG_QLM_MODE, device->node, qlm[i]);
        qlm_mode[i] = bdk_qlm_cfg_string_to_mode(qlm_mode_str[i]);

        switch (qlm_mode[i])
        {
            case BDK_QLM_MODE_10G_KR:
            case BDK_QLM_MODE_25GAUI_C2C:
                bdk_netphy_register(device, 0 + (i << 1), device->node, qlm[i], 0);
                bdk_netphy_register(device, 1 + (i << 1), device->node, qlm[i], 1);
                if (i == 0 && is_true_qlm[0])
                {
                    bdk_netphy_register(device, 2, device->node, qlm[i], 2);
                    bdk_netphy_register(device, 3, device->node, qlm[i], 3);
                }
                break;

            case BDK_QLM_MODE_50GAUI_2_C2C:
            case BDK_QLM_MODE_25GAUI_2_C2C:
                bdk_netphy_register(device, 0 + (i << 1), device->node, qlm[i], 0);
                if (i == 0 && is_true_qlm[0])
                    bdk_netphy_register(device, 2, device->node, qlm[i], 2);
                break;

            case BDK_QLM_MODE_50GAUI_4_C2C:
                if (i != 0)
                    break;
                bdk_netphy_register(device, 0, device->node, qlm[i], 0);
                break;

            default:
                bdk_error("%s: QLM mode %s is not supported for 88X6141 PHY\n", device->name, qlm_mode_str[i]);
                break;
        }
    }
}

static int phy_enable_prbs(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int prbs, bdk_qlm_direction_t dir)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (!priv)
    {
        bdk_warn("%s: For PHY PRBS you must first start traffic-gen\n", device->name);
        return -1;
    }

    MYD_STATUS status = mydSetPRBSClearOnRead(
        &priv->myddev,
        device->priv.phy.address,
        MYD_HOST_SIDE,
        phy.s.slice,
        1);
    if (status != MYD_OK)
    {
        bdk_error("%s(%d): mydSetPRBSClearOnRead() for host side failed\n", device->name, phy.s.slice);
        return -1;
    }

    status = mydSetPRBSClearOnRead(
        &priv->myddev,
        device->priv.phy.address,
        MYD_LINE_SIDE,
        phy.s.slice,
        1);
    if (status != MYD_OK)
    {
        bdk_error("%s(%d): mydSetPRBSClearOnRead() for line side failed\n", device->name, phy.s.slice);
        return -1;
    }

    MYD_PRBS_SELECTOR_TYPE prbs_sel;
    switch (prbs)
    {
        case 7:
            prbs_sel = MYD_PRBS7;
            break;
        case 9:
            prbs_sel = MYD_PRBS9;
            break;
        case 13:
            prbs_sel = MYD_PRBS13;
            break;
        case 15:
            prbs_sel = MYD_PRBS15;
            break;
        case 23:
            prbs_sel = MYD_PRBS23;
            break;
        case 31:
            prbs_sel = MYD_PRBS31;
            break;
        default:
            bdk_error("%s(%d): Unsupported PRBS mode %d, using 7\n", device->name, phy.s.slice, prbs);
            prbs_sel = MYD_PRBS7;
            break;
    }
    priv->slice[phy.s.slice].prbs_sel = prbs_sel;

    status = mydSetPRBSPattern(
        &priv->myddev,
        device->priv.phy.address,
        MYD_LINE_SIDE,
        phy.s.slice,
        prbs_sel,
        MYD_PRBS_NONE);
    if (status != MYD_OK)
    {
        bdk_error("%s(%d): mydSetPRBSPattern() for line side failed\n", device->name, phy.s.slice);
        return -1;
    }

    status = mydSetPRBSPattern(
        &priv->myddev,
        device->priv.phy.address,
        MYD_HOST_SIDE,
        phy.s.slice,
        prbs_sel,
        MYD_PRBS_NONE);
    if (status != MYD_OK)
    {
        bdk_error("%s(%d): mydSetPRBSPattern() for host side failed\n", device->name, phy.s.slice);
        return -1;
    }

    bool enable_tx = ((dir & BDK_QLM_DIRECTION_TX) != 0);
    bool enable_rx = ((dir & BDK_QLM_DIRECTION_RX) != 0);

    status = mydSetPRBSEnableTxRx(
        &priv->myddev,
        device->priv.phy.address,
        host_side ? MYD_HOST_SIDE : MYD_LINE_SIDE,
        phy.s.slice,
        (enable_tx | enable_rx) ? MYD_ENABLE : MYD_DISABLE, /* TX */
        (enable_rx) ? MYD_ENABLE : MYD_DISABLE, /* RX */
        prbs_sel);
    if (status != MYD_OK)
    {
        bdk_error("%s(%d): mydSetPRBSEnableTxRx() failed\n", device->name, phy.s.slice);
        return -1;
    }

    return 0;
}

static int phy_disable_prbs(bdk_device_t *device, bdk_netphy_t phy, bool host_side)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (!priv)
        return -1;

    MYD_STATUS status = mydSetPRBSEnableTxRx(
        &priv->myddev,
        device->priv.phy.address,
        host_side ? MYD_HOST_SIDE : MYD_LINE_SIDE,
        phy.s.slice,
        MYD_DISABLE, /* TX */
        MYD_DISABLE, /* RX */
        priv->slice[phy.s.slice].prbs_sel);
    if (status != MYD_OK)
    {
        bdk_error("%s(%d): mydSetPRBSEnableTxRx() failed\n", device->name, phy.s.slice);
        return -1;
    }

    mydLaneSoftReset(
        &priv->myddev,
        device->priv.phy.address,
        host_side ? MYD_HOST_SIDE : MYD_LINE_SIDE,
        phy.s.slice,
        10);

    return 0;
}

static uint64_t phy_get_prbs_errors(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int lane, int clear)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (!priv)
        return -1;

    MYD_BOOL prbsLocked;
    MYD_STATUS status = mydGetPRBSLocked(
        &priv->myddev,
        device->priv.phy.address,
        host_side ? MYD_HOST_SIDE : MYD_LINE_SIDE,
        phy.s.slice,
        &prbsLocked);
    if (status != MYD_OK)
    {
        bdk_error("%s(%d): mydGetPRBSLocked() failed\n", device->name, phy.s.slice);
        return -1;
    }
    if (!prbsLocked)
    {
        bdk_error("%s(%d): did not get PRBS lock\n", device->name, phy.s.slice);
        return -1;
    }

    MYD_U64 txBitCount, rxBitCount, rxBitErrorCount;

    status = mydGetPRBSCounts(
        &priv->myddev,
        device->priv.phy.address,
        host_side ? MYD_HOST_SIDE : MYD_LINE_SIDE,
        phy.s.slice,
        priv->slice[phy.s.slice].prbs_sel,
        &txBitCount, &rxBitCount, &rxBitErrorCount);
    if (status != MYD_OK)
    {
        bdk_error("%s(%d): mydGetPRBSCounts() failed\n", device->name, phy.s.slice);
        return -1;
    }

    if (host_side)
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
    if (!priv)
        return;

    MYD_U16 sAddr;
    mydGetSerdesAddress(
        &priv->myddev,
        device->priv.phy.address,
        host_side ? MYD_HOST_SIDE : MYD_LINE_SIDE,
        phy.s.slice,
        &sAddr);

    MYD_STATUS status = mydSerdesTxInjectError(&priv->myddev, sAddr, 1);
    if (status != MYD_OK)
        bdk_error("%s(%d): mydSerdesTxInjectError() failed\n", device->name, phy.s.slice);
}

bdk_driver_t __bdk_driver_netphy_88x6141 = {
    .name = "PHY-88X6141",
    .add = add,
    .api = BDK_DEVICE_API_NETPHY,
    .funcs.netphy.init = phy_init,
    .funcs.netphy.setup_an = phy_setup_an,
    .funcs.netphy.enable_prbs = phy_enable_prbs,
    .funcs.netphy.disable_prbs = phy_disable_prbs,
    .funcs.netphy.get_prbs_errors = phy_get_prbs_errors,
    .funcs.netphy.inject_prbs_error = phy_inject_prbs_error,
};
