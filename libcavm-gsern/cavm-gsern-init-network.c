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

static int cavm_gsern_init_pll(bdk_node_t node, int qlm, enum cavm_gsern_flags flags, enum gsern_lane_modes mode)
{
    /* Skip REFCLK setup as already done */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_BIAS_BCFG(qlm),
        c.s.dac1 = ((cavm_gsern_voltage > 950) || (mode == GSERN_GEN_25781250000)) ? 0xf : 0x8;
        c.s.dac0 = 8;
        c.s.bias = 1;
        c.s.bypass = 0;
        c.s.bias_pwdn = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_PLL_1_BCFG(qlm),
        c.s.cal_cp_mult = 3;
        c.s.cp = 0;
        c.s.cp_overide = 0;
        c.s.band_ppm = 0;
        c.s.band = 0xe;
        c.s.band_limits = 0;
        c.s.band_overide = 0;
        c.s.bg_div16 = 0;
        c.s.bg_clk_en = 0;
        c.s.dither_en = 0;
        c.s.cal_sel = 0;
        c.s.vco_sel = 0;
        c.s.sdm_en = 0;
        c.s.post_div = 0xa;
        c.s.div_n = 0x42;
        c.s.div_f = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_PLL_2_BCFG(qlm),
        c.s.mio_refclk_en = 1;
        c.s.lock_check_cnt_ovrd_en = 0;
        c.s.lock_check_cnt_ovrd = 0x7e01;
        c.s.vcm_sel = 0;
        c.s.cp_boost = 1;
        c.s.ssc_sata_mode = 2;
        c.s.ssc_ppm = 0;
        c.s.pnr_refclk_en = 1;
        c.s.ssc_en = 0;
        c.s.ref_clk_bypass = 0;
        c.s.pfd_offset = 0;
        c.s.opamp = 0;
        c.s.res = 4;
        c.s.vco_bias = 6;
        c.s.cal_dac_low = 4;
        c.s.cal_dac_mid = 8;
        c.s.cal_dac_high = 0xc);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
        c.s.lock_ppm = 2;
        c.s.lock_wait = 2;
        c.s.cal_en = 1;
        c.s.pwdn = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_COMMON_RST_BCFG(qlm),
        c.s.rst_pll_rst_sm = 0);

    /* Wait for Common PLL Ready */
    cavm_gsern_init_wait_for_sm_complete(node, qlm);

    return 0;
}

int cavm_gsern_init_network(bdk_node_t node, int qlm, int qlm_lane, enum cavm_gsern_flags flags, enum gsern_lane_modes mode)
{
    bool use_dual = (flags & CAVM_GSERN_FLAGS_DUAL) != 0;
    bool use_quad = (flags & CAVM_GSERN_FLAGS_QUAD) != 0;
    bool use_slow = (mode == GSERN_PCIE_02500000000) || (mode == GSERN_SGMII_01250000000);

    /* 2.5G is the same as 1.25G for the SERDES, but 20bit isn't used. This
       if statement marks that we really want 2.5G, but changes the mode to
       the needed 1.25G */
    bool sgmii_2p5 = false;
    if (mode == GSERN_PCIE_02500000000)
    {
        mode = GSERN_SGMII_01250000000;
        sgmii_2p5 = true;
    }

    /* Check if the common pll is setup. Only setup once */
    BDK_CSR_INIT(bias_cfg, node, BDK_GSERNX_COMMON_BIAS_BCFG(qlm));
    if (bias_cfg.s.bias_pwdn)
    {
        /* Common GSERN Initialization code for Ethernet XAUI,DXAUI,RXAUI,QSGMII,
           SGMII(1.25G,2.5G,3.125G),USXGMII(20.625G,10.3125G,5.15625G,2.578125G) */
        if (cavm_gsern_init_pll(node, qlm, flags, mode))
            return -1;
    }

    int prevga_gn_ovrd = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_RX_PREVGA_GN_OVRD, node, qlm, qlm_lane);
    int prevga_gn_ovrd_en;
    int prevga_gn_adpt = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_RX_PREVGA_GN_ADAPT, node, qlm, qlm_lane);

    /* Configure preVGA adaption overrides for 20Gb/s QLM modes */
    if (mode == GSERN_GEN_20625000000)
    {
        if (prevga_gn_adpt == -1)
        {
            prevga_gn_adpt = gsern_lane_do_prevga_gn_adpt[mode];
            prevga_gn_ovrd_en = gsern_lane_prevga_gn_ovrd_en[mode];
        }
        else if (prevga_gn_adpt == 1) /* preVGA adaptation enabled */
            prevga_gn_ovrd_en = 0;
        else  /* preVGA adaptation disabled */
            prevga_gn_ovrd_en = 1;

        /* Check if we should use the default preVGA setting */
        if (prevga_gn_ovrd == -1)
            prevga_gn_ovrd = gsern_lane_prevga_gn_ovrd[mode];
    }
    else
    {
        prevga_gn_adpt = gsern_lane_do_prevga_gn_adpt[mode];
        prevga_gn_ovrd_en = gsern_lane_prevga_gn_ovrd_en[mode];
        prevga_gn_ovrd = gsern_lane_prevga_gn_ovrd[mode];
    }

    /* Force lane into Rx idle while initializing the GSER */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_IDLEDET_2_BCFG(qlm, qlm_lane),
        c.s.frc_en = 1;
        c.s.frc_val = 1);

    /* Reset indiviual lane before continuing */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, qlm_lane),
        c.s.rst_pll_rst_sm = 1;
        c.s.rst_tx_rst_sm = 1;
        c.s.rst_rx_rst_sm = 1;
        c.s.rst_adpt_rst_sm = 1);
    bdk_wait_usec(1000);

    /* Here we will select Lane PLL values by protocol assuming the
       gsern_lane_modes can be used to make the selection another
       approach might be to add the Lane PLL values to the
       gsern_lane_modes table and index it by mode */
    bool qsgmii = (mode == GSERN_QSGMII_05000000000);
    bool sgmii_1p25 = !sgmii_2p5 && (mode == GSERN_SGMII_01250000000);
    //bool sgmii_3p125 = (mode == GSERN_GEN_03125000000) && !use_dual && !use_quad;
    bool usxgmii_20p625 = (mode == GSERN_GEN_20625000000);
    bool usxgmii_10p3125 = (mode == GSERN_GEN_10312500000);
    bool usxgmii_5p15625 = (mode == GSERN_GEN_05156250000);
    bool usxgmii_2p578125 = (mode == GSERN_GEN_02578125000);
    bool use_20bit = sgmii_1p25;

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

    if (use_quad)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RSTCLKMSK_BCFG(qlm, 4),
            c.s.txdivrst_algn_lane_mask = 0xf);
    }
    if (use_dual)
    {
        /* First lane in a dual pair is always the even lane */
        int first_lane = qlm_lane & -2;
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RSTCLKMSK_BCFG(qlm, qlm_lane),
            c.s.txdivrst_algn_lane_mask = 0x3 << first_lane);
    }
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TRAIN_0_BCFG(qlm, qlm_lane),
        c.s.cfg_cgx = 1;
        c.s.cgx_quad = use_quad;
        c.s.cgx_dual = use_dual);

    if ((mode == GSERN_GEN_03125000000) || (mode == GSERN_GEN_06250000000)) /* XAUI, DXAUI, RXAUI */
    {
        int post_div = (mode == GSERN_GEN_03125000000) ? 3 : 2;
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PLL_1_BCFG(qlm, qlm_lane),
            c.s.cal_cp_mult = 1;
            c.s.cp = 0xc;
            c.s.cp_overide = 0;
            c.s.band_ppm = 2;
            c.s.band = 0x5;
            c.s.band_limits = 0;
            c.s.band_overide = 0;
            c.s.bg_div16 = 0;
            c.s.bg_clk_en = 0;
            c.s.dither_en = 1;
            c.s.cal_sel = 0;
            c.s.vco_sel = 0;
            c.s.sdm_en = 1;
            c.s.post_div = post_div;
            c.s.div_n = 0x18;
            c.s.div_f = 0xf83e);
    }
    else if (qsgmii || sgmii_1p25 || sgmii_2p5)
    {
        int post_div = (qsgmii) ? 2 : 3;
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PLL_1_BCFG(qlm, qlm_lane),
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
            c.s.sdm_en = 1;
            c.s.post_div = post_div;
            c.s.div_n = 0x13;
            c.s.div_f = 0x19365);
    }
    else if (usxgmii_20p625 || usxgmii_10p3125 || usxgmii_5p15625 || usxgmii_2p578125)
    {
        int post_div = (usxgmii_20p625) ? 0 : (usxgmii_10p3125) ? 1 : (usxgmii_5p15625) ? 2 : 3;
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PLL_1_BCFG(qlm, qlm_lane),
            c.s.cal_cp_mult = 1;
            c.s.cp = 0xc;
            c.s.cp_overide = 0;
            c.s.band_ppm = 2;
            c.s.band = 0xe;
            c.s.band_limits = 0;
            c.s.band_overide = 0;
            c.s.bg_div16 = 0;
            c.s.bg_clk_en = 0;
            c.s.dither_en = 1;
            c.s.cal_sel = 0;
            c.s.vco_sel = 0;
            c.s.sdm_en = 0;
            c.s.post_div = post_div;
            c.s.div_n = 0x14;
            c.s.div_f = 0);
    }
    else if (mode == GSERN_GEN_25781250000)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PLL_1_BCFG(qlm, qlm_lane),
            c.s.cal_cp_mult = 1;
            c.s.cp = 0xc;
            c.s.cp_overide = 0;
            c.s.band_ppm = 2;
            c.s.band = 3;
            c.s.band_limits = 0;
            c.s.band_overide = 0;
            c.s.bg_div16 = 0;
            c.s.bg_clk_en = 0;
            c.s.dither_en = 1;
            c.s.cal_sel = 0;
            c.s.vco_sel = 0;
            c.s.sdm_en = 0;
            c.s.post_div = 0;
            c.s.div_n = 0x19;
            c.s.div_f = 0);
    }
    else if (mode == GSERN_GEN_12890625000)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PLL_1_BCFG(qlm, qlm_lane),
            c.s.cal_cp_mult = 1;
            c.s.cp = 0xc;
            c.s.cp_overide = 0;
            c.s.band_ppm = 2;
            c.s.band = 3;
            c.s.band_limits = 0;
            c.s.band_overide = 0;
            c.s.bg_div16 = 0;
            c.s.bg_clk_en = 0;
            c.s.dither_en = 1;
            c.s.cal_sel = 0;
            c.s.vco_sel = 0;
            c.s.sdm_en = 0;
            c.s.post_div = 1;
            c.s.div_n = 0x19;
            c.s.div_f = 0);
    }
    else
        bdk_error("N%d.QLm%d: Lane PLL setup not implemented\n", node, qlm);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PLL_2_BCFG(qlm, qlm_lane),
        c.s.lock_check_cnt_ovrd_en = 0;
        c.s.vcm_sel = 0;
        c.s.cp_boost = 0;
        c.s.ssc_sata_mode = 2;
        c.s.ssc_ppm = 0;
        c.s.pnr_refclk_en = 1;
        c.s.ssc_en = 0;
        c.s.shlb_en = 0;
        c.s.pfd_offset = 0;
        c.s.opamp = 0;
        c.s.res = 0;
        c.s.vco_bias = 6;
        c.s.cal_dac_low = 4;
        c.s.cal_dac_mid = 8;
        c.s.cal_dac_high = 0xc);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_SRCMX_BCFG(qlm, qlm_lane),
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
        c.s.txdivclk_mux_sel_ovrride = (use_quad) ? 2 : (use_dual) ? 1 : 0;
        c.s.tx_ctrl_sel = 2;  /* Set to CGX Mode */
        c.s.tx_data_sel = 2); /* Set to CGX Mode */

    /* For SGMII 1.25G mode only, SerDes PIPE runs in Bit-Stuff Mode
       with 20-bit data path, must enable 40-bit/20-bit word
       unpacking/packing to/from CGX */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_PCS_802P3_BCFG(qlm, qlm_lane),
        c.s.rx_wpk_order = 0;
        c.s.tx_wup_order = 0;
        c.s.rx_wpk_20b40b = use_20bit;
        c.s.tx_wup_40b20b = use_20bit);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_LT_BCFG(qlm, qlm_lane),
        c.s.inj_err_cnt_rst_n = 0;
        c.s.inj_err_cnt_en = 0;
        c.s.inj_err_cnt_len = 0;
        c.s.inj_err_burst_en = 0;
        c.s.inj_err_burst_len = 0;
        c.s.pat_dp_width = (use_20bit) ? 3 : 5;
        c.s.prbs_dp_width = (use_20bit) ? 3 : 5;
        c.s.rx_dp_width = 5;
        c.s.tx_dp_width = 5;
        c.s.core_loopback_mode = 0;
        c.s.sloop_mode = 0;
        c.s.bitstuff_rx_drop_even = use_20bit;
        c.s.bitstuff_rx_en = use_20bit;
        c.s.inv_rx_polarity = bdk_config_get_int(BDK_CONFIG_QLM_LANE_RX_POLARITY, node, qlm, qlm_lane);
        c.s.reverse_rx_bit_order = 1;
        c.s.fifo_algn_qlm_mask_rsvd = 0;
        c.s.fifo_algn_lane_mask_rsvd = 0;
        c.s.fifo_bypass_en = 0;
        c.s.tx_fifo_pop_start_addr = 6;
        c.s.fifo_rst_n = 1;
        c.s.bitstuff_tx_en = use_20bit;
        c.s.inv_tx_polarity = bdk_config_get_int(BDK_CONFIG_QLM_LANE_TX_POLARITY, node, qlm, qlm_lane);
        c.s.reverse_tx_bit_order = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_OS_5_BCFG(qlm, qlm_lane),
        c.s.run_eye_oscal = gsern_lane_run_eye_oscal;
        c.s.c1_e_adjust = 0;
        c.s.c1_i_adjust = 0;
        c.s.c1_q_adjust = gsern_lane_c1_q_adjust[mode];
        c.s.offset_comp_en = 0;
        c.s.binsrch_margin = 6;
        c.s.binsrch_wait = gsern_lane_binsrch_wait[mode];
        c.s.binsrch_acclen = 0;
        c.s.settle_wait = gsern_lane_settle_wait;
        c.s.ir_trim_early_iter_max = gsern_lane_ir_trim_early_iter_max;
        c.s.ir_trim_comp_en = gsern_lane_ir_trim_comp_en;
        c.s.ir_trim_trigger = 0;
        c.s.idle_offset_trigger = 0;
        c.s.afe_offset_trigger = 0;
        c.s.dfe_offset_trigger = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_CDRFSM_BCFG(qlm, qlm_lane),
        c.s.voter_sp_mask = gsern_lane_voter_sp_mask[mode];
        c.s.rst_n = 1;
        c.s.clk_sel = 2;
        c.s.trunc = 3;
        c.s.limit = 0;
        c.s.eoffs = gsern_lane_eoffs[mode];
        c.s.qoffs = gsern_lane_qoffs[mode];
        c.s.inc2 = gsern_lane_inc2[mode];
        c.s.inc1 = gsern_lane_inc1[mode]);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, qlm_lane),
        c.s.perst_n_ovrd = 1;
        c.s.perst_n_ovrd_en = 0;
        c.s.domain_rst_en = 1;
        c.s.rx_go2deep_idle = 0;
        c.s.rx_pd_qac_q = gsern_lane_rx_pd_qac_q;
        c.s.rx_pd_qac_e = gsern_lane_rx_pd_qac_e;
        c.s.rx_pd_idle = 1;
        c.s.rx_rst_deser = 0;
        c.s.rx_rst_dcc_q = (use_slow) ? 1 : 0;
        c.s.rx_rst_dcc_i = (use_slow) ? 1 : 0;
        c.s.rx_rst_dcc_e = (use_slow) ? 1 : 0;
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
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_QAC_BCFG(qlm, qlm_lane),
        c.s.cdr_qac_selq = gsern_lane_cdr_qac_selq[mode];  /* SGMII 1.25G only disable QAC E and QAC Q */
        c.s.cdr_qac_sele = gsern_lane_cdr_qac_sele[mode];  /* SGMII 1.25G only disable QAC E and QAC Q */
        c.s.qac_cntset_q = 3;
        c.s.qac_cntset_e = 3;
        c.s.qac_ref_qoffs = gsern_lane_qac_ref_qoffs[mode];
        c.s.qac_ref_eoffs = gsern_lane_qac_ref_eoffs;
        c.s.en_qac_e = gsern_lane_en_qac_e[mode];  /* SGMII 1.25G only disable QAC E and QAC Q */
        c.s.en_qac_q = gsern_lane_en_qac_q[mode]); /* SGMII 1.25G only disable QAC E and QAC Q */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_4_BCFG(qlm, qlm_lane),
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
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_ST_BCFG(qlm, qlm_lane),
        c.s.rxcdrfsmi = gsern_lane_rxcdrfsmi;
        c.s.rx_dcc_iboost = gsern_lane_rx_dcc_iboost[mode];
        c.s.rx_dcc_lowf = gsern_lane_rx_dcc_lowf[mode];
        c.s.bstuff = use_20bit;
        c.s.rx_idle_lowf = 1;
        c.s.idle_os_bitlen = 0;
        c.s.idle_os_ovrd_en = 0;
        c.s.refset = 3;
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
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_8_BCFG(qlm, qlm_lane),
        c.s.subrate_init = gsern_lane_subrate_init[mode];
        c.s.subrate_final = gsern_lane_subrate_final[mode]);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_13_BCFG(qlm, qlm_lane),
        c.s.afeos_subrate_scale = 7;
        c.s.afeos_subrate_init = gsern_lane_afeos_subrate_init[mode];
        c.s.afeos_subrate_final = gsern_lane_afeos_subrate_final[mode]);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_20_BCFG(qlm, qlm_lane),
        c.s.blwc_subrate_scale = 7;
        c.s.blwc_subrate_init = gsern_lane_blwc_subrate_init;
        c.s.blwc_subrate_final = gsern_lane_blwc_subrate_final);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_21_BCFG(qlm, qlm_lane),
        c.s.prevga_gn_subrate_now_ovrd_en = 0;
        c.s.prevga_gn_subrate_now_ovrd = 0xf732;
        c.s.prevga_gn_subrate_scale = 7;
        c.s.prevga_gn_subrate_init = gsern_lane_prevga_gn_subrate_init[mode];
        c.s.prevga_gn_subrate_fin = gsern_lane_prevga_gn_subrate_fin[mode]);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_9_BCFG(qlm, qlm_lane),
        c.s.ctlelte_deadband = gsern_lane_ctlelte_deadband;
        c.s.ctlez_deadband = gsern_lane_ctlez_deadband;
        c.s.ctle_deadband = gsern_lane_ctle_deadband;
        c.s.dfe_deadband = gsern_lane_dfe_deadband;
        c.s.vga_deadband = gsern_lane_vga_deadband);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_19_BCFG(qlm, qlm_lane),
        c.s.blwc_leak_sgn = gsern_lane_blwc_leak_sgn;
        c.s.blwc_updn_len = gsern_lane_blwc_updn_len;
        c.s.blwc_deadband = gsern_lane_blwc_deadband;
        c.s.blwc_deadband_inc = 0;
        c.s.blwc_leak = gsern_lane_blwc_leak;
        c.s.blwc_mu = gsern_lane_blwc_mu;
        c.s.blwc_timer_max = gsern_lane_blwc_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_23_BCFG(qlm, qlm_lane),
        c.s.prevga_gn_leak_sgn = gsern_lane_prevga_gn_leak_sgn;
        c.s.prevga_gn_deadband = gsern_lane_prevga_gn_deadband;
        c.s.prevga_gn_deadband_inc = 0;
        c.s.prevga_gn_leak = gsern_lane_prevga_gn_leak;
        c.s.prevga_gn_mu = gsern_lane_prevga_gn_mu;
        c.s.prevga_gn_timer_max = gsern_lane_prevga_gn_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_12_BCFG(qlm, qlm_lane),
        c.s.afeos_leak_sgn = gsern_lane_afeos_leak_sgn;
        c.s.afeos_deadband = gsern_lane_afeos_deadband;
        c.s.afeos_deadband_inc = 0;
        c.s.afeos_leak = gsern_lane_afeos_leak;
        c.s.afeos_mu = gsern_lane_afeos_mu;
        c.s.afeos_timer_max = gsern_lane_afeos_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_14_BCFG(qlm, qlm_lane),
        c.s.c6_c15_limit_hi = gsern_lane_c6_c15_limit_hi[mode];
        c.s.c6_c15_limit_lo = gsern_lane_c6_c15_limit_lo[mode];
        c.s.dfe_c1_deadband = gsern_lane_dfe_c1_deadband;
        c.s.dfe_c1_deadband_inc = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST_CNT4_BCFG(qlm, qlm_lane),
        c.s.svc_clk_freq = 0;
        c.s.blwc_reset_wait = 0xf;
        c.s.dfe_afe_oscal_wait = gsern_lane_dfe_afe_oscal_wait);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_6_BCFG(qlm, qlm_lane),
        c.s.ctlez_leak = gsern_lane_ctlez_leak;
        c.s.ctlez_mu = gsern_lane_ctlez_mu;
        c.s.ctlez_timer_max = gsern_lane_ctlez_timer_max;
        c.s.ctle_leak = gsern_lane_ctle_leak;
        c.s.ctle_mu = gsern_lane_ctle_mu;
        c.s.ctle_timer_max = gsern_lane_ctle_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_6A_BCFG(qlm, qlm_lane),
        c.s.ctlelte_leak_sgn = gsern_lane_ctlelte_leak_sgn;
        c.s.ctlelte_leak = gsern_lane_ctlelte_leak;
        c.s.ctlelte_mu = gsern_lane_ctlelte_mu;
        c.s.ctlelte_timer_max = gsern_lane_ctlelte_timer_max);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_5_BCFG(qlm, qlm_lane),
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
    /* Errata GSER-35489 Disable DFE C2 & C3 Taps for 25.78125Gbd mode */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_0_BCFG(qlm, qlm_lane),
        c.s.c9_ovrd_en = gsern_lane_c9_ovrd_en;
        c.s.c9_ovrd = gsern_lane_c9_ovrd;
        c.s.c8_ovrd_en = gsern_lane_c8_ovrd_en;
        c.s.c8_ovrd = gsern_lane_c8_ovrd;
        c.s.c7_ovrd_en = gsern_lane_c7_ovrd_en;
        c.s.c7_ovrd = gsern_lane_c7_ovrd;
        c.s.c6_ovrd_en = gsern_lane_c6_ovrd_en;
        c.s.c6_ovrd = gsern_lane_c6_ovrd;
        c.s.c5_ovrd_en = gsern_lane_c5_ovrd_en;
        c.s.c5_ovrd = gsern_lane_c5_ovrd;
        c.s.c4_ovrd_en = gsern_lane_c4_ovrd_en;
        c.s.c4_ovrd = gsern_lane_c4_ovrd;
        c.s.c3_ovrd_en = gsern_lane_c3_ovrd_en[mode];
        c.s.c3_ovrd = gsern_lane_c3_ovrd;
        c.s.c2_ovrd_en = gsern_lane_c2_ovrd_en[mode];
        c.s.c2_ovrd = gsern_lane_c2_ovrd);

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_1_BCFG(qlm, qlm_lane),
        c.s.prevga_gn_ovrd_en = prevga_gn_ovrd_en;
        c.s.prevga_gn_ovrd = prevga_gn_ovrd;
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
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_15_BCFG(qlm, qlm_lane),
        c.s.c1_limit_lo = c1_limit_lo;
        c.s.c1_limit_hi = gsern_lane_c1_limit_hi[mode];
        c.s.c2_limit_lo = gsern_lane_c2_limit_lo[mode];
        c.s.c2_limit_hi = gsern_lane_c2_limit_hi[mode];
        c.s.c3_limit_lo = gsern_lane_c3_limit_lo[mode];
        c.s.c3_limit_hi = gsern_lane_c3_limit_hi[mode];
        c.s.c4_limit_lo = gsern_lane_c4_limit_lo[mode];
        c.s.c4_limit_hi = gsern_lane_c4_limit_hi[mode];
        c.s.c5_limit_lo = gsern_lane_c5_limit_lo[mode];
        c.s.c5_limit_hi = gsern_lane_c5_limit_hi[mode]);

    /* Start v---v These will only set the ovrd_en=1 for the SGMII 1.25Gbd
       and CPRI 1.228Gbd data rates modes from the
       cavm-gsern-settings.h table */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_OS_1_BCFG(qlm, qlm_lane),
        c.s.os3_1_ovrd_en = gsern_lane_os3_1_ovrd_en;
        c.s.os3_1_ovrd    = gsern_lane_os3_1_ovrd;
        c.s.os3_0_ovrd_en = gsern_lane_os3_0_ovrd_en[mode];
        c.s.os3_0_ovrd    = gsern_lane_os3_0_ovrd;
        c.s.os2_1_ovrd_en = gsern_lane_os2_1_ovrd_en;
        c.s.os2_1_ovrd    = gsern_lane_os2_1_ovrd;
        c.s.os2_0_ovrd_en = gsern_lane_os2_0_ovrd_en[mode];
        c.s.os2_0_ovrd    = gsern_lane_os2_0_ovrd;
        c.s.os1_1_ovrd_en = gsern_lane_os1_1_ovrd_en;
        c.s.os1_1_ovrd    = gsern_lane_os1_1_ovrd;
        c.s.os1_0_ovrd_en = gsern_lane_os1_0_ovrd_en[mode];
        c.s.os1_0_ovrd    = gsern_lane_os1_0_ovrd;
        c.s.os0_1_ovrd_en = gsern_lane_os0_1_ovrd_en;
        c.s.os0_1_ovrd    = gsern_lane_os0_1_ovrd;
        c.s.os0_0_ovrd_en = gsern_lane_os0_0_ovrd_en[mode];
        c.s.os0_0_ovrd    = gsern_lane_os0_0_ovrd);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_OS_2_BCFG(qlm, qlm_lane),
        c.s.os7_1_ovrd_en = gsern_lane_os7_1_ovrd_en;
        c.s.os7_1_ovrd    = gsern_lane_os7_1_ovrd;
        c.s.os7_0_ovrd_en = gsern_lane_os7_0_ovrd_en[mode];
        c.s.os7_0_ovrd    = gsern_lane_os7_0_ovrd;
        c.s.os6_1_ovrd_en = gsern_lane_os6_1_ovrd_en;
        c.s.os6_1_ovrd    = gsern_lane_os6_1_ovrd;
        c.s.os6_0_ovrd_en = gsern_lane_os6_0_ovrd_en[mode];
        c.s.os6_0_ovrd    = gsern_lane_os6_0_ovrd;
        c.s.os5_1_ovrd_en = gsern_lane_os5_1_ovrd_en;
        c.s.os5_1_ovrd    = gsern_lane_os5_1_ovrd;
        c.s.os5_0_ovrd_en = gsern_lane_os5_0_ovrd_en[mode];
        c.s.os5_0_ovrd    = gsern_lane_os5_0_ovrd;
        c.s.os4_1_ovrd_en = gsern_lane_os4_1_ovrd_en;
        c.s.os4_1_ovrd    = gsern_lane_os4_1_ovrd;
        c.s.os4_0_ovrd_en = gsern_lane_os4_0_ovrd_en[mode];
        c.s.os4_0_ovrd    = gsern_lane_os4_0_ovrd);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_OS_3_BCFG(qlm, qlm_lane),
        c.s.os11_1_ovrd_en = gsern_lane_os11_1_ovrd_en;
        c.s.os11_1_ovrd    = gsern_lane_os11_1_ovrd;
        c.s.os11_0_ovrd_en = gsern_lane_os11_0_ovrd_en[mode];
        c.s.os11_0_ovrd    = gsern_lane_os11_0_ovrd;
        c.s.os10_1_ovrd_en = gsern_lane_os10_1_ovrd_en;
        c.s.os10_1_ovrd    = gsern_lane_os10_1_ovrd;
        c.s.os10_0_ovrd_en = gsern_lane_os10_0_ovrd_en[mode];
        c.s.os10_0_ovrd    = gsern_lane_os10_0_ovrd;
        c.s.os9_1_ovrd_en = gsern_lane_os9_1_ovrd_en;
        c.s.os9_1_ovrd    = gsern_lane_os9_1_ovrd;
        c.s.os9_0_ovrd_en = gsern_lane_os9_0_ovrd_en[mode];
        c.s.os9_0_ovrd    = gsern_lane_os9_0_ovrd;
        c.s.os8_1_ovrd_en = gsern_lane_os8_1_ovrd_en;
        c.s.os8_1_ovrd    = gsern_lane_os8_1_ovrd;
        c.s.os8_0_ovrd_en = gsern_lane_os8_0_ovrd_en[mode];
        c.s.os8_0_ovrd    = gsern_lane_os8_0_ovrd);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_OS_4_BCFG(qlm, qlm_lane),
        c.s.os15_1_ovrd_en = gsern_lane_os15_1_ovrd_en;
        c.s.os15_1_ovrd    = gsern_lane_os15_1_ovrd;
        c.s.os15_0_ovrd_en = gsern_lane_os15_0_ovrd_en[mode];
        c.s.os15_0_ovrd    = gsern_lane_os15_0_ovrd;
        c.s.os14_1_ovrd_en = gsern_lane_os14_1_ovrd_en;
        c.s.os14_1_ovrd    = gsern_lane_os14_1_ovrd;
        c.s.os14_0_ovrd_en = gsern_lane_os14_0_ovrd_en[mode];
        c.s.os14_0_ovrd    = gsern_lane_os14_0_ovrd;
        c.s.os13_1_ovrd_en = gsern_lane_os13_1_ovrd_en;
        c.s.os13_1_ovrd    = gsern_lane_os13_1_ovrd;
        c.s.os13_0_ovrd_en = gsern_lane_os13_0_ovrd_en[mode];
        c.s.os13_0_ovrd    = gsern_lane_os13_0_ovrd;
        c.s.os12_1_ovrd_en = gsern_lane_os12_1_ovrd_en;
        c.s.os12_1_ovrd    = gsern_lane_os12_1_ovrd;
        c.s.os12_0_ovrd_en = gsern_lane_os12_0_ovrd_en[mode];
        c.s.os12_0_ovrd    = gsern_lane_os12_0_ovrd);
    /* End ^---^ These will only set the ovrd_en for the SGMII 1.25Gbd and
       CPRI 1.228Gbd data rates - End */

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, qlm_lane),
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
        c.s.do_prevga_gn_adpt = prevga_gn_adpt;
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
        c.s.tx_dcc_rst = (use_slow) ? 1 : 0;
        c.s.tx_enctl = 1;
        c.s.tx_cdrdiv3 = gsern_lane_tx_cdrdiv3[mode];
        c.s.tx_endiv5 = 1;
        c.s.tx_pdb = 0;
        c.s.tx_dcc_pdb = 0);
    /* The trim16-45 overrides are enabled for XAUI,RXAUI,DXAUI,SGMII,QSGMII,
       USXGMII(5.15625,2.578125) modes should be automatically set to
       1 via the "mode" index in the table */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_ITRIM_3_BCFG(qlm, qlm_lane),
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
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_ITRIM_4_BCFG(qlm, qlm_lane),
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
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_ITRIM_5_BCFG(qlm, qlm_lane),
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
    /*  end trim16-45 overrides */

    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_TX_1_BCFG(qlm, qlm_lane),
        c.s.tx_acjtag = 0;
        c.s.tx_dacj = 0;
        c.s.tx_enloop = 0;
        c.s.nvlink = 0;
        c.s.rx_mod4 = 0;
        c.s.rx_post4 = 1;
        c.s.mod4 = gsern_lane_mod4[mode];
        c.s.div20 = gsern_lane_div20[mode];
        c.s.tx_enfast = gsern_lane_tx_enfast[mode];
        c.s.tx_encm = gsern_lane_tx_encm);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST_CNT5_BCFG(qlm, qlm_lane),
        c.s.idle_exit_wait = 0xff;
        c.s.idle_exit_wait_en = 1);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_OS_5_BCFG(qlm, qlm_lane),
        c.s.run_eye_oscal = gsern_lane_run_eye_oscal;
        c.s.c1_e_adjust = 0;
        c.s.c1_i_adjust = 0;
        c.s.c1_q_adjust = gsern_lane_c1_q_adjust[mode];
        c.s.offset_comp_en = 1;
        c.s.binsrch_margin = 6;
        c.s.binsrch_wait = gsern_lane_binsrch_wait[mode];
        c.s.binsrch_acclen = 0;
        c.s.settle_wait = gsern_lane_settle_wait;
        c.s.ir_trim_early_iter_max = gsern_lane_ir_trim_early_iter_max;
        c.s.ir_trim_comp_en = gsern_lane_ir_trim_comp_en;
        c.s.ir_trim_trigger = 0;
        c.s.idle_offset_trigger = 0;
        c.s.afe_offset_trigger = 0;
        c.s.dfe_offset_trigger = 0);
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST1_BCFG(qlm, qlm_lane),
        c.s.perst_n_ovrd = 1;
        c.s.perst_n_ovrd_en = 0;
        c.s.domain_rst_en = 1;
        c.s.rx_go2deep_idle = 0;
        c.s.rx_pd_qac_q = gsern_lane_rx_pd_qac_q;
        c.s.rx_pd_qac_e = gsern_lane_rx_pd_qac_e;
        c.s.rx_pd_idle = 0;
        c.s.rx_rst_deser = 0;
        c.s.rx_rst_dcc_q = (use_slow) ? 1 : 0;
        c.s.rx_rst_dcc_i = (use_slow) ? 1 : 0;
        c.s.rx_rst_dcc_e = (use_slow) ? 1 : 0;
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
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RST2_BCFG(qlm, qlm_lane),
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
        c.s.tx_dcc_rst = (use_slow) ? 1 : 0;
        c.s.tx_enctl = 1;
        c.s.tx_cdrdiv3 = gsern_lane_tx_cdrdiv3[mode];
        c.s.tx_endiv5 = 1;
        c.s.tx_pdb = 1;
        c.s.tx_dcc_pdb = 1);

    /* Wait for Lane PLL Ready */
    if (cavm_gsern_init_wait_for_sm_ready(node, qlm, qlm_lane))
        return -1;

    /* Wait for Lane Tx Ready */
    if (cavm_gsern_init_wait_for_tx_ready(node, qlm, qlm_lane))
        return -1;

    bdk_wait_usec(1000);

    /* Clear the Rx idle override after GSER init complete */
    BDK_CSR_MODIFY(c, node, BDK_GSERNX_LANEX_RX_IDLEDET_2_BCFG(qlm, qlm_lane),
        c.s.frc_en = 0;
        c.s.frc_val = 0);

    /* Note for the "QUAD" case we should wait for all four lanes to
       indicate Tx Ready and for the "DUAL" case we should wait for
       both lanes to indicate Tx Ready */

    /* Don't wait for RX_READY=1, allow CGX controller to start
       transmitting when TX_READY=1. RX_READY will not be set until
       remote transmitter sends serial data */
    return 0;
}
