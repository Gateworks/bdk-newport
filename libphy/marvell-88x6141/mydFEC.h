/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/************************************************************************
This file contains function prototypes to configure RS-FEC/KR-FEC 
and read RS-FEC/KR-FEC status for the Marvell X7120/X6181/X6141 Device.
************************************************************************/
#ifndef MYD_RSFEC_H
#define MYD_RSFEC_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#define MYD_NUM_200G_FEC_LANES   8 /* number of FEC lanes for 200G PCS, PCS lanes is the same */
#define MYD_NUM_100G_PCS_LANES  20 /* number of PCS lanes for 100G PCS */
#define MYD_NUM_100G_FEC_LANES   4 /* number of FEC lanes for 100G PCS */
#define MYD_NUM_50G_PCS_LANES    4 /* number of PCS lanes for 40G/50G PCS */
#define MYD_NUM_50G_FEC_LANES    2 /* number of FEC lanes for 50G PCS */

/*******************************************************************************
 These functions are general RS-FEC functions. Some are applicable to all
 RS-FEC and some are not applicable to certain PCSs. Read each function
 header to find which are applicable/not applicable. Note: two 40G modes
 use the 50G PCS. Those are P40BR and P40JR. For those modes, the comments
 related to 50G apply to those 40G modes as well.
*******************************************************************************/

/*******************************************************************************
MYD_STATUS mydSetRsFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 bypassIndicationEnable,
    IN MYD_U16 bypassCorrectionEnable
);

 Inputs:
    pDev       - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort   - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE       
                   
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane
                 
    bypassIndicationEnable - 
                 MYD_ENABLE:  FEC decoder does not indicate errors to the PCS; 
                 MYD_DISABLE: FEC decoder indicates errors to the PCS
                 
    bypassCorrectionEnable - 
                 MYD_ENABLE:  FEC decoder performs detection without correction; 
                 MYD_DISABLE: FEC decoder performs detection and correction

 Outputs:
    None

 Returns:
    MYD_OK if RS-FEC configuration is successful, MYD_FAIL if not

 Description:
    Used to modify the FEC Bypass Indication Enable and/or FEC Bypass Correction
    Enable in the RS-FEC Control Register.

    This API function sets 1.X0C8 bits 1:0 (RS-FEC Control Register). See
    the datasheet for details regarding which modes are supported for
    these two bits.

 Side effects:
    None.

 Notes/Warnings:
    If both are set to MYD_ENABLE, an error will be returned. This is not
    applicable to 200G modes. An error will be returned if called with any
    200G modes.

*******************************************************************************/
MYD_STATUS mydSetRsFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 bypassIndicationEnable,
    IN MYD_U16 bypassCorrectionEnable
);

/*******************************************************************************
MYD_STATUS mydGetRsFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *bypassIndicationEnable,
    OUT MYD_U16 *bypassCorrectionEnable
);


 Inputs:
    pDev       - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort   - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE       
                   
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane
                 
 Outputs:
    bypassIndicationEnable - 
                 MYD_ENABLE:  FEC decoder does not indicate errors to the PCS; 
                 MYD_DISABLE: FEC decoder indicates errors to the PCS
                 
    bypassCorrectionEnable - 
                 MYD_ENABLE:  FEC decoder performs detection without correction; 
                 MYD_DISABLE: FEC decoder performs detection and correction

 Returns:
    MYD_OK if RS-FEC configuration is successful, MYD_FAIL if not

 Description:
    Used to read the FEC Bypass Indication Enable and/or FEC Bypass Correction
    Enable in the RS-FEC Control Register in the RS-FEC Control register.

 Side effects:
    None.

 Notes/Warnings:
    This is not applicable to 200G modes. An error will be returned if called with 
    any 200G modes.

*******************************************************************************/
MYD_STATUS mydGetRsFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *bypassIndicationEnable,
    OUT MYD_U16 *bypassCorrectionEnable
);


/*******************************************************************************
MYD_STATUS mydGetRsFecStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *pcsLaneAlignment,
    OUT MYD_U16 *fecLaneAlignment,
    OUT MYD_U16 *rsFecLaneAMLock,
    OUT MYD_U16 *latchedRsFecHighErr,
    OUT MYD_U16 *currRsFecHighErr
);

 Inputs:
    pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE 

    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane

 Outputs:
    pcsLaneAlignment - PCS lane alignment status of FEC encoder
                       1 = aligned
                       0 = not-aligned
                       
    fecLaneAlignment - FEC receiver lane alignment status (locked and aligned)
                       1 = aligned (for 200G this is set to same as pcsLaneAlignment
                                    because in 100G FEC and PCS are integrated)
                       0 = not-aligned
                       
    rsFecLaneAMLock - Bits 0-7 are mapped to lanes 0-7.
                      For 200G, bits 0-7 are relevant.
                      For 50/100G, bits 0-3 are relevant
                      For 25G, 0 is always returned (this parameter is N/A)
                      1 = locked 
                      0 = not locked
                      
    latchedRsFecHighErr - first read of the LH bit for the RS FEC Error Indication
                          For 200G this is PCS FEC High SER LH bit
                          
    currRsFecHighErr - second read of the LH bit for the RS FEC Error Indication
                       For 200G this is PCS FEC High SER LH bit

 Returns:
    MYD_OK if RS-FEC status is successful, MYD_FAIL if not

 Description:
    Reads and returns the status above from the correct RS-FEC status 
    registers based on the mode/speed.

 Side effects:
    None.

 Notes/Warnings:
    None

 *******************************************************************************/
MYD_STATUS mydGetRsFecStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *pcsLaneAlignment,
    OUT MYD_U16 *fecLaneAlignment,
    OUT MYD_U16 *rsFecLaneAMLock,
    OUT MYD_U16 *latchedRsFecHighErr,
    OUT MYD_U16 *currRsFecHighErr
);

/*******************************************************************************
MYD_STATUS mydGetRsFecPCSAlignmentStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,    
    IN MYD_U16  pcs_lane,
    OUT MYD_U16 *blockLocked,
    OUT MYD_U16 *laneAligned
);

 Inputs:
    pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE 
                   
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane   
                 
    pcs_lane - PCS lane number, 0-19(100G), 0-3(50G)

 Outputs:
    blockLocked - RS-FEC PCS block lock status 
                  1 = locked
                  0 = not locked
                  
    laneAligned - RS-FEC PCS lane alignment status
                  1 = lane aligned
                  0 = lane not aligned

 Returns:
    MYD_OK if read RS-FEC PCS Alignment status is successful, MYD_FAIL if not

 Description:
    Reads the RS-FEC PCS alignment/lane lock status bit for a given RS-FEC lane.

 Side effects:
    None.

 Notes/Warnings:
    Not applicable to 200G modes or 25G modes. Will return an error if called
    with these modes.

*******************************************************************************/
MYD_STATUS mydGetRsFecPCSAlignmentStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,    
    IN MYD_U16  pcs_lane,
    OUT MYD_U16 *blockLocked,
    OUT MYD_U16 *laneAligned
);

/*******************************************************************************
MYD_STATUS mydGetRsFecPMALaneMapping
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,        
    OUT MYD_U16 mapping[MYD_NUM_LANES]
);

 Inputs:
    pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE 
                   
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane                   
                   
 Outputs:
    mapping - RS-FEC PMA lane mapping data array
              mapping[0] = RS-FEC lane 0 mapped to PMA lane# 
              mapping[1] = RS-FEC lane 1 mapped to PMA lane#
              mapping[2] = RS-FEC lane 2 mapped to PMA lane# (100G only)
              mapping[3] = RS-FEC lane 3 mapped to PMA lane# (100G only)

 Returns:
    MYD_OK if read RS-FEC PMA lane mapping is successful, MYD_FAIL if not

 Description:
    Get RS-FEC lane to PMA lane mapping.

 Side effects:
    None.

 Notes/Warnings:
    Not applicable to 200G modes or 25G modes. Will return an error if called
    with these modes.

*******************************************************************************/
MYD_STATUS mydGetRsFecPMALaneMapping
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,        
    OUT MYD_U16 mapping[MYD_NUM_LANES]
);

/*******************************************************************************
MYD_STATUS mydGetRxPCSLaneMapping
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 lane_offset,
    IN MYD_U16 interface_lane,
    OUT MYD_U16 *pcs_lane
);


 Inputs:
    pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE 
                   
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane        
                 
    interface_lane - interface lane number, 0-7 (200G), 0-19(100G), 0-3(40G/50G)

 Outputs:
    pcs_lane - PCS lane received in service interface lane #
               "interface_lane"

 Returns:
    MYD_OK if read PCS lane mapping is successful, MYD_FAIL if not

 Description:
    Reads the PCS Receive lane mapping, i.e. the received lane id on 
    that lane passed into "interface_lane".

 Side effects:
    None.

 Notes/Warnings:
    This is not applicable to 25G modes. Will return an error if called
    with this mode.

 *******************************************************************************/
MYD_STATUS mydGetRxPCSLaneMapping
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 lane_offset,
    IN MYD_U16 interface_lane,
    OUT MYD_U16 *pcs_lane
);


/*******************************************************************************
MYD_STATUS mydGetRsFecCorrectedCwCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *codeWordCounter
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
                   
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane                     

 Outputs:
    codeWordCounter - RS-FEC corrected codewords counter

 Returns:
    MYD_OK if read RS-FEC corrected codewords counter is successful, MYD_FAIL if not

 Description:
    Reads the RS-FEC corrected codewords counter

 Side effects:
    None.

 Notes/Warnings:
    None.

*******************************************************************************/
MYD_STATUS mydGetRsFecCorrectedCwCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *codeWordCounter
);

/*******************************************************************************
MYD_STATUS mydGetRsFecUnCorrectedCwCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *codeWordCounter
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE  
                   
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane 

 Outputs:
    codeWordCounter - RS-FEC uncorrected codewords counter

 Returns:
    MYD_OK if read RS-FEC uncorrected codewords counter is successful, MYD_FAIL if not

 Description:
    Reads the RS-FEC uncorrected codewords counter


 Side effects:
    None.

 Notes/Warnings:
    None.

*******************************************************************************/
MYD_STATUS mydGetRsFecUnCorrectedCwCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *codeWordCounter
);

/*******************************************************************************
MYD_STATUS mydGetRsFecSymbolErrorCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,  
    IN MYD_U16  fecLane,
    OUT MYD_U32 *errorCounter
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE       
                   
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane 

    fecLane - For 200G modes 0..7
              For 100G modes 0...3
              For 50G modes 0..1
              For 25G modes must be 0

 Outputs:
    errorCounter - RS-FEC Symbol error counter

 Returns:
    MYD_OK if read symbol error counter is successful, MYD_FAIL if not

 Description:
    Read RS-FEC symbol error counter per FEC lane

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MYD_STATUS mydGetRsFecSymbolErrorCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,  
    IN MYD_U16  fecLane,
    OUT MYD_U32 *errorCounter
);

/*******************************************************************************
MYD_STATUS mydGetRxPcsBipErrorCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_U16  pcs_lane,
    OUT MYD_U16 *errorCounter
);

 Inputs:
    pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort - MDIO port address, 0-31
    
    pcs_lane - PCS lane number, 0-19(100G), 0-3(50G/40G)
    
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane 
    

 Outputs:
    errorCounter - PCS BIP error counter corresponding to this PCS lane

 Returns:
    MYD_OK if read BIP error counter is successful, MYD_FAIL if not

 Description:
    Read the PCS Rx BIP Error Counter for the given PCS lane.

 Side effects:
    None.

 Notes/Warnings:
    This function is not applicable to 200G or 25G modes. Will return an error if
    called with either of these modes.

*******************************************************************************/
MYD_STATUS mydGetRxPcsBipErrorCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    IN MYD_U16  pcs_lane,
    OUT MYD_U16 *errorCounter
);

/*******************************************************************************
 These functions are specific to the 200G RS-FEC
*******************************************************************************/

/*******************************************************************************
MYD_STATUS mydSetRsFecSERControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 degradedSEREnable,
    IN MYD_U16 bypassIndicationEnable
);

 Inputs:
    pDev       - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort   - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
                   
    laneOffset - must be 0 for 200G modes
                 
    degradedSEREnable - 
                 MYD_ENABLE:  FEC decoder signals degraded SER 
                 MYD_DISABLE: FEC decoder does not signal degraded SER
                 
    bypassIndicationEnable - 
                 MYD_ENABLE:  FEC decoder does not indicate errors
                 MYD_DISABLE: FEC decoder indicates errors

 Outputs:
    None

 Returns:
    MYD_OK if RS-FEC configuration is successful, MYD_FAIL if not

 Description:
    This function sets the PCS FEC Degraded SER Enable and PCS FEC Bypass
    Indication Enable bits in the RS-FEC Degraded SER Control register.

 Side effects:
    None.

 Notes/Warnings:
    This function is only applicable to 200G mode.

*******************************************************************************/
MYD_STATUS mydSetRsFecSERControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    IN MYD_U16 degradedSEREnable,
    IN MYD_U16 bypassIndicationEnable
);

/*******************************************************************************
MYD_STATUS mydGetRsFecSERControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    IN MYD_U16 *degradedSEREnable,
    IN MYD_U16 *bypassIndicationEnable
);


 Inputs:
    pDev       - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort   - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
                   
    laneOffset - must be 0 for 200G modes
                 

 Outputs:
    degradedSEREnable - 
                 MYD_ENABLE:  FEC decoder signals degraded SER 
                 MYD_DISABLE: FEC decoder does not signal degraded SER
                 
    bypassIndicationEnable - 
                 MYD_ENABLE:  FEC decoder does not indicate errors
                 MYD_DISABLE: FEC decoder indicates errors

 Returns:
    MYD_OK if RS-FEC read is successful, MYD_FAIL if not

 Description:
    This function reads the PCS FEC Degraded SER Enable and PCS FEC Bypass
    Indication Enable bits in the RS-FEC Degraded SER Control register.

 Side effects:
    None.

 Notes/Warnings:
    This function is only applicable to 200G mode.

*******************************************************************************/
MYD_STATUS mydGetRsFecSERControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    IN MYD_U16 *degradedSEREnable,
    IN MYD_U16 *bypassIndicationEnable
);


/*******************************************************************************
MYD_STATUS mydSetRsFecSERThresholds
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    IN MYD_U32 serActivateThreshold,
    IN MYD_U32 serDeactivateThreshold,
    IN MYD_U32 serInterval
);

 Inputs:
    pDev       - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort   - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
                   
    laneOffset - must be 0 for 200G modes
                 
    serActivateThreshold - the FEC degraded SER activate threshold
                 
    serDeactivateThreshold - the FEC degraded SER deactivate threshold

    serInterval - the FEC degraded SER interval

 Outputs:
    None

 Returns:
    MYD_OK if RS-FEC configuration is successful, MYD_FAIL if not

 Description:
    This function sets the activate, deactivate thresholds and interval
    for degraded SER.

 Side effects:
    None.

 Notes/Warnings:
    This function is only applicable to 200G mode.

*******************************************************************************/
MYD_STATUS mydSetRsFecSERThresholds
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    IN MYD_U32 serActivateThreshold,
    IN MYD_U32 serDeactivateThreshold,
    IN MYD_U32 serInterval
);

/*******************************************************************************
MYD_STATUS mydGetRsFecSERThresholds
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    OUT MYD_U32 *serActivateThreshold,
    OUT MYD_U32 *serDeactivateThreshold,
    OUT MYD_U32 *serInterval
);


 Inputs:
    pDev       - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort   - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
                   
    laneOffset - must be 0 for 200G modes
                 
 Outputs:
    serActivateThreshold - the FEC degraded SER activate threshold
                 
    serDeactivateThreshold - the FEC degraded SER deactivate threshold

    serInterval - the FEC degraded SER interval

 Returns:
    MYD_OK if read is successful, MYD_FAIL if not

 Description:
    This function reads the activate, deactivate thresholds and interval
    for degraded SER.

 Side effects:
    None.

 Notes/Warnings:
    This function is only applicable to 200G mode.

*******************************************************************************/
MYD_STATUS mydGetRsFecSERThresholds
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    OUT MYD_U32 *serActivateThreshold,
    OUT MYD_U32 *serDeactivateThreshold,
    OUT MYD_U32 *serInterval
);


/*******************************************************************************
MYD_STATUS mydGetRsFecDegradedSERStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *localDegradedSerRcvd,
    OUT MYD_U16 *remoteDegradedSerRcvd,
    OUT MYD_U16 *serDegraded
);


 Inputs:
    pDev       - pointer to MYD_DEV initialized by mydInitDriver() call
    
    mdioPort   - MDIO port address, 0-31
    
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
                   
    laneOffset - must be 0 for 200G modes
                 
 Outputs:
    localDegradedSerRcvd - degraded SER received
        1 = local degraded SER received
        0 = no local degraded SER received
                 
    remoteDegradedSerRcvd - degraded SER received
        1 = remote degraded SER received
        0 = no remote degraded SER received

    serDegraded - PCS FEC Degraded SER status
        1 = SER is degraded
        0 = SER is not degraded       
        
 Returns:
    MYD_OK if read is successful, MYD_FAIL if not

 Description:
    This function reads the degraded SER received status bits in the 200G
    RS-FEC.

 Side effects:
    None.

 Notes/Warnings:
    This function is only applicable to 200G mode.

*******************************************************************************/
MYD_STATUS mydGetRsFecDegradedSERStatus
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,    
    IN MYD_U16 laneOffset,
    OUT MYD_U16 *localDegradedSerRcvd,
    OUT MYD_U16 *remoteDegradedSerRcvd,
    OUT MYD_U16 *serDegraded
);


/*******************************************************************************
 These functions are for KR-FEC
*******************************************************************************/

/*******************************************************************************
MYD_STATUS mydSetKrFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 bypassIndicationEnable
);

 Inputs:
    pDev       - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort   - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane 
    bypassIndicationEnable - 
                 MYD_ENABLE:  Enable FEC decoder to indicate errors to the PCS layer 
                 MYD_DISABLE: Disable FEC decoder to indicate errors to the PCS layer

 Outputs:
    None

 Returns:
    MYD_OK if KR-FEC configuration is successful, MYD_FAIL if not

 Description:
    Enable or disable the KR-FEC error indication decoder to indicate errors 
    to the PCS layer.


 Side effects:
    None.

 Notes/Warnings:
    None.

*******************************************************************************/
MYD_STATUS mydSetKrFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 bypassIndicationEnable
);

/*******************************************************************************
MYD_STATUS mydGetKrFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 *bypassIndicationEnable
);

 Inputs:
    pDev       - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort   - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane 

 Outputs:
    bypassIndicationEnable - 
                 MYD_ENABLE:  Enabled FEC decoder to indicate errors to the PCS layer 
                 MYD_DISABLE: Disabled FEC decoder to indicate errors to the PCS layer

 Returns:
    MYD_OK if KR-FEC configuration is successful, MYD_FAIL if not

 Description:
    Reads the KR-FEC configuration control register to query the status of the
    bit bypassIndicationEnable.


 Side effects:
    None.

 Notes/Warnings:
    None.

*******************************************************************************/
MYD_STATUS mydGetKrFecControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset,
    IN MYD_U16 *bypassIndicationEnable
);


/*******************************************************************************
MYD_STATUS mydGetKrFecAbility
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *krFecAbility,
    OUT MYD_U16 *errIndicationAbility
);

 Inputs:
    pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
   laneOffset - For R4 coupled modes, need to pass lane 0
                For R2 coupled modes, need to pass lanes 0, 2
                For single lane modes, 0-3 to select lane 

 Outputs:
    krFecAbility - 1 = PHY sublayer supports FEC
    errIndicationAbility - 1 = FEC sublayer is able to report FEC decoding 
                               error to the PCS sublayer 

 Returns:
    MYD_OK if KR-FEC ability is successful, MYD_FAIL if not

 Description:
    Reads and returns the value of the KR-FEC ability register. It returns 
    both the following:
    1. FEC sublayer ability to report FEC decoding error to the PCS sublayer 
       (errIndicationAbility)
    2. PHY sublayer ability to support for FEC (krFecAbility)

 Side effects:
    None.

 Notes/Warnings:
    None.

 *******************************************************************************/
MYD_STATUS mydGetKrFecAbility
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U16 *krFecAbility,
    OUT MYD_U16 *errIndicationAbility
);

/*******************************************************************************
MYD_STATUS mydGetKrFecCorrectedBlkCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *blockCounter
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane 

 Outputs:
    blockCounter - KR-FEC corrected block counter

 Returns:
    MYD_OK if read KR-FEC corrected block counter is successful, MYD_FAIL if not

 Description:
    Reads KR-FEC corrected block counter

 Side effects:
    None.

 Notes/Warnings:
    None

*******************************************************************************/
MYD_STATUS mydGetKrFecCorrectedBlkCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *blockCounter
);

/*******************************************************************************
MYD_STATUS mydGetKrFecUnCorrectedBlkCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *blockCounter
);

 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MYD_HOST_SIDE
                   MYD_LINE_SIDE        
    laneOffset - For R4 coupled modes, need to pass lane 0
                 For R2 coupled modes, need to pass lanes 0, 2
                 For single lane modes, 0-3 to select lane 

 Outputs:
    blockCounter - KR-FEC uncorrected block counter

 Returns:
    MYD_OK if read KR-FEC uncorrected block counter is successful, MYD_FAIL if not

 Description:
    Reads KR-FEC uncorrected block counter


 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MYD_STATUS mydGetKrFecUnCorrectedBlkCntr
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16  mdioPort,
    IN MYD_U16  host_or_line,
    IN MYD_U16  laneOffset,
    OUT MYD_U32 *blockCounter
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MYD_RSFEC_H */
