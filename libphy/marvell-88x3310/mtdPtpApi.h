/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mtdPtpApi.h
* 
* DESCRIPTION:
*       API Functions of PTP in MacSec.
*
* DEPENDENCIES:
*       None.
*
* FILE REVISION NUMBER:
*       $Revision: 1 $
*
*******************************************************************************/
#ifndef __Mtd_Ptp_Api_h
#define __Mtd_Ptp_Api_h
#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

/*******************************************************************************
* mtd_enable_ptp
*
* DESCRIPTION:
*       This routine enable PTP by clearing PTP bypass 
*
* INPUTS:
*    port - port number.
*   
* OUTPUTS:
*       None.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_enable_ptp (MTD_U16 port);
/*******************************************************************************
* mtd_disable_ptp
*
* DESCRIPTION:
*       This routine disables PTP by setting PTP bypass.
*
* INPUTS:
*    port - port number.
*   
* OUTPUTS:
*       None.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_disable_ptp (MTD_U16 port);

/*******************************************************************************
* mtd_ptp_prgm_lut_entry
*
* DESCRIPTION:
*     program lut entry
*      lut_key: 80 bit match fields
*      lut_valid: 80 bit valid fields (correspond to lut_match)
*      lut_action: 32 bit action fields
*      lut_index: index of LUT entry to program
*      path: eg0_ptp for egress or ig0_ptp for ingress
*
* INPUTS:
*       lut_match - 80 bit match fields
*       lut_valid: 80 bit valid fields (correspond to lut_match)
*       lut_action: 32 bit action fields
*       lut_index: index of LUT entry to program
*       path: eg0_ptp for egress or ig0_ptp for ingress
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_prgm_lut_entry (MTD_U16 port, long long lut_key, long long lut_valid, long lut_key_upper, long lut_valid_upper, long long lut_action, 
short lut_index, int path );

/*******************************************************************************
* mtd_ptp_check_lut_entry
*
* DESCRIPTION:
*   Check lut entry in memory 
*
* INPUTS:
*       lut_index: index of LUT entry to program
*       path: eg0_ptp for egress or ig0_ptp for ingress
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_check_lut_entry (MTD_U16 port,  int lut_index, int path );
/*******************************************************************************
* mtd_get_ptp_stats
*
* DESCRIPTION:
*     prints out the ptp statistics . 
*
* INPUTS:
*       port - port number
*       path - MTD_PTP_igr or MTD_PTP_egr.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_stats ( MTD_U16 port, MTD_PTP_Blk path );
/*******************************************************************************
* mtd_ptp_lut_clear
*
* DESCRIPTION:
*     Clear PTP lut. 
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_lut_clear (MTD_U16 port);

/*******************************************************************************
* mtd_get_ptp_tai_tod
*
* DESCRIPTION:
*       This routine gets Time of day of PTP TAI.
*
* INPUTS:
*    port - port number.
*   
* OUTPUTS:
*       ns - nanoseconds.
*       sec_lo - low bits seconds.
*       sec_hi - high bits seconds.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tai_tod(MTD_U16 port, unsigned int *_ns, unsigned int *_sec_lo, unsigned int *_sec_hi);
/*******************************************************************************
* mtd_get_ptp_tai_frc
*
* DESCRIPTION:
*       This routine gets Free running counter of PTP TAI.
*
* INPUTS:
*    port - port number.
*   
* OUTPUTS:
*       ns - nanoseconds.
*       sec_lo - low bits seconds.
*       sec_hi - high bits seconds.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tai_frc(MTD_U16 port, unsigned int *_ns, unsigned int *_sec_lo, unsigned int *_sec_hi);

/*******************************************************************************
* mtd_get_ptp_tai_drift_adjust
*
* DESCRIPTION:
*       This routine gets drift adjust of PTP TAI.
*
* INPUTS:
*    port - port number.
*   
* OUTPUTS:
*       adj - adjust value.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tai_drift_adjust (MTD_U16 port, unsigned int *adj);
/*******************************************************************************
* mtd_set_ptp_tai_drift_adjust
*
* DESCRIPTION:
*       This routine gets drift adjust of PTP TAI.
*
* INPUTS:
*    port - port number.
*       adj - adjust value.
*   
* OUTPUTS:
*   None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_ptp_tai_drift_adjust (MTD_U16 port, unsigned int adj);
/*******************************************************************************
* mtd_get_ptp_tsqh_drain
*
* DESCRIPTION:
*       This routine gets high TS queue of PTP TAI fully.
*
* INPUTS:
*    port - port number.
*   path: eg0_ptp for egress or ig0_ptp for ingress
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tsqh_drain (MTD_U16 port,  MTD_PTP_Blk path);
/*******************************************************************************
* mtd_get_ptp_tsql_drain
*
* DESCRIPTION:
*       This routine gets low TS queue of PTP TAI fully.
*
* INPUTS:
*    port - port number.
*   path: eg0_ptp for egress or ig0_ptp for ingress
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_tsql_drain (MTD_U16 port,  MTD_PTP_Blk path);
/*******************************************************************************
* mtd_set_tai_tod_func
*
* DESCRIPTION:
*       This routine sets TAI TOD trigger generaly.
*
* INPUTS:
*    port - port number.
*   tod_func - value: 0 - update, 1 -increment, 2- decrement, 3-capture 
*   trig - tod_func_trig, default 0, triggers tod function when set to 1 
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_tai_tod_func (MTD_U16 port, unsigned int tod_func, unsigned int trig);

/* set ingress or egress asymmetry */
MTD_STATUS mtd_set_asymmetry(unsigned int asym, MTD_PTP_Blk path, MTD_U16 port);
unsigned int mtd_get_asymmetry(MTD_PTP_Blk path, MTD_U16 port);
/* set ingress linkdelay */
MTD_STATUS mtd_set_link_delay(int ldelay, MTD_U16 port);


/*******************************************************************************
* mtd_new_ptp_init
*
* DESCRIPTION:
*        Completely Initialize new PTP block. It should be called bedore using any
*       new PTP function.
*
* INPUTS:
*        dev - point to device configuration 
*       port - port number
*       link_mode - 0-1G, 1-10G
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_new_ptp_init (MTD_DEV *dev, MTD_U16 port, int link_mode);

/*******************************************************************************
* mtd_new_ntp_init
*
* DESCRIPTION:
*        Completely Initialize new NTP block. It should be called bedore using any
*       new NTP function.
*
* INPUTS:
*        dev - point to device configuration 
*       port - port number
*       udp_src_port - second NTP source extend device number
*                      First extend device is 123, that is default on NTP standard.
*       udp_dst_port - second NTP destination extend device number
*                      First extend device is 123, that is default on NTP standard.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_new_ntp_init (MTD_DEV* dev, MTD_U16 port, int udp_src_port_2, int udp_dst_port_2, int link_mode);

/*******************************************************************************
* mtd_ptp_1step_config
*
* DESCRIPTION:
*        General function to set configuration for LUT
*
* INPUTS:
*       port - port number
*       mtd_ptp_cfg  - pointer to 1-step PTPconfiguration
*       numIngLut - number of ingress Lut
*       numEgLut - number of Egress Lut
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_1step_config(MTD_U16 port, MTD_PTP_1STEP_CFG *mtd_ptp_cfg, int numIngLut, int numEgLut);

/*******************************************************************************
* mtd_ptp_set_tai_clk_mode
*
* DESCRIPTION:
*   Set TAI TOD cfg general 
*   clk_mode: 1: clock generation, 2: clock reception, 3: clock reception adv 
*
* INPUTS:
*       port - port number
*       clk_mode - clk_mode: 
*          1: clock generation, 2: clock reception, 3: clock reception adv 
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Set TAI TOD cfg gen */
/* clk_mode: 1: clock generation, 2: clock reception, 3: clock reception adv */
MTD_STATUS mtd_ptp_set_tai_clk_mode
(
   IN MTD_U16 port, 
   IN int clk_mode
);

/*******************************************************************************
* mtd_ptp_set_clock_cyc
*
* DESCRIPTION:
*         Set clock cycle
*        Due to rtl incompleteness, cyc_ns need to be 0,  
*        and cyc_s needs to be 2 
*
* INPUTS:
*       port - port number
*       cyc_s  - clock cycle seconds
*       cyc_ns - clock cycle nanoseconds
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* Set clock cycle */
/* Due to rtl incompleteness, cyc_ns need to be 0,  */
/* and cyc_s needs to be 2 */
MTD_STATUS mtd_ptp_set_clock_cyc
(
  IN MTD_U16 port,
  IN unsigned int cyc_s,
  IN unsigned int cyc_ns
);

/*******************************************************************************
* mtd_ptp_go_clock_gen
*
* DESCRIPTION:
*         clock generation setup
*
* INPUTS:
*       port - port number
*       ntTime - next rise time
*       cyc - clock cycle
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* clock generation setup */
MTD_STATUS mtd_ptp_go_clock_gen 
(
  IN MTD_U16 port,
  IN MTD_NPTP_TIME_STRUCT *ntTime,
  IN MTD_NPTP_TIME_STRUCT *cyc
);

/*******************************************************************************
* mtd_ptp_go_clock_rec
*
* DESCRIPTION:
*         clock reception setup 
*
* INPUTS:
*       port - port number
*       todTime - TOD time
*       ntTime - next rise time
*       cyc - clock cycle
*       deley - clock propagation delay
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* clock reception setup */
MTD_STATUS mtd_ptp_go_clock_rec 
(
  IN MTD_U16 port,
  IN MTD_NPTP_TIME_STRUCT *todTime,
  IN MTD_NPTP_TIME_STRUCT *ntTime,
  IN MTD_NPTP_TIME_STRUCT *cyc,
  IN unsigned int delay
);

/*******************************************************************************
* mtd_ptp_set_pclk_period
*
* DESCRIPTION:
*         set pclk period
*
* INPUTS:
*       port - port number
*       period - pclk period
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* set pclk period */
MTD_STATUS mtd_ptp_set_pclk_period 
(
  IN MTD_U16 port,
  IN int period
);

/*******************************************************************************
* mtd_ptp_set_tai
*
* DESCRIPTION:
*         Set TAI TOD cfg 
*
* INPUTS:
*       port - port number
*       clk_mode - 
*       in_clk_en - 
*       tai_clkout_sel - 
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_set_tai 
(
  IN MTD_U16 port,
  IN int clk_mode,
  IN int in_clk_en,
  IN int tai_clkout_sel
);

/*******************************************************************************
* mtd_ptp_go_pulse_gen
*
* DESCRIPTION:
*         pulse generation setup (master)
*
* INPUTS:
*       port - port number
*       width_ns - width nanoseconds
*       trigsec - trigger time seconds
*       trignsec - trigger time nenoseconds
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* pulse generation setup (master) */
MTD_STATUS mtd_ptp_go_pulse_gen (MTD_U16 port, int width_ns, int trigsec, int trignsec);

/*******************************************************************************
* mtd_ptp_go_pulse_rec
*
* DESCRIPTION:
*         pulse reception setup (slave) 
*
* INPUTS:
*       port - port number
*       delay - Pulse delay time 
*       nextTime - Next Rise time 
*       ldTime - load time 
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* pulse reception setup (slave) */
MTD_STATUS mtd_ptp_go_pulse_rec (MTD_U16 port, int delay, MtdPtpTimeStruct *nextTime, MtdPtpTimeStruct * ldTime);


/* PTP Interrupt */
/*******************************************************************************
* mtd_set_ptp_intr_msk
*
* DESCRIPTION:
*         Set new PTP interrupt mask.
*
* INPUTS:
*       port - port number
*       path  - NewPtp block number: igr or egr.
*       mask  - New PTP interrupt mask.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_set_ptp_intr_msk ( MTD_U16 port, MTD_PTP_Blk path, unsigned int mask);

/*******************************************************************************
* mtd_get_ptp_interrupts
*
* DESCRIPTION:
*         Get new PTP interrupts.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        igrInt - IGR interupts
*        egrInt - EGR interupts
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_interrupts (MTD_U16 port, unsigned int *igrInt, unsigned int *egrInt);

/*******************************************************************************
* mtd_ptp_set_drift_adj
*
* DESCRIPTION:
*       Clock drift adjustment
*
* INPUTS:
*       port - port number
*       drift_base_adj_sl - base drift adjust low sec
*       drift_base_adj_ns - base drift adjust ns (invlude sign)
*       drift_base_adj_fs - base drift adjust fs
*       drift_fine_adj_fs - fine drift adjust fs
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* set drift adjustment */
MTD_STATUS mtd_ptp_set_drift_adj
(
  IN MTD_U16 port,
  IN int drift_base_adj_sl,
  IN int drift_base_adj_ns,
  IN int drift_base_adj_fs,
  IN int drift_fine_adj_fs
);

/*******************************************************************************
* mtd_ptp_get_drift_adj
*
* DESCRIPTION:
*    Get clock drift adjustment
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       drift_base_adj_sl - base drift adjust low sec
*       drift_base_adj_ns - base drift adjust ns (invlude sign)
*       drift_base_adj_fs - base drift adjust fs
*       drift_fine_adj_fs - fine drift adjust fs
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* get drift adjustment */
MTD_STATUS mtd_ptp_get_drift_adj
(
  IN MTD_U16 port,
  OUT int *drift_base_adj_sl,
  OUT int *drift_base_adj_ns,
  OUT int *drift_base_adj_fs,
  OUT int *drift_fine_adj_fs
);

/*******************************************************************************
* mtd_ptp_dev_init
*
* DESCRIPTION:
*     Initialization of PTP block. 
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*       port - port number
*       link_mode - MTD running mode.
*
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_dev_init(void * dev, MTD_U16 port, int link_mode);

MTD_STATUS mtd_init_macsec (MTD_U16 port, int link_mode);

#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* __Mtd_Ptp_Api_h */






