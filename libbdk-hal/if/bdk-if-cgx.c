/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <malloc.h>
#include "libbdk-arch/bdk-csrs-cgx.h"
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-gsern.h"

/* This file implements interfaces connected to the CGX block introduced
    for CN96XX */

#define MAX_MTU 9212

typedef enum
{
    CGX_MODE_DISABLED,          /* Represents an unused LMAC */
    CGX_MODE_SGMII,             /* 1 lane per port, fixed 1.250 Gbaud */
    CGX_MODE_1G_SINGLE,         /* 1 lane per port, fixed 1.250 Gbaud, 1000BASE-X */
    CGX_MODE_QSGMII,            /* 4 ports on one lane, fixed 5 Gbaud */
    CGX_MODE_XAUI,              /* 4 lanes per port, 3.125 or 6.250 Gbaud */
    CGX_MODE_RXAUI,             /* 2 lanes per port, 6.250 Gbaud */
    CGX_MODE_10G_SINGLE,        /* 1 lane per port, max 10 Gbaud */
    CGX_MODE_10G_QUAD,          /* 4 lanes per port, max 10 Gbaud */
    CGX_MODE_12G_DUAL,          /* 2 lanes per port, max 12.8 Gbaud */
    CGX_MODE_12G_QUAD,          /* 4 lanes per port, max 12.8 Gbaud */
    CGX_MODE_20G_SINGLE,        /* 1 lane per port, max 20 Gbaud */
    CGX_MODE_20G_DUAL,          /* 2 lanes per port, max 20 Gbaud */
    CGX_MODE_20G_QUAD,          /* 4 lanes per port, max 20 Gbaud */
    CGX_MODE_25G_SINGLE,        /* 1 lane per port, max 25 Gbaud */
    CGX_MODE_25G_DUAL,          /* 2 lanes per port, max 25 Gbaud */
    CGX_MODE_25G_QUAD,          /* 4 lanes per port, max 25 Gbaud */
    CGX_MODE_USXGMII_1PORT_2G,  /* 1 port on one lane, max 2 Gbaud */
    CGX_MODE_USXGMII_1PORT_5G,  /* 1 port on one lane, max 5 Gbaud */
    CGX_MODE_USXGMII_1PORT_10G, /* 1 port on one lane, max 10 Gbaud */
    CGX_MODE_USXGMII_2PORT_5G,  /* 2 ports on one lane, max 5 Gbaud */
    CGX_MODE_USXGMII_2PORT_10G, /* 2 ports on one lane, max 10 Gbaud */
    CGX_MODE_USXGMII_2PORT_20G, /* 2 ports on one lane, max 20 Gbaud */
    CGX_MODE_USXGMII_4PORT_10G, /* 4 ports on one lane, max 10 Gbaud */
    CGX_MODE_USXGMII_4PORT_20G, /* 4 ports on one lane, max 20 Gbaud */
} cgx_mode_t;

typedef enum
{
    CGX_FLAGS_NONE = 0,         /* No flags set */
    CGX_FLAGS_AUTO_NEG = 1,     /* Port uses auto-neg */
    CGX_FLAGS_TRAINING = 2,     /* Port uses KR training, requires AUTO_NEG */
    CGX_FLAGS_FEC = 4,          /* Port uses BASE-R FEC, requires AUTO_NEG */
    CGX_FLAGS_RS_FEC = 8,       /* Port uses Reed-Solomon FEC, requires AUTO_NEG */
    CGX_FLAGS_NO_NIX = 16,      /* Port doesn't connect to NIX, BPHY only */
} cgx_flags_t;

typedef struct
{
    /* CGX related config */
    cgx_mode_t  mode;           /* CGX mode */
    cgx_flags_t flags;          /* Port feature flags */
    uint64_t    restart_auto_neg; /* Time we last restarted auto-neg. Used to make sure we give auto-neg enough time */
    int64_t     phy_address;    /* PHY address from bdk-config */
    int         first_qlm;      /* First DLM/QLM number connected to this port. Mat have multiple for DLMs */
    int         first_lane;     /* Lane number of first_qlm the port starts on */
    int         lane_mask;      /* Masks of lanes used on DLM/QLM. May span muliple DLM */
} cgx_priv_t;

/**
 * Return the number of CGX supported by this chip
 *
 * @param node   Node to query
 *
 * @return Number of CGX
 */
static int if_num_interfaces(bdk_node_t node)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 3;
    else if (bdk_is_model(OCTEONTX_CNF95XX))
        return 3;
    else if (bdk_is_model(OCTEONTX_LOKI))
        return 4;
    else if (bdk_is_model(OCTEONTX_CN98XX))
        return 5;
    else
        return 0;
}

/**
 * Return the number of ports to create for this CGX
 *
 * @param node      Node to query
 * @param interface CGX interface
 *
 * @return Number of ports
 */
static int if_num_ports(bdk_node_t node, int interface)
{
    /* We always create a port for each LMAC */
    BDK_CSR_INIT(cgxx_const, node, BDK_CGXX_CONST(interface));
    return cgxx_const.s.lmacs;
}

/**
 * Change name to be something that might be meaningful to the user
 *
 * @param handle Port to rename
 */
static void update_name(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;
    const char *name_format = "UNKNOWN";

    switch (priv->mode)
    {
        case CGX_MODE_DISABLED:
            if (bdk_numa_is_only_one())
                name_format = "DIS%d.%d";
            else
                name_format = "N%d.DIS%d.%d";
            break;
        case CGX_MODE_SGMII:
            if (bdk_numa_is_only_one())
                name_format = "SGMII%d.%d";
            else
                name_format = "N%d.SGMII%d.%d";
            break;
        case CGX_MODE_1G_SINGLE:
            if (bdk_numa_is_only_one())
                name_format = "1G%d.%d";
            else
                name_format = "N%d.1G%d.%d";
            break;
        case CGX_MODE_QSGMII:
            if (bdk_numa_is_only_one())
                name_format = "QSGMII%d.%d";
            else
                name_format = "N%d.QSGMII%d.%d";
            break;
        case CGX_MODE_XAUI:
        {
            int speed = bdk_qlm_get_gbaud_mhz(node, priv->first_qlm, priv->first_lane);
            if (speed == 6250)
            {
                if (bdk_numa_is_only_one())
                    name_format = "DXAUI%d";
                else
                    name_format = "N%d.DXAUI%d";
            }
            else
            {
                if (bdk_numa_is_only_one())
                    name_format = "XAUI%d";
                else
                    name_format = "N%d.XAUI%d";
            }
            break;
        }
        case CGX_MODE_RXAUI:
            if (bdk_numa_is_only_one())
                name_format = "RXAUI%d.%d";
            else
                name_format = "N%d.RXAUI%d.%d";
            break;
        case CGX_MODE_10G_SINGLE:
            if (bdk_numa_is_only_one())
                name_format = "10G%d.%d";
            else
                name_format = "N%d.10G%d.%d";
            break;
        case CGX_MODE_10G_QUAD:
            if (bdk_numa_is_only_one())
                name_format = "40G%d";
            else
                name_format = "N%d.40G%d";
            break;
        case CGX_MODE_12G_DUAL:
            if (bdk_numa_is_only_one())
                name_format = "25G%d.%d";
            else
                name_format = "N%d.25G%d.%d";
            break;
        case CGX_MODE_12G_QUAD:
            if (bdk_numa_is_only_one())
                name_format = "50G%d";
            else
                name_format = "N%d.50G%d";
            break;
        case CGX_MODE_20G_SINGLE:
            if (bdk_numa_is_only_one())
                name_format = "20G%d.%d";
            else
                name_format = "N%d.20G%d.%d";
            break;
        case CGX_MODE_20G_DUAL:
            if (bdk_numa_is_only_one())
                name_format = "40G%d.%d";
            else
                name_format = "N%d.40G%d.%d";
            break;
        case CGX_MODE_20G_QUAD:
            if (bdk_numa_is_only_one())
                name_format = "80G%d";
            else
                name_format = "N%d.80G%d";
            break;
        case CGX_MODE_25G_SINGLE:
            if (bdk_numa_is_only_one())
                name_format = "25G%d.%d";
            else
                name_format = "N%d.25G%d.%d";
            break;
        case CGX_MODE_25G_DUAL:
            if (bdk_numa_is_only_one())
                name_format = "50G%d.%d";
            else
                name_format = "N%d.50G%d.%d";
            break;
        case CGX_MODE_25G_QUAD:
            if (bdk_numa_is_only_one())
                name_format = "100G%d";
            else
                name_format = "N%d.100G%d";
            break;
        case CGX_MODE_USXGMII_1PORT_2G ... CGX_MODE_USXGMII_4PORT_20G:
            if (bdk_numa_is_only_one())
                name_format = "USX%d.%d";
            else
                name_format = "N%d.USX%d.%d";
            break;
    }
    if (bdk_numa_is_only_one())
        snprintf(handle->name, sizeof(handle->name), name_format, cgx, lmac);
    else
        snprintf(handle->name, sizeof(handle->name), name_format, node, cgx, lmac);
    handle->name[sizeof(handle->name)-1] = 0;
}

/**
 * FIll in the QLM, lane, and lane mask used by this port
 *
 * @param handle Port to fill
 */
static void cgx_fill_priv(bdk_if_handle_t handle)
{
    cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;

    BDK_CSR_INIT(cmrx, node, BDK_CGXX_CMRX_CONFIG(cgx, 0));

    /* Determine the QLM, number of lanes, and mode */
    int qlm = bdk_if_get_qlm(handle);
    int num_lanes = (qlm < 0) ? 4 : bdk_qlm_get_lanes(node, qlm);
    int qlm_lane = (cmrx.s.lane_to_sds >> (lmac * 2)) & 3;
    if (qlm_lane >= num_lanes)
        qlm_lane -= num_lanes;
    bdk_qlm_modes_t qlm_mode = (qlm < 0) ? BDK_QLM_MODE_DISABLED : bdk_qlm_get_mode(node, qlm, qlm_lane);
    priv->first_qlm = qlm;
    priv->first_lane = qlm_lane;

    priv->mode = CGX_MODE_DISABLED;
    priv->lane_mask = 0;
    priv->phy_address = bdk_config_get_int(BDK_CONFIG_PHY_ADDRESS, node, cgx, lmac);
    switch (qlm_mode)
    {
        case BDK_QLM_MODE_SGMII:
            priv->mode = CGX_MODE_SGMII;
            priv->flags = CGX_FLAGS_AUTO_NEG;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_1G_X:
            priv->mode = CGX_MODE_1G_SINGLE;
            //priv->flags = CGX_FLAGS_AUTO_NEG;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_QSGMII:
            priv->mode = CGX_MODE_QSGMII;
            priv->flags = CGX_FLAGS_AUTO_NEG;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_XAUI:
            if (lmac == 0)
            {
                priv->mode = CGX_MODE_XAUI;
                priv->lane_mask = 0xf; /* Four lanes */
            }
            break;
        case BDK_QLM_MODE_RXAUI:
            if ((lmac & 1) == 0)
            {
                priv->mode = CGX_MODE_RXAUI;
                if (priv->first_lane & 1) /* Happens when lanes are swizzled on EBB */
                    priv->lane_mask = 3ull << (priv->first_lane - 1); /* Two lanes */
                else
                    priv->lane_mask = 3ull << priv->first_lane; /* Two lanes */
            }
            break;
        case BDK_QLM_MODE_XFI:
        case BDK_QLM_MODE_SFI:
            priv->mode = CGX_MODE_10G_SINGLE;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_XLAUI:
        case BDK_QLM_MODE_XLAUI_C2M:
            if (lmac == 0)
            {
                priv->mode = CGX_MODE_10G_QUAD;
                priv->lane_mask = 0xf; /* Four lanes */
            }
            break;
        case BDK_QLM_MODE_10G_KR:
            priv->mode = CGX_MODE_10G_SINGLE;
            priv->flags = CGX_FLAGS_AUTO_NEG | CGX_FLAGS_TRAINING;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_40G_CR4:
            if (lmac == 0)
            {
                priv->mode = CGX_MODE_10G_QUAD;
                priv->lane_mask = 0xf; /* Four lanes */
            }
            break;
        case BDK_QLM_MODE_40G_KR4:
            if (lmac == 0)
            {
                priv->mode = CGX_MODE_10G_QUAD;
                priv->lane_mask = 0xf; /* Four lanes */
                priv->flags = CGX_FLAGS_AUTO_NEG | CGX_FLAGS_TRAINING;
            }
            break;
        case BDK_QLM_MODE_20GAUI_C2C:
            priv->mode = CGX_MODE_20G_SINGLE;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_25GAUI_C2C:
        case BDK_QLM_MODE_25GAUI_C2M:
        case BDK_QLM_MODE_25G_CR:
            priv->mode = CGX_MODE_25G_SINGLE;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_25G_KR:
            priv->mode = CGX_MODE_25G_SINGLE;
            priv->flags = CGX_FLAGS_AUTO_NEG | CGX_FLAGS_TRAINING;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_25GAUI_2_C2C:
            if ((lmac & 1) == 0)
            {
                priv->mode = CGX_MODE_12G_DUAL;
                if (priv->first_lane & 1) /* Happens when lanes are swizzled on EBB */
                    priv->lane_mask = 3ull << (priv->first_lane - 1); /* Two lanes */
                else
                    priv->lane_mask = 3ull << priv->first_lane; /* Two lanes */
            }
            break;
        case BDK_QLM_MODE_40GAUI_2_C2C:
            if ((lmac & 1) == 0)
            {
                priv->mode = CGX_MODE_20G_DUAL;
                if (priv->first_lane & 1) /* Happens when lanes are swizzled on EBB */
                    priv->lane_mask = 3ull << (priv->first_lane - 1); /* Two lanes */
                else
                    priv->lane_mask = 3ull << priv->first_lane; /* Two lanes */
            }
            break;
        case BDK_QLM_MODE_50GAUI_2_C2C:
        case BDK_QLM_MODE_50GAUI_2_C2M:
        case BDK_QLM_MODE_50G_CR2:
            if ((lmac & 1) == 0)
            {
                priv->mode = CGX_MODE_25G_DUAL;
                if (priv->first_lane & 1) /* Happens when lanes are swizzled on EBB */
                    priv->lane_mask = 3ull << (priv->first_lane - 1); /* Two lanes */
                else
                    priv->lane_mask = 3ull << priv->first_lane; /* Two lanes */
            }
            break;
        case BDK_QLM_MODE_50G_KR2:
            if ((lmac & 1) == 0)
            {
                priv->mode = CGX_MODE_25G_DUAL;
                priv->flags = CGX_FLAGS_AUTO_NEG | CGX_FLAGS_TRAINING;
                if (priv->first_lane & 1) /* Happens when lanes are swizzled on EBB */
                    priv->lane_mask = 3ull << (priv->first_lane - 1); /* Two lanes */
                else
                    priv->lane_mask = 3ull << priv->first_lane; /* Two lanes */
            }
            break;
        case BDK_QLM_MODE_50GAUI_4_C2C:
            if (lmac == 0)
            {
                priv->mode = CGX_MODE_12G_QUAD;
                priv->lane_mask = 0xf; /* Four lanes */
            }
            break;
        case BDK_QLM_MODE_80GAUI_4_C2C:
            if (lmac == 0)
            {
                priv->mode = CGX_MODE_20G_QUAD;
                priv->lane_mask = 0xf; /* Four lanes */
            }
            break;
        case BDK_QLM_MODE_CAUI_4_C2C:
        case BDK_QLM_MODE_CAUI_4_C2M:
        case BDK_QLM_MODE_100G_CR4:
            if (lmac == 0)
            {
                priv->mode = CGX_MODE_25G_QUAD;
                priv->lane_mask = 0xf; /* Four lanes */
            }
            break;
        case BDK_QLM_MODE_100G_KR4:
            if (lmac == 0)
            {
                priv->mode = CGX_MODE_25G_QUAD;
                priv->lane_mask = 0xf; /* Four lanes */
                priv->flags = CGX_FLAGS_AUTO_NEG | CGX_FLAGS_TRAINING;
            }
            break;
        case BDK_QLM_MODE_USXGMII_4X1:
            priv->mode = CGX_MODE_USXGMII_4PORT_20G;
            priv->flags = CGX_FLAGS_AUTO_NEG;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_USXGMII_2X1:
            if (lmac < 2)
                priv->mode = CGX_MODE_USXGMII_2PORT_20G;
            priv->flags = CGX_FLAGS_AUTO_NEG;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        case BDK_QLM_MODE_USXGMII_1X1:
            if (lmac == 0)
                priv->mode = CGX_MODE_USXGMII_1PORT_10G;
            priv->flags = CGX_FLAGS_AUTO_NEG;
            priv->lane_mask = 1ull << priv->first_lane; /* One lane */
            break;
        default:
            break;
    }
    update_name(handle);
    if (priv->mode == CGX_MODE_DISABLED)
    {
        BDK_TRACE(BGX, "%s: Disabled\n", handle->name);
    }
    else
    {
        BDK_TRACE(BGX, "%s: Uses QLM%d, mode %s, lane %d, lane mask 0x%x (lane_to_sds = 0x%x)\n",
            handle->name, qlm, bdk_qlm_mode_tostring(qlm_mode), priv->first_lane,
            priv->lane_mask, cmrx.s.lane_to_sds);
    }
}

/**
 * Get the FEC settings for this port from the device tree
 *
 * @param handle
 */
static void get_fec_settings(bdk_if_handle_t handle)
{
    cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;
    int flags = bdk_config_get_int(BDK_CONFIG_NETWORK_FLAGS, node, cgx, lmac);
    switch (priv->mode)
    {
        case CGX_MODE_DISABLED:
        case CGX_MODE_SGMII:
        case CGX_MODE_1G_SINGLE:
        case CGX_MODE_QSGMII:
        case CGX_MODE_XAUI:
        case CGX_MODE_RXAUI:
        case CGX_MODE_12G_DUAL:
        case CGX_MODE_12G_QUAD:
            /* No FEC support */
            break;
        case CGX_MODE_10G_SINGLE:
        case CGX_MODE_10G_QUAD:
            /* FEC support */
            if (flags & 1)
                priv->flags |= CGX_FLAGS_FEC;
            break;
        case CGX_MODE_20G_SINGLE:
        case CGX_MODE_20G_DUAL:
        case CGX_MODE_20G_QUAD:
        case CGX_MODE_25G_SINGLE:
        case CGX_MODE_25G_DUAL:
        case CGX_MODE_25G_QUAD:
            /* RS-FEC support */
            if (flags & 2)
                priv->flags |= CGX_FLAGS_RS_FEC;
            break;
        case CGX_MODE_USXGMII_1PORT_2G:
        case CGX_MODE_USXGMII_1PORT_5G:
        case CGX_MODE_USXGMII_1PORT_10G:
        case CGX_MODE_USXGMII_2PORT_5G:
        case CGX_MODE_USXGMII_2PORT_10G:
        case CGX_MODE_USXGMII_2PORT_20G:
        case CGX_MODE_USXGMII_4PORT_10G:
        case CGX_MODE_USXGMII_4PORT_20G:
            /* Either FEC or RS-FEC */
            if (flags & 2)
                priv->flags |= CGX_FLAGS_RS_FEC;
            else if (flags & 1)
                priv->flags |= CGX_FLAGS_FEC;
            break;
    }
}

/**
 * Probe a port. Called before hardware is configured to setup names and such
 *
 * @param handle Port to probe
 *
 * @return Zero on success, negative on failure
 */
static int if_probe(bdk_if_handle_t handle)
{
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;

    int nix_index = 0;
    /* Stripe CGX across both NIX on CN98XX */
    if (bdk_is_model(OCTEONTX_CN98XX))
        nix_index = cgx & 1;

    /* Set LANE_TO_SDS based on the device tree settings */
    if (lmac == 0)
    {
        int lane_order = bdk_config_get_int(BDK_CONFIG_NETWORK_LANE_ORDER, node, cgx);
        int lane_to_sds = 0;
        lane_to_sds |= ((lane_order >> 0) & 3) << 0;
        lane_to_sds |= ((lane_order >> 4) & 3) << 2;
        lane_to_sds |= ((lane_order >> 8) & 3) << 4;
        lane_to_sds |= ((lane_order >> 12) & 3) << 6;
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, 0),
            c.s.p2x_select = nix_index + 1;
            c.s.x2p_select = nix_index + 1;
            c.s.lane_to_sds = lane_to_sds);
        BDK_CSR_MODIFY(c, node, BDK_CGXX_SPU_USXGMII_CONTROL(cgx),
            c.s.sds_id = lane_to_sds & 3);
    }
    else
    {
        BDK_CSR_INIT(cmrx, node, BDK_CGXX_CMRX_CONFIG(cgx, 0));
        int mask = (lmac & 1) ? 0x3 : 0xf; /* Even LMACs may cover two lanes in some modes */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
            c.s.p2x_select = nix_index + 1;
            c.s.x2p_select = nix_index + 1;
            c.s.lane_to_sds = (cmrx.s.lane_to_sds >> (lmac * 2)) & mask);
    }

    /* Change name to be something that might be meaningful to the user */
    if (bdk_numa_is_only_one())
        snprintf(handle->name, sizeof(handle->name), "CGX%d.%d", cgx, lmac);
    else
        snprintf(handle->name, sizeof(handle->name), "N%d.CGX%d.%d", node, cgx, lmac);
    handle->name[sizeof(handle->name)-1] = 0;

    handle->flags |= BDK_IF_FLAGS_HAS_FCS;

    /* Fill in the CGX private data */
    cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    memset(priv, 0, sizeof(*priv));
    cgx_fill_priv(handle);

    /* Don't show ports disabled in device tree */
    int enable = bdk_config_get_int(BDK_CONFIG_BGX_ENABLE, node, cgx, lmac);
    if (!enable)
    {
        BDK_TRACE(BGX, "%s: Disabled by device tree\n", handle->name);
        handle->flags |= BDK_IF_FLAGS_HIDDEN;
    }

    get_fec_settings(handle);
    if (priv->mode == CGX_MODE_DISABLED)
        handle->flags |= BDK_IF_FLAGS_HIDDEN;
    else
        handle->netphy = bdk_netphy_get_handle(handle->node, priv->first_qlm, priv->first_lane).u;

    /* CNF95XX and LOKI CGX1+ connect to BPHY, not NIX */
    if ((cgx > 0) && (bdk_is_model(OCTEONTX_CNF95XX) || bdk_is_model(OCTEONTX_LOKI)))
        priv->flags |= CGX_FLAGS_NO_NIX;

    return 0;
}

/**
 * Reset single CGX port. This will affect multiple LMACs for wide protocols or
 * protocols that multiplex multiple ports over a single wire (QSGMII, USXGMII).
 * This implements the first few steps of Link Bring-up in the HRM, specifically
 * the steps related to reset of hardware before use.
 *
 * @param handle Port to reset. If the port is a dual or quad, all LMACs it covers are reset
 */
static void cgx_reset(bdk_if_handle_t handle)
{
    const int TIMEOUT_RESET = 100; /* 100us - Timeout for resetting various blocks */
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;

    if (priv->mode != CGX_MODE_DISABLED)
        BDK_TRACE(BGX, "%s: Performing CGX reset\n", handle->name);

    /* Figure out how many LMACs we need to reset */
    int first_lmac = handle->index;
    int last_lmac = handle->index;
    switch (priv->mode)
    {
        case CGX_MODE_DISABLED:
        case CGX_MODE_SGMII:
        case CGX_MODE_QSGMII:
        case CGX_MODE_1G_SINGLE:
        case CGX_MODE_10G_SINGLE:
        case CGX_MODE_20G_SINGLE:
        case CGX_MODE_25G_SINGLE:
        case CGX_MODE_USXGMII_1PORT_2G:
        case CGX_MODE_USXGMII_1PORT_5G:
        case CGX_MODE_USXGMII_1PORT_10G:
            /* Only touch one LMAC  */
            break;
        case CGX_MODE_RXAUI:
        case CGX_MODE_12G_DUAL:
        case CGX_MODE_20G_DUAL:
        case CGX_MODE_25G_DUAL:
        case CGX_MODE_USXGMII_2PORT_5G:
        case CGX_MODE_USXGMII_2PORT_10G:
        case CGX_MODE_USXGMII_2PORT_20G:
            if ((first_lmac&1) != 0)
                return;
            /* Touch two LMACs */
            last_lmac++;
            break;
        case CGX_MODE_XAUI:
        case CGX_MODE_10G_QUAD:
        case CGX_MODE_12G_QUAD:
        case CGX_MODE_20G_QUAD:
        case CGX_MODE_25G_QUAD:
        case CGX_MODE_USXGMII_4PORT_10G:
        case CGX_MODE_USXGMII_4PORT_20G:
            if (first_lmac != 0)
                return;
            /* Touch four LMACs */
            last_lmac += 3;
            break;
    }

    /* Loop through each LMAC  */
    for (int lmac = first_lmac; lmac <= last_lmac; lmac++)
    {
        /* Section 57.6.3 Link Bring-Up, version 0.85998e */

        /* SPU */

        /* 1) Write CGX(0..2)_CMR(0..3)_CONFIG[ENABLE] = 0. For USXGMII,
            also write CGX(0..2)_SPU_USXGMII_CONTROL[ENABLE] = 0 */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
            c.s.enable = 0);
        if (lmac == first_lmac)
        {
            BDK_CSR_MODIFY(c, node, BDK_CGXX_SPU_USXGMII_CONTROL(cgx),
                c.s.enable = 0);
        }

        /* GMX */

        BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac),
            c.s.pwr_dn = 1);
        BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx, lmac),
            c.s.gmxeno = 1);
        /* Disparity check enable. When LMAC_TYPE=QSGMII the running
           disparity check should be disabled to prevent propagation
           across ports. */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx, lmac),
            c.s.disp_en = (priv->mode != CGX_MODE_QSGMII));

        /* 2) Take SPU through a reset sequence. If autonegotiation
            is desired, reset SPU by writing
            CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_RESET] = 1 (or
            CGX(0..2)_SPU(0..3)_USX_AN_CONTROL[AN_RESET] = 1 for USXGMII).
            Read CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_RESET] (or
            CGX(0..2)_SPU(0..3)_USX_AN_CONTROL[AN_RESET]) until it changes
            value to 0. If autonegotiation will not be enabled, write
            CGX(0..2)_SPU(0..3)_CONTROL1[RESET] = 1. Read
            CGX(0..2)_SPU(0..3)_CONTROL1[RESET] until it changes value to 0.
            For USXGMII, perform this step for all LMACs */
        if (priv->flags & CGX_FLAGS_AUTO_NEG)
        {
            /* SPU */

            BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_AN_CONTROL(cgx, lmac),
                c.s.an_reset = 1);
            BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_USX_AN_CONTROL(cgx, lmac),
                c.s.an_reset = 1);
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SPUX_AN_CONTROL(cgx, lmac), an_reset, ==, 0, TIMEOUT_RESET))
                bdk_error("%s: Timeout waiting for CGXX_SPUX_AN_CONTROL[AN_RESET] to complete\n", handle->name);
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SPUX_USX_AN_CONTROL(cgx, lmac), an_reset, ==, 0, TIMEOUT_RESET))
                bdk_error("%s: Timeout waiting for CGXX_SPUX_USX_AN_CONTROL[AN_RESET] to complete\n", handle->name);

            /* GMX */
            BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac),
                c.s.rst_an = 1);
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac), rst_an, ==, 0, TIMEOUT_RESET))
                bdk_error("%s: Timeout waiting for CGXX_GMP_PCS_MRX_CONTROL[RST_AN] to complete\n", handle->name);
        }
        else
        {
            /* SPU */

            BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_CONTROL1(cgx, lmac),
                c.s.reset = 1);
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SPUX_CONTROL1(cgx, lmac), reset, ==, 0, TIMEOUT_RESET))
                bdk_error("%s: Timeout waiting for CGXX_SPUX_CONTROL1[RESET] to complete\n", handle->name);

            /* GMX */

            BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac),
                c.s.reset = 1);
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac), reset, ==, 0, TIMEOUT_RESET))
                bdk_error("%s: Timeout waiting for CGXX_GMP_PCS_MRX_CONTROL[RESET] to complete\n", handle->name);
        }

        /* 3) At this point, it may be appropriate to disable some CGX
            and SMU/SPU interrupts, as a number of them will occur during
            bringup of the link.
                Zero CGX(0..2)_SMU(0..3)_RX_INT.
                Zero CGX(0..2)_SMU(0..3)_TX_INT.
                Zero CGX(0..2)_SPU(0..3)_INT. */
        /* SPU / SMU  */
        BDK_CSR_WRITE(node, BDK_CGXX_SMUX_RX_INT(cgx, lmac), -1);
        BDK_CSR_WRITE(node, BDK_CGXX_SMUX_TX_INT(cgx, lmac), -1);
        BDK_CSR_WRITE(node, BDK_CGXX_SPUX_INT(cgx, lmac), -1);
        /* GMX / GMP */
        BDK_CSR_WRITE(node, BDK_CGXX_GMP_GMI_RXX_INT(cgx, lmac), -1);
        BDK_CSR_WRITE(node, BDK_CGXX_GMP_GMI_TXX_INT(cgx, lmac), -1);
        BDK_CSR_WRITE(node, BDK_CGXX_GMP_PCS_INTX(cgx, lmac), -1);
    }

    /* 4) Configure the CGX RX and TX buffers by writing
       CGX(0..2)_CMR_RX_LMACS[LMACS] and CGX(0..2)_CMR_TX_LMACS[LMACS].
       This driver always configures 4 LMACs because cabling may change
       while we are running */
    if (lmac == 0)
    {
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_RX_LMACS(cgx),
            c.s.lmacs = 4);
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_TX_LMACS(cgx),
            c.s.lmacs = 4);
    }

    /* Disable EEE on all parts, feature dropped */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_RX_LPI_TIMING(cgx, lmac),
        c.s.rx_lpi_en = 0;
        c.s.rx_lpi_fw = 0);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_TX_LPI_TIMING(cgx, lmac),
        c.s.tx_lpi_en = 0;
        c.s.tx_lpi_fw = 0);
}

static void cgx_restart_autoneg(bdk_if_handle_t handle)
{
    cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;
    bool is_gmx = ((priv->mode >= CGX_MODE_SGMII) && (priv->mode <= CGX_MODE_QSGMII));
    bool is_usxgmii = (priv->mode >= CGX_MODE_USXGMII_1PORT_2G) && (priv->mode <= CGX_MODE_USXGMII_4PORT_20G);
    bool use_an = (priv->flags & CGX_FLAGS_AUTO_NEG) != 0;
    uint64_t time_cnt = bdk_clock_get_count(BDK_CLOCK_TIME);
    uint64_t time_rate = bdk_clock_get_rate(node, BDK_CLOCK_TIME);

    /* Disable packets */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
        c.s.data_pkt_rx_en = 0;
        c.s.data_pkt_tx_en = 0);

    /* Don't restart AN too quickly, every 5 sec */
    if (priv->restart_auto_neg + time_rate * 5 > time_cnt)
        return;

    priv->restart_auto_neg = time_cnt;
    if (priv->mode != CGX_MODE_DISABLED)
        BDK_TRACE(BGX, "%s: Resetting AN state machine\n", handle->name);

    /* Enable AN if needed */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_USX_AN_CONTROL(cgx, lmac),
        c.s.an_en = is_usxgmii && use_an);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_AN_CONTROL(cgx, lmac),
        c.s.an_en = !is_usxgmii && !is_gmx && use_an);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac),
        c.s.an_en = is_gmx && use_an);

    /* Program AN pages */
    bool use_extend_an = (priv->mode == CGX_MODE_25G_DUAL);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_AN_CONTROL(cgx, lmac),
        c.s.usx_an_arb_link_chk_en = 1;
        c.s.an_arb_link_chk_en = !use_extend_an;
        c.s.xnp_en = 1);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_AN_ADV(cgx, lmac),
        c.s.np = use_extend_an);

    int usx_spd = 2; /* 1G */
    switch (priv->mode)
    {
        case CGX_MODE_USXGMII_1PORT_2G:
            usx_spd = 4; /* 2.5G */
            break;
        case CGX_MODE_USXGMII_1PORT_5G:
            usx_spd = 5; /* 5G */
            break;
        case CGX_MODE_USXGMII_1PORT_10G:
            usx_spd = 3; /* 10G */
            break;
        case CGX_MODE_USXGMII_2PORT_5G:
            usx_spd = 4; /* 2.5G */
            break;
        case CGX_MODE_USXGMII_2PORT_10G:
            usx_spd = 5; /* 5G */
            break;
        case CGX_MODE_USXGMII_2PORT_20G:
            usx_spd = 3; /* 10G */
            break;
        case CGX_MODE_USXGMII_4PORT_10G:
            usx_spd = 4; /* 2.5G */
            break;
        case CGX_MODE_USXGMII_4PORT_20G:
        default:
            usx_spd = 5; /* 5G */
            break;
    }
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_USX_AN_ADV(cgx, lmac),
        c.s.lnk_st = 1;
        c.s.spd = usx_spd);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_AN_ADV(cgx, lmac),
        c.s.fec_req = !!(priv->flags & CGX_FLAGS_FEC);
        c.s.fec_able = !!(priv->flags & CGX_FLAGS_FEC);
        c.s.a25g_kr_cr = (priv->mode == CGX_MODE_25G_SINGLE);
        c.s.a25g_krs_crs = (priv->mode == CGX_MODE_25G_SINGLE);
        c.s.a100g_cr4 = (priv->mode == CGX_MODE_25G_QUAD);
        c.s.a100g_kr4 = (priv->mode == CGX_MODE_25G_QUAD);
        c.s.a40g_cr4 = ((priv->mode == CGX_MODE_10G_QUAD) || (priv->mode == CGX_MODE_25G_QUAD));
        c.s.a40g_kr4 = ((priv->mode == CGX_MODE_10G_QUAD) || (priv->mode == CGX_MODE_25G_QUAD));
        c.s.a10g_kr = ((priv->mode == CGX_MODE_10G_SINGLE) || (priv->mode == CGX_MODE_25G_SINGLE));
        c.s.a10g_kx4 = 0);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPU_DBG_CONTROL(cgx),
        c.s.an_nonce_match_dis=1); /* Needed for loopback */

    /* Restart AN */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_AN_CONTROL(cgx, lmac),
        c.s.an_restart = !is_usxgmii && !is_gmx && use_an);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_USX_AN_CONTROL(cgx, lmac),
        c.s.rst_an = is_usxgmii && use_an);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac),
        c.s.rst_an = is_gmx && use_an);
}

/**
 * Tweak GSERN setting before starting KR training. These setting are actually
 * in effect for all of AN and through training.
 *
 * @param handle
 */
static void cgx_gsern_adjust_before_training(bdk_if_handle_t handle)
{
    /* This only applies to CN96XX pass 1.x */
    if (!bdk_is_model(OCTEONTX_CN96XX_PASS1_X))
        return;

    cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    int qlm = priv->first_qlm;
    uint64_t lane_mask = priv->lane_mask;
    /* The lane mask may span multiple QLM/DLM. We require the QLM/DLM
       to be sequential */
    while (lane_mask)
    {
        /* Get the number of lanes on this QLM/DLM */
        int num_lanes = bdk_qlm_get_lanes(node, qlm);
        for (int lane = 0; lane < num_lanes; lane++)
        {
            if (lane_mask & (1<<lane))
            {
                BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_15_BCFG(qlm, lane),
                    c.s.c1_limit_lo = 0x21);
                BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, lane),
                    c.s.do_prevga_gn_final = 1;
                    c.s.do_ctle_final = 1);
                BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TRAIN_6_BCFG(qlm, lane),
                    c.s.cost_cache_en = 1;
                    c.s.en_rxwt_ctr = 1);
            }
        }

        /* Move the the next QLM/DLM */
        lane_mask >>= num_lanes;
        qlm++;
    }
}

/**
 * Tweak GSERN setting after finishing KR training. These setting are actually
 * in effect at some time after training, possible starting after link up.
 *
 * @param handle
 */
static void cgx_gsern_adjust_after_training(bdk_if_handle_t handle)
{
    /* This only applies to CN96XX pass 1.x */
    if (!bdk_is_model(OCTEONTX_CN96XX_PASS1_X))
        return;

    cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    int qlm = priv->first_qlm;
    uint64_t lane_mask = priv->lane_mask;
    /* The lane mask may span multiple QLM/DLM. We require the QLM/DLM
       to be sequential */
    while (lane_mask)
    {
        /* Get the number of lanes on this QLM/DLM */
        int num_lanes = bdk_qlm_get_lanes(node, qlm);
        for (int lane = 0; lane < num_lanes; lane++)
        {
            if (lane_mask & (1<<lane))
            {
                BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, lane),
                    c.s.do_prevga_gn_final = 0;
                    c.s.do_ctle_final = 0);
            }
        }

        /* Move the the next QLM/DLM */
        lane_mask >>= num_lanes;
        qlm++;
    }
}

/**
 * Called per LMAC before we try and bringup the link. CGX reset and global
 * init will be complete before this is called. This implements the middle
 * steps of Link Bring-up in the HRM, specifically the steps related to
 * "(5) Configure the CGX LMAC".
 *
 * @param handle Port to configure
 *
 * @return Return zero on success, negative if another call is needed
 */
static int cgx_init_pre_link(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;
    int lmac_type = BDK_CGX_LMAC_TYPES_E_TWENTYFIVEG_R;
    int usxgmii_type = BDK_CGX_USXGMII_TYPE_E_QXGMII_20G;
    if (priv->mode != CGX_MODE_DISABLED)
        BDK_TRACE(BGX, "%s: Performing CGX pre-link init\n", handle->name);

    switch (priv->mode)
    {
        case CGX_MODE_DISABLED:
            lmac_type = BDK_CGX_LMAC_TYPES_E_SGMII;
            break;
        case CGX_MODE_SGMII:
        case CGX_MODE_1G_SINGLE:
            lmac_type = BDK_CGX_LMAC_TYPES_E_SGMII;
            break;
        case CGX_MODE_QSGMII:
            lmac_type = BDK_CGX_LMAC_TYPES_E_QSGMII;
            break;
        case CGX_MODE_XAUI:
            lmac_type = BDK_CGX_LMAC_TYPES_E_XAUI;
            break;
        case CGX_MODE_RXAUI:
            lmac_type = BDK_CGX_LMAC_TYPES_E_RXAUI;
            break;
        case CGX_MODE_10G_SINGLE:
            lmac_type = BDK_CGX_LMAC_TYPES_E_TENG_R;
            break;
        case CGX_MODE_10G_QUAD:
        case CGX_MODE_12G_QUAD:
            lmac_type = BDK_CGX_LMAC_TYPES_E_FORTYG_R;
            break;
        case CGX_MODE_20G_SINGLE:
        case CGX_MODE_25G_SINGLE:
            lmac_type = BDK_CGX_LMAC_TYPES_E_TWENTYFIVEG_R;
            break;
        case CGX_MODE_12G_DUAL:
        case CGX_MODE_20G_DUAL:
        case CGX_MODE_25G_DUAL:
            lmac_type = BDK_CGX_LMAC_TYPES_E_FIFTYG_R;
            break;
        case CGX_MODE_20G_QUAD:
        case CGX_MODE_25G_QUAD:
            lmac_type = BDK_CGX_LMAC_TYPES_E_HUNDREDG_R;
            break;
        case CGX_MODE_USXGMII_1PORT_2G:
            lmac_type = BDK_CGX_LMAC_TYPES_E_USXGMII;
            usxgmii_type = BDK_CGX_USXGMII_TYPE_E_SXGMII_2G;
            break;
        case CGX_MODE_USXGMII_1PORT_5G:
            lmac_type = BDK_CGX_LMAC_TYPES_E_USXGMII;
            usxgmii_type = BDK_CGX_USXGMII_TYPE_E_SXGMII_5G;
            break;
        case CGX_MODE_USXGMII_1PORT_10G:
            lmac_type = BDK_CGX_LMAC_TYPES_E_USXGMII;
            usxgmii_type = BDK_CGX_USXGMII_TYPE_E_SXGMII_10G;
            break;
        case CGX_MODE_USXGMII_2PORT_5G:
            lmac_type = BDK_CGX_LMAC_TYPES_E_USXGMII;
            usxgmii_type = BDK_CGX_USXGMII_TYPE_E_DXGMII_5G;
            break;
        case CGX_MODE_USXGMII_2PORT_10G:
            lmac_type = BDK_CGX_LMAC_TYPES_E_USXGMII;
            usxgmii_type = BDK_CGX_USXGMII_TYPE_E_DXGMII_10G;
            break;
        case CGX_MODE_USXGMII_2PORT_20G:
            lmac_type = BDK_CGX_LMAC_TYPES_E_USXGMII;
            usxgmii_type = BDK_CGX_USXGMII_TYPE_E_DXGMII_20G;
            break;
        case CGX_MODE_USXGMII_4PORT_10G:
            lmac_type = BDK_CGX_LMAC_TYPES_E_USXGMII;
            usxgmii_type = BDK_CGX_USXGMII_TYPE_E_QXGMII_10G;
            break;
        case CGX_MODE_USXGMII_4PORT_20G:
            lmac_type = BDK_CGX_LMAC_TYPES_E_USXGMII;
            usxgmii_type = BDK_CGX_USXGMII_TYPE_E_QXGMII_20G;
            break;
    }

    /* Section 57.6.3 Link Bring-Up, version 0.85998e */

    /* 5) Configure the CGX LMAC */
    /* 5.1) Configure the LMAC type (USXGMII/100GBASE-R4/50GBASE-R2/
        40GBASE-R4/25GBASE-R/10GBASE-R/RXAUI/XAUI) and SerDes selection
        in the CGX(0..2)_CMR(0..3)_CONFIG register, but keep the
        [ENABLE], [DATA_PKT_TX_EN] and [DATA_PKT_RX_EN] bits clear.

        For USXGMII, program the physical SerDes lane rate type in
        CGX(0..2)_SPU_USXGMII_CONTROL[USXGMII_TYPE] (i.e. QXGMII_20G),
        and program each LMAC’s port rate in
        CGX(0..2)_SPU(0..3)_CONTROL1[USXGMII_RATE] (i.e. RATE_1G). Note
        that USXGMII_TYPE is not negotiated with the link partner during
        autonegotiation.  However, USXGMII_RATE is negotiated and CGX
        will automatically adjust its USXGMII rate based on the link
        partner’s supported rate */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
        c.s.data_pkt_rx_en = 0;
        c.s.data_pkt_tx_en = 0;
        c.s.lmac_type = lmac_type);
    if (lmac == 0)
    {
        BDK_CSR_MODIFY(c, node, BDK_CGXX_SPU_USXGMII_CONTROL(cgx),
            c.s.usxgmii_type = usxgmii_type);
    }

    /* 5.2) Initialize the selected SerDes lane(s) in the QLM/DLM (see
        Chapter 53). If autonegotiation is enabled, it is recommended to
        check that the receiver is out of electrical idle (link partner
        is out of reset) before proceeding to step (6). This check helps
        to synchronize the autonegotiation process. However, it is
        important to note that some link partners disable their
        transmitters if they detect electrical idle on their receivers.
        Set the polarity and lane swapping of the QLM/DLM SerDes. Refer
        to Section 57.4.1,
        CGX(0..2)_SPU(0..3)_MISC_CONTROL[XOR_TXPLRT,XOR_RXPLRT] and
        CGX(0..2)_SPU(0..3)_MISC_CONTROL[TXPLRT,RXPLRT]. For USXGMII,
        note that the single physical SerDes lane used for USXGMII is
        programmable using CGX(0..2)_SPU_USXGMII_CONTROL[SDS_ID]. In
        this mode, the lane assignments in
        CGX(0..2)_CMR(0..3)_CONFIG[LANE_TO_SDS] are ignored */

    /* 5.3) If connected to a physical medium that supports link
        training, optionally enable it by writing
        CGX(0..2)_SPU(0..3)_BR_PMD_CONTROL[TRAIN_EN] = 1 and
        CGX(0..2)_SPU(0..3)_BR_PMD_CONTROL[TRAIN_RESTART] = 1 */
    bool use_training = (priv->flags & CGX_FLAGS_TRAINING) != 0;
    if (use_training)
        cgx_gsern_adjust_before_training(handle);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_BR_PMD_CONTROL(cgx, lmac),
        c.s.train_en = use_training;
        c.s.train_restart = use_training);

    /* 5.4) Program all other relevant CGX configuration while
        CGX(0..2)_CMR(0..3)_CONFIG[ENABLE] = 0. This includes everything
        described in this chapter. Note that programmed values of
        certain thresholds are dependent on the RX and TX buffer
        configurations determined in step (4). These include the
        registers listed below:
            CGX(0..2)_CMR(0..3)_RX_BP_ON[MARK]
            CGX(0..2)_SMU(0..3)_TX_THRESH[ECNT] */

    /* SPU */

    /* Calculate the number of s-clk cycles per usec. */
    uint64_t usec_cycles = bdk_clock_get_rate(node, BDK_CLOCK_SCLK) / 1000000;
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPU_DBG_CONTROL(cgx),
        c.s.us_clk_period = usec_cycles-1);

    /* For RXAUI, We're using a Marvel PHY on the plugin modules. The code
       below programs CGX to use "Interleaved running disparity", which
       is required for these PHYs. This will need to be changed if PHYs are
       used that expect "Common running disparity". */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_MISC_CONTROL(cgx, lmac),
        c.s.intlv_rdisp = 1);
    if (priv->mode == CGX_MODE_RXAUI)
    {
        /* RXAUI with Marvell PHY requires some tweaking */
        if (priv->phy_address != -1)
            __bdk_if_phy_xs_init(node, priv->phy_address);
    }

    /* Configure to allow max sized frames.The +4 is for FCS, and +8 if for
       preamble. Jabber must be a multiple of 16 */
    int jabber = MAX_MTU + 4 + 8;
    jabber = ((jabber + 15) >> 4) << 4;
    BDK_CSR_WRITE(node, BDK_CGXX_SMUX_RX_JABBER(cgx, lmac), jabber);

    /* GMX */
    int samp_pt = (priv->phy_address == BDK_IF_PHY_FIXED_100MB) ? 5 : 1;
    int spd = (priv->phy_address == BDK_IF_PHY_FIXED_100MB) ? 0x1 : 0x2;
    BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx, lmac),
        c.s.mac_phy = (handle->netphy == 0); /* PHY mode if a PHY is not connected, otherwise MAC mode */
        c.s.mode = (priv->mode == CGX_MODE_1G_SINGLE);
        c.s.samp_pt = samp_pt);
    const uint64_t clock_mhz = bdk_clock_get_rate(node, BDK_CLOCK_SCLK) / 1000000;
    BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_LINKX_TIMER(cgx, lmac),
        if (priv->mode == CGX_MODE_1G_SINGLE)
        {
            /* 1000BASE-X specifies a 10ms interval */
            c.s.count = (10000ull * clock_mhz) >> 10;
        }
        else
        {
            /* SGMII specifies a 1.6ms interval */
            c.s.count = (1600ull * clock_mhz) >> 10;
        });
    BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac),
        c.s.dup = 1;
        c.s.spdmsb = spd >> 1;
        c.s.spdlsb = spd & 1);

    /* Configure to allow max sized frames */
    BDK_CSR_WRITE(node, BDK_CGXX_GMP_GMI_RXX_JABBER(cgx, lmac), MAX_MTU + 4);

    /* Disable frame alignment if using preamble. This allows the link to
        reach full rate for odd length packets. For example, without this
        SGMII is slower than RGMII for 65 byte packets */
    BDK_CSR_INIT(txx_append, node, BDK_CGXX_GMP_GMI_TXX_APPEND(cgx, lmac));
    BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_GMI_TXX_SGMII_CTL(cgx, lmac),
        c.s.align = !txx_append.s.preamble);

    /* Common */

    /* Strip FCS */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_GLOBAL_CONFIG(cgx),
        c.s.fcs_strip = 1);

    /* Set the PKND */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_RX_ID_MAP(cgx, lmac),
        c.s.pknd = handle->pknd);

    /* Set the backpressure AND mask. Each interface gets 16 channels in this
       mask. When there is only 1 port, all 64 channels are available but
       the upper channels are used for anything. That's why this code only uses
       16 channels per interface */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_CHAN_MSK_AND(cgx),
        c.s.msk_and |= ((1ull <<1/*num_channels*/) - 1ull) << (lmac * 16));

    /* Disable all MAC filtering */
    for (int i = 0; i < 32; i++)
    {
        BDK_CSR_WRITE(node, BDK_CGXX_CMR_RX_DMACX_CAM0(cgx, i), 0);
        BDK_CSR_WRITE(node, BDK_CGXX_CMR_RX_DMACX_CAM1(cgx, i), 0);
    }
    /* Disable MAC steering */
    for (int i = 0; i < 8; i++)
    {
        BDK_CSR_WRITE(node, BDK_CGXX_CMR_RX_STEERING0X(cgx, i), 0);
        BDK_CSR_WRITE(node, BDK_CGXX_CMR_RX_STEERING1X(cgx, i), 0);
    }

    /* 5.5) If forward error correction is desired for 10GBASE-R,
        25GBASE-R, 40GBASE-R4, 50GBASE-R2, 100GBASE-R4 or USXGMII,
        enable it by writing the correct value to
        CGX(0..2)_SPU(0..3)_FEC_CONTROL[FEC_EN]. BASE-R FEC is supported
        for 10GBASE-R, 25GBASE-R, 40GBASE-R4, and 50GBASE- R2.
        Reed-Solomon FEC (RS-FEC) is supported for 25GBASE-R,
        50GBASE-R2, 100GBASE-R4, and USXGMII.
        Note that for USXGMII, the FEC type is not a negotiated
        capability in autonegotiation */
    int fec_setting;
    if (priv->flags & CGX_FLAGS_FEC)
        fec_setting = 1;
    else if (priv->flags & CGX_FLAGS_RS_FEC)
        fec_setting = 2;
    else
        fec_setting = 0;
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_FEC_CONTROL(cgx, lmac),
        c.s.fec_en = fec_setting);
    int ram_mrk_cnt = ((priv->mode == CGX_MODE_25G_QUAD) || (priv->mode == CGX_MODE_20G_QUAD)) ? 7 : 15;
    int by_mrk_100g = 1; /* default value after CGX comes out of reset */
    int mrk_cnt = 0x3fff;
    switch (priv->mode)
    {
        case CGX_MODE_DISABLED:
        case CGX_MODE_SGMII:
        case CGX_MODE_1G_SINGLE:
        case CGX_MODE_QSGMII:
        case CGX_MODE_XAUI:
        case CGX_MODE_RXAUI:
        case CGX_MODE_10G_SINGLE:
        case CGX_MODE_10G_QUAD:
        case CGX_MODE_12G_QUAD:
        case CGX_MODE_20G_QUAD:
        case CGX_MODE_25G_QUAD:
            mrk_cnt = 0x3fff;
            break;
        case CGX_MODE_20G_SINGLE:
        case CGX_MODE_25G_SINGLE:
            /* 20G or 25G one lane modes */
            if (priv->flags & CGX_FLAGS_RS_FEC)
                mrk_cnt = 0x13ffc;
            else
                mrk_cnt = 0x3fff;
            break;
        case CGX_MODE_12G_DUAL:
        case CGX_MODE_20G_DUAL:
        case CGX_MODE_25G_DUAL:
            /* 40G or 50G two lane modes */
            if (priv->flags & CGX_FLAGS_RS_FEC)
            {
                mrk_cnt = 0x4fff;
                by_mrk_100g = 0;
            }
            else
                mrk_cnt = 0x3fff;
            break;
        case CGX_MODE_USXGMII_1PORT_2G:
        case CGX_MODE_USXGMII_1PORT_5G:
        case CGX_MODE_USXGMII_1PORT_10G:
        case CGX_MODE_USXGMII_2PORT_5G:
        case CGX_MODE_USXGMII_2PORT_10G:
        case CGX_MODE_USXGMII_2PORT_20G:
        case CGX_MODE_USXGMII_4PORT_10G:
        case CGX_MODE_USXGMII_4PORT_20G:
            if (priv->flags & CGX_FLAGS_RS_FEC)
                mrk_cnt = 0x13ffc;
            else
                mrk_cnt = 0x4010;
            break;
    }
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_TX_MRK_CNT(cgx, lmac),
        c.s.ram_mrk_cnt = ram_mrk_cnt;
        c.s.by_mrk_100g = by_mrk_100g;
        c.s.mrk_cnt = mrk_cnt);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_RX_MRK_CNT(cgx, lmac),
        c.s.ram_mrk_cnt = ram_mrk_cnt;
        c.s.by_mrk_100g = by_mrk_100g;
        c.s.mrk_cnt = mrk_cnt);

    /* 5.6) If autonegotiation is desired, configure and enable
        autonegotiation as follows:
        (a) For USXGMII: Write
            CGX(0..2)_SPU(0..3)_USX_AN_CONTROL[AN_EN] = 1.
            Adjust CGX(0..2)_SPU(0..3)_USX_AN_LINK_TIMER[COUNT] as needed.
            Optionally, write
            CGX(0..2)_SPU(0..3)_AN_CONTROL[USX_AN_ARB_LINK_CH K_EN] = 1.
            Refer to steps (6) and (7) for details on this optional
            feature.
            Program the negotiation parameters to be advertised to the
            link partner in CGX(0..2)_SPU(0..3)_USX_AN_ADV. The
            advertised parameters must be consistent with the programmed
            CGX(0..2)_CMR(0..3)_CONFIG[LMAC_TYPE],
            CGX(0..2)_SPU(0..3)_FEC_CONTROL[FEC_EN], and
            CGX(0..2)_SPU_USXGMII_CONTROL[USXGMII_TYPE] values.
        (b)  For all other LMAC types:
            Write CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_EN] = 1.
            If an extended next page is needed, write
            CGX(0..2)_SPU(0..3)_AN_CONTROL[XNP_EN] = 1 and
            CGX(0..2)_SPU(0..3)_AN_ADV[NP] = 1.  It is important that
            CGX(0..2)_SPU(0..3)_AN_XNP_TX is not written at this time.
            Optionally write CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_ARB_LINK_CHK_EN]
            = 1. Refer to steps (6) and (7) for details on this optional
            feature.
            Program the negotiation parameters to be advertised to the
            link partner in CGX(0..2)_SPU(0..3)_AN_ADV. The advertised
            parameters must be consistent with the programmed
            CGX(0..2)_CMR(0..3)_CONFIG[LMAC_TYPE] and
            CGX(0..2)_SPU(0..3)_FEC_CONTROL[FEC_EN] values. Note that
            autonegotiation for Ethernet Consortium 50GBASE-R2 or
            Ethernet Consortium 25GBASE-R requires the use of extended
            pages (refer to section 3.2.5 of the 25G/50G Ethernet
            Consortium specification).  See step (6) for details on the
            extended pages sequence */
    cgx_restart_autoneg(handle);

    /* 5.7) Select deficit idle count mode and unidirectional
            enable/disable via CGX(0..2)_SMU(0..3)_TX_CTL[DIC_EN,UNI_EN] */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SMUX_TX_CTL(cgx, lmac),
        c.s.l2p_bp_conv = 1; /* If set, causes TX to generate 802.3 pause packets when CMR applies logical backpressure */
        c.s.mia_en = 1; /* Marker(alignmentand/or RS FEC marker) idle adjustment enable */
        c.s.dic_en = 1; /* Enable better IFG packing and improves performance */
        c.s.uni_en = 0);
    return 0;
}

/**
 * Attempt to bring up the link. This implements the last steps of Link Bring-up
 * in the HRM, specifically the steps related to "(6) Bring up the SMU/SPU and
 * the CGX reconciliation layer logic" and beyond.
 *
 * @param handle Port to bring up
 *
 * @return Zero on success, negative on failure
 */
static int cgx_bring_link_up(bdk_if_handle_t handle)
{
    const int TIMEOUT_AN_PAGE = 1000; /* 1ms - Timeout for receiving partners AN page */
    const int TIMEOUT_TRAINING = 800000; /* 800ms - Wait for training to complete */
    const int TIMEOUT_STATUS = 10000; /* 10ms for link status good */
    cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;
    bool is_gmx = ((priv->mode >= CGX_MODE_SGMII) && (priv->mode <= CGX_MODE_QSGMII));
    bool is_usxgmii = (priv->mode >= CGX_MODE_USXGMII_1PORT_2G) && (priv->mode <= CGX_MODE_USXGMII_4PORT_20G);

    if (priv->mode == CGX_MODE_DISABLED)
        return -1;

    BDK_TRACE(BGX, "%s: Performing CGX link up\n", handle->name);
    BDK_CSR_WRITE(node, BDK_CGXX_SMUX_RX_INT(cgx, lmac), -1);
    BDK_CSR_WRITE(node, BDK_CGXX_SMUX_TX_INT(cgx, lmac), -1);
    bdk_cgxx_spux_int_t spux_int;
    spux_int.u = -1;
    spux_int.s.an_page_rx = 0; /* Don't clear AN base page status */
    spux_int.s.an_link_good = 0; /* Don't clear AN link good */
    spux_int.s.an_complete = 0; /* Don't clear AN complete */
    spux_int.s.training_done = 0; /* Don't clear training complete */
    spux_int.s.training_failure = 0; /* Don't clear training complete */
    BDK_CSR_WRITE(node, BDK_CGXX_SPUX_INT(cgx, lmac), spux_int.u);

    /* Section 57.6.3 Link Bring-Up, version 0.85998e */

    BDK_CSR_INIT(cmrx_config, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac));
    if (!cmrx_config.s.enable)
    {
        /* 6) Bring up the SMU/SPU and the CGX reconciliation layer logic: */
        /* 6.1) Set CGX(0..2)_SPU(0..3)_CONTROL1[LO_PWR] = 0. */
        /* SPU */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_CONTROL1(cgx, lmac),
            c.s.lo_pwr = is_gmx);
        /* GMX */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac),
            c.s.pwr_dn = !is_gmx);

        /* 6.2) Set CGX(0..2)_CMR(0..3)_CONFIG[ENABLE] = 1 to enable the LMAC. */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
            c.s.enable = 1);

        /* 6.3) For USXGMII, also set CGX(0..2)_SPU_USXGMII_CONTROL[ENABLE] = 1. */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_SPU_USXGMII_CONTROL(cgx),
            c.s.enable = is_usxgmii);
    }

    if (is_gmx)
    {
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_GMP_PCS_RXX_SYNC(cgx, lmac), bit_lock, ==, 1, 1000))
        {
            BDK_TRACE(BGX, "%s: Bit lock not achieved\n", handle->name);
            return -1;
        }
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_GMP_PCS_RXX_SYNC(cgx, lmac), sync, ==, 1, 1000))
        {
            BDK_TRACE(BGX, "%s: Code group synchronization not achieved\n", handle->name);
            return -1;
        }
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_GMP_PCS_MRX_STATUS(cgx, lmac), lnk_st, ==, 1, 1000))
        {
            BDK_TRACE(BGX, "%s: Link down\n", handle->name);
            return -1;
        }
        BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx, lmac),
            c.s.gmxeno = 0);
        goto smu_skip;
    }

    /* If autonegotiation was not enabled, proceed to step (8). */
    if (!(priv->flags & CGX_FLAGS_AUTO_NEG))
        goto step_8;
    /* USXGMII does AN in hardware. The below code is only for ethernet */
    if (is_usxgmii)
        goto step_8;
    spux_int.u = BDK_CSR_READ(node, BDK_CGXX_SPUX_INT(cgx, lmac));
    BDK_CSR_INIT(an_control, node, BDK_CGXX_SPUX_AN_CONTROL(cgx, lmac));
    if (an_control.s.an_arb_link_chk_en)
    {
        if (spux_int.s.an_complete)
        {
            BDK_TRACE(BGX, "%s: Skipping AN, AN complete\n", handle->name);
            goto step_8;
        }
    }
    else
    {
        if (spux_int.s.an_link_good)
        {
            BDK_TRACE(BGX, "%s: Skipping AN, AN link good\n", handle->name);
            goto step_8;
        }
    }

    /* If autonegotiation was enabled, SPU will execute the
        autonegotiation protocol with the link partner.  If extended pages
        were enabled in step (5.6b), then software must sequence through
        the exchanges of base pages and extended pages.  Here is a sample
        sequence for 50GBASE-R2:

        Wait for the CGX(0..2)_SPU(0..3)_INT[AN_PAGE_RX] interrupt which
        signals the receipt of the link partner’s base page. */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SPUX_INT(cgx, lmac), an_page_rx, ==, 1, TIMEOUT_AN_PAGE))
    {
        BDK_TRACE(BGX, "%s: Timeout waiting for AN base page\n", handle->name);
        cgx_restart_autoneg(handle);
        return -1;
    }
    BDK_CSR_INIT(an_page1, node, BDK_CGXX_SPUX_AN_LP_BASE(cgx, lmac));
    spux_int.u = 0;
    spux_int.s.an_page_rx = 1;
    BDK_CSR_WRITE(node, BDK_CGXX_SPUX_INT(cgx, lmac), spux_int.u);
    BDK_TRACE(BGX, "%s: AN base page 0x%lx\n", handle->name, an_page1.u);

    /* Check if the partner or us has extended pages */
    BDK_CSR_INIT(an_adv, node, BDK_CGXX_SPUX_AN_ADV(cgx, lmac));
    if (an_page1.s.np || an_adv.s.np)
    {
        int num_pages = 0;
        bdk_cgxx_spux_an_xnp_tx_t xnp_tx;
        bdk_cgxx_spux_an_lp_xnp_t lp_xnp;
        spux_int.u = 0;
        spux_int.s.an_page_rx = 1;
        do
        {
            xnp_tx.u = 0;
            switch (num_pages)
            {
                case 0: /* Send ethernet consortium header */
                    if (priv->mode == CGX_MODE_25G_DUAL)
                    {
                        xnp_tx.s.u = 0x4df0353; //0x3530fd40;
                        xnp_tx.s.np = 1;
                        xnp_tx.s.mp = 1;
                        xnp_tx.s.m_u = 0x005;
                    }
                    break;
                case 1: /* Send ethernet consortium data */
                    if (priv->mode == CGX_MODE_25G_DUAL)
                    {
                        xnp_tx.s.u |= 1 << 4; /* 25GBASE-KR */
                        xnp_tx.s.u |= 1 << 5; /* 25GBASE-CR */
                        xnp_tx.s.u |= 1 << 8; /* 50GBASE-KR2 */
                        xnp_tx.s.u |= 1 << 9; /* 50GBASE-CR2 */
                        xnp_tx.s.u |= 1 << 24; /* F1 - Clause 91 FEC ability */
                        xnp_tx.s.u |= 1 << 25; /* F2 - Clause 74 FEC ability */
                        if (priv->flags & CGX_FLAGS_FEC)
                        {
                            xnp_tx.s.u |= 1 << 26; /* F3 - Clause 91 FEC request */
                            xnp_tx.s.u |= 1 << 27; /* F4 - Clause 74 FEC request */
                        }
                        xnp_tx.s.np = 0;
                        xnp_tx.s.mp = 0;
                        xnp_tx.s.m_u = 0x203;
                    }
                default: /* Send empty page to finish protocol */
                    break;
            }
            BDK_CSR_WRITE(node, BDK_CGXX_SPUX_AN_XNP_TX(cgx, lmac), xnp_tx.u);
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SPUX_INT(cgx, lmac), an_page_rx, ==, 1, TIMEOUT_AN_PAGE))
            {
                BDK_TRACE(BGX, "%s: Timeout waiting for AN extended page %d\n", handle->name, num_pages);
                cgx_restart_autoneg(handle);
                return -1;
            }
            lp_xnp.u = BDK_CSR_READ(node, BDK_CGXX_SPUX_AN_LP_XNP(cgx, lmac));
            BDK_CSR_WRITE(node, BDK_CGXX_SPUX_INT(cgx, lmac), spux_int.u);
            BDK_TRACE(BGX, "%s: AN extended page %d sent 0x%lx, received 0x%lx\n", handle->name, num_pages, xnp_tx.u, lp_xnp.u);
            num_pages++;
        } while (lp_xnp.s.np || xnp_tx.s.np);
    }

    if (an_control.s.an_arb_link_chk_en)
    {
        /* If CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_ARB_LINK_CHK_EN] is set
            (CGX(0..2)_SPU(0..3)_AN_CONTROL[USX_AN_ARB_LINK_CHK_EN] for
            USXGMII) and the HCD matches the current settings for LMAC type
            (CGX(0..2)_CMR(0..3)_CONFIG[LMAC_TYPE]) and FEC type
            (CGX(0..2)_SPU(0..3)_FEC_CONTROL[FEC_EN]), CGX will set the
            CGX(0..2)_SPU(0..3)_INT[AN_COMPLETE] interrupt when the link is up
            (CGX(0..2)_SPU(0..3)_INT[USX_AN_CPT] for USXGMII). Proceed to
            step (8). */
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SPUX_INT(cgx, lmac), an_complete, ==, 1, TIMEOUT_AN_PAGE))
        {
            BDK_TRACE(BGX, "%s: Timeout waiting for AN complete\n", handle->name);
            return -1;
        }
        else
        {
            BDK_TRACE(BGX, "%s: AN complete\n", handle->name);
            goto step_8;
        }
    }
    else
    {
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SPUX_INT(cgx, lmac), an_link_good, ==, 1, TIMEOUT_AN_PAGE))
        {
            BDK_TRACE(BGX, "%s: Timeout waiting for AN link good\n", handle->name);
            return -1;
        }
        BDK_TRACE(BGX, "%s: AN link good\n", handle->name);
        /* If CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_ARB_LINK_CHK_EN] = 0
            (CGX(0..2)_SPU(0..3)_AN_CONTROL[USX_AN_ARB_LINK_CHK_EN] = 0 for
            USXGMII) or the negotiated HCD does not match the current settings for
            LMAC type and FEC type, then proceed to step (7). */

        /* 7) This step requires software intervention to complete the
            autonegotiation process. Inspect the link partner’s advertised
            capabilities as captured in CGX(0..2)_SPU(0..3)_AN_LP_BASE and
            CGX(0..2)_SPU(0..3)_AN_LP_XNP to determine if CGX’s current
            LMAC or FEC configuration need to be changed. If no change is
            required (as in the case of an HCD match, but
            CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_ARB_LINK_CHK_EN] is disabled),
            then clear CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_EN] = 0 and proceed
            to step (8). At this point, link training can be optionally
            enabled if it wasn’t enabled in previous steps. If CGX’s
            current LMAC or FEC configuration require changes, then
            proceed with the following steps: */

        /* 7.1) Force on the CGX global clocks by writing
            CGX(0..2)_CMR_GLOBAL_CONFIG[CGX_CLK_ENABLE] = 1. */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_GLOBAL_CONFIG(cgx),
            c.s.cgx_clk_enable = 1);

        /* 7.2) Disable the LMAC by writing
            CGX(0..2)_CMR(0..3)_CONFIG[ENABLE] = 0. */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
            c.s.enable = 0);

        /* 7.3) Disable autonegotiation by writing
          CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_EN] = 0. */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_USX_AN_CONTROL(cgx, lmac),
            c.s.an_en = 0);
        BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_AN_CONTROL(cgx, lmac),
            c.s.an_en = 0);

        /* 7.4) Reconfigure the LMAC type or FEC type as needed
            (CGX(0..2)_CMR(0..3)_CONFIG[LMAC_TYPE],
            CGX(0..2)_SPU(0..3)_FEC_CONTROL[FEC_EN]).  Reconfiguring the LMAC
            type may require a reconfiguration of GSER as well. */
        BDK_CSR_INIT(an_adv, node, BDK_CGXX_SPUX_AN_ADV(cgx, lmac));
        bool use_fec = (an_page1.s.fec_able && an_adv.s.fec_able) &&
            (an_page1.s.fec_req || an_adv.s.fec_req);
        BDK_TRACE(BGX, "%s: Turning FEC per AN results: %s\n", handle->name, use_fec ? "ON" : "OFF");
        BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_FEC_CONTROL(cgx, lmac),
            c.s.fec_en = use_fec);

        /* 7.5) Write CGX(0..2)_CMR_GLOBAL_CONFIG[CGX_CLK_ENABLE] = 0. */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_GLOBAL_CONFIG(cgx),
            c.s.cgx_clk_enable = 0);

        /* 7.6) Optionally enable link training by writing
            CGX(0..2)_SPU(0..3)_BR_PMD_CONTROL[TRAIN_EN] = 1 and
            CGX(0..2)_SPU(0..3)_BR_PMD_CONTROL[TRAIN_RESTART] = 1. At this
            point, it is possible to configure CGX to restart
            autonegotiation with the updated LMAC type and FEC type to
            improve synchronization of link training start with he link
            partner.  To enable a restart of autonegotiation, first reset
            the AN state machine by setting
            CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_RESET] = 1 and waiting for the
            AN_RESET to clear to 0. This reset will clear the contents of
            autonegotiation-related CSRs, so they must be reprogrammed.
            Reenable autonegotiation by writing
            CGX(0..2)_SPU(0..3)_AN_CONTROL[AN_EN] = 1. */

        /* 7.7) Reenable the LMAC by writing
            CGX(0..2)_CMR(0..3)_CONFIG[ENABLE] = 1. It is recommended to
            complete step (7) within 10ms to avoid timeout issues with the
            link partner. */
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
            c.s.enable = 1);
    }

step_8:
    /* 8) If link training was enabled, CGX will go through link
        training with the link partner and set
        CGX(0..2)_SPU(0..3)_INT[TRAINING_DONE] when done.

        If link training was disabled and the per-lane speed is 10 Gb/s
        or greater, a receiver adaptation should be completed before
        proceeding. Refer to the GSER section for details on how to
        complete the RX adaptation.

        Immediately after CGX comes out of reset (or after completing
        autonegotiation and/or link training), a LOC_FAULT (refer to
        Section 57.5.1) occurs. This normally causes the remote fault
        sequence to be driven onto the TX bus (only during idle cycles
        if CGX(0..2)_SMU(0..3)_TX_CTL[UNI_EN] = 1) by the reconciliation
        layer transmit logic until the link achieves alignment. Note
        that any receive-polarity and/or receive-lane-swap register
        changes (that occur in step (5.2)) will likely cause SMU/SPU to
        restart bringup of the link.
        CGX should be both transmitting and receiving normal 64/66
        blocks. Assuming no training failure, CGX will begin
        transmitting an idle or remote fault pattern. */
    if (priv->flags & CGX_FLAGS_TRAINING)
    {
        BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SPUX_INT(cgx, lmac), training_done || c.s.training_done, ==, 1, TIMEOUT_TRAINING);
        BDK_CSR_INIT(spux_int, node, BDK_CGXX_SPUX_INT(cgx, lmac));
        if (spux_int.s.training_done && !spux_int.s.training_failure)
        {
            cgx_gsern_adjust_after_training(handle);
            BDK_TRACE(BGX, "%s: Training complete\n", handle->name);
        }
        else if (spux_int.s.training_failure)
        {
            BDK_TRACE(BGX, "%s: Training failed, restarting\n", handle->name);
            /* Don't clear AN state */
            spux_int.s.an_complete = 0;
            spux_int.s.an_link_good = 0;
            BDK_CSR_WRITE(node, BDK_CGXX_SPUX_INT(cgx, lmac), spux_int.u);
            BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_BR_PMD_CONTROL(cgx, lmac),
                c.s.train_restart = 1);
            return -1;
        }
        else
        {
            BDK_TRACE(BGX, "%s: Training not done\n", handle->name);
            cgx_gsern_adjust_after_training(handle); // FIXME?
            //return -1;
        }
    }
    else
    {
        /* Conditionally perform RX adaptation */
        int qlm = priv->first_qlm;
        uint64_t lane_mask = priv->lane_mask;
        /* Skip RX adaptation in loopback mode */
        BDK_CSR_INIT(spux_control1, node, BDK_CGXX_SPUX_CONTROL1(cgx, lmac));
        if (spux_control1.s.loopbck)
            lane_mask = 0;
        /* Only do RX adaptation on first LMAC of USXGMII */
        if (is_usxgmii && (lmac > 0))
            lane_mask = 0;
        /* The lane mask may span multiple QLM/DLM. We require the QLM/DLM to be sequential */
        while (lane_mask)
        {
            /* Get the number of lanes on this QLM/DLM */
            int num_lanes = bdk_qlm_get_lanes(node, qlm);
            for (int lane = 0; lane < num_lanes; lane++)
            {
                if (lane_mask & (1 << lane))
                {
                    bool skip = false;
                    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
                    {
                        /* Make sure the GSERN lane is connected to CGX */
                        BDK_CSR_INIT(src, node, BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, lane));
                        BDK_CSR_INIT(lanex_lt_bcfg, node, BDK_GSERNX_LANEX_LT_BCFG(qlm, lane));
                        if (src.s.tx_ctrl_sel != 2)
                        {
                            skip = true;
                            BDK_TRACE(BGX, "%s: RX skipped, QLM%d Lane %d. Not connected to CGX\n", handle->name, qlm, lane);
                        }
                        else if (lanex_lt_bcfg.s.core_loopback_mode)
                        {
                            skip = true;
                            BDK_TRACE(BGX, "%s: GSERN core loopback, RX adaptiation skipped, QLM%d Lane %d\n", handle->name, qlm, lane);
                        }
                    }
                    if (!bdk_config_get_int(BDK_CONFIG_QLM_RX_ADAPTATION, node, qlm, lane))
                    {
                        skip = true;
                        BDK_TRACE(BGX, "%s: RX adaptation skipped according to configuration, QLM%d Lane %d\n", handle->name, qlm, lane);
                    }
                    if (!skip && bdk_qlm_rx_equalization(handle->node, qlm, lane))
                    {
                        BDK_TRACE(BGX, "%s: RX adaptation failed, QLM%d Lane %d\n", handle->name, qlm, lane);
                        return -1;
                    }
                    else if (!skip)
                        BDK_TRACE(BGX, "%s: RX adaptation success, QLM%d Lane %d\n", handle->name, qlm, lane);
                }
            }

            /* Move the the next QLM/DLM */
            lane_mask >>= num_lanes;
            qlm++;
        }
    }

    /* Check to make sure that the link appears up and stable. The link
        appears up when CGX(0..2)_SPU(0..3)_STATUS1[RCV_LNK] = 1 and
        CGX(0..2)_SMU(0..3)_RX_CTL[STATUS] = 0.  For a stable link,
        support recommends to wait until
        CGX(0..2)_SPU(0..3)_BR_STATUS2[BER_CNT] and
        CGX(0..2)_SPU(0..3)_BR_STATUS2[ERR_BLKS] read back as 0 after
        100 ms (for BASE-R modes). Refer to Section 57.6.5 for
        additional information to determine a stable link-up status. */
    /* Clear latching errors */
    bdk_cgxx_spux_status1_t spux_status1;
    spux_status1.u = 0;
    spux_status1.s.rcv_lnk = 1;
    bdk_cgxx_spux_status2_t spux_status2;
    spux_status2.u = 0;
    spux_status2.s.rcvflt = 1;
    BDK_CSR_WRITE(node, BDK_CGXX_SPUX_STATUS2(cgx, lmac), spux_status2.u);
    BDK_CSR_READ(node, BDK_CGXX_SPUX_STATUS2(cgx, lmac));
    BDK_CSR_WRITE(node, BDK_CGXX_SPUX_STATUS1(cgx, lmac), spux_status1.u);
    /* USXGMII - Check if link is good */
    if (is_usxgmii && !bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        /* Wait up to 10ms for receive ready */
        uint64_t timeout = bdk_clock_get_rate(node, BDK_CLOCK_TIME)/100 + bdk_clock_get_count(BDK_CLOCK_TIME);
        while (1)
        {
            /* Require the bit to stay set for at least 1ms */
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SPUX_STATUS1(cgx, lmac), rcv_lnk, ==, 0, 1000))
                break;
            if (bdk_clock_get_count(BDK_CLOCK_TIME) >= timeout)
            {
                BDK_TRACE(BGX, "%s: Timeout waiting for CGXX_SPUX_STATUS1[RCV_LNK]\n", handle->name);
                return -1;
            }
            /* Latching bit, so set it again */
            BDK_CSR_WRITE(node, BDK_CGXX_SPUX_STATUS1(cgx, lmac), spux_status1.u);
        }
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_SMUX_RX_CTL(cgx, lmac), status, ==, 0, TIMEOUT_STATUS))
        {
            BDK_CSR_INIT(rx_ctl, node, BDK_CGXX_SMUX_RX_CTL(cgx, lmac));
            BDK_TRACE(BGX, "%s: Timeout waiting for CGXX_SMUX_RX_CTL[STATUS]==0 (STATUS=%d)\n", handle->name, rx_ctl.s.status);
            return -1;
        }
    }
    /* non-USXGMII - Check if link is good */
    if (!is_usxgmii && !bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        /* Wait up to 50ms for an error-free link */
        uint64_t timeout_usec = 50000;
        uint64_t timeout = bdk_clock_get_count(BDK_CLOCK_TIME) + timeout_usec *
            bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;

        while (1)
        {
            bool link_up = true;
            uint64_t debounce_usec = 10000;
            uint64_t debounce_time = bdk_clock_get_count(BDK_CLOCK_TIME) + debounce_usec *
                bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;

            /* Clear the ERR_BLKS and BER_CNT counters */
            BDK_CSR_WRITE(node, BDK_CGXX_SPUX_BR_STATUS2(cgx, lmac), 0);

            /* Verify link is up and error-free for the debounce time */
            while (link_up && (bdk_clock_get_count(BDK_CLOCK_TIME) < debounce_time))
            {
                bdk_wait_usec(1);
                BDK_CSR_INIT(smux_rx_ctl, node, BDK_CGXX_SMUX_RX_CTL(cgx, lmac));
                BDK_CSR_INIT(spux_br_status2, node, BDK_CGXX_SPUX_BR_STATUS2(cgx, lmac));
                BDK_CSR_INIT(spux_status1, node, BDK_CGXX_SPUX_STATUS1(cgx, lmac));

                /* Verify link is up and error free */
                link_up = (spux_status1.s.rcv_lnk == 1) && (smux_rx_ctl.s.status == 0) &&
                    (spux_br_status2.s.err_blks == 0) && (spux_br_status2.s.ber_cnt == 0);
            }

            if (link_up)
                break;

            if (bdk_clock_get_count(BDK_CLOCK_TIME) >= timeout)
            {
                BDK_CSR_INIT(smux_rx_ctl, node, BDK_CGXX_SMUX_RX_CTL(cgx, lmac));
                BDK_CSR_INIT(spux_br_status2, node, BDK_CGXX_SPUX_BR_STATUS2(cgx, lmac));
                BDK_CSR_INIT(spux_status1, node, BDK_CGXX_SPUX_STATUS1(cgx, lmac));
                if (spux_status1.s.rcv_lnk != 1)
                    BDK_TRACE(BGX, "%s: Timeout waiting for CGXX_SPUX_STATUS1[RCV_LNK]\n", handle->name);
                else if (smux_rx_ctl.s.status == 1)
                    BDK_TRACE(BGX, "%s: Timeout waiting for CGXX_SMUX_RX_CTL[STATUS]==0 (STATUS=%d). Local fault detected\n", handle->name, smux_rx_ctl.s.status);
                else if (smux_rx_ctl.s.status == 2)
                    BDK_TRACE(BGX, "%s: Timeout waiting for CGXX_SMUX_RX_CTL[STATUS]==0 (STATUS=%d). Remote fault detected\n", handle->name, smux_rx_ctl.s.status);
                else if (spux_br_status2.s.err_blks)
                    BDK_TRACE(BGX, "%s: %d error blocks\n", handle->name, spux_br_status2.s.err_blks);
                else if (spux_br_status2.s.ber_cnt)
                    BDK_TRACE(BGX, "%s: %d BER\n", handle->name, spux_br_status2.s.ber_cnt);
                else
                    BDK_TRACE(BGX, "%s: Timeout waiting for CGXX_SMUX_RX_CTL[STATUS]==0 (STATUS=%d) to be stable\n", handle->name, smux_rx_ctl.s.status);
                return -1;
            }

            /* Clear the error counts */
            BDK_CSR_WRITE(node, BDK_CGXX_SPUX_BR_STATUS2(cgx, lmac), 0);
            /* RCV_LNK is a latching bit, so set it again */
            spux_status1.s.rcv_lnk = 1;
            BDK_CSR_WRITE(node, BDK_CGXX_SPUX_STATUS1(cgx, lmac), spux_status1.u);
        }
    }

    /* If autonegotiation was enabled and step (7) was skipped,
        CGX(0..2)_SPU(0..3)_AN_STATUS[AN_COMPLETE] is set along with
        CGX(0..2)_SPU(0..3)_INT[AN_COMPLETE] when the link is up
        (CGX(0..2)_SPU(0..3)_USX_AN_STATUS[AN_CPT] and
        CGX(0..2)_SPU(0..3)_INT[USX_AN_CPT] for USXGMII). */
    /* Not applicable right now */

    /* 9) At this point, it is appropriate to clear out all the
        error states that accumulated during link bringup and reenable the
        relevant interrupts.

        Clear out CGX(0..2)_SMU(0..3)_RX_INT, CGX(0..2)_SMU(0..3)_TX_INT, and CGX(0..2)_SPU(0..3)_INT.
        Enable interrupts via CGX(0..2)_SMU(0..3)_RX_INT_ENA_W1S, CGX(0..2)_SMU(0..3)_TX_INT_ENA_W1S, and CGX(0..2)_SPU(0..3)_INT_ENA_W1S respectively.
        Write 1 to clear CGX(0..2)_SPU(0..3)_BR_STATUS2[LATCHED_BER]. */
    BDK_CSR_WRITE(node, BDK_CGXX_SMUX_RX_INT(cgx, lmac), -1);
    BDK_CSR_WRITE(node, BDK_CGXX_SMUX_TX_INT(cgx, lmac), -1);
    BDK_CSR_WRITE(node, BDK_CGXX_SPUX_INT(cgx, lmac), -1);
    BDK_CSR_DEFINE(status2, BDK_CGXX_SPUX_BR_STATUS2(cgx, lmac));
    status2.u = 0;
    status2.s.latched_ber = 1;
    BDK_CSR_WRITE(node, BDK_CGXX_SPUX_BR_STATUS2(cgx, lmac), status2.u);
smu_skip:
    /* 10) Enable packet transmit and receive by writing
        CGX(0..2)_CMR(0..3)_CONFIG[DATA_PKT_TX_EN,DATA_PKT_RX_EN] = 1.
        This step should only be executed after NIX has been configured,
        as packets should not arrive at NIX until they are fully
        configured. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
        c.s.data_pkt_rx_en = 1;
        c.s.data_pkt_tx_en = 1);
    return 0;
}

/**
 * Bring the link down. This implements the steps of Link Bring-Down
 * in the HRM
 *
 * @param handle Port to bring down
 *
 * @return Zero on success, negative on failure
 */
static int cgx_bring_link_down(bdk_if_handle_t handle)
{
    const int TIMEOUT_FIFO = 1000; /* 1ms - Wait for RX or TX fifo to be empty */
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;
    bool is_usxgmii = (priv->mode >= CGX_MODE_USXGMII_1PORT_2G) && (priv->mode <= CGX_MODE_USXGMII_4PORT_20G);
    int result = 0;

    BDK_TRACE(BGX, "%s: Performing CGX link down\n", handle->name);

    /* Section 57.6.4 Link Bring-Down, version 0.85998e */

    /* 1) Write CGX(0..2)_CMR(0..3)_CONFIG[DATA_PKT_RX_EN] = 0.
        The MAC layer stops accepting RX data packets; remaining RX
        packets in the CGX are drained to the NIX or NCSI block. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
        c.s.data_pkt_rx_en = 0);

    /* 2) Wait a minimum of 500 ns plus the maximum jabber receive
        time based on the link speed and RX jabber count value
        (CGX(0..2)_SMU(0..3)_RX_JABBER[CNT]). For example, a 10GBASE-R
        link with the default jabber count value of 0x2800 (10240 bytes)
        will have a maximum jabber receive time of 10240*8/10, i.e. ~8200
        ns. */
    bdk_wait_usec(10);

    /* 3) Wait until the RX buffer is empty by reading
        CGX(0..2)_CMR(0..3)_RX_FIFO_LEN[FIFO_LEN_E] and
        CGX(0..2)_CMR(0..3)_RX_FIFO_LEN[FIFO_LEN]. */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_CMRX_RX_FIFO_LEN(cgx, lmac), fifo_len_e, ==, 0, TIMEOUT_FIFO))
    {
        bdk_error("%s: Timeout waiting for CGXX_CMRX_RX_FIFO_LEN[FIFO_LEN_E]\n", handle->name);
        result = -1;
    }
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_CMRX_RX_FIFO_LEN(cgx, lmac), fifo_len, ==, 0, TIMEOUT_FIFO))
    {
        bdk_error("%s: Timeout waiting for CGXX_CMRX_RX_FIFO_LEN[FIFO_LEN]\n", handle->name);
        result = -1;
    }

    /* 4) The TX data path may optionally be drained at this time.
        If this step is bypassed, software may reenable the link at a
        later time to resume the transmission of queued packets in the NIX
        or NCSI block and/or TX buffer. To drain the TX data path:

        Stop queuing TX packets for the LMAC in NIX or NCSI.

        Wait until NIX or NCSI queues are empty (refer to Chapter 37,
        and Chapter 42).

        Wait until the CGX TX buffer for this LMAC is empty by reading
        CGX(0..2)_CMR(0..3)_TX_FIFO_LEN[FIFO_E_LEN] and
        CGX(0..2)_CMR(0..3)_TX_FIFO_LEN[FIFO_LEN].

        Wait an additional 500 bytes times (based on link speed) to
        ensure that the rest of the CGX TX data path has been drained.

        Note that TX data path drain is required if the LMAC is to be
        disabled after link bring-down. */
    // FIXME: Stop NIX and NCSI
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_CMRX_TX_FIFO_LEN(cgx, lmac), fifo_e_len, ==, 0, TIMEOUT_FIFO))
    {
        bdk_error("%s: Timeout waiting for CGXX_CMRX_TX_FIFO_LEN[FIFO_E_LEN]\n", handle->name);
        result = -1;
    }
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_CGXX_CMRX_TX_FIFO_LEN(cgx, lmac), fifo_len, ==, 0, TIMEOUT_FIFO))
    {
        bdk_error("%s: Timeout waiting for CGXX_CMRX_TX_FIFO_LEN[FIFO_LEN]\n", handle->name);
        result = -1;
    }
    bdk_wait_usec(1);

    /* 5) Write CGX(0..2)_CMR(0..3)_CONFIG[DATA_PKT_TX_EN] = 0;
        the MAC layer stops transmitting data packets. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
        c.s.data_pkt_tx_en = 0);

    /* 6) If flow control is enabled, disable the transmission and
        reception of the appropriate flow control packets
        (PAUSE/PFC/HiGig) by writing:

        CGX(0..2)_SMU(0..3)_HG2_CONTROL[HG2TX_EN] = 0 to disable HG2
        message generation.

        CGX(0..2)_SMU(0..3)_CBFC_CTL[TX_EN] = 0 to disable CBFC packet
        generation.

        CGX(0..2)_CMR_RX_OVR_BP[EN<n>] = 1 AND
        CGX(0..2)_CMR_RX_OVR_BP[BP<n>] = 0 to disable 802.3 PAUSE packet
        generation. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SMUX_HG2_CONTROL(cgx, lmac),
        c.s.hg2tx_en = 0);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SMUX_CBFC_CTL(cgx, lmac),
        c.s.tx_en = 0);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_RX_OVR_BP(cgx),
        c.s.en |= 1 << lmac;
        c.s.bp &= ~(1 << lmac));

    /* 7) Disable the selected SerDes lane(s) by writing
        CGX(0..2)_SPU(0..3)_CONTROL1[LO_PWR] = 1. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_CONTROL1(cgx, lmac),
        c.s.lo_pwr = 1);
    /* GMX */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac),
        c.s.pwr_dn = 1);

    /* 8) Force on the CGX clocks to ensure successful propagation
        of the reset when disabling the link. Write
        CGX(0..2)_CMR_GLOBAL_CONFIG[CGX_CLK_ENABLE] = 1. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_GLOBAL_CONFIG(cgx),
        c.s.cgx_clk_enable = 1);

    /* 9) At this point, the LMAC can be disabled by writing
        CGX(0..2)_CMR(0..3)_CONFIG[ENABLE] = 0.  In the case of USXGMII,
        also clear CGX(0..2)_SPU_USXGMII_CONTROL[ENABLE] = 0. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
        c.s.enable = 0);
    if (is_usxgmii)
    {
        BDK_CSR_MODIFY(c, node, BDK_CGXX_SPU_USXGMII_CONTROL(cgx),
            c.s.enable = 0);
    }

    /* 10) Release the force of the clocks from step (8) by writing
        CGX(0..2)_CMR_GLOBAL_CONFIG[CGX_CLK_ENABLE] = 0. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_GLOBAL_CONFIG(cgx),
        c.s.cgx_clk_enable = 0);

    return result;
}

/**
 * Called when link lost. This implements the steps of Recovering from a
 * Lost Link in the HRM
 *
 * @param handle Port to bring down
 *
 * @return Zero on success, negative on failure
 */
static int cgx_link_lost(bdk_if_handle_t handle)
{
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;

    /* Section 57.6.6 Recovering from a Lost Link, version 0.85998e */

    /* To reset an LMAC when the link is lost:
    1) If the SerDes interface is reset and/or the SerDes interface
    has become nonfunctional, write
    CGX(0..2)_CMR(0..3)_CONFIG[INT_BEAT_GEN] = 1 to enable the automatic
    generation of RX idle beats and TX beats. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
        c.s.int_beat_gen = 1);

    /* 2) If the TX data path is to be drained and the LMAC type is
    100GBASE-R/50GBASE-R/40GBASE-R/25GBASE-R/10GBASE-R/RXAUI/XAUI/USXGMII
    (i.e. non-SGMII), write CGX(0..2)_SMU(0..3)_TX_CTL[LS] = 0x3
    (link-drain mode). This allows the MAC layer (SMU) to read and drop
    packets from the TX buffer, even though the link is in a fault
    state. */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SMUX_TX_CTL(cgx, lmac),
        c.s.ls = 3);

    /* 3) Execute the link bring down sequence described in Section
    57.6.4. */
    return cgx_bring_link_down(handle);
}

/**
 * Get SGMII link speed
 *
 * @param handle
 *
 * @return
 */
static bdk_if_link_t cgx_check_link_gmx(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;
    bdk_if_link_t result;

    result.u64 = 0;

    BDK_CSR_INIT(gmp_pcs_mrx_control, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac));
    BDK_CSR_INIT(gmp_pcs_mrx_status, node, BDK_CGXX_GMP_PCS_MRX_STATUS(cgx, lmac));
    BDK_CSR_INIT(gmp_pcs_rxx_sync, node, BDK_CGXX_GMP_PCS_RXX_SYNC(cgx, lmac));

    int speed = bdk_qlm_get_gbaud_mhz(node, priv->first_qlm, priv->first_lane) * 8 / 10;
    if (priv->mode == CGX_MODE_QSGMII) /* 4 ports on one lane, divide speed */
        speed /= 4;

    /* Force 1Gbps full duplex link for internal loopback */
    if (bdk_is_platform(BDK_PLATFORM_ASIM) || gmp_pcs_mrx_control.s.loopbck1)
    {
        result.s.up = 1;
        result.s.full_duplex = 1;
        result.s.speed = speed;
        return result;
    }

    /* If auto negotiation is disabled, report speed based on the hardware setup */
    if (!gmp_pcs_mrx_control.s.an_en)
    {
        if (gmp_pcs_mrx_status.s.lnk_st && gmp_pcs_rxx_sync.s.sync)
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
    BDK_CSR_INIT(gmp_pcs_anx_results, node, BDK_CGXX_GMP_PCS_ANX_RESULTS(cgx, lmac));
    if (!gmp_pcs_anx_results.s.an_cpt)
    {
        BDK_TRACE(BGX, "%s: Auto negotiation not complete\n", handle->name);
        cgx_restart_autoneg(handle);
        return result;
    }
    if (!gmp_pcs_anx_results.s.link_ok)
    {
        BDK_TRACE(BGX, "%s: Auto negotiation not link ok\n", handle->name);
        cgx_restart_autoneg(handle);
        return result;
    }

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
    return result;
}

/**
 * Determine the current link state and speed. It doesn't change
 * anything with respect to the link.
 *
 * @param handle Port to check
 *
 * @return Link status
 */
static bdk_if_link_t cgx_check_link(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;
    bool is_gmx = ((priv->mode >= CGX_MODE_SGMII) && (priv->mode <= CGX_MODE_QSGMII));
    bool is_xaui = (priv->mode >= CGX_MODE_XAUI) && (priv->mode <= CGX_MODE_RXAUI);
    bool is_usxgmii = (priv->mode >= CGX_MODE_USXGMII_1PORT_2G) && (priv->mode <= CGX_MODE_USXGMII_4PORT_20G);
    bool is_multiple = (priv->mode == CGX_MODE_10G_QUAD) ||
        (priv->mode == CGX_MODE_25G_DUAL) || (priv->mode == CGX_MODE_25G_QUAD) ||
        (priv->mode == CGX_MODE_20G_DUAL) || (priv->mode == CGX_MODE_20G_QUAD) ||
        (priv->mode == CGX_MODE_12G_DUAL) || (priv->mode == CGX_MODE_12G_QUAD);

    int gbaud_mhz = bdk_qlm_get_gbaud_mhz(node, priv->first_qlm, priv->first_lane);
    int num_ports = 1;
    int data_bits_per_symbol = 64;
    int wire_bits_per_symbol = 66;
    int repeat_factor = 1;

    bdk_if_link_t link_state;
    link_state.u64 = 0;
    link_state.s.lanes = 1;
    link_state.s.full_duplex = 1;
    link_state.s.up = 1;

    BDK_CSR_INIT(cmrx_config, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac));
    if (priv->mode == CGX_MODE_DISABLED)
    {
        handle->flags |= BDK_IF_FLAGS_HIDDEN;
        link_state.u64 = 0;
    }
    else if (!cmrx_config.s.data_pkt_tx_en)
    {
        BDK_TRACE(BGX, "%s: Hasn't completed link bringup\n", handle->name);
        link_state.u64 = 0;
    }
    else if (is_gmx)
    {
        return cgx_check_link_gmx(handle);
    }
    else if (is_usxgmii)
    {
        /* USXGMII number of prots varies by mode */
        if ((priv->mode >= CGX_MODE_USXGMII_2PORT_5G) && (priv->mode <= CGX_MODE_USXGMII_2PORT_20G))
            num_ports = 2;
        if ((priv->mode >= CGX_MODE_USXGMII_4PORT_10G) && (priv->mode <= CGX_MODE_USXGMII_4PORT_20G))
            num_ports = 4;
        /* USXGMII always uses 64/66 encoding */
        data_bits_per_symbol = 64;
        wire_bits_per_symbol = 66;
        /* For USXGMII, the state of the link in CN96XX SPU/ SMU is
            indicated by:
            - Whether the SerDes lane achieved block lock
             (CGX(0..2)_SPU(0..3)_BR_STATUS1[BLK_LOCK])
            - Whether FEC/RS-FEC alignment was acquired (if enabled)
             (CGX(0..2)_SPU(0..3)_RSFEC_STATUS[FEC_ALIGN_STATUS])
            - Whether the interface achieved marker lock
             (CGX(0..2)_SPU(0..3)_BR_ALGN_STATUS[MARKER_LOCK]) */
        BDK_CSR_INIT(fec_control, node, BDK_CGXX_SPUX_FEC_CONTROL(cgx, lmac));
        BDK_CSR_INIT(br_status1, node, BDK_CGXX_SPUX_BR_STATUS1(cgx, lmac));
        BDK_CSR_INIT(rsfec_status, node, BDK_CGXX_SPUX_RSFEC_STATUS(cgx, lmac));
        /* Marker lock is always on LMAC 0 */
        BDK_CSR_INIT(br_algn_status, node, BDK_CGXX_SPUX_BR_ALGN_STATUS(cgx, 0));
        if (bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            br_status1.s.blk_lock = 1;
            rsfec_status.s.fec_align_status = 1;
            br_algn_status.s.marker_lock = 1;
        }
        if (!br_status1.s.blk_lock)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_BR_STATUS1[BLK_LOCK]=0x%x\n", handle->name, br_status1.s.blk_lock);
            cgx_restart_autoneg(handle);
        }
        if ((fec_control.s.fec_en == 2) && !rsfec_status.s.fec_align_status)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_RSFEC_STATUS[FEC_ALIGN_STATUS]=0x%x\n", handle->name, rsfec_status.s.fec_align_status);
            cgx_restart_autoneg(handle);
        }
        if (!br_algn_status.s.marker_lock)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_BR_ALGN_STATUS[MARKER_LOCK]=0x%x\n", handle->name, br_algn_status.s.marker_lock);
            cgx_restart_autoneg(handle);
        }
    }
    else if (is_xaui)
    {
        /* XAUI/RXAUI always uses 8b10 encoding  */
        data_bits_per_symbol = 8;
        wire_bits_per_symbol = 10;
        link_state.s.lanes = (priv->mode == CGX_MODE_RXAUI) ? 2 : 4;

        /* For XAUI/DXAUI/RXAUI, the state of the link in CN96XX SPU/SMU
            is indicated by:
            - Whether each SerDes lane achieved code group
             synchronization (CGX(0..2)_SPU(0..3)_BX_STATUS[LSYNC])
            - Whether the interface achieved lane alignment
             (CGX(0..2)_SPU(0..3)_BX_STATUS[ALIGND]) */
        BDK_CSR_INIT(bx_status, node, BDK_CGXX_SPUX_BX_STATUS(cgx, lmac));
        if (bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            bx_status.s.lsync = bdk_build_mask(link_state.s.lanes);
            bx_status.s.alignd = 1;
        }
        if (bx_status.s.lsync != bdk_build_mask(link_state.s.lanes))
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_BX_STATUS[LSYNC]=0x%x\n", handle->name, bx_status.s.lsync);
        }
        if (!bx_status.s.alignd)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_BX_STATUS[ALIGND]=0x%x\n", handle->name, bx_status.s.alignd);
        }
    }
    else if (is_multiple) /* SMU multiple */
    {
        /* Always uses 64b66 encoding */
        data_bits_per_symbol = 64;
        wire_bits_per_symbol = 66;
        link_state.s.lanes = ((priv->mode == CGX_MODE_25G_DUAL) || (priv->mode == CGX_MODE_20G_DUAL) || (priv->mode == CGX_MODE_12G_DUAL)) ? 2 : 4;

        /* For 40GBASE-R4, 50GBASE-R2, and 100GBASE-R4, the state of the
            link in CN96XX SPU/SMU is indicated by:
            - Whether each SerDes lane achieved block lock
             (CGX(0..2)_SPU(0..3)_BR_ALGN_STATUS[BLOCK_LOCK] and
             CGX(0..2)_SPU(0..3)_BR_STATUS1[BLK_LOCK])
            - Whether the 40G/50G/100G interface achieved lane alignment
             (CGX(0..2)_SPU(0..3)_BR_ALGN_STATUS[ALIGND])
            - Whether the 50G/100G interface achieved FEC/RS-FEC
             alignment (if enabled)
             (CGX(0..2)_SPU(0..3)_RSFEC_STATUS[FEC_ALIGN_STATUS])
            - Whether the 40G/50G/100G interface achieved marker lock
             (CGX(0..2)_SPU(0..3)_BR_ALGN_STATUS[MARKER_LOCK]) */
        BDK_CSR_INIT(fec_control, node, BDK_CGXX_SPUX_FEC_CONTROL(cgx, lmac));
        BDK_CSR_INIT(spux_int, node, BDK_CGXX_SPUX_INT(cgx, lmac));
        BDK_CSR_INIT(br_algn_status, node, BDK_CGXX_SPUX_BR_ALGN_STATUS(cgx, lmac));
        BDK_CSR_INIT(br_status1, node, BDK_CGXX_SPUX_BR_STATUS1(cgx, lmac));
        BDK_CSR_INIT(rsfec_status, node, BDK_CGXX_SPUX_RSFEC_STATUS(cgx, lmac));
        if (bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            br_algn_status.s.block_lock = 1;
            br_status1.s.blk_lock = 1;
            br_algn_status.s.alignd = 1;
            rsfec_status.s.fec_align_status = 1;
            br_algn_status.s.marker_lock = 1;
        }
        if (spux_int.s.rx_link_down)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_INT[RX_LINK_DOWN]\n", handle->name);
            cgx_restart_autoneg(handle);
        }
        if (!br_algn_status.s.block_lock)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_BR_ALGN_STATUS[BLOCK_LOCK]=0x%x\n", handle->name, br_algn_status.s.block_lock);
            cgx_restart_autoneg(handle);
        }
        if (!br_status1.s.blk_lock)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_BR_STATUS1[BLK_LOCK]=0x%x\n", handle->name, br_status1.s.blk_lock);
            cgx_restart_autoneg(handle);
        }
        if (!br_algn_status.s.alignd)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_BR_ALGN_STATUS[ALIGND]=0x%x\n", handle->name, br_algn_status.s.alignd);
            cgx_restart_autoneg(handle);
        }
        if ((fec_control.s.fec_en == 2) && !rsfec_status.s.fec_align_status)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_RSFEC_STATUS[FEC_ALIGN_STATUS]=0x%x\n", handle->name, rsfec_status.s.fec_align_status);
            cgx_restart_autoneg(handle);
        }
        if (!br_algn_status.s.marker_lock)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_BR_ALGN_STATUS[MARKER_LOCK]=0x%x\n", handle->name, br_algn_status.s.marker_lock);
            cgx_restart_autoneg(handle);
        }
    }
    else /* SMU single */
    {
        /* Always uses 64b66 encoding */
        data_bits_per_symbol = 64;
        wire_bits_per_symbol = 66;
        /* For 10GBASE-R and 25GBASE-R, the state of the link in CN96XX
            SPU/SMU is indicated by:
            - Whether the SerDes lane achieved block lock
             (CGX(0..2)_SPU(0..3)_BR_STATUS1[BLK_LOCK])
            - Whether FEC/RS-FEC alignment was acquired (if enabled)
             (CGX(0..2)_SPU(0..3)_RSFEC_STATUS[FEC_ALIGN_STATUS]) */
        BDK_CSR_INIT(fec_control, node, BDK_CGXX_SPUX_FEC_CONTROL(cgx, lmac));
        BDK_CSR_INIT(spux_int, node, BDK_CGXX_SPUX_INT(cgx, lmac));
        BDK_CSR_INIT(br_status1, node, BDK_CGXX_SPUX_BR_STATUS1(cgx, lmac));
        BDK_CSR_INIT(rsfec_status, node, BDK_CGXX_SPUX_RSFEC_STATUS(cgx, lmac));
        if (bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            br_status1.s.blk_lock = 1;
            rsfec_status.s.fec_align_status = 1;
        }
        if (spux_int.s.rx_link_down)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_INT[RX_LINK_DOWN]\n", handle->name);
            cgx_restart_autoneg(handle);
        }
        if (!br_status1.s.blk_lock)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_BR_STATUS1[BLK_LOCK]=0x%x\n", handle->name, br_status1.s.blk_lock);
            cgx_restart_autoneg(handle);
        }
        if ((fec_control.s.fec_en == 2) && !rsfec_status.s.fec_align_status)
        {
            link_state.s.up = 0;
            BDK_TRACE(BGX, "%s: Down due to CGXX_SPUX_RSFEC_STATUS[FEC_ALIGN_STATUS]=0x%x\n", handle->name, rsfec_status.s.fec_align_status);
            cgx_restart_autoneg(handle);
        }
    }

    if (link_state.s.up)
    {
        uint64_t speed = gbaud_mhz * link_state.s.lanes; /* wire bits/sec */
        speed = (speed * data_bits_per_symbol + wire_bits_per_symbol - 1) / wire_bits_per_symbol; /* data bits/sec */
        speed /= num_ports; /* Divide by ports multiplexed on lane */
        speed /= repeat_factor; /* Repeat for this port to od slower speeds (10Mbps, 100Mbps) */
        speed = ((speed + 9) / 10) * 10; /* Round up to nearest 10Mbps */
        link_state.s.speed = speed;
    }
    return link_state;
}

static int if_init(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;

    int bytes_per_port;
    BDK_CSR_INIT(cgxx_const, node, BDK_CGXX_CONST(cgx));
    bytes_per_port = cgxx_const.s.tx_fifosz / cgxx_const.s.lmacs;

    if (!(priv->flags & CGX_FLAGS_NO_NIX))
    {
        if (bdk_nix_port_init(handle, BDK_NIX_TYPE_CGX, bytes_per_port))
            return -1;
    }

    /* Configure the LEDs */
    handle->led[BDK_IF_LED_LINK_SLOW].device = bdk_device_led_lookup(&handle->led[BDK_IF_LED_LINK_SLOW].led, BDK_CONFIG_NETWORK_LED_LINK_SLOW, node, cgx, lmac);
    if (handle->led[BDK_IF_LED_LINK_SLOW].device)
    {
        BDK_TRACE(BGX, "%s: Link slow LED: %s\n", handle->name, handle->led[BDK_IF_LED_LINK_SLOW].device->name);
        bdk_device_led_set(handle->led[BDK_IF_LED_LINK_SLOW].device,
            handle->led[BDK_IF_LED_LINK_SLOW].led, false);
    }

    handle->led[BDK_IF_LED_LINK_FAST].device = bdk_device_led_lookup(&handle->led[BDK_IF_LED_LINK_FAST].led, BDK_CONFIG_NETWORK_LED_LINK_FAST, node, cgx, lmac);
    if (handle->led[BDK_IF_LED_LINK_FAST].device)
    {
        BDK_TRACE(BGX, "%s: Link fast LED: %s\n", handle->name, handle->led[BDK_IF_LED_LINK_FAST].device->name);
        bdk_device_led_set(handle->led[BDK_IF_LED_LINK_FAST].device,
            handle->led[BDK_IF_LED_LINK_FAST].led, false);
    }

    handle->led[BDK_IF_LED_ACTIVITY].device = bdk_device_led_lookup(&handle->led[BDK_IF_LED_ACTIVITY].led, BDK_CONFIG_NETWORK_LED_ACTIVITY, node, cgx, lmac);
    if (handle->led[BDK_IF_LED_ACTIVITY].device)
    {
        BDK_TRACE(BGX, "%s: Activity LED: %s\n", handle->name, handle->led[BDK_IF_LED_ACTIVITY].device->name);
        bdk_device_led_attach(handle->led[BDK_IF_LED_ACTIVITY].device,
            handle->led[BDK_IF_LED_ACTIVITY].led,
            BDK_GPIO_PIN_SEL_E_CGXX_LMACX_RXTX(cgx, lmac));
    }

    handle->led[BDK_IF_LED_ID].device = bdk_device_led_lookup(&handle->led[BDK_IF_LED_ID].led, BDK_CONFIG_NETWORK_LED_ID, node, cgx, lmac);
    if (handle->led[BDK_IF_LED_ID].device)
    {
        BDK_TRACE(BGX, "%s: ID LED: %s\n", handle->name, handle->led[BDK_IF_LED_ID].device->name);
        bdk_device_led_set(handle->led[BDK_IF_LED_ID].device,
            handle->led[BDK_IF_LED_ID].led, false);
    }
    handle->netport = bdk_device_netport_lookup(BDK_CONFIG_NETWORK_PORT, node, cgx, lmac);
    if (handle->netport)
        BDK_TRACE(BGX, "%s: NETPORT: %s\n", handle->name, handle->netport->name);

    cgx_reset(handle);

    if (handle->netport)
        bdk_device_netport_init(handle->netport);

    bdk_netphy_init(bdk_netphy_handle(handle->netphy));

    if ((priv->first_qlm >= 0) && (priv->mode != CGX_MODE_DISABLED))
    {
        bdk_netphy_flags_t flags = BDK_NETPHY_FLAG_NONE;
        if (priv->flags & CGX_FLAGS_RS_FEC)
            flags = BDK_NETPHY_FLAG_RS_FEC;
        else if (priv->flags & CGX_FLAGS_FEC)
            flags = BDK_NETPHY_FLAG_FEC;
        bdk_qlm_modes_t qlm_mode = bdk_qlm_get_mode(handle->node, priv->first_qlm, priv->first_lane);
        int qlm_speed = bdk_qlm_get_gbaud_mhz(handle->node, priv->first_qlm, priv->first_lane);
        bdk_netphy_setup_an(bdk_netphy_handle(handle->netphy), 1, &qlm_mode, &qlm_speed, flags);
    }

    cgx_init_pre_link(handle);
    return 0;
}

static bdk_if_link_t if_link_get(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;

    /* Get the link status */
    bdk_if_link_t result = cgx_check_link(handle);

    /* Get the port status as it might force up down */
    bool force_down = false;
    bdk_device_netport_state_t np_state;
    if (handle->netport)
    {
        bdk_device_netport_get(handle->netport, &np_state);
        force_down = (np_state.flags & (BDK_DEVICE_NETPORT_FLAG_MISSING | BDK_DEVICE_NETPORT_FLAG_RX_ERROR | BDK_DEVICE_NETPORT_FLAG_TX_ERROR)) != 0;
    }
    bdk_netphy_get_speed(bdk_netphy_handle(handle->netphy));

    /* Set some booleans about what is going on */
    bool was_up = result.s.up;
    bool going_down = was_up && force_down;
    bool allow_up = !was_up && !force_down;

    /* Bail if everything was good and is still good */
    if (was_up && !force_down)
        return result;

    if (allow_up)
    {
        /* Try and bring the link up */
        if (cgx_bring_link_up(handle))
        {
            result.s.up = 0;
            result.s.speed = 0;
        }
        else
        {
            result = cgx_check_link(handle);
        }
    }
    else if (going_down)
    {
        /* Bring the link down */
        cgx_link_lost(handle);
        result.s.up = 0;
        result.s.speed = 0;
    }

    /* Update the LINK status LEDs  */
    if (handle->led[BDK_IF_LED_LINK_SLOW].device)
    {
        bdk_device_led_set(handle->led[BDK_IF_LED_LINK_SLOW].device,
            handle->led[BDK_IF_LED_LINK_SLOW].led, result.s.up);
    }
    if (handle->led[BDK_IF_LED_LINK_FAST].device)
    {
        bdk_device_led_set(handle->led[BDK_IF_LED_LINK_FAST].device,
            handle->led[BDK_IF_LED_LINK_FAST].led, result.s.up);
    }

    /* Update the port */
    if (handle->netport)
    {
        bdk_qlm_modes_t qlm_mode = bdk_qlm_get_mode(handle->node, priv->first_qlm, priv->first_lane);
        int speed = bdk_qlm_get_gbaud_mhz(handle->node, priv->first_qlm, priv->first_lane);
        bdk_device_netport_set(handle->netport, qlm_mode, speed, true, result.s.up);
    }
    return result;
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
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;
    bool is_internal = (loopback & BDK_IF_LOOPBACK_INTERNAL) != 0;
    bool is_external = (loopback & BDK_IF_LOOPBACK_EXTERNAL) != 0;

    /* Errata (CGX-35544) Loopback fails to come up
        Before writing CGX()_SPU()_CONTROL1[LOOPBCK] = 1, write
        CGX()_SPU()_MISC_CONTROL[RX_EDET_SIGNAL_OK] = 1 */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0))
    {
        BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_MISC_CONTROL(cgx, lmac),
            c.s.rx_edet_signal_ok = is_internal);
    }

    /* INT_BEAT_GEN must be set for loopback if the QLMs are not clocked. Set
       it whenever we use internal loopback */
    BDK_CSR_MODIFY(c, node, BDK_CGXX_CMRX_CONFIG(cgx, lmac),
        c.s.int_beat_gen = is_internal);

    BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MRX_CONTROL(cgx, lmac),
        c.s.loopbck1 = is_internal);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx, lmac),
        c.s.loopbck2 = is_external);

    BDK_CSR_MODIFY(c, node, BDK_CGXX_SPUX_CONTROL1(cgx, lmac),
        c.s.loopbck = is_internal);
    BDK_CSR_MODIFY(c, node, BDK_CGXX_SMUX_EXT_LOOPBACK(cgx, lmac),
        c.s.en = is_external);
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
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    const int node = handle->node;
    const int cgx = handle->interface;
    const int lmac = handle->index;

    if (priv->flags & CGX_FLAGS_NO_NIX)
    {
        /* CNF95XX and LOKI CGX1+ can only be accessed by BPHY */
        BDK_CSR_INIT(rx_packets, node, BDK_CGXX_CMRX_RX_STAT0(cgx, lmac));
        BDK_CSR_INIT(rx_octets, node, BDK_CGXX_CMRX_RX_STAT1(cgx, lmac));
        //BDK_CSR_INIT(rx_pause, node, BDK_CGXX_CMRX_RX_STAT2(cgx, lmac));
        //BDK_CSR_INIT(rx_pause_octet, node, BDK_CGXX_CMRX_RX_STAT3(cgx, lmac));
        //BDK_CSR_INIT(rx_fifo_full, node, BDK_CGXX_CMRX_RX_STAT6(cgx, lmac));
        //BDK_CSR_INIT(rx_fifo_full_octets, node, BDK_CGXX_CMRX_RX_STAT7(cgx, lmac));
        BDK_CSR_INIT(rx_errors, node, BDK_CGXX_CMRX_RX_STAT8(cgx, lmac));

        BDK_CSR_INIT(tx_underflow, node, BDK_CGXX_CMRX_TX_STAT16(cgx, lmac));
        //BDK_CSR_INIT(tx_pause, node, BDK_CGXX_CMRX_TX_STAT17(cgx, lmac));
        BDK_CSR_INIT(tx_octets, node, BDK_CGXX_CMRX_TX_STAT4(cgx, lmac));
        BDK_CSR_INIT(tx_packets, node, BDK_CGXX_CMRX_TX_STAT5(cgx, lmac));

        handle->stats.rx.errors = bdk_update_stat_with_overflow(rx_errors.u, handle->stats.rx.errors, 48);
        handle->stats.rx.octets = bdk_update_stat_with_overflow(rx_octets.u, handle->stats.rx.octets, 48);
        handle->stats.rx.packets = bdk_update_stat_with_overflow(rx_packets.u, handle->stats.rx.packets, 48);

        handle->stats.tx.errors = bdk_update_stat_with_overflow(tx_underflow.u, handle->stats.tx.errors, 48);
        handle->stats.tx.octets = bdk_update_stat_with_overflow(tx_octets.u, handle->stats.tx.octets, 48);
        handle->stats.tx.packets = bdk_update_stat_with_overflow(tx_packets.u, handle->stats.tx.packets, 48);

        /* External loopback bypasses the RX counters, so fake them by copying the TX */
        BDK_CSR_INIT(ext_loopback, node, BDK_CGXX_SMUX_EXT_LOOPBACK(cgx, lmac));
        if (ext_loopback.s.en)
        {
            handle->stats.rx.octets = handle->stats.tx.octets;
            handle->stats.rx.packets = handle->stats.tx.packets;
        }
    }
    else
    {
        bdk_nix_fill_rx_stats(handle);
        bdk_nix_fill_tx_stats(handle);
    }

    /* RS-FEC */
    if (priv->flags & CGX_FLAGS_RS_FEC)
    {
        /* Must manually clear, non atomic */
        BDK_CSR_INIT(rsfec_corr, node, BDK_CGXX_SPUX_RSFEC_CORR(cgx, lmac));
        BDK_CSR_WRITE(node, BDK_CGXX_SPUX_RSFEC_CORR(cgx, lmac), 0);
        handle->stats.rsfec_corrected_errors += rsfec_corr.s.cw_cnt;

        /* Must manually clear, non atomic */
        BDK_CSR_INIT(rsfec_uncorr, node, BDK_CGXX_SPUX_RSFEC_UNCORR(cgx, lmac));
        BDK_CSR_WRITE(node, BDK_CGXX_SPUX_RSFEC_UNCORR(cgx, lmac), 0);
        handle->stats.rsfec_uncorrected_errors += rsfec_uncorr.s.cw_cnt;

        for (int lane = 0; lane < 4; lane++)
        {
            /* Must manually clear, non atomic */
            BDK_CSR_INIT(rsfec_err, node, BDK_CGXX_SPUX_FEC_LNX_RSFEC_ERR(cgx, lmac, lane));
            BDK_CSR_WRITE(node, BDK_CGXX_SPUX_FEC_LNX_RSFEC_ERR(cgx, lmac, lane), 0);
            handle->stats.rsfec_symbol_errors += rsfec_err.s.symb_err_cnt;
        }
    }

    /* FEC */
    if (priv->flags & CGX_FLAGS_FEC)
    {
        for (int lane = 0; lane < 20; lane++)
        {
            BDK_CSR_INIT(fec_corr, node, BDK_CGXX_SPUX_LNX_FEC_CORR_BLKS(cgx, lmac, lane));
            handle->stats.fec_corrected_errors += fec_corr.s.ln_corr_blks;

            BDK_CSR_INIT(fec_uncorr, node, BDK_CGXX_SPUX_LNX_FEC_UNCORR_BLKS(cgx, lmac, lane));
            handle->stats.fec_uncorrected_errors += fec_uncorr.s.ln_uncorr_blks;
        }
    }

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
    return priv->lane_mask;
}

static void if_link_set(bdk_if_handle_t handle, bdk_if_link_t link_info)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;

    const int cgx = handle->interface;
    const int lmac = handle->index;
    const int node = handle->node;

    if (priv->mode == CGX_MODE_SGMII && link_info.s.full_duplex)
    {
        /*
         * for now, only handle 1Gbit and 100Mbit SGMII full duplex cases
         */

        if ( link_info.s.speed == 100 )
        {
            BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx, lmac),
                           c.s.samp_pt = 5);
            BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_GMI_TXX_SLOT(cgx, lmac),
                c.s.slot = 64;);
            BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_GMI_PRTX_CFG(cgx, lmac),
                c.s.slottime = 0;c.s.speed=0;);
        }
        else if ( link_info.s.speed == 1000 )
        {
            BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_PCS_MISCX_CTL(cgx, lmac),
                           c.s.samp_pt = 1);
            BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_GMI_TXX_SLOT(cgx, lmac),
                c.s.slot = 512;);
            BDK_CSR_MODIFY(c, node, BDK_CGXX_GMP_GMI_PRTX_CFG(cgx, lmac),
                c.s.slottime = 1;c.s.speed=1;);
        }
    }
}

static int cgx_transmit(bdk_if_handle_t handle, const bdk_if_packet_t *packet, int repeat_count)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    if (priv->flags & CGX_FLAGS_NO_NIX)
        return 0;
    return bdk_nix_transmit(handle, packet, repeat_count);
}

static int cgx_get_queue_depth(bdk_if_handle_t handle)
{
    const cgx_priv_t *priv = (cgx_priv_t *)handle->priv;
    if (priv->flags & CGX_FLAGS_NO_NIX)
        return 0;
    return bdk_nix_get_queue_depth(handle);
}

const __bdk_if_ops_t __bdk_if_ops_cgx = {
    .priv_size = sizeof(cgx_priv_t),
    .if_num_interfaces = if_num_interfaces,
    .if_num_ports = if_num_ports,
    .if_probe = if_probe,
    .if_init = if_init,
    .if_link_get = if_link_get,
    .if_link_set = if_link_set,
    .if_transmit = cgx_transmit,
    .if_loopback = if_loopback,
    .if_get_queue_depth = cgx_get_queue_depth,
    .if_get_stats = if_get_stats,
    .if_get_lane_mask = if_get_lane_mask,
};

