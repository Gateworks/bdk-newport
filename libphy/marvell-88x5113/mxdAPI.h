/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains function prototypes for mode selections, interrupts
and real-time controls, configurations and status for the Marvell
X5113 PHY.
********************************************************************/
#ifndef MXD_API_H
#define MXD_API_H
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#define MXD_API_MAJOR_VERSION 11
#define MXD_API_MINOR_VERSION 2
#define MXD_API_BUILD_ID 0

/* This macro is handy for calling a function when you want to test the
   return value and return MXD_FAIL, if the function returned MXD_FAIL,
   otherwise continue */
#ifndef ATTEMPT
#define ATTEMPT(xFuncToTry) {if(xFuncToTry != MXD_OK) \
                            {MXD_DBG_ERROR("ATTEMPT failed at %s:%u\n",__FUNCTION__,__LINE__); \
                            return MXD_FAIL;}}
#endif

/* MXD error status for mode selection */
#define MXD_STATUS_MODE_SUCCESS            0x0  /* Mode selection completed successfully */
#define MXD_STATUS_MODE_GENERAL_ERROR      0x1  /* Mode selection general error */
#define MXD_STATUS_MODE_GROUP_ERROR        0x2  /* Grouped mode selected on individual non-grouped lane mode */
#define MXD_STATUS_MODE_NON_GROUP_ERROR    0x3  /* Individual non-grouped lane mode selected in grouped mode */
#define MXD_STATUS_MODE_HOST_LINE_ERROR    0x4  /* Combination of host and line mode selection invalid    */

/******************************************************************************
MXD_VOID mxdGetAPIVersion
(
    OUT MXD_U8 *major,
    OUT MXD_U8 *minor,
    OUT MXD_U8 *buildID
);

 Inputs:
    None

 Outputs:
    major - major version number
    minor - minor version number
    buildID - build ID for the API

 Returns:
    None
    
 Description:
    Returns the version and build ID numbers of this API. The non-zero build ID 
    is used for test and preview releases.  General release build ID is 0.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MXD_VOID mxdGetAPIVersion
(
    OUT MXD_U8 *major,
    OUT MXD_U8 *minor,
    OUT MXD_U8 *buildID
);

/******************************************************************************
MXD_STATUS mxdSetFixedModeSelection
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16     mdioPort,
     IN MXD_U16     laneOffset,
     IN MXD_FIXED_OP_MODE portMode,
     IN MXD_BOOL    forceReConfig,
     OUT MXD_U16    *result
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort   - MDIO port address 0...31 of mdioPort to be configured
    laneOffset - 0-3; Only for speed 1G - 25G, can set different
                 operational speed mode for each lane
    portMode   - operational mode
    forceReConfig - force re-configuration; override current OP mode if MXD_TRUE
                    Used when switch between GROUPED and NON-GROUPED mode.

 Outputs:
    result -  Returns 0 if mode selection is successful. Otherwise an error result
              will be returned.
              MXD_STATUS_MODE_SUCCESS
              MXD_STATUS_MODE_GENERAL_ERROR
              MXD_STATUS_MODE_GROUP_ERROR - GROUPED mode is selected and current mode is NON-GROUND mode
              MXD_STATUS_MODE_NON_GROUP_ERROR - NON-GROUPED MODE is selected and current mode is GROUPED MODE

 Returns:
    MXD_OK or MXD_FAIL, if action was successful or not

 Description:
    This function configures both the host and line interfaces with the provided pre-defined 
    operational mode from the MXD_FIXED_OP_MODE list. Refer to the MXD_FIXED_OP_MODE structure
    definition for more details. 

    The group and non-group mode definitions are used to differentiate the various operational modes.  
    The group mode is associated with speeds that operate in a single PCS block.  Speeds at 40G or 
    greater operate in a single PCS block.  

    As for the non-group mode, these are speeds between 1G to 25G that operate its PCS block on 
    individual SerDes lane.

    When switching between a group to a non-group mode or vise-versa, a hardware reset will be issued 
    since the SerDes configuration is significantly different in the PCS block.  Any existing operational 
    mode settings in the device structure(pDev) will be reset and will be configured to the requested
    mode.

 Side effects:
    The current link state will be interrupted and reset to the requested operational mode
    
 Notes/Warnings:
    Each line and host interfaces has 4 SerDes lanes.  Each individual SerDes lane can operate at 
    different speed for speeds between 1G to 25G.  For speeds between 40G to 100G, only lane offset 0 
    will be used.

    When switching between a group to a non-group mode or vise-versa, the forceReConfig must be set 
    to MXD_TRUE, otherwise, an error status will be returned

******************************************************************************/
MXD_STATUS mxdSetFixedModeSelection
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16     mdioPort,
     IN MXD_U16     laneOffset,
     IN MXD_FIXED_OP_MODE portMode,
     IN MXD_BOOL    forceReConfig,
     OUT MXD_U16    *result
);

/******************************************************************************
MXD_STATUS mxdSetUserFixedModeSelection
(
     IN MXD_DEV_PTR   pDev,
     IN MXD_U16       mdioPort,
     IN MXD_U16       laneOffset,
     IN MXD_OP_CONFIG hostMode,
     IN MXD_OP_CONFIG lineMode,
     IN MXD_BOOL      forceReConfig,
     OUT MXD_U16      *result
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort   - MDIO port address 0...31 of mdioPort to be configured
    laneOffset - 0-3; Only for speed 1G - 25G, can set different
                 operational speed mode for each lane
    hostMode   - host operational mode(configuration)
    lineMode   - line operational mode(configuration)
    forceReConfig - force re-configuration; override current OP mode if MXD_TRUE
                    Used when switch between GROUPED and NON-GROUPED mode.

 Outputs:
    result -  Returns 0 if mode selection is successful. Otherwise an error result
              will be returned.
              MXD_STATUS_MODE_SUCCESS
              MXD_STATUS_MODE_GENERAL_ERROR
              MXD_STATUS_MODE_GROUP_ERROR - GROUPED mode is selected and current mode is NON-GROUND mode
              MXD_STATUS_MODE_NON_GROUP_ERROR - NON-GROUPED MODE is selected and current mode is GROUPED MODE
              MXD_STATUS_MODE_HOST_LINE_ERROR - Combination of host and line mode selection invalid
 Returns:
    MXD_OK or MXD_FAIL, if action was successful or not

 Description:
    This function provides an option to individually select the operational mode for both host and 
    line interfaces. Unlike the mxdSetFixedModeSelection function that uses the pre-defined 
    MXD_FIXED_OP_MODE input, this function uses the MXD_OP_CONFIG selection to configure each host 
    and line interfaces. Refer to the MXD_OP_CONFIG structure definition for more details. 

    Note that an error status will be returned if the provided mode combination is invalid for the 
    host and line interfaces.

    The group and non-group mode definitions are used to differentiate the various operational modes.  
    The group mode is associated with speeds that operate in a single PCS block.  Speeds at 40G or 
    greater operate in a single PCS block.  

    As for the non-group mode, these are speeds between 1G to 25G that operate its PCS block on 
    individual SerDes lane.

    When switching between a group to a non-group mode or vise-versa, a hardware reset will be issued 
    since the SerDes configuration is significantly different in the PCS block.  Any existing operational 
    mode settings in the device structure(pDev) will be reset and will be configured to the requested
    mode.

 Side effects:
    The current link state will be interrupted and reset to the requested operational mode
    
 Notes/Warnings:
    Each line and host interfaces has 4 SerDes lanes.  Each individual SerDes lane can operate at 
    different speed for speeds between 1G to 25G.  For speeds between 40G to 100G, only lane offset 0 
    will be used.

    When switching between a group to a non-group mode or vise-versa, the forceReConfig must be set 
    to MXD_TRUE, otherwise, an error status will be returned
******************************************************************************/
MXD_STATUS mxdSetUserFixedModeSelection
(
     IN MXD_DEV_PTR   pDev,
     IN MXD_U16       mdioPort,
     IN MXD_U16       laneOffset,
     IN MXD_OP_CONFIG hostMode,
     IN MXD_OP_CONFIG lineMode,
     IN MXD_BOOL      forceReConfig,
     OUT MXD_U16      *result
);

/******************************************************************************
MXD_STATUS mxdGetFixedModeSelection
(
     IN MXD_DEV_PTR        pDev,
     IN MXD_U16            mdioPort,
     OUT MXD_FIXED_OP_MODE opMode[MXD_NUM_LANES],
     OUT MXD_OP_CONFIG     hostMode[MXD_NUM_LANES],
     OUT MXD_OP_CONFIG     lineMode[MXD_NUM_LANES],
     OUT MXD_U16           *groupMode
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort   - MDIO port address 0...31 of mdioPort to be configured

 Outputs:
    opMode     - operational speed mode for each lane
    hostMode   - host operational mode(configuration)
    lineMode   - line operational mode(configuration)
    groupMode  - 1 = GROUPED MODE; 0 = NON-GROUPED MODE.

 Returns:
    MXD_OK or MXD_FAIL, if action was successful or not

 Description:
    Get the operational mode and Host and Line side mode selection for all the lanes.
    For the list of operational mode selections, refer to the MXD_FIXED_OP_MODE structure.
    For the list of host and line mode selections, refer to the MXD_OP_CONFIG structure.

 Side effects:

 Notes/Warnings:

******************************************************************************/
MXD_STATUS mxdGetFixedModeSelection
(
     IN MXD_DEV_PTR        pDev,
     IN MXD_U16            mdioPort,
     OUT MXD_FIXED_OP_MODE opMode[MXD_NUM_LANES],
     OUT MXD_OP_CONFIG     hostMode[MXD_NUM_LANES],
     OUT MXD_OP_CONFIG     lineMode[MXD_NUM_LANES],
     OUT MXD_U16           *groupMode
);

#define MXD_CLEAR_PAUSE     0 /*  clears both pause bits */
#define MXD_SYM_PAUSE       1 /*  for symmetric pause only */
#define MXD_ASYM_PAUSE      2 /*  for asymmetric pause only */
#define MXD_SYM_ASYM_PAUSE  3 /*  for both */
/******************************************************************************
MXD_STATUS mxdSetPauseAdvertisement
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  host_or_line,
     IN MXD_U16  laneOffset,
     IN MXD_U8   pauseType,
     IN MXD_BOOL anRestart
);
                               
 Inputs:
    pDev      - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort  - MDIO port address, 0-31
    host_or_line - which interface is being modified:
                MXD_HOST_SIDE
                MXD_LINE_SIDE
    laneOffset - lane number 0-3
    pauseType - one of the following: 
                MXD_SYM_PAUSE, 
                MXD_ASYM_PAUSE, 
                MXD_SYM_ASYM_PAUSE,
                MXD_CLEAR_PAUSE.
    anRestart - this takes the value of MXD_TRUE or MXD_FALSE.
                This should be set to MXD_FALSE, if this API is called prior to 
                mxdSetFixedModeSelection() or mxdSetUserFixedModeSelection() is called. 
                This should be set to MXD_TRUE, if this API is called after the OP mode 
                is set.

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL, if action was successful or failed

 Description:
    This function sets the asymmetric and symmetric pause bits in the technology 
    ability field in the pDev data structure. This selects what type of pause is 
    to be advertised to the far end MAC during auto-negotiation. If anRestart option 
    is not selected, this function must be called prior to mxdSetFixedModeSelection() 
    or mxdSetUserFixedModeSelection(). After the mode is set and link is up, anRestart
    option must be selected to restart the auto-negotiation to exchange the new pause type.

    Sets entire 2-bit field to the value passed in pauseType.

    To clear both bits, pass in MXD_CLEAR_PAUSE.

 Side effects:
    None

 Notes/Warnings:
******************************************************************************/
MXD_STATUS mxdSetPauseAdvertisement
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  host_or_line,
     IN MXD_U16  laneOffset,
     IN MXD_U8   pauseType,
     IN MXD_BOOL anRestart
);

/******************************************************************************
MXD_STATUS mxdGetPauseAdvertisement
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U8 *pauseType
);
                               
 Inputs:
    pDev      - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort  - MDIO port address, 0-31
    host_or_line - which interface is being modified:
                MXD_HOST_SIDE
                MXD_LINE_SIDE
    laneOffset - lane number 0-3
 Outputs:
    pauseType - one of the following: 
                MXD_SYM_PAUSE, 
                MXD_ASYM_PAUSE, 
                MXD_SYM_ASYM_PAUSE,
                MXD_CLEAR_PAUSE

 Returns:
    MXD_OK or MXD_FAIL, if action was successful or failed

 Description:
    This function gets the asymmetric and symmetric pause bits in the technology 
    ability field in the AN Advertisement register.

    Gets entire 2-bit field to the value passed in pauseType.

 Side effects:
    None

 Notes/Warnings:
    None
******************************************************************************/
MXD_STATUS mxdGetPauseAdvertisement
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U8 *pauseType
);

/******************************************************************************
MXD_STATUS mxdGetLPAdvertisedPause
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U8 *pauseType
);

 Inputs:
    pDev     - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being modified:
                MXD_HOST_SIDE
                MXD_LINE_SIDE
    laneOffset - lane number 0-3

 Outputs:
    pauseType - setting of link partner's pause bits based on bit definitions above in 
                mxdSetPauseAdvertisement().
                one of the following: 
                MXD_SYM_PAUSE, 
                MXD_ASYM_PAUSE, 
                MXD_SYM_ASYM_PAUSE,
                MXD_CLEAR_PAUSE

 Returns:
    MXD_OK or MXD_FAIL, based on whether the query succeeded or failed. 

 Description:
    This function reads 7.0013.11:10(LP Base page ability) and returns the advertised
    pause setting that was received from the link partner.

 Side effects:
    None

 Notes/Warnings:
    The user must make sure auto-negotiation has completed by calling
    mxdSetFixedModeSelection() or mxdSetUserFixedModeSelection() and 
    the link is up prior to calling this function.
******************************************************************************/
MXD_STATUS mxdGetLPAdvertisedPause
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U8 *pauseType
);

/******************************************************************************
MXD_STATUS mxdGetTxRxPauseResolution
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_BOOL *pauseResolved,
     OUT MXD_BOOL *tx_pause_enabled,
     OUT MXD_BOOL *rx_pause_enabled
);

 Inputs:
    pDev         - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort     - MDIO port address, 0-31
    host_or_line - which interface is being modified:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE
    laneOffset - lane number 0-3

 Outputs:
    pauseResolved    - MXD_TRUE/MXD_FALSE based on whether AN speed/duplex
                       is resolved or not
    tx_pause_enabled - MXD_TRUE/MXD_FALSE based on local and LP pause
                       advertisement
    rx_pause_enabled - MXD_TRUE/MXD_FALSE based on local and LP pause
                       advertisement

 Returns:
    MXD_OK or MXD_FAIL, based on whether the query succeeded or failed

 Description:
    This function is returning tx or rx pause enabled according to the priority 
    resolution described in the 802.3 Annex 28B.3. The resolution is based on 
    the local device's advertised pause bits and the link partner's advertised 
    pause bits. It then setting the tx_pause_enabled or rx_pause_enabled to 
    true or false based on the resolution priority as defined by the standard 
    in 802.3 Annex 28B.3.

    If the operation is successful, the pauseResolved is set to MXD_TRUE, 
    otherwise, sets to MXD_FALSE.

 Side effects:
    None

 Notes/Warnings:
    The user must make sure auto-negotiation has completed by calling
    mxdSetFixedModeSelection() or mxdSetUserFixedModeSelection() and  
    the link is up prior to calling this function.
******************************************************************************/
MXD_STATUS mxdGetTxRxPauseResolution
(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_BOOL *pauseResolved,
     OUT MXD_BOOL *tx_pause_enabled,
     OUT MXD_BOOL *rx_pause_enabled
);

/*******************************************************************************
MXD_STATUS mxdGetAutoNegResolution
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *speed_bits
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
         MXD_HOST_SIDE
         MXD_LINE_SIDE
    laneOffset - lane number 0-3.

 Outputs:
    speed_bits - autonegotiation result (could be multiple bits set depending on
                 RS FEC/BASE-R FEC):
    
                 1000B-KX       = 0x0002
                 10GB-KX4       = 0x0004
                 10GB-KR        = 0x0008
                 BASE-R FEC     = 0x0010
                 40GB-KR4       = 0x0020
                 40GB-CR4       = 0x0040
                 RS-FEC         = 0x0080
                 100GB-CR10     = 0x0100
                 100GB-KP4      = 0x0200
                 100GB-KR4      = 0x0400
                 100GB-CR4      = 0x0800
                 25GB-KR-S/CR-S = 0x1000
                 25GB-KR/CR     = 0x2000

 Returns:
    MXD_OK or MXD_FAIL, if query succeeded or failed

 Description:
    Gets AN negotiated speed/abilities after auto-neg is completed.

 Side effects:

 Notes/Warnings:
    AN result will not be available until after AN completes.

*******************************************************************************/
MXD_STATUS mxdGetAutoNegResolution
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *speed_bits
);

/******************************************************************************
MXD_STATUS mxdCL37AutoNeg
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig,
    IN MXD_U16 enabledAutoNeg
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface(s) to apply the CL-37 Auto-Neg
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE
                   MXD_BOTH_SIDE
    laneOffset - lane number from 0 to 3
    opConfig   - operational mode(configuration)
    enabledAutoNeg - MXD_ENABLE or MXD_DISABLE the CL-37 Auto-Neg

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL, if action was successful or not

 Description:
    This API enables or disables the CL-37 Auto-Neg for the 1000BASE-X. Only the 
    MXD_P1X operational mode is supported for the CL-37 Auto-Neg. The Auto-Neg 
    operation will be executed once this API is called. No reset is needed to 
    enable or disable the CL-37 Auto-Neg.

    Refer to the device 3/4, register 0x3n01(n:0/2/4/6 for lane:0/1/2/3) bit 5 
    for the Auto-Neg completion status.

    The line or host interface can either be configured separately or together 
    on the same call. Use MXD_BOTH_SIDE option for both line and host interfaces.

 Side effects:
    None

 Notes/Warnings:
    The CL-37 Auto-Neg bit will be cleared after a software reset.
******************************************************************************/
MXD_STATUS mxdCL37AutoNeg
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig,
    IN MXD_U16 enabledAutoNeg
);

/******************************************************************************
MXD_STATUS mxdAutoNegStart
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig,
    IN MXD_BOOL swReset
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
      MXD_HOST_SIDE
      MXD_LINE_SIDE
    laneOffset - lane number 0-3
    opConfig   - operational mode(configuration)
    swReset    - Issue a software reset to re-start Auto-neg.

 Outputs:
    None

 Returns:
    MXD_OK or MXD_FAIL, if action was successful or not
    
 Description:
    Start or Restarts auto-negotiation. If the link is up, the link will drop 
    and auto-negotiation will start again.

 Side effects:
    None

 Notes/Warnings:

******************************************************************************/
MXD_STATUS mxdAutoNegStart
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_OP_CONFIG opConfig,
    IN MXD_BOOL swReset
);

/*******************************************************************************
MXD_STATUS mxdAutoNegCheckComplete
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U8 *autoNegComplete
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
      MXD_HOST_SIDE
      MXD_LINE_SIDE
    laneOffset - lane number 0-3

 Outputs:
    autoNegComplete - 1: Auto-neg is completed 
                      0: Auto-neg is still on going.

 Returns:
    MXD_OK or MXD_FAIL, if action was successful or not

 Description:
    This function checks if Auto-neg is completed.
    Successful when *autoNegComplete = 1 and return MXD_OK

 Side effects:
    None

 Notes/Warnings:
    This function needs to be polled periodically until the the *autoNegComplete
    is MXD_TRUE. If returns MXD_OK and *autoNegComplete is 0, the auto-neg 
    is not completed.
*******************************************************************************/
MXD_STATUS mxdAutoNegCheckComplete
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U8 *autoNegComplete
);


#define MXD_LINK_UP   1
#define MXD_LINK_DOWN 0
typedef union
{
    struct
    {
        MXD_U16 hostCurrent[MXD_NUM_LANES];
        MXD_U16 hostLatched[MXD_NUM_LANES];
        MXD_U16 lineCurrent[MXD_NUM_LANES];
        MXD_U16 lineLatched[MXD_NUM_LANES];
    } Per_lane_status; /* Link status, lanes not grouped */
                       /* P25, P10, P2_5, P5, or P1, or R25, R1, etc. */
                       /* or lanes are a mixture of per lane PCS */
                       /* and per lane repeater, or all lanes are in repeater mode like R40 or R100 */

                       /* NOTE: Those lanes in repeater mode will not have a valid "Latched" status, */
                       /* only "Current", check the lane mode setting before reading the latched status  */
                       /* For lanes which are not configured the data is not valid */
                       /**/
                       /* Multi-lane repeater modes like R40 and R100 use this structure. */
    struct
    {
        MXD_U16 hostCurrent;
        MXD_U16 hostLatched;
        MXD_U16 lineCurrent;
        MXD_U16 lineLatched;
    } PCS_lanes_grouped_status; /* PCS link status, lanes grouped */
                                /* P40..P100, or P40/P25 gearbox mode */

    /* Repeater mode */
    struct
    {
        MXD_U16 hostCurrent[MXD_NUM_LANES]; /* per lane */
        MXD_U16 lineCurrent[MXD_NUM_LANES]; /* per lane */
    } Repeater_status; /* R1, R2.5, R5, R10L, R25L, R40L, R100L */

} MXD_DETAILED_STATUS_TYPE;

/******************************************************************************
 MXD_STATUS mxdCheckLinkStatus
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16  mdioPort,
     IN MXD_U16  laneOffset,
     IN MXD_BOOL perLaneStatus,
     OUT MXD_U16 *currentStatus,
     OUT MXD_U16 *latchedStatus,
     OUT MXD_DETAILED_STATUS_TYPE *statusDetail
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0-3; in non grouped mode pass the lane number and set perLaneStatus
                      to MXD_TRUE to get combined status (currentStatus, latchedStatus)
                      for a specific lane only, otherwise pass 0 and set perLaneStatus
                      to MXD_FALSE to get a combined status for all lanes
                      (excluding lanes not configured yet).

                      When lanes are grouped (P40, P100, for example), pass
                      0 and perLaneStatus is ignored.

    perLaneStatus - if MXD_FALSE, combined status (currentStatus, latchedStatus)
                    is combined for all lanes, if MXD_TRUE, combined status
                    is only for the lane in "laneOffset".

                    This variable is ignored when grouped (P40 or P100, for example).

 Outputs:
    currentStatus - overall current status of link. May be specific lane, or
        an aggregate of multiple lanes depending on mode and the values
        of laneOffset and perLaneStatus

        When grouped (modes such as P40, P100 or gearbox mode P40/P25, this
        is the combined current status of the PCS on both host and line side).

        When not grouped (individual lanes are in repeater mode or or single lane
        PCS mode, then it depends on laneOffset and perLaneStatus). When perLaneStatus
        is MXD_TRUE, then this is the combined host and line status of the lane passed
        in laneOffset. When perLaneStatus is MXD_FALSE, then this is the combined
        host and lane status of all configured lanes.

        MXD_LINK_UP if one/all lanes are up. MXD_LINK_DOWN, if any component lane
        is down.

        Lanes not yet configured in non-grouped modes will not be
        used in the overall status.

    latchedStatus - latched status since last time mxdCheckLinkStatus()
        was called.

        When grouped (modes such as P40, P100 or gearbox mode P40/P25, this
        is the combined latched status of the PCS on both host and line side).

        When not grouped (individual lanes are single lane PCS mode, then it depends on
        laneOffset and perLaneStatus). When perLaneStatus
        is MXD_TRUE, then this is the combined host and line PCS latched status of the
        lane passed in laneOffset. When perLaneStatus is MXD_FALSE, then this is the combined
        host and lane latched PCS status of all configured lanes.

        Lanes not yet configured in non-grouped modes will not be
        used in the overall status.

        Lanes in repeater mode do not have a latched status available and
        they will be excluded in any combined latched status.

    statusDetail - gives details of status for all components links
        on both host and line side.

        Pass in Per_lane_status structure when lanes are not grouped (mixture of single
        lane repeater modes and/or single lane PCS modes, or repeater modes like R40/R100). Note
        that latched status is invalid for any lane(s) in repeater mode.

        Pass in PCS_lanes_grouped_status structure for grouped PCS modes like P40, P100
        or gearbox mode P40/P25.

        Device structure per-lane details can be used to interpret the results.

 Returns:
    MXD_OK or MXD_FAIL, if action was successful or not.

 Description:
    Depending on the mode of operation of the port and individual lanes, and based on
    the values of laneOffset and perLaneStatus, returns an aggregated status in currentStatus
    and latchedStatus, with more detailed status in the MXD_DETAILED_STATUS_TYPE.

    Lanes in repeater mode have no latched values and latched variables are not valid for those
    lanes and the results should be ignored. They are not included in the aggregated lane results
    for latchedStatus. Also, any unconfigured lanes are not included in the aggregated results
    nor the detailed results.

 Side effects:
    Calling this function will clear any latched bits that are a component of the link status.

 Notes/Warnings:
    None
******************************************************************************/
MXD_STATUS mxdCheckLinkStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  laneOffset,
    IN MXD_BOOL perLaneStatus,
    OUT MXD_U16 *currentStatus,
    OUT MXD_U16 *latchedStatus,
    OUT MXD_DETAILED_STATUS_TYPE *statusDetail
);


/*******************************************************************************
 MXD_STATUS mxdSetRmFifoCntl
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 txThresholdHigh,
     IN MXD_U16 txThresholdLow,
     IN MXD_U16 rxThreshold,
     IN MXD_U16 txSatThreshold
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    txThresholdHigh - TX FIFO high water mark threshold.
    txThresholdLow  - TX FIFO low water mark threshold.
    rxThreshold     - RX FIFO threshold.
    rxSatThreshold  - TX FIFO saturation threshold.

 Outputs:
    None

 Returns:
    MXD_OK if change was successful, MXD_FAIL if not.
    MXD_FAIL if the device is not initialized.

 Description:
    This function sets rate matching FIFO thresholds. The RX_FIFO
    is used in 25 Gbps to 40 Gbps direction

 Side effects:
    None.

 Notes/Warnings:
    All input threshold values should be less than 0x7FF

    Recommended txThresholdHigh value should be 300~400. Each unit is 16 bytes
    size. i.e. 400/16 = 25 units of 16 bytes (default = 0x19)

    The txThresholdLow value should be lower than txThresholdHigh (default = 0x12)

    The rxThreshold - high watermark >= 3648/16 = 228, in units of 16 bytes.
    P_max*(1 - rd_rate/wr_rate)= 9728*(1-25/40) = 3648 bytes (default = 0x0E4)

    rxSatThreshold:
    "saturation" region = P_max*(1 - rd_rate/wr_rate)=9728*(1-25/40) = 3648 bytes,
    allow 40 cycles for clock crossing "sat" threshold should less than
    (16k-3648) / 16 - 40 = 756, in units of 16 bytes (default = 0x2F4)

*******************************************************************************/
MXD_STATUS mxdSetRmFifoCntl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 txThresholdHigh,
    IN MXD_U16 txThresholdLow,
    IN MXD_U16 rxThreshold,
    IN MXD_U16 txSatThreshold
);

/*******************************************************************************
MXD_STATUS mxdGetRmFifoCntl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *txThresholdHigh,
    OUT MXD_U16 *txThresholdLow,
    OUT MXD_U16 *rxThreshold,
    OUT MXD_U16 *txSatThreshold
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    txThresholdHigh - TX FIFO high water mark threshold.
    txThresholdLow  - TX FIFO low water mark threshold.
    rxThreshold     - RX FIFO threshold.
    rxSatThreshold  - TX FIFO saturation threshold.

 Returns:
    MXD_OK if change was successful, MXD_FAIL if not.
    MXD_FAIL if the device is not initialized.

 Description:
    This function reads back the rate matching FIFO threshold settings. The
    RX_FIFO is used in 25 Gbps to 40 Gbps direction

 Side effects:
    None.

 Notes/Warnings:
    See above mxdSetRmFifoCntl notes for details on the threshold values
*******************************************************************************/
MXD_STATUS mxdGetRmFifoCntl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *txThresholdHigh,
    OUT MXD_U16 *txThresholdLow,
    OUT MXD_U16 *rxThreshold,
    OUT MXD_U16 *txSatThreshold
);

/*******************************************************************************
MXD_STATUS mxdGetRmFifoPktDropCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 readClear,
    OUT MXD_U16 *txPktDropCntr
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    readClear - if set, the drop counter is cleared after the read.

 Outputs:
    TxPktDropCntr - TX FIFO packet drop counter

 Returns:
    MXD_OK if change was successful, MXD_FAIL if not.
    MXD_FAIL if the device is not initialized.

 Description:
    This function reads back the TX packet drop counters. Packet Drop Counter
    due to fifo overflow in 40Gb/s to 25Gb/s direction

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdGetRmFifoPktDropCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 readClear,
    OUT MXD_U16 *txPktDropCntr
);

/*****************************************************************************
Rate matching FIFO Interrupts enable Bits
*****************************************************************************/
/* NOT USED (1<<15) */
/* NOT USED (1<<14) */
/* NOT USED (1<<13) */
/* NOT USED (1<<12) */
#define MXD_RX_FIFO_UNDERRUN_BIT     (1<<11)
#define MXD_TX_FIFO_UNDERRUN_BIT     (1<<10)
#define MXD_RX_FIFO_OVERFLOW_BIT     (1<<9)
#define MXD_TX_FIFO_OVERFLOW_BIT     (1<<8)
#define MXD_RX_FIFO_MEM_1BIT_ERR_BIT (1<<6)  /* 2 bits */
#define MXD_TX_FIFO_MEM_1BIT_ERR_BIT (1<<4)  /* 2 bits */
#define MXD_RX_FIFO_MEM_2BIT_ERR_BIT (1<<2)  /* 2 bits */
#define MXD_TX_FIFO_MEM_2BIT_ERR_BIT (1<<0)  /* 2 bits */

/******************************************************************************
 MXD_STATUS mxdSetRmFifoInterruptEnable
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 intrEnableFlags1,
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    intrEnableFlags - 0:Enables the interrupt. Refer to above "Rate matching
                      FIFO Interrupts enable Bits" flags for details.

 Outputs:
    None

 Returns:
    MXD_OK if change was successful, MXD_FAIL if not.
    MXD_FAIL if the device is not initialized.

 Description:
    This function enable/disable Rate Matching FIFO interrupts. Setting "1"
    will disable the corresponding interrupt.

 Side effects:
    None.

 Notes/Warnings:
    This is interrupt mask register, set "0" to enable the interrupt. Setting "1"
    will disable the corresponding interrupt.

******************************************************************************/
MXD_STATUS mxdSetRmFifoInterruptEnable
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 intrEnableFlags
);

/******************************************************************************
 MXD_STATUS mxdGetRmFifoInterruptStatus
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     OUT MXD_U16 *rmFifoIntrStatus
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    rmFifoIntrStatus - Refer to above "Rate matching FIFO Interrupts
                       enable Bits" flags for details.

 Returns:
    MXD_OK if change was successful, MXD_FAIL if not.
    MXD_FAIL if the device is not initialized.

 Description:
    This function reads Rate Matching FIFO interrupts status

 Side effects:
    None.

 Notes/Warnings:
    Refer to above "Rate matching FIFO Interrupts enable Bits" flags for
    details.
******************************************************************************/
MXD_STATUS mxdGetRmFifoInterruptStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *rmFifoIntrStatus
);

#define MXD_RX_MIN_IPG_8BYTES    0x0
#define MXD_RX_MIN_IPG_16BYTES   0x2
#define MXD_TX_IPG_DIC           0x0 /* Deficit Idle Count */
#define MXD_TX_MIN_IPG_8BYTES    0x1
#define MXD_TX_MIN_IPG_12BYTES   0x2
#define MXD_TX_MIN_IPG_16BYTES   0x3

/*******************************************************************************
 MXD_STATUS mxdSetIPGMode
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 rxIPGMode,
     IN MXD_U16 txIPGMode,
     IN MXD_U16 avgDIC
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    rxIPGMode - rx direction (25Gb/s to 40Gb/s) ipg control between packets
    txIPGMode - tx direction (25Gb/s to 40Gb/s) ipg control between packets
    avgDIC - tx direction (40Gb/s to 25Gb/s) average IPG setting in
             DIC mode (in unit of bytes) valid setting is 8 to 15
 Outputs:
    None

 Returns:
    MXD_OK if change was successful, MXD_FAIL if not.
    MXD_FAIL if the device is not initialized.

 Description:
    This function sets Inter-Packet Gap mode of TX and RX

 Side effects:
    None.

 Notes/Warnings:
    rxIPGMode - Rx direction (25Gb/s to 40Gb/s) IPG control between packets
      00/01: minimum 8 bytes IPG
      10: minimum 16 bytes IPG

    txIPGMode - Tx direction (40Gb/s to 25Gb/s) IPG control between packets
      00: DIC
      01: minimum 8 bytes IPG
      10: minimum 12 bytes IPG
      11: minimum 16 bytes IPG

    avgDIC - Tx direction (40Gb/s to 25Gb/s) average IPG setting in DIC mode
             (in unit of bytes) valid setting is 8 to 15 (default=12)
             Note: avgDIC is set if txIPGMode = DIC(0), else value is ignored

*******************************************************************************/
MXD_STATUS mxdSetIPGMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 rxIPGMode,
    IN MXD_U16 txIPGMode,
    IN MXD_U16 avgDIC
);

/*******************************************************************************
MXD_STATUS mxdGetIPGMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *rxIPGMode,
    OUT MXD_U16 *txIPGMode,
    OUT MXD_U16 *avgDIC
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    rxIPGMode - rx direction (25Gb/s to 40Gb/s) IPG control between packets
    txIPGMode - tx direction (25Gb/s to 40Gb/s) IPG control between packets
    avgDIC

 Returns:
    MXD_OK if change was successful, MXD_FAIL if not.
    MXD_FAIL if the device is not initialized.

 Description:
    This function reads back the IPG mode settings

 Side effects:
    None.

 Notes/Warnings:
     Refer to mxdSetIPGMode for details on the rxIPGMode, txIPGMode and avgDIC
     outputs.
*******************************************************************************/
MXD_STATUS mxdGetIPGMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *txIPGMode,
    OUT MXD_U16 *rxIPGMode,
    OUT MXD_U16 *avgDIC
);


/******************************************************************************
 MXD_STATUS mxdGetPcsFaultStatus
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U16 *currentTxFaultStatus,
     OUT MXD_U16 *currentRxFaultStatus,
     OUT MXD_U16 *latchedTxFaultStatus,
     OUT MXD_U16 *latchedRxFaultStatus
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
       MXD_HOST_SIDE
       MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. For 10G and above, set to 0.

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
    MXD_OK if query was successful, MXD_FAIL if not.
    MXD_FAIL if the operating mode is not set properly or
    the device is not initialized for this mode of operation.

 Description:
    This function is to be called in any of the 10G to 100G PCS
    modes to check the Tx/Rx fault bits.

    Based on the current operating mode, it reads the current
    speed Host/Line PCS Status 2 register twice and returns the value
    of the Tx/Rx fault bits. It returns the first read in the
    "latched" version and the second read in the "current" version.

    For 100G Host Side:
        4.8.11 Tx Fault
        4.8.10 Rx Fault

    For 100G Line Side:
        3.8.11 Tx Fault
        3.8.10 Rx Fault

    For 40G/50G Host Side:
        4.1008.11 Tx Fault
        4.1008.10 Rx Fault

    For 40G/50G Line Side:
        3.1008.11 Tx Fault
        3.1008.10 Rx Fault

    For 10G/25G Host Side:
        4.2008.11 Tx Fault
        4.2008.10 Rx Fault

    For 10G/25G Line Side:
        3.2008.11 Tx Fault
        3.2008.10 Rx Fault

 Side effects:
    None.

 Notes/Warnings:
    Clears the latch status of those registers being read.

    Speed must be resolved if using AN and/or port must be configured using
    10G to 100G PCS mode, otherwise an error is returned.

******************************************************************************/
MXD_STATUS mxdGetPcsFaultStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *currentTxFaultStatus,
    OUT MXD_U16 *currentRxFaultStatus,
    OUT MXD_U16 *latchedTxFaultStatus,
    OUT MXD_U16 *latchedRxFaultStatus
);

/*****************************************************************************
Global Interrupts Control Bits
*****************************************************************************/

#define MXD_SPEED_UP_TI_TIMERS_BIT  (1<<15) /* When set, accelerates cunit timer */
/* NOT USED (1<<13) */
/* NOT USED (1<<12) */
/* NOT USED (1<<11) */
/* NOT USED (1<<10) */
/* NOT USED (1<<9)  */
/* NOT USED (1<<8)  */
/* NOT USED (1<<7)  */
/* NOT USED (1<<6)  */
/* NOT USED (1<<5)  */
/* NOT USED (1<<4)  */
/* NOT USED (1<<3)  */

/* Bit setting for MXD_INTR_TRISTATE_BIT and MXD_INTR_POLARITY_BIT
   00 = Active - drive INT low, Inactive - drive INT high
   01 = Active - drive INT high, Inactive - drive INT low
   10 = Active - drive INT low, Inactive - tristate INT
   11 = Active - drive INT high, Inactive - tristate INT
   example: (MXD_INTR_POLARITY_BIT | MXD_INTR_TRISTATE_BIT)
            Active - drive INT high, Inactive - tristate INT
*/
#define MXD_INTR_TRISTATE_BIT       (1<<2)  /* Active - drive INT high, Inactive - drive tristate INT */
#define MXD_INTR_POLARITY_BIT       (1<<1)  /* Active - drive INT high, Inactive - drive INT low  */
#define MXD_FORCE_INTR_PIN_ACT_BIT  (1<<0)  /* 1 = Force Interrupt pin active */

/*******************************************************************************
MXD_STATUS mxdSetGlobalInterruptCntl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 globalIntrCntl
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    globalIntrCntl - controls interrupt as defined above.

 Outputs:
    None

 Returns:
    MXD_OK   if query was successful, MXD_FAIL if not.
    MXD_FAIL if the device is not initialized.

 Description:
    This function sets global interrupt control bits. Refer to the above Global
    Interrupts Control Bits  for setting the various interrupt controls by
    masking the bit combinations.

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdSetGlobalInterruptCntl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 globalIntrCntl
);

/*****************************************************************************
Global Interrupts Status Bits
    0 = No Interrupt
    1 = Active Interrupt
*****************************************************************************/
#define MXD_TEMP_SENSOR_INTR_BIT  (1<<11) /* Temperature higher than pre-programmed threshold Interrupt Status */
#define MXD_GPIO_INTR_BIT         (1<<10) /* GPIO Interrupt Status */
#define MXD_RM_FIFO_INTR_BIT      (1<<9)  /* RM_FIFO Interrupt Status */
#define MXD_ON_CHIP_PROC_INTR_BIT (1<<8)  /* Z80 Chip Interrupt Status */
#define MXD_M0_INTR_BIT           (1<<4)  /* M0 Interrupt Status */
#define MXD_N0_INTR_BIT           (1<<0)  /* N0 Interrupt Status */

/*******************************************************************************
 MXD_STATUS mxdGetGlobalInterruptStatus
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     OUT MXD_U16 *globalIntrStatus
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    globalIntrStatus - value of the global interrupt status register.
    Bit values are defined above.

 Returns:
    MXD_OK   if query was successful, MXD_FAIL if not.
    MXD_FAIL if the device is not initialized.

 Description:
    This function reads the global interrupt status bits. Refer to the above
    Global Interrupts Status Bits to decode the status.

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdGetGlobalInterruptStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    OUT MXD_U16 *globalIntrStatus
);


/*****************************************************************************
Enabling and Checking Interrupts 1000BASE-X and 2.5GBASE-R Bit Definitions
*****************************************************************************/
#define MXD_1G_SPEED_CHD_BIT  (1<<14) /* Speed Changed Interrupt Enable */
#define MXD_1G_DPX_CHD_BIT    (1<<13) /* Duplex Changed Interrupt Enable */
#define MXD_1G_PAGE_RX_BIT    (1<<12) /* Page Received Interrupt Enable */
#define MXD_1G_ANEG_COMP_BIT  (1<<11) /* Auto-Negotiation Completed Interrupt Enable */
#define MXD_1G_LINK_UP_DN_BIT (1<<10) /* Link Up to Link Down Interrupt Enable */
#define MXD_1G_LINK_DN_UP_BIT (1<<9)  /* Link Down to Link Up Interrupt Enable */
#define MXD_1G_SYM_ERR_BIT    (1<<8)  /* Symbol Error Interrupt Enable */
#define MXD_1G_FALSE_CAR_BIT  (1<<7)  /* False Carrier Interrupt Enable */

/*****************************************************************************
Real-Time Status 1000BASE-X and 2.5GBASE-R Bit Definitions
*****************************************************************************/
#define MXD_1G_SPEED2_RT_BIT     (1<<15) /* Bits 15-14: 11=Reserved; 10=1000Mbps */
#define MXD_1G_SPEED1_RT_BIT     (1<<14) /* Bits 15-14: 01=100Mbps; 00=10Mbps */
#define MXD_1G_DPX_CHD_RT_BIT    (1<<13) /* Duplex mode (Full-duplex=1; Half-duplex=0) */
#define MXD_1G_PAGE_RX_RT_BIT    (1<<12) /* Page received=1; Page not received=0  */
#define MXD_1G_ANEG_COMP_RT_BIT  (1<<11) /* When ANeg is not enabled this bit is always 1 */
                                         /* Speed and Duplex (Resolved=1; Not Resolved=0) */
#define MXD_1G_LINK_UP_DN_RT_BIT (1<<10) /* Realtime Link (Up=1; Down=0) */
/* Bit 6-9 NOT USED */                   /* Reserved */
#define MXD_1G_SYNC_STATUS_BIT   (1<<5)  /* sync status */
#define MXD_1G_ENERGY_DETECT_BIT (1<<4)  /* Energy Detect Status (0=Energy Detected)*/
#define MXD_1G_TX_PAUSE_BIT      (1<<3)  /* Transmit Pause Enabled */
#define MXD_1G_RX_PAUSE_BIT      (1<<2)  /* Receive Pause Enabled */


/*****************************************************************************
Enabling and Checking Interrupts 5GBASE-R, 10GBASE-R and 25GBASE-R
Bit Definitions
*****************************************************************************/
#define MXD_25G_LOCAL_FLT_TX_BIT  (1<<11) /* Local Fault Transmitted Interrupt Enable */
#define MXD_25G_LOCAL_FLT_RX_BIT  (1<<10) /* Local Fault Received Interrupt Enable */
/* Bit 7-9 NOT USED */                    /* Reserved */
#define MXD_25G_RX_FIFO_OVER_BIT  (1<<6)  /* Rxfifo Overflow Interrupt Enable */
#define MXD_25G_RX_FIFO_UNDER_BIT (1<<5)  /* Rxfifo Underflow Interrupt Enable */
/* Bit 3-4 NOT USED */                    /* Reserved */
#define MXD_25G_LINK_STATUS_BIT   (1<<2)  /* Link status change Interrupt Enable */
#define MXD_25G_HI_BER_BIT        (1<<1)  /* High BER Change Interrupt Enable */
#define MXD_25G_BLK_LOCK_BIT      (1<<0)  /* Block Lock Change Interrupt Enable */

/*****************************************************************************
Real-Time Status 5GBASE-R, 10GBASE-R and 25GBASE-R Bit Definitions
*****************************************************************************/
#define MXD_25G_LOCAL_FLT_TX_RT_BIT  (1<<11) /* Local Fault Transmitted Status */
#define MXD_25G_LOCAL_FLT_RX_RT_BIT  (1<<10) /* Local Fault Received Status */
/* Bit 7-9 NOT USED */                       /* Reserved */
#define MXD_25G_RX_FIFO_OVER_RT_BIT  (1<<6)  /* Rxfifo Overflow */
#define MXD_25G_RX_FIFO_UNDER_RT_BIT (1<<5)  /* Rxfifo Underflow */
#define MXD_25G_JIT_0_LOCK_BIT       (1<<4)  /* JIT 0 lock achieved if 1 */
#define MXD_25G_JIT_LF_LOCK_BIT      (1<<3)  /* JIT local fault lock achieved */
#define MXD_25G_LINK_STATUS_BIT      (1<<2)  /* 5GBASE-R/10GBASE-R/25GBASE-R Link Status */
#define MXD_25G_HIGH_BER_BIT         (1<<1)  /* High BER Status */
#define MXD_25G_LN3_BLK_LK_BIT       (1<<0)  /* Lane 3 Block Lock Status (lock=1) */


/*****************************************************************************
Enabling and Checking Interrupts and Real-Time Status 40GBASE-R4
and 50GBASE-R4 Bit Definitions
*****************************************************************************/
#define MXD_40G_LN3_AM_LOCK_BIT  (1<<15) /* Lane 3 AM lock Interrupt Enable */
#define MXD_40G_LN2_AM_LOCK_BIT  (1<<14) /* Lane 2 AM lock Interrupt Enable */
#define MXD_40G_LN1_AM_LOCK_BIT  (1<<13) /* Lane 1 AM lock Interrupt Enable */
#define MXD_40G_LN0_AM_LOCK_BIT  (1<<12) /* Lane 0 AM lock Interrupt Enable */
#define MXD_40G_LF_TXD_BIT       (1<<11) /* Local Fault Transmitted Interrupt Enable */
#define MXD_40G_LF_RXD_BIT       (1<<10) /* Local Fault Received Interrupt Enable */
#define MXD_40G_LN_ALIGN_BIT     (1<<9)  /* Lane alignment interrupt enable */
#define MXD_40G_TX_LN_ERRCNT_BIT (1<<8)  /* Tx lane count err interrupt enable */
#define MXD_40G_JIT0_LOCK_BIT    (1<<7)  /* JIT 0 Lock Change Interrupt Enable */
#define MXD_40G_JIT_LF_BIT       (1<<6)  /* JIT Local-Fault Lock Change Interrupt Enable */
#define MXD_40G_LINK_BIT         (1<<5)  /* Link Change Interrupt Enable */
#define MXD_40G_HI_BER_BIT       (1<<4)  /* High BER Change Interrupt Enable */
#define MXD_40G_LN3_BLK_LK_BIT   (1<<3)  /* Lane 3 Block Lock Change Interrupt Enable */
#define MXD_40G_LN2_BLK_LK_BIT   (1<<2)  /* Lane 2 Block Lock Change Interrupt Enable */
#define MXD_40G_LN1_BLK_LK_BIT   (1<<1)  /* Lane 1 Block Lock Change Interrupt Enable */
#define MXD_40G_LN0_BLK_LK_BIT   (1<<0)  /* Lane 0 Block Lock Change Interrupt Enable */


/*****************************************************************************
Enabling and Checking Interrupts and Real-Time Status 100GBASE-R4 Bit
Definitions Flags 1 and Flags 2
*****************************************************************************/
#define MXD_100G_RXIFO_EMPTY_BIT  (1<<15) /* 100G PCS Rx FIFO Empty Interrupt Enable */
#define MXD_100G_RXFIFO_FULL_BIT  (1<<14) /* 100G PCS Rx FIFO Full Interrupt Enable */
#define MXD_100G_TXFIFO_OF_BIT    (1<<13) /* 100G PCS Tx PPM FIFO Overflow Interrupt Enable */
#define MXD_100G_TXFIFO_UF_BIT    (1<<12) /* 100G PCS Tx PPM FIFO Underflow Interrupt Enable */
#define MXD_100G_LF_TXD_BIT       (1<<11) /* Rising Edge of the Local Fault Condition on Tx Path Interrupt Enable */
#define MXD_100G_LF_RXD_BIT       (1<<10) /* Rising Edge of the Local Fault Condition on Rx Path Interrupt Enable */
/* NOT USED (1<<9) */                     /* Reserved */
/* NOT USED (1<<8) */                     /* Reserved */
#define MXD_100G_PKTCK_CRCERR_BIT (1<<7)  /* 100G Packet Check CRC Error interrupt Enable */
/* NOT USED (1<<6) */                     /* Reserved */
#define MXD_100G_LINK_BIT         (1<<5)  /* Link Change Interrupt Enable */
#define MXD_100G_HI_BER_BIT       (1<<4)  /* High BER Change Interrupt Enable */
#define MXD_100G_LN3_BLK_LK_BIT   (1<<3)  /* Lane 3 Block Lock Change Interrupt Enable */
#define MXD_100G_LN2_BLK_LK_BIT   (1<<2)  /* Lane 2 Block Lock Change Interrupt Enable */
#define MXD_100G_LN1_BLK_LK_BIT   (1<<1)  /* Lane 1 Block Lock Change Interrupt Enable */
#define MXD_100G_LN0_BLK_LK_BIT   (1<<0)  /* Lane 0 Block Lock Change Interrupt Enable */

/* Flags 2 */
#define MXD_100G_LN19_BLK_LK_BIT  (1<<15) /* Lane 19 Block Lock Change Interrupt Enable */
#define MXD_100G_LN18_BLK_LK_BIT  (1<<14) /* Lane 18 Block Lock Change Interrupt Enable */
#define MXD_100G_LN17_BLK_LK_BIT  (1<<13) /* Lane 17 Block Lock Change Interrupt Enable */
#define MXD_100G_LN16_BLK_LK_BIT  (1<<12) /* Lane 16 Block Lock Change Interrupt Enable */
#define MXD_100G_LN15_BLK_LK_BIT  (1<<11) /* Lane 15 Block Lock Change Interrupt Enable */
#define MXD_100G_LN14_BLK_LK_BIT  (1<<10) /* Lane 14 Block Lock Change Interrupt Enable */
#define MXD_100G_LN13_BLK_LK_BIT  (1<<9)  /* Lane 13 Block Lock Change Interrupt Enable */
#define MXD_100G_LN12_BLK_LK_BIT  (1<<8)  /* Lane 12 Block Lock Change Interrupt Enable */
#define MXD_100G_LN11_BLK_LK_BIT  (1<<7)  /* Lane 11 Block Lock Change Interrupt Enable */
#define MXD_100G_LN10_BLK_LK_BIT  (1<<6)  /* Lane 10 Block Lock Change Interrupt Enable */
#define MXD_100G_LN9_BLK_LK_BIT   (1<<5)  /* Lane 9 Block Lock Change Interrupt Enable */
#define MXD_100G_LN8_BLK_LK_BIT   (1<<4)  /* Lane 8 Block Lock Change Interrupt Enable */
#define MXD_100G_LN7_BLK_LK_BIT   (1<<3)  /* Lane 7 Block Lock Change Interrupt Enable */
#define MXD_100G_LN6_BLK_LK_BIT   (1<<2)  /* Lane 6 Block Lock Change Interrupt Enable */
#define MXD_100G_LN5_BLK_LK_BIT   (1<<1)  /* Lane 5 Block Lock Change Interrupt Enable */
#define MXD_100G_LN4_BLK_LK_BIT   (1<<0)  /* Lane 4 Block Lock Change Interrupt Enable */


/*****************************************************************************
Enabling and Checking Interrupts and Real-Time Status Combined Functions for
various speeds
*****************************************************************************/


/******************************************************************************
 MXD_STATUS mxdSetInterruptEnable
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     IN MXD_U16 intrEnableFlags1,
     IN MXD_U16 intrEnableFlags2  (only valid for 100GBR)
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
       MXD_HOST_SIDE
       MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.
    intrEnableFlags1 - For each flag a 1 enables the interrupt and a
        0 disables the interrupt. Flags are defined above.
        Flag values depend on operating mode
    intrEnableFlags2 - For each flag a 1 enables the interrupt and a
        0 disables the interrupt. Flags are defined above.
        Flag values depend on operating mode (this flag is only for
        100G mode, ignored for other modes)

 Outputs:
    None

 Returns:
    MXD_OK if change was successful, MXD_FAIL if not.
    MXD_FAIL if the operating mode is not set properly or
    the device is not initialized.

 Description:
    This function can be called after the port has been initialized for
    any of the 1GR to 100GR modes of operation to enable interrupts.

    Note that the second flag is only for 100G mode. It's ignored
    if the port is in other mode.

 Side effects:
    None.

 Notes/Warnings:
    The bit flags can be OR together to enable multiple interrupts.
    For example:
        (MXD_100G_RXIFO_FULL_BIT | MXD_100G_RXFIFO_EMPTY_BIT) for
    intrEnableFlags1 to enable these two interrupts on 100GR mode.

******************************************************************************/
MXD_STATUS mxdSetInterruptEnable
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 intrEnableFlags1,
    IN MXD_U16 intrEnableFlags2 /* only valid for 100GBR */
);

/******************************************************************************
 MXD_STATUS mxdGetInterruptEnable
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U16 *intrEnableFlags1,
     OUT MXD_U16 *intrEnableFlags2  only valid for 100GBR
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
       MXD_HOST_SIDE
       MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.

 Outputs:
    intrEnableFlags1 - For each flag a 1 indicates the interrupt is
        enabled and a 0 indicates the interrupt is disabled.
        Flags are defined above.
        Flag values depend on operating mode
    intrEnableFlags2 - For each flag a 1 indicates the interrupt is
        enabled and a 0 indicates the interrupt is disabled.
        Flags are defined above.
        Flag values depend on operating mode (this flag is only for
        100G mode, ignored for other modes)

 Returns:
    MXD_OK if query was successful, MXD_FAIL if not.
    MXD_FAIL if the operating mode is not set properly or
    the device is not initialized.

 Description:
    This function can be called after the port has been initialized for
    any of the 1GR to 100GR modes of operation to read what
    interrupts are enabled.

    Note that the second flag is only for 100G mode. It's invalid
    if the port is in other mode.

 Side effects:
    None.

 Notes/Warnings:
    None

******************************************************************************/
MXD_STATUS mxdGetInterruptEnable
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *intrEnableFlags1,
    OUT MXD_U16 *intrEnableFlags2 /* only valid for 100GBR */
);

/******************************************************************************
 MXD_STATUS mxdGetInterruptStatus
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U16 *latchedStatusFlags1,
     OUT MXD_U16 *currentStatusFlags1,
     OUT MXD_U16 *latchedStatusFlags2,  only valid for 100GBR
     OUT MXD_U16 *currentStatusFlags2,  only valid for 100GBR
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
       MXD_HOST_SIDE
       MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.

 Outputs:
    latchedStatusFlags1 - value of the first read of the
        interrupt status register. Bit values are defined above.
    currentStatusFlags1 - value of the second read of the
        interrupt status register. Bit values are defined above.
    latchedStatusFlags2 - value of the first read of the
        interrupt status register 2. Only valid in 100GR mode.
        Bit values are defined above.
    currentStatusFlags2 - value of the second read of the
        interrupt status register 2.
        Bit values are defined above. Only valid in 100GR mode.


 Returns:
    MXD_OK if query was successful, MXD_FAIL if not.
    MXD_FAIL if the operating mode is not set properly or
    the device is not initialized.

 Description:
    This function can be called after the port has been initialized for
    any of the 1GR to 100GR modes of operation to read what
    interrupts have occurred. The first read value is passed in the
    latched parameter, while the second read value is passed in the
    current read parameter.

    Note that the second flag (#2) is only for 100G mode. It's invalid
    if the port is in other mode.

 Side effects:
    None.

 Notes/Warnings:
    If the interrupt has gone away, calling this function will clear the
    latched bit.

******************************************************************************/
MXD_STATUS mxdGetInterruptStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *latchedStatusFlags1,
    OUT MXD_U16 *currentStatusFlags1,
    OUT MXD_U16 *latchedStatusFlags2, /* only valid for 100GBR */
    OUT MXD_U16 *currentStatusFlags2 /* only valid for 100GBR */
);

/******************************************************************************
 MXD_STATUS mxdGetRealtimeStatus
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort,
     IN MXD_U16 host_or_line,
     IN MXD_U16 laneOffset,
     OUT MXD_U16 *rtStatusFlags1,
     OUT MXD_U16 *rtStatusFlags2  only valid for 100GBR
 );

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdLoadDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
       MXD_HOST_SIDE
       MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3. For 40G and above, set to 0.

 Outputs:
    rtStatusFlags1 - value of reading the real-time status register
        Bit values are defined above.
    rtStatusFlags2 - value of reading the real-time status register
        #2. Bit values are defined above. Only valid in 100GR mode.


 Returns:
    MXD_OK if query was successful, MXD_FAIL if not.
    MXD_FAIL if the operating mode is not set properly or
    the device is not initialized.

 Description:
    This function can be called after the port has been initialized for
    any of the 1GR to 100GR modes of operation to read what
    the current status is.

    Note that the second flag (#2) is only for 100G mode. It's invalid
    if the port is in other mode.

 Side effects:
    None.

 Notes/Warnings:
    None.

******************************************************************************/
MXD_STATUS mxdGetRealtimeStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    OUT MXD_U16 *rtStatusFlags1,
    OUT MXD_U16 *rtStatusFlags2 /* only valid for 100GBR */
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif


#endif /* defined MXD_API_H */

