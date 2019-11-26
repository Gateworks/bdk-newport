/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions using MDIO access to download firmware
into the internal RAM or attached flash memory of the Marvell 
X7120/X6181/X6141 PHYs.
********************************************************************/
#ifndef MYDDL_H
#define MYDDL_H

#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif

/* Firmware and EEPROM error codes */
#define MYD_FW_CRC_CHECKSUM_ERROR           0xA0 /*CRC checksum error*/
#define MYD_FW_FAIL_WRITE_REG               0xA1 /*Error access register*/
#define MYD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR  0xA2 /*Unknown download EEPROM error*/
#define MYD_FW_IMAGE_TOO_LARGE_TO_DOWNLOAD  0xA3 /*Image larger than the target device's memory*/
#define MYD_FW_INVALID_IMAGE_SIZE           0xA4 /*Invalid image size*/
#define MYD_FW_IMAGE_MISMATCHED             0xA5 /*Read back image mismatched */


/******************************************************************************
 MYD_STATUS mydLoadSBusSerdesFW
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 imageSize,
    IN MYD_U16 image[],
    OUT MYD_U16 *errCode
);
                                  
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - file size 
    image[] - application code to be downloaded in to the flash

 Outputs:
    errCode - if return status is MYD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:

        MYD_STATUS_CRC_CHECKSUM_ERROR - RAM checksum register bad checksum          
        MYD_STATUS_FAIL_WRITE_REG - Error writing to register      
                  
 Returns:
    MYD_OK if successful, MYD_FAIL if an error was detected

 Description:
    This function download the Serdes firmware image to the chip. The input 
    file image is read in as a string of 10bit hex value. This function will 
    packed the 10bit into 32bit value and load them into the Serdes. After 
    the image load completed, the CRC will be checked for correctness.

 Side effects:
    None

 Notes/Warnings:
    Do not run any process to access the mdioPort while the firmware download is 
    in process. 

 Example:
    Refer to the sample API mydSampleLoadImageFile() on loading the image file

 *****************************************************************************/
MYD_STATUS mydLoadSBusSerdesFW
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 imageSize,
    IN MYD_U16 image[],
    OUT MYD_U16 *errCode
);


/******************************************************************************
 MYD_STATUS mydLoadSBusMasterFW
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 imageSize,
    IN MYD_U16 image[],
    OUT MYD_U16 *errCode
);
                                  
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - file size 
    image[] - application code to be downloaded in to the flash

 Outputs:
    errCode - if return status is MYD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:

        MYD_STATUS_CRC_CHECKSUM_ERROR - RAM checksum register bad checksum          
        MYD_STATUS_FAIL_WRITE_REG - Error writing to register      
                  
 Returns:
    MYD_OK if successful, MYD_FAIL if an error was detected

 Description:
    This function download the SBus master firmware image to the chip. The input 
    file image is read in as a string of 10bit hex value. This function will 
    packed the 10bit into 32bit value and load them into the SBus master. After 
    the image load completed, the CRC will be checked for correctness.

 Side effects:
    None

 Notes/Warnings:
    Do not run any process to access the mdioPort while the firmware download is in 
    process. 

 Example:
    Refer to the sample API mydSampleLoadImageFile() on loading the image file
*****************************************************************************/
MYD_STATUS mydLoadSBusMasterFW
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 imageSize,
    IN MYD_U16 image[],
    OUT MYD_U16 *errCode
);


/******************************************************************************
 MYD_STATUS mydLoadZ80FWImage
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 imageSize,
    IN MYD_U16 image[],
    IN MYD_U16 reset,
    OUT MYD_U16 *errCode
);
                                  
 Inputs:
    pDev - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - file size 
    image[] - application code to be downloaded in to the flash
    reset - hardware reset before the firmware download. (no reset if 0) 

 Outputs:
    errCode - if return status is MYD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:
        MYD_FW_IMAGE_MISMATCHED - read back image mismatch with the write image

 Returns:
    MYD_OK if successful, MYD_FAIL if an error was detected

 Description:
    This function download the Z80 firmware image to the chip. The reset option 
    is provided to perform a hardware reset at the start of the download.  
    If the reset option is 1, the mydChipAndZ80ResetControl() must be called with 
    the MYD_Z80_RESET_RELEASE after the image download is completed.  

 Side effects:
    None

 Notes/Warnings:
    Do not run any process to access the mdioPort while the firmware download is 
    in process. 
    Make sure to disable copying ROM image to RAM by setting the 31.F418 to 0x1. Refer
    to mydFirmwareDownload for reference on calling this mydLoadZ80FWImage API.
    If the reset option is 1, the mydChipAndZ80ResetControl() must be called with 
    the MYD_Z80_RESET_RELEASE after the image download is completed.  

 Example:
    Refer to the sample API mydSampleLoadImageFile() on loading the image file
*****************************************************************************/
MYD_STATUS mydLoadZ80FWImage
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_U16 imageSize,
    IN MYD_U16 image[],
    IN MYD_BOOL reset,
    OUT MYD_U16 *errCode
);


/******************************************************************************
 MYD_STATUS mydUpdateEEPROMImage
(
     IN MYD_DEV_PTR pDev,
     IN MYD_U16   mdioPort,
     IN MYD_U16   sbusImageData[],
     IN MYD_U16   sbusImageSize, 
     IN MYD_U16   serdesImageData[],
     IN MYD_U16   serdesImageSize, 
     IN MYD_U16   z80ImageData[],
     IN MYD_U16   z80ImageSize,
     OUT MYD_U16  *errCode
 );
                                  
 Inputs:
    pDev            - pointer to MYD_DEV initialized by mydInitDriver() call
    mdioPort        - MDIO port address, 0-31
    sbusImageData   - input buffer image of the SBUS Master
    sbusImageSize   - SBUS Master image size
    serdesImageData - input buffer image of the SERDES
    serdesImageSize - SERDES image size
    z80ImageData    - input buffer image of the Z80 firmware   :optional input    
    z80ImageSize    - Z80 firmware image size                  :optional input

 Outputs:
    errCode - if function returns MYD_FAIL, more information is contained in errCode
    as follows:
         MYD_IO_ERROR - MDIO IO Error 
         MYD_STATUS_ERR_DEV - Driver not initialized or invalid device structure
         MYD_FW_INVALID_IMAGE_SIZE - A size of 0 in anyone of the 3 image sizes
         MYD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR - Unknown error updating the EEPROM

 Returns:
    MYD_OK if successful. MYD_FAIL if not.

 Description:
    This function updates the EEPROM with either the 2 Serdes/SBus images or all 3 images
    including the Z80(Z80 image is optional). It resets the chip into EEPROM programmable 
    state and writes the images to the EEPROM. After the write is completed, it checks 
    the EEPROM if the programming is successfully completed and load the images to the RAM.

 Side effects:
    None.

 Notes/Warnings:
    Both Serdes and SBus images must be provided or all 3 images including the Z80. 

    This operation can takes several seconds to complete.  

    Do not run any process to access the mdioPort while the firmware download is 
    in process. 

    This function applies to chip that supports EEPROM features. 

    The Z80 firmware file image is optional and not needed in some chip revision.
    If this image is not available, setting the z80Size to 0 will by-pass the
    Z80 firmware download.

 Example:

    mydSampleLoadImageFile(MYD_FIRMWARE_TYPE, MYD_Z80_IMAGE, &z80Size, &pZ80Image);
    mydSampleLoadImageFile(MYD_ROM_TYPE, MYD_SBUS_IMAGE, &busMasterSize, &pBusMasterImage);
    mydSampleLoadImageFile(MYD_ROM_TYPE, MYD_SERDES_IMAGE, &serdesSize, &pSerdesImage);
    
    retVal = mydUpdateEEPROMImage(pDev, 0, pBusMasterImage, busMasterSize, pSerdesImage, 
                                  serdesSize, pZ80Image, z80Size, &errCode);

******************************************************************************/ 
MYD_STATUS mydUpdateEEPROMImage
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16   mdioPort,
    IN MYD_U16   sbusImageData[],
    IN MYD_U16   sbusImageSize, 
    IN MYD_U16   serdesImageData[],
    IN MYD_U16   serdesImageSize, 
    IN MYD_U16   z80ImageData[],
    IN MYD_U16   z80ImageSize,
    OUT MYD_U16  *errCode
);


/******************************************************************************
MYD_STATUS mydLoadEEPROMImageToRAM
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_BOOL loadAllPorts
);
                                  
 Inputs:
   pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
   mdioPort - MDIO port address, 0-31
   loadAllPorts - option to load to 1 PHY or all PHYs

 Outputs:
   None.

 Returns:
    MYD_OK if successful. MYD_FAIL if not.

 Description:
    This function updates the RAM with the EEPROM images. It resets the RAM
    and loads the images from the EEPROM to the RAM. After the image is 
    successfully loaded, it returns a MYD_OK status.

 Side effects:
    None.

 Notes/Warnings:
    Make sure the EEPROM is available and the EEPROM images is valid. 
    Do not run any process to access the mdioPort while the firmware download is 
    in process. 
    This function applies to chip that supports EEPROM features. 
******************************************************************************/ 
MYD_STATUS mydLoadEEPROMImageToRAM
(
    IN MYD_DEV_PTR pDev,
    IN MYD_U16 mdioPort,
    IN MYD_BOOL loadAllPorts
);

/*******************************************************************************
MYD_STATUS mydFirmwareDownload
(
    IN MYD_DEV_PTR     pDev,
    IN MYD_U16         mdioPort,
    IN MYD_U16         *pZ80Image,
    IN MYD_U16         z80Size,
    IN MYD_U16         *pBusMasterImage,
    IN MYD_U16         busMasterSize,
    IN MYD_U16         *pSerdesImage,
    IN MYD_U16         serdesSize,
    IN MYD_BOOL        loadAllPorts,
    IN MYD_BOOL        broadcastMode
);

 Inputs:
   pDev     - pointer to MYD_DEV initialized by mydInitDriver() call
   mdioPort - MDIO port address on this device
   pZ80Image - input buffer image of the Z80 firmware           
   z80Size   - Z80 firmware image size                          
   pBusMasterImage - input buffer image of the SBUS Master  
   busMasterSize - SBUS Master image size                   
   pSerdesImage - input buffer image of the SERDES          
   serdesSize - SERDES image size        
   loadAllPorts - option to load to 1 PHY or all PHYs
   broadcastMode - option to use broadcast mode within a chip

 Outputs:
   None

 Returns:
   MYD_OK    - on success
   MYD_FAIL  - on error

 Description:
   This function provides various download options to update all 3 firmware 
   images to the device. The Z80 image is optional but both SBUS and SerDes 
   images must be provided. For a 4-port X7120 device, this call can load 
   the image to a single port or all 4 ports with the loadAllPorts boolean 
   parameter. The broadcastMode broadcast the write to all ports which 
   reduces the MDIO traffic and speed up the download time.  

   Refers to the MYD_FW_WRITE_VERIFIED for the firmware write verify option.
   This option will verify each write access to the device. Enabling the 
   MYD_FW_WRITE_VERIFIED will increase the download time.

 Side effects:
   None

 Notes/Warnings:
   The download will only be executed if both Serdes and SBus images are 
   provided or all 3 images including the Z80. If the incorrect image 
   combination is provided, this function will return an error.

   The Z80 firmware file image has a different format as the Z80 image used 
   in EEPROM programming. The EEPROM Z80 file format has 1 byte on each line. 
   Whereas, the Z80 firmware file format has 2 bytes on each line.
   
   The Z80 firmware file image is optional and not needed in some chip revision.
   If this image is not available, setting the z80Size to 0 will by-pass the
   Z80 firmware download.

*******************************************************************************/
MYD_STATUS mydFirmwareDownload
(
    IN MYD_DEV_PTR     pDev,
    IN MYD_U16         mdioPort,
    IN MYD_U16         *pZ80Image,
    IN MYD_U16         z80Size,
    IN MYD_U16         *pBusMasterImage,
    IN MYD_U16         busMasterSize,
    IN MYD_U16         *pSerdesImage,
    IN MYD_U16         serdesSize,
    IN MYD_BOOL        loadAllPorts,
    IN MYD_BOOL        broadcastMode
);


#if C_LINKAGE
#if defined __cplusplus 
}
#endif 
#endif

#endif /* defined MYDDL_H */
