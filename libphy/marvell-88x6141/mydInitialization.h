/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions for initializing the driver, setting up 
the user-provide MDIO access functions, chip reset and various driver
initialization operations for the Marvell X7120/X6181/X6141 Device.
********************************************************************/

#ifndef MYDINITIALIZATION_H
#define MYDINITIALIZATION_H

#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

#define MYD_HW_RESET_WAITTIME 1500  /* 1.5 sec max wait time after a hardware reset */

#define MYD_PORT_SW_RESET     (1<<15) /* Port software reset; this reset self clears */
#define MYD_PORT_HW_RESET     (1<<14) /* Port hardware reset; this reset self clears;
                                         can be combined with MYD_Z80_RESET */
#define MYD_CHIP_SW_RESET     (1<<15) /* Chip software reset; this reset self clears */
#define MYD_CHIP_HW_RESET     (1<<14) /* Chip hardware reset; this reset self clears; 
                                         can be combined with MYD_Z80_RESET */
#define MYD_Z80_RESET         (1<<13) /* Will leave Z80 in reset, does not self clear */
#define MYD_Z80_RESET_RELEASE 0


/*******************************************************************************
 MYD_STATUS mydInitDriver
 (
    IN FMYD_READ_MDIO  readMdio,
    IN FMYD_WRITE_MDIO writeMdio,
    IN MYD_U16         mdioPort,
    IN MYD_U16         *pZ80Image,
    IN MYD_U16         z80Size,
    IN MYD_U16         *pBusMasterImage,
    IN MYD_U16         busMasterSize,
    IN MYD_U16         *pSerdesImage,
    IN MYD_U16         serdesSize,
    IN MYD_PVOID       pHostContext,
    INOUT MYD_DEV_PTR  pDev
 );

 Inputs:
   readMdio - pointer to host's function to do MDIO read
   writeMdio - point to host's function to do MDIO write
   mdioPort - 1st MDIO port address on this device
   pZ80Image - input buffer image of the Z80 firmware       :optional input
   z80Size   - Z80 firmware image size                      :optional input
   pBusMasterImage - input buffer image of the SBUS Master  :optional input
   busMasterSize - SBUS Master image size               :optional input
   pSerdesImage - input buffer image of the SERDES      :optional input
   serdesSize - SERDES image size                       :optional input
   pHostContext - user specific data for host to pass to the low layer  :optional input

 Outputs:
   pDev  - memory allocated for this pointer to holds device information to be used 
           for API call.

 Returns:
   MYD_OK    - on success
   MYD_FAIL  - on error

 Description:
   Marvell X7120/X6181/X6141 Driver Initialization Routine.
   This is the first routine that needs be called by system software.
   It takes parameters from system software, and returns a pointer (*dev)
   to a data structure which includes information related to this Marvell PHY
   device. This pointer (*dev) is then used for all the API functions.
   The following is the job performed by this routine:
       1. store MDIO read/write function into the given MYD_DEV structure
       2. run any device specific initialization routine (chip hardware reset,
          firmware download, etc.)
       3. Initialize the deviceId and revision information

   The firmware download will use the broadcast mode using the default 
   MYD_FW_WRITE_VERIFIED option, which is disabled. Broadcast write mode can  
   only work when write verify is disabled. 

 Side effects:
   None

 Notes/Warnings:
   The devEEPROM in the device structure is defaulted to MYD_FALSE. If the EEPROM is
   available and used in the device, set devEEPROM to MYD_TRUE. Setting the devEEPROM
   to MYD_TRUE will allow more time for the EEPROM image to load to the RAM after a 
   hardware reset. The devEEPROM will be set if mydLoadEEPROMImageToRAM is called.

   An MYD_DEV is required for each of Marvell X7120/X6181/X6141 device in the system. 
   For example, if there are two X7120 devices, two MYD_DEV are required.   

   The download will only be executed if both Serdes and SBus images are 
   provided or all 3 images including the Z80. If the combination is not 
   provided, this function will skip the firmware images download. 
   However, it will continue with the rest of the driver initialization.   

   The Z80 firmware file image used in the mydInitDriver function has a 
   different format as the Z80 image used in EEPROM programming. The EEPROM
   Z80 file format has 1 byte on each line. Whereas, the mydInitDriver Z80 
   file format has 2 bytes on each line.
   
   The Z80 firmware file image is optional and not needed in some chip revision.
   If this image is not available, setting the z80Size to 0 will by-pass the
   Z80 firmware download.

   There are 2 ways to load the firmware into the device. The host may load 
   firmware into the device by providing the image to mydInitDriver or load 
   from an EEPROM. 

   When device is power-up or after a hardware reset, the firmware will be 
   loaded from the EEPROM(if available). If firmware images are passed-in 
   from the mydInitDriver, it will update using the passed-in images.

   The table below shows the behavior of loading firmware:

   Firmware   F/W from     
   passed-in  previous
   init drv   init drv     Expected Behavior
   ----------------------------------------------------------------------
   No         No           Loads EEPROM image if available; else no firmware loaded
   No         Yes*         Use previously loaded image
   Yes        No           Use passed-in image
   Yes        Yes*         Use passed-in image

   (*) driver reloads without power-down or hardware reset

*******************************************************************************/
MYD_STATUS mydInitDriver
(
    IN FMYD_READ_MDIO  readMdio,
    IN FMYD_WRITE_MDIO writeMdio,
    IN MYD_U16         mdioPort,
    IN MYD_U16         *pZ80Image,
    IN MYD_U16         z80Size,
    IN MYD_U16         *pBusMasterImage,
    IN MYD_U16         busMasterSize,
    IN MYD_U16         *pSerdesImage,
    IN MYD_U16         serdesSize,
    IN MYD_PVOID       pHostContext,
    INOUT MYD_DEV_PTR  pDev
);

/* optionFlag use for reloading the driver mydReloadDriver() */
#define MYD_RELOAD_CONFIG (1<<0)  /* Bit 0: if set to 1, it reads the mode registers to 
                                            re-fill the mode configuration */
                                  /* Bit 1-15: reserved for future used */

/*******************************************************************************
MYD_STATUS mydReloadDriver
(
    IN FMYD_READ_MDIO  readMdio,
    IN FMYD_WRITE_MDIO writeMdio,
    IN MYD_U16         mdioPort,
    IN MYD_PVOID       pHostContext,
    IN MYD_U16         optionFlag,
    OUT MYD_DEV_PTR    pDev
);

 Inputs:
   readMdio - pointer to host's function to do MDIO read
   writeMdio - point to host's function to do MDIO write
   mdioPort - 1st MDIO port address on this device
   pHostContext - user specific data for host to pass to the low layer  :optional input
   optionFlag - option available when reloading the driver. Refer to the MYD_RELOAD_xxx
                definition for options.

 Outputs:
   pDev  - memory allocated for this pointer to holds device information to be used 
           for API call.

 Returns:
   MYD_OK   - on success
   MYD_FAIL - on error

 Description:
   This API reads the mode register of all lanes and re-filled the device structure MYD_DEV
   with the existing configured mode on all the lanes on both the host and line interfaces.  

   This driver reloads do not perform resets or firmware download to the device.  

   This call will not keep track of the previously configured states, i.e. loopbacks, 
   polarity changes, etc...

   This reload driver API can be used when the driver was previous unloaded.  The reload 
   driver will preserve the exiting configured modes and continue with the existing 
   operations without disruption to the configuration. 

   If the SerDes API is enabled, this call will initialize and re-allocate the SerDes 
   structure memory.  

 Side effects:
   Any state change will *not* be tracked in the driver reloads.

 Notes/Warnings:
   The mydReloadDriver will not keep track of the previously configured states, 
   i.e. loopbacks, polarity changes, etc...  The client application will need to re-query 
   and track any state change.  
     
   The mydReloadDriver reads back the mode registers for all lanes.  However, if an 
   existing mode is switched to another mode with a smaller lane count, the may be stale 
   info in the mode registers.  The read back the Repeater MYD_R400U and MYD_R200L on 
   reloading the device structure will report back as MYD_R50U on all 8 lanes for MYD_R400U 
   and MYD_R25L for MYD_R200L respectively.

*******************************************************************************/
MYD_STATUS mydReloadDriver
(
    IN FMYD_READ_MDIO  readMdio,
    IN FMYD_WRITE_MDIO writeMdio,
    IN MYD_U16         mdioPort,
    IN MYD_PVOID       pHostContext,
    IN MYD_U16         optionFlag,
    OUT MYD_DEV_PTR    pDev
);


/*******************************************************************
MYD_STATUS mydUnloadDriver
(
    IN MYD_DEV_PTR pDev
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.

 Outputs:
   None

 Returns:
   MYD_OK    - on success
   MYD_FAIL  - on error

 Description:
   This function performs the clean-up task in releasing the Serdes 
   memory structure, resetting the dev structure and other clean-up 
   operations.

 Side effects:
   None

 Notes/Warnings:
   The mydUnloadDriver() will not handle the hostContext clean-up
   operations. If the hostContext is used, it should either be freed before 
   calling this API or track the hostContext pointer and freed it after 
   calling this API. The mydUnloadDriver() will zero-out the dev structure
   after completion.
*******************************************************************/
MYD_STATUS mydUnloadDriver
(
    IN MYD_DEV_PTR pDev
);


/*******************************************************************
MYD_STATUS mydLanePowerdown
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.
   
   mdioPort - MDIO port address, 0-31
   
   host_or_line - which interface is being power-down:
        MYD_HOST_SIDE
        MYD_LINE_SIDE
        MYD_BOTH_SIDE
        
   laneOffset - lane number to power down 0-3 or MYD_ALL_LANES to
                 power-down all lanes
   
 Outputs:
   None

 Returns:
   MYD_OK    - on success
   MYD_FAIL  - on error

 Description:
   This function performs power-down on a specific lane or all lanes
   on a given interface. 

   For multi-lane modes, you only need to power down the first lane
   to power-down that mode. However, it shouldn't hurt to power-down
   all lanes on that mode. 

 Side effects:
   None

 Notes/Warnings:
    None
    
*******************************************************************/
MYD_STATUS mydLanePowerdown
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
);


/*******************************************************************
MYD_STATUS mydLanePowerup
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.
   
   mdioPort - MDIO port address, 0-31
   
   host_or_line - which interface is being power-up:
        MYD_HOST_SIDE
        MYD_LINE_SIDE
        MYD_BOTH_SIDE
        
   laneOffset - lane number to power up 0-3 or MYD_ALL_LANES to
                 power up all lanes
   
 Outputs:
   None

 Returns:
   MYD_OK    - on success
   MYD_FAIL  - on error

 Description:
   This function performs power-up on a specific lane or all lanes
   on a given interface. 

   If you pass MYD_ALL_LANES, the function will only power up
   all the lanes assigned to modes on that port. It will figure
   out the first lane of each multi-lane mode and power that
   lane up and skip lanes that shouldn't be power up.

   If you pass a specific lane and it is not the first lane
   of a multi-lane mode, that lane will not be powered up and an
   error message will be returned.

 Side effects:
   None

 Notes/Warnings:
   For multi-lane modes, only the first lane assigned should be
   powered up.
    
*******************************************************************/
MYD_STATUS mydLanePowerup
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_U16 laneOffset
);


/*******************************************************************
MYD_STATUS mydPortReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_RESET_TYPE resetType,
    IN MYD_U16 timeoutMs
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.
   mdioPort - MDIO port address, 0-31
   host_or_line - which interface is being modified:
        MYD_HOST_SIDE
        MYD_LINE_SIDE
        MYD_BOTH_SIDE
   resetType - option for Hard or Soft port reset
        MYD_SOFT_RESET
        MYD_HARD_RESET
   timeoutMs - reset timeout in ms

 Outputs:
   None

 Returns:
   MYD_OK    - on success
   MYD_FAIL  - on error

 Description:
   This function performs a port level hardware or software reset.

 Side effects:
   None

 Notes/Warnings:
*******************************************************************/
MYD_STATUS mydPortReset
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 host_or_line,
    IN MYD_RESET_TYPE resetType,
    IN MYD_U16 timeoutMs
);


/*******************************************************************
MYD_STATUS mydChipAndZ80ResetControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 resetType,
    IN MYD_BOOL bRestore
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.
   resetType - From the following list
    MYD_CHIP_SW_RESET - software reset on all ports
    MYD_CHIP_HW_RESET - hardware reset on all ports
    MYD_Z80_RESET - reset the Z80 processor
    MYD_Z80_RESET_RELEASE - release the reset on the Z80 processor   
    Note:
    (MYD_CHIP_HW_RESET | MYD_Z80_RESET) can be combined on a single call

   bRestore - restore saved registers on power-on default 

 Outputs:
   None

 Returns:
   MYD_OK               - on success
   MYD_FAIL             - on error

 Description:
   This API performs reset on the entire chip.  It issues the resets to all 
   ports on the device. 

   The MYD_CHIP_SW_RESET will issue software reset on all ports
   (this bit self clears).

   The MYD_CHIP_HW_RESET will issue hardware reset on all ports
   (this bit self clears)

   MYD_CHIP_HW_RESET | MYD_Z80_RESET, will issue hardware reset 
   and Z80 reset on all ports. The Z80 will stay in the reset state
   until the MYD_Z80_RESET_RELEASE is called to take the Z80 out of 
   reset.

 Side effects:
   None

 Notes/Warnings:
   After a hardware reset is issued to the device, it requires a few
   seconds for recovery before performing further operations. Otherwise, 
   the operation may fail with an unexpected error.

   After issuing a hardware reset(MYD_CHIP_HW_RESET), it is recommended 
   to re-initialize the API by calling the mydInitDriver().

   The hardware reset(MYD_CHIP_HW_RESET) will load the EEPROM image(if available).
   It is recommended to re-initialize the API by calling the mydInitDriver() after 
   hardware reset. If a different firmware version is required, it will be loaded when
   provided in mydInitDriver().

   Note: The physical power-up defaults the EEPROM image to load. The hardware 
   reset(31.F404:14) will not reset the EEPROM to default behavior. The 
   mydChipAndZ80ResetControl() API will reset the EEPROM to default setting 
   when issuing the hardware reset to the entire chip. This will load the 
   EEPROM image, if available.
*******************************************************************/
MYD_STATUS mydChipAndZ80ResetControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 resetType,
    IN MYD_BOOL bRestore
);

/*******************************************************************
MYD_STATUS mydPortAndZ80ResetControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 resetType,
    IN MYD_BOOL bRestore
);

 Inputs:
   pDev  - pointer to holds device information to be used for each API call.
   mdioPort - MDIO port address, 0-31
   resetType - From the following list
    MYD_PORT_SW_RESET - software reset on a single port
    MYD_PORT_HW_RESET - hardware reset on a single port
    MYD_Z80_RESET - reset the Z80 processor
    MYD_Z80_RESET_RELEASE - release the reset on the Z80 processor   
    Note:
    (MYD_CHIP_HW_RESET | MYD_Z80_RESET) can be combined on a single call

   bRestore - restore saved registers on power-on default 

 Outputs:
   None

 Returns:
   MYD_OK    - on success
   MYD_FAIL  - on error

 Description:
   This API performs the reset on a single port based on the provided
   reset type.  

   The MYD_PORT_SW_RESET will issue software reset on a single port
   (this bit self clears).

   The MYD_PORT_HW_RESET will issue hardware reset on a single port
   (this bit self clears)

   MYD_PORT_HW_RESET | MYD_Z80_RESET, will issue hardware reset 
   and Z80 reset on a single port. The Z80 will stay in the reset state
   until the MYD_Z80_RESET_RELEASE is called to take the Z80 out of 
   reset.

 Side effects:
   None

 Notes/Warnings:
   After a hardware reset is issued to the port, it requires a few
   seconds for recovery before performing further operations. Otherwise, 
   the operation may fail with an unexpected error.

   It is recommended to use the mydChipAndZ80ResetControl() for issuing 
   hardware reset. This mydPortAndZ80ResetControl() API issues hardware 
   reset to a single port and will require further handling on a multi-port 
   device. Refer to more details in the datasheet on hardware reset

   When issuing the hardware reset(MYD_PORT_HW_RESET), it is recommended  
   to use the mydChipAndZ80ResetControl(), which resets all ports on a 
   multi-port device.  
*******************************************************************/
MYD_STATUS mydPortAndZ80ResetControl
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 resetType,
    IN MYD_BOOL bRestore
);



#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* MYDINITIALIZATION_H */
