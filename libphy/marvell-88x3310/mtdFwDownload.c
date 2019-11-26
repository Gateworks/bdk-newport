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
#include "mtdApiRegs.h"
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdAPI.h"
#include "mtdFwDownload.h"
#include "mtdAPIInternal.h"

#if DB_TEST_FLASHCODE
void amuse_user(void);
#endif

MTD_STATUS mtdUpdateFlashImage(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 appData[],
    IN MTD_U32 appSize, 
    IN MTD_U8 slaveData[],
    IN MTD_U32 slaveSize,
    OUT MTD_U16 *errCode)
{    
    MTD_BOOL appStarted;
    MTD_U16 slaveReply;
#if DB_TEST_FLASHCODE
    MTD_U16 flashType;
    MTD_U16 numSections;
#endif

    *errCode = 0;
    
    /******************************************************************************* 
       Check if the code about to be downloaded can fit into the device's memory
    *******************************************************************************/
    if (appSize > (mtdGetDevMemorySize(devPtr) + MTD_HEADER_SIZE))
    {
        // App size cannot be larger than the device memory size. Code download cannot proceed
#if DB_TEST_FLASHCODE
        MTD_DBG_ERROR("Image is larger than the device memory size!\n");
#endif
        *errCode = MTD_IMAGE_TOO_LARGE_TO_DOWNLOAD; 
        return MTD_FAIL;
    }
    
    /*******************************************************************************
             Download slave code to phy's RAM and start it,
             this code assists in programming the flash connected by SPI
    *******************************************************************************/    
#if DB_TEST_FLASHCODE
    if (!(slaveData == (MTD_U8 *)0 && slaveSize == 0))
    {
        /* In test code allow skipping slave download by passing NULL/0 */
        ATTEMPT(mtdMdioRamDownload(devPtr,slaveData,slaveSize,port,MTD_FALSE,0,errCode));  
    }
#else
    ATTEMPT(mtdMdioRamDownload(devPtr,slaveData,slaveSize,port,MTD_FALSE,0,errCode));  
#endif

    /* make sure the slave code started/is running */
    TRY_IO(mtdDidPhyAppCodeStart(devPtr,port,&appStarted));
   
    if (appStarted == MTD_FALSE)
    {
#if DB_TEST_FLASHCODE
        MTD_DBG_ERROR("Slave code did not start.\n");
        MTD_DBG_ERROR("Slave download failed. Exiting...\n");
#endif
        *errCode = MTD_SLAVE_CODE_DID_NOT_START;        
        return MTD_FAIL;
    }

    /*******************************************************************************
       Write the image to flash with slave's help
    *******************************************************************************/
    ATTEMPT(mtdMdioFlashDownload(devPtr,port, appData, appSize, errCode));
    
    /*******************************************************************************
       Let slave verify image
    *******************************************************************************/

    /* Using slave code to verify image.
       This commands slave to read in entire flash image and calculate checksum and make sure
       checksum matches the checksum in the header. A failure means flash was corrupted.
      
       Another method would be to reset the phy (with SPI_CONFIG[1]= 0) and see that the new code
       starts successfully, since a bad checksum will result in the code not being started */

#if DB_TEST_FLASHCODE
    ATTEMPT(mtdHwXmdioRead(devPtr, port, FLASH_MFG_TYPE, &flashType));
    MTD_DBG_INFO("Flash type is 0x%04X\n",(int)flashType);
    MTD_DBG_INFO("Flash programming complete. Verifying image via slave.\n");    
#endif

    if (mtdTrySlaveCommand(devPtr, port, VERIFY_FLASH, &slaveReply, 15000) == MTD_FAIL)
    {
        *errCode = MTD_SLAVE_CMD_TIMEOUT;
        return MTD_FAIL;
    }

    if (slaveReply == MTD_SLAVE_OK)
    {
#if DB_TEST_FLASHCODE
        MTD_DBG_INFO("\nFlash image verified. Call mtdRemovePhyDownloadMode() or change strap and reboot to execute new code\n");
        ATTEMPT(mtdHwXmdioRead(devPtr, port, NUM_SECTIONS, &numSections));
        MTD_DBG_INFO("Flash image had %d sections\n",(int)(numSections+1));
#endif
        return MTD_OK;   /*Flash download complete */
    }
    else
    {
        if (slaveReply == MTD_SLAVE_VERIFY_ERR)
        {
#if DB_TEST_FLASHCODE
            MTD_DBG_ERROR("\nFlash verifed FAILED! Flash probably corrupted. Re-try download.\n");
            ATTEMPT(mtdHwXmdioRead(devPtr, port, NUM_SECTIONS, &numSections));
            MTD_DBG_INFO("Section number %d had a verification error.\n",(int)(numSections));
#endif
            *errCode = MTD_VERIFY_ERR;                
            return MTD_FAIL;
        }
        else
        {
#if DB_TEST_FLASHCODE
            MTD_DBG_ERROR("\nExpected 0x%04X from slave got 0x%04X. Exiting...\n", MTD_SLAVE_OK, (int)slaveReply);
#endif
            *errCode = MTD_UNKNOWN_DOWNLOAD_TO_FLASH_FAIL;
            return MTD_FAIL;
        }
    }

}

MTD_STATUS mtdUpdateRamImage(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U8 appData[],
    IN MTD_U32 appSize,
    OUT MTD_U16 *errCode)
{
    MTD_BOOL appStarted;

    MTD_U16 expectedChecksum;

    *errCode = 0;

    /******************************************************************************* 
       Check if the code about to be downloaded can fit into the device's memory
    *******************************************************************************/
    if (appSize > (mtdGetDevMemorySize(devPtr) + MTD_HEADER_SIZE))
    {
        // App size cannot be larger than the device memory size. Code download cannot proceed
#if DB_TEST_FLASHCODE
        MTD_DBG_ERROR("Image is larger than the device memory size!\n");
#endif
        *errCode = MTD_IMAGE_TOO_LARGE_TO_DOWNLOAD; 
        return MTD_FAIL;
    }

    /*******************************************************************************
       This handles downloading the binary part of the HDR file to RAM and executing
       it without modifying the flash.
    *******************************************************************************/
    
    /*******************************************************************************
           Sample of what downloading an HDR file to RAM and executing it would
           look like (non-flash installation or when another image than what's in
           flash is desired to be executed but without changing the flash).
    *******************************************************************************/

    /* Puts phy in download mode, skips over header and downloads binary to RAM
    then starts the app code running */
    expectedChecksum = (MTD_U16)appData[MTD_CKSUM_OFFSET] + (((MTD_U16)appData[MTD_CKSUM_OFFSET+1])<<8);
    ATTEMPT(mtdMdioRamDownload(devPtr,&appData[MTD_HEADER_SIZE],(appSize-MTD_HEADER_SIZE), \
                           port,MTD_TRUE,~expectedChecksum,errCode));

    /* make sure the app code started */
    TRY_IO(mtdDidPhyAppCodeStart(devPtr,port,&appStarted))
    
    if (appStarted == MTD_FALSE)
    {
#if DB_TEST_FLASHCODE
        MTD_DBG_ERROR("App code did not start.\n");
        MTD_DBG_ERROR("App download failed.\n");
#endif

        *errCode = MTD_APP_CODE_DID_NOT_START;
        return MTD_FAIL;
    }
    else
    {
#if DB_TEST_FLASHCODE
        MTD_DBG_INFO("App code started.\n");
#endif
    }

    return MTD_OK;  /* Ram download is done*/    
}


MTD_STATUS mtdParallelUpdateRamImage(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 ports[],
    IN MTD_U8 appData[],
    IN MTD_U32 appSize, 
    IN MTD_U16 numPorts,
    OUT MTD_U16 erroredPorts[],
    OUT MTD_U16 *errCode)
{
    MTD_U16 i;
    MTD_U16 expectedChecksum;
    MTD_BOOL appStarted;

    *errCode = 0;

    if(numPorts > MAX_PORTS_TO_DOWNLOAD)
    {
        *errCode = MTD_NUM_PORTS_TOO_LARGE;
        return MTD_FAIL;
    }

    for(i = 0; i < numPorts; i++) /* Initialize all port status to no error */   
    {
        erroredPorts[i] = 0;
    }

    /******************************************************************************* 
       Check if the code about to be downloaded can fit into the device's memory
    *******************************************************************************/
    if (appSize > (mtdGetDevMemorySize(devPtr) + MTD_HEADER_SIZE))
    {
        // App size cannot be larger than the device memory size. Code download cannot proceed
#if DB_TEST_FLASHCODE
        MTD_DBG_ERROR("Image is larger than the device memory size!\n");
#endif
        *errCode = MTD_IMAGE_TOO_LARGE_TO_DOWNLOAD; 
        return MTD_FAIL;
    }

    /*******************************************************************************
       This handles downloading the binary part of the HDR file to RAM and executing
       it without modifying the flash.
    *******************************************************************************/
    
    /*******************************************************************************
           Sample of what downloading an HDR file to RAM and executing it would
           look like (non-flash installation or when another image than what's in
           flash is desired to be executed but without changing the flash).
    *******************************************************************************/

    /* Puts phy in download mode, skips over header and downloads binary to RAM
    then starts the app code running, puts PHY in parallel write mode as needed, or when
    reading an MDIO register, removes parallel write mode as needed */
    expectedChecksum = (MTD_U16)appData[MTD_CKSUM_OFFSET] + (((MTD_U16)appData[MTD_CKSUM_OFFSET+1])<<8);    
    ATTEMPT(mtdParallelMdioRamDownload(devPtr,&appData[MTD_HEADER_SIZE],(appSize-MTD_HEADER_SIZE), ports, \
                                       numPorts, erroredPorts,MTD_TRUE,~expectedChecksum,errCode));    
        
    /* make sure the app code started on all ports downloaded */
    for(i = 0; i < numPorts; i++)
    {
        if(erroredPorts[i] == 0)
        {
            TRY_IO(mtdDidPhyAppCodeStart(devPtr,ports[i],&appStarted));
            
            if (appStarted == MTD_FALSE)
            {
#if DB_TEST_FLASHCODE
                MTD_DBG_ERROR("App code did not start on MDIO port %d.\n",(int)ports[i]);
                MTD_DBG_ERROR("App download failed.\n");
#endif             
                erroredPorts[i] = MTD_APP_CODE_DID_NOT_START;
            }
            else
            {
#if DB_TEST_FLASHCODE
                MTD_DBG_INFO("App code started on port %d.\n", (int)ports[i]);
#endif
            }
        }
        else
        {
#if DB_TEST_FLASHCODE
            MTD_DBG_INFO( "Error downloading to port %d, so code not started.\n",(int)ports[i]);        
#endif
        }
        
    }
    
    for(i = 0; i < numPorts; i++)
    {
        if(erroredPorts[i] != 0)
        {
            *errCode = MTD_PAR_DOWNLOAD_FAILED;
            return MTD_FAIL;  /* Parallel Ram download is done, at least one port has error*/
        }
    }

    return MTD_OK;  /* Parallel Ram download is done, successful on all ports*/    
}

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
)
{
    MTD_U16 i;
    MTD_BOOL appStarted;
    
    for(i = 0; i < numPorts; i++) /* initialize to no errors on all ports */
    {
        erroredPorts[i] = 0;
    }

    *errCode = 0; 

    if(numPorts > MAX_PORTS_TO_DOWNLOAD)
    {
        *errCode = MTD_NUM_PORTS_TOO_LARGE;
        return MTD_FAIL;
    }

    /******************************************************************************* 
       Check if the code about to be downloaded can fit into the device's memory
    *******************************************************************************/
    if (appSize > (mtdGetDevMemorySize(devPtr) + MTD_HEADER_SIZE))
    {
        // App size cannot be larger than the device memory size. Code download cannot proceed
#if DB_TEST_FLASHCODE
        MTD_DBG_ERROR("Image is larger than the device memory size!\n");
#endif
        *errCode = MTD_IMAGE_TOO_LARGE_TO_DOWNLOAD; 
        return MTD_FAIL;
    }

    /*******************************************************************************
             Put all ports into download mode on all the chips, this is needed because
             the parallel write will write to all ports on a chip anyways,
             so the firmware will get corrupted in RAM.

             Any port failed will cause the download to stop. errCode will hold result.
    *******************************************************************************/
    ATTEMPT(mtdPutAllPortsInDownloadMode(devPtr, ports, numPorts, errCode));
    
    /*******************************************************************************
             Download slave code to phy's RAM and start it
    *******************************************************************************/
    /* Puts phy in download mode, skips over header and downloads binary to RAM
      then starts the slave code running. If returns MTD_OK, there may be some ports
      that failed to download correctly, they will be stored in erroredPorts and should be skipped. 
      Major error will return MTD_FAIL and errCode will be non-zero and will not move forward. */
    ATTEMPT(mtdParallelMdioRamDownload(devPtr,slaveData,slaveSize, ports, \
                                       numPorts, erroredPorts, MTD_FALSE, 0, errCode));   
        
    /* Parallel download bit should be in the OFF position here (anywhere a "read" takes place) */
    /* Reads must be done in series and results collected */
    /* make sure the slave app code started */
    for(i = 0; i < numPorts; i++)
    {
        if(erroredPorts[i] == 0)
        {
            TRY_IO(mtdDidPhyAppCodeStart(devPtr,ports[i],&appStarted));
            
            if (appStarted == MTD_FALSE)
            {
                MTD_DBG_ERROR("Slave code did not start on MDIO port %d.\n",(int)ports[i]);
                MTD_DBG_ERROR("Port will be skipped.\n");
                erroredPorts[i] = MTD_SLAVE_CODE_DID_NOT_START;            
            }
            else
            {
#if DB_TEST_FLASHCODE
                MTD_DBG_INFO("Slave code started on MDIO port %d.\n", ports[i]);
#endif
            }
        }
        else
        {
#if DB_TEST_FLASHCODE
            MTD_DBG_INFO("Slave code wasn't downloaded to MDIO port %d\n", ports[i]);
#endif
        }        
    }

    /*******************************************************************************
       Write the image to flash with slave's help which is running now. Skip
       any ports that have had an error. Try the ports that haven't had an 
       error.
    *******************************************************************************/

    ATTEMPT(mtdParallelMdioFlashDownload(devPtr, appData, appSize, ports, numPorts, erroredPorts, errCode));    

    /*******************************************************************************
       Let slave verify image
    *******************************************************************************/

    /* Using slave code to verify image.
       This commands slave to read in entire flash image and calculate checksum and make sure
       checksum matches the checksum in the header. A failure means flash was corrupted.
      
       Another method would be to reset the phy (with SPI_CONFIG = 0) and see that the new code
       starts successfully, since a bad checksum will result in the code not being started */
#if DB_TEST_FLASHCODE
    MTD_DBG_INFO("Flash programming complete. Verifying image via slave.\n");
#endif

    TRY_IO(mtdTryParallelSlaveCommand(devPtr, VERIFY_FLASH, ports, numPorts, erroredPorts, MTD_FLASH_ERASE_WRITE));
   
    for(i = 0; i < numPorts; i++)
    {
        if(erroredPorts[i] != 0)
        {
            *errCode = MTD_PAR_DOWNLOAD_FAILED;            
            return MTD_FAIL;  /* at least one port has error*/
        }           
    }

    return MTD_OK;
}


