/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "bdk-qlm-common.h"
#include "bdk-qlm-common-gsern.h"
#include "libbdk-arch/bdk-csrs-gsern.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libcavm-gsern/cavm-gsern-api.h"

/**
 * Return the number of QLMs supported for the chip
 *
 * @return Number of QLMs
 */
static int qlm_get_num(bdk_node_t node)
{
    return 4; /* 3 QLM + 1 DLM */
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
    if (qlm == 3)
        return 2; /* DLM 3 */
    else
        return 4; /* QLMs 0-2 */
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
            for (int qlm = 0; qlm < 4; qlm++)
            {
                bool is_split;
                bool is_upper;
                int cgx = bdk_qlm_to_network(node, qlm, &is_split, &is_upper);
                if (cgx == interface)
                {
                    int num_lanes = qlm_get_lanes(node, qlm);
                    int lane = index;
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
                    bdk_qlm_state_lane_t state = { .u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, lane, 0)) };
                    if (state.s.cgx)
                        return qlm;
                }
            }
            return -1;
        }
        case BDK_IF_PCIE: /* PCIe */
        {
            if (interface == 0)
            {
                bdk_qlm_state_lane_t state = {.u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(0, 0, 0))};
                if (state.s.pcie)
                    return 0;
            }
            return -1;
        }
        default: /* Not supported by CNF95XX */
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

    /* Only call the code below on the first lane setup */
    if (lane && (lane != -1))
        return 0;

    /* The CNF95 is un-supported PCIE mode, but we will only use it in x1, x2 or x4 mode    */
    /* Mapping is always QLM0 for this testing.         */
    if ((mode >= BDK_QLM_MODE_PCIE_X1) && (mode <= BDK_QLM_MODE_PCIE_X16))
    {
        int lanes = (mode <= BDK_QLM_MODE_PCIE_X2) ? 0 : 1;
        bool is_rc = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
        BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(0),
            c.cn9.hostmd = is_rc;
            c.cn9.pipe_grp_ptr = 0;
            c.cn9.pipe  = 0;
            c.cn9.lanes = lanes);
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
    bdk_qlm_state_lane_t state = {.u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, lane, 0))};
    return state.s.baud_mhz;
}

static const bdk_qlm_mode_desc_t qlm0[] = {
    /* PEM0 */
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t qlm1[] = {
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
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
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
static const bdk_qlm_mode_desc_t qlm2[] = {
    /* CGX1 */
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
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
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
static const bdk_qlm_mode_desc_t dlm3[] = {
    /* CGX2 */
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
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
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
    switch (qlm)
    {
        case 0: return qlm0;
        case 1: return qlm1;
        case 2: return qlm2;
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
    /* Which CGX maps to a specific QLM/DLM
       CGX0: QLM1
       CGX1: QLM2
       CGX2: DLM3 */
    const int8_t qlm_to_cgx[4] = {-1, 0, 1, 2};
    *is_split = false;
    *is_upper = false;
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
const bdk_qlm_ops_t bdk_qlm_ops_cnf95xx = {
    .chip_model = OCTEONTX_CNF95XX_PASS1_X,
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

