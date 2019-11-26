/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "mcdApiTypes.h"
#include "mcdApiRegs.h"
#include "mcdAPI.h"
#include "mcdAPIInternal.h"
#include "mcdUtils.h"
#include "mcdInitialization.h"
#include "mcdDiagnostics.h"
#include "mcdFwDownload.h"
#include "mcdServiceCpuCm3BvFw.h"
#include "mcd_sbus_master.0x101A_0001.h"
#include "mcd_serdes.0x2464_0245swap.h"
#include "mcd_serdes.0x2464_0245.h"

BDK_REQUIRE_DEFINE(DRIVER_NETPHY_88X5123);

typedef struct
{
    MCD_DEV mcddev;
    bdk_device_t *device;
    bool init_complete;
    struct
    {
        bool use_an;
        bool completed_an;
        uint64_t prbs_errors_host;
        uint64_t prbs_errors_line;
        int8_t cmain_host;
        int8_t cpre_host;
        int8_t cpost_host;
        int8_t cmain_line;
        int8_t cpre_line;
        int8_t cpost_line;
        int8_t tx_lane_host;
        int8_t rx_lane_host;
        int8_t tx_lane_line;
        int8_t rx_lane_line;
    } slice[8];
} phy_priv_t;

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    device->priv.phy.smi = bdk_driver_extract_int(config_str, "smi", 0, 2);
    device->priv.phy.address = bdk_driver_extract_int(config_str, "addr", 0, 31);
    int qlm0 = bdk_driver_extract_int(config_str, "qlm0", 0, bdk_qlm_get_num(device->node) - 1);
    int qlm1 = bdk_driver_extract_int(config_str, "qlm1", 0, bdk_qlm_get_num(device->node) - 1);
    int host_order0 = bdk_driver_extract_int(config_str, "host_order0", 0, 0x3210);
    int line_order0 = bdk_driver_extract_int(config_str, "line_order0", 0, 0x3210);
    int host_order1 = bdk_driver_extract_int(config_str, "host_order1", 0, 0x3210);
    int line_order1 = bdk_driver_extract_int(config_str, "line_order1", 0, 0x3210);

    BDK_TRACE(DEVICE, "%s: 88X5123 PHY on SMI=%d, ADDR=%d QLM0=%d, QLM1=%d\n",
        device->name, device->priv.phy.smi, device->priv.phy.address, qlm0, qlm1);

    /* Allocate structure for PHY data */
    phy_priv_t *priv = calloc(1, sizeof(phy_priv_t));
    priv->device = device;
    device->priv.phy.priv = priv;

    /* Record order of Line side lanes */
    for (int slice = 0; slice < 4; slice++)
    {
        if (host_order0)
            priv->slice[slice].tx_lane_host = (host_order0 >> (4 * slice)) & 0xf;
        else
            priv->slice[slice].tx_lane_host = slice;
        priv->slice[slice].rx_lane_host = priv->slice[slice].tx_lane_host;

        if (line_order0)
            priv->slice[slice].tx_lane_line = (line_order0 >> (4 * slice)) & 0xf;
        else
            priv->slice[slice].tx_lane_line = slice;
        priv->slice[slice].rx_lane_line = priv->slice[slice].tx_lane_line;

        if (host_order1)
            priv->slice[slice + 4].tx_lane_host = (host_order1 >> (4 * slice)) & 0xf;
        else
            priv->slice[slice + 4].tx_lane_host = slice;
        priv->slice[slice + 4].rx_lane_host = priv->slice[slice + 4].tx_lane_host;

        if (line_order1)
            priv->slice[slice + 4].tx_lane_line = (line_order1 >> (4 * slice)) & 0xf;
        else
            priv->slice[slice + 4].tx_lane_line = slice;
        priv->slice[slice + 4].rx_lane_line = priv->slice[slice + 4].tx_lane_line;
    }

    /* Record SERDES tuning */
    for (int i = 0; i < 8; i++)
    {
        priv->slice[i].cmain_host = 14; /* ~1/2 the max amplitude. Setting based on FIO 20G tuning */
        priv->slice[i].cpre_host = 0;   /* Setting based on FIO 20G tuning */
        priv->slice[i].cpost_host = 1;  /* Setting based on FIO 20G tuning */
        priv->slice[i].cmain_line = 1;  /* Copied from mcdSerdesTxRxTuneParamsArray */
        priv->slice[i].cpre_line = 0;   /* Copied from mcdSerdesTxRxTuneParamsArray */
        priv->slice[i].cpost_line = 6;  /* Copied from mcdSerdesTxRxTuneParamsArray */
    }

    /* Register slice to QLM lane mappings */
    for (int slice = 0; slice < 4; slice++)
    {
        bdk_netphy_register(device, slice, device->node, qlm0, priv->slice[slice].tx_lane_host);
        bdk_netphy_register(device, slice + 4, device->node, qlm1, priv->slice[slice + 4].tx_lane_host);
    }
}

static MCD_STATUS read_mdio(MCD_DEV_PTR pDev, MCD_U16 mdioPort, MCD_U16 mmd, MCD_U16 reg, MCD_U16 *value)
{
    phy_priv_t *priv = pDev->hostContext;
    int mdio_bus = priv->device->priv.phy.smi;
    int status = bdk_mdio_45_read(priv->device->node, mdio_bus, mdioPort, mmd, reg);
    if (status >= 0)
    {
        *value = status;
        return MCD_OK;
    }
    else
        return MCD_FAIL;
}

static MCD_STATUS write_mdio(MCD_DEV_PTR pDev, MCD_U16 mdioPort, MCD_U16 mmd, MCD_U16 reg, MCD_U16 value)
{
    phy_priv_t *priv = pDev->hostContext;
    int mdio_bus = priv->device->priv.phy.smi;
    if (bdk_mdio_45_write(priv->device->node, mdio_bus, mdioPort, mmd, reg, value))
        return MCD_FAIL;
    else
        return MCD_OK;
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
    phy_priv_t *priv = device->priv.phy.priv;
    if (!priv->init_complete)
    {
        priv->init_complete = true;
        printf("%s(%d): Loading 88x5123 firmware...\n", device->name, phy.s.slice);
        MCD_STATUS status = mcdInitDriver(
            read_mdio,
            write_mdio,
            device->priv.phy.address,
            (const MCD_U8 *)mcdServiceCpuCm3BvFw,
            sizeof(mcdServiceCpuCm3BvFw),
            (const MCD_U16 *)mcd_sbusMaster01x101A_0001Data,
            AVAGO_SBUS_MASTER_FW_IMAGE_SIZE,
            (const MCD_U16 *)mcd_serdes0x2464_0245Swap,
            AVAGO_SERDES_FW_SWAP_IMAGE_SIZE,
            (const MCD_U16 *)mcd_serdes0x2464_0245Data,
            AVAGO_SERDES_FW_IMAGE_SIZE,
            priv,
            &priv->mcddev);
        if (status != MCD_OK)
        {
            bdk_error("%s(%d): mcdInitDriver() failed\n", device->name, phy.s.slice);
            return -1;
        }
        MCD_U16 serdesRevision = 0;
        MCD_U16 sbmRevision = 0;
        status = mcdSerdesGetRevision(&priv->mcddev, &serdesRevision, &sbmRevision);
        if (status != MCD_OK)
        {
            bdk_error("%s(%d): mcdSerdesGetRevision() failed\n", device->name, phy.s.slice);
            return -1;
        }
        printf("%s(%d): SERDES FW revision 0x%x BUS MASTER FW revision 0x%x\n",
            device->name, phy.s.slice, serdesRevision, sbmRevision);

        /* Program lane order */
        MCD_SERDES_TXRX_LANE_REMAP remap[8][2] = {
            /* Line side */
            {{ priv->slice[0].tx_lane_line, priv->slice[0].rx_lane_line }, { priv->slice[4].tx_lane_line, priv->slice[4].rx_lane_line }},
            {{ priv->slice[1].tx_lane_line, priv->slice[1].rx_lane_line }, { priv->slice[5].tx_lane_line, priv->slice[5].rx_lane_line }},
            {{ priv->slice[2].tx_lane_line, priv->slice[2].rx_lane_line }, { priv->slice[6].tx_lane_line, priv->slice[6].rx_lane_line }},
            {{ priv->slice[3].tx_lane_line, priv->slice[3].rx_lane_line }, { priv->slice[7].tx_lane_line, priv->slice[7].rx_lane_line }},
            /* Host side, unused. Swapping done in CGX */
            {{ 0, 0 }, { 0, 0 }},
            {{ 1, 1 }, { 1, 1 }},
            {{ 2, 2 }, { 2, 2 }},
            {{ 3, 3 }, { 3, 3 }}
        };

        status = mcdSetLaneRemapping(&priv->mcddev, MCD_LINE_SIDE, 0, remap);
        if (status != MCD_OK)
        {
            bdk_error("%s(%d): mcdSetLaneRemapping() failed\n", device->name, phy.s.slice);
            return -1;
        }
        status = mcdSetLaneRemapping(&priv->mcddev, MCD_LINE_SIDE, 1, remap);
        if (status != MCD_OK)
        {
            bdk_error("%s(%d): mcdSetLaneRemapping() failed\n", device->name, phy.s.slice);
            return -1;
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

    if (priv->slice[phy.s.slice].use_an)
    {
        if (priv->slice[phy.s.slice].completed_an)
            return result;

        MCD_MODE_CONFIG_PARAM config;
        memset(&config, 0, sizeof(config));
        config.ctleBiasParams.host = MCD_CTLE_BIAS_NORMAL;
        config.noPpmMode = MCD_NO_PPM_RX_SQUELCH_MODE;

        MCD_U16 speed;
        MCD_STATUS status = mcdAutoNegCheckCompleteExt(&priv->mcddev,
            phy.s.slice, MCD_LINE_SIDE, TRUE, &config, &speed);
        if (status != MCD_OK)
        {
            BDK_TRACE(DEVICE, "%s: mcdAutoNegCheckCompleteExt() failed", device->name);
            return result;
        }

        BDK_TRACE(DEVICE, "%s(%d): 88X5123 PHY returned speed 0x%x\n", device->name, phy.s.slice, speed);
        if (speed)
            priv->slice[phy.s.slice].completed_an = true;

        switch (speed)
        {
            case MCD_NEG_1000KX:
                result.s.full_duplex = 1;
                result.s.speed = 1000;
                result.s.up = 1;
                break;
            case MCD_NEG_100CR10:
            case MCD_NEG_100KP4:
            case MCD_NEG_100KR4:
            case MCD_NEG_100CR4:
                result.s.full_duplex = 1;
                result.s.lanes = 4;
                result.s.speed = 100000;
                result.s.up = 1;
                break;
            case MCD_NEG_10KR:
                result.s.full_duplex = 1;
                result.s.speed = 10000;
                result.s.up = 1;
                break;
            case MCD_NEG_40KR4:
            case MCD_NEG_40CR4:
                result.s.full_duplex = 1;
                result.s.lanes = 4;
                result.s.speed = 40000;
                result.s.up = 1;
                break;
            case MCD_NEG_25KR_CONSORTIUM:
            case MCD_NEG_25CR_CONSORTIUM:
            case MCD_NEG_25KRCS:
            case MCD_NEG_25KCR:
                result.s.full_duplex = 1;
                result.s.speed = 25000;
                result.s.up = 1;
                break;
            case MCD_NEG_50KR_CONSORTIUM:
            case MCD_NEG_50CR_CONSORTIUM:
                result.s.full_duplex = 1;
                result.s.lanes = 2;
                result.s.speed = 50000;
                result.s.up = 1;
                break;
            case MCD_NEG_NONE:
            default:
                result.u64 = 0;
                break;
        }
    }
    else
    {
        MCD_U16 currentStatus = 0;
        MCD_U16 latchedStatus = 0;
        MCD_STATUS status =  mcdCheckLinkStatus(&priv->mcddev,
            phy.s.slice, &currentStatus, &latchedStatus, NULL);
        if (status != MCD_OK)
            bdk_error("%s: mcdCheckLinkStatus() failed", device->name);
        MCD_MODE_SPEED speed = 0;
        MCD_MODE mode = 0;
        status = mcdGetModeSpeed(&priv->mcddev, phy.s.slice, MCD_HOST_SIDE,
            &speed, &mode);
        if (status != MCD_OK)
            bdk_error("%s: mcdGetModeSpeed() failed", device->name);

        BDK_TRACE(DEVICE, "%s(%d): 88X5123 PHY link is %d, speed 0x%x\n", device->name, phy.s.slice, currentStatus, speed);

        result.s.up = (currentStatus == MCD_LINK_UP);
        result.s.full_duplex = result.s.up;
        switch (speed)
        {
            case MCD_10GB:
                result.s.speed = 10000;
                break;
            case MCD_20GB:
                result.s.speed = 20000;
                break;
            case MCD_25GB:
                result.s.speed = 25000;
                break;
            case MCD_40GB:
                result.s.speed = 40000;
                result.s.lanes = 4;
                break;
            case MCD_100GB:
                result.s.speed = 100000;
                result.s.lanes = 4;
                break;
            case MCD_2_5GB:
                result.s.speed = 2500;
                break;
            case MCD_1GB:
                result.s.speed = 1000;
                break;
            case MCD_50GB:
                result.s.speed = 50000;
                result.s.lanes = 2;
                break;
            default:
                result.s.speed = speed;
        }
    }

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
    MCD_STATUS status = mcdSetHostLoopback(&priv->mcddev, phy.s.slice,
        MCD_DEEP_PCS_LB, host_side ? MCD_ENABLE : MCD_DISABLE);
    if (status != MCD_OK)
    {
        bdk_error("%s: mcdSetHostLoopback() failed", device->name);
        return -1;
    }

    status = mcdSetLineLoopback(&priv->mcddev, phy.s.slice,
        MCD_DEEP_PCS_LB, line_side ? MCD_ENABLE : MCD_DISABLE);
    if (status != MCD_OK)
    {
        bdk_error("%s: mcdSetLineLoopback() failed", device->name);
        return -1;
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
    phy_priv_t *priv = device->priv.phy.priv;
    if (num_modes != 1)
    {
        bdk_error("%s: 88x5123 PHy driver doesn't support AN yet\n", device->name);
        return -1;
    }

    MCD_U32 modesVector = MCD_AN_10GBase_KR;
    MCD_OP_MODE op_mode = MCD_MODE_P10L;
    MCD_FEC_TYPE fec_type = MCD_NO_FEC;
    const char *mode_str = "10GBASE-KR";
    priv->slice[phy.s.slice].use_an = true;

    if (flags & BDK_NETPHY_FLAG_RS_FEC)
        fec_type = MCD_RS_FEC_HOST; /* Only host side */
    else if (flags & BDK_NETPHY_FLAG_FEC)
        fec_type = MCD_FC_FEC_HOST; /* Only host side */

    switch (qlm_speeds[0])
    {
        case 1250:
            if (qlm_modes[0] == BDK_QLM_MODE_SGMII)
            {
                priv->slice[phy.s.slice].use_an = true;
                op_mode = MCD_MODE_P1_BaseX_SGMII;
                modesVector = MCD_AN_1000BASE_KX;
                mode_str = "SGMII/1GBASE-X";
            }
            else
            {
                priv->slice[phy.s.slice].use_an = false;
                op_mode = MCD_MODE_P1;
                mode_str = "1GBASE-X";
            }
            break;
        case 10312:
            if ((qlm_modes[0] == BDK_QLM_MODE_XLAUI) ||
                (qlm_modes[0] == BDK_QLM_MODE_XLAUI_C2M) ||
                (qlm_modes[0] == BDK_QLM_MODE_40G_CR4) ||
                (qlm_modes[0] == BDK_QLM_MODE_40G_KR4)) /* Not supported by PHY */
            {
                priv->slice[phy.s.slice].use_an = (qlm_modes[0] == BDK_QLM_MODE_40G_KR4);
                op_mode = MCD_MODE_P40L;
                modesVector = MCD_AN_40GBASE_KR4;
                mode_str = (priv->slice[phy.s.slice].use_an) ? "40GBASE-KR4" : "40GBASE-R4";
            }
            else
            {
                priv->slice[phy.s.slice].use_an = (qlm_modes[0] == BDK_QLM_MODE_10G_KR);
                op_mode = MCD_MODE_P10S;
                modesVector = MCD_AN_10GBase_KR;
                mode_str = (priv->slice[phy.s.slice].use_an) ? "10GBASE-KR" : "10GBASE-R";
            }
            break;
        case 20625:
            /* AN not supported */
            priv->slice[phy.s.slice].use_an = false;
            if (qlm_modes[0] == BDK_QLM_MODE_80GAUI_4_C2C)
            {
                op_mode = MCD_MODE_P40R2S; /* FIXME: PHY doesn't support 80G */
                mode_str = "80GBASE-R4, Not supported by PHY";
            }
            else if (qlm_modes[0] == BDK_QLM_MODE_40GAUI_2_C2C)
            {
                op_mode = MCD_MODE_P40R2S;
                mode_str = "40GBASE-R2";
            }
            else
            {
                op_mode = MCD_MODE_P20S;
                //modesVector = MCD_AN_20GBase_KR1S;
                mode_str = (priv->slice[phy.s.slice].use_an) ? "20GBASE-KR" : "20GBASE-R";
            }
            break;
        case 25781:
            if ((qlm_modes[0] == BDK_QLM_MODE_CAUI_4_C2C) ||
                (qlm_modes[0] == BDK_QLM_MODE_CAUI_4_C2M) ||
                (qlm_modes[0] == BDK_QLM_MODE_100G_CR4) ||
                (qlm_modes[0] == BDK_QLM_MODE_100G_KR4)) /* Not supported by PHY */
            {
                priv->slice[phy.s.slice].use_an = (qlm_modes[0] == BDK_QLM_MODE_100G_KR4);
                op_mode = MCD_MODE_P100S;
                modesVector = MCD_AN_100GBASE_KR4;
                mode_str = (priv->slice[phy.s.slice].use_an) ? "100GBASE-KR4" : "100GBASE-R4";
            }
            else if ((qlm_modes[0] == BDK_QLM_MODE_50GAUI_2_C2C) ||
                (qlm_modes[0] == BDK_QLM_MODE_50GAUI_2_C2M) ||
                (qlm_modes[0] == BDK_QLM_MODE_50G_CR2) ||
                (qlm_modes[0] == BDK_QLM_MODE_50G_KR2)) /* Not supported by PHY */
            {
                priv->slice[phy.s.slice].use_an = (qlm_modes[0] == BDK_QLM_MODE_50G_KR2);
                op_mode = MCD_MODE_P50R2S;
                modesVector = MCD_AN_50GBase_KR2_CONSORTIUM;
                mode_str = (priv->slice[phy.s.slice].use_an) ? "50GBASE-KR2" : "50GBASE-R2";
            }
            else
            {
                priv->slice[phy.s.slice].use_an = (qlm_modes[0] == BDK_QLM_MODE_25G_KR);
                op_mode = MCD_MODE_P25S;
                modesVector = MCD_AN_25GBase_KR1S;
                mode_str = (priv->slice[phy.s.slice].use_an) ? "25GBASE-KR" : "25GBASE-R";
            }
            break;
    }

    int port = phy.s.slice;
    printf("%s(%d): Setting %s\n", device->name, port, mode_str);
    MCD_PORT_PER_SERDES_CONFIG_DATA paramsPtr;
    for (int i = 0; i < 8; i++)
    {
        paramsPtr.params[i].bitMapEnable =
            (1 << MCD_ELEC_PARAM_PRECUSOR_OFFSET) |
            (1 << MCD_ELEC_PARAM_ATTENU_OFFSET) |
            (1 << MCD_ELEC_PARAM_POSTCURSOR_OFFSET);
        paramsPtr.params[i].rxPolarity = 0;
        paramsPtr.params[i].txPolarity = 0;
        paramsPtr.params[i].preCursor = priv->slice[i].cpre_line;
        paramsPtr.params[i].attenuation = priv->slice[i].cmain_line;
        paramsPtr.params[i].postCursor = priv->slice[i].cpost_line;
        paramsPtr.params[8 + i].bitMapEnable =
            (1 << MCD_ELEC_PARAM_PRECUSOR_OFFSET) |
            (1 << MCD_ELEC_PARAM_ATTENU_OFFSET) |
            (1 << MCD_ELEC_PARAM_POSTCURSOR_OFFSET);
        paramsPtr.params[8 + i].rxPolarity = 0;
        paramsPtr.params[8 + i].txPolarity = 0;
        paramsPtr.params[8 + i].preCursor = priv->slice[i].cpre_host;
        paramsPtr.params[8 + i].attenuation = priv->slice[i].cmain_host;
        paramsPtr.params[8 + i].postCursor = priv->slice[i].cpost_host;
    }

    MCD_STATUS status = mcdPortReset(&priv->mcddev, port, MCD_BOTH_SIDE,
        MCD_SOFT_RESET, 1000);
    if (status != MCD_OK)
    {
        bdk_error("%s(%d): mcdPortReset() failed\n", device->name, phy.s.slice);
        return -1;
    }

    MCD_STATUS mcdSetSetSerdesElectricalParametersDB(unsigned int portNum,
        MCD_OP_MODE portMode, MCD_PORT_PER_SERDES_CONFIG_DATA *paramsPtr);
    status = mcdSetSetSerdesElectricalParametersDB(port, MCD_MODE_P10L, &paramsPtr);
    if (status != MCD_OK)
    {
        bdk_error("%s(%d): mcdSetSetSerdesElectricalParametersDB() failed\n", device->name, phy.s.slice);
        return -1;
    }
    status = mcdSetSetSerdesElectricalParametersDB(port, MCD_MODE_P20L, &paramsPtr);
    if (status != MCD_OK)
    {
        bdk_error("%s(%d): mcdSetSetSerdesElectricalParametersDB() failed\n", device->name, phy.s.slice);
        return -1;
    }
    status = mcdSetSetSerdesElectricalParametersDB(port, MCD_MODE_P25L, &paramsPtr);
    if (status != MCD_OK)
    {
        bdk_error("%s(%d): mcdSetSetSerdesElectricalParametersDB() failed\n", device->name, phy.s.slice);
        return -1;
    }
    if (priv->slice[phy.s.slice].use_an)
    {
        status = mcdSetAPModeSelection(&priv->mcddev,
            port, /* Internal PHY port 0-7, step larger for multi-lane */
            port, /* Which lane used for AN */
            modesVector, /* What modes AN allows */
            MCD_TRUE, /* Allow fcPause */
            MCD_TRUE, /* Allow fcAsmDir */
            fec_type, /* Support FEC on host and line side */
            fec_type, /* Request FEC */
            MCD_TRUE, /* Disable AN nonce checking */
            NULL, /* configPtr */
            MCD_TRUE); /* Enable AN */
        if (status != MCD_OK)
        {
            bdk_error("%s(%d): mcdSetModeSelection() failed\n", device->name, phy.s.slice);
            return -1;
        }
    }
    else
    {
        MCD_MODE_CONFIG_PARAM config;
        memset(&config, 0, sizeof(config));
        status = mcdSetDefaultInitDB(&priv->mcddev,
            port, /* Internal PHY port 0-7, step larger for multi-lane */
            &config);
        if (status != MCD_OK)
        {
            bdk_error("%s(%d): mcdSetDefaultInitDB() failed\n", device->name, phy.s.slice);
            return -1;
        }
        status = mcdSetModeSelectionExt(&priv->mcddev,
            port, /* Internal PHY port 0-7, step larger for multi-lane */
            op_mode,
            MCD_FALSE, /* autoNegAdvEnable */
            fec_type, /* Request FEC */
            &config);
        if (status != MCD_OK)
        {
            bdk_error("%s(%d): mcdSetModeSelectionExt() failed\n", device->name, phy.s.slice);
            return -1;
        }
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
    if (!host_side)
        return -1;

    bool enable_tx = ((dir & BDK_QLM_DIRECTION_TX) != 0);
    bool enable_rx = ((dir & BDK_QLM_DIRECTION_RX) != 0);
    MCD_PRBS_LINE_SELECTOR_TYPE linepat;
    MCD_PRBS_HOST_SELECTOR_TYPE hostpat;
    switch (prbs)
    {
        case 7:
            linepat = MCD_LINE_PRBS7;
            hostpat = MCD_HOST_PRBS7;
            break;
        case 9:
            linepat = MCD_LINE_PRBS9;
            hostpat = MCD_HOST_PRBS9;
            break;
        case 11:
            linepat = MCD_LINE_PRBS11;
            hostpat = MCD_HOST_PRBS11;
            break;
        case 15:
            linepat = MCD_LINE_PRBS15;
            hostpat = MCD_HOST_PRBS15;
            break;
        case 23:
            linepat = MCD_LINE_PRBS23;
            hostpat = MCD_HOST_PRBS23;
            break;
        case 31:
            linepat = MCD_LINE_PRBS31;
            hostpat = MCD_HOST_PRBS31;
            break;
        default:
            bdk_error("%s(%d): Unsupported PRBS mode %d, using 7\n", device->name, phy.s.slice, prbs);
            linepat = MCD_LINE_PRBS7;
            hostpat = MCD_HOST_PRBS7;
            break;
    }
    MCD_STATUS status = mcdSetLineSidePRBSPattern(
        &priv->mcddev,
        phy.s.slice,
        0, /* lane */
        linepat,
        MCD_LINE_PRBS_NONE);
    if (status != MCD_OK)
    {
        bdk_error("%s(%d): mcdSetLineSidePRBSPattern() failed\n", device->name, phy.s.slice);
        return -1;
    }
    status = mcdSetHostSidePRBSPattern(
        &priv->mcddev,
        phy.s.slice,
        0, /* lane */
        hostpat);
    if (status != MCD_OK)
    {
        bdk_error("%s(%d): mcdSetHostSidePRBSPattern() failed\n", device->name, phy.s.slice);
        return -1;
    }
    status = mcdSetPRBSEnableTxRx(
        &priv->mcddev,
        phy.s.slice,
        (host_side) ? MCD_HOST_SIDE : MCD_LINE_SIDE,
        0, /* lane */
        (enable_tx | enable_rx) ? MCD_ENABLE : MCD_DISABLE, /* TX */
        (enable_rx) ? MCD_ENABLE : MCD_DISABLE); /* RX */
    if (status != MCD_OK)
    {
        bdk_error("%s(%d): mcdSetPRBSEnableTxRx() failed\n", device->name, phy.s.slice);
        return -1;
    }
    return 0;
}

static int phy_disable_prbs(bdk_device_t *device, bdk_netphy_t phy, bool host_side)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (priv == NULL)
        return -1;
    if (!host_side)
        return -1;

    MCD_STATUS status = mcdSetPRBSEnableTxRx(
        &priv->mcddev,
        phy.s.slice,
        (host_side) ? MCD_HOST_SIDE : MCD_LINE_SIDE,
        0, /* lane */
        MCD_DISABLE, /* TX */
        MCD_DISABLE); /* RX */
    if (status != MCD_OK)
    {
        bdk_error("%s(%d): mcdSetPRBSEnableTxRx() failed\n", device->name, phy.s.slice);
        return -1;
    }
    return 0;
}

static uint64_t phy_get_prbs_errors(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int lane, int clear)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (priv == NULL)
        return -1;
    if (!host_side)
        return -1;

    MCD_U64 txBitCount;
    MCD_U64 rxBitCount;
    MCD_U64 rxBitErrorCount;
    MCD_STATUS status = mcdGetPRBSCounts(
        &priv->mcddev,
        phy.s.slice,
        (host_side) ? MCD_HOST_SIDE : MCD_LINE_SIDE,
        0, /* lane */
        &txBitCount,
        &rxBitCount,
        &rxBitErrorCount);
    if (status != MCD_OK)
    {
        bdk_error("%s(%d): mcdGetPRBSCounts() failed\n", device->name, phy.s.slice);
        return -1;
    }
    if (host_side)
    {
        /* 5123 API seems to return 0xffff when there isn't a lock. Documentation is useless */
        if (rxBitErrorCount == 0xffff)
        {
            priv->slice[phy.s.slice].prbs_errors_host = 0;
            return -1;
        }
        else
        {
            uint64_t errors = priv->slice[phy.s.slice].prbs_errors_host + rxBitErrorCount;
            priv->slice[phy.s.slice].prbs_errors_host = (clear) ? 0 : errors;
            return errors;
        }
    }
    else
    {
        /* 5123 API seems to return 0xffff when there isn't a lock. Documentation is useless */
        if (rxBitErrorCount == 0xffff)
        {
            priv->slice[phy.s.slice].prbs_errors_line = 0;
            return -1;
        }
        else
        {
            uint64_t errors = priv->slice[phy.s.slice].prbs_errors_line + rxBitErrorCount;
            priv->slice[phy.s.slice].prbs_errors_line = (clear) ? 0 : errors;
            return errors;
        }
    }
}

static void phy_inject_prbs_error(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int lane)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (priv == NULL)
        return;
    if (!host_side)
        return;
    MCD_STATUS status = mcdSerdesTxInjectError(&priv->mcddev,
        ((host_side) ? 9 : 1) + phy.s.slice, 1);
    if (status != MCD_OK)
        bdk_error("%s(%d): mcdSerdesTxInjectError() failed\n", device->name, phy.s.slice);
}

static int phy_tune_tx(bdk_device_t *device, bdk_netphy_t phy, bool host_side, int cmain, int cpre, int cpost)
{
    phy_priv_t *priv = device->priv.phy.priv;
    if (host_side)
    {
        priv->slice[phy.s.slice].cmain_host = cmain;
        priv->slice[phy.s.slice].cpre_host = cpre;
        priv->slice[phy.s.slice].cpost_host = cpost;
    }
    else
    {
        priv->slice[phy.s.slice].cmain_line = cmain;
        priv->slice[phy.s.slice].cpre_line = cpre;
        priv->slice[phy.s.slice].cpost_line = cpost;
    }
    /* Redo AN, which load the new settings */
    priv->slice[phy.s.slice].completed_an = false;
    return 0;
}

/**
 * Needed by 5123 driver
 *
 * @param usec
 */
int usleep(useconds_t usec)
{
    bdk_wait_usec(usec);
    return 0;
}

bdk_driver_t __bdk_driver_netphy_88x5123 = {
    .name = "PHY-88X5123",
    .add = add,
    .api = BDK_DEVICE_API_NETPHY,
    .funcs.netphy.init = phy_init,
    .funcs.netphy.get_speed = phy_get_speed,
    .funcs.netphy.loopback = phy_loopback,
    .funcs.netphy.setup_an = phy_setup_an,
    .funcs.netphy.enable_prbs = phy_enable_prbs,
    .funcs.netphy.disable_prbs = phy_disable_prbs,
    .funcs.netphy.get_prbs_errors = phy_get_prbs_errors,
    .funcs.netphy.inject_prbs_error = phy_inject_prbs_error,
    .funcs.netphy.tune_tx = phy_tune_tx,
};
