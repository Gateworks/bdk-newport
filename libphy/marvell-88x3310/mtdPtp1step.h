/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mtdPtp1step.h
*
* DESCRIPTION:
*       Definitions of internal functions for new PTP control API's
*
* DEPENDENCIES:
*
* FILE REVISION NUMBER:
*
*******************************************************************************/

#ifndef __MTDPTP1STEP_H
#define __MTDPTP1STEP_H
#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

#include "mtdMsecPtpApiDefs.h"

#define MTD_PTP_ADDR_ADJ 2     /*1 */
/*#define MTD_PTP_ADDR_ADJ 1   2 */

/* status / error codes */

/*extern MTD_DEV       *mtddev; */
/*#define MTD_PTP_PORT_OFF(port) ((port%4)*0x800) */
#define MTD_PTP_PORT_OFF(port) (0) 

#define MTD_APP 1

/*  Data structure for Time of Day */
typedef struct {
 unsigned long subnano; /* Sun-nanoseconds */
 unsigned long nanosec; /* nanoseconds */
 unsigned long lowsec; /* low seconds */
 unsigned long highsec; /* high seconds */
} MTD_NPTP_TIME_STRUCT;

#define  MTD_MSEC_PTP_GLOBAL        MTD_VN_GLOBAL_PTP

/* PTP address Memory Map */
#define  MTD_PTP_PMEU_PAM        0x0000                    /* pped */
#define  MTD_PTP_UMEU_PAM        0x0040*MTD_PTP_ADDR_ADJ       /* pued */
#define  MTD_PTP_RF             0x0080*MTD_PTP_ADDR_ADJ       /* rf */
#define  MTD_PTP_STATS             0x00c0*MTD_PTP_ADDR_ADJ       /* stat */
#define  MTD_PTP_PMEU_UDATA        0x0100*MTD_PTP_ADDR_ADJ       /* ppec */
#define  MTD_PTP_UMEU_UDATA        0x0200*MTD_PTP_ADDR_ADJ       /* ppdc */
#define  MTD_PTP_LUT_ACTION        0x0300*MTD_PTP_ADDR_ADJ       /* plud */
#define  MTD_PTP_LUT_KEYMASK    0x0380*MTD_PTP_ADDR_ADJ       /* pluc */

 
/* New PTP Register oFFSET Defines */
typedef enum  {
 MTD_PTP_1STEP_CFG_GEN =0*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_CFG_GEN2 =1*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_INTR_SET =2*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_INTR_SET_MSK =3*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_TIMEOUT_CTL =4*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_STT_CTL =5*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_DISP =6*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_DISP_RMA_S =7*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_DISP_RMA_M =8*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_TS_QUEUE =9*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_TS_USAGE =10*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_TSQL_DATA =11*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_TSQH_DATA =12*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_BIST_CTL0 =13*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_BIST_STATUS =14*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_CFG_STAT =15*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_CFG_TIMEOUT_CTL2 =16*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_CFG_TIMEOUT_CTL =17*MTD_PTP_ADDR_ADJ,
 MTD_PTP_1STEP_CFG_LUT_CTRL =18*MTD_PTP_ADDR_ADJ
} MTD_PTP_1STEP_RF_NAME;

/* Base addresses  */
typedef enum {
 MTD_PTP_igr,
 MTD_PTP_egr
 } MTD_PTP_Blk;

 typedef enum {
 MTD_GLOBAL_PTP,
 MTD_TAI_CFG,
 MTD_EG_PTP,
 MTD_IG_PTP
} MTD_PTP_TYPE;


/* Set bits by ANDing inverse of new value with old value */
typedef enum {
 MTD_MacName_RxGoodOctLo,
 MTD_MacName_RxGoodOctHi,
 MTD_MacName_RxBadOct,
 MTD_MacName_TxFifoUnder,
 MTD_MacName_RxUnicast,
 MTD_MacName_SentDeferred,
 MTD_MacName_BroadRx,
 MTD_MacName_MultiRx,
 MTD_MacName_Fr64,
 MTD_MacName_Fr65_127,
 MTD_MacName_Fr128_255,
 MTD_MacName_Fr256_511,
 MTD_MacName_Fr512_1023,
 MTD_MacName_Fr1024_Max,
 MTD_MacName_GoodTxOctLo,
 MTD_MacName_GoodTxOctHi,
 MTD_MacName_TxUnicast,
 MTD_MacName_ExCol,
 MTD_MacName_TxMulti,
 MTD_MacName_TxBroad,
 MTD_MacName_SentMultiple,
 MTD_MacName_FCSent,
 MTD_MacName_FCReceived,
 MTD_MacName_RxFifoOver,
 MTD_MacName_Undersize,
 MTD_MacName_Fragments,
 MTD_MacName_Oversize,
 MTD_MacName_Jabber,
 MTD_MacName_RxError,
 MTD_MacName_BadCrc,
 MTD_MacName_Collisions,
 MTD_MacName_LateCol,
 MTD_MacName_MacBameEnd
} MTD_MacName;

/* CAM match name. Associative array for LUT CAM match fields */
typedef enum {
 MTD_M_FLAGS,          
 MTD_M_PTP_VERSIONS,   
 MTD_M_PTP_MSGTYPE,    
 MTD_M_PTP_TRANS_SPEC, 
 MTD_M_TST_E,          
 MTD_M_TST_ACTION,     
 MTD_M_PTP_FLAGS      
}MTD_PTP_MATCH;

typedef enum {
 MTD_A_RX_TST_ACTION,
 MTD_A_RX_TST_OFFSETTYPE,
 MTD_A_RX_TST_U,
 MTD_A_RX_INSERTTST,
 MTD_A_RX_DROP,
 MTD_A_RX_INIPIGGYBACK,
 MTD_A_RX_STAMPLOW,
 MTD_A_RX_STAMPHIGH,
 MTD_A_RX_TST_E
}MTD_PTP_RX_ACTION;

typedef enum {
 MTD_A_TX_UPDATETXTIME,
 MTD_A_TX_REMOVETST,
 MTD_A_TX_DROP,
 MTD_A_TX_UPDATERESIDENCE,
 MTD_A_TX_CLEAR_PIGGYBACK,
 MTD_A_TX_STAMPLOW,
 MTD_A_TX_STAMPHIGH,
 MTD_A_TX_HOLD_FOR_TRANS
}MTD_PTP_TX_ACTION;

typedef enum {
 MTD_K_FlagPTPv2,
 MTD_K_FlagUDP,
 MTD_K_FlagIPv4,
 MTD_K_FlagIPv6,
 MTD_K_FlagTST,
 MTD_K_FlagGRE,
 MTD_K_FlagY1731,
 MTD_K_FlagNTP,
 MTD_K_FlagPTPv1,
 MTD_K_FlagDOT1q,
 MTD_K_FlagSTAG,
 MTD_K_FlagITAG,
 MTD_K_FlagSNAP,
 MTD_K_FlagMPLS,
 MTD_K_FlagMACSEC,
 MTD_K_AlwaysZero,
 MTD_K_VersionPTP,
 MTD_K_MessageType,
 MTD_K_TransportSpecific,
 MTD_K_TST_action,
 MTD_K_TST_E,
 MTD_K_FlagField,
 MTD_K_DomainNumber
}MTD_PTP_KEY;

typedef enum {
 MTD_PTP_Act_UpdateTxTime,      /* Tx action */
 MTD_PTP_Act_RemoveTST,         /* Tx action */
 MTD_PTP_Act_Drop,              /* Tx/Rx action */
 MTD_PTP_Act_UpdateResidence,   /* Tx action */
 MTD_PTP_Act_StampLow,          /* Tx/Rx action */
 MTD_PTP_Act_StampHigh,         /* Tx/Rx action */
 MTD_PTP_Act_TST_action,           /* Rx action */
 MTD_PTP_Act_TST_mode,             /* Rx action */
 MTD_PTP_Act_TST_E,                /* Rx action */
 MTD_PTP_Act_InsertTST,            /* Rx action */
 MTD_PTP_Act_IniPiggyback,         /* Rx action */
 MTD_PTP_Act_HoldForTransmission,  /* Tx action */
 MTD_PTP_Act_ClearPiggyback,       /* Tx action */
 MTD_PTP_Act_AddAsymmetry,            /* no use action */
 MTD_PTP_Act_AddLinkDelay,         /* no use action */
 MTD_PTP_Act_No_Action = -1
}MTD_PTP_1STEP_LUT_ACT;
typedef enum {
 MTD_PTP_ACTIONS_UpdateTxTime         = 0x0001,      /* Tx action */
 MTD_PTP_ACTIONS_RemoveTST            = 0x0002,         /* Tx action */
 MTD_PTP_ACTIONS_Drop                 = 0x0004,              /* Tx/Rx action */
 MTD_PTP_ACTIONS_UpdateResidence      = 0x0008,   /* Tx action */
 MTD_PTP_ACTIONS_StampLow             = 0x0010,          /* Tx/Rx action */
 MTD_PTP_ACTIONS_StampHigh            = 0x0020,         /* Tx/Rx action */
 MTD_PTP_ACTIONS_TST_action           = 0x0040,           /* Rx action */
 MTD_PTP_ACTIONS_TST_mode             = 0x0080,             /* Rx action */
 MTD_PTP_ACTIONS_TST_E                = 0x0100,                /* Rx action */
 MTD_PTP_ACTIONS_InsertTST            = 0x0200,            /* Rx action */
 MTD_PTP_ACTIONS_IniPiggyback         = 0x0400,         /* Rx action */
 MTD_PTP_ACTIONS_HoldForTransmission  = 0x0800,  /* Tx action */
 MTD_PTP_ACTIONS_ClearPiggyback       = 0x1000,       /* Tx action */
 MTD_PTP_ACTIONS_AddAsymmetry         = 0x2000,            /* no use action */
 MTD_PTP_ACTIONS_AddLinkDelay         = 0x4000,         /* no use action */
 MTD_PTP_ACTIONS_No_Action = 0
}MTD_PTP_1STEP_LUT_ACTIONS;


typedef enum {
 MTD_REG_TOD_0,             /* 0 */
 MTD_REG_TOD_1,
 MTD_REG_TOD_2,
 MTD_REG_TOD_3,
 MTD_REG_FRC_0,
 MTD_REG_FRC_1,
 MTD_REG_FRC_2,
 MTD_REG_FRC_3,
 MTD_REG_DRIFT_ADJ_CFG,     /* 8 */
 MTD_REG_TOD_STEP_NS,
 MTD_REG_TOD_STEP_FS,
 MTD_REG_TOD_CFG_GEN,
 MTD_REG_PULSE_DELAY,       /* 12 */
 MTD_REG_TRIG_GEN_TOD_0,    /* 13 */
 MTD_REG_TRIG_GEN_TOD_1,
 MTD_REG_TRIG_GEN_TOD_2,
 MTD_REG_TRIG_GEN_TOD_3,
 MTD_REG_TRIG_GEN_MSK_0,
 MTD_REG_TRIG_GEN_MSK_1,
 MTD_REG_TRIG_GEN_MSK_2,
 MTD_REG_TRIG_GEN_MSK_3,
 MTD_REG_TOD_LOAD_0,        /* 21 */
 MTD_REG_TOD_LOAD_1,
 MTD_REG_TOD_LOAD_2,
 MTD_REG_TOD_LOAD_3,
 MTD_REG_TOD_CAP_0,
 MTD_REG_TOD_CAP_1,
 MTD_REG_TOD_CAP_2,
 MTD_REG_TOD_CAP_3,
 MTD_REG_TOD_CAP1_0,         /* 29 */
 MTD_REG_TOD_CAP1_1,
 MTD_REG_TOD_CAP1_2,
 MTD_REG_TOD_CAP1_3,
 MTD_REG_TOD_CAP_CFG,        /* 33 */
 MTD_REG_PULSE_IN_CNT,
 MTD_REG_TOD_FUNC_CFG,       /* 35(0x23) */
 MTD_REG_PCLK_CFG,
 MTD_REG_PCLK_CNT_0,
 MTD_REG_PCLK_CNT_1,
 MTD_REG_DRIFT_THR_CFG,
 MTD_REG_NEXT_RT_0,          /* 40(0x28) */
 MTD_REG_NEXT_RT_1,
 MTD_REG_NEXT_RT_2,
 MTD_REG_NEXT_RT_3,
 MTD_REG_CLOCK_CYC,
 MTD_RSVD,
 MTD_REG_CLK_IN_CNT,
 MTD_REG_TAI_INTR,
 MTD_REG_TAI_INTR_MASK       /* 48 (0x30) */
} MTD_PTP_1STEP_TAI_REGS;

/* TAI register list */
#define MTD_TOD_0           MTD_VN_TAI_CFG +MTD_REG_TOD_0*MTD_PTP_ADDR_ADJ
#define MTD_TOD_1           MTD_VN_TAI_CFG +MTD_REG_TOD_1*MTD_PTP_ADDR_ADJ
#define MTD_TOD_2           MTD_VN_TAI_CFG +MTD_REG_TOD_2*MTD_PTP_ADDR_ADJ
#define MTD_TOD_3           MTD_VN_TAI_CFG +MTD_REG_TOD_3*MTD_PTP_ADDR_ADJ
#define MTD_FRC_0           MTD_VN_TAI_CFG +MTD_REG_FRC_0*MTD_PTP_ADDR_ADJ
#define MTD_FRC_1           MTD_VN_TAI_CFG +MTD_REG_FRC_1*MTD_PTP_ADDR_ADJ
#define MTD_FRC_2           MTD_VN_TAI_CFG +MTD_REG_FRC_2*MTD_PTP_ADDR_ADJ
#define MTD_FRC_3           MTD_VN_TAI_CFG +MTD_REG_FRC_3*MTD_PTP_ADDR_ADJ
#define MTD_DRIFT_ADJ_CFG   MTD_VN_TAI_CFG +MTD_REG_DRIFT_ADJ_CFG*MTD_PTP_ADDR_ADJ
#define MTD_TOD_STEP_NS     MTD_VN_TAI_CFG +MTD_REG_TOD_STEP_NS*MTD_PTP_ADDR_ADJ
#define MTD_TOD_STEP_FS     MTD_VN_TAI_CFG +MTD_REG_TOD_STEP_FS*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CFG_GEN     MTD_VN_TAI_CFG +MTD_REG_TOD_CFG_GEN*MTD_PTP_ADDR_ADJ
#define MTD_PULSE_DELAY     MTD_VN_TAI_CFG +MTD_REG_PULSE_DELAY*MTD_PTP_ADDR_ADJ
#define MTD_TRIG_GEN_TOD_0  MTD_VN_TAI_CFG +MTD_REG_TRIG_GEN_TOD_0*MTD_PTP_ADDR_ADJ
#define MTD_TRIG_GEN_TOD_1  MTD_VN_TAI_CFG +MTD_REG_TRIG_GEN_TOD_1*MTD_PTP_ADDR_ADJ
#define MTD_TRIG_GEN_TOD_2  MTD_VN_TAI_CFG +MTD_REG_TRIG_GEN_TOD_2*MTD_PTP_ADDR_ADJ
#define MTD_TRIG_GEN_TOD_3  MTD_VN_TAI_CFG +MTD_REG_TRIG_GEN_TOD_3*MTD_PTP_ADDR_ADJ
#define MTD_TRIG_GEN_MASK_0  MTD_VN_TAI_CFG +MTD_REG_TRIG_GEN_MASK_0*MTD_PTP_ADDR_ADJ
#define MTD_TRIG_GEN_MASK_1  MTD_VN_TAI_CFG +MTD_REG_TRIG_GEN_MASK_1*MTD_PTP_ADDR_ADJ
#define MTD_TRIG_GEN_MASK_2  MTD_VN_TAI_CFG +MTD_REG_TRIG_GEN_MASK_2*MTD_PTP_ADDR_ADJ
#define MTD_TRIG_GEN_MASK_3  MTD_VN_TAI_CFG +MTD_REG_TRIG_GEN_MASK_3*MTD_PTP_ADDR_ADJ
#define MTD_TOD_LOAD_0       MTD_VN_TAI_CFG +MTD_REG_TOD_LOAD_0*MTD_PTP_ADDR_ADJ
#define MTD_TOD_LOAD_1       MTD_VN_TAI_CFG +MTD_REG_TOD_LOAD_1*MTD_PTP_ADDR_ADJ
#define MTD_TOD_LOAD_2       MTD_VN_TAI_CFG +MTD_REG_TOD_LOAD_2*MTD_PTP_ADDR_ADJ
#define MTD_TOD_LOAD_3       MTD_VN_TAI_CFG +MTD_REG_TOD_LOAD_3*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CAP_0        MTD_VN_TAI_CFG +MTD_REG_TOD_CAP_0*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CAP_1        MTD_VN_TAI_CFG +MTD_REG_TOD_CAP_1*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CAP_2        MTD_VN_TAI_CFG +MTD_REG_TOD_CAP_2*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CAP_3        MTD_VN_TAI_CFG +MTD_REG_TOD_CAP_3*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CAP1_0       MTD_VN_TAI_CFG +MTD_REG_TOD_CAP1_0*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CAP1_1       MTD_VN_TAI_CFG +MTD_REG_TOD_CAP1_1*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CAP1_2       MTD_VN_TAI_CFG +MTD_REG_TOD_CAP1_2*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CAP1_3       MTD_VN_TAI_CFG +MTD_REG_TOD_CAP1_3*MTD_PTP_ADDR_ADJ
#define MTD_TOD_CAP_CFG      MTD_VN_TAI_CFG +MTD_REG_TOD_CAP_CFG*MTD_PTP_ADDR_ADJ
#define MTD_PULSE_IN_CNT     MTD_VN_TAI_CFG +MTD_REG_PULSE_IN_CNT*MTD_PTP_ADDR_ADJ
#define MTD_TOD_FUNC_CFG     MTD_VN_TAI_CFG +MTD_REG_TOD_FUNC_CFG*MTD_PTP_ADDR_ADJ
#define MTD_PCLK_CFG         MTD_VN_TAI_CFG +MTD_REG_PCLK_CFG*MTD_PTP_ADDR_ADJ
#define MTD_PCLK_CNT_0       MTD_VN_TAI_CFG +MTD_REG_PCLK_CNT_0*MTD_PTP_ADDR_ADJ
#define MTD_PCLK_CNT_1       MTD_VN_TAI_CFG +MTD_REG_PCLK_CNT_1*MTD_PTP_ADDR_ADJ
#define MTD_DRIFT_THR_CFG    MTD_VN_TAI_CFG +MTD_REG_DRIFT_THR_CFG*MTD_PTP_ADDR_ADJ
#define MTD_NEXT_RT_0        MTD_VN_TAI_CFG +MTD_REG_NEXT_RT_0*MTD_PTP_ADDR_ADJ
#define MTD_NEXT_RT_1        MTD_VN_TAI_CFG +MTD_REG_NEXT_RT_1*MTD_PTP_ADDR_ADJ
#define MTD_NEXT_RT_2        MTD_VN_TAI_CFG +MTD_REG_NEXT_RT_2*MTD_PTP_ADDR_ADJ
#define MTD_NEXT_RT_3        MTD_VN_TAI_CFG +MTD_REG_NEXT_RT_3*MTD_PTP_ADDR_ADJ
#define MTD_CLOCK_CYC        MTD_VN_TAI_CFG +MTD_REG_CLOCK_CYC*MTD_PTP_ADDR_ADJ
#define MTD_CLK_DELAY         MTD_VN_TAI_CFG +MTD_RSVD*MTD_PTP_ADDR_ADJ
#define MTD_CLK_IN_CNT       MTD_VN_TAI_CFG +MTD_REG_CLK_IN_CNT*MTD_PTP_ADDR_ADJ
#define MTD_TAI_INTR         MTD_VN_TAI_CFG +MTD_REG_TAI_INTR*MTD_PTP_ADDR_ADJ
#define MTD_TAI_INTR_MASK    MTD_VN_TAI_CFG +MTD_REG_TAI_INTR_MASK*MTD_PTP_ADDR_ADJ
#define MTD_OLD_TOD_0        MTD_VN_TAI_CFG +0x31*MTD_PTP_ADDR_ADJ
#define MTD_OLD_TOD_1        MTD_VN_TAI_CFG +0x32*MTD_PTP_ADDR_ADJ
#define MTD_OLD_TOD_2        MTD_VN_TAI_CFG +0x33*MTD_PTP_ADDR_ADJ
#define MTD_OLD_TOD_3        MTD_VN_TAI_CFG +0x34*MTD_PTP_ADDR_ADJ
#define MTD_DRIFT_MCAND         MTD_VN_TAI_CFG +0x36*MTD_PTP_ADDR_ADJ
#define MTD_TIME_UPD_CNT     MTD_VN_TAI_CFG +0x38*MTD_PTP_ADDR_ADJ


typedef enum  {
 MTD_PTPv2_MSG_Sync = 0x0,
 MTD_PTPv2_MSG_Delay_Req = 0x1,
 MTD_PTPv2_MSG_Pdelay_Req = 0x2,
 MTD_PTPv2_MSG_Pdelay_Resp = 0x3,
 MTD_PTPv2_MSG_Follow_Up = 0x8,
 MTD_PTPv2_MSG_Delay_Resp = 0x9,
 MTD_PTPv2_MSG_Pdelay_Resp_Follow_Up = 0xa,
 MTD_PTPv2_MSG_Announce = 0xb,
 MTD_PTPv2_MSG_Signaling = 0xc,
 MTD_PTPv2_MSG_Management = 0xd
}MTD_PTPv2_message_type;


typedef enum  {
 MTD_PTP_1STEP_VER_V1,
 MTD_PTP_1STEP_VER_V2
}MTD_PTP_1STEP_VERSION;

typedef int MTD_PTP_1STEP_TRANS_SPEC;

typedef enum  {
 MTD_PTP_1STEP_OVER_L2,
 MTD_PTP_1STEP_OVER_IP4_UDP,
 MTD_PTP_1STEP_OVER_IP6_UDP,
 MTD_PTP_1STEP_OVER_NTP,
 MTD_PTP_1STEP_OVER_MPLS
}MTD_PTP_1STEP_OVER_LAYER;

typedef enum  {
 MTD_PTP_1STEP_ING_ACT_TS_TAG        = 0x1,
 MTD_PTP_1STEP_ING_ACT_TS_TAG_EX   = 0x2,
 MTD_PTP_1STEP_ING_ACT_PIGGY       = 0x4,
 MTD_PTP_1STEP_ING_ACT_LOW_QUEUE   = 0x8,
 MTD_PTP_1STEP_ING_ACT_HIGH_QUEUE  = 0x10
}MTD_PTP_1STEP_ING_ACTION;

typedef enum  {
 MTD_PTP_1STEP_EG_ACT_LOW_QUEUE    = 0x1,
 MTD_PTP_1STEP_EG_ACT_HIGH_QUEUE   = 0x2,
 MTD_PTP_1STEP_EG_ACT_UPDATE_TS    = 0x4,
 MTD_PTP_1STEP_EG_ACT_SET_RES_TS   = 0x8,
 MTD_PTP_1STEP_EG_ACT_REMOVE_TST   = 0x10
}MTD_PTP_1STEP_EG_ACTION;

typedef enum  {
 MTD_PTP_1STEP_MSG_SYNC            = (1<<MTD_PTPv2_MSG_Sync),
 MTD_PTP_1STEP_MSG_DELAY_REQ        = (1<<MTD_PTPv2_MSG_Delay_Req),
 MTD_PTP_1STEP_MSG_PDELAY_REQ        = (1<<MTD_PTPv2_MSG_Pdelay_Req),
 MTD_PTP_1STEP_MSG_PDELAY_RESP        = (1<<MTD_PTPv2_MSG_Pdelay_Resp),
 MTD_PTP_1STEP_MSG_FOLLOWUP        = (1<<MTD_PTPv2_MSG_Follow_Up),
 MTD_PTP_1STEP_MSG_DELAY_RESP        = (1<<MTD_PTPv2_MSG_Delay_Resp),
 MTD_PTP_1STEP_MSG_PDELAY_RESP_FOLLOWUP    = (1<<MTD_PTPv2_MSG_Pdelay_Resp_Follow_Up),
 MTD_PTP_1STEP_MSG_ANNOUNCE                = (1<<MTD_PTPv2_MSG_Announce),
 MTD_PTP_1STEP_MSG_SIGNALING                = (1<<MTD_PTPv2_MSG_Signaling),
 MTD_PTP_1STEP_MSG_MANAGEMENT                = (1<<MTD_PTPv2_MSG_Management)
}MTD_PTP_1STEP_MSG_TYPE;

typedef enum  {
 MTD_PTP_1STEP_QUEUE_HIGH,
 MTD_PTP_1STEP_QUEUE_LOW
} MTD_PTP_1STEP_QUEUE_TYPE;

#define MTD_PTP_TS_QUEUE_SIZE 8  /* For 10G. 7 for 1G */

typedef struct {
 MTD_PTP_1STEP_VERSION version;
 MTD_PTP_1STEP_TRANS_SPEC transSpec ;
 MTD_PTP_1STEP_MSG_TYPE   msgTypes;
 MTD_PTP_1STEP_OVER_LAYER overLayer;
 MTD_PTP_1STEP_ING_ACTION ingaction;
 MTD_PTP_1STEP_EG_ACTION egaction;
} MTD_PTP_1STEP_CFG;

/* PPT time structure in register : tod_0, frc_0, trig_gen_tod_0, trig_gen_msk_0, tod_load_0, tod_cap_0, tod_cap1_0, next_rt_0 */
typedef struct {
 unsigned int      sec_hi;  /* High seconds */
 unsigned int      sec_lo;  /* Low seconds */
 unsigned int      nanosec; /* nanoseconds */ 
 unsigned short    frec;    /* sub-nanoseconds */ 
} MtdPtpTimeStruct; 


/* Time stamp struct */
typedef union {
 struct {
 unsigned int      nanoseconds;  
 unsigned short    topseconds; 
 unsigned int      seconds;
 }  extTs;
 unsigned int      ts;  
} MtdPtp1StepTsStruct; 

typedef struct {
 unsigned short      seqId; 
 unsigned char       domainNum; 
 unsigned char       transpSpec; 
 unsigned char       msgId; 
 MtdPtp1StepTsStruct     ts; 
} MtdPtpTsQueueStruct;

typedef struct {
 unsigned int        lat_adj1;
 unsigned int        lat_adj0;
} MtdPtpPamLatAdj;

//extern unsigned short mtd_ptp_addr[];

/*  */
extern unsigned short mtd_ptp_1step_base_addr[];
extern char * mtd_ptp_1step_macNmList[];
extern char *mtd_ptp_lut_match_fld_pos_name[];
extern int mtd_ptp_lut_match_fld_pos[];
extern char *mtd_ptp_lut_match_fld_sz_name[];
extern int mtd_ptp_lut_match_fld_sz[];
extern char * mtd_ptp_lut_tx_action_fld_pos_name[];
extern int mtd_ptp_lut_tx_action_fld_pos[];
extern int mtd_ptp_lut_tx_action_fld_sz[];
extern char * mtd_ptp_lut_rx_action_fld_pos_name[];
extern int mtd_ptp_lut_rx_action_fld_pos[];
extern int mtd_ptp_lut_rx_action_fld_sz[];

extern char * mtd_ptp_stat_name [];
extern char * mtd_ptp_rf_names_list [];
extern char * mtd_ptp_egr_stats_names_list[];
extern char * mtd_ptp_igr_stats_names_list[];
extern int mtd_ptp_lut_key_pos[];
extern int mtd_ptp_lut_key_size[]; 
extern int mtd_ptp_lut_act_pos[];
extern char * mtd_ptp_tai_regs_list_name [];

typedef enum {
 MTD_CLK_MODE,
 MTD_IN_CLK_EN,
 MTD_NTP_TOD_MODE,
 MTD_EN_DECOUPLE,
 MTD_CNT_SEL_TS,
 MTD_DRIFT_ADJ_TRIG_EN,
 MTD_CLK_DELAY_CALC_EN,
 MTD_PULSE_DELAY_CALC_EN
} MTD_TAI_TOD_CFG_GEN;

extern char *mtd_tai_tod_cfg_gen_name[];
extern int mtd_tai_tod_cfg_gen_pos[];
extern int mtd_tai_tod_cfg_gen_sz[];

typedef enum {
 MTD_TAI_TOD_PULSE_WIDTH,
 MTD_TAI_TOD_CNT_SEL,
 MTD_TAI_TOD_TOD_FUNC_TRIG,
 MTD_TAI_TOD_TRIG_GEN_EN,
 MTD_TAI_TOD_TOD_FUNC 
} MTD_TAI_TOD_FUNC_CFG;

typedef enum {
 MTD_TOD_FUNC_TIMER_UPDATE,
 MTD_TOD_FUNC_TIMER_INC,
 MTD_TOD_FUNC_TIMER_DEC,
 MTD_TOD_FUNC_TIMER_CAPT 
} MTD_TOD_FUNC_TIMER_OP;

#define MTD_PTP_CYCLE 16 /* 625M clock, clock period 1.6ns. multiplied by 10 */

extern char *mtd_tai_tod_func_cfg_name[];
extern int mtd_tai_tod_func_cfg_pos[];
extern int mtd_tai_tod_func_cfg_sz[];

/* functions */
MTD_PTP_TYPE mtd_get_ptp_base_addr_id (MTD_PTP_Blk path );

MTD_STATUS mtd_clear_bits (MTD_U16 port, unsigned short addr, unsigned int data);

MTD_STATUS mtd_ptp_msec_set_link_down_reset(MTD_U16 port, int flag);
MTD_STATUS mtd_ptp_msec_sem_take(MTD_U32 timeOut);
MTD_STATUS mtd_ptp_msec_sem_give();

unsigned int _mtd_ptp_read_reg (MTD_U16 port, unsigned short addr);
unsigned int mtd_ptp_read_reg (MTD_U16 port, unsigned short addr);

//unsigned int _mtd_ptp_readcheck_reg (MTD_U16 port, unsigned short addr);
unsigned int mtd_ptp_readcheck_reg (MTD_U16 port, unsigned short addr);

MTD_STATUS _mtd_ptp_write_reg (MTD_U16 port, unsigned short addr, unsigned int data);
MTD_STATUS mtd_ptp_write_reg (MTD_U16 port, unsigned short addr, unsigned int data);

//MTD_STATUS _mtd_ptp_writecheck_reg(MTD_U16 port, unsigned short addr, unsigned int data);
MTD_STATUS mtd_ptp_writecheck_reg(MTD_U16 port, unsigned short addr, unsigned int data);

void mtd_ptp_1step_print_reg (MTD_U16 port, unsigned short addr);
/* Set bits by ORing new value with old value */
MTD_STATUS mtd_set_bits (MTD_U16 port, unsigned short addr, unsigned int data);

#ifdef DEBUG_MTD
MTD_STATUS mtd_ptp_1step_dump_mac_statistics (MTD_U16 port, unsigned int *macValList);
void mtd_ptp_1step_print_mac_statistics (MTD_U16 port, unsigned int *macValList);
MTD_STATUS mtd_ptp_1step_dump_sysmac_statistics (MTD_U16 port, unsigned int *sysmacValList);
void mtd_ptp_1step_print_sysmac_statistics (MTD_U16 port, unsigned int *sysmacValList);
void mtd_get_mac_stats (MTD_U16 port, unsigned int *macValList);
void mtd_get_sysmac_stats (MTD_U16 port, unsigned int *sysmacValList);
#endif
MTD_STATUS mtd_ptp_1step_set_smac_loopback (MTD_U16 port, int en);

void mtd_ptp_1step_print_rumi_stats (MTD_U16 port);

/* common PTP init  */
MTD_STATUS mtd_ptp_common_init (MTD_U16 port);

/* PTP parser init */
MTD_STATUS mtd_ptp_parser_init (MTD_U16 port);

MTD_STATUS mtd_ptp_parser_set_udata (MTD_U16 port);

MTD_STATUS mtd_ptp_parser_check_udata (MTD_U16 port);

/* PTP update init */
MTD_STATUS mtd_ptp_update_init (MTD_U16 port);

MTD_STATUS mtd_ptp_update_set_udata (MTD_U16 port);
MTD_STATUS mtd_ptp_update_check_udata (MTD_U16 port);

/* Set PTP udata into udata space */
MTD_STATUS mtd_ptp_set_udata (MTD_U16 port, unsigned int * filedata, unsigned int baseaddr );
/* Check PTP udata from file against udata space */
MTD_STATUS mtd_ptp_check_udata (MTD_U16 port,  unsigned int * filedata, unsigned int baseaddr );

/* Write DONE to udata spaces to just make PTP pass packet along */
/* (Enric modified this as follows) */
/* for parser (both ingress and egress): addr 0 & 1 => HALT */
/* for update: for ingress: addr 0 => HALT, addr 1 => OUT EOP, addr 2 => HALT */
/*             for egress : addr 0 => HALT, addr 1 => OUT HFT, addr 2 => OUT EOP, addr 3 => HALT  */
MTD_STATUS mtd_ptp_1step_setup_simple_udata (MTD_U16 port);

/* return LUT value adjusted for field position */
long long mtd_ptp_lut_match_fld_val(MTD_PTP_MATCH field, long long value );
/* return LUT value extracted from vector */
long long  mtd_ptp_lut_match_fld_extract( MTD_PTP_MATCH field, long long vector);

/* return TX LUT value adjusted for field position */
unsigned short mtd_ptp_lut_tx_action_fld_val( MTD_PTP_TX_ACTION field, unsigned short value );

/* return TX LUT value extracted from vector  */
unsigned long long mtd_ptp_lut_tx_action_fld_extract (MTD_PTP_TX_ACTION field, unsigned long long vector );

/* return RX LUT value adjusted for field position */
unsigned short mtd_ptp_lut_rx_action_fld_val( MTD_PTP_RX_ACTION field, unsigned short value );

/* return RX LUT value extracted from vector  */
unsigned long long mtd_ptp_lut_rx_action_fld_extract (MTD_PTP_RX_ACTION field, unsigned long long vector );

/* return flag value adjusted for flag position */
unsigned long long mtd_lut_flag_fld_val(int flag, unsigned long long value );
/* Read lut entry */
MTD_STATUS mtd_read_lut_entry (MTD_U16 port, long long *lut_key, long long *lut_valid, long *lut_key_upper, long *lut_valid_upper, long long *lut_action, 
short lut_index, int path );
/* find entry, that has required action */
MTD_STATUS mtd_ptp_find_lut_action(MTD_U16 port, MTD_PTP_1STEP_LUT_ACT action, MTD_PTP_Blk path, int *entryNum);
/* Enable/Disable lut action */
MTD_STATUS mtd_ptp_enable_lut_action(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACT action, MTD_PTP_Blk path, MTD_BOOL en );

#ifdef DEBUG_MTD
/* dump memory */
MTD_STATUS mtd_ptp_1step_dump_mem (MTD_U16 port, unsigned int addr, int range);
#endif
/* memory test */
MTD_STATUS mtd_ptp_1step_write_fs_check (MTD_U16 port, unsigned int addr, int range, unsigned int mask);
/* memory test */
MTD_STATUS mtd_ptp_1step_write_unique_check (MTD_U16 port, unsigned short addr, int range, unsigned int mask);

#ifdef DEBUG_MTD
/* udata mem dump */
MTD_STATUS mtd_ptp_1step_mem_dump_update_udata (MTD_U16 port);
#endif
/* udata mem test */
MTD_STATUS mtd_ptp_1step_mem_test_update_udata (MTD_U16 port);
/* udata mem test */
MTD_STATUS mtd_ptp_1step_mem_test_parser_udata (MTD_U16 port);

/* prints out the ptp registers (portber 'port') */
MTD_STATUS mtd_get_ptp_regs ( MTD_U16 port, MTD_PTP_Blk path );

/* prints out the ptp pam (parser and update) contents (portber 'port' and path 'egr|igr') */
MTD_STATUS mtd_get_ptp_pam ( MTD_U16 port, MTD_PTP_Blk path );

/* prints out the ptp lut (key, mask and action) contents (portber 'port' and path 'egr|igr') */
MTD_STATUS mtd_get_ptp_lut ( MTD_U16 port, MTD_PTP_Blk path );
/*get_ptp_regs 0 igr */
/*get_ptp_regs 0 egr */
/*get_ptp_stats 0 igr */
/*get_ptp_stats 0 egr */
/*get_ptp_pam 0 igr */
/*get_ptp_pam 0 egr */
/*get_ptp_lut 0 igr */
/*get_ptp_lut 0 egr */

unsigned long long mtd_ptp_lut_key_adjust ( MTD_PTP_KEY name, unsigned long long value );
unsigned long long mtd_ptp_vld_key_adjust ( MTD_PTP_KEY name );
/*  global mtd_ptp_lut_key_pos */
/*  global mtd_ptp_lut_key_size */

unsigned long long mtd_ptp_lut_act_adjust ( MTD_PTP_1STEP_LUT_ACT name, unsigned long long value );

/**demo LUT */
MTD_STATUS mtd_ptp_lut_init (MTD_U16 port);

/* init example */

MTD_STATUS _mtd_set_ptp_tai_tod(MTD_U16 port, unsigned int ns, unsigned int sec_lo, unsigned int sec_hi);
MTD_STATUS mtd_set_ptp_tai_frc(MTD_U16 port, unsigned int ns, unsigned int sec_lo, unsigned int sec_hi);
MTD_STATUS mtd_get_ptp_tai_step(MTD_U16 port, unsigned int *nanosec, unsigned int *fracnanosec);
MTD_STATUS mtd_set_ptp_tai_step(MTD_U16 port, unsigned int nanosec, unsigned int fracnanosec);

int mtd_get_ptp_tsql_usage(MTD_U16 port, MTD_PTP_Blk path);
int mtd_get_ptp_tsqh_usage(MTD_U16 port, MTD_PTP_Blk path);

MTD_STATUS mtd_ptp_get_tsql_part(MTD_U16 port, MTD_PTP_Blk path, int count, MtdPtpTsQueueStruct *tsQueue);
MTD_STATUS mtd_ptp_get_tsqh_part(MTD_U16 port, MTD_PTP_Blk path, int count, MtdPtpTsQueueStruct *tsQueue);
MTD_STATUS mtd_displayPTPTsQueue(MtdPtpTsQueueStruct *tsQueue);
MTD_STATUS mtd_ptp_get_tsql(MTD_U16 port, MTD_PTP_Blk path, MtdPtpTsQueueStruct *tsQueue);
MTD_STATUS mtd_ptp_get_tsqh(MTD_U16 port, MTD_PTP_Blk path, MtdPtpTsQueueStruct *tsQueue);

MTD_STATUS mtd_get_ptp_tsql_data (MTD_U16 port,  MTD_PTP_Blk path, int numhwords);

MTD_STATUS mtd_get_ptp_tsqh_data (MTD_U16 port,  MTD_PTP_Blk path, int numhwords);

MTD_STATUS mtd_get_ptp_stuff (MTD_U16 port);

MTD_STATUS mtd_ptp_lut_update (MTD_U16 port, unsigned long long delete_lut_key , 
 unsigned long long delete_lut_vld,
 unsigned long long delete_lut_act,
 unsigned long long add_lut_key , 
 unsigned long long add_lut_vld,
 unsigned long long add_lut_act,
 short lut_index, int path );

MTD_STATUS mtd_set_ptp_tai_reg (MTD_U16 port, MTD_PTP_1STEP_TAI_REGS regname, unsigned int value );
/* Set PTP register */
MTD_STATUS mtd_get_ptp_tai_reg (MTD_U16 port, MTD_PTP_1STEP_TAI_REGS regname, unsigned int *value  ); 

/* set drift adjustment (frac nsec) */
MTD_STATUS mtd_set_drift_adj (MTD_U16 port, unsigned int frac_ns);
/* get drift adjustment (frac nsec) */
MTD_STATUS mtd_get_drift_adj (MTD_U16 port, unsigned int *frac_ns);
MTD_STATUS mtd_disable_macsec_both (MTD_U16 port);
/* TAI / TOD */
/* Get PTP time register  */
/* Valid regname is one of: tod_0, frc_0, trig_gen_tod_0, trig_gen_msk_0, tod_load_0, tod_cap_0, tod_cap1_0, next_rt_0 */
MTD_STATUS mtd_get_ptp_tai_timereg (MTD_U16 port, MTD_PTP_1STEP_TAI_REGS regname,unsigned int *sec_hi,unsigned int *sec_lo,unsigned int *ns, unsigned int *fs);
/* Set PTP time register  */
/* Valid regname is one of: tod_0, frc_0, trig_gen_tod_0, trig_gen_msk_0, tod_load_0, tod_cap_0, tod_cap1_0, next_rt_0 */
MTD_STATUS mtd_set_ptp_tai_timereg (MTD_U16 port, MTD_PTP_1STEP_TAI_REGS regname,unsigned int sec_hi,unsigned int sec_lo,unsigned int ns, unsigned int fs);
/* return value with modified field  */
unsigned int mtd_tai_tod_cfg_gen_set_field (unsigned int oldvalue, int field, unsigned int value);
/* return value extracted from vector */
unsigned int mtd_tai_tod_cfg_gen_extract(int field, int vector);

/* return value with modified field  */
unsigned int mtd_tai_tod_func_cfg_set_field(unsigned int oldvalue, int field, unsigned int value) ;

/* return value extracted from vector */
unsigned int mtd_tai_tod_func_cfg_extract(int field, int vector);
#ifdef DEBUG_MTD
/* Show TAI TOD cfg gen */
void mtd_ptp_1step_print_tai_tod_func_cfg (MTD_U16 port);
#endif
/* ------------------------------------------------------------------------------------ zzz */
MTD_STATUS mtd_set_tai_pulse_in_cnt (MTD_U16 port, unsigned int val);

MTD_STATUS mtd_get_tai_pulse_in_cnt (MTD_U16 port);
//MTD_STATUS mtd_set_tai_pulse_delay (MTD_U16 port, unsigned int val);

MTD_STATUS mtd_ptp_lut_default (MTD_U16 port);
/* entry 14 */
/* if parser is interrupted => do nothing */
MTD_STATUS mtd_ptp_lut_interrupt (MTD_U16 port);
MTD_STATUS mtd_set_tai_ntp_mode (MTD_U16 port);

/* set tod_cap_cfg bits cap_ */
MTD_STATUS mtd_set_tod_cap_cfg (MTD_U16 port, unsigned int val);
MTD_STATUS mtd_set_elu_entry_match_da (MTD_U16 port, int en, int da);

MTD_STATUS mtd_ptp_update_set_udata_ntp (MTD_U16 port);
MTD_STATUS mtd_ptp_update_check_udata_ntp (MTD_U16 port);
MTD_STATUS mtd_ptp_parser_set_udata_ntp (MTD_U16 port);
MTD_STATUS mtd_ptp_parser_check_udata_ntp (MTD_U16 port);
MTD_STATUS mtd_ptp_lut_init_ntp (MTD_U16 port);
MTD_STATUS mtd_ptp_lut_init_ntp_2 (MTD_U16 port, int udp_src_port, int udp_dst_port);
MTD_STATUS mtd_set_ntp_tod_mode (MTD_U16 port, unsigned int ntp_mode);

unsigned long long  mtd_prgm_ptp_get_lut_act (MTD_PTP_1STEP_LUT_ACT action);
unsigned long long  mtd_prgm_ptp_get_lut_actions (MTD_PTP_1STEP_LUT_ACTIONS actions);
/* */
 
MTD_STATUS mtd_set_ptp_timeout_ctrl(unsigned int cycles, MTD_U16 port);
MTD_STATUS mtd_set_ptp_igr_mode (MTD_U16 port, unsigned int mode );
unsigned int mtd_get_ptp_igr_mode (MTD_U16 port);

MTD_STATUS mtd_set_ntp_mode (MTD_U16 port, unsigned int flag );
unsigned int mtd_get_ntp_mode (MTD_U16 port, MTD_PTP_Blk path);

MTD_STATUS mtd_set_ptp_pam_egr_latadj (MTD_U16 port, MtdPtpPamLatAdj *lat);
MTD_STATUS mtd_get_ptp_pam_egr_latadj (MTD_U16 port, MtdPtpPamLatAdj *lat);
unsigned int  mtd_get_ptp_egr_latadj(MTD_U16 port);
MTD_STATUS mtd_set_ptp_egr_latadj (MTD_U16 port, unsigned int ns );
unsigned int  mtd_get_ptp_igr_latadj(MTD_U16 port);
MTD_STATUS mtd_set_ptp_igr_latadj(MTD_U16 port, unsigned int ns );
MTD_STATUS mtd_set_ptp_egr_stt_ctl(MTD_U16 port, unsigned int value);
unsigned int  mtd_get_ptp_egr_stt_ctl(MTD_U16 port);
MTD_STATUS mtd_set_ptp_igr_stt_ctl(MTD_U16 port, unsigned int value);
unsigned int  mtd_get_ptp_igr_stt_ctl(MTD_U16 port);
MTD_STATUS mtd_set_egr_fr_latency(MTD_U16 port, unsigned int fr_lat);
unsigned int  mtd_get_egr_fr_latency(MTD_U16 port);
unsigned int  mtd_get_egr_latency(MTD_U16 port);
MTD_STATUS mtd_set_igr_fr_latency(MTD_U16 port, unsigned int fr_lat);
unsigned int mtd_get_core_period (void);
unsigned int  mtd_get_igr_fr_latency(MTD_U16 port);
unsigned int  mtd_get_igr_latency(MTD_U16 port);
/*
# set top_interrupt mask in 0x8006
# b8~11, port0~3
# b12, global interrupt for MACsec and PTP
# b15, TAI interrupt
*/
MTD_STATUS mtd_set_top_intr_msk(MTD_U16 port, unsigned int msk);
unsigned int  mtd_get_top_intr_msk(MTD_U16 port);
/*
# get interrupt source in 0x8004
*/
unsigned int  mtd_get_intr_src(MTD_U16 port); 


/*******************************************************************************
* mtd_ptp_get_ts_tsq
*
* DESCRIPTION:
*       This routine gets Time stamp from TS Queue.
*
* INPUTS:
*    port - port number.
*       path  - NewPtp block number: igr or egr.
*       queue - NewPtp queue number: high or low.
*       seqId - sequence id of PTP frame .
*       msgId - message id of PTP frame .
n*   
* OUTPUTS:
*       ts - NewPtp Time stamp data.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_get_ts_tsq 
(
  IN  MTD_U16 port, 
  IN  MTD_PTP_Blk path, 
  IN  MTD_PTP_1STEP_QUEUE_TYPE queue, 
  IN  unsigned short seqId, 
  IN  unsigned short msgId, 
  OUT MtdPtp1StepTsStruct *ts);

/*******************************************************************************
* mtd_ptp_get_ntp_ts_tsq
*
* DESCRIPTION:
*       This routine gets Time stamp from TS Queue for NTP.
*
* INPUTS:
*    port - port number.
*       path  - NewPtp block number: igr or egr.
*       queue - NewPtp queue number: high or low.
*   
* OUTPUTS:
*       numwords - number of TS elements in Queue.
*       ts - NewPtp Time stamp data.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on no ts or error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_get_ntp_ts_tsq
(
  IN  MTD_U16 port, 
  IN  MTD_PTP_Blk path, 
  IN  MTD_PTP_1STEP_QUEUE_TYPE queue, 
  OUT int *numwords,
  OUT MtdPtp1StepTsStruct *ts);

/* TAI / TOD */

/*******************************************************************************
* mtd_ptp_print_tai_tod_cfg_gen
*
* DESCRIPTION:
*         Show TAI TOD cfg general
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
/* Show TAI TOD cfg gen */
MTD_STATUS mtd_ptp_print_tai_tod_cfg_gen 
(
   IN MTD_U16 port
);

/*******************************************************************************
* mtd_ptp_disable_tai_clk_gen
*
* DESCRIPTION:
     Disable TAI from generating external clock signal, 
*    keeping internal clock generation 
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
/* Disable TAI from generating external clock signal, keeping internal clock generation */
MTD_STATUS mtd_ptp_disable_tai_clk_gen 
(
  IN MTD_U16 port
);

/*******************************************************************************
* mtd_ptp_set_tai_clk_gen
*
* DESCRIPTION:
*         Set TAI to generate external clock signal
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
/* Set TAI to generate external clock signal */
MTD_STATUS mtd_ptp_set_tai_clk_gen 
(
  IN MTD_U16 port
);

/*******************************************************************************
* mtd_ptp_set_tai_clk_rec
*
* DESCRIPTION:
*         Set TAI to update TOD based on external clock signal
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
/* Set TAI to update TOD based on external clock signal */
MTD_STATUS mtd_ptp_set_tai_clk_rec 
(
  IN MTD_U16 port
);

/*******************************************************************************
* mtd_ptp_set_tai_clk_rec_adv
*
* DESCRIPTION:
*         Set TAI to update TOD based and auto adjust frequency based on ext clock signal
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
/* Set TAI to update TOD based and auto adjust frequency based on ext clock signal */
MTD_STATUS mtd_ptp_set_tai_clk_rec_adv 
(
  IN MTD_U16 port
);

/*******************************************************************************
* mtd_ptp_tai_trig_load_timer
*
* DESCRIPTION:
*         Set TOD func trig to copy LOAD into NEXT RT 
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
/* Set TOD func trig to copy LOAD into NEXT RT */
MTD_STATUS mtd_ptp_tai_trig_load_timer 
(
  IN MTD_U16 port
);

/*******************************************************************************
* mtd_ptp_print_tai_intr
*
* DESCRIPTION:
*         Print TAI interrupts
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
/* Print TAI interrupts */
MTD_STATUS mtd_ptp_print_tai_intr 
(
  IN MTD_U16 port
);

/*******************************************************************************
* mtd_ptp_set_drift_thr_cfg
*
* DESCRIPTION:
*         Set drift threshold config
*
* INPUTS:
*       port - port number
*       minimal_drift - min drift in ns that triggers drift adj 
*       drift_thr - min drift in ns that causes interrupt to be invoked to CPU 
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
/* Set drift threshold config */
/* minimal_drift: min drift in ns that triggers drift adj */
/* drift_thr: min drift in ns that causes interrupt to be invoked to CPU */
MTD_STATUS mtd_ptp_set_drift_thr_cfg
(
  IN MTD_U16 port,
  IN unsigned int minimal_drift,
  IN unsigned int drift_thr
);

/* pclk period generated by 1548P Z1 ASIC is actually  */
/* 8ns more than pclk_cfg setting so write a pclk_cfg  */
/* setting that is 8ns less than what you want */

/*******************************************************************************
* mtd_ptp_set_pclk_freq
*
* DESCRIPTION:
*         set pclk period to 10Mhz
*
* INPUTS:
*       port - port number
*       freq - pclk period 
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
/* set pclk period to 10Mhz */
MTD_STATUS mtd_ptp_set_pclk_freq
(
  IN MTD_U16 port,
  IN int freq
);

/*******************************************************************************
* mtd_ptp_set_tai_pulse_delay_en
*
* DESCRIPTION:
*         Set pulse delay enable. If set to 1, pulse_delay will be added to TOD_LOAD
*         when doing UPDATE operation.
*
* INPUTS:
*       port - port number
*        en - pulse_delay 
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
MTD_STATUS mtd_set_tai_pulse_delay_en (MTD_U16 port, MTD_BOOL en);

/*******************************************************************************
* mtd_ptp_get_tai_pulse_delay_en
*
* DESCRIPTION:
*         Get pulse delay enable. If set to 1, pulse_delay will be added to TOD_LOAD
*         when doing UPDATE operation.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        en - pulse_delay 
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_tai_pulse_delay_en (MTD_U16 port, MTD_BOOL *en);

/*******************************************************************************
* mtd_ptp_set_tai_pulse_delay
*
* DESCRIPTION:
*         Set pulse delay
*
* INPUTS:
*       port - port number
*        val - pulse delay value
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
MTD_STATUS mtd_set_tai_pulse_delay (MTD_U16 port, unsigned int val) ;

/*******************************************************************************
* mtd_ptp_get_tai_pulse_delay
*
* DESCRIPTION:
*         Get pulse delay
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
MTD_STATUS mtd_ptp_get_tai_pulse_delay 
(
  IN MTD_U16 port
);

/*******************************************************************************
* mtd_ptp_set_tai_clk_delay_en
*
* DESCRIPTION:
*         Set clock delay enable. If set to 1, clk_delay will be used to compensate
*         TOD alignment clock delay
*
* INPUTS:
*       port - port number
*        en - clk_delay 
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
MTD_STATUS mtd_set_tai_clk_delay_en (MTD_U16 port, MTD_BOOL en);

/*******************************************************************************
* mtd_ptp_get_tai_clk_delay_en
*
* DESCRIPTION:
*         Get clock delay enable. If set to 1, clk_delay will be used to compensate
*         TOD alignment clock delay
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*        en - clk_delay 
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_tai_clk_delay_en (MTD_U16 port, MTD_BOOL *en);

/*******************************************************************************
* mtd_ptp_set_tai_clk_delay
*
* DESCRIPTION:
*         Set clock delay
*
* INPUTS:
*       port - port number
*        val - pulse delay value
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
MTD_STATUS mtd_set_tai_clk_delay (MTD_U16 port, unsigned int val);

/*******************************************************************************
* mtd_ptp_get_tai_clk_delay
*
* DESCRIPTION:
*         Get clock delay
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
MTD_STATUS mtd_ptp_get_tai_clk_delay 
(
  IN MTD_U16 port
);

/*******************************************************************************
* mtd_ptp_enable_tai
*
* DESCRIPTION:
*         Enable TAI
*
* INPUTS:
*      port - port number
*      kpTodCfg    - keep original TOD comfiguration
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
MTD_STATUS mtd_ptp_enable_tai 
(
  IN MTD_U16 port,
  IN unsigned int kpTodCfg
);

/*******************************************************************************
* mtd_ptp_disable_tai
*
* DESCRIPTION:
*         Disable TAI
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*      kpTodCfg    - keep original TOD comfiguration
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_disable_tai 
(
  IN MTD_U16 port,
  OUT unsigned int *kpTodCfg
);

/*******************************************************************************
* mtd_ptp_tai_get_timer_operation
*
* DESCRIPTION:
*         Get tod function timer operation
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       timerOp - timer operation
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_tai_get_timer_operation 
(
  IN MTD_U16 port,
  OUT MTD_TOD_FUNC_TIMER_OP *timerOp
);

/*******************************************************************************
* mtd_ptp_tai_set_timer_operation
*
* DESCRIPTION:
*         Set tod function timer operation
*
* INPUTS:
*       port - port number
*       timerOp - timer operation
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
MTD_STATUS mtd_ptp_tai_set_timer_operation 
(
  IN MTD_U16 port,
  IN MTD_TOD_FUNC_TIMER_OP timerOp
);

/*******************************************************************************
* mtd_ptp_tai_set_pulse_width
*
* DESCRIPTION:
*         Set pulse width
*
* INPUTS:
*       port - port number
*       width_ns - width nanoseconds
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
MTD_STATUS mtd_ptp_tai_set_pulse_width 
(
  IN MTD_U16 port,
  IN unsigned int width_ns
);

/*******************************************************************************
* mtd_ptp_tai_get_pulse_width
*
* DESCRIPTION:
*         Get pulse width
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       width_ns - width nanoseconds
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_ptp_tai_get_pulse_width 
(
  IN MTD_U16 port,
  OUT unsigned int *width_ns
);

/*******************************************************************************
* mtd_ptp_tai_set_trig_gen_en
*
* DESCRIPTION:
*         Set enable trig generator gen
*
* INPUTS:
*       port - port number
*       bitval - 
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
MTD_STATUS mtd_ptp_tai_set_trig_gen_en 
(
  IN MTD_U16 port,
  IN int bitval
);

/*******************************************************************************
* mtd_ptp_get_pulse_gen
*
* DESCRIPTION:
*        Get pulse generation setup (master)
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       width_ns - width nanoseconds
*       trigsec - trigger time seconds
*       trignsec - trigger time nenoseconds
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
/* get pulse generation setup (master) */
MTD_STATUS mtd_ptp_get_pulse_gen (MTD_U16 port, unsigned int* width_ns, unsigned int* trigsec, unsigned int* trignsec);

/*******************************************************************************
* mtd_get_ptp_intr_msk
*
* DESCRIPTION:
*         Get new PTP interrupt mask.
*
* INPUTS:
*       port - port number
*       path  - NewPtp block number: igr or egr.
*
* OUTPUTS:
*       mask  - New PTP interrupt mask.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_ptp_intr_msk ( MTD_U16 port, MTD_PTP_Blk path, unsigned int *mask);

/*******************************************************************************
* mtd_disable_ptp_watchdog_timer
*
* DESCRIPTION:
*         Set new PTP mtd_ptp_watchdog_timer disable.
*
* INPUTS:
*       port - port number
*       path  - NewPtp block number: igr or egr.
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
MTD_STATUS mtd_disable_ptp_watchdog_timer ( MTD_U16 port, MTD_PTP_Blk path);

/*******************************************************************************
* mtd_clear_ptp_interrupts
*
* DESCRIPTION:
*         Clear new PTP interrupts.
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
MTD_STATUS mtd_clear_ptp_interrupts ( MTD_U16 port);

/*******************************************************************************
* mtd_set_tai_intr_msk
*
* DESCRIPTION:
*         Set new PTP TAI interrupt mask.
*
* INPUTS:
*       port - port number
*       mask  - New PTP TAI interrupt mask.
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
MTD_STATUS mtd_set_tai_intr_msk (MTD_U16 port, unsigned int mask);

/*******************************************************************************
* mtd_get_tai_intr_msk
*
* DESCRIPTION:
*         Get new PTP TAI interrupt mask.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       mask  - New PTP TAI interrupt mask.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_tai_intr_msk (MTD_U16 port, unsigned int *mask);

/*******************************************************************************
* mtd_ptp_global_intr_en
*
* DESCRIPTION:
*         Set new PTP Global interrupt enable.
*
* INPUTS:
*       port - port number
*       en  - New PTP interrupt enable/disable.
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
MTD_STATUS mtd_ptp_global_intr_en ( MTD_U16 port, int en);

#if 0
/*******************************************************************************
* mtd_set_top_intr_msk
*
* DESCRIPTION:
*         Set new PTP top interrupt mask.
*
* INPUTS:
*       port - port number
*       mask  - New PTP top interrupt mask.
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
MTD_STATUS mtd_set_top_intr_msk (MTD_U16 port, unsigned int mask);

/*******************************************************************************
* mtd_get_top_intr_msk
*
* DESCRIPTION:
*         Get new PTP top interrupt mask.
*
* INPUTS:
*       port - port number
*
* OUTPUTS:
*       mask  - New PTP top interrupt mask.
*
* RETURNS:
*       MTD_OK          - on success
*       MTD_FAIL        - on error
*
* COMMENTS:
*
*******************************************************************************/
MTD_STATUS mtd_get_top_intr_msk (MTD_U16 port, unsigned int *mask);
#endif
/*******************************************************************************
* mtd_set_ptp_tai_tod
*
* DESCRIPTION:
*       Set TOD
*
* INPUTS:
*       port - port number
*       ns - nanoseconds of TOD 
*       sec_lo - low seconds of TOD
*       sec_hi - high seconds of TOD
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
/* set TOD */
MTD_STATUS mtd_set_ptp_tai_tod
(
  IN MTD_U16 port,
  IN unsigned int ns,
  IN unsigned int sec_lo,
  IN unsigned int sec_hi 
);

/*******************************************************************************
* mtd_prgm_ptp_lut_ent_msgType
*
* DESCRIPTION:
*         program an lut entry that matches on specified msgtype and actions
*        msgid: 0 - Sync, 1 - DelayReq, 2 - PdelayReq, 3 - PdelayResp
*               8 - FollowUp, 9 - DelayResp, A - PdelayRespFU, 
*               B - Announce, C - Signaling, D - Management
*               multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       msgId - PTP Message Id.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_ptp_lut_ent_msgType(MTD_U16 port, int idx, MTD_PTPv2_message_type msgId, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);

/*******************************************************************************
* mtd_prgm_ptp_lut_ent_domain_num
*
* DESCRIPTION:
*     program an lut entry that matches on specified domain number and actions
*     domain_num: domain number used as lut key
*     Action abreviation
*     DR - drop, INI - IniPiggyback, INS - InsertTST
*     SH - StampHigh, AA - AddAsymmetry, NO - no action
*     multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       domain_num - PTP domain number.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_ptp_lut_ent_domain_num(MTD_U16 port, int idx, int domain_num, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);

/*******************************************************************************
* mtd_prgm_ptp_lut_ent_transspec
*
* DESCRIPTION:
*         program an lut entry that matches on specified transspec and actions
*        multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       transspec - PTP transspec.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_ptp_lut_ent_transspec(MTD_U16 port, int idx, int transspec, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);

/*******************************************************************************
* mtd_prgm_lut_ent_ipv4
*
* DESCRIPTION:
*         program an lut entry that matches IPV4 and actions
*               multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_lut_ent_ipv4(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);

/*******************************************************************************
* mtd_prgm_lut_ent_ntp
*
* DESCRIPTION:
*         program an lut entry that matches NTP and actions
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*       ext_dev - extend device
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
MTD_STATUS mtd_prgm_lut_ent_ntp(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path, int ext_dev);

/*******************************************************************************
* mtd_prgm_lut_ent_ntp_list
*
* DESCRIPTION:
*         program an lut entry that matches NTP and actions
*               multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - List of Lut actions. The last action is MTD_PTP_Act_No_Action.
*       path - MTD_PTP_igr or MTD_PTP_egr.
*       ext_dev - extend device
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
MTD_STATUS mtd_prgm_lut_ent_ntp_list(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACT *action, MTD_PTP_Blk path, int ext_dev);

/*******************************************************************************
* mtd_prgm_lut_ent_ptpv2
*
* DESCRIPTION:
*         program an lut entry that matches PTPv2 and actions
*               multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_lut_ent_ptpv2(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);

/*******************************************************************************
* mtd_prgm_lut_ent_ptpv1
*
* DESCRIPTION:
*         program an lut entry that matches PTPv1 and actions
*               multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_lut_ent_ptpv1(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);

/* use the IP-in-IP for Y1731 */
/*******************************************************************************
* mtd_prgm_lut_ent_1731
*
* DESCRIPTION:
*         program an lut entry that matches Y1731 and actions
*               multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_lut_ent_1731(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);

/*******************************************************************************
* mtd_prgm_lut_ent_1731_opcode
*
* DESCRIPTION:
*         program an lut entry that matches the IP-in-IP for Y1731, Version PTP for opcode and actions 
*        multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       opcode - opcode on Y1731, Version PTP.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_lut_ent_1731_opcode(MTD_U16 port, int idx, int opcode, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);

/*******************************************************************************
* mtd_prgm_lut_ent_stag
*
* DESCRIPTION:
*         program an lut entry that matches stag and actions
*        multiple actions are defined in a list 
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_lut_ent_stag(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);

/*******************************************************************************
* mtd_prgm_lut_ent_always0
*
* DESCRIPTION:
*         program an lut entry that do nothing
*
* INPUTS:
*       port - port number
*       idx  - Lut entry number.
*       actions - Lut actions.
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
MTD_STATUS mtd_prgm_lut_ent_always0(MTD_U16 port, int idx, MTD_PTP_1STEP_LUT_ACTIONS actions, MTD_PTP_Blk path);


/*******************************************************************************
* mtd_get_ptp_tai
*
* DESCRIPTION:
*       This routine prints PTP TAI for debug.
*
* INPUTS:
*       None.
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
MTD_STATUS mtd_get_ptp_tai(void);

#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* __MTDPTP1STEP_H */
