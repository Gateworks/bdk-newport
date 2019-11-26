/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

#ifndef MCDINTRNL_H
#define MCDINTRNL_H

#include "mcdDiagnostics.h"
#include "mcdHwSerdesCntl.h"

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/******************************************************************************
 MCD_STATUS mcdCheckIsDeviceSupported
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
);
 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    None.

 Returns:
    MCD_OK if obtained supported device, MCD_FAIL if not.

 Description:
    Determines the PHY revision and returns the value in phyRev.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdCheckIsDeviceSupported
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
);

/* X5123 and EC808 Channel mode types */
typedef enum {
    MCD_SGMII = 1,
    MCD_QSGMII,
    MCD_BASE_R1,
    MCD_BASE_R2,
    MCD_BASE_R4,
    MCD_BASE_R8,
    MCD_BASE_R10,
    MCD_2_5G_USXGMII = 0xc,
    MCD_5G_USXGMII
} MCD_CHANNEL_MODE_TYPE;

/* X5123 and EC808 supported speeds in LSMPCS */
typedef enum {
    MCD_LOW_SPEED_10M,
    MCD_LOW_SPEED_100M,
    MCD_LOW_SPEED_1000M,
    MCD_LOW_SPEED_UNKNOWN
}MCD_LOW_SPEED_MODE;

typedef enum {
    MCD_PCS_CHANNEL_CLOCK_GATE,
    MCD_PCS_CLOCK_GATE,
    MCD_MAC_CLOCK_GATE,
    MCD_MACSEC_CLOCK_GATE
}MCD_CLOCK_GATE_TYPE;

#define MCD_CLOCK_GATING_SLICE_OFFSET       16
#define MCD_CLOCK_GATING_PCS_CHANNEL_OFFSET  3
#define MCD_CLOCK_GATING_MAC_OFFSET          2
#define MCD_CLOCK_GATING_MACSEC_OFFSET      11

#define PRV_MCD_DELAY_RETIMER_CLOCK_SWITCH 50

/* This macro is handy for calling a function when you want to test the
   return value and return MCD_FAIL, if the function returned MCD_FAIL,
   otherwise continue. Will set the return code to MCD_IO_ERROR. */
#define TRY_IO(xFuncToTry) if (xFuncToTry == MCD_FAIL) {*errCode = MCD_IO_ERROR; return MCD_FAIL;}

#define CHAN_IN_SLICE_NUM(num) (num & 3)

/* the formula for serdes number calculation : 4 * slice + 8 * LineOrHost + chan ,
                                                                where chan is 0-3
                                                                      LineOrHost = 0 for line side
                                                                      LineOrHost = 1 for host side */
#define MCD_HOST_SIDE_START_SERDES_NUMBER 8
#define MCD_SERDES_NUM(serdes,slice) (serdes + (slice << 2)) /* for host side serdes = (MCD_HOST_SIDE_START_SERDES_NUMBER + chan)*/
#define MCD_SERDES_LANE_NUM(host_or_line, slice, lane_offset) \
    (((host_or_line == MCD_HOST_SIDE) \
      ? MCD_HOST_SIDE_START_SERDES_NUMBER : 0) \
     + MCD_SERDES_NUM(lane_offset, slice))
#define MCD_SERDES_LANE_SBUS_ADDR(host_or_line, slice, lane_offset) \
    (MCD_SERDES_LANE_NUM(host_or_line, slice, lane_offset) + 1)

#define MCD_HOST_OR_LINE_SIDE(lane_offset)   \
    ((lane_offset > 3) ? MCD_LINE_SIDE: MCD_HOST_SIDE)

#define MCD_GET_PORTNUM_FROM_CHANUNIT(slice, channelUnit)   \
    (((slice == MCD_FALSE) ? 0 : 4) + CHAN_IN_SLICE_NUM(channelUnit))

/* Internal CPU polling algorithm statistic. */
#define MCD_POLLING_SERDES_NUM_CNS 16
#define MCD_POLLING_PORTS_NUM_CNS 8

typedef struct
{
    MCD_U32 hostFec;
    MCD_U32 lineFec;
} MCD_FEC_TYPE_GET;

#define MCD_FEC_TYPE_GET_MAC(_fecCorrect, _fecConfig)              \
do                                                                 \
{                                                                  \
    if (_fecCorrect <= MCD_FC_FEC)                                 \
    {                                                              \
        _fecConfig.hostFec = _fecConfig.lineFec = _fecCorrect;     \
    }                                                              \
    else                                                           \
    {                                                              \
        _fecConfig.hostFec = (_fecCorrect >> 2) & 0x3;             \
        _fecConfig.lineFec = (_fecCorrect >> 4) & 0x3;             \
    }                                                              \
}while(0);

#define MCD_SYNCE_VALID_PORT(_mdioPort,_slice)                          \
((_mdioPort/4) == _slice? MCD_OK : MCD_FAIL)

/* check NULL pointer */
#define MCD_NULL_PTR_CHECK_MAC(_ptr)    if(_ptr == NULL) { \
    MCD_DBG_ERROR("\n Error, NULL ptr");                   \
    return MCD_FAIL;                                       \
}

#define MCD_GET_SLICE_NUM_BY_SERDES(_serdesNum,_slice)                       \
do                                                                           \
{                                                                            \
    if (_serdesNum >= MCD_HOST_SIDE_START_SERDES_NUMBER)                     \
    {                                                                        \
        _slice = (_serdesNum - MCD_HOST_SIDE_START_SERDES_NUMBER)/4;         \
    }                                                                        \
    else                                                                     \
    {                                                                        \
        _slice = _serdesNum/4;                                               \
    }                                                                        \
}while(0);

#define MCD_LOGIC_TO_PHYSICAL_SERDES_MAC(_serdesNum, _phySerdesNum)                                         \
do                                                                                                          \
{                                                                                                           \
    _phySerdesNum = mcdSerdesLogicalToPhysicalConvert(pDev, _serdesNum, slice);                             \
}while(0);

#define MCD_LOGIC_TO_PHYSICAL_SERDES_TX_MAC(_serdesNum, _phySerdesNum)                                         \
do                                                                                                          \
{                                                                                                           \
    _phySerdesNum = mcdSerdesLogicalToPhysicalConvertTx(pDev, _serdesNum, slice);                             \
}while(0);

#define MCD_FW_LOGIC_TO_PHYSICAL_SERDES_MAC(_serdesNum, _phySerdesNum)                                      \
do                                                                                                          \
{                                                                                                           \
    _phySerdesNum = mcdSerdesLogicalToPhysicalConvert(&mcdDevDb, _serdesNum, slice);                        \
}while(0);

/*
   Port statistic
   lineLastUpTime       - Line side - Time in milliseconds for
                          last Link/Signal UP detection and training
   hostLastUpTime       - Host side - Time in milliseconds for
                          last Link/Signal UP detection and training
   lineLongestUpTime    - Line side - Time in milliseconds for
                          longest Link/Signal UP detection and training
   hostLongestUpTime    - Host side - Time in milliseconds for
                          longest Link/Signal UP detection and training

   SERDES statistic
   signalCheckCount     - count of SERDES signal checks
   signalCheckFailCount - count of SERDES signal checks with no signal result
   trainCount           - count of SERDES training
   trainFailCount       - count SERDES training failures
*/
typedef struct
{
    /* port statistic */
    MCD_U32    lineLastUpTime[MCD_POLLING_PORTS_NUM_CNS];
    MCD_U32    hostLastUpTime[MCD_POLLING_PORTS_NUM_CNS];
    MCD_U32    lineLongestUpTime[MCD_POLLING_PORTS_NUM_CNS];
    MCD_U32    hostLongestUpTime[MCD_POLLING_PORTS_NUM_CNS];
    MCD_U16    linePcsCheckCount[MCD_POLLING_PORTS_NUM_CNS];
    MCD_U16    linePcsCheckFailCount[MCD_POLLING_PORTS_NUM_CNS];
    MCD_U16    hostPcsCheckCount[MCD_POLLING_PORTS_NUM_CNS];
    MCD_U16    hostPcsCheckFailCount[MCD_POLLING_PORTS_NUM_CNS];

    /* SERDES statistic */
    MCD_U16    signalCheckCount[MCD_POLLING_SERDES_NUM_CNS];
    MCD_U16    signalCheckFailCount[MCD_POLLING_SERDES_NUM_CNS];
    MCD_U16    trainCount[MCD_POLLING_SERDES_NUM_CNS];
    MCD_U16    trainFailCount[MCD_POLLING_SERDES_NUM_CNS];
    MCD_U16    countICalFailed[MCD_POLLING_SERDES_NUM_CNS];
    MCD_U16    countEoFailed[MCD_POLLING_SERDES_NUM_CNS];
    MCD_U16    stopAdaptiveFailed[MCD_POLLING_SERDES_NUM_CNS];
    MCD_U16    countConfidenceIntFailed[MCD_POLLING_SERDES_NUM_CNS];

    /* port side statistics counters - index 0 - host, index 1 - line */
    MCD_U16 countSignalOffToCheckStable[2][MCD_POLLING_PORTS_NUM_CNS];
    MCD_U16 countSignalCheckStableToOff[2][MCD_POLLING_PORTS_NUM_CNS];
    MCD_U16 countSignalCheckStableToOn[2][MCD_POLLING_PORTS_NUM_CNS];
    MCD_U16 countSignalOnToOff[2][MCD_POLLING_PORTS_NUM_CNS];

    /* port side statistics counters - index 0 - host, index 1 - line */
    MCD_U16 registedSignalLastStates[2][MCD_POLLING_PORTS_NUM_CNS];

    /* retimer port side statistics OS mSec times - index 0 - host, index 1 - line   */
    MCD_U32 minSignalOnTime[2][MCD_POLLING_PORTS_NUM_CNS];
    MCD_U32 maxSignalOffToCheckTime[2][MCD_POLLING_PORTS_NUM_CNS];
    MCD_U32 maxSignalOffToOnTime[2][MCD_POLLING_PORTS_NUM_CNS];
    MCD_U32 maxSignalOtherSideOnToBothSidesOnTime[2][MCD_POLLING_PORTS_NUM_CNS];

    /* port statistic */
    /* retimer port statistics OS mSec times */
    MCD_U32 minSignalOnBothSidesTime[MCD_POLLING_PORTS_NUM_CNS];

    #ifdef  MCD_AP_STATE_STATUS_LOG
    /* AP statistics */
    /* Keeping the last STATES of the AP per SM */
    MCD_U64 registedApSmLog      [MCD_POLLING_PORTS_NUM_CNS];  /* Each U64 includes max of 12 statuses states */
    MCD_U16 registedApSmLogType  [MCD_POLLING_PORTS_NUM_CNS];  /* Each U16 includes 16 different log types
                                                                    (0-state, 1-status)*/
    MCD_U64 registedPortSmLog    [MCD_POLLING_PORTS_NUM_CNS];  /* Each U64 includes max of 12 statuses states */
    MCD_U16 registedPortSmLogType[MCD_POLLING_PORTS_NUM_CNS];  /* Each U16 includes 16 different log types
                                                                (0-state, 1-status)*/
    #endif /*MCD_AP_STATE_STATUS_LOG*/

} MCD_POLLING_PORT_STATISTIC_STC;


/* In order to enable access to these registers from the CM3 and from the HOST CPU side
   The below ifdef is required.
*/
#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
    extern MCD_POLLING_PORT_STATISTIC_STC mcdFwPortCtrlPollingStat;
    #define MCD_STAT_SIGNAL_DECODE(_lineSide, _portIndex)  \
                                       (mcdFwPortCtrlPollingStat.registedSignalLastStates[_lineSide][_portIndex])
    #ifdef  MCD_AP_STATE_STATUS_LOG
    #define MCD_AP_SM_DECODE(_portIndex)          (mcdFwPortCtrlPollingStat.registedApSmLog[_portIndex])
    #define MCD_AP_SM_DECODE_TYPE(_portIndex)     (mcdFwPortCtrlPollingStat.registedApSmLogType[_portIndex])
    #define MCD_PORT_SM_DECODE(_portIndex)        (mcdFwPortCtrlPollingStat.registedPortSmLog[_portIndex])
    #define MCD_PORT_SM_DECODE_TYPE(_portIndex)   (mcdFwPortCtrlPollingStat.registedPortSmLogType[_portIndex])
    #endif  /*MCD_AP_STATE_STATUS_LOG*/
#else
    #define MCD_STAT_SIGNAL_DECODE(_lineSide, _portIndex)  \
                                       (pollingStat.registedSignalLastStates[_lineSide][_portIndex])

    #ifdef  MCD_AP_STATE_STATUS_LOG
    #define MCD_AP_SM_DECODE(_portIndex)          (pollingStat.registedApSmLog[_portIndex])
    #define MCD_AP_SM_DECODE_TYPE(_portIndex)     (pollingStat.registedApSmLogType[_portIndex])
    #define MCD_PORT_SM_DECODE(_portIndex)        (pollingStat.registedPortSmLog[_portIndex])
    #define MCD_PORT_SM_DECODE_TYPE(_portIndex)   (pollingStat.registedPortSmLogType[_portIndex])
    #endif  /*MCD_AP_STATE_STATUS_LOG*/
#endif

/* Mickey - Adding...  */
typedef enum {
    MCD_STAT_OFF_TO_CHK_STABLE,
    MCD_STAT_CHK_STABLE_TO_OFF,
    MCD_STAT_CHK_STABLE_TO_ON,
    MCD_STAT_ON_TO_OFF
}MCD_STAT_SIGNAL_TYPE;


/* Keeping the Signals state information coded in the argument */
/* Binary 00 01 10 11... - means according to the MCD_STAT_SIGNAL_TYPE above */
#define MCD_STAT_SIGNAL_INSERT(_lineSide, _portIndex,_state) \
    (MCD_STAT_SIGNAL_DECODE(_lineSide, _portIndex) = \
    ((MCD_STAT_SIGNAL_DECODE(_lineSide, _portIndex) << 2) | ((MCD_U16)_state & 0x3)))

#define MCD_STAT_SIGNAL_GET(_lineSide, _portIndex,_location) \
    ((MCD_STAT_SIGNAL_DECODE(_lineSide, _portIndex) >> (2*_location)) & 0x3)


/************************************************************************/
/* Adding new macros for saving the AP/Port State machine States/Status */
/************************************************************************/

/*******************************************************************************
*                            AP Port Log State/Status                          *
* ============================================================================ *
*******************************************************************************/

/* Keeping the AP_SM state information coded in the argument */
/* Binary 00 01 10 11... - means according to the MV_AP_PORT_SM_STATE above */
#define MCD_STAT_AP_SM_STATE_INSERT(_portIndex,_state) \
     mcdStatApSmStateInsert(_portIndex, _state)

/* Keeping the AP_SM status information coded in the argument */
/* Binary 00000 00001 00010 00011... - means according to the MV_AP_PORT_SM_STATUS above */
#define MCD_STAT_AP_SM_STATUS_INSERT(_portIndex,_status) \
     mcdStatApSmStatusInsert(_portIndex, _status)

/* Keeping the AP_SM state information coded in the argument */
/* Binary 00 01 10 11... - means according to the MV_AP_PORT_SM_STATE above */
#define MCD_STAT_PORT_SM_STATE_INSERT(_portIndex,_state) \
     mcdStatPortSmStateInsert(_portIndex, _state)

/* Keeping the AP_SM status information coded in the argument */
/* Binary 00000 00001 00010 00011... - means according to the MV_AP_PORT_SM_STATUS above */
#define MCD_STAT_PORT_SM_STATUS_INSERT(_portIndex,_status) \
     mcdStatPortSmStatusInsert(_portIndex, _status)

/*******************************************************************
 MCD_STATUS mcdChannelSwReset
    Software Reset/Unreset of channel.
    Both Host and Line sides are in same state.
*******************************************************************/
MCD_STATUS mcdChannelSwReset
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      port,
    IN MCD_BOOL     action
);

/*******************************************************************************
 MCD_STATUS mcdDisableAllUmacInterrupts
 (
    IN MCD_DEV_PTR pDev,
);
 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call

 Outputs:
    None.

 Returns:
    MCD_OK if action was implemented successfuly, MCD_FAIL if not.

 Description:
    Disables all interrpt on UMAC/PCS level.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdDisableAllUmacInterrupts
(
    IN MCD_DEV_PTR pDev

);

/*******************************************************************
 MCD_STATUS mcdChannelMacBypas
 set/clear MAC and MACSEC and rate match bypass
*******************************************************************/
MCD_STATUS mcdChannelMacBypass
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 chan,
    IN MCD_BOOL action
);

/*******************************************************************
MCD_STATUS mcdClockGatingControl
set/clear clock gating for MAC ,MACSEC, PCS and PCS channels
*******************************************************************/
MCD_STATUS mcdClockGatingControl
(
    IN MCD_DEV_PTR pDev,
    IN MCD_CLOCK_GATE_TYPE cgType,
    IN MCD_U16 portNum,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL action
);

/*******************************************************************
 MCD_STATUS mcdChannelControl
   Channel enable/disable.
    Both Host and Line sides are in same state.
*******************************************************************/
MCD_STATUS mcdChannelControl
(
    IN MCD_DEV_PTR  pDev,
    IN MCD_U16      port,
    IN MCD_BOOL     action
);

/**
* @internal mcdPortSerdesTxEnable function
* @endinternal
*
* @brief   Enable/Disable Tx of port lines.
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
* @retval MCD_STATUS_NOT_READY     - when training is in process.
*/
MCD_STATUS mcdPortSerdesTxEnable
(
   MCD_DEV_PTR      pDev,
   MCD_U16          phyPortNum,
   MCD_BOOL         enable
);

/**
* @internal mcdForceOutputLocalFaults function
* @endinternal
*
* @brief   Start/Stop trasnmiting local faults
*
* @param[in] pDev                     - pointer to MCD_DEV
* @param[in] mdioPort                 - mdioPort
* @param[in] host_or_line             - side
* @param[in] serdesSpeed              - serdes speed
* @param[in] outputEnable             - enable/disable outputing
*       Local Faults.
*/
MCD_STATUS mcdForceOutputLocalFaults
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_SERDES_SPEED serdesSpeed,
    IN  MCD_BOOL outputEnable
);

/**
* @internal mcdLowSpeedANEnable function
* @endinternal
*
* @brief   Enable/Disable Auto Negotiation for 1G (Low speed) port mode.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be modified, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[in] anEnable               - 1 for AN enable, 0 for disable
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANEnable
(
    IN  MCD_DEV_PTR     pDev,
    IN  MCD_U16         mdioPort,
    IN  MCD_U16         host_or_line,
    IN  MCD_BOOL        anEnable
);

/**
* @internal mcdLowSpeedANEnableGet function
* @endinternal
*
* @brief   Read status (Enabled/Disabled) of ANenable for 1G (Low speed) port mode.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[out] anEnableSts           - Read ANenable status, 1=AN is Enabled, 0=AN Disabled.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANEnableGet
(
    IN  MCD_DEV_PTR     pDev,
    IN  MCD_U16         mdioPort,
    IN  MCD_U16         host_or_line,
    OUT  MCD_U32         *enable
);

/**
* @internal mcdLowSpeedANRestart function
* @endinternal
*
* @brief   Restarting AN will enable ANenable bit in case it is disabled (or) if ANenable bit is already
*          set then just restart AN state machine.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANRestart
(
    IN  MCD_DEV_PTR     pDev,
    IN  MCD_U16         mdioPort,
    IN  MCD_U16         host_or_line
);

/**
* @internal mcdLowSpeedANDoneGet function
* @endinternal
*
* @brief   Read the status of AN done bit.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[out] anDoneReg             - Read status of AN done.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANDoneGet
(
    IN  MCD_DEV_PTR     pDev,
    IN  MCD_U16         mdioPort,
    IN  MCD_U16         host_or_line,
    OUT MCD_U32         *anDoneReg
);

/**
* @internal mcdSetPortModeG21common function
* @endinternal
*
* @brief   Port configuration for G21L/G21SK.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call.
* @param[in] mdioPort               - MDIO port 0 to 7.
* @param[in] portMode               - operational mode of port that will be configured.
* @param[in] fecConfigPtr           - pointer to FEC type.
* @param[in] configPtr              - pointer to config DB.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
* @retval MCD_STATUS_BAD_PARAM      - on incorrect config structure
*
*/
MCD_STATUS mcdSetPortModeG21common
(
    IN  MCD_DEV_PTR               pDev,
    IN  MCD_U16                   mdioPort,
    IN  MCD_OP_MODE               portMode,
    IN  MCD_FEC_TYPE_GET          *fecConfigPtr,
    IN  MCD_MODE_CONFIG_PARAM_PTR configPtr
);

/**
* @internal mcdLowSpeedANAdvertSet function
* @endinternal
*
* @brief   Advertise AN capabilities.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[in] mode                   - Advertise modes of operation
*                                     MCD_BASEX_AD_ASYM_PAUSE 0x0100, i.e Bit-8: Asymm Pause bit
*                                     MCD_BASEX_AD_PAUSE      0x0080, i.e Bit-7: Pause
*                                     MCD_BASEX_AD_1000HDX    0x0040, i.e Bit-6: 1000X Half Duplex
*                                     MCD_BASEX_AD_1000FDX    0x0020, i.e Bit-5: 1000X Full Duplex
*                                     Ex1: To advertise Full duplex and pause, set mode = 0x00A0
*                                     Ex2: To advertise HALF & FULL duplex, set mode = 0x0060
*                                     Ex3: To advertise all of 1000Base-x capability, set mode = 0x01E0
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedANAdvertSet
(
    IN MCD_DEV_PTR      pDev,
    IN MCD_U16          mdioPort,
    IN MCD_U16          host_or_line,
    IN MCD_U32          mode
);

/*******************************************************************************
 MCD_STATUS mcdConfigurePcs1gR1
   This function performs channel configuration in  1GR1 mode
   basex_or_sgmii = 0 (SGMII) or 1 (BASEX)
   anEnable - enable inband AN
*******************************************************************************/
MCD_STATUS mcdConfigurePcs1gR1
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_U16 basex_or_sgmii,
    IN MCD_BOOL anEnable
);
/* *******************************************************************************
  MCD_STATUS mcdConfigurePcs2p5gR1
   This function performs channel configuration in 2.5G USXGMII mode
*******************************************************************************/
MCD_STATUS mcdConfigurePcs2p5gR1
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_FEC_TYPE fecCorrect
);
/* *******************************************************************************
  MCD_STATUS mcdConfigurePcs2p5gBasex
   This function performs channel configuration in 2.5G BASEx mode
*******************************************************************************/
MCD_STATUS mcdConfigurePcs2p5gBasex
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit
);

/******************************************************************************
MCD_STATUS mcdConfigurePcs10_25gR1
   This function performs channel configuration in 10 R1 or 25G R1 mode
******************************************************************************/
MCD_STATUS mcdConfigurePcs10_25gR1
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 slice,
    IN MCD_U16 chan,
    IN MCD_FEC_TYPE  fecCorrect,
    IN MCD_OP_MODE portMode
);

/******************************************************************************
MCD_STATUS mcdConfigurePcs40g
   This function performs channel configuration in 40/50G
******************************************************************************/
MCD_STATUS mcdConfigurePcs40g
(
    IN MCD_DEV_PTR pDev,
    IN MCD_OP_MODE portMode,
    IN MCD_U16 slice,
    IN MCD_U16 chan,
    IN MCD_CHANNEL_MODE_TYPE chanMode,
    IN MCD_FEC_TYPE fecCorrect
);
/*************************************************************************************
MCD_STATUS mcdConfigurePcs40gNewLs
configure 40GR2 mode with lane remapping on on unit
**************************************************************************************/
MCD_STATUS mcdConfigurePcs40gNewLs
(
    IN MCD_DEV_PTR pDev,
    IN MCD_OP_MODE portMode,
    IN MCD_U16 slice,
    IN MCD_U16 channelUnit,
    IN MCD_CHANNEL_MODE_TYPE chanMode,
    IN MCD_U16 laneRxDstArr[],
    IN MCD_U16 laneTxDstArr[],
    IN MCD_FEC_TYPE fecCorrect
);

/******************************************************************************
MCD_STATUS mcdConfigurePcs100gR4
   This function performs channel configuration in 100G R4 mode
******************************************************************************/
MCD_STATUS mcdConfigurePcs100gR4
(
    IN MCD_DEV_PTR pDev,
    IN MCD_OP_MODE portMode,
    IN MCD_U16 slice,
    IN MCD_U16 chan,
    IN MCD_FEC_TYPE  fecCorrect
);

/******************************************************************************
MCD_STATUS mcdPortPowerHwReset
   Power down and reset port on both the host and line side
******************************************************************************/
MCD_STATUS mcdPortPowerHwReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
);

/*******************************************************************
 MCD_STATUS mcdPortModeGetLanesNum
   Amount of lanes used by port mode (0 on wrong params).
*******************************************************************/
MCD_U16 mcdPortModeGetLanesNum
(
    IN MCD_OP_MODE portMode,
    IN MCD_U16 host_or_line
);

/**
* @internal mcdPortBuildLanesArray function
* @endinternal
*
* @brief   build an array of active SerDes lanes per side
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] portMode               - port mode.
* @param[in] host_or_line           - side.
* @param[out] serdesArr             - array of active lanes.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdPortBuildLanesArray
(
    IN  MCD_U16     mdioPort,
    IN  MCD_OP_MODE portMode,
    IN  MCD_U16 host_or_line,
    OUT MCD_U32 *serdesArr
);

/*******************************************************************
 MCD_STATUS mcdPortModeGetStoppedSerdesBitmaps
   returns bitmap of lanes in the slice that should be powered down
   before initialization of port with given mode at host and line sides.
*******************************************************************/
MCD_STATUS mcdPortModeGetSideSerdesBitmaps
(
    IN  MCD_OP_MODE portMode,
    IN  MCD_U16     mdioPort,
    OUT MCD_U16     *hostBmpPtr,
    OUT MCD_U16     *lineBmpPtr
);

/*******************************************************************
 MCD_STATUS mcdPortModeGetStoppedSerdesBitmaps
   returns bitmap of lanes in the slice that should be powered down
   before initialization of port with given mode at host and line sides.
*******************************************************************/
MCD_STATUS mcdPortModeGetStoppedSerdesBitmaps
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_OP_MODE portMode,
    IN  MCD_U16     mdioPort,
    OUT MCD_U16     *hostBmpPtr,
    OUT MCD_U16     *lineBmpPtr,
    OUT MCD_U16     *apPortsBmpPtr
);

/*******************************************************************
 MCD_STATUS mcdIsRetimerMode
   returns MCD_TRUE for retimer mode, otherwize MCD_FALSE.
*******************************************************************/
MCD_BOOL mcdIsRetimerMode
(
    IN MCD_OP_MODE portMode
);

/* header placed here because this function is not API */
/**
* @internal mcdPortStop function
* @endinternal
*
* @brief   Release all port resources, calls to serdes power down in order to
*         configure new port.
* @param[in] pDev                     - pointer to MCD_DEV
* @param[in] mdioPort                 - MDIO port address 0...7
* @param[in] newPortMode              - operational mode of port that will be configured
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdPortStop
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     mdioPort,
    IN MCD_OP_MODE newPortMode
);

/*******************************************************************
 MCD_STATUS mcdPortGetLanesNum
   Amount of lanes used by port (0 on wrong params).
*******************************************************************/
MCD_U16 mcdPortGetLanesNum
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line
);
/*******************************************************************
 MCD_STATUS mcdGetLaneSpeed
   returns lane speed.
*******************************************************************/
MCD_STATUS mcdGetLaneSpeed
(
    IN MCD_OP_MODE portMode,
    IN MCD_U16 host_or_line,
    OUT MCD_U32  *laneSpeed
);

/*******************************************************************************
 MCD_STATUS mcdIsPortValid
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MCD_OK - if mdioPort number is valid for the mode type
    MCD_FAIL - otherwise returns MCD_FAIL

 Description:
    Check the MDIO port number if it is valid for the selected mode type.
    Does various checking to make sure the given mdioPort is allowed to be configured
    in the selected mode type.

 Side effects:

 Notes/Warnings:
    None

*******************************************************************************/
MCD_STATUS mcdIsPortValid
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
);


/**
* @internal mcdServiceCpuRead function
* @endinternal
*
*/
MCD_STATUS mcdServiceCpuRead
(
    IN MCD_DEV_PTR pDev,
    unsigned int offset,
    unsigned int *dataPtr,
    unsigned int size
);

/**
* @internal mcdServiceCpuWrite function
* @endinternal
*
* @brief   Write to data Service CPU memory
*
* @retval 0                        - on success
* @retval 1                        - on error
*/
MCD_STATUS mcdServiceCpuWrite
(
    IN MCD_DEV_PTR pDev,
    unsigned int offset,
    unsigned int *data,
    unsigned int size
);

/*******************************************************************
 MCD_STATUS mcdPowerMgmtLineWait
    Extend power management wait time
*******************************************************************/
MCD_STATUS mcdPowerMgmtLineWait
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode,
    IN MCD_U16 waitBits
);

/*******************************************************************
 MCD_STATUS mcdPCSModePortPowerUp
    Power up chip PCS Mode
*******************************************************************/
MCD_STATUS mcdPCSModePortPowerUp
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode
);

/*******************************************************************
 MCD_STATUS mcdPortPowerUp
    Power up chip PCS Mode
*******************************************************************/
MCD_STATUS mcdPortPowerUp
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode
);

/*******************************************************************************
 MCD_STATUS mcdPowerConsumptionReduce
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_BOOL    action
)

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    action  = MCD_TRUE - disconnectclock from unused blocks
              MCD_FALSE - clock supplied to all blocks
Outputs:
    None

 Returns:
    MCD_OK if change was successful, MCD_FAIL if not. Will return
    MCD_FAIL if the parameters are not valid

 Description:

   disconnects unused blocks
*******************************************************************************/
MCD_STATUS mcdPowerConsumptionReduce
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_BOOL    action
);

/*******************************************************************
 MCD_STATUS mcdConfigRepeaterCK
    Power up chip PCS Mode
*******************************************************************/
MCD_STATUS mcdConfigRepeaterCK
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode
);
/******************************************************************************
MCD_STATUS mcdOneSideSetMode
   Line or Host mode selection
   portMode  - OP Mode
******************************************************************************/
MCD_STATUS mcdOneSideSetMode
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_OP_MODE portMode,
     IN MCD_U16 host_or_line,
     IN MCD_FEC_TYPE fecCorrect,
     IN MCD_MODE_CONFIG_PARAM_PTR configPtr
)
;

/******************************************************************************
MCD_STATUS mcdSetHostSideRetimerMode
 configue all lines on Host side
****************************************************************************/
MCD_STATUS mcdSetHostSideRetimerMode
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U32 laneSpeed,
     IN MCD_U32 numOfActLanes
);
/******************************************************************************
MCD_STATUS mcdSetMode
   Line and Host mode selection
   portMode  - OP Mode
   Note: soft reset is performed in this function.
******************************************************************************/
MCD_STATUS mcdSetMode
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode
);

/*******************************************************************************
 MCD_STATUS mcdGetModeSpeed
    Get mode speed based on the OP mode setting
*******************************************************************************/
MCD_STATUS mcdGetModeSpeed
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16     mdioPort,
    IN MCD_U16     host_or_line,
    OUT MCD_MODE_SPEED    *speed,
    OUT MCD_MODE          *mode
);

/*******************************************************************************
 MCD_STATUS mcdIsPortModePcsControlled
    Checks is mode of port controlled by PCS (retutn 1) or not (return 0).
*******************************************************************************/
MCD_U16 mcdIsPortModePcsControlled
(
    IN MCD_MODE portMode
);

/******************************************************************************
MCD_STATUS mcdGetNumberPorts
   The function checks the operational mode and returns the supported port
   count
******************************************************************************/
MCD_STATUS mcdGetNumberPorts
(
    IN MCD_OP_MODE mode,
    IN MCD_U16 *numPorts
);

/*******************************************************************************
 MCD_STATUS mcdGetAutoNegAcquiredSpeed
    Get Auto-neg aquired speed after auto-neg is completed
      MCD_AN_10GBKR                      0x0008
      MCD_AN_40GBKR4                     0x0020
      MCD_AN_40GBCR4                     0x0040
      MCD_AN_100GBCR10                   0x0100
      MCD_AN_100GBKP4                    0x0200
      MCD_AN_100GBKR4                    0x0400
      MCD_AN_100GBCR4                    0x0800
*******************************************************************************/
MCD_STATUS mcdGetAutoNegAcquiredSpeed
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_U16 *speed_bits
);

/*******************************************************************************
 MCD_STATUS mcdSetAutoNegAcquiredSpeed
    Set Auto-neg acquired speed after auto-neg is completed
*******************************************************************************/
MCD_STATUS mcdSetAutoNegAcquiredSpeed
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 speed_bit
);

/*******************************************************************************
 MCD_STATUS mcdReadPCSLinkStatus
    Check 40G PCS link status
*******************************************************************************/
MCD_STATUS mcdReadPCSLinkStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 hostRegAddr,
    IN MCD_U32 lineRegAddr,
    IN MCD_U32 bitIndex,
    OUT MCD_U16 *currentStatus,
    OUT MCD_U16 *latchedStatus,
    OUT DETAILED_STATUS_TYPE *statusDetail
);

/*******************************************************************************
 MCD_STATUS mcdReadRepeaterLinkStatus
    Check Serdes DSP lock status
*******************************************************************************/
MCD_STATUS mcdReadRepeaterLinkStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_U16 *CurrentStatus,
    OUT DETAILED_STATUS_TYPE *statusDetail
);
/*******************************************************************************
 MCD_STATUS mcdReadPCSLineLinkStatus
    Check status of port line side
*******************************************************************************/
MCD_STATUS mcdReadPCSLineLinkStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_U32 *currentStatus
);

/*****************************************************************************
Set port AP mode with referenced parameters - not applicable for retimer mode:
     MCD_U32 polarityVector - defines polarity map for all serdess
     MCD_U32 modesVector    - defines port AP capabilities :
                                    MCD_AN_1000BASE_KX
                                    MCD_AN_10GBase_KX4
                                    MCD_AN_10GBase_KR
                                    MCD_AN_40GBASE_KR4
                                    MCD_AN_40GBASE_CR4
                                    MCD_AN_100GBASE_CR10
                                    MCD_AN_100GBASE_KP4
                                    MCD_AN_100GBASE_KR4
                                    MCD_AN_100GBASE_CR4
                                    MCD_AN_25GBase_KR1S
                                    MCD_AN_25GBASE_KCR
                                    MCD_AN_25GBase_KR1_CONSORTIUM
                                    MCD_AN_25GBase_CR1_CONSORTIUM
                                    MCD_AN_50GBase_KR2_CONSORTIUM
                                    MCD_AN_50GBase_CR2_CONSORTIUM
    MCD_BOOL fcPause - TRUE if FC is enabled
    MCD_BOOL fcAsmDir - TRUE if assymetric FC is enabled
    MCD_FEC_TYPE fecSup - supported FEC
    MCD_FEC_TYPE fecReq - required FEC
    MCD_BOOL nonceDis - TRUE if in loopback
*************************************************************************/
MCD_STATUS mcdSetAutoNegParameters
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 apLaneNum,
    IN MCD_U32 polarityVector,
    IN MCD_U32 modesVector,
    IN MCD_BOOL fcPause,
    IN MCD_BOOL fcAsmDir,
    IN MCD_FEC_TYPE fecSup,
    IN MCD_FEC_TYPE fecReq,
    IN MCD_BOOL nonceDis

);

/*******************************************************************************
 MCD_STATUS mcdGetApPortParams
    Get AP port parameters
*******************************************************************************/
MCD_STATUS mcdGetApPortParams
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32 mdioPort,
    IN MCD_OP_MODE portMode,
    OUT MCD_U32  *modeVector,
    OUT MCD_U32  *laneSpeed,
    OUT MCD_U32 *numOfActLanes
);
/*******************************************************************************
 MCD_STATUS mcdIsFecParamValid
    Check if Fec is valid for the mode type
*******************************************************************************/
MCD_STATUS mcdIsFecParamValid
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_OP_MODE portMode,
    IN MCD_FEC_TYPE fecCorrect
);

/**
* @internal mcdLaneSteeringModeValidate function
* @endinternal
*
* @brief   lane steering validation function
*
* @param[in] pDev                   - device pointer
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] masterSlice            - master slice
* @param[in] laneSteeringMode       - lane steering port mode
*
* @retval MCD_OK                    - on success
* @retval MCD_FAIL                  - on failure
*
*
*/
MCD_STATUS mcdLaneSteeringModeValidate
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_MASTER_SLICE  masterSlice,
    IN  MCD_LANE_STEERING_MODE  laneSteeringMode
);

/**
* @internal mcdLaneSteeringRemapVectorRebuild function
* @endinternal
*
* @brief   constructing the remap data for single lane
* lane steering mode
*
* @param[in] pDev                   - device pointer
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] slice                  - slice
* @param[in] laneSteeringMode       - lane steering port mode
* @param[in] laneSteeringOverride   - lane steering override
* pointer
*
* @retval MCD_OK                    - on success
* @retval MCD_FAIL                  - on failure
*
*
*/
MCD_STATUS mcdLaneSteeringRemapVectorRebuild
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 slice,
    IN  MCD_LANE_STEERING_MODE  laneSteeringMode,
    IN  MCD_LANE_STEERING_OVERRIDE_CFG* laneSteeringOverride
);

/**
* @internal mcdLaneSteeringSingleModeTune function
* @endinternal
*
* @brief   single mode tuning for lane steering
* lane steering mode
*
* @param[in] pDev                   - device pointer
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] masterSlice            - master slice
*
* @retval MCD_OK                    - on success
* @retval MCD_FAIL                  - on failure
*
*
*/
MCD_STATUS mcdLaneSteeringSingleModeTune
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16  mdioPort,
    IN  MCD_MASTER_SLICE  masterSlice
);

/*******************************************************************
 MCD_STATUS mcdPortResetTimeout
 Check timeout after the soft or hard reset
*******************************************************************/
MCD_STATUS mcdPortResetTimeout
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 timeoutMs
);

/*******************************************************************
 MCD_STATUS mcdLaneReset
 Check timeout after the Lane soft reset
*******************************************************************/
MCD_STATUS mcdLaneSoftReset
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 timeoutMs
);

/*******************************************************************
 MCD_STATUS mcdLaneResetTimeout
 Check timeout after the Lane soft reset
*******************************************************************/
MCD_STATUS mcdLaneResetTimeout
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 timeoutMs
);

#ifndef ASIC_SIMULATION
/*******************************************************************
MCD_STATUS mcdInitBroadcastDev
(
    IN  MCD_DEV_PTR pPatternDev,
    OUT MCD_DEV_PTR pBroacastDev
);

 Inputs:
   pPatternDev  - pointer to holds device information to be used for each API call.
                  used to copy relevant info to the new "broadcast" device holder.
                  This device holder must be already initialized

 Outputs:
   pBroadcastDev - pointer to new "broadcast" device holder.

 Returns:
   MCD_OK    - on success
   MCD_FAIL  - on error

 Description:
   This function initializes "broadcast" device holder.
   Copies all relevant info from pPatternDev that must be already initialized
   destructed by mcdUnloadDriver.
   This device holder should be destructed by mcdUnloadDriver after use
   as a regular device holder.

 Side effects:
   None

 Notes/Warnings:
*******************************************************************/
MCD_STATUS mcdInitBroadcastDev
(
    IN  MCD_DEV_PTR pPatternDev,
    OUT MCD_DEV_PTR pBroadcastDev
);
#endif /*ASIC_SIMULATION*/

/******************************************************************************
 MCD_STATUS mcdLoadCm3FWImageStartOrEnd
*******************************************************************************/
MCD_STATUS mcdLoadCm3FWImageStartOrEnd
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_BOOL start    /* MCD_TRUE - start, MCD_FALSE - END */
);

/******************************************************************************
 MCD_STATUS mcdLoadCm3FWImageLoad
*******************************************************************************/
MCD_STATUS mcdLoadCm3FWImageLoad
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 imageSize, /* size in bytes         */
    IN const MCD_U8 image[]
);

/*******************************************************************************
 MCD_STATUS mcdPortPollingParamsGet
  *******************************************************************************/
MCD_STATUS mcdPortPollingParamsGet
(
    IN   MCD_DEV_PTR       pDev,
    IN   MCD_U16           mdioPort,
    OUT  MCD_BOOL          *retimerModePtr,
    OUT  MCD_SERDES_SPEED  *lineSerdesSpeedPtr,
    OUT  MCD_SERDES_SPEED  *hostSerdesSpeedPtr,
    OUT  MCD_U16           *lineSerdesBitmapPtr,
    OUT  MCD_U16           *hostSerdesBitmapPtr,
    OUT  MCD_NO_PPM_MODE   *noPpmModePtr
);

/*******************************************************************************
 MCD_STATUS mcdPortPollingLinkStatusStart
*******************************************************************************/
MCD_STATUS mcdPortPollingLinkStatusStart
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
);

/*******************************************************************************
 MCD_STATUS mcdPortPollingLinkStatusStop
  *******************************************************************************/
MCD_STATUS mcdPortPollingLinkStatusStop
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
);

/*******************************************************************************
 MCD_STATUS mcdPortSerdesDfeConfig_noSignalCheck
  *******************************************************************************/
MCD_STATUS mcdPortSerdesDfeConfig_noSignalCheck
(
    IN MCD_DEV_PTR       pDev,
    IN MCD_U16           mdioPort,
    IN MCD_DFE_MODE      dfeMode,
    IN MCD_BOOL          configIfRetimerMode,
    IN MCD_BOOL          configIfPcsMode,
    IN MCD_BOOL          configHostSide,
    IN MCD_BOOL          configLineSide
);

/**
* @internal mcdClearSerdesSignalLostIntCause function
* @endinternal
*
* @brief   Clear status of Serdes Signal Lost Interrupt.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] host_or_line             - the side of port (host or line)
* @param[in] slice                    -  0..1
* @param[in] channel                  -  0..3
*
* @retval MSD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdClearSerdesSignalLostIntCause
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U32 host_or_line,
    IN MCD_U32 slice,
    IN MCD_U32 channel
);

/**
* @internal mcdGetSerdesSignalLostIntCause function
* @endinternal
*
* @brief   Get status of Serdes Signal Lost Interrupt.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] host_or_line             - the side of port (host or line)
* @param[in] slice                    -  0..1
* @param[in] channel                  -  0..3
*
* @param[out] status                   - pointer to  of interrupt (0 - no signal lost or 1 - signal lost)
*
* @retval MSD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdGetSerdesSignalLostIntCause
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32 host_or_line,
    IN  MCD_U32 slice,
    IN  MCD_U32 channel,
    OUT MCD_U32 *status
);

/**
* @internal mcdCheckSerdesSignalStability function
* @endinternal
*
* @brief   Check Serdes Signal Stability.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] host_or_line             - the side of port (host or line)
* @param[in] slice                    -  0..1
* @param[in] channel                  -  0..3
* @param[in] testTimeMs               - time of period without signal lost in milliseconds.
*
* @param[out] status                   - pointer to  of interrupt (0 - signal not stable or 1 - signal stable)
*
* @retval MSD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdCheckSerdesSignalStability
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32 host_or_line,
    IN  MCD_U32 slice,
    IN  MCD_U32 channel,
    IN  MCD_U32 testTimeMs,
    OUT MCD_U32 *status
);

/**
* @internal mcdLockHwSemaphore function
* @endinternal
*
* @brief   Lock HW semaphore.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] semaphore_id             - semaphore id 0..127
* @param[in] event_id                 - event id 0..254
*
* @retval MCD_OK                   - on success
* @retval MCD_PENDING              - semaphore locked by other event
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdLockHwSemaphore
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32 semaphore_id,
    IN  MCD_U32 event_id
);

/**
* @internal mcdUnlockHwSemaphore function
* @endinternal
*
* @brief   Unock HW semaphore.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] semaphore_id             - semaphore id 0..127
*                                      event_id     - event id 0..254
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdUnlockHwSemaphore
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U32 semaphore_id
);
/**
* @internal mcd25gRsFecInit function
* @endinternal
*
* @brief   Init registers to support RS FEC 1.6 consortium.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcd25gRsFecInit
(
     IN MCD_DEV_PTR pDev
);
/**
* @internal mcdGetHwTimestamp function
* @endinternal
*
* @brief   Get HW timestamp.
*
* @param[in] pDev                     - pointer to MCD_DEV initialized by mcdInitDriver() call
*                                       Timestamp value in clocks.
*/
MCD_STATUS mcdGetHwTimestamp
(
    IN  MCD_DEV_PTR pDev
);

/*******************************************************************
 MCD_STATUS mcdPortModeVectorToPortMode
   returns portMode that mach the Port vector (for AP port), get the fastest mode.

*******************************************************************/
MCD_STATUS mcdPortModeVectorToPortMode
(
    IN  MCD_U32     modesVector,
    OUT MCD_OP_MODE *portModePtr
);

/*******************************************************************
  MCD_STATUS mcdSetPortLoopback
  lbMode options are:
    MCD_CLEAR_SERDES_LOOPBACK 0
    MCD_DEEP_SERDES_LOOPBACK 1
    MCD_SHALLOW_SERDES_LOOPBACK 2
    MCD_PARALLEL_SERDES_LOOPBACK 2
*******************************************************************/
MCD_STATUS mcdSetPortLoopback
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_OP_MODE portMode,
    IN  MCD_U16 host_or_line,
    IN  MCD_U32  lbMode
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MCDINTRNL_H */

