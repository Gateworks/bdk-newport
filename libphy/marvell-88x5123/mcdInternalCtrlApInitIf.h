/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

#ifndef __mcdPortCtrlApIf_H
#define __mcdPortCtrlApIf_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcdInternalPortApInitIf.h"
#include "mcdPortCtrlApLogDefs.h"

/**
* @internal mcdAutoNegPortCtrlStart function
* @endinternal
*
* @brief   Init AP port capability.
*         Runs AP protocol(802.3ap Serdes AutoNeg) and configures the best port
*         mode and all it's elements accordingly.
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] retimerMode              = TRUE for retimer
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdAutoNegPortCtrlStart
(
    MCD_DEV_PTR    pDev,
    MCD_U16        phyPortNum,
    MCD_BOOL       retimerMode
);

/**
* @internal mcdApSerdesRxParametersManualSetStart function
* @endinternal
*
* @brief   Set serdes RX parameters . Those offsets
*         will take place after TRX training.
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdApSerdesRxParametersManualSetStart
(
    MCD_DEV_PTR                         pDev,
    MCD_U16                             phyPortNum,
    MCD_MAN_TUNE_CTLE_CONFIG_OVERRIDE   *rxCfgPtr
);

/**
* @internal mcdApSerdesTxParametersManualSetStart function
* @endinternal
*
* @brief   Set serdes Tx parameters . Those values
*         will take place after resolution detected.
* @param[in] pDev                     - physical device number
*                                      mdioPort         - portNum
*                                      txOverrideParamsPtr - (pointer to) parameters data
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on fail
*/
MCD_STATUS mcdApSerdesTxParametersManualSetStart
(
    MCD_DEV_PTR                         pDev,
    MCD_U16                             phyPortNum,
    MCD_PORT_AP_SERDES_TX_CONFIG        *txCfgPtr
);

/**
* @internal mcdAutoNegPortCtrlStop function
* @endinternal
*
* @brief   Disable the AP engine on port and release all its resources.
*         Clears the port mode and release all its resources according to selected.
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdAutoNegPortCtrlStop
(
    MCD_DEV_PTR pDev,
    MCD_U16 phyPortNum
);

/**
* @internal mcdApPortCtrlSysAck function
* @endinternal
*
* @brief   Acknowledge port resources were allocated at application level
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlSysAck
(
    MCD_DEV_PTR pDev,
    MCD_U32 phyPortNum
);

/**
* @internal mcdApPortCtrlCfgGet function
* @endinternal
*
* @brief   Returns the AP port configuration.
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] apCfg                    - AP configuration parameters
*
* @param[out] apCfg                    - AP configuration parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlCfgGet
(
    MCD_DEV_PTR    pDev,
    MCD_U32        phyPortNum,
    MCD_AP_CFG     *apCfg
);

/**
* @internal mcdApPortCtrlStatusGet function
* @endinternal
*
* @brief   Returns the AP port resolution information
*
* @param[in] pDev
*                                      phyPortNum - physical port number
* @param[in] apStatus                 - AP status parameters
*
* @param[out] apStatus                 - AP/HCD results
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlStatusGet
(
    MCD_DEV_PTR            pDev,
    MCD_U32                apPortNum,
    MCD_AP_PORT_STATUS *apStatus
);

/**
* @internal mcdApPortCtrlStatsGet function
* @endinternal
*
* @brief   Returns the AP port statistics information
*
* @param[in] pDev
*                                      phyPortNum - physical port number
*
* @param[out] apStats                  - AP stats
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlStatsGet
(
    MCD_DEV_PTR           pDev,
    MCD_U32               apPortNum,
    MCD_AP_PORT_STATS *apStats
);

/**
* @internal mcdApPortCtrlStatsReset function
* @endinternal
*
* @brief   Reset AP port statistics information
*
* @param[in] pDev
* @param[in] apPortNum                - AP port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlStatsReset
(
    MCD_DEV_PTR           pDev,
    MCD_U32               apPortNum
);

/**
* @internal mcdApPortCtrlIntropSet function
* @endinternal
*
* @brief   Set AP port introp information
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*                                      apintrop    - AP introp parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlIntropSet
(
    MCD_DEV_PTR            pDev,
    MCD_U32                phyPortNum,
    MCD_AP_PORT_INTROP *apIntrop
);

/**
* @internal mcdApPortCtrlIntropGet function
* @endinternal
*
* @brief   Return AP port introp information
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*                                      apintrop    - AP introp parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlIntropGet
(
    MCD_DEV_PTR           pDev,
    MCD_U32               phyPortNum,
    MCD_AP_PORT_INTROP   *apIntrop
);

/**
* @internal mcdApPortCtrlDebugGet function
* @endinternal
*
* @brief   Return AP debug information
*
* @param[in] pDev
*
* @param[out] apDebug                  - AP debug parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlDebugGet
(
    MCD_DEV_PTR           pDev,
    MCD_FW_LOG *apDebug
);

/**
* @internal mcdApPortCtrlSerdesGuiSet function
* @endinternal
*
* @brief   Set AP state machine state when GUI is enabled
*         GUI access Serdes Firmware as SBUS command level
*         Therefore it is required to stop the periodic behiviour of AP state
*         machine when Serdes GUI is enabled
* @param[in] pDev
* @param[in] state                    - Serdes GUI state
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlSerdesGuiSet
(
    MCD_DEV_PTR pDev,
    MCD_U8 state
);

/**
* @internal mcdApPortCtrlStatsShow function
* @endinternal
*
* @brief   Print AP port statistics information stored in system
*
* @param[in] pDev
* @param[in] apPortNum                - AP port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlStatsShow
(
    MCD_DEV_PTR pDev,
    MCD_U32  apPortNum
);

/**
* @internal mcdApPortCtrlIntropShow function
* @endinternal
*
* @brief   Print AP port introp information stored in system
*
* @param[in] pDev
* @param[in] apPortNum                - AP port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlIntropShow
(
    MCD_DEV_PTR pDev,
    MCD_U32  apPortNum
);

/**
* @internal mcdApPortCtrlDebugInfoShow function
* @endinternal
*
* @brief   Print AP port real-time log information stored in system
*
* @param[in] pDev
* @param[in] apPortNum                - AP port number
*                                      cpssLog   - boolean value indicate if log will be part of CPSS log mechanism or terminal print
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdApPortCtrlDebugInfoShow
(
    MCD_DEV_PTR pDev,
    MCD_U32    apPortNum,
    MCD_BOOL   apCpssLogEnable
);

/**
* @internal mcdPollingStatShow function
* @endinternal
*
* @brief   Print FW Hws real-time polling statistic information stored in system
*
* @param[in] pDev                     - pointer to device
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPollingStatShow
(
    MCD_DEV_PTR             pDev
);

/**
* @internal mcdPollingStatClear function
* @endinternal
*
* @brief   Clear FW Hws real-time polling statistic information stored in system
*
* @param[in] pDev                     - pointer to device
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPollingStatClear
(
    MCD_DEV_PTR             pDev
);

typedef enum
{
    MCD_POLLING_PORT_STATISTIC_VAL_LAST_UP_TIME_E,
    MCD_POLLING_PORT_STATISTIC_VAL_LONGEST_UP_TIME_E,
    MCD_POLLING_PORT_STATISTIC_VAL_PCS_CHECK_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_PCS_CHECK_FAIL_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SERDES_SIGNAL_CHECK_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SERDES_SIGNAL_CHECK_FAIL_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SERDES_TRAIN_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SERDES_TRAIN_FAIL_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_OFF_TO_CHECK_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_CHECK_TO_OFF_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_CHECK_TO_ON_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_ON_TO_OFF_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_LAST_STATES_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MIN_ON_TIME_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MAX_OFF_TO_CHECK_TIME_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MAX_OFF_TO_ON_TIME_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MIN_BOTH_SIDES_ON_TIME_E,
    MCD_POLLING_PORT_STATISTIC_VAL_SIGNAL_MAX_ONE_SIDE_ON_TO_BOTH_SIDES_ON_TIME_E,
    MCD_POLLING_PORT_STATISTIC_VAL_ICAL_FAILED_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_EO_FAILED_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_ADAPTIVE_FAILED_COUNT_E,
    MCD_POLLING_PORT_STATISTIC_VAL_CONFIDENCE_INT_FAILED_COUNT_E
} MCD_POLLING_PORT_STATISTIC_VAL_ENT;

/**
* @internal mcdPollingStatValueGet function
* @endinternal
*
* @brief   Get FW real-time polling statistic information stored in system
*
* @param[in] pDev                     - pointer to device
* @param[in] lineSide                 - host side - 0, line side - 1
*
* @param[out] pollingStatValPtr        - pointer to required value.
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on wrong parameters
*/
MCD_STATUS mcdPollingStatValueGet
(
    IN  MCD_DEV_PTR                         pDev,
    IN  MCD_U32                             portOrSerdes,
    IN  MCD_U32                             lineSide,
    IN  MCD_POLLING_PORT_STATISTIC_VAL_ENT  valueType,
    OUT MCD_U32                             *pollingStatValPtr
);

/**
* @internal mcdPollingStatRetimerPerPortValuesClear function
* @endinternal
*
* @brief   Clear FW real-time polling statistic related to retimer port side.
*
* @param[in] pDev                     - pointer to device
* @param[in] portNum                  - port number
* @param[in] lineSide                 - host side - 0, line side - 1
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on wrong parameters
*/
MCD_STATUS mcdPollingStatRetimerPerPortValuesClear
(
    IN  MCD_DEV_PTR                         pDev,
    IN  MCD_U32                             portNum,
    IN  MCD_U32                             lineSide
);

#ifdef __cplusplus
}
#endif

#endif /* mcdervicesPortCtrlApIf_H */




