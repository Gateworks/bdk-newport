/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mtd_ptp_costants.c
* 
* DESCRIPTION:
*       Constant definitions of one step PTP.
*
* DEPENDENCIES:
*       None.
*
* FILE REVISION NUMBER:
*       $Revision: 1 $
*
*******************************************************************************/

#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdSemaphore.h"
#include "mtdMsecPtpApiDefs.h"
#include "mtdMsecTypes.h"
#include "mtdPtp1step.h"

/* Constants */
MTD_U16 mtd_ptp_1step_base_addr[] = {
   MTD_VN_GLOBAL_PTP,
   MTD_VN_TAI_CFG,
   MTD_VN_EG_PTP,
   MTD_VN_IG_PTP
};
char * mtd_ptp_1step_macNmList[] =
    {
    "RxGoodOctLo",
    "RxGoodOctHi",
    "RxBadOct",
    "TxFifoUnder",
    "RxUnicast",
    "SentDeferred",
    "BroadRx",
    "MultiRx",
    "Fr64",
    "Fr65_127",
    "Fr128_255",
    "Fr256_511",
    "Fr512_1023",
    "Fr1024_Max",
    "GoodTxOctLo",
    "GoodTxOctHi",
    "TxUnicast",
    "ExCol",
    "TxMulti",
    "TxBroad",
    "SentMultiple",
    "FCSent",
    "FCReceived",
    "RxFifoOver",
    "Undersize",
    "Fragments",
    "Oversize",
    "Jabber",
    "RxError",
    "BadCrc",
    "Collisions",
    "LateCol",
    0
    };

/* use for display information */
char *mtd_ptp_lut_match_fld_pos_name[] = {
  "FLAGS",          
  "PTP_VERSIONS",   
  "PTP_MSGTYPE",    
  "PTP_TRANS_SPEC", 
  "TST_E",          
  "TST_ACTION",     
  "PTP_FLAGS",
  0  
};

int mtd_ptp_lut_match_fld_pos[]= {
      0,
     16,
     24,
     28,
     32,
     47,
     48
};

char *mtd_ptp_lut_match_fld_sz_name[] = {
  "FLAGS",
  "PTP_VERSIONS",
  "PTP_MSGTYPE",
  "PTP_TRANS_SPEC",
  "TST_E",
  "TST_ACTION",
  "PTP_FLAGS",
  0
};

int mtd_ptp_lut_match_fld_sz[]={
    16,
     8,
     4,
     4,
     1,
     3,
    16
};

char * mtd_ptp_lut_tx_action_fld_pos_name[] = {
  "UPDATETXTIME",
  "REMOVETST",
  "DROP",
  "UPDATERESIDENCE",
  "CLEAR_PIGGYBACK",
  "STAMPLOW",
  "STAMPHIGH",
  "HOLD_FOR_TRANS",
  0
};

int mtd_ptp_lut_tx_action_fld_pos[] = {
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
};

int mtd_ptp_lut_tx_action_fld_sz[] = {
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1
};

char * mtd_ptp_lut_rx_action_fld_pos_name[] = {
  "TST_ACTION",
  "TST_OFFSETTYPE",
  "TST_U",
  "INSERTTST",
  "DROP",
  "INIPIGGYBACK",
  "STAMPLOW",
  "STAMPHIGH",
  "TST_E",
  0
};

int mtd_ptp_lut_rx_action_fld_pos[] = {
    0,
    3,
    8,
    9,
    10,
    12,
    13,
    14,
    15
};

int mtd_ptp_lut_rx_action_fld_sz[] = {
    3,
    5,
    1,
    1,
    1,
    1,
    1,
    1,
    1
};

char * mtd_ptp_stat_name [] = {
"STAT_ACT_BIT4",
"STAT_ACT_BIT5",
"STAT_ACT_BIT6",
"STAT_UPDATE_TX",
"STAT_INSRMV_TST",
"STAT_DROP",
"STAT_UPDATE_RES",
"STAT_INY_PIGGY",
"STAT_STAMP_LOW",
"STAT_STAMP_HIGH",
"STAT_TST_E",
"STAT_FlagPTPv2",
"STAT_FlagUDP",
"STAT_FlagIPv4",
"STAT_FlagIPv6",
"STAT_FlagTST",
"STAT_FlagGRE",
"STAT_FlagY1731",
"STAT_FlagNTP",
"STAT_FLAGPTPV1",
"STAT_FlagDOT1Q",
"STAT_FlagSTAG",
"STAT_FlagITAG",
"STAT_FlagSNAP",
"STAT_FlagMPLS",
"STAT_FlagMACSEC",
"STAT_FlagERROR",
"STAT_RSVD0",
"STAT_RSVD1",
"STAT_RSVD2",
"STAT_RSVD3",
0
};
char * mtd_ptp_rf_names_list [] = {
"cfg_gen",
"cfg_gen2",
"intr_set",
"intr_set_msk",
"timeout_ctl",
"stt_ctl",
"disp",
"disp_rma_s",
"disp_rma_m",
"ts_queue",
"ts_usage",
"tsql_data",
"tsqh_data",
"bist_ctl0",
"bist_status",
"cfg_stat",
0
};

char * mtd_ptp_egr_stats_names_list [] = {
"act_bit4",
"act_bit5",
"act_bit6",
"intr_update",
"update_tx",
"remove_tst",
"drop",
"update_res",
"ini_piggy",
"stamp_low",
"stamp_high",
"tst_e",
"flag_ptpv2",
"flag_udp",
"flag_ipv4",
"flag_ipv6",
"flag_tst",
"flag_gre",
"flag_ipinip",
"flag_ntp",
"flag_ptpv1",
"flag_dot1q",
"flag_stag",
"flag_itag",
"flag_snap",
"flag_mpls",
"flag_macsec",
"flag_error",
"reserved",
"reserved",
"reserved",
"reserved",
0
};

char * mtd_ptp_igr_stats_names_list [] = {
"tst_offtype1",
"tst_offtype2",
"tst_offtype3",
"tst_offtype4",
"tst_u",
"insert_tst",
"drop",
"reserved",
"ini_piggyback",
"stamp_low",
"stamp_high",
"tst_e",
"flag_ptpv2",
"flag_udp",
"flag_ipv4",
"flag_ipv6",
"reserved",
"flag_gre",
"flag_ipinip",
"flag_ntp",
"flag_ptpv1",
"flag_dot1q",
"flag_stag",
"flag_itag",
"flag_snap",
"flag_mpls",
"flag_macsec",
"flag_error",
"reserved",
"reserved",
"reserved",
"reserved",
0
};

int mtd_ptp_lut_key_pos[] = {
              0,
              1,
              2,
              3,
              4,
              5,
              6,
              7,
              8,
              9,
              10,
              11,
              12,
              13,
              14,
              15,
              16,
              24,
              28,
              32,
              47,
              48,
/*# Note: DomainNumber starts at bit 72, but here we have to put 64-72=8 */
                8
};


int mtd_ptp_lut_key_size[] = {
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              1,
              8,
              4,
              4,
              3,
              1,
              16,
          8
}; 

/* use Enum MTD_PTP_1STEP_LUT_ACT as index */
int mtd_ptp_lut_act_pos[] = {
          8,  /* UpdateTxTime     Tx action */
          9,  /* RemoveTST        Tx action */
          10, /* Drop             Tx/Rx action */
          11, /* UpdateResidence, Tx action */
          13, /* StampLow,        Tx/Rx action */
          14, /* StampHigh,       Tx/Rx action */
          0,  /* TST_action,         Rx action */
          3,  /* TST_mode,           Rx action */
          15, /* TST_E,              Rx action */
          9,  /* InsertTST,          Rx action */
          12, /* IniPiggyback,       Rx action */
          15, /* HoldForTransmission,  Tx action */
          12, /* ClearPiggyback,       Tx action */
          6,
          5
};

char * mtd_ptp_tai_regs_list_name [] = {
"tod_0",
"tod_1",
"tod_2",
"tod_3",
"frc_0",
"frc_1",
"frc_2",
"frc_3",
"drift_adj_cfg",
"tod_step_ns",
"tod_step_fs",
"tod_cfg_gen",
"pulse_delay",
"tri_gen_tod_0",
"tri_gen_tod_1",
"tri_gen_tod_2",
"tri_gen_tod_3",
"trig_gen_msk_0",
"trig_gen_msk_1",
"trig_gen_msk_2",
"trig_gen_msk_3",
"tod_load_0",
"tod_load_1",
"tod_load_2",
"tod_load_3",
"tod_cap_0",
"tod_cap_1",
"tod_cap_2",
"tod_cap_3",
"tod_cap1_0",
"tod_cap1_1",
"tod_cap1_2",
"tod_cap1_3",
"tod_cap_cfg",
"pulse_in_cnt",
"tod_func_cfg",
"pclk_cfg",
"pclk_cnt_0",
"pclk_cnt_1",
"drift_thr_cfg",
"next_rt_0",
"next_rt_1",
"next_rt_2",
"next_rt_3",
"clock_cyc",
"extr_clk_prop_d",
"clk_in_cnt",
"tai_intr",
"tai_intr_mask",
0
};




char *mtd_tai_tod_cfg_gen_name[] = {
  "CLK_MODE",
  "IN_CLK_EN",
  "EXT_CLK_EN",
  "EN_SYNCE_TAI_CLK",
  "SYNCE_CLK_SEL",
  "TAI_CLKOUT_SEL",
  "PULSE_IN_SEL",
  "CLK_IN_SEL",
  "NTP_TOD_MODE"
};



int mtd_tai_tod_cfg_gen_pos[]= {
   0,
   2,
   10,
   11,
   12,
   13,
   14,
   15
};

int mtd_tai_tod_cfg_gen_sz[]= {
   2,
   1,
   1,
   1,
   1,
   1,
   1,
   1
};



char *mtd_tai_tod_func_cfg_name[] = {
  "PULSE_WIDTH",
  "CNT_SEL",
  "TOD_FUNC_TRIG",
  "TRIG_GEN_EN",
  "TOD_FUNC"
};

int mtd_tai_tod_func_cfg_pos[]= {
    0,
    27,
    28,
    29,
    30,
    -1
};

int mtd_tai_tod_func_cfg_sz[]= {
   27,
    1,
    1,
    1,
    2
};



