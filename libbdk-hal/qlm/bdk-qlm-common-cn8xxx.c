/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include "bdk-qlm-common.h"
#include "libbdk-arch/bdk-csrs-gser.h"
#include "libbdk-arch/bdk-csrs-pem.h"

/* Indexed by QLM number and lane */
static uint64_t prbs_errors[14][4];

/**
 * Setup the PEM to either driver or receive reset from PRST based on RC or EP
 *
 * @param node   Node to use in a Numa setup
 * @param pem    Which PEM to setuo
 * @param is_endpoint
 *               Non zero if PEM is a EP
 */
void __bdk_qlm_setup_pem_reset_cn8xxx(bdk_node_t node, int pem, int is_endpoint)
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
            BDK_CSR_MODIFY(c, node, BDK_PEMX_CLK_EN(pem),
                c.cn83xx.pceclk_gate = 0;
                c.cn83xx.csclk_gate = 0);
            BDK_CSR_MODIFY(c, node, BDK_PEMX_ON(pem),
                c.s.pemon = 1);
        }
    }
}

/**
 * Figure out which lane mode to use for a given reference clock and GBaud
 *
 * @param mode_name String name for error messages
 * @param qlm       QlM being configured
 * @param ref_clk   Reference clock in hertz
 * @param baud_mhz  Baud rate in Mhz
 *
 * @return Lane mode or -1 on failure
 */
int __bdk_qlm_get_lane_mode_for_speed_and_ref_clk_cn8xxx(const char *mode_name, int qlm, int ref_clk, int baud_mhz)
{
    if (baud_mhz <= 1250)
    {
        if ((ref_clk == REF_156MHZ) || (ref_clk == REF_100MHZ))
            return BDK_GSER_LMODE_E_R_125G_REFCLK15625_SGMII;
        else
        {
            bdk_error("Invalid reference clock for %s on QLM%d with speed %d, ref %d Mhz\n", mode_name, qlm, baud_mhz, ref_clk / 1000000);
            return -1;
        }
    }
    else if (baud_mhz <= 2500)
    {
        if (ref_clk == REF_100MHZ)
            return BDK_GSER_LMODE_E_R_25G_REFCLK100;
        else if (ref_clk == REF_125MHZ)
            return BDK_GSER_LMODE_E_R_25G_REFCLK125;
        else
        {
            bdk_error("Invalid reference clock for %s on QLM%d with speed %d, ref %d Mhz\n", mode_name, qlm, baud_mhz, ref_clk / 1000000);
            return -1;
        }
    }
    else if (baud_mhz <= 3125)
    {
        if (ref_clk == REF_156MHZ)
            return BDK_GSER_LMODE_E_R_3125G_REFCLK15625_XAUI;
        else
        {
            bdk_error("Invalid reference clock for %s on QLM%d with speed %d, ref %d Mhz\n", mode_name, qlm, baud_mhz, ref_clk / 1000000);
            return -1;
        }
    }
    else if (baud_mhz <= 5000)
    {
        if (ref_clk == REF_100MHZ)
            return BDK_GSER_LMODE_E_R_5G_REFCLK100;
        else if (ref_clk == REF_125MHZ)
            return BDK_GSER_LMODE_E_R_5G_REFCLK125;
        else
            return BDK_GSER_LMODE_E_R_5G_REFCLK15625_QSGMII;
    }
    else if (baud_mhz <= 6250)
    {
        if (ref_clk == REF_156MHZ)
            return BDK_GSER_LMODE_E_R_625G_REFCLK15625_RXAUI;
        else
        {
            bdk_error("Invalid reference clock for %s on QLM%d with speed %d, ref %d Mhz\n", mode_name, qlm, baud_mhz, ref_clk / 1000000);
            return -1;
        }
    }
    else if (baud_mhz <= 8000)
    {
        if (ref_clk == REF_100MHZ)
            return BDK_GSER_LMODE_E_R_8G_REFCLK100;
        else if (ref_clk == REF_125MHZ)
            return BDK_GSER_LMODE_E_R_8G_REFCLK125;
        else
        {
            bdk_error("Invalid reference clock for %s on QLM%d with speed %d, ref %d Mhz\n", mode_name, qlm, baud_mhz, ref_clk / 1000000);
            return -1;
        }
    }
    else /* Baud 10312.5 */
    {
        if (ref_clk == REF_156MHZ)
            return BDK_GSER_LMODE_E_R_103125G_REFCLK15625_KR;
        else
        {
            bdk_error("Invalid reference clock for %s on QLM%d with speed %d, ref %d Mhz\n", mode_name, qlm, baud_mhz, ref_clk / 1000000);
            return -1;
        }
    }
    bdk_error("Invalid speed for %s on QLM%d with speed %d, ref %d Mhz\n", mode_name, qlm, baud_mhz, ref_clk / 1000000);
    return -1;
}

/**
 * Measure the reference clock of a QLM
 *
 * @param qlm    QLM to measure
 *
 * @return Clock rate in Hz
 */
int __bdk_qlm_measure_refclock_cn8xxx(bdk_node_t node, int qlm)
{
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        BDK_CSR_INIT(refclk, node, BDK_GSERX_REFCLK_SEL(qlm));
        if (refclk.s.com_clk_sel)
        {
            if (refclk.s.use_com1)
                return REF_156MHZ;
            else
                return REF_100MHZ;
        }
        else
            return REF_100MHZ;
    }

    /* Clear the counter */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_REFCLK_EVT_CTRL(qlm),
        c.s.enb = 0;
        c.s.clr = 1);
    bdk_wait_usec(1); /* Give counter a chance to clear */
    if (BDK_CSR_READ(node, BDK_GSERX_REFCLK_EVT_CNTR(qlm)))
        bdk_error("GSER%d: Ref clock counter not zero\n", qlm);
    /* Start counting */
    uint64_t start = bdk_clock_get_count(BDK_CLOCK_TIME);
    BDK_CSR_MODIFY(c, node, BDK_GSERX_REFCLK_EVT_CTRL(qlm),
        c.s.enb = 1;
        c.s.clr = 0);
    /* Wait for a short time to get a number of counts */
    bdk_wait_usec(20000); /* 20ms */
    /* Stop counting */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_REFCLK_EVT_CTRL(qlm),
        c.s.enb = 0);
    uint64_t stop = bdk_clock_get_count(BDK_CLOCK_TIME);
    bdk_wait_usec(1); /* Give counter a chance to stabalize */

    /* Calculate the rate */
    uint64_t count = BDK_CSR_READ(node, BDK_GSERX_REFCLK_EVT_CNTR(qlm));
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
int __bdk_qlm_reset_cn8xxx(bdk_node_t node, int qlm)
{
    BDK_CSR_MODIFY(c, node, BDK_GSERX_PHY_CTL(qlm),
        c.s.phy_reset = 1);
    return 0;
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
int __bdk_qlm_enable_prbs_cn8xxx(bdk_node_t node, int qlm, int prbs, bdk_qlm_direction_t dir)
{
    const int NUM_LANES = bdk_qlm_get_lanes(node, qlm);
    int mode;
    switch (prbs)
    {
        case 31:
            mode = 1;
            break;
        case 23:
            mode = 2; /* Or 3? */
            break;
        case 16:
            mode = 4;
            break;
        case 15:
            mode = 5;
            break;
        case 11:
            mode = 6;
            break;
        case 7:
            mode = 7;
            break;
        default:
            mode = prbs & 0xff;
            for (int lane = 0; lane < NUM_LANES; lane++)
                BDK_CSR_WRITE(node, BDK_GSERX_LANEX_LBERT_PAT_CFG(qlm, lane), prbs >> 8);
            BDK_TRACE(QLM, "Using mode 0x%x with custom pattern 0x%x\n", mode, prbs >> 8);
            break;
    }

    /* For some reason PRBS doesn't work if GSER is configured for PCIe.
       Disconnect PCIe when we start PRBS */
    BDK_CSR_INIT(gserx_cfg, node, BDK_GSERX_CFG(qlm));
    if (gserx_cfg.s.pcie)
    {
        gserx_cfg.s.pcie = 0;
        BDK_CSR_WRITE(node, BDK_GSERX_CFG(qlm), gserx_cfg.u);
        bdk_warn("N%d.QLM%d: Disabling PCIe for PRBS/pattern generation\n", node, qlm);
    }
    /* For some reason PRBS doesn't work if GSER is configured for SATA.
       Disconnect SATA when we start PRBS */
    if (gserx_cfg.s.sata)
    {
        gserx_cfg.s.sata = 0;
        BDK_CSR_WRITE(node, BDK_GSERX_CFG(qlm), gserx_cfg.u);
        bdk_warn("N%d.QLM%d: Disabling SATA for PRBS/pattern generation\n", node, qlm);
        bdk_warn("N%d.QLM%d: SATA PRBS/patterns always run at 6G\n", node, qlm);
    }

    BDK_CSR_MODIFY(c, node, BDK_GSERX_PHY_CTL(qlm),
        c.s.phy_reset = 0);

    if (dir & BDK_QLM_DIRECTION_TX)
    {
        /* Disable first in case already running */
        for (int lane = 0; lane < NUM_LANES; lane++)
            BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_LBERT_CFG(qlm, lane),
                c.s.lbert_pg_en = 0);
        for (int lane = 0; lane < NUM_LANES; lane++)
            BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_LBERT_CFG(qlm, lane),
                c.s.lbert_pg_en = 1; /* Enable generator */
                c.s.lbert_pg_width = 3; /* 20 bit */
                c.s.lbert_pg_mode = mode);
    }

    if (dir & BDK_QLM_DIRECTION_RX)
    {
        /* Clear the error counter and Disable the matcher */
        for (int lane = 0; lane < NUM_LANES; lane++)
        {
            prbs_errors[qlm][lane] = 0;
            BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_LBERT_CFG(qlm, lane),
                c.s.lbert_pm_en = 0);
        }
        for (int lane = 0; lane < NUM_LANES; lane++)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_LBERT_CFG(qlm, lane),
                c.s.lbert_pm_en = 1; /* Enable matcher */
                c.s.lbert_pm_width = 3; /* 20 bit */
                c.s.lbert_pm_mode = mode);
        }
        /* Tell the matcher to start sync */
        for (int retry=0; retry < 4; retry++)
        {
            for (int lane = 0; lane < NUM_LANES; lane++)
            {
                BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_LBERT_CFG(qlm, lane),
                    c.s.lbert_pm_sync_start = 1);
            }
            /* Wait 10ms */
            bdk_wait_usec(10000);
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
int __bdk_qlm_disable_prbs_cn8xxx(bdk_node_t node, int qlm)
{
    const int NUM_LANES = bdk_qlm_get_lanes(node, qlm);
    BDK_CSR_INIT(phy_ctl, node, BDK_GSERX_PHY_CTL(qlm));
    if (phy_ctl.s.phy_reset)
        return -1;

    for (int lane = 0; lane < NUM_LANES; lane++)
    {
        prbs_errors[qlm][lane] = 0;
        BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_LBERT_CFG(qlm, lane),
            c.s.lbert_pg_en = 0;
            c.s.lbert_pm_en = 0);
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
uint64_t __bdk_qlm_get_prbs_errors_cn8xxx(bdk_node_t node, int qlm, int lane, int clear)
{
    /* Restart synchronization */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_LBERT_CFG(qlm, lane),
        c.s.lbert_pm_sync_start = 1);
    /* This CSR is self clearing per the CSR description, but it doesn't
       seem to do that. Instead it clears when we trigger sync again */
    BDK_CSR_INIT(rx, node, BDK_GSERX_LANEX_LBERT_ECNT(qlm, lane));
    uint64_t errors = rx.s.lbert_err_cnt;
    if (rx.s.lbert_err_ovbit14)
        errors <<= 7;
    prbs_errors[qlm][lane] += errors;
    uint64_t result = prbs_errors[qlm][lane];
    if (clear)
        prbs_errors[qlm][lane] = 0;
    return result;
}

/**
 * Inject an error into PRBS
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 */
void __bdk_qlm_inject_prbs_error_cn8xxx(bdk_node_t node, int qlm, int lane)
{
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_LBERT_CFG(qlm, lane),
        c.s.lbert_pg_err_insert = 1);
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
int __bdk_qlm_enable_loop_cn8xxx(bdk_node_t node, int qlm, bdk_qlm_loop_t loop)
{
    int num_lanes = bdk_qlm_get_lanes(node, qlm);
    for (int lane = 0; lane < num_lanes; lane++)
    {
        BDK_CSR_INIT(lanex_misc_cfg_0, node, BDK_GSERX_LANEX_MISC_CFG_0(qlm, lane));
        switch (loop)
        {
            case BDK_QLM_LOOP_DISABLED:
                lanex_misc_cfg_0.s.cfg_pcs_loopback = 0;
                break;
            case BDK_QLM_LOOP_CORE:
            case BDK_QLM_LOOP_NEAR_END: /* Using digital as an approximation. Nobody will notice */
                /* Near end loop TX to RX in PCS */
                lanex_misc_cfg_0.s.cfg_pcs_loopback = 1;
                break;
            case BDK_QLM_LOOP_SHALLOW:
                bdk_error("Shallow loopback not supported on this chip\n");
                return -1;
        }
        BDK_CSR_WRITE(node, BDK_GSERX_LANEX_MISC_CFG_0(qlm, lane), lanex_misc_cfg_0.u);
    }
    return 0;
}

/**
 * Initialize the QLM mode table
 *
 * @param node    Node to initialize
 * @param qlm     Which QLM
 * @param ref_clk Reference clock of the QLM in Hz
 */
void __bdk_qlm_init_mode_table_cn8xxx(bdk_node_t node, int qlm, int ref_clk)
{
    /* The QLM PLLs are controlled by an array of parameters indexed
       by the QLM mode for each QLM. We need to fill in these tables.
       Also each lane has some mode parameters, again in a array index
       by the lane_mode */
    for (int lane_mode = 0; lane_mode < 12; lane_mode++)
    {
        /* The values used below are all from
           http://mawiki.caveonetworks.com/wiki/78xx/GSER_WEST */
        BDK_CSR_INIT(pll_mode_0 , node, BDK_GSERX_PLL_PX_MODE_0(qlm, lane_mode));
        BDK_CSR_INIT(pll_mode_1 , node, BDK_GSERX_PLL_PX_MODE_1(qlm, lane_mode));
        BDK_CSR_INIT(lane_mode_0, node, BDK_GSERX_LANE_PX_MODE_0(qlm, lane_mode));
        BDK_CSR_INIT(lane_mode_1, node, BDK_GSERX_LANE_PX_MODE_1(qlm, lane_mode));
        switch (lane_mode)
        {
            case BDK_GSER_LMODE_E_R_25G_REFCLK100:
            case BDK_GSER_LMODE_E_R_5G_REFCLK100:
            case BDK_GSER_LMODE_E_R_8G_REFCLK100:
                /* These modes are used for PCIe where the defaults are
                   correct. Skip programming these */
                continue;
            case BDK_GSER_LMODE_E_R_125G_REFCLK15625_KX:
                pll_mode_0.s.pll_icp = 0x1;
                pll_mode_0.s.pll_rloop = 0x3;
                pll_mode_0.s.pll_pcs_div = 0x28;

                pll_mode_1.s.pll_16p5en = 0x1;
                pll_mode_1.s.pll_cpadj = 0x3;
                pll_mode_1.s.pll_pcie3en = 0x0;
                pll_mode_1.s.pll_opr = 0x0;
                pll_mode_1.s.pll_div = 0x10;

                lane_mode_0.s.ctle = 0x0;
                lane_mode_0.s.pcie = 0x0;
                lane_mode_0.s.tx_ldiv = 0x2;
                lane_mode_0.s.rx_ldiv = 0x2;
                lane_mode_0.s.srate = 0x0;
                lane_mode_0.s.tx_mode = 0x3;
                lane_mode_0.s.rx_mode = 0x3;

                lane_mode_1.s.vma_fine_cfg_sel = 0x0;
                lane_mode_1.s.vma_mm = 0x1;
                lane_mode_1.s.cdr_fgain = 0xc;
                lane_mode_1.s.ph_acc_adj = 0x1e;
                break;
            case BDK_GSER_LMODE_E_R_3125G_REFCLK15625_XAUI:
                pll_mode_0.s.pll_icp = 0x1;
                pll_mode_0.s.pll_rloop = 0x3;
                pll_mode_0.s.pll_pcs_div = 0x14;

                pll_mode_1.s.pll_16p5en = 0x1;
                pll_mode_1.s.pll_cpadj = 0x2;
                pll_mode_1.s.pll_pcie3en = 0x0;
                pll_mode_1.s.pll_opr = 0x0;
                pll_mode_1.s.pll_div = 0x14;

                lane_mode_0.s.ctle = 0x0;
                lane_mode_0.s.pcie = 0x0;
                lane_mode_0.s.tx_ldiv = 0x1;
                lane_mode_0.s.rx_ldiv = 0x1;
                lane_mode_0.s.srate = 0x0;
                lane_mode_0.s.tx_mode = 0x3;
                lane_mode_0.s.rx_mode = 0x3;

                lane_mode_1.s.vma_fine_cfg_sel = 0x0;
                lane_mode_1.s.vma_mm = 0x1;
                lane_mode_1.s.cdr_fgain = 0xc;
                lane_mode_1.s.ph_acc_adj = 0x1e;
                break;
            case BDK_GSER_LMODE_E_R_103125G_REFCLK15625_KR:
                pll_mode_0.s.pll_icp = 0x1;
                pll_mode_0.s.pll_rloop = 0x5;
                pll_mode_0.s.pll_pcs_div = 0xa;

                pll_mode_1.s.pll_16p5en = 0x1;
                pll_mode_1.s.pll_cpadj = 0x2;
                pll_mode_1.s.pll_pcie3en = 0x0;
                pll_mode_1.s.pll_opr = 0x1;
                pll_mode_1.s.pll_div = 0x21;

                lane_mode_0.s.ctle = 0x3;
                lane_mode_0.s.pcie = 0x0;
                lane_mode_0.s.tx_ldiv = 0x0;
                lane_mode_0.s.rx_ldiv = 0x0;
                lane_mode_0.s.srate = 0x0;
                lane_mode_0.s.tx_mode = 0x3;
                lane_mode_0.s.rx_mode = 0x3;

                lane_mode_1.s.vma_fine_cfg_sel = 0x1;
                lane_mode_1.s.vma_mm = 0x0;
                lane_mode_1.s.cdr_fgain = 0xa;
                lane_mode_1.s.ph_acc_adj = 0xf;
                break;
            case BDK_GSER_LMODE_E_R_125G_REFCLK15625_SGMII:
                pll_mode_0.s.pll_icp = 0x1;
                pll_mode_0.s.pll_rloop = 0x3;
                pll_mode_0.s.pll_pcs_div = 0x28;

                pll_mode_1.s.pll_16p5en = 0x1;
                pll_mode_1.s.pll_cpadj = 0x3;
                pll_mode_1.s.pll_pcie3en = 0x0;
                pll_mode_1.s.pll_opr = 0x0;
                pll_mode_1.s.pll_div = 0x10;

                lane_mode_0.s.ctle = 0x0;
                lane_mode_0.s.pcie = 0x0;
                lane_mode_0.s.tx_ldiv = 0x2;
                lane_mode_0.s.rx_ldiv = 0x2;
                lane_mode_0.s.srate = 0x0;
                lane_mode_0.s.tx_mode = 0x3;
                lane_mode_0.s.rx_mode = 0x3;

                lane_mode_1.s.vma_fine_cfg_sel = 0x0;
                lane_mode_1.s.vma_mm = 0x1;
                lane_mode_1.s.cdr_fgain = 0xc;
                lane_mode_1.s.ph_acc_adj = 0x1e;
                if(ref_clk == REF_100MHZ)
                {
                    pll_mode_0.s.pll_pcs_div = 0x28;
                    pll_mode_1.s.pll_div = 0x19;
                    pll_mode_1.s.pll_cpadj = 0x2;
                }
                break;
            case BDK_GSER_LMODE_E_R_5G_REFCLK15625_QSGMII:
                pll_mode_0.s.pll_icp = 0x1; /* Per Scott McIlhenny 5/17/2016 (t81) */
                pll_mode_0.s.pll_rloop = 0x3;
                pll_mode_0.s.pll_pcs_div = 0xa;

                pll_mode_1.s.pll_16p5en = 0x0;
                pll_mode_1.s.pll_cpadj = 0x2;
                pll_mode_1.s.pll_pcie3en = 0x0;
                pll_mode_1.s.pll_opr = 0x0;
                /* QSGMII is a special case. We use the same table entry for
                   100Mhz and 125Mhz clocks as the normal 156Mhz */
                switch (ref_clk)
                {
                    case REF_100MHZ:
                        pll_mode_1.s.pll_div = 0x19;
                        break;
                    case REF_125MHZ:
                        pll_mode_1.s.pll_div = 0x14;
                        break;
                    default: /* REF_156MHZ */
                        pll_mode_1.s.pll_div = 0x10;
                        break;
                }

                lane_mode_0.s.ctle = 0x0;
                lane_mode_0.s.pcie = 0x0;
                lane_mode_0.s.tx_ldiv = 0x0;
                lane_mode_0.s.rx_ldiv = 0x0;
                lane_mode_0.s.srate = 0x0;
                lane_mode_0.s.tx_mode = 0x3;
                lane_mode_0.s.rx_mode = 0x3;

                lane_mode_1.s.vma_fine_cfg_sel = 0x0;
                lane_mode_1.s.vma_mm = 0x1; /* Per Scott McIlhenny 5/17/2016 (t81) */
                lane_mode_1.s.cdr_fgain = 0xc;
                lane_mode_1.s.ph_acc_adj = 0x1e;
                break;
            case BDK_GSER_LMODE_E_R_625G_REFCLK15625_RXAUI:
                pll_mode_0.s.pll_icp = 0x1;
                pll_mode_0.s.pll_rloop = 0x3;
                pll_mode_0.s.pll_pcs_div = 0xa;

                pll_mode_1.s.pll_16p5en = 0x0;
                pll_mode_1.s.pll_cpadj = 0x2;
                pll_mode_1.s.pll_pcie3en = 0x0;
                pll_mode_1.s.pll_opr = 0x0;
                pll_mode_1.s.pll_div = 0x14;

                lane_mode_0.s.ctle = 0x0;
                lane_mode_0.s.pcie = 0x0;
                lane_mode_0.s.tx_ldiv = 0x0;
                lane_mode_0.s.rx_ldiv = 0x0;
                lane_mode_0.s.srate = 0x0;
                lane_mode_0.s.tx_mode = 0x3;
                lane_mode_0.s.rx_mode = 0x3;

                lane_mode_1.s.vma_fine_cfg_sel = 0x0;
                lane_mode_1.s.vma_mm = 0x0;
                lane_mode_1.s.cdr_fgain = 0xa;
                lane_mode_1.s.ph_acc_adj = 0x14;
                break;
            case BDK_GSER_LMODE_E_R_25G_REFCLK125:
                pll_mode_0.s.pll_icp = 0x3;
                pll_mode_0.s.pll_rloop = 0x3;
                pll_mode_0.s.pll_pcs_div = 0x5;

                pll_mode_1.s.pll_16p5en = 0x0;
                pll_mode_1.s.pll_cpadj = 0x1;
                pll_mode_1.s.pll_pcie3en = 0x0;
                pll_mode_1.s.pll_opr = 0x0;
                pll_mode_1.s.pll_div = 0x14;

                lane_mode_0.s.ctle = 0x0;
                lane_mode_0.s.pcie = 0x1;
                lane_mode_0.s.tx_ldiv = 0x1;
                lane_mode_0.s.rx_ldiv = 0x1;
                lane_mode_0.s.srate = 0x0;
                lane_mode_0.s.tx_mode = 0x3;
                lane_mode_0.s.rx_mode = 0x3;

                lane_mode_1.s.vma_fine_cfg_sel = 0x0;
                lane_mode_1.s.vma_mm = 0x1;
                lane_mode_1.s.cdr_fgain = 0xa;
                lane_mode_1.s.ph_acc_adj = 0x14;
                break;
            case BDK_GSER_LMODE_E_R_5G_REFCLK125:
                pll_mode_0.s.pll_icp = 0x3;
                pll_mode_0.s.pll_rloop = 0x3;
                pll_mode_0.s.pll_pcs_div = 0xa;

                pll_mode_1.s.pll_16p5en = 0x0;
                pll_mode_1.s.pll_cpadj = 0x1;
                pll_mode_1.s.pll_pcie3en = 0x0;
                pll_mode_1.s.pll_opr = 0x0;
                pll_mode_1.s.pll_div = 0x14;

                lane_mode_0.s.ctle = 0x0;
                lane_mode_0.s.pcie = 0x1;
                lane_mode_0.s.tx_ldiv = 0x0;
                lane_mode_0.s.rx_ldiv = 0x0;
                lane_mode_0.s.srate = 0x0;
                lane_mode_0.s.tx_mode = 0x3;
                lane_mode_0.s.rx_mode = 0x3;

                lane_mode_1.s.vma_fine_cfg_sel = 0x0;
                lane_mode_1.s.vma_mm = 0x0;
                lane_mode_1.s.cdr_fgain = 0xa;
                lane_mode_1.s.ph_acc_adj = 0x14;
                break;
            case BDK_GSER_LMODE_E_R_8G_REFCLK125:
                pll_mode_0.s.pll_icp = 0x2;
                pll_mode_0.s.pll_rloop = 0x5;
                pll_mode_0.s.pll_pcs_div = 0xa;

                pll_mode_1.s.pll_16p5en = 0x0;
                pll_mode_1.s.pll_cpadj = 0x1;
                pll_mode_1.s.pll_pcie3en = 0x1;
                pll_mode_1.s.pll_opr = 0x1;
                pll_mode_1.s.pll_div = 0x20;

                lane_mode_0.s.ctle = 0x3;
                lane_mode_0.s.pcie = 0x0;
                lane_mode_0.s.tx_ldiv = 0x0;
                lane_mode_0.s.rx_ldiv = 0x0;
                lane_mode_0.s.srate = 0x0;
                lane_mode_0.s.tx_mode = 0x2;
                lane_mode_0.s.rx_mode = 0x2;

                lane_mode_1.s.vma_fine_cfg_sel = 0x0;
                lane_mode_1.s.vma_mm = 0x0;
                lane_mode_1.s.cdr_fgain = 0xb;
                lane_mode_1.s.ph_acc_adj = 0x23;
                break;
        }
        BDK_CSR_WRITE(node, BDK_GSERX_PLL_PX_MODE_0(qlm, lane_mode), pll_mode_0.u);
        BDK_CSR_WRITE(node, BDK_GSERX_PLL_PX_MODE_1(qlm, lane_mode), pll_mode_1.u);
        BDK_CSR_WRITE(node, BDK_GSERX_LANE_PX_MODE_0(qlm, lane_mode), lane_mode_0.u);
        BDK_CSR_WRITE(node, BDK_GSERX_LANE_PX_MODE_1(qlm, lane_mode), lane_mode_1.u);
    }
}

/**
 * Given a valid PEM number, return its speed in Gbaud
 *
 * @param node   Node to use in numa setup
 * @param pem    PEM to get speed of
 *
 * @return Speed in Gbaud. Zero if disabled
 */
int __bdk_qlm_get_gbaud_mhz_pem_cn8xxx(bdk_node_t node, int pem)
{
    BDK_CSR_INIT(pem_cfg, node, BDK_PEMX_CFG(pem));
    switch (pem_cfg.cn83xx.md)
    {
        case 0: /* Gen 1 */
            return 2500;
        case 1: /* Gen 2 */
            return 5000;
        case 2: /* Gen 3 */
            return 8000;
        default:
            return 0;
    }
}

/**
 * Get the speed of a QLM using its LMODE. This can't be used on PCIe QLMs.
 *
 * @param node   Node to use in numa setup
 * @param qlm    Which QLM
 *
 * @return QLM speed on Gbaud
 */
int __bdk_qlm_get_gbaud_mhz_lmode_cn8xxx(bdk_node_t node, int qlm)
{
    /* QLM is not in PCIe, assume LMODE is good enough for determining
       the speed */
    BDK_CSR_INIT(lane_mode, node, BDK_GSERX_LANE_MODE(qlm));
    switch (lane_mode.s.lmode)
    {
        case BDK_GSER_LMODE_E_R_25G_REFCLK100:
            return 2500;
        case BDK_GSER_LMODE_E_R_5G_REFCLK100:
            return 5000;
        case BDK_GSER_LMODE_E_R_8G_REFCLK100:
            return 8000;
        case BDK_GSER_LMODE_E_R_125G_REFCLK15625_KX:
            return 1250;
        case BDK_GSER_LMODE_E_R_3125G_REFCLK15625_XAUI:
            return 3125;
        case BDK_GSER_LMODE_E_R_103125G_REFCLK15625_KR:
            return 10312;
        case BDK_GSER_LMODE_E_R_125G_REFCLK15625_SGMII:
            return 1250;
        case BDK_GSER_LMODE_E_R_5G_REFCLK15625_QSGMII:
            return 5000;
        case BDK_GSER_LMODE_E_R_625G_REFCLK15625_RXAUI:
            return 6250;
        case BDK_GSER_LMODE_E_R_25G_REFCLK125:
            return 2500;
        case BDK_GSER_LMODE_E_R_5G_REFCLK125:
            return 5000;
        case BDK_GSER_LMODE_E_R_8G_REFCLK125:
            return 8000;
        default:
            return 0;
    }
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
void __bdk_qlm_display_settings_cn8xxx(bdk_node_t node, int qlm, int qlm_lane, bool show_tx, bool show_rx)
{
    const char *dir_label[] = {"Hold", "Inc", "Dec", "Hold"};

    uint64_t rx_aeq_out_0 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_AEQ_OUT_0(qlm, qlm_lane));
    uint64_t rx_aeq_out_1 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_AEQ_OUT_1(qlm, qlm_lane));
    uint64_t rx_aeq_out_2 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_AEQ_OUT_2(qlm, qlm_lane));
    uint64_t rx_vma_status_0 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_VMA_STATUS_0(qlm, qlm_lane));
    uint64_t rx_vma_status_1 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_VMA_STATUS_1(qlm, qlm_lane));
    uint64_t sds_pin_mon_1 = BDK_CSR_READ(node, BDK_GSERX_LANEX_SDS_PIN_MON_1(qlm, qlm_lane));
    uint64_t sds_pin_mon_2 = BDK_CSR_READ(node, BDK_GSERX_LANEX_SDS_PIN_MON_2(qlm, qlm_lane));
    uint64_t br_rxx_eer = BDK_CSR_READ(node, BDK_GSERX_BR_RXX_EER(qlm, qlm_lane));
    BDK_CSR_INIT(tx_cfg_3, node, BDK_GSERX_LANEX_TX_CFG_3(qlm, qlm_lane));

    printf("N%d.QLM%d Lane %d:\n", node, qlm, qlm_lane);
    if (show_rx)
    {
        int fom = bdk_extract(br_rxx_eer, 6, 8);
        BDK_CSR_INIT(gser_cfg, node, BDK_GSERX_CFG(qlm));
        if (gser_cfg.s.pcie)
        {
            uint64_t dwc_rx_delta_pm_0 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_DELTA_PM_0(qlm, qlm_lane));
            uint64_t dwc_rx_delta_pm_1 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_DELTA_PM_1(qlm, qlm_lane));
            BDK_CSR_INIT(gser_lane_mode, node, BDK_GSERX_LANE_MODE(qlm));
            BDK_CSR_INIT(lane_mode_1, node, BDK_GSERX_LANE_PX_MODE_1(qlm, gser_lane_mode.s.lmode));
            BDK_CSR_INIT(vma_fine_ctrl_0, node, BDK_GSERX_LANE_VMA_FINE_CTRL_0(qlm));
            BDK_CSR_INIT(vma_coarse_ctrl_0, node, BDK_GSERX_LANE_VMA_COARSE_CTRL_0(qlm));

            /* PCIe FOM Calculations: */
            int rx_vma_esamp_delta = bdk_extract(rx_vma_status_1, 4, 3);
            int rx_vma_delta = 7 - rx_vma_esamp_delta;
            int rx_vma_count = (bdk_extract(dwc_rx_delta_pm_0, 0, 3) << 16) | bdk_extract(dwc_rx_delta_pm_1, 0, 16);
            int rx_fom_delta = (rx_vma_esamp_delta >= 4) ? 0 : (rx_vma_delta & 3);
            int vma_window_wait = (lane_mode_1.s.vma_fine_cfg_sel) ? vma_fine_ctrl_0.s.vma_window_wait_fine : vma_coarse_ctrl_0.s.window_wait;
            int rx_fom_count = bdk_extract(rx_vma_count, (vma_window_wait & 7) + 4, 8);
            fom = (rx_fom_delta << 6) | bdk_extract(rx_fom_count, 2, 6);
        }
        printf("    DFE Tap 1: %lu, Tap 2: %ld, Tap 3: %ld, Tap 4: %ld, Tap 5: %ld\n",
            bdk_extract(rx_aeq_out_1, 0, 5),
            bdk_extract_smag(rx_aeq_out_1, 5, 9),
            bdk_extract_smag(rx_aeq_out_1, 10, 14),
            bdk_extract_smag(rx_aeq_out_0, 0, 4),
            bdk_extract_smag(rx_aeq_out_0, 5, 9));
        printf("    Pre-CTLE Gain: %lu, Post-CTLE Gain: %lu, CTLE Peak: %lu, CTLE Pole: %lu\n",
            bdk_extract(rx_aeq_out_2, 4, 4),
            bdk_extract(rx_aeq_out_2, 0, 4),
            bdk_extract(rx_vma_status_0, 2, 4),
            bdk_extract(rx_vma_status_0, 0, 2));
        printf("    RX Equalization Tx Directions Hints TXPRE: %s, TXMAIN: %s, TXPOST: %s, Figure of Merit: %d\n",
            dir_label[bdk_extract(br_rxx_eer, 0, 2)],
            dir_label[bdk_extract(br_rxx_eer, 2, 2)],
            dir_label[bdk_extract(br_rxx_eer, 4, 2)],
            fom);
    }
    if (show_tx)
    {
        printf("    TX Swing: %lu, Pre-emphasis Pre-cursor: %lu, Post-cursor: %lu\n",
            bdk_extract(sds_pin_mon_1, 1, 5),
            bdk_extract(sds_pin_mon_2, 0, 4),
            bdk_extract(sds_pin_mon_2, 4, 5));
        printf("    TX Boost Enable: %lu, TX Turbo Mode: %lu, TX Gain: %d\n",
            bdk_extract(sds_pin_mon_2, 10, 1),
            bdk_extract(sds_pin_mon_2, 9, 1),
            tx_cfg_3.s.pcs_sds_tx_gain);
    }
    printf("    Training-done: %lu\n",
           bdk_extract(rx_vma_status_1, 7, 1));
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
int __bdk_qlm_rx_equalization_cn8xxx(bdk_node_t node, int qlm, int qlm_lane)
{
    /* Emulator doesn't support GSER */
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return 0;
    /* Don't touch QLMs is reset or powered down */
    BDK_CSR_INIT(phy_ctl, node, BDK_GSERX_PHY_CTL(qlm));
    if (phy_ctl.s.phy_pd || phy_ctl.s.phy_reset)
        return -1;
    /* Don't run on PCIe links */
    if (bdk_qlm_get_mode(node, qlm, 0) <= BDK_QLM_MODE_PCIE_X8)
        return -1;

    int fail = 0; /* Bitmask of lanes that failed CDR Lock or Eltrical Idle check */
    int pending = 0; /* Bitmask of lanes that we're waiting for */
    int MAX_LANES = bdk_qlm_get_lanes(node, qlm);

    BDK_TRACE(QLM, "N%d.QLM%d: Starting RX equalization on lane %d\n", node, qlm, qlm_lane);
    for (int lane = 0; lane < MAX_LANES; lane++)
    {
        /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;
        /* Check that the lane has completed CDR lock */
        BDK_CSR_INIT(eie_detsts, node, BDK_GSERX_RX_EIE_DETSTS(qlm));
        if (((1 << lane) & eie_detsts.s.cdrlock) == 0)
        {
            /* Mark bad so we skip this lane below */
            fail |= 1 << lane;
            continue;
        }
        /* Enable software control */
        BDK_CSR_MODIFY(c, node, BDK_GSERX_BR_RXX_CTL(qlm, lane),
            c.s.rxt_swm = 1);
        /* Clear the completion flag and initiate a new request */
        BDK_CSR_MODIFY(c, node, BDK_GSERX_BR_RXX_EER(qlm, lane),
            c.s.rxt_esv = 0;
            c.s.rxt_eer = 1);
        /* Remember that we have to wait for this lane */
        pending |= 1 << lane;
    }

    /* Timing a few of these over XFI on CN73XX, each takes 21-23ms. XLAUI
       was about the same time. DXAUI and RXAUI both took 2-3ms. Put the
       timeout at 250ms, which is roughly 10x my measurements. */
    uint64_t timeout = bdk_clock_get_count(BDK_CLOCK_TIME) + bdk_clock_get_rate(node, BDK_CLOCK_TIME) / 4;
    while (pending)
    {
        for (int lane = 0; lane < MAX_LANES; lane++)
        {
            int lane_mask = 1 << lane;
            /* Only check lanes that are pending */
            if (!(pending & lane_mask))
                continue;
            /* Read the registers for checking Electrical Idle / CDR lock and
               the status of the RX equalization */
            BDK_CSR_INIT(eie_detsts, node, BDK_GSERX_RX_EIE_DETSTS(qlm));
            BDK_CSR_INIT(gserx_br_rxx_eer, node, BDK_GSERX_BR_RXX_EER(qlm, lane));
            /* Mark failure if lane entered Electrical Idle or lost CDR Lock. The
               bit for the lane will have cleared in either EIESTS or CDRLOCK */
            if (!(eie_detsts.s.eiests & eie_detsts.s.cdrlock & lane_mask))
            {
                fail |= lane_mask;
                pending &= ~lane_mask;
            }
            else if (gserx_br_rxx_eer.s.rxt_esv)
            {
                /* Clear pending if RX equalization finished */
                pending &= ~lane_mask;
            }
        }
        /* Break out of the loop on timeout */
        if (bdk_clock_get_count(BDK_CLOCK_TIME) > timeout)
            break;
        /* Yield to other threads while we wait */
        bdk_thread_yield();
    }

    /* Cleanup and report status */
    for (int lane = 0; lane < MAX_LANES; lane++)
    {
        /* Skip lanes we don't care about */
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;
        int lane_mask = 1 << lane;
        /* Get the final RX equalization status */
        BDK_CSR_INIT(gserx_br_rxx_eer, node, BDK_GSERX_BR_RXX_EER(qlm, lane));
        /* Disable software control */
        BDK_CSR_MODIFY(c, node, BDK_GSERX_BR_RXX_CTL(qlm, lane),
            c.s.rxt_swm = 0);
        /* Report status */
        if (fail & lane_mask)
        {
            BDK_TRACE(QLM, "N%d.QLM%d: Lane %d RX equalization lost CDR Lock or entered Electrical Idle\n", node, qlm, lane);
        }
        else if ((pending & lane_mask) || !gserx_br_rxx_eer.s.rxt_esv)
        {
            BDK_TRACE(QLM, "N%d.QLM%d: Lane %d RX equalization timeout\n", node, qlm, lane);
            fail |= 1 << lane;
        }
        else
        {
            if (bdk_trace_enables & (1ull << BDK_TRACE_ENABLE_QLM))
                bdk_qlm_display_settings(node, qlm, lane, false, true);
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
 * @param tx_swing  Transmit swing (coef 0) Range 0-31
 * @param tx_pre    Pre cursor emphasis (Coef -1). Range 0-15
 * @param tx_post   Post cursor emphasis (Coef +1). Range 0-31
 * @param tx_gain   Transmit gain. Range 0-7
 * @param tx_vboost Transmit voltage boost. Range 0-1
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_tune_lane_tx_cn8xxx(bdk_node_t node, int qlm, int lane, int tx_swing, int tx_pre, int tx_post, int tx_gain, int tx_vboost)
{
    /* Check tuning constraints */
    if ((tx_swing < 0) || (tx_swing > 25))
    {
        bdk_error("N%d.QLM%d: Lane %d: Invalid TX_SWING(%d)\n", node, qlm, lane, tx_swing);
        return -1;
    }
    if ((tx_pre < 0) || (tx_pre > 10))
    {
        bdk_error("N%d.QLM%d: Lane %d: Invalid TX_PRE(%d)\n", node, qlm, lane, tx_pre);
        return -1;
    }
    if ((tx_post < 0) || (tx_post > 15))
    {
        bdk_error("N%d.QLM%d: Lane %d: Invalid TX_POST(%d)\n", node, qlm, lane, tx_post);
        return -1;
    }
    if ((tx_pre >= 0) && (tx_post >= 0) && (tx_swing >= 0) && (tx_pre + tx_post - tx_swing > 2))
    {
        bdk_error("N%d.QLM%d: Lane %d: TX_PRE(%d) + TX_POST(%d) - TX_SWING(%d) must be less than or equal to 2\n", node, qlm, lane, tx_pre, tx_post, tx_swing);
        return -1;
    }
    if ((tx_pre >= 0) && (tx_post >= 0) && (tx_swing >= 0) && (tx_pre + tx_post + tx_swing > 35))
    {
        bdk_error("N%d.QLM%d: Lane %d: TX_PRE(%d) + TX_POST(%d) + TX_SWING(%d) must be less than or equal to 35\n", node, qlm, lane, tx_pre, tx_post, tx_swing);
        return -1;
    }

    if ((tx_gain < 0) || (tx_gain > 7))
    {
        bdk_error("N%d.QLM%d: Lane %d: Invalid TX_GAIN(%d). TX_GAIN must be between 0 and 7\n", node, qlm, lane, tx_gain);
        return -1;
    }

    if ((tx_vboost < 0) || (tx_vboost > 1))
    {
        bdk_error("N%d.QLM%d: Lane %d: Invalid TX_VBOOST(%d).  TX_VBOOST must be 0 or 1.\n", node, qlm, lane, tx_vboost);
        return -1;
    }

    BDK_TRACE(QLM, "N%d.QLM%d: Lane %d: TX_SWING=%d, TX_PRE=%d, TX_POST=%d, TX_GAIN=%d, TX_VBOOST=%d\n",
        node, qlm, lane, tx_swing, tx_pre, tx_post, tx_gain, tx_vboost);

    /* Manual Tx Swing and Tx Equalization Programming Steps */

    /* 1) Enable Tx swing and Tx emphasis overrides */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_TX_CFG_1(qlm, lane),
        c.s.tx_swing_ovrrd_en = 1;
        c.s.tx_premptap_ovrrd_val = 1;
        c.s.tx_vboost_en_ovrrd_en = 1); /* Vboost override */
    /* 2) Program the Tx swing and Tx emphasis Pre-cursor and Post-cursor values */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_TX_CFG_0(qlm, lane),
        c.s.cfg_tx_swing = tx_swing);
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_TX_PRE_EMPHASIS(qlm, lane),
        c.s.cfg_tx_premptap = (tx_post << 4) | tx_pre);
    /* Apply TX gain settings */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_TX_CFG_3(qlm, lane),
        c.s.pcs_sds_tx_gain = tx_gain);
    /* Apply TX vboost settings */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_TX_CFG_3(qlm, lane),
        c.s.cfg_tx_vboost_en = tx_vboost);
    /* 3) Program override for the Tx coefficient request */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_0(qlm, lane),
        c.s.cfg_tx_coeff_req_ovrrd_val = 1;
        c.s.cfg_tx_vboost_en_ovrrd_val = 1);
    /* 4) Enable the Tx coefficient request override enable */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
        c.s.cfg_tx_coeff_req_ovrrd_en = 1;
        c.s.cfg_tx_vboost_en_ovrrd_en = 1);
    /* 5) Issue a Control Interface Configuration Override request to start
        the Tx equalizer Optimization cycle which applies the new Tx swing
        and equalization settings */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
        c.s.ctlifc_ovrrd_req = 1);

    /* 6) Prepare for a subsequent Tx swing and Tx equalization adjustment:
        a) Disable the Tx coefficient request override enable */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
        c.s.cfg_tx_coeff_req_ovrrd_en = 0);
    /* b) Issue a Control Interface Configuration Override request */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
        c.s.ctlifc_ovrrd_req = 1);
    /* The new Tx swing and Pre-cursor and Post-cursor settings will now take
       effect. */
    return 0;
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
int __bdk_qlm_get_tune_lane_tx_cn8xxx(bdk_node_t node, int qlm, int lane, int *tx_swing, int *tx_pre, int *tx_post, int *tx_gain_bias, int *tx_vboost_unused)
{
    uint64_t sds_pin_mon_1 = BDK_CSR_READ(node, BDK_GSERX_LANEX_SDS_PIN_MON_1(qlm, lane));
    uint64_t sds_pin_mon_2 = BDK_CSR_READ(node, BDK_GSERX_LANEX_SDS_PIN_MON_2(qlm, lane));
    BDK_CSR_INIT(cfg_3, node, BDK_GSERX_LANEX_TX_CFG_3(qlm, lane));

    *tx_swing = bdk_extract(sds_pin_mon_1, 1, 5);
    *tx_pre = bdk_extract(sds_pin_mon_2, 0, 4);
    *tx_post = bdk_extract(sds_pin_mon_2, 4, 5);
    *tx_gain_bias = cfg_3.s.pcs_sds_tx_gain;
    *tx_vboost_unused = bdk_extract(sds_pin_mon_2, 10, 1);
    return 0;
}

/**
 * Some QLM speeds need to override the default tuning parameters
 *
 * @param node     Node to use in a Numa setup
 * @param qlm      QLM to configure
 * @param mode     Desired mode
 * @param baud_mhz Desired speed
 */
void __bdk_qlm_tune_cn8xxx(bdk_node_t node, int qlm, bdk_qlm_modes_t mode, int baud_mhz)
{
    /* Note: This function is not called for CCPI. For CCPI tuning, see
       bdk-init-nz-node.c */
    /* Tuning parameters override the KR training. Don't apply them for KR links */
    switch (mode)
    {
        case BDK_QLM_MODE_10G_KR:
        case BDK_QLM_MODE_40G_KR4:
            return;
        case BDK_QLM_MODE_PCIE_X1:
        case BDK_QLM_MODE_PCIE_X2:
        case BDK_QLM_MODE_PCIE_X4:
        case BDK_QLM_MODE_PCIE_X8:
            /* Don't tune PCIe Gen3 as it has its own builtin, similar to KR */
            if (baud_mhz > 5000)
                return;
            break;
        default:
            break;
    }

    /* We're apply tuning for all lanes on this QLM */
    int num_lanes = bdk_qlm_get_lanes(node, qlm);
    for (int lane = 0; lane < num_lanes; lane++)
    {
        /* TX Swing: First read any board specific setting from the environment */
        int swing = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_SWING, node, qlm, lane);
        /* If no setting, use hard coded generic defaults */
        if (swing == -1)
        {
            if (baud_mhz == 6250)
            {
                /* Email from Brendan Metzner about RXAUI around 2/7/2016 */
                swing = 0x12;
            }
            else if (baud_mhz == 10312)
            {
                /* From lab measurements of EBB8800 at 10.3125G */
                swing = 0xd;
            }
        }

        /* TX Premptap: First read any board specific setting from the environment */
        int premptap = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_PREMPTAP, node, qlm, lane);
        /* If no setting, use hard coded generic defaults */
        if (premptap == -1)
        {
            if (baud_mhz == 6250)
            {
                /* From lab measurements of EBB8800 at 6.25G */
                premptap = 0xa0;
            }
            else if (baud_mhz == 10312)
            {
                /* From lab measurements of EBB8800 at 10.3125G */
                premptap = 0xd0;
            }
        }

        int tx_pre = (premptap == -1) ? -1 : premptap & 0xf;
        int tx_post = (premptap == -1) ? -1 : premptap >> 4;
        int gain = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_GAIN, node, qlm, lane);
        int vboost = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_VBOOST, node, qlm, lane);

        bdk_qlm_tune_lane_tx(node, qlm, lane, swing, tx_pre, tx_post, gain, vboost);

        /* Email from Brendan Metzner about RXAUI around 2/7/2016 suggested the
           following setting for RXAUI at 6.25G with both PHY or cable. I'm
           applying it to all lanes running at 6.25G */
        if (baud_mhz == 6250)
        {
            /* This is changing the Q/QB error sampler 0 threshold from 0xD
                to 0xF */
            BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_CFG_4(qlm, lane),
                c.s.cfg_rx_errdet_ctrl = 0xcf6f);
        }
    }
}

/**
 * Disables DFE for the specified QLM lane(s).
 * This function should only be called for low-loss channels.
 *
 * @param node   Node to configure
 * @param qlm    QLM to configure
 * @param lane   Lane to configure, or -1 for all lanes
 */
void __bdk_qlm_dfe_disable_cn8xxx(int node, int qlm, int lane)
{
    int num_lanes = bdk_qlm_get_lanes(node, qlm);
    int l;

    for (l = 0; l < num_lanes; l++) {
        if ((lane != -1) && (lane != l))
	    continue;
        /* 1. Write GSERX_LANEx_RX_LOOP_CTRL = 0x0270 (var "loop_ctrl" with bits 8 & 1 cleared).
         * bit<1> dfe_en_byp = 1'b0 */
        BDK_CSR_MODIFY(c, node,  BDK_GSERX_LANEX_RX_LOOP_CTRL(qlm, l),
            c.s.cfg_rx_lctrl = c.s.cfg_rx_lctrl & 0x3fd);

        /* 2. Write GSERX_LANEx_RX_VALBBD_CTRL_1 = 0x0000 (var "ctrl1" with all bits cleared)
         * bits<14:11> CFG_RX_DFE_C3_MVAL = 4'b0000
         * bit<10> CFG_RX_DFE_C3_MSGN = 1'b0
         * bits<9:6> CFG_RX_DFE_C2_MVAL = 4'b0000
         * bit<5> CFG_RX_DFE_C2_MSGN = 1'b0
         * bits<4:1> CFG_RX_DFE_C1_MVAL = 5'b0000
         * bits<0> CFG_RX_DFE_C1_MSGN = 1'b0 */
        BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_VALBBD_CTRL_1(qlm, l),
            c.s.dfe_c3_mval = 0;
            c.s.dfe_c3_msgn = 0;
            c.s.dfe_c2_mval = 0;
            c.s.dfe_c2_msgn = 0;
            c.s.dfe_c1_mval = 0;
            c.s.dfe_c1_msgn = 0);

        /* 3. Write GSERX_LANEx_RX_VALBBD_CTRL_0 = 0x2400 (var "ctrl0" with following bits set/cleared)
         * bits<11:10> CFG_RX_DFE_GAIN = 0x1
         * bits<9:6> CFG_RX_DFE_C5_MVAL = 4'b0000
         * bit<5> CFG_RX_DFE_C5_MSGN = 1'b0
         * bits<4:1> CFG_RX_DFE_C4_MVAL = 4'b0000
         * bit<0> CFG_RX_DFE_C4_MSGN = 1'b0 */
        BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_VALBBD_CTRL_0(qlm, l),
            c.s.dfe_gain = 0x1;
            c.s.dfe_c5_mval = 0;
            c.s.dfe_c5_msgn = 0;
            c.s.dfe_c4_mval = 0;
            c.s.dfe_c4_msgn = 0);

        /* 4. Write GSER(0..13)_LANE(0..3)_RX_VALBBD_CTRL_2 = 0x003F  //enable DFE tap overrides
         * bit<5> dfe_ovrd_en = 1
         * bit<4> dfe_c5_ovrd_val = 1
         * bit<3> dfe_c4_ovrd_val = 1
         * bit<2> dfe_c3_ovrd_val = 1
         * bit<1> dfe_c2_ovrd_val = 1
         * bit<0> dfe_c1_ovrd_val = 1
         */
        BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_VALBBD_CTRL_2(qlm, l),
            c.s.dfe_ovrd_en = 0x1;
            c.s.dfe_c5_ovrd_val = 0x1;
            c.s.dfe_c4_ovrd_val = 0x1;
            c.s.dfe_c3_ovrd_val = 0x1;
            c.s.dfe_c2_ovrd_val = 0x1;
            c.s.dfe_c1_ovrd_val = 0x1);

    }
}

/**
 * Check if a specific lane is using KR training. This is used by low level GSER
 * code to remember which QLMs and lanes need to support KR training for BGX. The
 * hardware doesn't have a bit set aside to record this, so we repurpose the
 * register GSERX_SCRATCH.
 *
 * @param node   Node to check
 * @param qlm    QLM to check
 * @param lane   Lane to check
 *
 * @return True if this lane uses KR with BGX, false otherwise
 */
bool __bdk_qlm_is_lane_kr_cn8xxx(bdk_node_t node, int qlm, int lane)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        uint64_t mask = BDK_CSR_READ(node, BDK_GSERX_SCRATCH(qlm));
        return 1 & (mask >> lane);
    }
    else
    {
        bdk_error("N%d.QLM%d: Function %s not implemented\n", node, qlm, __FUNCTION__);
        return 0;
    }
}

/**
 * Set if a specific lane is using KR training. This is used by low level GSER
 * code to remember which QLMs and lanes need to support KR training for BGX. The
 * hardware doesn't have a bit set aside to record this, so we repurpose the
 * register GSERX_SCRATCH.
 *
 * @param node   Node to set
 * @param qlm    QLM to set
 * @param lane   Lane to set
 * @param is_kr  KR (true) or XFI/XLAUI (false)
 */
void __bdk_qlm_set_lane_kr_cn8xxx(bdk_node_t node, int qlm, int lane, bool is_kr)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        uint64_t mask = BDK_CSR_READ(node, BDK_GSERX_SCRATCH(qlm));
        if (is_kr)
            mask |= 1 << lane;
        else
            mask &= ~(1 << lane);
        BDK_CSR_WRITE(node, BDK_GSERX_SCRATCH(qlm), mask);
    }
    else
    {
        bdk_error("N%d.QLM%d: Function %s not implemented\n", node, qlm, __FUNCTION__);
    }
}

