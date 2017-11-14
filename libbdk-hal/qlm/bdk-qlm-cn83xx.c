/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
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
#include "bdk-qlm-common.h"
#include "libbdk-arch/bdk-csrs-bgx.h"
#include "libbdk-arch/bdk-csrs-gser.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-sata.h"

/**
 * Return the number of QLMs supported for the chip
 *
 * @return Number of QLMs
 */
static int qlm_get_num(bdk_node_t node)
{
    return 7; /* 4 QLM + 3 DLM */
}

/**
 * Return the number of lanes in a QLM. QLMs normally contain
 * 4 lanes, except for chips which only have half of a QLM.
 *
 * @param qlm    QLM to get lanes number for
 *
 * @return Number of lanes on the QLM
 */
static int qlm_get_lanes(bdk_node_t node, int qlm)
{
    if (qlm < 4)
        return 4; /* QLMs 0-3 */
    else
        return 2; /* DLMs 4-6 */
}

/**
 * Lookup the hardware QLM number for a given interface type and index. This
 * function will fail with a fatal error if called on invalid interfaces for
 * a chip. It returns the QLM number for an interface without checking to
 * see if the QLM is in the correct mode.
 *
 * @param iftype    Interface type
 * @param interface Interface index number
 *
 * @return QLM number. Dies on a fatal error on failure.
 */
static int qlm_get_qlm_num(bdk_node_t node, bdk_if_t iftype, int interface, int index)
{
    switch (iftype)
    {
        case BDK_IF_BGX:
        {
            if (bdk_is_platform(BDK_PLATFORM_EMULATOR)) {
                switch (interface)
                {
                    case 0: /* BGX0 connects to QLM2 */
                        return 2;
                    case 1: /* BGX1 connects to QLM3 */
                        return 3;
                    case 2: /* BGX2 connects to DLM5-6 */
                        return 5;
                    case 3: /* BGX3 connects to DLM4 */
                        return 4;
                    default:
                        return -1;
                }
            }
            int qlm;
            switch (interface)
            {
                case 0: /* BGX0 connects to QLM2 */
                    qlm = 2;
                    break;
                case 1: /* BGX1 connects to QLM3 */
                    qlm = 3;
                    break;
                case 2: /* BGX2 connects to DLM5, DLM6, or DLM5-6 */
                {
                    /* This BGX spans two DLMs. The index must be used to
                       figure out which DLM we are using */
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(5));
                    if (gserx_cfg.s.bgx)
                    {
                        if (gserx_cfg.s.bgx_quad) /* 4 lanes together */
                            qlm = 5;
                        else if (gserx_cfg.s.bgx_dual) /* 2 lanes together */
                            qlm = (index >= 1) ? 6 : 5;
                        else /* All lanes independent */
                        {
                            bdk_qlm_modes_t mode = bdk_qlm_get_mode(node, 5);
                            if (mode == BDK_QLM_MODE_QSGMII_4X1)
                                qlm = 5;
                            else if (mode <= BDK_QLM_MODE_PCIE_1X8)
                                qlm = 6;
                            else
                                qlm = (index >= 2) ? 6 : 5;
                        }
                    }
                    else
                        qlm = 6;
                    break;
                }
                case 3: /* BGX3 connects to DLM4 */
                    qlm = 4;
                    break;
                default:
                    return -1;
            }
            /* Make sure the QLM is powered up and out of reset */
            BDK_CSR_INIT(phy_ctl, node, BDK_GSERX_PHY_CTL(qlm));
            if (phy_ctl.s.phy_pd || phy_ctl.s.phy_reset)
                return -1;
            /* Make sure the QLM is in BGX mode */
            BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(qlm));
            if (gserx_cfg.s.bgx)
                return qlm;
            else
                return -1;
        }
        case BDK_IF_PCIE: /* PCIe */
        {
            if (bdk_is_platform(BDK_PLATFORM_EMULATOR)) {
                return -1;
            }
            switch (interface)
            {
                case 0: /* PEM0 */
                {
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(0));
                    if (gserx_cfg.s.pcie)
                        return 0; /* PEM0 is on QLM0 and possibly QLM1 */
                    else
                        return -1; /* PEM0 is disabled */
                }
                case 1: /* PEM1 */
                {
                    BDK_CSR_INIT(pem0_cfg, node, BDK_PEMX_CFG(0));
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(1));
                    if (!pem0_cfg.cn83xx.lanes8 && gserx_cfg.s.pcie)
                        return 1; /* PEM1 is on QLM 1 */
                    else
                        return -1; /* PEM1 is disabled */
                }
                case 2: /* PEM2 */
                {
                    BDK_CSR_INIT(pemx_qlm, node, BDK_PEMX_QLM(2));
                    if (pemx_qlm.s.pem_bdlm)
                    {
                        /* PEM2 is routed to DLM4 */
                        BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(4));
                        if (gserx_cfg.s.pcie)
                            return 4; /* PEM2 is on DLM4 */
                        else
                            return -1; /* PEM2 is disabled */
                    }
                    else
                    {
                        /* PEM2 is routed to QLM2 */
                        BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(2));
                        if (gserx_cfg.s.pcie)
                            return 2; /* PEM2 is on QLM2 and possibly QLM3 */
                        else
                            return -1; /* PEM2 is disabled */
                    }
                }
                case 3: /* PEM3 */
                {
                    BDK_CSR_INIT(pemx_qlm, node, BDK_PEMX_QLM(3));
                    if (pemx_qlm.s.pem_bdlm)
                    {
                        /* PEM3 is routed to DLM5 */
                        BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(5));
                        if (gserx_cfg.s.pcie)
                            return 5; /* PEM3 is on DLM5 */
                        else
                            return -1; /* PEM3 is disabled */
                    }
                    else
                    {
                        /* PEM3 is routed to QLM3 */
                        BDK_CSR_INIT(pem2_cfg, node, BDK_PEMX_CFG(2));
                        BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(3));
                        if (!pem2_cfg.cn83xx.lanes8 && gserx_cfg.s.pcie)
                            return 3; /* PEM3 is on QLM3 */
                        else
                            return -1; /* PEM3 is disabled */
                    }
                }
                default: /* Max of 4 PEMs, 0-3 */
                    return -1;
            }
        }
        default: /* Not supported by CN83XX */
            return -1;
    }
}

/**
 * Get the mode of a QLM as a human readable string
 *
 * @param qlm    QLM to examine
 *
 * @return String mode
 */
static bdk_qlm_modes_t qlm_get_mode(bdk_node_t node, int qlm)
{
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
    {
        if ((qlm == 2) || (qlm == 3))
            return BDK_QLM_MODE_XFI_4X1;
        else if ((qlm >= 4) && (qlm <= 6))
            return BDK_QLM_MODE_XFI_2X1;
        else if (qlm < 2)
            return BDK_QLM_MODE_PCIE_1X4;
        else
            return BDK_QLM_MODE_DISABLED;
    }
    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(qlm));
    if (gserx_cfg.s.pcie)
    {
        switch (qlm)
        {
            case 0: /* Either PEM0 x4 or PEM0 x8 */
            case 1: /* Either PEM0 x8 or PEM1 x4 */
            {
                BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(0));
                if (pemx_cfg.cn83xx.lanes8)
                    return BDK_QLM_MODE_PCIE_1X8;
                else
                    return BDK_QLM_MODE_PCIE_1X4;
            }
            case 2: /* Either PEM2 x4 or PEM2 x8 */
            {
                BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(2));
                if (pemx_cfg.cn83xx.lanes8)
                    return BDK_QLM_MODE_PCIE_1X8; /* PEM2 x8 */
                else
                    return BDK_QLM_MODE_PCIE_1X4; /* PEM2 x4 */
            }
            case 3: /* Either PEM2 x8 or PEM3 x4 */
            {
                /* Can be last 4 lanes of PEM2 */
                BDK_CSR_INIT(pem2_cfg, node, BDK_PEMX_CFG(2));
                if (pem2_cfg.cn83xx.lanes8)
                    return BDK_QLM_MODE_PCIE_1X8; /* PEM2 x8 */
                /* Can be 4 lanes of PEM3 */
                return BDK_QLM_MODE_PCIE_1X4; /* PEM3 x4 */
            }
            case 4: /* PEM2 x2 */
                return BDK_QLM_MODE_PCIE_1X2; /* PEM2 x2 */
            case 5: /* PEM3 x2 or PEM3 x4 */
            {
                BDK_CSR_INIT(pem3_cfg, node, BDK_PEMX_CFG(3));
                if (pem3_cfg.cn83xx.lanes8)
                    return BDK_QLM_MODE_PCIE_1X4; /* PEM3 x4 */
                else
                    return BDK_QLM_MODE_PCIE_1X2; /* PEM3 x2 */
            }
            case 6: /* PEM3 x4 */
                return BDK_QLM_MODE_PCIE_1X4; /* PEM3 x4 */
            default:
                return BDK_QLM_MODE_DISABLED;
        }
    }
    else if (gserx_cfg.s.bgx)
    {
        int bgx;
        int bgx_index;
        switch (qlm)
        {
            case 2:
                bgx = 0;
                bgx_index = 0;
                break;
            case 3:
                bgx = 1;
                bgx_index = 0;
                break;
            case 4:
                bgx = 3;
                bgx_index = 0;
                break;
            case 5:
            case 6:
                bgx = 2;
                bgx_index = (qlm == 5) ? 0 : 2;
                if (qlm == 5)
                {
                    /* Special check for RXAUI in DLM5. If DLM6 is XFI and there
                       is no RGMII, BGX will overwrite index 1 with XFI's mode
                       and RGMII will be shown in index 0 */
                    BDK_CSR_INIT(cmrx_config, node, BDK_BGXX_CMRX_CONFIG(bgx, 0));
                    if (cmrx_config.s.lmac_type == 0x2)
                        bgx_index=0;
                }
                break;
            default:
                return BDK_QLM_MODE_DISABLED;
        }
        BDK_CSR_INIT(cmrx_config, node, BDK_BGXX_CMRX_CONFIG(bgx, bgx_index));
        bool is_kr = __bdk_qlm_is_lane_kr(node, qlm, 0);
        switch (cmrx_config.s.lmac_type)
        {
            case 0x0: return (bgx >= 2) ? BDK_QLM_MODE_SGMII_2X1 : BDK_QLM_MODE_SGMII_4X1;
            case 0x1: return BDK_QLM_MODE_XAUI_1X4; /* Doesn't differntiate between XAUI and DXAUI */
            case 0x2: return (bgx >= 2) ? BDK_QLM_MODE_RXAUI_1X2 : BDK_QLM_MODE_RXAUI_2X2;
            case 0x3:
                if (is_kr)
                    return (bgx >= 2) ? BDK_QLM_MODE_10G_KR_2X1 : BDK_QLM_MODE_10G_KR_4X1;
                else
                    return (bgx >= 2) ? BDK_QLM_MODE_XFI_2X1 : BDK_QLM_MODE_XFI_4X1;
            case 0x4:
                if (is_kr)
                    return BDK_QLM_MODE_40G_KR4_1X4;
                else
                    return BDK_QLM_MODE_XLAUI_1X4;
            case 0x6: return BDK_QLM_MODE_QSGMII_4X1;
            default:  return BDK_QLM_MODE_DISABLED;
        }
    }
    else if (gserx_cfg.s.sata)
        return BDK_QLM_MODE_SATA_2X1;
    else
        return BDK_QLM_MODE_DISABLED;
}

static int qlm_set_sata(bdk_node_t node, int qlm, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    /* SATA has a fixed mapping for ports on CN83XX */
    int sata_port;
    switch (qlm)
    {
        case 4: /* SATA 0-1 = DLM4 lanes 0-1 */
            sata_port = 0;
            break;
        case 5: /* SATA 2-3 = DLM5 lanes 0-1 */
            sata_port = 2;
            break;
        case 6: /* SATA 4-5 = DLM6 lanes 0-1 */
            sata_port = 4;
            break;
        default:
            bdk_error("Attempted to configure SATA on QLM that doesn't support it\n");
            return -1;
    }
    return __bdk_qlm_set_sata_cn8xxx(node, qlm, baud_mhz, sata_port, sata_port + 1);
}

/**
 * The SDK expects unused BGX LMACs to have DMAC_CTL=0. This is only needed on
 * BGX that have no way for software to determine the in use LMACs. For CN83XX,
 * this is most important on DLM4, BGX3.
 *
 * @param node   Node to setup
 * @param bgx    BGX to update
 * @param num_used_ports
 *               Number of BGX in use
 */
static void disable_unused_bgx(bdk_node_t node, int bgx, int num_used_ports)
{
    /* Create a variable that contains the default DMAC control setup */
    BDK_CSR_DEFINE(dmac_ctl, BDK_BGXX_CMRX_RX_DMAC_CTL(0, 0));
    dmac_ctl.u = 0;
    dmac_ctl.s.mcst_mode = 1;
    dmac_ctl.s.bcst_accept = 1;

    /* Mark used ports with the DMAC_CTL default and unused ports with zero */
    for (int index = 0; index < 4; index++)
    {
        uint64_t v = (index < num_used_ports) ? dmac_ctl.u : 0;
        BDK_CSR_WRITE(node, BDK_BGXX_CMRX_RX_DMAC_CTL(bgx, index), v);
    }
}

/**
 * For chips that don't use pin strapping, this function programs
 * the QLM to the specified mode
 *
 * @param node     Node to use in a Numa setup
 * @param qlm      QLM to configure
 * @param mode     Desired mode
 * @param baud_mhz Desired speed
 * @param flags    Flags to specify mode specific options
 *
 * @return Zero on success, negative on failure
 */
static int qlm_set_mode(bdk_node_t node, int qlm, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return -1;

    int lane_mode = 0xf;
    int lmac_type = -1;
    int is_pcie = 0;
    int is_sata = 0;
    int is_ilk = 0;
    int is_bgx = 0;
    int bgx_block;
    int bgx_index;

    switch (qlm)
    {
        case 2:
            bgx_block = 0;
            bgx_index = 0;
            break;
        case 3:
            bgx_block = 1;
            bgx_index = 0;
            break;
        case 4:
            bgx_block = 3;
            bgx_index = 0;
            break;
        case 5 ... 6:
            bgx_block = 2;
            bgx_index = (qlm == 5) ? 0 : 2;
            break;
        default:
            bgx_block = -1;
            bgx_index = -1;
            break;
    }

    int measured_ref = bdk_qlm_measure_clock(node, qlm);
    int ref_clk = (mode == BDK_QLM_MODE_DISABLED) ? 0 : __bdk_qlm_round_refclock(node, qlm, measured_ref);
    int kr_mode = 0;

    switch (mode)
    {
        case BDK_QLM_MODE_PCIE_1X2:
        case BDK_QLM_MODE_PCIE_1X4:
        case BDK_QLM_MODE_PCIE_1X8:
        {
            /* Note: PCIe ignores baud_mhz. Use the GEN 1/2/3 flags
               to control speed */
            is_pcie = 1;
            if (ref_clk == REF_100MHZ)
            {
                BDK_CSR_MODIFY(c, node, BDK_GSERX_REFCLK_SEL(qlm),
                    c.s.pcie_refclk125 = 0);
                if (baud_mhz == 2500)
                    lane_mode = BDK_GSER_LMODE_E_R_25G_REFCLK100;
                else if (baud_mhz == 5000)
                    lane_mode = BDK_GSER_LMODE_E_R_5G_REFCLK100;
                else
                    lane_mode = BDK_GSER_LMODE_E_R_8G_REFCLK100;
            }
            else if (ref_clk == REF_125MHZ)
            {
                BDK_CSR_MODIFY(c, node, BDK_GSERX_REFCLK_SEL(qlm),
                    c.s.pcie_refclk125 = 1);
                if (baud_mhz == 2500)
                    lane_mode = BDK_GSER_LMODE_E_R_25G_REFCLK125;
                else if (baud_mhz == 5000)
                    lane_mode = BDK_GSER_LMODE_E_R_5G_REFCLK125;
                else
                    lane_mode = BDK_GSER_LMODE_E_R_8G_REFCLK125;
            }
            else
            {
                bdk_error("Invalid reference clock for PCIe on QLM%d\n", qlm);
                return -1;
            }
            int cfg_md;
            if (baud_mhz == 2500)
                cfg_md = 0; /* Gen1 Speed */
            else if (baud_mhz == 5000)
                cfg_md = 1; /* Gen2 Speed */
            else
                cfg_md = 2; /* Gen3 Speed */
            switch (qlm)
            {
                case 0: /* Either x4 or x8 based on PEM0 */
                    BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(0),
                        c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                    __bdk_qlm_setup_pem_reset(node, 0, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(0),
                        c.cn83xx.lanes8 = (mode == BDK_QLM_MODE_PCIE_1X8);
                        c.cn83xx.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        c.cn83xx.md = cfg_md);
                    break;
                case 1: /* Either PEM0 x8 or PEM1 x4 */
                    if (mode == BDK_QLM_MODE_PCIE_1X8)
                    {
                        /* Last 4 lanes of PEM0 */
                        /* PEMX_CFG already setup */
                    }
                    else
                    {
                        /* Four lanes for PEM1 */
                        BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(1),
                            c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                        __bdk_qlm_setup_pem_reset(node, 1, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(1),
                            c.cn83xx.lanes8 = 0;
                            c.cn83xx.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                            c.cn83xx.md = cfg_md);
                    }
                    break;
                case 2: /* Either PEM2 x4 or PEM2 x8 */
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_QLM(2),
                        c.s.pem_bdlm = 0); /* PEM2 is on QLM2 */
                    BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(2),
                        c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                    __bdk_qlm_setup_pem_reset(node, 2, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(2),
                        c.cn83xx.lanes8 = (mode == BDK_QLM_MODE_PCIE_1X8);
                        c.cn83xx.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        c.cn83xx.md = cfg_md);
                    /* GSER5 can't be PCIe */
                    BDK_CSR_MODIFY(c, node, BDK_GSERX_CFG(5), c.s.pcie = 0);
                    break;
                case 3: /* Either PEM2 x8, or PEM3 x4 */
                {
                    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(2));
                    if (pemx_cfg.cn83xx.lanes8)
                    {
                        /* Last 4 lanes of PEM2 */
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_QLM(3),
                            c.s.pem_bdlm = 1); /* PEM3 can only be on DLM6 */
                        /* PEMX_CFG already setup */
                    }
                    else
                    {
                        /* Four lanes of PEM3 */
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_QLM(3),
                            c.s.pem_bdlm = 0); /* PEM3 is on QLM3 */
                        BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(3),
                            c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                        __bdk_qlm_setup_pem_reset(node, 3, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(3),
                            c.cn83xx.lanes8 = 0;
                            c.cn83xx.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                            c.cn83xx.md = cfg_md);
                        /* GSER5-6 can't be PCIe */
                        BDK_CSR_MODIFY(c, node, BDK_GSERX_CFG(5), c.s.pcie = 0);
                        BDK_CSR_MODIFY(c, node, BDK_GSERX_CFG(6), c.s.pcie = 0);
                    }
                    break;
                }
                case 4: /* PEM2 x2 on DLM4 */
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_QLM(2),
                        c.s.pem_bdlm = 1); /* PEM2 is on DLM4 */
                    BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(2),
                        c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                    __bdk_qlm_setup_pem_reset(node, 2, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(2),
                        c.cn83xx.lanes8 = 0;
                        c.cn83xx.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        c.cn83xx.md = cfg_md);
                    /* GSER2 can't be PCIe */
                    BDK_CSR_MODIFY(c, node, BDK_GSERX_CFG(2), c.s.pcie = 0);
                    break;
                case 5: /* PEM3 x2 on DLM5 or x4 on DLM5-6 */
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_QLM(3),
                        c.s.pem_bdlm = 1); /* PEM3 is on DLM5 */
                    BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(3),
                        c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                    __bdk_qlm_setup_pem_reset(node, 3, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(3),
                        c.cn83xx.lanes8 = (mode == BDK_QLM_MODE_PCIE_1X4);
                        c.cn83xx.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        c.cn83xx.md = cfg_md);
                    /* GSER3 can't be PCIe unless pem2 is x8 */
                    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(2));
                    if (!pemx_cfg.cn83xx.lanes8)
                        BDK_CSR_MODIFY(c, node, BDK_GSERX_CFG(3), c.s.pcie = 0);
                    break;
                case 6: /* PEM3 x4 on DLM5-6 */
                    /* PEMX_CFG already setup */
                    break;
                default:
                    return -1;
            }
            break;
        }
        case BDK_QLM_MODE_SGMII_4X1:
        case BDK_QLM_MODE_SGMII_2X1:
            if (qlm == 4)
                disable_unused_bgx(node, bgx_block, 2);
            lmac_type = 0; /* SGMII */
            is_bgx = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("SGMII", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_XAUI_1X4:
            disable_unused_bgx(node, bgx_block, 1);
            lmac_type = 1; /* XAUI */
            is_bgx = 5;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("XAUI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_RXAUI_2X2:
        case BDK_QLM_MODE_RXAUI_1X2:
            if (qlm == 4)
                disable_unused_bgx(node, bgx_block, 1);
            lmac_type = 2; /* RXAUI */
            is_bgx = 3;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("RXAUI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_XFI_4X1:
        case BDK_QLM_MODE_XFI_2X1:
            if (qlm == 4)
                disable_unused_bgx(node, bgx_block, 2);
            lmac_type = 3; /* 10G_R */
            is_bgx = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("XFI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_XLAUI_1X4:
            disable_unused_bgx(node, bgx_block, 1);
            lmac_type = 4; /* 40G_R */
            is_bgx = 5;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("XLAUI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_10G_KR_4X1:
        case BDK_QLM_MODE_10G_KR_2X1:
            if (qlm == 4)
                disable_unused_bgx(node, bgx_block, 2);
            lmac_type = 3; /* 10G_R */
            is_bgx = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("10G-KR", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            kr_mode = 1;
            break;
        case BDK_QLM_MODE_40G_KR4_1X4:
            disable_unused_bgx(node, bgx_block, 1);
            lmac_type = 4; /* 40G_R */
            is_bgx = 5;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("40G-KR", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            kr_mode = 1;
            break;
        case BDK_QLM_MODE_QSGMII_4X1:
            disable_unused_bgx(node, bgx_block, 4);
            lmac_type = 6; /* QSGMII */
            is_bgx = 1;
            lane_mode = BDK_GSER_LMODE_E_R_5G_REFCLK15625_QSGMII;
            break;
        case BDK_QLM_MODE_SATA_2X1:
        case BDK_QLM_MODE_SATA_4X1:
            BDK_CSR_MODIFY(c, node, BDK_GSERX_LANE_MODE(qlm), c.s.lmode = BDK_GSER_LMODE_E_R_8G_REFCLK100);
            /* SATA initialization is different than BGX. Call its init function
               and skip the rest of this routine */
            return qlm_set_sata(node, qlm, mode, baud_mhz, flags);
        case BDK_QLM_MODE_DISABLED:
            /* Set gser for the interface mode */
            BDK_CSR_MODIFY(c, node, BDK_GSERX_CFG(qlm),
                c.u = 0);
            /* Put the PHY in reset */
            BDK_CSR_MODIFY(c, node, BDK_GSERX_PHY_CTL(qlm),
                c.s.phy_reset = 1);
            return 0;
        default:
            bdk_error("Unsupported QLM mode %d\n", mode);
            return -1;
    }

    /* For some non-obvious reason DLM6 LMODE msut be programmed before DLM5
       is brought up when it is half of a BGX single port */
    if ((qlm == 5) && ((mode == BDK_QLM_MODE_XAUI_1X4) ||
                       (mode == BDK_QLM_MODE_XLAUI_1X4) ||
                       (mode == BDK_QLM_MODE_40G_KR4_1X4)))
    {
        BDK_CSR_WRITE(node, BDK_GSERX_REFCLK_SEL(qlm + 1),
            BDK_CSR_READ(node, BDK_GSERX_REFCLK_SEL(qlm)));
        BDK_CSR_MODIFY(c, node, BDK_GSERX_LANE_MODE(qlm + 1),
            c.s.lmode = lane_mode);
    }

    /* Power up phy, but keep it in reset */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_PHY_CTL(qlm),
        c.s.phy_pd = 0;
        c.s.phy_reset = 1);

    /* Set gser for the interface mode */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_CFG(qlm),
        c.s.sata = is_sata;
        c.s.ila = is_ilk;
        c.s.bgx = is_bgx & 1;
        c.s.bgx_quad = (is_bgx >> 2) & 1;
        c.s.bgx_dual = (is_bgx >> 1) & 1;
        c.s.pcie = is_pcie);

    /* Lane mode */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANE_MODE(qlm),
        c.s.lmode = lane_mode);

    /* LMAC type. We only program one port as the full setup is done in BGX */
    if (lmac_type != -1)
    {
        BDK_CSR_MODIFY(c, node, BDK_BGXX_CMRX_CONFIG(bgx_block, bgx_index),
            c.s.enable = 0;
            c.s.lmac_type = lmac_type);
    }

    /* Bring phy out of reset */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_PHY_CTL(qlm),
        c.s.phy_reset = 0);

    /* Wait 1us until the management interface is ready to accept
       read/write commands.*/
    bdk_wait_usec(1);

    /* Configure the gser pll */
    __bdk_qlm_init_mode_table(node, qlm, ref_clk);

    /* Remember which lanes are using KR over BGX */
    if (is_bgx)
    {
        int num_lanes = bdk_qlm_get_lanes(node, qlm);
        for (int lane = 0; lane < num_lanes; lane++)
            __bdk_qlm_set_lane_kr(node, qlm, lane, kr_mode);
    }

    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        /* Wait for reset to complete and the PLL to lock */
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERX_PLL_STAT(qlm), pll_lock, ==, 1, 10000))
        {
            bdk_error("QLM%d: Timeout waiting for GSERX_PLL_STAT[pll_lock]\n", qlm);
            return -1;
        }

        /* PCIe mode doesn't become ready until the PEM block attempts to bring
           the interface up. Skip this check for PCIe */
        if (!is_pcie && BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERX_QLM_STAT(qlm), rst_rdy, ==, 1, 10000))
        {
            bdk_error("QLM%d: Timeout waiting for GSERX_QLM_STAT[rst_rdy]\n", qlm);
            return -1;
        }
    }

    /* cdrlock will be checked in the BGX */

    /* Errata (GSER-27140) SERDES temperature drift sensitivity in receiver */
    int channel_loss = bdk_config_get_int(BDK_CONFIG_QLM_CHANNEL_LOSS, node, qlm);
    __bdk_qlm_errata_gser_27140(node, qlm, baud_mhz, channel_loss);

    /* Apply any custom tuning */
    __bdk_qlm_tune(node, qlm, mode, baud_mhz);

    /* If we're setting up the first QLM of a PCIe x8 interface, go ahead and
       setup the other inteface automatically */
    if (mode == BDK_QLM_MODE_PCIE_1X8)
    {
        switch (qlm)
        {
            case 0:
            case 2:
                /* Use the same reference clock for the second QLM */
                BDK_CSR_WRITE(node, BDK_GSERX_REFCLK_SEL(qlm + 1),
                    BDK_CSR_READ(node, BDK_GSERX_REFCLK_SEL(qlm)));
                return bdk_qlm_set_mode(node, qlm + 1, mode, baud_mhz, flags);
        }
    }

    /* If we're setting up the first DLM of a 4 lane interface on DLM5-6, go
       ahead and setup the other inteface automatically */
    if ((qlm == 5) && ((mode == BDK_QLM_MODE_XAUI_1X4) ||
                       (mode == BDK_QLM_MODE_XLAUI_1X4) ||
                       (mode == BDK_QLM_MODE_40G_KR4_1X4) ||
                       (mode == BDK_QLM_MODE_PCIE_1X4)))
    {
        /* Use the same reference clock for the second DLM */
        BDK_CSR_WRITE(node, BDK_GSERX_REFCLK_SEL(qlm + 1),
            BDK_CSR_READ(node, BDK_GSERX_REFCLK_SEL(qlm)));
        return bdk_qlm_set_mode(node, qlm + 1, mode, baud_mhz, flags);
    }

    return 0;
}

/**
 * Get the speed (Gbaud) of the QLM in Mhz.
 *
 * @param qlm    QLM to examine
 *
 * @return Speed in Mhz
 */
static int qlm_get_gbaud_mhz(bdk_node_t node, int qlm)
{
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return 10312;

    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(qlm));
    if (gserx_cfg.u == 0)
        return 0;
    if (gserx_cfg.s.pcie)
    {
        /* QLMs in PCIe mode ignore LMODE and get their speed from
           the PEM block that controls them */
        int pem;
        switch (qlm)
        {
            case 0: /* Either PEM0 x4 or PEM0 x8 */
                pem = 0;
                break;
            case 1: /* Either PEM0 x8 or PEM1 x4 */
            {
                BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(0));
                if (pemx_cfg.cn83xx.lanes8)
                    pem = 0;
                else
                    pem = 1;
                break;
            }
            case 2: /* Either PEM2 x4 or PEM2 x8 */
                pem = 2;
                break;
            case 3: /* Either PEM2 x8 or PEM3 x4 */
            {
                /* Can be last 4 lanes of PEM2 */
                BDK_CSR_INIT(pem2_cfg, node, BDK_PEMX_CFG(2));
                if (pem2_cfg.cn83xx.lanes8)
                {
                    pem = 2;
                }
                else
                {
                    /* Not last 4 lanes of PEM2, so should surely be PEM3 */
                    pem = 3;
                }
                break;
            }
            case 4: /* PEM2 x2 */
                pem = 2;
                break;
            case 5: /* PEM3 x2 or x4 */
                pem = 3;
                break;
            case 6: /* PEM3 x4 */
                pem = 3;
                break;
            default:
                bdk_fatal("QLM%d: In PCIe mode, which shouldn't happen\n", qlm);
        }
        return __bdk_qlm_get_gbaud_mhz_pem(node, pem);
    }
    else if (gserx_cfg.s.sata)
    {
        int sata;
        switch (qlm)
        {
            case 4:
                sata = 0;
                break;
            case 5:
                sata = 2;
                break;
            case 6:
                sata = 4;
                break;
            default:
                return 0;
        }
        BDK_CSR_INIT(sata_uctl_ctl, node, BDK_SATAX_UCTL_CTL(sata));
        if (!sata_uctl_ctl.s.a_clk_en)
            return 0;
        BDK_CSR_INIT(sctl, node, BDK_SATAX_UAHC_P0_SCTL(sata));
        switch (sctl.s.spd)
        {
            case 1: return 1500;
            case 2: return 3000;
            case 3: return 6000;
            default: return 6000; /* No limit, assume 6G */
        }
    }
    else
        return __bdk_qlm_get_gbaud_mhz_lmode(node, qlm);
}

/**
 * Initialize the QLM layer
 */
static void qlm_init(bdk_node_t node)
{
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return;

    /* Setup how each PEM drives the PERST lines */
    for (int pem = 0; pem < 4; pem++)
    {
        BDK_CSR_INIT(rst_ctlx, node, BDK_RST_CTLX(pem));
        __bdk_qlm_setup_pem_reset(node, pem, !rst_ctlx.s.host_mode);
    }
}

/* Each chip has its own QLM operation table */
const bdk_qlm_ops_t bdk_qlm_ops_cn83xx = {
    .chip_model = CAVIUM_CN83XX,
    .init = qlm_init,
    .get_num = qlm_get_num,
    .get_lanes = qlm_get_lanes,
    .get_mode = qlm_get_mode,
    .set_mode = qlm_set_mode,
    .get_gbaud_mhz = qlm_get_gbaud_mhz,
    .measure_refclock = __bdk_qlm_measure_refclock,
    .get_qlm_num = qlm_get_qlm_num,
    .reset = __bdk_qlm_reset,
    .enable_prbs = __bdk_qlm_enable_prbs,
    .disable_prbs = __bdk_qlm_disable_prbs,
    .get_prbs_errors = __bdk_qlm_get_prbs_errors,
    .inject_prbs_error = __bdk_qlm_inject_prbs_error,
    .enable_loop = __bdk_qlm_enable_loop,
    .auto_config = bdk_qlm_mcu_auto_config,
    .tune_lane_tx = __bdk_qlm_tune_lane_tx,
    .rx_equalization = __bdk_qlm_rx_equalization,
    .eye_capture = __bdk_qlm_eye_capture_cn8xxx,
};

