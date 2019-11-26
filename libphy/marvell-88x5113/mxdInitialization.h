/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mxdInitialization.h
*
* DESCRIPTION:
*       API Prototypes for Marvell X5113 Device for initializing the driver.
*
* DEPENDENCIES:
*
* FILE REVISION NUMBER:
*
*******************************************************************************/

#ifndef MXDINITIALIZATION_H
#define MXDINITIALIZATION_H

#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

/*******************************************************************************
 MXD_STATUS mxdInitDriver
 (
    IN FMXD_READ_MDIO  readMdio,
    IN FMXD_WRITE_MDIO writeMdio,
    IN MXD_U16         mdioPort,
    IN MXD_U16         *pZ80Image,
    IN MXD_U16         z80Size,
    IN MXD_U16         *pBusMasterImage,
    IN MXD_U16         busMasterSize,
    IN MXD_U16         *pSerdesImage,
    IN MXD_U16         serdesSize,
    IN MXD_PVOID       pHostContext,
    OUT MXD_DEV_PTR    pDev
 );

 Inputs:
   readMdio - pointer to host's function to do MDIO read
   writeMdio - point to host's function to do MDIO write
   mdioPort - MDIO port address on this device
   pZ80Image - input buffer image of the Z80 firmware           :optional input
   z80Size   - Z80 firmware image size                          :optional input
   pBusMasterImage - input buffer image of the SBUS Master      :optional input
   busMasterSize - SBUS Master image size                       :optional input
   pSerdesImage - input buffer image of the SERDES              :optional input
   serdesSize - SERDES image size                               :optional input
   pHostContext - user specific data for host to pass to the low layer  :optional input

 Outputs:
       pDev  - pointer to holds device information to be used for each API call.

 Returns:
       MXD_OK               - on success
       MXD_FAIL             - on error

 Description:
   Marvell X5113 Driver Initialization Routine.
   This is the first routine that needs be called by system software.
   It takes parameters from system software, and returns a pointer (*dev)
   to a data structure which includes infomation related to this Marvell PHY
   device. This pointer (*dev) is then used for all the API functions.
   The following is the job performed by this routine:
       1. store MDIO read/write function into the given MXD_DEV structure
       2. run any device specific initialization routine (chip hardware reset,
          firmware download, etc.)
       3. Initialize the deviceId and revision information

 Side effects:
   None

 Notes/Warnings:
   An MXD_DEV is required for each of Marvell X5113 device in the system. 
   For example, if there are two X5113 devices, two MXD_DEV are required.   

   The download will only be executed if both Serdes and SBus images are 
   provided or all 3 images including the Z80. If the combination is not 
   provided, this function will skip the firmware images download. 
   However, it will continue with the rest of the driver initialization.   

   The Z80 firmware file image used in the mxdInitDriver function has a 
   different format as the Z80 image used in EEPROM programming. The EEPROM
   Z80 file format has 1 byte on each line. Whereas, the mxdInitDriver Z80 
   file format has 2 bytes on each line.
   
   The Z80 firmware file image is optional and not needed in some chip revision.
   If this image is not available, setting the z80Size to 0 will by-pass the
   Z80 firmware download.

   The firmware may be loaded into the device from an EEPROM or the host 
   may load firmware into the device by providing the image to mxdInitDriver. 
   The table below shows the behavior of firmware loading depending upon the 
   device configuration and whether a firmware image is passed into 
   mxdInitDriver.

    Firmware   F/W from     
    passed-in  previous
    init drv   init drv     Expected Behavior
    ----------------------------------------------------------------------
    No         No           Use EEPROM image
    No         Yes*         Use previously loaded image
    Yes        No           Use passed-in image
    Yes        Yes*         Use passed-in image

    (*) driver reloads without power-down or hardware reset

*******************************************************************************/
MXD_STATUS mxdInitDriver
(
    IN FMXD_READ_MDIO  readMdio,
    IN FMXD_WRITE_MDIO writeMdio,
    IN MXD_U16         mdioPort,
    IN MXD_U16         *pZ80Image,
    IN MXD_U16         z80Size,
    IN MXD_U16         *pBusMasterImage,
    IN MXD_U16         busMasterSize,
    IN MXD_U16         *pSerdesImage,
    IN MXD_U16         serdesSize,
    IN MXD_PVOID       pHostContext,
    OUT MXD_DEV_PTR    pDev
);


/*******************************************************************
MXD_STATUS mxdUnloadDriver
(
    IN MXD_DEV_PTR pDev
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.

 Outputs:
   None

 Returns:
   MXD_OK    - on success
   MXD_FAIL  - on error

 Description:
   This function performs the clean-up task in releasing the Serdes 
   memory structure, resetting the dev structure and other clean-up 
   operations.

 Side effects:
   None

 Notes/Warnings:
   The mxdUnloadDriver() will not handle the hostContext clean-up
   operations. If the hostContext is used, it should either be freed before 
   calling this API or track the hostContext pointer and freed it after 
   calling this API. The mxdUnloadDriver() will zero-out the dev structure
   after completion.
*******************************************************************/
MXD_STATUS mxdUnloadDriver
(
    IN MXD_DEV_PTR pDev
);


/*******************************************************************
MXD_STATUS mxdPortReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_RESET_TYPE resetType,
    IN MXD_U16 timeoutMs
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.
   mdioPort - MDIO port address, 0-31
   host_or_line - which interface is being modified:
        MXD_HOST_SIDE
        MXD_LINE_SIDE
        MXD_BOTH_SIDE
   resetType - option for Hard or Soft port reset
        MXD_SOFT_RESET
        MXD_HARD_RESET
   timeoutMs - reset timeout in ms

 Outputs:
   None

 Returns:
   MXD_OK               - on success
   MXD_FAIL             - on error

 Description:
   This function performs a port level hardware or software reset.

 Side effects:
   None

 Notes/Warnings:
*******************************************************************/
MXD_STATUS mxdPortReset
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 host_or_line,
    IN MXD_RESET_TYPE resetType,
    IN MXD_U16 timeoutMs
);

#define MXD_CHIP_SW_RESET     (1<<15) /* This reset self clears */
#define MXD_CHIP_HW_RESET     (1<<14) /* This reset self clears, can be combined with MXD_Z80_RESET */
#define MXD_Z80_RESET         (1<<13) /* Will leave Z80 in reset, does not self clear */
#define MXD_Z80_RESET_RELEASE 0

/*******************************************************************
MXD_STATUS mxdChipAndZ80ResetControl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 resetType,
    IN MXD_BOOL bRestore
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.
   resetType - From the following list
    MXD_CHIP_SW_RESET
         or
    MXD_CHIP_HW_RESET (optionally | with MXD_Z80_RESET to reset both)
    MXD_Z80_RESET (optionally | with MXD_CHIP_HW_RESET to reset both)
         or
    MXD_Z80_RESET_RELEASE (following MXD_Z80_RESET to take the Z80 out of reset)    
        
   bRestore - restore saved registers on power-on default 

 Outputs:
   None

 Returns:
   MXD_OK               - on success
   MXD_FAIL             - on error

 Description:
   If the option is MXD_CHIP_SW_RESET, does a chip-level software reset
   (this bit self clears).

   If the option is MXD_CHIP_HW_RESET, does a chip-level hardware reset
   (this bit self clears)

   MXD_CHIP_HW_RESET | MXD_Z80_RESET, will do a chip-level and also
   reset the Z80 leaving the Z80 in reset when this function exits. Call
   with MXD_Z80_RESET_RELEASE to take the Z80 out of reset.

   MXD_Z80_RESET, does a Z80 reset, leaving the Z80 in reset. Call
   with MXD_Z80_RESET_RELEASE to take the Z80 out of reset.

 Side effects:
   None

 Notes/Warnings:
   After a hardware reset is issued to the device, it requires a few
   seconds for recovery before performing further operations. Otherwise, 
   the operation may fail with an unexpected error.
    
*******************************************************************/
MXD_STATUS mxdChipAndZ80ResetControl
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 resetType,
    IN MXD_BOOL bRestore
);


#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* MXDINITIALIZATION_H */
