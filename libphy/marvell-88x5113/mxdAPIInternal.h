/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and data that are strictly internal
for the proper functioning of the API on the Marvell X5113 PHY.
********************************************************************/
#ifndef MXDINTRNL_H
#define MXDINTRNL_H

#include "mxdDiagnostics.h"

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#define PCS_TYPE_IDX        0
#define FEC_TYPE_IDX        1
#define AUTONEG_IDX         2
#define SPEED_IDX           3
#define INTERFACE_IDX       4

/* 3.F000.7:6 FEC */
#define MXD_FEC_NONE        0
#define MXD_KR_FEC          1 /* B:0001 KR = 01b */
#define MXD_RS_FEC          2 /* B:0010 RS = 10b */
#define MXD_FEC_BOTH        3 /* B:0011 Both RS and KR */ 
#define MXD_KR_FEC_CON      5 /* B:0101 KR = 01b */
#define MXD_RS_FEC_CON      6 /* B:0110 RS = 10b */

#define MXD_RS_FEC_IEEE     0x10 /* Not a register bit */
#define MXD_KR_FEC_IEEE     0x11 /* Not a register bit */

extern const MXD_U16 portConfigTbl[MXD_OP_CONFIG_NUM][5];

/*******************************************************************************
 MXD_STATUS mxdGetModeSpeed
    Get mode speed based on the OP mode setting
*******************************************************************************/
MXD_STATUS mxdGetModeSpeed
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16     mdioPort,
    IN MXD_U16     host_or_line,
    IN MXD_U16     laneOffset,
    OUT MXD_SPEED  *speed,
    OUT MXD_PCS_TYPE   *mode
);

/******************************************************************************
 MXD_STATUS mxdIsLaneOffsetValid
******************************************************************************/
MXD_STATUS mxdIsLaneOffsetValid
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset
);

/*******************************************************************************
 MXD_STATUS mxdIsPortValid
    Check the MDIO port address if it is valid against the port address input
    during the mxdInitDriver initialization
*******************************************************************************/
MXD_STATUS mxdIsPortValid
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
);

/*******************************************************************************
 MXD_STATUS mxdIsOpModeValid
    Check the host and line Op Mode if it is valid combination
*******************************************************************************/
MXD_STATUS mxdIsOpModeValid
(
    IN MXD_DEV_PTR pDev,
    IN MXD_OP_CONFIG hostMode,
    IN MXD_OP_CONFIG lineMode
);

/******************************************************************************
MXD_STATUS mxdSetFixedMode
   Line and Host mode selection
   portMode  - Fixed OP Mode
   Note: soft reset is performed in this function.
******************************************************************************/
MXD_STATUS mxdSetFixedMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
);

/*******************************************************************
 MXD_STATUS mxdGetFixedMode
    Get Line and Host mode selection
*******************************************************************/
MXD_STATUS mxdGetFixedMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_OP_CONFIG *opConfig
);

/******************************************************************************
 MXD_STATUS mxdGetDetailedLinkStatus
    Gets current and latched status for one side and lane of the interface based
    on the operating mode of that side/lane. Returns 0 for latchStat
    for lanes in any repeater mode.
******************************************************************************/
MXD_STATUS mxdGetDetailedLinkStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 host_or_line,
    OUT MXD_U16 *currStat,
    OUT MXD_U16 *latchStat
);

/*******************************************************************************
 MXD_STATUS mxdReadPCSLinkStatus
    Check PCS link status
*******************************************************************************/
MXD_STATUS mxdReadPCSLinkStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16  laneOffset,
    IN MXD_BOOL perLaneStatus,
    OUT MXD_U16 *currentStatus,
    OUT MXD_U16 *latchedStatus,
    OUT MXD_DETAILED_STATUS_TYPE *statusDetail
);

/*******************************************************************************
 MXD_STATUS mxdReadRepeaterLinkStatus
    Check Serdes DSP lock status on the ports
    Returns status of single lane or all lanes on both host and line side.
*******************************************************************************/
MXD_STATUS mxdReadRepeaterLinkStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_BOOL perLaneStatus,
    OUT MXD_U16 *CurrentStatus,
    OUT MXD_DETAILED_STATUS_TYPE *statusDetail
);

/*******************************************************************
 MXD_STATUS mxdPortResetTimeout
 Check timeout after the soft or hard reset
*******************************************************************/
MXD_STATUS mxdPortResetTimeout
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 timeoutMs
);

/*******************************************************************
 MXD_STATUS mxdLaneSoftReset
 Check timeout after the Lane soft reset
*******************************************************************/
MXD_STATUS mxdLaneSoftReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 timeoutMs
);

/*******************************************************************
 MXD_STATUS mxdLaneResetTimeout
 Check timeout after the Lane soft reset
*******************************************************************/
MXD_STATUS mxdLaneResetTimeout
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 timeoutMs
);

/*******************************************************************
 MXD_STATUS mxdPortPowerHwResetTimeout
    Power down and Reset mdioPort wait time
*******************************************************************/
MXD_STATUS mxdPortPowerHwResetTimeout
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 timeoutMs
);

/*******************************************************************
 MXD_STATUS mxdPortPowerHwReset
   Power down and reset mdioPort on both the host and line side
*******************************************************************/
MXD_STATUS mxdPortPowerHwReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
);

/*******************************************************************
 MXD_STATUS mxdPortPowerUp
   Power up the host or line side
*******************************************************************/
MXD_STATUS mxdPortPowerUp
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
);

/*******************************************************************
 MXD_STATUS mxdRestoreStart
   Restore start of a port
*******************************************************************/
MXD_STATUS mxdRestoreStart
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
);

/*******************************************************************
 MXD_STATUS mxdRepeaterConfig
   Repeater modes config 
*******************************************************************/
MXD_STATUS mxdRepeaterConfig
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
);

/*******************************************************************
 MXD_STATUS mxdStartEnhance
   Start enhancements 
*******************************************************************/
MXD_STATUS mxdStartEnhance
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
);

/*******************************************************************
 MXD_STATUS mxdPerfConfig
   Performance config 
*******************************************************************/
MXD_STATUS mxdPerfConfig
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
);

/*******************************************************************
 MXD_STATUS mxdOverrideClockModifier
  Override clock on some speeds
*******************************************************************/
MXD_STATUS mxdOverrideClockModifier
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
);

/*******************************************************************
 MXD_STATUS mxdTapConfig
   Tap Settings 
*******************************************************************/
MXD_STATUS mxdTapConfig
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig
);

/*******************************************************************
 MXD_STATUS mxdSetFecConfig
   Set FEC Configurations
*******************************************************************/
MXD_STATUS mxdSetFecConfig
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 fecType,
    IN MXD_OP_CONFIG opConfig
);

/*******************************************************************************
MXD_STATUS mxdGetPktGenRegOffset

*******************************************************************************/
MXD_STATUS mxdGetPktGenRegOffset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *regAddrOffset
);

/*******************************************************************************
 MXD_STATUS mxdCheckFecLaneOffset
    Check if the laneOffset is valid to FEC
*******************************************************************************/
MXD_STATUS mxdCheckFecLaneOffset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_U16  fecType
);

/*******************************************************************************
 MXD_STATUS mxdSetDeepPCSLoopback
*******************************************************************************/
MXD_STATUS mxdSetDeepPCSLoopback
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 laneOffset,
    IN MXD_U16 host_or_line,
    IN MXD_U16 gearboxMode,
    IN MXD_U16 autoNeg,
    IN MXD_SPEED lineSpeed,
    IN MXD_U16 regAddrPCS,
    IN MXD_U16 loopbackBit
);

/*******************************************************************************
 MXD_STATUS mxdSetDeepPMALoopback100G
*******************************************************************************/
MXD_STATUS mxdSetDeepPMALoopback100G
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 autoNeg,
    IN MXD_U16 enableLoopback
);

/*******************************************************************
 MXD_STATUS mxdMappedSerdesIDs
   Mapped the Serdes ID to the matching Host and Line lanes 
       Host LaneOffset   SerdesID  
             0              1
             1              2
             2              3
             3              4
       Line LaneOffset   SerdesID  
             0              5
             1              6
             2              7
             3              8

*******************************************************************/
MXD_STATUS mxdMappedSerdesIDs
(
    IN MXD_DEV_PTR pDev
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MXDINTRNL_H */
