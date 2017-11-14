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
#include <stdio.h>
#include <math.h>
#include "libbdk-arch/bdk-csrs-gser.h"
#include "libbdk-arch/bdk-csrs-gsern.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(QLM);

/* Each chip has its own QLM operation table */
extern const bdk_qlm_ops_t bdk_qlm_ops_cn88xx;
extern const bdk_qlm_ops_t bdk_qlm_ops_cn83xx;
extern const bdk_qlm_ops_t bdk_qlm_ops_cn81xx;
extern const bdk_qlm_ops_t bdk_qlm_ops_cn93xx;

static const bdk_qlm_ops_t *qlm_ops_list[] = {
    &bdk_qlm_ops_cn88xx,
    &bdk_qlm_ops_cn83xx,
    &bdk_qlm_ops_cn81xx,
    &bdk_qlm_ops_cn93xx,
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
#define MODE_CASE(m) case m: return #m+13
    switch (mode)
    {
        MODE_CASE(BDK_QLM_MODE_DISABLED);
        MODE_CASE(BDK_QLM_MODE_PCIE_1X1);
        MODE_CASE(BDK_QLM_MODE_PCIE_2X1);
        MODE_CASE(BDK_QLM_MODE_PCIE_1X2);
        MODE_CASE(BDK_QLM_MODE_PCIE_1X4);
        MODE_CASE(BDK_QLM_MODE_PCIE_1X8);
        MODE_CASE(BDK_QLM_MODE_PCIE_1X16);

        MODE_CASE(BDK_QLM_MODE_SATA_4X1);
        MODE_CASE(BDK_QLM_MODE_SATA_2X1);

        MODE_CASE(BDK_QLM_MODE_ILK);
        MODE_CASE(BDK_QLM_MODE_SGMII_4X1);
        MODE_CASE(BDK_QLM_MODE_SGMII_2X1);
        MODE_CASE(BDK_QLM_MODE_SGMII_1X1);
        MODE_CASE(BDK_QLM_MODE_XAUI_1X4);
        MODE_CASE(BDK_QLM_MODE_RXAUI_2X2);
        MODE_CASE(BDK_QLM_MODE_RXAUI_1X2);
        MODE_CASE(BDK_QLM_MODE_OCI);
        MODE_CASE(BDK_QLM_MODE_XFI_4X1);
        MODE_CASE(BDK_QLM_MODE_XFI_2X1);
        MODE_CASE(BDK_QLM_MODE_XFI_1X1);
        MODE_CASE(BDK_QLM_MODE_XLAUI_1X4);
        MODE_CASE(BDK_QLM_MODE_10G_KR_4X1);
        MODE_CASE(BDK_QLM_MODE_10G_KR_2X1);
        MODE_CASE(BDK_QLM_MODE_10G_KR_1X1);
        MODE_CASE(BDK_QLM_MODE_40G_KR4_1X4);
        MODE_CASE(BDK_QLM_MODE_QSGMII_4X1);
        MODE_CASE(BDK_QLM_MODE_25G_4X1);
        MODE_CASE(BDK_QLM_MODE_25G_2X1);
        MODE_CASE(BDK_QLM_MODE_50G_2X2);
        MODE_CASE(BDK_QLM_MODE_50G_1X2);
        MODE_CASE(BDK_QLM_MODE_100G_1X4);
        MODE_CASE(BDK_QLM_MODE_25G_KR_4X1);
        MODE_CASE(BDK_QLM_MODE_25G_KR_2X1);
        MODE_CASE(BDK_QLM_MODE_50G_KR_2X2);
        MODE_CASE(BDK_QLM_MODE_50G_KR_1X2);
        MODE_CASE(BDK_QLM_MODE_100G_KR4_1X4);
        MODE_CASE(BDK_QLM_MODE_USXGMII_4X1);
        MODE_CASE(BDK_QLM_MODE_USXGMII_2X1);

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

    for (mode = 0; mode < BDK_QLM_MODE_LAST; mode++)
    {
        if (0 == strcmp(val, bdk_qlm_mode_to_cfg_str(mode)))
        {
            return mode;
        }
    }
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
        case BDK_QLM_MODE_PCIE_1X1:
            result = "1 PCIe, 1 lane";
            break;
        case BDK_QLM_MODE_PCIE_2X1:
            result = "2 PCIe, 1 lane each";
            break;
        case BDK_QLM_MODE_PCIE_1X2:
            result = "1 PCIe, 2 lanes";
            break;
        case BDK_QLM_MODE_PCIE_1X4:
            result = "1 PCIe, 4 lanes";
            break;
        case BDK_QLM_MODE_PCIE_1X8:
            result = "1 PCIe, 8 lanes";
            break;
        case BDK_QLM_MODE_PCIE_1X16:
            result = "1 PCIe, 16 lanes";
            break;

        case BDK_QLM_MODE_SATA_4X1:
            result = "4 SATA, one lane each";
            break;
        case BDK_QLM_MODE_SATA_2X1:
            result = "2 SATA, one lane each";
            break;

        case BDK_QLM_MODE_ILK:
            result = "Interlaken";
            break;
        case BDK_QLM_MODE_SGMII_4X1:
            result = "4 SGMII, 1 lane each";
            break;
        case BDK_QLM_MODE_SGMII_2X1:
            result = "2 SGMII, 1 lane each";
            break;
        case BDK_QLM_MODE_SGMII_1X1:
            result = "1 SGMII, 1 lane";
            break;
        case BDK_QLM_MODE_XAUI_1X4:
            result = "1 XAUI, 4 lanes";
            break;
        case BDK_QLM_MODE_RXAUI_2X2:
            result = "2 RXAUI, 2 lanes each";
            break;
        case BDK_QLM_MODE_RXAUI_1X2:
            result = "1 RXAUI, 2 lanes each";
            break;
        case BDK_QLM_MODE_OCI:
            result = "Cavium Coherent Processor Interconnect";
            break;
        case BDK_QLM_MODE_XFI_4X1:
            result = "4 XFI, 1 lane each";
            break;
        case BDK_QLM_MODE_XFI_2X1:
            result = "2 XFI, 1 lane each";
            break;
        case BDK_QLM_MODE_XFI_1X1:
            result = "1 XFI, 1 lane";
            break;
        case BDK_QLM_MODE_XLAUI_1X4:
            result = "1 XLAUI, 4 lanes";
            break;
        case BDK_QLM_MODE_10G_KR_4X1:
            result = "4 10GBASE-KR, 1 lane each";
            break;
        case BDK_QLM_MODE_10G_KR_2X1:
            result = "2 10GBASE-KR, 1 lane each";
            break;
        case BDK_QLM_MODE_10G_KR_1X1:
            result = "1 10GBASE-KR, 1 lane";
            break;
        case BDK_QLM_MODE_40G_KR4_1X4:
            result = "1 40GBASE-KR4, 4 lanes";
            break;
        case BDK_QLM_MODE_QSGMII_4X1:
            result = "4 QSGMII, 1 lane";
            break;
        case BDK_QLM_MODE_25G_4X1:
            result = "4 25G, 1 lane each";
            break;
        case BDK_QLM_MODE_25G_2X1:
            result = "2 25G, 1 lane each";
            break;
        case BDK_QLM_MODE_50G_2X2:
            result = "2 50G, 2 lanes each";
            break;
        case BDK_QLM_MODE_50G_1X2:
            result = "1 50G, 2 lanes";
            break;
        case BDK_QLM_MODE_100G_1X4:
            result = "1 100G, 4 lanes";
            break;
        case BDK_QLM_MODE_25G_KR_4X1:
            result = "4 25G, 1 lane each";
            break;
        case BDK_QLM_MODE_25G_KR_2X1:
            result = "2 25G, 1 lane each";
            break;
        case BDK_QLM_MODE_50G_KR_2X2:
            result = "2 50G, 2 lanes each";
            break;
        case BDK_QLM_MODE_50G_KR_1X2:
            result = "1 50G, 2 lanes";
            break;
        case BDK_QLM_MODE_100G_KR4_1X4:
            result = "1 100G, 4 lanes";
            break;
        case BDK_QLM_MODE_USXGMII_4X1:
            result = "4 USXGMII, 1 lane each";
            break;
        case BDK_QLM_MODE_USXGMII_2X1:
            result = "2 USXGMII, 1 lane each";
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
 *
 * @return String mode
 */
bdk_qlm_modes_t bdk_qlm_get_mode(bdk_node_t node, int qlm)
{
    return qlm_ops->get_mode(node, qlm);
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
int bdk_qlm_set_mode(bdk_node_t node, int qlm, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    return qlm_ops->set_mode(node, qlm, mode, baud_mhz, flags);
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
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
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
    else
    {
        int cclksel;
        switch (clk)
        {
            case BDK_QLM_CLK_COMMON_0:
                cclksel = 0;
                break;
            case BDK_QLM_CLK_COMMON_1:
                cclksel = 1;
                break;
            case BDK_QLM_CLK_COMMON_2:
                cclksel = 2;
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
            c.s.pwdn = (clk == BDK_QLM_CLK_EXTERNAL) ? 0 : 1;
            c.s.cclksel = cclksel);
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
int bdk_qlm_get_gbaud_mhz(bdk_node_t node, int qlm)
{
    return qlm_ops->get_gbaud_mhz(node, qlm);
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
 * @param node      Node to configure
 * @param qlm       QLM to configure
 * @param lane      Lane to configure
 * @param tx_swing  Transmit swing (coef 0) Range 0-31
 * @param tx_pre    Pre cursor emphasis (Coef -1). Range 0-15
 * @param tx_post   Post cursor emphasis (Coef +1). Range 0-31
 * @param tx_gain   Transmit gain. Range 0-7
 * @param tx_vboost Transmit voltage boost. Range 0-1
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_tune_lane_tx(bdk_node_t node, int qlm, int lane, int tx_swing, int tx_pre, int tx_post, int tx_gain, int tx_vboost)
{
    return qlm_ops->tune_lane_tx(node, qlm, lane, tx_swing, tx_pre, tx_post, tx_gain, tx_vboost);
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
 * @param node     Node to use in numa setup
 * @param qlm      QLM to use
 * @param qlm_lane Which lane
 * @param eye      Output eye data
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_eye_capture(bdk_node_t node, int qlm, int qlm_lane, bdk_qlm_eye_t *eye)
{
    if (qlm_ops->eye_capture)
        return qlm_ops->eye_capture(node, qlm, qlm_lane, eye);
    else
    {
        bdk_error("Eye capture not supported on this chip\n");
        return -1;
    }
}

/**
 * Display an eye diagram for the given QLM lane. The eye data can be in "eye", or
 * captured during the call if "eye" is NULL.
 *
 * @param node     Node to use in numa setup
 * @param qlm      QLM to use
 * @param qlm_lane Which lane
 * @param format   Display format. 0 = raw, 1 = Color ASCII
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
        if (bdk_qlm_eye_capture(node, qlm, qlm_lane, eye_data))
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
    else if (format == 1) /* Color ASCII */
    {
        int last_color = -1;
        char color_str[] = "\33[40m"; /* Note: This is modified, not constant */

        for (int y = 0; y < eye->height-1; y++)
        {
            for (int x = 0; x < eye->width-1; x++)
            {
                #define DIFF(a,b) (a<b) ? b-a : a-b
                int64_t dy = DIFF(eye->data[y][x], eye->data[y + 1][x]);
                int64_t dx = DIFF(eye->data[y][x], eye->data[y][x + 1]);
                #undef DIFF
                int64_t dist = dx * dx + dy * dy;
                double f = log10(sqrt(dist) + 1);
                const double MAX_LOG = 6;
                if (f > MAX_LOG)
                    f = MAX_LOG;
                int level = 9 * f / MAX_LOG + 0.5;
                int color = 7.0 * f / MAX_LOG + 0.5;
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
 * Call the board specific method of determining the required QLM configuration
 * and automatically settign up the QLMs to match. For example, on the SFF8100
 * this function queries the GPIO pins for the current setup.
 *
 * @param node   Node to configure
 *
 * @return Zero on success, negative on failure
 */
int bdk_qlm_dip_auto_config(bdk_node_t node)
{
    if (qlm_ops->dip_auto_config)
        return qlm_ops->dip_auto_config(node);
    bdk_error("QLM DIP auto config is not implemented for this setup");
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
        if (CAVIUM_IS_MODEL(qlm_ops_list[i]->chip_model))
        {
            qlm_ops = qlm_ops_list[i];
            break;
        }
        i++;
    }

    if (!qlm_ops)
        bdk_fatal("bdk_qlm_init: OPs table not found for this chip\n");

    /* Skip QLM setup in simulation */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
        qlm_ops->init(node);
}

