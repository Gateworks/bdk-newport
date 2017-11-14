/***********************license start***********************************
* Copyright (c) 2003-2016  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include <malloc.h>
#include "libbdk-arch/bdk-csrs-cgx.h"

/* This file implements interfaces connected to the CGX block introduced
    for CN93XX. This block combines SGMII, QSGMII, XAUI, DXAUI, RXAUI,
    XFI, XLAUI, 10GBASE-KR, 40GBASE-KR, 25G, 50G, 100G, and USXGMII all
    into one interface */

#define MAX_MTU 9212

typedef enum
{
    CGX_MODE_SGMII, /* 1 lane, 1.250 Gbaud */
    CGX_MODE_QSGMII, /* 4 ports on 1 lane, 5.0 Gbaud */
    CGX_MODE_XAUI,  /* 4 lanes, 3.125 Gbaud */
    CGX_MODE_DXAUI, /* 4 lanes, 6.250 Gbaud */
    CGX_MODE_RXAUI, /* 2 lanes, 6.250 Gbaud */
    CGX_MODE_XFI,   /* 1 lane, 10.3125 Gbaud */
    CGX_MODE_XLAUI, /* 4 lanes, 10.3125 Gbaud */
    CGX_MODE_10G_KR,/* 1 lane, 10.3125 Gbaud */
    CGX_MODE_40G_KR,/* 4 lanes, 10.3125 Gbaud */
    CGX_MODE_25G,   /* 1 lane, 25G Gbaud */
    CGX_MODE_50G,   /* 2 lanes, 25G Gbaud */
    CGX_MODE_100G,  /* 4 lanes, 25 Gbaud */
    CGX_MODE_25G_KR,  /* 1 lane, 25G Gbaud */
    CGX_MODE_50G_KR,  /* 2 lanes, 25G Gbaud */
    CGX_MODE_100G_KR4,/* 4 lanes, 25 Gbaud */
    CGX_MODE_USXGMII, /* 1 lane, autoneg? */
} cgx_mode_t;

typedef struct
{
    /* CGX related config */
    cgx_mode_t  mode;           /* CGX mode */
    int         port;           /* Which physical port this handle connects to */
    int         num_port;       /* Number of physical ports on this interface */
    int         use_training;   /* True if this port is in 10G or 40G and uses training */
    uint64_t    restart_auto_neg; /* Time we last restarted auto-neg. Ued to make sure we give auto-neg enough time */
    int64_t     phy_address;    /* PHY address from bdk-config */
} cgx_priv_t;

/**
 * Create the private structure needed by CGX
 *
 * @param node      Node this CGX is on
 * @param interface Which CGX
 * @param index     Which channel on the CGX. This is an encoding of port and channel.
 *
 * @return The private structure
 */
static void create_priv(bdk_node_t node, int interface, int index, cgx_priv_t *priv)
{
    memset(priv, 0, sizeof(*priv));
    int qlm = bdk_qlm_get(node, BDK_IF_CGX, interface, index);
    bdk_qlm_modes_t qlm_mode = (qlm == -1) ? BDK_QLM_MODE_DISABLED : bdk_qlm_get_mode(node, qlm);
    int gbaud_mhz = (qlm == -1) ? 0 : bdk_qlm_get_gbaud_mhz(node, qlm);

    int lmac_type = -1;
    switch (qlm_mode)
    {
        case BDK_QLM_MODE_SGMII_4X1:
        case BDK_QLM_MODE_SGMII_2X1:
        case BDK_QLM_MODE_SGMII_1X1:
            lmac_type = BDK_CGX_LMAC_TYPES_E_SGMII;
            priv->num_port = (qlm_mode == BDK_QLM_MODE_SGMII_4X1) ? 4 :
                             (qlm_mode == BDK_QLM_MODE_SGMII_2X1) ? 2 :
                             1;
            priv->mode = CGX_MODE_SGMII;
            break;
        case BDK_QLM_MODE_QSGMII_4X1:
            lmac_type = BDK_CGX_LMAC_TYPES_E_QSGMII;
            priv->num_port = 4;
            priv->mode = CGX_MODE_QSGMII;
            /* Disparity check enable. When LMAC_TYPE=QSGMII the running
               disparity check should be disabled to prevent propagation
               across ports. */
            BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MISCX_CTL(interface, index),
                c.s.disp_en = 0);
            break;
        case BDK_QLM_MODE_XAUI_1X4:
            lmac_type = BDK_CGX_LMAC_TYPES_E_XAUI;
            priv->num_port = 1;
            priv->mode = CGX_MODE_XAUI;
            if (gbaud_mhz == 3125)
                priv->mode = CGX_MODE_XAUI;
            else
                priv->mode = CGX_MODE_DXAUI;
            break;
        case BDK_QLM_MODE_RXAUI_2X2:
        case BDK_QLM_MODE_RXAUI_1X2:
            lmac_type = BDK_CGX_LMAC_TYPES_E_RXAUI;
            priv->num_port = (qlm_mode == BDK_QLM_MODE_RXAUI_1X2) ? 1 : 2;
            priv->mode = CGX_MODE_RXAUI;
            break;
        case BDK_QLM_MODE_XFI_4X1:
        case BDK_QLM_MODE_XFI_2X1:
        case BDK_QLM_MODE_XFI_1X1:
            lmac_type = BDK_CGX_LMAC_TYPES_E_TENG_R;
            priv->num_port = (qlm_mode == BDK_QLM_MODE_XFI_4X1) ? 4 :
                             (qlm_mode == BDK_QLM_MODE_XFI_2X1) ? 2 :
                             1;
            priv->mode = CGX_MODE_XFI;
            /* XFI doesn't support tx training */
            break;
        case BDK_QLM_MODE_XLAUI_1X4:
            lmac_type = BDK_CGX_LMAC_TYPES_E_FORTYG_R;
            priv->num_port = 1;
            priv->mode = CGX_MODE_XLAUI;
            /* XLAUI doesn't support tx training */
            break;
        case BDK_QLM_MODE_10G_KR_4X1:
        case BDK_QLM_MODE_10G_KR_2X1:
        case BDK_QLM_MODE_10G_KR_1X1:
            lmac_type = BDK_CGX_LMAC_TYPES_E_TENG_R;
            priv->num_port = (qlm_mode == BDK_QLM_MODE_10G_KR_4X1) ? 4 :
                             (qlm_mode == BDK_QLM_MODE_10G_KR_2X1) ? 2 :
                             1;
            priv->mode = CGX_MODE_10G_KR;
            priv->use_training = 1; /* 10GBASE-KR supports tx training */
            break;
        case BDK_QLM_MODE_40G_KR4_1X4:
            lmac_type = BDK_CGX_LMAC_TYPES_E_FORTYG_R;
            priv->num_port = 1;
            priv->mode = CGX_MODE_40G_KR;
            priv->use_training = 1; /* 40GBASE-KR4 supports tx training */
            break;
        default:
            priv->num_port = 0;
            break;
    }

    /* Handle where CGX spans two DLMs. This happens on CN93XX CGX1,
       DLM4-5 */
    if ((qlm != -1) && (CAVIUM_IS_MODEL(CAVIUM_CN93XX) && (interface == 1)))
    {
        int num_ports = 0;
        int base_qlm = 4;
        for (int dlm = base_qlm; dlm <= base_qlm + 1; dlm++)
        {
            switch (bdk_qlm_get_mode(node, dlm))
            {
                case BDK_QLM_MODE_SGMII_2X1:
                case BDK_QLM_MODE_XFI_2X1:
                case BDK_QLM_MODE_10G_KR_2X1:
                    /* 2 ports on DLM */
                    num_ports += 2;
                    break;
                case BDK_QLM_MODE_SGMII_1X1:
                case BDK_QLM_MODE_XFI_1X1:
                case BDK_QLM_MODE_10G_KR_1X1:
                case BDK_QLM_MODE_RXAUI_1X2:
                    /* 1 port on DLM */
                    num_ports += 1;
                    break;
                case BDK_QLM_MODE_XAUI_1X4:
                case BDK_QLM_MODE_XLAUI_1X4:
                case BDK_QLM_MODE_40G_KR4_1X4:
                    /* 1 port on across DLMs */
                    num_ports += 1;
                    dlm++; /* No need to check next DLM */
                    break;
                case BDK_QLM_MODE_QSGMII_4X1:
                    /* 4 ports on DLM */
                    num_ports += 4;
                    dlm++; /* No need to check next DLM */
                    break;
                default:
                    /* Invalid mode, no ports */
                    break;
            }
        }
        /* It is possible for the above code to count more than 4 ports when QSGMII
           is used. Since the hardware can only support 4 ports, we limit ourselves
           to 4. The higher ports are unavailable */
        if (num_ports > 4)
            num_ports = 4;
        priv->num_port = num_ports;
    }

    /* Make sure the CGX LMAC type is programmed correctly. The QLM code doesn't
       program all of them */
    if (lmac_type != -1)
    {
        BDK_CSR_INIT(cmrx_config, node, BDK_CGXX_CMRX_CONFIG(interface, index));
        if ((cmrx_config.s.lmac_type != 0x5) &&
            (cmrx_config.s.lmac_type != lmac_type))
        {
            BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(interface, index),
                c.s.lmac_type = lmac_type);
        }
    }

    priv->port = index;
    priv->phy_address = bdk_config_get_int(BDK_CONFIG_PHY_ADDRESS, node, interface, index);
}

static int if_num_interfaces(bdk_node_t node)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN93XX))
        return 3;
    else
        return 0;
}

static int if_num_ports(bdk_node_t node, int interface)
{
    cgx_priv_t priv;
    create_priv(node, interface, 0, &priv);
    return priv.num_port;
}

/**
 * Perform initialization of the CGX required before use. This should only be
 * called once for each CGX. Before this is called, the mode of
 * the SERDES must be set by bdk_qlm_set_mode().
 *
 * @param interface Which CGX to setup. This will have index=0
 *
 * @return Zero on success, negative on failure
 */
static int cgx_setup_one_time(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;

    /* Strip FCS */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMR_GLOBAL_CONFIG(handle->interface),
        c.s.fcs_strip = 1);

    /* First warn if BIST failed */
    //uint64_t bist = BDK_CSR_READ(handle->node, BDK_CGXX_CMR_BIST_STATUS(handle->interface));
    //if (bist)
    //    bdk_warn("CGX%d failed BIST\n", handle->interface);

    int qlm = bdk_qlm_get(handle->node, BDK_IF_CGX, handle->interface, handle->index);

    /* Based on the mode of this port, figure out which lanes it maps too */
    int lane_to_sds;
    switch (priv->mode)
    {
        case CGX_MODE_SGMII:
        case CGX_MODE_QSGMII:
        case CGX_MODE_XFI:
        case CGX_MODE_10G_KR:
            /* This normally uses 1 lane for each port, mapping directly
               to CGX index */
            lane_to_sds = handle->index;
            /* CN93XX: DLM5 index to lane mapping change based on what
               DLM4 has on it, which shares the same CGX1 */
            if (CAVIUM_IS_MODEL(CAVIUM_CN93XX) && (qlm == 5))
            {
                switch (bdk_qlm_get_mode(handle->node, qlm - 1))
                {
                    case BDK_QLM_MODE_SGMII_2X1:
                    case BDK_QLM_MODE_XFI_2X1:
                    case BDK_QLM_MODE_10G_KR_2X1:
                        /* Index 2+ maps to lanes 2+ */
                        lane_to_sds = handle->index;
                        break;
                    case BDK_QLM_MODE_SGMII_1X1:
                    case BDK_QLM_MODE_XFI_1X1:
                    case BDK_QLM_MODE_10G_KR_1X1:
                    case BDK_QLM_MODE_RXAUI_1X2:
                        /* Index 1+ maps to lanes 2+ */
                        lane_to_sds = handle->index + 1;
                        break;
                    default:
                        /* Index 0+ maps to lanes 2+ */
                        lane_to_sds = handle->index + 2;
                        break;
                }
            }
            break;
        case CGX_MODE_XAUI:
        case CGX_MODE_DXAUI:
        case CGX_MODE_XLAUI:
        case CGX_MODE_40G_KR:
            /* These always use all four lanes */
            lane_to_sds = 0xe4;
            break;
        case CGX_MODE_RXAUI:
            /* RGMII is normally using index 0 and 1 for two ports. If RGMII is
               in use, then the index is 1 and 2 */
            lane_to_sds = (handle->index) ? 0xe : 0x4;
            /* DLM5 on CN93XX always maps to lanes 2-3. The above check
               would be wrong if DLM4 was disabled, causing DLM5 to be
               first */
            if (CAVIUM_IS_MODEL(CAVIUM_CN93XX) && (qlm == 5))
                lane_to_sds = 0xe;
            break;
        default:
            return -1;
    }
    /* Set mode and lanes */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_CONFIG(handle->interface, handle->index),
        c.s.lane_to_sds = lane_to_sds);
    /* Set the PKND */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_RX_ID_MAP(handle->interface, handle->index),
        c.s.pknd = handle->pknd);

    /* Determine the CGX FIFO size */
    BDK_CSR_INIT(cgxx_const, handle->node, BDK_CGXX_CONST(handle->interface));
    int fifo_size = cgxx_const.s.tx_fifosz;
    if (priv->num_port == 2)
        fifo_size /= 2;
    else if (priv->num_port >= 3)
        fifo_size /= 4;

    /* Program the transmit threshold to use the whole FIFO. Leave 256 bytes
       free so there is room for another packet to begin. Note that the
       threshholds are limited to 10 bits */
    int cnt = fifo_size / 16 - 16;
    if (cnt > 0x3ff)
        cnt = 0x3ff;
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_GMI_TXX_THRESH(handle->interface, handle->index),
        c.s.cnt = cnt);
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SMUX_TX_THRESH(handle->interface, handle->index),
        c.s.cnt = cnt);

    /* When using PKI with CGX divided into 4 ports, the default backpresure
       assert level is too high. More packets arrive before a MTU packet is
       removed, causing truncation */
    if ((priv->num_port >= 3) && (handle->pki_channel != -1))
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_RX_BP_ON(handle->interface, handle->index),
            c.s.mark = 128);

    /* Set the number of LMACs we will use */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMR_TX_LMACS(handle->interface),
        c.s.lmacs = priv->num_port);
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMR_RX_LMACS(handle->interface),
        c.s.lmacs = priv->num_port);

    /* Set the backpressure AND mask. Each interface gets 16 channels in this
       mask. When there is only 1 port, all 64 channels are available but
       the upper channels are used for anything. That's why this code only uses
       16 channels per interface */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMR_CHAN_MSK_AND(handle->interface),
        c.s.msk_and |= ((1ull <<1/*num_channels*/) - 1ull) << (handle->index * 16));

    /* Disable all MAC filtering */
    for (int i = 0; i < 32; i++)
    {
        BDK_CSR_WRITE(handle->node, BDK_CGXX_CMR_RX_DMACX_CAM0(handle->interface, i), 0);
        BDK_CSR_WRITE(handle->node, BDK_CGXX_CMR_RX_DMACX_CAM1(handle->interface, i), 0);
    }
    /* Disable MAC steering */
    for (int i = 0; i < 8; i++)
    {
        BDK_CSR_WRITE(handle->node, BDK_CGXX_CMR_RX_STEERING0X(handle->interface, i), 0);
        BDK_CSR_WRITE(handle->node, BDK_CGXX_CMR_RX_STEERING1X(handle->interface, i), 0);
    }

    /* Calculate the number of s-clk cycles per usec. */
    uint64_t usec_cycles = bdk_clock_get_rate(handle->node, BDK_CLOCK_SCLK) / 1000000;
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPU_DBG_CONTROL(handle->interface),
        c.s.us_clk_period = usec_cycles-1);

    /* Set the default pause interval as the hardware default is too short */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SMUX_TX_PAUSE_PKT_TIME(handle->interface, handle->index),
            c.s.p_time = 0x100);

    /* For RXAUI, We're using a Marvel PHY on the plugin modules. The code
       below programs all CGXs to use "Interleaved running disparity", which
       is required for these PHYs. This will need to be changed if PHYs are
       used that expect "Common running disparity". */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_MISC_CONTROL(handle->interface, handle->index),
        c.s.intlv_rdisp = 1);
    return 0;
}

static int if_probe(bdk_if_handle_t handle)
{
    /* Don't show ports that have zero in CGXX_CMRX_RX_DMAC_CTL. These are
       not on the board and hidden by the bootstub */
    if (BDK_CSR_READ(handle->node, BDK_CGXX_CMRX_RX_DMAC_CTL0(handle->interface, handle->index)) == 0)
    {
        BDK_TRACE(BGX, "%s: Disabled by bootstub\n", handle->name);
        return -1;
    }

    cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    create_priv(handle->node, handle->interface, handle->index, priv);
    bool is_basex = ((priv->phy_address & BDK_IF_PHY_TYPE_MASK)== BDK_IF_PHY_TWSI);

    /* Change name to be something that might be meaningful to the user */
    const char *name_format = "UNKNOWN";
    switch (priv->mode)
    {
        case CGX_MODE_SGMII:
            if (is_basex)
            {
                if (bdk_numa_is_only_one())
                    name_format = "1GX%d.%d";
                else
                    name_format = "N%d.1GX%d.%d";
            }
            else
            {
                if (bdk_numa_is_only_one())
                    name_format = "SGMII%d.%d";
                else
                    name_format = "N%d.SGMII%d.%d";
            }
            break;
        case CGX_MODE_QSGMII:
            if (bdk_numa_is_only_one())
                name_format = "QSGMII%d.%d";
            else
                name_format = "N%d.QSGMII%d.%d";
            break;
        case CGX_MODE_XAUI:
            if (bdk_numa_is_only_one())
                name_format = "XAUI%d";
            else
                name_format = "N%d.XAUI%d";
            break;
        case CGX_MODE_DXAUI:
            if (bdk_numa_is_only_one())
                name_format = "DXAUI%d";
            else
                name_format = "N%d.DXAUI%d";
            break;
        case CGX_MODE_RXAUI:
            if (bdk_numa_is_only_one())
                name_format = "RXAUI%d.%d";
            else
                name_format = "N%d.RXAUI%d.%d";
            break;
        case CGX_MODE_XFI:
            if (bdk_numa_is_only_one())
                name_format = "XFI%d.%d";
            else
                name_format = "N%d.XFI%d.%d";
            break;
        case CGX_MODE_XLAUI:
            if (bdk_numa_is_only_one())
                name_format = "XLAUI%d";
            else
                name_format = "N%d.XLAUI%d";
            break;
        case CGX_MODE_10G_KR:
            if (bdk_numa_is_only_one())
                name_format = "10GKR%d.%d";
            else
                name_format = "N%d.10GKR%d.%d";
            break;
        case CGX_MODE_40G_KR:
            if (bdk_numa_is_only_one())
                name_format = "40GKR%d";
            else
                name_format = "N%d.40GKR%d";
            break;
        case CGX_MODE_25G:
            if (bdk_numa_is_only_one())
                name_format = "25G%d";
            else
                name_format = "N%d.25G%d";
            break;
        case CGX_MODE_50G:
            if (bdk_numa_is_only_one())
                name_format = "50G%d";
            else
                name_format = "N%d.50G%d";
            break;
        case CGX_MODE_100G:
            if (bdk_numa_is_only_one())
                name_format = "100G%d";
            else
                name_format = "N%d.100G%d";
            break;
        case CGX_MODE_25G_KR:
            if (bdk_numa_is_only_one())
                name_format = "25GKR%d";
            else
                name_format = "N%d.25GKR%d";
            break;
        case CGX_MODE_50G_KR:
            if (bdk_numa_is_only_one())
                name_format = "50GKR%d";
            else
                name_format = "N%d.50GKR%d";
            break;
        case CGX_MODE_100G_KR4:
            if (bdk_numa_is_only_one())
                name_format = "100GKR%d";
            else
                name_format = "N%d.100GKR%d";
            break;
        case CGX_MODE_USXGMII:
            if (bdk_numa_is_only_one())
                name_format = "USXGMII%d";
            else
                name_format = "N%d.USXGMII%d";
            break;
    }
    if (bdk_numa_is_only_one())
        snprintf(handle->name, sizeof(handle->name), name_format, handle->interface, priv->port);
    else
        snprintf(handle->name, sizeof(handle->name), name_format, handle->node, handle->interface, priv->port);
    handle->name[sizeof(handle->name)-1] = 0;

    handle->flags |= BDK_IF_FLAGS_HAS_FCS;
    return 0;
}

/**
 * Link poll for 1Gbps protcols such as 1000BASE-X, SGMII, and QSGMII. This is
 * called perodically to control link status of GMP (GMI, PCS, and PMA).
 *
 * @param handle Handle for the port
 *
 * @return Zero on success, negative on failure
 */
static int sgmii_link(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    bool is_basex = ((priv->phy_address & BDK_IF_PHY_TYPE_MASK)== BDK_IF_PHY_TWSI);
    bool use_autoneg = (priv->phy_address != BDK_IF_PHY_FIXED_1GB) && (priv->phy_address != BDK_IF_PHY_FIXED_100MB);

    /* 29.5.2 Autonegotiation Execution
        Section 29.2.1 describes PCS autonegotiation. */

    /* Software should do the following to execute this autonegotiation when
       autonegotiation is desired: */
    /* (1) Enable the interface. Set CGX(0..1)_CMR(0..3)_CONFIG[ENABLE] = 1
       if not already set. */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_CONFIG(handle->interface, handle->index),
        c.s.enable = 1);

    /* (2) Disable GMI. Set CGX(0..1)_GMP_PCS_MISC(0..3)_CTL[GMXENO] = 1.
       Refer to Section 29.5.1 above. */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(handle->interface, handle->index),
        c.s.gmxeno = 1);

    /* (3) Write CGX(0..1)_GMP_PCS_MISC(0..3)_CTL[MODE,AN_OVRD, MAC_PHY,
       SAMP_PT] to the selected values. If the final speed (after
       autonegotiation) is known to be 10Mbit,
       CGX(0..1)_GMP_PCS_MISC(0..3)_CTL[SAMP_PT] should be written to the
       value appropriate for 10 Mbit (e.g. 50). Otherwise,
       CGX(0..1)_GMP_PCS_MISC(0..3)_CTL[SAMP_PT] should be written to the
       value appropriate for 100 Mbit (e.g., 5). */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(handle->interface, handle->index),
        c.s.mac_phy = (priv->phy_address == -1); /* Use PHY mode if no PHY configured */
        c.s.mode = is_basex;
        c.s.an_ovrd = !use_autoneg; /* Fixed speed doesn't use auto negotiation */
        c.s.samp_pt = (priv->phy_address == BDK_IF_PHY_FIXED_100MB) ? 5 : 1);

    /* (4) If desired, set the polarity of the SerDes link. Refer to
       Section 29.3.1 and CGX(0..1)_GMP_PCS_TX_RX(0..3)_POLARITY. */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_TX_RXX_POLARITY(handle->interface, handle->index),
        c.s.rxovrd = 0); /* RX Auto polarity */

    /* (5) Write CGX(0..1)_GMP_PCS_LINK(0..3)_TIMER[COUNT] with the appropriate
       value.
        - 1000BASE-X specifies a 10ms interval
        - SGMII specifies a 1.6ms interval */
    const uint64_t clock_mhz = bdk_clock_get_rate(handle->node, BDK_CLOCK_SCLK) / 1000000;
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_LINKX_TIMER(handle->interface, handle->index),
        if (is_basex)
        {
            /* 1000BASE-X */
            c.s.count = (10000ull * clock_mhz) >> 10;
        }
        else
        {
            /* SGMII */
            c.s.count = (1600ull * clock_mhz) >> 10;
        });

    /* (6) Write the advertisement register to be used as the
       tx_Config_Reg<D15:D0> of the autonegotiation.
        - In 1000BASE-X mode, tx_Config_Reg<D15:D0> is CGX(0..1)_GMP_PCS_AN(0..3)_ADV.
        - In SGMII PHY mode, tx_Config_Reg<D15:D0> is CGX(0..1)_GMP_PCS_SGM(0..3)_AN_ADV.
        - In SGMII MAC mode, tx_Config_Reg<D15:D0> is the fixed value 0x4001,
            so this step can be skipped. */
    if (is_basex)
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_ANX_ADV(handle->interface, handle->index),
            c.s.rem_flt = 0;
            c.s.pause = 3;
            c.s.hfd = 1;
            c.s.fd = 1);
    }
    else
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_SGMX_AN_ADV(handle->interface, handle->index),
            c.s.link = 0;
            c.s.dup = 1;
            c.s.speed = 2);
    }

    /* (7) Preload CGX(0..1)_GMP_PCS_MR(0..3)_CONTROL
        - CGX(0..1)_GMP_PCS_MR(0..3)_CONTROL[DUP,SPDLSB,SPDMSB] should be
        written to appropriate values if CGX(0..1)_GMP_PCS_MISC(0..3)_CTL[AN_OVRD] = 1.
        - Set CGX(0..1)_GMP_PCS_MR(0..3)_CONTROL[AN_EN] = 1 to enable autonegotiation. */
    BDK_CSR_INIT(pcs_miscx_ctl, handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(handle->interface, handle->index));
    if (pcs_miscx_ctl.s.an_ovrd)
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(handle->interface, handle->index),
            c.s.spdlsb = (priv->phy_address == BDK_IF_PHY_FIXED_100MB) ? 1 : 0;
            c.s.dup = 1;
            c.s.spdmsb = (priv->phy_address == BDK_IF_PHY_FIXED_100MB) ? 0 : 1);
    }
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(handle->interface, handle->index),
        c.s.an_en = use_autoneg);

    /* (8) Take PCS through a reset sequence.
       CGX(0..1)_GMP_PCS_MR(0..3)_CONTROL[PWR_DN] should be cleared to 0. Write
       CGX(0..1)_GMP_PCS_MR(0..3)_CONTROL[RESET] = 1 (while not changing the
       value of the other CGX(0..1)_GMP_PCS_MR(0..3)_CONTROL bits). Read
       CGX(0..1)_GMP_PCS_MR(0..3)_CONTROLRESET] until it changes value to 0. */
    BDK_CSR_INIT(control, handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(handle->interface, handle->index));
    BDK_CSR_INIT(status, handle->node, BDK_CGXX_GMP_PCS_MRX_STATUS(handle->interface, handle->index));
    if (control.s.pwr_dn)
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(handle->interface, handle->index),
            c.s.pwr_dn = 0);
    }
    if (control.s.pwr_dn || (use_autoneg && !status.s.an_cpt))
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(handle->interface, handle->index),
            c.s.reset = 1);
    }
    if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(handle->interface, handle->index), reset, ==, 0, 10000))
    {
        bdk_error("%s: Timeout waiting for reset finish\n", handle->name);
        return -1;
    }

    if (use_autoneg)
    {
        if (!status.s.an_cpt)
        {
            /* (9) Write CGX(0..1)_GMP_PCS_MR(0..3)_CONTROL[RST_AN] = 1 to ensure a
               fresh autonegotiation starts. */
            BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(handle->interface, handle->index),
                c.s.rst_an = 1);

            /* (10) Wait for CGX(0..1)_GMP_PCS_MR(0..3)_STATUS[AN_CPT] to be set,
               indicating that autonegotiation is complete. */
            BDK_TRACE(BGX, "%s: Waiting for auto-neg to finish\n", handle->name);
            return -1;
        }

        /* (11) The link-partner's advertisement can be observed at this point.
            - In 1000BASE-X mode, rx_Config_Reg<D15:D0> is CGX(0..1)_GMP_PCS_AN(0..3)_LP_ABIL.
            - In SGMII PHY mode, rx_Config_Reg<D15:D0> should be the constant
                0x4001, and need not be observed.
            - In SGMII MAC mode, rx_Config_Reg<D15:D0> is CGX(0..1)_GMP_PCS_SGM(0..3)_LP_ADV. */
        BDK_CSR_INIT(anx_results, handle->node, BDK_CGXX_GMP_PCS_ANX_RESULTS(handle->interface, handle->index));

        /* (12) The final mode can be determined. Section 29.2.2 describes how to
           do this. If the final selected speed is 10 Mbit,
           CGX(0..1)_GMP_PCS_MISC(0..3)_CTL[SAMP_PT] may be changed to the value
           most appropriate for 10Mbit operation at this point. */
        if (anx_results.s.spd == 0)
        {
            BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(handle->interface, handle->index),
                c.s.samp_pt = 0x50);
        }
    }

    /* Check final link status, read twice to clear sticky bits */
    BDK_CSR_READ(handle->node, BDK_CGXX_GMP_PCS_MRX_STATUS(handle->interface, handle->index));
    status.u = BDK_CSR_READ(handle->node, BDK_CGXX_GMP_PCS_MRX_STATUS(handle->interface, handle->index));
    if (status.s.lnk_st)
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(handle->interface, handle->index),
            c.s.gmxeno = 0);
    }
    return 0;
}

/**
 * @INTERNAL
 * Configure an SGMII link to the specified speed after the SERTES
 * link is up.
 *
 * @param interface Interface to init
 * @param index     Index of prot on the interface
 * @param link_info Link state to configure
 *
 * @return Zero on success, negative on failure
 */
static int sgmii_speed(bdk_if_handle_t handle, bdk_if_link_t link_info)
{
    const int cgx_block = handle->interface;
    const int cgx_index = handle->index;
    int is_enabled;

    /* Disable GMX before we make any changes. Remember the enable state */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_CONFIG(cgx_block, cgx_index),
        is_enabled = c.s.data_pkt_tx_en;
        c.s.data_pkt_tx_en = 0;
        c.s.data_pkt_rx_en = 0);

    /* Wait for GMX to be idle */
    if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_GMP_GMI_PRTX_CFG(cgx_block, cgx_index), rx_idle, ==, 1, 10000) ||
        BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_GMP_GMI_PRTX_CFG(cgx_block, cgx_index), tx_idle, ==, 1, 10000))
    {
        bdk_error("%s: Timeout waiting for idle\n", handle->name);
        return -1;
    }

    /* Read GMX CFG again to make sure the disable completed */
    BDK_CSR_INIT(prtx_cfg, handle->node, BDK_CGXX_GMP_GMI_PRTX_CFG(cgx_block, cgx_index));

    /* Get the misc control for PCS. We will need to set the duplication amount */
    BDK_CSR_INIT(pcsx_miscx_ctl_reg, handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx_block, cgx_index));

    /* Only change the duplex setting if the link is up */
    if (link_info.s.up)
        prtx_cfg.s.duplex = link_info.s.full_duplex;

    /* Do speed based setting for GMX */
    switch (link_info.s.speed)
    {
        case 10:
            prtx_cfg.s.speed = 0;
            prtx_cfg.s.speed_msb = 1;
            prtx_cfg.s.slottime = 0;
            pcsx_miscx_ctl_reg.s.samp_pt = 25; /* Setting from GMX-603 */
            BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_GMI_TXX_SLOT(cgx_block, cgx_index), 64);
            BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_GMI_TXX_BURST(cgx_block, cgx_index), 0);
            break;
        case 100:
            prtx_cfg.s.speed = 0;
            prtx_cfg.s.speed_msb = 0;
            prtx_cfg.s.slottime = 0;
            pcsx_miscx_ctl_reg.s.samp_pt = 0x5;
            BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_GMI_TXX_SLOT(cgx_block, cgx_index), 64);
            BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_GMI_TXX_BURST(cgx_block, cgx_index), 0);
            break;
        case 1000:
            prtx_cfg.s.speed = 1;
            prtx_cfg.s.speed_msb = 0;
            prtx_cfg.s.slottime = 1;
            pcsx_miscx_ctl_reg.s.samp_pt = 1;
            BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_GMI_TXX_SLOT(cgx_block, cgx_index), 512);
	    if (prtx_cfg.s.duplex)
                BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_GMI_TXX_BURST(cgx_block, cgx_index), 0); // full duplex
	    else
                BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_GMI_TXX_BURST(cgx_block, cgx_index), 8192); // half duplex
            break;
        default:
            break;
    }

    /* Write the new misc control for PCS */
    BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx_block, cgx_index), pcsx_miscx_ctl_reg.u);

    /* Write the new GMX settings with the port still disabled */
    BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_GMI_PRTX_CFG(cgx_block, cgx_index), prtx_cfg.u);

    /* Restore the enabled / disabled state */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_CONFIG(cgx_block, cgx_index),
        c.s.data_pkt_tx_en = is_enabled;
        c.s.data_pkt_rx_en = link_info.s.up && is_enabled);
    return 0;
}

/**
 * Setup auto neg on a port. Called one at init for each port
 *
 * @param handle Port to configure
 *
 * @return Zero no success, negative on failure
 */
static int setup_auto_neg(bdk_if_handle_t handle)
{
    const int cgx_block = handle->interface;
    const int cgx_index = handle->index;
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;

    /* 10GBASE-KR and 40GBASE-KR4 optionally support auto negotiation. Note
       that this referse to auto negotiation for links other than SGMII. SGMII
       takes a different code path */
    int use_auto_neg = (priv->mode == CGX_MODE_10G_KR) || (priv->mode == CGX_MODE_40G_KR);

    /* Software should do the following to execute Auto-Negotiation when
       desired: */
    /* 1. Set CGX(0..5)_SPU(0..3)_AN_CONTROL[AN_EN] = 1. */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_AN_CONTROL(cgx_block, cgx_index),
        c.s.xnp_en=0; /* Disable extended next pages */
        c.s.an_en = use_auto_neg);

    /* 2. Program the negotiation parameters to be advertised to the link
       parter in CGX(0..5)_SPU(0..3)_AN_ADV. The advertised parameters must
       be consistent with the programmed CGX(0..5)_CMR(0..3)_CONFIG[LMAC_TYPE]
       and CGX(0..5)_SPU(0..3)_FEC_CONTROL[FEC_EN] values. */
    BDK_CSR_INIT(fec_control, handle->node, BDK_CGXX_SPUX_FEC_CONTROL(cgx_block, cgx_index));
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_AN_ADV(cgx_block, cgx_index),
        c.s.fec_req = fec_control.s.fec_en;
        c.s.fec_able = 1;
        c.s.a100g_cr10 = 0;
        c.s.a40g_cr4 = 0;
        c.s.a40g_kr4 = (priv->mode == CGX_MODE_40G_KR);
        c.s.a10g_kr = (priv->mode == CGX_MODE_10G_KR);
        c.s.a10g_kx4 = 0;
        c.s.a1g_kx = 0;
        c.s.xnp_able = 0;
        c.s.rf = 0);

    /* 3. Set CGX(0..5)_SPU_DBG_CONTROL[AN_ARB_LINK_CHK_EN] = 1. */
    /* This needs to be set if any port on the CGX uses AN */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPU_DBG_CONTROL(cgx_block),
        c.s.an_nonce_match_dis=1; /* Needed for loopback */
        c.s.an_arb_link_chk_en |= use_auto_neg);

    /* 4. Execute the link bring-up sequence in Section 33.6.3. */
    /* Done after this function is called */

    /* 5. If the auto-negotiation protocol is successful,
       CGX(0..5)_SPU(0..3)_AN_ADV[AN_COMPLETE] is set along with
       CGX(0..5)_SPU(0..3)_INT[AN_COMPLETE] when the link is up. */
    /* Done after this function is called */
    return 0;
}

/**
 * Port initialization for all protocols except for SGMII. Its
 * call xaui_init() for the lack of a better name, but it
 * applies to everything other than SGMII.
 *
 * @param handle Handle to the port
 *
 * @return Zero on success, negative on failure
 */
static int xaui_init(bdk_if_handle_t handle)
{
    const int cgx_block = handle->interface;
    const int cgx_index = handle->index;
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;

    /* NOTE: This code was moved first, out of order compared to the HRM
       because the RESET causes all SPU registers to loose their value */
    /* 4. Next, bring up the SMU/SPU and the CGX reconciliation layer logic: */
    /* 4a. Take SMU/SPU through a reset sequence. Write
        CGX(0..5)_SPU(0..3)_CONTROL1[RESET] = 1. Read
        CGX(0..5)_SPU(0..3)_CONTROL1[RESET] until it changes value to 0. Keep
        CGX(0..5)_SPU(0..3)_MISC_CONTROL[RX_PACKET_DIS] = 1 to disable
        reception. */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_CONTROL1(cgx_block, cgx_index),
            c.s.reset = 1);
        if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_SPUX_CONTROL1(cgx_block, cgx_index), reset, ==, 0, 1000))
        {
            BDK_TRACE(BGX, "%s: SPU stuck in reset\n", handle->name);
            return -1;
        }
    }

    /* 1. Write CGX(0..5)_CMR(0..3)_CONFIG[ENABLE] to 0,
       CGX(0..5)_SPU(0..3)_CONTROL1[LO_PWR] = 1 and
       CGX(0..5)_SPU(0..3)_MISC_CONTROL[RX_PACKET_DIS] = 1. */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_CONFIG(cgx_block, cgx_index),
        c.s.enable = 0);
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_CONTROL1(cgx_block, cgx_index),
        c.s.lo_pwr = 1);
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_MISC_CONTROL(cgx_block, cgx_index),
        c.s.rx_packet_dis = 1);

    /* 2. At this point, it may be appropriate to disable all CGX and SMU/SPU
       interrupts, as a number of them will occur during bring-up of the Link.
        - zero CGX(0..5)_SMU(0..3)_RX_INT
        - zero CGX(0..5)_SMU(0..3)_TX_INT
        - zero CGX(0..5)_SPU(0..3)_INT */
    BDK_CSR_WRITE(handle->node, BDK_CGXX_SMUX_RX_INT(cgx_block, cgx_index), BDK_CSR_READ(handle->node, BDK_CGXX_SMUX_RX_INT(cgx_block, cgx_index)));
    BDK_CSR_WRITE(handle->node, BDK_CGXX_SMUX_TX_INT(cgx_block, cgx_index), BDK_CSR_READ(handle->node, BDK_CGXX_SMUX_TX_INT(cgx_block, cgx_index)));
    BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_INT(cgx_block, cgx_index), BDK_CSR_READ(handle->node, BDK_CGXX_SPUX_INT(cgx_block, cgx_index)));

    /* 3. Configure the CGX LMAC. */
    /* 3a. Configure the LMAC type (40GBASE-R/10GBASE-R/RXAUI/XAUI) and
        SerDes selection in the CGX(0..5)_CMR(0..3)_CONFIG register, but keep
        the ENABLE, DATA_PKT_TX_EN and DATA_PKT_RX_EN bits clear. */
    /* Already done in cgx_setup_one_time */

    /* 3b. Write CGX(0..5)_SPU(0..3)_CONTROL1[LO_PWR] = 1 and
       CGX(0..5)_SPU(0..3)_MISC_CONTROL[RX_PACKET_DIS] = 1. */
    /* Duplicate step */

    /* 3c. Initialize the selected SerDes lane(s) in the QLM. See Section
       28.1.2.2 in the GSER chapter. */
    /* Already done in QLM setup */

    /* 3d. For 10GBASE-KR or 40GBASE-KR, enable link training by writing
       CGX(0..5)_SPU(0..3)_BR_PMD_CONTROL[TRAIN_EN] = 1. */
    if (priv->use_training)
    {
        /* These registers aren't cleared when training is restarted. Manually
           clear them */
        BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_BR_PMD_LP_CUP(cgx_block, cgx_index), 0);
        BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_BR_PMD_LD_CUP(cgx_block, cgx_index), 0);
        BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_BR_PMD_LD_REP(cgx_block, cgx_index), 0);
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_BR_PMD_CONTROL(cgx_block, cgx_index),
            c.s.train_en = 1);
    }

    /* 3e. Program all other relevant CGX configuration while
       CGX(0..5)_CMR(0..3)_CONFIG[ENABLE] = 0. This includes all things
       described in this chapter. */

    /* 3f. If Forward Error Correction is desired for 10GBASE-R or 40GBASE-R,
       enable it by writing CGX(0..5)_SPU(0..3)_FEC_CONTROL[FEC_EN] = 1.
       BDK:
        FEC is optional for 10GBASE-KR, 40GBASE-KR4, and XLAUI. We're going
        to disable it by default per recommendation from Scott Meninger */
    int use_fec = 0;
    use_fec &= ((priv->mode == CGX_MODE_10G_KR) ||
                (priv->mode == CGX_MODE_40G_KR) ||
                (priv->mode == CGX_MODE_XLAUI));
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_FEC_CONTROL(cgx_block, cgx_index),
        c.s.fec_en = use_fec);

    /* 3g. If Auto-Negotiation is desired, configure and enable
       Auto-Negotiation as described in Section 33.6.2. */
    if (setup_auto_neg(handle))
        return -1;

    /* 3h. Set CGX(0..5)_CMR(0..3)_CONFIG[ENABLE] = 1 and
       CGX(0..5)_SPU(0..3)_CONTROL1[LO_PWR] = 0 to enable the LMAC. */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_CONFIG(cgx_block, cgx_index),
        c.s.enable = 1);
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_CONTROL1(cgx_block, cgx_index),
        c.s.lo_pwr = 0);

    /* 4b. Set the polarity and lane swapping of the QLM SerDes. Refer to
        Section 33.4.1, CGX(0..5)_SPU(0..3)_MISC_CONTROL[XOR_TXPLRT,XOR_RXPLRT]
        and CGX(0..5)_SPU(0..3)_MISC_CONTROL[TXPLRT,RXPLRT]. */

    /* 4c. Write CGX(0..5)_SPU(0..3)_CONTROL1[LO_PWR] = 0. */
    /* Duplicate step */

    /* 4d. Select Deficit Idle Count mode and unidirectional enable/disable
       via CGX(0..5)_SMU(0..3)_TX_CTL[DIC_EN,UNI_EN]. */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SMUX_TX_CTL(cgx_block, cgx_index),
        c.s.dic_en = 1; /* Enable better IFG packing and improves performance */
        c.s.uni_en = 0);

    /* RXAUI with Marvell PHY requires some tweaking */
    if (priv->mode == CGX_MODE_RXAUI)
    {
        if (priv->phy_address != -1)
            __bdk_if_phy_xs_init(handle->node, priv->phy_address);
    }

    return 0;
}

/**
 * Restart training after traiing fails
 *
 * @param handle Port to restart
 */
static void restart_training(bdk_if_handle_t handle)
{
    const int cgx_block = handle->interface;
    const int cgx_index = handle->index;
    BDK_CSR_DEFINE(spux_int, BDK_CGXX_SPUX_INT(cgx_block, cgx_index));
    /* Clear the training interrupts (W1C) */
    spux_int.u = 0;
    spux_int.s.training_failure = 1;
    spux_int.s.training_done = 1;
    BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_INT(cgx_block, cgx_index), spux_int.u);
    /* These registers aren't cleared when training is restarted. Manually
       clear them */
    BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_BR_PMD_LP_CUP(cgx_block, cgx_index), 0);
    BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_BR_PMD_LD_CUP(cgx_block, cgx_index), 0);
    BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_BR_PMD_LD_REP(cgx_block, cgx_index), 0);
    /* Restart training */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_BR_PMD_CONTROL(cgx_block, cgx_index),
        c.s.train_restart = 1);
}

/**
 * Link up/down processing for all protocols except for SGMII. Its call
 * xaui_link() for the lack of a better name, but it applies to
 * everything other than SGMII.
 *
 * @param handle Handle to the port
 * @param force_link_init
 *               Set to force link init even if the link is already up
 *
 * @return Zero on success, negative on failure
 */
static int xaui_link(bdk_if_handle_t handle, bool force_link_init)
{
    const int cgx_block = handle->interface;
    const int cgx_index = handle->index;
    const int TIMEOUT = 100; /* 100us */
    cgx_priv_t *priv = (cgx_priv_t *)handle->priv;

    /* Check if the link is up */
    if (!force_link_init)
    {
        BDK_CSR_INIT(status1, handle->node, BDK_CGXX_SPUX_STATUS1(cgx_block, cgx_index));
        BDK_CSR_INIT(rx_ctl, handle->node, BDK_CGXX_SMUX_RX_CTL(cgx_block, cgx_index));
        BDK_CSR_INIT(misc_control, handle->node, BDK_CGXX_SPUX_MISC_CONTROL(cgx_block, cgx_index));
        bool link_up = status1.s.rcv_lnk && (rx_ctl.s.status == 0) && !misc_control.s.rx_packet_dis;
        if (link_up)
            return 0;
    }

    /* Disable packet reception */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_MISC_CONTROL(cgx_block, cgx_index),
        c.s.rx_packet_dis = 1);

    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        /* Check if we're using auto negotiation */
        BDK_CSR_INIT(spux_an_control, handle->node, BDK_CGXX_SPUX_AN_CONTROL(cgx_block, cgx_index));
        if (spux_an_control.s.an_en)
        {
            BDK_CSR_INIT(an_status, handle->node, BDK_CGXX_SPUX_AN_STATUS(cgx_block, cgx_index));
            if (!an_status.s.an_complete)
            {
                uint64_t now = bdk_clock_get_count(BDK_CLOCK_TIME);
                uint64_t next_restart = priv->restart_auto_neg + bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) * 2;
                if (now >= next_restart)
                {
                    BDK_TRACE(BGX, "%s: Waiting for auto negotiation\n", handle->name);
                    return -1;
                }
                priv->restart_auto_neg = now;
                /* Restart auto negotiation */
                BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_AN_CONTROL(cgx_block, cgx_index),
                    c.s.an_restart = 1);
                BDK_TRACE(BGX, "%s: Restarting auto negotiation\n", handle->name);
                return -1;
            }
        }

        if (priv->use_training)
        {
            /* Check if training is done */
            BDK_CSR_INIT(spux_int, handle->node, BDK_CGXX_SPUX_INT(cgx_block, cgx_index));
            if (spux_int.s.training_failure)
            {
                restart_training(handle);
                BDK_TRACE(BGX, "%s: Restarting link training\n", handle->name);
                return -1;
            }
            if (!spux_int.s.training_done)
            {
                BDK_TRACE(BGX, "%s: Waiting for link training\n", handle->name);
                return -1;
            }
        }

        /* (GSER-21957) GSER RX Equalization may make >= 5gbaud non-KR channel better
           With DXAUI, RXAUI, XFI and XLAUI, we need to perform RX equalization when
           the link is receiving data the first time */
        BDK_CSR_INIT(spux_control1, handle->node, BDK_CGXX_SPUX_CONTROL1(handle->interface, priv->port));
        if (spux_control1.s.loopbck)
        {
            /* Skip RX equalization when in loopback */
        }
        else if ((priv->mode == CGX_MODE_XFI) || (priv->mode == CGX_MODE_XLAUI) ||
                 (priv->mode == CGX_MODE_DXAUI) || (priv->mode == CGX_MODE_RXAUI))
        {
            /* We need to do RX equalization on every lane in use by this port.
               Figure out the starting QLM and lanes in use */
            int qlm = bdk_qlm_get(handle->node, BDK_IF_CGX, handle->interface, handle->index);
            uint64_t mask = bdk_if_get_lane_mask(handle);
            /* The lane mask may span multiple QLM/DLM. We require the QLM/DLM
               to be sequencial */
            while (mask)
            {
                /* Get the number of lanes on this QLM/DLM */
                int num_lanes = bdk_qlm_get_lanes(handle->node, qlm);
                uint64_t this_qlm_mask = bdk_build_mask(num_lanes);
                /* Check if all the lanes are used by this port */
                if ((this_qlm_mask & mask) == this_qlm_mask)
                {
                    /* Do RX equalization across entire QLM/DLM */
                    if (bdk_qlm_rx_equalization(handle->node, qlm, -1))
                    {
                        BDK_TRACE(BGX, "%s: Waiting for RX equalization\n", handle->name);
                        return -1;
                    }
                }
                else
                {
                    /* Not all lanes are used, loop one at a time */
                    for (int lane = 0; lane < num_lanes; lane++)
                    {
                        if (mask & (1ull << lane))
                        {
                            if (bdk_qlm_rx_equalization(handle->node, qlm, lane))
                            {
                                BDK_TRACE(BGX, "%s: Waiting for RX equalization\n", handle->name);
                                return -1;
                            }
                        }
                    }
                }
                /* Move the the next QLM/DLM */
                mask >>= num_lanes;
                qlm++;
            }
        }

        /* Wait for PCS to come out of reset */
        if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_SPUX_CONTROL1(cgx_block, cgx_index), reset, ==, 0, TIMEOUT))
        {
            BDK_TRACE(BGX, "%s: PCS in reset\n", handle->name);
            return -1;
        }

        if ((priv->mode == CGX_MODE_XFI) || (priv->mode == CGX_MODE_XLAUI) ||
            (priv->mode == CGX_MODE_10G_KR) || (priv->mode == CGX_MODE_40G_KR))
        {
            /* 10G-R/40G-R - Wait for BASE-R PCS block lock */
            if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_SPUX_BR_STATUS1(cgx_block, cgx_index), blk_lock, ==, 1, TIMEOUT))
            {
                BDK_TRACE(BGX, "%s: BASE-R PCS block not locked\n", handle->name);
                return -1;
            }
        }
        else
        {
            /* XAUI/DXAUI/RXAUI - Wait for PCS to be aligned */
            if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_SPUX_BX_STATUS(cgx_block, cgx_index), alignd, ==, 1, TIMEOUT))
            {
                BDK_TRACE(BGX, "%s: PCS not aligned\n", handle->name);
                return -1;
            }
        }

        /* Set the CGXX_SPUX_BR_STATUS2[latched_lock] bit (latching low). This
           will be checked prior to enabling packet tx and rx, ensuring block
           lock is sustained throughout the CGX link-up procedure */
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_BR_STATUS2(cgx_block, cgx_index),
            c.s.latched_lock = 1);

        /* Clear rcvflt bit if it is high (it latchs high) and read it back */
        BDK_CSR_INIT(spux_status2, handle->node, BDK_CGXX_SPUX_STATUS2(cgx_block, cgx_index));
        if (spux_status2.s.rcvflt)
        {
            BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_STATUS2(cgx_block, cgx_index), spux_status2.u);
            spux_status2.u = BDK_CSR_READ(handle->node, BDK_CGXX_SPUX_STATUS2(cgx_block, cgx_index));
        }
        if (spux_status2.s.rcvflt)
        {
            BDK_TRACE(BGX, "%s: Receive fault, need to retry\n", handle->name);
            if (priv->use_training)
            {
                BDK_CSR_INIT(spux_int, handle->node, BDK_CGXX_SPUX_INT(cgx_block, cgx_index));
                if (!spux_int.s.training_done)
                    restart_training(handle);
                else /* Clear everything and restart */
                    BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_INT(cgx_block, cgx_index), spux_int.u);
            }
            return -1;
        }
        /* Wait for MAC RX to be ready */
        if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_SMUX_RX_CTL(cgx_block, cgx_index), status, ==, 0, TIMEOUT))
        {
            BDK_TRACE(BGX, "%s: RX not ready\n", handle->name);
            return -1;
        }

        /* (6) Configure CGX */

        /* Wait for CGX RX to be idle */
        if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_SMUX_CTRL(cgx_block, cgx_index), rx_idle, ==, 1, TIMEOUT))
        {
            BDK_TRACE(BGX, "%s: RX not idle\n", handle->name);
            return -1;
        }
        /* Wait for CGX TX to be idle */
        if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_SMUX_CTRL(cgx_block, cgx_index), tx_idle, ==, 1, TIMEOUT))
        {
            BDK_TRACE(BGX, "%s: TX not idle\n", handle->name);
            return -1;
        }
        /* rcvflt should still be 0 */
        spux_status2.u = BDK_CSR_READ(handle->node, BDK_CGXX_SPUX_STATUS2(cgx_block, cgx_index));
        if (spux_status2.s.rcvflt)
        {
            BDK_TRACE(BGX, "%s: Receive fault, need to retry\n", handle->name);
            return -1;
        }
        /* Receive link is latching low. Force it high and verify it */
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_STATUS1(cgx_block, cgx_index),
            c.s.rcv_lnk = 1);
        if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_CGXX_SPUX_STATUS1(cgx_block, cgx_index), rcv_lnk, ==, 1, TIMEOUT))
        {
            BDK_TRACE(BGX, "%s: Receive link down\n", handle->name);
            return -1;
        }

        if ((priv->mode == CGX_MODE_XFI) || (priv->mode == CGX_MODE_XLAUI) ||
            (priv->mode == CGX_MODE_10G_KR) || (priv->mode == CGX_MODE_40G_KR))
        {
            /* Clear out the CGX error counters/bits. These errors are expected
               as part of the CGX link up procedure */
            /* BIP_ERR counters clear as part of this read */
            for (int counter = 0; counter < 20; counter++)
                BDK_CSR_READ(handle->node, BDK_CGXX_SPUX_LNX_BR_BIP_ERR_CNT(cgx_block, cgx_index, counter));
            /* BER_CNT and ERR_BLKs clear as part of this read */
            BDK_CSR_INIT(spu_br_status2, handle->node, BDK_CGXX_SPUX_BR_STATUS2(cgx_block, cgx_index));
            /* Checking that latched BLOCK_LOCK is still set (Block Lock never lost) */
            if (!spu_br_status2.s.latched_lock)
            {
                BDK_TRACE(BGX, "%s: BASE-R PCS block lock lost, need to retry\n", handle->name);
                return -1;
            }

            /* If set, clear the LATCHED_BER by writing it to a one.  */
            if (spu_br_status2.s.latched_ber)
                BDK_CSR_WRITE(handle->node, BDK_CGXX_SPUX_BR_STATUS2(cgx_block, cgx_index), spu_br_status2.u);
            /* Complete a BER test.  If latched_ber = 1, then BER >= 10e^4 */
            /* The BER detection time window is 125us for 10GBASE-R (1250us for 40G). */
            bdk_wait_usec(1500);
            spu_br_status2.u = BDK_CSR_READ(handle->node, BDK_CGXX_SPUX_BR_STATUS2(cgx_block, cgx_index));
            if (spu_br_status2.s.latched_ber)
            {
                BDK_TRACE(BGX, "%s: BER test failed, BER >= 10e^4, need to retry\n", handle->name);
                return -1;
            }
        }
        /* Some PHYs have been found that pass all the above checks but report
           a fault in CGXX_SMUX_RX_CTL[status]. Check for these */
        BDK_CSR_INIT(rx_ctl, handle->node, BDK_CGXX_SMUX_RX_CTL(cgx_block, cgx_index));
        if (rx_ctl.s.status)
        {
            BDK_TRACE(BGX, "%s: Reports a %s fault, need retry\n", handle->name,
                (rx_ctl.s.status == 1) ? "local" :
                (rx_ctl.s.status == 2) ? "remote" :
                "reserved");
            return -1;
        }
    }

    /* Enable packet reception */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_MISC_CONTROL(cgx_block, cgx_index),
        c.s.rx_packet_dis = 0);
    return 0;
}

static int if_init(bdk_if_handle_t handle)
{
    const int cgx_block = handle->interface;
    const int cgx_index = handle->index;
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    if (cgx_setup_one_time(handle))
        return -1;

    if ((priv->mode != CGX_MODE_SGMII) && (priv->mode != CGX_MODE_QSGMII))
    {
        /* Everything other than SGMII/QSGMII */
        xaui_init(handle);
    }

    /* Configure to allow max sized frames */
    const int buffer_size = bdk_config_get_int(BDK_CONFIG_PACKET_BUFFER_SIZE);
    int max_size = buffer_size * 12; /* 12 is from nic_cqe_rx_s */
    BDK_CSR_WRITE(handle->node, BDK_CGXX_GMP_GMI_RXX_JABBER(cgx_block, cgx_index), max_size);
    BDK_CSR_WRITE(handle->node, BDK_CGXX_SMUX_RX_JABBER(cgx_block, cgx_index), max_size);

    /* Disable frame alignment if using preamble. This allows the link to
        reach full rate for odd length packets. For example, without this
        SGMII is slower than RGMII for 65 byte packets */
    BDK_CSR_INIT(txx_append, handle->node, BDK_CGXX_GMP_GMI_TXX_APPEND(cgx_block, cgx_index));
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_GMI_TXX_SGMII_CTL(cgx_block, cgx_index),
        c.s.align = !txx_append.s.preamble);

    int bytes_per_port;
    BDK_CSR_INIT(cgxx_const, handle->node, BDK_CGXX_CONST(handle->interface));
    bytes_per_port = cgxx_const.s.tx_fifosz / priv->num_port;
    if (bdk_nix_port_init(handle, BDK_NIX_TYPE_CGX, bytes_per_port))
        return -1;

    return 0;
}

static int if_enable(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_CONFIG(handle->interface, priv->port),
        c.s.enable = 1;
        c.s.data_pkt_tx_en = 1;
        c.s.data_pkt_rx_en = 1);
    return 0;
}

static int if_disable(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_CONFIG(handle->interface, priv->port),
        c.s.enable = 0;
        c.s.data_pkt_tx_en = 0;
        c.s.data_pkt_rx_en = 0);
    return 0;
}

/**
 * Get SGMII link speed
 *
 * @param handle
 *
 * @return
 */
static bdk_if_link_t if_link_get_sgmii(bdk_if_handle_t handle)
{
    const int cgx_block = handle->interface;
    const int cgx_index = handle->index;
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    bdk_if_link_t result;

    result.u64 = 0;

    BDK_CSR_INIT(gmp_pcs_mrx_control, handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx_block, cgx_index));
    BDK_CSR_INIT(gmp_pcs_mrx_status, handle->node, BDK_CGXX_GMP_PCS_MRX_STATUS(cgx_block, cgx_index));
    BDK_CSR_INIT(gmp_pcs_miscx_ctl, handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx_block, cgx_index));

    int qlm = bdk_qlm_get(handle->node, BDK_IF_CGX, handle->interface, handle->index);
    int speed = bdk_qlm_get_gbaud_mhz(handle->node, qlm) * 8 / 10;
    if (priv->mode == CGX_MODE_QSGMII) /* 4 ports on one lane, divide speed */
        speed /= 4;

    if (bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        /* The simulator gives you a simulated 1Gbps full duplex link */
        result.s.up = 1;
        result.s.full_duplex = 1;
        result.s.speed = speed;
        return result;
    }

    /* Perform a full link check if:
       1) The link reports bad status
       2) AUto negotiation is enabled and not complete
       3) GMP is disabled */
    bool check_link = !gmp_pcs_mrx_status.s.lnk_st ||
        (gmp_pcs_mrx_control.s.an_en && !gmp_pcs_mrx_status.s.an_cpt) ||
        gmp_pcs_miscx_ctl.s.gmxeno;
    if (check_link)
    {
        if (sgmii_link(handle))
            return result;

        /* Re-read registers as they may have changed */
        gmp_pcs_mrx_control.u = BDK_CSR_READ(handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx_block, cgx_index));
        gmp_pcs_mrx_status.u = BDK_CSR_READ(handle->node, BDK_CGXX_GMP_PCS_MRX_STATUS(cgx_block, cgx_index));
        gmp_pcs_miscx_ctl.u = BDK_CSR_READ(handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx_block, cgx_index));
    }

    /* Force 1Gbps full duplex link for internal loopback */
    if (gmp_pcs_mrx_control.s.loopbck1)
    {
        result.s.up = 1;
        result.s.full_duplex = 1;
        result.s.speed = speed;
        return result;
    }

    /* If auto negotiation is disabled, report speed based on the hardware setup */
    if (!gmp_pcs_mrx_control.s.an_en)
    {
        if (gmp_pcs_mrx_status.s.lnk_st)
        {
            result.s.up = gmp_pcs_mrx_status.s.lnk_st;
            result.s.full_duplex = gmp_pcs_mrx_control.s.dup;
            int spd = (gmp_pcs_mrx_control.s.spdmsb << 1) | gmp_pcs_mrx_control.s.spdlsb;
            switch (spd)
            {
                case 0:
                    result.s.speed = speed / 100;
                    break;
                case 1:
                    result.s.speed = speed / 10;
                    break;
                case 2:
                    result.s.speed = speed;
                    break;
                default:
                    result.s.speed = 0;
                    result.s.up = 0;
                    break;
            }
        }
        return result;
    }

    /* Read the autoneg results and use thim if complete */
    BDK_CSR_INIT(gmp_pcs_anx_results, handle->node, BDK_CGXX_GMP_PCS_ANX_RESULTS(cgx_block, cgx_index));
    if (gmp_pcs_anx_results.s.an_cpt && gmp_pcs_anx_results.s.link_ok)
    {
        /* SGMII auto negotiation reports bad results for link down. Check the actual PHY */
        if ((gmp_pcs_miscx_ctl.s.mode == 0) && (priv->phy_address != -1))
            return __bdk_if_phy_get(handle->node, priv->phy_address);

        /* Auto negotiation is complete. Set status accordingly */
        result.s.full_duplex = gmp_pcs_anx_results.s.dup;
        result.s.up = gmp_pcs_anx_results.s.link_ok;
        switch (gmp_pcs_anx_results.s.spd)
        {
            case 0:
                result.s.speed = speed / 100;
                break;
            case 1:
                result.s.speed = speed / 10;
                break;
            case 2:
                result.s.speed = speed;
                break;
            default:
                result.s.speed = 0;
                result.s.up = 0;
                break;
        }
    }
    return result;
}

/**
 * Get link status of ports in modes other than SGMII
 *
 * @param handle Port to query
 *
 * @return Port speed structure
 */
static bdk_if_link_t if_link_get_xaui(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    bdk_if_link_t result;
    result.u64 = 0;

    int link_up;
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        link_up = 1;
    }
    else
    {
        link_up = (xaui_link(handle, false) == 0);
    }

    if (link_up)
    {
        int qlm = bdk_qlm_get(handle->node, BDK_IF_CGX, handle->interface, handle->index);
        result.s.up = 1;
        result.s.full_duplex = 1;
        uint64_t speed = bdk_qlm_get_gbaud_mhz(handle->node, qlm);
        switch (priv->mode)
        {
            case CGX_MODE_SGMII:
            case CGX_MODE_QSGMII:
                /* Using 8b10b symbol encoding */
                speed = (speed * 8 + 5) / 10;
                result.s.lanes = 1;
                break;
            case CGX_MODE_XFI:
            case CGX_MODE_10G_KR:
            case CGX_MODE_25G:
            case CGX_MODE_25G_KR:
            case CGX_MODE_USXGMII:
                /* Using 64b66b symbol encoding */
                speed = (speed * 64 + 33) / 66;
                result.s.lanes = 1;
                break;
            case CGX_MODE_XAUI:
            case CGX_MODE_DXAUI:
                /* Using 8b10b symbol encoding */
                speed = (speed * 8 + 5) / 10;
                result.s.lanes = 4;
                break;
            case CGX_MODE_RXAUI:
                /* Using 8b10b symbol encoding */
                speed = (speed * 8 + 5) / 10;
                result.s.lanes = 2;
                break;
            case CGX_MODE_XLAUI:
            case CGX_MODE_40G_KR:
            case CGX_MODE_100G:
            case CGX_MODE_100G_KR4:
                /* Using 64b66b symbol encoding */
                speed = (speed * 64 + 33) / 66;
                result.s.lanes = 4;
                break;
            case CGX_MODE_50G:
            case CGX_MODE_50G_KR:
                /* Using 64b66b symbol encoding */
                speed = (speed * 64 + 33) / 66;
                result.s.lanes = 2;
                break;
        }
        speed *= result.s.lanes;
        result.s.speed = speed;
    }
    return result;
}

static bdk_if_link_t if_link_get(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    bdk_if_link_t result;
    result.u64 = 0;

    if ((priv->mode == CGX_MODE_SGMII) || (priv->mode == CGX_MODE_QSGMII))
        result = if_link_get_sgmii(handle);
    else
        result = if_link_get_xaui(handle);
    return result;
}

static void if_link_set(bdk_if_handle_t handle, bdk_if_link_t link_info)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    if ((priv->mode == CGX_MODE_SGMII) || (priv->mode == CGX_MODE_QSGMII))
    {
        int status = sgmii_link(handle);
        if (status == 0)
            sgmii_speed(handle, link_info);
    }
    else
        xaui_link(handle, false);
}

/**
 * Setup loopback
 *
 * @param handle
 * @param loopback
 *
 * @return
 */
static int if_loopback(bdk_if_handle_t handle, bdk_if_loopback_t loopback)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;

    /* INT_BEAT_GEN must be set for loopback if the QLMs are not clocked. Set
       it whenever we use internal loopback */
    BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_CMRX_CONFIG(handle->interface, priv->port),
        c.s.int_beat_gen = (loopback & BDK_IF_LOOPBACK_INTERNAL));

    if ((priv->mode == CGX_MODE_SGMII) || (priv->mode == CGX_MODE_QSGMII))
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MRX_CONTROL(handle->interface, priv->port),
            c.s.loopbck1 = ((loopback & BDK_IF_LOOPBACK_INTERNAL) != 0));
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_GMP_PCS_MISCX_CTL(handle->interface, priv->port),
            c.s.loopbck2 = ((loopback & BDK_IF_LOOPBACK_EXTERNAL) != 0));
        sgmii_link(handle);
    }
    else
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SPUX_CONTROL1(handle->interface, priv->port),
            c.s.loopbck = ((loopback & BDK_IF_LOOPBACK_INTERNAL) != 0));
        BDK_CSR_MODIFY(c, handle->node, BDK_CGXX_SMUX_EXT_LOOPBACK(handle->interface, priv->port),
            c.s.en = ((loopback & BDK_IF_LOOPBACK_EXTERNAL) != 0));
        xaui_link(handle, true);
    }
    return 0;
}

/**
 * Get the interface RX and TX counters.
 *
 * @param handle Handle of port
 *
 * @return Statistics
 */
static const bdk_if_stats_t *if_get_stats(bdk_if_handle_t handle)
{
    bdk_nix_fill_rx_stats(handle);

    /* FCS, if present, is already accounted for */
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    BDK_CSR_INIT(pkts, handle->node, BDK_CGXX_CMRX_TX_STAT5(handle->interface,priv->port));
    BDK_CSR_INIT(octs, handle->node, BDK_CGXX_CMRX_TX_STAT4(handle->interface,priv->port));
    handle->stats.tx.packets = bdk_update_stat_with_overflow(pkts.u, handle->stats.tx.packets, 48);
    handle->stats.tx.octets = bdk_update_stat_with_overflow(octs.u, handle->stats.tx.octets, 48);

    bdk_nix_fill_tx_stats(handle);
    return &handle->stats;
}

/**
 * Return the QLM/DLM lane mask used by the port. Bit 0 is lane 0 on the QLM/DLM
 * return by bdk_if_get_qlm()
 *
 * @param handle Handle to query
 *
 * @return Mask of lanes in use
 */
static uint64_t if_get_lane_mask(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    switch (priv->mode)
    {
        case CGX_MODE_SGMII:
        case CGX_MODE_QSGMII:
        case CGX_MODE_XFI:
        case CGX_MODE_10G_KR:
        case CGX_MODE_25G:
        case CGX_MODE_25G_KR:
        case CGX_MODE_USXGMII:
        {
            BDK_CSR_INIT(cmrx, handle->node, BDK_CGXX_CMRX_CONFIG(handle->interface, handle->index));
            int qlm = bdk_qlm_get(handle->node, BDK_IF_CGX, handle->interface, handle->index);
            int num_lanes = bdk_qlm_get_lanes(handle->node, qlm);
            /* Even though CN80XX only has one lane per DLM, CGX treats it like
               there are two. It's part of the hardware's teams plan to make
               every chip a special case, keeping software busy forever */
            if (cavium_is_altpkg(CAVIUM_CN81XX) && (qlm < 2))
                num_lanes = 2;
            int start_lane = cmrx.s.lane_to_sds & 3;
            if (start_lane >= num_lanes)
                return 1ull << (start_lane - num_lanes); /* One lane on second DLM */
            return 1ull << start_lane; /* One lane */
        }
        case CGX_MODE_RXAUI:
        case CGX_MODE_50G:
        case CGX_MODE_50G_KR:
        {
            BDK_CSR_INIT(cmrx, handle->node, BDK_CGXX_CMRX_CONFIG(handle->interface, handle->index));
            int qlm = bdk_qlm_get(handle->node, BDK_IF_CGX, handle->interface, handle->index);
            int num_lanes = bdk_qlm_get_lanes(handle->node, qlm);
            int start_lane = cmrx.s.lane_to_sds & 3;
            if (start_lane >= num_lanes)
                return 3ull << (start_lane - num_lanes); /* Two lanes on second DLM */
            return 3ull << start_lane; /* Two lanes */
        }
        case CGX_MODE_XAUI:
        case CGX_MODE_DXAUI:
        case CGX_MODE_XLAUI:
        case CGX_MODE_40G_KR:
        case CGX_MODE_100G:
        case CGX_MODE_100G_KR4:
            return 0xf; /* Four lanes */
    }
    return 0;
}

const __bdk_if_ops_t __bdk_if_ops_cgx = {
    .priv_size = sizeof(cgx_priv_t),
    .if_num_interfaces = if_num_interfaces,
    .if_num_ports = if_num_ports,
    .if_probe = if_probe,
    .if_init = if_init,
    .if_enable = if_enable,
    .if_disable = if_disable,
    .if_link_get = if_link_get,
    .if_link_set = if_link_set,
    .if_transmit = bdk_nix_transmit,
    .if_loopback = if_loopback,
    .if_get_queue_depth = bdk_nix_get_queue_depth,
    .if_get_stats = if_get_stats,
    .if_get_lane_mask = if_get_lane_mask,
};

