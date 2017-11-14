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
    return 14; /* 8 QLM + 6 OCI */
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
    return 4; /* All are 4 lanes each */
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
            if (interface >= 2)
                return -1;
            /* Figure out which QLM the BGX connects to */
            int qlm = interface;
            if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
                return qlm;

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
            if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
                return -1;
            switch (interface)
            {
                case 0: /* PEM0 */
                {
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(2));
                    if (gserx_cfg.s.pcie)
                        return 2; /* PEM0 is on QLM2 (x4) and possibly QLM3 (x8) */
                    else
                        return -1; /* PEM0 is disabled */
                }
                case 1: /* PEM1 */
                {
                    BDK_CSR_INIT(pem0_cfg, node, BDK_PEMX_CFG(0));
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(3));
                    if (!pem0_cfg.cn88xx.lanes8 && gserx_cfg.s.pcie)
                        return 3; /* PEM1 is on QLM 3 (x4) */
                    else
                        return -1; /* PEM1 is disabled */
                }
                case 2: /* PEM2 */
                {
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(4));
                    if (gserx_cfg.s.pcie)
                        return 4; /* PEM2 is on QLM4 (x4) and possibly QLM5 (x8) */
                    else
                        return -1; /* PEM2 is disabled */
                }
                case 3: /* PEM3 */
                {
                    BDK_CSR_INIT(pem2_cfg, node, BDK_PEMX_CFG(2));
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(5));
                    if (!pem2_cfg.cn88xx.lanes8 && gserx_cfg.s.pcie)
                        return 5; /* PEM3 is on QLM5 (x4) */
                    else
                        return -1; /* PEM3 is disabled */
                }
                case 4: /* PEM4 */
                {
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(6));
                    if (gserx_cfg.s.pcie)
                        return 6; /* PEM4 is on QLM6 (x4) and possibly QLM7 (x8) */
                    else
                        return -1; /* PEM4 is disabled */
                }
                case 5: /* PEM5 */
                {
                    BDK_CSR_INIT(pem4_cfg, node, BDK_PEMX_CFG(4));
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(7));
                    if (!pem4_cfg.cn88xx.lanes8 && gserx_cfg.s.pcie)
                        return 7; /* PEM5 is on QLM7 (x4) */
                    else
                        return -1; /* PEM5 is disabled */
                }
                default: /* Max of 6 PEMs, 0-5 */
                    return -1;
            }
        }
        default: /* Not supported by CN88XX */
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
    if (qlm < 8)
    {
        if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        {
            if (qlm < 2)
                return BDK_QLM_MODE_XLAUI_1X4;
            else
                return BDK_QLM_MODE_DISABLED;
        }
        BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(qlm));
        if (gserx_cfg.s.pcie)
        {
            switch (qlm)
            {
                case 2: /* Either PEM0 x4 or PEM0 x8 */
                case 3: /* Either PEM0 x8 or PEM1 x4 */
                {
                    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(0));
                    if (pemx_cfg.cn88xx.lanes8)
                        return BDK_QLM_MODE_PCIE_1X8; /* PEM0 x8 */
                    else
                        return BDK_QLM_MODE_PCIE_1X4; /* PEM0-1 x4 */
                }
                case 4: /* Either PEM2 x4 or PEM2 x8 */
                case 5: /* Either PEM2 x8 or PEM3 x4 */
                {
                    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(2));
                    if (pemx_cfg.cn88xx.lanes8)
                        return BDK_QLM_MODE_PCIE_1X8; /* PEM2 x8 */
                    else
                        return BDK_QLM_MODE_PCIE_1X4; /* PEM2-3 x4 */
                }
                case 6: /* Either PEM4 x8 or PEM4 x4 */
                case 7: /* Either PEM4 x8 or PEM5 x4 */
                {
                    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(4));
                    if (pemx_cfg.cn88xx.lanes8)
                        return BDK_QLM_MODE_PCIE_1X8; /* PEM4 x8 */
                    else
                        return BDK_QLM_MODE_PCIE_1X4; /* PEM4-5 x4 */
                }
                default: /* QLMs 0-1 can't be PCIe */
                    return BDK_QLM_MODE_DISABLED;
            }
        }
        else if (gserx_cfg.s.ila)
            return BDK_QLM_MODE_ILK;
        else if (gserx_cfg.s.sata)
        {
            /* Hardcode SATA to QLM mapping for CN88XX */
            int sata = (qlm >= 6) ? 8 + (qlm-6) * 4 : (qlm-2) * 4;
            BDK_CSR_INIT(uctl_ctl, node, BDK_SATAX_UCTL_CTL(sata));
            if (uctl_ctl.s.a_clk_en && !uctl_ctl.s.a_clkdiv_rst)
                return cavium_is_altpkg(CAVIUM_CN88XX) ? BDK_QLM_MODE_SATA_2X1 : BDK_QLM_MODE_SATA_4X1;
            else
                return BDK_QLM_MODE_DISABLED;
        }
        else if (gserx_cfg.s.bgx)
        {
            if (qlm >= 2)
                return BDK_QLM_MODE_DISABLED;
            int bgx_block = qlm;
            BDK_CSR_INIT(cmrx_config, node, BDK_BGXX_CMRX_CONFIG(bgx_block, 0));
            bool is_kr = __bdk_qlm_is_lane_kr(node, qlm, 0);
            switch (cmrx_config.s.lmac_type)
            {
                case 0x0: return BDK_QLM_MODE_SGMII_4X1;
                case 0x1: return BDK_QLM_MODE_XAUI_1X4; /* Doesn't differentiate between XAUI and DXAUI */
                case 0x2: return BDK_QLM_MODE_RXAUI_2X2;
                case 0x3:
                    if (is_kr)
                        return BDK_QLM_MODE_10G_KR_4X1;
                    else
                        return BDK_QLM_MODE_XFI_4X1;
                case 0x4:
                    if (is_kr)
                        return BDK_QLM_MODE_40G_KR4_1X4;
                    else
                        return BDK_QLM_MODE_XLAUI_1X4;
                default:  return BDK_QLM_MODE_DISABLED;
            }
        }
        else
            return BDK_QLM_MODE_DISABLED;
    }
    else
        return BDK_QLM_MODE_OCI;
}

static int qlm_set_sata(bdk_node_t node, int qlm, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    /* SATA has a fixed mapping for ports on CN88XX */
    int sata_port;
    switch (qlm)
    {
        case 2: /* SATA 0-3 = QLM2 lanes 0-3 */
            sata_port = 0;
            break;
        case 3: /* SATA 4-7 = QLM3 lanes 0-3 */
            sata_port = 4;
            break;
        case 6: /* SATA 8-11 = QLM6 lanes 0-3 */
            sata_port = 8;
            break;
        case 7: /* SATA 12-15 = QLM7 lanes 0-3 */
            sata_port = 12;
            break;
        default:
            bdk_error("Attempted to configure SATA on QLM that doesn't support it\n");
            return -1;
    }
    return __bdk_qlm_set_sata_cn8xxx(node, qlm, baud_mhz, sata_port, sata_port + 3);
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
    int bgx_block = (qlm < 2) ? qlm : -1;

    /* Disable QLMs that are affected by the QLM we're working on */
    switch (qlm)
    {
        case 2:
        case 4:
        case 6:
            /* When reconfiguring QLM that are the first of 8 pcie lanes, disable the
               second set as their config will change too */
            if ((mode != BDK_QLM_MODE_PCIE_1X8) &&
                (qlm_get_mode(node, qlm + 1) == BDK_QLM_MODE_PCIE_1X8))
                BDK_CSR_WRITE(node, BDK_GSERX_CFG(qlm + 1), 0);
            break;
        case 3:
        case 5:
        case 7:
            /* When reconfiguring QLM that are the second of 8 pcie lanes, disable the
               first set as their config will change too */
            if ((mode != BDK_QLM_MODE_PCIE_1X8) &&
                (qlm_get_mode(node, qlm - 1) == BDK_QLM_MODE_PCIE_1X8))
                BDK_CSR_WRITE(node, BDK_GSERX_CFG(qlm - 1), 0);
            break;
    }

    int measured_ref = bdk_qlm_measure_clock(node, qlm);
    int ref_clk = (mode == BDK_QLM_MODE_DISABLED) ? 0 : __bdk_qlm_round_refclock(node, qlm, measured_ref);
    int kr_mode = 0;

    switch (mode)
    {
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
                case 2: /* Either x4 or x8 based on PEM0 */
                    BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(0),
                        c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                    __bdk_qlm_setup_pem_reset(node, 0, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(0),
                        c.cn88xx.lanes8 = (mode == BDK_QLM_MODE_PCIE_1X8);
                        //c.s.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        c.cn88xx.md = cfg_md);
                    break;
                case 3: /* Either PEM0 x8 or PEM1 x4 */
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
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(0),
                            c.cn88xx.lanes8 = 0);
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(1),
                            c.cn88xx.lanes8 = 0;
                            //c.s.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                            c.cn88xx.md = cfg_md);
                    }
                    break;
                case 4: /* Either PEM2 x4 or PEM2 x8 */
                    BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(2),
                        c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                    __bdk_qlm_setup_pem_reset(node, 2, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(2),
                        c.cn88xx.lanes8 = (mode == BDK_QLM_MODE_PCIE_1X8);
                        //c.s.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        c.cn88xx.md = cfg_md);
                    break;
                case 5: /* Either PEM2 x8, or PEM3 x4 */
                {
                    if (mode == BDK_QLM_MODE_PCIE_1X8)
                    {
                        /* Last 4 lanes of PEM2 */
                        /* PEMX_CFG already setup */
                    }
                    else
                    {
                        /* Four lanes of PEM3 */
                        BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(3),
                            c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                        __bdk_qlm_setup_pem_reset(node, 3, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(2),
                            c.cn88xx.lanes8 = 0);
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(3),
                            c.cn88xx.lanes8 = 0;
                            //c.s.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                            c.cn88xx.md = cfg_md);
                    }
                    break;
                }
                case 6: /* Either PEM4 x4 or PEM4 x8 */
                    BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(4),
                        c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                    __bdk_qlm_setup_pem_reset(node, 4, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(4),
                        c.cn88xx.lanes8 = (mode == BDK_QLM_MODE_PCIE_1X8);
                        //c.s.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        c.cn88xx.md = cfg_md);
                    break;
                case 7: /* PEM4 x8 */
                    if (mode == BDK_QLM_MODE_PCIE_1X8)
                    {
                        /* Last 4 lanes of PEM4 */
                        /* PEMX_CFG already setup */
                    }
                    else
                    {
                        /* Four lanes of PEM5 */
                        BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(5),
                            c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                        __bdk_qlm_setup_pem_reset(node, 5, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(4),
                            c.cn88xx.lanes8 = 0);
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(5),
                            c.cn88xx.lanes8 = 0;
                            //c.s.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                            c.cn88xx.md = cfg_md);
                    }
                    break;
                default:
                    return -1;
            }
            break;
        }
        case BDK_QLM_MODE_ILK:
            is_ilk = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("ILK", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_SATA_2X1: /* Used by CN86XX MCU */
        case BDK_QLM_MODE_SATA_4X1:
            BDK_CSR_MODIFY(c, node, BDK_GSERX_LANE_MODE(qlm), c.s.lmode = BDK_GSER_LMODE_E_R_8G_REFCLK100);
            /* SATA initialization is different than BGX. Call its init function
               and skip the rest of this routine */
            return qlm_set_sata(node, qlm, mode, baud_mhz, flags);
        case BDK_QLM_MODE_SGMII_4X1:
            lmac_type = 0; /* SGMII */
            is_bgx = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("SGMII", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_XAUI_1X4:
            lmac_type = 1; /* XAUI */
            is_bgx = 5;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("XAUI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_RXAUI_2X2:
            lmac_type = 2; /* RXAUI */
            is_bgx = 3;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("RXAUI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_XFI_4X1:
            lmac_type = 3; /* 10G_R */
            is_bgx = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("XFI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_XLAUI_1X4:
            lmac_type = 4; /* 40G_R */
            is_bgx = 5;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("XLAUI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_10G_KR_4X1:
            lmac_type = 3; /* 10G_R */
            is_bgx = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("10G-KR", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            kr_mode = 1;
            break;
        case BDK_QLM_MODE_40G_KR4_1X4:
            lmac_type = 4; /* 40G_R */
            is_bgx = 5;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("40G-KR", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            kr_mode = 1;
            break;
        case BDK_QLM_MODE_DISABLED:
            /* Set gser for the interface mode */
            BDK_CSR_MODIFY(c, node, BDK_GSERX_CFG(qlm),
                c.u = 0);
            /* Put the PHY in reset */
            BDK_CSR_MODIFY(c, node, BDK_GSERX_PHY_CTL(qlm),
                c.s.phy_reset = 1);
            return 0;
        case BDK_QLM_MODE_OCI:
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk("CCPI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            /* OCI is now in software mode as we are reprogramming it */
            BDK_CSR_MODIFY(c, node, BDK_GSERX_SPD(qlm),
                c.s.spd = 0xf);
            /* 6.25G normally doesn't do TX training. In software mode, force
               enable  TX training */
            if (baud_mhz == 6250)
            {
                for (int lane = 0; lane < 4; lane++)
                {
                    /* 3) Program override for the Tx coefficient request
                        Write GSER(8..13)_LANE(0..3)_PCS_CTLIFC_0.CFG_TX_COEFF_REQ_OVRRD_VAL = 0x1 */
                    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_0(qlm, lane),
                        c.s.cfg_tx_coeff_req_ovrrd_val = 1);
                    /* 4) Enable the Tx coefficient request override enable
                        Write GSER(8..13)_LANE(0..3)_PCS_CTLIFC_2.CFG_TX_COEFF_REQ_OVRRD_EN = 0x1 */
                    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
                        c.s.cfg_tx_coeff_req_ovrrd_en = 1);
                    /* 5) Issue a Control Interface Configuration Override request
                        to start the Tx equalizer Optimization cycle which applies
                        the new Tx swing and equalization settings
                        Write GSER(0..13)_LANE(0..3)_PCS_CTLIFC_2.CTLIFC_OVRRD_REQ = 0x1
                        The new Tx swing and Pre-cursor and Post-cursor settings
                        will now take effect. */
                    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
                        c.s.ctlifc_ovrrd_req = 1);
                }
            }
            is_ilk = 1; /* CCPI looks like ILK */
            break;
        default:
            bdk_error("Unsupported QLM mode %d\n", mode);
            return -1;
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
        BDK_CSR_MODIFY(c, node, BDK_BGXX_CMRX_CONFIG(bgx_block, 0),
            c.s.enable = 0;
            c.s.lmac_type = lmac_type);
    }

    /* Bring phy out of reset */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_PHY_CTL(qlm),
        c.s.phy_reset = 0);

    /* Wait 250 ns until the management interface is ready to accept
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

        /* Errata (GSER-25992) RX EQ Default Settings Update */
        __bdk_qlm_errata_gser_25992(node, qlm, baud_mhz);

        /* Errata (GSER-26150) 10G PHY PLL Temperature Failure */
        __bdk_qlm_errata_gser_26150(node, qlm, baud_mhz);

        /* Errata (GSER-26636) 10G-KR/40G-KR - Inverted Tx Coefficient Direction Change */
        __bdk_qlm_errata_gser_26636(node, qlm, baud_mhz);

        /* Errata (GSER-27140) SERDES temperature drift sensitivity in receiver */
        int channel_loss = bdk_config_get_int(BDK_CONFIG_QLM_CHANNEL_LOSS, node, qlm);
        __bdk_qlm_errata_gser_27140(node, qlm, baud_mhz, channel_loss);

        /* Errata (GSER-27882) GSER 10GBASE-KR Transmit Equalizer */
        /* Applied in bdk-if-bgx.c */

        /* cdrlock will be checked in the BGX */

        /* Apply any custom tuning */
        __bdk_qlm_tune(node, qlm, mode, baud_mhz);
    }

    /* If we're setting up the first QLM of a PCIe x8 interface, go ahead and
       setup the other inteface automatically */
    if (mode == BDK_QLM_MODE_PCIE_1X8)
    {
        switch (qlm)
        {
            case 2:
            case 4:
            case 6:
                /* Use the same reference clock for the second QLM */
                BDK_CSR_WRITE(node, BDK_GSERX_REFCLK_SEL(qlm + 1),
                    BDK_CSR_READ(node, BDK_GSERX_REFCLK_SEL(qlm)));
                return bdk_qlm_set_mode(node, qlm + 1, mode, baud_mhz, flags);
        }
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

    if (qlm < 8)
    {
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
                case 2: /* Either PEM0 x4 or PEM0 x8 */
                    pem = 0;
                    break;
                case 3: /* Either PEM0 x8 or PEM1 x4 */
                {
                    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(0));
                    if (pemx_cfg.cn88xx.lanes8)
                        pem = 0;
                    else
                        pem = 1;
                    break;
                }
                case 4: /* Either PEM2 x4 or PEM2 x8 */
                    pem = 2;
                    break;
                case 5: /* Either PEM2 x8 or PEM 3 x4 */
                {
                    /* Can be last 4 lanes of PEM2 */
                    BDK_CSR_INIT(pem2_cfg, node, BDK_PEMX_CFG(2));
                    if (pem2_cfg.cn88xx.lanes8)
                        pem = 2;
                    else
                        pem = 3;
                    break;
                }
                case 6: /* Either PEM4 x8 or PEM4 x4 */
                    pem = 4;
                    break;
                case 7: /* Either PEM4 x8 or PEm5 x4 */
                {
                    /* Can be last 4 lanes of PEM4 */
                    BDK_CSR_INIT(pem4_cfg, node, BDK_PEMX_CFG(4));
                    if (pem4_cfg.cn88xx.lanes8)
                        pem = 4;
                    else
                        pem = 5;
                    break;
                }
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
                case 2:
                    sata = 0;
                    break;
                case 3:
                    sata = 4;
                    break;
                case 6:
                    sata = 8;
                    break;
                case 7:
                    sata = 12;
                    break;
                default:
                    return 0;
            }
            BDK_CSR_INIT(uctl_ctl, node, BDK_SATAX_UCTL_CTL(sata));
            if (!uctl_ctl.s.a_clk_en || uctl_ctl.s.a_clkdiv_rst)
                return 0;
            BDK_CSR_INIT(sctl, node, BDK_SATAX_UAHC_P0_SCTL(sata));
            switch (sctl.s.spd)
            {
                case 1:
                    return 1500;
                case 2:
                    return 3000;
                case 3:
                    return 6000;
                default:
                    return 6000; /* No limit, assume 6G */
            }
        }
        else
        {
            /* Fall through to lane mode check below */
        }
    }
    else
    {
        /* Use the OCI strapping to find the speed. This will not work if
           the OCI is in SW_MODE */
        BDK_CSR_INIT(gserx_spd, node, BDK_GSERX_SPD(qlm));
        if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
        {
            /* Pass 1.x used a different encoding than pass 2.x */
            switch (gserx_spd.s.spd)
            {
                case 0x0: return 1250; /* Ref 100Mhz */
                case 0x1: return 2500;
                case 0x2: return 5000;
                case 0x3: return 8000;
                case 0x4: return 1250; /* Ref 125Mhz */
                case 0x5: return 2500;
                case 0x6: return 3125;
                case 0x7: return 5000;
                case 0x8: return 6250;
                case 0x9: return 8000;
                case 0xa: return 2500; /* Ref 156.25Mhz */
                case 0xb: return 3125;
                case 0xc: return 5000;
                case 0xd: return 6250;
                case 0xe: return 10312; /* KR training */
                default: /* Software mode */
                    /* Fall through to lane mode check below */
                    break;
            }
        }
        else
        {
            /* This is for pass 2.x (and beyond) */
            switch (gserx_spd.s.spd)
            {
                case 0x0: return 5000; /* Ref 100Mhz, Training short (Rx EQ only) */
                case 0x1: return 2500; /* Ref 100Mhz, No training */
                case 0x2: return 5000; /* Ref 100Mhz, No training */
                case 0x3: return 8000; /* Ref 100Mhz, No training */
                case 0x4: return 8000; /* Ref 100Mhz, Training short (Rx EQ only) */
                case 0x5: return 8000; /* Ref 100Mhz, KR training */
                case 0x6: return 3125; /* Ref 156.25Mhz, No training */
                case 0x7: return 5000; /* Ref 125Mhz, No training */
                case 0x8: return 6250; /* Ref 156.25Mhz, No training */
                case 0x9: return 8000; /* Ref 125Mhz, No training */
                case 0xa: return 10312;/* Ref 156.25Mhz, Training short (Rx EQ only) */
                case 0xb: return 3125; /* Ref 156.25Mhz, No training */
                case 0xc: return 5000; /* Ref 125Mhz, Training short (Rx EQ only) */
                case 0xd: return 6250; /* Ref 156.25Mhz, Training short (Rx EQ only) */
                case 0xe: return 10312;/* Ref 156.25Mhz, KR training */
                default: /* Software mode */
                    /* Fall through to lane mode check below */
                    break;
            }
        }
    }

    /* Show PHYs in reset as down */
    BDK_CSR_INIT(gserx_phy_ctl, node, BDK_GSERX_PHY_CTL(qlm));
    if (gserx_phy_ctl.s.phy_reset)
        return 0;

    /* QLM is not in PCIe, assume LMODE is good enough for determining
       the speed */
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
const bdk_qlm_ops_t bdk_qlm_ops_cn88xx = {
    .chip_model = CAVIUM_CN88XX,
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

