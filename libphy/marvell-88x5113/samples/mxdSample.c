/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/***********************************************************************
This file contains sample functions code for calling the driver initialization
and loading firmware/ROM images to the Marvell X5113 PHY.

For Reference Only. 
***********************************************************************/

#include "mxdApiTypes.h"
#include "mxdApi.h"
#include "mxdHwCntl.h"
#include "mxdUtils.h"
#include "mxdApiRegs.h"
#include "mxdFwDownload.h"
#include "mxdInitialization.h"
#include "mxdHwSerdesCntl.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MXD_ROM_TYPE            1  /* Serdes/SBus ROM file type */
#define MXD_FIRMWARE_TYPE       2  /* Z80 firmware file type */
#define MXD_Z80_EEPROM_FW_TYPE  3  /* EEPROM Z80 firmware file type */

/* rename these files and locations to match the image filename */
#define MXD_Z80_IMAGE  "..//Scripts//z80_firmware.txt"
#define MXD_Z80_EEPROM_IMAGE  "..//Scripts//z80_EEPROM_firmware.txt"
#define MXD_SBUS_IMAGE "..//Scripts//sbus_master.swap.rom"
#define MXD_SERDES_IMAGE "..//Scripts//serdes.rom"

/******************************************************************************
 MXD_STATUS mxdSampleLoadImageFile
*******************************************************************************/
MXD_STATUS mxdSampleLoadImageFile
(
    IN MXD_U32 fileType,
    IN const MXD_U8 *filename,   /* Full path to a valid firmware image */
    OUT MXD_U16 *rom_size,       /* Address to receive length of image */
    OUT MXD_U16 **rom_ptr        /* Address to receive image */
)
{
    MXD_U16 *rom, addr = 0;
    MXD_U8 mem_buffer[6];
    FILE *file;
    if (!filename)
        return MXD_FAIL;

    file = fopen(filename, "r");

    *rom_ptr = 0;
    *rom_size = 0;

    if( !file )
    {
        return MXD_FAIL;
    }

    fseek(file, 0, SEEK_END);

    /* handled format size of various images */
    if (fileType == MXD_ROM_TYPE || fileType == MXD_FIRMWARE_TYPE)
    {
        *rom_size = (MXD_U16)ftell(file) / 4;
    }
    else if (fileType == MXD_Z80_EEPROM_FW_TYPE)
    {
        *rom_size = (MXD_U16)ftell(file) / 3;
    }
    else
    {
        fclose(file);
        return MXD_FAIL;
    }

    rewind(file);
    if( *rom_size <= 0 )
    {
        fclose(file);
        return MXD_FAIL;
    }

    rom = (MXD_U16*)malloc(sizeof(MXD_U16) * (*rom_size + 2));
    if( !rom )
    {
        *rom_size = 0;
        fclose(file);
        return MXD_FAIL;
    }

    while( fgets(mem_buffer, 6, file) )
    {
        MXD_U8 *ptr;
        rom[addr] = (MXD_U16)strtol(mem_buffer, &ptr, 16);

        if (fileType == MXD_ROM_TYPE)
        {
            if( ptr != mem_buffer+3 && (ptr != mem_buffer+4 || mem_buffer[3] != '\r') )
            {
                fclose(file);
                free(rom);
                MXD_DBG_ERROR("mxdLoadImageFile: Incorrect file format for Serdes/SBus image \n");
                return MXD_FAIL;
            }
        }

        if (fileType == MXD_FIRMWARE_TYPE)
        {    
            if( ptr != mem_buffer+4 && (ptr != mem_buffer+5 || mem_buffer[4] != '\n') )
            {
                fclose(file);
                free(rom);
                MXD_DBG_ERROR("mxdLoadImageFile: Incorrect file format for Z80 MDC/MDIO image \n");
                return MXD_FAIL;
            }
        }

        if (fileType == MXD_Z80_EEPROM_FW_TYPE)
        {    
            if( ptr != mem_buffer+2 && (ptr != mem_buffer+3 || mem_buffer[2] != '\n') )
            {
                fclose(file);
                free(rom);
                MXD_DBG_ERROR("mxdLoadImageFile: Incorrect file format for Z80 EEPROM image \n");
                return MXD_FAIL;
            }
        }

        addr ++;
    }

    *rom_size = addr;

    rom[*rom_size+0] = 0;
    rom[*rom_size+1] = 0;

    fclose(file);
    *rom_ptr = rom;
    return MXD_OK;
}


/******************************************************************************
 MXD_STATUS mxdSampleUnloadDrv
*******************************************************************************/

MXD_STATUS mxdSampleUnloadDrv
(
    IN MXD_DEV_PTR pDev
)
{
    if (pDev && pDev->hostContext)
    {
        free(pDev->hostContext);
    }

#if MXD_ENABLE_SERDES_API
    mxdFreeSerdesDev(pDev);
#endif

    MXD_DBG_INFO("mxdSampleUnloadDrv: Free Dev structure\n");

    return MXD_OK;
}

/******************************************************************************
 MXD_STATUS mxdSampleInitDrv

 MDIO readMdio and writeMdio functions provided in below format required to be
 passed into MXD driver initialization. 

 typedef MXD_STATUS (*FMXD_READ_MDIO)(MXD_DEV_PTR pDev, MXD_U16 mdioPort,
                                      MXD_U16 mmd, MXD_U16 reg, MXD_U16* value);

 typedef MXD_STATUS (*FMXD_WRITE_MDIO)(MXD_DEV_PTR pDev, MXD_U16 mdioPort,
                                       MXD_U16 mmd, MXD_U16 reg, MXD_U16 value);
*******************************************************************************/
MXD_STATUS mxdSampleInitDrv
(
    IN MXD_PVOID pHostContext,  /* optional host context */
    IN MXD_BOOL loadImage,      /* 1:load image; 0:do not load */
    IN FMXD_READ_MDIO  readMdio, 
    IN FMXD_WRITE_MDIO writeMdio,
    OUT MXD_DEV mxdDeviceStruct /* MXD device to be used in all API calls */
)
{
    MXD_U16   port = 0;
    MXD_U16   mdioFirstPort = 0; /* change as needed for the 1st PHY addr  */
    MXD_U16   *pZ80Image;
    MXD_U16   z80Size;
    MXD_U16   *pBusMasterImage;
    MXD_U16   busMasterSize;
    MXD_U16   *pSerdesImage;
    MXD_U16   serdesSize;
    MXD_STATUS retVal = MXD_OK;

    mxdMemSet(&mxdDeviceStruct, 0, (sizeof(MXD_DEV)));

    if (loadImage)
    {
        /* Not all chip requires Z80 f/w */
        mxdSampleLoadImageFile(MXD_FIRMWARE_TYPE, MXD_Z80_IMAGE, &z80Size, &pZ80Image);

        mxdSampleLoadImageFile(MXD_ROM_TYPE, MXD_SBUS_IMAGE, &busMasterSize, &pBusMasterImage);
        mxdSampleLoadImageFile(MXD_ROM_TYPE, MXD_SERDES_IMAGE, &serdesSize, &pSerdesImage);

        /* Not all chip requires Z80 f/w; Set either z80Size=0 or pZ80Image=NULL will skip Z80 download  */
        retVal = mxdInitDriver(readMdio, writeMdio, mdioFirstPort, pZ80Image, z80Size, pBusMasterImage,
                               busMasterSize, pSerdesImage, serdesSize, pHostContext, &mxdDeviceStruct);

        if (pZ80Image)
        {
            free(pZ80Image);
        }
        if (pBusMasterImage)
        {
            free(pBusMasterImage);
        }
        if (pSerdesImage)
        {
            free(pSerdesImage);
        }
    }
    else
    {
        /* initialized the dev structure without loading the ROMs and firmware */
        mxdInitDriver(readMdio, writeMdio, mdioFirstPort, NULL, 0, NULL, 0, NULL, 0, 
                      pHostContext, &mxdDeviceStruct);
    }

    return retVal;
}

/******************************************************************************
 MXD_STATUS mxdSampleUpdateLoadEEPROM

 Sample function to update the EEPROM with the provided images. Both 
 Serdes and SBus images must be provided or all 3 images including the Z80.
 If Z80 image is not provided, set the z80Size size to 0

*******************************************************************************/

MXD_STATUS mxdSampleUpdateLoadEEPROM
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 mdioPort
)
{
    MXD_STATUS retVal = MXD_OK;
    MXD_U16   port = 0;
    MXD_U16   *pZ80Image;
    MXD_U16   z80Size = 0;
    MXD_U16   *pBusMasterImage;
    MXD_U16   busMasterSize = 0;
    MXD_U16   *pSerdesImage;
    MXD_U16   serdesSize = 0;
    MXD_U16   errCode;

    if (!pDev)
    {
        MXD_DBG_INFO("mxdSampleUpdateLoadEEPROM: Error - Null pDev pointer\n");
        return MXD_FAIL;
    }

    /* optional to load Z80; comment out if Z80 is not provided */
    mxdSampleLoadImageFile(MXD_Z80_EEPROM_FW_TYPE, MXD_Z80_EEPROM_IMAGE, &z80Size, &pZ80Image);

    mxdSampleLoadImageFile(MXD_ROM_TYPE, MXD_SBUS_IMAGE, &busMasterSize, &pBusMasterImage);
    mxdSampleLoadImageFile(MXD_ROM_TYPE, MXD_SERDES_IMAGE, &serdesSize, &pSerdesImage);
    
    retVal = mxdUpdateEEPROMImage(pDev, mdioPort, pBusMasterImage, busMasterSize, 
                                  pSerdesImage, serdesSize, pZ80Image, z80Size, &errCode);

    if (pZ80Image)
    {
        free(pZ80Image);
    }
    if (pBusMasterImage)
    {
        free(pBusMasterImage);
    }
    if (pSerdesImage)
    {
        free(pSerdesImage);
    }

    return retVal;
}


/******************************************************************************
 MXD_STATUS mxdSampleSetMode

   Sample code to configure the speed and mode on a MDIO port using the 
   mxdSetModeSelection(). If the configuration is successful, the 
   mxdCheckLinkStatus() is polled to check for the link status.  
*******************************************************************************/
MXD_STATUS mxdSampleSetMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16     mdioPort,
    IN MXD_U16     laneOffset,
    IN MXD_BOOL    perLaneStatus,
    IN MXD_U16     forceReConfig,
    IN MXD_FIXED_OP_MODE  portMode
)
{
    MXD_STATUS status;
    MXD_U16 latchedStatus;
    MXD_U16 i;
    MXD_U16 currentStatus;
    MXD_U16 result;
    MXD_U16 linkCheckDelay;
    MXD_DETAILED_STATUS_TYPE statusDetail;

    /* **Sample**: setting to MXD_MODE_P40KN_P25CN gearbox mode */
    portMode = MXD_MODE_P40KN_P25CN;

    status = mxdSetFixedModeSelection(pDev, mdioPort, laneOffset, portMode, (MXD_BOOL)forceReConfig, &result);

    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSampleSetMode: mxdSetFixedModeSelection failed with result:0x%x\n", result);
        return MXD_FAIL;
    }

    /* Sample: Polling the link status. Refer to MXD_DETAILED_STATUS_TYPE structure for link status details */
    mxdMemSet(&statusDetail, 0, sizeof(MXD_DETAILED_STATUS_TYPE));

    linkCheckDelay = 10;

    for (i=0; i<linkCheckDelay; i++)
    {
        status = mxdCheckLinkStatus(pDev, mdioPort, laneOffset, perLaneStatus, 
                                    &currentStatus, &latchedStatus, &statusDetail);
        if (status == MXD_OK)
        {
            if (currentStatus == MXD_LINK_UP)
            {
                MXD_DBG_INFO("mxdSampleSetMode: link is up in %u seconds\n", i);
                /* refer to the MXD_DETAILED_STATUS_TYPE structure for detail link status */
                break;
            }
        }
        mxdWait(pDev, 1000);
    }

    if ( i >= linkCheckDelay )
    {
        MXD_DBG_INFO("mxdSampleSetMode: link is down\n");
    }

    return status;
}


/******************************************************************************
 MXD_STATUS mxdSampleSetUserMode

   Sample code to configure the speed and mode on a MDIO port using the 
   mxdSetUserFixedModeSelection(). This function provides an option to individually 
   select the operational mode for both host and line interfaces. 
   If the configuration is successful, the mxdCheckLinkStatus() is polled to check 
   for the link status.  

   To set the host and line interfaces mode, provide the operational modes from the
   MXD_OP_CONFIG selection to both the hostMode and the lineMode inputs. 

   Examples:
   - setting Gearbox mode on host:P40KN and line:P25CN:
       set hostMode = MXD_P40KN and lineMode = MXD_P25CN
                 
   - setting Gearbox mode on host:P29P09LN and line:P25CN:
       set hostMode = MXD_P29P09LN and lineMode = MXD_P25CN

*******************************************************************************/
MXD_STATUS mxdSampleSetUserMode
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16     mdioPort,
    IN MXD_U16     laneOffset,
    IN MXD_BOOL    perLaneStatus,
    IN MXD_U16     forceReConfig,
    IN MXD_OP_CONFIG hostMode,
    IN MXD_OP_CONFIG lineMode
)
{
    MXD_STATUS status;
    MXD_U16 latchedStatus;
    MXD_U16 i;
    MXD_U16 currentStatus;
    MXD_U16 result;
    MXD_U16 linkCheckDelay;
    MXD_DETAILED_STATUS_TYPE statusDetail;

    /* ** Sample only **: setting for Host MXD_P40KN and Line MXD_P25CN gearbox mode */
    hostMode = MXD_P40KN;
    lineMode = MXD_P25CN;

    status = mxdSetUserFixedModeSelection(pDev, mdioPort, laneOffset, hostMode, lineMode, 
                                          (MXD_BOOL)forceReConfig, &result);

    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSampleSetUserMode: mxdSetUserFixedModeSelection failed with result:0x%x\n", result);
        return MXD_FAIL;
    }

    /* Sample: Polling the link status. Refer to MXD_DETAILED_STATUS_TYPE structure for link status details */
    mxdMemSet(&statusDetail, 0, sizeof(MXD_DETAILED_STATUS_TYPE));

    linkCheckDelay = 10;

    for (i=0; i<linkCheckDelay; i++)
    {
        status = mxdCheckLinkStatus(pDev, mdioPort, laneOffset, perLaneStatus, &currentStatus, &latchedStatus, &statusDetail);
        if (status == MXD_OK)
        {
            if (currentStatus == MXD_LINK_UP)
            {
                MXD_DBG_INFO("mxdSampleSetUserMode: link is up in %u seconds\n", i);
                /* refer to the MXD_DETAILED_STATUS_TYPE structure for detail link status */
                break;
            }
        }
        mxdWait(pDev, 1000);
    }

    if ( i >= linkCheckDelay )
    {
        MXD_DBG_INFO("mxdSampleSetUserMode: link is down\n");
    }

    return status;
}

#define MXD_AUTONEG_TIMEOUT 1000   /* 1000 msec */
/******************************************************************************
MXD_STATUS mxdSampleSetAutoNegPause

  Sample code performs the following tasks:
  - Sets Advertised Pause type and Restart the Auto negotiation by setting 
    anRestart to MXD_TRUE
  - Waits till the auto negotiation is completed, if times out before completion,
    returns fail.
  - Checks link partner advertised ability
  - Gets advertised Pause type.
  - Gets Pause resolution

Notes:
  This sample code assumes that the proper operation mode has been set and both 
  line and host side links are up. For Grouped OP modes, only lane 0 is valid. 
  For non-grouped OP modes, 4 lanes can perform auto negotiation individually as 
  long as the link is up for that lane.

*******************************************************************************/
MXD_STATUS mxdSampleSetAutoNegPause
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16  mdioPort,
    IN MXD_U16  host_or_line,
    IN MXD_U16  laneOffset,
    IN MXD_U8   pauseType
)
{
    MXD_STATUS status;
    MXD_U16  i;
    MXD_U8   autoNegComplete, lpPauseType;
    MXD_U16  lpSpeedBits;
    MXD_BOOL pauseResolved;
    MXD_BOOL tx_pause_enabled;
    MXD_BOOL rx_pause_enabled;

    /* Sample: Sets Auto negotiation advertised Pause type */
    status = mxdSetPauseAdvertisement(pDev, mdioPort, host_or_line, 
                                      laneOffset, pauseType, MXD_TRUE);

    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSampleSetAutoNegPause: mxdSetPauseAdvertisement failed on MDIO port:%u\n", mdioPort);
        return status;
    }

    /* Sample: Polling Auto negotiation complete status */
    for (i=0; i<MXD_AUTONEG_TIMEOUT; i++)
    {
        mxdWait(pDev, 1);
        /* checks for Autoneg completion */
        status = mxdAutoNegCheckComplete(pDev, mdioPort, host_or_line, laneOffset, &autoNegComplete);
        
        if (status != MXD_OK)
        {
            MXD_DBG_ERROR("mxdSampleSetAutoNegPause: mxdAutoNegCheckComplete failed on MDIO port:%u\n", mdioPort);
            return status;
        }

        if (autoNegComplete == 1)
        {
            /* autoneg completed. Auto-Negotiated speed of line and host has been set by API. 
               No futher action required */
            MXD_DBG_INFO("mxdSampleSetAutoNegPause: autoneg completed in %u msec \n", i);
            break;
        }
    }    
    
    /* Sample: If Auto negotiation complete times out, returns fail */
    if ( i >= MXD_AUTONEG_TIMEOUT )
    {
        MXD_DBG_ERROR("mxdSampleSetAutoNegPause: autoneg timeout on MDIO port%u!\n", mdioPort);
        return MXD_FAIL;
    }

    /* Sample: Retrieves AN resolution */
    status = mxdGetAutoNegResolution(pDev, mdioPort, host_or_line, laneOffset, &lpSpeedBits);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSampleSetAutoNegPause: mxdGetAutoNegResolution failed on MDIO port:%u\n", mdioPort);
        return status;
    }

    MXD_DBG_INFO("mxdSampleSetAutoNegPause: AN Resolution: 0x%x\n", lpSpeedBits);

    /* Sample: Retrieves link partner advertised Pause type */
    status = mxdGetLPAdvertisedPause(pDev, mdioPort, host_or_line, laneOffset, &lpPauseType);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSampleSetAutoNegPause: mxdGetLPAdvertisedPause failed on MDIO port:%u\n", mdioPort);
        return status;
    }

    MXD_DBG_INFO("mxdSampleSetAutoNegPause: Link Partner Pause: %d\n", lpPauseType);

    /* Sample: Gets auto negotiated Pause resolution */
    status = mxdGetTxRxPauseResolution(pDev, mdioPort, host_or_line, laneOffset, 
                                        &pauseResolved, &tx_pause_enabled, &rx_pause_enabled);
    if (status != MXD_OK)
    {
        MXD_DBG_ERROR("mxdSampleSetAutoNegPause: mxdGetTxRxPauseResolution failed on MDIO port:%u\n", mdioPort);
        return status;
    }

    if (!pauseResolved)
    {
        MXD_DBG_INFO("mxdSampleSetAutoNegPause: AutoNeg Pause not resolved on MDIO port%u!\n", 
                     mdioPort);
    }
    else
    {
        MXD_DBG_INFO("mxdSampleSetAutoNegPause: tx_pause_enabled: %d rx_pause_enabled: %d\n", 
                     tx_pause_enabled, rx_pause_enabled);
    }

    return status;
}

#if MXD_ENABLE_SERDES_API
/******************************************************************************
MXD_STATUS mxdSampleGetEye
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 host_or_line,
   IN MXD_U16 laneOffset,
   IN MXD_U16 sampleSize,    
   IN MXD_U16 highDefinition,
   IN MXD_U16 serdesLogLevel
)

 Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    host_or_line - which interface is being read:
                   MXD_HOST_SIDE
                   MXD_LINE_SIDE
    laneOffset - 0..3 for lanes 0-3.
    sampleSize - The eye sample size based on the max dwell bit.
                       Range [4 to 8] where x is the exponential 
                       e.g. 4 = 10,000; 8 = 100,000,000 
    highDefinition - MXD_DISABLE: disable high resolution; 
                     MXD_ENABLE: enable high definition
                     The high definition option increases the y resolution to 1 step
    serdesLogLevel - The level of logging in the serdes APIs
                     Range [0 - 15]. Set to 0 when not debugging. 

 Outputs:
    None

 Returns:
    Returns MXD_OK if execution is successful, MXD_FAIL otherwise
    
 Description:
    Sample code to extract the Eye diagram by calling the mxdSerdesGetEye API. 
    Refer to the mxdSerdesGetEye function prototype for details on the parameters.

 Side effects:
    None

 Notes/Warnings:
    The caller to mxdSerdesGetEye() must call mxdWrapperEyeAllocDataSt() to allocate  
    the pEyeData buffer memory before passing in the pEyeData pointer. The caller 
    must free the pEyeData by calling mxdWrapperEyeFreeDataSt() after processing 
    the eye data.

    If pCal is running before plotting the eye, the pCal must be disabled before 
    plotting the eye.  After completion, the pCal DFE tuning needs to be re-enabled 
    after eye measurement.

*******************************************************************************/
MXD_STATUS mxdSampleGetEye
(
   IN MXD_DEV_PTR pDev,
   IN MXD_U16 host_or_line,
   IN MXD_U16 laneOffset,
   IN MXD_U16 sampleSize,    
   IN MXD_U16 highDefinition,
   IN MXD_U16 serdesLogLevel
)
{
    MXD_U16 sAddr;   /* Refer to mxdMappedSerdesIDs for more info */      
    MXD_SER_EYE_DATA_TYPE *eyeDataBuf = (MXD_SER_EYE_DATA_TYPE*)NULL;
    MXD_STATUS status;
    MXD_BOOL dfeStatusPCalInProgress, dfeStatusRunPCal;
    MXD_BOOL tempVal;
    MXD_U16 i;
    MXD_U16 waitTimeOut = 10;
    double db;
    double td;
    const double q06 = 4.74;
    const double q10 = 6.36;
    const double q12 = 7.03;
    const double q15 = 7.94;
    const double q17 = 8.49;
    MXD_BOOL pCalConfig = MXD_FALSE; /* Disabled pCal only if pCal is running.
                                        The pCal must be re-enabled after eye plotting */

    if (host_or_line == MXD_HOST_SIDE)
    {
        sAddr = pDev->serdesID[MXD_HOST_MODE_IDX][laneOffset];
    }
    else if (host_or_line == MXD_LINE_SIDE)
    {
        sAddr = pDev->serdesID[MXD_LINE_MODE_IDX][laneOffset];
    }
    else
    {
        MXD_DBG_ERROR("mxdSampleGetEye incorrect Host/Line interface: %u\n", host_or_line);
    }


    /* run a status check on the pCal if it's running */
    mxdSerdesGetRxDFEStatus(pDev, sAddr, &tempVal, &dfeStatusPCalInProgress, 
                        &tempVal, &tempVal, &dfeStatusRunPCal, &tempVal);

    /* Disabled pCal only if pCal is running. The pCal will be re-enabled after eye plotting */
    if (dfeStatusPCalInProgress && dfeStatusRunPCal)
    {
        /* Disabled pCal */
        mxdSerdesTune_pCal(pDev, sAddr, MXD_DFE_STOP_ADAPTIVE);  
        pCalConfig = MXD_TRUE;

        for (i=0; i<waitTimeOut; i++)
        {
            mxdSerdesGetRxDFEStatus(pDev, sAddr, &tempVal, &dfeStatusPCalInProgress, 
                                    &tempVal, &tempVal, &dfeStatusRunPCal, &tempVal);
        
            if ((dfeStatusPCalInProgress == MXD_FALSE) && (dfeStatusRunPCal == MXD_FALSE))
            {
                MXD_DBG_INFO(" ****** pCal disabled in %u00 msec\n", i);
                break;
            }
            mxdWait(pDev, 100);
        }

        if (i >= waitTimeOut) 
        {
            MXD_DBG_INFO(" ****** pCal FAILED to disabled in %u00 msec\n", i);
        }
    }

    /* call mxdWrapperEyeAllocDataSt to malloc the memory for the eye data structure */
    eyeDataBuf = mxdWrapperEyeAllocDataSt((MXD_SER_DEV_PTR)pDev->serdesDev);

    status = mxdSerdesGetEye(pDev, sAddr, sampleSize, highDefinition, serdesLogLevel, eyeDataBuf);

    /* Re-enabled pCal only if pCal was earlier disabled */
    if (pCalConfig)
    {
        /* run a status check on the pCal before re-enabling it */
        mxdSerdesGetRxDFEStatus(pDev, sAddr, &tempVal, &dfeStatusPCalInProgress, 
                                &tempVal, &tempVal, &dfeStatusRunPCal, &tempVal);

        mxdSerdesTune_pCal(pDev, sAddr, MXD_DFE_START_ADAPTIVE);

        for (i=0; i<waitTimeOut; i++)
        {
            mxdSerdesGetRxDFEStatus(pDev, sAddr, &tempVal, &dfeStatusPCalInProgress, 
                                    &tempVal, &tempVal, &dfeStatusRunPCal, &tempVal);
        
            if ((dfeStatusPCalInProgress == MXD_TRUE) && (dfeStatusRunPCal == MXD_TRUE))
            {
                MXD_DBG_INFO(" ****** pCal enabled in %u00 msec\n", i);
                break;
            }
            mxdWait(pDev, 100);
        }

        if (i >= waitTimeOut) 
        {
            MXD_DBG_INFO(" ****** pCal FAILED to enabled in %u00 msec\n", i);
        }
    }

    db = eyeDataBuf->ed_vbtc.dc_balance;

    MXD_DBG_INFO("x.UI:         %3d\n",eyeDataBuf->ed_x_UI);
    MXD_DBG_INFO("x.resolution: %3d\n",eyeDataBuf->ed_x_resolution);
    MXD_DBG_INFO("x.points:     %3d\n",eyeDataBuf->ed_x_points);
    MXD_DBG_INFO("x.min:        %3d\n",eyeDataBuf->ed_x_min);
    MXD_DBG_INFO("x.max:        %3d\n",eyeDataBuf->ed_x_max);
    MXD_DBG_INFO("x.step:       %3d\n",eyeDataBuf->ed_x_step);
    MXD_DBG_INFO("x.center:     %3d\n",(eyeDataBuf->ed_x_min + eyeDataBuf->ed_x_max) / 2);
    MXD_DBG_INFO("x.width:      %3d\n",eyeDataBuf->ed_width);
    MXD_DBG_INFO("x.width_mUI:  %3d\n",eyeDataBuf->ed_width_mUI);
    MXD_DBG_INFO("\n");

    MXD_DBG_INFO("y.resolution: %3d (DAC points)\n",eyeDataBuf->ed_y_resolution);
    MXD_DBG_INFO("y.points:     %3d\n",eyeDataBuf->ed_y_points);
    MXD_DBG_INFO("y.step:       %3d\n",eyeDataBuf->ed_y_step);
    MXD_DBG_INFO("y.min:        %3d (DAC for y=0)\n",eyeDataBuf->ed_y_min);
    MXD_DBG_INFO("y.mission_points: %3d\n",eyeDataBuf->ed_y_mission_points);
    MXD_DBG_INFO("y.mission_step:   %3d\n",eyeDataBuf->ed_y_mission_step);
    MXD_DBG_INFO("y.mission_min:    %3d (DAC for y=0)\n",eyeDataBuf->ed_y_mission_min);

    MXD_DBG_INFO("y.center:     %3d (DAC middle)\n",eyeDataBuf->ed_y_min + eyeDataBuf->ed_y_points / 2 * eyeDataBuf->ed_y_step);
    MXD_DBG_INFO("y.height:     %3d\n",eyeDataBuf->ed_height);
    MXD_DBG_INFO("y.height_mV:  %3d\n",eyeDataBuf->ed_height_mV);
    MXD_DBG_INFO("\n");

    MXD_DBG_INFO("dc_balance:    %6.2g\n", eyeDataBuf->ed_dc_balance);
    MXD_DBG_INFO("trans_density: %6.2g\n", eyeDataBuf->ed_trans_density);
    MXD_DBG_INFO("error_threshold: %d\n",  eyeDataBuf->ed_error_threshold);
    MXD_DBG_INFO("min_dwell_bits:  %g\n",  eyeDataBuf->ed_min_dwell_bits*1.0);
    MXD_DBG_INFO("max_dwell_bits:  %g\n",  eyeDataBuf->ed_max_dwell_bits*1.0);
    MXD_DBG_INFO("fast_dynamic:    %d\n",  eyeDataBuf->ed_fast_dynamic);
    MXD_DBG_INFO("\n");

    if (eyeDataBuf->ed_vbtc.data_column < 0)
        MXD_DBG_INFO("# Vertical Bathtub Curve (mission data channel %d..%d eye):\n", -1-eyeDataBuf->ed_vbtc.data_column, 0-eyeDataBuf->ed_vbtc.data_column);
    else if (eyeDataBuf->ed_vbtc.data_column == eyeDataBuf->ed_vbtc.total_columns / 2)
        MXD_DBG_INFO("# Vertical Bathtub Curve (calculated phase center):\n");
    else
        MXD_DBG_INFO("# Vertical Bathtub Curve (calculated phase center %+d):\n", eyeDataBuf->ed_vbtc.data_column - eyeDataBuf->ed_vbtc.total_columns / 2);

    if (eyeDataBuf->ed_vbtc.points)
    {

        if (eyeDataBuf->ed_vbtc.bottom_R_squared < 0.95 || eyeDataBuf->ed_vbtc.top_R_squared < 0.95 ||
            eyeDataBuf->ed_vbtc.bottom_slope <= 0.0 || eyeDataBuf->ed_vbtc.top_slope >= 0.0)
            MXD_DBG_INFO("#\n# WARNING: This projection is based on measurements with poor correlation.\n#\n");

        MXD_DBG_INFO("BER/%g = Q at eye height of  0 mV: %4.2e, %5.2f\n", db, eyeDataBuf->ed_vbtc.vert_ber_0mV, eyeDataBuf->ed_vbtc.height_0mV);
        MXD_DBG_INFO("BER/%g = Q at eye height of 25 mV: %4.2e, %5.2f\n", db, eyeDataBuf->ed_vbtc.vert_ber_25mV, eyeDataBuf->ed_vbtc.height_25mV);

        if (eyeDataBuf->ed_vbtc.Vmean > 0)
            MXD_DBG_INFO("Eye height (Vmean) at %g BER=Q(%4.2f): %3d mV\n",db,0.0,eyeDataBuf->ed_vbtc.Vmean);

        MXD_DBG_INFO("Eye height at 1e-06 BER/%g = Q(%4.2f): %3d mV\n",db,q06,eyeDataBuf->ed_vbtc.vert_eye_1e06);
        MXD_DBG_INFO("Eye height at 1e-10 BER/%g = Q(%4.2f): %3d mV\n",db,q10,eyeDataBuf->ed_vbtc.vert_eye_1e10);
        MXD_DBG_INFO("Eye height at 1e-12 BER/%g = Q(%4.2f): %3d mV\n",db,q12,eyeDataBuf->ed_vbtc.vert_eye_1e12);
        MXD_DBG_INFO("Eye height at 1e-15 BER/%g = Q(%4.2f): %3d mV\n",db,q15,eyeDataBuf->ed_vbtc.vert_eye_1e15);
        MXD_DBG_INFO("Eye height at 1e-17 BER/%g = Q(%4.2f): %3d mV\n",db,q17,eyeDataBuf->ed_vbtc.vert_eye_1e17);
        MXD_DBG_INFO("Slope bottom/top:       %6.2f, %6.2f mV/Q\n", eyeDataBuf->ed_vbtc.bottom_slope, eyeDataBuf->ed_vbtc.top_slope);
        MXD_DBG_INFO("X-intercept bottom/top: %6.2f, %6.2f    Q\n", eyeDataBuf->ed_vbtc.bottom_intercept, eyeDataBuf->ed_vbtc.top_intercept);
        MXD_DBG_INFO("Indexes bottom/top:     %6u, %6u\n",eyeDataBuf->ed_vbtc.bottom_index,eyeDataBuf->ed_vbtc.top_index);
        MXD_DBG_INFO("R-squared fit bottom/top:%5.2f, %6.2f\n", eyeDataBuf->ed_vbtc.bottom_R_squared, eyeDataBuf->ed_vbtc.top_R_squared);
        MXD_DBG_INFO("Est RJrms bottom/top:   %7.3f, %6.3f  mV\n", eyeDataBuf->ed_vbtc.bottom_rj, eyeDataBuf->ed_vbtc.top_rj);
        MXD_DBG_INFO("Est signal noise ratio: %6.2f\n", eyeDataBuf->ed_vbtc.snr);
    }


    td = eyeDataBuf->ed_hbtc.trans_density;

    MXD_DBG_INFO("\n");
    if( eyeDataBuf->ed_hbtc.data_row == eyeDataBuf->ed_hbtc.total_rows/2 )
        MXD_DBG_INFO("# Horizontal Bathtub Curve for center eye:\n");
    else
        MXD_DBG_INFO("# Horizontal Bathtub Curve for eye at %+d mV (%+d rows) from center:\n", eyeDataBuf->ed_hbtc.data_millivolts, eyeDataBuf->ed_hbtc.data_row-eyeDataBuf->ed_hbtc.total_rows/2);
    if( eyeDataBuf->ed_hbtc.points)
    {

        if( eyeDataBuf->ed_hbtc.left_R_squared < 0.95 || eyeDataBuf->ed_hbtc.right_R_squared < 0.95 ||
            eyeDataBuf->ed_hbtc.left_slope <= 0.0 || eyeDataBuf->ed_hbtc.right_slope >= 0.0 )
            MXD_DBG_INFO("#\n# WARNING: This projection is based on measurements with poor correlation.\n#\n");

        MXD_DBG_INFO("BER/%g = Q at eye width of   0 mUI: %4.2e, %5.2f\n", td, eyeDataBuf->ed_hbtc.horz_ber_0mUI, eyeDataBuf->ed_hbtc.width_0mUI);
        MXD_DBG_INFO("BER/%g = Q at eye width of 100 mUI: %4.2e, %5.2f\n", td, eyeDataBuf->ed_hbtc.horz_ber_100mUI, eyeDataBuf->ed_hbtc.width_100mUI);
        MXD_DBG_INFO("Eye width at 1e-06 BER/%g = Q(%4.2f): %3d mUI\n", td, q06, eyeDataBuf->ed_hbtc.horz_eye_1e06);
        MXD_DBG_INFO("Eye width at 1e-10 BER/%g = Q(%4.2f): %3d mUI\n", td, q10, eyeDataBuf->ed_hbtc.horz_eye_1e10);
        MXD_DBG_INFO("Eye width at 1e-12 BER/%g = Q(%4.2f): %3d mUI\n", td, q12, eyeDataBuf->ed_hbtc.horz_eye_1e12);
        MXD_DBG_INFO("Eye width at 1e-15 BER/%g = Q(%4.2f): %3d mUI\n", td, q15, eyeDataBuf->ed_hbtc.horz_eye_1e15);
        MXD_DBG_INFO("Eye width at 1e-17 BER/%g = Q(%4.2f): %3d mUI\n", td, q17, eyeDataBuf->ed_hbtc.horz_eye_1e17);
        MXD_DBG_INFO("Slope left/right:       %6.2f, %6.2f Q/UI\n", eyeDataBuf->ed_hbtc.left_slope, eyeDataBuf->ed_hbtc.right_slope);
        MXD_DBG_INFO("Y-intercept left/right: %6.2f, %6.2f    Q\n", eyeDataBuf->ed_hbtc.left_intercept, eyeDataBuf->ed_hbtc.right_intercept);
        MXD_DBG_INFO("Indexes left/right:     %6u, %6u\n",eyeDataBuf->ed_hbtc.left_index,eyeDataBuf->ed_hbtc.right_index);
        MXD_DBG_INFO("R-squared fit left/right:%5.2f, %6.2f\n", eyeDataBuf->ed_hbtc.left_R_squared, eyeDataBuf->ed_hbtc.right_R_squared);
        MXD_DBG_INFO("Est RJrms left/right:   %7.3f, %6.3f mUI\n",  eyeDataBuf->ed_hbtc.left_rj, eyeDataBuf->ed_hbtc.right_rj);
        MXD_DBG_INFO("Est DJpp:               %7.3f  mUI\n", eyeDataBuf->ed_hbtc.dj);
        MXD_DBG_INFO("Est signal noise ratio: %6.2f\n", eyeDataBuf->ed_hbtc.snr);
    }

    /* eyeDataBuf must be freed */
    mxdWrapperEyeFreeDataSt((MXD_SER_DEV_PTR)pDev->serdesDev, eyeDataBuf);

    return status;
}

/******************************************************************************
 static void mxdTapReq
    Function used in mxdSerdesPMDTrainingLog 
*******************************************************************************/

static void mxdTapReq(uint request, uint tap, char *str)
{
    if (request & 0x2000)
        strcpy(str,(tap > 0) ? " " : "PRESET");
    else if (request & 0x1000)
        strcpy(str,(tap > 0) ? " " : "INITIALIZE");
    else
        switch( (request >> (tap*2)) & 0x3 )
        {
        case 0  : {strcpy(str,"HOLD"); break;}
        case 1  : {strcpy(str,"INC");  break;}
        case 2  : {strcpy(str,"DEC");  break;}
        default : {strcpy(str,"RSVD"); break;}
        }
}

/******************************************************************************
 MXD_STATUS mxdSamplePMDTrainingLog

   Sample code to extract the Training Log by calling the mxdSerdesPMDTrainingLog 
   API. Refer to the mxdSerdesPMDTrainingLog function prototype for details on 
   the parameters.

    Inputs:
    pDev - pointer to MXD_DEV initialized by mxdInitDriver() call
    sAddr - SerDes lane addr. Range[1-8]; 
            Refer to SerdesID and mxdMappedSerdesIDs for more info on the 
            mapping of SerdesID and Host/Line lane offset          
*******************************************************************************/
MXD_STATUS mxdSamplePMDTrainingLog
(
    IN MXD_DEV_PTR pDev,
    IN MXD_U16 sAddr
)
{
    MXD_TRAINING_INFO trainInfo;
    int i,j;
    char rem[3][12];
    char loc[3][12];

    mxdSerdesPMDTrainingLog(pDev, sAddr, &trainInfo);

    MXD_DBG_INFO("Rx Eq Metric: %d (0x%04x)\n",trainInfo.rx_metric,trainInfo.rx_metric);
    MXD_DBG_INFO("+------+----------------------+----------------------+\n");
    MXD_DBG_INFO("| %4s | %20s | %20s |\n"," ","Remote Tx Requests","Local Tx Requests");
    MXD_DBG_INFO("| %4s | %6s %6s %6s | %6s %6s %6s |\n","REQ","PRE","CURSOR","POST","PRE","CURSOR","POST");
    MXD_DBG_INFO("+------+----------------------+----------------------+\n");
    MXD_DBG_INFO("| %4s | %6d %6s %6s | %6d %6s %6s |\n",
        "PRE",
        trainInfo.remote.preset, " ", " ",
        trainInfo.local.preset, " ", " ");
    MXD_DBG_INFO("| %4s | %6d %6s %6s | %6d %6s %6s |\n",
        "INIT",
        trainInfo.remote.initialize, " ", " ",
        trainInfo.local.initialize, " ", " ");
    MXD_DBG_INFO("| %4s | %6d %6d %6d | %6d %6d %6d |\n",
        "INC",
        trainInfo.remote.tap[0].inc,
        trainInfo.remote.tap[1].inc,
        trainInfo.remote.tap[2].inc,
        trainInfo.local.tap[0].inc,
        trainInfo.local.tap[1].inc,
        trainInfo.local.tap[2].inc);
    MXD_DBG_INFO("| %4s | %6d %6d %6d | %6d %6d %6d |\n",
        "DEC",
        trainInfo.remote.tap[0].dec,
        trainInfo.remote.tap[1].dec,
        trainInfo.remote.tap[2].dec,
        trainInfo.local.tap[0].dec,
        trainInfo.local.tap[1].dec,
        trainInfo.local.tap[2].dec);
    MXD_DBG_INFO("| %4s | %6d %6d %6d | %6d %6d %6d |\n",
        "MAX",
        trainInfo.remote.tap[0].max,
        trainInfo.remote.tap[1].max,
        trainInfo.remote.tap[2].max,
        trainInfo.local.tap[0].max,
        trainInfo.local.tap[1].max,
        trainInfo.local.tap[2].max);
    MXD_DBG_INFO("| %4s | %6d %6d %6d | %6d %6d %6d |\n",
        "MIN",
        trainInfo.remote.tap[0].min,
        trainInfo.remote.tap[1].min,
        trainInfo.remote.tap[2].min,
        trainInfo.local.tap[0].min,
        trainInfo.local.tap[1].min,
        trainInfo.local.tap[2].min);
    MXD_DBG_INFO("+------+----------------------+----------------------+\n");
    for (i=0; i<8; i++)
    {
        for (j=0; j<3; j++)
        {
            mxdTapReq(trainInfo.last_remote_request[i],j,rem[j]);
            if (i > 0)
                strcpy(loc[j]," ");
            else
                mxdTapReq(trainInfo.last_local_request,j,loc[j]);
        }
        MXD_DBG_INFO("| %4s | %6s %6s %6s | %6s %6s %6s |\n",
            "CMD",
            rem[0],
            rem[1],
            rem[2],
            loc[0],
            loc[1],
            loc[2]);
    }
    MXD_DBG_INFO("+------+----------------------+----------------------+\n");

    return MXD_OK;
}
#endif