/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/
/**
********************************************************************************
* @file mcdInternalIpcDefs.h
*
* @brief Definitions for IPC feature
*
* @version   1
********************************************************************************
*/

#ifndef __mcdInternalIpcDefs_H
#define __mcdInternalIpcDefs_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcdApiTypes.h"
/**************************** Definition *************************************************/
#define MCD_IPC_HI_PRI_RX_CH_ID           0
#define MCD_IPC_LO_PRI_RX_CH_ID           1
#define MCD_IPC_TX_0_CH_ID                2
#define MCD_IPC_TX_1_CH_ID                3
#define MCD_IPC_TX_2_CH_ID                4
#define MCD_IPC_TX_3_CH_ID                5
#define MCD_IPC_CH_NUM                    6

#define MCD_IPC_MSG_INFO_LENGTH           4  /* 4 bytes for msg info (dev size, type & queue) */
#define MCD_IPC_MAX_MSG_DATA_LENGTH       56
#define MCD_IPC_PORT_GEN_DATA_LENGTH      16 /* general data includes 4 parameters :
                                                   devNum;
                                                   portGroup;
                                                   phyPortNum;
                                                   portMode;*/

#define MCD_IPC_PORT_MISC_DATA_LENGTH    (MCD_IPC_MAX_MSG_DATA_LENGTH - MCD_IPC_PORT_GEN_DATA_LENGTH)

#define MCD_MAX_IPC_CTRL_MSG_LENGTH      (MCD_IPC_MAX_MSG_DATA_LENGTH + MCD_IPC_MSG_INFO_LENGTH)
#define MCD_MAX_IPC_REPLY_LENGTH          40 /* the number should be updated after all APIs are implemented
                                                   = max length of reply data - now max is:
                                                   status per serdes in port = MCD_BOOL*MCD_MAX_LANES_NUM_PER_PORT */

#define MCD_MAX_HOST2SCPU_REQ_MSG_NUM      6
#define MCD_MAX_SCPU2HOST_REPLY_QUEUE_NUM  MCD_MAX_HOST2SCPU_REQ_MSG_NUM

#define MCD_IPC_FREE_QUEUE                0
#define MCD_IPC_QUEUE_BUSY                0xff

#define MCD_IPC_MAX_PORT_NUM              72

#define MCD_WRONG_IPC_MSG_TYPE            0xF0

#define MCD_MAX_LANES_NUM_PER_PORT        4

#define MCD_MAN_TUNE_CTLE_CONFIG_OVERRIDE_LOOPWIDTH_SHIFT 4
#define MCD_MAN_TUNE_CTLE_CONFIG_OVERRIDE_HF_SHIFT 4
#define MCD_MAN_TUNE_ETL_CONFIG_OVERRIDE_ENABLE_SHIFT 7
#define MCD_MAN_TX_TUNE_EMPH0_OVERRIDE_ENABLE_SHIFT 5
#define MCD_MAN_TX_TUNE_EMPH1_OVERRIDE_ENABLE_SHIFT 10

#define MCD_MAN_TUNE_CTLE_CONFIG_10G_INDEX_CNS 0
#define MCD_MAN_TUNE_CTLE_CONFIG_25G_INDEX_CNS 1

typedef enum
{
    MCD_IPC_HIGH_PRI_QUEUE,
    MCD_IPC_LOW_PRI_QUEUE

}MCD_IPC_PRIORITY_QUEUE;

typedef enum
{
    /* AP messages */
    MCD_IPC_PORT_AP_ENABLE_MSG,
    MCD_IPC_PORT_AP_DISABLE_MSG,
    MCD_IPC_PORT_AP_SYS_CFG_VALID_MSG,
    MCD_IPC_PORT_AP_CFG_GET_MSG,
    MCD_IPC_PORT_AP_STATUS_MSG,
    MCD_IPC_PORT_AP_STATS_MSG,
    MCD_IPC_PORT_AP_STATS_RESET_MSG,
    MCD_IPC_PORT_AP_INTROP_GET_MSG,
    MCD_IPC_PORT_AP_INTROP_SET_MSG,
    MCD_IPC_PORT_AP_DEBUG_GET_MSG,
    MCD_IPC_PORT_PARAMS_MSG,
    MCD_IPC_PORT_AVAGO_SERDES_INIT_MSG,
    MCD_IPC_PORT_AVAGO_GUI_SET_MSG,
    MCD_IPC_PORT_AVAGO_SERDES_RESET_DATA_MSG,
    MCD_IPC_VOS_OVERRIDE_PARAMS_DATA_MSG,
    MCD_IPC_VOS_OVERRIDE_MODE_SET_MSG,
    MCD_IPC_EXECUTE_CMDLINE_MSG,
    MCD_IPC_NOOP_MSG,
    MCD_IPC_PORT_INIT_MSG,
    MCD_IPC_PORT_RESET_MSG,
    MCD_IPC_PORT_RESET_EXT_MSG,
    MCD_IPC_HWS_LOG_GET_MSG,
    MCD_IPC_PORT_AUTO_TUNE_SET_EXT_MSG,
    MCD_IPC_PORT_AUTO_TUNE_STOP_MSG,
    MCD_IPC_PORT_AUTO_TUNE_STATE_CHK_MSG,
    MCD_IPC_PORT_LINK_STATUS_GET_MSG,
    MCD_IPC_PORT_FEC_CONFIG_GET_MSG,
    MCD_IPC_PORT_TX_ENABLE_GET_MSG,
    MCD_IPC_PORT_SERDES_RESET_MSG,
    MCD_IPC_PORT_POLARITY_SET_MSG,
    MCD_IPC_PORT_FEC_CONFIG_MSG,
    MCD_IPC_PORT_TX_ENABLE_MSG,
    MCD_IPC_PORT_SIGNAL_DETECT_GET_MSG,
    MCD_IPC_PORT_CDR_LOCK_STATUS_GET_MSG,
    MCD_IPC_PORT_LOOPBACK_SET_MSG,
    MCD_IPC_PORT_LOOPBACK_STATUS_GET_MSG,
    MCD_IPC_PORT_PPM_SET_MSG,
    MCD_IPC_PORT_PPM_GET_MSG,
    MCD_IPC_PORT_IF_GET_MSG,
    MCD_IPC_PORT_SERDES_MANUAL_RX_CONFIG_MSG,
    MCD_IPC_PORT_SERDES_MANUAL_TX_CONFIG_MSG,
    MCD_IPC_PORT_PCS_ACTIVE_STATUS_GET_CONFIG_MSG,
    MCD_IPC_PORT_FC_STATE_SET_MSG,
    MCD_IPC_PORT_SERVICE_CPU_UART_ENABLE_SET_MSG,
    MCD_IPC_PORT_SERVICE_CPU_UART_ENABLE_GET_MSG,
    MCD_IPC_RX_CLOCK_CTRL_PIN_SET_MSG,
    MCD_IPC_PORT_POLLING_START_MSG,
    MCD_IPC_PORT_POLLING_STOP_MSG,
    MCD_IPC_PORT_POLLING_GET_LINK_ON_BITMAP_MSG,
    MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_MSG,
    MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_MSG,

    MCD_IPC_LAST_CTRL_MSG_TYPE

}MCD_IPC_CTRL_MSG_DEF_TYPE;


typedef struct
{
    MCD_U16 portGroup;
    MCD_U16 phyPortNum;
    MCD_U32 advMode;
    MCD_U16 options;
    MCD_U8 laneNum;
    MCD_U8 pcsNum;
    MCD_U8 macNum;
    MCD_U8  polarityVector;
    MCD_U32 retimerMode;
    MCD_U16 rxRemapVector;
    MCD_U16 txRemapVector;
    MCD_BOOL enSdTuningApRes;
}MCD_IPC_PORT_AP_DATA_STRUCT;

typedef struct
{
    MCD_U32 state;

}MCD_IPC_PORT_SERDES_GUI_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/ portMode;
    MCD_U16 attrBitMask;
    MCD_U16 txDisDuration;
    MCD_U16 abilityDuration;
    MCD_U16 abilityMaxInterval;
    MCD_U16 abilityFailMaxInterval;
    MCD_U16 apLinkDuration;
    MCD_U16 apLinkMaxInterval;
    MCD_U16 pdLinkDuration;
    MCD_U16 pdLinkMaxInterval;

}MCD_IPC_PORT_AP_INTROP_STRUCT;

/* General structure for all get/check status functions*/
typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*_PORT_STANDARD*/       portMode;
}MCD_IPC_PORT_INFO_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_U8                           portMiscData[MCD_IPC_PORT_MISC_DATA_LENGTH];
}MCD_IPC_PORT_GENERAL_STRUCT;

typedef struct
{
    MCD_U16                            portGroup;
    MCD_U16                            phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/      portStandard;
    MCD_U32 /*MCD_PORT_MAC_TYPE*/      portMacType;
    MCD_U32                            portMacNumber;
    MCD_U32 /*MCD_PORT_PCS_TYPE*/      portPcsType;
    MCD_U32                            portPcsNumber;
    MCD_U32 /*MCD_PORT_FEC_MODE*/      portFecMode;
    MCD_U32 /*MCD_SERDES_SPEED*/       serdesSpeed;
    MCD_U8                             firstLaneNum;
    MCD_U8                             numOfActLanes;
    MCD_U8                             activeLanesList[MCD_MAX_LANES_NUM_PER_PORT];
    MCD_U32 /*MCD_SERDES_MEDIA*/       serdesMediaType;
    MCD_U32 /*MCD_SERDES_10B_MODE*/    serdes10BitStatus;

}MCD_IPC_PORT_PARAMS_DATA_STRUCT;

typedef struct
{
    MCD_U16    portGroup;
    MCD_U16    phyPortNum;
    MCD_U32    serdesSpeed;
    MCD_U16    fieldOverrideBmp;
    MCD_U16    squelch;
    MCD_U8     dcGain;
    MCD_U8     lfHf; /* bits 0-3 = LF, bits 4-7 = HF */
    MCD_U8     bandLoopWidth; /* bits 0-3 = bandWidth, bits 4-7 = loopBandwidth */
    MCD_U8     etlMinDelay;
    MCD_U8     etlMaxDelay;   /* bits 0-7 = max delay , bit 7 = etl enable value*/
}MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_STRUCT;

typedef struct
{
    MCD_U16    portGroup;
    MCD_U16    phyPortNum;
    MCD_U32    serdesSpeed;
    MCD_U16    serdesTxParams;
    MCD_U8     txOverrideBmp;

}MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_STRUCT;

typedef struct
{
    MCD_U16                              portGroup;
    MCD_U16                              phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD */       portMode;
    MCD_U32 /*MCD_BOOL*/                 lbPort;
    MCD_U32 /*MCD_REF_CLOCK_SUP_VAL*/    refClock;
    MCD_U32 /*MCD_REF_CLOCK_SOURCE*/     refClockSource;

}MCD_IPC_PORT_INIT_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_U32 /*MCD_PORT_ACTION*/      action;

}MCD_IPC_PORT_RESET_DATA_STRUCT;

typedef struct
{
    MCD_U16                                portGroup;
    MCD_U16                                phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/          portMode;
    MCD_U32 /*MCD_PORT_AUTO_TUNE_MODE*/    portTuningMode;
    MCD_U32                                optAlgoMask;

}MCD_IPC_PORT_AUTO_TUNE_SET_EXT_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_U32 /*MCD_BOOL*/             stopRx;
    MCD_U32 /*MCD_BOOL*/             stopTx;

}MCD_IPC_PORT_AUTO_TUNE_STOP_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_32                           txInvMask;
    MCD_32                           rxInvMask;

}MCD_IPC_PORT_POLARITY_SET_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_U32 /*MCD_BOOL*/             enable;

}MCD_IPC_PORT_TX_ENABLE_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_U32 /*MCD_BOOL*/             portFecEn;

}MCD_IPC_PORT_FEC_CONFIG_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_U32 /*MCD_UNIT*/             lpPlace;
    MCD_U32 /*MCD_PORT_LB_TYPE*/     lbType;

}MCD_IPC_PORT_LOOPBACK_SET_DATA_STRUCT;

typedef struct
{
    MCD_U16                                  portGroup;
    MCD_U16                                  phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/            portMode;
    MCD_U32 /*MCD_PORT_FLOW_CONTROL_ENT*/    fcState;

}MCD_IPC_PORT_FLOW_CONTROL_SET_DATA_STRUCT;

typedef struct
{
    MCD_U32 /*MCD_BOOL*/                    enable;

}MCD_IPC_PORT_SERVICE_CPU_UART_ENABLE_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_U32 /*MCD_UNIT*/             lpPlace;

}MCD_IPC_PORT_LOOPBACK_GET_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_U32 /*MCD_PPM_VALUE*/        portPPM;

}MCD_IPC_PORT_PPM_SET_DATA_STRUCT;

typedef struct
{
    MCD_U16 portGroup;
    MCD_U16 phyPortNum;

}MCD_IPC_PORT_IF_GET_DATA_STRUCT;

typedef struct
{
    MCD_U16                               portGroup;
    MCD_U16                               serdesNum;
    MCD_U32 /*MCD_SERDES_TYPE*/           serdesType;
    MCD_U32 /*MCD_PORT_MAN_TUNE_MODE*/    portTuningMode;
    MCD_U32                               sqlch;
    MCD_U32                               ffeRes;
    MCD_U32                               ffeCap;
    MCD_U32 /*MCD_BOOL*/                  dfeEn;
    MCD_U32                               alig;

}MCD_IPC_PORT_SERDES_MANUAL_RX_CONFIG_DATA_STRUCT;

typedef struct
{
    MCD_U16                        portGroup;
    MCD_U16                        serdesNum;
    MCD_U32 /*MCD_SERDES_TYPE*/    serdesType;
    MCD_U32                        txAmp;
    MCD_U32 /*MCD_BOOL*/           txAmpAdj;
    MCD_U32                        emph0;
    MCD_U32                        emph1;
    MCD_U32 /*MCD_BOOL*/           txAmpShft;

}MCD_IPC_PORT_SERDES_MANUAL_TX_CONFIG_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;

}MCD_IPC_PORT_PCS_ACTIVE_STATUS_GET_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_RX_CLOCK_CTRL_TYPE           clckCtrlPin;


}MCD_IPC_RX_CLOCK_CTRL_DATA_STRUCT;

typedef struct
{
    MCD_U32 data;
}MCD_IPC_NOOP_DATA_STRUCT;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_U32                          vosOverrideParamsBufferPtr[8];
    MCD_U32                          vosOverrideParamsBufferIdx;
    MCD_U32                          vosOverrideParamsBufferLength;

}MCD_IPC_VOS_OVERRIDE_PARAMS;

typedef struct
{
    MCD_U16                          portGroup;
    MCD_U16                          phyPortNum;
    MCD_U32 /*MCD_PORT_STANDARD*/    portMode;
    MCD_BOOL                         vosOverrideMode;

}MCD_IPC_VOS_OVERRIDE_MODE_STRUCT;

typedef struct
{
    MCD_U16                       mdioPort;
    MCD_U16                       retimerMode;
    MCD_U16 /*MCD_SERDES_SPEED*/  lineSerdesSpeed;
    MCD_U16 /*MCD_SERDES_SPEED*/  hostSerdesSpeed;
    MCD_U16                       lineSerdesBitmap;
    MCD_U16                       hostSerdesBitmap;
/*  add ap parameters */
    MCD_U16                       laneNum;/*also used as pcsNum*/
    MCD_U16                       options;
    MCD_U32                       advMode;
    MCD_BOOL                      retimerWithAp;
    MCD_U32                       polarityVector;
    MCD_U16                       hostRxRemapVector;
    MCD_U16                       hostTxRemapVector;
    MCD_U16                       lineRxRemapVector;
    MCD_U16                       lineTxRemapVector;
    MCD_U32                       minEyeThreshold;
    MCD_U32                       maxEyeThreshold;
    MCD_U32                       lfLowThreshold;
    MCD_U32                       lfHighThreshold;
    MCD_U32                       hfThreshold;
    MCD_U16                       noPpmMode;
    MCD_U8                        calibrationMode;
    MCD_U8                        calibrationAlgo;

} MCD_IPC_POLLING_PORT_LINK_STATUS_START_STC;

typedef struct
{
    MCD_U16                       mdioPort;

} MCD_IPC_POLLING_PORT_LINK_STATUS_STOP_STC;

typedef union
{
    MCD_U8                                           ctrlData[MCD_IPC_MAX_MSG_DATA_LENGTH];
    MCD_IPC_PORT_GENERAL_STRUCT                      portGeneral;
    MCD_IPC_PORT_PARAMS_DATA_STRUCT                  portParams;
    MCD_IPC_PORT_INIT_DATA_STRUCT                    portInit;
    MCD_IPC_PORT_RESET_DATA_STRUCT                   portReset;
    MCD_IPC_PORT_AUTO_TUNE_SET_EXT_DATA_STRUCT       portAutoTuneSetExt;
    MCD_IPC_PORT_INFO_STRUCT                         portLinkStatus;
    MCD_IPC_PORT_AUTO_TUNE_STOP_DATA_STRUCT          portAutoTuneStop;
    MCD_IPC_PORT_INFO_STRUCT                         portAutoTuneStateChk;
    MCD_IPC_PORT_INFO_STRUCT                         portTxEnableGet;
    MCD_IPC_PORT_INFO_STRUCT                         portFecConfigGet;
    MCD_IPC_PORT_POLARITY_SET_DATA_STRUCT            portPolaritySet;
    MCD_IPC_PORT_TX_ENABLE_DATA_STRUCT               portTxEnableData;
    MCD_IPC_PORT_INFO_STRUCT                         portSignalDetectGet;
    MCD_IPC_PORT_INFO_STRUCT                         portCdrLockStatus;
    MCD_IPC_PORT_FEC_CONFIG_DATA_STRUCT              portFecConfig;
    MCD_IPC_PORT_LOOPBACK_SET_DATA_STRUCT            portLoopbackSet;
    MCD_IPC_PORT_LOOPBACK_GET_DATA_STRUCT            portLoopbackGet;
    MCD_IPC_PORT_PPM_SET_DATA_STRUCT                 portPPMSet;
    MCD_IPC_PORT_INFO_STRUCT                         portPPMGet;
    MCD_IPC_PORT_IF_GET_DATA_STRUCT                  portInterfaceGet;
    MCD_IPC_PORT_SERDES_MANUAL_RX_CONFIG_DATA_STRUCT serdesManualRxConfig;
    MCD_IPC_PORT_SERDES_MANUAL_TX_CONFIG_DATA_STRUCT serdesManualTxConfig;
    MCD_IPC_PORT_PCS_ACTIVE_STATUS_GET_DATA_STRUCT   portPcsActiveStatus;
    MCD_IPC_PORT_FLOW_CONTROL_SET_DATA_STRUCT        portFcStateSet;
    MCD_IPC_PORT_AP_DATA_STRUCT                      apConfig;
    MCD_IPC_PORT_INFO_STRUCT                         apSysConfig;
    MCD_IPC_PORT_INFO_STRUCT                         apStatusGet;
    MCD_IPC_PORT_INFO_STRUCT                         apStatsGet;
    MCD_IPC_PORT_INFO_STRUCT                         apStatsReset;
    MCD_IPC_PORT_INFO_STRUCT                         apIntropGet;
    MCD_IPC_PORT_AP_INTROP_STRUCT                    apIntropSet;
    MCD_IPC_PORT_INFO_STRUCT                         logGet;
    MCD_IPC_PORT_INFO_STRUCT                         avagoAddrGet;
    MCD_IPC_PORT_SERDES_GUI_STRUCT                   avagoGuiSet;
    MCD_IPC_PORT_SERVICE_CPU_UART_ENABLE_DATA_STRUCT serviceCpuUartEnableSet;
    MCD_IPC_PORT_SERVICE_CPU_UART_ENABLE_DATA_STRUCT serviceCpuUartEnableGet;
    MCD_IPC_NOOP_DATA_STRUCT                         noop;
    MCD_IPC_PORT_INFO_STRUCT                         avagoAaplInit;
    MCD_IPC_VOS_OVERRIDE_PARAMS                      vosOverrideParams;
    MCD_IPC_VOS_OVERRIDE_MODE_STRUCT                 vosOverrideModeSet;
    MCD_IPC_RX_CLOCK_CTRL_DATA_STRUCT                rxClockControl;
    MCD_IPC_POLLING_PORT_LINK_STATUS_START_STC       pollingPortLinkStatusStart;
    MCD_IPC_POLLING_PORT_LINK_STATUS_STOP_STC        pollingPortLinkStatusStop;
    MCD_IPC_PORT_SERDES_RX_CONFIG_OVERRIDE_STRUCT    portSerdesRxConfigOverride;
    MCD_IPC_PORT_SERDES_TX_CONFIG_OVERRIDE_STRUCT    portSerdesTxConfigOverride;


}MCD_IPC_MSG_API_PARAMS;


typedef struct
{
    MCD_U32 /*MCD_AUTO_TUNE_STATUS*/ rxTune;
    MCD_U32 /*MCD_AUTO_TUNE_STATUS*/ txTune;
}MCD_IPC_PORT_REPLY_AUTO_TUNE_STATE_CHK;

typedef struct
{
    MCD_U32 /*MCD_BOOL*/ status;

}MCD_IPC_PORT_REPLY_STATUS_GET;

typedef struct
{
    MCD_U32 /*MCD_BOOL*/ status[MCD_MAX_LANES_NUM_PER_PORT];

}MCD_IPC_PORT_REPLY_PER_SERDES_STATUS_GET;

typedef struct
{
    MCD_U32 ifNum;
    MCD_U16 capability;
    MCD_U16 options;

}MCD_IPC_PORT_REPLY_AP_CFG_GET;

typedef struct
{
    MCD_U16 state;
    MCD_U16 status;
    MCD_U16 laneNum;
    MCD_U16 ARMSmStatus;
    MCD_U32 hcdStatus;

}MCD_IPC_PORT_REPLY_AP_STATUS_GET;

typedef struct
{
    MCD_U16 txDisCnt;
    MCD_U16 abilityCnt;
    MCD_U16 abilitySuccessCnt;
    MCD_U16 linkFailCnt;
    MCD_U16 linkSuccessCnt;
    MCD_U32 hcdResoultionTime;
    MCD_U32 linkUpTime;

}MCD_IPC_PORT_REPLY_AP_STATS_GET;

typedef struct
{
    MCD_U16 txDisDuration;
    MCD_U16 abilityDuration;
    MCD_U16 abilityMaxInterval;
    MCD_U16 abilityFailMaxInterval;
    MCD_U16 apLinkDuration;
    MCD_U16 apLinkMaxInterval;
    MCD_U16 pdLinkDuration;
    MCD_U16 pdLinkMaxInterval;

}MCD_IPC_PORT_REPLY_AP_INTROP_GET;

typedef struct
{
    MCD_U32 fwBaseAddr;
    MCD_U32 logBaseAddr;
    MCD_U32 logCountAddr;
    MCD_U32 logPointerAddr;
    MCD_U32 logResetAddr;

}MCD_IPC_PORT_REPLY_AP_DEBUG_GET;

typedef struct
{
    MCD_U32 /*MCD_BOOL*/              enable;

}MCD_IPC_PORT_REPLY_SERVICE_CPU_UART_ENABLE_GET;

typedef struct
{
    MCD_U32 data;
}MCD_IPC_NOOP_REPLY;

typedef struct
{
    MCD_U32 results;

}MCD_IPC_PORT_REPLY_RESULT;

typedef struct
{
    MCD_U32 /*MCD_PORT_LB_TYPE*/ lbType;

}MCD_IPC_PORT_REPLY_LOOPBACK_STATUS_GET;

typedef struct
{
    MCD_U32 /*MCD_PPM_VALUE*/ portPpm;

}MCD_IPC_PORT_REPLY_PPM_GET;

typedef struct
{
    MCD_U32 /*MCD_PORT_STANDARD*/ portIf;

}MCD_IPC_PORT_REPLY_IF_GET;

typedef struct
{
    MCD_U32 fwBaseAddr;
    MCD_U32 logBaseAddr;
    MCD_U32 logCountAddr;
    MCD_U32 logPointerAddr;
    MCD_U32 logResetAddr;
    MCD_U32 pollingDbAddr;

}MCD_IPC_LOG_GET;

typedef struct
{
    MCD_U32 addr;
    MCD_U32 size;

}MCD_IPC_PORT_REPLY_AVAGO_AAPL_GET;

typedef union
{
    MCD_U8                                         resultData[MCD_MAX_IPC_REPLY_LENGTH];
    MCD_IPC_PORT_REPLY_AUTO_TUNE_STATE_CHK         portAutoTuneStateChk;
    MCD_IPC_PORT_REPLY_STATUS_GET                  portStatusGet;
    MCD_IPC_PORT_REPLY_RESULT                      portReplyGet;
    MCD_IPC_PORT_REPLY_PER_SERDES_STATUS_GET       portSerdesTxEnableGet;
    MCD_IPC_PORT_REPLY_LOOPBACK_STATUS_GET         portLoopbackStatusGet;
    MCD_IPC_PORT_REPLY_PPM_GET                     portPpmGet;
    MCD_IPC_PORT_REPLY_IF_GET                      portIfGet;
    MCD_IPC_PORT_REPLY_PER_SERDES_STATUS_GET       portSerdesSignalDetectGet;
    MCD_IPC_PORT_REPLY_PER_SERDES_STATUS_GET       portSerdesCdrLockStatusGet;
    MCD_IPC_PORT_REPLY_AP_CFG_GET                  portApCfgGet;
    MCD_IPC_PORT_REPLY_AP_STATUS_GET               portApStatusGet;
    MCD_IPC_PORT_REPLY_AP_STATS_GET                portApStatsGet;
    MCD_IPC_PORT_REPLY_AP_INTROP_GET               portApIntropGet;
    MCD_IPC_LOG_GET                                logGet;
    MCD_IPC_PORT_REPLY_SERVICE_CPU_UART_ENABLE_GET portServiceCpuUartEnableGet;
    MCD_IPC_NOOP_REPLY                             noopReply;
    MCD_IPC_PORT_REPLY_AVAGO_AAPL_GET              portAvagoAaplGet;

}MCD_IPC_REPLY_MSG_DATA_TYPE;


typedef struct
{
    MCD_U8                      devNum;
    MCD_U8                      ctrlMsgType;
    MCD_U8                      msgQueueId;
    MCD_U8                      msgLength;
    MCD_IPC_MSG_API_PARAMS      msgData;

 }MCD_IPC_CTRL_MSG_STRUCT;


typedef struct
{
    MCD_U32                         returnCode;
    MCD_U32                         replyTo;
    MCD_IPC_REPLY_MSG_DATA_TYPE     readData;

}MCD_IPC_REPLY_MSG_STRUCT;

typedef struct
{
    MCD_U32 mcdHostRxMsgCount[MCD_IPC_LAST_CTRL_MSG_TYPE];
    MCD_U32 mcdHostTxMsgCount[MCD_IPC_LAST_CTRL_MSG_TYPE];

    MCD_U32 mcdPortIpcFailureCount[MCD_IPC_MAX_PORT_NUM];
    MCD_U32 mcdIpcGenFailureCount;

}MCD_IPC_STATISTICS_STRUCT;

#ifdef __cplusplus
}
#endif

#endif /* __mcdInternalIpcDefs_H */




