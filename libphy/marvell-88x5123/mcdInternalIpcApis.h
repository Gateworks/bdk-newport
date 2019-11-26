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
* @file mcdInternalIpcApis.h
*
* @brief Definitions for IPC feature
*
* @version   1
********************************************************************************
*/

#ifndef __mcdInternalIpcApis_H
#define __mcdInternalIpcApis_H

#include "mcdHwSerdesCntl.h"

#if defined(CPU_BE) || defined(MV_CPU_BE)
#define MCD_IPC_CNV_ENABLE
/*#define MCD_IPC_CNV_TEST*/
#endif

#ifdef MCD_IPC_CNV_ENABLE

/* ------------------------------------------------------------------- */
/* Big Endian and Little Endian CPUs shared memory based IPC support.  */
/* ------------------------------------------------------------------- */
/* IPC mcdInternalShmIpcSend and mcdInternalShmIpcRecv message API     */
/* read and write shared memory using functions that copy 32-bit words */
/* with byte swapping.                                                 */
/* The IPC control data delivered in correct format but message        */
/* payload should be prepared to match the other CPU format after byte */
/* swapping.                                                           */

/* order of fields in this enum as in structure describes data */
typedef enum
{
    MCD_IPC_CNV_WORD32_FORMAT_U32_E,       /* 32-bit field                    */
    MCD_IPC_CNV_WORD32_FORMAT_2U16_E,      /* 2 16-bit fields                 */
    MCD_IPC_CNV_WORD32_FORMAT_U16_2U8_E,   /* 16-bit field and 2 8-bit fields */
    MCD_IPC_CNV_WORD32_FORMAT_2U8_U16_E,   /* 2 8-bit fields and 16-bit field */
    MCD_IPC_CNV_WORD32_FORMAT_4U8_E        /* 4 8-bit fields                  */
} MCD_IPC_CNV_WORD32_FORMAT_ENT;

/* ----------------------------------------------- */
/* This function converts both                     */
/* Big Endian to Swapped Little Endian and         */
/* Little Endian to Swapped Big Endian             */
MCD_U32 mcdInternalIpcBeToSwappedLeConvert
(
    IN MCD_IPC_CNV_WORD32_FORMAT_ENT wordFormat,
    IN MCD_U32                       wordValue
);

/* ----------------------------------------------- */
/* This function converts both                     */
/* Swapped Little Endian to Big Endian and         */
/* Swapped Big Endian to Little Endian             */
MCD_U32 mcdInternalIpcSwappedLeToBeConvert
(
    IN MCD_IPC_CNV_WORD32_FORMAT_ENT wordFormat,
    IN MCD_U32                       wordValue
);

#endif /*MCD_IPC_CNV_ENABLE*/

/**
* @internal mcdInternalIpcDbInit function
* @endinternal
*
* @brief   IPC database initialization
*
* @param[in] pDev
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalIpcDbInit
(
    IN MCD_DEV_PTR pDev
);

/**
* @internal mcdServiceCpuFwPostInit function
* @endinternal
*
* @brief   Init Serdes Configuration DB and Log support on service CPU.
*
* @param[in] pDev
*                                      phyPortNum  - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdServiceCpuFwPostInit
(
    IN MCD_DEV_PTR pDev
);

/**
* @internal mcdInternalServiceCpuMsgSend function
* @endinternal
*
* @brief   Send message to Service CPU via IPC channel
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalServiceCpuMsgSend
(
    IN MCD_DEV_PTR pDev,
    IN unsigned int channel,
    IN char* msg
);

/**
* @internal mcdInternalServiceCpuMsgRecv function
* @endinternal
*
* @brief   Receive message from Service CPU via IPC channel
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalServiceCpuMsgRecv
(
    IN  MCD_DEV_PTR pDev,
    IN  unsigned int channel,
    OUT char* msg
);

/**
* @internal mcdInternalIpcSendRequestAndGetReply function
* @endinternal
*
* @brief   Gets reply from HW Services to the Host
*
* @param[in] requestMsg               - pointer to request message
* @param[in] msgId                    - message ID
*
* @param[out] replyData                - pointer to reply message
*
* @retval 0                        - on success
* @retval 1                        - on error,
*/
MCD_STATUS mcdInternalIpcSendRequestAndGetReply
(
    IN  MCD_DEV_PTR                 pDev,
    IN  MCD_IPC_CTRL_MSG_STRUCT     *requestMsg,
    OUT MCD_IPC_REPLY_MSG_STRUCT    *replyData,
    IN  MCD_U32                     msgLength,
    IN  MCD_IPC_CTRL_MSG_DEF_TYPE   msgId
);


/**
* @internal mcdSerdesCfgAddrGetIpc function
* @endinternal
*
* @brief   Return Serdes Configuration structure address
*
* @param[in] pDev
*
* @param[out] avagoCfgAddr             - Serdes Configuration structure address
* @param[out] avagoCfgSize             - Serdes Configuration structure size
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdSerdesCfgAddrGetIpc
(
   IN  MCD_DEV_PTR                 pDev,
   OUT MCD_U32                     *avagoCfgAddr,
   OUT MCD_U32                     *avagoCfgSize
);

/**
* @internal mcdSerdesAaplInitIpc function
* @endinternal
*
* @brief   Init Serdes Configuration structure pointers parameters, on service CPU, with NULL values.
*
* @param[in] pDev
*                                      phyPortNum  - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdSerdesAaplInitIpc
(
    MCD_DEV_PTR                 pDev
);

/**
* @internal mcdInternalPortInitIpc function
* @endinternal
*
* @brief   Sends to FW request to init physical port.
*
* @param[in] pDev
* @param[in] portGroup                - port group (core) number
* @param[in] phyPortNum               - physical port number
* @param[in] portMode                 - port standard metric
* @param[in] lbPort                   - if true, init port without serdes activity
* @param[in] refClock                 - Reference clock frequency
* @param[in] refClock                 - Reference clock source line
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortInitIpc
(
    MCD_DEV_PTR              pDev,
    MCD_U32                  portGroup,
    MCD_U32                  phyPortNum,
    MCD_U32                  portMode,
    MCD_BOOL                 lbPort,
    MCD_U32                  refClock,
    MCD_U32                  refClockSource

);

/**
* @internal mcdInternalPortResetIpc function
* @endinternal
*
* @brief   Sends to FW request to power down or reset physical port.
*
* @param[in] pDev
* @param[in] portGroup                - port group (core) number
* @param[in] phyPortNum               - physical port number
* @param[in] portMode                 - port standard metric
*                                      lbPort     - if true, init port without serdes activity
* @param[in] action                   - Power down or reset
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortResetIpc
(
    MCD_DEV_PTR            pDev,
    MCD_U32                portGroup,
    MCD_U32                phyPortNum,
    MCD_U32                portMode,
    MCD_BOOL               action
);

/**
* @internal mcdInternalPortAutoTuneStateCheckIpc function
* @endinternal
*
* @param[in] pDev
* @param[in] portGroup                - port group (core) number
* @param[in] phyPortNum               - physical port number
* @param[in] portMode                 - port standard metric
*                                      portTuningMode - port TX related tuning mode
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortAutoTuneStateCheckIpc
(
    MCD_DEV_PTR              pDev,
    MCD_U32                  portGroup,
    MCD_U32                  phyPortNum,
    MCD_U32                  portMode,
    MCD_AUTO_TUNE_STATUS     *rxTune,
    MCD_AUTO_TUNE_STATUS     *txTune
);

/**
* @internal mcdInternalPortLinkStatusGetIpc function
* @endinternal
*
* @brief   Sends message to get the port link status.
*         Can be run any time.
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortLinkStatusGetIpc
(
    MCD_DEV_PTR                pDev,
    MCD_U32                  portGroup,
    MCD_U32                  phyPortNum,
    MCD_U32                  portMode,
    MCD_BOOL                 *linkStatus
);

/**
* @internal mcdInternalPortAutoTuneStopIpc function
* @endinternal
*
* @brief   Send IPC message to stop Tx and Rx training
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortAutoTuneStopIpc
(
    MCD_DEV_PTR                      pDev,
    MCD_U32                          portGroup,
    MCD_U32                          phyPortNum,
    MCD_U32                          portMode,
    MCD_BOOL                         stopRx,
    MCD_BOOL                         stopTx
);

/**
* @internal mcdInternalPortApStartIpc function
* @endinternal
*
* @brief   Send message to configure AP port parameters and start execution
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] retimerMode              = TRUE for retimer
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApStartIpc
(
    MCD_DEV_PTR                pDev,
    MCD_U16                    phyPortNum,
    MCD_BOOL                   retimerMode
);

/**
* @internal mcdInternalPortApStopIpc function
* @endinternal
*
* @brief   Send message to stop AP port execution
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApStopIpc
(
    MCD_DEV_PTR                 pDev,
    MCD_U16 phyPortNum
);

/**
* @internal mcdInternalPortApCfgGetIpc function
* @endinternal
*
* @brief   Send message to retrive AP port configuration parameters
*
* @param[in] pDev
* @param[in] portGroup                - core number
* @param[in] phyPortNum               - physical port number
*                                      portApCfg  - AP configuration parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApCfgGetIpc
(
    MCD_DEV_PTR                pDev,
    MCD_U32 portGroup,
    MCD_U32 phyPortNum,
    MCD_U32 *apCfg
);

/**
* @internal mcdSetSquelchRxClockControlIpc function
* @endinternal
*
* @brief   Sends to Service CPU Squelch parameters
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] clckCtrl                 - pin to output the clock
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdSetSquelchRxClockControlIpc
(
   MCD_DEV_PTR                 pDev,
   MCD_U32                     phyPortNum,
   MCD_RX_CLOCK_CTRL_TYPE       clckCtrl
);

/**
* @internal mcdInternalPortApStatusGetIpc function
* @endinternal
*
* @brief   Send message to retrive AP port status parameters
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*                                      apStatus   - AP Status parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApStatusGetIpc
(
    MCD_DEV_PTR                pDev,
    MCD_U32 phyPortNum,
    MCD_U32 *portApStatus
);

/**
* @internal mcdInternalPortApStatsGetIpc function
* @endinternal
*
* @brief   Send message to retrive AP port stats parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApStatsGetIpc
(
    MCD_DEV_PTR                pDev,
    MCD_U32 portGroup,
    MCD_U32 phyPortNum,
    MCD_U32 *portApStats
);

/**
* @internal mcdPortApIntropSetIpc function
* @endinternal
*
* @brief   Set AP port introp 
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortApIntropSetIpc
(
    MCD_DEV_PTR  pDev,
    MCD_U32      phyPortNum,
    MCD_U32      *apIntrop
);


/**
* @internal mcdInternalPortApStatsResetIpc function
* @endinternal
*
* @brief   Reset AP port statistics information
*
* @param[in] pDev
* @param[in] portGroup                - port group (core) number
* @param[in] apPortNum                - AP port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApStatsResetIpc
(
    MCD_DEV_PTR pDev,
    MCD_U32 portGroup,
    MCD_U32 apPortNum
);

/**
* @internal mcdInternalPortApIntropSetIpc function
* @endinternal
*
* @brief   Set AP port introp information
*
* @param[in] pDev
* @param[in] portGroup                - port group (core) number
* @param[in] phyPortNum               - physical port number
*                                      apintrop    - AP introp parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApIntropSetIpc
(
    MCD_DEV_PTR                pDev,
    MCD_U32 portGroup,
    MCD_U32 phyPortNum,
    MCD_U32 *portApIntrop
);

/**
* @internal mcdInternalPortApIntropGetIpc function
* @endinternal
*
* @brief   Return AP port introp information
*
* @param[in] pDev
* @param[in] portGroup                - port group (core) number
* @param[in] phyPortNum               - physical port number
*                                      apintrop    - AP introp parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApIntropGetIpc
(
    MCD_DEV_PTR                pDev,
    MCD_U32 portGroup,
    MCD_U32 phyPortNum,
    MCD_U32 *portApIntrop
);

/**
* @internal mcdInternalPortApDebugGetIpc function
* @endinternal
*
* @brief   Return AP debug information
*
* @param[in] pDev
* @param[in] portGroup                - port group (core) number
* @param[in] phyPortNum               - physical port number
*                                      apDebug    - AP debug parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalPortApDebugGetIpc
(
    MCD_DEV_PTR                pDev,
    MCD_U32 portGroup,
    MCD_U32 phyPortNum,
    MCD_U32 *portApDebug
);

/**
* @internal mcdPortPollingLinkStatusStartIpc function
* @endinternal
*
* @brief   Start Port link status polling.
*
* @param[in] pDev
* @param[in] mdioPort                 - physical port number
* @param[in] retimerMode              - 1 - retimer mode, 0 -PCS mode
* @param[in] retimerWithAP            - true - retimer with ap
*                                      lineSerdesSpeed  - line Serdes Speed
*                                      hostSerdesSpeed  - host Serdes Speed
* @param[in] lineSerdesBitmap         - line Serdes Bitmap (bits 0-7)
* @param[in] hostSerdesBitmap         - host Serdes Bitmap (bits 0-7)
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortPollingLinkStatusStartIpc
(
    MCD_DEV_PTR                   pDev,
    MCD_U16                       mdioPort,
    MCD_BOOL                      retimerMode,
    MCD_BOOL                      retimerWithAP,
    MCD_U16 /*MCD_SERDES_SPEED*/  lineSerdesSpeed,
    MCD_U16 /*MCD_SERDES_SPEED*/  hostSerdesSpeed,
    MCD_U16                       lineSerdesBitmap,
    MCD_U16                       hostSerdesBitmap,
    MCD_U16                       noPpmMode,
    MCD_U8                        reducedRxTraining,
    MCD_CALIBRATION_ALGO_E        calibrationAlgo,
    MCD_CONFIDENCE_INTERVAL_PARAMS_OVERRIDE  *confidenceInterval,
    MCD_LINE_SIDE_EO_TH_OVERRIDE  *eoThreshold
);

/**
* @internal mcdPortPollingLinkStatusStopIpc function
* @endinternal
*
* @brief   Stop Port link status polling.
*
* @param[in] pDev
* @param[in] mdioPort                 - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortPollingLinkStatusStopIpc
(
    MCD_DEV_PTR                   pDev,
    MCD_U16                       mdioPort
);

#endif /* __mcdInternalIpcApis_H */




