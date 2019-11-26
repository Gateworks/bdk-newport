/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "bdk-qlm-common.h"
#include "bdk-qlm-common-cn8xxx.h"
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
    return 4; /* 4 DLM */
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
    if ((qlm < 2) && bdk_is_altpkg(OCTEONTX_CN81XX))
        return 1; /* DLM0 and DLM1 are a single lane on CN80XX */
    else
        return 2; /* DLMs */
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
            if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
                return interface * 2;
            int qlm;
            switch (interface)
            {
                case 0:
                {
                    /* This BGX spans two DLMs. The index must be used to
                       figure out which DLM we are using */
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(0));
                    if (gserx_cfg.s.bgx)
                    {
                        if (gserx_cfg.s.bgx_quad) /* 4 lanes together */
                            qlm = 0;
                        else if (gserx_cfg.s.bgx_dual) /* 2 lanes together */
                            qlm = (index >= 1) ? 1 : 0;
                        else /* All lanes independent */
                        {
                            bdk_qlm_modes_t mode = bdk_qlm_get_mode(node, 0, 0);
                            if (mode == BDK_QLM_MODE_QSGMII)
                                qlm = 0;
                            else if (mode <= BDK_QLM_MODE_PCIE_X8)
                                qlm = 1;
                            else if (bdk_is_altpkg(OCTEONTX_CN81XX))
                            {
                                bdk_qlm_modes_t mode1 = bdk_qlm_get_mode(node, 1, 0);
                                if ((mode1 != BDK_QLM_MODE_QSGMII) && (index >= 2))
                                    return -1;
                                qlm = (index >= 1) ? 1 : 0;
                            }
                            else
                                qlm = (index >= 2) ? 1 : 0;
                        }
                    }
                    else
                        qlm = 1;
                    break;
                }
                case 1:
                {
                    /* This BGX spans two DLMs. The index must be used to
                       figure out which DLM we are using */
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(2));
                    if (gserx_cfg.s.bgx)
                    {
                        if (gserx_cfg.s.bgx_quad) /* 4 lanes together */
                            qlm = 2;
                        else if (gserx_cfg.s.bgx_dual) /* 2 lanes together */
                            qlm = (index >= 1) ? 3 : 2;
                        else /* All lanes independent */
                        {
                            bdk_qlm_modes_t mode = bdk_qlm_get_mode(node, 2, 0);
                            if (mode == BDK_QLM_MODE_QSGMII)
                                qlm = 2;
                            else if (mode <= BDK_QLM_MODE_PCIE_X8)
                                qlm = 1;
                            else
                                qlm = (index >= 2) ? 3 : 2;
                        }
                    }
                    else
                        qlm = 3;
                    break;
                }
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
            if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
                return -1;
            switch (interface)
            {
                case 0: /* PEM0 */
                {
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(0));
                    if (gserx_cfg.s.pcie)
                        return 0; /* PEM0 is on DLM0 */
                    else
                        return -1; /* PEM0 is disabled */
                }
                case 1: /* PEM1 */
                {
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(2));
                    if (gserx_cfg.s.pcie)
                        return 2; /* PEM1 is on DLM2 */
                    else
                        return -1; /* PEM1 is disabled */
                }
                case 2: /* PEM2 */
                {
                    BDK_CSR_INIT(pem1_cfg, node, BDK_PEMX_CFG(1));
                    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(3));
                    if (!pem1_cfg.cn81xx.lanes4 && gserx_cfg.s.pcie)
                        return 3; /* PEM2 is on DLM3 */
                    else
                        return -1; /* PEM2 is disabled */
                }
                default: /* Max of 3 PEMs, 0-2 */
                    return -1;
            }
        }
        default: /* Not supported by CN81XX */
            return -1;
    }
}

/**
 * Get the mode of a QLM as a human readable string
 *
 * @param node   Node to use in a Numa setup
 * @param qlm    QLM to examine
 * @param lane   Lane inside the QLM
 *
 * @return String mode
 */
static bdk_qlm_modes_t qlm_get_mode(bdk_node_t node, int qlm, int lane)
{
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
    {
        if (qlm < 4)
            return BDK_QLM_MODE_XLAUI;
        else
            return BDK_QLM_MODE_DISABLED;
    }
    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(qlm));
    if (gserx_cfg.s.pcie)
    {
        switch (qlm)
        {
            case 0: /* PEM0 */
            {
                BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(0));
                if (bdk_is_altpkg(OCTEONTX_CN81XX))
                    return BDK_QLM_MODE_PCIE_X1; /* PEM0 x1 */
                else if (pemx_cfg.cn81xx.lanes4)
                    return BDK_QLM_MODE_PCIE_X4; /* PEM0 x4 */
                else
                    return BDK_QLM_MODE_PCIE_X2; /* PEM0 x2 */
            }
            case 1: /* PEM0 second two lanes */
                return BDK_QLM_MODE_PCIE_X4; /* PEM0 x4 */
            case 2: /* Either PEM1 x4 or PEM1 x2 */
            {
                BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(1));
                if (pemx_cfg.cn81xx.lanes4)
                    return BDK_QLM_MODE_PCIE_X4; /* PEM1 x4 */
                else
                    return BDK_QLM_MODE_PCIE_X2; /* PEM1 x2 */
            }
            case 3: /* Either PEM1 x4 or PEM2 x2 */
            {
                /* Can be last 2 lanes of PEM1 */
                BDK_CSR_INIT(pem1_cfg, node, BDK_PEMX_CFG(1));
                if (pem1_cfg.cn81xx.lanes4)
                    return BDK_QLM_MODE_PCIE_X4; /* PEM1 x4 */
                /* Can be 2 lanes of PEM2 */
                return BDK_QLM_MODE_PCIE_X2; /* PEM2 x2 */
            }
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
            case 0:
            {
                bgx = 0;
                bgx_index = 0;
                break;
            }
            case 1:
                bgx = 0;
                bgx_index = 2;
                break;
            case 2:
            {
                bgx = 1;
                bgx_index = 0;
                break;
            }
            case 3:
                bgx = 1;
                bgx_index = 2;
                break;
            default:
                return BDK_QLM_MODE_DISABLED;
        }
        BDK_CSR_INIT(cmrx_config, node, BDK_BGXX_CMRX_CONFIG(bgx, bgx_index));
        bool is_kr = __bdk_qlm_is_lane_kr_cn8xxx(node, qlm, 0);
        switch (cmrx_config.s.lmac_type)
        {
            case BDK_BGX_LMAC_TYPES_E_SGMII:
            {
                /* SGMII or 1000X in BGX block */
                BDK_CSR_INIT(gmp_pcs_miscx_ctl, node, BDK_BGXX_GMP_PCS_MISCX_CTL(bgx, bgx_index));
                if (gmp_pcs_miscx_ctl.s.mode)
                    return BDK_QLM_MODE_1G_X;
                else
                    return BDK_QLM_MODE_SGMII;
            }
            case BDK_BGX_LMAC_TYPES_E_XAUI:
                return BDK_QLM_MODE_XAUI; /* Doesn't differentiate between XAUI and DXAUI */
            case BDK_BGX_LMAC_TYPES_E_RXAUI:
                return BDK_QLM_MODE_RXAUI;
            case BDK_BGX_LMAC_TYPES_E_TENG_R:
                if (is_kr)
                    return BDK_QLM_MODE_10G_KR;
                else
                    return BDK_QLM_MODE_XFI;
            case BDK_BGX_LMAC_TYPES_E_FORTYG_R:
                if (is_kr)
                    return BDK_QLM_MODE_40G_KR4;
                else
                    return BDK_QLM_MODE_XLAUI;
            case BDK_BGX_LMAC_TYPES_E_QSGMII:
                return BDK_QLM_MODE_QSGMII;
            default:  return BDK_QLM_MODE_DISABLED;
        }
    }
    else if (gserx_cfg.s.sata)
        return BDK_QLM_MODE_SATA;
    else
        return BDK_QLM_MODE_DISABLED;
}

static int qlm_set_sata(bdk_node_t node, int qlm, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    /* SATA has a fixed mapping for ports on CN81XX */
    int sata_port;
    switch (qlm)
    {
        case 3: /* SATA 0-1 = DLM3 lanes 0-1 */
            sata_port = 0;
            break;
        default:
            bdk_error("Attempted to configure SATA on QLM that doesn't support it\n");
            return -1;
    }
    return __bdk_qlm_set_sata_cn8xxx(node, qlm, baud_mhz, sata_port, sata_port + 1);
}

/**
 * For chips that don't use pin strapping, this function programs
 * the QLM to the specified mode
 *
 * @param node     Node to use in a Numa setup
 * @param qlm      QLM to configure
 * @param lane     Lane inside the QLM
 * @param mode     Desired mode
 * @param baud_mhz Desired speed
 * @param flags    Flags to specify mode specific options
 *
 * @return Zero on success, negative on failure
 */
static int qlm_set_mode(bdk_node_t node, int qlm, int lane, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
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
        case 0:
            bgx_block = 0;
            bgx_index = 0;
            break;
        case 1:
            bgx_block = 0;
            bgx_index = 2;
            break;
        case 2:
            bgx_block = 1;
            bgx_index = 0;
            break;
        case 3:
            bgx_block = 1;
            bgx_index = 2;
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
        case BDK_QLM_MODE_PCIE_X1:
        case BDK_QLM_MODE_PCIE_X2:
        case BDK_QLM_MODE_PCIE_X4:
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
                case 0: /* Either PEM0 x4 or PEM0 x2 or PEM0 x1 */
                    BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(0),
                        c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                    __bdk_qlm_setup_pem_reset_cn8xxx(node, 0, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(0),
                        c.cn81xx.lanes4 = (mode == BDK_QLM_MODE_PCIE_X4);
                        //c.cn81xx.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        c.cn81xx.md = cfg_md);
                    break;
                case 1: /* Second two lanes for PEM0 x4 */
                    /* PEMX_CFG already setup */
                    break;
                case 2: /* Either PEM1 x4 or PEM1 x2 */
                    BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(1),
                        c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                    __bdk_qlm_setup_pem_reset_cn8xxx(node, 1, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                    BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(1),
                        c.cn81xx.lanes4 = (mode == BDK_QLM_MODE_PCIE_X4);
                        //c.cn81xx.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        c.cn81xx.md = cfg_md);
                    break;
                case 3: /* Either PEM1 x4 or PEM2 x2 */
                    if (mode == BDK_QLM_MODE_PCIE_X4)
                    {
                        /* Last 2 lanes of PEM1 */
                        /* PEMX_CFG already setup */
                    }
                    else
                    {
                        /* Two lanes for PEM2 */
                        BDK_CSR_MODIFY(c, node, BDK_RST_SOFT_PRSTX(2),
                            c.s.soft_prst = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT));
                        __bdk_qlm_setup_pem_reset_cn8xxx(node, 2, flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(2),
                            c.cn81xx.lanes4 = 0;
                            //c.cn81xx.hostmd = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                            c.cn81xx.md = cfg_md);
                    }
                    break;
                default:
                    return -1;
            }
            break;
        }
        case BDK_QLM_MODE_SGMII:
        case BDK_QLM_MODE_1G_X:
            /* Disable port BGX ports 2-3 on CN80XX */
            if ((qlm < 2) && bdk_is_altpkg(OCTEONTX_CN81XX))
            {
                BDK_CSR_WRITE(node, BDK_BGXX_CMRX_RX_DMAC_CTL(0, 2), 0);
                BDK_CSR_WRITE(node, BDK_BGXX_CMRX_RX_DMAC_CTL(0, 3), 0);
            }
            lmac_type = BDK_BGX_LMAC_TYPES_E_SGMII; /* SGMII */
            is_bgx = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk_cn8xxx("SGMII", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_XAUI:
            lmac_type = BDK_BGX_LMAC_TYPES_E_XAUI; /* XAUI */
            is_bgx = 5;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk_cn8xxx("XAUI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_RXAUI:
            lmac_type = BDK_BGX_LMAC_TYPES_E_RXAUI; /* RXAUI */
            is_bgx = 3;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk_cn8xxx("RXAUI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_XFI:
            /* Disable port BGX ports 2-3 on CN80XX */
            if ((qlm < 2) && bdk_is_altpkg(OCTEONTX_CN81XX))
            {
                BDK_CSR_WRITE(node, BDK_BGXX_CMRX_RX_DMAC_CTL(0, 2), 0);
                BDK_CSR_WRITE(node, BDK_BGXX_CMRX_RX_DMAC_CTL(0, 3), 0);
            }
            lmac_type = BDK_BGX_LMAC_TYPES_E_TENG_R; /* 10G_R */
            is_bgx = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk_cn8xxx("XFI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_XLAUI:
            lmac_type = BDK_BGX_LMAC_TYPES_E_FORTYG_R; /* 40G_R */
            is_bgx = 5;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk_cn8xxx("XLAUI", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            break;
        case BDK_QLM_MODE_10G_KR:
            /* Disable port BGX ports 2-3 on CN80XX */
            if ((qlm < 2) && bdk_is_altpkg(OCTEONTX_CN81XX))
            {
                BDK_CSR_WRITE(node, BDK_BGXX_CMRX_RX_DMAC_CTL(0, 2), 0);
                BDK_CSR_WRITE(node, BDK_BGXX_CMRX_RX_DMAC_CTL(0, 3), 0);
            }
            lmac_type = BDK_BGX_LMAC_TYPES_E_TENG_R; /* 10G_R */
            is_bgx = 1;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk_cn8xxx("10G-KR", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            kr_mode = 1;
            break;
        case BDK_QLM_MODE_40G_KR4:
            lmac_type = BDK_BGX_LMAC_TYPES_E_FORTYG_R; /* 40G_R */
            is_bgx = 5;
            lane_mode = __bdk_qlm_get_lane_mode_for_speed_and_ref_clk_cn8xxx("40G-KR", qlm, ref_clk, baud_mhz);
            if (lane_mode == -1)
                return -1;
            kr_mode = 1;
            break;
        case BDK_QLM_MODE_QSGMII:
            lmac_type = BDK_BGX_LMAC_TYPES_E_QSGMII; /* QSGMII */
            is_bgx = 1;
            lane_mode = BDK_GSER_LMODE_E_R_5G_REFCLK15625_QSGMII;
            break;
        case BDK_QLM_MODE_SATA:
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
        /* Record SGMII or 1000X in BGX block */
        BDK_CSR_MODIFY(c, node, BDK_BGXX_GMP_PCS_MISCX_CTL(bgx_block, bgx_index),
            c.s.mode = (mode == BDK_QLM_MODE_1G_X));
    }

    /* Bring phy out of reset */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_PHY_CTL(qlm),
        c.s.phy_reset = 0);

    /* Wait 1us until the management interface is ready to accept
       read/write commands.*/
    bdk_wait_usec(1);

    /* Configure the gser pll */
    __bdk_qlm_init_mode_table_cn8xxx(node, qlm, ref_clk);

    /* Remember which lanes are using KR over BGX */
    if (is_bgx)
    {
        int num_lanes = bdk_qlm_get_lanes(node, qlm);
        for (int lane = 0; lane < num_lanes; lane++)
            __bdk_qlm_set_lane_kr_cn8xxx(node, qlm, lane, kr_mode);
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
    __bdk_qlm_tune_cn8xxx(node, qlm, mode, baud_mhz);

    /* Some modes require 4 lanes, which spans DLMs. For these modes, we need
       to setup the second DLM at the same time we setup the first. The second
       DLM also must use the same reference clock as the first */
    bool paired_dlm = ((qlm & 1) == 0) && /* We're on the first (even) DLM */
        ((mode == BDK_QLM_MODE_PCIE_X4) || /* We're using a 4 lane mode */
         (mode == BDK_QLM_MODE_XAUI) ||
         (mode == BDK_QLM_MODE_XLAUI) ||
         (mode == BDK_QLM_MODE_40G_KR4));
    if (paired_dlm)
    {
        /* Use the same reference clock for the second QLM */
        BDK_CSR_WRITE(node, BDK_GSERX_REFCLK_SEL(qlm + 1),
            BDK_CSR_READ(node, BDK_GSERX_REFCLK_SEL(qlm)));
        return bdk_qlm_set_mode(node, qlm + 1, lane, mode, baud_mhz, flags);
    }

    return 0;
}

/**
 * Get the speed (Gbaud) of the QLM in Mhz.
 *
 * @param node   Node to query
 * @param qlm    QLM to examine
 * @param lane   Lane inside the QLM
 *
 * @return Speed in Mhz
 */
static int qlm_get_gbaud_mhz(bdk_node_t node, int qlm, int lane)
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
            case 0: /* PEM0 */
            case 1: /* PEM0 */
                pem = 0;
                break;
            case 2: /* PEM1 */
                pem = 1;
                break;
            case 3: /* PEM1 or PEM2 */
            {
                BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(1));
                if (pemx_cfg.cn81xx.lanes4)
                    pem = 1;
                else
                    pem = 2;
                break;
            }
            default:
                bdk_fatal("QLM%d: In PCIe mode, which shouldn't happen\n", qlm);
        }
        return __bdk_qlm_get_gbaud_mhz_pem_cn8xxx(node, pem);
    }
    else if (gserx_cfg.s.sata)
    {
        int sata;
        switch (qlm)
        {
            case 3:
                sata = 0;
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
        return __bdk_qlm_get_gbaud_mhz_lmode_cn8xxx(node, qlm);
}

static const bdk_qlm_mode_desc_t dlm0_cn81xx[] = {
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    //{BDK_QLM_MODE_XAUI,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 3125}, /* Not supported per HRM */
    //{BDK_QLM_MODE_XAUI,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 6250}, /* Not supported per HRM */
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    //{BDK_QLM_MODE_XLAUI,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312}, /* Not supported per HRM */
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    //{BDK_QLM_MODE_40G_KR4,    BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312}, /* Not supported per HRM */
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 2500},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 8000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t slm0_cn80xx[] = {
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 2500},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 8000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t dlm1_cn81xx[] = {
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t slm1_cn80xx[] = {
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t dlm2[] = {
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    //{BDK_QLM_MODE_XAUI,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 3125}, /* Not supported per HRM */
    //{BDK_QLM_MODE_XAUI,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 6250}, /* Not supported per HRM */
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    //{BDK_QLM_MODE_XLAUI,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312}, /* Not supported per HRM */
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    //{BDK_QLM_MODE_40G_KR4,    BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312}, /* Not supported per HRM */
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 2500},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 8000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t dlm3[] = {
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 10312},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 2500},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 5000},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 8000},
    {BDK_QLM_MODE_SATA,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 1500},
    {BDK_QLM_MODE_SATA,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 3000},
    {BDK_QLM_MODE_SATA,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 6000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};

/**
 * Return an array describing the modes allowed for q QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to describe
 *
 * @return Mode description
 */
static const bdk_qlm_mode_desc_t* qlm_get_mode_desc(bdk_node_t node, int qlm)
{
    switch (qlm)
    {
        case 0: return bdk_is_altpkg(OCTEONTX_CN81XX) ? slm0_cn80xx : dlm0_cn81xx;
        case 1: return bdk_is_altpkg(OCTEONTX_CN81XX) ? slm1_cn80xx : dlm1_cn81xx;
        case 2: return dlm2;
        case 3: return dlm3;
        default: return NULL;
    }
}

/**
 * Return the BGX/CGX interface number that corresponds to the supplied DLM/QLM.
 * This function returns the same result regardless of board configuration. If a
 * single BGX/CGX can be used by multiple DLM/QLM, all of those DLM/QLM will
 * return the same interface. The current active configuration is ignored.
 *
 * @param node     Node to lookup
 * @param qlm      DLM/QLM to lookup
 * @param is_split Set to true if the BGX/CGX is split across two DLMs
 * @param is_upper Set to true if the requested DLM is the upper half of a BGX/CGX
 *
 * @return BGX/CGX number, or -1 if the DLM/QLM can't be used with networking
 */
static int qlm_to_network(bdk_node_t node, int qlm, bool *is_split, bool *is_upper)
{
    /* Which BGX maps to a specific DLM
       BGX0: DLM0-1
       BGX1: DLM2-3*/
    const int8_t qlm_to_cgx[4] = {0, 0, 1, 1};
    *is_split = true;
    *is_upper = ((qlm == 1) || (qlm == 3));
    return qlm_to_cgx[qlm];
}

/**
 * Initialize the QLM layer
 */
static void qlm_init(bdk_node_t node)
{
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return;

    /* Setup how each PEM drives the PERST lines */
    for (int pem = 0; pem < 3; pem++)
    {
        BDK_CSR_INIT(rst_ctlx, node, BDK_RST_CTLX(pem));
        __bdk_qlm_setup_pem_reset_cn8xxx(node, pem, !rst_ctlx.s.host_mode);
    }
}

/* Each chip has its own QLM operation table */
const bdk_qlm_ops_t bdk_qlm_ops_cn81xx = {
    .chip_model = OCTEONTX_CN81XX,
    .init = qlm_init,
    .get_num = qlm_get_num,
    .get_lanes = qlm_get_lanes,
    .get_mode = qlm_get_mode,
    .set_mode = qlm_set_mode,
    .get_gbaud_mhz = qlm_get_gbaud_mhz,
    .measure_refclock = __bdk_qlm_measure_refclock_cn8xxx,
    .get_qlm_num = qlm_get_qlm_num,
    .reset = __bdk_qlm_reset_cn8xxx,
    .enable_prbs = __bdk_qlm_enable_prbs_cn8xxx,
    .disable_prbs = __bdk_qlm_disable_prbs_cn8xxx,
    .get_prbs_errors = __bdk_qlm_get_prbs_errors_cn8xxx,
    .inject_prbs_error = __bdk_qlm_inject_prbs_error_cn8xxx,
    .enable_loop = __bdk_qlm_enable_loop_cn8xxx,
    .auto_config = bdk_qlm_mcu_auto_config,
    .tune_lane_tx = __bdk_qlm_tune_lane_tx_cn8xxx,
    .get_tune_lane_tx = __bdk_qlm_get_tune_lane_tx_cn8xxx,
    .rx_equalization = __bdk_qlm_rx_equalization_cn8xxx,
    .eye_capture = __bdk_qlm_eye_capture_cn8xxx,
    .display_settings = __bdk_qlm_display_settings_cn8xxx,
    .get_mode_desc = qlm_get_mode_desc,
    .qlm_to_network = qlm_to_network,
};

