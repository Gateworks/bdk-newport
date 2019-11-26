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
* @file mcdInternalInitApApis.h
*
* @brief API to configure and run 802.3ap Serdes AutoNeg engine
*
* @version   17
********************************************************************************
*/

#ifndef __mcdInternalInitApApis_H
#define __mcdInternalInitApApis_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcdApiTypes.h"



/**
* @internal mcdInternalApEngineInit function
* @endinternal
*
* @brief   Initialize AP engine.
*
* @param[in] pDev
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApEngineInit
(
    MCD_DEV_PTR               pDev
);

/**
* @internal mcdInternalApEngineStop function
* @endinternal
*
* @brief   Disable whole AP engine.
*
* @param[in] pDev
*                                      portGroup   - port group (core) number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApEngineStop
(
    MCD_DEV_PTR               pDev
);

/**
* @internal mcdInternalApEngineInitGet function
* @endinternal
*
* @brief   Checks if AP engine is enabled whole AP engine.
*
* @param[in] pDev
* @param[in] engineEnabled            - pointer to boolean that indicated whether the engine
*                                      is enabled
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApEngineInitGet
(
    MCD_DEV_PTR               pDev,
    MCD_BOOL                  *engineEnabled
);

/**
* @internal mcdInternalApPortStart function
* @endinternal
*
* @brief   Init AP port capability.
*         Runs AP protocol(802.3ap Serdes AutoNeg) and configures the best port
*         mode and all it's elements accordingly.
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] apCfg                    - AP configuration parameters
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApPortStart
(
    MCD_DEV_PTR               pDev,
    MCD_U32                   phyPortNum,
    MCD_AP_CFG                *apCfg
);


/**
* @internal mcdInternalApPortConfigGet function
* @endinternal
*
* @brief   Returns the AP port configuration.
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApPortConfigGet
(
    MCD_DEV_PTR              pDev,
    MCD_U32                  phyPortNum,
    MCD_BOOL                 *apPortEnabled,
    MCD_AP_CFG               *apCfg

);

/**
* @internal mcdInternalApPortSetActiveLanes function
* @endinternal
*
* @brief   Disable the AP engine on port and release all its resources.
*         Clears the port mode and release all its resources according to selected.
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
* @param[in] portMode                 - port mode
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApPortSetActiveLanes
(
    MCD_DEV_PTR              pDev,
    MCD_U32                  portGroup,
    MCD_U32                  phyPortNum,
    MCD_U32                  portMode

);

/**
* @internal mcdInternalApPortResolutionMaskGet function
* @endinternal
*
* @brief   Returns the port's resolution bit mask
*
* @param[in] pDev
*
* @param[out] portBitmask              - port's resolution bit mask
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApPortResolutionMaskGet
(
    MCD_DEV_PTR              pDev,
    MCD_U32                  *portBitmask
);

/**
* @internal mcdInternalApLockGet function
* @endinternal
*
* @brief   Acquires lock so host and AP machine won't access the same
*         resource at the same time.
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApLockGet
(
    MCD_DEV_PTR pDev,
    MCD_U32 phyPortNum
);

/**
* @internal mcdInternalApLockRelease function
* @endinternal
*
* @brief   Releases the synchronization lock (between Host and AP machine.
*
* @param[in] pDev
* @param[in] phyPortNum               - physical port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApLockRelease
(
    MCD_DEV_PTR  pDev,
    MCD_U32 phyPortNum
);

/**
* @internal mcdInternalApCheckCounterGet function
* @endinternal
*
* @brief   Read checkCounter value display AP engine activity.
*
* @param[in] pDev
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApCheckCounterGet
(
  MCD_DEV_PTR pDev,
  MCD_U32 *counter
);

/**
* @internal mcdInternalApPortStatusShow function
* @endinternal
*
* @brief   Print AP port status information stored in system.
*
* @param[in] pDev
* @param[in] apPortNum                - AP port number
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApPortStatusShow
(
  MCD_DEV_PTR pDev,
  MCD_U32  apPortNum
);

/**
* @internal mcdInternalApPortCtrlServiceCpuUartEnableSet function
* @endinternal
*
* @brief   Enable or disable Service CPU UART
*
* @param[in] pDev
* @param[in] enable                   - boolean value indicate UART setting (enable/disable)
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdInternalApPortCtrlServiceCpuUartEnableSet
(
    MCD_DEV_PTR pDev,
    MCD_BOOL   enable
);

/**
* @internal mcdpPortCtrlServiceCpuUartEnableGet function
* @endinternal
*
* @brief   Get Service CPU UART status (enable or disable).
*
* @param[in] pDev
*                                      enable - boolean value indicate UART setting (enable/disable)
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdpPortCtrlServiceCpuUartEnableGet
(
    MCD_DEV_PTR pDev,
    MCD_BOOL   *enablePtr
);

#ifdef __cplusplus
}
#endif

#endif /* mcdInternalInitApApis_H */





