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
higher-level functions using MDIO access to download firmware
into the internal RAM or attached flash memory of the Marvell
X5121/X5111/X2381/X5123/EC808 PHY.
********************************************************************/
#ifndef MCDDL_H
#define MCDDL_H

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

/* Firmware and EEPROM error codes */
#define MCD_FW_CRC_CHECKSUM_ERROR           0xA0 /*CRC checksum error*/
#define MCD_FW_FAIL_WRITE_REG               0xA1 /*Error access register*/
#define MCD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR  0xA2 /*Unknown download EEPROM error*/
#define MCD_FW_IMAGE_TOO_LARGE_TO_DOWNLOAD  0xA3 /*Image larger than the target device's memory*/
#define MCD_FW_INVALID_IMAGE_SIZE           0xA4 /*Invalid image size*/
#define MCD_FW_IMAGE_MISMATCHED             0xA5 /*Read back image mismatched */

typedef struct _MCD_FIRMWARE_CONFIG
{

    MCD_U32      fwLoadAddr; /* CM3 address */
    MCD_U8       *fwData;
    MCD_U32      fwSize;     /* actual (uncompressed) size in bytes */
    MCD_U32      fwArrSize;  /* size of buffer */
    MCD_U32      compress;   /* 0 - no compression, 2 - simple compression */
    MCD_U32      ipcShmAddr; /* shared memory  address */
    MCD_U32      ipcShmSize; /* Size of shared memory */
}MCD_FIRMWARE_CONFIG;

/******************************************************************************
 MCD_STATUS mcdLoadSBusSerdesFW
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 imageSize,
    IN MCD_U16 const image[],
    OUT MCD_U16 *errCode
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - file size
    image[] - application code to be downloaded in to the flash

 Outputs:
    errCode - if return status is MCD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:

         RAM checksum register bad checksum
         MCD_STATUS_CRC_CHECKSUM_ERROR

         Error writing to register
         MCD_STATUS_FAIL_WRITE_REG

 Returns:
    MCD_OK if successful, MCD_FAIL if an error was detected

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
    MCD_U8 image[]; - firmware file image
    MCD_U16 error;
    MCD_STATUS retStatus;

    fileSize = mcdOpenReadFile(pDev, mdioPort, &hFile, image, imageSize);
    retStatus = mcdLoadSBusSerdesFW(pDev, mdioPort, imageSize, image, &error);
    if (retStatus == MCD_FAIL)...check "error" for possible error codes

    fclose(hFile);
*****************************************************************************/
MCD_STATUS mcdLoadSBusSerdesFW
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 imageSize,
    IN MCD_U16 const image[],
    OUT MCD_U16 *errCode
);


/******************************************************************************
MCD_STATUS mcdLoadSBusMasterFW
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 imageSize,
    IN MCD_U16 const image[],
    IN MCD_U16 swapImageSize,
    IN MCD_U16 const swapImage[],
    OUT MCD_U16 *errCode
);
 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - file size
    image[] - application code to be downloaded in to the flash
    swapImageSize - swap image size
    swapImage[] - swap application code to be downloaded in to the flash

 Outputs:
    errCode - if return status is MCD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:

         RAM checksum register bad checksum
         MCD_STATUS_CRC_CHECKSUM_ERROR

         Error writing to register
         MCD_STATUS_FAIL_WRITE_REG

 Returns:
    MCD_OK if successful, MCD_FAIL if an error was detected

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
    MCD_U8 image[]; - firmware file image
    MCD_U16 error;
    MCD_STATUS retStatus;

    fileSize = mcdOpenReadFile(pDev, mdioPort, &hFile, image, imageSize);
    retStatus = mcdLoadSBusMasterFW(pDev, mdioPort, imageSize, image, &error);
    if (retStatus == MCD_FAIL)...check "error" for possible error codes

    fclose(hFile);
*****************************************************************************/
MCD_STATUS mcdLoadSBusMasterFW
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 imageSize, /* 0 if skipped */
    IN MCD_U16 const image[],
    IN MCD_U16 swapImageSize, /* 0 if skipped */
    IN MCD_U16 const swapImage[],
    OUT MCD_U16 *errCode
);

/******************************************************************************
 MCD_STATUS mcdLoadZ80FWImage
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 imageSize,
    IN MCD_U16 image[],
    IN MCD_U16 reset,
    OUT MCD_U16 *errCode
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - file size
    image[] - application code to be downloaded in to the flash
    reset - hardware reset before the firmware download. (no reset if 0)

 Outputs:
    errCode - if return status is MCD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:

 Returns:
    MCD_OK if successful, MCD_FAIL if an error was detected

 Description:
    This function download the Z80 firmware image to the chip. The reset option
    is provided to perform a hardware reset at the start of the download.

 Side effects:
    None

 Notes/Warnings:
    Do not run any process to access the mdioPort while the firmware download is
    in process.

 Example:
    FILE *hFile;
    MCD_U8 image[]; - firmware file image
    MCD_U16 error;
    MCD_STATUS retStatus;

    fileSize = mcdOpenReadFile(pDev, mdioPort, &hFile, image, imageSize);
    retStatus = mcdLoadZ80FWImage(pDev, mdioPort, imageSize, image, TRUE, &error);
    if (retStatus == MCD_FAIL)...check "error" for possible error codes

    fclose(hFile);
*****************************************************************************/
MCD_STATUS mcdLoadZ80FWImage
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U16 imageSize,
    IN MCD_U16 image[],
    IN MCD_BOOL reset,
    OUT MCD_U16 *errCode
);

/******************************************************************************
MCD_STATUS mcdLoadCm3FWImage
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 imageSize,
    IN MCD_U32 const image[]
);

 Inputs:
    pDev - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31
    imageSize - image size in bytes.
    image[] - application code to be downloaded to CM3 memory.

 Outputs:
    None.

 Returns:
    MCD_OK if successful, MCD_FAIL if an error was detected

 Description:
    This function downloads the Cm3 firmware image to the chip.
    Hardware reset before and start after the download done.

 Side effects:
    None
*****************************************************************************/
MCD_STATUS mcdLoadCm3FWImage
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort,
    IN MCD_U32 imageSize,
    IN MCD_U8 const image[]
);

/******************************************************************************
 MCD_STATUS mcdUpdateEEPROMImage(
     IN MCD_DEV_PTR pDev,
     IN MCD_U16   mdioPort,
     IN MCD_U16   sbusImageData[],
     IN MCD_U16   sbusImageSize,
     IN MCD_U16   serdesImageData[],
     IN MCD_U16   serdesImageSize,
     IN MCD_U16   z80ImageData[],
     IN MCD_U16   z80ImageSize,
     OUT MCD_U16  *errCode
 );

 Inputs:
    pDev            - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort        - MDIO port address, 0-31
    sbusImageData   - input buffer image of the SBUS Master ROM
    sbusImageSize   - SBUS Master ROM image size
    serdesImageData - input buffer image of the SERDES ROM
    serdesImageSize - SERDES ROM image size
    z80ImageData    - input buffer image of the Z80 firmware
    z80ImageSize    - Z80 firmware image size

 Outputs:
    errCode - if function returns MCD_FAIL, more information is contained in errCode
    as follows:
         MCD_IO_ERROR - MDIO IO Error
         MCD_STATUS_ERR_DEV - Driver not initialized or invalid device structure
         MCD_FW_INVALID_IMAGE_SIZE - A size of 0 in anyone of the 3 image sizes
         MCD_FW_UNKNOWN_DOWNLOAD_EEPROM_ERR - Unknown error updating the EEPROM

 Returns:
    MCD_OK if successful. MCD_FAIL if not.

 Description:
    This function updates the EEPROM with either the 2 Serdes/SBus images or all 3 images
    including the Z80. It resets the chip into EEPROM programmable state and writes the
    images to the EEPROM. After the write is completed, it checks the EEPROM if the
    programming is successfully completed and load the images to the RAM.

 Side effects:
    None.

 Notes/Warnings:
    Both Serdes and SBus images must be provided or all 3 images including the Z80.
    This operation can takes several seconds to complete.
    Do not run any process to access the mdioPort while the firmware download is
    in process.
    This function applies to chip that supports EEPROM features.

 Example:

    mcdLoadImageFile(pDev, MCD_FIRMWARE_TYPE, MCD_Z80_IMAGE, &z80Size, &pZ80Image);
    mcdLoadImageFile(pDev, MCD_ROM_TYPE, MCD_SBUS_IMAGE, &busMasterSize, &pBusMasterImage);
    mcdLoadImageFile(pDev, MCD_ROM_TYPE, MCD_SERDES_IMAGE, &serdesSize, &pSerdesImage);

    retVal = mcdUpdateEEPROMImage(pDev, 0, pBusMasterImage, busMasterSize, pSerdesImage,
                                  serdesSize, pZ80Image, z80Size, &errCode);

******************************************************************************/
MCD_STATUS mcdUpdateEEPROMImage
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16   mdioPort,
    IN MCD_U16   sbusImageData[],
    IN MCD_U16   sbusImageSize,
    IN MCD_U16   serdesImageData[],
    IN MCD_U16   serdesImageSize,
    IN MCD_U16   z80ImageData[],
    IN MCD_U16   z80ImageSize,
    OUT MCD_U16  *errCode
);


/******************************************************************************
 MCD_STATUS mcdLoadEEPROMImageToRAM
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort
 );

 Inputs:
    pDev     - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
   None.

 Returns:
    MCD_OK if successful. MCD_FAIL if not.

 Description:
    This function updates the RAM with the EEPROM images. It resets the RAM
    and loads the images from the EEPROM to the RAM. After the image is
    successfully loaded, it returns a MCD_OK status.

 Side effects:
    None.

 Notes/Warnings:
    Make sure the EEPROM is available and the EEPROM images is valid.
    Do not run any process to access the mdioPort while the firmware download is
    in process.
    This function applies to chip that supports EEPROM features.
******************************************************************************/
MCD_STATUS mcdLoadEEPROMImageToRAM
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
);


/******************************************************************************
 MCD_STATUS mcdLoadROMImageToRAM
 (
     IN MCD_DEV_PTR pDev,
     IN MCD_U16 mdioPort
 );

 Inputs:
    pDev     - pointer to MCD_DEV initialized by mcdInitDriver() call
    mdioPort - MDIO port address, 0-31

 Outputs:
   None.

 Returns:
    MCD_OK if successful. MCD_FAIL if not.

 Description:
    This function updates the RAM with the ROM images. It resets the RAM
    and loads the images from the ROM to the RAM. After the image is
    successfully loaded, it returns a MCD_OK status.

 Side effects:
    None.

 Notes/Warnings:
    Do not run any process to access the mdioPort while the firmware download is
    in process.
******************************************************************************/
MCD_STATUS mcdLoadROMImageToRAM
(
    IN MCD_DEV_PTR pDev,
    IN MCD_U16 mdioPort
);

/**
* @internal mcdLoadSBusSerdesFromCpuMemoryAllDevices function
* @endinternal
*
*/
MCD_STATUS mcdLoadSBusSerdesFromCpuMemoryAllDevices
(
    IN MCD_DEV_PTR   broadcastDevPtr,
    IN MCD_U16       num_of_devs,
    IN MCD_DEV_PTR   pDevArr[],  /* all devices on XSMI Bus */
    IN MCD_U16       imageSize,
    IN MCD_U16 const image[]
);

/**
* @internal mcdLoadSBusMasterFromCpuMemoryAllDevices function
* @endinternal
*
*/
MCD_STATUS mcdLoadSBusMasterFromCpuMemoryAllDevices
(
    IN MCD_DEV_PTR   broadcastDevPtr,
    IN MCD_U16       num_of_devs,
    MCD_DEV_PTR      pDevArr[],  /* all devices on XSMI Bus */
    IN MCD_U16       imageSize,
    IN MCD_U16 const image[],
    IN MCD_U16       swapImageSize, /* 0 if skipped */
    IN MCD_U16 const swapImage[]
);

/******************************************************************************
 MCD_STATUS mcdLoadCm3FWImageAllDevices
*******************************************************************************/
MCD_STATUS mcdLoadCm3FWImageAllDevices
(
    IN MCD_DEV_PTR   broadcastDevPtr,
    IN MCD_U16       num_of_devs,
    MCD_DEV_PTR      pDevArr[],  /* all devices on XSMI Bus */
    IN MCD_U32       imageSize,   /* size in bytes         */
    IN const MCD_U8  image[]
);

#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MCDDL_H */


