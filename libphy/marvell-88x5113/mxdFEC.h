/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/************************************************************************
This file contains function prototypes to configure RS-FEC/KR-FEC 
and read RS-FEC/KR-FEC status
************************************************************************/
#ifndef MXD_RSFEC_H
#define MXD_RSFEC_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/*******************************************************************************
MXD_STATUS mxdSetRsFecControl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 bypassIndicationEnable,
    IN MXD_U16 bypassCorrectionEnable
);

 Inputs:
    pDev       - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort   - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3; laneOffset 1 - 3 are only used for 25G RS-FEC
    bypassIndicationEnable - 
                 MXD_ENABLE:  FEC decoder does not indicate errors to the PCS; 
                 MXD_DISABLE: FEC decoder indicates errors to the PCS
    bypassCorrectionEnable - 
                 MXD_ENABLE:  FEC decoder performs detection without correction; 
                 MXD_DISABLE: FEC decoder performs detection and correction

 Outputs:
    None

 Returns:
    MXD_OK if RS-FEC configuration is successful, MXD_FAIL if not

 Description:
    Enable or disable the RS-FEC bypass indication and bypass correction
    Register name: RS-FEC control register
    Device 1 Register 0x00C8 for 25GB and 0x80C8 for 50GB and 100GB

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdSetRsFecControl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 bypassIndicationEnable,
    IN MXD_U16 bypassCorrectionEnable
);

/*******************************************************************************
MXD_STATUS mxdGetRsFecStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *pcsLaneAlignment,
    OUT MXD_U16 *fecLaneAlignment,
    OUT MXD_U16 *rsFecLaneAMLock,
    OUT MXD_U16 *latchedRsFecHighErr,
    OUT MXD_U16 *currRsFecHighErr
);

 Inputs:
    pDev     - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3; laneOffset 1 - 3 are Only used for 25G RS-FEC

 Outputs:
    pcsLaneAlignment 
    fecLaneAlignment
    rsFecLaneAMLock   - for 50GB and 100GB only, bit 0-3 for lane 0-3 respectively,
                        bits 0-1 relevant for both 50/100G, bits 2-3 relevant
                        only to 100G. Returns 0 for 25G (not applicable).
    latchedRsFecHighErr
    currRsFecHighErr

 Returns:
    MXD_OK if RS-FEC status is successful, MXD_FAIL if not

 Description:
    Reads and returns the value of bits in the RS-FEC status register.

 Side effects:
    None.

 Notes/Warnings:

 *******************************************************************************/
MXD_STATUS mxdGetRsFecStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *pcsLaneAlignment,
    OUT MXD_U16 *fecLaneAlignment,
    OUT MXD_U16 *rsFecLaneAMLock,
    OUT MXD_U16 *latchedRsFecHighErr,
    OUT MXD_U16 *currRsFecHighErr
);

/*******************************************************************************
MXD_STATUS mxdGetRsFecPCSAlignmentStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  pcs_lane,
    OUT MXD_U16 *blockLocked,
    OUT MXD_U16 *laneAligned
);

 Inputs:
    pDev     - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE 
    pcs_lane - PCS lane number, 0-19(100G), 0-3(50G)

 Outputs:
    blockLocked - RS-FEC PCS block lock status 
    laneAligned - RS-FEC PCS lane alignment status

 Returns:
    MXD_OK if read RS-FEC PCS Aligment status is successful, MXD_FAIL if not

 Description:
    Get RS-FEC PCS Alignment status per lane.
    Register name: RS-FEC PCS Alignment status 1 - 3, 
    Device 1, Register 0x0118, 0x0119, 0x011A, 0x811B

 Side effects:
    None.

 Notes/Warnings:
    This API applies for only 50G and 100G PCS speeds. The 100G uses PCS 
    lane 0-19. The 50G uses PCS lane 0-3.

*******************************************************************************/
MXD_STATUS mxdGetRsFecPCSAlignmentStatus
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  pcs_lane,
    OUT MXD_U16 *blockLocked,
    OUT MXD_U16 *laneAligned
);

/*******************************************************************************
MXD_STATUS mxdGetRsFecPMALaneMapping
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line;
    OUT MXD_U16 mapping[MXD_NUM_LANES]
);

 Inputs:
    pDev     - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE 
 Outputs:
    mapping - RS-FEC PMA lane mapping data array
              mapping[0] = RS-FEC lane 0 mapped to PMA lane# 
              mapping[1] = RS-FEC lane 1 mapped to PMA lane#
              mapping[2] = RS-FEC lane 2 mapped to PMA lane# (100G only)
              mapping[3] = RS-FEC lane 3 mapped to PMA lane# (100G only)

 Returns:
    MXD_OK if read RS-FEC PMA lane mapping is successful, MXD_FAIL if not

 Description:
    Get RS-FEC lane to PMA lane mapping
    Register name: RS-FEC lane mapping register, Device 1, Register 0x80CE

 Side effects:
    None.

 Notes/Warnings:
    This API applies for only 50G and 100G PCS speeds. The 100G will return 
    mapping for all 4 lanes. For 50G, only lanes 0 and 1 mapping are returned.

*******************************************************************************/
MXD_STATUS mxdGetRsFecPMALaneMapping
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    OUT MXD_U16 mapping[MXD_NUM_LANES]
);

/*******************************************************************************
MXD_STATUS mxdGetRsFecPCSLaneMapping
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 interface_lane,
    OUT MXD_U16 *pcs_lane
);

 Inputs:
    pDev     - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE 
    interface_lane - interface lane number, 0-19(100G), 0-3(50G)

 Outputs:
    pcs_lane - PCS lane received in service interface lane #
               "interface_lane"

 Returns:
    MXD_OK if read RS-FEC PMA lane mapping is successful, MXD_FAIL if not

 Description:
    Get RS-FEC PCS lane mapping received in service interface lane #
    "interface_lane".

 Side effects:
    None.

 Notes/Warnings:
    None.

*******************************************************************************/
MXD_STATUS mxdGetRsFecPCSLaneMapping
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  interface_lane,
    OUT MXD_U16 *pcs_lane
);

/*******************************************************************************
MXD_STATUS mxdGetRsFecCorrectedCwCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *codeWordCounter
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3; laneOffset 1 - 3 are only used for 25G RS-FEC

 Outputs:
    codeWordCounter - RS-FEC corrected codewords counter

 Returns:
    MXD_OK if read RS-FEC corrected codewords counter is successful, MXD_FAIL if not

 Description:
    Get RS-FEC corrected codewords counter
    Register name: RS-FEC corrected codewords counter lower
                   RS-FEC corrected codewords counter upper
    Device 1, Register 0x80CA, 0x80CB 

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdGetRsFecCorrectedCwCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *codeWordCounter
);

/*******************************************************************************
MXD_STATUS mxdGetRsFecUnCorrectedCwCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *codeWordCounter
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3; laneOffset 1 - 3 are Only used for 25G RS-FEC

 Outputs:
    codeWordCounter - RS-FEC uncorrected codewords counter

 Returns:
    MXD_OK if read RS-FEC uncorrected codewords counter is successful, MXD_FAIL if not

 Description:
    Get RS-FEC uncorrected codewords counter
    Register name: RS-FEC Uncorrected codewords counter lower
                   RS-FEC Uncorrected codewords counter upper
    Device 1, Register 0x80CC, 0x80CD 

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdGetRsFecUnCorrectedCwCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *codeWordCounter
);

/*******************************************************************************
MXD_STATUS mxdGetRsFecSymbolErrorCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *errorCounter
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3; laneOffset 1 - 3 are Only used for 25G RS-FEC

 Outputs:
    errorCounter - RS-FEC Symbol error counter

 Returns:
    MXD_OK if read symbol error counter is successful, MXD_FAIL if not

 Description:
    Get RS-FEC symbol error counter per lane
    Register name: RS-FEC symbol error counter lower lane #
                   RS-FEC symbol error counter upper lane #
    Device 1, Register 0x80D2, 0x80D3 - 0x80D8 0x80D9 

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdGetRsFecSymbolErrorCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *errorCounter
);

/*******************************************************************************
MXD_STATUS mxdGetRsFecBipErrorCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  pcs_lane,
    OUT MXD_U16 *errorCounter
);

 Inputs:
    pDev     - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    pcs_lane - PCS lane number, 0-19(100G), 0-3(50G)

 Outputs:
    errorCounter - RS-FEC BIP error counter per PCS lane

 Returns:
    MXD_OK if read BIP error counter is successful, MXD_FAIL if not

 Description:
    Get RS-FEC BIP error counter per PCS lane
    Register name: RS-FEC BIP error counter lane #
    Device 1, Register 0x80E6 - 0x80F9 

 Side effects:
    None.

 Notes/Warnings:
    This API applies for only 50G and 100G PCS speeds. The 100G uses PCS 
    lane 0-19. The 50G uses PCS lane 0-3.

*******************************************************************************/
MXD_STATUS mxdGetRsFecBipErrorCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  pcs_lane,
    OUT MXD_U16 *errorCounter
);

/*******************************************************************************
MXD_STATUS mxdSetKrFecControl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 bypassIndicationEnable
);

 Inputs:
    pDev       - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort   - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3; laneOffset 1 - 3 are only used for 10G and 25G KR-FEC
    bypassIndicationEnable - 
                 MXD_ENABLE:  Enable FEC decoder to indicate errors to the PCS layer 
                 MXD_DISABLE: Disable FEC decoder to indicate errors to the PCS layer

 Outputs:
    None

 Returns:
    MXD_OK if KR-FEC configuration is successful, MXD_FAIL if not

 Description:
    Enable or disable the KR-FEC error indication decoder to indicate errors 
    to the PCS layer.
    Register name: KR-FEC control register, Device 1 Register 0x00AB,
    lane register offset = 0x2000 

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdSetKrFecControl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_U16 laneOffset,
    IN MXD_U16 bypassIndicationEnable
);

/*******************************************************************************
MXD_STATUS mxdGetKrFecAbility
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *krFecAbility,
    OUT MXD_U16 *errIndicationAbility
);

 Inputs:
    pDev     - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
   laneOffset - 0..3 for lanes 0-3; laneOffset 1 - 3 are only used for 10G and 25G KR-FEC

 Outputs:
    krFecAbility - 1 = PHY sublayer supports FEC
    errIndicationAbility - 1 = FEC sublayer is able to report FEC decoding error to the PCS sublayer 

 Returns:
    MXD_OK if KR-FEC ability is successful, MXD_FAIL if not

 Description:
    Reads and returns the value of the KR-FEC ability register. It returns both the  the following:
    1. FEC sublayer ability to report FEC decoding error to the PCS sublayer
    2. PHY sublayer ability to support for FEC
    
    Register name: KR-FEC status register, 
    Device 1 Register 0x00AA for line side and 0x10AA for host side,
    lane register offset = 0x2000 

 Side effects:
    None.

 Notes/Warnings:

 *******************************************************************************/
MXD_STATUS mxdGetKrFecAbility
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U16 *krFecAbility,
    OUT MXD_U16 *errIndicationAbility
);


/*******************************************************************************
MXD_STATUS mxdGetKrFecCorrectedBlkCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *blockCounter
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3; laneOffset 1 - 3 are only used for 10G and 25G KR-FEC

 Outputs:
    blockCounter - KR-FEC corrected block counter

 Returns:
    MXD_OK if read KR-FEC corrected block counter is successful, MXD_FAIL if not

 Description:
    Get KR-FEC corrected block counter
    Register name: KR-FEC corrected block counter LSB
                   KR-FEC corrected block counter MSB
    Device 1, Register 0x012C line side, 0x112C host side, lane register offset = 0x2000 

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdGetKrFecCorrectedBlkCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *blockCounter
);

/*******************************************************************************
MXD_STATUS mxdGetKrFecUnCorrectedBlkCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *blockCounter
);

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    host_or_line - which interface is being set:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE        
    laneOffset - 0..3 for lanes 0-3; laneOffset 1 - 3 are only used for 10G and 25G KR-FEC

 Outputs:
    blockCounter - KR-FEC uncorrected block counter

 Returns:
    MXD_OK if read KR-FEC uncorrected block counter is successful, MXD_FAIL if not

 Description:
    Get KR-FEC uncorrected block counter
    Register name: KR-FEC Uncorrected block counter lower
                   KR-FEC Uncorrected block counter upper
    Device 1, Register 0x02BC line side, 0x12BC host side, lane register offset = 0x2000

 Side effects:
    None.

 Notes/Warnings:

*******************************************************************************/
MXD_STATUS mxdGetKrFecUnCorrectedBlkCntr
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    OUT MXD_U32 *blockCounter
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MXD_RSFEC_H */
