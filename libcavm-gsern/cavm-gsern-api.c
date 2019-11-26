/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include "libbdk-arch/bdk-csrs-gsern.h"
#include "cavm-gsern-api.h"
#include "cavm-gsern-settings.h"
#include "cavm-gsern-init.h"

/**
 * Setup the initial mode of a GSERN serdes. This is called for the initial mode
 * set, not mode change due to auto negotiation.
 *
 * @param node     Node to setup
 * @param qlm      DLM/QLM to setup
 * @param qlm_lane Lane in QLM to setup. Only used in networking modes
 * @param mode     Mode to setup
 * @param is_first Set if this is the first DLM/QLM in a sequence used for wide
 *                 protocols. For example, PCIe x16 would set this on QLM0 but not
 *                 on QLM1-3.
 * @param baud_mhz Baud rate in MegaHertz
 * @param flags    Mode flags for optional features
 *
 * @return Zero on success, negative on failure
 */
int cavm_gsern_set_mode(int node, int qlm, int qlm_lane, enum cavm_gsern_mode mode, bool is_first, int baud_mhz, enum cavm_gsern_flags flags)
{
    enum gsern_lane_modes lane_mode;

    switch (mode)
    {
        case CAVM_GSERN_MODE_DISABLED:
            return 0;
        case CAVM_GSERN_MODE_PCIE_RC:
        case CAVM_GSERN_MODE_PCIE_EP:
            switch (baud_mhz)
            {
                case 2500:
                    lane_mode = GSERN_PCIE_02500000000;
                    break;
                case 5000:
                    lane_mode = GSERN_PCIE_05000000000;
                    break;
                case 8000:
                    lane_mode = GSERN_PCIE_08000000000;
                    break;
                case 16000:
                default:
                    lane_mode = GSERN_PCIE_16000000000;
                    break;
            }
            return cavm_gsern_init_pcie(node, qlm, is_first, flags, lane_mode);
        case CAVM_GSERN_MODE_CGX:
            switch (baud_mhz)
            {
                case 1250:
                    lane_mode = GSERN_SGMII_01250000000;
                    break;
                case 2500:
                    lane_mode = GSERN_PCIE_02500000000;
                    break;
                case 3125:
                    lane_mode = GSERN_GEN_03125000000;
                    break;
                case 5000:
                    lane_mode = GSERN_QSGMII_05000000000;
                    break;
                case 6250:
                    lane_mode = GSERN_GEN_06250000000;
                    break;
                case 10312:
                    lane_mode = GSERN_GEN_10312500000;
                    break;
                case 12890:
                    lane_mode = GSERN_GEN_12890625000;
                    break;
                case 20625:
                    lane_mode = GSERN_GEN_20625000000;
                    break;
                case 25781:
                default:
                    lane_mode = GSERN_GEN_25781250000;
                    break;
            }
            return cavm_gsern_init_network(node, qlm, qlm_lane, flags, lane_mode);
    }
    return -1;
}

