/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/****************************************************************************//**
* \file mtdMsecApi.h
*
* DESCRIPTION:
*       Definitions for MacSec control API's
*
* DEPENDENCIES:
*
* FILE REVISION NUMBER:
*
*******************************************************************************/
#ifndef __mtdMsecApi_h
#define __mtdMsecApi_h

#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

#include "mtdMsecTypes.h"
#include "aes.h"
#include "mtdMsecPtpApiDefs.h"
#include "mtdApiTypes.h"
#include "mtdAPIInternal.h"
#include "mtdHwCntl.h"

#include "mtdMsecInternal.h"

/*****************************************************************************
* mtd_msec_ae_init
*
* DESCRIPTION:
*        Initialize AE core
*        Brings AE core out of reset and into a basic non-bypass configuration with all
*        traffic passing through the core.  In this state the core is ready to begin
*        encrypt and decrypt operations.
*
* INPUTS:
*        dev - pointer to MTD driver structure returned from mtdLoadDriver
*         port - port number
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
MTD_STATUS mtd_msec_ae_init
(
    IN  MTD_DEV     *dev,
    MTD_U16 port
);

/*****************************************************************************
* mtd_msec_set_fwd_mode
*
* DESCRIPTION:
*       set forward mode: 
*
* INPUTS:
*        dev - pointer to device handle
*         port - port number
*    fwd_mode - fowarding mode
*        - 2'b00= cut-through; 
*        - 2'b01=egr store-foward; 
*        - 2'b10=igr store-foward;
*        - 2'b11 = store-forward;
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
MTD_STATUS mtd_msec_set_fwd_mode(MTD_DEV *dev, MTD_U16 port, int fwd_mode);

/*****************************************************************************
*  mtd_msec_set_mac_power_mode
*
* DESCRIPTION:
   set mac power mode
*
* INPUTS:
*    dev - pointer to device handle
*    mode - 
*            MTD_MACSEC_POWER_MODE_POWEROFF     
*            MTD_MACSEC_POWER_MODE_RESET     
*            MTD_MACSEC_POWER_MODE_SLEEP      
*            MTD_MACSEC_POWER_MODE_ACTIVE    
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
void mtd_msec_set_mac_power_mode (MTD_DEV * devp, MTD_U16 port, MTD_MACSEC_POWER_MODE mode);

/*****************************************************************************
*  mtd_msec_get_mac_power_mode
*
* DESCRIPTION:
   get mac power mode
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
* 
* OUTPUTS:
*    mode - 
*            MTD_MACSEC_POWER_MODE_POWEROFF     
*            MTD_MACSEC_POWER_MODE_RESET     
*            MTD_MACSEC_POWER_MODE_SLEEP      
*            MTD_MACSEC_POWER_MODE_ACTIVE    
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
int mtd_msec_get_mac_power_mode (MTD_DEV * dev, MTD_U16 port, MTD_MACSEC_POWER_MODE *mode);

/*****************************************************************************
*  mtd_set_mac_speed
*
* DESCRIPTION:
   set mac link speed
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    mac_type - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    speed - link speed : 0 - MTD_GMII, 1 - MTD_XGMII
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
MTD_STATUS mtd_set_mac_speed (MTD_DEV *dev, MTD_U16 port, int mac_type,int speed);

/*****************************************************************************
*  mtd_msec_mac_init
*
* DESCRIPTION:
*   initialize mac with specified speed
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    speed - wmac and smac link speed
*       - 0 1G-1G symmetric speed
*       - 1 10G-10G symmetric speed
*       - 2 1G-10G asymmetric speed
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
MTD_STATUS mtd_msec_mac_init(MTD_DEV *dev, MTD_U16 port, int speed);

/*****************************************************************************
*  mtd_msec_set_mac_framesize
*
* DESCRIPTION:
*   set mac frame size
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    size - frame size
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
/* mactype: MTD_SMAC=0, MTD_WMAC=1 */
MTD_STATUS mtd_msec_set_mac_framesize (MTD_DEV *dev, MTD_U16 port, int mactype, int size);

/*****************************************************************************
*  mtd_msec_set_10g_mac_pause_fwd
*
* DESCRIPTION:
*   set 10G mac MACsec pause forwarding
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    flag - pause forwarding flag: 1 = forward pause, 0 = No forward pause
* 
* OUTPUTS:
*    None
*
* RETURNS:
*    MTD_OK          - on success
*    MTD_FAIL        - on error
*
* COMMENTS:
*    Enable pause forwarding on SMAC or WMAC when link speed is 10G,5G and 
*    2.5G. This API does not apply to 1G and lower speed.
*    
*    By default, when flow control is not enabled, pause frames are 
*    terminated in MAC.
*
*    When flow control is not enabled, pause frames can be forwarded this 
*    flag is set
*
*    When flow control is enabled, pause frames are terminated regardless of 
*    setting of this flag.
*******************************************************************************/
MTD_STATUS mtd_msec_set_10g_mac_pause_fwd 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT mactype, 
    MTD_INT flag
);

/*****************************************************************************
*  mtd_msec_get_10g_mac_pause_fwd
*
* DESCRIPTION:
*   get 10G mac MACsec pause forwarding setting
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
* 
* OUTPUTS:
*    flag - pause forwarding flag: 1 = forward pause, 0 = No forward pause
*
* RETURNS:
*    MTD_OK          - on success
*    MTD_FAIL        - on error
*
* COMMENTS:
*    The pause forwarding on SMAC or WMAC is only available when link speed is 
*    10G, 5G and 2.5G. This API does not apply to 1G and lower speed.
*******************************************************************************/
MTD_STATUS mtd_msec_get_10g_mac_pause_fwd 
(
    MTD_DEV *dev, 
    MTD_U16 port, 
    MTD_INT mactype, 
    MTD_INT *flag
);

/*****************************************************************************
*  mtd_msec_set_sym_flow_ctrl
*
* DESCRIPTION:
*   set mac symmetric flow control
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    flag - flow control flag: 0- disable, 1-enable
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
MTD_STATUS mtd_msec_set_sym_flow_ctrl(MTD_DEV *dev, MTD_U16 port, int flag);

/*****************************************************************************
*  mtd_msec_set_asym_flow_ctrl
*
* DESCRIPTION:
*   set mac asymmetric flow control
*   Asymetric flow control only set flow control on one MAC side, not both side. 
*   mac_type 1 - smac, 2 - wmac 
*   It's mainly used for a port operating in Asymmetric speed 10G-1G, flow control shall be enabled
*   on 10G side.
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    mactype  -  1 - smac, 2 - wmac 
*    flag - flow control flag: 0- disable, 1-enable
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
MTD_STATUS mtd_msec_set_asym_flow_ctrl(MTD_DEV *dev, MTD_U16 port, int mactype, int flag);

/*****************************************************************************
*  mtd_msec_set_priority_flow_ctrl
*
* DESCRIPTION:
   Set priority flow control: qos_def_class, qos_stats_en, qbb_en, x_drop_en 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    flag - flow control flag: 0- disable, 1-enable
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
MTD_STATUS mtd_msec_set_priority_flow_ctrl(MTD_DEV *dev, MTD_U16 port, int flag);

/*****************************************************************************
*  mtd_msec_get_etm_ent
*
* DESCRIPTION:
*   get ETM entry
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    ent_num - entry number
* 
* OUTPUTS:
*    etm - structure of MTD_ETM_T
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_etm_ent (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_ETM_T *etm);

/*****************************************************************************
*  mtd_msec_set_egr_gen_pn_roll_over
*
* DESCRIPTION:
*   when pn is saturated, it is allowed to roll over pn by setting
*    this bit 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    ro - rollover flag
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
MTD_STATUS mtd_msec_set_egr_gen_pn_roll_over(MTD_DEV *dev, MTD_U16 port, int ro);

/*****************************************************************************
*  mtd_msec_path_soft_reset
*
* DESCRIPTION:
*   egress and ingress path soft reset 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    rs - reset flag
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
MTD_STATUS mtd_msec_path_soft_reset(MTD_DEV *dev, MTD_U16 port, int rs);

/*****************************************************************************
*  mtd_msec_set_bypass_macsec
*
* DESCRIPTION:
*   bypass MACsec on both egress and ingress path 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    bp - bypass flag
*       1 - bypass MACsec 
*       0 - enable MACsec 
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
MTD_STATUS mtd_msec_set_bypass_macsec(MTD_DEV *dev, MTD_U16 port, int bp);

/*****************************************************************************
*  mtd_msec_set_igr_scb_port
*
* DESCRIPTION:
*   set ingress scb port
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    scb_p - scb port
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
MTD_STATUS mtd_msec_set_igr_scb_port(MTD_DEV *dev, MTD_U16 port, MTD_U32 scb_p);

/*****************************************************************************
*  mtd_msec_set_igr_implicit_sci
*
* DESCRIPTION:
*   set ingress implicit SCI
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    sci_hi - higher 32 bits of SCI (63:32)
*    sci_lo - lower 32 bits of SCI (31:0)
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
MTD_STATUS mtd_msec_set_igr_implicit_sci(MTD_DEV *dev, MTD_U16 port, MTD_U32 sci_hi, MTD_U32 sci_lo);

/*****************************************************************************
*  mtd_msec_set_igr_chk_slide_wind
*
* DESCRIPTION:
*   Set ingress CHK CTL sliding window 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    flag - sliding window flag
*        0- disable, 1 - enable 
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
MTD_STATUS mtd_msec_set_igr_chk_slide_wind(MTD_DEV *dev, MTD_U16 port, int flag);

/*****************************************************************************
*  mtd_msec_set_igr_chk_validate_frames
*
* DESCRIPTION:
*   Ingress CHK CTL Validate frames setting 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    flag - sliding window flag
*      - 0 - disable
*      - 1 - check
*      - 2 - strict 
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
MTD_STATUS mtd_msec_set_igr_chk_validate_frames(MTD_DEV *dev, MTD_U16 port, int flags);

/*****************************************************************************
*  mtd_msec_set_igr_chk_rpy_prot
*
* DESCRIPTION:
*   Ingress CHK CTL replay protect
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    flag - replay protect flag
*      - 0 - disable
*      - 1 - enable
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
MTD_STATUS mtd_msec_set_igr_chk_rpy_prot(MTD_DEV *dev, MTD_U16 port, int flag);
/*****************************************************************************
*  mtd_msec_set_igr_chk_act_en
*
* DESCRIPTION:
*   Ingress CHK CTL action enable
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    flag - action enable flag
*      - 0 - disable
*      - 1 - enable
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
MTD_STATUS mtd_msec_set_igr_chk_act_en(MTD_DEV *dev, MTD_U16 port, int flag);

/*****************************************************************************
*  mtd_msec_set_igr_gen_cfg
*
* DESCRIPTION:
*   set ingress general config
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    igr_gen - structure for ingress general config
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
MTD_STATUS mtd_msec_set_igr_gen_cfg(MTD_DEV *dev, MTD_U16 port, MTD_IGR_GEN_T *igr_gen);

/*****************************************************************************
*  mtd_msec_set_igr_nxtpn
*
* DESCRIPTION:
*   set ingress path next pn 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    ent_num - entry number
*    nxtpn - next pn
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
/* set ingress path next pn */
MTD_STATUS mtd_msec_set_igr_nxtpn(MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_U32 nxtpn);

/*****************************************************************************
*  mtd_msec_set_igr_rpy_wind
*
* DESCRIPTION:
*   set ingress path replay window 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    rpy - replay window
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
MTD_STATUS mtd_msec_set_igr_rpy_wind(MTD_DEV *dev, MTD_U16 port, MTD_U32 rpy);

/*****************************************************************************
*  mtd_msec_set_ect_pn
*
* DESCRIPTION:
*   set egress Context Front Table pn field
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    ent_num - entry number
*    pn - pn field
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
MTD_STATUS mtd_msec_set_ect_pn (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_U32 pn);

/*****************************************************************************
*  mtd_msec_set_ect_bk_ent_all
*
* DESCRIPTION:
*   set egress Context Back Table
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    asa - authentication stop field
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
MTD_STATUS mtd_msec_set_ect_bk_ent_all (MTD_DEV *dev, MTD_U16 port, MTD_U8 asa);

/*****************************************************************************
*  mtd_msec_set_egr_entry
*
* DESCRIPTION:
*   setup egress entry 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    ent_num - entry number
*    flag_en - bitmask for flag_en
*    flag_data - bitmask for flag_data
*    match_en - structure for match enable
*    match_fld - structure for match fields
*    ect - structure for context entry
*    act_fld - structure for action field
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
MTD_STATUS mtd_msec_set_egr_entry (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_U8 flag_en, 
                               MTD_U8 flag_data, MTD_MATCH_EN *match_en, MTD_MATCH_FLD* match_fld, 
                               MTD_CTX_T *ect, MTD_ACT_FLD *act_fld);
MTD_STATUS mtd_msec_set_egr_entry_atomic (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_U8 flag_en, 
                               MTD_U8 flag_data, MTD_MATCH_EN *match_en, MTD_MATCH_FLD* match_fld, 
                               MTD_CTX_T *ect, MTD_ACT_FLD *act_fld);

/*****************************************************************************
*  mtd_msec_set_igr_retain_hdr
*
* DESCRIPTION:
*   set ingress retain header
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    ent_num - entry number
*    retain_hdr - retain header flag
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
MTD_STATUS mtd_msec_set_igr_retain_hdr (MTD_DEV *dev, MTD_U16 port, int ent_num, int retain_hdr);

/*****************************************************************************
*  mtd_msec_set_igr_entry
*
* DESCRIPTION:
*   setup ingress entry 
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    ent_num - entry number
*    flag_en - bitmask for flag_en
*    flag_data - bitmask for flag_data
*    match_en - structure for match enable
*    match_fld - structure for match fields
*    ect - structure for context entry
*    act_fld - structure for action field
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
/* setup ingress entry */
MTD_STATUS mtd_msec_set_igr_entry (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_U8 flag_en, MTD_U8 flag_data, 
                               MTD_MATCH_EN *match_en, MTD_MATCH_FLD* match_fld, MTD_CTX_T *ict, MTD_ACT_FLD *act_fld);
MTD_STATUS mtd_msec_set_igr_entry_atomic (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_U8 flag_en, MTD_U8 flag_data, 
                               MTD_MATCH_EN *match_en, MTD_MATCH_FLD* match_fld, MTD_CTX_T *ict, MTD_ACT_FLD *act_fld);

/*******************************************************************************
* mtd_msec_port_fips_chk
*
* DESCRIPTION:
*         Per Port FIPS Compliance Check 
*         It programs 128 bit input vector (Plain Text).
*         It    also programs key or hash key for egress or ingress path as defined by user.
*         For AES operation, Key[0] is programmed.
*         For GHASH operation, Hash Key[0] is programmed.
*        It triggers AES or GHASH operation and returns 128 bit output vector when operation is done.
*        After operation is done, It clears MTD_FIPS_CTL register.
*        It also toggles MACSEC core soft reset.
*
* INPUTS:
*       dev       - pointer to MTD driver structure returned from mtdLoadDriver
*       fips_cfg  - MTD_FIPS_CFG_T
*
* OUTPUTS:
*        fips_out  - 128 bits AES or GHASH observation vector output 
*                    (fips_out[3] -> [31:0], fips_out[0] -> [127:96])
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_port_fips_chk 
(
    IN  MTD_DEV        *dev,
    IN  MTD_U16 port,
    IN    MTD_FIPS_CFG_T    *fips_cfg,
    OUT MTD_U32    *fips_out
);

/*******************************************************************************
* mtd_msec_port_fips_ctl
*
* DESCRIPTION:
*            Per Port FIPS Control Setting
*            It programs key or hash key for egress or ingress path as defined by user.
*            For AES operation, Key[0] is programmed.
*            For GHASH operation, Hash Key[0] is programmed.
*            It triggers AES or GHASH operation.
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*       port - The port number
*        fips_cfg MTD_FIPS_CFG_T
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
MTD_STATUS mtd_msec_port_fips_ctl 
(
    IN  MTD_DEV        *dev,
    IN  MTD_U16 port,
    IN    MTD_FIPS_CFG_T    *fips_cfg
);

/*****************************************************************************
*  mtd_msec_set_intr_msk
*
* DESCRIPTION:
*   set macsec interrupt mask
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    msk - structure of MTD_MSEC_INT_T
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
MTD_STATUS mtd_msec_set_intr_msk(MTD_DEV *dev, MTD_U16 port, MTD_MSEC_INT_T *msk);

/*****************************************************************************
*  mtd_msec_get_intr
*
* DESCRIPTION:
  get macsec interrupt
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
* 
* OUTPUTS:
*    intr - structure of MTD_MSEC_INT_T
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_intr(MTD_DEV *dev, MTD_U16 port, MTD_MSEC_INT_T *intr);

/*****************************************************************************
*  mtd_msec_get_stats
*
* DESCRIPTION:
   read statistics value
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*    group - MTD_EGR_SEC, MTD_IGR_SEC,  MTD_SMAC_RX,  MTD_SMAC_TX, MTD_WMAC_RX, MTD_WMAC_TX 
* 
* OUTPUTS:
*    stats - statistics data
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_stats (MTD_DEV *dev, MTD_U16 port, int group, unsigned long long *stats);

/*****************************************************************************
*  mtd_msec_set_pcs_block_traffic
*
* DESCRIPTION:
*   set macsec pcs block trafic.
*
* INPUTS:
*    dev - pointer to device handle
*    flag - 0 clear, 1: set.
*    type - for 3240 type can be MTD_PATH_TYPE_LINE 
*                                MTD_PATH_TYPE_HOST 
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
MTD_STATUS mtd_msec_set_pcs_block_traffic(MTD_DEV *dev, MTD_U16 port, int flag, int type);

/*   */
/*****************************************************************************
*  mtd_msec_get_pn_full_intr
*
* DESCRIPTION:
*    get macsec pn full interrupt.
*    port - port number
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       intr value
*
* COMMENTS:
*
*******************************************************************************/
int  mtd_msec_get_pn_full_intr(MTD_DEV * dev, MTD_U16 port);
/*****************************************************************************
*  mtd_msec_get_nextpn_almost_intr
*
* DESCRIPTION:
*   get macsec nextpn almost interrupt.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       intr value
*
* COMMENTS:
*
*******************************************************************************/
int  mtd_msec_get_nextpn_almost_intr(MTD_DEV * dev, MTD_U16 port);
/*****************************************************************************
*  mtd_msec_get_nextpn_full_intr
*
* DESCRIPTION:
*   get macsec nextpn full interrupt.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       intr value
*
* COMMENTS:
*
*******************************************************************************/
int  mtd_msec_get_nextpn_full_intr(MTD_DEV * dev, MTD_U16 port);
/*****************************************************************************
*  mtd_msec_clr_pn_almost_full_intr
*
* DESCRIPTION:
*   clear macsec pn almost interrupt.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
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
MTD_STATUS  mtd_msec_clr_pn_almost_full_intr(MTD_DEV * dev, MTD_U16 port);
/*****************************************************************************
*  mtd_msec_clr_pn_full_intr
*
* DESCRIPTION:
*   clear macsec pn full interrupt.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
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
MTD_STATUS  mtd_msec_clr_pn_full_intr(MTD_DEV * dev, MTD_U16 port);
/*****************************************************************************
*  mtd_msec_clr_nxtpn_almost_full_intr
*
* DESCRIPTION:
*   clear macsec nxtpn almost full interrupt.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
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
MTD_STATUS  mtd_msec_clr_nxtpn_almost_full_intr(MTD_DEV * dev, MTD_U16 port);
/*****************************************************************************
*  mtd_msec_clr_nxtpn_full_intr
*
* DESCRIPTION:
*   clear macsec nxtpn full interrupt.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
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
MTD_STATUS  mtd_msec_clr_nxtpn_full_intr(MTD_DEV * dev, MTD_U16 port);

/*****************************************************************************
*  mtd_msec_force_1g_mac_ctl
*
* DESCRIPTION:
*   force macsec 1G mac control.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
* 
* OUTPUTS:
*        None
*
* RETURNS:
*        None
*
* COMMENTS:
*
*******************************************************************************/
void  mtd_msec_force_1g_mac_ctl(MTD_DEV * dev, MTD_U16 port);

/*****************************************************************************
*  mtd_msec_dis_elu_ent
*
* DESCRIPTION:
*    Disable ELU entrry.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    ent_num - entry number
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
MTD_STATUS mtd_msec_dis_elu_ent (MTD_DEV *dev, MTD_U16 port, int ent_num);
    
/*****************************************************************************
*  mtd_msec_dis_ilu_ent
*
* DESCRIPTION:
*    Disable ILU entrry.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    ent_num - entry number
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
void mtd_msec_dis_ilu_ent (MTD_DEV *dev, MTD_U16 port, int ent_num);
/*****************************************************************************
*  mtd_msec_clr_cam_tbl
*
* DESCRIPTION:
*    Clear CAM Table.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
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
MTD_STATUS mtd_msec_clr_cam_tbl(MTD_DEV * devp, MTD_U16 port);

/*******************************************************************************
* mtd_msec_get_intr_src
*
* DESCRIPTION:
*         Get new PTP interrupt source.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       intSrc  - New PTP interrupt source.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_intr_src (MTD_DEV *dev, MTD_U16 port, unsigned *intSrc);

/*******************************************************************************
* mtdPortSetMacsecBypass
*
* DESCRIPTION:
*       This routine set Port Macsec bypass.
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*       msecBypassMode - Macsec bypass state.
*            MTD_MACSEC_BYPASS_RESERVED     
*            MTD_MACSEC_BYPASS_RESET     
*            MTD_MACSEC_BYPASS_SLEEP      
*            MTD_MACSEC_BYPASS_ACTIVE    
*   
* OUTPUTS:
*       nothing.
*
* RETURNS:
*       MTD_OK   - on success
*       MTD_FAIL - on error
*
* COMMENTS:
*       Reg 31.f000, Bit 11 - 10 : Macsec state
*
*******************************************************************************/
MTD_STATUS mtdPortSetMacsecBypass
(
    IN  MTD_DEV     *dev,
    IN  MTD_U16     port,
    IN  MTD_MACSEC_BYPASS_MODE msecBypassMode
);

/*******************************************************************************
* mtdPortGetMacsecBypass
*
* DESCRIPTION:
*       This routine get Port Macsec Bypass.
*
* INPUTS:
*       dev  - pointer to MTD driver structure returned from mtdLoadDriver
*   
* OUTPUTS:
*       msecBypassMode - Macsec bypass state.
*            MTD_MACSEC_BYPASS_RESERVED     
*            MTD_MACSEC_BYPASS_RESET     
*            MTD_MACSEC_BYPASS_SLEEP      
*            MTD_MACSEC_BYPASS_ACTIVE    
*
* RETURNS:
*       MTD_OK   - on success
*       MTD_FAIL - on error
*
* COMMENTS:
*       Reg 31.f000, Bit 11 - 10 : Macsec state
*
*******************************************************************************/
MTD_STATUS mtdPortGetMacsecBypass
(
    IN   MTD_DEV     *dev,
    IN   MTD_U16     port,
    OUT  MTD_MACSEC_BYPASS_MODE *msecBypassMode
);

/* # when this bit is set, macsec stats is cleared when a PHY soft reset is applied.  */
/*****************************************************************************
*  mtd_mac_clr_stats_on_reset
*
* DESCRIPTION:
*  Mac clear stats on reset.
*
* INPUTS:
*    port - port number
* 
* OUTPUTS:
*        None
*
* RETURNS:
*        None
*
* COMMENTS:
*
*******************************************************************************/
void mtd_mac_clr_stats_on_reset(MTD_U16 port, int flag);
/*******************************************************************************
* mtd_set_frag_drop_size
*
* DESCRIPTION:
*         Set frag drop size.
*
* INPUTS:
*       port - port number
*       size - frag drop size
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
MTD_STATUS mtd_set_frag_drop_size (MTD_U16 port, int size);
/*******************************************************************************
* mtd_get_frag_drop_size
*
* DESCRIPTION:
*         Get frag drop size.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        None
*
* RETURNS:
*       size - frag drop size
*
* COMMENTS:
*
*******************************************************************************/
unsigned int  mtd_get_frag_drop_size(MTD_U16 port);
/*****************************************************************************
*  mtd_macsec_clr_stats_on_reset
*
* DESCRIPTION:
*  macsec clear stats on reset.
*
* INPUTS:
*     port - port number
* 
* OUTPUTS:
*        None
*
* RETURNS:
*        None
*
* COMMENTS:
*
*******************************************************************************/
void mtd_macsec_clr_stats_on_reset(MTD_U16 port, int flag);
/*****************************************************************************
*  mtd_msec_set_delay_ext_reset
*
* DESCRIPTION:
*   set delay external reset
*
* INPUTS:
*    dev - pointer to device handle
*     port - port number
*     flag - 1: enable    0: disable   
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_API_MACSEC_NOT_SUPPORT        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_delay_ext_reset(MTD_DEV *dev, MTD_U16 port, int flag);

/*****************************************************************************
*  mtd_msec_set_egr_flow_ctrl_drop_thrh
*
* DESCRIPTION:
*  macsec set egress flow control drop threshold.
*
* INPUTS:
*    devp - pointer to device handle
*    port - port number
*    thrh_h - threshold high
*    thrh_l - threshold low
*    enableFlag - 0:disabled; 1:enabled
* 
* OUTPUTS:
*        None
*
* RETURNS:
*        None
*
* COMMENTS:
*
*******************************************************************************/
void mtd_msec_set_egr_flow_ctrl_drop_thrh 
(
    MTD_DEV * devp, 
    MTD_U16 port, 
    MTD_INT thrh_h, 
    MTD_INT thrh_l,
    MTD_INT enableFlag
);

/*****************************************************************************
*  mtd_msec_set_igr_flow_ctrl_drop_thrh
*
* DESCRIPTION:
*  macsec set igress flow control drop threshold.
*
* INPUTS:
*    devp - pointer to device handle
*    port - port number
*    thrh_h64 - threshold high; threshold in units of 64B
*    thrh_l64 - threshold low; threshold in units of 64B
*    thrh_h32 - threshold high; threshold in units of 32B
*    thrh_l32 - threshold low; threshold in units of 32B
*    enableFlag - 0:disabled; 1:enabled
* 
* OUTPUTS:
*
* RETURNS:
*
* COMMENTS:
*
*******************************************************************************/
void mtd_msec_set_igr_flow_ctrl_drop_thrh
(
    MTD_DEV * devp, 
    MTD_U16 port, 
    MTD_INT thrh_h64, 
    MTD_INT thrh_l64, 
    MTD_INT thrh_h32, 
    MTD_INT thrh_l32,
    MTD_INT enableFlag
);

/*****************************************************************************
*  mtd_msec_set_egr_xoff_xon_threshold
*
* DESCRIPTION:
*    set macsec egress drop buffer XOFF and XON threshold
*    
* INPUTS:
*    devp - pointer to device handle
*    port - port number
*    xoff_thrh - XOFF egress drop buffer threshold; threshold in units of 64B
*    xon_thrh - XON egress drop buffer threshold; threshold in units of 64B
* 
* OUTPUTS:
*
* RETURNS:
*       MTD_OK    - on success
*       MTD_FAIL  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_egr_xoff_xon_threshold
(
    MTD_DEV *devp, 
    MTD_U16 port, 
    MTD_INT xoff_thrh, 
    MTD_INT xon_thrh
);

/*****************************************************************************
*  mtd_msec_set_igr_xoff_xon_threshold
*
* DESCRIPTION:
*    set macsec ingress drop buffer XOFF and XON threshold
*    
* INPUTS:
*    devp - pointer to device handle
*    port - port number
*    xoff_thrh - XOFF ingress drop buffer threshold; threshold in units of 64B
*    xon_thrh - XON ingress drop buffer threshold; threshold in units of 64B
* 
* OUTPUTS:
*
* RETURNS:
*       MTD_OK    - on success
*       MTD_FAIL  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_igr_xoff_xon_threshold
(
    MTD_DEV *devp, 
    MTD_U16 port, 
    MTD_INT xoff_thrh, 
    MTD_INT xon_thrh
);

/*****************************************************************************
*  mtd_msec_periodic_pause
*
* DESCRIPTION:
*     Function to enable or disable the periodic pause trigger timer
*
* INPUTS:
*     devp - pointer to device handle
*     port - port number
*     sel  - 1:enable  0:disable
* 
* OUTPUTS:
*     None
*
* RETURNS:
*     MTD_OK    - on success
*     MTD_FAIL  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_periodic_pause
(
    MTD_DEV *devp, 
    MTD_U16 port, 
    MTD_U16 sel
);

/*****************************************************************************
*  mtd_msec_set_mdio_watchdog_timer
*
* DESCRIPTION:
*  macsec set mdio watchdog timer.
*
* INPUTS:
*     port - port number
*    mode - watchdog timer mode
*    cycle - timeout value in cycle
* 
* OUTPUTS:
*        None
*
* RETURNS:
*        None
*
* COMMENTS:
*
*******************************************************************************/
void mtd_msec_set_mdio_watchdog_timer (MTD_DEV * devp, MTD_U16 port, int mode, int cycle);

/*****************************************************************************
*  mtd_msec_set_10g_mac_ipgMode_ipgVal
*
* DESCRIPTION:
*  This function sets both the 10G Tx Inter-Packet gap mode and value
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    ipgMode - inter-packet gap mode 
*              0 = LAN PHY: Maintains a Deficit Idle Count (DIC), which is 
*                  used to decide whether to add or delete idle characters and 
*                  maintain an average IPG 96BT to 192BT, in steps of 32BT.
*              1 = WAN PHY: IPG is stretched to adopt to OC-192 speed.
*              2 = Fixed IPG: Fixed IPG LAN mode. Adds up to three idle 
*                  symbols to <FixedIPGBase>, to align the start symbol to lane 0.
*    macType - 1:SMAC  2:WMAC
*    ipgVal - inter-packet gap value
*             The IPG base used to calculate the IPG when <TxIPGIMode> = 2.
*             12 = Fixed IPG uses 12 bytes as the base IPG.
*             if value is not 12  = Fixed IPG uses 8 bytes as the base IPG.
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK  - on success
*       MTD_FAIL - on error
*       MTD_API_MACSEC_NOT_SUPPORT  - on error
*       MTD_MSEC_FAIL_PORT_GET_MAC_SPEED  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_10g_mac_ipgMode_ipgVal(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 ipgMode,
    IN MTD_U16 macType,
    IN MTD_U16 ipgVal); 

/*******************************************************************************
* mtd_msec_get_10g_mac_ipg_mode
*
* DESCRIPTION:
*  Gets the 10G Tx Inter-Packet mode
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    macType - 1:SMAC  2:WMAC
* 
* OUTPUTS:
*    txIPGMode - inter-packet gap mode
*              0 = LAN PHY: Maintains a Deficit Idle Count (DIC), which is 
*                  used to decide whether to add or delete idle characters and 
*                  maintain an average IPG 96BT to 192BT, in steps of 32BT.
*              1 = WAN PHY: IPG is stretched to adopt to OC-192 speed.
*              2 = Fixed IPG: Fixed IPG LAN mode. Adds up to three idle 
*                  symbols to <FixedIPGBase>, to align the start symbol to lane 0.
*
* RETURNS:
*       MTD_OK  - on success
*       MTD_FAIL - on error
*       MTD_API_MACSEC_NOT_SUPPORT  - on error
*       MTD_MSEC_FAIL_PORT_GET_MAC_SPEED  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_10g_mac_ipg_mode(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    OUT MTD_U32 *txIPGMode);

/*******************************************************************************
* mtd_msec_get_10g_mac_ipg
*
* DESCRIPTION:
*  Gets the 10G Inter-Packet Gap Tx and Rx length
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    macType - 1:SMAC  2:WMAC
* 
* OUTPUTS:
*    fixedIPGByteSize - inter-packet gap Tx and Rx length
*                   12 = Fixed IPG uses 12 bytes as the base IPG.
*                   8  = Fixed IPG uses 8 bytes as the base IPG.
*
* RETURNS:
*       MTD_OK  - on success
*       MTD_FAIL - on error
*       MTD_API_MACSEC_NOT_SUPPORT  - on error
*       MTD_MSEC_FAIL_PORT_GET_MAC_SPEED  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_10g_mac_ipg(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    OUT MTD_U32 *fixedIPGByteSize);

/*******************************************************************************
* mtd_msec_set_10g_mac_preamble
*
* DESCRIPTION:
*  Sets the 10G Preamble Tx and Rx length in bytes of the minimal preamble 
*  supported for Tx and Rx packets.
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    macType - 1:SMAC  2:WMAC
*    preAmble - Length in bytes of the minimal preamble supported for Tx and Rx packets.
*              (Length including SFD and Start Symbol)
*              0 = 4 bytes min preamble for Tx and 4 bytes on Rx
*              1 = 4 bytes min preamble for Tx and 8 bytes on Rx
*              2 = 8 bytes min preamble for Tx and 4 bytes on Rx 
*              3 = 8 bytes min preamble for Tx and 8 bytes on Rx 
*
* OUTPUTS:
*    none
*
* RETURNS:
*       MTD_OK  - on success
*       MTD_FAIL - on error
*       MTD_API_MACSEC_NOT_SUPPORT  - on error
*       MTD_MSEC_FAIL_PORT_GET_MAC_SPEED  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_10g_mac_preamble(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    IN MTD_U16 preAmble);

/*******************************************************************************
* mtd_msec_get_10g_mac_preamble
*
* DESCRIPTION:
*  Gets the 10G Preamble Tx and Rx length
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    macType - 1:SMAC  2:WMAC
*
* OUTPUTS:
*    preAmble - Length in bytes of the minimal preamble supported for Tx and Rx packets.
*              (Length including SFD and Start Symbol)
*              0 = 4 bytes min preamble for Tx and 4 bytes on Rx
*              1 = 4 bytes min preamble for Tx and 8 bytes on Rx
*              2 = 8 bytes min preamble for Tx and 4 bytes on Rx 
*              3 = 8 bytes min preamble for Tx and 8 bytes on Rx 
*
* RETURNS:
*       MTD_OK  - on success
*       MTD_FAIL - on error
*       MTD_API_MACSEC_NOT_SUPPORT  - on error
*       MTD_MSEC_FAIL_PORT_GET_MAC_SPEED  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_10g_mac_preamble(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    OUT MTD_U32 *preAmble);

/*******************************************************************************
* mtd_msec_set_1g_mac_ipg
*
* DESCRIPTION:
*  Sets the minimal Inter-packet gap byte size for 1G mode
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    macType - 1:SMAC  2:WMAC
*    ipg - byte size of the Inter-packet gap value; default is 12 bytes
*
* OUTPUTS:
*    none
*
* RETURNS:
*       MTD_OK  - on success
*       MTD_FAIL - on error
*       MTD_API_MACSEC_NOT_SUPPORT  - on error
*       MTD_MSEC_FAIL_PORT_GET_MAC_SPEED  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_1g_mac_ipg(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    IN MTD_U16 ipg);

/*******************************************************************************
* mtd_msec_get_1g_mac_ipg
*
* DESCRIPTION:
*  Gets the minimal Inter-packet gap byte size for 1G mode
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    macType - 1:SMAC  2:WMAC
*
* OUTPUTS:
*    ipg - byte size of the Inter-packet gap value
*
* RETURNS:
*       MTD_OK  - on success
*       MTD_FAIL - on error
*       MTD_API_MACSEC_NOT_SUPPORT  - on error
*       MTD_MSEC_FAIL_PORT_GET_MAC_SPEED  - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_1g_mac_ipg(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port, 
    IN MTD_U16 macType,
    OUT MTD_U32 *ipg);


#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* __mtdMsecApi_h */
