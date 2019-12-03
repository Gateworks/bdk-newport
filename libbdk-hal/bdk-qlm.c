/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include <math.h>
#include "libbdk-arch/bdk-csrs-gser.h"
#include "libbdk-arch/bdk-csrs-gsern.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(QLM);

/* Each chip has its own QLM operation table */
extern const bdk_qlm_ops_t bdk_qlm_ops_cn83xx;
extern const bdk_qlm_ops_t bdk_qlm_ops_cn81xx;
extern const bdk_qlm_ops_t bdk_qlm_ops_cn96xx;
extern const bdk_qlm_ops_t bdk_qlm_ops_cn96xx_gserr;
extern const bdk_qlm_ops_t bdk_qlm_ops_cnf95xx;
extern const bdk_qlm_ops_t bdk_qlm_ops_cnf95xx_gserr;
extern const bdk_qlm_ops_t bdk_qlm_ops_loki;
extern const bdk_qlm_ops_t bdk_qlm_ops_cn98xx;

static const bdk_qlm_ops_t *qlm_ops_list[] = {
#if 0 // saves 163568 bytes
    &bdk_qlm_ops_cn83xx,
    &bdk_qlm_ops_cn81xx,
    &bdk_qlm_ops_cn96xx,
    &bdk_qlm_ops_cn96xx_gserr,
    &bdk_qlm_ops_cnf95xx,
    &bdk_qlm_ops_cnf95xx_gserr,
    &bdk_qlm_ops_loki,
    &bdk_qlm_ops_cn98xx,
#else
    &bdk_qlm_ops_cn81xx,
#endif
    NULL
};
static const bdk_qlm_ops_t *qlm_ops;

/**
 * Return the number of QLMs supported for the chip
 *
 * @return Number of QLMs
 */
int bdk_qlm_get_num(bdk_node_t node)
{
    return qlm_ops->get_num(node);
}

/**
 * Lookup the hardware QLM number for a given interface type and
 * index. If the associated interface doesn't map to a QLM,
 * returns -1.
 *
 * @param node      Node to use in a Numa setup
 * @param iftype    Interface type
 * @param interface Interface index number
 * @param index     Port on the interface. Most chips use the
 *                  same mode for all ports, but there are
 *                  exceptions. For example, BGX2 on CN83XX
 *                  spans two DLMs.
 *
 * @return QLM number or -1 on failure
 */
int bdk_qlm_get(bdk_node_t node, bdk_if_t iftype, int interface, int index)
{
    return qlm_ops->get_qlm_num(node, iftype, interface, index);
}

/**
 * Return the number of lanes in a QLM. QLMs normally contain
 * 4 lanes, except for chips which only have half of a QLM.
 *
 * @param qlm    QLM to get lanes number for
 *
 * @return Number of lanes on the QLM
 */
int bdk_qlm_get_lanes(bdk_node_t node, int qlm)
{
    return qlm_ops->get_lanes(node, qlm);
}

/**
 * Convert a mode into a configuration variable string value
 *
 * @param mode   Mode to convert
 *
 * @return configuration value string
 */
const char *bdk_qlm_mode_to_cfg_str(bdk_qlm_modes_t mode)
{
#define MODE_CASE(m) case m: return ((const char *)#m)+13
    switch (mode)
    {
        MODE_CASE(BDK_QLM_MODE_DISABLED);
        MODE_CASE(BDK_QLM_MODE_PCIE_X1);
        MODE_CASE(BDK_QLM_MODE_PCIE_X2);
        MODE_CASE(BDK_QLM_MODE_PCIE_X4);
        MODE_CASE(BDK_QLM_MODE_PCIE_X8);
        MODE_CASE(BDK_QLM_MODE_PCIE_X16);

        MODE_CASE(BDK_QLM_MODE_SATA);

        MODE_CASE(BDK_QLM_MODE_SGMII);
        MODE_CASE(BDK_QLM_MODE_1G_X);
        MODE_CASE(BDK_QLM_MODE_QSGMII);
        MODE_CASE(BDK_QLM_MODE_XAUI);
        MODE_CASE(BDK_QLM_MODE_RXAUI);
        MODE_CASE(BDK_QLM_MODE_XFI);
        MODE_CASE(BDK_QLM_MODE_SFI);
        MODE_CASE(BDK_QLM_MODE_XLAUI);
        MODE_CASE(BDK_QLM_MODE_XLAUI_C2M);
        MODE_CASE(BDK_QLM_MODE_10G_KR);
        MODE_CASE(BDK_QLM_MODE_40G_CR4);
        MODE_CASE(BDK_QLM_MODE_40G_KR4);
        MODE_CASE(BDK_QLM_MODE_20GAUI_C2C);
        MODE_CASE(BDK_QLM_MODE_25GAUI_C2C);
        MODE_CASE(BDK_QLM_MODE_25GAUI_C2M);
        MODE_CASE(BDK_QLM_MODE_25G_CR);
        MODE_CASE(BDK_QLM_MODE_25G_KR);
        MODE_CASE(BDK_QLM_MODE_25GAUI_2_C2C);
        MODE_CASE(BDK_QLM_MODE_40GAUI_2_C2C);
        MODE_CASE(BDK_QLM_MODE_50GAUI_2_C2C);
        MODE_CASE(BDK_QLM_MODE_50GAUI_2_C2M);
        MODE_CASE(BDK_QLM_MODE_50G_CR2);
        MODE_CASE(BDK_QLM_MODE_50G_KR2);
        MODE_CASE(BDK_QLM_MODE_50GAUI_4_C2C);
        MODE_CASE(BDK_QLM_MODE_80GAUI_4_C2C);
        MODE_CASE(BDK_QLM_MODE_CAUI_4_C2C);
        MODE_CASE(BDK_QLM_MODE_CAUI_4_C2M);
        MODE_CASE(BDK_QLM_MODE_100G_CR4);
        MODE_CASE(BDK_QLM_MODE_100G_KR4);
        MODE_CASE(BDK_QLM_MODE_USXGMII_4X1);
        MODE_CASE(BDK_QLM_MODE_USXGMII_2X1);
        MODE_CASE(BDK_QLM_MODE_USXGMII_1X1);

        case BDK_QLM_MODE_LAST: break; /* fall through error */
    }
    return "INVALID_QLM_MODE_VALUE";
}

/**
 * Convert a configuration variable value string into a mode
 *
 * @param val  Configuration variable value
 *
 * @return mode
 */
bdk_qlm_modes_t bdk_qlm_cfg_string_to_mode(const char *val)
{
    bdk_qlm_modes_t mode;

    /* Strip off any QLM flags, denoted by "-" */
    char tmp[strlen(val) + 1];
    if (strchr(val, '-'))
    {
        strcpy(tmp, val);
        *strchr(tmp, '-') = 0;
        val = tmp;
    }

    /* Search for matching mode */
    for (mode = 0; mode < BDK_QLM_MODE_LAST; mode++)
    {
        if (0 == strcmp(val, bdk_qlm_mode_to_cfg_str(mode)))
        {
            return mode;
        }
    }

    /* Previous BDKs had a suffix after network modes, look for these
       for backwards compatibility */
    if (strncmp(val, "SGMII_", 6) == 0)
        return BDK_QLM_MODE_SGMII;
    if (strncmp(val, "XAUI_", 5) == 0)
        return BDK_QLM_MODE_XAUI;
    if (strncmp(val, "RXAUI_", 6) == 0)
        return BDK_QLM_MODE_RXAUI;
    if (strncmp(val, "XFI_", 4) == 0)
        return BDK_QLM_MODE_XFI;
    if (strncmp(val, "XLAUI_1", 6) == 0)
        return BDK_QLM_MODE_XLAUI;
    if (strncmp(val, "10G_KR_", 7) == 0)
        return BDK_QLM_MODE_10G_KR;
    if (strncmp(val, "40G_KR4_", 8) == 0)
        return BDK_QLM_MODE_40G_KR4;
    if (strncmp(val, "QSGMII_", 7) == 0)
        return BDK_QLM_MODE_QSGMII;
    if (strncmp(val, "SATA_", 5) == 0)
        return BDK_QLM_MODE_SATA;
    if (strcmp(val, "PCIE_1X1") == 0)
        return BDK_QLM_MODE_PCIE_X1;
    if (strcmp(val, "PCIE_1X2") == 0)
        return BDK_QLM_MODE_PCIE_X2;
    if (strcmp(val, "PCIE_1X4") == 0)
        return BDK_QLM_MODE_PCIE_X4;
    if (strcmp(val, "PCIE_1X8") == 0)
        return BDK_QLM_MODE_PCIE_X8;
    if (strcmp(val, "PCIE_1X16") == 0)
        return BDK_QLM_MODE_PCIE_X16;

    return -1;
}

/**
 * Convert a mode into a human understandable string
 *
 * @param mode   Mode to convert
 *
 * @return Easy to read string
 */
const char *bdk_qlm_mode_tostring(bdk_qlm_modes_t mode)
{
    const char *result = "Unknown, update bdk_qlm_mode_tostring()";
    switch (mode)
    {
        case BDK_QLM_MODE_DISABLED:
            result = "Disabled";
            break;
        case BDK_QLM_MODE_PCIE_X1:
            result = "PCIe, 1 lane";
            break;
        case BDK_QLM_MODE_PCIE_X2:
            result = "PCIe, 2 lanes";
            break;
        case BDK_QLM_MODE_PCIE_X4:
            result = "PCIe, 4 lanes";
            break;
        case BDK_QLM_MODE_PCIE_X8:
            result = "PCIe, 8 lanes";
            break;
        case BDK_QLM_MODE_PCIE_X16:
            result = "PCIe, 16 lanes";
            break;

        case BDK_QLM_MODE_SATA:
            result = "SATA, one lane each";
            break;

        case BDK_QLM_MODE_SGMII:
            result = "SGMII, 1 lane each";
            break;
        case BDK_QLM_MODE_1G_X:
            result = "1000BASE-X, 1 lane each";
            break;
        case BDK_QLM_MODE_QSGMII:
            result = "4 QSGMII over 1 lane";
            break;
        case BDK_QLM_MODE_XAUI:
            result = "XAUI, 4 lanes";
            break;
        case BDK_QLM_MODE_RXAUI:
            result = "RXAUI, 2 lanes each";
            break;
        case BDK_QLM_MODE_XFI:
            result = "XFI, 1 lane each";
            break;
        case BDK_QLM_MODE_SFI:
            result = "SFI, 1 lane each";
            break;
        case BDK_QLM_MODE_XLAUI:
            result = "XLAUI, 4 lanes";
            break;
        case BDK_QLM_MODE_XLAUI_C2M:
            result = "XLAUI-C2M, 4 lanes";
            break;
        case BDK_QLM_MODE_10G_KR:
            result = "10GBASE-KR, 1 lane each";
            break;
        case BDK_QLM_MODE_40G_CR4:
            result = "40GBASE-CR4, 4 lanes";
            break;
        case BDK_QLM_MODE_40G_KR4:
            result = "40GBASE-KR4, 4 lanes";
            break;
        case BDK_QLM_MODE_20GAUI_C2C:
            result = "20GAUI-C2C, 1 lane each";
            break;
        case BDK_QLM_MODE_25GAUI_C2C:
            result = "25GAUI-C2C, 1 lane each";
            break;
        case BDK_QLM_MODE_25GAUI_C2M:
            result = "25GAUI-C2M, 1 lane each";
            break;
        case BDK_QLM_MODE_25G_CR:
            result = "25GBASE-CR, 1 lane each";
            break;
        case BDK_QLM_MODE_25G_KR:
            result = "25GBASE-KR, 1 lane each";
            break;
        case BDK_QLM_MODE_25GAUI_2_C2C:
            result = "25GAUI-2-C2C, 2 lanes each";
            break;
        case BDK_QLM_MODE_40GAUI_2_C2C:
            result = "40GAUI-2-C2C, 2 lanes each";
            break;
        case BDK_QLM_MODE_50GAUI_2_C2C:
            result = "50GAUI-2-C2C, 2 lanes each";
            break;
        case BDK_QLM_MODE_50GAUI_2_C2M:
            result = "50GAUI-2-C2M, 2 lanes each";
            break;
        case BDK_QLM_MODE_50G_CR2:
            result = "50GBASE-CR2, 2 lanes";
            break;
        case BDK_QLM_MODE_50G_KR2:
            result = "50GBASE-KR2, 2 lanes";
            break;
        case BDK_QLM_MODE_50GAUI_4_C2C:
            result = "50GAUI-4-C2C, 4 lanes each";
            break;
        case BDK_QLM_MODE_80GAUI_4_C2C:
            result = "80GAUI-4-C2C, 4 lanes each";
            break;
        case BDK_QLM_MODE_CAUI_4_C2C:
            result = "CAUI-4-C2C, 4 lanes";
            break;
        case BDK_QLM_MODE_CAUI_4_C2M:
            result = "CAUI-4-C2M, 4 lanes";
            break;
        case BDK_QLM_MODE_100G_CR4:
            result = "100GBASE-CR4, 4 lanes";
            break;
        case BDK_QLM_MODE_100G_KR4:
            result = "100GBASE-KR4, 4 lanes";
            break;
        case BDK_QLM_MODE_USXGMII_4X1:
            result = "4 USXGMII over 1 lane";
            break;
        case BDK_QLM_MODE_USXGMII_2X1:
            result = "2 USXGMII over 1 lane";
            break;
        case BDK_QLM_MODE_USXGMII_1X1:
            result = "1 USXGMII over 1 lane";
            break;

        case BDK_QLM_MODE_LAST:
            break; /* fallthrough error */
    }
    return result;
}

/**
 * Get the mode of a QLM as a human readable string
 *
 * @param node   Node to use in a Numa setup. Can be an exact ID or a special
 *               value.
 * @param qlm    QLM to examine
 * @param lane   Lane inside the QLM
 *
 * @return String mode
 */
bdk_qlm_modes_t bdk_qlm_get_mode(bdk_node_t node, int qlm, int lane)
{
    return qlm_ops->get_mode(node, qlm, lane);
}

/**
 * For chips that don't use pin strapping, this function programs
 * the QLM lane to the specified mode
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
int bdk_qlm_set_mode(bdk_node_t node, int qlm, int lane, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    return qlm_ops->set_mode(node, qlm, lane, mode, baud_mhz, flags);
}

/**
 * Set the QLM's clock source.
 *
 * @param node     Node to use in a Numa setup
 * @param qlm      QLM to configure
 * @param clk      Clock source for QLM
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_set_clock(bdk_node_t node, int qlm, bdk_qlm_clock_t clk)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        int sel;
        int com1;
        switch (clk)
        {
            case BDK_QLM_CLK_COMMON_0:
                sel = 1;
                com1 = 0;
                break;
            case BDK_QLM_CLK_COMMON_1:
                sel = 1;
                com1 = 1;
                break;
            case BDK_QLM_CLK_EXTERNAL:
                sel = 0;
                com1 = 0;
                break;
            default:
                bdk_warn("Unrecognized clock mode %d for QLM%d on node %d.\n",
                     clk, qlm, node);
                return -1;
        }

        BDK_CSR_MODIFY(c, node, BDK_GSERX_REFCLK_SEL(qlm),
            c.s.com_clk_sel = sel;
            c.s.use_com1 = com1);
    }
    else if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
    {
        int clk_term = bdk_config_get_int(BDK_CONFIG_QLM_CLK_TERM, node, qlm);
        int cclksel;
        switch (clk)
        {
            case BDK_QLM_CLK_COMMON_0:
                cclksel = 0;
                break;
            case BDK_QLM_CLK_COMMON_1:
                cclksel = 1;
                BDK_CSR_MODIFY(c, node, BDK_RST_REFC_CTL,
                    c.s.cclk1_sel = clk_term & 3;
                    c.s.cclk1_pwdn = 0);
                break;
            case BDK_QLM_CLK_COMMON_2:
                cclksel = 2;
                BDK_CSR_MODIFY(c, node, BDK_RST_REFC_CTL,
                    c.s.cclk2_sel = clk_term & 3;
                    c.s.cclk2_pwdn = 0);
                break;
            case BDK_QLM_CLK_EXTERNAL:
                cclksel = 3;
                break;
            default:
                bdk_warn("Unrecognized clock mode %d for QLM%d on node %d.\n",
                     clk, qlm, node);
                return -1;
        }
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm),
            c.s.hcsl = (clk_term == 3);
            c.s.oct = (clk_term != 0);
            c.s.pwdn = 0; /* Always power on */
            c.s.cclksel = cclksel);
    }
    else
        BDK_TRACE(QLM, "N%d.QLM%d: Ignoring refclock select, fixed by GSER\n", node, qlm);
    return 0;
}

/**
 * Get the speed (Gbaud) of the QLM in Mhz.
 *
 * @param node   Node to use in a Numa setup. Can be an exact ID or a special
 *               value.
 * @param qlm    QLM to examine
 * @param lane   Lane inside the QLM
 *
 * @return Speed in Mhz
 */
int bdk_qlm_get_gbaud_mhz(bdk_node_t node, int qlm, int lane)
{
    return qlm_ops->get_gbaud_mhz(node, qlm, lane);
}

/**
 * Measure the reference clock of a QLM
 *
 * @param qlm    QLM to measure
 *
 * @return Clock rate in Hz
 */
int bdk_qlm_measure_clock(bdk_node_t node, int qlm)
{
    int ref_clock = qlm_ops->measure_refclock(node, qlm);
    BDK_TRACE(QLM, "N%d.QLM%d: Ref clock %d Hz\n", node, qlm, ref_clock);
    return ref_clock;
}

/**
 * Reset a QLM to its initial state
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_reset(bdk_node_t node, int qlm)
{
    return qlm_ops->reset(node, qlm);
}

/**
 * Enable PRBS on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 * @param prbs   PRBS mode (31, etc)
 * @param dir    Directions to enable. This is so you can enable TX and later
 *               enable RX after TX has run for a time
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_enable_prbs(bdk_node_t node, int qlm, int prbs, bdk_qlm_direction_t dir)
{
    return qlm_ops->enable_prbs(node, qlm, prbs, dir);
}

/**
 * Disable PRBS on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_disable_prbs(bdk_node_t node, int qlm)
{
    return qlm_ops->disable_prbs(node, qlm);
}

/**
 * Return the number of PRBS errors since PRBS started running
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 * @param clear  Clear the counter after returning its value
 *
 * @return Number of errors
 */
uint64_t bdk_qlm_get_prbs_errors(bdk_node_t node, int qlm, int lane, int clear)
{
    return qlm_ops->get_prbs_errors(node, qlm, lane, clear);
}

/**
 * Inject an error into PRBS
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 */
void bdk_qlm_inject_prbs_error(bdk_node_t node, int qlm, int lane)
{
    qlm_ops->inject_prbs_error(node, qlm, lane);
}

/**
 * Enable shallow loopback on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 * @param loop   Type of loopback. Not all QLMs support all modes
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_enable_loop(bdk_node_t node, int qlm, bdk_qlm_loop_t loop)
{
    return qlm_ops->enable_loop(node, qlm, loop);
}

/**
 * Configure the TX tuning parameters for a QLM lane. The tuning parameters can
 * be specified as -1 to maintain their current value
 *
 * @param node     Node to configure
 * @param qlm      QLM to configure
 * @param lane     Lane to configure
 * @param tx_swing Transmit swing, also called cMain (coef 0)
 * @param tx_pre   Pre cursor emphasis (Coef -1)
 * @param tx_post  Post cursor emphasis (Coef +1)
 * @param tx_gain_bias
 *                 For CN8XXX, this is transmit gain. For CN9XXX, this is transmit bias
 * @param tx_vboost_unused
 *                 For CN8XXX, this is transmit voltage boost. For CN9XXX, this is unused
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_tune_lane_tx(bdk_node_t node, int qlm, int lane, int tx_swing, int tx_pre, int tx_post, int tx_gain_bias, int tx_vboost_unused)
{
    int old_tx_swing;
    int old_tx_pre;
    int old_tx_post;
    int old_tx_gain_bias;
    int old_tx_vboost_unused;
    if (bdk_qlm_get_tune_lane_tx(node, qlm, lane, &old_tx_swing, &old_tx_pre,
        &old_tx_post, &old_tx_gain_bias, &old_tx_vboost_unused))
        return -1;

    if (tx_swing == -1)
        tx_swing = old_tx_swing;
    if (tx_pre == -1)
        tx_pre = old_tx_pre;
    if (tx_post == -1)
        tx_post = old_tx_post;
    if (tx_gain_bias == -1)
        tx_gain_bias = old_tx_gain_bias;
    if (tx_vboost_unused == -1)
        tx_vboost_unused = old_tx_vboost_unused;

    return qlm_ops->tune_lane_tx(node, qlm, lane, tx_swing, tx_pre, tx_post, tx_gain_bias, tx_vboost_unused);
}

/**
 * Get the TX tuning parameters for a QLM lane
 *
 * @param node     Node to configure
 * @param qlm      QLM to configure
 * @param lane     Lane to configure
 * @param tx_swing Transmit swing, also called cMain (coef 0)
 * @param tx_pre   Pre cursor emphasis (Coef -1)
 * @param tx_post  Post cursor emphasis (Coef +1)
 * @param tx_gain_bias
 *                 For CN8XXX, this is transmit gain. For CN9XXX, this is transmit bias
 * @param tx_vboost_unused
 *                 For CN8XXX, this is transmit voltage boost. For CN9XXX, this is unused
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_get_tune_lane_tx(bdk_node_t node, int qlm, int lane, int *tx_swing, int *tx_pre, int *tx_post, int *tx_gain_bias, int *tx_vboost_unused)
{
    return qlm_ops->get_tune_lane_tx(node, qlm, lane, tx_swing, tx_pre, tx_post, tx_gain_bias, tx_vboost_unused);
}

/**
 * Perform RX equalization on a QLM
 *
 * @param node   Node the QLM is on
 * @param qlm    QLM to perform RX equalization on
 * @param lane   Lane to use, or -1 for all lanes
 *
 * @return Zero on success, negative if any lane failed RX equalization
 */
int bdk_qlm_rx_equalization(bdk_node_t node, int qlm, int lane)
{
    return qlm_ops->rx_equalization(node, qlm, lane);
}

/**
 * Capture an eye diagram for the given QLM lane. The output data is written
 * to "eye".
 *
 * @param node      Node to use in numa setup
 * @param qlm       QLM to use
 * @param qlm_lane  Which lane
 * @param show_data Set to non-zero to have the eye capture dump the raw eye data as
 *                  it is captured
 * @param eye       Output eye data
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_eye_capture(bdk_node_t node, int qlm, int qlm_lane, int show_data, bdk_qlm_eye_t *eye)
{
    if (qlm_ops->eye_capture)
        return qlm_ops->eye_capture(node, qlm, qlm_lane, show_data, eye);
    else
    {
        bdk_error("Eye capture not supported on this chip\n");
        return -1;
    }
}

/**
 * Calculate the log10() of an integer number, avoiding using the math library. It
 * will return 0 for zero, which is unstandard.
 *
 * @param v      Value to take log10() of
 *
 * @return log10() of value
 */
static int int_log10(uint64_t v)
{
    int r = 0;
    while (v >= 10)
    {
        v /= 10;
        r++;
    }
    return r;
}

/**
 * Display an eye diagram for the given QLM lane. The eye data can be in "eye", or
 * captured during the call if "eye" is NULL.
 *
 * @param node     Node to use in numa setup
 * @param qlm      QLM to use
 * @param qlm_lane Which lane
 * @param format   Display format. 0 = table, 1 = Color ASCII, 2 = Color + raw
 * @param eye      Eye data to display, or NULL if the data should be captured.
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_eye_display(bdk_node_t node, int qlm, int qlm_lane, int format, const bdk_qlm_eye_t *eye)
{
    int result;
    int need_free = 0;
    if (eye == NULL)
    {
        bdk_qlm_eye_t *eye_data = malloc(sizeof(bdk_qlm_eye_t));
        if (eye_data == NULL)
        {
            bdk_error("Failed to allocate space for eye\n");
            return -1;
        }
        int show_data = (format == 2);
        if (bdk_qlm_eye_capture(node, qlm, qlm_lane, show_data, eye_data))
            return -1;
        eye = eye_data;
    }

    /* Calculate the max eye width */
    int eye_area = 0;
    int eye_width = 0;
    for (int y = 0; y < eye->height; y++)
    {
        int width = 0;
        for (int x = 0; x < eye->width; x++)
        {
            if (eye->data[y][x] == 0)
            {
                width++;
                eye_area++;
            }
        }
        if (width > eye_width)
            eye_width = width;
    }

    /* Calculate the max eye height */
    int eye_height = 0;
    for (int x = 0; x < eye->width; x++)
    {
        int height = 0;
        for (int y = 0; y < eye->height; y++)
        {
            if (eye->data[y][x] == 0)
            {
                height++;
                eye_area++;
            }
        }
        if (height > eye_height)
            eye_height = height;
    }

    printf("\nEye Diagram for Node %d, QLM %d, Lane %d\n", node, qlm, qlm_lane);

    if (format == 0) /* Raw */
    {
        for (int y = 0; y < eye->height; y++)
        {
            for (int x = 0; x < eye->width; x++)
                printf("%u\t", eye->data[y][x]);
            printf("\n");
        }
        result = 0;
    }
    else if ((format == 1) || (format == 2)) /* Color ASCII */
    {
        int last_color = -1;
        char color_str[] = "\33[40m"; /* Note: This is modified, not constant */

        for (int y = 0; y < eye->height; y++)
        {
            for (int x = 0; x < eye->width; x++)
            {
                int level = 0;
                if (eye->data[y][x])
                    level = int_log10(eye->data[y][x]) + 1;
                if (level > 9)
                    level = 9;
                int deltay = (y == (eye->height - 1)) ? -1 : 1;
                int deltax = (x == (eye->width - 1)) ? -1 : 1;
                uint32_t dist;
                if (eye->data[y][x] < eye->data[y + deltay][x + deltax])
                    dist = eye->data[y + deltay][x + deltax] - eye->data[y][x];
                else
                    dist = eye->data[y][x] - eye->data[y + deltay][x + deltax];
                int color = level;
                if (dist)
                    color += int_log10(dist);
                if (color > 7)
                    color = 7 - ((color - 7) & 3);
                if (color != last_color)
                {
                    color_str[3] = '0' + color;
                    fputs(color_str, stdout);
                    last_color = color;
                }
                fputc('0' + level, stdout);
            }
            fputs("\33[0m\n", stdout);
            last_color = -1;
        }
        printf("\nEye Width %d, Height %d, Area %d\n", eye_width, eye_height, eye_area);
        result = 0;
    }
    else
        result = -1;

    if (need_free)
        free((void*)eye);
    return result;
}

/**
 * Call the board specific method of determining the required QLM configuration
 * and automatically settign up the QLMs to match. For example, on the EBB8800
 * this function queries the MCU for the current setup.
 *
 * @param node   Node to configure
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_auto_config(bdk_node_t node)
{
    if (qlm_ops->auto_config)
        return qlm_ops->auto_config(node);
    bdk_error("QLM auto config is not implemented for this setup");
    return -1;
}

/**
 * Initialize the QLM layer
 */
void bdk_qlm_init(bdk_node_t node)
{
    /* Find the QLM operations for this chip */
    qlm_ops = NULL;
    int i = 0;
    while (qlm_ops_list[i])
    {
        if (bdk_is_model(qlm_ops_list[i]->chip_model))
        {
            qlm_ops = qlm_ops_list[i];
            break;
        }
        i++;
    }

    if (!qlm_ops)
        bdk_fatal("bdk_qlm_init: OPs table not found for this chip\n");

    /* Skip QLM setup in simulation */
    if (!bdk_is_model(OCTEONTX_CN8XXX) || !bdk_is_platform(BDK_PLATFORM_ASIM))
        qlm_ops->init(node);
}

/**
 * Display the current settings of a QLM lane
 *
 * @param node     Node the QLM is on
 * @param qlm      QLM to display
 * @param qlm_lane Lane to use
 * @param show_tx  Display TX parameters
 * @param show_rx  Display RX parameters
 */
void bdk_qlm_display_settings(bdk_node_t node, int qlm, int qlm_lane, bool show_tx, bool show_rx)
{
    return qlm_ops->display_settings(node, qlm, qlm_lane, show_tx, show_rx);
}

/**
 * Get a supported mode for a QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to query
 * @param index  Index into modes list. Start at zero and increment until the QLM/DLM
 *               mode is disabled.
 *
 * @return QLM/DLM mode
 */
bdk_qlm_modes_t bdk_qlm_get_mode_desc_mode(bdk_node_t node, int qlm, int index)
{
    if (!qlm_ops->get_mode_desc)
        return BDK_QLM_MODE_DISABLED;
    const bdk_qlm_mode_desc_t *descr = qlm_ops->get_mode_desc(node, qlm);
    return descr[index].mode;
}

/**
 * Get a supported flags for a QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to query
 * @param index  Index into modes list. Start at zero and increment until the QLM/DLM
 *               mode is disabled.
 *
 * @return QLM/DLM flags
 */
bdk_qlm_mode_flags_t bdk_qlm_get_mode_desc_flags(bdk_node_t node, int qlm, int index)
{
    if (!qlm_ops->get_mode_desc)
        return BDK_QLM_MODE_FLAG_NONE;
    const bdk_qlm_mode_desc_t *descr = qlm_ops->get_mode_desc(node, qlm);
    return descr[index].flags;
}

/**
 * Get a supported ref clock for a QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to query
 * @param index  Index into modes list. Start at zero and increment until the QLM/DLM
 *               mode is disabled.
 *
 * @return QLM/DLM ref clock
 */
bdk_qlm_clock_t bdk_qlm_get_mode_desc_ref_clk(bdk_node_t node, int qlm, int index)
{
    if (!qlm_ops->get_mode_desc)
        return BDK_QLM_CLK_COMMON_0;
    const bdk_qlm_mode_desc_t *descr = qlm_ops->get_mode_desc(node, qlm);
    return descr[index].ref_clk;
}

/**
 * Get a supported speed for a QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to query
 * @param index  Index into modes list. Start at zero and increment until the QLM/DLM
 *               mode is disabled.
 *
 * @return QLM/DLM speed
 */
uint16_t bdk_qlm_get_mode_desc_speed(bdk_node_t node, int qlm, int index)
{
    if (!qlm_ops->get_mode_desc)
        return 0;
    const bdk_qlm_mode_desc_t *descr = qlm_ops->get_mode_desc(node, qlm);
    return descr[index].speed;
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
int bdk_qlm_to_network(bdk_node_t node, int qlm, bool *is_split, bool *is_upper)
{
    return qlm_ops->qlm_to_network(node, qlm, is_split, is_upper);
}

