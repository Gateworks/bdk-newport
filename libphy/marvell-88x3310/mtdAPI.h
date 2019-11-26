/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions using MDIO access to perform resets, perform
queries of the phy, etc. that are necessary to control and read
status of the Marvell 88X32X0, 88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTD_API_H
#define MTD_API_H
#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif

#define MTD_API_MAJOR_VERSION 2
#define MTD_API_MINOR_VERSION 4
#define MTD_API_BUILD_ID      0

/* This macro is handy for calling a function when you want to test the
   return value and return MTD_FAIL, if the function returned MTD_FAIL,
   otherwise continue */
#define ATTEMPT(xFuncToTry) {if(xFuncToTry != MTD_OK) \
                            {MTD_DBG_ERROR("ATTEMPT failed at %s:%u\n",__FUNCTION__,__LINE__); \
                            return MTD_FAIL;}}

/* These defines are used for some registers which represent the copper
   speed as a 2-bit binary number */
#define MTD_CU_SPEED_10_MBPS    0 /* copper is 10BASE-T */
#define MTD_CU_SPEED_100_MBPS   1 /* copper is 100BASE-TX */
#define MTD_CU_SPEED_1000_MBPS  2 /* copper is 1000BASE-T */
#define MTD_CU_SPEED_10_GBPS    3 /* copper is 10GBASE-T */

/* for 88X33X0/E21X0 family: */
#define MTD_CU_SPEED_NBT        3 /* copper is NBASE-T */
#define MTD_CU_SPEED_NBT_10G    0 /* copper is 10GBASE-T (not applicable to E21X0) */
#define MTD_CU_SPEED_NBT_5G     2 /* copper is 5GBASE-T */
#define MTD_CU_SPEED_NBT_2P5G   1 /* copper is 2.5GBASE-T */

/*******************************************************************
 API Version
 Resets
 Download Mode Selection/Query
 Phy Low Power Mode
 Tunit Low Power Mode
 Parallel Write Mode
 MDIO Download Mode
 *******************************************************************/

/******************************************************************************
 MTD_VOID mtdGetAPIVersion
 (
     OUT MTD_U8 *major,
     OUT MTD_U8 *minor,
     OUT MTD_U8 *buildID
 );


 Inputs:
    None

 Outputs:
    major - major version number
    minor - minor version number
    buildID - if non-released software, this number will be non-zero
              indicating the interim version between releases

 Returns:
    None
    
 Description:
    Returns the version number of this API. The non-zero build ID 
    is used for test and preview releases.  General release build ID is 0.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MTD_VOID mtdGetAPIVersion
(
    OUT MTD_U8 *major,
    OUT MTD_U8 *minor,
    OUT MTD_U8 *buildID
);

/******************************************************************************
MTD_STATUS mtdSoftwareReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 timeoutMs    
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    timeoutMs - 0 will not wait for reset to complete, otherwise
                waits 'timeout' milliseconds for reset to complete

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL if IO error or timed out

 Description:
    Issues a software reset (1.0.15 <= 1) command. Resets firmware and
    hardware state machines and returns non-retain bits to their hardware
    reset values and retain bits keep their values through the reset.

    If timeoutMs is 0, returns immediately. If timeoutMs is non-zero, 
    waits up to 'timeoutMs' milliseconds looking for the reset to complete
    before returning. Returns MTD_FAIL if times out.

 Side effects:
    All "retain" bits keep their values through this reset. Non-"retain"-type
    bits are returned to their hardware reset values following this reset.
    See the Datasheet for a list of retain bits.

 Notes/Warnings:
    Use mtdIsPhyReadyAfterReset() to see if the software reset is complete
    before issuing any other MDIO commands following this reset or pass
    in non-zero timeoutMs to have this function do it for you.

    This is a T unit software reset only. It may only be issued if the T
    unit is ready (1.0.15 is 0) and the T unit is not in low power mode.

******************************************************************************/
MTD_STATUS mtdSoftwareReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 timeoutMs
);


// Definitions for Boot and Flash Upload Status Register 1.C050
#define MTD_FATAL_BOOT_ERROR_POS (0)
#define MTD_BOOT_PROGRESS_POS    (1)
#define MTD_BOOT_COMPLETE_POS    (3)
#define MTD_CODE_STARTED_POS     (4)
#define MTD_UL_CHECKSUM_OK_POS   (5)
#define MTD_CODE_DOWNLOADED_POS  (6)
#define MTD_UL_PROGRESS_POS      (7)
#define MTD_RESET_CAUSE_POS      (8)

#define MTD_FATAL_BOOT_ERROR_MASK (0x1<<MTD_FATAL_BOOT_ERROR_POS)
#define MTD_BOOT_PROGRESS_MASK    (0x3<<MTD_BOOT_PROGRESS_POS)
#define MTD_BOOT_COMPLETE_MASK    (0x1<<MTD_BOOT_COMPLETE_POS)
#define MTD_CODE_STARTED_MASK     (0x1<<MTD_CODE_STARTED_POS)
#define MTD_UL_CHECKSUM_OK_MASK   (0x1<<MTD_UL_CHECKSUM_OK_POS)
#define MTD_CODE_DOWNLOADED_MASK  (0x1<<MTD_CODE_DOWNLOADED_POS)
#define MTD_UL_PROGRESS_MASK      (0x1<<MTD_UL_PROGRESS_POS)
#define MTD_RESET_CAUSE_MASK      (0x3<<MTD_RESET_CAUSE_POS)

// Definitions for Boot Progress field
#define MTD_BOOT_INIT        0x00
#define MTD_WAIT_DL          0x01
#define MTD_CHECKSUM_STARTED 0x02
#define MTD_JUMPING_TO_APP   0x03


/******************************************************************************
MTD_STATUS mtdIsPhyInMdioDownloadMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *downloadMode
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    downloadMode - MTD_TRUE   if it is waiting for download via MDIO or FR2R
                   MTD_FALSE  if it is not waiting for download.

 Returns:
    MTD_OK or MTD_FAIL if function failed to read status


 Description:
    Reads certain bits of register 1.C050 and returns MTD_TRUE if waiting 
    for download and MTD_FALSE if not. 
    if not.

 Side effects:
    None.

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdIsPhyInMdioDownloadMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *downloadMode
);

#define MTD_HARDWARE_RESET          0x00  // Power-on reset, hardware reset or 
                                          // special software reset
#define MTD_INTERNAL_RESET          0x01  // Phy reset itself. Possible reasons
                                          // are an internal fault or a watchdog timer
                                          // overflow. More information is available
                                          // via registers 1.C02A-1.C02D
/******************************************************************************
MTD_STATUS mtdGetPhyResetReason
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *resetType
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    resetType - one of 
        MTD_HARDWARE_RESET
        MTD_INTERNAL_RESET (from 1.C050.9:8)

 Returns:
    MTD_OK or MTD_FAIL depending on whether failed to read status or not

 Description:
    Reads certain bits of register 1.C050 and returns the above values.

 Side effects:
    None.

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdGetPhyResetReason
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *resetType
);

/******************************************************************************
MTD_STATUS mtdDidPhyAppCodeStart
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *appStarted
);
                                    

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    appStarted - MTD_TRUE if it started, MTD_FALSE if it did not

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    Reads certain bits of register 1.C050 and returns the above values.

 Side effects:
    None.

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdDidPhyAppCodeStart
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *appStarted
);

/******************************************************************************
MTD_STATUS mtdFlashUploadedChecksumGood
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *checksumGood
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    checksumGood - MTD_TRUE if the checksum on the uploaded code was good
                   MTD_FALSE if the checksum was not good

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    Reads certain bits of register 1.C050 and returns the above values.

 Side effects:
    None.

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdFlashUploadedChecksumGood
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *checksumGood
);

/******************************************************************************
MTD_STATUS mtdCheckForFatalBootError
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *fatalBootError
)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    fatalBootError - MTD_TRUE if there was a fatal boot error (boot code
                     halted), MTD_FALSE if there was no fatal boot error

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    Reads certain bits of register 1.C050 and returns the above values.

 Side effects:
    None.

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdCheckForFatalBootError
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *fatalBootError
);

/******************************************************************************
MTD_STATUS mtdIsTunitResponsive
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *tunitReady
)              

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    tunitReady - MTD_TRUE if T-unit firmware is ready to accept commands
               MTD_FALSE if T-unit is not ready 

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    This function reads several registers to check if the T-unit firmware 
    is in a state to respond to MDIO write commands.

    If tunitReady is MTD_FALSE, the T-unit is not able to process 
    commands. If tunitReady is MTD_TRUE, the T-unit should be able to
    process commands

 Side effects:

 Notes/Warnings:
    This functions checks for several conditions that could cause the T-unit
    to not be able to respond to commands. These conditions are as follows:

    1. Still in reset (hardware or software reset is not complete), indicated
       by 1.0.15 being 1.
    2. Fatal BIST error during reset.
    3. T-unit in download mode (SPI_CONFIG is 1, or SPI_CONFIG override is 1)
       and no code has been downloaded/started.
    4. T-unit is in low power mode/powered down.
    5. Fatal or non-fatal BIST error on unreleased/engineering only released
       code.
    6. Repeated fatal boot errors (will show as still in reset state)
    7. T-unit placed in test mode (e.g. 10GBASE-T PMA test modes)

    This function calls mtdIsTunitInLowPowerMode() which clears the short
    reach fault bit which is in the same register as the T-unit mode/state.

******************************************************************************/
MTD_STATUS mtdIsTunitResponsive
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *tunitReady
);  

/******************************************************************************
MTD_STATUS mtdIsPhyReadyAfterReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *phyReady
)              

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    phyReady - MTD_TRUE if reset has completed (firmware is up and running)
               MTD_FALSE if reset is in progress or PHY is in download mode

 Returns:
    MTD_OK if query was successful, MTD_FAIL if not

 Description:
    This function reads the register x.1.0.15 and checks if the phy application 
    code has loaded and started. It returns a value MTD_TRUE meaning reset is 
    completed and code started and a MTD_FALSE if reset is in progress or if the 
    T-unit is in flash download mode.

    MDIO commands (other than download-related and hardware reset commands) 
    should not be sent before this function returns MTD_TRUE.

    MTD_TRUE indicates the T-unit has completed its reset.

 Side effects:

 Notes/Warnings:
    To query if reset has completed and T-unit is ready to accept
    MDIO commands (app code started successfully and reset is complete).

    Should complete within 500ms following a special software reset, power-on
    reset or hardware reset.

    If Phy is in download mode (pin SPI_CONFIG[1] is high or override is 1), 
    this function will always return MTD_FALSE.

******************************************************************************/
MTD_STATUS mtdIsPhyReadyAfterReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *phyReady
);

/******************************************************************************
MTD_STATUS mtdPutPhyInLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    This function puts the T-unit and the XFI portion of the
    H and X-unit, and the 1000BX/SGMII interface of the
    X-unit into a powered down mode.

 Side effects:

 Notes/Warnings:
    The PHY can be removed from low power mode by either calling
    mtdRemovePhyLowPowerMode() or by doing a hardware reset on the PHY (a
    software reset will not remove the low power mode, because the low power
    bits are retain bits), assuming the strap PDSTATE is strapped
    to have the PHY not come up in low power mode. If PDSTATE is strapped
    to have the PHY come up in low power mode, then the only way to restore
    power is to call mtdRemovePhyLowPowerMode().

******************************************************************************/
MTD_STATUS mtdPutPhyInLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
MTD_STATUS mtdRemovePhyLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)


 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    This function removes the T-unit and the XFI portion of the
    H and X-unit, and the 1000BX/SGMII interface of the
    X-unit from a powered down mode.


 Side effects:
    H/X-Unit SGMII and T-unit AN will start (if they are enabled).

 Notes/Warnings:
    The PHY can be removed from low power mode by either calling
    mtdRemovePhyLowPowerMode() or by doing a hardware reset on the PHY (a
    software reset will not remove the low power mode, because the low power
    bits are retain bits), assuming the strap PDSTATE is strapped
    to have the PHY not come up in low power mode. If PDSTATE is strapped
    to have the PHY come up in low power mode, then the only way to restore
    power is to call mtdRemovePhyLowPowerMode().

    If the PHY was strapped with PDSTATE to have the PHY come up in low power
    mode, mtdRemovePhyLowPowerMode() must be called before the PHY can
    complete its initialization and be configured.

    After removing the PHY from low power mode, make sure the T unit is ready
    by calling mtdIsTunitResponsive() before writing any T unit registers.

******************************************************************************/
MTD_STATUS mtdRemovePhyLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);


/******************************************************************************
MTD_STATUS mtdPutTunitInLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    This function uses a firmware register bit to put the T-unit in low power 
    mode by writing a '1' 1.0.11.

 Side effects:

 Notes/Warnings:
    The T-unit can be removed from low power mode by either calling
    mtdRemoveTunitPhyLowPowerMode() or by doing a hardware reset on the PHY (a
    software reset will not remove the low power mode, because the low power
    bits are retain bits). The hardware reset behavior depends on the
    PDSTATE strap pin ultimately. This note assumes the PDSTATE strap
    is set to not come up in power-down. A hardware reset may also
    remove other units from a power-down state depending on the PDSTATE
    as well. See the datasheet for details.

    Calling this function will not remove the T-unit from low power mode if
    the T-unit is powered down because the PHY has been put in fiber-only
    mode or if the T-unit is powered down because of the auto-media detect

******************************************************************************/
MTD_STATUS mtdPutTunitInLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
MTD_STATUS mtdRemoveTunitLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    This function sets both 1.0.11 and 3.0.11 to 0, which should remove
    the low power mode. Restarts AN (if it is enabled).


 Side effects:
    AN will start (if it is enabled).

 Notes/Warnings:
    The T-unit can be removed from low power mode by either calling
    mtdRemoveTunitLowPowerMode() or by doing a hardware reset on the PHY (a
    software reset will not remove the low power mode, because the low power
    bits are retain bits). The hardware reset behavior depends on the
    PDSTATE strap pin ultimately. This note assumes the PDSTATE strap
    is set to not come up in power-down. A hardware reset may also
    remove other units from a power-down state depending on the PDSTATE
    as well. See the datasheet for details.

    After removing the T unit from low power mode, make sure the T unit is ready
    by calling mtdIsTunitResponsive() before writing any T unit registers.    

******************************************************************************/
MTD_STATUS mtdRemoveTunitLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
MTD_STATUS mtdIsTunitInLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *inLowPowerMode
)

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    inLowPowerMode - MTD_TRUE if T-unit is in low power mode, MTD_FALSE if not

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not

 Description:
    This function checks 1.0.11 and 3.0.11, and also checks BIST status and
    internal T-unit state/mode variable to see if T-unit is powered down.

    When T-unit is powered-down, it will not respond to command.

    T-unit can be powered-down explicitly through 1.0.11 or 3.0.11, or it
    can be powered-down conditionally based on the PHY operating mode based
    on settings in 31.F000 and 31.F001 (for example, in fiber-only mode, the
    T-unit is powered down).

 Side effects:
    None

 Notes/Warnings:
    If the T-unit was powered down explicitly it can be powered-up by
    calling mtdRemoveTunitLowPowerMode(). If it was powered-down indirectly
    by PHY settings in 31.F000 and 31.F001,  it will stay powered down
    until those conditions change. For example, if the PHY was put in
    fiber-only mode, the T-unit is powered down until the PHY is removed
    from fiber-only mode.

******************************************************************************/
MTD_STATUS mtdIsTunitInLowPowerMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *inLowPowerMode
);

/******************************************************************************
MTD_STATUS mtdPutPhyInParallelWriteMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Sets 3.D101.14 to put the PHY into in parallel write mode. 

 Side effects:
    Setting this bit will causes the PHY to ignore the MDIO port address on 
    writes.


 Notes/Warnings:
    1. Reset is not needed after setting this pin to 1.
    2. The read will not work with this bit set. Therefore to read, this bit has 
    to be set to '0' and read has to be done one port at a time. The function 
    mtdRemovePhyFromParallelWriteMode() can be used to set bit back to 0.
******************************************************************************/
MTD_STATUS mtdPutPhyInParallelWriteMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
MTD_STATUS mtdRemovePhyFromParallelWriteMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Sets 31.D101.14 to 0 (off) to take PHY out of parallel write mode. 

 Side effects:
    None.
    
 Notes/Warnings:
    1. Reset is not needed after setting this bit to 0.
    2. For normal MDIO operation the bit must be 0.
    3. MDIO read on all ports will not work until this bit is set back to 0.
******************************************************************************/
MTD_STATUS mtdRemovePhyFromParallelWriteMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);


/******************************************************************************
MTD_STATUS mtdPutPhyInMdioDownloadMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Sets override of SPI_CONFIG to 1, then resets the T-unit so boot code will
    wait for MDIO download of code to RAM (or allow code to be downloaded into
    flash for a flash update).

 Side effects:
    None

 Notes/Warnings:
    None
******************************************************************************/
MTD_STATUS mtdPutPhyInMdioDownloadMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
MTD_STATUS mtdRemovePhyMdioDownloadMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Sets override of SPI_CONFIG to 0, then resets the T-unit so code will
    load from flash.

 Side effects:
    None

 Notes/Warnings:
    This function does a T unit hardware reset which will cause the
    firmware to be reloaded from flash (if the strap is set to cause this
    behavior). Reloading from flash can take several hundred milliseconds
    depending on the number of ports.

    To check if firmware is loaded, check all ports using mtdDidPhyAppCodeStart()
    before continuing any T unit configuration (such as removing low power
    mode).

******************************************************************************/
MTD_STATUS mtdRemovePhyMdioDownloadMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);


/****************************************************************************/
/*******************************************************************
  Firmware Version
 *******************************************************************/
/****************************************************************************/

/******************************************************************************
MTD_STATUS mtdGetFirmwareVersion
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    OUT MTD_U8 *major, 
    OUT MTD_U8 *minor, 
    OUT MTD_U8 *inc, 
    OUT MTD_U8 *test
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    major - major version, X.Y.Z.W, the X
    minor - minor version, X.Y.Z.W, the Y
    inc   - incremental version, X.Y.Z.W, the Z
    test  - test version, X.Y.Z.W, the W, should be 0 for released code, 
            non-zero indicates this is a non-released code

 Returns:
    MTD_FAIL if version can't be queried or firmware is in download mode 
    (meaning all version numbers are 0), MTD_OK otherwise

 Description:
    This function reads the firmware version number and stores it in the
    pointers passed in by the user.

 Side effects:
    None

 Notes/Warnings:
    This function returns all 0's if the phy is in download mode. The phy 
    application code must have started and be ready before issuing this 
    command.

******************************************************************************/
MTD_STATUS mtdGetFirmwareVersion
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    OUT MTD_U8 *major, 
    OUT MTD_U8 *minor, 
    OUT MTD_U8 *inc, 
    OUT MTD_U8 *test
);



/*******************************************************************
   802.3 Clause 28 and Clause 45
   Auto-negotiation Related Control & Status
 *******************************************************************/

/*******************************************************************
 Enabling speeds for autonegotiation
 Reading speeds enabled for autonegotation
 Set/get pause advertisement for autonegotiation
 Other Autoneg-related Control and Status (restart,disable/enable,
 force master/slave/auto, checking for autoneg resolution, etc.)
 *******************************************************************/
#define MTD_ADV_NONE           0x0000 /* No speeds to be advertised */
#define MTD_SPEED_10M_HD       0x0001 /* 10BT half-duplex */
#define MTD_SPEED_10M_FD       0x0002 /* 10BT full-duplex */
#define MTD_SPEED_100M_HD      0x0004 /* 100BASE-TX half-duplex */
#define MTD_SPEED_100M_FD      0x0008 /* 100BASE-TX full-duplex */
#define MTD_SPEED_1GIG_HD      0x0010 /* 1000BASE-T half-duplex */
#define MTD_SPEED_1GIG_FD      0x0020 /* 1000BASE-T full-duplex */
#define MTD_SPEED_10GIG_FD     0x0040 /* 10GBASE-T full-duplex, not available on 88E20X0/88E21X0 devices */
#define MTD_SPEED_2P5GIG_FD    0x0800 /* 2.5GBASE-T full-duplex, 88X33X0/88E20X0/88E21X0 family only */
#define MTD_SPEED_5GIG_FD      0x1000 /* 5GBASE-T full-duplex, 88X33X0/88E20X0/88E21X0 family only */

/* Will query the device type and pick all copper speeds available on this device */
#define MTD_ALL_SPEEDS_AVAILABLE 0xFFFF /* Pass this to dynamically pick one of the below defines to select all 
                                           speeds available on this PHY device */

/* All speeds available on X32X0 devices, left for backward compatibility */
#define MTD_SPEED_ALL          (MTD_SPEED_10M_HD | \
                                MTD_SPEED_10M_FD | \
                                MTD_SPEED_100M_HD | \
                                MTD_SPEED_100M_FD | \
                                MTD_SPEED_1GIG_HD | \
                                MTD_SPEED_1GIG_FD | \
                                MTD_SPEED_10GIG_FD)

/* All speeds available on X32X0 devices */
#define MTD_SPEED_ALL_32X0 MTD_SPEED_ALL

/* All speeds available on X33X0 devices */
#define MTD_SPEED_ALL_33X0     (MTD_SPEED_10M_HD | \
                                MTD_SPEED_10M_FD | \
                                MTD_SPEED_100M_HD | \
                                MTD_SPEED_100M_FD | \
                                MTD_SPEED_1GIG_HD | \
                                MTD_SPEED_1GIG_FD | \
                                MTD_SPEED_10GIG_FD | \
                                MTD_SPEED_2P5GIG_FD |\
                                MTD_SPEED_5GIG_FD)

/* All speeds available on E20X0 and E21X0 devices */
#define MTD_SPEED_ALL_21X0_20X0 (MTD_SPEED_10M_HD | \
                                 MTD_SPEED_10M_FD | \
                                 MTD_SPEED_100M_HD | \
                                 MTD_SPEED_100M_FD | \
                                 MTD_SPEED_1GIG_HD | \
                                 MTD_SPEED_1GIG_FD | \
                                 MTD_SPEED_2P5GIG_FD |\
                                 MTD_SPEED_5GIG_FD)

/* these bits are for forcing the speed and disabling autonegotiation */
#define MTD_SPEED_10M_HD_AN_DIS  0x0080 /* Speed forced to 10BT half-duplex */
#define MTD_SPEED_10M_FD_AN_DIS  0x0100 /* Speed forced to 10BT full-duplex */
#define MTD_SPEED_100M_HD_AN_DIS 0x0200 /* Speed forced to 100BT half-duplex */
#define MTD_SPEED_100M_FD_AN_DIS 0x0400 /* Speed forced to 100BT full-duplex */

/* this value is returned for the speed when the link status is checked and the speed has been */
/* forced to one speed but the link is up at a different speed. it indicates an error. */
#define MTD_SPEED_MISMATCH       0x8000 /* Speed is forced to one speed, but status indicates another */

/******************************************************************************
 MTD_STATUS mtdGetSpeedsAvailable
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *speed_bits,     
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    speed_bits - depending on the device id, returns one of the following:
        MTD_SPEED_ALL_32X0
        MTD_SPEED_ALL_33X0
        MTD_SPEED_ALL_21X0_20X0

 Returns:
    MTD_OK or MTD_FAIL, if query succeeded or failed

 Description:
    This function returns a bit mask of the copper speeds available on
    the T unit based on the device id.

 Side effects:

 Notes/Warnings:
    
******************************************************************************/
MTD_STATUS mtdGetSpeedsAvailable
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *speed_bits     
);

/******************************************************************************
 MTD_STATUS mtdEnableSpeeds
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 speed_bits, 
     IN MTD_BOOL anRestart
 );

 Inputs: 2
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    speed_bits - speeds to be advertised during auto-negotiation. One or more 
                 of the following (bits logically OR together):
                MTD_ADV_NONE (no bits set)
                MTD_SPEED_10M_HD
                MTD_SPEED_10M_FD
                MTD_SPEED_100M_HD
                MTD_SPEED_100M_FD
                MTD_SPEED_1GIG_HD
                MTD_SPEED_1GIG_FD
                MTD_SPEED_10GIG_FD
                MTD_SPEED_2P5GIG_FD (88X33X0/88E20X0/88E21X0 family only)
                MTD_SPEED_5GIG_FD (88X33X0/88E20X0/88E21X0 family only)
                MTD_SPEED_ALL (10G and below, excludes 2.5G/5G)
                MTD_SPEED_ALL_32X0 (10G and below, excludes 2.5G/5G)                
                MTD_SPEED_ALL_33X0 (88X33X0 family only)
                MTD_SPEED_ALL_21X0_20X0 (5G and below, all speeds on E21X0 and E20X0)
                MTD_ALL_SPEEDS_AVAILABLE (dynamically picks all speeds available based on PHY type)

    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.

 Outputs:
    None

 Returns:
    MTD_OK if action was successfully taken, MTD_FAIL if not. Also returns
    MTD_FAIL if try to force the speed or try to advertise a speed not supported
    on this PHY.

 Description:
    This function allows the user to select the speeds to be advertised to the 
    link partner during auto-negotiation.

    First, this function enables auto-negotiation and XNPs by calling 
    mtdUndoForcedSpeed(). 

    The function takes in a 16 bit value and sets the appropriate bits in MMD
    7 to have those speeds advertised.

    The function also checks if the input parameter is MTD_ADV_NONE, in which case 
    all speeds are disabled effectively disabling the phy from training 
    (but not disabling auto-negotiation).

    If anRestart is MTD_TRUE, an auto-negotiation restart is issued making the change 
    immediate. If anRestart is MTD_FALSE, the change will not take effect until the 
    next time auto-negotiation restarts.

 Side effects:
    Setting speed in 1.0 to 10GBASE-T has the effect of enabling XNPs in 7.0 and
    enabling auto-negotiation in 7.0.

 Notes/Warnings:

    Example:
    To train the highest speed matching the far end among
    either 1000BASE-T Full-duplex or 10GBASE-T:
    mtdEnableSpeeds(devPtr,port,MTD_SPEED_1GIG_FD | MTD_SPEED_10GIG_FD, MTD_TRUE);

    To allow only 10GBASE-T to train:
    mtdEnableSpeeds(devPtr,port,MTD_SPEED_10GIG_FD, MTD_TRUE);

    To disable all speeds (but AN will still be running, just advertising no
    speeds)
    mtdEnableSpeeds(devPtr,port,MTD_ADV_NONE, MTD_TRUE);

    This function is not to be used to disable autonegotiation and force the speed
    to 10BASE-T or 100BASE-TX. Use mtdForceSpeed() for this.

    88X33X0 Z1/Z2 and E20X0 Z2 are not supported starting with API version 1.2.
    Version 1.2 and later require A0 revision of these devices.

******************************************************************************/
MTD_STATUS mtdEnableSpeeds
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 speed_bits, 
    IN MTD_BOOL anRestart
);

/******************************************************************************
 MTD_STATUS mtdEnableAllSpeedsRestartAn
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port     
 );


 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if query succeeded or failed

 Description:
    This function enables all the speeds available on this type
    of PHY based on the device id and restarts AN.

 Side effects:

 Notes/Warnings:
    Equivalent to
    
    MTD_U16 speeds;

    ATTEMPT(mtdGetSpeedsAvailable(devPtr,port,&speeds));
    ATTEMPT(mtdEnableSpeeds(devPtr,port,speeds,MTD_TRUE));

******************************************************************************/
MTD_STATUS mtdEnableAllSpeedsRestartAn
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port     
);

/******************************************************************************
 MTD_STATUS mtdGetSpeedsEnabled
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *speed_bits,     
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    speed_bits - bits set according to which speeds are currently being
        advertised. One or more bits set according to the defines above
        in mtdEnableSpeeds().

 Returns:
    MTD_OK or MTD_FAIL, if query succeeded or failed

 Description:
    This function returns the speeds that have been enabled.

 Side effects:

 Notes/Warnings:
    Speeds enabled don't take effect until auto-negotiation is restarted.

******************************************************************************/
MTD_STATUS mtdGetSpeedsEnabled
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *speed_bits     
);

/*****************************************************************************
MTD_STATUS mtdForceSpeed
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 forcedSpeedBit 
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    forcedSpeedBit - one of the following
        MTD_SPEED_10M_HD_AN_DIS  - speed forced to 10BT half-duplex
        MTD_SPEED_10M_FD_AN_DIS  - speed forced to 10BT full-duplex
        MTD_SPEED_100M_HD_AN_DIS - speed forced to 100BT half-duplex
        MTD_SPEED_100M_FD_AN_DIS - speed forced to 100BT full-duplex
 
 Outputs:
    None

 Returns:
    MTD_OK if the change was successful, or MTD_FAIL if not
    
 Description:
    Disables autonegotation, and forces the T-unit to one of the speeds above. 
    Will drop the link and attempt to train the link at the forced speed.

    Modifies the speed bits in 1.0 to one of the speeds above.

    Does a software reset of the T unit and wait until it is complete before 
    returning.

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdForceSpeed
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 forcedSpeedBit 
);

/*****************************************************************************
MTD_STATUS mtdUndoForcedSpeed
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.
 
 Outputs:
    None

 Returns:
    MTD_OK if the change was successful, or MTD_FAIL if not
    
 Description:
    Sets the speed bits in 1.0 back to the power-on default of 11b 
    (10GBASE-T). Enables auto-negotiation.

    Does a software reset of the T unit and wait until it is complete before 
    enabling AN and returning.   

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdUndoForcedSpeed
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);


/*****************************************************************************
MTD_STATUS mtdGetForcedSpeed
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *speedIsForced,
    OUT MTD_U16 *forcedSpeed 
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
 
 Outputs:
    speedIsForced - MTD_TRUE if an is disabled (1.0.12 == 0) AND
        the speed in 1.0.13/6 is set to 10BT or 100BT (speeds which do
        not require an to train).
    forcedSpeed - one of the following if speedIsForced is MTD_TRUE
        MTD_SPEED_10M_HD_AN_DIS  - speed forced to 10BT half-duplex
        MTD_SPEED_10M_FD_AN_DIS  - speed forced to 10BT full-duplex
        MTD_SPEED_100M_HD_AN_DIS - speed forced to 100BT half-duplex
        MTD_SPEED_100M_FD_AN_DIS - speed forced to 100BT full-duplex

 Returns:
    MTD_OK if the query was successful, or MTD_FAIL if not
    
 Description:
    Checks if AN is disabled (7.0.12=0) and if the speed select in
    register 1.0.13 and 1.0.6 is set to either 10BT or 100BT speeds. If
    all of this is true, returns MTD_TRUE in speedIsForced along with 
    the speed/duplex setting in forcedSpeedBits. If any of this is 
    false (AN is enabled, or the speed is set to 1000BT or 10GBT), then
    speedIsForced is returned MTD_FALSE and the forcedSpeedBit value
    is invalid.

 Notes/Warnings:
    None.

******************************************************************************/
MTD_STATUS mtdGetForcedSpeed
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *speedIsForced,
    OUT MTD_U16 *forcedSpeed 
);



#define MTD_CLEAR_PAUSE     0 /*  clears both pause bits */
#define MTD_SYM_PAUSE       1 /*  for symmetric pause only */
#define MTD_ASYM_PAUSE      2 /*  for asymmetric pause only */
#define MTD_SYM_ASYM_PAUSE  3 /*  for both */
/******************************************************************************
MTD_STATUS mtdSetPauseAdvertisement
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 pauseType,
    IN MTD_BOOL anRestart
);
                               
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    pauseType - one of the following: 
                MTD_SYM_PAUSE, 
                MTD_ASYM_PAUSE, 
                MTD_SYM_ASYM_PAUSE or 
                MTD_CLEAR_PAUSE.
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or failed

 Description:
    This function sets the asymmetric and symmetric pause bits in the technology 
    ability field in the AN Advertisement register and optionally restarts 
    auto-negotiation to use the new values. This selects what type of pause 
    is to be advertised to the far end MAC during auto-negotiation. If 
    auto-negotiation is restarted, it is enabled first.

    Sets entire 2-bit field to the value passed in pauseType.

    To clear both bits, pass in MTD_CLEAR_PAUSE.

 Side effects:
    None

 Notes/Warnings:
    This function will not take effect unless the auto-negotiation is restarted.

******************************************************************************/
MTD_STATUS mtdSetPauseAdvertisement
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 pauseType,
    IN MTD_BOOL anRestart
);

/******************************************************************************
MTD_STATUS mtdGetLPAdvertisedSpeeds
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *ieeeSpeedBits,
    OUT MTD_U16 *nbasetSpeedBits
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    ieeeSpeedBits - the speeds the link partner advertised via the base page,
        10GBASE-T message page or 1GBASE-T message page
        One or all of the following (bit mask)
            MTD_ADV_NONE
            MTD_SPEED_10M_HD
            MTD_SPEED_10M_FD
            MTD_SPEED_100M_HD
            MTD_SPEED_100M_FD
            MTD_SPEED_1GIG_HD
            MTD_SPEED_1GIG_FD
            MTD_SPEED_10GIG_FD
            MTD_SPEED_2P5GIG_FD (88X33X0/88E20X0/88E21X0 family only)
            MTD_SPEED_5GIG_FD (88X33X0/88E20X0/88E21X0 family only)
        
    nbasetSpeedBits - the speeds the link partner advertised via the
        NBASE-T message page (88X33X0/88E20X0/88E21X0 family only)
        One or both of the following (bit mask)
            MTD_ADV_NONE (always this value if the device is not 88X33X0/88E20X0 device)
            MTD_SPEED_2P5GIG_FD (88X33X0/88E20X0/88E21X0 family only)
            MTD_SPEED_5GIG_FD (88X33X0/88E20X0/88E21X0 family only)

           

 Returns:
    MTD_OK or MTD_FAIL, based on whether the query succeeded or failed. Returns
    MTD_FAIL and no speeds bits will be set if AN is not complete.

 Description:
    This function reads the AN status registers and reports the speeds the
    link partner advertised during AN.

    These values are only valid after AN completes.

 Side effects:
    None

 Notes/Warnings:
    AN must be complete in order for this function to return valid results.

    Check 7.1.5, AN complete or check the return status to know if the result
    is valid. Returns MTD_FAIL if AN is not complete.

    88X32X0 device family always returns MTD_ADV_NONE for nbasetSpeedBits
    regardless if LP advertised 2.5G/5G or not.

******************************************************************************/
MTD_STATUS mtdGetLPAdvertisedSpeeds
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *ieeeSpeedBits,
    OUT MTD_U16 *nbasetSpeedBits /* this is always MTD_ADV_NONE for !(88X33X0/88E20X0/E21X0) devices */
);


/******************************************************************************
MTD_STATUS mtdGetLPAdvertisedPause
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *pauseBits
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    pauseBits - setting of link partner's pause bits based on bit definitions above in 
                mtdmtdSetPauseAdvertisement()

 Returns:
    MTD_OK or MTD_FAIL, based on whether the query succeeded or failed. Returns
    MTD_FAIL and MTD_CLEAR_PAUSE if AN is not complete.

 Description:
    This function reads 7.19 (LP Base page ability) and returns the advertised
    pause setting that was received from the link partner.

 Side effects:
    None

 Notes/Warnings:
    AN must be complete in order for this function to return valid results.

    Check 7.1.5, AN complete or check the return status to know if the result
    is valid. Returns MTD_FAIL if AN is not complete.

******************************************************************************/
MTD_STATUS mtdGetLPAdvertisedPause
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *pauseBits
);


/******************************************************************************
MTD_STATUS mtdGetTxRxPauseResolution
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *tx_pause_enabled,
    OUT MTD_BOOL *rx_pause_enabled
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    pauseResolved - MTD_TRUE/MTD_FALSE based on whether AN speed/duplex
                    is resolved or not
    tx_pause_enabled - MTD_TRUE/MTD_FALSE based on local and LP pause
                       advertisement
    rx_pause_enabled - MTD_TRUE/MTD_FALSE based on local and LP pause
                       advertisement

 Returns:
    MTD_OK or MTD_FAIL, based on whether the query succeeded or failed

 Description:
    This function first checks 3.8008.11 to insure that autonegotiation
    has resolved the pause settings and sets pauseResolved to 
    MTD_TRUE or MTD_FALSE based on this register bit.
 
    This function reads 3.8008.9:8 and sets corresponding flags based
    on bits.

 Side effects:
    None

 Notes/Warnings:
    None

******************************************************************************/
MTD_STATUS mtdGetTxRxPauseResolution
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *pauseResolved,
    OUT MTD_BOOL *tx_pause_enabled,
    OUT MTD_BOOL *rx_pause_enabled
);


/******************************************************************************
 MTD_STATUS mtdAutonegRestart
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, depending on if action was successful

 Description:
    Restarts auto-negotiation. The bit is self-clearing. If the link is up,
    the link will drop and auto-negotiation will start again.

 Side effects:
    None.

 Notes/Warnings:
    Restarting auto-negotiation will have no effect if auto-negotiation is 
    disabled.

    This function is important as it is necessary to restart auto-negotiation 
    after changing many auto-negotiation settings before the changes will take 
    effect.

******************************************************************************/
MTD_STATUS mtdAutonegRestart
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
 MTD_STATUS mtdAutonegDisable
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Turns off the enable auto-negotiation bit disabling auto-negotiation. 
    The phy will not train with auto-negotiation disabled (except in 100M/10BT 
    forced mode).

 Side effects:

 Notes/Warnings:
    Restart autonegation will not take effect if AN is disabled.

    IMPORTANT. AN cannot be disabled if the speed in 1.0 is set to 1G or
    10G speed. The PHY will ignore writes to 7.0.12 = 0 if the speed is
    1G or 10G. Ths speed in 1.0 must first be set to 10M or 100M
    before calling this function for it to have any effect on 7.0.12.

    To keep the PHY from coming up at any speed, set speed advertisement
    to MTD_ADV_NONE and restart AN.

    To make PHY quiet (no transmission at all) put PHY into low
    power mode, mtdPutTunitInLowPowerMode().

******************************************************************************/
MTD_STATUS mtdAutonegDisable
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
 MTD_STATUS mtdAutonegEnable
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Re-enables auto-negotiation.

 Side effects:

 Notes/Warnings:
    Restart autonegation will not take effect if AN is disabled.

******************************************************************************/
MTD_STATUS mtdAutonegEnable
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

/******************************************************************************
 MTD_STATUS mtdAutonegForceMaster
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL anRestart
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.


 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Sets auto-negotiation to manual and forced as a master.

    Restarts auto-negotiation by calling the function only if the input 
    parameter anRestart was selected. Also re-enables auto-negotiation before 
    restarting auto-negotiation.

 Side effects:
    auto-negotiation has to be restarted for it to take effect

 Notes/Warnings:
    Auto-negotiation will not complete if far end is also forced as a master.

******************************************************************************/
MTD_STATUS mtdAutonegForceMaster
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);

/******************************************************************************
 MTD_STATUS mtdAutonegForceSlave
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL anRestart
 );
                          

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Sets auto-negotiation to manual and forced as a slave.

    Restarts auto-negotiation by calling the function only if the input parameter 
    anRestart was selected. Also re-enables auto-negotiation before restarting 
    auto-negotiation.

 Side effects:
    Auto-negotiation has to be restarted for it to take effect

 Notes/Warnings:
    Auto-negotiation will not complete if far end is also forced as a slave.

******************************************************************************/
MTD_STATUS mtdAutonegForceSlave
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);


/******************************************************************************
 MTD_STATUS mtdAutonegSetAutoMasterSlave
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL anRestart
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Sets the master/slave determination to "auto" which means the 
    master/slave setting will be random from one auto-negotiation to the next 
    auto-negotiation.

    Restarts auto-negotiation by calling the function only if the input 
    parameter anRestart was selected. Also re-enables auto-negotiation before 
    restarting auto-negotiation.

 Side effects:
    Auto-negotiation has to be restarted for it to take effect

******************************************************************************/
MTD_STATUS mtdAutonegSetAutoMasterSlave
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);

/******************************************************************************
 MTD_STATUS mtdAutonegSetMasterPreference
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL anRestart
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Sets master/slave setting to "auto" and selects multi-port (preference is
    to be a master).

    Restarts auto-negotiation by calling the function only if the input parameter 
    anRestart was selected. Also re-enables auto-negotiation before restarting 
    auto-negotiation.

 Side effects:
    None

 Notes/Warnings:
     auto-negotiation has to be restarted for it to take effect


******************************************************************************/
MTD_STATUS mtdAutonegSetMasterPreference
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);

/******************************************************************************
 MTD_STATUS mtdAutonegSetSlavePreference
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL anRestart
 );
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).

                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Sets master/slave setting to "auto" and selects single-port (preference is
    to be a slave).

    Restarts auto-negotiation by calling the function only if the input 
    parameter anRestart was selected. Also re-enables auto-negotiation before 
    restarting auto-negotiation.

 Side effects:
    None

 Notes/Warnings:
    Auto-negotiation has to be restarted for it to take effect

******************************************************************************/
MTD_STATUS mtdAutonegSetSlavePreference
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL anRestart
);



#define MTD_AN_RESOLUTION_FAULT   (2) /* if a config fault was detected */
#define MTD_AN_RESOLUTION_MASTER  (1)
#define MTD_AN_RESOLUTION_SLAVE   (0)
#define MTD_AN_RESOLUTION_UNKNOWN (0xFF) /* During autonegotiation */
/******************************************************************************
 MTD_STATUS mtdAutonegIsResolutionMasterOrSlave
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U8 *anMsResolution
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    anMsResolution - one of the following
        MTD_AN_RESOLUTION_MASTER if the PHY is a MASTER and autoneg was resolved
        MTD_AN_RESOLUTION_SLAVE if the PHY is a SLAVE and autoneg was resolved        
        MTD_AN_RESOLUTION_UNKNOWN if it is not resolved yet
        MTD_AN_RESOLUTION_FAULT if a config fault is detected (for example, both
            sides forced to slave, etc.)

 Returns:
    MTD_OK or MTD_FAIL, if query was successful or not

 Description:
    The function checks if auto-negotiation speed is resolved by calling the
    mtdAutonegIsSpeedDuplexResolutionDone(). If speed/duplex is not resolved,
    it then checks for a config fault. If a config fault exists, it
    returns MTD_AN_RESOLUTION_FAULT for anMsResolution. If a config
    fault doesn't exist, it returns MTD_AN_RESOLUTION_UNKNOWN since
    AN is in progress.

    If AN is done (meaning duplex/speed is resolved AND autonegotiation
    is completed), the master/slave bit from the correct register either 7.33
    or 7.32769 is read and a value of AN_MTD_RESOLUTION_MASTER/SLAVE is returned 
    for anMsResolution.

    If AN is done but not completed (meaning speed/duplex are resolved,
    but the link has not trained up), AN_MTD_RESOLUTION_UNKNOWN is returned.
    Master/slave status bits are not valid until AN is complete (7.1.5 is 1).

 Side effects:
    Calling this function will clear the auto-negotiation config fault bit in
    register 7.33/32769 since it is a latched bit.

 Notes/Warnings:
    None

******************************************************************************/
MTD_STATUS mtdAutonegIsResolutionMasterOrSlave
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *anMsResolution
);


/******************************************************************************
 MTD_STATUS mtdGetAutonegSpeedDuplexResolution
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U16 *speedResolution
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs: 
    speedResolution - one of the following:
        MTD_ADV_NONE - autonegotiation is in progress or disabled
        MTD_SPEED_10M_HD - speed is resolved to 10BT half-duplex
        MTD_SPEED_10M_FD - speed is resolved to 10BT full-duplex
        MTD_SPEED_100M_HD - speed is resolved to 100BASE-TX half-duplex
        MTD_SPEED_100M_FD - speed is resolved to 100BASE-TX full-duplex
        MTD_SPEED_1GIG_HD - speed is resolved to 1000BASE-T half-duplex
        MTD_SPEED_1GIG_FD - speed is resolved to 1000BASE-T full-duplex
        MTD_SPEED_10GIG_FD - speed is resolved to 10GBASE-T    
        MTD_SPEED_2P5GIG_FD - speed is resolved to 2.5GBASE-T (88X33X0/88E20X0/88E21X0 family only)
        MTD_SPEED_5GIG_FD - speed is resolved to 5GBASE-T (88X33X0/88E20X0/88E21X0 family only)

  Returns: 
    MTD_OK or MTD_FAIL, if query was successful or not.

 Description:
    Checks if autonegoation is disabled, and if so, returns MTD_ADV_NONE.
    If autonegotiation is enabled, checks if autonegotiation speed/duplex is ready
    by calling mtdAutonegIsSpeedDuplexResolutionDone(), if not returns MTD_ADV_NONE,
    if it is ready, then it reads the speed and duplex resolution
    in 3.8008.15:13 and returns one of the values above based on these
    three bits.

    Speed/duplex being resolved does not imply autonegotiation is completed
    (that values in 7.1, 7.33, etc. are valid). Check autonegiation complete,
    mtdAutonegIsCompleted(), before reading any autonegotiation registers
    in MMD 7.

    This function returns and early indication of what speed and duplex has
    been autonegotiated and will attempt to train (or trained up if called 
    after the link is up).

 Side effects:
    None

 Notes/Warnings:
    If speed is forced to 100BASE-TX or 10BASE-T through register 1.0,
    this function should not be called. It may return incorrect results. 
    If the speed may be forced (meaning autonegotiation is disabled) to 
    one of these, first check if the speed is forced by calling 
    mtdGetForcedSpeed(). mtdGetAutonegSpeedDuplexResolution() is only to be used
    if autonegotiation is enabled.

    The value returned gives the result of autonegoation, but does not
    mean the copper link is up. It could be training or re-training. To
    check if the copper link is up and at what speed, call mtdIsBaseTUp().

******************************************************************************/
MTD_STATUS mtdGetAutonegSpeedDuplexResolution
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *speedResolution
);

/******************************************************************************
MTD_STATUS mtdIsBaseTUp(
    IN MTD_DEV_PTR devPtr,
    MTD_U16 port,
    MTD_U16 *speed,
    MTD_BOOL *linkUp
);
                                  

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    speed - which speed was resolved or will be resolved by auto-negotiation, 
            one of following
             MTD_ADV_NONE - autonegotiation is in progress or disabled
             MTD_SPEED_10M_HD - speed is resolved to 10BT half-duplex
             MTD_SPEED_10M_FD - speed is resolved to 10BT full-duplex
             MTD_SPEED_100M_HD - speed is resolved to 100BASE-TX half-duplex
             MTD_SPEED_100M_FD - speed is resolved to 100BASE-TX full-duplex
             MTD_SPEED_1GIG_HD - speed is resolved to 1000BASE-T half-duplex
             MTD_SPEED_1GIG_FD - speed is resolved to 1000BASE-T full-duplex
             MTD_SPEED_10GIG_FD - speed is resolved to 10GBASE-T  
             MTD_SPEED_2P5GIG_FD - speed is resolved to 2.5GBASE-T (88X33X0/88E20X0/88E21X0 family only)
             MTD_SPEED_5GIG_FD - speed is resolved to 5GBASE-T (88X33X0/88E20X0/88E21X0 family only)

             MTD_SPEED_10M_HD_AN_DIS - speed forced to 10BT half-duplex
             MTD_SPEED_10M_FD_AN_DIS - speed forced to 10BT full-duplex
             MTD_SPEED_100M_HD_AN_DIS - speed forced to 100BT half-duplex
             MTD_SPEED_100M_FD_AN_DIS - speed forced to 100BT full-duplex
             MTD_SPEED_MISMATCH - speed is forced to one of above speeds, but
                                  indicated up at a different speed (this is an error)
             
    linkUp - MTD_TRUE if the copper link is up at the speed above
             MTD_FALSE if the link is down or autonegotiation is in progress or
             there's an error

 Returns:
    MTD_OK, if query was successful, MTD_FAIL if query was unsuccessful or if there
    was an error such as MTD_SPEED_MISMATCH. MTD_OK indicates speed and link
    status are valid. MTD_FAIL indicates speed and link status are invalid.

 Description:

    First checks if the speed is forced to 10BT or 100BTX, and if it is returns
    one of the following combinations

    Speed Forced Value           Link Status    Status
    ------------------           -----------    ------
    MTD_SPEED_10M_HD_AN_DIS      MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    MTD_SPEED_10M_FD_AN_DIS      MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    MTD_SPEED_100M_HD_AN_DIS     MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    MTD_SPEED_100M_FD_AN_DIS     MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid 
    any of the above with        MTD_FALSE      MTD_FAIL - query failed

    MTD_SPEED_MISMATCH           MTD_FALSE      MTD_FAIL - link at different speed than forced value
                                                This is an error. Link may be up at wrong speed
                                                or training at wrong speed.

    If speed is not forced, then checks if autonegotation is resolved or in-progress and
    returns one of the following combinations:

    Autonegotation Result        Link Status    Status
    ---------------------        -----------    ------
    MTD_ADV_NONE                 MTD_FALSE      MTD_OK - autonegotiation is in progress (link is down)
    MTD_SPEED_10M_HD             MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    MTD_SPEED_10M_FD             MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    MTD_SPEED_100M_HD            MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    MTD_SPEED_100M_FD            MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    MTD_SPEED_1GIG_HD            MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid 
    MTD_SPEED_1GIG_FD            MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid 
    MTD_SPEED_10GIG_FD           MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    MTD_SPEED_2P5GIG_FD          MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    MTD_SPEED_5GIG_FD            MTD_TRUE/FALSE MTD_OK - query successful, link status/speed valid
    
    any of the above with        MTD_FALSE      MTD_FAIL - query failed

 Side effects:
    None

 Notes/Warnings:
    Gives current real-time status of the copper interface.
******************************************************************************/
MTD_STATUS mtdIsBaseTUp(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *speed,
    OUT MTD_BOOL *linkUp
);

#define MTD_FORCE_MDI        0x00
#define MTD_FORCE_MDIX       0x01
/* 0x02 is reserved */
#define MTD_AUTO_MDI_MDIX    0x03
/*****************************************************************************
MTD_STATUS mtdMDIXControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 MDIXOptions, 
    IN MTD_BOOL swReset
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    MDIXOptions - 0x00 - MTD_FORCE_MDI
                  0x01 - MTD_FORCE_MDIX
                  0x03 - MTD_AUTO_MDI_MDIX
    swReset - MTD_TRUE is to do a software reset
              MTD_FALSE is not to do a software reset, it should
              be done later for the change to take effect
 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    The function forces the MDI/MDI-X or sets it to auto MDI/MDI-X based on the
    input. Optionally the software reset is issued following the change (this
    change requires a software reset to take effect).

 Side effects:
    None

 Notes/Warnings:
    Following changes to MDI/MDI-X, a software reset must be performed to
    restart the state machine. This will drop the link. If swReset is set to
    MTD_FALSE, it must be done later to make change become active.

    Following a software reset, the PHY should be polled looking for the
    software reset to be completed before interacting with the PHY via any
    other MDIO registers by polling mtdIsPhyReadyAfterReset().
******************************************************************************/
MTD_STATUS mtdMDIXControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 MDIXOptions, 
    IN MTD_BOOL swReset
);


/*****************************************************************************
MTD_STATUS mtdGetMDIXControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *MDIXOptions,
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    MDIXOptions - 0x00 - MTD_FORCE_MDI
                  0x01 - MTD_FORCE_MDIX
                  0x03 - MTD_AUTO_MDI_MDIX

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    The function queries the current setting of the MDIX control
    bits.

    NOTE: The current value of the register bits are returned.
    These bits only become valid following a software reset. If
    the register was changed, but no software reset was issued,
    the new value will be returned but won't have taken effect
    yet.

 Side effects:
    None

 Notes/Warnings:
    Following changes to MDI/MDI-X, a software reset must be performed to
    restart the state machine. This will drop the link. If swReset is set to
    MTD_FALSE, it must be done later to make change become active.

    Following a software reset, the PHY should be polled looking for the
    software reset to be completed before interacting with the PHY via any
    other MDIO registers by polling mtdIsPhyReadyAfterReset().
******************************************************************************/
MTD_STATUS mtdGetMDIXControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *MDIXOptions
);

#define MTD_MDI_RESOLVED           0x00
#define MTD_MDIX_RESOLVED          0x01
#define MTD_MDI_MDIX_NOT_RESOLVED  0x02
/*****************************************************************************
 MTD_STATUS mtdGetMDIXResolution
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     OUT MTD_U8 *MDIX
 );


 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

 Outputs:
    MDIX - MTD_MDIX_RESOLVED means AN resolved to MDIX (local device transmitting on pair
           B and receiving on pair A)
           MTD_MDI_RESOLVED means AN resolved to MDI (local device transmitting on pair
           A and receiving on pair B)
           MTD_MDI_MDIX_NOT_RESOLVED means resolution is not ready yet (link could
           be unplugged, or AN could be in progress but not to the point of reporting this)

 Returns:
    MTD_OK or MTD_FAIL, if query was successful or not

 Description:
    Checks if speed/duplex has been resolved (3.8008.11 is 1). If it has not,
    returns MTD_MDI_MDIX_NOT_RESOLVED.

    If speed/duplex has been resolved, reads the MDI/MDI-X resolution in
    3.8008.6 and returns the value in MDIX along with MTD_OK for the return
    status.

 Side effects:
    None

 Notes/Warnings:
    This function checks for MDI/MDI-X setting in the vendor specific register
    3.8008. For 10GBASE-T, there is also an IEEE defined bit field in 1.130.1:0
    which can be checked once the 10GBASE-T link is up. However, that bit field
    is only valid in 10GBASE-T operation. 3.8008.6 is valid for all speeds
    where MDI/MDI-X is relevant (100BT, 1000BT, 10GBT).
******************************************************************************/
MTD_STATUS mtdGetMDIXResolution
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U8 *MDIX
);


/******************************************************************************
 MTD_STATUS mtdAutonegSetNbaseTAdvertisement
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL enableNbaseTMP,
     IN MTD_BOOL anRestart
 );
 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    enableNbaseTMP - set to MTD_TRUE to enable sending the NBASE-T message page
                     or set to MTD_FALSE to disable sending the NBASE-T message
                     page
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the change. 
                If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).

                MTD_TRUE will both enable AN and restart it.

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Either enables sending the NBASE-T OUI Message Page or disables it
    When enabled, will use the speed control bits in 7.32 to advertise support
    of 2.5G or 5G NBASE-T for interoperability with 2.5/5G NBASE-T
    only devices.

    If disabled, will not send the NBASE-T Message Page and will not
    interoperate with devices which only support NBASE-T 2.5/5G.

 Side effects:
    None

 Notes/Warnings:
    Auto-negotiation has to be restarted for it to take effect

******************************************************************************/
MTD_STATUS mtdAutonegSetNbaseTAdvertisement
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL enableNbaseTMP,
    IN MTD_BOOL anRestart
);


/******************************************************************************
 MTD_STATUS mtdAutonegSetNbaseTDownshiftControl
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 downshiftThreshold,
     IN MTD_BOOL noEnergyReset,
     IN MTD_BOOL downshiftEnable
 );

 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31

    downShiftThreshold - 0...15, threshold of number of failed training
        attempts before downshifting to next lower enabled speed.

    NOTE: setting threshold to 0 disables downshift

    noEnergyReset - MTD_TRUE to re-enable all speeds when no energy
    is detected on MDI. MTD_FALSE to disable this feature.

    downshiftEnable - MTD_TRUE to enable downshift. MTD_FALSE
        to disable downshift. (setting threshold to 0 overrides this,
        see above)

    anRestart - MTD_TRUE to restart AN after upating register. MTD_FALSE
        to not restart AN (do it later to have changes take effect).
    

 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Sets the control bits for the downshift control register.

    Changes don't take effect until AN is restarted.
    

 Side effects:
    None

 Notes/Warnings:
    This feature is only available on 88X33x0/E20x0/E21x0 devices.

******************************************************************************/
MTD_STATUS mtdAutonegSetNbaseTDownshiftControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 downshiftThreshold,
    IN MTD_BOOL noEnergyReset,
    IN MTD_BOOL downshiftEnable,
    IN MTD_BOOL anRestart
);

/******************************************************************************
 MTD_STATUS mtdAutonegGetNbaseTDownshiftControl
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U16 *downshiftThreshold,
     IN MTD_BOOL *noEnergyReset,
     IN MTD_BOOL *downshiftEnable
 );

 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
 Outputs:
    downShiftThreshold - 0...15, threshold of number of failed training
        attempts before downshifting to next lower enabled speed.

    noEnergyReset - MTD_TRUE to re-enable all speeds when no energy
        is detected on MDI. MTD_FALSE to disable this feature.

    downshiftEnable - MTD_TRUE to enable downshift. MTD_FALSE
        to disable downshift.

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Reads the control bits for the downshift control register.
    

 Side effects:
    None

 Notes/Warnings:
    This feature is only available on 88X33x0/E20x0/E21x0 devices.

******************************************************************************/
MTD_STATUS mtdAutonegGetNbaseTDownshiftControl
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 *downshiftThreshold,
    IN MTD_BOOL *noEnergyReset,
    IN MTD_BOOL *downshiftEnable
);

/******************************************************************************
 MTD_STATUS mtdAutonegGetNbaseTDownshiftStatus
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL *downshiftFrom10G,
     IN MTD_BOOL *downshiftFrom5G,
     IN MTD_BOOL *downshiftFrom2P5G,
     IN MTD_BOOL *downshiftFrom1G,
     IN MTD_U16 *downshiftCount
 );

 
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    
 Outputs:
    downshiftFrom10G- MTD_TRUE if downshifted to lower speed from 10G
    downshiftFrom5G - MTD_TRUE if downshifted to lower speed from 5G
    downshiftFrom2P5G - MTD_TRUE if downshifted to lower speed from 2.5G
    downshiftFrom1G - MTD_TRUE if downshifted to lower speed from 1G
    downshiftCount - Number of link attempts at the current advertised
        speed.

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    Reads the status from the downshift status register.
    

 Side effects:
    None

 Notes/Warnings:
    This feature is only available on 88X33x0/E20x0/E21x0 devices.

******************************************************************************/
MTD_STATUS mtdAutonegGetNbaseTDownshiftStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL *downshiftFrom10G,
    IN MTD_BOOL *downshiftFrom5G,
    IN MTD_BOOL *downshiftFrom2P5G,
    IN MTD_BOOL *downshiftFrom1G,
    IN MTD_U16 *downshiftCount
);




/******************************************************************************
 MTD_STATUS mtdControlEmiCanceller
 (
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_BOOL enableCanceller.
     IN MTD_BOOL anRestart
 );

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    enableCanceller - MTD_TRUE to enable it, MTD_FALSE to disable it
    anRestart - this takes the value of MTD_TRUE or MTD_FALSE and indicates 
                if auto-negotiation should be restarted following the speed 
                enable change. If this is MTD_FALSE, the change will not
                take effect until AN is restarted in some other way (link
                drop, toggle low power, toggle AN enable, toggle soft reset).
    
                If this is MTD_TRUE and AN has been disabled, it will be
                enabled before being restarted.                
 Outputs:
    None

 Returns:
    MTD_OK or MTD_FAIL, if action was successful or not

 Description:
    This function enables or disables the EMI Canceller Mode.
    
 Side effects:
    None. 
    
 Notes/Warnings:. 
    The EMI Canceller is enabled by default. If the link is up, it must be
    dropped/retrained for the change to take effect. Set the flag anRestart
    to MTD_TRUE to drop the link and have the change take effect.

******************************************************************************/
MTD_STATUS mtdControlEmiCanceller
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_BOOL enableCanceller,
    IN MTD_BOOL anRestart
);

                                
#if C_LINKAGE
#if defined __cplusplus 
}
#endif 
#endif

#endif /* defined MTD_API_H */

