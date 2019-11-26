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
X5113 PHY.
********************************************************************/
#ifndef MXDDL_H
#define MXDDL_H

#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif

/* Firmware and EEPROM error codes */
#define MXD_FW_CRC_CHECKSUM_ERROR           0xA0 /*CRC checksum error*/
#define MXD_FW_FAIL_WRITE_REG               0xA1 /*Error access register*/
#define MXD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR  0xA2 /*Unknown download EEPROM error*/
#define MXD_FW_IMAGE_TOO_LARGE_TO_DOWNLOAD  0xA3 /*Image larger than the target device's memory*/
#define MXD_FW_INVALID_IMAGE_SIZE           0xA4 /*Invalid image size*/
#define MXD_FW_IMAGE_MISMATCHED             0xA5 /*Read back image mismatched */


/******************************************************************************
 MXD_STATUS mxdLoadSBusSerdesFW
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 imageSize,
    IN MXD_U16 image[],
    OUT MXD_U16 *errCode
);
                                  
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - file size 
    image[] - application code to be downloaded in to the flash

 Outputs:
    errCode - if return status is MXD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:

        MXD_STATUS_CRC_CHECKSUM_ERROR - RAM checksum register bad checksum          
        MXD_STATUS_FAIL_WRITE_REG - Error writing to register      
                  
 Returns:
    MXD_OK if successful, MXD_FAIL if an error was detected

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
    FILE *hFile;
    MXD_U8 image[]; - firmware file image 
    MXD_U16 error;
    MXD_STATUS retStatus;
    
    fileSize = mxdOpenReadFile(pDev, mdioPort, &hFile, image, imageSize);
    retStatus = mxdLoadSBusSerdesFW(pDev, mdioPort, imageSize, image, &error);
    if (retStatus == MXD_FAIL)...check "error" for possible error codes    

    fclose(hFile);
*****************************************************************************/
MXD_STATUS mxdLoadSBusSerdesFW
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 imageSize,
    IN MXD_U16 image[],
    OUT MXD_U16 *errCode
);


/******************************************************************************
 MXD_STATUS mxdLoadSBusMasterFW
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 imageSize,
    IN MXD_U16 image[],
    OUT MXD_U16 *errCode
);
                                  
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - file size 
    image[] - application code to be downloaded in to the flash

 Outputs:
    errCode - if return status is MXD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:

        MXD_STATUS_CRC_CHECKSUM_ERROR - RAM checksum register bad checksum          
        MXD_STATUS_FAIL_WRITE_REG - Error writing to register      
                  
 Returns:
    MXD_OK if successful, MXD_FAIL if an error was detected

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
    FILE *hFile;
    MXD_U8 image[]; - firmware file image
    MXD_U16 error;
    MXD_STATUS retStatus;
    
    fileSize = mxdOpenReadFile(pDev, mdioPort, &hFile, image, imageSize);
    retStatus = mxdLoadSBusMasterFW(pDev, mdioPort, imageSize, image, &error);
    if (retStatus == MXD_FAIL)...check "error" for possible error codes    

    fclose(hFile);
*****************************************************************************/
MXD_STATUS mxdLoadSBusMasterFW
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 imageSize,
    IN MXD_U16 image[],
    OUT MXD_U16 *errCode
);


/******************************************************************************
 MXD_STATUS mxdLoadZ80FWImage
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 imageSize,
    IN MXD_U16 image[],
    IN MXD_U16 reset,
    OUT MXD_U16 *errCode
);
                                  
 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - file size 
    image[] - application code to be downloaded in to the flash
    reset - hardware reset before the firmware download. (no reset if 0) 

 Outputs:
    errCode - if return status is MXD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:
        MXD_FW_IMAGE_MISMATCHED - read back image mismatch with the write image

 Returns:
    MXD_OK if successful, MXD_FAIL if an error was detected

 Description:
    This function download the Z80 firmware image to the chip. The reset option 
    is provided to perform a hardware reset at the start of the download.  
    If the reset option is 1, the mxdChipAndZ80ResetControl() must be called with 
    the MXD_Z80_RESET_RELEASE after the image download is completed.  

 Side effects:
    None

 Notes/Warnings:
    Do not run any process to access the mdioPort while the firmware download is 
    in process. 
    If the reset option is 1, the mxdChipAndZ80ResetControl() must be called with 
    the MXD_Z80_RESET_RELEASE after the image download is completed.  

 Example:
    FILE *hFile;
    MXD_U8 image[]; - firmware file image
    MXD_U16 error;
    MXD_STATUS retStatus;
    
    fileSize = mxdOpenReadFile(pDev, mdioPort, &hFile, image, imageSize);
    retStatus = mxdLoadZ80FWImage(pDev, mdioPort, imageSize, image, TRUE, &error);
    if (retStatus == MXD_FAIL)...check "error" for possible error codes    

    fclose(hFile);
*****************************************************************************/
MXD_STATUS mxdLoadZ80FWImage
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort,
    IN MXD_U16 imageSize,
    IN MXD_U16 image[],
    IN MXD_BOOL reset,
    OUT MXD_U16 *errCode
);


/******************************************************************************
 MXD_STATUS mxdUpdateEEPROMImage(
     IN MXD_DEV_PTR pDev,
     IN MXD_U16   mdioPort,
     IN MXD_U16   sbusImageData[],
     IN MXD_U16   sbusImageSize, 
     IN MXD_U16   serdesImageData[],
     IN MXD_U16   serdesImageSize, 
     IN MXD_U16   z80ImageData[],
     IN MXD_U16   z80ImageSize,
     OUT MXD_U16  *errCode
 );
                                  
 Inputs:
    pDev            - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort        - MDIO port address, 0-31
    sbusImageData   - input buffer image of the SBUS Master
    sbusImageSize   - SBUS Master image size
    serdesImageData - input buffer image of the SERDES
    serdesImageSize - SERDES image size
    z80ImageData    - input buffer image of the Z80 firmware   :optional input    
    z80ImageSize    - Z80 firmware image size                  :optional input

 Outputs:
    errCode - if function returns MXD_FAIL, more information is contained in errCode
    as follows:
         MXD_IO_ERROR - MDIO IO Error 
         MXD_STATUS_ERR_DEV - Driver not initialized or invalid device structure
         MXD_FW_INVALID_IMAGE_SIZE - A size of 0 in anyone of the 3 image sizes
         MXD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR - Unknown error updating the EEPROM

 Returns:
    MXD_OK if successful. MXD_FAIL if not.

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

    mxdLoadImageFile(pDev, MXD_FIRMWARE_TYPE, MXD_Z80_IMAGE, &z80Size, &pZ80Image);
    mxdLoadImageFile(pDev, MXD_ROM_TYPE, MXD_SBUS_IMAGE, &busMasterSize, &pBusMasterImage);
    mxdLoadImageFile(pDev, MXD_ROM_TYPE, MXD_SERDES_IMAGE, &serdesSize, &pSerdesImage);
    
    retVal = mxdUpdateEEPROMImage(pDev, 0, pBusMasterImage, busMasterSize, pSerdesImage, 
                                  serdesSize, pZ80Image, z80Size, &errCode);

******************************************************************************/ 
MXD_STATUS mxdUpdateEEPROMImage
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16   mdioPort,
    IN MXD_U16   sbusImageData[],
    IN MXD_U16   sbusImageSize, 
    IN MXD_U16   serdesImageData[],
    IN MXD_U16   serdesImageSize, 
    IN MXD_U16   z80ImageData[],
    IN MXD_U16   z80ImageSize,
    OUT MXD_U16  *errCode
);


/******************************************************************************
 MXD_STATUS mxdLoadEEPROMImageToRAM
 (
     IN MXD_DEV_PTR pDev,
     IN MXD_U16 mdioPort
 );
                                  
 Inputs:
    pDev     - pointer to MXD_DEV initialized by mxdInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
   None.

 Returns:
    MXD_OK if successful. MXD_FAIL if not.

 Description:
    This function updates the RAM with the EEPROM images. It resets the RAM
    and loads the images from the EEPROM to the RAM. After the image is 
    successfully loaded, it returns a MXD_OK status.

 Side effects:
    None.

 Notes/Warnings:
    Make sure the EEPROM is available and the EEPROM images is valid. 
    Do not run any process to access the mdioPort while the firmware download is 
    in process. 
    This function applies to chip that supports EEPROM features. 
******************************************************************************/ 
MXD_STATUS mxdLoadEEPROMImageToRAM
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
);


#if C_LINKAGE
#if defined __cplusplus 
}
#endif 
#endif

#endif /* defined MXDDL_H */
