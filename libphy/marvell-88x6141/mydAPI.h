/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains function prototypes for mode selections, interrupts
and real-time controls, configurations and status for the 
Marvell X7120/X6181/X6141 PHY.
********************************************************************/
#ifndef MYD_API_H
#define MYD_API_H
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#define MYD_API_MAJOR_VERSION 1
#define MYD_API_MINOR_VERSION 2
#define MYD_API_BUILD_ID 0

/* These macros are handy for calling a function when you want to test the
   return value and return MYD_FAIL, if the function returned MYD_FAIL,
   otherwise continue */
#ifndef ATTEMPT
#define ATTEMPT(xFuncToTry) {if(xFuncToTry != MYD_OK)                                                 \
                             {MYD_DBG_ERROR("ATTEMPT failed at %s: line:%u\n",__FUNCTION__,__LINE__); \
                             return MYD_FAIL;}}
#endif

#ifndef MYD_CHECK_DEV
#define MYD_CHECK_DEV(XpDev, XmdioPort, XlaneOffset)                                                          \
        {                                                                                                     \
            if (!XpDev)                                                                                       \
            {   MYD_DBG_ERROR("MYD_CHECK_DEV: pDev is NULL; failed at %s: line:%u\n", __FUNCTION__,__LINE__); \
                return MYD_FAIL;}                                                                             \
                                                                                                              \
            if (!XpDev->devEnabled)                                                                           \
            {   MYD_DBG_ERROR("MYD_CHECK_DEV: pDev->devEnabled is not initialized; failed at %s: line:%u\n",  \
                                __FUNCTION__,__LINE__);                                                       \
                return MYD_FAIL;}                                                                             \
                                                                                                              \
            if ((XmdioPort < XpDev->mdioPort) || (XmdioPort >= (XpDev->mdioPort + XpDev->portCount)))         \
            {   MYD_DBG_ERROR("MYD_CHECK_DEV: invalid mdioPort number:%u; failed at %s: line:%u\n",           \
                              XmdioPort, __FUNCTION__,__LINE__);                                              \
                return MYD_FAIL;}                                                                             \
                                                                                                              \
            if (XlaneOffset >= MYD_NUM_LANES)                                                                 \
            {   MYD_DBG_ERROR("MYD_CHECK_DEV: incorrect lane offset: %u at %s: line:%u\n",                    \
                              XlaneOffset, __FUNCTION__,__LINE__);                                            \
               return MYD_FAIL;}                                                                              \
        }
#endif

#ifndef MYD_CHECK_DEV_SIDE
#define MYD_CHECK_DEV_SIDE(XpDev, XmdioPort, XlaneOffset, XhostLineSel)                                 \
        {                                                                                               \
            MYD_CHECK_DEV(XpDev, XmdioPort, XlaneOffset);                                               \
                                                                                                        \
            if (!(XhostLineSel == MYD_HOST_SIDE || XhostLineSel == MYD_LINE_SIDE))                      \
            {   MYD_DBG_ERROR("MYD_CHECK_DEV_SIDE: incorrect host/side selection: %u at %s: line:%u\n", \
                              XhostLineSel, __FUNCTION__,__LINE__);                                     \
               return MYD_FAIL;}                                                                        \
        }
#endif

/* MYD error status for mode selection */
#define MYD_STATUS_MODE_SUCCESS            0x0  /* Mode selection completed successfully */
#define MYD_STATUS_MODE_GENERAL_ERROR      0x1  /* Mode selection general error */
#define MYD_STATUS_MODE_GROUP_ERROR        0x2  /* Grouped mode selected on individual non-grouped lane mode */
#define MYD_STATUS_MODE_NON_GROUP_ERROR    0x3  /* Individual non-grouped lane mode selected in grouped mode */
#define MYD_STATUS_MODE_HOST_LINE_ERROR    0x4  /* Combination of host and line mode selection invalid    */

/******************************************************************************
MYD_VOID mydGetAPIVersion
(
    OUT MYD_U8 *major,
    OUT MYD_U8 *minor,
    OUT MYD_U8 *buildID
)

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
MYD_VOID mydGetAPIVersion
(
    OUT MYD_U8 *major,
    OUT MYD_U8 *minor,
    OUT MYD_U8 *buildID
);


/* mydSetModeSelection Mode Option List
     Multiple mode option flags can be combined. Some option like the 
     MYD_MODE_ICAL_EFFORT_0 or MYD_MODE_ICAL_EFFORT_1, only one should
     be selected. If both the ICAL options are not selected, the API 
     will use the default based on the selected mode
     
     usage:
     status = mydSetModeSelection(pDev, mdioPort, laneOffset, hostMode, lineMode, 
                                  (MYD_MODE_FORCE_RECONFIG|MYD_MODE_ICAL_EFFORT_0), &result); 
*/

/*  Mode Option List */
#define MYD_MODE_FORCE_RECONFIG (1<<0) /* force override current operational mode;
                                          this option needs to be set when switching 
                                          between modes of different number of lane used.  
                                          e.g. changing from a 2-lane P100UP to a 1-lane 
                                          P50UP on the same port and laneOffset */

                                         /* iCal Effort 0.5 default if iCal option bit 1:2 not set */
#define MYD_MODE_ICAL_EFFORT_0    (1<<1) /* shorten linkup time for some modes */
#define MYD_MODE_ICAL_EFFORT_1    (1<<2) /* improves performance for some modes */
#define MYD_MODE_ICAL_EFFORT_0_FV (1<<3) /* iCal Effort 0 Fixed Vernier */
#define MYD_MODE_SHORT_CHANNEL    (1<<4) /* Long channel (default) */
#define MYD_MODE_TEMPERATURE_RAMP (1<<5) /* No temperature ramp (default) PAM4 signal only*/

/******************************************************************************
MYD_STATUS mydSetModeSelection
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16     mdioPort,
    IN MYD_U16     laneOffset,
    IN MYD_OP_MODE hostMode,
    IN MYD_OP_MODE lineMode,
    IN MYD_U32     modeOption,
    OUT MYD_U16    *result
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort   - MDIO port address 0...31 of mdioPort to be configured
    laneOffset - lane 0 to lane 3
    hostMode   - host operational mode(configuration)
    lineMode   - line operational mode(configuration)
    modeOption - optional; one or more mode option from Mode Option List  

 Outputs:
    result -  Returns 0 if mode selection is successful. Otherwise an error result
              will be returned.
              MYD_STATUS_MODE_SUCCESS
              MYD_STATUS_MODE_GENERAL_ERROR
              MYD_STATUS_MODE_GROUP_ERROR - GROUPED mode is selected and current  
                                            mode is NON-GROUND mode
              MYD_STATUS_MODE_NON_GROUP_ERROR - NON-GROUPED MODE is selected and  
                                                current mode is GROUPED MODE
              MYD_STATUS_MODE_HOST_LINE_ERROR - Combination of host and line mode  
                                                selection invalid
 Returns:
    MYD_OK or MYD_FAIL, if action was successful or not

 Description:
    This function provides an option to select the operational mode for both
    host and line interfaces. This function uses the MYD_OP_MODE selection 
    to configure each host and line interfaces. Refer to the MYD_OP_MODE structure 
    definition for more details on the available modes and descriptions. 

    Note that an error status will be returned if the provided mode combination 
    is invalid for the host and line interfaces.

    The group and non-group mode definitions are used to differentiate the various 
    operational modes. The group mode is associated with speeds that operate in a 
    single PCS block.  

    When switching between a group to a non-group mode or vise-versa, a hardware 
    reset will be issued since the SerDes configuration is significantly different 
    in the PCS block. Any existing operational mode settings in the device 
    structure(pDev) will be reset and will be configured to the requested mode.

 Side effects:
    The current link state will be interrupted and reset to the requested operational 
    mode
    
 Notes/Warnings:
    Each line and host interfaces has 4 SerDes lanes.  Each individual SerDes lane can 
    operate at different speed for speeds between 1G to 50G.  
    
    Refer to the datasheet for the number of lane used in the mode. For 100G, only 
    lane offset 0 and 2 should be used when calling this API. For 200G, only 
    lane offset 0 should be used.

    When switching between a group to a non-group mode or vise-versa within a port, the 
    MYD_MODE_FORCE_RECONFIG must be set, otherwise, an error status will be returned.

    The MYD_MODE_FORCE_RECONFIG needs to be set when switching between modes of different 
    number of lane used.  e.g. changing from a 2-lane P100UP to a 1-lane P50UP on the same 
    port and laneOffset, the MYD_MODE_FORCE_RECONFIG must be set.
    
    The MYD_MODE_ICAL_EFFORT_0 option allows to speed up the linkup time on some
    operational modes. This option may change in future releases.

******************************************************************************/
MYD_STATUS mydSetModeSelection
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16     mdioPort,
    IN MYD_U16     laneOffset,
    IN MYD_OP_MODE hostMode,
    IN MYD_OP_MODE lineMode,
    IN MYD_U32     modeOption,
    OUT MYD_U16    *result
);

/******************************************************************************
MYD_STATUS mydGetOpMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,   
    OUT MYD_OP_MODE *opMode
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
      MYD_HOST_SIDE
      MYD_LINE_SIDE
    laneOffset - lane number 0-3

 Outputs:
    opMode - the operating mode of this lane returned from the MYD_DEV
             structure
 Returns:
    MYD_OK or MYD_FAIL, if action was successful or not

 Description:
    Reads the operating mode from the device structure. A convenience
    function for accessing the mode from the device structure.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MYD_STATUS mydGetOpMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,   
    OUT MYD_OP_MODE *opMode
);


/******************************************************************************
MYD_STATUS mydAutoNegControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_OP_MODE opConfig,    
    IN MYD_U16 enableAutoNeg,
    IN MYD_BOOL swReset
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
      MYD_HOST_SIDE
      MYD_LINE_SIDE
    laneOffset - lane number 0-3
    enableAutoNeg - MYD_ENABLE or MYD_DISABLE the Auto-neg
    swReset    - Issue a software reset to re-start Auto-neg.

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL, if action was successful or not

 Description:
    Enables or disables AN and restarts it. If it is enabled AN will
    restart if swReset is MYD_TRUE. If it is disabled, the link will drop 
    and stay down if swReset is MYD_TRUE.

 Side effects:
    None

 Notes/Warnings:
    Any change will not take effect until a software reset is issued.

******************************************************************************/
MYD_STATUS mydAutoNegControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,   
    IN MYD_U16 enableAutoNeg,    
    IN MYD_BOOL swReset
);

/*******************************************************************************
MYD_STATUS mydAutoNegCheckComplete
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_BOOL *autoNegComplete
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being checked:
      MYD_HOST_SIDE
      MYD_LINE_SIDE
    laneOffset - lane number 0-3

 Outputs:
    autoNegComplete - MYD_TRUE: Auto-neg is completed 
                      MYD_FALSE: Auto-neg is still on going.

 Returns:
    MYD_OK or MYD_FAIL, if action was successful or not

 Description:
    This function checks if Auto-neg is completed by checking the AN complete
    bit in the AN status register for host or line side.

 Side effects:
    None

 Notes/Warnings:
    This function needs to be polled periodically until the *autoNegComplete
    is MYD_TRUE to check for auto-neg done.
*******************************************************************************/
MYD_STATUS mydAutoNegCheckComplete
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_BOOL *autoNegComplete
);

/*******************************************************************************
MYD_STATUS mydGetAutoNegResolution
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *speed_bits
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being read:
         MYD_HOST_SIDE
         MYD_LINE_SIDE
    laneOffset - lane number 0-3

 Outputs:
    speed_bits - auto-negotiation result

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
                 2.5GB-KX       = 0x4000
                 5GB-KR         = 0x8000

 Returns:
    MYD_OK or MYD_FAIL, if query succeeded or failed

 Description:
    Gets AN negotiated speed and ability.

 Side effects:

 Notes/Warnings:
    AN result will not be available until after AN completes.

*******************************************************************************/
MYD_STATUS mydGetAutoNegResolution
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *speed_bits
);


/******************************************************************************
MYD_STATUS mydCL37AutoNegControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 enabledAutoNeg
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - interface(s) to apply the CL-37 Auto-Neg
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE
                   MYD_BOTH_SIDE
    laneOffset - lane number from 0 to 3
    enableAutoNeg - MYD_ENABLE or MYD_DISABLE the CL-37 Auto-Neg

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL, if action was successful or not

 Description:
    This API enables or disables the CL-37 Auto-Neg for the 1000BASE-X. Only the 
    MYD_P1X operational mode is supported for the CL-37 Auto-Neg. The Auto-Neg 
    operation will be executed once this API is called. No reset is needed to 
    enable or disable the CL-37 Auto-Neg, it restarts automatically when
    changed from enable to disable.

    Refer to the device 3/4, register 0x3n01(n:0/2/4/6 for lane:0/1/2/3) bit 5 
    for the Auto-Neg completion status.

    The line or host interface can either be configured separately or together 
    on the same call. Use MYD_BOTH_SIDE option for both line and host interfaces.

 Side effects:
    None

 Notes/Warnings:
    The CL-37 Auto-Neg bit will be cleared after a software reset and must
    be re-enabled.

    Clause 37 auto-neg only applies to MYD_P1X mode. If this function is
    called in any other mode an error will be returned.
******************************************************************************/
MYD_STATUS mydCL37AutoNegControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 enableAutoNeg
);

#define MYD_CLEAR_PAUSE     0 /*  clears both pause bits */
#define MYD_SYM_PAUSE       1 /*  for symmetric pause only */
#define MYD_ASYM_PAUSE      2 /*  for asymmetric pause only */
#define MYD_SYM_ASYM_PAUSE  3 /*  for both */
/******************************************************************************
MYD_STATUS mydSetPauseAdvertisement
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,
     IN MYD_U16  laneOffset,
     IN MYD_U16   pauseType,
     IN MYD_BOOL swReset
);
                               
 Inputs:
    pDev      - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort  - MDIO port address, 0-31
    host_or_line - which interface is being modified:
                MYD_HOST_SIDE
                MYD_LINE_SIDE
    laneOffset - lane number 0-3
    pauseType - one of the following: 
                MYD_SYM_PAUSE, 
                MYD_ASYM_PAUSE, 
                MYD_SYM_ASYM_PAUSE,
                MYD_CLEAR_PAUSE.
    swReset - MYD_TRUE to issue a lane software reset after the change,
                MYD_FALSE to wait until later to issue the software reset

 Outputs:
    None

 Returns:
    MYD_OK or MYD_FAIL, if action was successful or failed

 Description:
    This function sets the asymmetric and symmetric pause bits in the technology 
    ability field in the auto-neg advertisement register. This selects what type of 
    pause is to be advertised to the far end during auto-negotiation. 

    Sets entire 2-bit field to the value passed in pauseType.

    To clear both bits, pass in MYD_CLEAR_PAUSE.

 Side effects:
    None

 Notes/Warnings:
    The change will not take effect until a soft reset or auto-neg restart
    is issued.
******************************************************************************/
MYD_STATUS mydSetPauseAdvertisement
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  host_or_line,
     IN MYD_U16  laneOffset,
     IN MYD_U16  pauseType,
     IN MYD_BOOL swReset
);

/******************************************************************************
MYD_STATUS mydGetPauseAdvertisement
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_U16 *pauseType
);
                               
 Inputs:
    pDev      - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort  - MDIO port address, 0-31
    host_or_line - which interface is being modified:
                MYD_HOST_SIDE
                MYD_LINE_SIDE
    laneOffset - lane number 0-3
    
 Outputs:
    pauseType - one of the following: 
                MYD_SYM_PAUSE, 
                MYD_ASYM_PAUSE, 
                MYD_SYM_ASYM_PAUSE,
                MYD_CLEAR_PAUSE

 Returns:
    MYD_OK or MYD_FAIL, if action was successful or failed

 Description:
    This function gets the asymmetric and symmetric pause bits in the technology 
    ability field in the AN Advertisement register.

    Gets entire 2-bit field to the value passed in pauseType.

 Side effects:
    None

 Notes/Warnings:
    None
******************************************************************************/
MYD_STATUS mydGetPauseAdvertisement
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_U16 *pauseType
);

/******************************************************************************
MYD_STATUS mydGetLPAdvertisedPause
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_U16 *pauseType
);

 Inputs:
    pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being modified:
                MYD_HOST_SIDE
                MYD_LINE_SIDE
    laneOffset - lane number 0-3

 Outputs:
    pauseType - setting of link partner's pause bits based on bit definitions  
                above in mydSetPauseAdvertisement().
                one of the following: 
                MYD_SYM_PAUSE, 
                MYD_ASYM_PAUSE, 
                MYD_SYM_ASYM_PAUSE,
                MYD_CLEAR_PAUSE

 Returns:
    MYD_OK or MYD_FAIL, based on whether the query succeeded or failed. 

 Description:
    This function reads the auto-neg LP base page ability register and returns the 
    advertised pause setting that was received from the link partner.

 Side effects:
    None

 Notes/Warnings:
    The user must make sure auto-negotiation has completed by calling
    mydSetModeSelection() and the link is up prior to calling this function.
******************************************************************************/
MYD_STATUS mydGetLPAdvertisedPause
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_U16 *pauseType
);

/******************************************************************************
MYD_STATUS mydGetTxRxPauseResolution
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_BOOL *pauseResolved,
     OUT MYD_BOOL *tx_pause_enabled,
     OUT MYD_BOOL *rx_pause_enabled
);

 Inputs:
    pDev         - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort     - MDIO port address, 0-31
    host_or_line - which interface is being modified:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE
    laneOffset - lane number 0-3

 Outputs:
    pauseResolved    - MYD_TRUE/MYD_FALSE based on whether AN speed/duplex
                       is resolved or not
    tx_pause_enabled - MYD_TRUE/MYD_FALSE based on local and LP pause
                       advertisement
    rx_pause_enabled - MYD_TRUE/MYD_FALSE based on local and LP pause
                       advertisement

 Returns:
    MYD_OK or MYD_FAIL, based on whether the query succeeded or failed

 Description:
    This function is returning tx or rx pause enabled according to the priority 
    resolution described in the 802.3 Annex 28B.3. The resolution is based on 
    the local device's advertised pause bits and the link partner's advertised 
    pause bits. It then setting the tx_pause_enabled or rx_pause_enabled to 
    true or false based on the resolution priority as defined by the standard 
    in 802.3 Annex 28B.3.

    If the operation is successful, the pauseResolved is set to MYD_TRUE, 
    otherwise, sets to MYD_FALSE.

 Side effects:
    None

 Notes/Warnings:
    The user must make sure auto-negotiation has completed before calling this
    function (link is up or auto-neg is complete).
******************************************************************************/
MYD_STATUS mydGetTxRxPauseResolution
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_BOOL *pauseResolved,
     OUT MYD_BOOL *tx_pause_enabled,
     OUT MYD_BOOL *rx_pause_enabled
);


#define MYD_LINK_DOWN 0
#define MYD_LINK_UP   1

/* PCS mode link status */
typedef struct _MYD_PCS_LINK_STATUS
{
    MYD_U16 hostCurrent;
    MYD_U16 hostLatched;
    MYD_U16 lineCurrent;
    MYD_U16 lineLatched;
} MYD_PCS_LINK_STATUS;  

/* Repeater mode link status */
typedef struct _MYD_REPEATER_LINK_STATUS
{
    MYD_U16 hostCurrent[MYD_NUM_LANES*2]; /* 400G uses 8 lanes across 2 ports(port 0-1 or 2-3) */ 
    MYD_U16 lineCurrent[MYD_NUM_LANES*2];
} MYD_REPEATER_LINK_STATUS;  


/******************************************************************************
 MYD_STATUS mydCheckPCSLinkStatus
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16  mdioPort,
     IN MYD_U16  laneOffset,
     OUT MYD_U16 *currentStatus,
     OUT MYD_U16 *latchedStatus,
     OUT MYD_PCS_LINK_STATUS *statusDetail
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0-3; lane offset to be checked for link status;
                 For PCS mode that uses multiple lanes, i.e. R2 and R4, the 
                 first lane offset should be provided.

 Outputs:
    currentStatus - overall current host and line status of the link 

    latchedStatus - latched status since last time mydCheckPCSLinkStatus()
        was called. Overall current host and line latched status of the link.

    statusDetail - returns details of status for links on both host and line side.
        The MYD_PCS_LINK_STATUS_TYPE structure details can be used to interpret 
        the results.

 Returns:
    MYD_OK or MYD_FAIL, if action was successful or not.

 Description:
    This API checks the link status of a single lane for the PCS mode. For PCS mode 
    that uses multiple lanes, i.e. R2 and R4, the first lane offset should be 
    provided in the laneOffset input.

    To check the link status on multiple lanes, this API will need to be called 
    for each lane with the requested laneOffset and mdioPort number.

    The latchedStatus is latched low. For example: if the return latchedStatus 
    is 0 and the currentStatus is 1, it means the link is currently up but it was 
    toggled since the last read due to initial mode setting or other link events.

 Side effects:
    Calling this function will clear any latched bits that are a component of 
    the link status.

 Notes/Warnings:
    None
******************************************************************************/
MYD_STATUS mydCheckPCSLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *currentStatus,
    OUT MYD_U16 *latchedStatus,
    OUT MYD_PCS_LINK_STATUS *statusDetail
);

/******************************************************************************
MYD_STATUS mydCheckRepeaterLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_BOOL perLaneStatus,
    OUT MYD_U16 *currentStatus,
    OUT MYD_REPEATER_LINK_STATUS *statusDetail
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0-3; lane offset to be checked for link status
    perLaneStatus - if MYD_FALSE, combined currentStatus status is combined 
                    for all lanes on the provided mdioPort number. The laneOffset
                    must be the 1st laneOffset of the Repeater mode.
                    if MYD_TRUE, currentStatus status is only for the 
                    provided single laneOffset

 Outputs:
    currentStatus - overall current link status of Repeater mode. May be specific lane, 
       or an aggregate of multiple lanes depending on mode and the values of laneOffset 
       and perLaneStatus

       MYD_LINK_UP if one/all lanes are up. MYD_LINK_DOWN, if any component lane
       is down.
       
       Lanes not yet configured in non-grouped modes will not be
       used in the overall status.

    statusDetail - gives details of status for all components links
       on both host and line side.
       Device structure per-lane details can be used to interpret the results.

 Returns:
    MYD_OK or MYD_FAIL, if action was successful or not.

 Description:
    This API checks the Repeater mode link status of the port or the individual lane.  
    Based on the values of laneOffset and perLaneStatus, it returns an aggregated status 
    in currentStatus, with more detailed status in the MYD_REPEATER_LINK_STATUS.

 Side effects:

 Notes/Warnings:
    If perLaneStatus is MYD_FALSE, it will return the combined currentStatus status of
    for all lanes on the provided mdioPort number.  The laneOffset must be the 
    1st laneOffset of the Repeater mode.

******************************************************************************/
MYD_STATUS mydCheckRepeaterLinkStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 laneOffset,
    IN MYD_BOOL perLaneStatus,
    OUT MYD_U16 *currentStatus,
    OUT MYD_REPEATER_LINK_STATUS *statusDetail
);

/*******************************************************************************
 MYD_STATUS mydSetRmFifoCntl
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 txThresholdHigh,
     IN MYD_U16 txThresholdLow,
     IN MYD_U16 rxThreshold,
     IN MYD_U16 txSatThreshold
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    txThresholdHigh - TX FIFO high water mark threshold.
    txThresholdLow  - TX FIFO low water mark threshold.
    rxThreshold     - RX FIFO threshold.
    rxSatThreshold  - TX FIFO saturation threshold.

 Outputs:
    None

 Returns:
    MYD_OK if change was successful, MYD_FAIL if not.
    MYD_FAIL if the device is not initialized.

 Description:
    This function sets rate matching FIFO thresholds. The RX_FIFO
    is used in 25 Gbps to 40 Gbps direction

 Side effects:
    None.

 Notes/Warnings:
    All input threshold values should be less than 0x7FF

    Recommended txThresholdHigh value should be 300~400. Each unit is 16 bytes
    size. i.e. 400/16 = 25 units of 16 bytes (default = 0x19(25 units))

    The txThresholdLow value should be lower than txThresholdHigh (default = 0x12)

    The rxThreshold - high watermark >= 3648/16 = 228, in units of 16 bytes.
    P_max*(1 - rd_rate/wr_rate)= 9728*(1-25/40) = 3648 bytes (default = 0x0E4)

    rxSatThreshold:
    "saturation" region = P_max*(1 - rd_rate/wr_rate)=9728*(1-25/40) = 3648 bytes,
    allow 40 cycles for clock crossing "sat" threshold should less than
    (16k-3648) / 16 - 40 = 756, in units of 16 bytes (default = 0x2F4)

*******************************************************************************/
MYD_STATUS mydSetRmFifoCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 txThresholdHigh,
    IN MYD_U16 txThresholdLow,
    IN MYD_U16 rxThreshold,
    IN MYD_U16 txSatThreshold
);

/*******************************************************************************
MYD_STATUS mydGetRmFifoCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *txThresholdHigh,
    OUT MYD_U16 *txThresholdLow,
    OUT MYD_U16 *rxThreshold,
    OUT MYD_U16 *txSatThreshold
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    txThresholdHigh - TX FIFO high water mark threshold.
    txThresholdLow  - TX FIFO low water mark threshold.
    rxThreshold     - RX FIFO threshold.
    rxSatThreshold  - TX FIFO saturation threshold.

 Returns:
    MYD_OK if change was successful, MYD_FAIL if not.
    MYD_FAIL if the device is not initialized.

 Description:
    This function reads back the rate matching FIFO threshold settings. The
    RX_FIFO is used in 25 Gbps to 40 Gbps direction

 Side effects:
    None.

 Notes/Warnings:
    See above mydSetRmFifoCntl notes for details on the threshold values
*******************************************************************************/
MYD_STATUS mydGetRmFifoCntl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *txThresholdHigh,
    OUT MYD_U16 *txThresholdLow,
    OUT MYD_U16 *rxThreshold,
    OUT MYD_U16 *txSatThreshold
);

/*******************************************************************************
MYD_STATUS mydGetRmFifoPktDropCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 readClear,
    OUT MYD_U16 *txPktDropCntr
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    readClear - if set, the drop counter is cleared after the read.

 Outputs:
    TxPktDropCntr - TX FIFO packet drop counter

 Returns:
    MYD_OK if change was successful, MYD_FAIL if not.
    MYD_FAIL if the device is not initialized.

 Description:
    This function reads back the TX packet drop counters. Packet Drop Counter
    due to FIFO overflow in 40Gb/s to 25Gb/s direction

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MYD_STATUS mydGetRmFifoPktDropCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 readClear,
    OUT MYD_U16 *txPktDropCntr
);

/*****************************************************************************
Rate matching FIFO Interrupts enable Bits
*****************************************************************************/
/* NOT USED (1<<15) */
/* NOT USED (1<<14) */
/* NOT USED (1<<13) */
/* NOT USED (1<<12) */
#define MYD_RX_FIFO_UNDERRUN_BIT     (1<<11)
#define MYD_TX_FIFO_UNDERRUN_BIT     (1<<10)
#define MYD_RX_FIFO_OVERFLOW_BIT     (1<<9)
#define MYD_TX_FIFO_OVERFLOW_BIT     (1<<8)
#define MYD_RX_FIFO_MEM_1BIT_ERR_BIT (1<<6)  /* 2 bits */
#define MYD_TX_FIFO_MEM_1BIT_ERR_BIT (1<<4)  /* 2 bits */
#define MYD_RX_FIFO_MEM_2BIT_ERR_BIT (1<<2)  /* 2 bits */
#define MYD_TX_FIFO_MEM_2BIT_ERR_BIT (1<<0)  /* 2 bits */

/******************************************************************************
 MYD_STATUS mydSetRmFifoInterruptEnable
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 intrEnableFlags,
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    intrEnableFlags - 0:Enables the interrupt. Refer to above "Rate matching
                      FIFO Interrupts enable Bits" flags for details.

 Outputs:
    None

 Returns:
    MYD_OK if change was successful, MYD_FAIL if not.
    MYD_FAIL if the device is not initialized.

 Description:
    This function enable/disable Rate Matching FIFO interrupts. Setting "1"
    will disable the corresponding interrupt.

 Side effects:
    None.

 Notes/Warnings:
    This is interrupt mask register, set "0" to enable the interrupt. Setting "1"
    will disable the corresponding interrupt.

******************************************************************************/
MYD_STATUS mydSetRmFifoInterruptEnable
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 intrEnableFlags
);

/******************************************************************************
 MYD_STATUS mydGetRmFifoInterruptStatus
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     OUT MYD_U16 *rmFifoIntrStatus
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    rmFifoIntrStatus - Refer to above "Rate matching FIFO Interrupts
                       enable Bits" flags for details.

 Returns:
    MYD_OK if change was successful, MYD_FAIL if not.
    MYD_FAIL if the device is not initialized.

 Description:
    This function reads Rate Matching FIFO interrupts status

 Side effects:
    None.

 Notes/Warnings:
    Refer to above "Rate matching FIFO Interrupts enable Bits" flags for
    details.
******************************************************************************/
MYD_STATUS mydGetRmFifoInterruptStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *rmFifoIntrStatus
);

#define MYD_RX_MIN_IPG_8BYTES    0x0
#define MYD_RX_MIN_IPG_16BYTES   0x2
#define MYD_TX_IPG_DIC           0x0 /* Deficit Idle Count */
#define MYD_TX_MIN_IPG_8BYTES    0x1
#define MYD_TX_MIN_IPG_12BYTES   0x2
#define MYD_TX_MIN_IPG_16BYTES   0x3

/*******************************************************************************
 MYD_STATUS mydSetIPGMode
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 rxIPGMode,
     IN MYD_U16 txIPGMode,
     IN MYD_U16 avgDIC
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    rxIPGMode - rx direction (25Gb/s to 40Gb/s) IPG control between packets
    txIPGMode - tx direction (25Gb/s to 40Gb/s) IPG control between packets
    avgDIC - tx direction (40Gb/s to 25Gb/s) average IPG setting in
             DIC mode (in unit of bytes) valid setting is 8 to 15
 Outputs:
    None

 Returns:
    MYD_OK if change was successful, MYD_FAIL if not.
    MYD_FAIL if the device is not initialized.

 Description:
    This function sets Inter-Packet Gap mode of TX and RX

 Side effects:
    None.

 Notes/Warnings:
    rxIPGMode - Rx direction (25Gb/s to 40Gb/s) IPG control between packets
      b00/01: minimum 8 bytes IPG
      b10: minimum 16 bytes IPG

    txIPGMode - Tx direction (40Gb/s to 25Gb/s) IPG control between packets
      b00: DIC
      b01: minimum 8 bytes IPG
      b10: minimum 12 bytes IPG
      b11: minimum 16 bytes IPG

    avgDIC - Tx direction (40Gb/s to 25Gb/s) average IPG setting in DIC mode
             (in unit of bytes) valid setting is 8 to 15 (default=12)
             Note: avgDIC is set if txIPGMode = DIC(0), else value is ignored

*******************************************************************************/
MYD_STATUS mydSetIPGMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 rxIPGMode,
    IN MYD_U16 txIPGMode,
    IN MYD_U16 avgDIC
);

/*******************************************************************************
MYD_STATUS mydGetIPGMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *rxIPGMode,
    OUT MYD_U16 *txIPGMode,
    OUT MYD_U16 *avgDIC
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
    rxIPGMode - rx direction (25Gb/s to 40Gb/s) IPG control between packets
    txIPGMode - tx direction (25Gb/s to 40Gb/s) IPG control between packets
    avgDIC - average IPG setting in DIC mode

 Returns:
    MYD_OK if change was successful, MYD_FAIL if not.
    MYD_FAIL if the device is not initialized.

 Description:
    This function reads back the IPG mode settings

 Side effects:
    None.

 Notes/Warnings:
     Refer to mydSetIPGMode for details on the rxIPGMode, txIPGMode and avgDIC
     outputs.
*******************************************************************************/
MYD_STATUS mydGetIPGMode
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    OUT MYD_U16 *txIPGMode,
    OUT MYD_U16 *rxIPGMode,
    OUT MYD_U16 *avgDIC
);

/******************************************************************************
 MYD_STATUS mydGetPcsFaultStatus
 (
     IN MYD_DEV_PTR pDev,
     IN MYD_U16 mdioPort,
     IN MYD_U16 host_or_line,
     IN MYD_U16 laneOffset,
     OUT MYD_U16 *currentTxFaultStatus,
     OUT MYD_U16 *currentRxFaultStatus,
     OUT MYD_U16 *latchedTxFaultStatus,
     OUT MYD_U16 *latchedRxFaultStatus
 );

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort - MDIO port address, 0-31
    
    host_or_line - which interface is being read:
       MYD_HOST_SIDE
       MYD_LINE_SIDE
       
    laneOffset - 0..3 for lanes 0-3. 

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
    MYD_OK if query was successful, MYD_FAIL if not.
    MYD_FAIL if the operating mode is not set properly or
    the device is not initialized for this mode of operation.

 Description:
    This function is to be called in any of the 5G to 200G PCS
    modes to check the Tx/Rx fault bits.

    Based on the current operating mode, it reads the current
    speed Host/Line PCS Status 2 register twice and returns the value
    of the Tx/Rx fault bits. It returns the first read in the
    "latched" version and the second read in the "current" version.

    In the following register map, X is laneOffset * 2.

    For 200G Host Side:
        4.4008.11 Tx Fault
        4.4008.10 Rx Fault

    For 200G Line Side:
        3.4008.11 Tx Fault
        3.4008.10 Rx Fault

    For 100G Host Side:
        4.0X08.11 Tx Fault
        4.0X8.10 Rx Fault

    For 100G Line Side:
        3.0X08.11 Tx Fault
        3.0X08.10 Rx Fault

    For 40G/50G Host Side:
        4.1X08.11 Tx Fault
        4.1X08.10 Rx Fault

    For 40G/50G Line Side:
        3.1X08.11 Tx Fault
        3.1X08.10 Rx Fault

    For 5/10G/25G Host Side:
        4.2X08.11 Tx Fault
        4.2X08.10 Rx Fault

    For 5/10G/25G Line Side:
        3.2X08.11 Tx Fault
        3.2X08.10 Rx Fault

 Side effects:
    None.

 Notes/Warnings:
    Clears the latch status of those registers being read.

    Speed must be resolved if using AN and/or port must be configured using
    5G to 200G PCS mode, otherwise an error is returned. 

******************************************************************************/
MYD_STATUS mydGetPcsFaultStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *currentTxFaultStatus,
    OUT MYD_U16 *currentRxFaultStatus,
    OUT MYD_U16 *latchedTxFaultStatus,
    OUT MYD_U16 *latchedRxFaultStatus
);


/*******************************************************************
MYD_STATUS mydLaneSoftReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 timeoutMs
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    laneOffset - 0-3; lane to be reset
    timeoutMs - millisec to wait after issuing the lane soft reset

 Returns:
    MYD_OK or MYD_FAIL, if action was successful or not.

 Description:
    Issues a soft reset to a single lane with the wait time.

 Side effects:

 Notes/Warnings:
    None
*******************************************************************/
MYD_STATUS mydLaneSoftReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 timeoutMs
);


/* To select the datapath fault configuration mode: */
#define MYD_DP_DEFAULT_MODE           0 /* Default. Link does not break when the other side link down */
#define MYD_DP_DISENGAGE_MODE         1 /* Disengage TX and RX by sending LF or RF or IDLE */
#define MYD_DP_RESET_MODE             2 /* Reset this side and keep the link down while other side is down */

/* When the mode is MYD_DP_DISENGAGE_MODE, these are the options of what pattern to send */
#define MYD_DP_FAULT_IDLE             0 /* Default. Sending IDLE pattern */
#define MYD_DP_FAULT_LF               1 /* Sending Local Fault pattern*/
#define MYD_DP_FAULT_RF               2 /* Sending Remote Fault pattern */
/*******************************************************************
MYD_STATUS mydSetDPFaultConfig
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 datapathMode,
    IN MYD_U16 txType,
    IN MYD_U16 rxType
);

 Inputs:
   pDev  - pointer to MYD_DEV initialized by mydInitDriver() call
   
   mdioPort - MDIO port address, 0-31
   
   host_or_line - side which datapath is being controlled for:
        MYD_HOST_SIDE
        MYD_LINE_SIDE
        
   laneOffset - lane number 0-3 or MYD_ALL_LANES to control all lanes
                For PCS mode that uses multiple lanes, i.e. R2 and R4, the 
                first lane number or MYD_ALL_LANES should be provided.

   datapathMode - select which data path mode to use on this side when the
                  other side link drops. See definitions above.
        MYD_DP_DEFAULT_MODE
        MYD_DP_DISENGAGE_MODE
        MYD_DP_RESET_MODE

   txType - select which fixed pattern be sent in the Disengage Mode toward
            the copper/fiber when the opposite side is link down. Only used
            when the datapathMode is MYD_DP_DISENGAGE_MODE.
        MYD_DP_FAULT_IDLE
        MYD_DP_FAULT_LF
        MYD_DP_FAULT_RF
   
   rxType - select which fixed pattern be sent in the Disengage Mode towards
            the internal side of the chip (e.g. if this is the host side, towards
            the line side and vise versa) when the opposite side is link down. 
            Only used when the datapathMode is MYD_DP_DISENGAGE_MODE.
        MYD_DP_FAULT_IDLE
        MYD_DP_FAULT_LF
        MYD_DP_FAULT_RF
        
 Outputs:
   None

 Returns:
    MYD_OK if change was successful, MYD_FAIL if not.

 Description:
   "This side" indicates the input "host_or_line". "The other side" means the other
   half of the device. For example, if "host_or_line" is HOST, the other side
   is LINE.

   Sets the data path(DP) mode on this side. This function is used to select what
   happens on "this side" when the other side is link down. Options are to use
   default (link stays up), link drops (MYD_DP_RESET_MODE), or link stays up
   but a fixed pattern replaces the data in the Tx or Rx direction 
   (MYD_DP_DISENGAGE_MODE). Tx direction is towards "this side" serdes. Rx 
   direction is towards the other side.
   
   See the datasheet for suggestions/details.
   
 Side effects:
   None

 Notes/Warnings:
    If you pass MYD_ALL_LANES, the function will only configure all the lanes assigned
    to modes on that port. It will figure out the first lane of each multi-lane mode
    and skip lanes that shouldn't be configured.

    If you pass a specific lane and it is not the first lane of a multi-lane mode,
    that lane will not be configured and an error message will be returned.
*******************************************************************/
MYD_STATUS mydSetDPFaultConfig
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 datapathMode,
    IN MYD_U16 txType,
    IN MYD_U16 rxType
);

/*******************************************************************
MYD_STATUS mydGetDPFaultConfig
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *datapathMode,
    OUT MYD_U16 *txType,
    OUT MYD_U16 *rxType
);

 Inputs:
   pDev  - pointer to MYD_DEV initialized by mydInitDriver() call
   
   mdioPort - MDIO port address, 0-31
   
   host_or_line - whose datapath is being read:
        MYD_HOST_SIDE
        MYD_LINE_SIDE
        
   laneOffset - lane number 0-3
                For PCS mode that uses multiple lanes, i.e. R2 and R4, the 
                first lane number should be provided.

 Outputs:
   datapathMode - read the data path mode on this side when the other side link down.
                  See MACRO definitions above.
        MYD_DP_DEFAULT_MODE
        MYD_DP_DISENGAGE_MODE
        MYD_DP_RESET_MODE

   txType - indicates which fixed pattern is sent in the Disengage Mode toward
            the copper/fiber when the opposite side is link down.
        MYD_DP_FAULT_IDLE
        MYD_DP_FAULT_LF
        MYD_DP_FAULT_RF
   
   rxType - indicates which fixed pattern is sent in the Disengage Mode towards
            the internal side of the chip (e.g. if this is the host side, towards
            the line side and vise versa) when the opposite side is link down.
        MYD_DP_FAULT_IDLE
        MYD_DP_FAULT_LF
        MYD_DP_FAULT_RF

 Returns:
    MYD_OK if query was successful, MYD_FAIL if not.

 Description:
   Reads the settings for this option and returns them. See the description
   for mydSetDPFaultConfig() for details.

 Side effects:
   None

 Notes/Warnings:
   None
*******************************************************************/
MYD_STATUS mydGetDPFaultConfig
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *datapathMode,
    OUT MYD_U16 *txType,
    OUT MYD_U16 *rxType
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif


#endif /* defined MYD_API_H */
