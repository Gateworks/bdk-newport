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
 * A number of the GSERN settings are encoded in a bitfield where bit 0 is Gen1
 * and bit 3 is Gen4. This function looks up the bit values for a setting and sets
 * the correct mode mask bits.
 *
 * @param setting_array
 *               Array from cavm-gsern-settings.h
 *
 * @return Mask for Gen* modes
 */
static int build_mode_mask(const int setting_array[])
{
    int mask = setting_array[GSERN_PCIE_02500000000];   /* Gen 1 */
    mask |= setting_array[GSERN_PCIE_05000000000] << 1; /* Gen 2 */
    mask |= setting_array[GSERN_PCIE_08000000000] << 2; /* Gen 3 */
    mask |= setting_array[GSERN_PCIE_16000000000] << 3; /* Gen 4 */
    return mask;
}

int cavm_gsern_init_pcie(bdk_node_t node, int qlm, bool is_first_qlm, enum cavm_gsern_flags flags, enum gsern_lane_modes mode)
{
    const int BROADCAST = 4; /* Broadcast across all lanes */
    const int num_lanes = bdk_qlm_get_lanes(node, qlm);
    bool use_dual = (flags & CAVM_GSERN_FLAGS_DUAL) != 0;
    bool use_quad = (flags & CAVM_GSERN_FLAGS_QUAD) != 0;

    /* adpt_wait is tha max of a number of other values plus 16 */
    int adpt_wait = MAX(gsern_lane_vga_timer_max, gsern_lane_dfe_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_ctlez_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_ctle_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_ctlelte_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_afeos_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_blwc_timer_max);
    adpt_wait = MAX(adpt_wait, gsern_lane_prevga_gn_timer_max);
    adpt_wait += 16;
    if (adpt_wait > 0x3ffff)
        adpt_wait = 0x3ffff;

    /* Calculate the total lanes in use for PCIe. Will 2, 4, 8, or 16 */
    int total_lanes = num_lanes;
    if (use_quad)
        total_lanes *= 4;
    else if (use_dual)
        total_lanes *= 2;

    /* Figure out the mask of the QLM/DLMs used for this PCIe */
    int txdivrst_algn_qlm_mask = 0;
    if (use_quad)
        txdivrst_algn_qlm_mask = 0xf;
    else if (use_dual)
    {
        if (qlm == 2 || qlm == 3)
            txdivrst_algn_qlm_mask = 0xc;
        else
            txdivrst_algn_qlm_mask = 0x3;
    }

    /* The lane masks used for synchronization. Currently the BDK
       doesn't allow widths less than the QLM/DLM */
    int txdivrst_algn_lane_mask = bdk_build_mask(num_lanes);

    int txdivclk_mux_sel_ovrride = 0; /* 1 lane */
    switch (total_lanes)
    {
        case 2:
            txdivclk_mux_sel_ovrride = 1;
            break;
        case 4:
            txdivclk_mux_sel_ovrride = 2;
            break;
        case 8:
            txdivclk_mux_sel_ovrride = 3;
            break;
        case 16:
            txdivclk_mux_sel_ovrride = 4;
            break;
    }

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PLL_1_BCFG(qlm, BROADCAST),
        c.s.cal_cp_mult = 1;
        c.s.cp = 0xc;
        c.s.cp_overide = 0;
        c.s.band_ppm = 2;
        c.s.band = 0x10;
        c.s.band_limits = 0;
        c.s.band_overide = 0;
        c.s.bg_div16 = 0;
        c.s.bg_clk_en = 0;
        c.s.dither_en = 1;
        c.s.cal_sel = 0;
        c.s.vco_sel = 0;
        c.s.sdm_en = 0;
        c.s.post_div = 3;
        c.s.div_n = 0x64;
        c.s.div_f = 0);
    /* Need to add more configuration options for the GSERNX_LANEX_RSTCLKMSK_BCFG  */
    /* txdivrst_algn_qlm_mask and txdivrst_algn_lane_mask when PEM is configured */
    /* for x8 with two QLMs, x4 with one QLM or two DLMs, and x2 with one DLM */
    /* the Txdivclk alignment by QLM and DLM will change */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RSTCLKMSK_BCFG(qlm, BROADCAST),
        c.s.txdivrst_algn_qlm_mask = txdivrst_algn_qlm_mask;
        c.s.txdivrst_algn_lane_mask = txdivrst_algn_lane_mask;
        c.s.txdivrst_algn_wait_en = 0;
        c.s.txdivrst_algn_wait = 0xff);
    /* Need to add more configuration options for the GSERNX_LANEX_SRCMX_BCFG  */
    /* txdivclk_mux_sel_ovrride when PEM is configured */
    /* for x8 with two QLMs, x4 with one QLM or two DLMs, and x2 with one DLM */
    /* the Txdivclk alignment by QLM and DLM will change */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, BROADCAST),
        c.s.en_hldcdrfsm_on_idle = 1;
        c.s.en_pauseadpt_on_idle = 1;
        c.s.trn_sclk_cgt_on = 0;
        c.s.trn_tx_cgt_on = 0;
        c.s.trn_rx_cgt_on = 0;
        c.s.ocx_tx_cgt_on = 0;
        c.s.ocx_rx_cgt_on = 0;
        c.s.sata_tx_cgt_on = 0;
        c.s.sata_rx_cgt_on = 0;
        c.s.pcie_tx_cgt_on = 0;
        c.s.pcie_rx_cgt_on = 0;
        c.s.pat_tx_cgt_on = 0;
        c.s.pat_rx_cgt_on = 0;
        c.s.cgx_tx_cgt_on = 0;
        c.s.cgx_rx_cgt_on = 0;
        c.s.txdivclk_mux_sel_ovrride_en = 1;
        c.s.txdivclk_mux_sel_ovrride = txdivclk_mux_sel_ovrride;
        c.s.tx_ctrl_sel = 1;
        c.s.tx_data_sel = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_LT_BCFG(qlm, BROADCAST),
        c.s.inj_err_cnt_rst_n = 0;
        c.s.inj_err_cnt_en = 0;
        c.s.inj_err_cnt_len = 0;
        c.s.inj_err_burst_en = 0;
        c.s.inj_err_burst_len = 0;
        c.s.pat_dp_width = 3;
        c.s.prbs_dp_width = 3;
        c.s.rx_dp_width = 3;
        c.s.tx_dp_width = 3;
        c.s.core_loopback_mode = 0;
        c.s.sloop_mode = 0;
        c.s.bitstuff_rx_drop_even = 0;
        c.s.bitstuff_rx_en = 0;
        c.s.inv_rx_polarity = 0;
        c.s.reverse_rx_bit_order = 1;
        c.s.fifo_algn_qlm_mask_rsvd = 0;
        c.s.fifo_algn_lane_mask_rsvd = 0;
        c.s.fifo_bypass_en = 0;
        c.s.tx_fifo_pop_start_addr = 6;
        c.s.fifo_rst_n = 1;
        c.s.bitstuff_tx_en = 0;
        c.s.inv_tx_polarity = 0;
        c.s.reverse_tx_bit_order = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_BIAS_BCFG(qlm),
        c.s.dac1 = (cavm_gsern_voltage > 950) ? 0xf : 0x8;
        c.s.dac0 = 8;
        c.s.bias = 1;
        c.s.bypass = 0;
        c.s.bias_pwdn = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_OS_5_BCFG(qlm, BROADCAST),
        c.s.run_eye_oscal = gsern_lane_run_eye_oscal;
        c.s.c1_e_adjust = 0;
        c.s.c1_i_adjust = 0;
        c.s.c1_q_adjust = gsern_lane_c1_q_adjust[mode];
        c.s.offset_comp_en = 1;
        c.s.binsrch_margin = 5;
        c.s.binsrch_wait = gsern_lane_binsrch_wait[mode];
        c.s.binsrch_acclen = 3;
        c.s.settle_wait = gsern_lane_settle_wait;
        c.s.ir_trim_early_iter_max = gsern_lane_ir_trim_early_iter_max;
        c.s.ir_trim_comp_en = gsern_lane_ir_trim_comp_en;
        c.s.ir_trim_trigger = 0;
        c.s.idle_offset_trigger = 0;
        c.s.afe_offset_trigger = 0;
        c.s.dfe_offset_trigger = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_ST_BCFG(qlm, BROADCAST),
        c.s.rxcdrfsmi = gsern_lane_rxcdrfsmi;
        c.s.rx_dcc_iboost = gsern_lane_rx_dcc_iboost[mode];
        c.s.rx_dcc_lowf = gsern_lane_rx_dcc_lowf[mode];
        c.s.bstuff = 0;
        c.s.rx_idle_lowf = 1;
        c.s.idle_os_bitlen = 0;
        c.s.idle_os_ovrd_en = 0;
        c.s.refset = 8;
        c.s.idle_os_ovrd = 0;
        c.s.en_idle_cal = 1;
        c.s.rxelecidle = 0;
        c.s.rxcdrhold = 0;
        c.s.rxcdrramp = 0;
        c.s.en_sh_lb = 0;
        c.s.erc = gsern_lane_erc[mode];
        c.s.term = gsern_lane_term[mode];
        c.s.en_rt85 = 0;
        c.s.en_lb = 0;
        c.s.en_rterm = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_IDLE_CAL_CFG(qlm, BROADCAST),
        c.s.idle_recal_disable = 0;
        c.s.idle_recal_oob_mode_disable = 0;
        c.s.idle_oob_adder_counter_clear = 0;
        c.s.max_oob_adder_count = 4;
        c.s.oob_delay_adder_count = 0x10000);

    /* Idle Detect Threshold
        Set GEN1,GEN2,GEN3,GEN4
        This change Aligns With Joe Vulih recommendation to
        Use a value of '4' for REFSET.  The value of 8
        Was causing issues with EP mode with adaptation failures
        This value is also same as ethernet */

    /* Use the value from device tree to allow changes across platforms */
    /* The same value is used for GEN1,GEN2,GEN3 and GEN4 speeds */
    int serdes_recalibration_refset_pcie_value = bdk_config_get_int(BDK_CONFIG_PCIE_IDLE_REFSET_VALUE, BDK_NODE_0, qlm);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXIDL1A_BCFG(qlm, BROADCAST),
        c.s.refset = serdes_recalibration_refset_pcie_value);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXIDL2A_BCFG(qlm, BROADCAST),
        c.s.refset = serdes_recalibration_refset_pcie_value);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXIDL3A_BCFG(qlm, BROADCAST),
        c.s.refset = serdes_recalibration_refset_pcie_value);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXIDL4A_BCFG(qlm, BROADCAST),
        c.s.refset = serdes_recalibration_refset_pcie_value);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_CDRFSM_BCFG(qlm, BROADCAST),
        c.s.voter_sp_mask = gsern_lane_voter_sp_mask[mode];
        c.s.rst_n = 1;
        c.s.clk_sel = 2;
        c.s.trunc = 3;
        c.s.limit = 0;
        c.s.eoffs = gsern_lane_eoffs[mode];
        c.s.qoffs = gsern_lane_qoffs[mode];
        c.s.inc2 = gsern_lane_inc2[mode];
        c.s.inc1 = gsern_lane_inc1[mode]);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, BROADCAST),
        c.s.perst_n_ovrd = 1;
        c.s.perst_n_ovrd_en = 0;
        c.s.domain_rst_en = 1; /* Set for RC */
        c.s.rx_go2deep_idle = 0;
        c.s.rx_pd_qac_q = gsern_lane_rx_pd_qac_q;
        c.s.rx_pd_qac_e = gsern_lane_rx_pd_qac_e;
        c.s.rx_pd_idle = 1;
        c.s.rx_rst_deser = 0;
        c.s.rx_rst_dcc_q = 0;
        c.s.rx_rst_dcc_i = 0;
        c.s.rx_rst_dcc_e = 0;
        c.s.idle = 0;
        c.s.rx_rst_qac_q = 0;
        c.s.rx_rst_qac_e = 0;
        c.s.rx_rst_blwc = 0;
        c.s.rx_rst_cdrfsm = 0;
        c.s.rx_rst_voter = 0;
        c.s.rx_rst_div_e = 0;
        c.s.rx_rst_div = 0;
        c.s.rx_rst_interp_q = 0;
        c.s.rx_rst_interp_i = 0;
        c.s.rx_rst_interp_e = 0;
        c.s.rx_pd_interp_q = 1;
        c.s.rx_pd_interp_i = 1;
        c.s.rx_pd_interp_e = 1;
        c.s.rx_pd_dfe_x = gsern_lane_rx_pd_dfe_x;
        c.s.rx_pd_dfe_q = gsern_lane_rx_pd_dfe_q;
        c.s.rx_pd_dfe_i = gsern_lane_rx_pd_dfe_i;
        c.s.rx_pd_dfe_e = gsern_lane_rx_pd_dfe_e;
        c.s.rx_pd_dcc_q = 1;
        c.s.rx_pd_dcc_i = 1;
        c.s.rx_pd_dcc_e = 1;
        c.s.rx_pd_biasdac = 1;
        c.s.rx_pd_afe = 1;
        c.s.rx_en_cdrfsm = 0;
        c.s.pll_go2deep_idle = 0;
        c.s.lock_ppm = 0;
        c.s.lock_wait = 0;
        c.s.lock_check = 0;
        c.s.vco_cal_reset = 0;
        c.s.fracn_reset = 0;
        c.s.ssc_reset = 0;
        c.s.post_div_reset = 0;
        c.s.reset = 0;
        c.s.cal_en = 0;
        c.s.pwdn = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_4_BCFG(qlm, BROADCAST),
        c.s.edgesel_even_ovrd_en = gsern_lane_edgesel_even_ovrd_en;
        c.s.edgesel_even_ovrd = gsern_lane_edgesel_even_ovrd;
        c.s.edgesel_odd_ovrd_en = gsern_lane_edgesel_odd_ovrd_en;
        c.s.edgesel_odd_ovrd = gsern_lane_edgesel_odd_ovrd;
        c.s.en_os_afe_ovrd_en = 0;
        c.s.en_os_afe_ovrd = 0;
        c.s.os_afe_odd_ovrd_en = gsern_lane_os_afe_odd_ovrd_en;
        c.s.os_afe_odd_ovrd = gsern_lane_os_afe_odd_ovrd;
        c.s.os_afe_even_ovrd_en = gsern_lane_os_afe_even_ovrd_en[mode];
        c.s.os_afe_even_ovrd = gsern_lane_os_afe_even_ovrd;
        c.s.ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[mode];
        c.s.ctle_lte_gain_ovrd_en = gsern_lane_ctle_lte_gain_ovrd_en;
        c.s.ctle_lte_gain_ovrd = gsern_lane_ctle_lte_gain_ovrd[mode];
        c.s.ctle_zero_ovrd_en = gsern_lane_ctle_zero_ovrd_en;
        c.s.ctle_zero_ovrd = gsern_lane_ctle_zero_ovrd[mode];
        c.s.ctle_gain_ovrd_en = gsern_lane_ctle_gain_ovrd_en[mode];
        c.s.ctle_gain_ovrd = gsern_lane_ctle_gain_ovrd[mode];
        c.s.vga_gain_ovrd_en = gsern_lane_vga_gain_ovrd_en[mode];
        c.s.vga_gain_ovrd = gsern_lane_vga_gain_ovrd[mode]);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_ST_BCFG(qlm, BROADCAST),
        c.s.rxcdrfsmi = gsern_lane_rxcdrfsmi;
        c.s.rx_dcc_iboost = gsern_lane_rx_dcc_iboost[mode];
        c.s.rx_dcc_lowf = gsern_lane_rx_dcc_lowf[mode];
        c.s.bstuff = 0;
        c.s.rx_idle_lowf = 1;
        c.s.idle_os_bitlen = 0;
        c.s.idle_os_ovrd_en = 0;
        c.s.refset = 8;
        c.s.idle_os_ovrd = 0;
        c.s.en_idle_cal = 1;
        c.s.rxelecidle = 0;
        c.s.rxcdrhold = 0;
        c.s.rxcdrramp = 0;
        c.s.en_sh_lb = 0;
        c.s.erc = gsern_lane_erc[mode];
        c.s.term = gsern_lane_term[mode];
        c.s.en_rt85 = 0;
        c.s.en_lb = 0;
        c.s.en_rterm = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_8_BCFG(qlm, BROADCAST),
        c.s.dfe_edgemode_ovrd = 0;
        c.s.dfe_edgemode_ovrd_en = 0;
        c.s.subrate_scale = 7;
        c.s.subrate_init = gsern_lane_subrate_init[mode];
        c.s.subrate_final = gsern_lane_subrate_final[mode]);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_13_BCFG(qlm, BROADCAST),
        c.s.afeos_subrate_scale = 7;
        c.s.afeos_subrate_init = gsern_lane_afeos_subrate_init[mode];
        c.s.afeos_subrate_final = gsern_lane_afeos_subrate_final[mode]);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_20_BCFG(qlm, BROADCAST),
        c.s.blwc_subrate_scale = 7;
        c.s.blwc_subrate_init = gsern_lane_blwc_subrate_init;
        c.s.blwc_subrate_final = gsern_lane_blwc_subrate_final);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_21_BCFG(qlm, BROADCAST),
        c.s.prevga_gn_subrate_now_ovrd_en = 0;
        c.s.prevga_gn_subrate_now_ovrd = 0;
        c.s.prevga_gn_subrate_scale = 7;
        c.s.prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[mode];
        c.s.prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[mode]);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_9_BCFG(qlm, BROADCAST),
        c.s.ctlelte_deadband = gsern_lane_ctlelte_deadband;
        c.s.ctlez_deadband = gsern_lane_ctlez_deadband;
        c.s.ctle_deadband = gsern_lane_ctle_deadband;
        c.s.dfe_deadband = gsern_lane_dfe_deadband;
        c.s.vga_deadband = gsern_lane_vga_deadband);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_19_BCFG(qlm, BROADCAST),
        c.s.blwc_leak_sgn = gsern_lane_blwc_leak_sgn;
        c.s.blwc_updn_len = gsern_lane_blwc_updn_len;
        c.s.blwc_deadband = gsern_lane_blwc_deadband;
        c.s.blwc_deadband_inc = 0;
        c.s.blwc_leak = gsern_lane_blwc_leak;
        c.s.blwc_mu = gsern_lane_blwc_mu;
        c.s.blwc_timer_max = gsern_lane_blwc_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_23_BCFG(qlm, BROADCAST),
        c.s.prevga_gn_leak_sgn = gsern_lane_prevga_gn_leak_sgn;
        c.s.prevga_gn_deadband = gsern_lane_prevga_gn_deadband;
        c.s.prevga_gn_deadband_inc = 0;
        c.s.prevga_gn_leak = gsern_lane_prevga_gn_leak;
        c.s.prevga_gn_mu = gsern_lane_prevga_gn_mu;
        c.s.prevga_gn_timer_max = gsern_lane_prevga_gn_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_12_BCFG(qlm, BROADCAST),
        c.s.afeos_leak_sgn = gsern_lane_afeos_leak_sgn;
        c.s.afeos_deadband = gsern_lane_afeos_deadband;
        c.s.afeos_deadband_inc = 0;
        c.s.afeos_leak = gsern_lane_afeos_leak;
        c.s.afeos_mu = gsern_lane_afeos_mu;
        c.s.afeos_timer_max = gsern_lane_afeos_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_14_BCFG(qlm, BROADCAST),
        c.s.c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[mode];
        c.s.c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[mode];
        c.s.dfe_c1_deadband = gsern_lane_dfe_c1_deadband;
        c.s.dfe_c1_deadband_inc = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST_CNT4_BCFG(qlm, BROADCAST),
        c.s.svc_clk_freq = 0;
        c.s.blwc_reset_wait = 0xf;
        c.s.dfe_afe_oscal_wait = gsern_lane_dfe_afe_oscal_wait);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_6_BCFG(qlm, BROADCAST),
        c.s.ctlez_leak = gsern_lane_ctlez_leak;
        c.s.ctlez_mu = gsern_lane_ctlez_mu;
        c.s.ctlez_timer_max = gsern_lane_ctlez_timer_max;
        c.s.ctle_leak = gsern_lane_ctle_leak;
        c.s.ctle_mu = gsern_lane_ctle_mu;
        c.s.ctle_timer_max = gsern_lane_ctle_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_6A_BCFG(qlm, BROADCAST),
        c.s.ctlelte_leak_sgn = gsern_lane_ctlelte_leak_sgn;
        c.s.ctlelte_leak = gsern_lane_ctlelte_leak;
        c.s.ctlelte_mu = gsern_lane_ctlelte_mu;
        c.s.ctlelte_timer_max = gsern_lane_ctlelte_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_5_BCFG(qlm, BROADCAST),
        c.s.ctle_leak_sgn = gsern_lane_ctle_leak_sgn;
        c.s.ctlez_leak_sgn = gsern_lane_ctlez_leak_sgn;
        c.s.dfe_c1_leak_sgn = gsern_lane_dfe_c1_leak_sgn;
        c.s.vga_leak_sgn = gsern_lane_vga_leak_sgn;
        c.s.dfe_c1_leak = gsern_lane_dfe_c1_leak;
        c.s.dfe_c1_mu = gsern_lane_dfe_c1_mu;
        c.s.vga_leak = gsern_lane_vga_leak;
        c.s.vga_mu = gsern_lane_vga_mu;
        c.s.vga_timer_max = gsern_lane_vga_timer_max;
        c.s.cont_dfe_leak_en = 0;
        c.s.dfe_leak_sgn = gsern_lane_dfe_leak_sgn;
        c.s.dfe_leak = gsern_lane_dfe_leak;
        c.s.dfe_mu = gsern_lane_dfe_mu;
        c.s.dfe_timer_max = gsern_lane_dfe_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_1_BCFG(qlm, BROADCAST),
        c.s.prevga_gn_ovrd_en = gsern_lane_prevga_gn_ovrd_en[mode];
        c.s.prevga_gn_ovrd = gsern_lane_prevga_gn_ovrd[mode];
        c.s.blwc_ovrd_en = gsern_lane_blwc_ovrd_en[mode];
        c.s.blwc_ovrd = gsern_lane_blwc_ovrd;
        c.s.c15_ovrd_en = gsern_lane_c15_ovrd_en;
        c.s.c15_ovrd = gsern_lane_c15_ovrd;
        c.s.c14_ovrd_en = gsern_lane_c14_ovrd_en;
        c.s.c14_ovrd = gsern_lane_c14_ovrd;
        c.s.c13_ovrd_en = gsern_lane_c13_ovrd_en;
        c.s.c13_ovrd = gsern_lane_c13_ovrd;
        c.s.c12_ovrd_en = gsern_lane_c12_ovrd_en;
        c.s.c12_ovrd = gsern_lane_c12_ovrd;
        c.s.c11_ovrd_en = gsern_lane_c11_ovrd_en;
        c.s.c11_ovrd = gsern_lane_c11_ovrd;
        c.s.c10_ovrd_en = gsern_lane_c10_ovrd_en;
        c.s.c10_ovrd = gsern_lane_c10_ovrd);

    int c1_limit_lo = bdk_is_model(OCTEONTX_CN96XX_PASS1_X) ?
        gsern_lane_c1_limit_lo_cn96xx[mode] :
        gsern_lane_c1_limit_lo_cnf95xx[mode];

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_15_BCFG(qlm, BROADCAST),
        c.s.c5_limit_hi = gsern_lane_c5_limit_hi[mode];
        c.s.c4_limit_hi = gsern_lane_c4_limit_hi[mode];
        c.s.c3_limit_hi = gsern_lane_c3_limit_hi[mode];
        c.s.c2_limit_hi = gsern_lane_c2_limit_hi[mode];
        c.s.c1_limit_hi = gsern_lane_c1_limit_hi[mode];
        c.s.c5_limit_lo = gsern_lane_c5_limit_lo[mode];
        c.s.c4_limit_lo = gsern_lane_c4_limit_lo[mode];
        c.s.c3_limit_lo = gsern_lane_c3_limit_lo[mode];
        c.s.c2_limit_lo = gsern_lane_c2_limit_lo[mode];
        c.s.c1_limit_lo = c1_limit_lo);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_OS_5_BCFG(qlm, BROADCAST),
        c.s.run_eye_oscal = gsern_lane_run_eye_oscal;
        c.s.c1_e_adjust = 0;
        c.s.c1_i_adjust = 0;
        c.s.c1_q_adjust = gsern_lane_c1_q_adjust[mode];
        c.s.offset_comp_en = 1;
        c.s.binsrch_margin = 5;
        c.s.binsrch_wait = gsern_lane_binsrch_wait[mode];
        c.s.binsrch_acclen = 3;
        c.s.settle_wait = gsern_lane_settle_wait;
        c.s.ir_trim_early_iter_max = gsern_lane_ir_trim_early_iter_max;
        c.s.ir_trim_comp_en = gsern_lane_ir_trim_comp_en;
        c.s.ir_trim_trigger = 0;
        c.s.idle_offset_trigger = 0;
        c.s.afe_offset_trigger = 0;
        c.s.dfe_offset_trigger = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, BROADCAST),
        c.s.do_prevga_gn_final = gsern_lane_do_prevga_gn_final;
        c.s.do_blwc_final = gsern_lane_do_blwc_final[mode];
        c.s.do_afeos_final = gsern_lane_do_afeos_final[mode];
        c.s.do_ctlelte_final = gsern_lane_do_ctlelte_final;
        c.s.do_ctlez_final = gsern_lane_do_ctlez_final;
        c.s.do_ctle_final = gsern_lane_do_ctle_final;
        c.s.adpt_trigger_wait = 0xf;
        c.s.adpt_wait = adpt_wait;
        c.s.do_dfe_final = gsern_lane_do_dfe_final[mode];
        c.s.do_vga_final = gsern_lane_do_vga_final[mode];
        c.s.do_prevga_gn_adpt = gsern_lane_do_prevga_gn_adpt[mode];
        c.s.do_blwc_adpt = gsern_lane_do_blwc_adpt[mode];
        c.s.do_afeos_adpt = gsern_lane_do_afeos_adpt[mode];
        c.s.do_ctlelte_adpt = gsern_lane_do_ctlelte_adpt[mode];
        c.s.do_ctlez_adpt = gsern_lane_do_ctlez_adpt[mode];
        c.s.do_ctle_adpt = gsern_lane_do_ctle_adpt[mode];
        c.s.do_dfe_adpt = gsern_lane_do_dfe_adpt[mode];
        c.s.do_vga_adpt = gsern_lane_do_vga_adpt[mode];
        c.s.rst_adpt_rst_sm = 1;
        c.s.rst_eye_rst_sm = 0;
        c.s.ln_reset_use_eye = 0;
        c.s.rst_rx_rst_sm = 1;
        c.s.rst_tx_rst_sm = 1;
        c.s.rst_pll_rst_sm = 1;
        c.s.tx_dcc_iboost = gsern_lane_tx_dcc_iboost[mode];
        c.s.tx_go2deep_idle = 0;
        c.s.tx_dcc_lowf = gsern_lane_tx_dcc_lowf[mode];
        c.s.tx_idle = 0;
        c.s.tx_div_rst = 0;
        c.s.tx_dcc_rst = 0;
        c.s.tx_enctl = 1;
        c.s.tx_cdrdiv3 = gsern_lane_tx_cdrdiv3[mode];
        c.s.tx_endiv5 = 1;
        c.s.tx_pdb = 0;
        c.s.tx_dcc_pdb = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_ITRIM_3_BCFG(qlm, BROADCAST),
        c.s.trim15_ovrd_en = gsern_lane_trim15_ovrd_en;
        c.s.trim14_ovrd_en = gsern_lane_trim14_ovrd_en;
        c.s.trim13_ovrd_en = gsern_lane_trim13_ovrd_en;
        c.s.trim12_ovrd_en = gsern_lane_trim12_ovrd_en;
        c.s.trim11_ovrd_en = gsern_lane_trim11_ovrd_en;
        c.s.trim10_ovrd_en = gsern_lane_trim10_ovrd_en;
        c.s.trim9_ovrd_en = gsern_lane_trim9_ovrd_en;
        c.s.trim8_ovrd_en = gsern_lane_trim8_ovrd_en;
        c.s.trim7_ovrd_en = gsern_lane_trim7_ovrd_en;
        c.s.trim6_ovrd_en = gsern_lane_trim6_ovrd_en;
        c.s.trim5_ovrd_en = gsern_lane_trim5_ovrd_en;
        c.s.trim4_ovrd_en = gsern_lane_trim4_ovrd_en;
        c.s.trim3_ovrd_en = gsern_lane_trim3_ovrd_en;
        c.s.trim2_ovrd_en = gsern_lane_trim2_ovrd_en;
        c.s.trim1_ovrd_en = gsern_lane_trim1_ovrd_en);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_ITRIM_4_BCFG(qlm, BROADCAST),
        c.s.trim31_ovrd_en = gsern_lane_trim31_ovrd_en;
        c.s.trim30_ovrd_en = gsern_lane_trim30_ovrd_en;
        c.s.trim29_ovrd_en = gsern_lane_trim29_ovrd_en;
        c.s.trim28_ovrd_en = gsern_lane_trim28_ovrd_en;
        c.s.trim27_ovrd_en = gsern_lane_trim27_ovrd_en;
        c.s.trim26_ovrd_en = gsern_lane_trim26_ovrd_en;
        c.s.trim25_ovrd_en = gsern_lane_trim25_ovrd_en;
        c.s.trim24_ovrd_en = gsern_lane_trim24_ovrd_en;
        c.s.trim23_ovrd_en = gsern_lane_trim23_ovrd_en;
        c.s.trim22_ovrd_en = gsern_lane_trim22_ovrd_en;
        c.s.trim21_ovrd_en = gsern_lane_trim21_ovrd_en;
        c.s.trim20_ovrd_en = gsern_lane_trim20_ovrd_en;
        c.s.trim19_ovrd_en = gsern_lane_trim19_ovrd_en;
        c.s.trim18_ovrd_en = gsern_lane_trim18_ovrd_en;
        c.s.trim17_ovrd_en = gsern_lane_trim17_ovrd_en;
        c.s.trim16_ovrd_en = gsern_lane_trim16_ovrd_en);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_ITRIM_5_BCFG(qlm, BROADCAST),
        c.s.trim45_ovrd_en = gsern_lane_trim45_ovrd_en;
        c.s.trim44_ovrd_en = gsern_lane_trim44_ovrd_en;
        c.s.trim43_ovrd_en = gsern_lane_trim43_ovrd_en;
        c.s.trim42_ovrd_en = gsern_lane_trim42_ovrd_en;
        c.s.trim41_ovrd_en = gsern_lane_trim41_ovrd_en;
        c.s.trim40_ovrd_en = gsern_lane_trim40_ovrd_en;
        c.s.trim39_ovrd_en = gsern_lane_trim39_ovrd_en;
        c.s.trim38_ovrd_en = gsern_lane_trim38_ovrd_en;
        c.s.trim37_ovrd_en = gsern_lane_trim37_ovrd_en;
        c.s.trim36_ovrd_en = gsern_lane_trim36_ovrd_en;
        c.s.trim35_ovrd_en = gsern_lane_trim35_ovrd_en;
        c.s.trim34_ovrd_en = gsern_lane_trim34_ovrd_en;
        c.s.trim33_ovrd_en = gsern_lane_trim33_ovrd_en;
        c.s.trim32_ovrd_en = gsern_lane_trim32_ovrd_en);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, BROADCAST),
        c.s.do_prevga_gn_final = gsern_lane_do_prevga_gn_final;
        c.s.do_blwc_final = gsern_lane_do_blwc_final[mode];
        c.s.do_afeos_final = gsern_lane_do_afeos_final[mode];
        c.s.do_ctlelte_final = gsern_lane_do_ctlelte_final;
        c.s.do_ctlez_final = gsern_lane_do_ctlez_final;
        c.s.do_ctle_final = gsern_lane_do_ctle_final;
        c.s.adpt_trigger_wait = 0xf;
        c.s.adpt_wait = adpt_wait;
        c.s.do_dfe_final = gsern_lane_do_dfe_final[mode];
        c.s.do_vga_final = gsern_lane_do_vga_final[mode];
        c.s.do_prevga_gn_adpt = gsern_lane_do_prevga_gn_adpt[mode];
        c.s.do_blwc_adpt = gsern_lane_do_blwc_adpt[mode];
        c.s.do_afeos_adpt = gsern_lane_do_afeos_adpt[mode];
        c.s.do_ctlelte_adpt = gsern_lane_do_ctlelte_adpt[mode];
        c.s.do_ctlez_adpt = gsern_lane_do_ctlez_adpt[mode];
        c.s.do_ctle_adpt = gsern_lane_do_ctle_adpt[mode];
        c.s.do_dfe_adpt = gsern_lane_do_dfe_adpt[mode];
        c.s.do_vga_adpt = gsern_lane_do_vga_adpt[mode];
        c.s.rst_adpt_rst_sm = 1;
        c.s.rst_eye_rst_sm = 0;
        c.s.ln_reset_use_eye = 0;
        c.s.rst_rx_rst_sm = 1;
        c.s.rst_tx_rst_sm = 1;
        c.s.rst_pll_rst_sm = 1;
        c.s.tx_dcc_iboost = gsern_lane_tx_dcc_iboost[mode];
        c.s.tx_go2deep_idle = 0;
        c.s.tx_dcc_lowf = gsern_lane_tx_dcc_lowf[mode];
        c.s.tx_idle = 0;
        c.s.tx_div_rst = 0;
        c.s.tx_dcc_rst = 0;
        c.s.tx_enctl = 1;
        c.s.tx_cdrdiv3 = gsern_lane_tx_cdrdiv3[mode];
        c.s.tx_endiv5 = 1;
        c.s.tx_pdb = 0;
        c.s.tx_dcc_pdb = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_10_BCFG(qlm, BROADCAST),
        c.s.ctlelte_deadband_inc = 0;
        c.s.ctlez_deadband_inc = 0;
        c.s.ctle_deadband_inc = 0;
        c.s.dfe_deadband_inc = 2;
        c.s.vga_deadband_inc = 2);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_1_BCFG(qlm, BROADCAST),
        c.s.tx_acjtag = 0;
        c.s.tx_dacj = 0;
        c.s.tx_enloop = 0;
        c.s.nvlink = 0;
        c.s.rx_mod4 = 0;
        c.s.rx_post4 = 0;
        c.s.mod4 = gsern_lane_mod4[mode];
        c.s.div20 = gsern_lane_div20[mode];
        c.s.tx_enfast = gsern_lane_tx_enfast[mode];
        c.s.tx_encm = gsern_lane_tx_encm);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, BROADCAST),
        c.s.perst_n_ovrd = 1;
        c.s.perst_n_ovrd_en = 0;
        c.s.domain_rst_en = 1; /* Set for RC */
        c.s.rx_go2deep_idle = 0;
        c.s.rx_pd_qac_q = gsern_lane_rx_pd_qac_q;
        c.s.rx_pd_qac_e = gsern_lane_rx_pd_qac_e;
        c.s.rx_pd_idle = 0;
        c.s.rx_rst_deser = 0;
        c.s.rx_rst_dcc_q = 0;
        c.s.rx_rst_dcc_i = 0;
        c.s.rx_rst_dcc_e = 0;
        c.s.idle = 0;
        c.s.rx_rst_qac_q = 0;
        c.s.rx_rst_qac_e = 0;
        c.s.rx_rst_blwc = 0;
        c.s.rx_rst_cdrfsm = 0;
        c.s.rx_rst_voter = 0;
        c.s.rx_rst_div_e = 0;
        c.s.rx_rst_div = 0;
        c.s.rx_rst_interp_q = 0;
        c.s.rx_rst_interp_i = 0;
        c.s.rx_rst_interp_e = 0;
        c.s.rx_pd_interp_q = 0;
        c.s.rx_pd_interp_i = 0;
        c.s.rx_pd_interp_e = 0;
        c.s.rx_pd_dfe_x = gsern_lane_rx_pd_dfe_x;
        c.s.rx_pd_dfe_q = gsern_lane_rx_pd_dfe_q;
        c.s.rx_pd_dfe_i = gsern_lane_rx_pd_dfe_i;
        c.s.rx_pd_dfe_e = gsern_lane_rx_pd_dfe_e;
        c.s.rx_pd_dcc_q = 0;
        c.s.rx_pd_dcc_i = 0;
        c.s.rx_pd_dcc_e = 0;
        c.s.rx_pd_biasdac = 0;
        c.s.rx_pd_afe = 0;
        c.s.rx_en_cdrfsm = 1;
        c.s.pll_go2deep_idle = 0;
        c.s.lock_ppm = 2;
        c.s.lock_wait = 2;
        c.s.lock_check = 0;
        c.s.vco_cal_reset = 0;
        c.s.fracn_reset = 0;
        c.s.ssc_reset = 0;
        c.s.post_div_reset = 0;
        c.s.reset = 0;
        c.s.cal_en = 1;
        c.s.pwdn = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, BROADCAST),
        c.s.do_prevga_gn_final = gsern_lane_do_prevga_gn_final;
        c.s.do_blwc_final = gsern_lane_do_blwc_final[mode];
        c.s.do_afeos_final = gsern_lane_do_afeos_final[mode];
        c.s.do_ctlelte_final = gsern_lane_do_ctlelte_final;
        c.s.do_ctlez_final = gsern_lane_do_ctlez_final;
        c.s.do_ctle_final = gsern_lane_do_ctle_final;
        c.s.adpt_trigger_wait = 0xf;
        c.s.adpt_wait = adpt_wait;
        c.s.do_dfe_final = gsern_lane_do_dfe_final[mode];
        c.s.do_vga_final = gsern_lane_do_vga_final[mode];
        c.s.do_prevga_gn_adpt = gsern_lane_do_prevga_gn_adpt[mode];
        c.s.do_blwc_adpt = gsern_lane_do_blwc_adpt[mode];
        c.s.do_afeos_adpt = gsern_lane_do_afeos_adpt[mode];
        c.s.do_ctlelte_adpt = gsern_lane_do_ctlelte_adpt[mode];
        c.s.do_ctlez_adpt = gsern_lane_do_ctlez_adpt[mode];
        c.s.do_ctle_adpt = gsern_lane_do_ctle_adpt[mode];
        c.s.do_dfe_adpt = gsern_lane_do_dfe_adpt[mode];
        c.s.do_vga_adpt = gsern_lane_do_vga_adpt[mode];
        c.s.rst_adpt_rst_sm = 0;
        c.s.rst_eye_rst_sm = 0;
        c.s.ln_reset_use_eye = 0;
        c.s.rst_rx_rst_sm = 0;
        c.s.rst_tx_rst_sm = 0;
        c.s.rst_pll_rst_sm = 0;
        c.s.tx_dcc_iboost = gsern_lane_tx_dcc_iboost[mode];
        c.s.tx_go2deep_idle = 0;
        c.s.tx_dcc_lowf = gsern_lane_tx_dcc_lowf[mode];
        c.s.tx_idle = 0;
        c.s.tx_div_rst = 0;
        c.s.tx_dcc_rst = 0;
        c.s.tx_enctl = 1;
        c.s.tx_cdrdiv3 = gsern_lane_tx_cdrdiv3[mode];
        c.s.tx_endiv5 = 1;
        c.s.tx_pdb = 1;
        c.s.tx_dcc_pdb = 1);
    /* Skip REFCLK setup as already done */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_PLL_2_BCFG(qlm),
        c.s.mio_refclk_en = 1;
        c.s.lock_check_cnt_ovrd_en = 0;
        c.s.lock_check_cnt_ovrd = 0;
        c.s.vcm_sel = 0;
        c.s.cp_boost = 0;
        c.s.ssc_sata_mode = 2;
        c.s.ssc_ppm = 0;
        c.s.pnr_refclk_en = 1;
        c.s.ssc_en = 0;
        c.s.ref_clk_bypass = 1;
        c.s.pfd_offset = 0;
        c.s.opamp = 0;
        c.s.res = 0;
        c.s.vco_bias = 4;
        c.s.cal_dac_low = 4;
        c.s.cal_dac_mid = 8;
        c.s.cal_dac_high = 0xc);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_PCS_BCFG(qlm, BROADCAST),
        c.s.do_afeos_adpt = build_mode_mask(gsern_lane_do_afeos_adpt);
        c.s.do_ctlelte_adpt = build_mode_mask(gsern_lane_do_ctlelte_adpt);
        c.s.do_ctlez_adpt = build_mode_mask(gsern_lane_do_ctlez_adpt);
        c.s.do_ctle_adpt = build_mode_mask(gsern_lane_do_ctle_adpt);
        c.s.do_dfe_adpt = build_mode_mask(gsern_lane_do_dfe_adpt);
        c.s.do_vga_adpt = build_mode_mask(gsern_lane_do_vga_adpt);
        c.s.do_blwc_adpt = build_mode_mask(gsern_lane_do_blwc_adpt));
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_PCS2_BCFG(qlm, BROADCAST),
        c.s.do_prevga_gn_adpt = build_mode_mask(gsern_lane_do_prevga_gn_adpt));
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_PCS3_BCFG(qlm, BROADCAST),
        c.s.tx_enfast = build_mode_mask(gsern_lane_tx_enfast);
        c.s.do_afeos_final = build_mode_mask(gsern_lane_do_afeos_final);
        c.s.do_ctlelte_final = gsern_lane_do_ctlelte_final ? 0xf : 0;
        c.s.do_ctlez_final = gsern_lane_do_ctlez_final ? 0xf : 0;
        c.s.do_ctle_final = gsern_lane_do_ctle_final ? 0xf : 0;
        c.s.do_dfe_final = build_mode_mask(gsern_lane_do_dfe_final);
        c.s.do_vga_final = build_mode_mask(gsern_lane_do_vga_final);
        c.s.do_blwc_final = build_mode_mask(gsern_lane_do_blwc_final);
        c.s.do_prevga_gn_final = gsern_lane_do_prevga_gn_final ? 0xf : 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_PCS3_BCFG(qlm, 0),
        c.s.lane_is_0 = is_first_qlm);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_CNT1_BCFG(qlm),
        c.s.cal_en_wait = 7;
        c.s.pre_cal_en_wait = 2;
        c.s.pre_pwup_wait = 0x3ff);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_CNT2_BCFG(qlm),
        c.s.pre_run_wait = 7;
        c.s.pre_pll_sm_reset_wait = 1;
        c.s.pre_pdiv_reset_wait = 5;
        c.s.pre_pll_reset_wait = 2);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
        c.s.domain_rst_en = 1; /* Set for RC */
        c.s.rst_pll_rst_sm = 1;
        c.s.pll_go2deep_idle = 0;
        c.s.lock_ppm = 0;
        c.s.lock_wait = 0;
        c.s.lock_check = 0;
        c.s.vco_cal_reset = 1;
        c.s.fracn_reset = 1;
        c.s.ssc_reset = 1;
        c.s.post_div_reset = 0;
        c.s.reset = 0;
        c.s.cal_en = 0;
        c.s.pwdn = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
        c.s.domain_rst_en = 1; /* Set for RC */
        c.s.rst_pll_rst_sm = 0;
        c.s.pll_go2deep_idle = 0;
        c.s.lock_ppm = 0;
        c.s.lock_wait = 0;
        c.s.lock_check = 0;
        c.s.vco_cal_reset = 1;
        c.s.fracn_reset = 1;
        c.s.ssc_reset = 1;
        c.s.post_div_reset = 0;
        c.s.reset = 0;
        c.s.cal_en = 0;
        c.s.pwdn = 1);

    /* Adjust presence detection timeout */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_RXD_BCFG(qlm, BROADCAST),
        c.s.sample_wait = 4);

    /* Adjust PCIe per Gen Rx equalization settings */
    /* PCIe Gen1 */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ1_1_BCFG(qlm, BROADCAST),
        c.s.pcie_g1_blwc_deadband = gsern_lane_blwc_deadband;
        c.s.pcie_g1_erc = gsern_lane_erc[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.pcie_g1_ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[GSERN_PCIE_02500000000];
        c.s.pcie_g1_settle_wait = gsern_lane_settle_wait;
        c.s.pcie_g1_voter_sp_mask = gsern_lane_voter_sp_mask[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c1_q_adjust =  gsern_lane_c1_q_adjust[GSERN_PCIE_02500000000]);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ1_2_BCFG(qlm, BROADCAST),
        c.s.pcie_g1_afeos_subrate_final = gsern_lane_afeos_subrate_final[GSERN_PCIE_02500000000];
        c.s.pcie_g1_afeos_subrate_init = gsern_lane_afeos_subrate_init[GSERN_PCIE_02500000000];
        c.s.pcie_g1_subrate_final = gsern_lane_subrate_final[GSERN_PCIE_02500000000];
        c.s.pcie_g1_subrate_init = gsern_lane_subrate_init[GSERN_PCIE_02500000000]);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ1_3_BCFG(qlm, BROADCAST),
        c.s.pcie_g1_c5_limit_hi = gsern_lane_c5_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c4_limit_hi = gsern_lane_c4_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c3_limit_hi = gsern_lane_c3_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c2_limit_hi = gsern_lane_c2_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c1_limit_hi = gsern_lane_c1_limit_hi[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c5_limit_lo = gsern_lane_c5_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c4_limit_lo = gsern_lane_c4_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c3_limit_lo = gsern_lane_c3_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c2_limit_lo = gsern_lane_c2_limit_lo[GSERN_PCIE_02500000000];
        c.s.pcie_g1_c1_limit_lo = c1_limit_lo);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ1_4_BCFG(qlm, BROADCAST),
        c.s.pcie_g1_prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[GSERN_PCIE_02500000000];
        c.s.pcie_g1_prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[GSERN_PCIE_02500000000];
        c.s.pcie_g1_blwc_subrate_final = gsern_lane_blwc_subrate_final;
        c.s.pcie_g1_blwc_subrate_init = gsern_lane_blwc_subrate_init);

    /* PCIe Gen2 */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ2_1_BCFG(qlm, BROADCAST),
        c.s.pcie_g2_blwc_deadband = gsern_lane_blwc_deadband;
        c.s.pcie_g2_erc = gsern_lane_erc[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.pcie_g2_ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[GSERN_PCIE_05000000000];
        c.s.pcie_g2_settle_wait = gsern_lane_settle_wait;
        c.s.pcie_g2_voter_sp_mask = gsern_lane_voter_sp_mask[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c1_q_adjust =  gsern_lane_c1_q_adjust[GSERN_PCIE_05000000000]);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ2_2_BCFG(qlm, BROADCAST),
        c.s.pcie_g2_afeos_subrate_final = gsern_lane_afeos_subrate_final[GSERN_PCIE_05000000000];
        c.s.pcie_g2_afeos_subrate_init = gsern_lane_afeos_subrate_init[GSERN_PCIE_05000000000];
        c.s.pcie_g2_subrate_final = gsern_lane_subrate_final[GSERN_PCIE_05000000000];
        c.s.pcie_g2_subrate_init = gsern_lane_subrate_init[GSERN_PCIE_05000000000]);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ2_3_BCFG(qlm, BROADCAST),
        c.s.pcie_g2_c5_limit_hi = gsern_lane_c5_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c4_limit_hi = gsern_lane_c4_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c3_limit_hi = gsern_lane_c3_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c2_limit_hi = gsern_lane_c2_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c1_limit_hi = gsern_lane_c1_limit_hi[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c5_limit_lo = gsern_lane_c5_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c4_limit_lo = gsern_lane_c4_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c3_limit_lo = gsern_lane_c3_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c2_limit_lo = gsern_lane_c2_limit_lo[GSERN_PCIE_05000000000];
        c.s.pcie_g2_c1_limit_lo = c1_limit_lo);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ2_4_BCFG(qlm, BROADCAST),
        c.s.pcie_g2_prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[GSERN_PCIE_05000000000];
        c.s.pcie_g2_prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[GSERN_PCIE_05000000000];
        c.s.pcie_g2_blwc_subrate_final = gsern_lane_blwc_subrate_final;
        c.s.pcie_g2_blwc_subrate_init = gsern_lane_blwc_subrate_init);

    /* PCIe Gen3 */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ3_1_BCFG(qlm, BROADCAST),
        c.s.pcie_g3_blwc_deadband = gsern_lane_blwc_deadband;
        c.s.pcie_g3_erc = gsern_lane_erc[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.pcie_g3_ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[GSERN_PCIE_08000000000];
        c.s.pcie_g3_settle_wait = gsern_lane_settle_wait;
        c.s.pcie_g3_voter_sp_mask = gsern_lane_voter_sp_mask[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c1_q_adjust =  gsern_lane_c1_q_adjust[GSERN_PCIE_08000000000]);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ3_2_BCFG(qlm, BROADCAST),
        c.s.pcie_g3_afeos_subrate_final = gsern_lane_afeos_subrate_final[GSERN_PCIE_08000000000];
        c.s.pcie_g3_afeos_subrate_init = gsern_lane_afeos_subrate_init[GSERN_PCIE_08000000000];
        c.s.pcie_g3_subrate_final = gsern_lane_subrate_final[GSERN_PCIE_08000000000];
        c.s.pcie_g3_subrate_init = gsern_lane_subrate_init[GSERN_PCIE_08000000000]);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ3_3_BCFG(qlm, BROADCAST),
        c.s.pcie_g3_c5_limit_hi = gsern_lane_c5_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c4_limit_hi = gsern_lane_c4_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c3_limit_hi = gsern_lane_c3_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c2_limit_hi = gsern_lane_c2_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c1_limit_hi = gsern_lane_c1_limit_hi[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c5_limit_lo = gsern_lane_c5_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c4_limit_lo = gsern_lane_c4_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c3_limit_lo = gsern_lane_c3_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c2_limit_lo = gsern_lane_c2_limit_lo[GSERN_PCIE_08000000000];
        c.s.pcie_g3_c1_limit_lo = c1_limit_lo);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ3_4_BCFG(qlm, BROADCAST),
        c.s.pcie_g3_prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[GSERN_PCIE_08000000000];
        c.s.pcie_g3_prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[GSERN_PCIE_08000000000];
        c.s.pcie_g3_blwc_subrate_final = gsern_lane_blwc_subrate_final;
        c.s.pcie_g3_blwc_subrate_init = gsern_lane_blwc_subrate_init);

    /* PCIe Gen4 */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ4_1_BCFG(qlm, BROADCAST),
        c.s.pcie_g4_blwc_deadband = gsern_lane_blwc_deadband;
        c.s.pcie_g4_erc = gsern_lane_erc[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_ctle_lte_zero_ovrd_en = gsern_lane_ctle_lte_zero_ovrd_en;
        c.s.pcie_g4_ctle_lte_zero_ovrd = gsern_lane_ctle_lte_zero_ovrd[GSERN_PCIE_16000000000];
        c.s.pcie_g4_settle_wait = gsern_lane_settle_wait;
        c.s.pcie_g4_voter_sp_mask = gsern_lane_voter_sp_mask[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c1_q_adjust =  gsern_lane_c1_q_adjust[GSERN_PCIE_16000000000]);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ4_2_BCFG(qlm, BROADCAST),
        c.s.pcie_g4_afeos_subrate_final = gsern_lane_afeos_subrate_final[GSERN_PCIE_16000000000];
        c.s.pcie_g4_afeos_subrate_init = gsern_lane_afeos_subrate_init[GSERN_PCIE_16000000000];
        c.s.pcie_g4_subrate_final = gsern_lane_subrate_final[GSERN_PCIE_16000000000];
        c.s.pcie_g4_subrate_init = gsern_lane_subrate_init[GSERN_PCIE_16000000000]);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ4_3_BCFG(qlm, BROADCAST),
        c.s.pcie_g4_c5_limit_hi = gsern_lane_c5_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c4_limit_hi = gsern_lane_c4_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c3_limit_hi = gsern_lane_c3_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c2_limit_hi = gsern_lane_c2_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c1_limit_hi = gsern_lane_c1_limit_hi[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c5_limit_lo = gsern_lane_c5_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c4_limit_lo = gsern_lane_c4_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c3_limit_lo = gsern_lane_c3_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c2_limit_lo = gsern_lane_c2_limit_lo[GSERN_PCIE_16000000000];
        c.s.pcie_g4_c1_limit_lo = c1_limit_lo);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCIE_RXEQ4_4_BCFG(qlm, BROADCAST),
        c.s.pcie_g4_prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[GSERN_PCIE_16000000000];
        c.s.pcie_g4_prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[GSERN_PCIE_16000000000];
        c.s.pcie_g4_blwc_subrate_final = gsern_lane_blwc_subrate_final;
        c.s.pcie_g4_blwc_subrate_init = gsern_lane_blwc_subrate_init);

    BDK_CSR_INIT(common_pll_2_bcfg, node, BDK_GSERNX_COMMON_PLL_2_BCFG(qlm));
    /* Only check common PLL status if it is not bypassed */
    if (!common_pll_2_bcfg.s.ref_clk_bypass)
        if (cavm_gsern_init_wait_for_sm_complete(node, qlm))
            return -1;
    if (cavm_gsern_init_wait_for_sm_ready(node, qlm, -1))
        return -1;

    /* Complete Tx state machine checks after final QLM in PEM is initialized */
    if (use_quad)
    {
        if ((qlm&3) == 3)
        {
            for (int q = qlm; q >= qlm - 3; q--)
            {
                if (cavm_gsern_init_wait_for_tx_ready(node, q, -1))
                    return -1;
            }
        }
    }
    else if (use_dual)
    {
        if ((qlm&1) == 1)
        {
            for (int q = qlm; q >= qlm - 1; q--)
            {
                if (cavm_gsern_init_wait_for_tx_ready(node, q, -1))
                    return -1;
            }
        }
    }
    else
    {
        if (cavm_gsern_init_wait_for_tx_ready(node, qlm, -1))
            return -1;
    }

    return 0;
}
