/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
higher-level functions using MDIO access to download firmware
into the internal RAM or attached flash memory of the Marvell 88X32X0, 
88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTDDL_H
#define MTDDL_H

#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif

#if DB_TEST_ENVIRONMENT
#define DB_TEST_FLASHCODE   1 /* set to 0 for host environment*/
                              /* (removes many extra print statements) */
                              /* set to 1 to build sample code */
                              /* to interface to Marvell DB via USB2SMI board */
                              /* (extra debug statements during flash/ram download) */
#else
#define DB_TEST_FLASHCODE   0
#endif

/* Parallel Download - RAM & FLASH */
#define MAX_PORTS_TO_DOWNLOAD 16  /* this is the maximum number of ports that can be downloaded */
                                  /* in parallel ram or parallel flash download functions */

#define MTD_MAX_APP_SIZE (216*1024UL)

#define MTD_MAX_SLAVE_SIZE (28*1024)

#define MTD_HEADER_SIZE 32

#define MTD_CKSUM_OFFSET 8 /* checksum location in HDR file, this is low byte */

/* One or more PHY port couldn't be put into download mode */
#define MTD_PHY_DL_MODE_FAILED              0xFFDB
/* Slave command timed out */
#define MTD_SLAVE_CMD_TIMEOUT               0xFFDC
/* Header file download to RAM checksum doesn't match expected checksum in header */
#define MTD_HDR_RAM_CHECKSUM_BAD            0xFFDD
/* At least one port during a parallel RAM or flash download failed */
#define MTD_PAR_DOWNLOAD_FAILED             0xFFDE
/*Image larger than the target device's memory*/
#define MTD_IMAGE_TOO_LARGE_TO_DOWNLOAD     0xFFDF
/* Slave code did not start. - Slave code failed to download properly. */
#define MTD_SLAVE_CODE_DID_NOT_START        0xFFE0
/* Flash verifed FAILED! Flash probably corrupted */
#define MTD_VERIFY_ERR                      0xFFE1
/* Unknown error, downloading the flash failed! */
#define MTD_UNKNOWN_DOWNLOAD_TO_FLASH_FAIL  0xFFE2
/* App code did not start. - App code failed to download properly in to the RAM. */
#define MTD_APP_CODE_DID_NOT_START          0xFFE3
/* App code failed. - Number of ports to download is greater than maximum ports */
#define MTD_NUM_PORTS_TOO_LARGE             0xFFE4

/* Error reading or writing MDIO register */
#define MTD_IO_ERROR                        0xFFE5
/*size must be an even number of bytes*/
#define MTD_SIZE_NOT_EVEN                   0xFFE6
/* Slave encountered error while erasing flash */
#define MTD_ERR_ERASING_FLASH               0xFFE7
/* unexpected value read back from download code */
#define MTD_ERR_VALUE_READ_BACK             0xFFE8
/* Did not get MTD_SLAVE_OK for writing the data */
#define MTD_ERR_START_WRITE_DATA            0xFFE9
/* Slave failed to get all the data correctly*/
#define MTD_WRITE_VERIFY_DATA                0xFFEA
/* Some kind of error occurred on Slave */
#define MTD_ERR_ON_SLAVE                    0xFFEB
/* Checksum error */
#define MTD_ERR_CHECKSUM                    0xFFEC
/* Slave didn't write enough words to flash. Some kind of error occurred*/
#define MTD_ERR_SLAVE_WRITE_FULL            0xFFED
/* last transfer failed */
#define MTD_ERR_LAST_TRANSFER               0xFFEE
/* RAM checksum register (present only in SFT910X RevB or later) had wrong checksum */
#define MTD_RAM_HW_CHECKSUM_ERR             0xFFEF
/* PHY wasn't waiting in download mode */
#define MTD_PHY_NOT_IN_DOWNLOAD_MODE        0xFFFF


/******************************************************************************
 MTD_STATUS mtdUpdateFlashImage(
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U8 appData[],
     IN MTD_U32 appSize, 
     IN MTD_U8 slaveData[],
     IN MTD_U32 slaveSize,
     OUT MTD_U16 *errCode);
                                  
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    appData[] - application code to be downloaded into the flash
    appSize - application code size in bytes (must be even)
    slaveData[] - slave code to be downloaded into the RAM
    slaveSize - size of the slave code in bytes (must be even)

 Outputs:
    errCode - if function returns MTD_FAIL, more information is contained in errCode
    as follows:
         
         MTD_IO_ERROR
         MTD_IMAGE_TOO_LARGE_TO_DOWNLOAD     
         MTD_PHY_NOT_IN_DOWNLOAD_MODE        
         MTD_SLAVE_CMD_TIMEOUT 
         MTD_HDR_RAM_CHECKSUM_BAD
         MTD_RAM_HW_CHECKSUM_ERR        
         MTD_SLAVE_CODE_DID_NOT_START        
         MTD_SIZE_NOT_EVEN              
         MTD_ERR_ERASING_FLASH      
         MTD_ERR_VALUE_READ_BACK   
         MTD_ERR_START_WRITE_DATA  
         MTD_WRITE_VERIFY_DATA  
         MTD_ERR_ON_SLAVE  
         MTD_ERR_CHECKSUM 
         MTD_ERR_SLAVE_WRITE_FULL 
         MTD_ERR_LAST_TRANSFER                    
         MTD_VERIFY_ERR                      
         MTD_UNKNOWN_DOWNLOAD_TO_FLASH_FAIL  

 Returns:
    MTD_OK if successful. MTD_FAIL if not.

 Description:
    The function first checks if the app code size is greater than what it 
    should be and returns an error if that was the case (or if the image
    sizes are not even, an error will also be returned).
    
    Then it calls mtdPutPhyInMdioDownloadMode() to put the PHY in download mode 
    and downloads the slave code in to the RAM and starts executing. 
    
    Once the flash is written with the help of the slave, slave verifies
    the flash program and returns errors if the image is corrupted (the slave
    reads back the image from flash and verifies the checksum matches the expected checksum).

    Any error occurs returns MTD_FAIL and additional information may be in "errCode".

 Side effects:
    None.

 Notes/Warnings:
    This function calls two main functions ...
    1. mtdMdioRamDownload() to download the slave helper code
    2. mtdMdioFlashDownload() to update the flash using the slave helper code

    The function asserts the SPI_CONFIG (by calling mtdPutPhyInMdioDownloadMode()) when it begins the code download, 
    but it does not remove the download mode. In order to execute the newly downloaded 
    code, SPI_CONFIG must be lowered by calling mtdRemovePhyMdioDownloadMode() (or changing the strap config) and the 
    PHY must be reset to use the newly updated flash image. Or the PHY chip hardware reset can
    be issued to both remove the download mode and reload the code from flash (assuming the PHY is strapped
    for flash upload and not MDIO loading).

 Example:
    FILE *hFile, *sFile;                        
    MTD_U8 appData[MTD_MAX_APP_SIZE+MTD_HEADER_SIZE];        // hdr file image
    MTD_U8 slaveCode[MTD_MAX_SLAVE_SIZE];    // slave code image
    MTD_STATUS retStatus;
    MTD_U16 error;

    fileSize = mtdOpenReadFile(devPtr,port, &hFile, "image_name.hdr", appData,
                                    (MTD_MAX_APP_SIZE+ MTD_HEADER_SIZE));
    slaveFileSize = mtdOpenReadFile(devPtr,port, &sFile, 
                                    "x3240flashdlslave_0_3_0_0_6147.bin", slaveCode,
                                    MTD_MAX_SLAVE_SIZE);
    retStatus = mtdUpdateFlashImage(devPtr,port, appData, fileSize, slaveCode, 
                                 slaveFileSize, &error);
    if (retStatus == MTD_FAIL)
        ...check "error" for what happened/type of error that occurred

    mtdChipHardwareReset(devPtr,port); // Removes download mode from all ports and reloads all
                                       // ports with the new code from flash
    
    fclose(hFile);
    fclose(sFile);

******************************************************************************/ 
MTD_STATUS mtdUpdateFlashImage(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 appData[],
    IN MTD_U32 appSize, 
    IN MTD_U8 slaveData[],
    IN MTD_U32 slaveSize,
    OUT MTD_U16 *errCode);

/******************************************************************************
 MTD_STATUS mtdUpdateRamImage(
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 port,
     IN MTD_U8 appData[],
     IN MTD_U32 appSize
     OUT MTD_U16 *errCode);
                                  
 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31
    appData[] - application code to be downloaded into the RAM
    appSize - application code size in bytes (must be even)

 Outputs:
    errCode - if return status is MTD_FAIL, errCode may contain additional
    information about the error. If it does, it will be one of the following:

         MTD_IO_ERROR
         MTD_SIZE_NOT_EVEN               
         MTD_IMAGE_TOO_LARGE_TO_DOWNLOAD     
         MTD_PHY_NOT_IN_DOWNLOAD_MODE        
         MTD_RAM_HW_CHECKSUM_ERR             
         MTD_APP_CODE_DID_NOT_START 
         MTD_HDR_RAM_CHECKSUM_BAD
                  
 Returns:
    MTD_OK if successful, MTD_FAIL if an error was detected

 Description:
    The function first checks if the app code size is greater than what it 
    should be and returns an error if that was the case (or if the image size
    is not even, and error will also be returned).

    It calls mtdPutPhyInMdioDownloadMode() to put the port in download mode by
    raising the SPI_CONFIG bit (required to execute from RAM) and resets the T unit.

    Then it downloads the app code to the RAM and starts it executing. Returns
    MTD_FAIL if any error is encountered, with possibly more information in "errCode".
    
 Side effects:
    None

 Notes/Warnings:
    None

Example:
    FILE *hFile;
    MTD_U8 appData[MTD_MAX_APP_SIZE+MTD_HEADER_SIZE];        // hdr file image
    MTD_U16 error;
    MTD_STATUS retStatus;
    
    fileSize = mtdOpenReadFile(devPtr,port, &hFile, "image_name.hdr", appData,
                                    (MTD_MAX_APP_SIZE+MTD_HEADER_SIZE));
    retStatus = mtdUpdateRamImage(devPtr,port, appData, fileSize, &error);
    if (retStatus == MTD_FAIL)...check "error" for possible error codes    

    fclose(hFile);
******************************************************************************/
MTD_STATUS mtdUpdateRamImage(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 appData[],
    IN MTD_U32 appSize,
    OUT MTD_U16 *errCode);

/******************************************************************************
 MTD_STATUS mtdParallelUpdateRamImage(
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16 ports[],
     IN MTD_U8 appData[],
     IN MTD_U32 appSize, 
     IN MTD_U16 numPorts,
     OUT MTD_U16 erroredPorts[]
     OUT MTD_U16 *errCode);
                                  

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    ports[] - list of port numbers to which the application code needs to be downloaded
              (should include all ports on a chip)
    appData[] - application code to be downloaded into RAM
    appSize - appplication code size in bytes (must be even)
    numPorts - number of ports to download (any number from 0-31)

 Outputs:
    errCode - If return status is MTD_FAIL, errCode may contain one of the following:

        MTD_IO_ERROR
        MTD_NUM_PORTS_TOO_LARGE
        MTD_SIZE_NOT_EVEN               
        MTD_IMAGE_TOO_LARGE_TO_DOWNLOAD
        MTD_RAM_HW_CHECKSUM_ERR
        MTD_PAR_DOWNLOAD_FAILED (one or more ports failed)          
            
    erroredPorts[] - Failure code on ports that had error during download.

        The following are the failure codes stored in the array erroredPorts[]

        MTD_PHY_NOT_IN_DOWNLOAD_MODE        
        MTD_RAM_HW_CHECKSUM_ERR             
        MTD_APP_CODE_DID_NOT_START 
        MTD_HDR_RAM_CHECKSUM_BAD
        
                
 Returns:
    Download successful on all ports - MTD_OK
    Download not successful on at least one port - MTD_FAIL

    
 Description:
    The function first checks if the number of ports to download is greater
    than maximum ports to download and if true returns an error.
    
    The code then checks if the app code size is greater than what it 
    should be and returns an error if that was the case (or code size is
    not even will also return an error).

    Then it puts all the ports into the download mode by calling
    mtdPutPhyInMdioDownloadMode() which will overwrite the SPI_CONFIG to
    disable flash loading and do a T unit hardware reset. 
    
    Then it downloads the app code in to the RAM in parallel and starts it executing. 

    Makes sure code started.

 Side effects:
    None.

 Notes/Warnings:
    It's not possible to use this function to download some ports on a chip
    and not others. The parallel write feature is a chip-level feature. All
    ports on a chip will be written if the feature is enabled, so the list
    of ports should include all ports on any chip being downloaded.
    
    If this function returns an error in errCode, then it should be assumed
    possibly no ports were downloaded successfully.

    If this function returns MTD_FAIL, the chip(s) should be hardware reset to 
    recover, because one or more ports may be left in parallel download mode.

    If MTD_PAR_DOWNLOAD_FAILED is returned, the erroredPorts[] list will
    contain the ports that had an error (non-zero value) and the ports
    that have a 0 value were loaded successfully.

Example:
    FILE *hFile;
    MTD_U8 appData[MTD_MAX_APP_SIZE+MTD_HEADER_SIZE];        // hdr file image
    MTD_U16 error;
    MTD_STATUS retStatus;
    const MTD_U16 ports[4] = {0,1,2,3}; // Will download MDIO ports 0...3 in parallel
    
    fileSize = mtdOpenReadFile(devPtr,port, &hFile, "image_name.hdr", appData,
                                    (MTD_MAX_APP_SIZE+MTD_HEADER_SIZE));
                                    
    retStatus = mtdParallelUpdateRamImage(devPtr,ports, 
                                          appData, fileSize, 4,
                                          erroredPorts, &error);
    if (retStatus == MTD_FAIL)
    {
        ...check error, and/or all ports in erroredPorts for failure codes
    }
    fclose(hFile);

******************************************************************************/
MTD_STATUS mtdParallelUpdateRamImage(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 ports[],
    IN MTD_U8 appData[],
    IN MTD_U32 appSize, 
    IN MTD_U16 numPorts,
    OUT MTD_U16 erroredPorts[],
    OUT MTD_U16 *errCode);

/******************************************************************************       
  MTD_STATUS mtdParallelUpdateFlashImage
  (
      IN MTD_DEV_PTR devPtr,
      IN MTD_U16 ports[],
      IN MTD_U8 appData[],
      IN MTD_U32 appSize, 
      IN MTD_U8 slaveData[],
      IN MTD_U32 slaveSize,
      IN MTD_U16 numPorts, 
      OUT MTD_U16 erroredPorts[],
      OUT MTD_U16 *errCode
  );
                                  

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    ports[] - list of port numbers to which the application code needs to be downloaded
              important: only one port per chip
    appData[] - application code to be downloaded into the flash
    appSize - application code size in bytes (must be even)
    slaveData[] - slave code to be downloaded in to the RAM
    slaveSize - file size of the slave code un bytes (must be even)
    numPorts - number of ports to download (any number from 0-31), should be
               one per chip (as multiple ports per chip share the same flash)

 Outputs:
    erroredPorts[] - Failure code on ports that had error during download.

        The following are the failure codes stored in the array erroredPorts[]
            
        MTD_PHY_NOT_IN_DOWNLOAD_MODE        
        MTD_RAM_HW_CHECKSUM_ERR   
        MTD_HDR_RAM_CHECKSUM_BAD
        MTD_SLAVE_CODE_DID_NOT_START        
        MTD_ERR_ERASING_FLASH           
        MTD_ERR_VALUE_READ_BACK         
        MTD_ERR_START_WRITE_DATA        
        MTD_WRITE_VERIFY_DATA            
        MTD_ERR_ON_SLAVE                
        MTD_ERR_CHECKSUM                
        MTD_ERR_SLAVE_WRITE_FULL                        
        MTD_VERIFY_ERR  
        MTD_SLAVE_CMD_TIMEOUT


     errCode - if return is MTD_FAIL, errCode may contain additional information:
        MTD_IO_ERROR
        MTD_NUM_PORTS_TOO_LARGE 
        MTD_IMAGE_TOO_LARGE_TO_DOWNLOAD    
        MTD_PHY_DL_MODE_FAILED
        MTD_SIZE_NOT_EVEN
        MTD_PAR_DOWNLOAD_FAILED (one or more ports failed to download successfully,
                                 failed ports listed in erroredPorts with error
                                 code there)

        
               
 Returns:
    Download successful on all ports - MTD_OK
    Download not successful on at least one port - MTD_FAIL

 Description:
    This function parallelizes the flash download to speed up downloading a new
    image by using the MDIO parallel write feature in the PHY to allow writing
    multiple PHYs at the same time during the write cycles. It does this by
    enabling the parallel write feature for writes, disabling it for reads.

    The function first checks if the number of ports to download is greater
    than maximum ports to download and if true returns an error.

    The code then checks if the app code size is greater than what it 
    should be (or not even) and returns an error if that was the case.

    Then it puts the PHYs in download mode using mtdPutPhyInMdioDownloadMode() and 
    downloads the slave code into the RAM and starts it executing. 

    The slave code helps program the app code into the flash and verifies 
    the image after downloading by reading back and matching against the checksum.

 Side effects:
    None.

 Notes/Warnings:
    The function puts the PHY into download mode but it does
    not remove the download mode after the download. In order to execute the downloaded 
    code, do a chip reset, mtdChipHardwareReset(), which will remove download
    mode (if it was enabled with the overwrite function, if not, then the strap
    pin must be changed before calling the chip reset) and have all ports load
    the new image from flash.

    On chips with multiple ports per chip, only download on one port. All ports
    on a chip share the same flash part. For example X3220, has 2 ports, only
    download the first port. On X3240, it has 4 ports, so only download the first
    port (if multiple X3240, download every fourth port, e.g. 0,4,8, etc.).

    All ports on all chips will be put in the download mode during the flash update,
    so any port operating will stop operating during the flash update. If you want
    to keep other ports operational during the flash update, you must do them
    one-at-a-time using mtdUpdateFlashImage().

    If this function returns MTD_FAIL, the chip(s) should be hardware reset
    because one or more ports may be left in parallel download mode.

 Example:
    FILE *hFile, *sFile;                        
    MTD_U8 appData[MTD_MAX_APP_SIZE+MTD_HEADER_SIZE];        // hdr file image
    MTD_U8 slaveCode[MTD_MAX_SLAVE_SIZE];    // slave code image
    MTD_U16 error;
    MTD_STATUS retStatus;
    const MTD_U16 ports = {0,4,8}; // Will download 4 flashes in parallel, in this
                                   // case these are 4 x 4-port chips
    
    fileSize = mtdOpenReadFile(devPtr,port, &hFile, 
                               "image_name.hdr", appData, 
                               (MTD_MAX_APP_SIZE + MTD_HEADER_SIZE)); 
    slaveFileSize = mtdOpenReadFile(devPtr,port, &sFile, 
                                    "flashdownloadslave.bin", slaveCode, 
                                    MTD_MAX_SLAVE_SIZE);
    retStatus = mtdParallelUpdateFlashImage(devPtr,ports, appData, 
                                            fileSize, slaveCode, 
                                            slaveFileSize, 3,
                                            erroredPorts,&error);
    if (retStatus == MTD_FAIL)
    {
        ...check error, and/or all ports in erroredPorts for failure codes
    }                                
    
    mtdChipHardwareReset(devPtr,0); // Removes download mode from all ports and reloads all
                                    // ports with the new code from flash
    mtdChipHardwareReset(devPtr,4); // Removes download mode from all ports and reloads all
                                    // ports with the new code from flash
    mtdChipHardwareReset(devPtr,8); // Removes download mode from all ports and reloads all
                                    // ports with the new code from flash    fclose(hFile);
    fclose(sFile);

******************************************************************************/ 
MTD_STATUS mtdParallelUpdateFlashImage
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 ports[],
    IN MTD_U8 appData[],
    IN MTD_U32 appSize, 
    IN MTD_U8 slaveData[],
    IN MTD_U32 slaveSize,
    IN MTD_U16 numPorts, 
    OUT MTD_U16 erroredPorts[],
    OUT MTD_U16 *errCode
);

#if C_LINKAGE
#if defined __cplusplus 
}
#endif 
#endif

#endif /* defined MTDDL_H */
