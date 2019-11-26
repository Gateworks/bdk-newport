/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mtdMsecInternal.h
*
* DESCRIPTION:
*       Definitions for MacSec control API's
*
* DEPENDENCIES:
*
* FILE REVISION NUMBER:
*
*******************************************************************************/

#ifndef __MTDMSECINTERNAL_h
#define __MTDMSECINTERNAL_h
#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

#include "mtdMsecPtpApiDefs.h"
#include "mtdMsecTypes.h"
#include "aes.h"        

extern int MTD_DEBUG_MSEC_WRITE;
extern int MTD_DEBUG_MSEC_READ;
int mtd_msec_bits_write (MTD_U32 *data, int in_data, int bit_to, int bit_from);
int mtd_msec_bits_get (int in_data, int bit_to, int bit_from);
int mtd_aes_hkey (MTD_CTX_T *ctx);

MTD_STATUS _mtdMsecWritePortReg 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    IN  MTD_U32    data
);

MTD_STATUS _mtdMsecWritePortReg_64 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16    addr,
    IN  unsigned long    dataL,
    IN  unsigned long    dataH
);


MTD_STATUS _mtdMsecReadPortReg 
(
    IN  MTD_DEV    *dev,
    IN  MTD_U16    port,
    IN  MTD_U16   addr,
    OUT MTD_U32   *data
);

MTD_STATUS mtd_msec_dev_init(void * dev);

void mtd_msec_soft_reset(MTD_U16 port);
/*
# reset the sigba core on both egress and ingress
# then bring it out of reset
*/
void mtd_macsec_core_reset(MTD_U16 port);
MTD_STATUS mtd_disable_macsec_both(MTD_U16 port);
MTD_STATUS mtd_enable_macsec_both(MTD_U16 port);
MTD_STATUS mtd_disable_macsec_encrypt(MTD_U16 port);
MTD_STATUS mtd_disable_macsec_decrypt(MTD_U16 port);
MTD_STATUS mtd_enable_macsec_encrypt(MTD_U16 port);
MTD_STATUS mtd_enable_macsec_decrypt(MTD_U16 port);

void mtd_set_smac_aneg_en(MTD_U16 port, int mode);
void mtd_set_wmac_aneg_en(MTD_U16 port, int mode);


/*****************************************************************************
* mtd_msec_set_strip_add_crc
*
* DESCRIPTION:
*    set smac and wmac strip crc, add crc
*
* INPUTS:
*    dev - pointer to device handle
*    bmsk - bitmask for strip and add crc
*       - 4'b0000 = no strip or add crc; 
*       - 4'b1111 = strip and add crc on smac and wmac
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
MTD_STATUS mtd_msec_set_strip_add_crc(MTD_DEV *dev, MTD_U16 port, MTD_U8 bmsk);

/*****************************************************************************
*  mtd_msec_set_qos_stag
*
* DESCRIPTION:
*   set 802.1s ether-type 
*
* INPUTS:
*    dev - pointer to device handle
*    tag - 802.1s ether-type
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
MTD_STATUS mtd_msec_set_qos_stag(MTD_DEV *dev, MTD_U16 port, MTD_U16 tag);

/*****************************************************************************
* mtd_msec_set_qos_qtag
*
* DESCRIPTION:
   set 802.1q ether-type 
*
* INPUTS:
*    dev - pointer to device handle
*    tag - 802.1q ether-type
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
MTD_STATUS mtd_msec_set_qos_qtag(MTD_DEV *dev, MTD_U16 port, MTD_U16 tag);

/*****************************************************************************
* mtd_init_linkcrypt
*
* DESCRIPTION:
*   initialize linkcrypt
*
* INPUTS:
*    dev - pointer to device handle
*    macsec_mode 
*          - 1 to bypass
*          - 0 to enable
*    fwd_mode
*          - 0: cut-through
*          - 1: egress cut-through, ingress store-forward,
*          - 2: egress store-forward, ingress cut-through
*          - 3: store-forward
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
MTD_STATUS mtd_init_linkcrypt(MTD_DEV *dev, MTD_U16 port, int macsec_mode, int fwd_mode);

/*****************************************************************************
*  mtd_set_mac_MTU
*
* DESCRIPTION:
   set mac MTU
*
* INPUTS:
*    dev - pointer to device handle
*    mac - structure for mac with mac type and link speed
*    MTU - maximum frame size
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
MTD_STATUS mtd_set_mac_MTU (MTD_DEV *dev, MTD_U16 port, MTD_MAC_T *mac, int MTU);


/*****************************************************************************
*  mtd_msec_get_speed_status
*
* DESCRIPTION:
   get the MAC speed mode
*
* INPUTS:
*    dev - pointer to device handle
*    port - port number
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       -1  - on error
*       0   - 10M
*       1   - 100M
*       2   - 1G
*       3   - 10G
*
* COMMENTS:
*
*******************************************************************************/
int mtd_msec_get_speed_status(MTD_DEV *dev, MTD_U16 port, MTD_INT mactype);

/*****************************************************************************
*  mtd_msec_get_mac_xg_sel
*
* DESCRIPTION:
*   get mac speed mode
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
* 
* OUTPUTS:
*        None
*
* RETURNS:
*   speed mode:
*       1 - 10G, 0 - 1G 
*
* COMMENTS:
*
*******************************************************************************/
int mtd_msec_get_mac_xg_sel(MTD_DEV *dev, MTD_U16 port, int mactype);

/*****************************************************************************
*  mtd_msec_set_mac_loopback
*
* DESCRIPTION:
*   set mac loopback
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    flag - loopback flag
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
MTD_STATUS mtd_msec_set_mac_loopback(MTD_DEV *dev, MTD_U16 port, int mactype, int flag);

/*****************************************************************************
*  mtd_msec_set_mac_forward_fc
*
* DESCRIPTION:
*   Enable foR/Ward 802.3x flow control frames (instead of termination in port).
*
* INPUTS:
*    dev - pointer to device handle
*    mactype - mac type: 1 - MTD_SMAC, 2 -MTD_WMAC
*    en - 0: disable, 1: enable
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
MTD_STATUS mtd_msec_set_mac_forward_fc(MTD_DEV *dev, MTD_U16 port, int mactype, int en);

/*****************************************************************************
*  mtd_msec_set_etm_ent
*
* DESCRIPTION:
*   set ETM entry
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    etm - structure of MTD_ETM_T
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
MTD_STATUS mtd_msec_set_etm_ent (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_ETM_T *etm);

/*****************************************************************************
*  mtd_msec_set_etm_ent_igr_mode
*
* DESCRIPTION:
   get ETM entry ingress mode
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    igr_mode - ingress mode
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
MTD_STATUS mtd_msec_set_etm_ent_igr_mode (MTD_DEV *dev, MTD_U16 port, int ent_num, int igr_mode);

/*****************************************************************************
*  mtd_msec_set_etm_ent_egr_mode
*
* DESCRIPTION:
*   set ETM entry egress mode
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    egr_mode - egress mode
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
MTD_STATUS mtd_msec_set_etm_ent_egr_mode (MTD_DEV *dev, MTD_U16 port, int ent_num, int egr_mode);

/*****************************************************************************
*  mtd_msec_set_etm_ent_etype
*
* DESCRIPTION:
*   set ETM entry etype
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    etype - ether-type
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
MTD_STATUS mtd_msec_set_etm_ent_etype (MTD_DEV *dev, MTD_U16 port, int ent_num, int etype);

/*****************************************************************************
*  mtd_msec_set_egr_parser
*
* DESCRIPTION:
*   set egress parser
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_egr_parser(MTD_DEV *dev, MTD_U16 port);
MTD_STATUS mtd_msec_set_egr_parser_atomic(MTD_DEV *dev, MTD_U16 port);

/*****************************************************************************
*  mtd_msec_set_igr_parser
*
* DESCRIPTION:
*   set ingress parser
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_igr_parser(MTD_DEV *dev, MTD_U16 port);
MTD_STATUS mtd_msec_set_igr_parser_atomic(MTD_DEV *dev, MTD_U16 port);
/*****************************************************************************
*  mtd_msec_set_egr_rc
*
* DESCRIPTION:
*   set egress rewrite constructor
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_egr_rc (MTD_DEV *dev, MTD_U16 port);

/*****************************************************************************
*  mtd_msec_set_igr_rc
*
* DESCRIPTION:
*   set ingress rewrite constructor
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_igr_rc (MTD_DEV *dev, MTD_U16 port);

/*****************************************************************************
*  mtd_msec_set_egress_seca
*
* DESCRIPTION:
*   set egress security entry - obsolete
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_egress_seca (MTD_DEV *dev, MTD_U16 port, int seca_num);

/*****************************************************************************
*  mtd_msec_set_ingress_seca
*
* DESCRIPTION:
*   set ingress security entry - obsolete
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_ingress_seca (MTD_DEV *dev, MTD_U16 port, int seca_num);

/*****************************************************************************
*  mtd_msec_elu_init
*
* DESCRIPTION:
*   ELU init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_elu_init(MTD_DEV *dev, MTD_U16 port);

/*****************************************************************************
*  mtd_msec_ect_fr_init
*
* DESCRIPTION:
*   ECT front table init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_ect_fr_init(MTD_DEV *dev, MTD_U16 port);

/*****************************************************************************
*  mtd_msec_ect_bk_init
*
* DESCRIPTION:
*   ECT back table init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_ect_bk_init(MTD_DEV *dev, MTD_U16 port);

/*****************************************************************************
*  mtd_msec_ilu_init
*
* DESCRIPTION:
*   ILU init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_ilu_init(MTD_DEV *dev, MTD_U16 port);

/*****************************************************************************
*  mtd_msec_ict_fr_init
*
* DESCRIPTION:
*   ICT front table init
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_ict_fr_init(MTD_DEV *dev, MTD_U16 port);

/*****************************************************************************
* mtd_msec_set_egr_short_pkt_adj
*
* DESCRIPTION:
*   set egress short packet adjacency
*
* INPUTS:
*    dev - pointer to device handle
*    s_pkt_adj - short packet adjacency
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
MTD_STATUS mtd_msec_set_egr_short_pkt_adj(MTD_DEV *dev, MTD_U16 port, MTD_U8 s_pkt_adj);

/*****************************************************************************
*  mtd_msec_set_egr_short_pkt_sz
*
* DESCRIPTION:
   set short packet size 
*
* INPUTS:
*    dev - pointer to device handle
*    s_pkt_sz - short packet size
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
MTD_STATUS mtd_msec_set_egr_short_pkt_sz(MTD_DEV *dev, MTD_U16 port, MTD_U8 s_pkt_sz);

/*****************************************************************************
*  mtd_msec_set_egr_thr
*
* DESCRIPTION:
   set Egress threshold register 
*
* INPUTS:
*    dev - pointer to device handle
*    e_thr - transmit threshold for egress HYST FIFO
*    m_thr - transmit threshold for main data FIFO
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
MTD_STATUS mtd_msec_set_egr_thr(MTD_DEV *dev, MTD_U16 port, MTD_U8 e_thr, MTD_U8 m_thr);

/*****************************************************************************
*  mtd_msec_set_egr_gen_miss_act
*
* DESCRIPTION:
*    Egress Gen Register
*
* INPUTS:
*    dev - pointer to device handle
*    act - action field for missing lookup match packet:
*       2'b00 - bypass, 2'b01 drop, 2'b10 loopback
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
MTD_STATUS mtd_msec_set_egr_gen_miss_act(MTD_DEV *dev, MTD_U16 port, int act);

/*****************************************************************************
*  mtd_msec_set_egr_reset
*
* DESCRIPTION:
*   egress path soft reset 
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_egr_reset(MTD_DEV *dev, MTD_U16 port, int rs);

/*****************************************************************************
*  mtd_msec_set_igr_reset
*
* DESCRIPTION:
*   ingress path soft reset 
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_msec_set_igr_reset(MTD_DEV *dev, MTD_U16 port, int rs);

/*****************************************************************************
*  mtd_msec_set_clr_read
*
* DESCRIPTION:
*   Enable or disable clear-on-read statistics behavior 
*
* INPUTS:
*    dev - pointer to device handle
*    clr - clear flag
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
MTD_STATUS mtd_msec_set_clr_read(MTD_DEV *dev, MTD_U16 port, int clr);

/*****************************************************************************
*  mtd_msec_set_igr_short_pkt_sz
*
* DESCRIPTION:
*   set ingress short packet size 
*
* INPUTS:
*    dev - pointer to device handle
*    sz - short packet size
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
MTD_STATUS mtd_msec_set_igr_short_pkt_sz(MTD_DEV *dev, MTD_U16 port, int sz);

/*****************************************************************************
* mtd_msec_set_ict_trail_sz
*
* DESCRIPTION:
*   set ICT trail size 
*
* INPUTS:
*    dev - pointer to device handle
*    sz - trail size
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
MTD_STATUS mtd_msec_set_ict_trail_sz(MTD_DEV *dev, MTD_U16 port, int sz);

/*****************************************************************************
*  mtd_msec_set_igr_chk_act
*
* DESCRIPTION:
*   set ingress check action fields 
*
* INPUTS:
*    dev - pointer to device handle
*    igr_act - structure for ingress action fields
*      - 2'b00 - bypass
*      - 2'b01 - drop
*      - 2'b10 - redir 
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
MTD_STATUS mtd_msec_set_igr_chk_act(MTD_DEV *dev, MTD_U16 port, MTD_IGR_CHK_ACT_T *igr_act);

/*****************************************************************************
*  mtd_msec_get_igr_chk_act
*
* DESCRIPTION:
*   get ingress check action fields 
*
* INPUTS:
*    dev - pointer to device handle
* 
* OUTPUTS:
*      igr_act - structure for ingress action fields
*          - 2'b00 - bypass
*          - 2'b01 - drop
*          - 2'b10 - redir 
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_igr_chk_act (MTD_DEV *dev, MTD_U16 port, MTD_IGR_CHK_ACT_T *igr_act);

/*****************************************************************************
*  mtd_msec_set_igr_rpy_var
*
* DESCRIPTION:
*   set ingress path replay variable 
*
* INPUTS:
*    dev - pointer to device handle
*    rpy - replay variable
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
MTD_STATUS mtd_msec_set_igr_rpy_var (MTD_DEV *dev, MTD_U16 port, MTD_RPY_T *rpy);

/*****************************************************************************
*  mtd_msec_get_igr_rpy_var
*
* DESCRIPTION:
*   get ingress path replay variable 
*
* INPUTS:
*    dev - pointer to device handle
* 
* OUTPUTS:
*    rpy - replay variable
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_igr_rpy_var (MTD_DEV *dev, MTD_U16 port, MTD_RPY_T *rpy);

/*****************************************************************************
*  mtd_msec_set_ect_act_fld
*
* DESCRIPTION:
*   set egress Context Front Table action field
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
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
MTD_STATUS mtd_msec_set_ect_act_fld (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_ACT_FLD *act_fld);

/*****************************************************************************
*  mtd_msec_get_ect_act_fld
*
* DESCRIPTION:
*   get egress Context Front Table action field
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
* 
* OUTPUTS:
*    act_fld - structure for action field
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_ect_act_fld (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_ACT_FLD *act_fld);

/*****************************************************************************
*  mtd_msec_set_ect_front_ent
*
* DESCRIPTION:
*   set egress Context Front Table entry
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    ctx - structure for context entry
*    act_fld - action field
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
MTD_STATUS mtd_msec_set_ect_front_ent(MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_CTX_T *ctx, MTD_ACT_FLD *act_fld);

/*****************************************************************************
*  mtd_msec_set_ect_bk_ent
*
* DESCRIPTION:
*   set egress Context Back Table entry
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
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
MTD_STATUS mtd_msec_set_ect_bk_ent (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_U8 asa);

/*****************************************************************************
*  mtd_msec_get_igr_retain_hdr
*
* DESCRIPTION:
*   get ingress retain header
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
* 
* OUTPUTS:
*        None
*
* RETURNS:
*    retain_hdr - retain header flag
*
* COMMENTS:
*
*******************************************************************************/
int mtd_msec_get_igr_retain_hdr (MTD_DEV *dev, MTD_U16 port, int ent_num);

/*****************************************************************************
*  mtd_msec_set_ict_act_fld
*
* DESCRIPTION:
*   set ICT action field
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    act_fld - action field
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
MTD_STATUS mtd_msec_set_ict_act_fld (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_ACT_FLD *act_fld);

/*****************************************************************************
*  mtd_msec_get_ict_act_fld
*
* DESCRIPTION:
*   get ICT action field
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
* 
* OUTPUTS:
*    act_fld - structure for action field
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_get_ict_act_fld (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_ACT_FLD *act_fld);

/*****************************************************************************
*  mtd_msec_set_ict_front_ent
*
* DESCRIPTION:
   set ICT front entry
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    ctx - structure for context fields
*    act_fld - action field
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
MTD_STATUS mtd_msec_set_ict_front_ent(MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_CTX_T *ctx, MTD_ACT_FLD *act_fld);

/*****************************************************************************
*  mtd_msec_set_elu_match_en
*
* DESCRIPTION:
*   set ELU match enable
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    match_en - structure for match enable
*    flag_en - flag enable bits
*    flag_data - flag data bits
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
MTD_STATUS mtd_msec_set_elu_match_en (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_MATCH_EN *match_en, MTD_U8 flag_en, MTD_U8 flag_data);

/*****************************************************************************
*  mtd_msec_set_elu_match_data
*
* DESCRIPTION:
*   set ELU match data
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    match_fld - structure for match data fields
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
MTD_STATUS mtd_msec_set_elu_match_data(MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_MATCH_FLD * match_fld);

/*****************************************************************************
*  mtd_msec_cfg_egr_pmask
*
* DESCRIPTION:
*   set egress parser mask eg. from_bit 140, to_bit 143 to mask off CFI bits of
*   vlan
*
* INPUTS:
*    dev - pointer to device handle
*    flag - bitmask data
*    to_bit - to bit
*    from_bit - from bit
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
MTD_STATUS mtd_msec_cfg_egr_pmask(MTD_DEV *dev, MTD_U16 port, int flag, int to_bit, int from_bit);

/*****************************************************************************
*  mtd_msec_set_elu_ent
*
* DESCRIPTION:
*    Program ELU Table Entry
*
* INPUTS:
*    dev Device ID
*    ent_num Lookup table entry number (0-31)
*    flag_en 8-bit bit field enabling match on particular packet types
*    flag_data 8-bit bit field showing value to match on.
   - 0: Match on flag not set
   - 1: Match on flag set
*    match_en structure enabling match on particular fields in the packet
*    match_fld structure containing values to be matched against packet fields
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
MTD_STATUS mtd_msec_set_elu_ent(MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_U8 flag_en, MTD_U8 flag_data, MTD_MATCH_EN *match_en, MTD_MATCH_FLD* match_fld);

/*****************************************************************************
*  mtd_msec_set_ilu_match_en
*
* DESCRIPTION:
*   set ILU match enable
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    match_en - structure for match enable
*    flag_en - flag enable bits
*    flag_data - flag data bits
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
MTD_STATUS mtd_msec_set_ilu_match_en (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_MATCH_EN *match_en, MTD_U8 flag_en, MTD_U8 flag_data);

/*****************************************************************************
*  mtd_msec_set_ilu_match_data
*
* DESCRIPTION:
*  set ILU match data
* according to IPR Output Parse Vector bitmap *
* ~~~~~~~~~~ IPR defines   ~~~~~~~~~~
*   define ENV_IPR_SCI          63:0
*   define ENV_IPR_PN           95:64
*   define ENV_IPR_SL           103:96
*   define ENV_IPR_TCI          111:104
*   define ENV_IPR_PHDR         143:128
*   define ENV_IPR_ETH          159:144
*   define ENV_IPR_MACSA        207:160
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    match_fld - structure for match data fields
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
MTD_STATUS mtd_msec_set_ilu_match_data(MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_MATCH_FLD * match_fld);

/*****************************************************************************
*  mtd_msec_cfg_igr_pmask
*
* DESCRIPTION:
*   set igress parser mask eg. from_bit 109, to_bit 112
*       flag: 0 - clear, 1 - set
*
*
* INPUTS:
*    dev - pointer to device handle
*    flag - bitmask data
*    to_bit - to bit
*    from_bit - from bit
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
MTD_STATUS mtd_msec_cfg_igr_pmask(MTD_DEV *dev, MTD_U16 port, int flag, int to_bit, int from_bit);

/*****************************************************************************
*  mtd_msec_set_ilu_ent
*
* DESCRIPTION:
*   Program ILU Table Entry
*
* INPUTS:
*    dev Device ID
*    ent_num Lookup table entry number (0-31)
*    flag_en 8-bit bit field enabling match on particular packet types
*    flag_data 8-bit bit field showing value to match on.
*       - 0: Match on flag not set
*       - 1: Match on flag set
*    match_en structure enabling match on particular fields in the packet
*    match_fld structure containing values to be matched against packet fields
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
MTD_STATUS mtd_msec_set_ilu_ent(MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_U8 flag_en, MTD_U8 flag_data, MTD_MATCH_EN *match_en, MTD_MATCH_FLD* match_fld);

/*****************************************************************************
*  mtd_port_fips_obv
*
* DESCRIPTION:
*   FIPS observation
*
* INPUTS:
*    dev - pointer to device handle
*    fips_cfg - structure of MTD_FIPS_CFG_T
* 
* OUTPUTS:
*    fips_out - FIPs output data
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_port_fips_obv (MTD_DEV *dev, MTD_U16 port, MTD_FIPS_CFG_T *fips_cfg, MTD_U32 *fips_out);

/*****************************************************************************
*  mtd_clear_fips_vec
*
* DESCRIPTION:
*   clear FIPS vector
*
* INPUTS:
*    dev - pointer to device handle
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
MTD_STATUS mtd_clear_fips_vec (MTD_DEV *dev, MTD_U16 port);

/*******************************************************************************
* mtd_msec_set_fips_vec
*
* DESCRIPTION:
*            FIPS Vector setting
*            It programs 128 bit input vector (Plain Text).
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
MTD_STATUS mtd_msec_set_fips_vec 
(
    IN  MTD_DEV        *dev,
    IN  MTD_U16 port,
    IN    MTD_FIPS_CFG_T    *fips_cfg
);

/*****************************************************************************
*  mtd_msec_set_fips_key_in
*
* DESCRIPTION:
*   set FIPS encryption decryption key
*
* INPUTS:
*    dev - pointer to device handle
*    fips_cfg - structure of MTD_FIPS_CFG_T
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
MTD_STATUS mtd_msec_set_fips_key_in 
(
    IN  MTD_DEV        *dev,
    IN  MTD_U16 port,
    IN    MTD_FIPS_CFG_T    *fips_cfg
);

/*****************************************************************************
*  mtd_msec_get_egr_stats_val_lo
*
* DESCRIPTION:
*   Get egress individual statistics value Lower 32bits counter
*   ent_num only applies to per-entry based statistics
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    stat_idx - index for ENUM MTD_MSEC_EGR_STAT_E
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       stats_lo - egress individual statistics value Lower 32bits counter       
*
* COMMENTS:
*
*******************************************************************************/
MTD_U32 mtd_msec_get_egr_stats_val_lo (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_MSEC_EGR_STAT_E stat_idx);

/*****************************************************************************
*
* DESCRIPTION:
*   Get egress individual statistics value higer 16 bits counter
*   ent_num only applies to per-entry based statistics
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    stat_idx - index for ENUM MTD_MSEC_EGR_STAT_E
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       stats_hi - egress individual statistics value higer 16 bits counter
*
* COMMENTS:
*
*******************************************************************************/
MTD_U16 mtd_msec_get_egr_stats_val_hi (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_MSEC_EGR_STAT_E stat_idx);

/*****************************************************************************
* mtd_msec_get_igr_stats_val_lo
*
* DESCRIPTION:
*   Get ingress individual statistics value Lower 32bits counter
*   ent_num only applies to per-entry based statistics
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    stat_idx - index for ENUM MTD_MSEC_IGR_STAT_E
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       stats_lo - ingress individual statistics value Lower 32bits counter
*
* COMMENTS:
*
*******************************************************************************/
MTD_U32 mtd_msec_get_igr_stats_val_lo (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_MSEC_IGR_STAT_E stat_idx);

/*************************************************************************
*  mtd_msec_get_igr_stats_val_hi
*
* DESCRIPTION:
*   Get ingress individual statistics value higer 16 bits counter
*   ent_num only applies to per-entry based statistics
*
* INPUTS:
*    dev - pointer to device handle
*    ent_num - entry number
*    stat_idx - index for ENUM MTD_MSEC_IGR_STAT_E
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       stats_hi - ingress individual statistics value higer 16 bits counter
*
* COMMENTS:
*
*******************************************************************************/
MTD_U16 mtd_msec_get_igr_stats_val_hi (MTD_DEV *dev, MTD_U16 port, int ent_num, MTD_MSEC_IGR_STAT_E stat_idx);

MTD_STATUS mtd_msec_set_egr_pn_rollover (MTD_DEV * dev, MTD_U16 port, int flag);
int  mtd_msec_get_pn_almost_full_intr(MTD_DEV * dev, MTD_U16 port);

/*
# default preamble setting for 10G mode is 4B, shall set to 8B 
# flag 1 - 8B preamble, 0 - 4B preamble
*/
void  mtd_msec_set_10g_mac_ctl_preamble_rx(MTD_DEV * dev, MTD_U16 port, int flag);
void mtd_msec_dis_ilu_ent (MTD_DEV *dev, MTD_U16 port, int ent_num);
/*# MTD_GMII - 1Gbps, MTD_XGMII - 10Gbps*/
int mtd_msec_get_smac_xg_sel (MTD_DEV * dev, MTD_U16 port);
/*# MTD_GMII - 1Gbps, MTD_XGMII - 10Gbps*/
int mtd_msec_get_wmac_xg_sel (MTD_DEV * dev, MTD_U16 port);
MTD_STATUS mtd_msec_set_local_fault_fwd(MTD_DEV * dev, MTD_U16 port, int flag);

/*****************************************************************************
*  mtd_msec_set_link_down_reset
*
* DESCRIPTION:
*  set macsec link down reset
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
    Workaround for MACsec lockup issue. When link down reset bit is set, it holds MACsec data path 
    under resets for a couple of cycles whenever there is a link down event. Side effect occurs when 
    resetting the data path; the MACsec table registers are also held for reset, causing register access
    failure during the reset. To avoid this side effect, clears the reset bits before any MACsec register 
    access, then set the reset bits after that.  This workaround is required for all macsec enabled parts. 

*
*******************************************************************************/
MTD_STATUS mtd_msec_set_link_down_reset(MTD_DEV *dev, MTD_U16 port, int flag);

/*****************************************************************************
*  mtd_msec_set_link_down_detect
*
* DESCRIPTION:
*   set macsec link down detect
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
MTD_STATUS mtd_msec_set_link_down_detect(MTD_DEV *dev, MTD_U16 port, int flag);

/*****************************************************************************
*  mtd_msec_set_delay_ext_reset
*
* DESCRIPTION:
*   set ignore external reset
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
*  mtd_msec_set_constant_latency
*
* DESCRIPTION:
*   Set the constant latency to disable or enable based on the input flag
*
* INPUTS:
*   port - port number
*   flag - 1: enable  0: disable   
* 
* OUTPUTS:
*        None
*
* RETURNS:
*       MTD_OK          - on success
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_msec_set_constant_latency(MTD_U16 port, unsigned int flag );


#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* __MTDMSECINTERNAL_h */
