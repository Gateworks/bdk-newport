/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gser.h"

/**
 * (GSER-27140) SERDES has temperature drift sensitivity in the RX EQ<p>
 * SERDES temperature drift sensitivity in receiver. Issues have
 * been found with the Bit Error Rate (BER) reliability of
 * 10GBASE-KR links over the commercial temperature range (0 to 100C),
 * especially when subjected to rapid thermal ramp stress testing.
 * (See HRM for corresponding case temperature requirements for each speed grade.)<p>
 * Applies to:
 *     CN88XX pass 1.x
 *     CN88XX pass 2.x
 *     CN83XX pass 1.x
 *     CN81XX pass 1.x
 * Fixed in hardware:
 *     TBD<p>
 * Only applies to QLMs running 10G
 *
 * @param node     Note to apply errata fix to
 * @param qlm      QLM to apply errata fix to
 * @param baud_mhz QLM baud rate in Mhz
 * @param channel_loss
 *                 Insertion loss at Nyquist rate (e.g. 5.125Ghz for XFI/XLAUI) in dB
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_errata_gser_27140(bdk_node_t node, int qlm, int baud_mhz, int channel_loss)
{
    if (baud_mhz != 10312)
        return 0;

    /* A channel loss of -1 means the loss is unknown. A short channel is
       considered to have loss between 0 and 10 dB */
    bool short_channel = (channel_loss >= 0) && (channel_loss <= 10);

    /* I. For each GSER QLM: */
    /* Workaround GSER-27140: */
    /* (1) GSER-26150 = Applied by the caller */
    /* (2) Write GSER()_LANE_VMA_FINE_CTRL_0[RX_SDLL_IQ_MAX_FINE] = 0xE */
    /* (3) Write GSER()_LANE_VMA_FINE_CTRL_0[RX_SDLL_IQ_MIN_FINE] = 0x8 */
    /* (4) Write GSER()_LANE_VMA_FINE_CTRL_0[RX_SDLL_IQ_STEP_FINE] = 0x2 */
    /* (5) Write GSER()_LANE_VMA_FINE_CTRL_0[VMA_WINDOW_WAIT_FINE] = 0x5 */
    /* (6) Write GSER()_LANE_VMA_FINE_CTRL_0[LMS_WAIT_TIME_FINE] = 0x5 */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANE_VMA_FINE_CTRL_0(qlm),
        c.s.rx_sdll_iq_max_fine = 0xE;
        c.s.rx_sdll_iq_min_fine = 0x8;
        c.s.rx_sdll_iq_step_fine = 0x2;
        c.s.vma_window_wait_fine = 0x5;
        c.s.lms_wait_time_fine = 0x5);
    /* (7) Write GSER()_LANE_VMA_FINE_CTRL_2[RX_PRECTLE_GAIN_MAX_FINE] = 0xB */
    /* (8) Write GSER()_LANE_VMA_FINE_CTRL_2[RX_PRECTLE_GAIN_MIN_FINE] = 0x6(long) or 0x0(short) */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANE_VMA_FINE_CTRL_2(qlm),
        c.s.rx_prectle_gain_max_fine = 0xB;
        c.s.rx_prectle_gain_min_fine = short_channel ? 0x0 : 0x6);
    /* (9) Write GSER()_RX_TXDIR_CTRL_0[RX_BOOST_LO_THRES] = 0x4 */
    /* (10) Write GSER()_RX_TXDIR_CTRL_0[RX_BOOST_HI_THRES] = 0xB */
    /* (11) Write GSER()_RX_TXDIR_CTRL_0[RX_BOOST_HI_VAL] = 0xF */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_RX_TXDIR_CTRL_0(qlm),
        c.s.rx_boost_lo_thrs = 0x4;
        c.s.rx_boost_hi_thrs = 0xB;
        c.s.rx_boost_hi_val = 0xF);
    /* (12) Write GSER()_RX_TXDIR_CTRL_1[RX_TAP1_LO_THRS] = 0x8 */
    /* (13) Write GSER()_RX_TXDIR_CTRL_1[RX_TAP1_HI_THRS] = 0x17 */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_RX_TXDIR_CTRL_1(qlm),
        c.s.rx_tap1_lo_thrs = 0x8;
        c.s.rx_tap1_hi_thrs = 0x17);

    /* (14) Write GSER()_EQ_WAIT_TIME[RXEQ_WAIT_CNT] = 0x6 */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_EQ_WAIT_TIME(qlm),
        c.s.rxeq_wait_cnt = 0x6);
    /* (15) Write GSER()_RX_TXDIR_CTRL_2[RX_PRECORR_HI_THRS] = 0xC0 */
    /* (16) Write GSER()_RX_TXDIR_CTRL_2[RX_PRECORR_LO_THRS] = 0x40 */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_RX_TXDIR_CTRL_2(qlm),
        c.s.rx_precorr_hi_thrs = 0xc0;
        c.s.rx_precorr_lo_thrs = 0x40);

    /* We can't call the normal bdk-qlm function as it uses pointers that
       don't work when running in secondary nodes before CCPI is up */
    int num_lanes = 4;
    if (bdk_is_model(OCTEONTX_CN81XX) || (bdk_is_model(OCTEONTX_CN83XX) && (qlm >= 4)))
        num_lanes = 2;

    /* II. For each GSER QLM SerDes lane: */
    /* Establish typical values, which are already reset values in pass 2: */
    for (int lane = 0; lane < num_lanes; lane++)
    {
        /* (17) For each GSER lane in the 10GBASE-KR link: */
        /*    (a) Write GSER()_LANE()_RX_VALBBD_CTRL_0[AGC_GAIN] = 0x3 */
        /*    (b) Write GSER()_LANE()_RX_VALBBD_CTRL_0[DFE_GAIN] = 0x2 */
        BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_RX_VALBBD_CTRL_0(qlm, lane),
            c.s.agc_gain = 0x3;
            c.s.dfe_gain = 0x2);
    }

    /* III. The GSER QLM SerDes Lanes are now ready. */
    return 0;
}
