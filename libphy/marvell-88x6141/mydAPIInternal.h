/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and data that are strictly internal
for the proper functioning of the API on the Marvell X7120/X6181/X6141 PHY.
********************************************************************/
#ifndef MYDINTRNL_H
#define MYDINTRNL_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

extern const MYD_U16 opModeTable[MYD_OP_MODE_COUNT][MYD_OP_TABLE_COUNT];

#define MYD_RESET_TIMEOUT  10000 /* 10 sec max wait for power down HW reset */

/*******************************************************************************
 MYD_STATUS mydIsPortValid
    Check the MDIO port address if it is valid against the port address input
    during the mydInitDriver initialization
*******************************************************************************/
MYD_STATUS mydIsPortValid
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort
);

/*******************************************************************************
 MYD_STATUS mydIsOpModeValid
    Check the host and line Op Mode if it is valid combination
*******************************************************************************/
MYD_STATUS mydIsOpModeValid
(
    IN MYD_DEV_PTR pDev,
    IN MYD_OP_MODE lineOpMode,
    IN MYD_OP_MODE hostOpMode
);

/*******************************************************************************
 MYD_STATUS mydCheckOpModeLaneOffset
    Check if the lane offset is valid for the operational mode
*******************************************************************************/
MYD_STATUS mydCheckOpModeLaneOffset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode
);

/*******************************************************************************
 MYD_STATUS mydIsLaneOffsetValid
    Check if the lane offset is valid for the current mode setting of the
    given host or line side. Gets the current opMode and checks if the laneOffset
    is in range (0-3 for single lanes, 0 or 4 lanes, or 0,2 for 2 lane modes).
*******************************************************************************/
MYD_STATUS mydIsLaneOffsetValid
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
);

/*******************************************************************************
 MYD_STATUS mydCheckNeedReConfig
    Check if the new opMode on the laneOffset needs port re-configuration 
*******************************************************************************/
MYD_STATUS mydCheckNeedReConfig
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode
);

/*******************************************************************************
 MYD_STATUS mydCheckMixedOpModeSupport
    Check if mixed PCS and Repeater Op mode is supported in device or port
*******************************************************************************/
MYD_STATUS mydCheckMixedOpModeSupport
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE hostOpMode,
    IN MYD_OP_MODE lineOpMode
);

/*******************************************************************
 MYD_STATUS mydSetConfigInfo
    Set the config info on the Line or Host config structure
*******************************************************************/
MYD_STATUS mydSetConfigInfo
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode
);

/*******************************************************************************
 MYD_STATUS mydReadPCSLinkStatus
    Check PCS link status
*******************************************************************************/
MYD_STATUS mydReadPCSLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *currentStatus,
    OUT MYD_U16 *latchedStatus,
    OUT MYD_PCS_LINK_STATUS *statusDetail
);

/*******************************************************************************
 MYD_STATUS mydReadRepeaterLinkStatus
    Check Serdes DSP lock status on the ports
    Returns status of all lanes on both host and line side.
*******************************************************************************/
MYD_STATUS mydReadRepeaterLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_BOOL perLaneStatus,
    OUT MYD_U16 *CurrentStatus,
    OUT MYD_REPEATER_LINK_STATUS *statusDetail
);

/*******************************************************************
 MYD_STATUS mydConfigAutoNeg
   Configures the AutoNeg and Training mode setting for the host or 
   line sides
*******************************************************************/
MYD_STATUS mydConfigAutoNeg
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opMode,
    IN MYD_U16 enableFlag /* MYD_ENABLE or MYD_DISABLE */
);

/*******************************************************************
 MYD_STATUS mydExtendDeviceAutoNegTimer
    Used internally for mode configuration to extent the AN timer. 
*******************************************************************/
MYD_STATUS mydExtendDeviceAutoNegTimer
(
    IN MYD_DEV_PTR pDev
);

/*******************************************************************
 MYD_STATUS mydSetFixedMode
    Setting the Line or Host mode selection
*******************************************************************/
MYD_STATUS mydSetFixedMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption,
    IN MYD_OP_MODE opMode
);

/*******************************************************************
 MYD_STATUS mydSetRepeater400U
    Use 8xR50U for the R400U 
*******************************************************************/
MYD_STATUS mydSetRepeater400U
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption
);

/*******************************************************************
 MYD_STATUS mydSetRepeater200L
    Use 8xR25L for the R200L 
*******************************************************************/
MYD_STATUS mydSetRepeater200L
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U32 modeOption
);

/*******************************************************************************
 MYD_STATUS mydGetPktGenRegOffset
    Get packet generator register address offset based on Mode speed and lane
*******************************************************************************/
MYD_STATUS mydGetPktGenRegOffset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *regAddrOffset
);

/*******************************************************************
 MYD_STATUS mydPortPowerHwReset
   Power down and reset mdioPort on both the host and line side
*******************************************************************/
MYD_STATUS mydPortPowerHwReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort
);

/*******************************************************************
 MYD_STATUS mydPortPowerHwResetTimeout
    Power down and Reset mdioPort wait time
*******************************************************************/
MYD_STATUS mydPortPowerHwResetTimeout
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 timeoutMs
);

/*******************************************************************
 MYD_STATUS mydPortResetTimeout
 Check timeout after the soft or hard reset
*******************************************************************/
MYD_STATUS mydPortResetTimeout
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 timeoutMs
);

/*******************************************************************************
 MYD_STATUS mydSetDeepPCSLoopback
*******************************************************************************/
MYD_STATUS mydSetDeepPCSLoopback
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_U16 host_or_line,
    IN MYD_U16 gearboxMode,
    IN MYD_U16 autoNeg,
    IN MYD_SPEED Speed,
    IN MYD_U16 regAddrPCS,
    IN MYD_U16 loopbackBit
);

/*******************************************************************
 MYD_STATUS mydReloadConfigInfo
 Called by reload driver to update the host and line config info
*******************************************************************/
MYD_STATUS mydReloadConfigInfo
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort
);

/*******************************************************************
 MYD_STATUS mydLaneResetTimeout
 Check timeout after the Lane soft reset
*******************************************************************/
MYD_STATUS mydLaneResetTimeout
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 timeoutMs
);

/*******************************************************************
 MYD_STATUS mydLoadEEPROMSerdesWaitTime
 This will always return MYD_OK. It will speed up the wait time
 if checking for EEPROM is possible.
 Checks Serdes firmware loading from EEPROM completion
 If no EEPROM, the wait time is timeoutMs
*******************************************************************/
MYD_STATUS mydLoadEEPROMSerdesWaitTime
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 timeoutMs,
    OUT MYD_U16 *waitTimeMs
);

/*******************************************************************************
 MYD_STATUS mydCheckSupportedPinMode
    Check if a mode is supported for the given multi-purpose Pin
*******************************************************************************/
MYD_STATUS mydCheckSupportedPinMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    IN MYD_PIN_MODE pinMode
);

/******************************************************************************
 MYD_STATUS mydGPIOPinGetPortAndReg()
    This function calculate the port and register needed for configure GPIO Pin
******************************************************************************/
MYD_STATUS mydGPIOPinGetPortAndReg
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID gpioPinId,
    OUT MYD_U16 *GPIOPort,
    OUT MYD_U16 *GPIOCtrlReg
);

/******************************************************************************
 MYD_STATUS mydLEDConfigInputCheck
    This function check if passed-in LED configuration is out of range 
    See mydConfigLEDPin() for details.
******************************************************************************/
MYD_STATUS mydLEDConfigInputCheck
(
    IN MYD_LED_ID ledId,
    IN MYD_LED_CTRL ledCtrl,
    IN MYD_LED_TIMER_CONFIG ledTimerConfig
);

/******************************************************************************
 MYD_STATUS mydRClkMuxInputCheck
    This function check if passed-in MYD_RCLK_MUX_OPTION is out of range
    See mydConfigRClkMux() for details.
******************************************************************************/
MYD_STATUS mydRClkMuxInputCheck
(
    IN MYD_U16 portIndex,
    IN MYD_U16 interfaceIndex,
    IN MYD_U16 muxNum,
    IN MYD_RCLK_MUX_OPTION mux
);

/******************************************************************************
 MYD_STATUS mydRClkConfigInputCheck
    This function check if passed-in RCLK configuration is out of range 
    See mydConfigRClkPin() for details.
******************************************************************************/
MYD_STATUS mydRClkConfigInputCheck
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID rClkPinId,
    IN MYD_U16 portSelect,
    IN MYD_U16 interfaceSelect,
    IN MYD_U16 muxOptionSelect
);

/******************************************************************************
 MYD_STATUS mydRClkSelectSource
    This function select source for given RCLK Pin by given Port, interface and MUX
    See mydConfigRClkPin() for details.
******************************************************************************/
MYD_STATUS mydRClkSelectSource
(
    IN MYD_DEV_PTR pDev,
    IN MYD_PIN_ID pinId,
    IN MYD_U16 portSelect,
    IN MYD_U16 interfaceSelect,
    IN MYD_U16 muxOptionSelect
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MYDINTRNL_H */
