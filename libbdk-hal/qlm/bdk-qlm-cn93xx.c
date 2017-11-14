/***********************license start***********************************
 *Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
 *reserved.
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
#include "libbdk-arch/bdk-csrs-gsern.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-sata.h"

/**
 * Return the number of QLMs supported for the chip
 *
 * @return Number of QLMs
 */
static int qlm_get_num(bdk_node_t node)
{
    return 8; /* 4 QLM + 2 DLM + 2 QLM */
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
    if ((qlm == 4) || (qlm == 5))
        return 2; /* DLMs 4-5 */
    else
        return 4; /* QLMs 0-3, 6-7 */
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
        case BDK_IF_CGX:
        {
            int qlm;
            switch (interface)
            {
                case 0: /* CGX0 connects to QLM3 or QLM7 */
                    // FIXME: GERN mode
                    qlm = (0) ? 7 : 3;
                    break;
                case 1: /* CGX1 connects to DLM4, DLM5, DLM4-5 */
                {
                    /* This CGX spans two DLMs. The index must be used
                       to figure out which DLM we are using */
                    // FIXME: GERN mode
                    //BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(4));
                    if (1 /* gserx_cfg.s.bgx */)
                    {
                        if (0 /* gserx_cfg.s.bgx_quad */) /* 4 lanes together */
                            qlm = 4;
                        else if (1 /* gserx_cfg.s.bgx_dual */) /* 2 lanes together */
                            qlm = (index >= 1) ? 5 : 4;
                        else /* All lanes independent */
                        {
                            bdk_qlm_modes_t mode = bdk_qlm_get_mode(node, 4);
                            if (mode == BDK_QLM_MODE_QSGMII_4X1)
                                qlm = 4;
                            else if (mode <= BDK_QLM_MODE_PCIE_1X16)
                                qlm = 5;
                            else
                                qlm = (index >= 2) ? 5 : 4;
                        }
                    }
                    else
                        qlm = 5;
                    break;
                }
                case 2: /* CGX2 connects to QLM6 */
                    qlm = 6;
                    break;
                default:
                    return -1;
            }
            /* Make sure the QLM is powered up and out of reset */
            //BDK_CSR_INIT(common_rst_bcfg, node, BDK_GSERNX_COMMON_RST_BCFG(qlm));
            //if (common_rst_bcfg.s.pwdn || common_rst_bcfg.s.reset)
            //    return -1;
            /* Make sure the QLM is in CGX mode */
            // FIXME: GERN mode
            //BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(qlm));
            if (1 /* gserx_cfg.s.bgx */)
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
                    // FIXME: GERN mode
                    return -1;
                }
                case 1: /* PEM1 */
                {
                    // FIXME: GERN mode
                    return -1;
                }
                case 2: /* PEM2 */
                {
                    // FIXME: GERN mode
                    return -1;
                }
                case 3: /* PEM3 */
                {
                    // FIXME: GERN mode
                    return -1;
                }
                default: /* Max of 4 PEMs, 0-3 */
                    return -1;
            }
        }
        default: /* Not supported by CN93XX */
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
    switch (qlm)
    {
        case 0:
            return BDK_QLM_MODE_PCIE_1X8;
        case 1:
            return BDK_QLM_MODE_PCIE_1X8;
        case 2:
            return BDK_QLM_MODE_PCIE_1X4;
        case 3:
            return BDK_QLM_MODE_XFI_4X1;
        case 4:
            return BDK_QLM_MODE_RXAUI_1X2;
        case 5:
            return BDK_QLM_MODE_SATA_2X1;
        case 6:
            return BDK_QLM_MODE_XFI_4X1;
        case 7:
            return BDK_QLM_MODE_XLAUI_1X4;
        default:
            return BDK_QLM_MODE_DISABLED;
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
    switch (mode)
    {
        case BDK_QLM_MODE_SATA_2X1:
        case BDK_QLM_MODE_SATA_4X1:
        {
            int sata_port = (qlm == 4) ? 0 : 2;
            return __bdk_qlm_set_sata_cn9xxx(node, qlm, baud_mhz, sata_port, sata_port + 1);
        }
        default:
            return -1;
    }
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
    switch (qlm)
    {
        case 0:
            return 8000;
        case 1:
            return 8000;
        case 2:
            return 8000;
        case 3:
            return 10312;
        case 4:
            return 6250;
        case 5:
            return 6000;
        case 6:
            return 10312;
        case 7:
            return 10312;
        default:
            return 0;
    }
}

/**
 * Initialize the QLM layer
 */
static void qlm_init(bdk_node_t node)
{
}

/* Each chip has its own QLM operation table */
const bdk_qlm_ops_t bdk_qlm_ops_cn93xx = {
    .chip_model = CAVIUM_CN93XX,
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

