/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions using MDIO access to perform resets, perform
queries of the phy, etc. that are necessary to control and read
status of the Marvell X5121/X5111/X2381/X5123 PHY.
********************************************************************/
#ifndef MCD_API_H
#define MCD_API_H
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#define MCD_API_MAJOR_VERSION 5
#define MCD_API_MINOR_VERSION 1
#define MCD_API_PATCH_VERSION 2

#define MCD_MAX_SERDES_PER_SLICE 4
#define MCD_MAX_SERDES 8

#define MCD_LANE_STEERING_NO_LPB 0xFF

/* This macro is handy for calling a function when you want to test the
   return value and return MCD_FAIL, if the function returned MCD_FAIL,
   otherwise continue */

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
#define ATTEMPT(xFuncToTry) {if(xFuncToTry != MCD_OK) \
                            {MCD_DBG_ERROR("ATTEMPT failed at %s:%u\n",__FUNCTION__,__LINE__); \
                            return MCD_FAIL;}}
#else
#define ATTEMPT(xFuncToTry) {if(xFuncToTry != MCD_OK) \
                           { MCD_DBG_ERROR("ATTEMPT failed at %s\n",__FUNCTION__); \
                            return MCD_FAIL;}}
#endif

/******************************************************************************
MCD_STATUS mcdSetDefaultInitDB
(
    IN MCD_DEV_PTR                    pDev,
    IN MCD_U16                        mdioPort,
    IN MCD_MODE_CONFIG_PARAM_PTR      configPtr
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address 0...7 of mdioPort to be configured
    configPtr  - the structure contains fields to configure different parameters:
         noPpmMode          - should be set to TRUE if there is a need to propagate the line side Rx
                              clock through the device toward the host side, and use it as Tx clock
                              this mode is used in synchronous ethernet applications in which the recovered clock selection
                              is done on the host side  and not directly from the device.
         electricalParamPtr - pointer to array of serdes electrical parameters structure:
                                       where
                                              typedef struct
                                              {
                                                  MCD_U8     rxPolarity;
                                                  MCD_U8     txPolarity;
                                                  MCD_U16    preCursor;
                                                  MCD_U16    attenuation;
                                                  MCD_U16    postCursor;
                                                  MCD_U8     bitMapEnable;
                                              }MCD_SERDES_CONFIG_DATA;
                        if electricalParamPtr is NULL - default parameters are set:
                                rxPolarity = 0
                                txPolarity = 0
                                precursor   - default per baudrate (see mcdSerdesTxRxTuneParamsArray)
                                attenuation - default per baudrate (see mcdSerdesTxRxTuneParamsArray)
                                postCursor  - default per baudrate (see mcdSerdesTxRxTuneParamsArray)

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL, if action was successful or not

 Description:
    Initialization the Data structure with defaults. Must be called after
    mcdInitDriver() and before mcdSetModeSelectionExt()

 Side effects:
    None

 Notes/Warnings:
   Must be called after mcdInitDriver() and before mcdSetModeSelectionExt() call

******************************************************************************/
MCD_STATUS mcdSetDefaultInitDB
(
    IN MCD_DEV_PTR                    pDev,
    IN MCD_U16                        mdioPort,
    IN MCD_MODE_CONFIG_PARAM_PTR      configPtr
);

/******************************************************************************
MCD_STATUS mcdSetModeSelectionExt
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_OP_MODE portMode,
     IN MCD_BOOL autoNegAdvEnable,
     IN MCD_BOOL fecCorrect,
     IN MCD_MODE_CONFIG_PARAM_PTR configPtr
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address 0...7 of mdioPort to be configured
    portMode - operational mode
    autoNegAdvEnable - Enable Auto Neg if set to TRUE
    fecCorrect - FEC correct
    configPtr  - the structure contains fields to configure different parameters:
         noPpmMode          - should be set to TRUE if there is a need to propagate the line side Rx
                              clock through the device toward the host side, and use it as Tx clock
                              this mode is used in synchronous ethernet applications in which the recovered clock selection
                              is done on the host side  and not directly from the device.
         electricalParamPtr - pointer to array of serdes electrical parameters structure:
                                       where
                                              typedef struct
                                              {
                                                  MCD_U8     rxPolarity;
                                                  MCD_U8     txPolarity;
                                                  MCD_U16    preCursor;
                                                  MCD_U16    attenuation;
                                                  MCD_U16    postCursor;
                                                  MCD_U8     bitMapEnable;
                                              }MCD_SERDES_CONFIG_DATA;
                        if electricalParamPtr is NULL - default parameters are set:
                                rxPolarity = 0
                                txPolarity = 0
                                precursor   - default per baudrate (see mcdSerdesTxRxTuneParamsArray)
                                attenuation - default per baudrate (see mcdSerdesTxRxTuneParamsArray)
                                postCursor  - default per baudrate (see mcdSerdesTxRxTuneParamsArray)


 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL, if action was successful or not

 Description:
    Set the port mode parameters , including noPPM mode.

 Side effects:

 Notes/Warnings:

******************************************************************************/
MCD_STATUS mcdSetModeSelectionExt
(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_OP_MODE portMode,
     IN MCD_BOOL autoNegAdvEnable,
     IN MCD_FEC_TYPE fecCorrect,
     IN MCD_MODE_CONFIG_PARAM_PTR configPtr
);

/******************************************************************************
MCD_STATUS mcdSetLaneSteering

 Description:
    Set port with laneSteering/Remap mode, support AP and none AP port.
 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address 0...31 of mdioPort to be configured
    portMode - operational mode
    masterSlice - active slice
    laneSteeringMode - MCD_P100G_STEERING,
                        MCD_P40G_STEERING,
                        MCD_4P_P25G_STEERING,
                        MCD_4P_P10G_STEERING,
                        MCD_P100G_P40G_P10G_STEERING_AP,
                        MCD_4P_P25G_STEERING_AP,
                        MCD_4P_P10G_STEERING_AP,
                        MCD_4P_P1G_1000BaseX_STEERING,
                        MCD_4P_P1G_SGMII_STEERING,
                        MCD_G21L_NONE_STEERING,
                        MCD_G21L_P10G_NONE_STEERING_AP,
                        MCD_1P_P25G_STEERING,
                        MCD_1P_P10G_STEERING,
                        MCD_1P_P10G_25G_STEERING_AP,
                        MCD_1P_P1G_1000BaseX_STEERING,
                        MCD_1P_P1G_SGMII_STEERING
                        fecCorrect - FEC correct
    reducedRxTraining - bypass HF/BW values



 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL, if action was successful or not

 Notes/Warnings:

******************************************************************************/

MCD_STATUS mcdSetLaneSteering
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_MASTER_SLICE  masterSlice,
    IN  MCD_LANE_STEERING_MODE  laneSteeringMode,
    IN  MCD_FEC_TYPE  fecCorrect,
    IN  MCD_BOOL      reducedRxTraining,
    IN MCD_MODE_CONFIG_PARAM_PTR configPtr
);

MCD_STATUS mcdSetLaneRemapping
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      host_or_line,
    IN  MCD_U16      sliceNum,
    IN  MCD_SERDES_TXRX_LANE_REMAP (*configSerdesRemapPtr)[MCD_MAX_SLICE_NUM]
);

/*******************************************************************
 Enabling speeds for autonegotiation to advertise
 Reading speeds enabled for autonegotation
 Enabling/Disabling/Restarting autonegoation
 *******************************************************************/
#define MCD_ADV_NONE           0x0000 /* No speeds to be advertised */
#define MCD_ADV_10KR           0x0001
#define MCD_ADV_40KR4          0x0002
#define MCD_ADV_40CR4          0x0004
#define MCD_ADV_100CR10        0x0008
#define MCD_ADV_100KP4         0x0010
#define MCD_ADV_100KR4         0x0020
#define MCD_ADV_100CR4         0x0040
#define MCD_ADV_25CKR          0x1000
#define MCD_ADV_ALL_CR4        (MCD_ADV_40CR4 | MCD_ADV_100CR4)
#define MCD_ADV_ALL_KR4        (MCD_ADV_40KR4 | MCD_ADV_100KR4)

/******************************************************************************
 MCD_STATUS mcdSetAutoNegAdvertisingSpeeds
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U16 host_or_line,
     IN MCD_U16 speed_bits
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being modified:
         MCD_HOST_SIDE
         MCD_LINE_SIDE
    speed_bits - speeds to be advertised during auto-negotiation. One of the following:
        MCD_ADV_NONE
        MCD_ADV_40KR4
        MCD_ADV_40CR4
        MCD_ADV_100KR4
        MCD_ADV_100CR4
        MCD_ADV_ALL_CR4
        MCD_ADV_ALL_KR4

 Outputs:
    None

 Returns:
    MCD_OK if action was successfully taken, MCD_FAIL if not (modes
    not supporting a particular speed combination or attempting
    to advertising CR and KR both will result in MCD_FAIL)

 Description:
    This function sets the auto-negotiation local advertising speeds only.
    It does not start the auto negotiation. To start auto-negotiation, function
    mcdAutoNegStart() needs to be called.

 Side effects:

 Notes/Warnings:

    Example:
******************************************************************************/
MCD_STATUS mcdSetAutoNegAdvertisingSpeeds
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_U16 speed_bits
);

/******************************************************************************
MCD_STATUS mcdGetAutoNegAdvertisingSpeeds
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_U16 *speed_bits
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
         MCD_HOST_SIDE
         MCD_LINE_SIDE

 Outputs:
    speed_bits - bits set according to which speeds are currently being
        advertised. One or more bits set according to the defines above
        in mcdSetAutoNegAdvertisingSpeeds().

 Returns:
    MCD_OK or MCD_FAIL, if query succeeded or failed

 Description:
    This function returns the speeds that have been advertised.

 Side effects:

 Notes/Warnings:
    Speeds advertised don't take effect until auto-negotiation is restarted.

******************************************************************************/
MCD_STATUS mcdGetAutoNegAdvertisingSpeeds
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_U16 *speed_bits
);


/******************************************************************************
 MCD_STATUS mcdAutoNegStart
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U16 host_or_line,
     IN MCD_BOOL swReset
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being modified:
      MCD_HOST_SIDE
      MCD_LINE_SIDE

    swReset - changes to advertisement require a software reset to take
              effect, MCD_TRUE or MCD_FALSE indicates whether to perform
              the software reset

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL, depending on if action was successful

 Description:
    Start or Restarts auto-negotiation. The bit is self-clearing. If the link is up,
    the link will drop and auto-negotiation will start again.

 Side effects:
    None.

 Notes/Warnings:
    Restarting auto-negotiation will enable the auto-negotiation if auto-negotiation is
    disabled.

    This function is important as it is necessary to start or restart auto-negotiation
    after changing many auto-negotiation settings before the changes will take
    effect.

******************************************************************************/
MCD_STATUS mcdAutoNegStart
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL swReset
);

/******************************************************************************
 MCD_STATUS mcdAutoNegDisable
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U16 host_or_line,
     IN MCD_BOOL swReset
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being modified:
      MCD_HOST_SIDE
      MCD_LINE_SIDE
    swReset - disable Auto-neg require a software reset to stop auto-neg
              in progress

 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL, if action was successful or not

 Description:
    Turns off the enable auto-negotiation bit disabling auto-negotiation.

 Side effects:

 Notes/Warnings:
    Restart autonegation will not take effect if AN is disabled.

******************************************************************************/
MCD_STATUS mcdAutoNegDisable
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL swReset
);

/******************************************************************************
 MCD_STATUS mcdAutoNegEnable
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U16 host_or_line
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being modified:
      MCD_HOST_SIDE
      MCD_LINE_SIDE


 Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL, if action was successful or not

 Description:
    Re-enables auto-negotiation.

 Side effects:

 Notes/Warnings:
    Restart autonegation will not take effect if AN is disabled.

******************************************************************************/
MCD_STATUS mcdAutoNegEnable
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line
);

/**
* @internal mcdLowSpeedAutoNegEnable function
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
MCD_STATUS mcdLowSpeedAutoNegEnable
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL anEnable
);

/**
* @internal mcdLowSpeedAutoNegEnableGet function
* @endinternal
*
* @brief   Read the current status (Enalbed/Disabled) of AN for 1G (Low speed) port mode.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[out] enable                - Read AN status
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedAutoNegEnableGet
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_BOOL *enable
);

/**
* @internal mcdLowSpeedAutoNegRestart function
* @endinternal
*
* @brief   Restarting AN will enable ANenable bit in case it is disabled (or) if ANenable bit is already
*          set then just restart AN.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedAutoNegRestart
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line
);

/**
* @internal mcdLowSpeedAutoNegDoneGet function
* @endinternal
*
* @brief   Read the status of AN done bit.
*
* @param[in] pDev                   - pointer to MCD_DEV initialized by mcdInitDriver() call
* @param[in] mdioPort               - MDIO port, 0-7
* @param[in] host_or_line           - which interface to be monitored, MCD_HOST_SIDE or MCD_LINE_SIDE
* @param[out] anDoneSts             - Read status of AN done.
*
* @retval MCD_OK                    - on success.
* @retval MCD_FAIL                  - on failure
*
*/
MCD_STATUS mcdLowSpeedAutoNegDoneGet
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_BOOL *anDoneSts
);

/**
* @internal mcdLowSpeedAutoNegAdvertSet function
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
MCD_STATUS mcdLowSpeedAutoNegAdvertSet
(
    IN MCD_DEV_PTR      pDev,
    IN MCD_U16          mdioPort,
    IN MCD_U16          host_or_line,
    IN MCD_U32          mode
);

/*******************************************************************
 AP capabilities definitions
 *******************************************************************/
#define MCD_AN_1000BASE_KX                            0x0001
#define MCD_AN_10GBase_KX4                            0x0002
#define MCD_AN_10GBase_KR                             0x0004
#define MCD_AN_40GBASE_KR4                            0x0008
#define MCD_AN_40GBASE_CR4                            0x0010
#define MCD_AN_100GBASE_CR10                          0x0020
#define MCD_AN_100GBASE_KP4                           0x0040
#define MCD_AN_100GBASE_KR4                           0x0080
#define MCD_AN_100GBASE_CR4                           0x0100
#define MCD_AN_25GBase_KR1S                           0x0200
#define MCD_AN_25GBASE_KCR                            0x0400
#define MCD_AN_25GBase_KR1_CONSORTIUM                 0x0800
#define MCD_AN_25GBase_CR1_CONSORTIUM                 0x1000
#define MCD_AN_50GBase_KR2_CONSORTIUM                 0x2000
#define MCD_AN_50GBase_CR2_CONSORTIUM                 0x4000

/*******************************************************************
 Reading speed after autonegotation
 *******************************************************************/
#define MCD_NEG_NONE               0x0000 /* Auto-Neg not completed */
#define MCD_NEG_1000KX             0x0001
#define MCD_NEG_10KR               0x0009
#define MCD_NEG_40KR4              0x0021
#define MCD_NEG_40CR4              0x0041
#define MCD_NEG_100CR10            0x0101
#define MCD_NEG_100KP4             0x0201
#define MCD_NEG_100KR4             0x0401
#define MCD_NEG_100CR4             0x0801
#define MCD_NEG_25KR_CONSORTIUM    0x0011
#define MCD_NEG_25CR_CONSORTIUM    0x0081
#define MCD_NEG_25KRCS             0x1001
#define MCD_NEG_25KCR              0x2001
#define MCD_NEG_50KR_CONSORTIUM    0x4001
#define MCD_NEG_50CR_CONSORTIUM    0x8001


/******************************************************************************
MCD_STATUS mcdSetAPModeSelection
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 apLaneNum,
    IN MCD_U32 modesVector,
    IN MCD_BOOL fcPause,
    IN MCD_BOOL fcAsmDir,
    IN MCD_FEC_TYPE fecSup,
    IN MCD_FEC_TYPE fecReq,
    IN MCD_BOOL nonceDis
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address 0...7 of mdioPort to be configured
    MCD_U32 apLaneNum - lane number for AP protocol run
    MCD_U32 modesVector - defines port AP capabilities :
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

    MCD_BOOL fcPause                         - TRUE if FC is enabled
    MCD_BOOL fcAsmDir                        - TRUE if assymetric FC is enabled
    MCD_FEC_TYPE fecSup                      - supported FEC
    MCD_FEC_TYPE fecReq                      - required FEC
    MCD_BOOL nonceDis                        - TRUE if in loopback
    MCD_CONFIG_SERDES_AP_PARAM_PTR configPtr - pointer to the structure that defines
                                               serdes electrical params (Tx and Rx polarity)
                                               if  configPtr == NULL - Tx and Rx polarity set to 0

    MCD_BOOL apEnable - if TRUE - starts the AP
Outputs:
    None

 Returns:
    MCD_OK or MCD_FAIL, if action was successful or not

 Description:
    Set port AP mode with referenced parameters - not applicable for retimer mode.

 Side effects:

 Notes/Warnings:

******************************************************************************/
MCD_STATUS mcdSetAPModeSelection
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 portNum,
    IN MCD_U32 apLaneNum,
    IN MCD_U32 modesVector,
    IN MCD_BOOL fcPause,
    IN MCD_BOOL fcAsmDir,
    IN MCD_FEC_TYPE fecSup,
    IN MCD_FEC_TYPE fecReq,
    IN MCD_BOOL nonceDis,
    IN MCD_CONFIG_SERDES_AP_PARAM_PTR configPtr,
    IN MCD_BOOL apEnable
);

/******************************************************************************
 MCD_STATUS mcdAutoNegCheckCompleteExt
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U16 host_or_line,
     IN MCD_BOOL set_speed,
     IN MCD_MODE_CONFIG_PARAM_PTR configPtr,
     OUT MCD_U16 *speed
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-7
    host_or_line - which interface is being checked:
      MCD_HOST_SIDE
      MCD_LINE_SIDE
    set_speed - TRUE:  Set the opposite side speed with AN result.
                FALSE: Don't set speed
    configPtr  - the structure contains fields to configure different parameters:
         noPpmMode          - should be set to TRUE if there is a need to propagate the line side Rx
                              clock through the device toward the host side, and use it as Tx clock -
                              this mode is used in synchronous ethernet applications in which the recovered clock selection
                              is done on the host side  and not directly from the device.
         electricalParamPtr - pointer to array of serdes electrical parameters structure:
                                       where
                                              typedef struct
                                              {
                                                  MCD_U8     rxPolarity;
                                                  MCD_U8     txPolarity;
                                                  MCD_U16    preCursor;
                                                  MCD_U16    attenuation;
                                                  MCD_U16    postCursor;
                                                  MCD_U8     bitMapEnable;
                                              }MCD_SERDES_CONFIG_DATA;
                        if electricalParamPtr is NULL - default parameters are set:

 Outputs:
    speed - the result of auto-negotiation. One of the following:
        MCD_NEG_NONE (AN still in process or disabled)
        MCD_NEG_10KR
        MCD_NEG_40KR4
        MCD_NEG_40CR4
        MCD_NEG_100CR10
        MCD_NEG_100KP4
        MCD_NEG_100KR4
        MCD_NEG_100CR4
        MCD_NEG_25KR_CONSORTIUM
        MCD_NEG_25CR_CONSORTIUM
        MCD_NEG_25KRCS
        MCD_NEG_25KCR
        MCD_NEG_50KR_CONSORTIUM
        MCD_NEG_50CR_CONSORTIUM

 Returns:
    MCD_OK or MCD_FAIL, if action was successful or not

 Description:
    Set the Host side speed/FEC with AN result, noPPM mode and electrical parameters if set-speed is TRUE.
    This function returns the auto-negotiated speed upon completion.
    If the training/AN is not finished, it returns MTD_NEG_NONE
    for the speed.

 Side effects:

 Notes/Warnings:

******************************************************************************/
MCD_STATUS mcdAutoNegCheckCompleteExt
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    IN MCD_BOOL set_speed,
    IN MCD_MODE_CONFIG_PARAM_PTR configPtr,
    OUT MCD_U16 *speed
);

#define MCD_LINK_UP   1
#define MCD_LINK_DOWN 0
typedef union
{
    /*********** PCS MODES **********************/
    struct
    {
        MCD_U16  hostCurrent; /* per mdioPort */
        MCD_U16  hostLatched;
        MCD_U16  lineCurrent;
        MCD_U16  lineLatched;
        MCD_U16  hostLinkChanged;
        MCD_U16  lineLinkChanged;
    } P100_40_status; /* P100L/S/C/K and P40L/C/K */

    /********* REPEATER MODES ********************/
    struct
    {
        MCD_U16 hostCurrent[8]; /* per lane */
        MCD_U16 lineCurrent[8]; /* per lane */
    } R25_10_status; /* R25L/C, R10L/K */

    struct
    {
        MCD_U16 host_P0[4];
        MCD_U16 host_P1[4];
        MCD_U16 line_P0[4];
        MCD_U16 line_P1[4];
        MCD_U16 hostCurrent[8]; /* per lane */
        MCD_U16 lineCurrent[8]; /* per lane */
    } R100_40_status; /* R100L/C, R40L/C */

    /********* MLG MODES *************************/
#if 0 /* TBD */
    struct
    {
    }
#endif
} DETAILED_STATUS_TYPE;

/******************************************************************************
 MCD_STATUS mcdCheckLinkStatus
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     OUT MCD_U16 *currentStatus,
     OUT MCD_U16 *latchedStatus,
     OUT DETAILED_STATUS_TYPE *statusDetail
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    currentStatus - overall current status of link. MCD_LINK_UP if
        both line and host is up, MCD_LINK_DOWN if any component of
        host or line is down
    latchedStatus - latched status since last time mcdCheckLinkStatus()
        was called. Not available in repeater modes. Available only in
        PCS modes and MLG modes. This is the combination of all latched
        bits on both host and line side giving an overall latched
        indication if link dropped since last read. MCD_LINK_UP
        if no link drop was seen, MCD_LINK_DOWN if any link drop
        was seen.
        Note: This status does not apply to the repeater mode.
    statusDetail - gives details of status for all components links
        on both host and line side. For repeater modes, this is
        the combined serdes status of all lanes on host and line
        side. For PCS modes this is the combined PCS status for host
        and line side. The structure returned depends on the
        mode of operation. See DETAILED_STATUS_TYPE for details.

 Returns:
    MCD_OK or MCD_FAIL, if action was successful or not.

 Description:
    Depending on the mode of operation of this mdioPort, looks at all
    components of the link on both host and line side and returns an
    overall indication if the link is up or down currently in
    "currentStatus". Returns an indication if the link dropped since
    the last time mcdCheckLinkStatus() was called for those
    modes that have a latched status (PCS modes and MLG modes).

    Also returns more details in "statusDetail" in case host or
    line side details for specific lanes are desired. See
    DETAILED_STATUS_TYPE for the different structures that will be
    returned for different modes of operation.

 Side effects:
    Calling this function will clear any latched bits that are
    a component of the link status.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdCheckLinkStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    OUT MCD_U16 *currentStatus,
    OUT MCD_U16 *latchedStatus,
    OUT DETAILED_STATUS_TYPE *statusDetail
);

/******************************************************************************
 MCD_STATUS mcdGetPcsFaultStatus
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort,
     IN MCD_U16 host_or_line,
     OUT MCD_U16 *currentTxFaultStatus,
     OUT MCD_U16 *currentRxFaultStatus,
     OUT MCD_U16 *latchedTxFaultStatus,
     OUT MCD_U16 *latchedRxFaultStatus
 );

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
       MCD_HOST_SIDE
       MCD_LINE_SIDE


 Outputs:
    currentTxFaultStatus - the value of the Tx Fault Status
        on the second read of the status register (the current status
        after clearing the latch bit)
    currentRxFaultStatus - the value of the Rx Fault Status
        on the second read of the status register (the current status
        after clearing the latch bit)
    latchedTxFaultStatus - the value of the Tx Fault Status
        on the first read of the status register (the value of
        the latched bit since the last read)
    latchedRxFaultStatus - the value of the Rx Fault Status
        on the first read of the status register (the value of
        the latched bit since the last read)

 Returns:
    MCD_OK if query was successful, MCD_FAIL if not. Will return
    MCD_FAIL if the operating mode is not set properly or
    the device is not initialized for this mode of operation.

 Description:
    This function is to be called in any of the 40G or 100G PCS
    modes to check the Tx/Rx fault bits.

    Based on the current operating mode, it reads either the 40G
    or 100G Host/Line PCS Status 2 register twice and returns the value
    of the Tx/Rx fault bits. It returns the first read in the
    "latched" version and the second read in the "current" version.

    For 100G Host Side:
        4.8.11 Tx Fault
        4.8.10 Rx Fault

    For 100G Line Side:
        3.8.11 Tx Fault
        3.8.10 Rx Fault

    For 40G Host Side:
        4.1008.11 Tx Fault
        4.1008.10 Rx Fault

    For 40G Line Side:
        3.1008.11 Tx Fault
        4.1008.10 Rx Fault

 Side effects:
    None.

 Notes/Warnings:
    Clears the latch status of those registers being read.

    Speed must be resolved if using AN and/or port must be configured using
    40G or 100G PCS mode, otherwise an error is returned.

******************************************************************************/
MCD_STATUS mcdGetPcsFaultStatus
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 host_or_line,
    OUT MCD_U16 *currentTxFaultStatus,
    OUT MCD_U16 *currentRxFaultStatus,
    OUT MCD_U16 *latchedTxFaultStatus,
    OUT MCD_U16 *latchedRxFaultStatus
);

/*****************************************************************************
Enabling and Checking Interrupts and Real-Time Status 40GBASE-R4 Bit
Definitions (for first field in interrupt/status registers)
NOTE: the second field in the functions are not used for 40GBASE-R4 only
for 100GBASE-R4.
*****************************************************************************/
#define MCD_40G_LF_TXD_BIT       (1<<11)   /* Bit definitions for 40GBASE-R4 Interrupt Enable Register */
#define MCD_40G_LF_RXD_BIT       (1<<10)   /* and 40GBASE-R4 Interrupt Status Register */
#define MCD_40G_LN_ALIGN_BIT     (1<<9)
#define MCD_40G_TX_LN_ERRCNT_BIT (1<<8)
#define MCD_40G_JIT0_LOCK_BIT    (1<<7)
#define MCD_40G_JIT_LF_BIT       (1<<6)
#define MCD_40G_LINK_BIT         (1<<5)
#define MCD_40G_HI_BER_BIT       (1<<4)
#define MCD_40G_LN3_BLK_LK_BIT   (1<<3)
#define MCD_40G_LN2_BLK_LK_BIT   (1<<2)
#define MCD_40G_LN1_BLK_LK_BIT   (1<<1)
#define MCD_40G_LN0_BLK_LK_BIT   (1<<0)

#define MCD_40G_LN3_LOCK_BIT      (1<<15)  /* Bit definitions for 40GBASE-R4 Real Time Status Register */
#define MCD_40G_LN2_LOCK_BIT      (1<<14)
#define MCD_40G_LN1_LOCK_BIT      (1<<13)
#define MCD_40G_LN0_LOCK_BIT      (1<<12)
#define MCD_40G_LF_TXD_RT_BIT     (1<<11)
#define MCD_40G_LF_RXD_RT_BIT     (1<<10)
#define MCD_40G_LN_ALIGN_RT_BIT   (1<<9)
/* NOT USED (1<<8) */
#define MCD_40G_JIT0_LOCK_RT_BIT  (1<<7)
#define MCD_40G_JIT_LF_RT_BIT     (1<<6)
#define MCD_40G_LINK_RT_BIT       (1<<5)
#define MCD_40G_HI_BER_RT_BIT     (1<<4)
#define MCD_40G_LN3_BLK_LK_RT_BIT (1<<3)
#define MCD_40G_LN2_BLK_LK_RT_BIT (1<<2)
#define MCD_40G_LN1_BLK_LK_RT_BIT (1<<1)
#define MCD_40G_LN0_BLK_LK_RT_BIT (1<<0)

/*****************************************************************************
Enabling and Checking Interrupts and Real-Time Status 100GBASE-R4 Bit
Definitions Flags 1 and Flags 2
*****************************************************************************/
#define MCD_100G_RXIFO_FULL_BIT   (1<<15)  /* Bit definitions for 100GBASE-R4 Interrupt Enable/Status */
#define MCD_100G_RXFIFO_EMPTY_BIT (1<<14)  /* and real-time Status Registers 1 */
#define MCD_100G_TXFIFO_OF_BIT    (1<<13)
#define MCD_100G_TXFIFO_UF_BIT    (1<<12)
#define MCD_100G_LF_TXD_BIT       (1<<11)
#define MCD_100G_LF_RXD_BIT       (1<<10)
/* NOT USED (1<<9) */
/* NOT USED (1<<8) */
#define MCD_100G_PKTCK_CRCERR_BIT (1<<7)
/* NOT USED (1<<6) */
#define MCD_100G_LINK_BIT         (1<<5)
#define MCD_100G_HI_BER_BIT       (1<<4)
#define MCD_100G_LN3_BLK_LK_BIT   (1<<3)
#define MCD_100G_LN2_BLK_LK_BIT   (1<<2)
#define MCD_100G_LN1_BLK_LK_BIT   (1<<1)
#define MCD_100G_LN0_BLK_LK_BIT   (1<<0)

#define MCD_100G_LN19_BLK_LK_BIT  (1<<15)  /* Bit definitions for 100GBASE-R4 Interrupt Enable/Status */
#define MCD_100G_LN18_BLK_LK_BIT  (1<<14)  /* and real-time Status Registers 2 */
#define MCD_100G_LN17_BLK_LK_BIT  (1<<13)
#define MCD_100G_LN16_BLK_LK_BIT  (1<<12)
#define MCD_100G_LN15_BLK_LK_BIT  (1<<11)
#define MCD_100G_LN14_BLK_LK_BIT  (1<<10)
#define MCD_100G_LN13_BLK_LK_BIT  (1<<9)
#define MCD_100G_LN12_BLK_LK_BIT  (1<<8)
#define MCD_100G_LN11_BLK_LK_BIT  (1<<7)
#define MCD_100G_LN10_BLK_LK_BIT  (1<<6)
#define MCD_100G_LN9_BLK_LK_BIT   (1<<5)
#define MCD_100G_LN8_BLK_LK_BIT   (1<<4)
#define MCD_100G_LN7_BLK_LK_BIT   (1<<3)
#define MCD_100G_LN6_BLK_LK_BIT   (1<<2)
#define MCD_100G_LN5_BLK_LK_BIT   (1<<1)
#define MCD_100G_LN4_BLK_LK_BIT   (1<<0)

/*****************************************************************************
Enabling and Checking Interrupts and Real-Time Status Combined Functions for
40GBR and 100GBR
*****************************************************************************/

/*******************************************************************************
MCD_STATUS mcdGetAPIVersion
(
    OUT MCD_U8 *major,
    OUT MCD_U8 *minor,
    OUT MCD_U8 *patch
);

 Outputs:
    major  - Pointer to MCD_API_MAJOR_VERSION macro
    minor  - Pointer to MCD_API_MINOR_VERSION macro
    patch  - Pointer to MCD_API_PATCH_VERSION macro

 Returns:
    MCD_OK if query was successful.

 Description:
    Get MCD Software API version.

 Side effects:
    None.

 Notes/Warnings:
    None
*******************************************************************************/
MCD_STATUS mcdGetAPIVersion
(
    OUT MCD_U8 *major,
    OUT MCD_U8 *minor,
    OUT MCD_U8 *patch
);

/******************************************************************************
 MCD_STATUS mcdSquelchRxClockSet
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_RX_CLOCK_CTRL_TYPE pinNum
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-7
    pinNum - select the pin to control clock squelch :
                MCD_RCLK_CTRL0,MCD_RCLK_CTRL1 or MCD_RCLK_CTRL2
 Outputs:
    None

 Returns:
    MCD_OK if change was successful, MCD_FAIL if not. Will return
    MCD_FAIL if the parameters are not valid or if link on line side is not UP

 Description:
    The function defines which pin should be set to squelch RX clock
    clears interrupt on all port lanes and enables
    link status change interrupt for the referenced port

 Side effects:
    None.

 Notes/Warnings:
 This function can be called after the port has been initialized and link is UP

******************************************************************************/
MCD_STATUS mcdSquelchRxClockSet
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 laneNum,
    IN MCD_RX_CLOCK_CTRL_TYPE pinNum
);

/******************************************************************************
MCD_STATUS mcdSetInterruptEnableEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_U16 interruptRegisterNum,
    IN  MCD_U16 intrEnableFlags
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-7
    host_or_line - which interface is being read:
        MCD_HOST_SIDE
        MCD_LINE_SIDE
    interruptRegisterNum - number of interrupt related register 0..14
        described in Functional Specification.
    intrEnableFlags - For each flag a 1 enables the interrupt and a
        0 disables the interrupt. Flags described in Functional Specification.

 Outputs:
    None

 Returns:
    MCD_OK if change was successful, MCD_FAIL if not.

 Description:
        This function can be called after the port has been initialized.

 Side effects:
    None.

 Notes/Warnings:
    The bit flags can be OR together to enable multiple interrupts.

******************************************************************************/
MCD_STATUS mcdSetInterruptEnableEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_U16 interruptRegisterNum, /*0..14*/
    IN  MCD_U16 intrEnableFlags
);

/******************************************************************************
MCD_STATUS mcdGetInterruptEnableEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_U16 interruptRegisterNum,
    OUT MCD_U16 *intrEnableFlags
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-7
    host_or_line - which interface is being read:
        MCD_HOST_SIDE
        MCD_LINE_SIDE
    interruptRegisterNum - number of interrupt related register 0..14
        described in Functional Specification.

 Outputs:
        intrEnableFlags - For each flag a 1 enables the interrupt and a
            0 disables the interrupt. Flags described in Functional Specification.

 Returns:
    MCD_OK if change was successful, MCD_FAIL if not.

 Description:
        This function can be called after the port has been initialized.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdGetInterruptEnableEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_U16 interruptRegisterNum, /*0..14*/
    OUT MCD_U16 *intrEnableFlags
);

/******************************************************************************
MCD_STATUS mcdGetInterruptStatusEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_BOOL toClearStatus,
    IN  MCD_U16 interruptRegisterNum,
    OUT MCD_U16 *interruptStatusFlags
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-7
    host_or_line - which interface is being read:
        MCD_HOST_SIDE
        MCD_LINE_SIDE
    toClearStatus - MCD_TRUE - clear interrupt status register after reading,
                    MCD_FALSE - leave interrupt status register as was before reading.
    interruptRegisterNum - number of interrupt related register 0..14
        described in Functional Specification.

 Outputs:
        interruptStatusFlags - For each flag a 1 means interrupt occurred and a
        0 means the interrupt not occurred. Flags described in Functional Specification.

 Returns:
    MCD_OK if change was successful, MCD_FAIL if not.

 Description:
        This function can be called after the port has been initialized.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdGetInterruptStatusEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_BOOL toClearStatus,       /* to clear after read */
    IN  MCD_U16 interruptRegisterNum, /*0..14*/
    OUT MCD_U16 *interruptStatusFlags
);

#define MCD_DOORBELL_EVENT_PORT_0_802_3_AP_E  0x00000001
#define MCD_DOORBELL_EVENT_PORT_1_802_3_AP_E  0x00000002
#define MCD_DOORBELL_EVENT_PORT_2_802_3_AP_E  0x00000004
#define MCD_DOORBELL_EVENT_PORT_3_802_3_AP_E  0x00000008
#define MCD_DOORBELL_EVENT_PORT_4_802_3_AP_E  0x00000010
#define MCD_DOORBELL_EVENT_PORT_5_802_3_AP_E  0x00000020
#define MCD_DOORBELL_EVENT_PORT_6_802_3_AP_E  0x00000040
#define MCD_DOORBELL_EVENT_PORT_7_802_3_AP_E  0x00000080

#define MCD_DOORBELL_EVENT_PORT_0_STATUS_CHANGE_E   0x00010000
#define MCD_DOORBELL_EVENT_PORT_1_STATUS_CHANGE_E   0x00020000
#define MCD_DOORBELL_EVENT_PORT_2_STATUS_CHANGE_E   0x00040000
#define MCD_DOORBELL_EVENT_PORT_3_STATUS_CHANGE_E   0x00080000
#define MCD_DOORBELL_EVENT_PORT_4_STATUS_CHANGE_E   0x00100000
#define MCD_DOORBELL_EVENT_PORT_5_STATUS_CHANGE_E   0x00200000
#define MCD_DOORBELL_EVENT_PORT_6_STATUS_CHANGE_E   0x00400000
#define MCD_DOORBELL_EVENT_PORT_7_STATUS_CHANGE_E   0x00800000

/**
* @internal mcdGetCm3ToHostSignal function
* @endinternal
*
*/
MCD_STATUS mcdGetCm3ToHostSignal
(
    IN   MCD_DEV_PTR pDev,
    OUT  MCD_U32     *signalCodePtr
);


/******************************************************************************
MCD_STATUS mcdGetRealtimeStatusEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_U16 interruptRegisterNum,
    OUT MCD_U16 *intrRtStatusFlags
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-7
    host_or_line - which interface is being read:
        MCD_HOST_SIDE
        MCD_LINE_SIDE
    interruptRegisterNum - number of interrupt related register 0..14
        described in Functional Specification.

 Outputs:
        intrRtStatusFlags - For each flag a 1 means interrupt occurred and a
            0 means the interrupt not occurred. Flags described in Functional Specification.

 Returns:
    MCD_OK if change was successful, MCD_FAIL if not.

 Description:
        This function can be called after the port has been initialized.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MCD_STATUS mcdGetRealtimeStatusEx
(
    IN  MCD_DEV_PTR pDev,
    IN  MCD_U16 mdioPort,
    IN  MCD_U16 host_or_line,
    IN  MCD_BOOL clearOnRead,
    IN  MCD_U16 interruptRegisterNum, /*0..14*/
    IN  MCD_U16 mask,
    OUT MCD_U16 *intrRtStatusFlags
);

/******************************************************************************
 MCD_STATUS mcdSyncEClkConfig
(
    IN MCD_DEV_PTR        pDev,
    IN MCD_U16            mdioPort,
    IN MCD_U32            laneNum,
    IN MCD_RCLK_DIV_VAL   divider,
    IN MCD_BOOL           squelchEnable,
    OUT MCD_RCLK_OUT_PIN  outPin
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdLoadDriver() call
    mdioPort - MDIO port address, 0-7.
    laneNum - SerDes lane number, 0-3.
    divider - selects the division value of the recovered clock.
    squelchEnable - MCD_TRUE - enable Rx squelch,
                    MCD_FALSE - ignore Rx squelch.

 Outputs:
    outPin - configures the pin to output the selected divided recvored
             clock.

 Returns:
    MCD_OK if successful, MCD_FAIL if not. Will return
    MCD_FAIL if the parameters are not valid or if link on line side is not UP

 Description:
    The function defines which pin should output the recovered clock and if squelch
    is enable, call the API mcdSquelchRxClockSet.

 Side effects:
    None.

 Notes/Warnings:
 This function can be called after the port has been initialized and link is UP

******************************************************************************/
MCD_STATUS mcdSyncEClkConfig
(
    IN  MCD_DEV_PTR         pDev,
    IN  MCD_U16             mdioPort,
    IN  MCD_U32             laneNum,
    IN  MCD_RCLK_DIV_VAL    divider,
    IN  MCD_BOOL            squelchEnable,
    IN MCD_RCLK_OUT_PIN    outPin
);

/**
* @internal mcdSetApManualRxParmaeters function
* @endinternal
*
* @brief   Set serdes RX parameters . Those offsets
*         will take place after TRX training.
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on error
*/
MCD_STATUS mcdSetApManualRxParameters
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_U16      laneNum,
    IN  MCD_PORT_AP_SERDES_RX_CONFIG *rxOverrideParamsPtr
);

/**
* @internal mcdSetApManualTxParmaeters function
* @endinternal
*
* @brief   Set serdes Tx parameters . Those values
*         will take place after resolution detected.
* @param[in] pDev                     - physical device number
* @param[in] mdioPort                 - portNum
* @param[in] laneNum                  - number of SERDES lane of port (0-> lane 0,...,3 -> lane 3 etc.)
* @param[in] txOverrideParamsPtr      - (pointer to) parameters data
*
* @retval MCD_OK                   - on success
* @retval MCD_FAIL                 - on fail
*/
MCD_STATUS mcdSetApManualTxParameters
(
    IN  MCD_DEV_PTR  pDev,
    IN  MCD_U16      mdioPort,
    IN  MCD_U16      laneNum,
    IN  MCD_PORT_AP_SERDES_TX_CONFIG *txOverrideParamsPtr
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MCD_API_H */



