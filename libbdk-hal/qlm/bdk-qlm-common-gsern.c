/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include "bdk-qlm-common.h"
#include "bdk-qlm-common-gsern.h"
#include "libbdk-arch/bdk-csrs-gsern.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-tsn.h"
#include "libcavm-gsern/cavm-gsern-api.h"
#include "libcavm-gsern/cavm-gsern-settings.h"
#include "libcavm-gsern/cavm-gsern-init.h"

static const int TX_TUNING_INVALID = -1000;
static const int TX_TUNING_IDLE = -2000;

/**
 * Structure to define default tuning parameters
 */
typedef struct
{
    bdk_qlm_modes_t mode : 16;
    uint16_t baud_mhz;
    uint8_t tx_cmain;
    uint8_t tx_cpre;
    uint8_t tx_cpost;
    uint8_t tx_bs;
} default_tuning_t;

static const default_tuning_t DEF_TUNING[] = {
    { BDK_QLM_MODE_PCIE_X1,       2500, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X1,       5000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X1,       8000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X1,      16000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X2,       2500, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X2,       5000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X2,       8000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X2,      16000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X4,       2500, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X4,       5000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X4,       8000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X4,      16000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X8,       2500, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X8,       5000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X8,       8000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X8,      16000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X16,      2500, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X16,      5000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X16,      8000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_PCIE_X16,     16000, 24, 0,  0, 52 },
    { BDK_QLM_MODE_SGMII,         1250, 29, 0,  0, 42 },
    { BDK_QLM_MODE_1G_X,          1250, 29, 0,  0, 42 },
    { BDK_QLM_MODE_QSGMII,        5000, 29, 0,  0, 42 },
    { BDK_QLM_MODE_XAUI,          3125, 48, 0,  0, 42 },
    { BDK_QLM_MODE_XAUI,          6250, 48, 0,  0, 42 },
    { BDK_QLM_MODE_RXAUI,         6250, 48, 0,  0, 42 },
    { BDK_QLM_MODE_XFI,          10312, 29, 0,  0, 42 },
    { BDK_QLM_MODE_SFI,          10312, 40, 6,  2, 42 },
    { BDK_QLM_MODE_XLAUI,        10312, 36, 0, 12, 42 },
    { BDK_QLM_MODE_XLAUI_C2M,    10312, 40, 0,  8, 42 },
    { BDK_QLM_MODE_10G_KR,       10312, 48, 0,  0, 42 },
    { BDK_QLM_MODE_40G_CR4,      10312, 48, 0,  0, 42 },
    { BDK_QLM_MODE_40G_KR4,      10312, 48, 0,  0, 42 },
    { BDK_QLM_MODE_20GAUI_C2C,   20625, 42, 6,  0, 42 },
    { BDK_QLM_MODE_25GAUI_C2C,   25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_25GAUI_C2M,   25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_25G_CR,       25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_25G_KR,       25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_25GAUI_2_C2C, 12890, 42, 6,  0, 42 },
    { BDK_QLM_MODE_40GAUI_2_C2C, 20625, 42, 6,  0, 42 },
    { BDK_QLM_MODE_50GAUI_2_C2C, 25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_50GAUI_2_C2M, 25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_50G_CR2,      25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_50G_KR2,      25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_50GAUI_4_C2C, 12890, 42, 6,  0, 42 },
    { BDK_QLM_MODE_80GAUI_4_C2C, 20625, 42, 6,  0, 42 },
    { BDK_QLM_MODE_CAUI_4_C2C,   25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_CAUI_4_C2M,   25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_100G_CR4,     25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_100G_KR4,     25781, 42, 6,  0, 42 },
    { BDK_QLM_MODE_USXGMII_4X1,  20625, 42, 6,  0, 42 },
    { BDK_QLM_MODE_USXGMII_2X1,  20625, 42, 6,  0, 42 },
    { BDK_QLM_MODE_USXGMII_1X1,  10312, 48, 0,  0, 42 },
    { BDK_QLM_MODE_DISABLED,         0,  0, 0,  0,  0 }
};

/**
 * Setup the PEM to either driver or receive reset from PRST based on RC or EP
 *
 * @param node   Node to use in a Numa setup
 * @param pem    Which PEM to setuo
 * @param is_endpoint
 *               Non zero if PEM is a EP
 */
void __bdk_qlm_setup_pem_reset_gsern(bdk_node_t node, int pem, int is_endpoint)
{
    /* Make sure is_endpoint is either 0 or 1 */
    is_endpoint = (is_endpoint != 0);
    BDK_CSR_MODIFY(c, node, BDK_RST_CTLX(pem),
        c.s.prst_link = 0;          /* Link down doesn't automatically assert PERST */
        c.s.rst_link = is_endpoint; /* Link down automatically assert soft reset for EP */
        c.s.rst_drv = !is_endpoint; /* PERST is output for RC, input for EP */
        c.s.rst_rcv = is_endpoint;  /* Only read PERST in EP mode */
        c.s.rst_chip = 0);          /* PERST doesn't pull CHIP_RESET */

    if (is_endpoint)
    {
        /* If we're configuring an endpoint manually the PEM will not
           be turned on by default by the hardware. Turn it on now */
        BDK_CSR_INIT(pemx_on, node, BDK_PEMX_ON(pem));
        if (!pemx_on.s.pemon)
        {
            BDK_CSR_MODIFY(c, node, BDK_PEMX_ON(pem),
                c.s.pemon = 1);
        }
    }
}

/**
 * Measure the reference clock of a QLM
 *
 * @param qlm    QLM to measure
 *
 * @return Clock rate in Hz
 */
int __bdk_qlm_measure_refclock_gsern(bdk_node_t node, int qlm)
{
    if (bdk_is_platform(BDK_PLATFORM_ASIM) || bdk_is_platform(BDK_PLATFORM_EMULATOR))
    {
        BDK_CSR_INIT(refclk, node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm));
        switch (refclk.s.cclksel)
        {
            case 0: /* HRM recommended 100Mhz non SSC for SATA, PCIe, or USB */
                return REF_100MHZ;
            case 1: /* HRM recommended 100Mhz SSC for PCIe, or USB */
                return REF_100MHZ;
            case 2: /* HRM recommended 156.25Mhz non SSC for networking */
                return REF_156MHZ;
            case 3: /* External ref, probably 100Mhz SSC for PCIe EP */
                return REF_100MHZ;
        }
    }

    BDK_CSR_INIT(ctr_start, node, BDK_GSERNX_COMMON_REFCLK_CTR(qlm));
    uint64_t start = bdk_clock_get_count(BDK_CLOCK_TIME);

    /* Wait for a short time to get a number of counts */
    bdk_wait_usec(50000); /* 50ms */

    BDK_CSR_INIT(ctr_stop, node, BDK_GSERNX_COMMON_REFCLK_CTR(qlm));
    uint64_t stop = bdk_clock_get_count(BDK_CLOCK_TIME);

    /* Calculate the rate */
    uint64_t count = ctr_stop.u - ctr_start.u;
    count *= bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
    count /= stop - start;
    return count;
}

/**
 * Put a QLM into hardware reset
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_reset_gsern(bdk_node_t node, int qlm)
{
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
        c.s.domain_rst_en = 1;
        c.s.rst_pll_rst_sm = 1;
        c.s.pwdn = 1);
    return 0;
}

static void extract_tx_tuning(bdk_gsernx_lanex_tx_drv_bsts_t tx_drv_bsts, int *tx_cmain, int *tx_cpre, int *tx_cpost)
{
    if (tx_drv_bsts.s.tx_invalid)
    {
        *tx_cmain = TX_TUNING_INVALID;
        *tx_cpre = TX_TUNING_INVALID;
        *tx_cpost = TX_TUNING_INVALID;
        return;
    }
    bool idle = (tx_drv_bsts.s.muxpost == 0) && (tx_drv_bsts.s.cpostb == 7) &&
        (tx_drv_bsts.s.cposta == 7) && (tx_drv_bsts.s.enpost == 0) &&
        (tx_drv_bsts.s.muxmain == 0) && (tx_drv_bsts.s.cmaind == 7) &&
        (tx_drv_bsts.s.enmain == 3) && (tx_drv_bsts.s.muxpre == 0) &&
        (tx_drv_bsts.s.cpreb == 7) && (tx_drv_bsts.s.cprea == 7) &&
        (tx_drv_bsts.s.enpre == 3);
    if (idle)
    {
        *tx_cmain = TX_TUNING_IDLE;
        *tx_cpre = TX_TUNING_IDLE;
        *tx_cpost = TX_TUNING_IDLE;
        return;
    }

    int cprea_int = (tx_drv_bsts.s.enpre & 1) ? tx_drv_bsts.s.cprea + 1 : 0;
    int cpreb_int = (tx_drv_bsts.s.enpre & 2) ? tx_drv_bsts.s.cpreb + 1 : 0;
    int cposta_int = (tx_drv_bsts.s.enpost & 1) ? tx_drv_bsts.s.cposta + 1 : 0;
    int cpostb_int = (tx_drv_bsts.s.enpost & 2) ? tx_drv_bsts.s.cpostb + 1 : 0;
    int cmaind_int = (tx_drv_bsts.s.enmain & 8) ? tx_drv_bsts.s.cmaind + 1 : 0;

    int cmainx = cmaind_int;
    if ((tx_drv_bsts.s.enpost & 2) && (tx_drv_bsts.s.muxpost & 2) &&
        (tx_drv_bsts.s.enmain & 8) && (tx_drv_bsts.s.muxmain & 8))
        cmainx += cpostb_int;
    if ((tx_drv_bsts.s.enpre & 2) && (tx_drv_bsts.s.muxpre & 2) &&
        (tx_drv_bsts.s.enmain & 8) && (tx_drv_bsts.s.muxmain & 8))
        cmainx += cpreb_int;

    int enpost_int = (cmainx <= 16) && (tx_drv_bsts.s.enpost & 2) ? 1 : 0;
    int muxpost_int = (cmainx <= 16) && (tx_drv_bsts.s.muxpost & 2) ? 1 : 0;
    int enpre_int = (cmainx <= 16) && (tx_drv_bsts.s.enpre & 2) ? 1 : 0;
    int muxpre_int = (cmainx <= 16) && (tx_drv_bsts.s.muxpre & 2) ? 1 : 0;

    int cmain = cmainx + 24;
    int post = 0;
    if (enpost_int && !muxpost_int)
        post = cposta_int + cpostb_int;
    else if (tx_drv_bsts.s.enpost & 1)
        post = cposta_int;
    int pre = 0;
    if (enpre_int && !muxpre_int)
        pre = cprea_int + cpreb_int;
    else if (tx_drv_bsts.s.enpre & 1)
        pre = cprea_int;

    *tx_cmain = cmain;
    *tx_cpre = pre;
    *tx_cpost = post;
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
int __bdk_qlm_enable_prbs_gsern(bdk_node_t node, int qlm, int prbs, bdk_qlm_direction_t dir)
{
    bool enable_tx = ((dir & BDK_QLM_DIRECTION_TX) != 0);
    bool enable_rx = ((dir & BDK_QLM_DIRECTION_RX) != 0);
    int prbs_type;
    switch (prbs)
    {
        case 0: /* Use pattern memory */
            prbs_type = -1;
            break;
        case 7:
            prbs_type = 0;
            break;
        case 9:
            prbs_type = 2;
            break;
        case 11:
            prbs_type = 3;
            break;
        case 15:
            prbs_type = 4;
            break;
        case 20:
            prbs_type = 5;
            break;
        case 23:
            prbs_type = 6;
            break;
        case 29:
            prbs_type = 7;
            break;
        case 31:
        default:
            prbs_type = 8;
            break;
    }
    int num_lanes = bdk_qlm_get_lanes(node, qlm);
    int is_pattern = (prbs_type == -1);
    for (int lane = 0; lane < num_lanes; lane++)
    {
        /* PRBS polarity is inverted internally. Need to invert the current polarity */
        BDK_CSR_INIT(lt_bcfg, node, BDK_GSERNX_LANEX_LT_BCFG(qlm, lane));
        if (enable_rx)
            lt_bcfg.s.inv_rx_polarity = ~(bdk_config_get_int(BDK_CONFIG_QLM_LANE_RX_POLARITY, node, qlm, lane));
        if (enable_tx)
            lt_bcfg.s.inv_tx_polarity = ~(bdk_config_get_int(BDK_CONFIG_QLM_LANE_TX_POLARITY, node, qlm, lane));
        BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_LT_BCFG(qlm, lane), lt_bcfg.u);

        if (enable_tx)
        {
            /* Enable Bias Override and Tx Driver */
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_DRV_BCFG(qlm, lane),
                c.s.en_tx_bs = 1;  //Enable the TX_BS override
                c.s.en_tx_drv = 1);  //Enable the Tx Driver
        }

        if (is_pattern)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PAT_CTRL(qlm, lane),
                if (enable_tx)
                    c.s.tx_rst_n = is_pattern;
                if (enable_rx)
                    c.s.rx_rst_n = is_pattern;
                c.s.en = is_pattern;
                c.s.cycle_cnt_en = 0;
                c.s.cycle_cnt = 0);
        }
        else
        {
            /* Check if the prbs_type has changed.  This requires a PRBS reset */
            bool prbs_type_changed = false;
            BDK_CSR_INIT(lt_prbs1_bcfg, node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane));
            if (enable_rx && (lt_prbs1_bcfg.s.prbs_type_rx != prbs_type))
            {
                lt_prbs1_bcfg.s.prbs_rx_rst_n = 0;
                prbs_type_changed = true;
            }
            if (enable_tx && (lt_prbs1_bcfg.s.prbs_type_rx != prbs_type))
            {
                lt_prbs1_bcfg.s.prbs_tx_rst_n = 0;
                prbs_type_changed = true;
            }
            BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane), lt_prbs1_bcfg.u);
            if (prbs_type_changed)
                bdk_wait_usec(1);

            lt_prbs1_bcfg.u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane));
            if (enable_rx)
            {
                lt_prbs1_bcfg.s.prbs_rx_mode = !is_pattern;
                lt_prbs1_bcfg.s.prbs_type_rx = prbs_type;
            }
            if (enable_tx)
            {
                lt_prbs1_bcfg.s.prbs_tx_mode = !is_pattern;
                lt_prbs1_bcfg.s.prbs_type_tx = prbs_type;
            }
            lt_prbs1_bcfg.s.cycle_cnt_en = 0;
            lt_prbs1_bcfg.s.cycle_cnt = 0;
            BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane), lt_prbs1_bcfg.u);

            bdk_wait_usec(1);

            if (enable_rx)
            {
                lt_prbs1_bcfg.s.prbs_rx_rst_n = !is_pattern;
            }
            if (enable_tx)
            {
                lt_prbs1_bcfg.s.prbs_tx_rst_n = !is_pattern;
            }
            BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane), lt_prbs1_bcfg.u);

            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane),
                if (enable_rx)
                {
                    c.s.prbs_rx_rst_n = !is_pattern;
                    c.s.prbs_rx_mode = !is_pattern;
                    c.s.prbs_type_rx = prbs_type;
                }
                if (enable_tx)
                {
                    c.s.prbs_tx_rst_n = !is_pattern;
                    c.s.prbs_tx_mode = !is_pattern;
                    c.s.prbs_type_tx = prbs_type;
                }
                c.s.cycle_cnt_en = 0;
                c.s.cycle_cnt = 0);
        }

        if (enable_tx)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, lane),
                c.s.tx_ctrl_sel =  is_pattern ? 0x10 : 0;
                c.s.tx_data_sel = is_pattern ? 0x10 : 0);
        }
    }
    return 0;
}

/**
 * Disable PRBS on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_disable_prbs_gsern(bdk_node_t node, int qlm)
{
    int num_lanes = bdk_qlm_get_lanes(node, qlm);
    for (int lane = 0; lane < num_lanes; lane++)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PAT_CTRL(qlm, lane),
            c.s.tx_rst_n = 0;
            c.s.rx_rst_n = 0;
            c.s.en = 0);
        /* PRBS requires the polarity to be inverted. Need to set back to the original polarity */
        BDK_CSR_INIT(lt_bcfg, node, BDK_GSERNX_LANEX_LT_BCFG(qlm, lane));
        lt_bcfg.s.inv_rx_polarity = bdk_config_get_int(BDK_CONFIG_QLM_LANE_RX_POLARITY, node, qlm, lane);
        lt_bcfg.s.inv_tx_polarity = bdk_config_get_int(BDK_CONFIG_QLM_LANE_TX_POLARITY, node, qlm, lane);
        BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_LT_BCFG(qlm, lane), lt_bcfg.u);
        /* Put the PRBS Tx/Rx in Reset */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane),
            c.s.prbs_rx_rst_n = 0;
            c.s.prbs_tx_rst_n = 0);
        bdk_wait_usec(1);
        /* Disable Rx/Tx PRBS mode */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane),
            c.s.prbs_rx_mode = 0;
            c.s.prbs_tx_mode = 0;
            c.s.cycle_cnt_en = 0);
        /* Clear the TX_DRV CSR Tx EQ overrides */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_DRV_BCFG(qlm, lane),
            c.s.en_tx_bs = 0;    //Disable the TX_BS override
            c.s.en_tx_drv = 0);  //Disable the Tx Driver
        bdk_qlm_state_lane_t state = {.u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, lane, 0))};
        /* Determine where the QLM gets data from */
        int pcs_src;
        if (state.s.pcie)
            pcs_src = 1;
        else if (state.s.sata)
            pcs_src = 4;
        else if (state.s.cgx)
            pcs_src = 2;
        else
            pcs_src = 0; /* PRBS */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, lane),
            c.s.tx_ctrl_sel = pcs_src;
            c.s.tx_data_sel = pcs_src);
    }
    return 0;
}

/**
 * Return the number of PRBS errors since PRBS started running
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 * @param clear  Clear counter after return the current value
 *
 * @return Number of errors
 */
uint64_t __bdk_qlm_get_prbs_errors_gsern(bdk_node_t node, int qlm, int lane, int clear)
{
    BDK_CSR_INIT(srcx_bcfg, node, BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, lane));
    if (srcx_bcfg.s.tx_data_sel == 0x10)
    {
        /* Pattern mode */
        BDK_CSR_INIT(pat_dat, node, BDK_GSERNX_LANEX_PAT_DAT(qlm, lane));
        if (clear)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PAT_CTRL(qlm, lane),
                c.s.rx_rst_n = 0);
            bdk_wait_usec(1);
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PAT_CTRL(qlm, lane),
                c.s.rx_rst_n = 1);
        }
        if (!pat_dat.s.lock || pat_dat.s.err_cnt_ovf)
            return -1;
        return pat_dat.s.err_cnt;
    }
    else
    {
        /* PRBS mode */
        BDK_CSR_INIT(lt_prbs_sts, node, BDK_GSERNX_LANEX_LT_PRBS_STS(qlm, lane));
        if (clear)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane),
                c.s.prbs_rx_rst_n = 0);
            bdk_wait_usec(1);
            BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_LT_PRBS1_BCFG(qlm, lane),
                c.s.prbs_rx_rst_n = 1);
        }
        if (!lt_prbs_sts.s.lock || lt_prbs_sts.s.err_cnt_ovf)
            return -1;
        return lt_prbs_sts.s.err_cnt;
    }
}

/**
 * Inject an error into PRBS
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 */
void __bdk_qlm_inject_prbs_error_gsern(bdk_node_t node, int qlm, int lane)
{
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_LT_BCFG(qlm, lane),
        c.s.inj_err_cnt_rst_n = 0);
    bdk_wait_usec(1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_LT_BCFG(qlm, lane),
        c.s.inj_err_cnt_rst_n = 1;
        c.s.inj_err_cnt_en = 1;
        c.s.inj_err_cnt_len = 1);
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
int __bdk_qlm_enable_loop_gsern(bdk_node_t node, int qlm, bdk_qlm_loop_t loop)
{
    int num_lanes = bdk_qlm_get_lanes(node, qlm);
    for (int lane = 0; lane < num_lanes; lane++)
    {
        BDK_CSR_INIT(lanex_pll_2_bcfg, node, BDK_GSERNX_LANEX_PLL_2_BCFG(qlm, lane));
        BDK_CSR_INIT(lanex_lt_bcfg, node, BDK_GSERNX_LANEX_LT_BCFG(qlm, lane));
        BDK_CSR_INIT(lanex_rx_st_bcfg, node, BDK_GSERNX_LANEX_RX_ST_BCFG(qlm, lane));
        BDK_CSR_INIT(lanex_tx_1_bcfg, node, BDK_GSERNX_LANEX_TX_1_BCFG(qlm, lane));
        switch (loop)
        {
            case BDK_QLM_LOOP_DISABLED:
                lanex_pll_2_bcfg.s.shlb_en          = 0; /* Far end loop RX CDR to TX */
                lanex_lt_bcfg.s.core_loopback_mode  = 0; /* Near end loop TX to RX in PCS lite */
                lanex_lt_bcfg.s.sloop_mode          = 0; /* Far end loop RX to TX in PCS lite */
                lanex_rx_st_bcfg.s.en_sh_lb         = 0; /* Far end loop RX CDR to TX */
                lanex_rx_st_bcfg.s.en_lb            = 0; /* Near end loop TX to RX */
                lanex_tx_1_bcfg.s.tx_enloop         = 0; /* Near end loop TX to RX in analog */
                break;
            case BDK_QLM_LOOP_SHALLOW: /* External */
                lanex_pll_2_bcfg.s.shlb_en          = 1; /* Far end loop RX CDR to TX */
                lanex_lt_bcfg.s.core_loopback_mode  = 0; /* Near end loop TX to RX in PCS lite */
                lanex_lt_bcfg.s.sloop_mode          = 1; /* Far end loop RX to TX in PCS lite */
                lanex_rx_st_bcfg.s.en_sh_lb         = 1; /* Far end loop RX CDR to TX */
                lanex_rx_st_bcfg.s.en_lb            = 0; /* Near end loop TX to RX */
                lanex_tx_1_bcfg.s.tx_enloop         = 0; /* Near end loop TX to RX in analog */
                break;
            case BDK_QLM_LOOP_NEAR_END: /* Internal analog */
                lanex_pll_2_bcfg.s.shlb_en          = 0; /* Far end loop RX CDR to TX */
                lanex_lt_bcfg.s.core_loopback_mode  = 0; /* Near end loop TX to RX in PCS lite */
                lanex_lt_bcfg.s.sloop_mode          = 0; /* Far end loop RX to TX in PCS lite */
                lanex_rx_st_bcfg.s.en_sh_lb         = 0; /* Far end loop RX CDR to TX */
                lanex_rx_st_bcfg.s.en_lb            = 1; /* Near end loop TX to RX */
                lanex_tx_1_bcfg.s.tx_enloop         = 1; /* Near end loop TX to RX in analog */
                break;
            case BDK_QLM_LOOP_CORE: /* Internal digital */
                lanex_pll_2_bcfg.s.shlb_en          = 0; /* Far end loop RX CDR to TX */
                lanex_lt_bcfg.s.core_loopback_mode  = 1; /* Near end loop TX to RX in PCS lite */
                lanex_lt_bcfg.s.sloop_mode          = 0; /* Far end loop RX to TX in PCS lite */
                lanex_rx_st_bcfg.s.en_sh_lb         = 0; /* Far end loop RX CDR to TX */
                lanex_rx_st_bcfg.s.en_lb            = 0; /* Near end loop TX to RX */
                lanex_tx_1_bcfg.s.tx_enloop         = 0; /* Near end loop TX to RX in analog */
                break;
        }
        BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_PLL_2_BCFG(qlm, lane), lanex_pll_2_bcfg.u);
        BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_LT_BCFG(qlm, lane), lanex_lt_bcfg.u);
        BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_RX_ST_BCFG(qlm, lane), lanex_rx_st_bcfg.u);
        BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_TX_1_BCFG(qlm, lane), lanex_tx_1_bcfg.u);
    }
    return 0;
}

/**
 * Given a valid PEM number, return its speed in Gbaud
 *
 * @param node   Node to use in numa setup
 * @param pem    PEM to get speed of
 *
 * @return Speed in Gbaud. Zero if disabled
 */
int __bdk_qlm_get_gbaud_mhz_pem_gsern(bdk_node_t node, int pem)
{
    BDK_CSR_INIT(diag_status, node, BDK_PEMX_DIAG_STATUS(pem));
    switch (diag_status.cn9.pclk_rate)
    {
        case 0: /* Gen 1 */
            return 2500;
        case 1: /* Gen 2 */
            return 5000;
        case 2: /* Gen 3 */
            return 8000;
        case 3: /* Gen 4 */
            return 16000;
    }
    return 0;
}

/**
 * Calculate the Raw FOM for a given QLM lane
 *
 * @param node     Node to use in numa setup
 * @param qlm      QLM to use
 * @param qlm_lane Lane to use
 * @param fom_type Raw FOM type (0 or 1)
 *
 * @return Raw FOM value on success, negative on failure
 */
int __bdk_qlm_calculate_fom_gsern(bdk_node_t node, int qlm, int qlm_lane, int fom_type)
{
    const int TIMEOUT = 10000; /* 10ms */

    /* 1. Write GSERN()_LANE()_TRAIN_10_BCFG to select FOM measurement */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TRAIN_10_BCFG(qlm, qlm_lane),
        c.s.fom_type = fom_type);

    /* 2. Setup FOM divider and FOM eye cycles */
    /* Setup for PCIe */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TRAIN_8_BCFG(qlm, qlm_lane),
        c.s.pcie_ecnt_div_val = 6;
        c.s.pcie_ecnt_div_en = 1;
        c.s.pcie_eye_cnt_val = 32760;
        c.s.pcie_eye_cnt_en = 1);
    /* Setup for Networking */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TRAIN_4_BCFG(qlm, qlm_lane),
        c.s.err_cnt_div_ovrrd_val = 7;
        c.s.err_cnt_div_ovrrd_en = 1;
        c.s.eye_cnt_ovrrd_val = 26208;
        c.s.eye_cnt_ovrrd_en = 1);

    /* 3. Enable the equalization override */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TRAIN_4_BCFG(qlm, qlm_lane),
        c.s.eq_eval_ovrrd_en = 1);

    /* 4. Generate a SW based EQ FOM request */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TRAIN_4_BCFG(qlm, qlm_lane),
        c.s.eq_eval_ovrrd_req = 1);

    /* 5. Wait for equalization acknowledgement to read back as 1 */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_TRAIN_5_BCFG(qlm, qlm_lane),
        eq_eval_ack, ==, 1, TIMEOUT))
    {
        BDK_TRACE(QLM, "N%d.QLM%d.LANE%d: Error calculating RAW FOM\n", node, qlm, qlm_lane);
        return -1;
    }

    /* 6. Read the Raw FOM (12-bit) value */
    BDK_CSR_INIT(train_5_bcfg, node, BDK_GSERNX_LANEX_TRAIN_5_BCFG(qlm, qlm_lane));

    /* 7. Clear the Equalization Evaluation request to release the eye monitor */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TRAIN_4_BCFG(qlm, qlm_lane),
        c.s.eq_eval_ovrrd_req = 0;
        c.s.eq_eval_ovrrd_en = 0);

    return train_5_bcfg.s.raw_fom;
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
void __bdk_qlm_display_settings_gsern(bdk_node_t node, int qlm, int qlm_lane, bool show_tx, bool show_rx)
{
    if (show_rx)
    {
        bool is_pcie = false;
        /* Check to see if GSER is in PCIe mode */
        BDK_CSR_INIT(srcmx_bcfg, node, BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, qlm_lane));
        if (srcmx_bcfg.s.tx_ctrl_sel == 1)
            is_pcie = true;

        /* Generate the RAW FOM */
        if (is_pcie)
        {
            /* Determine the negotiated PCIe speed */
            /* If Gen3 or above use FOM = 1 */
            __bdk_qlm_calculate_fom_gsern(node, qlm, qlm_lane, 1);
        }
        else
        {
            int speed = bdk_qlm_get_gbaud_mhz(node, qlm, qlm_lane);
            if (speed < 8000)
                __bdk_qlm_calculate_fom_gsern(node, qlm, qlm_lane, 0);
            else
                __bdk_qlm_calculate_fom_gsern(node, qlm, qlm_lane, 1);
        }
    }
    BDK_CSR_INIT(c_bias_bcfg, node, BDK_GSERNX_COMMON_BIAS_BCFG(qlm));
    BDK_CSR_INIT(c_pll_1_bcfg, node, BDK_GSERNX_COMMON_PLL_1_BCFG(qlm));
    BDK_CSR_INIT(c_pll_2_bcfg, node, BDK_GSERNX_COMMON_PLL_2_BCFG(qlm));
    BDK_CSR_INIT(c_refclk_bcfg, node, BDK_GSERNX_COMMON_REFCLK_BCFG(qlm));
    BDK_CSR_INIT(init_bsts, node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(lt_bsts, node, BDK_GSERNX_LANEX_LT_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(pll_1_bcfg, node, BDK_GSERNX_LANEX_PLL_1_BCFG(qlm, qlm_lane));
    BDK_CSR_INIT(pll_2_bcfg, node, BDK_GSERNX_LANEX_PLL_2_BCFG(qlm, qlm_lane));
    BDK_CSR_INIT(rx_0_bsts, node, BDK_GSERNX_LANEX_RX_0_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_10_bsts, node, BDK_GSERNX_LANEX_RX_10_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_11_bsts, node, BDK_GSERNX_LANEX_RX_11_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_1_bsts, node, BDK_GSERNX_LANEX_RX_1_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_2_bsts, node, BDK_GSERNX_LANEX_RX_2_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_3_bsts, node, BDK_GSERNX_LANEX_RX_3_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_4_bsts, node, BDK_GSERNX_LANEX_RX_4_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_5_bsts, node, BDK_GSERNX_LANEX_RX_5_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_5a_bsts, node, BDK_GSERNX_LANEX_RX_5A_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_6_bsts, node, BDK_GSERNX_LANEX_RX_6_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(rx_8_bsts, node, BDK_GSERNX_LANEX_RX_8_BSTS(qlm, qlm_lane));
    BDK_CSR_INIT(srcmx_bcfg, node, BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, qlm_lane));
    BDK_CSR_INIT(train_0_bcfg, node, BDK_GSERNX_LANEX_TRAIN_0_BCFG(qlm, qlm_lane));
    BDK_CSR_INIT(train_10_bcfg, node, BDK_GSERNX_LANEX_TRAIN_10_BCFG(qlm, qlm_lane));
    BDK_CSR_INIT(train_1_bcfg, node, BDK_GSERNX_LANEX_TRAIN_1_BCFG(qlm, qlm_lane));
    BDK_CSR_INIT(train_4_bcfg, node, BDK_GSERNX_LANEX_TRAIN_4_BCFG(qlm, qlm_lane));
    BDK_CSR_INIT(train_5_bcfg, node, BDK_GSERNX_LANEX_TRAIN_5_BCFG(qlm, qlm_lane));
    BDK_CSR_INIT(tx_drv_bsts, node, BDK_GSERNX_LANEX_TX_DRV_BSTS(qlm, qlm_lane));

    printf("N%d.QLM%d Lane %d:\n", node, qlm, qlm_lane);
    if (show_tx && show_rx)
    {
        printf("  Reset Status:\n");
        printf("    TX_READY=%d, RX_READY=%d, EYE_READY=%d, CAL_READY=%d, CAL_FAIL=%d\n",
            init_bsts.s.tx_ready, init_bsts.s.rx_ready, init_bsts.s.eye_ready,
            init_bsts.s.cal_ready, init_bsts.s.cal_fail);
        printf("    TX_RST_SM_COMPLETE=%d, RX_RST_SM_COMPLETE=%d, EYE_RST_SM_COMPLETE=%d, RST_SM_COMPLETE=%d\n",
            init_bsts.s.tx_rst_sm_complete, init_bsts.s.rx_rst_sm_complete,
            init_bsts.s.eye_rst_sm_complete, init_bsts.s.rst_sm_complete);
        printf("    TX_DEEP_IDLE=%d, RX_DEEP_IDLE=%d, EYE_DEEP_IDLE=%d, PLL_DEEP_IDLE=%d\n",
            init_bsts.s.tx_deep_idle, init_bsts.s.rx_deep_idle,
            init_bsts.s.eye_deep_idle, init_bsts.s.pll_deep_idle);
    }
    if (show_rx)
    {
        printf("  Receiver Status:\n");
        bool use0 = rx_3_bsts.s.calo_even & 1;
        int c1 = (use0) ? bdk_extract_smag(rx_2_bsts.s.c1_0q, 0, 5) : bdk_extract_smag(rx_2_bsts.s.c1_1q, 0, 5);
        int c2 = bdk_extract_smag(rx_0_bsts.s.c2, 0, 5);
        int c3 = bdk_extract_smag(rx_0_bsts.s.c3, 0, 5);
        int c4 = bdk_extract_smag(rx_0_bsts.s.c4, 0, 5);
        int c5 = bdk_extract_smag(rx_0_bsts.s.c5, 0, 5);
        int c6 = bdk_extract_smag(rx_0_bsts.s.c6, 0, 5);
        int c7 = bdk_extract_smag(rx_0_bsts.s.c7, 0, 5);
        int c8 = bdk_extract_smag(rx_0_bsts.s.c8, 0, 5);
        int c9 = bdk_extract_smag(rx_0_bsts.s.c9, 0, 5);
        int c10 = bdk_extract_smag(rx_1_bsts.s.c10, 0, 5);
        int c11 = bdk_extract_smag(rx_1_bsts.s.c11, 0, 5);
        int c12 = bdk_extract_smag(rx_1_bsts.s.c12, 0, 5);
        int c13 = bdk_extract_smag(rx_1_bsts.s.c13, 0, 5);
        int c14 = bdk_extract_smag(rx_1_bsts.s.c14, 0, 5);
        int c15 = bdk_extract_smag(rx_1_bsts.s.c15, 0, 5);
        printf("    DFE Taps: C1=%+d,  C2=%+d,  C3=%+d,  C4=%+d,  C5=%+d,  C6=%+d,  C7=%+d, C8=%+d\n",
            c1, c2, c3, c4, c5, c6, c7, c8);
        printf("              C9=%+d, C10=%+d, C11=%+d, C12=%+d, C13=%+d, C14=%+d, C15=%+d\n",
            c9, c10, c11, c12, c13, c14, c15);
        printf("    BLWC=%d, PreVGA Gain=%d, CTLE LTE Gain=%d, CTLE LTE Zero=%d, CTLE Gain=%d, CTLE Zero=%d\n",
            rx_4_bsts.s.blwc, rx_4_bsts.s.prevga_gn, rx_4_bsts.s.ctle_lte_gain,
            rx_4_bsts.s.ctle_lte_zero, rx_4_bsts.s.ctle_gain, rx_4_bsts.s.ctle_zero);
        int os_afe_odd = bdk_extract_smag(rx_4_bsts.s.os_afe_odd, 0, 5);
        int os_afe_even = bdk_extract_smag(rx_4_bsts.s.os_afe_even, 0, 5);
        printf("    VGA Gain=%d, OS_AFE_Odd=%d, OS_AFE_Even=%d\n",
            rx_4_bsts.s.vga_gain, os_afe_odd, os_afe_even);
        printf("    BLWC_ADAPT_STATUS=%d, PREVGA_GN_ADAPT_STATUS=%d, CTLEZ_ADAPT_STATUS=%d, CTLELTE_ADAPT_STATUS=%d, CTLE_ADAPT_STATUS=%d\n",
            rx_10_bsts.s.blwc_adapt_status, rx_11_bsts.s.prevga_gn_adapt_status,
            rx_5a_bsts.s.ctlez_adapt_status, rx_6_bsts.s.ctlelte_adapt_status, rx_5_bsts.s.ctle_adapt_status);
        printf("    VGA_ADAPT_STATUS=%d, AFEOS_ADAPT_STATUS=%d, DFE_ADAPT_STATUS=%d\n",
               rx_5_bsts.s.vga_adapt_status, rx_8_bsts.s.afeos_adapt_status, rx_5_bsts.s.dfe_adapt_status);
        int sensor = bdk_is_model(OCTEONTX_CNF95XX) ? 2 : 9;
        BDK_CSR_INIT(temp_conv_result, node, BDK_TSNX_TS_TEMP_CONV_RESULT(sensor));
        if (temp_conv_result.s.temp_valid)
        {
            int temp_x4 = bdk_extracts(temp_conv_result.s.temp_corrected, 0, 11);
            printf("    TEMPERATURE=%d.%02dC\n", temp_x4 >> 2, (temp_x4 & 3) * 25);
        }
        else
            printf("    TEMPERATURE=Unavailable\n");
    }
    if (show_tx)
    {
        printf("  Transmitter Status:\n");
        printf("    TX_CSPD=%d, TX_BS=%d, TX_INVALID=%d, MUXPOST=%d, CPOSTB=%d, CPOSTA=%d, ENPOST=%d, MUXMAIN=%d\n",
            tx_drv_bsts.s.tx_cspd, tx_drv_bsts.s.tx_bs, tx_drv_bsts.s.tx_invalid,
            tx_drv_bsts.s.muxpost, tx_drv_bsts.s.cpostb, tx_drv_bsts.s.cposta,
            tx_drv_bsts.s.enpost, tx_drv_bsts.s.muxmain);
        printf("    CMAIND=%d, ENMAIN=%d, MUXPRE=%d, CPREB=%d, CPREA=%d, ENPRE=%d\n",
            tx_drv_bsts.s.cmaind, tx_drv_bsts.s.enmain, tx_drv_bsts.s.muxpre,
            tx_drv_bsts.s.cpreb, tx_drv_bsts.s.cprea, tx_drv_bsts.s.enpre);
        int tx_cmain;
        int tx_cpre;
        int tx_cpost;
        extract_tx_tuning(tx_drv_bsts, &tx_cmain, &tx_cpre, &tx_cpost);
        if (tx_cmain == TX_TUNING_INVALID)
            printf("    PRE=Invalid, MAIN=Invalid, POST=Invalid\n");
        else if (tx_cmain == TX_TUNING_IDLE)
            printf("    PRE=Idle, MAIN=Idle, POST=Idle\n");
        else
            printf("    PRE=%d, MAIN=%d, POST=%d\n", tx_cpre, tx_cmain, tx_cpost);
        printf("    SRCMX: TX_CTRL_SEL=%d, TX_DATA_SEL=%d, TXDIVCLK_MUX_SEL_OVRRIDE=0x%x, TXDIVCLK_MUX_SEL_OVRRIDE_EN=%d\n",
            srcmx_bcfg.s.tx_ctrl_sel, srcmx_bcfg.s.tx_data_sel,
            srcmx_bcfg.s.txdivclk_mux_sel_ovrride,
            srcmx_bcfg.s.txdivclk_mux_sel_ovrride_en);
    }
    if (show_tx && show_rx)
    {
        printf("  PLL Configurations:\n");
        printf("    COMMON PLL: CP=%d, BAND=%d, DITHER_EN=%d, SDM_EN=%d, POST_DIV=%d, DIV_N=%d, DIV_F=%d\n",
            c_pll_1_bcfg.s.cp, c_pll_1_bcfg.s.band, c_pll_1_bcfg.s.dither_en,
            c_pll_1_bcfg.s.sdm_en, c_pll_1_bcfg.s.post_div, c_pll_1_bcfg.s.div_n,
            c_pll_1_bcfg.s.div_f);
        printf("        REF_CLK_BYPASS=%d, CCLKSEL=%d, BIAS_PWDN=%d\n",
            c_pll_2_bcfg.s.ref_clk_bypass, c_refclk_bcfg.s.cclksel,
            c_bias_bcfg.s.bias_pwdn);
        printf("    LANE PLL: CP=%d, BAND=%d, DITHER_EN=%d, VCO_SEL=%d, SDM_EN=%d, POST_DIV=%d, DIV_N=%d\n",
            pll_1_bcfg.s.cp, pll_1_bcfg.s.band, pll_1_bcfg.s.dither_en,
            pll_1_bcfg.s.vco_sel, pll_1_bcfg.s.sdm_en, pll_1_bcfg.s.post_div,
            pll_1_bcfg.s.div_n);
        printf("        DIV_F=%d, CP_BOOST=%d, VCO_BIAS=%d\n",
            pll_1_bcfg.s.div_f, pll_2_bcfg.s.cp_boost, pll_2_bcfg.s.vco_bias);
        printf("  Miscellaneous:\n");
        printf("    CFG_CGX=%d, CFG_CGX_QUAD=%d, CFG_CGX_DUAL=%d, RAW_FOM=%d, FILTERED_FOM=%d, RXT_FOM=%d, FOM_TYPE=%d\n",
            train_0_bcfg.s.cfg_cgx, train_0_bcfg.s.cgx_quad,
            train_0_bcfg.s.cgx_dual, train_5_bcfg.s.raw_fom,
            train_5_bcfg.s.filtered_fom, train_1_bcfg.s.rxt_fom,
            train_10_bcfg.s.fom_type);
        printf("    ERR_CNT_DIV_OVRRD_VAL=%d, ERR_CNT_DIV_OVRRD_EN=%d, EYE_CNT_OVRRD_EN=%d, EYE_CNT_OVRRD_VAL=0x%lx\n",
            train_4_bcfg.s.err_cnt_div_ovrrd_val, train_4_bcfg.s.err_cnt_div_ovrrd_en, train_4_bcfg.s.eye_cnt_ovrrd_en,
            (uint64_t)train_4_bcfg.s.eye_cnt_ovrrd_val);
        printf("    LD_RECEIVER_RDY=%d, FIFO_PSH_POP_OS=%d\n",
            train_0_bcfg.s.ld_receiver_rdy, lt_bsts.s.fifo_psh_pop_os);
    }
}

/**
 * Perform RX equalization on a QLM
 *
 * @param node     Node the QLM is on
 * @param qlm      QLM to perform RX equalization on
 * @param qlm_lane Lane to use, or -1 for all lanes
 *
 * @return Zero on success, negative if any lane failed RX equalization
 */
int __bdk_qlm_rx_equalization_gsern(bdk_node_t node, int qlm, int qlm_lane)
{
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return 0;

    const int TIMEOUT = 10000; /* 10ms */
    const int MAX_LANES = bdk_qlm_get_lanes(node, qlm);
    if (qlm_lane == -1)
        BDK_TRACE(QLM, "N%d.QLM%d: Starting RX equalization on lanes 0 to %d\n", node, qlm, MAX_LANES-1);
    else
        BDK_TRACE(QLM, "N%d.QLM%d: Starting RX equalization on lane %d\n", node, qlm, qlm_lane);

    int fail = 0; /* Bitmask of lanes that failed Rx Ready, Electrical Idle check or Rx adaptation */

    /* Lanes must be RX ready and not idle. Mark lanes as failed if either
       check fails */
    for (int lane = 0; lane < MAX_LANES; lane++)
    {
        /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;

        /* Check if GSER Rx is NOT ready or */
        /* if GSER Rx is idle (no signal detected) */
        BDK_CSR_INIT(init_bsts, node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane));
        if (!init_bsts.s.rx_ready)
        {
            BDK_TRACE(QLM, "N%d.QLM%d: Rx is not ready on lane %d\n", node, qlm, lane);
            /* Mark bad so we skip this lane below */
            fail |= 1 << lane;
            continue;
        }
        BDK_CSR_INIT(rx_idledet_bsts, node, BDK_GSERNX_LANEX_RX_IDLEDET_BSTS(qlm, lane));
        if (rx_idledet_bsts.s.idle)
        {
            BDK_TRACE(QLM, "N%d.QLM%d: Rx is idle.  No signal detected on lane %d\n", node, qlm, lane);
            /* Mark bad so we skip this lane below */
            fail |= 1 << lane;
            continue;
        }

        /* Force lane into Rx idle before starting rx adaptation */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_IDLEDET_2_BCFG(qlm, lane),
            c.s.frc_en = 1;
            c.s.frc_val = 1);
        /* Enable deep idle */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, lane),
            c.s.rx_go2deep_idle = 1);
    }

    /* Wait for each lane to enter deep idle */
    for (int lane = 0; lane < MAX_LANES; lane++)
    {
        /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;
        /* Skip lanes that failed the Rx Idle or Rx ready check */
        if ((fail >> lane) & 0x1)
            continue;

        /* Wait for deep idle */
        BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane),
            rx_deep_idle, ==, 1, TIMEOUT);
    }

    /* Stay in deep idle for 100us */
    bdk_wait_usec(100);

    /* Take the lanes out of deep idle */
    for (int lane = 0; lane < MAX_LANES; lane++)
    {
        /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;
        /* Skip lanes that failed the Rx Idle or Rx ready check */
        if ((fail >> lane) & 0x1)
            continue;

        /* Disable deep idle */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, lane),
            c.s.rx_go2deep_idle = 0);
    }

    /* Make sure each line exits deep idle */
    for (int lane = 0; lane < MAX_LANES; lane++)
    {
        /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;
        /* Skip lanes that failed the Rx Idle or Rx ready check */
        if ((fail >> lane) & 0x1)
            continue;
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), rx_rst_sm_complete, ==, 1, TIMEOUT))
        {
            BDK_TRACE(QLM, "N%d.QLM%d: Rx RST state machine timed out on lane %d\n", node, qlm, lane);
            fail |= 1 << lane;
        }
        if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERNX_LANEX_INIT_BSTS(qlm, lane), rx_ready, ==, 1, TIMEOUT))
        {
            BDK_TRACE(QLM, "N%d.QLM%d: Rx ready timed out on lane %d\n", node, qlm, lane);
            fail |= 1 << lane;
        }
    }

    /* Allow lanes to settle for 1ms */
    bdk_wait_usec(1000); /* 1ms */

    /* Undo the force idle detect */
    for (int lane = 0; lane < MAX_LANES; lane++)
    {
        /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;
        /* Skip lanes that failed the Rx Idle or Rx ready check */
        if ((fail >> lane) & 0x1)
            continue;

        /* Clear  Rx idle override after rx adaptation loop reset */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_IDLEDET_2_BCFG(qlm, lane),
            c.s.frc_en = 0;
            c.s.frc_val = 0);
    }

    /* Verify all the Rx adaptation loops complete within 10ms */
    uint64_t timeout_adapt = bdk_clock_get_rate(node, BDK_CLOCK_TIME)/100 + bdk_clock_get_count(BDK_CLOCK_TIME);
    bool need_rx_adaptation;
    int adapt_fail = 0;
    while (1)
    {
        for (int lane = 0; lane < MAX_LANES; lane++)
        {
            /* Skip lanes we don't care about */
            if ((qlm_lane != -1) && (qlm_lane != lane))
                continue;
            /* Skip lanes that failed the Rx Idle or Rx ready check */
            if ((fail >> lane) & 0x1)
                continue;

            /* Read the QLM config and status */
            BDK_CSR_INIT(rst2_bcfg, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, lane));
            BDK_CSR_INIT(rx_10_bsts, node, BDK_GSERNX_LANEX_RX_10_BSTS(qlm, lane));
            BDK_CSR_INIT(rx_11_bsts, node, BDK_GSERNX_LANEX_RX_11_BSTS(qlm, lane));
            BDK_CSR_INIT(rx_5_bsts, node, BDK_GSERNX_LANEX_RX_5_BSTS(qlm, lane));
            BDK_CSR_INIT(rx_5a_bsts, node, BDK_GSERNX_LANEX_RX_5A_BSTS(qlm, lane));
            BDK_CSR_INIT(rx_6_bsts, node, BDK_GSERNX_LANEX_RX_6_BSTS(qlm, lane));
            BDK_CSR_INIT(rx_8_bsts, node, BDK_GSERNX_LANEX_RX_8_BSTS(qlm, lane));

            /* The various receiver status bits should match the final values */
            need_rx_adaptation = false;
            need_rx_adaptation |= (rx_10_bsts.s.blwc_adapt_status != rst2_bcfg.s.do_blwc_final);
            need_rx_adaptation |= (rx_11_bsts.s.prevga_gn_adapt_status != rst2_bcfg.s.do_prevga_gn_final);
            need_rx_adaptation |= (rx_5a_bsts.s.ctlez_adapt_status != rst2_bcfg.s.do_ctlez_final);
            need_rx_adaptation |= (rx_6_bsts.s.ctlelte_adapt_status != rst2_bcfg.s.do_ctlelte_final);
            need_rx_adaptation |= (rx_5_bsts.s.ctle_adapt_status != rst2_bcfg.s.do_ctle_final);
            need_rx_adaptation |= (rx_5_bsts.s.vga_adapt_status != rst2_bcfg.s.do_vga_final);
            need_rx_adaptation |= (rx_8_bsts.s.afeos_adapt_status != rst2_bcfg.s.do_afeos_final);
            need_rx_adaptation |= (rx_5_bsts.s.dfe_adapt_status != rst2_bcfg.s.do_dfe_final);

            /* If adaptation hasn't completed mark it as fail */
            if (need_rx_adaptation)
                adapt_fail |= 1 << lane;
            else
                adapt_fail &= ~(1 << lane);
        }
        if (!adapt_fail)
            break;

        if (bdk_clock_get_count(BDK_CLOCK_TIME) >= timeout_adapt)
        {
            break;
        }
    }

    /* Report any lanes that failed to complete Rx adaptation */
    if (adapt_fail)
    {
        for (int lane = 0; lane < MAX_LANES; lane++)
        {
            /* Skip lanes we don't care about */
            if ((qlm_lane != -1) && (qlm_lane != lane))
                continue;
            /* Skip lanes that failed the Rx Idle or Rx ready check */
            if ((fail >> lane) & 0x1)
                continue;
            if ((adapt_fail >> lane) & 0x1)
                BDK_TRACE(QLM, "N%d.QLM%d: Rx adaptation failed to complete on lane %d\n", node, qlm, lane);
        }
    }

    /* Declare lanes that failed to complete Rx adaptation as failures */
    fail |= adapt_fail;

    /* Print the Rx equalization settings */
    for (int lane = 0; lane < MAX_LANES; lane++)
    {
        /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;
        /* Skip lanes that failed the Rx Idle or Rx ready check */
        if ((fail >> lane) & 0x1)
            continue;

        /* Print our the Rx equalization setting if QLM tracing is enabled */
        if (bdk_trace_enables & (1ull << BDK_TRACE_ENABLE_QLM))
        {
            __bdk_qlm_display_settings_gsern(node, qlm, lane, 0, 1);
        }
    }

    return (fail) ? -1 : 0;
}

/**
 * Configure the TX tuning parameters for a QLM lane
 *
 * @param node      Node to configure
 * @param qlm       QLM to configure
 * @param lane      Lane to configure
 * @param tx_cmain  Transmitter Main (C0) equalizer tap coefficient value.
 *                  Programs the SerDes transmitter Main tap. Valid range is
 *                  0x30 to 0x18.
 * @param tx_cpre   Transmitter Pre (C-1) equalizer tap coefficient value.
 *                  Programs the transmitter Pre tap. Valid range is 0 to 0x10.
 * @param tx_cpost  Transmitter Post (C+1) equalizer tap coefficient value.
 *                  Programs the transmitter Post tap. Valid range is 0 to
 *                  0x10.
 * @param tx_bs     TX bias/swing selection. This setting only takes effect if
 *                  [TX_CSPD] is deasserted; with [TX_CSPD] asserted the
 *                  bias/swing control setting seen in the analog bias generator
 *                  is zero.
 *                  Typical override values would be:
 *                  42 = Nominal 1.0V p-p transmit amplitude.
 *                  52 = Nominal 1.2V p-p transmit amplitude.
 *                  The maximum usable value without transmitted waveform
 *                  distortion depends primarily on voltage, secondarily on
 *                  process corner and temperature, but is at least 52. There is
 *                  no minimum setting based on transmitter distortion, only
 *                  that set by the receiver.
 * @param tx_unused Currently unused
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_tune_lane_tx_gsern(bdk_node_t node, int qlm, int lane, int tx_cmain, int tx_cpre, int tx_cpost, int tx_bs, int tx_unused)
{
    /* The rules for programming the transmitter equalizer taps are (all
        values in decimal):
        [TX_CMAIN] + [TX_CPRE] + [TX_CPOST] <= 48
        [TX_CMAIN] - [TX_CPRE] - [TX_CPOST] >= 6
        48 >= [TX_CMAIN] >= 24
        16 >= [TX_CPRE] >= 0
        16 >= [TX_CPOST] >= 0 */
    if (tx_cmain + tx_cpre + tx_cpost > 48)
    {
        bdk_error("N%d.QLM%d.Lane%d: Invalid tuning, Main(%d) + Pre(%d) + Post(%d) <= 48(%d)\n",
            node, qlm, lane, tx_cmain, tx_cpre, tx_cpost, tx_cmain + tx_cpre + tx_cpost);
        return -1;
    }
    if (tx_cmain - tx_cpre - tx_cpost < 6)
    {
        bdk_error("N%d.QLM%d.Lane%d: Invalid tuning, Main(%d) - Pre(%d) - Post(%d) >= 6(%d)\n",
            node, qlm, lane, tx_cmain, tx_cpre, tx_cpost, tx_cmain - tx_cpre - tx_cpost);
        return -1;
    }
    if ((tx_cmain < 24) || (tx_cmain > 48))
    {
        bdk_error("N%d.QLM%d.Lane%d: Invalid tuning, Main (%d, should be 24-48)\n", node, qlm, lane, tx_cmain);
        return -1;
    }
    if ((tx_cpre < 0) || (tx_cpre > 16))
    {
        bdk_error("N%d.QLM%d.Lane%d: Invalid tuning, Pre (%d, should be 0-16)\n", node, qlm, lane, tx_cpre);
        return -1;
    }
    if ((tx_cpost < 0) || (tx_cpost > 16))
    {
        bdk_error("N%d.QLM%d.Lane%d: Invalid tuning, Post (%d, should be 0-16)\n", node, qlm, lane, tx_cpost);
        return -1;
    }

    /* Override the Transmitter Equalizer using the GSERNX_LANEX_TX_DRV_BCFG CSR
       and compute the decoded raw Tx EQ fields from the tx_cpre, tx_cmain, tx_cpost values passed in */

    int _i_en = 1;   //tx_drv enable
    int _stuff = 0;  //FIXME bitstuffing is off.  Add check if we are in bitstuffing mode and set this flag
    int _cpre;
    int _cmain;
    int _cpost;

    //Decoded Tx EQ variables to write to the GSERNX_LANEX_TX_DRV_BCFG CSR
    int enpre = 0;
    int cprea;
    int cpreb;
    int muxpre;
    int enmain;
    int cmaind;
    int muxmain;
    int enpost;
    int cposta;
    int cpostb;
    int muxpost;

    //internal variables
    int cpre, cmain, cpost;
    int en;
    int cprea_int, cpreb_int, cmaind_int, cposta_int, cpostb_int;
    int enpre_int = 0;
    int enmain_int, enpost_int;
    int cppru;  // =(cpre>>3) + (|cpre[2:0]) + (cpost>>3) + (|cpost[2:0]); range: 0..4
    int cmainx; // possible values are 0 to 24 (6'h18)
    int cmainx_x_21; // possible values are 0 to 504
    int cmaindiff;

    enmain_int = 0;
    muxmain = 0;
    enpre_int = 0;
    muxpre = 0;
    enpost_int  = 0;
    muxpost = 0;
    cprea_int = 1;
    cpreb_int = 1;
    cmaind_int = 1;
    cposta_int = 1;
    cpostb_int = 1;
    cpre =  tx_cpre;  // start with passed-in values
    cmain = tx_cmain;  // start with passed-in values
    cpost = tx_cpost;  // start with passed-in values
    _cpre =  tx_cpre;  // start with passed-in values
    _cmain = tx_cmain;  // start with passed-in values
    _cpost = tx_cpost;  // start with passed-in values
    en = _i_en;      // start with passed-in values

    // Check & fix 'invalid' settings
    if (_stuff == 1) {
        // No precursor during bit-stuffing
        if (_cpre != 0) { // if ( (|_cpre) ) {
            cpre = 0;
        }
    } else {
        // Precursor out of range (not-stuffed)
        if (_cpre > 12) {
            cpre = 12;
        }
    } // else: !if( _stuff )

    // Postcursor out of range
    if (_cpost > 16) {
        cpost = 16;
    }

    // Main cursor too large
    if (_cmain > 48) {
        cmain = 48;
    }

    // Main cursor too small
    if (_cmain < 24) {
        cmain = 24;
    }

    // check for too many blocks in use
    //original c code comment may work directly here if ((ceil(cprei/8)+ceil(cmaini/8)+ceil(cposti/8))>8) begin
    //original code from sv       cppru = (cpre[4:3]) + (|cpre[2:0]) + (cpost[4:3]) + (|cpost[2:0]);  // max possible value is 4, so

    int tmp_cpost1 = 0;
    int tmp_cpre = 0;

    tmp_cpost1 = (cpost >> 3) & (0x3);                    // (cpost[4:3])
    tmp_cpre = (cpre & 7) > 0  ?  1 : 0;      // (|cpre[2:0])

    cppru = (cpre >> 3) & 0x3;                                 //(cpre[4:3])
    cppru = (cppru + tmp_cpre + tmp_cpost1 + tmp_cpost1) & 0x3;

    //from sv           if ( ( (_cmain[5:3]) + (|_cmain[2:0]) + cppru ) > 8 ) begin
    int tmp__cmain = 0;

    tmp__cmain = ((_cmain & 7) > 0 ) ? 1 : 0;
    if ( (((_cmain >> 3) & 7) + tmp__cmain + cppru ) > 8) {
        cmain = 64 - (cppru << 3); // cmain = 'd64 - {cppru, 3'h0};  // result here must be =<63, so
    }

    // Set tap weights
    if (_stuff > 0) {
        // Common tap weights for all valid bit stuffing settings
        enpre_int  &= ~(1<<1); cpreb_int = 0; muxpre  |= (1<<1);  // enpre_int[1]  = '0;  cpreb_int = 'd0;   muxpre[1] = '1;   // Never used -- only E and ~L taps possible
        enmain_int |= 1;       muxmain &= ~(1);    // enmain_int[0] = '1;  muxmain[0] = '0;  // Choose E
        enmain_int |= (1<<1);  muxmain &= ~(1<<1); // enmain_int[1] = '1;  muxmain[1] = '0;  // Choose E
        enmain_int |= (1<<2);  muxmain &= ~(1<<2); // enmain_int[2] = '1;  muxmain[2] = '0;  // Choose E

        cmainx = cmain - 24;  // cmain=<48, so cmainx=<24

        // Set up postcursor tap weights
        if (cpost <= 8) {   // All tap weight on cpostb
            enpost_int &= ~(1); cposta_int = 0; muxpost &= ~(1);
            if (cpost > 0)
                enpost_int |= (1 << 1);
            else
                enpost_int &= ~(1 << 1);
            cpostb_int = cpost;  muxpost &= ~(1<<1);
        } else {            // Split tap weights between cpostb and cposta
            enpost_int |= 1;      cposta_int = (cpost>>1) + (cpost & 1);  muxpost &= ~(1);
            enpost_int |= (1<<1); cpostb_int = cpost - cposta_int;        muxpost &= ~(1<<1);
        }  // cpost

        // Set up main cursor tap weights for bit stuffing
        if (cmainx <= 8) {          // All tap weight on cmaind
            if (cmainx != 0)
                enmain_int |= (1 << 3);
            else
                enmain_int &= ~(1 << 3);
            cmaind_int = cmainx;  muxmain &= ~(1<<3);
            enpre_int  &= ~(1); cprea_int  = 0; muxpre |= 1;
        } else if (cmainx <= 16) {  // Split tap weight between cmaind and cprea
            enmain_int |= (1<<3);
            cmaind_int = (cmainx>>1) + (cmainx & 1);   muxmain &= ~(1<<3);
            enpre_int  |= 1;  cprea_int  = cmainx - cmaind_int; muxpre  |= 1;
        } else {                    // Split tap weight between cmaind, cprea, and cpost a

            // Need cmaind_int=ceil(cmainx/3); use (21*cmainx)>>6 + |frac_bits
            cmainx_x_21 = ((cmainx << 4) & 0x1ff) + ((cmainx << 2) & 0x1ff) + cmainx;
            int tmp_cmainx_x_21 = (cmainx_x_21 & 0x3f) ? 1 : 0;
            enmain_int |= (1<<3);
            cmaind_int = ((cmainx_x_21>>6) & 7) + tmp_cmainx_x_21;  muxmain &= ~(1<<3);
            cmaindiff = cmainx - ( cmaind_int&(0xf));
            enpre_int  |= 1;
            cprea_int  = (((cmaindiff >> 1) & 0xf) + (cmaindiff & 1)) & 0xf;  muxpre  |= 1;
            enpost_int |= 1;
            cposta_int = (cmainx - cmaind_int - cprea_int) & 0xf;  muxpost |= 1;
        }  // cmain
    } else { // if ( _stuff )

        // Common tap weights for all valid settings
        enmain_int |= 1;       muxmain |= 1;  // Choose M
        enmain_int |= (1<<1);  muxmain |= (1<<1);  // Choose M
        enmain_int |= (1<<2);  muxmain |= (1<<2);  // Choose M
        cmainx = cmain - 24;

        // Set up precursor tap weights
        if ( cpre <= 8) {
            enpre_int = (cpre>0) ? (enpre_int | 1) : (enpre & ~(1));  cprea_int = cpre;  muxpre &= ~(1);    //enpre_int[0] = (cpre>0);  cprea_int = cpre;  muxpre[0] = '0;  // Choose ~E
            enpre_int &= ~(1<<1);  cpreb_int = 0;    muxpre &= ~(1<<1);  // Choose ~E
        } else {
            enpre_int |= 1;  cprea_int = (cpre>>1) + (cpre & (1));  muxpre &= ~(1);          //enpre_int[0] = '1;  cprea_int = (cpre>>1) + cpre[0];  muxpre[0] = '0;  // Choose ~E
            enpre_int |= (1<<1);  cpreb_int = cpre - cprea_int;     muxpre &= ~(1<<1);    //enpre_int[1] = '1;  cpreb_int = cpre - cprea_int;     muxpre[1] = '0;  // Choose ~E
        }  // cpre

        // Set up postcursor tap weights (common with normal and bit stuffing)
        if (cpost <= 8) {
            if (cpost > 0)
                enpost_int |= 1;
            else
                enpost_int &= ~(1);
            cposta_int = cpost;  muxpost &= ~(1);  //enpost_int[0] = (cpost>0);  cposta_int = cpost;  muxpost[0] = '0;  // Choose ~L
            enpost_int &= ~(1<<1); cpostb_int = 0; muxpost &= ~(1<<1);      //enpost_int[1] = '0;         cpostb_int = '0;                  muxpost[1] = '0;  // Choose ~L
        } else {
            enpost_int |= 1; cposta_int = (cpost>>1) + (cpost & (1)); muxpost &= ~(1);      //enpost_int[0] = '1;  cposta_int = (cpost>>1) + cpost[0]; muxpost[0] = '0;  // Choose ~L
            enpost_int |= (1<<1);    cpostb_int = cpost - cposta_int;  muxpost &= ~(1<<1);   //enpost_int[1] = '1;  cpostb_int = cpost - cposta_int;  muxpost[1] = '0;  // Choose ~L
        }   // cpost

        // Set up main cursor tap weights
        if (cmainx <= 8) {            // <=8,  only use 4th main block
            if (cmainx > 0)
                enmain_int |= (1 << 3);
            else
                enmain_int &= ~(1 << 3);
            cmaind_int = cmainx; muxmain |= (1 << 3);  //enmain_int[3] = (cmainx>0);  cmaind_int = cmainx;  muxmain[3] = '1; // Choose M
        } else if (cmainx <= 16) {  // >8, <=16,  use 4th main block and one from pre or post
            enmain_int |= (1<<3); cmaind_int = (cmainx>>1) + (cmainx & (1)); muxmain |= (1<<3);  //enmain_int[3] = '1; cmaind_int = (cmainx>>1) + cmainx[0]; muxmain[3] = '1;// Choose M

            // Decide where to put the last block
            if (enpre_int&(1<<1)) {
                enpost_int |= (1<<1);  cpostb_int = (cmainx - cmaind_int) & 0xf;     muxpost |= (1<<1); // Choose M
            } else {
                enpre_int  |= (1<<1);  cpreb_int  = (cmainx - cmaind_int) & 0xf;     muxpre  |= (1<<1); //enpre_int[1]  = '1;  cpreb_int  = cmainx - cmaind_int;     muxpre[1]  = '1; // Choose M
            }
        } else {                 // >16, use 4th main block and one from pre & post
            cmainx_x_21 = ((cmainx << 4) & 0x1ff) + ((cmainx << 2) &0x1ff)  + cmainx;

            //enmain_int[3] = '1; cmaind_int = (cmainx_x_21[8:6]) + (|cmainx_x_21[5:0]); muxmain[3] = '1;  // Choose M
            int tmp_cmainx_x_21 = (cmainx_x_21 & 0x3f) ? 1 : 0;
            enmain_int |= (1<<3);
            cmaind_int = ((cmainx_x_21>>6) & 7) + tmp_cmainx_x_21;  muxmain |= (1<<3);

            cmaindiff = cmainx - ( cmaind_int&(0xf));  //cmaindiff = cmainx - {1'b0, cmaind_int};  //cmaindiff = cmainx - {1'b0, cmaind_int};
            enpre_int  |= (1<<1);  cpreb_int  =  ((cmaindiff >> 1) &0xf) + (cmaindiff &(1)); muxpre  |= (1<<1);  //enpre_int[1]  = '1; cpreb_int  = (cmaindiff[4:1]) + cmaindiff[0];          muxpre[1]  = '1;  // Choose M
            enpost_int |= (1<<1);   cpostb_int = cmainx - cmaind_int - cpreb_int;  muxpost |= 1<<1; //enpost_int[1] = '1; cpostb_int = cmainx - cmaind_int - cpreb_int;  muxpost[1] = '1;  // Choose M
        }
    } // else: !if( stuff )

    // max value for *_int is 8, so the c*-1 will all fit into 3b
    // corresponding en* is 0 when c* is zero, so the muxes may not be needed
    cprea =  (en > 0) ?  (  (cprea_int > 0)   ? cprea_int -1 : 0 ) : 0;    // cprea  = {4{en}} & ( (|cprea_int)  ? cprea_int  - 1 : '0 );
    cpreb =  (en > 0) ?  (  (cpreb_int > 0)   ? cpreb_int -1 : 0 ) : 0;    // cpreb  = {4{en}} & ( (|cpreb_int)  ? cpreb_int  - 1 : '0 );
    cmaind = (en > 0) ?  (  (cmaind_int > 0)  ? cmaind_int -1 : 0 ) : 0;   // cmaind = {4{en}} & ( (|cmaind_int) ? cmaind_int - 1 : '0 );
    cposta = (en > 0) ?  (  (cposta_int > 0)  ? cposta_int -1 : 0 ) : 0;   // cposta = {4{en}} & ( (|cposta_int) ? cposta_int - 1 : '0 );
    cpostb = (en > 0) ?  (  (cpostb_int > 0)  ? cpostb_int -1 : 0 ) : 0;   // cpostb = {4{en}} & ( (|cpostb_int) ? cpostb_int - 1 : '0 );

    enpre  = (en > 0) ? enpre_int : 0;     // enpre  = {2{en}} & enpre_int;
    enmain = (en > 0) ? enmain_int : 0;    // enmain = {4{en}} & enmain_int;
    enpost = (en > 0) ? enpost_int : 0;    // enpost = {2{en}} & enpost_int;

    /* Now Update the TX_DRV CSR with the decoded Tx EQ override values */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_DRV_BCFG(qlm, lane),
        if (tx_bs != -1)
            c.s.tx_bs = tx_bs;
        //Post EQ Tap
        if (muxpost != -1)
            c.s.muxpost = muxpost;
        if (cpostb != -1)
            c.s.cpostb = cpostb;
        if (cposta != -1)
            c.s.cposta = cposta;
        if (enpost != -1)
            c.s.enpost = enpost;
        // Main EQ Tap
        if (muxmain != -1)
            c.s.muxmain = muxmain;
        if (cmaind != -1)
            c.s.cmaind = cmaind;
        if (enmain != -1)
            c.s.enmain = enmain;
        // PRE EQ Tap
        if (muxpre != -1)
            c.s.muxpre = muxpre;
        if (cpreb != -1)
            c.s.cpreb = cpreb;
        if (cprea != -1)
            c.s.cprea = cprea;
        if (enpre != -1)
            c.s.enpre = enpre;
        );

    bdk_gsernx_lanex_srcmx_bcfg_t gsernx_lanex_srcmx_bcfg;
    gsernx_lanex_srcmx_bcfg.u = BDK_CSR_READ(node, BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, lane));
    /* Check if GSER lane is configured in PCIe mode */
    if (gsernx_lanex_srcmx_bcfg.s.tx_ctrl_sel == 1)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_TXBIAS_BCFG(qlm, lane),
            c.s.tx_bias_full = tx_bs);
        return 0;
    }
    /* Check if GSER lane is configured in CGX mode */
    else if (gsernx_lanex_srcmx_bcfg.s.tx_ctrl_sel == 2)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_CGX_TXEQ_BCFG(qlm, lane),
            if (tx_cpost != -1)
                c.s.tx_cpost = tx_cpost;
            if (tx_cmain != -1)
                c.s.tx_cmain = tx_cmain;
            if (tx_cpre != -1)
                c.s.tx_cpre = tx_cpre;
            if (tx_bs != -1)
                c.s.tx_bs = tx_bs;
            );
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_CGX_TXEQ_BCFG(qlm, lane),
            c.s.tx_coeff_update = 1);
        return 0;
    }
    /* Check if GSER lane is configured in SATA mode */
    else if (gsernx_lanex_srcmx_bcfg.s.tx_ctrl_sel == 4)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_SATA_TXDRV1_BCFG(qlm, lane),
            if (tx_cpost != -1)
                c.s.sata_g1_cpost = tx_cpost;
            if (tx_cpost != -1)
                c.s.sata_g1_cmain = tx_cmain;
            if (tx_cpost != -1)
                c.s.sata_g1_cpre = tx_cpre;
            if (tx_bs != -1)
                c.s.sata_g1_tx_bias = tx_bs;
            );
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_SATA_TXDRV2_BCFG(qlm, lane),
            if (tx_cpost != -1)
                c.s.sata_g2_cpost = tx_cpost;
            if (tx_cpost != -1)
                c.s.sata_g2_cmain = tx_cmain;
            if (tx_cpost != -1)
                c.s.sata_g2_cpre = tx_cpre;
            if (tx_bs != -1)
                c.s.sata_g2_tx_bias = tx_bs;
            );
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_SATA_TXDRV3_BCFG(qlm, lane),
            if (tx_cpost != -1)
                c.s.sata_g3_cpost = tx_cpost;
            if (tx_cpost != -1)
                c.s.sata_g3_cmain = tx_cmain;
            if (tx_cpost != -1)
                c.s.sata_g3_cpre = tx_cpre;
            if (tx_bs != -1)
                c.s.sata_g3_tx_bias = tx_bs;
            );
        return 0;
    }
    else
        /* Enable Bias Override and Tx Driver */
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_DRV_BCFG(qlm, lane),
            c.s.en_tx_bs = 1;  //Enable the TX_BS override
            c.s.en_tx_drv = 1);  //Enable the Tx Driver

    return 0;
}

/**
 * Get the TX tuning parameters for a QLM lane
 *
 * @param node      Node to configure
 * @param qlm       QLM to configure
 * @param lane      Lane to configure
 * @param tx_cmain  Transmitter Main (C0) equalizer tap coefficient value.
 *                  Programs the SerDes transmitter Main tap. Valid range is
 *                  0x30 to 0x18.
 * @param tx_cpre   Transmitter Pre (C-1) equalizer tap coefficient value.
 *                  Programs the transmitter Pre tap. Valid range is 0 to 0x10.
 * @param tx_cpost  Transmitter Post (C+1) equalizer tap coefficient value.
 *                  Programs the transmitter Post tap. Valid range is 0 to
 *                  0x10.
 * @param tx_bs     TX bias/swing selection. This setting only takes effect if
 *                  [TX_CSPD] is deasserted; with [TX_CSPD] asserted the
 *                  bias/swing control setting seen in the analog bias generator
 *                  is zero.
 *                  Typical override values would be:
 *                  42 = Nominal 1.0V p-p transmit amplitude.
 *                  52 = Nominal 1.2V p-p transmit amplitude.
 *                  The maximum usable value without transmitted waveform
 *                  distortion depends primarily on voltage, secondarily on
 *                  process corner and temperature, but is at least 52. There is
 *                  no minimum setting based on transmitter distortion, only
 *                  that set by the receiver.
 * @param tx_unused Currently unused
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_get_tune_lane_tx_gsern(bdk_node_t node, int qlm, int lane, int *tx_cmain, int *tx_cpre, int *tx_cpost, int *tx_bs, int *tx_unused)
{
    BDK_CSR_INIT(tx_drv_bsts, node, BDK_GSERNX_LANEX_TX_DRV_BSTS(qlm, lane));

    extract_tx_tuning(tx_drv_bsts, tx_cmain, tx_cpre, tx_cpost);
    *tx_bs = tx_drv_bsts.s.tx_bs;
    *tx_unused = 0;
    return 0;
}

/**
 * Some QLM speeds need to override the default tuning parameters
 *
 * @param node     Node to use in a Numa setup
 * @param qlm      QLM to configure
 * @param lane     Lane to tune, or -1 for all
 * @param mode     Desired mode
 * @param baud_mhz Desired speed
 */
void __bdk_qlm_tune_gsern(bdk_node_t node, int qlm, int lane, bdk_qlm_modes_t mode, int baud_mhz)
{
    const default_tuning_t *tuning = DEF_TUNING;
    while (tuning->mode)
    {
        if ((tuning->mode == mode) && (tuning->baud_mhz == baud_mhz))
            break;
        tuning++;
    }
    if (!tuning->mode)
        return;

    const char *smode = bdk_qlm_mode_to_cfg_str(mode);
    int num_lanes = bdk_qlm_get_lanes(node, qlm);
    for (int l = 0; l < num_lanes; l++)
    {
        if ((l == lane) || (lane == -1))
        {
            int tx_cmain = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_MAIN, smode, baud_mhz, node, qlm, l);
            if (tx_cmain < 0)
                tx_cmain = tuning->tx_cmain;

            int tx_cpre = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_PRE, smode, baud_mhz, node, qlm, l);
            if (tx_cpre < 0)
                tx_cpre = tuning->tx_cpre;

            int tx_cpost = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_POST, smode, baud_mhz, node, qlm, l);
            if (tx_cpost < 0)
                tx_cpost = tuning->tx_cpost;

            int tx_bs = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_BS, smode, baud_mhz, node, qlm, l);
            if (tx_bs < 0)
                tx_bs = tuning->tx_bs;

            __bdk_qlm_tune_lane_tx_gsern(node, qlm, l, tx_cmain, tx_cpre, tx_cpost, tx_bs, -1);
        }
    }
}

/**
 * Called to initialize the GSERN programming API
 *
 * @param node   Node to init
 */
void __bdk_qlm_init_gsern(bdk_node_t node)
{
    /* Power on the common clocks */
    BDK_CSR_MODIFY(c, node, BDK_RST_REFC_CTL,
        c.s.cclk2_pwdn = 0;
        c.s.cclk1_pwdn = 0);
    cavm_gsern_voltage = bdk_config_get_int(BDK_CONFIG_QLM_VOLTAGE, node);
}

/**
 * Call GSERN APIs for CN9XXX chips
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
int __bdk_qlm_set_mode_gsern(bdk_node_t node, int qlm, int lane, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    bdk_qlm_state_lane_t state = __bdk_qlm_build_state(mode, baud_mhz, flags);
    int num_lanes = bdk_qlm_get_lanes(node, qlm);
    enum cavm_gsern_mode gsern_mode = CAVM_GSERN_MODE_DISABLED;
    enum cavm_gsern_flags gsern_flags = CAVM_GSERN_FLAGS_NONE;
    bool is_first = false;
    bool is_network = false;

    switch (mode)
    {
        case BDK_QLM_MODE_DISABLED:
            gsern_mode = CAVM_GSERN_MODE_DISABLED;
            break;
        case BDK_QLM_MODE_PCIE_X1 ... BDK_QLM_MODE_PCIE_X16:
        {
            if (flags & BDK_QLM_MODE_FLAG_ENDPOINT)
                gsern_mode = CAVM_GSERN_MODE_PCIE_EP;
            else
                gsern_mode = CAVM_GSERN_MODE_PCIE_RC;
            /* Figure out how many lanes PCIe desires. This
               assumes the modes are in order from least lanes to
               most lanes */
            int desired_lanes = 1 << (mode - BDK_QLM_MODE_PCIE_X1);
            if (desired_lanes > num_lanes)
            {
                switch (desired_lanes)
                {
                    case 4:
                        is_first = (qlm & 1) == 0;
                        if (num_lanes < 4)
                            gsern_flags = CAVM_GSERN_FLAGS_DUAL;
                        break;
                    case 8:
                        is_first = (qlm & 1) == 0;
                        gsern_flags = CAVM_GSERN_FLAGS_DUAL;
                        break;
                    case 16:
                        is_first = (qlm & 3) == 0;
                        gsern_flags = CAVM_GSERN_FLAGS_QUAD;
                        break;
                }
            }
            else
                is_first = true;
            break;
        }
        case BDK_QLM_MODE_SGMII:
        case BDK_QLM_MODE_1G_X:
        case BDK_QLM_MODE_XFI:
        case BDK_QLM_MODE_SFI:
        case BDK_QLM_MODE_10G_KR:
        case BDK_QLM_MODE_QSGMII:
        case BDK_QLM_MODE_20GAUI_C2C:
        case BDK_QLM_MODE_25GAUI_C2C:
        case BDK_QLM_MODE_25GAUI_C2M:
        case BDK_QLM_MODE_25G_CR:
        case BDK_QLM_MODE_25G_KR:
        case BDK_QLM_MODE_USXGMII_4X1:
        case BDK_QLM_MODE_USXGMII_2X1:
        case BDK_QLM_MODE_USXGMII_1X1:
            gsern_mode = CAVM_GSERN_MODE_CGX;
            is_network = true;
            break;
        case BDK_QLM_MODE_RXAUI:
            gsern_mode = CAVM_GSERN_MODE_CGX;
            /* RXAUI requires synchonization between the lanes, need DUAL flag */
            gsern_flags = CAVM_GSERN_FLAGS_DUAL;
            is_network = true;
            break;
        case BDK_QLM_MODE_25GAUI_2_C2C:
        case BDK_QLM_MODE_40GAUI_2_C2C:
        case BDK_QLM_MODE_50GAUI_2_C2C:
        case BDK_QLM_MODE_50GAUI_2_C2M:
        case BDK_QLM_MODE_50G_CR2:
        case BDK_QLM_MODE_50G_KR2:
            gsern_mode = CAVM_GSERN_MODE_CGX;
            /* Although dual lane these modes don't need the DUAL flag */
            is_network = true;
            break;
        case BDK_QLM_MODE_XAUI:
            gsern_mode = CAVM_GSERN_MODE_CGX;
            /* XAUI requires synchonization between the lanes, need QUAD flag */
            gsern_flags = CAVM_GSERN_FLAGS_QUAD;
            is_network = true;
            break;
        case BDK_QLM_MODE_XLAUI:
        case BDK_QLM_MODE_XLAUI_C2M:
        case BDK_QLM_MODE_40G_CR4:
        case BDK_QLM_MODE_40G_KR4:
        case BDK_QLM_MODE_50GAUI_4_C2C:
        case BDK_QLM_MODE_80GAUI_4_C2C:
        case BDK_QLM_MODE_CAUI_4_C2C:
        case BDK_QLM_MODE_CAUI_4_C2M:
        case BDK_QLM_MODE_100G_CR4:
        case BDK_QLM_MODE_100G_KR4:
            gsern_mode = CAVM_GSERN_MODE_CGX;
            /* Although quad lane these modes don't need the QUAD flag */
            is_network = true;
            break;
        case BDK_QLM_MODE_SATA:
        case BDK_QLM_MODE_LAST:
            return -1;
    }

    /* Figure out how many lanes to apply the mode to */
    int start_lane = (lane == -1) ? 0 : lane;
    int end_lane = (lane == -1) ? num_lanes - 1 : lane;

    /* Loop through all lanes */
    for (int l = start_lane; l <= end_lane; l++)
    {
        /* Only networking requires a call per lane */
        if (is_network || (l == 0))
        {
            if (cavm_gsern_set_mode(node, qlm, l, gsern_mode, is_first, baud_mhz, gsern_flags))
                return -1;
        }
        BDK_CSR_WRITE(node, BDK_GSERNX_LANEX_SCRATCHX(qlm, l, 0), state.u);
        __bdk_qlm_tune_gsern(node, qlm, l, mode, baud_mhz);
    }

    return 0;
}

