/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "bdk-qlm-common.h"
#include "bdk-qlm-common-gsern.h"
#include "libbdk-arch/bdk-csrs-cgx.h"
#include "libbdk-arch/bdk-csrs-gsern.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libcavm-gsern/cavm-gsern-api.h"

/**
 * Figure out which PEM, pipe, and pipe group connect to a QLM/DLM. Yep, these
 * are all magic values.
 *
 * @param qlm      QLM that is in PCIe mode
 * @param mode     The mode of the PCIe. We need the width to figure out how it hooks up
 * @param pipe_grp_ptr
 *                 PEM value
 * @param pem_pipe PEM value
 * @param pipe_tx_sel
 *                 GSERN value
 *
 * @return PEM in use, or -1 if illegal
 */
static int map_qlm_to_pem(int qlm, bdk_qlm_modes_t mode, int *pipe_grp_ptr, int *pem_pipe, int *pipe_tx_sel)
{
    int pem = -1;
    /* Which PEM maps to a specific QLM/DLM
       PEM0: QLM0 spanning up to QLM3
       PEM1: QLM1, or DLM4 spanning up to DLM5
       PEM2: QLM3, DLM5, QLM6 spanning up to QLM7
       PEM3: QLM2 spanning up to QLM3 */
    switch (qlm)
    {
        case 0:
            switch (mode)
            {
                case BDK_QLM_MODE_PCIE_X1:
                case BDK_QLM_MODE_PCIE_X2:
                case BDK_QLM_MODE_PCIE_X4:
                case BDK_QLM_MODE_PCIE_X8:
                case BDK_QLM_MODE_PCIE_X16:
                    *pipe_grp_ptr = 0; /* PEM0: Configure to grp0 (QLM0/1/2/3) */
                    *pem_pipe = 0; /* PEM0 pipe0 (QLM0/1/2/3) */
                    *pipe_tx_sel = 0; /* Known good */
                    pem = 0; /* PEM0 up to 16 lanes */
                    break;
                default:
                    break;
            }
            break;
        case 1:
            switch (mode)
            {
                case BDK_QLM_MODE_PCIE_X1:
                case BDK_QLM_MODE_PCIE_X2:
                case BDK_QLM_MODE_PCIE_X4:
                    *pipe_grp_ptr = 0; /* PEM1: Configure to grp0 (QLM1) */
                    *pem_pipe = 0; /* PEM1 pipe0 (QLM1) */
                    *pipe_tx_sel = 1;
                    pem = 1; /* PEM1 up to 4 lanes */
                    break;
                case BDK_QLM_MODE_PCIE_X8:
                case BDK_QLM_MODE_PCIE_X16:
                    *pipe_grp_ptr = 0; /* PEM0: Configure to grp0 (QLM0/1/2/3) */
                    *pem_pipe = 0; /* PEM0 pipe0 (QLM0/1/2/3) */
                    *pipe_tx_sel = 0; /* Known good */
                    pem = 0; /* PEM0 up to 16 lanes */
                    break;
                default:
                    break;
            }
            break;
        case 2:
            switch (mode)
            {
                case BDK_QLM_MODE_PCIE_X1:
                case BDK_QLM_MODE_PCIE_X2:
                case BDK_QLM_MODE_PCIE_X4:
                case BDK_QLM_MODE_PCIE_X8:
                    *pipe_grp_ptr = 0; /* PEM3: Configure to grp0 (QLM2/3) */
                    *pem_pipe = 0; /* PEM3 pipe0 (QLM2/3) */
                    *pipe_tx_sel = 1; /* Known good */
                    pem = 3; /* PEM3 up to 8 lanes */
                    break;
                case BDK_QLM_MODE_PCIE_X16:
                    *pipe_grp_ptr = 0; /* PEM0: Configure to grp0 (QLM0/1/2/3) */
                    *pem_pipe = 0; /* PEM0 pipe0 (QLM0/1/2/3) */
                    *pipe_tx_sel = 0; /* Known good */
                    pem = 0; /* PEM0 up to 16 lanes */
                    break;
                default:
                    break;
            }
            break;
        case 3:
            switch (mode)
            {
                case BDK_QLM_MODE_PCIE_X1:
                case BDK_QLM_MODE_PCIE_X2:
                case BDK_QLM_MODE_PCIE_X4:
                    *pipe_grp_ptr = 0; /* PEM2: Configure to grp0 (QLM3) */
                    *pem_pipe = 0; /* PEM2 pipe0 (QLM3) */
                    *pipe_tx_sel = 2;
                    pem = 2; /* PEM2 up to 4 lanes */
                    break;
                case BDK_QLM_MODE_PCIE_X8:
                    *pipe_grp_ptr = 0; /* PEM3: Configure to grp0 (QLM2/3) */
                    *pem_pipe = 0; /* PEM3 pipe0 (QLM2/3) */
                    *pipe_tx_sel = 1; /* Known good */
                    pem = 3; /* PEM3 up to 8 lanes */
                    break;
                case BDK_QLM_MODE_PCIE_X16:
                    *pipe_grp_ptr = 0; /* PEM0: Configure to grp0 (QLM0/1/2/3) */
                    *pem_pipe = 0; /* PEM0 pipe0 (QLM0/1/2/3) */
                    *pipe_tx_sel = 0; /* Known good */
                    pem = 0; /* PEM0 up to 16 lanes */
                    break;
                default:
                    break;
            }
            break;
        case 4:
            switch (mode)
            {
                case BDK_QLM_MODE_PCIE_X1:
                case BDK_QLM_MODE_PCIE_X2:
                case BDK_QLM_MODE_PCIE_X4:
                    *pipe_grp_ptr = 1; /* PEM1: Configure to grp1 (DLM4/5) */
                    *pem_pipe = 1; /* PEM1 pipe1 (DLM4/5) */
                    *pipe_tx_sel = 0;
                    pem = 1; /* PEM1 up to 4 lanes */
                    break;
                default:
                    break;
            }
            break;
        case 5:
            switch (mode)
            {
                case BDK_QLM_MODE_PCIE_X1:
                case BDK_QLM_MODE_PCIE_X2:
                    *pipe_grp_ptr = 1; /* PEM2: Configure to grp1 (DLM5) */
                    *pem_pipe = 1; /* PEM2 pipe1 (DLM5) */
                    *pipe_tx_sel = 1;
                    pem = 2; /* PEM2 only with 2 lanes */
                    break;
                case BDK_QLM_MODE_PCIE_X4:
                    *pipe_grp_ptr = 1; /* PEM1: Configure to grp1 (DLM4/5) */
                    *pem_pipe = 1; /* PEM1 pipe1 (DLM4/5) */
                    *pipe_tx_sel = 0;
                    pem = 1; /* PEM1 only with 4 lanes */
                    break;
                default:
                    break;
            }
            break;
        case 6:
            switch (mode)
            {
                case BDK_QLM_MODE_PCIE_X1:
                case BDK_QLM_MODE_PCIE_X2:
                case BDK_QLM_MODE_PCIE_X4:
                case BDK_QLM_MODE_PCIE_X8:
                    *pipe_grp_ptr = 2; /* PEM2: Configure to grp2 (QLM6/7) */
                    *pem_pipe = 2; /* PEM2 pipe2 (QLM6/7) */
                    *pipe_tx_sel = 0;
                    pem = 2; /* PEM2 up to 8 lanes */
                    break;
                default:
                    break;
            }
            break;
        case 7:
            switch (mode)
            {
                case BDK_QLM_MODE_PCIE_X8:
                    *pipe_grp_ptr = 2; /* PEM2: Configure to grp2 (QLM6/7) */
                    *pem_pipe = 2; /* PEM2 pipe2 (QLM6/7) */
                    *pipe_tx_sel = 0;
                    pem = 2; /* PEM2 only with 8 lanes */
                    break;
                default:
                    break;
            }
            break;
    }
    return pem;
}

/**
 * Return the number of QLMs supported for the chip
 *
 * @return Number of QLMs
 */
static int qlm_get_num(bdk_node_t node)
{
    switch (bdk_is_altpkg(OCTEONTX_CN96XX))
    {
        case OCTEONTX_ALT_CN93XX: /* CN93XX */
            return 6; /* 4 QLM + 2 DLM */
        case OCTEONTX_ALT_CN95XXE: /* CN95XXE */
        default:
            return 8; /* 4 QLM + 2 DLM + 2 QLM */
    }
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
            for (int qlm = 0; qlm < 8; qlm++)
            {
                bool is_split;
                bool is_upper;
                int cgx = bdk_qlm_to_network(node, qlm, &is_split, &is_upper);
                if (cgx == interface)
                {
                    BDK_CSR_INIT(cmrx, node, BDK_CGXX_CMRX_CONFIG(cgx, 0));
                    int num_lanes = qlm_get_lanes(node, qlm);
                    int lane = (cmrx.s.lane_to_sds >> (index * 2)) & 3;
                    if (is_upper)
                    {
                        /* Upper doesn't match until index is in 2nd DLM */
                        if (lane < num_lanes)
                        {
                            bdk_qlm_state_lane_t state = { .u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, 0, 0)) };
                            /* QSGMII and USXGMII are special in that all LMACs map to one lane */
                            if ((state.s.mode == BDK_QLM_MODE_QSGMII) || (state.s.mode == BDK_QLM_MODE_USXGMII_4X1))
                                lane = num_lanes;
                            else
                                continue;
                        }
                        lane -= num_lanes;
                    }
                    else
                    {
                        /* Check that this shouldn't be in the next half */
                        if (lane >= num_lanes)
                        {
                            bdk_qlm_state_lane_t state = { .u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, 0, 0)) };
                            /* QSGMII and USXGMII are special in that all LMACs map to one lane */
                            if ((state.s.mode == BDK_QLM_MODE_QSGMII) || (state.s.mode == BDK_QLM_MODE_USXGMII_4X1))
                                lane = 0;
                            else
                                continue;
                        }
                    }
                    bdk_qlm_state_lane_t state = { .u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, lane, 0)) };
                    if (state.s.cgx)
                        return qlm;
                }
            }
            return -1;
        }
        case BDK_IF_PCIE: /* PCIe */
        {
            for (int qlm = 0; qlm < 8; qlm++)
            {
                bdk_qlm_state_lane_t state = {.u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, 0, 0))};
                int pipe_grp_ptr;
                int pem_pipe;
                int pipe_tx_sel;
                int pem = map_qlm_to_pem(qlm, state.s.mode, &pipe_grp_ptr, &pem_pipe, &pipe_tx_sel);
                if (pem == interface)
                    return qlm;
            }
            return -1;
        }
        default: /* Not supported by CN96XX */
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
    bdk_qlm_state_lane_t state = {.u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, lane, 0))};
    return state.s.mode;
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
    int status = __bdk_qlm_set_mode_gsern(node, qlm, lane, mode, baud_mhz, flags);
    if (status)
        return status;

    /* CGX0 routes to either to QLM3 or QLM7. Setup the routing when
       a network mode is selected on either of these QLMs */
    if ((mode >= BDK_QLM_MODE_SGMII) && ((qlm == 3) || (qlm == 7)))
    {
        BDK_CSR_MODIFY(c, node, BDK_CGXX_CMR_GLOBAL_CONFIG(0),
            c.s.pmux_sds_sel = (qlm == 7));
    }

    /* Only call the code below on the first lane setup */
    if (lane && (lane != -1))
        return 0;

    if ((mode >= BDK_QLM_MODE_PCIE_X1) && (mode <= BDK_QLM_MODE_PCIE_X16))
    {
        bool is_rc = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
        int lanes;
        int pipe_grp_ptr;
        int pem_pipe;
        int pipe_tx_sel;
        int pem = map_qlm_to_pem(qlm, mode, &pipe_grp_ptr, &pem_pipe, &pipe_tx_sel);
        if (pem >= 0)
        {
            /* LANES= 0= 2 lanes, 1= 4 lanes, 2 = 8 lanes, 3= 16 lanes */
            /* Because of Lane Swizzling, the pipe width has to be a minimum
                of the QLM width. We Really need a flag to indicate we are doing
                lane reversal, which is the only reason the pipe width is set to
                this value. QLM lanes is either 2 or 4 */
            int qlm_lanes = bdk_qlm_get_lanes(node, qlm);

            /* So, its only an issue when the mode is x1 or x2 */
            /* The width has to be the width of the QLM */
            if ((mode == BDK_QLM_MODE_PCIE_X1) || (mode == BDK_QLM_MODE_PCIE_X2))
                lanes = (qlm_lanes == 2) ? 0 : 1;
            else
                lanes = mode - 2;

            BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(pem),
                c.cn9.auto_dp_clr = is_rc;
                c.cn9.pipe_grp_ptr = pipe_grp_ptr;
                c.cn9.pipe = pem_pipe;
                c.cn9.lanes  = lanes;
                c.cn9.hostmd = is_rc);
            /* GSERN also has a pipe selection */
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_PCS2_BCFG(qlm, 4),
                c.s.pipe_tx_sel = pipe_tx_sel);
            __bdk_qlm_setup_pem_reset_gsern(node, pem, !is_rc);
        }
    }

    switch (mode)
    {
        case BDK_QLM_MODE_PCIE_X4:
        {
            if (qlm == 4)
            {
                BDK_CSR_INIT(bcfg, node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm));
                BDK_CSR_WRITE(node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm + 1), bcfg.u);
                return qlm_set_mode(node, qlm + 1, -1, mode, baud_mhz, flags);
            }
            return 0;
        }
        case BDK_QLM_MODE_PCIE_X8:
        {
            if ((qlm & 1) == 0)
            {
                BDK_CSR_INIT(bcfg, node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm));
                BDK_CSR_WRITE(node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm + 1), bcfg.u);
                return qlm_set_mode(node, qlm + 1, -1, mode, baud_mhz, flags);
            }
            return 0;
        }
        case BDK_QLM_MODE_PCIE_X16:
        {
            if ((qlm & 3) == 0)
            {
                BDK_CSR_INIT(bcfg, node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm));
                for (int q = qlm + 1; q < qlm + 4; q++)
                {
                    BDK_CSR_WRITE(node, BDK_GSERNX_COMMON_REFCLK_BCFG(q), bcfg.u);
                    int result = qlm_set_mode(node, q, -1, mode, baud_mhz, flags);
                    if (result)
                        return result;
                }
            }
            return 0;
        }
        case BDK_QLM_MODE_XAUI:
        case BDK_QLM_MODE_XLAUI:
        case BDK_QLM_MODE_XLAUI_C2M:
        case BDK_QLM_MODE_40G_CR4:
        case BDK_QLM_MODE_40G_KR4:
        case BDK_QLM_MODE_80GAUI_4_C2C:
        case BDK_QLM_MODE_CAUI_4_C2C:
        case BDK_QLM_MODE_CAUI_4_C2M:
        case BDK_QLM_MODE_100G_CR4:
        case BDK_QLM_MODE_100G_KR4:
            if (qlm == 4)
            {
                BDK_CSR_INIT(bcfg, node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm));
                BDK_CSR_WRITE(node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm + 1), bcfg.u);
                return qlm_set_mode(node, qlm + 1, -1, mode, baud_mhz, flags);
            }
            return 0;

        default:
            return 0;
    }
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
    bdk_qlm_state_lane_t state = {.u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, lane, 0))};
    return state.s.baud_mhz;
}

static const bdk_qlm_mode_desc_t qlm0[] = {
    /* PEM 0 - 4 lane mode */
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    /* PEM 0 - 8 lane mode (also uses QLM1) */
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    /* PEM 0 - 16 lane mode (also uses QLM1-3) */
    {BDK_QLM_MODE_PCIE_X16,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X16,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X16,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X16,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t qlm1[] = {
    /* PEM 1 - 4 lane mode */
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t qlm2[] = {
    /* PEM 2 - 4 lane mode */
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    /* PEM 3 - 8 lane mode (also uses QLM3) */
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t qlm3[] = {
    /* CGX0 */
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 5000},
    {BDK_QLM_MODE_XAUI,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 3125},
    {BDK_QLM_MODE_XAUI,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_SFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_XLAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_XLAUI_C2M,    BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_40G_CR4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_40G_KR4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_20GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_25GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_CR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 12890},
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_4_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 12890},
    {BDK_QLM_MODE_80GAUI_4_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_CAUI_4_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_CAUI_4_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_100G_CR4,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_100G_KR4,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    //{BDK_QLM_MODE_USXGMII_4X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_2X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_1X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    /* PEM 2 - 4 lane mode */
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t dlm4[] = {
    /* CGX1 */
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 5000},
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_SFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_20GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_25GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_CR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 12890},
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    //{BDK_QLM_MODE_USXGMII_4X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_2X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_1X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    /* PEM 1 - 4 lane mode */
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    /* PEM 1 - 2 lane mode */
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t dlm5[] = {
    /* CGX1 */
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 5000},
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_SFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_20GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_25GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_CR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 12890},
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    //{BDK_QLM_MODE_USXGMII_4X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_2X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_1X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    /* PEM 2 - 2 lane mode */
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t qlm6[] = {
    /* CGX2 */
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 5000},
    {BDK_QLM_MODE_XAUI,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 3125},
    {BDK_QLM_MODE_XAUI,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_SFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_XLAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_XLAUI_C2M,    BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_40G_CR4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_40G_KR4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_20GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_25GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_CR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 12890},
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_4_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 12890},
    {BDK_QLM_MODE_80GAUI_4_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_CAUI_4_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_CAUI_4_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_100G_CR4,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_100G_KR4,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    //{BDK_QLM_MODE_USXGMII_4X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_2X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_1X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    /* PEM 2 - 4 lane mode */
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    /* PEM 2 - 8 lane mode (also uses QLM1) */
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X8,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t qlm7[] = {
    /* CGX0 */
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 5000},
    {BDK_QLM_MODE_XAUI,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 3125},
    {BDK_QLM_MODE_XAUI,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_SFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_XLAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_XLAUI_C2M,    BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_40G_CR4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_40G_KR4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_20GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_25GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_CR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 12890},
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_4_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 12890},
    {BDK_QLM_MODE_80GAUI_4_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_CAUI_4_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_CAUI_4_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_100G_CR4,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_100G_KR4,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    //{BDK_QLM_MODE_USXGMII_4X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_2X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    //{BDK_QLM_MODE_USXGMII_1X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
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
    switch (bdk_is_altpkg(OCTEONTX_CN96XX))
    {
        case OCTEONTX_ALT_CN93XX: /* CN93XX */
            switch (qlm)
            {
                case 0: return qlm0;
                case 1: return qlm1;
                case 2: return qlm2;
                case 3: return qlm3;
                case 4: return dlm4;
                case 5: return dlm5;
                default: return NULL;
            }
        case OCTEONTX_ALT_CN95XXE: /* CN95XXE */
            switch (qlm)
            {
                case 3: return qlm1; /* Package QLM0. Return CN96XX QLM1 as it only supports PCIe x4 */
                case 4: return dlm5; /* Package DLM3 */
                case 6: return qlm6; /* Package QLM2 */
                case 7: return qlm7; /* Package QLM1 */
                default: return NULL;
            }
        default: /* 0 = CN96XX */
            switch (qlm)
            {
                case 0: return qlm0;
                case 1: return qlm1;
                case 2: return qlm2;
                case 3: return qlm3;
                case 4: return dlm4;
                case 5: return dlm5;
                case 6: return qlm6;
                case 7: return qlm7;
                default: return NULL;
            }
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
    /* Which CGX maps to a specific QLM/DLM
       CGX0: QLM3 or QLM7
       CGX1: DLM4+DLM5
       CGX2: QLM6 */
    const int8_t qlm_to_cgx[8] = {-1, -1, -1, 0, 1, 1, 2, 0};
    *is_split = (qlm == 4) || (qlm == 5);
    *is_upper = (qlm == 5);
    return qlm_to_cgx[qlm];
}

/**
 * Initialize the QLM layer
 */
static void qlm_init(bdk_node_t node)
{
    __bdk_qlm_init_gsern(node);
}

/* Each chip has its own QLM operation table */
const bdk_qlm_ops_t bdk_qlm_ops_cn96xx = {
    .chip_model = OCTEONTX_CN96XX_PASS1_X,
    .init = qlm_init,
    .get_num = qlm_get_num,
    .get_lanes = qlm_get_lanes,
    .get_mode = qlm_get_mode,
    .set_mode = qlm_set_mode,
    .get_gbaud_mhz = qlm_get_gbaud_mhz,
    .measure_refclock = __bdk_qlm_measure_refclock_gsern,
    .get_qlm_num = qlm_get_qlm_num,
    .reset = __bdk_qlm_reset_gsern,
    .enable_prbs = __bdk_qlm_enable_prbs_gsern,
    .disable_prbs = __bdk_qlm_disable_prbs_gsern,
    .get_prbs_errors = __bdk_qlm_get_prbs_errors_gsern,
    .inject_prbs_error = __bdk_qlm_inject_prbs_error_gsern,
    .enable_loop = __bdk_qlm_enable_loop_gsern,
    .auto_config = bdk_qlm_mcu_auto_config,
    .tune_lane_tx = __bdk_qlm_tune_lane_tx_gsern,
    .get_tune_lane_tx = __bdk_qlm_get_tune_lane_tx_gsern,
    .rx_equalization = __bdk_qlm_rx_equalization_gsern,
    .eye_capture = cavm_gsern_eye_capture,
    .display_settings = __bdk_qlm_display_settings_gsern,
    .get_mode_desc = qlm_get_mode_desc,
    .qlm_to_network = qlm_to_network,
};

